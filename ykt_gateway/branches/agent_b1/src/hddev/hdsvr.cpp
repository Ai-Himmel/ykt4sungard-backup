
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

void HDDEV::EncodeTermSN(unsigned long termid,char* sn)
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
			unsigned char tmp[4] = "";
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
					,crc_val,resp->mac[0],resp->mac[1]));
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
		|| node->GetDeviceType() == KSG_HD_ADD_POS_DEV)
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
	return addr;
}

int HDDEV::HDSendBuffer(ACE_HANDLE handler,char* buf,size_t buflen
				 ,ACE_Time_Value* timeout)
{
	if(ACE_INVALID_HANDLE == handler)
		return -1;
	ACE_SOCK_Stream stream(handler);
	size_t transfered;
	ACE_Time_Value tv(3);
	if(ACE::handle_write_ready(handler,&tv) <= 0) 
		return -1;
	stream.send_n(buf,buflen,timeout,&transfered);
	if(buflen == transfered)
	{
		return 0;
	}
	return -1;
}
int HDDEV::HDRecvBuffer(ACE_HANDLE handler,char* buf,size_t maxbuf
				 ,ACE_Time_Value* timeout)
{
	ACE_SOCK_Stream stream(handler);
	// USE recv_n ��ȡ����
	size_t transfered =	0;
	ACE_Time_Value tv(3);
	if(ACE::handle_read_ready(handler,&tv) <= 0) 
		return -1;
	stream.recv_n(buf,maxbuf,timeout,&transfered);
	if(transfered <= 0 || transfered > maxbuf)
	{
		return -1;
	}
	return transfered;
}

int HDDEV::HDParsePosRecord(BYTE* buf,TRADERECORDSTRUCT* trade)
{
	BUF_2_INT_LE(trade->CardNumber,buf);
	BUF_2_INT_LE(trade->Balance,buf+4);
	BUF_2_INT_LE(trade->Amount,buf+8);
	trade->Year = *(buf+12);
	trade->Month = *(buf+13);
	trade->Day = *(buf+14);
	trade->Hour = *(buf+15);
	trade->Minute = *(buf+16);
	trade->Second = *(buf+17);
	BUF_2_SHORT_LE(trade->TraceOfEW,buf+18);
	BUF_2_INT_LE(trade->TraceOfPOS,buf+20);
	BUF_2_INT_LE(trade->OrgTransTrace,buf+24);
	BUF_2_INT_LE(trade->OperatorID,buf+28);
	BUF_2_INT_LE(trade->TerminalSN,buf+32); // �ն˺�
	BUF_2_SHORT_LE(trade->AdditionalMoney,buf+36); // �����
	BUF_2_SHORT_LE(trade->GoodsNumber,buf+38);
	trade->IndexOfEW = *(buf+40);
	if(trade->IndexOfEW > 0)
		trade->IndexOfEW--;
	trade->RecordType = *(buf+41);
	trade->ConsumeMode = *(buf+42);
	memcpy(trade->MAC,buf+43,4);
	uint16 i = GenerateCRC16(buf,43);
	unsigned char tmp[4] = "";
	SHORT_2_BUF(i,tmp);
	/*tmp[0] = (unsigned char)((i & 0xFF00) >> 8);
	tmp[1] = (unsigned char)(i & 0xFF);*/
	tmp[2] = tmp[0];
	tmp[0] = tmp[1];
	tmp[1] = tmp[2];
	for(int i = 0;i < 2;++i)
		for(int j = 0;j < 4;++j)
			tmp[i] ^=  KsgGetGateway()->GetConfig()->_workKey[i+j*2];
	return (ACE_OS::memcmp(trade->MAC,tmp,2) == 0) ? 0 : -1;
	/*if( (i & 0xFF) != trade->MAC[1] || ((i & 0xFF00)>>8) != trade->MAC[0])
		return -1;
	return 0;
	*/
}
namespace HDDEV
{

