#include "ksglobal.h"
#include "soyal/soyal_pub.h"
#include "ksgateway.h"
#include "bit_endian.h"
#include <ace/ACE.h>
#include <ace/File_Lock.h>
#include <ace/CDR_Stream.h>
#include <ace/Proactor.h>
#include "xutils/xstring.h"
#include "netutil.h"

int SOYALDEV::GetMacChk(DataPack *pDataPack,int datalen,byte &xorchk,byte &sumchk)
{
	short sum=0;
	xorchk=0xFF;
	sumchk=0;

	xorchk ^= pDataPack->destid ^ pDataPack->cmdcode;
	sum += pDataPack->destid + pDataPack->cmdcode ;

	for(int i = 0;i<datalen;i++)
	{
		xorchk ^= pDataPack->data[i];
		sum += pDataPack->data[i];
	}
	sumchk = (sum + xorchk) & 0xFF;
	return 0;
}
int SOYALDEV::GetSendBuf(DataPack *pDataPack,byte *pBuf,int datalen)
{
	//assert(pBuf == NULL);
	pBuf[0] = pDataPack->head;
	pBuf[1] = pDataPack->len;
	pBuf[2] = pDataPack->destid;
	pBuf[3] = pDataPack->cmdcode;

	if(datalen)
	{	
		memcpy(pBuf+4,pDataPack->data,datalen);
	}
	pBuf[4+datalen] = pDataPack->xorchk;
	pBuf[5+datalen] = pDataPack->sumchk;
	pBuf[datalen + 6] = 0;
	return datalen + 6;
}

int SOYALDEV::SendRev(ACE_HANDLE handler,DataPack *pDataPack,int datalen,byte *recvbuf,size_t &recvlen)
{
	byte buf[256]="";
	byte xorchk0,sumchk0;
	byte xorchk1=0xFF,xorchk2;
	byte sumchk1=0,sumchk2;
	short summac=0;
	int len = 0;
	int ret =0;

	GetMacChk(pDataPack,datalen,xorchk0,sumchk0);
	pDataPack->xorchk = xorchk0;
	pDataPack->sumchk = sumchk0;

	len = GetSendBuf(pDataPack,buf,datalen);

	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	ret = KSGNetUtil::send_buffer(handler,buf,len,&tv);
	if(ret)
		return ret;

	memset(buf,0,sizeof buf);

	recvlen = 2;										// ����2���ֽ�ͷ
	ret = KSGNetUtil::recv_buffer_n(handler,buf,recvlen);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"recv_buffer head err[%d],recvlen[%d]",ret,recvlen));
		return -1;
	}
	//len = buf[1];
	recvlen = buf[1];
	ret = KSGNetUtil::recv_buffer_n(handler,buf,recvlen);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"recv_buffer body err[%d],recvlen[%d]",ret,recvlen));
		return -1;
	}

	// xor ,sum У��
	for (int i = 0;i<recvlen-2;i++)
	{
		xorchk1 ^= buf[i];
		summac += buf[i];
	}
	summac += xorchk1;
	sumchk1 = summac & 0xFF;

	xorchk2 = buf[recvlen-2];
	sumchk2 = buf[recvlen-1];

	if(xorchk1 != xorchk2 || sumchk1 != sumchk2)
	{
		ACE_DEBUG((LM_ERROR,"check err,calxorchk[%d],calsumchk[%d],recvxorchk[%d],recvsumchk[%d]",
			xorchk1,sumchk1,xorchk2,sumchk2));
		return -1;
	}

	memcpy(recvbuf,buf,recvlen);
	return 0;
}

