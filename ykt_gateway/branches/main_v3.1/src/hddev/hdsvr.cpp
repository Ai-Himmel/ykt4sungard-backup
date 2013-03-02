
#include "ksglobal.h"
#include "hddev/hdsvr.h"
#include "ksgateway.h"
#include "bit_endian.h"
#include "F8583.h"
#include "device.h"
#include <ace/ACE.h>
#include <ace/File_Lock.h>
#include <ace/CDR_Stream.h>
#include <ace/Proactor.h>
#include "xutils/xstring.h"
//#include "ftplib.h"
#include <curl/curl.h>
#include "osutil.h"
#include "pubfunc.h"

unsigned long HDDEV::SN2LongNum(const char* sn)
{
	unsigned long termid = ACE_OS::strtoul(sn,NULL,10);
#ifdef X86_ARCH
	unsigned char buf[4] = "";
	ACE_OS::memcpy(buf,(unsigned char*)&termid,4);
	for (int i = 0;i < 2 ;++i)
	{
		unsigned char b = buf[i];
		buf[i] = buf[4-i];
		buf[i] = b;
	}
	return termid;
#else
#endif //
}
void HDDEV::SN2Char(unsigned long termid,char* sn)
{

}
unsigned long HDDEV::DecodeTermSN(const char * sn)
{
	if(KsgGetGateway()->GetConfig()->_hdphyid)
	{
		int i = 0;
		char temp[2] = "";
		char text[12] = "";
		ACE_OS::strncpy(text,sn,4);
		temp[0] = sn[4];
		i = ACE_OS::strtoul(temp,NULL,16);
		if(i < 0)
			return 0;
		ACE_OS::sprintf(text+4,"%.02d",i);
		temp[0] = sn[5];
		i = ACE_OS::strtoul(temp,NULL,16);
		if(i < 0)
			return 0;
		ACE_OS::sprintf(text+6,"%.02d",i);
		ACE_OS::strncat(text+8,sn+6,2);
		text[10] = '\0';
		return ACE_OS::strtoul(text,NULL,10);
	}
	else
	{
		return ACE_OS::strtoul(sn,NULL,10);
	}
}

void HDDEV::EncodeTermSN(unsigned long termid,char* sn)
{
	if(KsgGetGateway()->GetConfig()->_hdphyid)
	{
		int i = 0;
		int j = 0;
		char temp[3] = "";
		char text[12] = "";
		ACE_OS::sprintf(text,"%.010lu",termid);
		ACE_OS::strncpy(sn,text,4);
		ACE_OS::strncpy(temp,text+4,2);
		i = atoi(temp);
		if(i < 0 || i >15)
			return;
		ACE_OS::strncpy(temp,text+6,2);
		j = ACE_OS::atoi(temp);
		if(j < 0 || j > 15)
			return;
		ACE_OS::sprintf(sn+4,"%X%X",i,j);
		ACE_OS::strncat(sn+6,text+8,2);
		sn[8] = '\0';
	}
	else
	{
		sprintf(sn,"%010d",termid);
	}
}

unsigned long HDDEV::EncodeVersionNum(const char* version)
{
	unsigned long ret = 0;
	char tmp[3] = "";
	int i;
	int d_offset[6] = {6,4,5,5,6,6};
	int d_mask[7] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F};

	unsigned long dateval[7];
	for(i = 0;i < 6;++i)
	{
		ACE_OS::strncpy(tmp,version+i*2,2);
		dateval[i] = (unsigned long)ACE_OS::atoi(tmp);
	}
	int j = 0;
	for(i = 0;i < 6;++i)
	{
		j += d_offset[i];
		ret |= (dateval[i] & d_mask[d_offset[i]]) 
			<< (sizeof(unsigned long) * 8 - j);
	}
	return ret;
}
int HDDEV::DecodeVersionNum(unsigned long num,char* ver)
{
	int i;
	int d_offset[6] = {6,4,5,5,6,6};
	int d_mask[7] = {0x00,0x01,0x03,0x07,0x0F,0x1F,0x3F};

	int j = 0;
	for(i = 0;i < 6;++i)
	{
		j += d_offset[i];
		BYTE t = (BYTE)(num >> (sizeof(unsigned long)*8 - j)) & d_mask[d_offset[i]];
		ACE_OS::sprintf(ver,"%.02d",t);
		ver+=2;
	}
	return 0;
}
int HDDEV::HDConvertCardPhyNo(unsigned int dec_no,char phy_no[9])
{
	unsigned long val = dec_no;
	KSG_Memory_Util::revert_buffer((unsigned char*)&val,sizeof val);
	char tmp[20] = "";
	ACE_OS::sprintf(tmp,"%08X",val);
	ACE_OS::strcpy(phy_no,tmp);
	return 0;
}

MYDATETIMESTRUCT HDDEV::HDGetDataTime()
{
	time_t now = ACE_OS::gettimeofday().sec();
	struct tm* tv = ACE_OS::localtime(&now);
	MYDATETIMESTRUCT ret;
	ret.Year = (tv->tm_year + 1900) % 2000;
	ret.Month = tv->tm_mon + 1;
	ret.Day = tv->tm_mday;
	ret.Hour = tv->tm_hour;
	ret.Minute = tv->tm_min;
	ret.Second = tv->tm_sec;
	ret.DayOfWeek = tv->tm_wday;
	return ret;
}

size_t HDDEV::PackRequestStruct(HD8583STRUCT& req,MESSAGETYPE msg_type
						 ,void* buf,size_t maxlen,bool with_crc )
{
	HDISO8583Msg msg;
	char * output = (char*)buf;
	char * bitmap = output+3;
	size_t packlen = msg.Pack(req,output+3,maxlen-3);
	if(packlen <= 0)
		return 0;
	output[2] = (char)msg_type;
	packlen++;
	if(with_crc)
	{
		bitmap[FIELD_MACOFBASALBITMAP/8] |= 1 << (7 - FIELD_MACOFBASALBITMAP % 8);
		unsigned short i = GenerateCRC16((unsigned char*)output+2,static_cast<uint16>(packlen));

		output[packlen+3] = i % 0x100;
		output[packlen+2] = i / 0x100;
		for(i = 0;i < 4;++i)
		{
			output[packlen+2] ^= KsgGetGateway()->GetConfig()->_workKey[i*2];
			output[packlen+3] ^= KsgGetGateway()->GetConfig()->_workKey[i*2+1];
		}
		packlen+=2;
	}
	short tmp = static_cast<short>(packlen);
	SHORT_2_BUF(tmp,output);
	return packlen+2;
}
int HDDEV::UnPackResponseStruct(HD8583STRUCT& resp,MESSAGETYPE* msg_type,
						 void* buf,size_t buflen)
{
	short datalen;
	HDISO8583Msg msg;
	char * input = (char*)buf;
	BUF_2_SHORT_LE(datalen,input);
	if(datalen != (buflen - 2))
		return -1;
	if(datalen > 1024)
		return -1;
	*msg_type = (MESSAGETYPE)(input[2] & 0xFF);
	unsigned char zero[2] = {0x00,0x00};
	if(msg.Unpack(resp,input+3,datalen-1) > 0)
	{
		// �Ƚ� MAC ��ַ
		if(ACE_OS::memcmp(resp->mac,zero,2))
		{
			// 2 byte ����, 2 byte mac ��
			unsigned short crc_val = GenerateCRC16((unsigned char*)input+2,buflen-4);
			unsigned char tmp[4] = {0};
			SHORT_2_BUF_LE(crc_val,tmp);
			/*
			tmp[0] = (unsigned char)((i & 0xFF00) >> 8);
			tmp[1] = (unsigned char)(i & 0xFF);
			*/
			tmp[2] = tmp[0];
			tmp[0] = tmp[1];
			tmp[1] = tmp[2];
			for(int i = 0;i < 2;++i)
				for(int j = 0;j < 4;++j)
					tmp[i] ^=  KsgGetGateway()->GetConfig()->_workKey[i+j*2];
			if(ACE_OS::memcmp(resp->mac,tmp,2) == 0)
				return 0;
			else
			{
				ACE_DEBUG((LM_ERROR,"������ݱ���MACУ�����,����ֵ[%04X],ʵ��ֵ[%02X%02X]"
					,tmp,resp->mac[0],resp->mac[1]));
				return -1;
			}
			
		}
		return 0;
	}
	return -1;
}

unsigned short HDDEV::GetDeviceAddress(KSGDeviceNode* node)
{
	if(!node)
		return 0;
	unsigned short addr = (unsigned short)
		ACE_OS::atoi(node->GetDevAddr().GetDevCode().c_str());
	if(node->GetDeviceType() == KSG_HD_POS_DEV
		|| node->GetDeviceType() == KSG_HD_ADD_POS_DEV
		|| node->GetDeviceType() == KSG_HD_PENSTOCK)
	{
		addr |= HDA_SYSTEMIDOFPOS1_1;
	}
	else if(node->GetDeviceType() == KSG_HD_GCU_DEV)
	{
		addr |= HDA_SYSTEMIDOFACC1_1;
	}
	else if(node->GetDeviceType() == KSG_HD_SERVER_DEV)
	{
		addr = HDA_SYSTEMIDOFALL;
	}
	else if(node->GetDeviceType() == KSG_JSB_DEV)
	{
		addr |= HDA_SYSTEMIDOFATT1_1;
	}
	return addr;
}

int HDDEV::HDSendBuffer(ACE_HANDLE handler,char* buf,size_t buflen
				 ,ACE_Time_Value* timeout)
{
	if(ACE_INVALID_HANDLE == handler)
		return -4;
	ACE_SOCK_Stream stream(handler);
	size_t transfered = 0;
	ACE_Time_Value tv = *timeout;
	int r;
	r = ACE::handle_write_ready(handler,&tv);
	if( r < 0) 
		return -1;
	else if(r == 0)
		return -5;
	ssize_t l = 0;
	do 
	{
		tv = *timeout;
		stream.send_n(buf+l,buflen-l,&tv,&transfered);
		if(transfered > 0)
		{
			l += transfered;
			if(l >= buflen)
				return 0;
			// continue send

		}
		else
		{
			if(l >= buflen)
				return 0;
			return -2;
		}
	} while (l <= buflen);
	/*stream.send_n(buf,buflen,timeout,&transfered);
	if(buflen == transfered)
	{
		return 0;
	}*/
	return -2;
}
int HDDEV::HDRecvBuffer(ACE_HANDLE handler,char* buf,size_t maxbuf
				 ,ACE_Time_Value* timeout)
{
	ACE_SOCK_Stream stream(handler);
	// USE recv_n ��ȡ����
	size_t transfered =	0;
	ACE_Time_Value tv(0);
	if(ACE::handle_read_ready(handler,timeout) <= 0) 
		return -1;
	ssize_t l = 0;
	do 
	{
		stream.recv_n(buf+l,maxbuf-l,&tv,&transfered);
		if(transfered > 0)
		{
			l += transfered;
			if(l >= maxbuf)
				return l;
		}
		else
		{
			if(l > 0)
				return l;
			return -2;
		}
	} while (l < maxbuf);
	return 0;
	/*
	if(transfered <= 0 || transfered > maxbuf)
	{
		return -1;
	}
	return transfered;
	*/
}

int HDDEV::HDParsePosRecord(BYTE* buf,TRADERECORDSTRUCT* trade)
{
	/*
	BUF_2_INT_LE(trade->CardNumber,buf);  // ���׿���
	BUF_2_INT_LE(trade->Balance,buf+4);   // ���
	BUF_2_INT_LE(trade->Amount,buf+8);	   // ���׽��
	trade->Year = *(buf+12);			   // ����ʱ��
	trade->Month = *(buf+13);
	trade->Day = *(buf+14);
	trade->Hour = *(buf+15);
	trade->Minute = *(buf+16);
	trade->Second = *(buf+17);
	BUF_2_SHORT_LE(trade->TraceOfEW,buf+18);    // Ǯ����ˮ��
	BUF_2_INT_LE(trade->TraceOfPOS,buf+20);     // POS��ˮ��
	BUF_2_INT_LE(trade->OrgTransTrace,buf+24);  // ԭ������ˮ�� ( reserved )
	BUF_2_INT_LE(trade->OperatorID,buf+28);     // ����Ա���� ( reserved )
	BUF_2_INT_LE(trade->TerminalSN,buf+32);     // �ն˺� 
	BUF_2_SHORT_LE(trade->AdditionalMoney,buf+36); // �����
	BUF_2_SHORT_LE(trade->GoodsNumber,buf+38);     // �ն˺�
	trade->IndexOfEW = *(buf+40);					// Ǯ����
	if(trade->IndexOfEW > 0)
		trade->IndexOfEW--;
	trade->RecordType = *(buf+41);				// ��¼����
	trade->ConsumeMode = *(buf+42);				// ����ģʽ
	BUF_2_SHORT_LE(trade->SubsidyNo,buf+43);	// �������κ�
	trade->MealId = *(buf+45);					// �ʹκ�
	memcpy(trade->MAC,buf+46,4);				// MAC У��
	// ���� MAC У��
	uint16 i = GenerateCRC16(buf,46);
	unsigned char tmp[4] = "";
	SHORT_2_BUF(i,tmp);
	tmp[2] = tmp[0];
	tmp[0] = tmp[1];
	tmp[1] = tmp[2];
	for(int i = 0;i < 2;++i)
		for(int j = 0;j < 4;++j)
			tmp[i] ^=  KsgGetGateway()->GetConfig()->_workKey[i+j*2];
	return (ACE_OS::memcmp(trade->MAC,tmp,2) == 0) ? 0 : -1;
	*/
	BUF_2_INT_LE(trade->CardNumber,buf);  // ���׿���
	BUF_2_INT_LE(trade->Balance,buf+4);   // ���
	BUF_2_INT_LE(trade->Amount,buf+8);	   // ���׽��
	trade->Year = *(buf+12);			   // ����ʱ��
	trade->Month = *(buf+13);
	trade->Day = *(buf+14);
	trade->Hour = *(buf+15);
	trade->Minute = *(buf+16);
	trade->Second = *(buf+17);
	BUF_2_SHORT_LE(trade->TraceOfEW,buf+18);    // Ǯ����ˮ��
	BUF_2_INT_LE(trade->TraceOfPOS,buf+20);     // POS��ˮ��
	BUF_2_INT_LE(trade->OrgTransTrace,buf+24);  // ԭ������ˮ�� ( reserved )
	BUF_2_INT_LE(trade->GoodsNumber,buf+28);     // ����Ա���� ( reserved )
	BUF_2_INT_LE(trade->TerminalSN,buf+32);     // �ն˺� 
	BUF_2_SHORT_LE(trade->AdditionalMoney,buf+36); // �����
	BUF_2_SHORT_LE(trade->OperatorID,buf+38);     // �ն˺�
	trade->IndexOfEW = *(buf+40);					// Ǯ����
	if(trade->IndexOfEW > 0)
		trade->IndexOfEW--;
	trade->ConsumeMode = *(buf+41);				// ��¼����
	trade->RecordType = *(buf+41);				// ����ģʽ
	//BUF_2_SHORT_LE(trade->SubsidyNo,buf+43);	// �������κ�
	//trade->MealId = *(buf+45);					// �ʹκ�
	memcpy(trade->MAC,buf+43,4);				// MAC У��
	// ���� MAC У��
	uint16 i = GenerateCRC16(buf,43);
	unsigned char tmp[4] = "";
	SHORT_2_BUF(i,tmp);
	tmp[2] = tmp[0];
	tmp[0] = tmp[1];
	tmp[1] = tmp[2];
	for(int i = 0;i < 2;++i)
		for(int j = 0;j < 4;++j)
			tmp[i] ^=  KsgGetGateway()->GetConfig()->_workKey[i+j*2];
	return (ACE_OS::memcmp(trade->MAC,tmp,2) == 0) ? 0 : -1;
}
namespace HDDEV
{

	//////////////////////////////////////////////////////////////
	// proactor
#ifdef USE_PROACTOR
	KSG_ADD_LISTENER_CLASS(KSG_HD_CCU_LISTENER,HD_CCU_Acceptor);
#endif // USE_PROACTOR
	HD_CCU_Acceptor::HD_CCU_Acceptor():_check_handle(NULL),_schd_id(-1)
	{
	}
	HD_CCU_Acceptor::~HD_CCU_Acceptor()
	{
	}

	int HD_CCU_Acceptor::validate_connection(const ACE_Asynch_Accept::Result& result 
		, const ACE_INET_Addr &remote, const ACE_INET_Addr& local)
	{
		// TODO : ���ӶԿͻ������ӵĺϷ��Լ���
		return 0;
	}
	KSG_Proactor_Handler* HD_CCU_Acceptor::new_handler()
	{
		ACE_DEBUG((LM_DEBUG,"�����µ�����..."));
		return new HD_CCU_Request_Handler(this);
	}
	
	int HD_CCU_Acceptor::start_listen()
	{
		// �˿ڴӺ�̨�ж�ȡ1
		std::string value;
		int port = 6001;
		if(KsgGetSystemParam(HD_SYSPARAM_LISTEN_PORT,value))
		{
			ACE_DEBUG((LM_INFO,"��ȡCCU�����˿ں�ʧ��,ʹ��Ĭ�϶˿�[%d]",port));
		}
		else
		{
			port = ACE_OS::atoi(value.c_str());
		}
		if(open(ACE_INET_Addr(port),0,1,ACE_DEFAULT_ASYNCH_BACKLOG
			,1,ACE_Proactor::instance(),0) == -1 )
		{
			ACE_DEBUG((LM_ERROR,"���CCU������������ʧ��\n"));
			return -1;
		}
		_check_handle = new KSG_Proactor_Check_Handler(this);
		_schd_id = ACE_Proactor::instance()->schedule_timer(
			*_check_handle,NULL,ACE_Time_Value::zero,ACE_Time_Value(10));
		ACE_DEBUG((LM_INFO,"CCU�����߳�ThreadId[%u]�˿�[%d]\n",ACE_OS::thr_self(),port));

		if(!KsgGetSystemParam(HD_CCU_FTP_USER,value))
		{
			hd_ccu_ftp_user_name = value;
		}

		if(!KsgGetSystemParam(HD_CCU_FTP_PSWD,value))
		{
			hd_ccu_ftp_pswd = value;
		}
		if(!KsgGetSystemParam(HD_CCU_FTP_PORT,value))
		{
			hd_ccu_ftp_port = value;
		}
		return 0;
	}
	int HD_CCU_Acceptor::stop_listen()
	{
		if(_schd_id > -1)
			ACE_Proactor::instance()->cancel_timer(_schd_id);
		if(_check_handle)
			delete _check_handle;
		close();
		return 0;
	}
	////////////////////////////////////////////////////////////////////
#define CCU_MTU 256
	HD_CCU_Request_Handler::~HD_CCU_Request_Handler()
	{
	}
	HD_CCU_Request_Handler::HD_CCU_Request_Handler(
		HD_CCU_Acceptor* acceptor /* = NULL */)
		:KSG_Proactor_Handler(acceptor),_request_handler(NULL)
	{
	}
	int HD_CCU_Request_Handler::on_open(ACE_HANDLE new_handle
		, ACE_Message_Block &message_block)
	{
		ACE_Message_Block *new_mb;
		ACE_NEW_NORETURN(new_mb,ACE_Message_Block(MAX_MESBUF_LEN));
		if(_reader.read(*new_mb,CCU_MTU) != 0)
		{
			int err = ACE_OS::last_error();
			ACE_DEBUG((LM_ERROR,"��ȡ CCU ��������ʧ��![%d][%s]"
				,err,ACE_OS::strerror(err)));
			new_mb->release();
			free_handler();
			return -1;
		}
		_mblk = new_mb;
		_recv_count++;
		_pack_index = 0;
		return 0;
	}

	int HD_CCU_Request_Handler::on_free_handler()
	{
		_request_handler = NULL;
		return 0;
	}
	
	void HD_CCU_Request_Handler::handle_write_stream(
		const ACE_Asynch_Write_Stream::Result &result)
	{

		_send_count--;
		if(_request_handler)
		{
			_request_handler->DoFinish(handle());
		}
		// �ͷ���Դ
		//result.message_block().release();
		ACE_DEBUG((LM_DEBUG,"handle[%d]Ӧ�����ݳɹ�!",_pack_index));
		//update_io_time();
		//reset_request();
		if(_send_count == 0)
			free_handler();
		
	}

	void HD_CCU_Request_Handler::reset_request()
	{
		if(_mblk)
			_mblk->reset();
		else
		{
			ACE_NEW_NORETURN(_mblk,ACE_Message_Block(MAX_MESBUF_LEN));
		}
		_pack_index = 0;
		if(_reader.read(*_mblk,CCU_MTU) != 0)
		{
			int err = ACE_OS::last_error();
			ACE_DEBUG((LM_ERROR,"��ȡ CCU ��������ʧ��![%d][%s]"
				,err,ACE_OS::strerror(err)));
			free_handler();
			return;
		}
	}