	//////////////////////////////////////////////////////////////
	// proactor
	KSG_ADD_LISTENER_CLASS(KSG_HD_CCU_LISTENER,HD_CCU_Acceptor);
	HD_CCU_Acceptor::HD_CCU_Acceptor()
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
		// �˿ڴӺ�̨�ж�ȡ
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
		if(open(ACE_INET_Addr(port),0,0,ACE_DEFAULT_ASYNCH_BACKLOG
			,1,ACE_Proactor::instance(),1) == -1 )
		{
			ACE_DEBUG((LM_ERROR,"���CCU������������ʧ��\n"));
			return -1;
		}
		ACE_DEBUG((LM_INFO,"CCU�����߳�ThreadId[%d]�˿�[%d]\n",ACE_OS::thr_self(),port));
		return 0;
	}
	int HD_CCU_Acceptor::stop_listen()
	{
		close();
		return 0;
	}
	////////////////////////////////////////////////////////////////////
#define CCU_MTU 255
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
		free_handler();
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
		//ACE_HEX_DUMP((LM_DEBUG,buffer,data_len));
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
	
	unsigned int termid = req->TerminalSN;
	unsigned short canid = req->Address;
	//��������Բ���Ҫ�ж� CCU �µ��豸�Ƿ����
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
	ACE_SOCK_Stream stream(peer);
	ACE_INET_Addr peer_addr;
	if(stream.get_remote_addr(peer_addr) == -1)
	{
		return -1;
	}
	char ipbuf[10] = "";
	ACE_UINT32 ip = peer_addr.get_ip_address();
	// ȫ��ʹ�������ֽ���
	ip = ACE_HTONL(ip);
	ACE_OS::memcpy(ipbuf,(const void*)&ip,sizeof ip);
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,ipbuf,ACE_OS::strlen(ipbuf));
	// ��ҪӦ��
	return 1;
}

//////////////////////////////////////////////////////////////////////////////
// �豸ǩ��ָ��
HD_REGISTER_HANDLER(MT_SIGNIN1,HDEnrollHandler);
int HDEnrollHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	size_t packlen;
	int ret;
	int term_no;
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

///////////////////////////////////////////////////////////////////////////
//
HD_REGISTER_HANDLER(MT_INITKEY1,HDInitKeyHandler);
int HDInitKeyHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	// ����豸��Ϣ
	ACE_INET_Addr peer_addr;
	ACE_SOCK_Stream peer_sock(peer);
	std::string device_ip;
	char buf[32] = "";
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_INVALIDTERMINAL);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,24);
	
	if(peer_sock.get_remote_addr(peer_addr))
	{
		ACE_DEBUG((LM_NOTICE,"ȡ�öԷ����ӵ�ַ����"));
		return 1;
	}
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
			if(req->Address != addr_port)
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
		if(req->Address != addr_port)
		{
			ACE_DEBUG((LM_ERROR,"�豸[%s]��ַ����ȷ��ע���ַ[%d]�豸��ַ[%d]"
				,phyid,(addr_port&0x00FF),(req->Address&0x00FF)));
			return 1;
		}
	}
	// �Ƚ� IP ��ַ
	if(device_ip == peer_addr.get_host_addr() 
		|| ACE_OS::strcmp(peer_addr.get_host_addr(),"0.0.0.0")==0)
	{
		if(xutil::StringUtil::Str2Hex(
			KsgGetGateway()->GetConfig()->_cardKey.c_str(),(unsigned char*)buf,8) == -1)
			return -1;
		ACE_OS::memset(buf+8,0xFF,16);
		resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,24);
	}
	else
	{
		ACE_DEBUG((LM_NOTICE,"�豸[%s]����IP[%s],ϵͳע��IP[%s]",
			phyid,peer_addr.get_host_addr(),device_ip.c_str()));
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
			ACE_HEX_DUMP((LM_INFO,data,packlen));
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
				ACE_HEX_DUMP((LM_INFO,data,recvlen));
				// ��Ϊ POS ������
				if(recvlen < 17)
				{
					ret = TASK_ERR_EXECUTE;
				}
				else if(UnPackResponseStruct(resp,&msg_type,data,17)) // ��ѹ���ݰ�
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
	
	return TASK_SUCCESS;
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
	//ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	//KSGDeviceNode * node = manager->FindDevice(phyid);
	//if(node == NULL)
	//{
	//	ACE_DEBUG((LM_DEBUG,"�豸������[%s]",phyid));
	//	return -1;
	//}
	EncodeTermSN(req->TerminalSN,phyid);
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
	resp.SetFieldValue(FIELD_VERSIONOFLIST,req->VerOfList);
	/*
	DRTPPoolType::SmartObject obj;
	obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(930057,1);
		obj->AddField(F_SDATE1,phyid);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		std::string the_time;
		KSGOSUtil::GetTimestamp(the_time);
		the_time = "20" + the_time;
		obj->AddField(F_SPHONE3,the_time.c_str());
		obj->AddField(F_LVOL2,0);
		obj->AddField(F_DAMT0,0.0);
		obj->AddField(F_DAMT1,0.0);
		obj->AddField(F_DAMT2,0.0);
		obj->AddField(F_SHOLDER_AC_NO2,the_time.c_str());
		int reccnt;
		BUF_2_INT(reccnt,req->AdditionalData1);
		obj->AddField(F_DAMT3,(double)reccnt);
		DecodeVersionNum(req->VerOfList,version);
		obj->AddField(F_SSERIAL4,version);
		if(obj->Connect())
		{
			ACE_DEBUG((LM_DEBUG,"����DRTPʧ��"));
		}
		else if(obj->SendRequest(500))
		{
			ACE_DEBUG((LM_DEBUG,"��������ʧ��"));
		}
		else if(obj->GetReturnCode())
		{
			ACE_DEBUG((LM_ERROR,"��������ʧ��[%s]",obj->GetReturnMsg().c_str()));
		}
	}
	*/
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
	ACE_DEBUG((LM_INFO,"��ʼ������¼�ļ�!"));
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
				ACE_DEBUG((LM_INFO,"���ڴ������һ����¼[%d]...",index));
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
			ACE_DEBUG((LM_INFO,"���ڴ����¼[%d]...",index));
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

int HDRecordFileReader::SaveAttendBuffer(BYTE *buf)
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
	record.RecordType = buf[13];

	return SaveAttendRecord(&record);
}