// Delete card data��if want all clear��AddrH �� AddrL �� Records ar 00
int SOYALDEV::ClearCardData(ACE_HANDLE handler,int ctrlid,short cardaddr,bool delall)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;	
	mydatapack.destid = ctrlid;	
	mydatapack.len = 0x07;
	mydatapack.cmdcode = 0x31;	

	datalen = 3;
	if(!delall)
	{
		SHORT_2_BUF_BE(cardaddr,mydatapack.data);					// ���Ŷ�Ӧ�ĵ�ַ
		mydatapack.data[2] = 0x01;
	}

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;
	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"ClearCardData ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}
	return 0;
}
int SOYALDEV::SetCardData(ACE_HANDLE handler,int ctrlid,DownCard_info info,int cardtype)
{
	int ret = 0;
	byte recvbuf[256]="";
	char tmp[3]="";
	size_t recvlen =0;
	int datalen = 0;
	
	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;	
	mydatapack.destid = ctrlid;	
	mydatapack.len = 0x14;
	mydatapack.cmdcode = 0x29;	

	datalen = 16;
	SHORT_2_BUF_BE(info.cardaddr,mydatapack.data);			// ��ַ	
	mydatapack.data[2] = 0x01;								// 1����¼	
	//SHORT_2_BUF_BE(passwd,&mydatapack.data[3]);			// ����	��ֻ֧��4λ��

	// mf������Ÿ���ǰ�������ˣ������Ϳ��Ժ�cpu��ͳһ��,�ֻ���ȡ��8λ
	memcpy(tmp,info.phyno+4,2);
	mydatapack.data[5] = strtoul(tmp,NULL,16);

	memcpy(tmp,info.phyno+6,2);
	mydatapack.data[6] = strtoul(tmp,NULL,16);

	memcpy(tmp,info.phyno,2);
	mydatapack.data[7] = strtoul(tmp,NULL,16);

	memcpy(tmp,info.phyno+2,2);
	mydatapack.data[8] = strtoul(tmp,NULL,16);		

	mydatapack.data[9] = 0x44;						// mode,ֻ��ͨ��ˢ������
	mydatapack.data[10] = 0xFF;						// group set

	// ����ʱ��
	mydatapack.data[11] = info.expdate[0];			// ��
	mydatapack.data[12] = info.expdate[1];			// �·�
	mydatapack.data[13] = info.expdate[2];			// ��

	mydatapack.data[14] = 0x00;						// time zone
	mydatapack.data[15] = 0x00;						// level
	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;
	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"SetCardData ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}

	return 0;
}

int SOYALDEV::SetGroupSet(ACE_HANDLE handler,int ctrlid,DownCard_info info)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;	
	mydatapack.destid = ctrlid;	
	mydatapack.cmdcode = 0x57;	
	
	SHORT_2_BUF_BE(info.cardaddr,mydatapack.data);			// ��ַ	
	mydatapack.data[2] = info.mapping[0];					// 1-8��ͷ��Ȩ��
	mydatapack.data[3] = info.mapping[1];					// 9-16��ͷ��Ȩ��

#ifdef KSG_SOYAL_4_BYTE
	mydatapack.len = 0x48;
	datalen = 68;
	for(int i=0;i<64;i++)
#else
	mydatapack.len = 0x18;
	datalen = 20;
	for(int i=0;i<16;i++)									//��ͷ1-16��time zone
#endif
	{
		mydatapack.data[4+i] = info.timezone[i];
	}

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;
	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"SetGroupSet ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}

	return 0;
}

int SOYALDEV::DeleteCtrlMsg(ACE_HANDLE handler,int ctrlid,bool delall)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;	
	mydatapack.destid = ctrlid;

	if(delall)
	{
		datalen = 6;
		mydatapack.len = 0x0A;
		mydatapack.cmdcode = 0x2D;
		memcpy(mydatapack.data,"DELALL",datalen);
	}
	else
	{
		datalen = 3;
		mydatapack.len = 0x07;
		mydatapack.cmdcode = 0x37;
		memcpy(mydatapack.data,"DEL",datalen);
	}	

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;

	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"DeleteCtrlMsg ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}
	return 0;
}