	void HD_CCU_Request_Handler::handle_read_stream(
		const ACE_Asynch_Read_Stream::Result &result)
	{
		static ACE_CDR::UShort data_len;
		ACE_Message_Block & mb = result.message_block();
		_recv_count--;
		if(!result.success() || result.bytes_transferred() == 0)
		{
			// ��Ϊ��������ʧ��
			ACE_DEBUG((LM_ERROR,"��ȡ CCU ����ʧ��!!"));
			free_handler();
			return;
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"��ʼ��������..."));
			// ��ȡ�������
			update_io_time();
			if(_pack_index == 0)
			{
				ACE_InputCDR cdr(&mb);
				cdr >> data_len;
				ACE_DEBUG((LM_DEBUG,"��ȡ��һ����"));
			}
			_pack_index++;
			if(mb.length() - MSG_BUF_LEN_HEADER >= data_len )
			{
				// ��ȡ���,����ҵ��
				//ACE_DEBUG((LM_INFO,"�������ݰ�������[%d]",(data_len+MSG_BUF_LEN_HEADER)));
				if( process_request(&mb,data_len+MSG_BUF_LEN_HEADER)<= 0 )
				{
					// ����ʧ�ܻ��߲���ҪӦ��
					free_handler();
				}
				return;
			}
			// ��Ϊ����������
			// ������ȡ
			if(mb.length() >= 65535)
			{
				ACE_DEBUG((LM_ERROR,"���ݰ����Ȳ��Ϸ�!!!!"));
				free_handler();
				return;
			}
			//ACE_HEX_DUMP((LM_INFO,mb.rd_ptr(),mb.length()));
			//ACE_DEBUG((LM_INFO,"������ȡ����...len[%d]",(data_len - (mb.length()-MSG_BUF_LEN_HEADER))));
			if( _reader.read(mb,CCU_MTU)!=0)
				//,data_len - mb.length() + MSG_BUF_LEN_HEADER) != 0)
			{
				ACE_DEBUG((LM_ERROR,"��ȡ CCU ����ʧ��!!"));
				free_handler();
				return;
			}
			_recv_count++;
		}
	}
	int HD_CCU_Request_Handler::process_request(ACE_Message_Block *mblk,int data_len)
	{
		HD8583STRUCT req;
		HD8583STRUCT resp;
		MESSAGETYPE msg_type;
		char * buffer = mblk->rd_ptr();
		int len = 0;
		//ACE_DEBUG((LM_INFO,"ҵ������..."));
		// ���ݶγ��ȳ�������Χ,��������
		//ACE_HEX_DUMP((LM_INFO,buffer,data_len));
		if(UnPackResponseStruct(req,&msg_type,buffer,data_len) != 0)
		{
			ACE_ERROR((LM_ERROR,"���ݰ����Ϸ�"));
			return -1;
		}
		ACE_HEX_DUMP((LM_DEBUG,mblk->rd_ptr(),mblk->length()));
		try
		{
			_request_handler = HDCCUProcessUnits::instance()->Create(msg_type);
			if(_request_handler)
			{
				_request_handler->_remote_addr = this->_remote_addr;
				_request_handler->set_resp_need_mac(false);
				resp.Init();
				int result = _request_handler->DoResponse(req,resp,handle());
				if(result > 0)
				{
					// send back
					mblk->reset();
					buffer = mblk->wr_ptr();
					len = (int)PackRequestStruct(resp,msg_type,buffer,mblk->size()
						,_request_handler->resp_need_mac());
					mblk->wr_ptr(len);
					ACE_HEX_DUMP((LM_DEBUG,buffer,mblk->length()));
					ACE_DEBUG((LM_DEBUG,"���ݰ�����[%d]",mblk->length()));
					if(mblk->length() == 0)
					{
						ACE_DEBUG((LM_ERROR,"Ӧ�������Ϊ0,������"));
						return -1;
					}
					if(_writer.write(*mblk,mblk->length()) !=0 )
					{
						ACE_DEBUG((LM_ERROR,"����Ӧ���ʧ��"));
						return -1;
					}
					_send_count++;
					return 1;
				}
				else if(result == 0)
				{
					// OK
					ACE_DEBUG((LM_DEBUG,"����ɹ�"));
				}
				else
				{
					// error
					ACE_DEBUG((LM_ERROR,"��������ʧ�ܣ�������[%d]",result));
				}
			}
			else
			{
				ACE_ERROR((LM_ERROR,"���ܴ����������[%c]",msg_type));
			}	
		}
		catch(...)
		{
			// �������е��쳣
			ACE_ERROR((LM_ERROR,"���������쳣,�������[%02x]",msg_type));
		}	
		return -1;
	}
///////////////////////////////////////////////////////////////////
//
HDCCUSvrHandler::HDCCUSvrHandler():_close_time(1)
{		
	// ms
	ACE_DEBUG((LM_DEBUG,"���� ACE Handler"));
	_max_timeout_sec = ACE_Time_Value(KsgGetGateway()->GetConfig()->_execTimeout/1000*4);
}
HDCCUSvrHandler::~HDCCUSvrHandler()
{
	ACE_DEBUG((LM_DEBUG,"�ͷ� ACE Handler"));
}
int HDCCUSvrHandler::open(void*)
{
	
	ACE_INET_Addr peer_addr;
	if(peer().get_remote_addr(peer_addr) == -1)
	{
		return -1;
	}
	ACE_DEBUG((LM_DEBUG,"������������[%s]",peer_addr.get_host_addr()));
	// TODO : ���IP��ַ�Ƿ�Ϸ�
	/*
	 if( IP ���Ϸ� )
		return -1;
	 */
	_close_time = 1;
	try
	{
		REACTOR::instance()->register_handler(this,READ_MASK);
	}
	catch(...)
	{
		return -1;
	}
	
	return 0;
}

int HDCCUSvrHandler::handle_input(ACE_HANDLE fd)
{
	ACE_Message_Block * mb;
	ACE_NEW_RETURN(mb,ACE_Message_Block(MAX_MESBUF_LEN),0);
	// read data
	ACE_INT32 n = 0;
	ACE_INT32 m = 0;
	while( (n = peer().recv(mb->wr_ptr(),mb->size() - m)) >= 0 )
	{
		mb->wr_ptr(n);
	}
	if(mb->length() <= 0)
	{
		mb->release();
		return -1;
	}

	// �������
	if(putq(mb) == -1)
	{
		ACE_DEBUG((LM_ERROR,"����ʧ��"));
		return -1;
	}
	_close_time = 1;
	// �߳��Ѿ�����,���� 0 ��ʾ���Լ��������¼�
	REACTOR::instance()->remove_handler(this,
		ACE_Event_Handler::READ_MASK|ACE_Event_Handler::DONT_CALL|
		ACE_Event_Handler::WRITE_MASK);
	activate(THR_NEW_LWP|THR_JOINABLE,1);
	//ACE_Time_Value reschedule(_max_timeout_sec.sec()/2);
	REACTOR::instance()->schedule_timer(this,NULL,_max_timeout_sec);
	return 0;
}

int HDCCUSvrHandler::handle_timeout(const ACE_Time_Value &time, const void *)
{
	ACE_DEBUG((LM_INFO,"ACE ���ӳ�ʱ��"));
	REACTOR::instance()->remove_handler(this,ACE_Event_Handler::READ_MASK|DONT_CALL);
	return -1;
}

int HDCCUSvrHandler::handle_close(ACE_HANDLE handler, ACE_Reactor_Mask mask)
{
	REACTOR::instance()->remove_handler(this,READ_MASK|DONT_CALL);
	dec_close_time();
	delete_self(handler);
	ACE_DEBUG((LM_DEBUG,"ACE �ر�����..................."));
	return 0;
}

//int HDCCUSvrHandler::close(u_long flags)
//{
//	dec_close_time();
//	delete_self();
//	return 0;
//}

void HDCCUSvrHandler::dec_close_time()
{
	_mutex.acquire();
	_close_time = (--_close_time >=  0 ) ? _close_time : 0;
	_mutex.release();
}

void HDCCUSvrHandler::delete_self(ACE_HANDLE handler)
{
	bool canClose = false;
	_mutex.acquire();
	canClose = (_close_time == 0);
	_mutex.release();
	if(canClose)
	{
		//ACE_OS::closesocket(handler);
		delete this;
	}
}

int HDCCUSvrHandler::svc()
{
#define MES_DATA_HEAD_LEN 2

	ACE_DEBUG((LM_DEBUG,"ACE ������............"));
	ACE_Message_Block * mb = NULL;
	
	ACE_Time_Value tv(5);
	if (this->getq(mb,&tv) == -1) return -1;
	HD8583STRUCT req;
	HD8583STRUCT resp;
	MESSAGETYPE msg_type;
	char * buffer = mb->rd_ptr();
	int len = 0;
	// ���ݶγ��ȳ�������Χ,��������
	if(UnPackResponseStruct(req,&msg_type,buffer,mb->length()) != 0)
	{
		ACE_ERROR((LM_ERROR,"���ݰ����Ϸ�"));
		mb->release();
		return -1;
	}
	
	ACE_HEX_DUMP((LM_DEBUG,mb->rd_ptr(),mb->length()));
	try
	{
		HDResponseHandler* handler = HDCCUProcessUnits::instance()->Create(msg_type);
		if(handler)
		{
			resp.Init();
			
			int result = handler->DoResponse(req,resp,peer().get_handle());
			if(result > 0)
			{
				// send back
				mb->reset();
				buffer = mb->wr_ptr();
				len = (int)PackRequestStruct(resp,msg_type,buffer,mb->size());
				mb->wr_ptr(len);
				ACE_HEX_DUMP((LM_DEBUG,buffer,mb->length()));
				ACE_DEBUG((LM_DEBUG,"���ݰ�����[%d]",mb->length()));
				if(peer().send_n(mb->rd_ptr(),mb->length()) <=0 )
				{
					ACE_DEBUG((LM_ERROR,"����Ӧ���ʧ��"));
				}
				
			}
			else if(result == 0)
			{
				// OK
				ACE_DEBUG((LM_DEBUG,"����ɹ�"));
			}
			else
			{
				// error
				ACE_DEBUG((LM_ERROR,"��������ʧ�ܣ�������[%d]",result));
			}
		}
		else
		{
			ACE_ERROR((LM_ERROR,"���ܴ����������[%c]",msg_type));
		}	
	}
	catch(...)
	{
		// �������е��쳣
		ACE_ERROR((LM_ERROR,"���������쳣,�������[%02x]",msg_type));
	}	
	mb->release();
	return 0;
}

////////////////////////////////////////////////////////////////////////
// 
HD_REGISTER_HANDLER(MT_REECHO1,HDReechoHandler1);
int HDReechoHandler1::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	//sockaddr_in sock_addr;
	//memset(&sock_addr,0,sizeof sock_addr);
	/*
	ACE_INET_Addr peer_addr;
	ACE_SOCK_Stream stream(peer);
	*/
	unsigned int termid = req->TerminalSN;
	unsigned short canid = req->Address;
	//��������Բ���Ҫ�ж� CCU �µ��豸�Ƿ����
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
	
	//if(ACE_OS::getpeername(peer,(sockaddr*)&(sock_addr.sin_addr),sizeof(peer_addr)))
	/*
	if(stream.get_remote_addr(peer_addr) == -1)
	{
		ACE_DEBUG((LM_ERROR,"��������޷�ȡ�öԷ�IP!"));
		return -1;
	}
	*/
	char ipbuf[10] = "";
	//peer_addr.set(&sock_addr,sizeof(sock_addr));

	ACE_UINT32 ip = _remote_addr.get_ip_address();
	// ȫ��ʹ�������ֽ���
	ip = ACE_HTONL(ip);
	ACE_OS::memcpy(ipbuf,(const void*)&ip,sizeof ip);
	ACE_DEBUG((LM_INFO,"�������,ip[%s]",_remote_addr.get_host_addr()));
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,ipbuf,ACE_OS::strlen(ipbuf));
	// ��ҪӦ��
	return 1;
}

//////////////////////////////////////////////////////////////////////////////
// ˮ�ػ���������ָ��
HD_REGISTER_HANDLER(MT_APPLYCONSUME,HDApplyConsumeHandler);
int HDApplyConsumeHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{

	int cardno = req->CardNumber;
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_CARDNUMBER,req->CardNumber);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_CONFIREPORTLOSSCARD);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	int respCode = hd_loadCardState.is_valid_card(cardno);
	//ACE_DEBUG((LM_DEBUG,"����Ϊ:%d,��֤Ϊ: %d",cardno,respCode));
	if (!respCode)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	}
	else
		ACE_DEBUG((LM_INFO,"����:[%d]Ϊ�ڿ�",cardno));
	return 1;

}
//////////////////////////////////////////////////////////////////////////////
int HDEnrollHandler::do_offline(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
//	size_t packlen;
//	int ret;
//	int term_no;
	char phyid[12] = "";
	char card_phyid[9] = "";
	char sn[9]  = "";
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_AUTHCARD_ERROR);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	//resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// ����ǳ�ֵ����
		obj->SetRequestHeader(849005);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		EncodeTermSN(req->TerminalSN,sn);
		obj->AddField(F_SDATE1,sn);
		obj->AddField(F_LVOL5,req->CardNumber);
		int phyid;
		BUF_2_INT_LE(phyid,req->AdditionalData2);
		HDConvertCardPhyNo(phyid,card_phyid);
		obj->AddField(F_SDATE0,card_phyid);
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{
			if(!obj->GetReturnCode())
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
			}
		}
	}
	return 1;
}
int HDEnrollHandler::do_online(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
//	int ret;
	int term_no;
	char phyid[12] = "";
	char date[9] ="";
	char time[9] ="";
	char opercode[9]="";
	char blkVersion[16]="";
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	sprintf(date,"20%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
	for(int i=0;i<14;i++)
	{
		sprintf(blkVersion+i,"%c",req->AdditionalData1[i]);
	}
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	BUF_2_INT_LE(term_no,req->PIN);
		KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// �豸ǩ��
		obj->SetRequestHeader(950050);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SDATE1,phyid);						//�ն����к�
		obj->AddField(F_SPOST_CODE,date);				//����
		obj->AddField(F_SPOST_CODE2,time);				//ʱ��
		//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_SSTATION0,term_no);			//�ն˻����
		obj->AddField(F_SNAME,blkVersion+2);			//������
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{
			if(!obj->GetReturnCode())
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					sprintf(blkVersion,"20%s",data->sname);
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion);
					unsigned char buf[256];
					int len;
					len = strlen(data->scust_limit);
					xutil::StringUtil::Str2BCD(data->scust_limit,len,buf);
					len /= 2;
					buf[len]=atoi(data->scust_limit2);
					len++;
					resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,len);
					ACE_DEBUG((LM_INFO,"ǩ���ɹ�!!dev[%s]blkVersion[%s]",phyid,data->sname));
				}
			}
		}
	}
	return 1;
}
// �豸ǩ��ָ��
HD_REGISTER_HANDLER(MT_SIGNIN1,HDEnrollHandler);
int HDEnrollHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	if(theGlobalGateWay->GetConfig()->_devType == "ONLINE")
		return do_online(req,resp,peer);
	else
		return do_offline(req,resp,peer);
}

///////////////////////////////////////////////////////////////////////////
//
HD_REGISTER_HANDLER(MT_INITKEY1,HDInitKeyHandler);
int HDInitKeyHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	// ����豸��Ϣ
	//ACE_INET_Addr peer_addr;
	//ACE_SOCK_Stream peer_sock(peer);
	std::string device_ip;
	char buf[32] = "";
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_INVALIDTERMINAL);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,24);
	/*
	if(peer_sock.get_remote_addr(peer_addr))
	{
		ACE_DEBUG((LM_NOTICE,"ȡ�öԷ����ӵ�ַ����"));
		return 1;
	}
	*/
	KSGDeviceManager * manager = KsgGetGateway()->GetDeviceManager();
	char phyid[12] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode * node = manager->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_NOTICE,"�豸������[%s]",phyid));
		return 1;
	}

	KSGDeviceNode *parent_node = node->GetParent();
	if(parent_node == NULL || parent_node->GetDevId() == KSGDeviceNode::LoopDeviceId)
	{
		// �������̫���豸
		device_ip = node->GetDevAddr().GetConnect();
		if(node->GetDeviceType() != KSG_HD_SERVER_DEV)
		{
			unsigned short addr_port = GetDeviceAddress(node);
			// �Ƚ��豸��ַ
			if((req->Address & 0x00FF) != (addr_port & 0x00FF))
			{
				ACE_DEBUG((LM_ERROR,"�豸[%s]��ַ����ȷ��ע���ַ[%d]�豸��ַ[%d]"
					,phyid,(addr_port&0x00FF),(req->Address&0x00FF)));
				return 1;
			}
		}
	}
	else
	{
		// ����� CAN �����豸
		device_ip = parent_node->GetDevAddr().GetConnect();
		unsigned short addr_port = GetDeviceAddress(node);
		// �Ƚ��豸��ַ
		if((req->Address & 0x00FF) != (addr_port & 0x00FF))
		{
			ACE_DEBUG((LM_ERROR,"�豸[%s]��ַ����ȷ��ע���ַ[%d]�豸��ַ[%d]"
				,phyid,(addr_port&0x00FF),(req->Address&0x00FF)));
			return 1;
		}
	}
	// �Ƚ� IP ��ַ
	if(device_ip == this->_remote_addr.get_host_addr() 
		|| node->GetConnType() == KSGDeviceURL::dctModem)
		//|| ACE_OS::strcmp(peer_addr.get_host_addr(),"0.0.0.0")==0)
	{
		if(xutil::StringUtil::Str2Hex(
			KsgGetGateway()->GetConfig()->_cardKey.c_str(),(unsigned char*)buf,8) == -1)
			return -1;
		ACE_OS::memset(buf+8,0xFF,16);
		resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,24);
		ACE_DEBUG((LM_INFO,"�豸[%s]����IP[%s],����[%d] ����ǩ���ɹ�",
			phyid,this->_remote_addr.get_host_addr(),node->GetTermId()));
	}
	else
	{
		ACE_DEBUG((LM_NOTICE,"�豸[%s]����IP[%s],ϵͳע��IP[%s],�豸��Ϣ��ϵͳ��ƥ��",
			phyid,this->_remote_addr.get_host_addr(),device_ip.c_str()));
	}
	// ������Կ
	return 1;
}