int HDRecordFileReader::SaveAttendRecord(ATTENDRECORDSTRUCT *record)
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
	KsgCardPhyNo_dec2hex(record->CardNumber,phyno);
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

int HDRecordFileReader::SaveTradeRecord(TRADERECORDSTRUCT *trade,int crc_status /* =0 */)
{	
	int crc_err = crc_status;
	int unconfirm = 0;
	char temp[10] = "";
	//ACE_DEBUG((LM_DEBUG,"���ڴ���һ����¼..."));
	char sn[12] = "";
	EncodeTermSN(trade->TerminalSN,sn);

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
		return -1;
	int tx_mark = E_999_FAILED;
	BYTE t = trade->RecordType & 0x0F;
	switch(t)
	{
	case 0x00:
		tx_mark = E_999_FAILED;
		break;
	case 0x01:
		tx_mark = E_999_SUCCESS;
		break;
	case 0x02:
		ACE_DEBUG((LM_DEBUG,"��������,���[%d][%d]",trade->Balance,trade->Amount));
		tx_mark = E_999_CANCEL;
		break;
	case 0x03:
		break;
	case 0x04:
		break;
	case 0x0A:
		tx_mark = E_999_ADD_MENOY;
		break;
	case 0x0B:
		tx_mark = E_999_SUBISIDY;
		break;
	case 0x0C:
		break;
	case 0x0D:
		break;
	case 0x0E:
		break;
	case 0x0F:
		break;
	}

	if(tx_mark == E_999_ADD_MENOY)
	{
		// ����ǳ�ֵ����
		obj->SetRequestHeader(930034);
	}
	else if(tx_mark == E_999_SUBISIDY)
	{
		obj->SetRequestHeader(930033);
	}
	else 
	{
		if(E_999_CANCEL == tx_mark && trade->Amount < 0)
		{
			obj->SetRequestHeader(930034);
		}
		else
			obj->SetRequestHeader(950031);
	}

	obj->AddField(F_LVOL4,trade->TraceOfPOS); // ��ˮ��
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);

	obj->AddField(F_SDATE1,sn);
	obj->AddField(F_STX_PWD,"");
	obj->AddField(F_LBANK_ACC_TYPE,19); // ͨѶ�汾�� 39 ����
	obj->AddField(F_LBANK_ACC_TYPE2,0); // ��Ŀ�շ�
	char crc[5] = "";
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
	obj->AddField(F_LVOL9,trade->Balance + (-1*trade->Amount)); //�뿨ֵ 
	obj->AddField(F_LVOL10,trade->Balance); // ����ֵ
	if(E_999_CANCEL == tx_mark)
	{
		obj->AddField(F_LVOL8,ABS(trade->Amount) * -1); // ���׽��
		obj->AddField(F_LVOL1,ABS(trade->AdditionalMoney) * -1); // �����
	}
	else
	{
		obj->AddField(F_LVOL8,ABS(trade->Amount));	//���׽��
		obj->AddField(F_LVOL1,ABS(trade->AdditionalMoney)); // �����
	}
	obj->AddField(F_LVOL7,trade->TraceOfEW); // Ǯ��ˮ�ź�
	char dt_buf[12] = "";
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade->Year,trade->Month,trade->Day);
	obj->AddField(F_SPOST_CODE,dt_buf);
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade->Hour,trade->Minute,trade->Second);
	obj->AddField(F_SPOST_CODE2,dt_buf);
	if(crc_err)
	{
		// ���CRCУ��ʧ��,����ļ�¼��־Ϊʧ��
		tx_mark = E_999_FAILED;
	}
	else if((trade->RecordType & 0x40) == 0)
	{
		// �ڿ�����
		tx_mark = E_999_BLKCARD;
	}
	else if(trade->RecordType & 0x20)
	{
		// ��;����
		ACE_DEBUG((LM_NOTICE,"��;������ˮ,��ˮ��[%d]�豸[%s]",trade->TraceOfPOS,sn));
		tx_mark = E_999_UNCONFIRM;
	}
	obj->AddField(F_LVOL12,tx_mark);

	int retries = 3;
	ACE_DEBUG((LM_DEBUG,"��ˮ�����ύ����̨..."));
	while(retries-->0)
	{
		if(obj->Connect())
		{
			// ����ʧ��
			ACE_DEBUG((LM_INFO,"����DRTPʧ�ܣ�����!!!"));
			continue;
		}
		// ������ˮ
		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"������ˮʧ��[%s][%d]������[%d][%s]"
				,sn,trade->TraceOfPOS,obj->GetReturnCode()
				,obj->GetReturnMsg().c_str()));
			}
			else
				return 0;
		}
		// 1 �������
		ACE_DEBUG((LM_NOTICE,"�ϴ���ˮ����ʧ��,�ȴ�����!!!"));
		KSGThreadUtil::Sleep(1000);
	}
	ACE_DEBUG((LM_ERROR,"������ˮ����̨ʧ��!"));
	return -1;
}