int SOYALDEV::ReadCtrlMsg(ACE_HANDLE handler,int ctrlid,CtrlMsg &ctrlmsg,int cardtype)
{
	int ret = 0;
	byte recvbuf[256]="";
	byte byte1,byte2,byte3,byte4;
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	Datetime_str datetime;
	memset(&mydatapack,0,sizeof mydatapack);
	memset(&datetime,0,sizeof datetime);

	memset(&ctrlmsg,0,sizeof ctrlmsg);

	mydatapack.head = 0x7E;
	mydatapack.len = 0x04;
	mydatapack.destid = ctrlid;
	mydatapack.cmdcode = 0x25;

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;

	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"ReadCtrlMsg ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}

	if(recvlen < 32)		//�����Ѿ�������
	{
		ACE_DEBUG((LM_INFO,"������[%d]��ˮ�Ѿ��ɼ���",ctrlid));
		return -2;
	}

	memcpy(&datetime,recvbuf+3,sizeof datetime);
	ACE_DEBUG((LM_DEBUG,"ˢ��ʱ�� : [20%d-%d-%d %d:%d:%d],week : [%d]",
		datetime.year,datetime.mon,datetime.day,datetime.hr,datetime.min,datetime.sec,datetime.week));

	sprintf(ctrlmsg.date,"20%02d%02d%02d",datetime.year,datetime.mon,datetime.day);
	sprintf(ctrlmsg.time,"%02d%02d%02d",datetime.hr,datetime.min,datetime.sec);

	byte1 = recvbuf[22];
	byte2 = recvbuf[21];
	byte3 = recvbuf[18];
	byte4 = recvbuf[17];
	/*
	if(cardtype==0)				
		sprintf(ctrlmsg.phyno,"%02X%02X%02X%02X",byte1,byte2,byte3,byte4);
	else					// cpu��
	*/
	sprintf(ctrlmsg.phyno,"%02X%02X%02X%02X",byte4,byte3,byte2,byte1);

	ctrlmsg.termid = recvbuf[10];		//����
	ctrlmsg.txmark = recvbuf[1];		//�¼�
	byte3 = recvbuf[19];				//�ź�

	ACE_DEBUG((LM_DEBUG,"������[%s],��ͷ[%d],�¼�[%d],�ź�[%d]\n",ctrlmsg.phyno,ctrlmsg.termid,ctrlmsg.txmark,byte3));
	return 0;
}

int SOYALDEV::TimeGroupToBuf(TimeGroup timegroup,byte *buf)
{
	char tmp[3]="";
	SHORT_2_BUF_BE(timegroup.sun_timesec.begin_time,tmp);
	memcpy(buf,tmp,2);
	SHORT_2_BUF_BE(timegroup.sun_timesec.end_time,tmp);
	memcpy(buf+2,tmp,2);

	SHORT_2_BUF_BE(timegroup.mon_timesec.begin_time,tmp);
	memcpy(buf+4,tmp,2);
	SHORT_2_BUF_BE(timegroup.mon_timesec.end_time,tmp);
	memcpy(buf+6,tmp,2);

	SHORT_2_BUF_BE(timegroup.tues_timesec.begin_time,tmp);
	memcpy(buf+8,tmp,2);
	SHORT_2_BUF_BE(timegroup.tues_timesec.end_time,tmp);
	memcpy(buf+10,tmp,2);

	SHORT_2_BUF_BE(timegroup.wed_timesec.begin_time,tmp);
	memcpy(buf+12,tmp,2);
	SHORT_2_BUF_BE(timegroup.wed_timesec.end_time,tmp);
	memcpy(buf+14,tmp,2);

	SHORT_2_BUF_BE(timegroup.thur_timesec.begin_time,tmp);
	memcpy(buf+16,tmp,2);
	SHORT_2_BUF_BE(timegroup.thur_timesec.end_time,tmp);
	memcpy(buf+18,tmp,2);

	SHORT_2_BUF_BE(timegroup.fri_timesec.begin_time,tmp);
	memcpy(buf+20,tmp,2);
	SHORT_2_BUF_BE(timegroup.fri_timesec.end_time,tmp);
	memcpy(buf+22,tmp,2);

	SHORT_2_BUF_BE(timegroup.sat_timesec.begin_time,tmp);
	memcpy(buf+24,tmp,2);
	SHORT_2_BUF_BE(timegroup.sat_timesec.end_time,tmp);
	memcpy(buf+26,tmp,2);

	return 0;
}
int SOYALDEV::SetTimeZone(ACE_HANDLE handler,int ctrlid,int zoneidx,int zonelink,TimeGroup timegroup)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;
	mydatapack.len = 0x24;
	mydatapack.destid = ctrlid;
	mydatapack.cmdcode = 0x2A;

	mydatapack.data[0]= zoneidx;			//Set time zone 
	mydatapack.data[1]= 0x01;				//Set some time zones��advance for No.1

	if(zonelink ==0)
		zonelink = 0x40;					//(Link)  (0x40:END.)
	else
		zonelink += 1;
	mydatapack.data[2]= zonelink;			
	mydatapack.data[3]= 0x00;				//level

	datalen = sizeof timegroup;
	//memcpy(mydatapack.data + 4,(char*)&timegroup,datalen);
	TimeGroupToBuf(timegroup,mydatapack.data+4);

	//mydatapack.data[datalen + 4]= 0x00;		//reserved
	//mydatapack.data[datalen + 5]= 0x00;		//reserved

	ret = SendRev(handler,&mydatapack,datalen+4,recvbuf,recvlen);
	if(ret)
		return ret;

	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"SetTimeZone ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}

	return 0;
}