////////////////////////////////////////////////////////////////////////
//
int HDDownloadBlkCard::DownloadBlackCard(BYTE addflag,KSGDeviceNode* node
										 ,KSGDeviceNode::Task* task)
{
	// ���ӣ�ɾ��������
	/*
	int ret = TASK_ERR_COMMON;
	try
	{
		int result;
		int cardid = task->GetParams().GetParamIntVal(XML_KEY_CARDID);
		std::string version = task->GetParams().GetParam(XML_KEY_VERNUM);
		KSGDeviceNode* task_node = task->GetDeviceNode();
		unsigned short addr;
		addr = GetDeviceAddress(task_node);
		// ׼��������������
		HD8583STRUCT req;
		req.Init();
		req.SetFieldValue(FIELD_ADDRESS,addr); // �ն˵�ַ
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId()); // �ն˻���
		unsigned long encode_ver = EncodeVersionNum(version.c_str()); // ѹ���汾��
		req.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// �������汾��
		char data[256] = "";
		ACE_OS::memset(data,0,sizeof data);
		data[0] = addflag;
		INT_2_BUF(cardid,data+1); 
		req.SetFieldValue(FIELD_ADDITIONALDATA2,data,5);  //  ���׿���
		data[0] = 0x01; 
		req.SetFieldValue(FIELD_ADDITIONALDATA3,data,1); // ��������
		ACE_OS::memset(data,0,sizeof data);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		ACE_Time_Value tv(3,0);
		int recvlen = -1;
		size_t packlen;
		handler = task->_handle;
		// ѹ�����ݰ�
		if((packlen = PackRequestStruct(req,MT_UPDATELIST2,data,sizeof data,true)) == 0)
		{
			// ��������ݰ�
			ret = TASK_ERR_COMMON;
			return ret;
		}		
		ACE_HEX_DUMP((LM_INFO,data,packlen));
		if((result=HDSendBuffer(handler,data,packlen,&tv))) // �������ݰ�
		{

			ACE_DEBUG((LM_ERROR,"���ͺ���������ʧ�ܣ�������[%d]",result));
			ret = TASK_ERR_TIMEOUT;
		}
		else
		{
			KSGThreadUtil::Sleep(60);
			tv = ACE_Time_Value(1);
			memset(data,0,sizeof data);
			if((recvlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0) // �������ݰ�
			{
				ACE_DEBUG((LM_ERROR,"ִ�к����������ͳ�ʱ,dev[%d][%s]",
					task_node->GetDevId(),task_node->get_name().c_str()));
				ret = TASK_ERR_TIMEOUT;
			}
			else
			{
				HD8583STRUCT resp;
				MESSAGETYPE msg_type;
				ACE_HEX_DUMP((LM_INFO,data,recvlen));
				if(UnPackResponseStruct(resp,&msg_type,data,(size_t)recvlen)) // ��ѹ���ݰ�
				{
					ACE_DEBUG((LM_ERROR,"ִ�к���������ʧ��,dev[%d][%s]",
						task_node->GetDevId(),task_node->get_name().c_str()));
					ret = TASK_ERR_EXECUTE;
				}
				else if( (req->Address != resp->Address)
					|| (req->VerOfList != resp->VerOfList)) // �Ƚ�POS��Ӧ����ҵĺ������汾��
				{
					char ver[15] = "";
					DecodeVersionNum(resp->VerOfList,ver);
					ACE_DEBUG((LM_ERROR,"���ͺ���������ʧ�ܣ�������[%d]�豸[%d][%s]�汾��[%s]"
						,resp->ResponseCode,task_node->GetDevId(),task_node->get_name().c_str(),ver));
					if(resp->ResponseCode != 39)
					{

						ret = TASK_ERR_EXECUTE;
						return ret;
					}
					else
					{
						// ���ܰ汾���Ѿ�������
						ACE_DEBUG((LM_INFO,"�豸[%d][%s]�豸�汾��[%s],ϵͳ�汾��[%s]"
							,task_node->GetDevId(),task_node->get_name().c_str(),ver,version.c_str()));
						ret = TASK_SUCCESS;
					}
				}
				else
				{
					ret = TASK_SUCCESS;
				}
				if(ret == TASK_SUCCESS)
				{
					// �ɹ�����Ӧ�����̨
					KSGTaskResponse &tresp = task->GetResponse();
					tresp.AddField(XML_KEY_CARDID,cardid);
					char version_str[14] = "";
					DecodeVersionNum(resp->VerOfList,version_str);
					tresp.AddField(XML_KEY_VERNUM,version_str);
					ACE_DEBUG((LM_INFO,"�����豸�������汾�ɹ�[%d][%s]�汾��[%s]"
						,task_node->GetDevId(),task_node->get_name().c_str(),version_str));
				}
			}
		}
		return ret;
	}
	catch(KeyNotFoundException& )
	{
		return TASK_ERR_COMMON;
	}
	catch(...)
	{
		return TASK_ERR_COMMON;
	}
	*/
	// ���ӣ�ɾ��������
	int ret = TASK_ERR_COMMON;
	try
	{
		int result;
		int cardid = task->GetParams().GetParamIntVal(XML_KEY_CARDID);
		std::string version = task->GetParams().GetParam(XML_KEY_VERNUM);
		KSGDeviceNode* task_node = task->GetDeviceNode();
		unsigned short addr;
		addr = GetDeviceAddress(task->GetDeviceNode());
		// ׼��������������
		HD8583STRUCT req;
		req.Init();
		unsigned long sn = DecodeTermSN(task_node->GetPhyId().c_str());
		//req.SetFieldValue(FIELD_TERMINALSN,sn);
		req.SetFieldValue(FIELD_ADDRESS,addr); // �ն˵�ַ
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId()); // �ն˻���
		unsigned long encode_ver = EncodeVersionNum(version.c_str()); // ѹ���汾��
		req.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// �������汾��
		char data[256] = "";
		ACE_OS::memset(data,0,sizeof data);
		data[0] = addflag;
		INT_2_BUF(cardid,data+1); 
		req.SetFieldValue(FIELD_ADDITIONALDATA2,data,5);  //  ���׿���
		data[0] = 0x01; 
		req.SetFieldValue(FIELD_ADDITIONALDATA3,data,1); // ��������
		ACE_OS::memset(data,0,sizeof data);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
		int recvlen = -1;
		size_t packlen;
		handler = task->_handle;
		// ѹ�����ݰ�
		if((packlen = PackRequestStruct(req,MT_UPDATELIST2,data,sizeof data,true)) == 0)
		{
			// ��������ݰ�
			ret = TASK_ERR_COMMON;
		}		
		else if((result=HDSendBuffer(handler,data,packlen,&tv))) // �������ݰ�
		{

			ACE_DEBUG((LM_ERROR,"���ͺ���������ʧ�ܣ�������[%d]",result));
			ret = TASK_ERR_TIMEOUT;
		}
		else 
		{
			ACE_HEX_DUMP((LM_DEBUG,data,packlen));
			KSGThreadUtil::Sleep(30);
			tv = ACE_Time_Value(1);
			if((recvlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0) // �������ݰ�
			{
				ACE_DEBUG((LM_ERROR,"ִ�к����������ͳ�ʱ,dev[%d][%s]",
					task_node->GetDevId(),task_node->get_name().c_str()));
				ret = TASK_ERR_TIMEOUT;
			}
			else
			{
				HD8583STRUCT resp;
				MESSAGETYPE msg_type;
				ACE_HEX_DUMP((LM_DEBUG,data,recvlen));
				// ��Ϊ POS ������
				if(recvlen < 17)
				{
					ret = TASK_ERR_EXECUTE;
				}
				else if(UnPackResponseStruct(resp,&msg_type,data,recvlen)) // ��ѹ���ݰ�
				{
					ACE_DEBUG((LM_ERROR,"ִ�к���������ʧ��,dev[%d][%s]",
						task_node->GetDevId(),task_node->get_name().c_str()));
					ret = TASK_ERR_EXECUTE;
				}
				else if( (req->Address != resp->Address)
					|| (req->VerOfList != resp->VerOfList)) // �Ƚ�POS��Ӧ����ҵĺ������汾��
				{
					char ver[15] = "";
					DecodeVersionNum(resp->VerOfList,ver);
					ACE_DEBUG((LM_ERROR,"���ͺ���������ʧ�ܣ�������[%d]�豸[%d][%s]�汾��[%s]"
						,resp->ResponseCode,task_node->GetDevId(),task_node->get_name().c_str(),ver));
					if(resp->ResponseCode != 39)
					{

						ret = TASK_ERR_EXECUTE;
						return ret;
					}
					else
					{
						// ���ܰ汾���Ѿ�������
						ACE_DEBUG((LM_INFO,"�豸[%d][%s]�豸�汾��[%s],ϵͳ�汾��[%s]"
							,task_node->GetDevId(),task_node->get_name().c_str(),ver,version.c_str()));
						ret = TASK_SUCCESS;
					}
				}
				else
					ret = TASK_SUCCESS;
				if(ret == TASK_SUCCESS)
				{
					// �ɹ�����Ӧ�����̨
					KSGTaskResponse &tresp = task->GetResponse();
					tresp.AddField(XML_KEY_CARDID,cardid);
					char version_str[14] = "";
					DecodeVersionNum(resp->VerOfList,version_str);
					tresp.AddField(XML_KEY_VERNUM,version_str);
					ACE_DEBUG((LM_INFO,"�����豸�������汾�ɹ�id[%d][%s]"
						,task_node->GetDevId(),version_str));
					ret = TASK_SUCCESS;
				}
			}
		}
		task->SetNeedResponse();
		return ret;
	}
	catch(KeyNotFoundException& )
	{
		return TASK_ERR_COMMON;
	}
	catch(...)
	{
		return TASK_ERR_COMMON;
}
}

/////////////////////////////////////////////////////////////////////////////
// 
HD_REGISTER_HANDLER(MT_QUERYHISTORYTRADE1,HDQueryPosTrade);

int HDQueryPosTrade::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret,offset,num;
	char term_no[17] = "";
	char phyid[20] = "";
	char start_datetime[20]="";
	char end_datetime[20]="";
	char buffer[32] = "";
	short shopid = 0;
	unsigned char addData[9] = "";
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);

	char datetime1[7]="";
	char datetime2[7]="";
	memcpy(datetime1,req->AdditionalData2,6);
	memcpy(datetime2,req->AdditionalData2 + 6,6);
	sprintf(start_datetime,"20%02d%02d%02d%02d%02d%02d",datetime1[0],datetime1[1],datetime1[2],datetime1[3],datetime1[4],datetime1[5]);
	sprintf(end_datetime,"20%02d%02d%02d%02d%02d%02d",datetime2[0],datetime2[1],datetime2[2],datetime2[3],datetime2[4],datetime2[5]);

	
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);

	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	ACE_DEBUG((LM_DEBUG,"��ѯ�ն���ʷ���ף��ն˻����[%s]",term_no));

	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_INFO,"�豸 [%s]������!",phyid));
		return 1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{		
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		if(node->GetDeviceType() == KSG_999_DEV_ADDPOS)
		{
			obj->SetRequestHeader(950074);
			obj->AddField(F_SPHONE3,phyid);									//�ն����к�
			obj->AddField(F_LWITHDRAW_FLAG,node->GetDevId());				//�豸id
			obj->AddField(F_SHOLDER_AC_NO,start_datetime);					//��ʼʱ��
			obj->AddField(F_SHOLDER_AC_NO2,end_datetime);					//����ʱ��

			offset = 0;
			BUF_2_INT(num,req->AdditionalData1+offset);
			obj->AddField(F_LVOL1,num); // ���κź�
			offset += 4;

			BUF_2_INT(num,req->AdditionalData1+offset);
			obj->AddField(F_LVOL2,num); // ��Ȩ��
			offset += 4;

			memset(buffer,0,sizeof buffer);
			memcpy(buffer,req->AdditionalData1+offset,8);
			obj->AddField(F_SEMP_NO,buffer); // ����Ա��
		}
		else
		{
			obj->SetRequestHeader(950065);
			obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
			obj->AddField(F_SPHONE3,phyid);									//�ն����к�
			obj->AddField(F_LSAFE_LEVEL,node->GetDevId());					//�豸id
			ACE_DEBUG((LM_DEBUG,"�豸id [%d] ",node->GetDevId()));
			obj->AddField(F_SHOLDER_AC_NO,start_datetime);					//��ʼʱ��
			obj->AddField(F_SHOLDER_AC_NO2,end_datetime);					//����ʱ��
		
			obj->AddField(F_SSTATION0,term_no);								//�ն˻����
			
			obj->AddField(F_LVOL3,shopid);									//�̻���
		}

	
		ACE_DEBUG((LM_INFO,"�ն�[%s]��ѯ��ʷ����",phyid));
		if(!obj->SendRequest(5000))
		{
			ret = obj->GetReturnCode();
			if(!ret)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					INT_2_BUF_LE(data->lvol1,addData);								//�ܱ���
					INT_2_BUF_LE(data->lvol2,addData+4);							//�ܽ��
					ACE_DEBUG((LM_DEBUG,"��ѯ�ն���ʷ���ף��ܱ���[%d],�ܽ��[%d]��",data->lvol1,data->lvol2));
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,addData,8);
				}
			}
			else
			{			
				resp.SetFieldValue(FIELD_RESPONSECODE,ret);
				ACE_DEBUG((LM_ERROR,"��ѯ�ն���ʷ����!!dev[%s],��̨���ش�����[%d]",phyid,ret));				
			}
		}
	}
	return 1;
}
/////////////////////////////////////////////////////////////////////////////
// HDOnlineNotice
HD_REGISTER_HANDLER(MT_ONLINENOTICE1,HDOnlineNotice);
int HDOnlineNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	MYDATETIMESTRUCT now;
	KSGDeviceManager * manager = KsgGetGateway()->GetDeviceManager();
	char phyid[12] = "";
	char version[14] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	KSGDeviceNode * node = manager->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_INFO,"�豸������[%s]",phyid));
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		return 1;
	}
	else
	{
		// ��¼�豸״̬��Ϣ
		node->SetState(KSGDeviceNode::dsOnline);
		int reccnt;
		BUF_2_INT(reccnt,req->AdditionalData1);
		if(reccnt > 0)
			node->SetState(KSGDeviceNode::dsHasRecord);
		node->update_time();
	}
	
	//char buf[32] = "";
	//if(xutil::StringUtil::Str2Hex(
	//	KsgGetGateway()->GetConfig()->_cardKey.c_str(),(unsigned char*)buf,8) == -1)
	//	return -1;
	//ACE_OS::memset(buf+8,0xFF,16);
	//resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,24);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	now = HDGetDataTime();
	resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,7);
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
	
	if(node->GetConnType() == KSGDeviceURL::dctModem)
	{
		// ��Ϊ�� GPRS POS ��
		long curr_ver;
		curr_ver = EncodeVersionNum(KsgGetGateway()->get_max_blk_version());
		resp.SetFieldValue(FIELD_VERSIONOFLIST,curr_ver);
	}
	else
		resp.SetFieldValue(FIELD_VERSIONOFLIST,req->VerOfList);
	
	// ������Կ
	return 1;
}
/////////////////////////////////////////////////////////////////////////////
//
ACE_Thread_Mutex HDRecordFileReader::_s_file_lock_mutex;
HDRecordFileReader::CCU_DEVICE_LOCK_TYPE HDRecordFileReader::_s_device_lock;

int HDRecordFileReader::test_lock_ccu(int devid)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_s_file_lock_mutex,1);
	//_s_file_lock_mutex.acquire_read();
	CCU_DEVICE_LOCK_TYPE::const_iterator i = _s_device_lock.find(devid);
	// �豸�Ѵ���
	if(i != _s_device_lock.end())
		return 0;
	return 1;
}

int HDRecordFileReader::lock_ccu(int devid)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_s_file_lock_mutex,-1);
	int ret = -1;
	// 5s ��ʱ
	/*
	ACE_Time_Value tv = ACE_OS::gettimeofday();
	tv += ACE_Time_Value(5,0);
	if(_s_file_lock_mutex.acquire(&tv)>0)
	{
		ACE_DEBUG((LM_ERROR,"���ʧ��"));
		return -1;
	}
	*/
	CCU_DEVICE_LOCK_TYPE::const_iterator i = _s_device_lock.find(devid);
	// �豸�Ѵ���
	if(i != _s_device_lock.end())
		ret = -1;
	else
	{
		_s_device_lock.insert(devid);
		ret = 0;
	}
	//ACE_DEBUG((LM_INFO,"�����ļ�"));
	//_s_file_lock_mutex.release();
	return ret;
}

int HDRecordFileReader::free_ccu_lock(int devid)
{
	//vACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_s_file_lock_mutex,-1);
L_TEST_AGAIN:
	{
		ACE_Guard<ACE_Thread_Mutex> guard(_s_file_lock_mutex);
		if(!guard.locked())
		{
			ACE_DEBUG((LM_ERROR,"�ͷ�CCU��¼����,������Դʧ��!"));
			goto L_TEST_AGAIN;
		}
		CCU_DEVICE_LOCK_TYPE::iterator i = _s_device_lock.find(devid);
		// �豸�Ѵ���
		if(i != _s_device_lock.end())
		{
			_s_device_lock.erase(i);
		}
		return 0;
	}
}
HDRecordFileReader::~HDRecordFileReader()
{
	//
}

int HDRecordFileReader::ReadFile()
{
	int ret = -1;
	ACE_DEBUG((LM_TRACE,"��ʼ������¼�ļ�!"));
	HDRecordFileReader_Lock_Guard ccu_guard(_device_id);
	if(!ccu_guard.is_owner())
	{
		ACE_DEBUG((LM_ERROR,"������¼�ļ�ʧ��[%s]",_filepath.c_str()));
		return -1;
	}
	try
	{
		if(ACE_OS::filesize(_filepath.c_str()) == 0)
		{
			ACE_DEBUG((LM_INFO,"�ռ�¼�ļ�,����Ҫ�ɼ�"));
			ret = 0;
		}
		else if((_file_handler = ACE_OS::open(_filepath.c_str()
			,O_RDWR)) == ACE_INVALID_HANDLE)
		{
			ACE_DEBUG((LM_ERROR,"����ˮ��¼�ļ�ʧ��"));
			ret = -1;
		}
		else
		{
			ret = ReadPosRecord();	
			ACE_OS::close(_file_handler);
		}
		if(ret == 0)
		{	
#if 0
			if(ACE_OS::unlink(_filepath.c_str()))
			{
				ACE_DEBUG((LM_ERROR,"ɾ���ɼ���ɼ�¼�ļ�ʧ��[%s][%s:%d]"
					,_filepath.c_str(),ACE_OS::strerror(ACE_OS::last_error())
					,ACE_OS::last_error()));
				ret = -1;
			}
#else
			std::string stamp;
			std::string newname;
			KSGOSUtil::GetTimestamp(stamp);
			std::string date_str = stamp.substr(0,6);
			date_str+="/";
			int pos = _filepath.rfind(KSGOSUtil::sc_path_sep);
			if(pos > 0)
			{
				std::string basepath = _filepath.substr(0,pos);
				basepath = KSGOSUtil::JoinPath(basepath,date_str);
				ACE_DIR* dir = ACE_OS::opendir(basepath.c_str());
				if(!dir)
				{
					if(ACE_OS::mkdir(basepath.c_str()))
					{
						ACE_DEBUG((LM_ERROR,"����Ŀ¼ʧ��[%s]",basepath.c_str()));
						ret = -1;
					}
				}
				else
					ACE_OS::closedir(dir);
				std::string file_name = _filepath.substr(pos+1) + "." + stamp;
				newname = KSGOSUtil::JoinPath(basepath,file_name);
			}
			else
			{
				newname = _filepath + "." + stamp;
			}
			if(!ret)
			{
				if(ACE_OS::rename(_filepath.c_str(),newname.c_str()))
				{
					ACE_DEBUG((LM_ERROR,"ɾ���ɼ���ɼ�¼�ļ�ʧ��[%s][%s:%d]"
						,_filepath.c_str(),ACE_OS::strerror(ACE_OS::last_error())
						,ACE_OS::last_error()));
					ret = -1;
				}
			}
			
#endif
		}
		else if(ret == -2)
		{
			// modify by cash 2007-1-25
			// �����������,���ڱ��ص���ˮ�ļ���С����ȷ,�����ܶ�ס�������ˮ
			// ��˽�����ļ����߱���
			std::string stamp;
			KSGOSUtil::GetTimestamp(stamp);
			std::string newname = _filepath + "." + stamp + ".err";
			ACE_DEBUG((LM_NOTICE,"���ؼ�¼�ļ���С����ȷ[%s],����Ϊ[%s]"
				,_filepath.c_str(),newname.c_str()));
			if(ACE_OS::rename(_filepath.c_str(),newname.c_str()))
			{
				ACE_DEBUG((LM_ERROR,"��������¼�ļ�ʧ��[%s][%s:%d]"
					,_filepath.c_str(),ACE_OS::strerror(ACE_OS::last_error())
					,ACE_OS::last_error()));
				ret = -1;
			}
		}
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"�����ļ�ʧ��,����δ֪�쳣"));
		ret = -1;
	}
	/*
	if(free_ccu_lock(_device_id))
	{
		ACE_DEBUG((LM_ERROR,"�ͷż�¼�ļ�ʧ��[%s]",_filepath.c_str()));
	}
	*/
	return ret;
}
int HDRecordFileReader::ReadPosRecord()
{
	/*
	std::string index_file = _filepath + ".ind";
	ACE_File_Lock file_lock(_file_handler);
	int ret = -1;
	_file_handler = ACE_OS::dup(file_lock.get_handle());
	if(file_lock.tryacquire())
	{
		ACE_DEBUG((LM_ERROR,"������¼�ļ�ʧ��[%s]",_filepath.c_str()));
		return -1;
	}
	try
	{
		ACE_DEBUG((LM_DEBUG,"������¼�ļ��ɹ�,��ʼ����..."));
		ret = DoReadRecordFile();
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"�����¼�ļ��쳣......."));
		ret = -1;
	}
	
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"�����¼ʧ��"));
	}
	else
	{
		ACE_OS::unlink(index_file.c_str());
	}
	if(file_lock.release())
	{
		ACE_DEBUG((LM_ERROR,"�ͷż�¼�ļ�ʧ��[%s]",_filepath.c_str()));
	}
	return ret;
	
	*/
	std::string index_file = _filepath + ".ind";
	int ret = -1;
	
	try
	{
		ACE_DEBUG((LM_DEBUG,"������¼�ļ��ɹ�,��ʼ����..."));
		ret = DoReadRecordFile();
	}
	catch(std::exception &ex)
	{
		KSG_DUMP_EXCEPTION(ex);
		ACE_DEBUG((LM_ERROR,"�����¼�ļ��쳣......."));
		ret = -1;
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"δ֪�쳣�������¼�ļ��쳣......."));
		ret = -1;
	}

	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"�����¼ʧ��"));
	}
	else
	{
		if(ACE_OS::unlink(index_file.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"ɾ�������ļ�ʧ�ܣ�"));
			ret = -1;
		}
	}
	return ret;
	
}
int HDRecordFileReader::SaveIndex(size_t index)
{
	std::string index_file = _filepath + ".ind";
	FILE* fp;
	if((fp = ACE_OS::fopen(index_file.c_str(),"wb+")) == NULL)
	{
		return -1;
	}
	ACE_OS::fwrite((void*)&index,1,sizeof(size_t),fp);
	ACE_OS::fclose(fp);
	return 0;
}
size_t HDRecordFileReader::LoadIndex()
{
	std::string index_file = _filepath + ".ind";
	if(!KSGOSUtil::FileExists(index_file))
		return 0;
	FILE* fp;
	if((fp = ACE_OS::fopen(index_file.c_str(),"rb")) == NULL)
	{
		return 0;
	}
	size_t ind = 0;
	size_t readbytes = ACE_OS::fread((void*)&ind,1,sizeof(size_t),fp);
	if(readbytes != sizeof(size_t))
		ind = 0;
	ACE_OS::fclose(fp);
	return ind;
}
int HDRecordFileReader::DoReadRecordFile()
{
	unsigned char buf[MAX_RECORD_BUF_LEN] = "";
	int record_buf_len;
	long filesize = 0;
	if((filesize = ACE_OS::lseek(_file_handler,0L,SEEK_END)) == -1 )
	{
		ACE_DEBUG((LM_ERROR,"ȡ���ļ���Сʧ��"));
		return -1;
	}
	// ��СΪ�յ��ļ���Ҫɾ��
	if(filesize == 0)
	{
		ACE_DEBUG((LM_ERROR,"�ռ�¼�ļ����Զ�ɾ��.."));
		return 0;
	}
	switch(_record_type)
	{
	case POS_RECORD:
		record_buf_len = RECORD_BUF_LEN;
		break;
	case ATTENDENT_RECORD:
		record_buf_len = ARECORD_BUF_LEN;
		break;
	default:
		ACE_DEBUG((LM_ERROR,"�����ļ�ʱ���ļ�����δ֪��"));
		return -1;
	}
	// �ļ���С����
	// modify cash 2007-09-05 �����С����ȷ����ˮ
	/*
	if(filesize % RECORD_BUF_LEN != 0)
	{
		ACE_DEBUG((LM_ERROR,"��ˮ��¼�ļ���С����ȷ!"));
		return -2;
	}
	*/
	size_t reccnt = filesize / record_buf_len;
	size_t index = LoadIndex();
	// ��Ϊ��ȡ��
	if(index >= reccnt)
		return 0;
#if 1
	if(index > 0)
		ACE_DEBUG((LM_DEBUG,"���·�����¼�ļ�index[%d]",index));
#endif
	if(ACE_OS::lseek(_file_handler,record_buf_len*index,SEEK_SET) == -1)
	{
		ACE_DEBUG((LM_ERROR,"��λ��¼ʧ��!"));
		return -1;
	}
	ssize_t readbytes = 0;
	ssize_t bufsize = 0;
	do
	{
		readbytes = ACE_OS::read(_file_handler,buf+bufsize,record_buf_len - bufsize);
		if(readbytes == 0)
		{
			if(bufsize == record_buf_len)
			{
				// һ����ˮ
				ACE_DEBUG((LM_DEBUG,"���ڴ������һ����¼[%d]...",index));
				if(DoSaveRecord(buf))
					return -1;
				SaveIndex(++index);
			}
			else if(bufsize > 0)
			{
				ACE_DEBUG((LM_NOTICE,"��ǰ��ˮ��¼�ļ��Ĵ�С����ȷ"));
			}
			return 0;
		}
		else if(readbytes < 0)
		{
			ACE_DEBUG((LM_ERROR,"��ȡ��¼�ļ�ʧ��"));
			return -1;
		}
		bufsize += readbytes;
		if(bufsize == record_buf_len)
		{
			// һ����ˮ
			ACE_DEBUG((LM_TRACE,"���ڴ����¼[%d]...",index));
			if(DoSaveRecord(buf))
				return -1;
			SaveIndex(++index);
			bufsize = 0;
		}
		//KSGThreadUtil::Sleep(1000);
	}while(1);
	return 0;
}