int HDRecordFileReader::SavePosRecord(BYTE* buf)
{
	TRADERECORDSTRUCT trade;
	int crc_err = 0;
	memset(&trade,0,sizeof trade);
	if(HDParsePosRecord(buf,&trade))
	{
		ACE_DEBUG((LM_ERROR,"POS��ˮ��¼У�����"));
		// CRC ����Ҫɾ��
		// ��ɾ��,����Ҫ�ϴ�
		//return 0;
		crc_err = 1;
	}
	return SaveTradeRecord(&trade,crc_err);
}

HDRecordFileReader_Lock_Guard::HDRecordFileReader_Lock_Guard(int devid)
	:_devid(devid),_is_owner(0)
{	
	ACE_DEBUG((LM_DEBUG,"����CCU dev[%d]",_devid));
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
				ACE_DEBUG((LM_DEBUG,"������ˮ���"));
			}
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"δ�ҵ����ؼ�¼�ļ�"));
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
		ACE_DEBUG((LM_DEBUG,"CCU Notice [��¼��%d]",recordcnt));
		// �����ʱĿ¼
		ret = CheckDownloadPath(devid,filepath);
		if(ret > 0)
		{
			ACE_DEBUG((LM_DEBUG,"�����ļ��Ѿ�����!"));
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
			ACE_DEBUG((LM_DEBUG,"CCU����ʹ�øü�¼�ļ� ... "));
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
	int term_no;
	char phyid[12] = "";
	char sn[9]  = "";
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
		ACE_DEBUG((LM_ERROR,"��ֵ����ʧ��,�豸 [%s] ������!",phyid));
		return 1;
	}
	term_no = req->TerminalID;
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"��ֵ����ʧ��,�豸���Ų���ȷ[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// ���ش���
		return 1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// ����ǳ�ֵ����
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
	}
	return 1;
}

HD_REGISTER_HANDLER(MT_ROLLBACK1,HDAddCancelNotice);
int HDAddCancelNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int term_no;
	char sn[9] = "";
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
		//resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
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
	}
	return 1;
}

