/* ----------------------------------------------------------
 * 程序名称：bank_boc_dlmu.cpp
 * 创建日期：2010-07-22 14:58
 * 程序作者：韩海东
 * 版本信息：1.0.0.0
 * 程序功能：通用接口规范的封装
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank.h"
#include "mac.h"
#include "typdef.h"
#include "iso8583.h"
#include "bank_interface.h"
#include "bank_boc_dlmu.h"
#include "stdfunc.h"

static int asctobcd(char *bcd, char *asc,int len)
{
char	*p;
int	i, j;

	p = (char *) malloc( (len+1) * sizeof(char) );

	for(i = 0; i < len; i++) {
		if( (asc[i] >= '0') && (asc[i] <= '9') )
			p[i] = asc[i] - '0';
		else if( (asc[i] >= 'a') && (asc[i] <= 'f') )
			p[i] = asc[i] - 'a' + 10;
		else if( (asc[i] >= 'A') && (asc[i] <= 'F') )
			p[i] = asc[i] - 'A' + 10;

		else { 
			free(p); 
			return(-1);
		}
	}

	j = (len + len%2) / 2;
	if( len%2 ) p[len+1] = 0;

	for (i=0; i<j; i++) {
		bcd[i] = (p[2*i] & 0x0f)<<4;
		bcd[i] |= (p[2*i+1] & 0x0f);
	}

	free(p);
	return(0);
}


void WriteBufferLog(const char *pBuffer,int Buffer_len,int colum_num)
{
	int i=0;
	int j=0;
	char buffer[10240]="";
	char hex_buffer[1024]="";
	char char_buffer[1024]="";
	char tmp_char[2+1]="";
	for(i=0;i<Buffer_len;i++)
	{
		sprintf(tmp_char,"%02X ",(unsigned char)pBuffer[i]);
		strcat(hex_buffer,tmp_char);
		if ((unsigned char)pBuffer[i]<32||(unsigned char)pBuffer[i]>128)
		{
			strcat(char_buffer,".");
		}
		else
		{
			sprintf(tmp_char,"%c",(unsigned char)pBuffer[i]);
			strcat(char_buffer,tmp_char);
		}
		if((i%colum_num+1==colum_num&&i>0))
		{ 
			strcat(buffer,hex_buffer);
			strcat(buffer," ; ");
			strcat(buffer,char_buffer);
			strcat(buffer,"\r\n");
			hex_buffer[0]=0;
			char_buffer[0]=0;
		}
	}
	memset(&hex_buffer[(i%colum_num)*3],' ',colum_num*3-(i%colum_num)*3);
	hex_buffer[colum_num*3]=0;
	strcat(buffer,hex_buffer);
	strcat(buffer," ; ");
	strcat(buffer,char_buffer);
	strcat(buffer,"\r\n");
	
	//writelog(LOG_DEBUG,"%s",buffer);
	printf(buffer);
}

static int Gen_pin(char* block,char* pin,char* cardno,char* key)
{
	char passwd1[17]={0};
	char passwd2[17]={0};
	char bcd1[9]={0};
	char bcd2[9]={0};
	char text[9]={0};
	char bank_card_no[20]={0};
	char out_block[256]={0};
	int len=0;
	memcpy(passwd1,"06",2);
	memcpy(passwd1+2,pin,6);
	memcpy(passwd1+8,"FFFFFFFF",8);
	des2src(bank_card_no,cardno);
	len=strlen(bank_card_no);
	if(len<=12) return -1;
	memcpy(passwd2,"0000",4);
	memcpy(passwd2+4,bank_card_no+len-13,12);
	WriteBufferLog(passwd1, 16, 16);
	WriteBufferLog(passwd2, 16, 16);
	ASC2BCD((unsigned char*)bcd1, passwd1, 16, 0);
	ASC2BCD((unsigned char*)bcd2, passwd2, 16, 0);
	memset(bcd1+4,0xFF,4);
	writelog(LOG_ERR,"bcd1=[%s],bcd2=[%s]",bcd1,bcd2);
	WriteBufferLog(bcd1, 8, 8);
	WriteBufferLog(bcd2, 8, 8);
	for(int i=0;i<8;i++)	text[i]=bcd1[i]^bcd2[i];
	WriteBufferLog(text, 8, 8);

	DES( (unsigned char*)key, (unsigned char*)text, (unsigned char*)out_block);
	
	memcpy(block,out_block,8);
	WriteBufferLog(key, 8, 8);
	WriteBufferLog(out_block, 8, 8);
	WriteBufferLog(block, 8, 8);


	return 0;
}

static int send_recv(const char* pSend, int send_len,char* pRecv,int recv_len,const char* ip,int port,int delay)
{
	struct SockNode  SockNode;
	char bank_ip[20]={0};
	int bank_port=0;
	int ret=0;
	strncpy(bank_ip,ip,15);
	//启用signal，防止阻塞模式的socket
	WriteBufferLog(pSend,send_len,16);
	if(delay>20)
	   delay=10;
	alarm(delay);
	//连接银行
	ret=SockNode.hSock.ConnectTcp(bank_ip,port);
	if(!ret)
	{	
		alarm(0);
		writelog(LOG_ERR,"Connect to bank error,error code is [%d],bank_ip[%s],port[%d] ",ret,bank_ip,port);
		return E_TRANS_BANK_NETERR;
	}
	alarm(0);
	
	//发送数据到银行
	ret=SockNode.hSock.Send(pSend, send_len);
	if (ret<0)
	{
	      	// 发送时，端口有问题，包括被关闭
		writelog(LOG_ERR,"Send to bank error,ret = [%d] ",ret);
		return E_TRANS_BANK_NETERR;
	}
	else if (0==ret)
	{
		// 不应该出现这种情况
	      	writelog(LOG_ERR,"Send to bank error,CTcpSocket.Send should not return this error,error code is[%d]!\n",errno);
	      	return	E_TRANS_BANK_NETERR;
	}

	//system("sleep 1");

	//接收银行返回信息
	ret=	SockNode.hSock.RecvDesignedLen(pRecv,recv_len,delay*1000);
	WriteBufferLog(pRecv,ret,16);
	if (ret<=0)
	{
		writelog(LOG_ERR,"Receive from bank error,ret= [%d] ",ret);
		return	E_TRANS_BANK_NOANSWER;  // 接收时候出错，或超时
	}
	SockNode.hSock.Close();
	return 0;
}
void WriteBufferLog(const char *pBuffer,int Buffer_len,int colum_num);
int debug=2;

int Bank_Query(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	int amt=0;
	double amt1=0.0;
	char temp[256]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_DAMT0,0);


	MSG8583 zgyh_req,zgyh_ans;
	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);


	ISO_MSG iso_zgyh_req,iso_zgyh_ans;
	iso8583_init(&iso_zgyh_req);
	iso8583_init(&iso_zgyh_ans);


	char zgyh_sbuf[2048]="";
	char zgyh_abuf[2048]="";

	char buf[2048]="";
	char bitmap[16]={0x60,0x20,0x00,0x00,0x20,0xc0,0x10,0x04};
	
	if(strlen(rPack->vsvarstr1)>0)	bitmap[4]=0x30;	//如果三磁道信息为空，三磁道的位图置空


	ret=iso8583_set(&iso_zgyh_req, 0, (unsigned char*)BANK_ZGYH_TRADE_CODE_QUERY_REQ, 4);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=iso8583_set(&iso_zgyh_req, 1, (unsigned char*)bitmap,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行卡号
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%02d",strlen(rPack->scust_auth));
	sprintf(buf+2,"%s",rPack->scust_auth);
	ret=iso8583_set(&iso_zgyh_req, 2, (unsigned char*)rPack->scust_auth,strlen(rPack->scust_auth));
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error,rPack->scust_limit2=[%s]",rPack->scust_auth);
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行处理代码-000000    3	处理代号		n6	 ME	  ME	(BCD)000000
	ret=iso8583_set(&iso_zgyh_req, 3, (unsigned char*)BANK_ZGYH_EXEC_CODE_QUERY_REQ, 6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}

	//写交易参考号-流水号-取交易参考号的后六位- 11 	系统跟踪号		n6	 ME	  ME	(BCD)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%s",rPack->sholder_ac_no+8);
	ret=iso8583_set(&iso_zgyh_req,11,(unsigned char*)buf,6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写二磁道数据- 35	第二磁道数据	LLVAR	z..37	 C2		(BCD)
	ret=iso8583_set(&iso_zgyh_req,35,(unsigned char*)rPack->vsvarstr0,strlen(rPack->vsvarstr0));
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error,Second track data=[%s]",rPack->vsvarstr0);
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写三磁道数据- 36	第三磁道数据	LLLVAR	z..104	 C2		(BCD)
	if(strlen(rPack->vsvarstr1)>0)
	{
		ret=iso8583_set(&iso_zgyh_req,36,(unsigned char*)rPack->vsvarstr1,strlen(rPack->vsvarstr1));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error,Second track data=[%s]",rPack->vsvarstr1);
			strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	//写终端号- 41	POS终端号		ans8	 ME	  ME	(ASCII)
	ret=iso8583_set(&iso_zgyh_req,41,(unsigned char*)rPack->sorder2,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写商户号- 42	商户号		ans15	 M		(ASCII)
	memset(buf,0,sizeof buf);
	sprintf(buf,"%s",BANK_ZGYH_MERCH_NO);
	ret=iso8583_set(&iso_zgyh_req,42,(unsigned char*)buf,15);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行卡个人密码- 52	个人密码信息包	BIN	b64	 C3		ANSI X9.8标准Format 01
	//测试报文
	/*
	memset(buf,0,sizeof buf);
	char key[9]={0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31};
	writelog(LOG_ERR,"pass=[%s],card_no=[%s],key=[%8s]",rPack->sbank_pwd,rPack->scust_auth,key);
	ret=Gen_pin(buf, "417515", rPack->scust_auth, key);
	if(ret)
	{
		writelog(LOG_ERR,"Gen_pin error");
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=iso8583_set(&iso_zgyh_req,52,(unsigned char*)buf,8);
	*/
	memset(buf,0,sizeof buf);
	asctobcd(buf,rPack->sphone3,16);
	ret=iso8583_set(&iso_zgyh_req,52,(unsigned char*)buf,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易参考号-  62	发票号	LLLVAR	ans999	 M		(ASCII)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%s",rPack->sholder_ac_no+8);
	ret=iso8583_set(&iso_zgyh_req,62,(unsigned char*)buf,6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	
	ret=iso8583_pack(&iso_zgyh_req, zgyh_sbuf);
	if(ret<=0)
	{
		writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	memset(temp,0x00,sizeof temp);
	des2src(temp,rPack->scust_limit2);
	ret=send_recv((char *)zgyh_sbuf,ret,(char*)zgyh_abuf,200,(char*)temp,rPack->lvol0,rPack->lvol1);
	if(ret)
	{
		writelog(LOG_ERR,"send_recv error,bank_id=[%d],errcode=[%d]",BANK_GSYH,ret);
		strcpy(szMsg,"数据发送银行超时，请重试或者与一卡通中心联系");
		return E_TRANS_BANK_NOANSWER;
	}
	ret=iso8583_unpack(&iso_zgyh_ans, zgyh_abuf);
	if(ret<0)
	{
		writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
		strcpy(szMsg,"数据压包处理错误，请检查输入信息是否正确");
		return E_TRANS_UNKNOW_ERROR;
	}
	if(0!=strncmp((char *)iso_zgyh_ans.fld[39].buf,"00",2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s] ",iso_zgyh_ans.fld[39].buf);
		memcpy(temp,iso_zgyh_ans.fld[39].buf,2);
		temp[2]=0;
		for(int i=0;i<75;i++)
		{
			if(strncmp(temp,BOC_ERR_CODE[i].ErrCode,2)==0)
			{
				strcpy(szMsg,BOC_ERR_CODE[i].ErrMsg);
				return E_TRANS_BANK_RECVERR;
			}
		}
		strcpy(szMsg,"银行返回错误未定义，请与银行联系");
		return E_TRANS_UNKNOW_ERROR;

	}
	memset(temp,0x00,sizeof temp);
	des2src(temp,(char*) iso_zgyh_ans.fld[4].buf);
	amt=atoi(temp);
	out_pack->damt0=amt/100.0;
	out_pack->lvol1=1;
	PutRow(handle,out_pack,pRetCode,szMsg);
	
	return 0;
}
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char temp[256]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);

	MSG8583 zgyh_req,zgyh_ans;
	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	ISO_MSG iso_zgyh_req,iso_zgyh_ans;
	iso8583_init(&iso_zgyh_req);
	iso8583_init(&iso_zgyh_ans);

	char zgyh_sbuf[2048]="";
	char zgyh_abuf[2048]="";

	char buf[2048]="";
	char bitmap[16]={0x70,0x20,0x00,0x00,0x20,0xc0,0x10,0x04};
	
	if(strlen(rPack->vsvarstr1)>0)	bitmap[4]=0x30;	//如果三磁道信息为空，三磁道的位图置空

	ret=iso8583_set(&iso_zgyh_req, 0, (unsigned char*)BANK_ZGYH_TRADE_CODE_DETRANS_REQ, 4);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=iso8583_set(&iso_zgyh_req, 1, (unsigned char*)bitmap,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行卡号
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%02d",strlen(rPack->scust_auth));
	sprintf(buf+2,"%s",rPack->scust_auth);
	ret=iso8583_set(&iso_zgyh_req, 2, (unsigned char*)rPack->scust_auth,strlen(rPack->scust_auth));
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error,bank_card_no=[%s]",rPack->scust_auth);
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行处理代码-000000    3	处理代号		n6	 ME	  ME	(BCD)000000
	ret=iso8583_set(&iso_zgyh_req, 3, (unsigned char*)BANK_ZGYH_EXEC_CODE_DETRANS_REQ, 6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易金额-  4	交易金额		n12	 ME	  ME	(BCD)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%012d",int(rPack->damt0*100));
	ret=iso8583_set(&iso_zgyh_req, 4,(unsigned char*)buf , 12);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易参考号-流水号-取交易参考号的后六位- 11 	系统跟踪号		n6	 ME	  ME	(BCD)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%-06s",rPack->sholder_ac_no+8);
	ret=iso8583_set(&iso_zgyh_req,11,(unsigned char*)buf,6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写二磁道数据- 35	第二磁道数据	LLVAR	z..37	 C2		(BCD)
	ret=iso8583_set(&iso_zgyh_req,35,(unsigned char*)rPack->vsvarstr0,strlen(rPack->vsvarstr0));
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error,Second track data=[%s]",rPack->vsvarstr0);
		return E_TRANS_UNKNOW_ERROR;
	}
	//写三磁道数据- 36	第三磁道数据	LLLVAR	z..104	 C2		(BCD)
	if(strlen(rPack->vsvarstr1)>0)
	{
		ret=iso8583_set(&iso_zgyh_req,36,(unsigned char*)rPack->vsvarstr1,strlen(rPack->vsvarstr1));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error,Second track data=[%s]",rPack->vsvarstr1);
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	//写终端号- 41	POS终端号		ans8	 ME	  ME	(ASCII)
	ret=iso8583_set(&iso_zgyh_req,41,(unsigned char*)rPack->sorder2,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写商户号- 42	商户号		ans15	 M		(ASCII)
	memset(buf,0,sizeof buf);
	sprintf(buf,"%s",BANK_ZGYH_MERCH_NO);
	ret=iso8583_set(&iso_zgyh_req,42,(unsigned char*)buf,15);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行卡个人密码- 52	个人密码信息包	BIN	b64	 C3		ANSI X9.8标准Format 01
	memset(buf,0,sizeof buf);
	asctobcd(buf,rPack->sphone3,16);

	ret=iso8583_set(&iso_zgyh_req,52,(unsigned char*)buf,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易参考号-  62	发票号	LLLVAR	ans999	 M		(ASCII)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%-06s",rPack->sholder_ac_no+8);
	ret=iso8583_set(&iso_zgyh_req,62,(unsigned char*)buf,6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	
	ret=iso8583_pack(&iso_zgyh_req, zgyh_sbuf);
	if(ret<=0)
	{
		writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	ret=send_recv((char *)zgyh_sbuf,ret,(char*)zgyh_abuf,200,rPack->scust_limit2,rPack->lvol0,rPack->lvol1);
	if(ret)
	{
		writelog(LOG_ERR,"Receive data return code error[Reverse],error code= [%2.2s],Refno=[%s],Bankcard=[%s],Term=[%s],Amt=[%d]",iso_zgyh_ans.fld[39].buf,rPack->sholder_ac_no,rPack->scust_auth,rPack->sorder2,int(rPack->damt0*100));
		return E_TRANS_BANK_NOANSWER;
	}
	
	ret=iso8583_unpack(&iso_zgyh_ans, zgyh_abuf);
	if(ret<0)
	{
		writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}
	if(0!=strncmp((char *)iso_zgyh_ans.fld[39].buf,"00",2))
	{
		writelog(LOG_ERR,"Receive data return code error[Reverse],error code= [%2.2s],Refno=[%s],Bankcard=[%s],Term=[%s],Amt=[%d]",iso_zgyh_ans.fld[39].buf,rPack->sholder_ac_no,rPack->scust_auth,rPack->sorder2,int(rPack->damt0*100));
		memcpy(temp,iso_zgyh_ans.fld[39].buf,2);
		temp[2]=0;
		for(int i=0;i<75;i++)
		{
			if(strncmp(temp,BOC_ERR_CODE[i].ErrCode,2)==0)
			{
				strcpy(szMsg,BOC_ERR_CODE[i].ErrMsg);
				return E_TRANS_BANK_RECVERR;
			}
		}
		strcpy(szMsg,"银行返回错误未定义，请与银行联系");
		return E_TRANS_UNKNOW_ERROR;
	}

	out_pack->lvol1=1;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;

}
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	char temp[256]="";
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL1,F_SDATE1,F_SCERT_NO,0);

	MSG8583 zgyh_req,zgyh_ans;
	memset(&zgyh_req,0x20,sizeof zgyh_req);
	memset(&zgyh_ans,0x20,sizeof zgyh_ans);

	ISO_MSG iso_zgyh_req,iso_zgyh_ans;
	iso8583_init(&iso_zgyh_req);
	iso8583_init(&iso_zgyh_ans);

	char zgyh_sbuf[2048]="";
	char zgyh_abuf[2048]="";

	char buf[2048]="";
	char bitmap[16]={0x70,0x20,0x00,0x00,0x20,0xc0,0x10,0x04};
	
	if(strlen(rPack->vsvarstr1)>0)	bitmap[4]=0x30;	//如果三磁道信息为空，三磁道的位图置空

	ret=iso8583_set(&iso_zgyh_req, 0, (unsigned char*)BANK_ZGYH_TRADE_CODE_TRANS_REQ, 4);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	ret=iso8583_set(&iso_zgyh_req, 1, (unsigned char*)bitmap,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行卡号
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%02d",strlen(rPack->scust_auth));
	sprintf(buf+2,"%s",rPack->scust_auth);
	ret=iso8583_set(&iso_zgyh_req, 2, (unsigned char*)rPack->scust_auth,strlen(rPack->scust_auth));
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error,bank_card_no=[%s]",rPack->scust_auth);
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行处理代码-000000    3	处理代号		n6	 ME	  ME	(BCD)000000
	ret=iso8583_set(&iso_zgyh_req, 3, (unsigned char*)BANK_ZGYH_EXEC_CODE_TRANS_REQ, 6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易金额-  4	交易金额		n12	 ME	  ME	(BCD)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%012d",int(rPack->damt0*100));
	ret=iso8583_set(&iso_zgyh_req, 4,(unsigned char*)buf , 12);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易参考号-流水号-取交易参考号的后六位- 11 	系统跟踪号		n6	 ME	  ME	(BCD)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%-06s",rPack->sholder_ac_no+8);
	ret=iso8583_set(&iso_zgyh_req,11,(unsigned char*)buf,6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写二磁道数据- 35	第二磁道数据	LLVAR	z..37	 C2		(BCD)
	ret=iso8583_set(&iso_zgyh_req,35,(unsigned char*)rPack->vsvarstr0,strlen(rPack->vsvarstr0));
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error,Second track data=[%s]",rPack->vsvarstr0);
		return E_TRANS_UNKNOW_ERROR;
	}
	//写三磁道数据- 36	第三磁道数据	LLLVAR	z..104	 C2		(BCD)
	if(strlen(rPack->vsvarstr1)>0)
	{
		ret=iso8583_set(&iso_zgyh_req,36,(unsigned char*)rPack->vsvarstr1,strlen(rPack->vsvarstr1));
		if(ret<=0)
		{
			writelog(LOG_ERR,"iso8583_set error,Second track data=[%s]",rPack->vsvarstr1);
			return E_TRANS_UNKNOW_ERROR;
		}
	}
	//写终端号- 41	POS终端号		ans8	 ME	  ME	(ASCII)
	ret=iso8583_set(&iso_zgyh_req,41,(unsigned char*)rPack->sorder2,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写商户号- 42	商户号		ans15	 M		(ASCII)
	memset(buf,0,sizeof buf);
	sprintf(buf,"%s",BANK_ZGYH_MERCH_NO);
	ret=iso8583_set(&iso_zgyh_req,42,(unsigned char*)buf,15);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写银行卡个人密码- 52	个人密码信息包	BIN	b64	 C3		ANSI X9.8标准Format 01
	//测试报文
	//memset(buf,0,sizeof buf);
	//char key[9]={0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31};
	//writelog(LOG_ERR,"pass=[%s],card_no=[%s],key=[%8s]",rPack->sbank_pwd,rPack->scust_auth,key);

	//ret=Gen_pin(buf, rPack->sbank_pwd, rPack->scust_auth, key);
	//if(ret)
	//{
	//	writelog(LOG_ERR,"Gen_pin error");
	//	return E_TRANS_UNKNOW_ERROR;
	//}
	//ret=iso8583_set(&iso_zgyh_req,52,(unsigned char*)buf,8);
	memset(buf,0,sizeof buf);
	asctobcd(buf,rPack->sphone3,16);
	ret=iso8583_set(&iso_zgyh_req,52,(unsigned char*)buf,8);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	//写交易参考号-  62	发票号	LLLVAR	ans999	 M		(ASCII)
	memset(buf,0x00,sizeof buf);
	sprintf(buf,"%-06s",rPack->sholder_ac_no+8);
	ret=iso8583_set(&iso_zgyh_req,62,(unsigned char*)buf,6);
	if(ret<=0)
	{
		writelog(LOG_ERR,"iso8583_set error");
		return E_TRANS_UNKNOW_ERROR;
	}
	
	ret=iso8583_pack(&iso_zgyh_req, zgyh_sbuf);
	if(ret<=0)
	{
		writelog(LOG_ERR,"Pack8583 error,errcode=[%d]",ret);
		return E_TRANS_UNKNOW_ERROR;
	}

	ret=send_recv((char *)zgyh_sbuf,ret,(char*)zgyh_abuf,200,rPack->scust_limit2,rPack->lvol0,rPack->lvol1);
	if(ret)
	{
		writelog(LOG_ERR,"Send_recv error,Refno=[%s],Bankcard=[%s],Term=[%s],Amt=[%d],Errcode=[%d]",rPack->sholder_ac_no,rPack->scust_auth,rPack->sorder2,int(rPack->damt0*100),ret);
		return E_TRANS_BANK_NOANSWER;
	}
	
	ret=iso8583_unpack(&iso_zgyh_ans, zgyh_abuf);
	if(ret<0)
	{
		writelog(LOG_ERR,"UnPack8583 error,errcode=[%d]",ret);
		return E_TRANS_BANK_NOANSWER;
	}
	if(0!=strncmp((char *)iso_zgyh_ans.fld[39].buf,"00",2))
	{
		writelog(LOG_ERR,"Receive data return code error,error code= [%2.2s],Refno=[%s],Bankcard=[%s],Term=[%s],Amt=[%d]",iso_zgyh_ans.fld[39].buf,rPack->sholder_ac_no,rPack->scust_auth,rPack->sorder2,int(rPack->damt0*100));
		memcpy(temp,iso_zgyh_ans.fld[39].buf,2);
		temp[2]=0;
		for(int i=0;i<75;i++)
		{
			if(strncmp(temp,BOC_ERR_CODE[i].ErrCode,2)==0)
			{
				strcpy(szMsg,BOC_ERR_CODE[i].ErrMsg);
				if((strncmp(BOC_ERR_CODE[i].ErrCode,"89",2)==0)||(strncmp(BOC_ERR_CODE[i].ErrCode,"19",2)==0)||(strncmp(BOC_ERR_CODE[i].ErrCode,"91",2)==0))
					return E_TRANS_BANK_NOANSWER;
				return E_TRANS_BANK_RECVERR;
			}
		}
		strcpy(szMsg,"银行返回错误未定义，请与银行联系");
		return E_TRANS_UNKNOW_ERROR;

	}
	out_pack->lvol1=1;
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
r_ret:
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
}


//按照通用接口规范进行封装各自银行的接口
int Bank_QueryBalance(INNER_TRANS_REQUEST * pNode,double *balance)
{
	return 0;
}

int Bank_Transfer(INNER_TRANS_REQUEST * pNode,int serial_no)
{
	return 0;
}

int Bank_Undo(INNER_TRANS_REQUEST * pNode)
{
	return 0;
}
int Bank_CheckLine()
{
	return 0;
}

int Bank_SignIn(INNER_TRANS_REQUEST *pNode)
{
	return 0;
}
int Bank_SignOut()
{
	return 0;
}