int HDRecordFileReader::DoSaveRecord(BYTE *buf)
{
	switch(_record_type)
	{
	case POS_RECORD:
		return SavePosRecord(buf);
	case ATTENDENT_RECORD:
		return SaveAttendBuffer(buf);
	default:
		ACE_DEBUG((LM_ERROR,"�����ļ�ʱ���ļ�����δ֪��"));
		return -1;
	}
}

int HDRecordFileReader::SaveAttendBuffer(BYTE *buf,int cardtype)
{
	ATTENDRECORDSTRUCT record;
	unsigned short termno;
	ACE_OS::memset(&record,0,sizeof record);
	BUF_2_LONG_LE(record.CardNumber,buf);

	record.Year = buf[4];
	record.Month = buf[5];
	record.Day = buf[6];
	record.Hour = buf[7];
	record.Minute = buf[8];
	record.Second = buf[9];

	BUF_2_SHORT_LE(termno,buf+10);
	record.TerminalID = termno;
	record.ReaderID = buf[12];
	//1:������Դ��2���رյ�Դ (����ý��ȡ��)
	record.RecordType = (buf[13] & 0x03) + HDA_SYSTEMIDOFATT1_1;		

	return SaveAttendRecord(&record,cardtype);
}

int HDRecordFileReader::SaveAttendRecord(ATTENDRECORDSTRUCT *record,int cardtype)
{
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
		return -1;
	char date_str[9] = "";
	char time_str[7] = "";
	char phyno[9] = "";
	char event_code[30] = "";
	int retries = 3;
	KSGVendorConfig *vendor;
	obj->SetRequestHeader(930203);
	// ���ڻ� ����
	//obj->AddField(F_LVOL3,record->TerminalID);
	// ��ͷ����
	//obj->AddField(F_LVOL1,record->ReaderID);
	obj->AddField(F_LVOL2,0);
	obj->AddField(F_LVOL3,0);
	if(record->ReaderID == 0)
		obj->AddField(F_LVOL1,record->TerminalID);
	else
	{
		// ���ڻ� ����
		obj->AddField(F_LVOL3,record->TerminalID);
		// ��ͷ����
		obj->AddField(F_LVOL1,record->ReaderID);
	}
	// ����
	obj->AddField(F_SBANK_CODE,KSG_JSB_DEV);
	// ����豸
	vendor = KsgGetGateway()->get_vendor_config(KSG_HD_DEV);
	if(vendor)
	{
		obj->AddField(F_LSERIAL0,vendor->_vendor_id);
	}
	else
		ACE_DEBUG((LM_ERROR,"���Ӳ������δ֪"));
	ACE_OS::sprintf(date_str,"20%.02d%.02d%.02d",record->Year,record->Month,record->Day);
	ACE_OS::sprintf(time_str,"%.02d%.02d%.02d",record->Hour,record->Minute,record->Second);
	obj->AddField(F_SDATE0,date_str);
	obj->AddField(F_STIME0,time_str);
	ACE_OS::sprintf(event_code,"%d",record->RecordType);
	obj->AddField(F_SEMP_NO,event_code);
	if(!cardtype)
		KsgCardPhyNo_dec2hex(record->CardNumber,phyno);
	else
		sprintf(phyno,"%08X",record->CardNumber);

	obj->AddField(F_SDATE1,phyno);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	while(retries-->0)
	{
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			continue;
		}
		if(!obj->SendRequest(1000))
		{
			if(!obj->GetReturnCode())
				return 0;
			else
			{
				ACE_DEBUG((LM_ERROR,"�ϴ����ڼ�¼ʧ�ܣ�����[%d][%s]",
					obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
			}
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"�ϴ����ڼ�¼ʱ�����̨ʧ��[%s]",obj->GetErrMsg().c_str()));
		}
		// ��һ������
		KSGThreadUtil::Sleep(300);
	}
	return -1;
}
//�����ѻ���ˮ��¼
int HDRecordFileReader::SaveTradeRecord(TRADERECORDSTRUCT *trade,int posdatatype,int crc_status /* =0 */)
{
	int crc_err = crc_status;
	int revflag=0;
	char devphyid[21]= {0};
	sprintf(devphyid,"%010d",trade->TerminalSN);
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"ʵʱ������ˮKsgGetDrtpPoolʧ��,�豸���к�[%s]�豸��ˮ��[%d]",devphyid,trade->TraceOfPOS));
		return 1;
	}
	unsigned long transmark=0;
	unsigned char cRecordType = trade->RecordType;
	/*
	switch(cRecordType)
	{
	case RT_HD_ONLINE_CONSUME:
		transmark = 153;//0x99
		break;
	case RT_HD_ONLINE_RUSH:
		revflag=1;
		transmark = 254;//0xFE
		break;
	case RT_HD_ONLINE_BLACK:
		transmark=5;
		break;
	case RT_HD_ONLINE_CANCEL:
		revflag=1;
		transmark=cRecordType;
		break;
	default:
		transmark=cRecordType;
		break;
	}
	*/
	transmark = cRecordType;
	if(cRecordType == 2)
	{
		transmark = 5;
	}

	obj->SetRequestHeader(950056);
	obj->AddField(F_LVOL0,cRecordType);				//��¼����
	obj->AddField(F_LVOL2,0);						//������ˮ��־:1����0�ѻ�
	obj->AddField(F_LSERIAL0,revflag);				//��������
	obj->AddField(F_LSERIAL1,posdatatype);			//��������
	obj->AddField(F_LVOL2,0);						//������ˮ��־1����0�ѻ�
	obj->AddField(F_LVOL4,trade->TraceOfPOS);		// ��ˮ��
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SPHONE3,devphyid);
	obj->AddField(F_STX_PWD,"");

	if(transmark == E_999_SUBISIDY)
	{
		// ����ǲ�����ˮ
		obj->AddField(F_LBANK_ACC_TYPE,trade->SubsidyNo); // �������κ�
	}
	else
		obj->AddField(F_LBANK_ACC_TYPE,19); // ͨѶ�汾�� 39 ����

	obj->AddField(F_LBANK_ACC_TYPE2,0); // ��Ŀ�շ�
	char crc[5] = {0};
	xutil::StringUtil::Hex2Str(trade->MAC,2,crc); // CRC У��
	obj->AddField(F_SBANK_CODE2,crc);
	obj->AddField(F_LVOL6,trade->IndexOfEW); // Ǯ����
	obj->AddField(F_LVOL5,trade->CardNumber); // ���׿���
	obj->AddField(F_LVOL3,trade->OperatorID); // ����Ա��
	/*
	 1. ����ʱ, ���׽���� ��ֵ , ������� ��ֵ
	 2. ��ֵʱ, ���׽���� ��ֵ
	 3. ���ѳ���ʱ, ���׽���� ��ֵ , ������� ��ֵ
	 4. ��ֵ����ʱ,���׽���� ��ֵ
	 */
	//ACE_DEBUG((LM_DEBUG,"������ˮ: �豸[%s],����ֵ[%d],���׽��[%d]",long_sn,trade->Balance,trade->Amount));
	obj->AddField(F_LVOL9,trade->Balance);				// �뿨ֵ
	trade->Amount = ABS(trade->Amount) + ABS(trade->AdditionalMoney); // ���ϴ���
	if(revflag)
	{
		obj->AddField(F_LVOL8,-ABS(trade->Amount));			// ���׽��
		obj->AddField(F_LVOL1,-ABS(trade->AdditionalMoney)); // �����
		obj->AddField(F_LVOL10,trade->Balance);				// �뿨ֵ
	}
	else
	{
		obj->AddField(F_LVOL8,ABS(trade->Amount));	//���׽��
		obj->AddField(F_LVOL1,ABS(trade->AdditionalMoney)); // �����
		obj->AddField(F_LVOL10,trade->Balance - ABS(trade->Amount)); // ����ֵ

	}
	obj->AddField(F_LVOL7,trade->TraceOfEW); // Ǯ��ˮ�ź�
	char dt_buf[12] = {0};
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade->Year,trade->Month,trade->Day);
	obj->AddField(F_SPOST_CODE,dt_buf);
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade->Hour,trade->Minute,trade->Second);
	obj->AddField(F_SPOST_CODE2,dt_buf);
	if(crc_err)
	{
		// ���CRCУ��ʧ��,����ļ�¼��־Ϊʧ��
		transmark = E_999_FAILED;
	}
	obj->AddField(F_LVOL11,trade->ConsumeMode);		//����ģʽ
	obj->AddField(F_LVOL12,transmark);

	if(obj->Connect())
	{
		// ����ʧ��
		ACE_DEBUG((LM_ERROR,"ʵʱ������ˮ:����DRTPʧ��,�豸���к�[%s]�豸��ˮ��[%d]DRTP������[%d][%s]",devphyid,trade->TraceOfPOS,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	// ������ˮ
	ACE_DEBUG((LM_TRACE,"ʵʱ������ˮ���͵�DRTP,�豸���к�[%s]�豸��ˮ��[%d]",devphyid,trade->TraceOfPOS));
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"ʵʱ������ˮ����ʧ��,�豸���к�[%s]�豸��ˮ��[%d]DRTP������[%d][%s]",devphyid,trade->TraceOfPOS,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	int ret = obj->GetReturnCode();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"ʵʱ��ˮ����ʧ��,�豸���к�[%s]�豸��ˮ��[%d]������[%d][%s]",devphyid,trade->TraceOfPOS,ret,obj->GetReturnMsg().c_str()));
		return ret;
	}
	ACE_DEBUG((LM_TRACE,"ʵʱ������ˮ����ɹ�,�豸���к�[%s]�豸��ˮ��[%d]",devphyid,trade->TraceOfPOS));
	return 0;
}
//���油�ɵ�POS��ˮ
int HDRecordFileReader::SavePosRecord(BYTE* buf)
{
	TRADERECORDSTRUCT trade;
	int crc_err = 0;
	memset(&trade,0,sizeof trade);
	if(HDParsePosRecord(buf,&trade))
	{
		// CRC ����Ҫɾ��
		// ��ɾ��,����Ҫ�ϴ�
		//return 0;
		if(!bColHisSeri)	//�ɼ���ʷ��ˮ����У��
		{
			ACE_DEBUG((LM_ERROR,"POS��ˮ��¼У�����"));
			crc_err = 1;
		}
	}
	return SaveTradeRecord(&trade,POSDATATYPE_COLLPOS,crc_err);
}

HDRecordFileReader_Lock_Guard::HDRecordFileReader_Lock_Guard(int devid)
	:_devid(devid),_is_owner(0)
{	
	ACE_DEBUG((LM_TRACE,"����CCU dev[%d]",_devid));
	if(!HDRecordFileReader::lock_ccu(_devid))
		_is_owner = 1;
}
HDRecordFileReader_Lock_Guard::~HDRecordFileReader_Lock_Guard()
{
	if(_is_owner == 1)
	{
		if(HDRecordFileReader::free_ccu_lock(_devid))
		{
			ACE_DEBUG((LM_ERROR,"�ͷ�CCU�ļ���ʧ��,dev[%d]",_devid));
		}
	}
	_is_owner = 0;
}
int HDRecordFileReader_Lock_Guard::is_owner()
{
	return (_is_owner == 1);
}
///////////////////////////////////////////////////////////////////////////////
// CCU ����֪ͨ
HD_REGISTER_HANDLER(MT_CCUONLINENOTICE1,HDCCUNoticeHandler);
int HDCCUNoticeHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int recordcnt = 0;
	size_t packlen;
	std::string filepath;
	char data[128] = "";
	int ret;
	char phyid[15] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"CCU [%s] ������!",phyid));
		return -1;
	}
	if(node->GetDeviceType() != KSG_HD_SERVER_DEV
		&& node->GetDeviceType() != KSG_HD_KQ_CCU)
	{
		ACE_DEBUG((LM_ERROR,"�յ��豸[%s]����֪ͨ�����Ǹ��豸����CCU��",phyid));
		return -1;
	}
	// ��¼�豸״̬��Ϣ
	node->SetState(KSGDeviceNode::dsOnline);
	node->update_time();

	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	
	MYDATETIMESTRUCT now = HDDEV::HDGetDataTime();
	resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,sizeof now);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	unsigned char buf[(FILEID_ARECORD2+1)* RECORD_SECT_LEN];
	ACE_OS::memset(buf,0x00,sizeof buf);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,(char*)buf,sizeof buf);
	packlen = PackRequestStruct(resp,MT_CCUONLINENOTICE1,data,sizeof data);
	if(HDSendBuffer(peer,data,packlen,&tv))
	{
		ACE_DEBUG((LM_ERROR,"����Ӧ��ʧ��"));
	}
	/*
	// ����Ӧ��
	filepath = HDA_FILENAME_PRECORD1;
	ret = DoFile(FILEID_PRECORD1,req->AdditionalData2+FILEID_PRECORD1*RECORD_SECT_LEN
		,node,req,filepath);

	if(!ret)
	{
		//�ɹ�
		ACE_DEBUG((LM_INFO,"����CCU[%s]��ˮ��¼�ļ�1�ɹ�",phyid));
	}
	filepath = HDA_FILENAME_PRECORD2;
	ret = DoFile(FILEID_PRECORD2,req->AdditionalData2+FILEID_PRECORD2*RECORD_SECT_LEN
		,node,req,filepath);

	if(!ret)
	{
		// �ɹ�
		ACE_DEBUG((LM_INFO,"����CCU[%s]��ˮ��¼�ļ�2�ɹ�",phyid));
	}
	*/
	
	filepath = HDA_FILENAME_ARECORD1;
	ret = DoFile(FILEID_ARECORD1,req->AdditionalData2+FILEID_ARECORD1*RECORD_SECT_LEN
		,node,req,filepath);
	if(!ret)
	{
		// �ɹ�
		ACE_DEBUG((LM_INFO,"����CCU[%s]���ڼ�¼�ļ�1�ɹ�",phyid));
	}
	filepath = HDA_FILENAME_ARECORD2;
	ret = DoFile(FILEID_ARECORD2,req->AdditionalData2+FILEID_ARECORD2*RECORD_SECT_LEN
		,node,req,filepath);
	if(!ret)
	{
		// �ɹ�
		ACE_DEBUG((LM_INFO,"����CCU[%s]���ڼ�¼�ļ�1�ɹ�",phyid));
	}

	return 0;
}