HD_REGISTER_HANDLER(MT_ALLOWANCE1,HDCheckSubsidyNotice);
int HDCheckSubsidyNotice::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
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

		obj->AddField(F_LVOL2,req->CardNumber);
		// ��ѯδ��ȡ��
		obj->AddField(F_SSTATUS1,"2");
		obj->AddField(F_LVOL3,req->IndexOfEW-1); // Ǯ����
		BUF_2_SHORT_LE(seqno,req->AdditionalData1);
		obj->AddField(F_LVOL1,seqno);
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
				ACE_DEBUG((LM_ERROR,"���벹������ʧ��,[%s][%d]������[%d][%s]"
					,sn,req->TraceOfPOS,obj->GetReturnCode()
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
					seqno = static_cast<unsigned short>(data->lvol10);
					// �������
					int t = (int)KSGMathUtil::D4U5(money*100);
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,t);
					char buf[10] = "";

					SHORT_2_BUF_LE(seqno,buf);
					// �������κ�
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,buf,sizeof(unsigned short));
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				}
				if(seqno > 0)
					ACE_DEBUG((LM_DEBUG,"��ѯ�������ؽ�������κ�[%d][%.2f]",seqno,money));
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
	char phyno[15] = "";
	ACE_OS::sprintf(phyno,"%.010d",req->TerminalSN);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_TRADE_FAILED);
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
	if(node->GetDeviceType() != KSG_HD_POS_DEV)
	{
		ACE_DEBUG((LM_ERROR,"POS[%s]�������ѻ�!",phyno));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID)
	{
		ACE_DEBUG((LM_ERROR,"����POS�����Ų���ȷ,�ϴ�����[%d]",req->TerminalID));
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
	// �����
	//trade.AdditionalMoney = req->ManageFee;
	// ����ģʽ
	trade.ConsumeMode = req->AdditionalData1[1];
	// ��¼����
	trade.RecordType = req->AdditionalData1[0];
	// �̻���
	//BUF_2_SHORT_LE(trade.shop_id,req->AdditionalData1+4);
	// �ʹκ�
	//trade.dinner_id = req->AdditionalData1[6];
	// MAC У����
	ACE_OS::memcpy(trade.MAC,req->AdditionalData4,2);
	HDRecordFileReader reader("",0);
	// ������ˮ
	if(!reader.SaveTradeRecord(&trade))
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	}
	return 1;
}

//! TCP POS ������
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

HD_REGISTER_HANDLER(MT_BATCHSENDRECORD1,HDPOS_Consume_Upload);
int HDPOS_Consume_Upload::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{

	unsigned char serial_buf[100] = "";
	int offset,ret,count;
	this->set_resp_need_mac();
	char phyno[15] = "";
	ACE_OS::sprintf(phyno,"%.010d",req->TerminalSN);
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_TRADE_FAILED);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	KSGDeviceNode *node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyno);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"����POS��δע��,phyid[%s]",phyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_HD_POS_DEV)
	{
		ACE_DEBUG((LM_ERROR,"POS[%s]�������ѻ�!",phyno));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID)
	{
		ACE_DEBUG((LM_ERROR,"����POS�����Ų���ȷ,�ϴ�����[%d]",req->TerminalID));
		return 1;
	}
	HDRecordFileReader reader("",0);
	int datalen = req->LenOfAdditionalData1;
	for(offset = 0,count=0;offset < datalen;
		offset+=HDRecordFileReader::RECORD_BUF_LEN)
	{
		if(offset + HDRecordFileReader::RECORD_BUF_LEN > datalen)
			break;
		ACE_OS::memcpy(serial_buf,req->AdditionalData1 + offset,HDRecordFileReader::RECORD_BUF_LEN);
		if(reader.SavePosRecord(serial_buf))
		{
			// ������ˮʧ��
			ACE_DEBUG((LM_ERROR,"����POS�������͵���ˮʧ�ܣ�phyno[%s]",phyno));
			return 1;
		}
		count++;
	}
	// �ϴ���ˮ
	if(offset >= req->LenOfAdditionalData1)
	{
		ACE_DEBUG((LM_INFO,"����POS�������͵���ˮ�ɹ���[%d]",count));
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
		ret = TASK_SUCCESS;
	}
	return 1;
}

//////////////////////////////////////////////////////////////////////////
// class HD_CCU_Listener

} // end of namespace