int SOYALDEV:: CtrlReader(ACE_HANDLE handler,int ctrlid,int reader,int flag)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;
	int cmdcode = 0;			// 0x82: ����,0x83:���ţ�0x84:����һ��

	if(flag == 0)
		cmdcode = 0x83;				// ����
	else if(flag ==1)
		cmdcode = 0x82;				// ����
	else
		cmdcode = 0x84;				// ��һ��


	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;	
	mydatapack.len = 0x08;
	mydatapack.destid = ctrlid;	
	mydatapack.cmdcode = 0x23;	

	datalen = 4;

	mydatapack.data[0] = 3;							// ����			
	mydatapack.data[1] = reader;					// 1-16��ͷ
	mydatapack.data[2] = 0x21;						// Relay Control
	mydatapack.data[3] = cmdcode;					// ��ת����

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;

	// У���ͷid��
	if(reader != recvbuf[2])
	{
		printf("CtrlReader reader not match,reader[%d],recvreader[%d]",reader,recvbuf[2]);
		return -1;
	}
	return 0;
}

int SOYALDEV::SetCtrlTime(ACE_HANDLE handler,int ctrlid,Datetime_str datetime)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;
	mydatapack.len = 0x0B;
	mydatapack.destid = ctrlid;
	mydatapack.cmdcode = 0x28;

	datalen = sizeof datetime;
	memcpy(mydatapack.data,(char*)&datetime,datalen);

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;

	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"SetCtrlTime ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}

	return 0;
}

int SOYALDEV::GetCtrlTime(ACE_HANDLE handler,int ctrlid,Datetime_str &datetime)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;
	mydatapack.len = 0x04;
	mydatapack.destid = ctrlid;
	mydatapack.cmdcode = 0x19;

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;

	if(ctrlid != recvbuf[2])			// У���������
	{
		ACE_DEBUG((LM_ERROR,"GetCtrlTime ctrlid not matched,ctrlid[%d],recvctrlid[%d]",ctrlid,recvbuf[2]));
		return -1;
	}
	
	memcpy(&datetime,recvbuf+3,sizeof Datetime_str);

	return 0;
}

int SOYALDEV::CtrlReaderAutoOpen(ACE_HANDLE handler,int ctrlid,int reader,byte cmdcode,byte addrL)
{
	int ret = 0;
	byte recvbuf[256]="";
	size_t recvlen =0;
	int datalen = 0;

	DataPack mydatapack;
	memset(&mydatapack,0,sizeof mydatapack);

	mydatapack.head = 0x7E;	
	mydatapack.len = 0x0B;
	mydatapack.destid = ctrlid;	
	mydatapack.cmdcode = 0x23;	

	datalen = 7;

	mydatapack.data[0] = 6;							// ����			
	mydatapack.data[1] = reader;					// 1-16��ͷ
	mydatapack.data[2] = 0x20;						// ����721 EPROM
	mydatapack.data[3] = 0x00;						// 00 06 ��ַ
	mydatapack.data[4] = addrL;
	mydatapack.data[5] = 0x01;						// 1���ֽ�
	mydatapack.data[6] = cmdcode;					// 14:������10:�ر�,01:��ʱ�Զ�����

	ret = SendRev(handler,&mydatapack,datalen,recvbuf,recvlen);
	if(ret)
		return ret;

	// У���ͷid��
	if(reader != recvbuf[2])
	{
		printf("CtrlReaderAutoOpen reader not match,sendreader[%d],recvreader[%d]",reader,recvbuf[2]);
		return -1;
	}
	return 0;
}