int HDCCUNoticeHandler::DoFile(int fileid,BYTE* filebuf
							   ,KSGDeviceNode* node,HD8583STRUCT& req
							   ,std::string& filepath)
{
	int ret;
	HDRecordFileReader::HD_RECORD_TYPE record_type;
	char devid[12] = "";
	char data[128] = "";
	bool need_free = false;
	HD8583STRUCT resp;
	int packlen;
	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();

	ACE_OS::sprintf(devid,"%.010d",req->TerminalSN);

	/*
	1. CCU ����֪ͨ����
	2. ���������¼�ļ�
	3. ������ش��ڼ�¼�ļ�,���²ɼ����
	4. ���CCU���м�¼�ļ���Ҫ�ɼ�,FTP���غ�ɼ����
	*/
	
	switch(fileid)
	{
	case FILEID_PRECORD1:
	case FILEID_PRECORD2:
		record_type = HDRecordFileReader::POS_RECORD;
		break;
	case FILEID_ARECORD1:
	case FILEID_ARECORD2:
		record_type = HDRecordFileReader::ATTENDENT_RECORD;
		break;
	default:
		ACE_DEBUG((LM_ERROR,"��֧�ֵ�CCU�ļ�¼����,ccu[%s]fileid[%d]",devid,fileid));
		return -1;
	}
	/*
	if(node->GetDeviceType() == KSG_HD_SERVER_DEV)
	{
		record_type = HDRecordFileReader::POS_RECORD;
	}
	else
	{
		record_type = HDRecordFileReader::ATTENDENT_RECORD;
	}
	*/
	ret = CheckFile(fileid,filebuf,devid,filepath);
	
	if(ret == 0)
	{
		ACE_DEBUG((LM_DEBUG,"���CCU�ϼ�¼�ļ�"));
		resp.Init();
		resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
		char tmp[3] = "";
		tmp[0] = fileid;
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,tmp,1);
		packlen = (size_t)PackRequestStruct(resp,MT_CLEARFILE2,data,sizeof data,true);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		MESSAGETYPE msg_type;
		ret = node->GetDevice()->find_handler(node,&handler);
		if(ret != 0)
		{
			ACE_DEBUG((LM_ERROR,"����CCUʧ��dev[%s]",devid));
		}
		else if(HDSendBuffer(handler,data,packlen,&tv))
		{
			need_free = true;
			ACE_DEBUG((LM_ERROR,"����ɾ����¼��ָ��ʧ��,dev[%s]",devid));
		}
		else
		{
			KSGThreadUtil::Sleep(100);
			if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
			{
				need_free = true;
				ACE_DEBUG((LM_ERROR,"���CCU��¼�ļ�ʧ��,dev[%s]",devid));
			}
			else if(UnPackResponseStruct(resp,&msg_type,data,packlen))
			{
				ACE_DEBUG((LM_ERROR,"���CCU��¼�ļ�����Ӧ��ʧ��"));
			}
			else if(resp->ResponseCode != RC_SUCCESS)
				//&& resp->ResponseCode != 28 // ��¼�ļ�ԭ�����ǿյ�
				//|| resp->TerminalSN != req->TerminalSN)
			{
				ACE_DEBUG((LM_ERROR,"ɾ��CCU[%s]��¼�ļ�ʧ��[%x]������[%d]"
					,devid,fileid,resp->ResponseCode));
				// add 2007-8-31 , ������ CCU ��¼�ļ�ʧ�ܣ���Ҫ���¶Ͽ�����
				need_free = true;
				// FIXME : �Ƿ�Ҫɾ����¼�ļ���
				// XXX: ��ɾ��,���Բɼ�
			}
			else
			{
				ACE_DEBUG((LM_NOTICE,"��� CCU ��¼�ļ��ɹ�!dev[%s]",devid));
			}
		}
		if(handler != ACE_INVALID_HANDLE)
			node->GetDevice()->release_handler(node,&handler,need_free);
		//if(retries <= 0)
		//{
		//	ACE_DEBUG((LM_ERROR,"����CCUʧ��"));
		//	// XXX: ����Ҫ�������.
		//	//return -1;
		//}
		// ������ˮ
		//ACE_DEBUG((LM_DEBUG,"��ʼ������ˮ"));
		// ����޷�ɾ����ˮ�ļ��������ȵ�����ˮ��
		HDRecordFileReader reader(filepath,node->GetDevId(),record_type);
		ret = reader.ReadFile();
		if(ret)
		{
			ACE_DEBUG((LM_DEBUG,"��ȡ��ˮʧ��[%d]",ret));
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"������ˮ���"));
		}
	}
	else if(ret > 0)
	{
		// �޼�¼��δ�ر�
		if(KSGOSUtil::FileExists(filepath))
		{
			ACE_DEBUG((LM_DEBUG,"������ʷ��ˮ"));
			HDRecordFileReader reader(filepath,node->GetDevId(),record_type);
			ret = reader.ReadFile();
			if(ret)
			{
				ACE_DEBUG((LM_DEBUG,"��ȡ��ˮʧ��[%d]",ret));
			}
			else
			{
				ACE_DEBUG((LM_TRACE,"������ˮ���"));
			}
		}
		else
		{
			ACE_DEBUG((LM_TRACE,"δ�ҵ����ؼ�¼�ļ�"));
		}
	}
	else
	{
		// ����
		//ACE_DEBUG((LM_ERROR,"�����ļ�ʧ��"));
	}
	return ret;

}
int HDCCUNoticeHandler::CheckDownloadPath(const std::string& devid,std::string& filepath)
{
	std::string basepath = KsgGetGateway()->GetConfig()->_basedir;
	basepath = KSGOSUtil::JoinPath(basepath,"data/");
	ACE_DIR* dir = ACE_OS::opendir(basepath.c_str());
	if(!dir)
	{
		if(ACE_OS::mkdir(basepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"����Ŀ¼ʧ��[%s]",basepath.c_str()));
			return -1;
		}
	}
	else
		ACE_OS::closedir(dir);
	basepath = KSGOSUtil::JoinPath(basepath,devid);
	dir = ACE_OS::opendir(basepath.c_str());
	if(!dir)
	{
		if(ACE_OS::mkdir(basepath.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"����Ŀ¼ʧ��[%s]",basepath.c_str()));
			return -1;
		}
	}
	else 
		ACE_OS::closedir(dir);
	filepath = KSGOSUtil::JoinPath(basepath,filepath);
	if(KSGOSUtil::FileExists(filepath))
	{
		/*
		if(ACE_OS::filesize(filepath.c_str()) <= 0)
		{
			// �ռ�¼�ļ�, ɾ��
			if(ACE_OS::unlink(filepath.c_str()))
			{
				ACE_DEBUG((LM_ERROR,"ɾ���ռ�¼�ļ�ʧ��!!!"));
				// ��ʾ�ļ��Ѵ���
				return 1;
			}
			// ����
			ACE_DEBUG((LM_DEBUG,"���ֱ��ؿռ�¼�ļ�,ɾ��֮!"));
			return 0;
		}
		*/
		// ��ʾ�ļ��Ѵ���
		return 1;
	}
	return 0;
}

int HDCCUNoticeHandler::ftp_writer(void *buffer, size_t size, size_t nmemb, void *stream)
{
	FILE * p;
	record_file *record = static_cast<record_file*>(stream);
	if(record && record->file_path)
	{
		if(!record->filp)
		{
			if((p = ACE_OS::fopen(record->file_path,"wb+")) == NULL)
				ACE_ERROR_RETURN((LM_ERROR,"д���ļ�[%s]ʧ��",record->file_path),-1);
			else
				record->filp = p;
		}
		return ACE_OS::fwrite(buffer,size,nmemb,record->filp);
	}
	if(!record->file_path)
	{
		ACE_DEBUG((LM_ERROR,"δָ���ļ�·��!"));
	}
	ACE_ERROR_RETURN((LM_ERROR,"���ô���"),-1);
}

int HDCCUNoticeHandler::ftp_curl_debug(CURL * curl, curl_infotype info, char * msg, size_t len, void * param)
{
	if(CURLINFO_TEXT == info)
	{
		if(msg && len > 0)
		{
			char tmp[512] = "";
			strncpy(tmp,msg,sizeof(tmp) - 1);
			ACE_DEBUG((LM_DEBUG,"%s",tmp));
		}
	}
	return 0;
}
int HDCCUNoticeHandler::CheckFile(int fileid,BYTE* data
								  ,const std::string& devid
								  ,std::string& filepath)
{
	int recordcnt = 0;
	int recordlen = 0;
	int ret;
	char ftp_msg[CURL_ERROR_SIZE+1] = "";
	// ������ˮ�ļ�
	std::string datafile = filepath;
	char user_pwd[256] = "";
	CURL *curl;
	CURLcode res;

	BYTE file_index = *data;
	BYTE file_flag = 0x00;
	if(file_index == fileid)
	{
		// ����¼�ļ� 1
		BUF_2_INT(recordcnt,data + 1);
		file_flag = *(data + 5);
		ACE_DEBUG((LM_TRACE,"CCU Notice idx[%d] [��¼��%d]",file_index,recordcnt));
		// �����ʱĿ¼
		ret = CheckDownloadPath(devid,filepath);
		if(ret > 0)
		{
			ACE_DEBUG((LM_TRACE,"�����ļ��Ѿ�����!"));
			// �ļ��Ѿ�����,��������ʹ����
			return ret;
		}
		else if(ret < 0)
		{
			// ����Ŀ¼ʧ��
			ACE_DEBUG((LM_ERROR,"����Ŀ¼ʧ��"));
			return ret;
		}
		if(file_flag != FILE_CLOSE)
		{
			ACE_DEBUG((LM_TRACE,"CCU����ʹ�øü�¼�ļ� ... "));
			return -1;
		}
		// û�м�¼
		if(recordcnt <= 0)
			return 1;
	}
	else
	{
		return -1;
	}
	
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(devid);
	if(node == NULL)
		return -1;
	
	// �����ļ�
	//ftp_netbuf* control;
	off_t rec_file_len = 0;
	int retries = 3;

	/*
	if(node->GetDeviceType() == KSG_HD_SERVER_DEV)
	{
		recordlen = HDRecordFileReader::RECORD_BUF_LEN;
	}
	else
	{
		recordlen = HDRecordFileReader::ARECORD_BUF_LEN;
	}
	*/
	switch(fileid)
	{
	case FILEID_PRECORD1:
	case FILEID_PRECORD2:
		recordlen = HDRecordFileReader::RECORD_BUF_LEN;
		break;
	case FILEID_ARECORD1:
	case FILEID_ARECORD2:
		recordlen = HDRecordFileReader::ARECORD_BUF_LEN;
		break;
	default:
		ACE_DEBUG((LM_ERROR,"��֧�ֵ�CCU�ļ�¼����,ccu[%s]fileid[%d]",devid.c_str(),fileid));
		return -1;
	}
	std::string ipstr = "ftp://" + node->GetDevAddr().GetConnect() + ":";
	ipstr += hd_ccu_ftp_port;
	ipstr += "/" + datafile;
	curl = NULL;
	ACE_OS::sprintf(user_pwd,"%s:%s",hd_ccu_ftp_user_name.c_str(),hd_ccu_ftp_pswd.c_str());
	record_file myfile = {filepath.c_str(),NULL};
	try
	{
		HDRecordFileReader_Lock_Guard ccu_guard(node->GetDevId());
		if(!ccu_guard.is_owner())
		{
			ACE_DEBUG((LM_INFO,"FTP�����ļ�ʱ��⵽�����ļ�����ʹ���У���dev[%d]",node->GetDevId()));
			return -1;
		}
		// �ɼ���ˮ
		do{
			ret = -1;
			ACE_DEBUG((LM_DEBUG,"��ʼ���ؼ�¼�ļ�"));
			curl = curl_easy_init();
			if(!curl)
			{
				ACE_DEBUG((LM_ERROR,"���� CURL ������Դʧ��!"));
				continue;
			}
			ACE_DEBUG((LM_DEBUG,"����CCU URL[%s]",ipstr.c_str()));
			curl_easy_setopt(curl,CURLOPT_URL,ipstr.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HDCCUNoticeHandler::ftp_writer);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &myfile);
#ifdef _DEBUG
			//curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE);
			//curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, HDCCUNoticeHandler::ftp_curl_debug);
#endif
			curl_easy_setopt(curl, CURLOPT_FTP_FILEMETHOD, CURLFTPMETHOD_NOCWD);
			curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, 0);
			curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, ftp_msg);
			// ���õ�½�û���������
			ACE_DEBUG((LM_INFO,"CCU [%s]",user_pwd));
			curl_easy_setopt(curl ,CURLOPT_USERPWD,user_pwd);
			// �������ӳ�ʱʱ��Ϊ 10 ��
			curl_easy_setopt(curl, CURLOPT_TIMEOUT,10);
			// ���� FTP ��ʱʱ��Ϊ 10 ��
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT,10);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;
			if(myfile.filp)
			{
				ACE_DEBUG((LM_DEBUG,"�ر��ļ����!"));
				ACE_OS::fclose(myfile.filp);
				myfile.filp = NULL;
			}
			if(CURLE_OK != res)
			{
				ACE_DEBUG((LM_ERROR,"����CCU[%s]��¼�ļ�[%s]ʧ��,CURL���ش���[%d][%s]"
					,node->GetPhyId().c_str(),datafile.c_str(),res,ftp_msg));
			}
			else if((rec_file_len = ACE_OS::filesize(filepath.c_str())) == 0)
			{
				// ���ص��ļ�Ϊ��,ɾ��֮
				ACE_DEBUG((LM_NOTICE,"���صļ�¼�ļ�Ϊ��,��CCU��¼�ļ���Ϊ��!"));
				if(ACE_OS::unlink(filepath.c_str()))
				{
					ACE_DEBUG((LM_ERROR,"ɾ���ռ�¼�ļ�ʧ��!"));
				}
				ret = -2;
			}
			else
			{
				// ����ļ���С������,ֻҪ�㹻����Ȳ�����.
				if(rec_file_len != recordlen * recordcnt)
				{
					ACE_DEBUG((LM_ERROR,"dev[%s]���ؼ�¼�ļ���С����������ļ���С��һ��except[%d]received[%d]"
						,node->GetPhyId().c_str(),recordcnt * recordlen,rec_file_len));
					
					// �������ؼ�¼�ļ�,ֱ���ɹ�Ϊֹ
					ACE_OS::unlink(filepath.c_str());
					// �ȴ�5 ������
					KSGThreadUtil::Sleep(5000);
				}
				else
				{
					ACE_DEBUG((LM_DEBUG,"����CCU��¼�ļ��ɹ�!"));
					ret = 0;
				}
			}
		}while(--retries > 0 && ret != 0);

		if(retries <= 0 && ret != 0)
		{
			ACE_DEBUG((LM_ERROR,"����CCU��¼�ļ�����,�ļ���С��������д�С��һ��"));
		}
	}
	catch(...)
	{
		// �����ļ�ʧ��,���� ERROR
		if(myfile.filp)
		{
			ACE_OS::fclose(myfile.filp);
			myfile.filp = NULL;
		}
		ret = -1;
	}
	//HDRecordFileReader::free_ccu_lock(node->GetDevId());
	return ret;
}
HD_REGISTER_HANDLER(MT_DEPOSIT1,HDAddNotice);
int HDAddNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int term_no,num,offset;
	short snum;
	char phyid[12] = "";
	char buffer[64]={0};
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"��ֵ����ʧ��,�豸 [%s] ������!",phyid));
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		return 1;
	}
	term_no = req->TerminalID;
	/*
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"��ֵ����ʧ��,�豸���Ų���ȷ[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// ���ش���
		return 1;
	}
	*/
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// ����ǳ�ֵ����
		obj->SetRequestHeader(950072);
		obj->AddField(F_LWITHDRAW_FLAG,node->GetDevId());
		obj->AddField(F_LSERIAL0,req->TraceOfPOS); // ��ˮ��
		obj->AddField(F_LVOL4,req->CardNumber); // ���׿���

		char dt_buf[32] = "";
		ACE_OS::sprintf(dt_buf,"20%.02d%.02d%.02d",
			req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
		obj->AddField(F_SDATE0,dt_buf);
		//ACE_DEBUG((LM_INFO,"tx date[%s]",dt_buf));
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
		obj->AddField(F_STIME0,dt_buf);
		//ACE_DEBUG((LM_INFO,"tx time[%s]",dt_buf));

		//ACE_HEX_DUMP((LM_INFO,(const char*)req->AdditionalData2,30));
		BUF_2_INT(num,req->AdditionalData2);
		offset=4;
		obj->AddField(F_LVOL7,num); // �뿨���

		BUF_2_SHORT(snum,req->AdditionalData2+offset);
		obj->AddField(F_LVOL5,snum); //��ֵ����
		offset+=2;

		offset += 2; // 
		xutil::StringUtil::Hex2Str(req->AdditionalData2+offset,4,buffer);
		buffer[8] = 0;
		obj->AddField(F_SBANK_PWD,buffer); // �����
		offset += 4;

		memset(buffer,0,sizeof buffer);
		xutil::StringUtil::Hex2Str(req->AdditionalData2+offset,4,buffer);
		obj->AddField(F_SSTOCK_CODE,buffer); //MAC1
		offset += 4;

		
		memset(buffer,0,sizeof buffer);
		xutil::StringUtil::Hex2Str(req->AdditionalData2+offset,8,buffer);
		obj->AddField(F_SNAME,buffer); // ������
		offset += 8;

		memset(buffer,0,sizeof buffer);
		xutil::StringUtil::BCD2Str(req->AdditionalData2+offset,6,buffer);
		obj->AddField(F_SSTATION0,buffer); // PSAM ���ն˺�

		offset = 0;
		BUF_2_INT(num,req->AdditionalData3+offset);
		obj->AddField(F_LVOL1,num); // ���κź�
		offset += 4;

		BUF_2_INT(num,req->AdditionalData3+offset);
		obj->AddField(F_LVOL2,num); // ��Ȩ��
		offset += 4;

		memset(buffer,0,sizeof buffer);
		memcpy(buffer,req->AdditionalData3+offset,8);
		obj->AddField(F_SEMP_NO,buffer); // ����Ա��

		obj->AddField(F_LVOL8,req->Amount); // ��ֵ���
		if(req->ManageFee == 0x01) // �����ֻ���
		{
			obj->AddField(F_LVOL5,req->TraceOfEW-1); // ��ֵ����
			obj->AddField(F_LVOL7,req->AdditionalAmount1 - req->Amount); // ��ֵ���
		}


		ACE_DEBUG((LM_DEBUG,"��ֵ����,��ˮ�����ύ����̨..."));
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_ERROR,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		if(!obj->SendRequest(2000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"��ֵ����ʧ��,�豸[%s][%d]������[%d][%s]"
					,phyid,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				resp.SetFieldValue(FIELD_RESPONSECODE,1);
			}
			else
			{
				// ���÷���ֵ
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lvol10);
					resp.SetFieldValue(FIELD_POSTRACE,data->lcert_code);
					resp.SetFieldValue(FIELD_RESPONSECODE,data->lcert_code);
					byte temp[64] = {0};
					xutil::StringUtil::Str2Hex(data->semail,temp,8);
					resp.SetFieldValue(FIELD_ADDITIONALDATA2,temp,8);
					ACE_DEBUG((LM_INFO,"��ֵmac[%s]",data->semail));
					ACE_DEBUG((LM_INFO,"��ֵ�������!!dev[%s]serialno[%d]rc[%d]",phyid,req->TraceOfPOS,
						data->lcert_code));
				}
			}
		}
		return 1;

#if 0
		obj->SetRequestHeader(849003);
		obj->AddField(F_LVOL4,req->TraceOfPOS); // ��ˮ��
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		EncodeTermSN(req->TerminalSN,sn);
		obj->AddField(F_SDATE1,sn);
		obj->AddField(F_STX_PWD,"");
		obj->AddField(F_LBANK_ACC_TYPE,19); // ͨѶ�汾�� 39 ����
		obj->AddField(F_LBANK_ACC_TYPE2,0); // ��Ŀ�շ�
		char crc[5] = "";
		xutil::StringUtil::Hex2Str(req->mac,2,crc); // CRC У��
		obj->AddField(F_SBANK_CODE2,crc);
		obj->AddField(F_LVOL6,req->IndexOfEW-1); // Ǯ����
		obj->AddField(F_LVOL5,req->CardNumber); // ���׿���
		obj->AddField(F_LVOL3,req->OperatorID); // ����Ա��
		/*
		1. ����ʱ, ���׽���� ��ֵ , ������� ��ֵ
		2. ��ֵʱ, ���׽���� ��ֵ
		3. ���ѳ���ʱ, ���׽���� ��ֵ , ������� ��ֵ
		4. ��ֵ����ʱ,���׽���� ��ֵ
		*/
		obj->AddField(F_LVOL9,req->AdditionalAmount1); //�뿨ֵ 
		obj->AddField(F_LVOL10,req->AdditionalAmount1 + req->Amount); // ����ֵ
		obj->AddField(F_LVOL8,ABS(req->Amount)); // ���׽��

		obj->AddField(F_LVOL7,req->TraceOfEW); // Ǯ��ˮ�ź�
		char dt_buf[12] = "";
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
		obj->AddField(F_SPOST_CODE,dt_buf);
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
		obj->AddField(F_SPOST_CODE2,dt_buf);
		obj->AddField(F_LVOL12,250);

		ACE_DEBUG((LM_DEBUG,"��ֵ����,��ˮ�����ύ����̨..."));
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ
		if(!obj->SendRequest(2000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"��ֵ����ʧ��,�豸[%s][%d]������[%d][%s]"
					,sn,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				// ���ݺ�̨�Ĵ�����������
				switch(obj->GetReturnCode())
				{
				case 100012:
				case 100581:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CONFIREPORTLOSSCARD);
					break;
				case 100572:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CARD_CANCEL);
					break;
				case 108110:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CARDBALANCE_EXCEED);
					break;
				case 100018:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CARD_INVALID);
					break;
				default:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_TRADE_FAILED);
					break;
				}
			}
			else
			{
				// ���÷���ֵ
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lvol10);
					resp.SetFieldValue(FIELD_POSTRACE,data->lcert_code);
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
					ACE_DEBUG((LM_INFO,"��ֵ���׳ɹ�!!dev[%s]serialno[%d]",sn,req->TraceOfPOS));
				}
			}
		}
#endif
	}
	return 1;
}

HD_REGISTER_HANDLER(MT_ROLLBACK1,HDAddCancelNotice);
int HDAddCancelNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int term_no;
	char phyid[12] = "";
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_OTHER_ERR);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"��ֵ��������ʧ��,�豸 [%s] ������!",phyid));
		return 1;
	}
	term_no = req->TerminalID;
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"��ֵ��������ʧ��,�豸���Ų���ȷ[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// ���ش���
		return 1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
#if 1
		obj->SetRequestHeader(950073);
		obj->AddField(F_LWITHDRAW_FLAG,node->GetDevId());
		obj->AddField(F_SPHONE3,phyid);
		obj->AddField(F_LSERIAL0,req->TraceOfPOS);
		obj->AddField(F_LVOL4,req->CardNumber);
		obj->AddField(F_LSERIAL1,req->OrgTransTrace);
		char dt_buf[20] = "";
		ACE_OS::sprintf(dt_buf,"20%.02d%.02d%.02d",
			req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
		obj->AddField(F_SDATE0,dt_buf);
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
		obj->AddField(F_STIME0,dt_buf);
		if(req->ManageFee == 0xDA)
		{
			obj->AddField(F_LVOL10,1);
		}
		else
		{
			obj->AddField(F_LVOL10,2);
		}

		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"��ֵ��������ʧ��,����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ

		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"��ֵ��������ʧ��,[%s][%d]������[%d][%s]"
					,phyid,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
			}
			else
			{
				ST_PACK *data;
				int rc = RC_OTHER_ERR;
				if(obj->HasMoreRecord())
				{
					data = obj->GetNextRecord();
					rc = data->lcert_code;
					resp.SetFieldValue(FIELD_RESPONSECODE,rc);
				}
				ACE_DEBUG((LM_INFO,"��ֵ�������!!dev[%s]serialno[%d]rc[%d]",phyid,req->TraceOfPOS,rc));
			}
		}
#else
		// ����ǳ�ֵ����
		obj->SetRequestHeader(849004);
		obj->AddField(F_LVOL4,req->TraceOfPOS); // ��ˮ��
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		EncodeTermSN(req->TerminalSN,sn);
		obj->AddField(F_SDATE1,sn);
		obj->AddField(F_LVOL5,req->CardNumber); // ���׿���
		obj->AddField(F_LVOL3,req->OrgTransTrace);
		char dt_buf[12] = "";
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
		obj->AddField(F_SPOST_CODE,dt_buf);
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
		obj->AddField(F_SPOST_CODE2,dt_buf);
		ACE_DEBUG((LM_DEBUG,"���ڳ���..."));
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"��ֵ��������ʧ��,����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ

		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"��ֵ��������ʧ��,[%s][%d]������[%d][%s]"
					,sn,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				// ���ݺ�̨�Ĵ�����������
				switch(obj->GetReturnCode())
				{
				case 100012:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CONFIREPORTLOSSCARD);
					break;
				case 100572:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CARD_CANCEL);
					break;
				case 108110:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CARDBALANCE_EXCEED);
					break;
				case 100018:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CARD_INVALID);
					break;
				default:
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_TRADE_FAILED);
					break;
				}
			}
			else
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				ACE_DEBUG((LM_INFO,"��ֵ�������׳ɹ�!!dev[%s]serialno[%d]",sn,req->TraceOfPOS));
			}
		}
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
#endif
	}
	return 1;
}

HD_REGISTER_HANDLER(MT_ALLOWANCE1,HDCheckSubsidyNotice);
int HDCheckSubsidyNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
//	int ret;
	int term_no;
	char phyid[12] = "";
	char sn[9]  = "";
	int card_bala = 0;
	unsigned short seqno = 0;
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SYSTEMDISABLED);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	resp.SetFieldValue(FIELD_CARDNUMBER,req->CardNumber);
	resp.SetFieldValue(FIELD_INDEXOFEW,req->IndexOfEW);
	resp.SetFieldValue(FIELD_POSTRACE,req->TraceOfPOS);
	resp.SetFieldValue(FIELD_TRANSAMOUNT,req->Amount);
	card_bala = req->AdditionalAmount1;
	resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,card_bala);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"���벹������ʧ��,�豸 [%s] ������!",phyid));
		return 1;
	}
	term_no = req->TerminalID;
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"���벹������ʧ��,�豸���Ų���ȷ[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// ���ش���
		return 1;
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(849006);

		obj->AddField(F_LVOL5,req->CardNumber);
		// ��ѯδ��ȡ��
		obj->AddField(F_SSTATUS1,"2");
		obj->AddField(F_LVOL1,req->IndexOfEW-1); // Ǯ����
		BUF_2_SHORT_LE(seqno,req->AdditionalData1);
		obj->AddField(F_LVOL3,seqno);
		ACE_DEBUG((LM_DEBUG,"���Ͳ�ѯ��������..."));
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"���벹������ʧ��,[%d][%d]������[%d][%s]"
					,req->CardNumber,seqno,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				return 1;
			}
			else
			{
				// ���÷���ֵ
				double money = 0;
				
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					money = data->damt0;
					seqno = static_cast<unsigned short>(data->lvol3);
					// �������
					int t = data->lvol9;
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,t);
					char buf[10] = "";

					SHORT_2_BUF_LE(seqno,buf);
					ACE_OS::memcpy(buf+2,buf,2);
					// �������κ�
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,buf,sizeof(unsigned long));
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				}
				if(seqno > 0)
					ACE_DEBUG((LM_INFO,"��ѯ�������ؽ�������κ�[%d][%.2f]",seqno,money));
				else
					ACE_DEBUG((LM_ERROR,"��ѯ�����������κ�"));
			}
		}
	}
	return 1;
}

static int HD_POS_Consume_Response(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	TRADERECORDSTRUCT trade;
	ACE_OS::memset(&trade,0,sizeof trade);
	char phyno[21] = {0};
	ACE_OS::sprintf(phyno,"%.010d",req->TerminalSN);
	ACE_DEBUG((LM_DEBUG,"ʵʱ������ˮ:�豸���к�[%s]�豸��ˮ��[%d]",phyno,req->TraceOfPOS));
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	resp.SetFieldValue(FIELD_TRANSAMOUNT,req->Amount);
	KSGDeviceNode *node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyno);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"����POS��δע��,phyid[%s]",phyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_HD_POS_DEV
		&& node->GetDeviceType() != KSG_HD_PENSTOCK)
	{
		ACE_DEBUG((LM_ERROR,"POS[%s]�������ѻ�!",phyno));
		return 1;
	}
	//
	trade.TerminalSN = req->TerminalSN;
	// ����
	trade.CardNumber = req->CardNumber;
	// Ǯ����
	trade.IndexOfEW = req->IndexOfEW-1;
	// Ǯ����ˮ��
	trade.TraceOfEW = req->TraceOfEW;
	// ���׽��
	trade.Amount = req->Amount;
	// �����
	trade.Balance = req->AdditionalAmount1;
	// POS ��ˮ��
	trade.TraceOfPOS = req->TraceOfPOS;
	// ����ʱ��
	trade.Year = req->DateTime.Year;
	trade.Month = req->DateTime.Month;
	trade.Day = req->DateTime.Day;
	trade.Hour = req->DateTime.Hour;
	trade.Minute = req->DateTime.Minute;
	trade.Second = req->DateTime.Second;
	// ����ģʽ
	trade.ConsumeMode = req->AdditionalData1[1];
	// ��¼����
	trade.RecordType = req->AdditionalData1[0];
	unsigned short shopid=0;
	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	trade.OperatorID =shopid;
	//�����
	trade.AdditionalMoney = req->ManageFee;
	// �̻���
	//BUF_2_SHORT_LE(trade.shop_id,req->AdditionalData1+4);
	// �ʹκ�
	//trade.dinner_id = req->AdditionalData1[6];
	// MAC У����
	ACE_OS::memcpy(trade.MAC,req->mac,2);
	HDRecordFileReader reader("",0);
	// ������ˮ
	int ret=reader.SaveTradeRecord(&trade,POSDATATYPE_POSREALTIME);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"����ʵʱ������ˮʧ��,ret[%d]�豸���к�[%s]�豸��ˮ��[%d]",ret,phyno,trade.TraceOfPOS));
		return 1;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,req->AdditionalData2,4);//����ָ��
	return 1; 
}

//! ʵʱ����
HD_REGISTER_HANDLER(MT_TRADE1,HDPOS_Consume);
int HDPOS_Consume::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	this->set_resp_need_mac();
	return HD_POS_Consume_Response(req,resp,peer);
}
//! TCP POS �����ѳ���
HD_REGISTER_HANDLER(MT_CANCELTRADE1,HDPOS_Consume_Cancel);
int HDPOS_Consume_Cancel::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	this->set_resp_need_mac();
	return HD_POS_Consume_Response(req,resp,peer);
}
//CPU�������������͵����ѻ���ˮ
int HDPOS_Consume_Upload::SaveRecord(char *buf,char *phyid,char *termno)
{
	int cardid = 0;
	int in_bala = 0;
	int trade_fee = 0;
	int trade_cnt = 0;
	int pos_seri = 0;
	int mend_amount = 0;
	int oper_cardid = 0;
	int manage_fee = 0;
	int shopid = 0;
	
	int purse_id = 0;
	unsigned long transmark = 0;
	int revflag=0;
	int trade_mode = 0;
	int onlineflag=0;
	char date[9] = {0};
	char time[7] = {0};
	char tac[20] = {0};

	MYDATETIMESTRUCT DateTime;
	BUF_2_INT_LE(cardid,buf);
	BUF_2_INT_LE(in_bala,buf+4);
	BUF_2_INT_LE(trade_fee,buf+8);
	
	ACE_OS::memcpy(&DateTime,buf+12,6);
	sprintf(date,"%02d%02d%02d",DateTime.Year,DateTime.Month,DateTime.Day);
	sprintf(time,"%02d%02d%02d",DateTime.Hour,DateTime.Minute,DateTime.Second);

	BUF_2_SHORT_LE(trade_cnt,buf+18);
	BUF_2_INT_LE(pos_seri,buf+20);
	ACE_DEBUG((LM_DEBUG,"������������ˮ:�豸���к�[%s]�豸��ˮ��[%d]",phyid,pos_seri));
	BUF_2_INT_LE(mend_amount,buf+24);
	BUF_2_INT_LE(oper_cardid,buf+28);
	BUF_2_SHORT_LE(manage_fee,buf+36);
	

	BUF_2_SHORT_LE(shopid,buf+38);
	purse_id = buf[40];
	//trade_type = buf[41];
	unsigned char cRecordType=buf[41];

	for (int i=0;i<4;i++)
	{
		sprintf(tac+2*i,"%02X",buf[43+i]);
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"������������ˮKsgGetDrtpPoolʧ��,�豸���к�[%s]�豸��ˮ��[%d]",phyid,pos_seri));
		return 1;
	}
	/*
	switch(cRecordType)
	{
	case RT_HD_ONLINE_CONSUME:
		transmark = 153;//0x99
		break;
	case RT_HD_ONLINE_RUSH:
		revflag=1;
		transmark = 254;//0xFE
		break;
	case RT_HD_OFFLINE_LOCKCARD:
		transmark=5;
		break;
	case RT_HD_ONLINE_CANCEL:
		revflag=1;
		transmark=cRecordType;
		break;
	default:
		transmark=cRecordType;
		break;
	}
	*/
	transmark = cRecordType;
	if(cRecordType == 2)
	{
		transmark = 5;
	}

	if(purse_id==1)					// ��Ǯ������
	{
		obj->SetRequestHeader(950056);
		obj->AddField(F_LVOL0,cRecordType);					//���ױ�־
		obj->AddField(F_LVOL2,0);							//������ˮ��־1����0�ѻ�
		obj->AddField(F_LSERIAL0,revflag);					//������־
		obj->AddField(F_LSERIAL1,POSDATATYPE_POSAUTOSEND);	//��������,ʵʱ�ѻ���ˮ		
		
		obj->AddField(F_LSAFE_LEVEL,mend_amount);			//��д���
		//obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_SSTATION0,termno);					//�ն˻����
		obj->AddField(F_SSTATUS2,1);						//��������
		obj->AddField(F_SSTATUS3,0);						//��ˮ��Դ
		obj->AddField(F_SSTATUS4,0);						//��ʾ��Ϣ��
		obj->AddField(F_SCUST_NO,tac);						//������֤��
		obj->AddField(F_LVOL3,shopid);						//�̻���
	}
	else							// СǮ����������ӡ��ˮ��...
	{
		obj->SetRequestHeader(930031);
		if(transmark==209)				// ����ѻ�СǮ������ֻ���������ͣ�209(�ɹ�),241(�Ҽ�¼)
			transmark=153;				// ����������ˮ
		else
			transmark=255;				// ˮ����;�ο���ˮ
	}
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_LVOL5,cardid);						//���׿���	//
	obj->AddField(F_LVOL6,purse_id);
	obj->AddField(F_LVOL7,trade_cnt);					//���״���
	obj->AddField(F_LVOL9,in_bala);						//�뿨ֵ
	trade_fee = ABS(trade_fee) + ABS(manage_fee);
	if(revflag)
	{
		//����
		obj->AddField(F_LVOL10,in_bala);		// ����ֵ
		obj->AddField(F_LVOL8,-ABS(trade_fee));				//���׽��
		obj->AddField(F_LVOL1,-ABS(manage_fee));				//������
	}
	else
	{
		obj->AddField(F_LVOL10,in_bala-ABS(trade_fee));		// ����ֵ
		obj->AddField(F_LVOL8,ABS(trade_fee));				//���׽��
		obj->AddField(F_LVOL1,ABS(manage_fee));				//������
	}
	obj->AddField(F_LVOL4,pos_seri);					//pos��ˮ��
	obj->AddField(F_SPOST_CODE,date);					//����
	obj->AddField(F_SPOST_CODE2,time);					//ʱ��
	obj->AddField(F_LVOL12,transmark);					//���ױ��
	obj->AddField(F_SPHONE3,phyid,strlen(phyid));		//�ն����к�
	ACE_DEBUG((LM_DEBUG,"������������ˮ:�豸���к�[%s]Ǯ����[%d]",phyid,purse_id));

	if(obj->Connect())
	{
		// ����ʧ��
		ACE_DEBUG((LM_ERROR,"������������ˮ����DRTPʧ��,�豸���к�[%s]�豸��ˮ��[%d]DRTP������[%d][%s]",phyid,pos_seri,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	// ������ˮ
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"������������ˮ���͵�DRTPʧ��,�豸���к�[%s]�豸��ˮ��[%d]DRTP������[%d][%s]",phyid,pos_seri,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	int ret = obj->GetReturnCode();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"������������ˮ����ʧ��,�豸���к�[%s]�豸��ˮ��[%d]������[%d][%s]",phyid,pos_seri,ret,obj->GetReturnMsg().c_str()));
		return ret;
	}
	return 0;
}
// CPU����POS���ѻ���¼������
HD_REGISTER_HANDLER(MT_BATCHSENDRECORD1,HDPOS_Consume_Upload);
int HDPOS_Consume_Upload::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret,count;
	short offset=0;
	int devtype = 0;
	const int recordlen = 47;
	char term_no[17]={0};

	//short shopid = 0;
	char phyid[20] = {0};
	char date[7] ={0};
	char time[7] ={0};
	char record[64] = {0};
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);

	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	//BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_INFO,"ǰ�û��и��豸[%s]������!",phyid));
		return 1;
	}
	
	//������ˮ��תphyid
	EncodeTermSN(req->TerminalSN,phyid);

	int cardtype = node->card_type();
	devtype = HDA_SYSTEMIDOFALL & (req->Address);

	if(node->GetDeviceType() == KSG_POS_DEV
		|| node->GetDeviceType() == KSG_HD_PENSTOCK)						// ����pos��, ˮ����
	{	
		short datalen = req->LenOfAdditionalData1;
		for(offset = 0,count=0;offset < datalen;offset+=recordlen)
		{
			if(offset + recordlen > datalen)
				break;
			ACE_OS::memcpy(record,req->AdditionalData1 + offset,recordlen);
			ret = SaveRecord(record,phyid,term_no);
			if(ret)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,2);
				ACE_DEBUG((LM_ERROR,"�����͵�%d����¼ʧ��!!�豸���к�[%s],������[%d]",count+1,phyid,ret));
				return 1;
			}
			/*	������ӡ���͵���ˮ���Ϊ470���ֽڣ�10��
			count++;
			if(count>7)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,2);
				ACE_DEBUG((LM_ERROR,"�����ͼ�¼����[%d]����,�豸���к�[%s]",datalen,phyid));
				return 1;
			}
			*/
		}

		ACE_DEBUG((LM_DEBUG,"��������ˮ�ɹ�,���ݳ���[%d]�豸���к�[%s]��¼����[%d]��",datalen,phyid,count));
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,req->AdditionalData2,4);//��ָ��
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	}
	else if(node->GetDeviceType() == KSG_JSB_DEV)				// ���ڻ�
	{
		unsigned char serial_buf[100] = {0};
		int datalen = req->LenOfAdditionalData1;
		HDRecordFileReader reader("",0);	
		for(offset = 0,count=0;offset < datalen;
			offset+=HDRecordFileReader::ARECORD_BUF_LEN)
		{
			if(offset + HDRecordFileReader::ARECORD_BUF_LEN > datalen)
				break;
			ACE_OS::memcpy(serial_buf,req->AdditionalData1 + offset,HDRecordFileReader::ARECORD_BUF_LEN);
			if(reader.SaveAttendBuffer(serial_buf,cardtype))
			{
				// ������ˮʧ��
				ACE_DEBUG((LM_ERROR,"���濼�ڻ������͵���ˮʧ�ܣ�phyno[%s]",phyid));
				return 1;
			}
			count++;
		}

		if(offset >= req->LenOfAdditionalData1)
		{
			ACE_DEBUG((LM_TRACE,"�����豸�����͵���ˮ�ɹ���[%d]",count));
			resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
			ret = TASK_SUCCESS;
		}
	}
	else
	{
		ACE_DEBUG((LM_ERROR,"�������ֵPOS��ˮ���ԣ��豸����ID[%s]�豸����[%s]����",
			phyid,node->GetDeviceType().c_str()));
		resp.SetFieldValue(FIELD_RESPONSECODE,0);

	}
	return 1;
}

HD_REGISTER_HANDLER(MT_SENDATTENDEVENT1,HDKQRequestHandler);
int HDKQRequestHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	unsigned char serial_buf[100] = "";
//	int offset,ret,count;
	this->set_resp_need_mac();
	char phyno[15] = "";
	char card_phyno[9] = "";
	ACE_OS::sprintf(phyno,"%.010d",req->TerminalSN);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_TERMINALSTATEERROR);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	KSGDeviceNode *node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyno);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"���ڻ�δע��,phyid[%s]",phyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_JSB_DEV)
	{
		ACE_DEBUG((LM_ERROR,"POS[%s]���ǿ���!",phyno));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID)
	{
		ACE_DEBUG((LM_ERROR,"���ڻ����Ų���ȷ,�ϴ�����[%d]",req->TerminalID));
		return 1;
	}
	// �ϴ�������ˮ

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(950101);
		//�豸 ID ��
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_LVOL0,node->GetDevId());
		KsgCardPhyNo_dec2hex(req->CardNumber,card_phyno);
		obj->AddField(F_SDATE1,card_phyno);
		int reader_id = req->AdditionalData1[0];
		obj->AddField(F_LVOL1,reader_id);
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"��������ʧ��,[%s]������[%d][%s]"
					,phyno,obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
				if(obj->GetReturnCode() == 100018)
				{
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_CONFIREPORTLOSSCARD);
				}
				return 1;
			}
			else
			{
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					if(data->lvol1 == 0xFF)
					{
						resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
					}
					else
					{
						resp.SetFieldValue(FIELD_RESPONSECODE,RC_INVALIDCARDNO);
					}
				}
			}
		}
	}
	
	return 1;
}

//! HDPOS_Check_Blackcard
HD_REGISTER_HANDLER(MT_UPDATELIST1,HDPOS_Check_Blackcard);
int HDPOS_Check_Blackcard::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	// POS ������º�����
//	int ret;
	KSGDeviceNode *node;
	char devphyno[11] = "";
	int count;
	unsigned char blk_buf[510];
	char max_vol[13] = "";
	static const int blk_card_cnt = 20;
	static const int card_len = 5;
	this->set_resp_need_mac(true);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_INVALIDTERMINAL);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	// �������ĺϷ���
	//EncodeTermSN(req->TerminalSN,devphyno);
	ACE_OS::sprintf(devphyno,"%.010d",req->TerminalSN);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(devphyno);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"���º���������ʱ�豸������[%s]",devphyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_HD_POS_DEV)
	{
		ACE_DEBUG((LM_ERROR,"���º���������ʱ�豸[%s]�������ѻ�",devphyno));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID
		|| node->GetConnType() != KSGDeviceURL::dctModem)
	{
		ACE_DEBUG((LM_ERROR,"���º���������ʱ�豸[%s]���Ų���ȷ,�����ӷ�ʽ����!"
			,devphyno));
		return 1;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_TRADE_FAILED);
	
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		return 1;
	}
	if(obj->Connect())
	{
		// ����ʧ��
		ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
		return 1;
	}
	// ���������
	// ���µ�ǰ���豸�������汾
	DecodeVersionNum(req->VerOfList,max_vol);
	
	obj->SetRequestHeader(950010);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
	obj->AddField(F_LVOL1,blk_card_cnt);
	obj->AddField(F_LVOL5,node->GetDevId());
	obj->AddField(F_SCUST_LIMIT,max_vol);
	if(obj->SendRequest(5000))
	{
		// ����ָ��ʧ��
		ACE_DEBUG((LM_DEBUG,"����ָ�ʱ�ȴ�����!"));
		return -1;
	}
	if(obj->GetReturnCode())
	{
		ACE_DEBUG((LM_ERROR,"���غ�����ʧ�ܣ�����[%d][%s]",
			obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
		return -1;
	}
	count = 0;
	ACE_OS::memset(blk_buf,0,sizeof blk_buf);
	ACE_OS::memset(max_vol,0,sizeof max_vol);
	while(obj->HasMoreRecord() && count < blk_card_cnt)
	{
		ST_PACK * data = obj->GetNextRecord();
		// ����ָ��
		int flag = data->lvol3;
		int devid = data->lvol5;
		int cardid = data->lvol2;
		char curr_vol[13] = "";
		ACE_OS::strcpy(curr_vol,data->sname);
		if(ACE_OS::strncmp(curr_vol,max_vol,12)>0)
		{
			ACE_OS::strcpy(max_vol,curr_vol);
		}
		// ��ɾ��־
		flag = (flag == 0) ? ADD_BLK_LIST : DEL_BLK_LIST;
		unsigned char buf[10] = "";
		INT_2_BUF_LE(cardid,buf);
		blk_buf[count*card_len] = flag;
		ACE_OS::memcpy(blk_buf + count*card_len+1 ,buf,4);
		//ACE_OS::sprintf(blk_buf+count*card_len,"%02X%02X%02X%02X%02X",flag,buf[0],buf[1],buf[2],buf[3]);
		count++;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	resp.SetFieldValue(FIELD_ADDITIONALDATA3,"1",1);
	if(count == 0)
	{
		ACE_DEBUG((LM_DEBUG,"�豸[%s]������º�����,��̨�������汾�Ѿ�ȫ������",devphyno));
		return 1;
	}
	ACE_DEBUG((LM_DEBUG,"�豸[%s]������º�����,һ������[%d]��",devphyno,count));
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,blk_buf,count*card_len);
	unsigned long encode_ver = EncodeVersionNum(max_vol); // ѹ���汾��
	resp.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// �������汾��
	return 1;

}

// pos�����̨ǩ��(CPU��)
HD_REGISTER_HANDLER(MT_POSENROLL,HDPosEnrollHandle);
int HDPosEnrollHandle::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
	char term_no[17]={0};
	char phyid[12] = {0};
	char date[7] ={0};
	char time[7] ={0};
	char opercode[9]={0};
	char blkVersion[15]={0};
	char ctCID[13] = {0};
	byte buffer[32] = {0};
	//char workkey[9]="11111111";
	char shopid[8]={0};
	memset(ctCID,0,sizeof ctCID);
	strcpy(ctCID,"MCTSHYJT");

	// Ĭ�Ϸ���һ�����
	resp.SetFieldValue(FIELD_RESPONSECODE,2);					//�������
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	
	sprintf(date,"%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
	
	/*
	for(int i=0;i<14;i++)			// ��̨������Ϊ12λ
	{
		blkVersion[i] = req->AdditionalData1[i];
	}
	*/
	memcpy(blkVersion,req->AdditionalData1,14);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	ACE_DEBUG((LM_DEBUG,"POS��ǩ��,�豸���к�[%s]�ն˻����[%s]",phyid,term_no));

	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);				//pos��δ����
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}
	if(node->GetTermId()!=req->TerminalID)
	{
		ACE_DEBUG((LM_WARNING,"�豸�ն�[%s]������ϵͳ����,�ն˻���[%d],ϵͳ[%d]",phyid,req->TerminalID,node->GetTermId()));
	}
	if(GetDeviceAddress(node) != req->Address)
	{
		ACE_DEBUG((LM_ERROR,"�豸�ն�[%s]��ַ��ϵͳ����,�ն˵�ַ[%d],ϵͳ[%d]",phyid,req->Address,GetDeviceAddress(node)));
		resp.SetFieldValue(FIELD_RESPONSECODE,25);					//�������
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"�豸ǩ��KsgGetDrtpPool����"));
		return 1;
	}
	// �豸ǩ��
	if(node->GetDeviceType() == KSG_999_DEV_ADDPOS)	// ��ֵ��
	{
		obj->SetRequestHeader(950070);
		obj->AddField(F_SPHONE3,phyid);
		obj->AddField(F_LWITHDRAW_FLAG,node->GetDevId());
		obj->AddField(F_SSTATION0,"");
		obj->AddField(F_LVOL0,req->CardNumber);
		obj->AddField(F_SEMP_NO,"");
		INT_2_BUF(req->ManageFee,buffer);
		char pwd[8] = "";
		xutil::StringUtil::BCD2Str(buffer,3,pwd);
		obj->AddField(F_STX_PWD,pwd);
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_ERROR,"����DRTPʧ��,�豸���к�[%s]DRTP������[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		// ������ˮ
		if(obj->SendRequest(1000))
		{
			ACE_DEBUG((LM_ERROR,"����ǩ������ʧ��,�豸���к�[%s]DRTP������[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		ret = obj->GetReturnCode();
		if(ret)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,1);
			ACE_DEBUG((LM_ERROR,"ǩ��ʧ��!�豸���к�[%s],��̨���ش�����[%d]",phyid,ret));
			return 1;
		}
		if(!obj->HasMoreRecord())
		{
			ACE_DEBUG((LM_ERROR,"ǩ��ʧ��!,��̨�����ݷ���"));
			return 1;
		}
		ST_PACK *data = obj->GetNextRecord();
		if(data->lcert_code != 0)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,data->lcert_code);
			return 1;
		}
		
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
		resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion,14);
		
		int offset = 0;
		xutil::StringUtil::Str2Hex((char*)KsgGetGateway()->GetConfig()->_workKey,buffer,8);
		offset+=8;
		// user code
		xutil::StringUtil::Str2BCD(data->sholder_ac_no,12,buffer+offset);
		offset += 6;
		// ID
		buffer[offset++] = (byte)data->lvol5;
		// AID
		memcpy(buffer+offset,ctCID,12);
		offset += 12;
		
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,buffer,offset);

		///////////////////
		offset = 0;
		INT_2_BUF(data->lvol1,buffer+offset);
		offset += 4;
		INT_2_BUF(data->lvol2,buffer+offset);
		offset += 4;
		memcpy(buffer+offset,data->semp_no,8);
		offset += 8;
		resp.SetFieldValue(FIELD_ADDITIONALDATA3,buffer,offset);

		memset(buffer,0xFF,sizeof buffer);
		resp.SetFieldValue(FIELD_ADDITIONALDATA4,buffer,4);

		ACE_DEBUG((LM_INFO,"��ֵ�ն�ǩ���ɹ�!���к�[%s]����Ա[%s]���κ�[%d]",phyid,data->semp_no,data->lvol1));

	}
	else
	{  // ���ѻ�
		obj->SetRequestHeader(950050);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SPHONE3,phyid);					//�ն����к�
		obj->AddField(F_SPOST_CODE,date);				//����
		obj->AddField(F_SPOST_CODE2,time);				//ʱ��
		//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_LVOL5,req->OperatorID);			//����Ա����
		obj->AddField(F_SSTATION0,term_no);				//�ն˻����
		obj->AddField(F_SNAME,blkVersion+2);			//������
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_ERROR,"����DRTPʧ��,�豸���к�[%s]DRTP������[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		// ������ˮ
		if(obj->SendRequest(1000))
		{
			ACE_DEBUG((LM_ERROR,"����ǩ������ʧ��,�豸���к�[%s]DRTP������[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		ret = obj->GetReturnCode();
		if(ret)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,ret);
			ACE_DEBUG((LM_ERROR,"ǩ��ʧ��!�豸���к�[%s],��̨���ش�����[%d]",phyid,ret));
			return 1;
		}
		if(!obj->HasMoreRecord())
		{
			ACE_DEBUG((LM_ERROR,"ǩ��ʧ��!,��̨�����ݷ���"));
			return 1;
		}
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
		ST_PACK *data = obj->GetNextRecord();
		unsigned char ucPosVersion[7]={0};
		int offset=0;
		ucPosVersion[offset]=data->lvol0;								//�豸����ģʽ0����1�ѻ�ģʽ
		offset++;
		short nYear=0;
		short nMonth=0;
		short nDay=0;
		short nHour=0;
		char szYear[5]={0};
		char szMonth[3]={0};
		char szDay[3]={0};
		char szHour[3]={0};
		memcpy(szYear,data->sdate0,4);
		memcpy(szMonth,data->sdate0+4,2);
		memcpy(szDay,data->sdate0+6,2);
		memcpy(szHour,data->stime0,2);
		nYear=atoi(szYear);
		nMonth=atoi(szMonth);
		nDay=atoi(szDay);
		nHour=atoi(szHour);
		SHORT_2_BUF_LE(nYear,ucPosVersion+offset);
		offset+=2;
		ucPosVersion[offset]=nMonth;
		offset++;
		ucPosVersion[offset]=nDay;
		offset++;
		ucPosVersion[offset]=nHour;					
		ACE_HEX_DUMP((LM_TRACE,(const char*)ucPosVersion,6));
		resp.SetFieldValue(FIELD_ADDITIONALDATA3,ucPosVersion,6);	//�豸����ģʽ
		SHORT_2_BUF_LE(data->lvol3,shopid);
		resp.SetFieldValue(FIELD_ADDITIONALDATA4,shopid,2);			//�̻���
		if(node->GetDeviceType() == KSG_999_DEV_JSB)				// ��ֵ��
			resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion);
		else
		{
			sprintf(blkVersion,"20%s",data->sname);				//תΪ14λ
			resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion);
		}
		unsigned char uWorkKey[9]={0};
		//memset(uWorkKey,0xFF,8);
		xutil::StringUtil::Str2Hex((char*)KsgGetGateway()->GetConfig()->_workKey,uWorkKey,8);
		//resp.SetFieldValue(FIELD_ADDITIONALDATA2,uWorkKey,8);
		offset=8;
		unsigned char buf[256];
		memcpy(buf,uWorkKey,offset);
		int len;
		len = strlen(data->scust_limit);
		xutil::StringUtil::Str2BCD(data->scust_limit,len,buf+offset);
		len /= 2;
		offset += len;
		buf[offset]=atoi(data->scust_limit2);
		offset++;
		
		memcpy(buf+offset,ctCID,12);
		offset+=12;
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,offset);
		ACE_DEBUG((LM_INFO,"�����ն�ǩ���ɹ�!�豸���к�[%s]�������汾[%s]�̻���[%d]",phyid,blkVersion,data->lvol3));
	}
	
	return 1;
}

// ��������/�������ѳ���
HD_REGISTER_HANDLER(MT_ONLINE_CONSUME,HDOnlineConsumeHandler);
int HDOnlineConsumeHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
	int i = 0;
	char term_no[17]={0};
	int onlineflag=0;	//������־
	int revflag=0;		//������־
	int transtype=0;	//��������
	int tradefee = 0; // ���׽��
	int shopid = 0;
	char phyid[12] = {0};
	char date[7] ={0};
	char time[7] ={0};	
	char tradetype[2]={0};
	char blkVersion[15]={0};
	char addData[8]={0};
	ACE_DEBUG((LM_DEBUG,"�������ѿ�ʼ"));
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_CARDNUMBER,req->CardNumber);
	resp.SetFieldValue(FIELD_TRANSAMOUNT,req->Amount);
	resp.SetFieldValue(FIELD_RESERVEFIELD,req->ManageFee);
//	SYSTEMTIME st; //������ʱ��Ľṹ��
//	GetSystemTime(&st);
//	ACE_DEBUG((LM_DEBUG,"�������ѿ�ʼ1:%02d%02d%02d%03d",st.wHour+8,st.wMinute,st.wSecond,st.wMilliseconds));

	sprintf(date,"%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);

	unsigned long transmark=0;	//���ױ��
	onlineflag = req->AdditionalData1[0] ;
	unsigned char cRecordType  = req->AdditionalData1[1];
	transtype=req->AdditionalData1[2];
	//ACE_DEBUG((LM_DEBUG,"�������ѱ�־[%d]",onlineflag));
	//tradetype[0] = req->AdditionalData1[2] + 0x30;
	for(i=0;i<14;i++)
	{
		//sprintf(blkVersion+i,"%c",req->AdditionalData1[3+i]);		//�ȽϺ�ʱ
		blkVersion[i] = req->AdditionalData1[3+i];
	}
	ACE_DEBUG((LM_DEBUG,"��������,������[%s]",blkVersion));
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);

	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	ACE_DEBUG((LM_DEBUG,"�������ѣ��ն˻����[%s]",term_no));

	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}
	node->update_time();
	
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"ȡdrtp���ӳ�ʧ��!"));
		return 1;
	}
	if(RT_HD_ONLINE_CONSUME == cRecordType)
		obj->SetRequestHeader(950051);
	else
		obj->SetRequestHeader(950055);

	switch(cRecordType)
	{
	case RT_HD_ONLINE_CONSUME:
		transmark = 153;//0x99
		break;
	case RT_HD_ONLINE_RUSH:
		revflag=1;
		transmark = 254;//0xFE
		break;
	case RT_HD_ONLINE_BLACK:
		transmark=5;
		break;
	case RT_HD_ONLINE_CANCEL:
		revflag=1;
		transmark=cRecordType;
		break;
	default:
		transmark=cRecordType;
		break;
	}
	obj->AddField(F_LVOL9, req->AdditionalAmount1);					//�뿨ֵ
	int nManageFee=req->ManageFee;
	ACE_DEBUG((LM_DEBUG,"amount[%d],managefee[%d]",req->Amount,nManageFee));
	tradefee = ABS(req->Amount) + ABS(nManageFee);
	if(revflag)
	{
		//������ȡ��
		obj->AddField(F_LVOL10, req->AdditionalAmount1);			// ����ֵ
		obj->AddField(F_LVOL8,-ABS(tradefee));						//���׽��
		obj->AddField(F_LVOL1,-ABS(nManageFee));						//������
	}
	else
	{
		//����
		obj->AddField(F_LVOL10,req->AdditionalAmount1 - ABS(tradefee));	// ����ֵ
		obj->AddField(F_LVOL8,ABS(tradefee));								//���׽��
		obj->AddField(F_LVOL1,ABS(nManageFee));								//������
	}
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_LSERIAL0,revflag);					//������־
	obj->AddField(F_LSERIAL1,POSDATATYPE_POSONLINE);	//��������
	obj->AddField(F_LVOL0,cRecordType);					//���ױ�־
	obj->AddField(F_LVOL2,onlineflag);					//������ˮ��־:1����0�ѻ�
	obj->AddField(F_LVOL3,shopid);						//�̻���
	obj->AddField(F_LVOL4,req->TraceOfPOS);				//POS��ˮ��
	obj->AddField(F_LVOL5,req->CardNumber);				//���׿���
	obj->AddField(F_LVOL7,req->TraceOfEW);				//���״���
	obj->AddField(F_SPHONE3,phyid);						//�ն����к�
	obj->AddField(F_LSAFE_LEVEL,req->OrgTransTrace);	//�������
	obj->AddField(F_SPOST_CODE,date);					//����
	obj->AddField(F_SPOST_CODE2,time);					//ʱ��
	//obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
	obj->AddField(F_SSTATION0,term_no);					//�ն˻����
	//ACE_DEBUG((LM_DEBUG,"�������ѣ�������[%d]",req->ManageFee));
	obj->AddField(F_LVOL12,transmark);					//���ױ�־
	//obj->AddField(F_SSTATUS2,tradetype);				//��������
	obj->AddField(F_SNAME,blkVersion+2);				//������

	if(obj->Connect())
	{
		// ����ʧ��
		ACE_DEBUG((LM_ERROR,"����DRTPʧ�ܣ�����!!!"));
		return 1;
	}
	ACE_DEBUG((LM_DEBUG,"SendRequest"));
	// ������ˮ
	if(obj->SendRequest(500))
	{
		ACE_DEBUG((LM_ERROR,"��������ʧ�ܣ�����!!!"));
		return 1;
	}
	ACE_DEBUG((LM_DEBUG,"GetResponse"));
	ret = obj->GetReturnCode();
	if(ret)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,ret);
		ACE_DEBUG((LM_ERROR,"��������ʧ��!!dev[%s],��̨���ش�����[%d]",phyid,ret));		
		return 1;
	}
	if(!obj->HasMoreRecord())
	{
		if(revflag)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
			ACE_DEBUG((LM_DEBUG,"�������ѳ����ɹ�!!dev[%s]",phyid));
			return 1;
		}
		else
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,1);
			ACE_DEBUG((LM_ERROR,"��������ʧ��!!dev[%s],��̨����û������",phyid));		
			return 1;
		}
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	ST_PACK *data = obj->GetNextRecord();
	//resp.SetFieldValue(FIELD_ORGTRANSTRACE,0);								//������
	//resp.SetFieldValue(FIELD_ORGTRANSTRACE,data->lsafe_level);			//������
	//if(data->lsafe_level)
	//	resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lsafe_level2);	//�������

	//resp.SetFieldValue(FIELD_RESPONSECODE,2);	//��̨������
	/*
	if(data->lbank_acc_type2)
	{
		ACE_DEBUG((LM_DEBUG,"�������ѣ����۽��[%d]",data->lbank_acc_type2));
		resp.SetFieldValue(FIELD_VERSIONOFLIST,data->lbank_acc_type2);	//���۽��
	}
	*/
	addData[0] = data->lvol2;		
	if(data->lvol2)
	{
		ACE_DEBUG((LM_DEBUG,"�ڿ���������!!dev[%s],����[%d]������Ϣ[%s]",phyid,req->CardNumber,data->vsmess));
	}
	else
	{
		ACE_DEBUG((LM_DEBUG,"�������ѳɹ�!!dev[%s]",phyid));
	}
	addData[1] = data->lbank_acc_type;
		//�Ժ���ӣ����Բ�����ˮ
	ACE_DEBUG((LM_DEBUG,"���º�������־[%d]",data->lbank_acc_type));
	// 1Ϊ���ɸո����ѵļ�¼��2Ϊ������һ����¼
	INT_2_BUF_LE(data->lvol4,addData+2);
	addData[6] = 0x00;
	//addData[6] = data->sstatus4[0] - 0x30;	
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,addData,7);
	return 1;
}

// �ɼ�CPU������ˮ
HD_REGISTER_HANDLER(MT_POSSERI_UPLOAD,HDPOS_SeriUpLoadHandler);
int HDPOS_SeriUpLoadHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
	char term_no[17]={0};
	int onlineflag=0;
	int revflag=0;
	short shopid = 0;
	char phyid[12] ={0};
	char date[7] ={0};
	char time[7] ={0};
	char tac[20]={0};
	unsigned long transmark=0;
	int transfee = 0;
	char seriorigin[2]={0};
	char tripcode[2]={0};
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	
	sprintf(date,"%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);

	for (int i=0;i<4;i++)
	{
		sprintf(tac+2*i,"%02X",req->AdditionalData3[i]);
	}
	ACE_DEBUG((LM_DEBUG,"����CPU����ˮ��tac[%s]",tac));

	onlineflag = 0;//req->AdditionalData1[0];
	unsigned char cRecordType= req->AdditionalData1[1];

	ACE_DEBUG((LM_DEBUG,"����CPU����ˮ�����ѱ�־[%d]",cRecordType));

//	tradetype[0] = req->AdditionalData1[2] + 0x30;
	seriorigin[0] = req->AdditionalData1[3] + 0x30;
	tripcode[0] = req->AdditionalData1[4] + 0x30;
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"��ȡdrtp����ʧ��!"));
		return 1;
	}
	/*
	switch(cRecordType)
	{
	case RT_HD_ONLINE_CONSUME:
		transmark = 153;//0x99
		break;
	case RT_HD_ONLINE_RUSH:
		revflag=1;
		transmark = 254;//0xFE
		break;
	case RT_HD_ONLINE_BLACK:
		transmark=5;
		break;
	case RT_HD_ONLINE_CANCEL:
		revflag=1;
		transmark=cRecordType;
		break;
	default:
		transmark=cRecordType;
		break;
	}
	*/

	transmark = cRecordType;
	if(cRecordType == 2)
	{
		transmark = 5;
	}

	obj->SetRequestHeader(950056);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_LVOL0,cRecordType);					//���ױ�־
	obj->AddField(F_LVOL2,0);					//������ˮ��־:1����0�ѻ�
	obj->AddField(F_LSERIAL0,revflag);					//������־
	obj->AddField(F_LSERIAL1,POSDATATYPE_COLLCARD);		//��������
	obj->AddField(F_SPHONE3,phyid);						//�ն����к�
	obj->AddField(F_LVOL3,shopid);						//�̻���
	obj->AddField(F_LVOL4,req->TraceOfPOS);				//pos��ˮ��
	obj->AddField(F_LVOL5,req->CardNumber);				//���׿���	//
	obj->AddField(F_LVOL7,req->TraceOfEW);				//���״���
	obj->AddField(F_LVOL9,req->AdditionalAmount1);	//�뿨ֵ
	//obj->AddField(F_LVOL1,-req->ManageFee);			//ManageFee���޷��ű���,һԪ�������Ӧ�����޷������ͣ������Ϊ�޷�������
	int nManageFee=req->ManageFee;
	ACE_DEBUG((LM_DEBUG,"amount[%d],manageFee[%d]",req->Amount,nManageFee));
	transfee = ABS(req->Amount) + ABS(nManageFee);
	if(revflag)
	{
		obj->AddField(F_LVOL10,req->AdditionalAmount1); // ����ֵ,���뿨ֵһ��
		obj->AddField(F_LVOL8,-ABS(transfee));			//���׽��
		obj->AddField(F_LVOL1,-ABS(nManageFee));			//������
		
	}
	else
	{
		obj->AddField(F_LVOL10,req->AdditionalAmount1 - ABS(transfee)); // ����ֵ
		obj->AddField(F_LVOL8,ABS(transfee));					//���׽��
		obj->AddField(F_LVOL1,ABS(nManageFee));					//������
	}
	obj->AddField(F_LVOL12,transmark);					//���ױ�־
	obj->AddField(F_SPOST_CODE,date);					//����
	obj->AddField(F_SPOST_CODE2,time);					//ʱ��
	//obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
	obj->AddField(F_SSTATION0,term_no);					//�ն˻����
//	obj->AddField(F_LVOL2,onlineflag);					//������־
//	obj->AddField(F_SSTATUS2,tradetype);				//��������
	obj->AddField(F_SSTATUS3,seriorigin);				//��ˮ��Դ
	obj->AddField(F_SSTATUS4,tripcode);					//��ʾ��Ϣ��
	obj->AddField(F_SCUST_NO,tac);						//������֤��
	
	if(obj->Connect())
	{
		// ����ʧ��
		ACE_DEBUG((LM_ERROR,"����DRTPʧ��!!!"));
		return 1;
	}
	// ������ˮ
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"��������ʧ��!!!"));
		return 1;
	}
	ret = obj->GetReturnCode();
	if(ret)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,ret);
		ACE_DEBUG((LM_ERROR,"�ɼ�CPU������ˮ�ɹ�,dev[%s],��̨���ش�����[%d]",phyid,ret));
		return 1;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	ACE_DEBUG((LM_DEBUG,"�ɼ�CPU������ˮ�ɹ�!!dev[%s]",phyid));
	return 1;
}

// ������ֵ/������ֵ����
HD_REGISTER_HANDLER(MT_ONLINE_DEPOSIT,HDOnlineDepositHandle);
int HDOnlineDepositHandle::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
	int i = 0;
	char term_no[17]="";
	int shopid = 0;
	short tradeseri = 0;
	char phyid[12] = "";
	char date[7] ="";
	char time[7] ="";
	char tradetype[2]="";
	char blkVersion[15]="";
	char dlk1[2]="";
	char dlk2[2]="";
	char rannum[9] = "";
	char mac1[9] ="";
	char addData1[8]="";
	char addData3[12]="";
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_CARDNUMBER,req->CardNumber);
	resp.SetFieldValue(FIELD_TRANSAMOUNT,req->Amount);
	resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,req->Amount);
	resp.SetFieldValue(FIELD_RESERVEFIELD,req->ManageFee);

	sprintf(date,"%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);

	int onlineflag = req->AdditionalData1[0] ;
	unsigned char cRecordType =req->AdditionalData1[1];
	int revflag=0;

//	tradetype[0] = req->AdditionalData1[2] + 0x30;
	for(i=0;i<14;i++)
	{
		//sprintf(blkVersion+i,"%c",req->AdditionalData1[3+i]);
		blkVersion[i] = req->AdditionalData1[3+i];
	}

	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	//BUF_2_INT_LE(term_no,req->PIN);
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);

	BUF_2_SHORT_LE(tradeseri,req->AdditionalData3);
	
	dlk1[0] = req->AdditionalData3[2] + 0x30;
	dlk2[0] = req->AdditionalData3[3] + 0x30;
	for(i=0;i<4;i++)
	{	
		sprintf(rannum + 2*i,"%02X",req->AdditionalData3[4+i]);
	}
	
	for(i=0;i<4;i++)
	{	
		sprintf(mac1 + 2*i,"%02X",req->AdditionalData3[8+i]);
	}
	
	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		return 1;
	}
	unsigned long transmark=0;
	switch(cRecordType)
	{
	case RT_HD_ONLINE_CONSUME:
		transmark = 153;//0x99
		break;
	case RT_HD_ONLINE_RUSH:
		revflag=1;
		transmark = 254;//0xFE
		break;
	case RT_HD_ONLINE_BLACK:
		transmark=5;
		break;
	case RT_HD_ONLINE_CANCEL:
		revflag=1;
		transmark=cRecordType;
		break;
	default:
		transmark=cRecordType;
		break;
	}
	if(!revflag)
		obj->SetRequestHeader(950052);
	else
		obj->SetRequestHeader(950053);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SPHONE3,phyid);						//�ն����к�
	obj->AddField(F_LVOL5,req->CardNumber);				//���׿���
	obj->AddField(F_LVOL7,req->TraceOfEW);				//���״���
	obj->AddField(F_LVOL8,req->Amount);					//���׽��
	obj->AddField(F_LVOL9,req->AdditionalAmount1);		//�뿨ֵ
	obj->AddField(F_LVOL4,req->TraceOfPOS);				//pos��ˮ��
	obj->AddField(F_SPOST_CODE,date);					//����
	obj->AddField(F_SPOST_CODE2,time);					//ʱ��
	//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
	obj->AddField(F_SSTATION0,term_no);					//�ն˻����
	obj->AddField(F_LVOL1,req->ManageFee);				//������
	obj->AddField(F_LVOL2,onlineflag);					//������־
	obj->AddField(F_LVOL12,revflag);				//������־
	obj->AddField(F_SSTATUS2,tradetype);				//��������
	obj->AddField(F_SNAME,blkVersion+2);				//������
	obj->AddField(F_LVOL0,tradeseri);					//ED/EP�����������
	obj->AddField(F_SSTATUS3,dlk1);						//��Կ�汾��
	obj->AddField(F_SSTATUS4,dlk2);						//�㷨��־
	obj->AddField(F_SSTOCK_CODE,rannum);				//α�����
	obj->AddField(F_SSTOCK_CODE2,mac1);					//MAC1
	obj->AddField(F_LVOL3,shopid);						//�̻���
	if(obj->Connect())
	{
		// ����ʧ��
		ACE_DEBUG((LM_INFO,"����DRTPʧ��!!!"));
		return 1;
	}
	// ������ˮ
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_INFO,"���ͳ�ֵ����ʧ��!!!"));
		return 1;
	}
	ret = obj->GetReturnCode();
	if(ret)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,ret);
		ACE_DEBUG((LM_ERROR,"������ֵʧ��!!dev[%s],��̨���ش�����[%d]",phyid,ret));
		return 1;
	}
	if(!obj->HasMoreRecord())
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,1);
		ACE_DEBUG((LM_ERROR,"������ֵʧ��!!dev[%s],��̨�޷�������",phyid));
		return 1;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	ST_PACK *data = obj->GetNextRecord();
	resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lvol9);
	/*
	addData1[0] = data->sstatus0[0] - 0x30;
	addData1[1] = data->sstatus4[0] - 0x30;
	INT_2_BUF_LE(data->lvol4,addData1+2);
	*/
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,addData1,6);
	if(transmark == 153)
	{
		char temp[3]={0};
		for (i=0;i<4;i++)			//����
		{
			memset(temp,0,sizeof temp);
			memcpy(temp,data+2*i,2);
			addData3[i] = strtoul(temp,NULL,10);
		}
		for (i=0;i<3;i++)			//ʱ��
		{
			memset(temp,0,sizeof temp);
			memcpy(temp,time+2*i,2);
			addData3[4+i] = strtoul(temp,NULL,10);
		}
		for (i=0;i<4;i++)			//MAC2
		{
			memset(temp,0,sizeof temp);
			memcpy(temp,data->sstock_code2+2*i,2);
			addData3[7+i] = strtoul(temp,NULL,16);
		}
		resp.SetFieldValue(FIELD_ADDITIONALDATA3,addData3,11);
	}
	ACE_DEBUG((LM_DEBUG,"������ֵ�ɹ�!!dev[%s]",phyid));
	return 1;
}

// ���غ�����
HD_REGISTER_HANDLER(MT_DOWNLOAD_BLKCARD,HDDownloadBlkCardHandle);
int HDDownloadBlkCardHandle::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
	int i = 0;
	char term_no[17] = "";
	char phyid[12] = "";
	char blkVersion[15]="";
	char old_blkver[15]="";
	char addData[1024] = "";
	// Ĭ�Ϸ���һ�����
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);

	for(i=0;i<14;i++)
	{
		//sprintf(blkVersion+i,"%c",req->AdditionalData1[i]);
		blkVersion[i] = req->AdditionalData1[i];
	}
	ACE_DEBUG((LM_DEBUG,"���غ�����,pos�����ͺ�������[%s]!",blkVersion));
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);

	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"�豸 [%s] ������!",phyid));
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// ת��������
		EncodeTermSN(req->TerminalSN,phyid);
		obj->SetRequestHeader(950007);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCERT_NO,phyid);				//�ն����к�
		//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_SSTATION0,term_no);				//�ն˻����
		obj->AddField(F_SNAME,blkVersion+2);			//������
		obj->AddField(F_LVOL1,9);						//ȡ����������
		strcpy(old_blkver,blkVersion);
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_ERROR,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{	
			ret = obj->GetReturnCode();
			if(!ret)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				
				i = 0;
				while(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					addData[5*i] = (data->lvol3 == 0)? 1:0;
					sprintf(blkVersion,"20%s",data->sname);
					INT_2_BUF_LE(data->lvol2,addData+5*i+1);
					i++;
				}
				if(i == 0)
				{
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,old_blkver);
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);		//�޺�����
					return 1;
				}
				resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion);
				resp.SetFieldValue(FIELD_ADDITIONALDATA3,addData,5*i);
				ACE_DEBUG((LM_DEBUG,"���غ������ɹ�!!dev[%s],blkversion[%s]",phyid,blkVersion));
			}
			else
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,ret);
				ACE_DEBUG((LM_ERROR,"���غ�����ʧ��!!dev[%s],��̨���ش�����[%d]",phyid,ret));
			}
		}
	}
	return 1;
}

// ����֪ͨ
HD_REGISTER_HANDLER(MT_ONLINENOTICE3,HDOnlineNotice1);
int HDOnlineNotice1::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret = 0;
	MYDATETIMESTRUCT now;
	KSGDeviceManager * manager = KsgGetGateway()->GetDeviceManager();
	char phyid[12] = "";
	char blkversion[15] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	resp.SetFieldValue(FIELD_RESPONSECODE,2);

	KSGDeviceNode * node = manager->FindDevice(phyid);
	if(node == NULL)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);	
		ACE_DEBUG((LM_DEBUG,"�豸������[%s]",phyid));
		return 1;
	}
	else
	{
		// ��¼�豸״̬��Ϣ
		node->SetState(KSGDeviceNode::dsOnline);
		/*
		int reccnt;
		BUF_2_INT(reccnt,req->AdditionalData1);
		if(reccnt > 0)
			node->SetState(KSGDeviceNode::dsHasRecord);
		*/
		node->update_time();
	}
	
	/*
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(820522);
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			return 1;
		}
		if(!obj->SendRequest(1000))
		{	
			ret = obj->GetReturnCode();
			if(!ret)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
				resp.SetFieldValue(FIELD_ADDRESS,req->Address);
				now = HDGetDataTime();
				resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,7);
				resp.SetFieldValue(FIELD_PIN,req->PIN,8);
				memcpy(blkversion,"20",2);
				memcpy(blkversion+2,KsgGetGateway()->get_max_blk_version(),12);
				resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkversion);
				
				ACE_DEBUG((LM_DEBUG,"����֪ͨ�ɹ�!!dev[%s],blkversion[%s]",phyid,blkversion));
			}
			else
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,ret);
				ACE_DEBUG((LM_ERROR,"����֪ͨʧ��!!dev[%s],��̨���ش�����[%d]",phyid,ret));
			}
		}
	}
	*/
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	now = HDGetDataTime();
	resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,7);
	resp.SetFieldValue(FIELD_PIN,req->PIN,8);
	memcpy(blkversion,"20",2);
	memcpy(blkversion+2,KsgGetGateway()->get_max_blk_version(),12);
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkversion);
	
	ACE_DEBUG((LM_DEBUG,"����֪ͨ�ɹ�!!dev[%s],blkversion[%s]",phyid,blkversion));
	
	return 1;
}

// GCU ����֪ͨ
HD_REGISTER_HANDLER(MT_GCUONLINENOTICE1,HDGCUOnlineNotice);
int HDGCUOnlineNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int recordcnt = 0,version=0;
	size_t packlen;
	char data[128] = "";
	char sversion[8]="";
	unsigned char buf[16]="";
	unsigned char temp[4]="";
	int ret;
	char phyid[15] = "";
	static const std::string param_timesect = "param_timesect_no";	
	static const std::string param_weekno = "param_week_no";		
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	ACE_DEBUG((LM_INFO,"�յ��豸[%s]����֪ͨ",phyid));
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"GCU [%s] ������!",phyid));
		return -1;
	}
	if(node->GetDeviceType() != "9003")
	{
		ACE_DEBUG((LM_ERROR,"�յ��豸[%s]����֪ͨ�����Ǹ��豸����GCU��",phyid));
		return -1;
	}
	// ��¼�豸״̬��Ϣ
	node->SetState(KSGDeviceNode::dsOnline);
	node->update_time();

	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);

	MYDATETIMESTRUCT now = HDDEV::HDGetDataTime();
	resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,sizeof now);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,16);

	memcpy(buf,req->AdditionalData2,16);		// �ļ��汾��Ϣ
	memcpy(temp,buf,4);							// �Ž�ʱ�ΰ汾��
	BUF_2_INT(version,temp);
	sprintf(sversion,"%d",version);
	node->set_param(param_timesect,sversion);

	memcpy(temp,buf+4,4);							// �������Ž�����汾��
	BUF_2_INT(version,temp);
	sprintf(sversion,"%d",version);
	node->set_param(param_weekno,sversion);	
	
	return 0;
}

//���GCU�����Ž��¼�
HD_REGISTER_HANDLER(MT_SENDACCESSEVENT1,HDGCURequestHandler);
int HDGCURequestHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	ACE_DEBUG((LM_DEBUG,"���GCU�����Ž��¼�"));
	KSGDeviceNode *node;
	char phyid[20];
	EncodeTermSN(req->TerminalSN,phyid);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_ERROR,"����豸�����Ž��¼���GCU������[%s]",phyid));
		return -1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
		return -1;
	}
	if(obj->Connect())
	{
		ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
		return -1;
	}
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	this->set_resp_need_mac(true);

	obj->SetRequestHeader(930203);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	/*
	char temp[20] = "";
	sprintf(temp,"%02X",req->AdditionalData1[0]);
	drtp->AddField(F_SEMP_NO,temp);
	xutil::StringUtil::Hex2Str((unsigned char*)&(req->CardNumber),4,temp);
	drtp->AddField(F_SDATE1,temp);
	char date_str[15] = "";
	sprintf(date_str,"20%02d%02d%02d%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,
	req->DateTime.Day,req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
	*/
	int device_id = req->AdditionalData2[0];
	obj->AddField(F_LVOL1,device_id);					// ��ͷ�ţ���Ӧ1-4����
	obj->AddField(F_LVOL2,node->GetDevId());			// GCU ID ��

	int cardno = req->CardNumber;						// ���׿���
	obj->AddField(F_LVOL0,cardno);			

	char temp[20] = "";
	int transmask = req->AdditionalData2[1];			// GCU �������
	/*
	switch(transmask)
	{
	case 0:
		transmask = 1;
		break;
	case 1:
		transmask = 2;
		break;
	case 2:
		transmask = 6;
		break;
	case 8:
		transmask = 113;
		break;
	default:
		transmask = 4;
		break;
	}
	*/
	sprintf(temp,"%02X",transmask);		
	obj->AddField(F_SEMP_NO,temp);

	char date_str[15] = "";
	MYDATETIMESTRUCT now = HDDEV::HDGetDataTime();
	sprintf(date_str,"20%02d%02d%02d%02d%02d%02d",now.Year,now.Month,
		now.Day,now.Hour,now.Minute,now.Second);
	obj->AddField(F_SDATE0,date_str,8);
	obj->AddField(F_STIME0,date_str+8,6);

	ACE_DEBUG((LM_DEBUG,"���GCU�����Ž���ˮ,GCU ID[%d],�ź�[%d],���׿���[%d],GCU�������[%s],����ʱ��[%s]"
		,node->GetDevId(),device_id,cardno,temp,date_str));

	int retries = 3;
	while(retries-->0)
	{
		if(!obj->SendRequest(5000))
		{
			if(!obj->GetReturnCode())
			{
				ACE_DEBUG((LM_DEBUG,"���GCU�����Ž���ˮ����̨�ɹ�"));
				return 1;
			}
			else
			{
				ACE_DEBUG((LM_ERROR,"���GCU�����Ž���ˮ����̨ʧ�ܣ�����[%d][%s]",
					obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
			}			
		}
	}
	return -1;
}
//////////////////////////////////////////////////////////////////////////
HD_REGISTER_HANDLER(MT_GETELECTRICAL,HDGetElecRequestHandler);
int HDGetElecRequestHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	ACE_DEBUG((LM_DEBUG,"����ý��ȡ��"));
	char card_phyno[9]="";
	char tmp[2]="";
	KSGDeviceNode *node;
	char phyid[20]="";
	char transmark[8]="";
	EncodeTermSN(req->TerminalSN,phyid);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_ERROR,"����ý��ȡ�磬�豸������[%s]",phyid));
		return -1;
	}
	if(node->GetDeviceType() != KSG_JSB_DEV)
	{
		ACE_DEBUG((LM_ERROR,"�豸[%s]���ǿ��ڻ�!",phyid));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID)
	{
		ACE_DEBUG((LM_ERROR,"���ڻ����Ų���ȷ,�ϴ�����[%d]",req->TerminalID));
		return 1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
		return -1;
	}
	if(obj->Connect())
	{
		ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
		return -1;
	}
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	this->set_resp_need_mac(true);

	obj->SetRequestHeader(950101);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_LVOL0,node->GetDevId());
	//KsgCardPhyNo_dec2hex(req->CardNumber,card_phyno);
	sprintf(card_phyno,"%08X",req->CardNumber);
	obj->AddField(F_SDATE1,card_phyno);

	tmp[0] = req->AdditionalData1[0];					//�رյ�Դ0x02��������Դ0x01
	sprintf(transmark,"%d",HDA_SYSTEMIDOFATT1_1 + tmp[0]);
	obj->AddField(F_SEMP_NO,transmark);

	ACE_DEBUG((LM_DEBUG,"����ý��ȡ��,�豸 ID[%d],������[%s],transmark[%s]",node->GetDevId(),card_phyno,transmark));

	////////������
	/*
	tmp[0] = 0x01;					// ����ȡ��		
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,tmp,1);
	return 1;
	*/
	//////////////////////////////////////////

	int retries = 3;
	while(retries-->0)
	{
		if(!obj->SendRequest(5000))
		{
			if(!obj->GetReturnCode())
			{
				ACE_DEBUG((LM_DEBUG,"����ý��ȡ��,��̨�ɹ�"));

				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					if(data->lvol1 == 0xFF)
						tmp[0] = 0x01;					// ����ȡ��						
					else		
					{
						tmp[0] = 0x00;
						resp.SetFieldValue(FIELD_RESPONSECODE,RC_INVALIDCARDNO);
					}
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,tmp,1);	
				}	
				return 1;
			}
			else
			{
				ACE_DEBUG((LM_ERROR,"����ý��ȡ��,��̨ʧ�ܣ�����[%d][%s]",
					obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
				break;
			}			
		}
	}

	return -1;
}

} // end of namespace
