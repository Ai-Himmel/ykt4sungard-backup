
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
		// 比较 MAC 地址
		if(ACE_OS::memcmp(resp->mac,zero,2))
		{
			// 2 byte 长度, 2 byte mac 码
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
				ACE_DEBUG((LM_ERROR,"汇多数据报文MAC校验错误,期望值[%04X],实际值[%02X%02X]"
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
	// USE recv_n 收取数据
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
	BUF_2_INT_LE(trade->CardNumber,buf);  // 交易卡号
	BUF_2_INT_LE(trade->Balance,buf+4);   // 余额
	BUF_2_INT_LE(trade->Amount,buf+8);	   // 交易金额
	trade->Year = *(buf+12);			   // 交易时间
	trade->Month = *(buf+13);
	trade->Day = *(buf+14);
	trade->Hour = *(buf+15);
	trade->Minute = *(buf+16);
	trade->Second = *(buf+17);
	BUF_2_SHORT_LE(trade->TraceOfEW,buf+18);    // 钱包流水号
	BUF_2_INT_LE(trade->TraceOfPOS,buf+20);     // POS流水号
	BUF_2_INT_LE(trade->OrgTransTrace,buf+24);  // 原交易流水号 ( reserved )
	BUF_2_INT_LE(trade->OperatorID,buf+28);     // 操作员卡号 ( reserved )
	BUF_2_INT_LE(trade->TerminalSN,buf+32);     // 终端号 
	BUF_2_SHORT_LE(trade->AdditionalMoney,buf+36); // 管理费
	BUF_2_SHORT_LE(trade->GoodsNumber,buf+38);     // 终端号
	trade->IndexOfEW = *(buf+40);					// 钱包号
	if(trade->IndexOfEW > 0)
		trade->IndexOfEW--;
	trade->RecordType = *(buf+41);				// 记录类型
	trade->ConsumeMode = *(buf+42);				// 消费模式
	BUF_2_SHORT_LE(trade->SubsidyNo,buf+43);	// 补助批次号
	trade->MealId = *(buf+45);					// 餐次号
	memcpy(trade->MAC,buf+46,4);				// MAC 校验
	// 计算 MAC 校验
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
	BUF_2_INT_LE(trade->CardNumber,buf);  // 交易卡号
	BUF_2_INT_LE(trade->Balance,buf+4);   // 余额
	BUF_2_INT_LE(trade->Amount,buf+8);	   // 交易金额
	trade->Year = *(buf+12);			   // 交易时间
	trade->Month = *(buf+13);
	trade->Day = *(buf+14);
	trade->Hour = *(buf+15);
	trade->Minute = *(buf+16);
	trade->Second = *(buf+17);
	BUF_2_SHORT_LE(trade->TraceOfEW,buf+18);    // 钱包流水号
	BUF_2_INT_LE(trade->TraceOfPOS,buf+20);     // POS流水号
	BUF_2_INT_LE(trade->OrgTransTrace,buf+24);  // 原交易流水号 ( reserved )
	BUF_2_INT_LE(trade->GoodsNumber,buf+28);     // 操作员卡号 ( reserved )
	BUF_2_INT_LE(trade->TerminalSN,buf+32);     // 终端号 
	BUF_2_SHORT_LE(trade->AdditionalMoney,buf+36); // 管理费
	BUF_2_SHORT_LE(trade->OperatorID,buf+38);     // 终端号
	trade->IndexOfEW = *(buf+40);					// 钱包号
	if(trade->IndexOfEW > 0)
		trade->IndexOfEW--;
	trade->ConsumeMode = *(buf+41);				// 记录类型
	trade->RecordType = *(buf+41);				// 消费模式
	//BUF_2_SHORT_LE(trade->SubsidyNo,buf+43);	// 补助批次号
	//trade->MealId = *(buf+45);					// 餐次号
	memcpy(trade->MAC,buf+43,4);				// MAC 校验
	// 计算 MAC 校验
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
		// TODO : 增加对客户端连接的合法性检验
		return 0;
	}
	KSG_Proactor_Handler* HD_CCU_Acceptor::new_handler()
	{
		ACE_DEBUG((LM_DEBUG,"创建新的连接..."));
		return new HD_CCU_Request_Handler(this);
	}
	
	int HD_CCU_Acceptor::start_listen()
	{
		// 端口从后台中读取1
		std::string value;
		int port = 6001;
		if(KsgGetSystemParam(HD_SYSPARAM_LISTEN_PORT,value))
		{
			ACE_DEBUG((LM_INFO,"获取CCU侦听端口号失败,使用默认端口[%d]",port));
		}
		else
		{
			port = ACE_OS::atoi(value.c_str());
		}
		if(open(ACE_INET_Addr(port),0,1,ACE_DEFAULT_ASYNCH_BACKLOG
			,1,ACE_Proactor::instance(),0) == -1 )
		{
			ACE_DEBUG((LM_ERROR,"汇多CCU侦听服务启动失败\n"));
			return -1;
		}
		_check_handle = new KSG_Proactor_Check_Handler(this);
		_schd_id = ACE_Proactor::instance()->schedule_timer(
			*_check_handle,NULL,ACE_Time_Value::zero,ACE_Time_Value(10));
		ACE_DEBUG((LM_INFO,"CCU侦听线程ThreadId[%u]端口[%d]\n",ACE_OS::thr_self(),port));

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
			ACE_DEBUG((LM_ERROR,"读取 CCU 连接数据失败![%d][%s]"
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
		// 释放资源
		//result.message_block().release();
		ACE_DEBUG((LM_DEBUG,"handle[%d]应答数据成功!",_pack_index));
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
			ACE_DEBUG((LM_ERROR,"读取 CCU 连接数据失败![%d][%s]"
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
			// 认为接收数据失败
			ACE_DEBUG((LM_ERROR,"读取 CCU 数据失败!!"));
			free_handler();
			return;
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"开始处理数据..."));
			// 读取数据完成
			update_io_time();
			if(_pack_index == 0)
			{
				ACE_InputCDR cdr(&mb);
				cdr >> data_len;
				ACE_DEBUG((LM_DEBUG,"读取第一个包"));
			}
			_pack_index++;
			if(mb.length() - MSG_BUF_LEN_HEADER >= data_len )
			{
				// 读取完成,处理业务
				//ACE_DEBUG((LM_INFO,"处理数据包，长度[%d]",(data_len+MSG_BUF_LEN_HEADER)));
				if( process_request(&mb,data_len+MSG_BUF_LEN_HEADER)<= 0 )
				{
					// 处理失败或者不需要应答
					free_handler();
				}
				return;
			}
			// 认为数据有问题
			// 继续读取
			if(mb.length() >= 65535)
			{
				ACE_DEBUG((LM_ERROR,"数据包长度不合法!!!!"));
				free_handler();
				return;
			}
			//ACE_HEX_DUMP((LM_INFO,mb.rd_ptr(),mb.length()));
			//ACE_DEBUG((LM_INFO,"继续读取数据...len[%d]",(data_len - (mb.length()-MSG_BUF_LEN_HEADER))));
			if( _reader.read(mb,CCU_MTU)!=0)
				//,data_len - mb.length() + MSG_BUF_LEN_HEADER) != 0)
			{
				ACE_DEBUG((LM_ERROR,"读取 CCU 数据失败!!"));
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
		//ACE_DEBUG((LM_INFO,"业务处理中..."));
		// 数据段长度超过允许范围,忽略请求
		//ACE_HEX_DUMP((LM_INFO,buffer,data_len));
		if(UnPackResponseStruct(req,&msg_type,buffer,data_len) != 0)
		{
			ACE_ERROR((LM_ERROR,"数据包不合法"));
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
					ACE_DEBUG((LM_DEBUG,"数据包长度[%d]",mblk->length()));
					if(mblk->length() == 0)
					{
						ACE_DEBUG((LM_ERROR,"应答包长度为0,不发送"));
						return -1;
					}
					if(_writer.write(*mblk,mblk->length()) !=0 )
					{
						ACE_DEBUG((LM_ERROR,"发送应答包失败"));
						return -1;
					}
					_send_count++;
					return 1;
				}
				else if(result == 0)
				{
					// OK
					ACE_DEBUG((LM_DEBUG,"处理成功"));
				}
				else
				{
					// error
					ACE_DEBUG((LM_ERROR,"处理请求失败，返回码[%d]",result));
				}
			}
			else
			{
				ACE_ERROR((LM_ERROR,"不能处理请求代码[%c]",msg_type));
			}	
		}
		catch(...)
		{
			// 捕获所有的异常
			ACE_ERROR((LM_ERROR,"处理请求异常,请求代码[%02x]",msg_type));
		}	
		return -1;
	}
///////////////////////////////////////////////////////////////////
//
HDCCUSvrHandler::HDCCUSvrHandler():_close_time(1)
{		
	// ms
	ACE_DEBUG((LM_DEBUG,"创建 ACE Handler"));
	_max_timeout_sec = ACE_Time_Value(KsgGetGateway()->GetConfig()->_execTimeout/1000*4);
}
HDCCUSvrHandler::~HDCCUSvrHandler()
{
	ACE_DEBUG((LM_DEBUG,"释放 ACE Handler"));
}
int HDCCUSvrHandler::open(void*)
{
	
	ACE_INET_Addr peer_addr;
	if(peer().get_remote_addr(peer_addr) == -1)
	{
		return -1;
	}
	ACE_DEBUG((LM_DEBUG,"接收请求来自[%s]",peer_addr.get_host_addr()));
	// TODO : 检查IP地址是否合法
	/*
	 if( IP 不合法 )
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

	// 放入队列
	if(putq(mb) == -1)
	{
		ACE_DEBUG((LM_ERROR,"保存失败"));
		return -1;
	}
	_close_time = 1;
	// 线程已经启动,返回 0 表示可以继续处理事件
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
	ACE_DEBUG((LM_INFO,"ACE 连接超时！"));
	REACTOR::instance()->remove_handler(this,ACE_Event_Handler::READ_MASK|DONT_CALL);
	return -1;
}

int HDCCUSvrHandler::handle_close(ACE_HANDLE handler, ACE_Reactor_Mask mask)
{
	REACTOR::instance()->remove_handler(this,READ_MASK|DONT_CALL);
	dec_close_time();
	delete_self(handler);
	ACE_DEBUG((LM_DEBUG,"ACE 关闭连接..................."));
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

	ACE_DEBUG((LM_DEBUG,"ACE 打开连接............"));
	ACE_Message_Block * mb = NULL;
	
	ACE_Time_Value tv(5);
	if (this->getq(mb,&tv) == -1) return -1;
	HD8583STRUCT req;
	HD8583STRUCT resp;
	MESSAGETYPE msg_type;
	char * buffer = mb->rd_ptr();
	int len = 0;
	// 数据段长度超过允许范围,忽略请求
	if(UnPackResponseStruct(req,&msg_type,buffer,mb->length()) != 0)
	{
		ACE_ERROR((LM_ERROR,"数据包不合法"));
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
				ACE_DEBUG((LM_DEBUG,"数据包长度[%d]",mb->length()));
				if(peer().send_n(mb->rd_ptr(),mb->length()) <=0 )
				{
					ACE_DEBUG((LM_ERROR,"发送应答包失败"));
				}
				
			}
			else if(result == 0)
			{
				// OK
				ACE_DEBUG((LM_DEBUG,"处理成功"));
			}
			else
			{
				// error
				ACE_DEBUG((LM_ERROR,"处理请求失败，返回码[%d]",result));
			}
		}
		else
		{
			ACE_ERROR((LM_ERROR,"不能处理请求代码[%c]",msg_type));
		}	
	}
	catch(...)
	{
		// 捕获所有的异常
		ACE_ERROR((LM_ERROR,"处理请求异常,请求代码[%02x]",msg_type));
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
	//　回响测试不需要判断 CCU 下的设备是否存在
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_RESPONSECODE,(BYTE)RC_SUCCESS);
	
	//if(ACE_OS::getpeername(peer,(sockaddr*)&(sock_addr.sin_addr),sizeof(peer_addr)))
	/*
	if(stream.get_remote_addr(peer_addr) == -1)
	{
		ACE_DEBUG((LM_ERROR,"回响测试无法取得对方IP!"));
		return -1;
	}
	*/
	char ipbuf[10] = "";
	//peer_addr.set(&sock_addr,sizeof(sock_addr));

	ACE_UINT32 ip = _remote_addr.get_ip_address();
	// 全部使用网络字节序
	ip = ACE_HTONL(ip);
	ACE_OS::memcpy(ipbuf,(const void*)&ip,sizeof ip);
	ACE_DEBUG((LM_INFO,"回响测试,ip[%s]",_remote_addr.get_host_addr()));
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,ipbuf,ACE_OS::strlen(ipbuf));
	// 需要应答
	return 1;
}

//////////////////////////////////////////////////////////////////////////////
// 水控机申请消费指令
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
	//ACE_DEBUG((LM_DEBUG,"卡号为:%d,验证为: %d",cardno,respCode));
	if (!respCode)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	}
	else
		ACE_DEBUG((LM_INFO,"卡号:[%d]为黑卡",cardno));
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
	// 默认返回一般错误
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
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
		return 1;
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// 如果是充值交易
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
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水
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
	// 默认返回一般错误
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
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
		return 1;
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// 设备签到
		obj->SetRequestHeader(950050);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SDATE1,phyid);						//终端序列号
		obj->AddField(F_SPOST_CODE,date);				//日期
		obj->AddField(F_SPOST_CODE2,time);				//时间
		//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_SSTATION0,term_no);			//终端机编号
		obj->AddField(F_SNAME,blkVersion+2);			//黑名单
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水
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
					ACE_DEBUG((LM_INFO,"签到成功!!dev[%s]blkVersion[%s]",phyid,data->sname));
				}
			}
		}
	}
	return 1;
}
// 设备签到指令
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
	// 检查设备信息
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
		ACE_DEBUG((LM_NOTICE,"取得对方连接地址错误！"));
		return 1;
	}
	*/
	KSGDeviceManager * manager = KsgGetGateway()->GetDeviceManager();
	char phyid[12] = "";
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode * node = manager->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_NOTICE,"设备不存在[%s]",phyid));
		return 1;
	}

	KSGDeviceNode *parent_node = node->GetParent();
	if(parent_node == NULL || parent_node->GetDevId() == KSGDeviceNode::LoopDeviceId)
	{
		// 如果是以太网设备
		device_ip = node->GetDevAddr().GetConnect();
		if(node->GetDeviceType() != KSG_HD_SERVER_DEV)
		{
			unsigned short addr_port = GetDeviceAddress(node);
			// 比较设备地址
			if((req->Address & 0x00FF) != (addr_port & 0x00FF))
			{
				ACE_DEBUG((LM_ERROR,"设备[%s]地址不正确！注册地址[%d]设备地址[%d]"
					,phyid,(addr_port&0x00FF),(req->Address&0x00FF)));
				return 1;
			}
		}
	}
	else
	{
		// 如果是 CAN 总线设备
		device_ip = parent_node->GetDevAddr().GetConnect();
		unsigned short addr_port = GetDeviceAddress(node);
		// 比较设备地址
		if((req->Address & 0x00FF) != (addr_port & 0x00FF))
		{
			ACE_DEBUG((LM_ERROR,"设备[%s]地址不正确！注册地址[%d]设备地址[%d]"
				,phyid,(addr_port&0x00FF),(req->Address&0x00FF)));
			return 1;
		}
	}
	// 比较 IP 地址
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
		ACE_DEBUG((LM_INFO,"设备[%s]请求IP[%s],机号[%d] 申请签到成功",
			phyid,this->_remote_addr.get_host_addr(),node->GetTermId()));
	}
	else
	{
		ACE_DEBUG((LM_NOTICE,"设备[%s]请求IP[%s],系统注册IP[%s],设备信息与系统不匹配",
			phyid,this->_remote_addr.get_host_addr(),device_ip.c_str()));
	}
	// 发送密钥
	return 1;
}

////////////////////////////////////////////////////////////////////////
//
int HDDownloadBlkCard::DownloadBlackCard(BYTE addflag,KSGDeviceNode* node
										 ,KSGDeviceNode::Task* task)
{
	// 增加，删除黑名单
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
		// 准备发送名单报文
		HD8583STRUCT req;
		req.Init();
		req.SetFieldValue(FIELD_ADDRESS,addr); // 终端地址
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId()); // 终端机号
		unsigned long encode_ver = EncodeVersionNum(version.c_str()); // 压缩版本号
		req.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// 黑名单版本号
		char data[256] = "";
		ACE_OS::memset(data,0,sizeof data);
		data[0] = addflag;
		INT_2_BUF(cardid,data+1); 
		req.SetFieldValue(FIELD_ADDITIONALDATA2,data,5);  //  交易卡号
		data[0] = 0x01; 
		req.SetFieldValue(FIELD_ADDITIONALDATA3,data,1); // 卡号条数
		ACE_OS::memset(data,0,sizeof data);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		ACE_Time_Value tv(3,0);
		int recvlen = -1;
		size_t packlen;
		handler = task->_handle;
		// 压缩数据包
		if((packlen = PackRequestStruct(req,MT_UPDATELIST2,data,sizeof data,true)) == 0)
		{
			// 错误的数据包
			ret = TASK_ERR_COMMON;
			return ret;
		}		
		ACE_HEX_DUMP((LM_INFO,data,packlen));
		if((result=HDSendBuffer(handler,data,packlen,&tv))) // 发送数据包
		{

			ACE_DEBUG((LM_ERROR,"发送黑明单返回失败，返回码[%d]",result));
			ret = TASK_ERR_TIMEOUT;
		}
		else
		{
			KSGThreadUtil::Sleep(60);
			tv = ACE_Time_Value(1);
			memset(data,0,sizeof data);
			if((recvlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0) // 接收数据包
			{
				ACE_DEBUG((LM_ERROR,"执行黑名单任务发送超时,dev[%d][%s]",
					task_node->GetDevId(),task_node->get_name().c_str()));
				ret = TASK_ERR_TIMEOUT;
			}
			else
			{
				HD8583STRUCT resp;
				MESSAGETYPE msg_type;
				ACE_HEX_DUMP((LM_INFO,data,recvlen));
				if(UnPackResponseStruct(resp,&msg_type,data,(size_t)recvlen)) // 解压数据包
				{
					ACE_DEBUG((LM_ERROR,"执行黑名单任务失败,dev[%d][%s]",
						task_node->GetDevId(),task_node->get_name().c_str()));
					ret = TASK_ERR_EXECUTE;
				}
				else if( (req->Address != resp->Address)
					|| (req->VerOfList != resp->VerOfList)) // 比较POS机应答给我的黑名单版本号
				{
					char ver[15] = "";
					DecodeVersionNum(resp->VerOfList,ver);
					ACE_DEBUG((LM_ERROR,"发送黑名单返回失败，返回码[%d]设备[%d][%s]版本号[%s]"
						,resp->ResponseCode,task_node->GetDevId(),task_node->get_name().c_str(),ver));
					if(resp->ResponseCode != 39)
					{

						ret = TASK_ERR_EXECUTE;
						return ret;
					}
					else
					{
						// 可能版本号已经被更新
						ACE_DEBUG((LM_INFO,"设备[%d][%s]设备版本号[%s],系统版本号[%s]"
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
					// 成功后发送应答给后台
					KSGTaskResponse &tresp = task->GetResponse();
					tresp.AddField(XML_KEY_CARDID,cardid);
					char version_str[14] = "";
					DecodeVersionNum(resp->VerOfList,version_str);
					tresp.AddField(XML_KEY_VERNUM,version_str);
					ACE_DEBUG((LM_INFO,"更新设备黑名单版本成功[%d][%s]版本号[%s]"
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
	// 增加，删除黑名单
	int ret = TASK_ERR_COMMON;
	try
	{
		int result;
		int cardid = task->GetParams().GetParamIntVal(XML_KEY_CARDID);
		std::string version = task->GetParams().GetParam(XML_KEY_VERNUM);
		KSGDeviceNode* task_node = task->GetDeviceNode();
		unsigned short addr;
		addr = GetDeviceAddress(task->GetDeviceNode());
		// 准备发送名单报文
		HD8583STRUCT req;
		req.Init();
		unsigned long sn = DecodeTermSN(task_node->GetPhyId().c_str());
		//req.SetFieldValue(FIELD_TERMINALSN,sn);
		req.SetFieldValue(FIELD_ADDRESS,addr); // 终端地址
		req.SetFieldValue(FIELD_TERMINALID,task_node->GetTermId()); // 终端机号
		unsigned long encode_ver = EncodeVersionNum(version.c_str()); // 压缩版本号
		req.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// 黑名单版本号
		char data[256] = "";
		ACE_OS::memset(data,0,sizeof data);
		data[0] = addflag;
		INT_2_BUF(cardid,data+1); 
		req.SetFieldValue(FIELD_ADDITIONALDATA2,data,5);  //  交易卡号
		data[0] = 0x01; 
		req.SetFieldValue(FIELD_ADDITIONALDATA3,data,1); // 卡号条数
		ACE_OS::memset(data,0,sizeof data);
		ACE_HANDLE handler = ACE_INVALID_HANDLE;
		ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
		int recvlen = -1;
		size_t packlen;
		handler = task->_handle;
		// 压缩数据包
		if((packlen = PackRequestStruct(req,MT_UPDATELIST2,data,sizeof data,true)) == 0)
		{
			// 错误的数据包
			ret = TASK_ERR_COMMON;
		}		
		else if((result=HDSendBuffer(handler,data,packlen,&tv))) // 发送数据包
		{

			ACE_DEBUG((LM_ERROR,"发送黑明单返回失败，返回码[%d]",result));
			ret = TASK_ERR_TIMEOUT;
		}
		else 
		{
			ACE_HEX_DUMP((LM_DEBUG,data,packlen));
			KSGThreadUtil::Sleep(30);
			tv = ACE_Time_Value(1);
			if((recvlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0) // 接收数据包
			{
				ACE_DEBUG((LM_ERROR,"执行黑名单任务发送超时,dev[%d][%s]",
					task_node->GetDevId(),task_node->get_name().c_str()));
				ret = TASK_ERR_TIMEOUT;
			}
			else
			{
				HD8583STRUCT resp;
				MESSAGETYPE msg_type;
				ACE_HEX_DUMP((LM_DEBUG,data,recvlen));
				// 认为 POS 的问题
				if(recvlen < 17)
				{
					ret = TASK_ERR_EXECUTE;
				}
				else if(UnPackResponseStruct(resp,&msg_type,data,recvlen)) // 解压数据包
				{
					ACE_DEBUG((LM_ERROR,"执行黑名单任务失败,dev[%d][%s]",
						task_node->GetDevId(),task_node->get_name().c_str()));
					ret = TASK_ERR_EXECUTE;
				}
				else if( (req->Address != resp->Address)
					|| (req->VerOfList != resp->VerOfList)) // 比较POS机应答给我的黑名单版本号
				{
					char ver[15] = "";
					DecodeVersionNum(resp->VerOfList,ver);
					ACE_DEBUG((LM_ERROR,"发送黑名单返回失败，返回码[%d]设备[%d][%s]版本号[%s]"
						,resp->ResponseCode,task_node->GetDevId(),task_node->get_name().c_str(),ver));
					if(resp->ResponseCode != 39)
					{

						ret = TASK_ERR_EXECUTE;
						return ret;
					}
					else
					{
						// 可能版本号已经被更新
						ACE_DEBUG((LM_INFO,"设备[%d][%s]设备版本号[%s],系统版本号[%s]"
							,task_node->GetDevId(),task_node->get_name().c_str(),ver,version.c_str()));
						ret = TASK_SUCCESS;
					}
				}
				else
					ret = TASK_SUCCESS;
				if(ret == TASK_SUCCESS)
				{
					// 成功后发送应答给后台
					KSGTaskResponse &tresp = task->GetResponse();
					tresp.AddField(XML_KEY_CARDID,cardid);
					char version_str[14] = "";
					DecodeVersionNum(resp->VerOfList,version_str);
					tresp.AddField(XML_KEY_VERNUM,version_str);
					ACE_DEBUG((LM_INFO,"更新设备黑名单版本成功id[%d][%s]"
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
	// 默认返回一般错误
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
	ACE_DEBUG((LM_DEBUG,"查询终端历史交易，终端机编号[%s]",term_no));

	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_INFO,"设备 [%s]不存在!",phyid));
		return 1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{		
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return 1;
		}
		if(node->GetDeviceType() == KSG_999_DEV_ADDPOS)
		{
			obj->SetRequestHeader(950074);
			obj->AddField(F_SPHONE3,phyid);									//终端序列号
			obj->AddField(F_LWITHDRAW_FLAG,node->GetDevId());				//设备id
			obj->AddField(F_SHOLDER_AC_NO,start_datetime);					//开始时间
			obj->AddField(F_SHOLDER_AC_NO2,end_datetime);					//结束时间

			offset = 0;
			BUF_2_INT(num,req->AdditionalData1+offset);
			obj->AddField(F_LVOL1,num); // 批次号号
			offset += 4;

			BUF_2_INT(num,req->AdditionalData1+offset);
			obj->AddField(F_LVOL2,num); // 授权码
			offset += 4;

			memset(buffer,0,sizeof buffer);
			memcpy(buffer,req->AdditionalData1+offset,8);
			obj->AddField(F_SEMP_NO,buffer); // 操作员号
		}
		else
		{
			obj->SetRequestHeader(950065);
			obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
			obj->AddField(F_SPHONE3,phyid);									//终端序列号
			obj->AddField(F_LSAFE_LEVEL,node->GetDevId());					//设备id
			ACE_DEBUG((LM_DEBUG,"设备id [%d] ",node->GetDevId()));
			obj->AddField(F_SHOLDER_AC_NO,start_datetime);					//开始时间
			obj->AddField(F_SHOLDER_AC_NO2,end_datetime);					//结束时间
		
			obj->AddField(F_SSTATION0,term_no);								//终端机编号
			
			obj->AddField(F_LVOL3,shopid);									//商户号
		}

	
		ACE_DEBUG((LM_INFO,"终端[%s]查询历史交易",phyid));
		if(!obj->SendRequest(5000))
		{
			ret = obj->GetReturnCode();
			if(!ret)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					INT_2_BUF_LE(data->lvol1,addData);								//总笔数
					INT_2_BUF_LE(data->lvol2,addData+4);							//总金额
					ACE_DEBUG((LM_DEBUG,"查询终端历史交易，总笔数[%d],总金额[%d]分",data->lvol1,data->lvol2));
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,addData,8);
				}
			}
			else
			{			
				resp.SetFieldValue(FIELD_RESPONSECODE,ret);
				ACE_DEBUG((LM_ERROR,"查询终端历史交易!!dev[%s],后台返回错误码[%d]",phyid,ret));				
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
		ACE_DEBUG((LM_INFO,"设备不存在[%s]",phyid));
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		return 1;
	}
	else
	{
		// 记录设备状态信息
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
		// 认为是 GPRS POS 机
		long curr_ver;
		curr_ver = EncodeVersionNum(KsgGetGateway()->get_max_blk_version());
		resp.SetFieldValue(FIELD_VERSIONOFLIST,curr_ver);
	}
	else
		resp.SetFieldValue(FIELD_VERSIONOFLIST,req->VerOfList);
	
	// 发送密钥
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
	// 设备已存在
	if(i != _s_device_lock.end())
		return 0;
	return 1;
}

int HDRecordFileReader::lock_ccu(int devid)
{
	ACE_GUARD_RETURN(ACE_Thread_Mutex,mon,_s_file_lock_mutex,-1);
	int ret = -1;
	// 5s 超时
	/*
	ACE_Time_Value tv = ACE_OS::gettimeofday();
	tv += ACE_Time_Value(5,0);
	if(_s_file_lock_mutex.acquire(&tv)>0)
	{
		ACE_DEBUG((LM_ERROR,"检测失败"));
		return -1;
	}
	*/
	CCU_DEVICE_LOCK_TYPE::const_iterator i = _s_device_lock.find(devid);
	// 设备已存在
	if(i != _s_device_lock.end())
		ret = -1;
	else
	{
		_s_device_lock.insert(devid);
		ret = 0;
	}
	//ACE_DEBUG((LM_INFO,"锁定文件"));
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
			ACE_DEBUG((LM_ERROR,"释放CCU记录操作,申请资源失败!"));
			goto L_TEST_AGAIN;
		}
		CCU_DEVICE_LOCK_TYPE::iterator i = _s_device_lock.find(devid);
		// 设备已存在
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
	ACE_DEBUG((LM_TRACE,"开始分析记录文件!"));
	HDRecordFileReader_Lock_Guard ccu_guard(_device_id);
	if(!ccu_guard.is_owner())
	{
		ACE_DEBUG((LM_ERROR,"锁定记录文件失败[%s]",_filepath.c_str()));
		return -1;
	}
	try
	{
		if(ACE_OS::filesize(_filepath.c_str()) == 0)
		{
			ACE_DEBUG((LM_INFO,"空记录文件,不需要采集"));
			ret = 0;
		}
		else if((_file_handler = ACE_OS::open(_filepath.c_str()
			,O_RDWR)) == ACE_INVALID_HANDLE)
		{
			ACE_DEBUG((LM_ERROR,"打开流水记录文件失败"));
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
				ACE_DEBUG((LM_ERROR,"删除采集完成记录文件失败[%s][%s:%d]"
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
						ACE_DEBUG((LM_ERROR,"创建目录失败[%s]",basepath.c_str()));
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
					ACE_DEBUG((LM_ERROR,"删除采集完成记录文件失败[%s][%s:%d]"
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
			// 在这种情况下,由于本地的流水文件大小不正确,但不能堵住后面的流水
			// 因此将这个文件移走保存
			std::string stamp;
			KSGOSUtil::GetTimestamp(stamp);
			std::string newname = _filepath + "." + stamp + ".err";
			ACE_DEBUG((LM_NOTICE,"本地记录文件大小不正确[%s],保存为[%s]"
				,_filepath.c_str(),newname.c_str()));
			if(ACE_OS::rename(_filepath.c_str(),newname.c_str()))
			{
				ACE_DEBUG((LM_ERROR,"保存错误记录文件失败[%s][%s:%d]"
					,_filepath.c_str(),ACE_OS::strerror(ACE_OS::last_error())
					,ACE_OS::last_error()));
				ret = -1;
			}
		}
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"处理文件失败,出现未知异常"));
		ret = -1;
	}
	/*
	if(free_ccu_lock(_device_id))
	{
		ACE_DEBUG((LM_ERROR,"释放记录文件失败[%s]",_filepath.c_str()));
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
		ACE_DEBUG((LM_ERROR,"锁定记录文件失败[%s]",_filepath.c_str()));
		return -1;
	}
	try
	{
		ACE_DEBUG((LM_DEBUG,"锁定记录文件成功,开始分析..."));
		ret = DoReadRecordFile();
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"处理记录文件异常......."));
		ret = -1;
	}
	
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"保存记录失败"));
	}
	else
	{
		ACE_OS::unlink(index_file.c_str());
	}
	if(file_lock.release())
	{
		ACE_DEBUG((LM_ERROR,"释放记录文件失败[%s]",_filepath.c_str()));
	}
	return ret;
	
	*/
	std::string index_file = _filepath + ".ind";
	int ret = -1;
	
	try
	{
		ACE_DEBUG((LM_DEBUG,"锁定记录文件成功,开始分析..."));
		ret = DoReadRecordFile();
	}
	catch(std::exception &ex)
	{
		KSG_DUMP_EXCEPTION(ex);
		ACE_DEBUG((LM_ERROR,"处理记录文件异常......."));
		ret = -1;
	}
	catch(...)
	{
		ACE_DEBUG((LM_ERROR,"未知异常，处理记录文件异常......."));
		ret = -1;
	}

	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"保存记录失败"));
	}
	else
	{
		if(ACE_OS::unlink(index_file.c_str()))
		{
			ACE_DEBUG((LM_ERROR,"删除索引文件失败！"));
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
		ACE_DEBUG((LM_ERROR,"取得文件大小失败"));
		return -1;
	}
	// 大小为空的文件，要删除
	if(filesize == 0)
	{
		ACE_DEBUG((LM_ERROR,"空记录文件，自动删除.."));
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
		ACE_DEBUG((LM_ERROR,"分析文件时，文件类型未知！"));
		return -1;
	}
	// 文件大小不对
	// modify cash 2007-09-05 处理大小不正确的流水
	/*
	if(filesize % RECORD_BUF_LEN != 0)
	{
		ACE_DEBUG((LM_ERROR,"流水记录文件大小不正确!"));
		return -2;
	}
	*/
	size_t reccnt = filesize / record_buf_len;
	size_t index = LoadIndex();
	// 认为读取完
	if(index >= reccnt)
		return 0;
#if 1
	if(index > 0)
		ACE_DEBUG((LM_DEBUG,"重新分析记录文件index[%d]",index));
#endif
	if(ACE_OS::lseek(_file_handler,record_buf_len*index,SEEK_SET) == -1)
	{
		ACE_DEBUG((LM_ERROR,"定位记录失败!"));
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
				// 一条流水
				ACE_DEBUG((LM_DEBUG,"正在处理最后一条记录[%d]...",index));
				if(DoSaveRecord(buf))
					return -1;
				SaveIndex(++index);
			}
			else if(bufsize > 0)
			{
				ACE_DEBUG((LM_NOTICE,"当前流水记录文件的大小不正确"));
			}
			return 0;
		}
		else if(readbytes < 0)
		{
			ACE_DEBUG((LM_ERROR,"读取记录文件失败"));
			return -1;
		}
		bufsize += readbytes;
		if(bufsize == record_buf_len)
		{
			// 一条流水
			ACE_DEBUG((LM_TRACE,"正在处理记录[%d]...",index));
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
		ACE_DEBUG((LM_ERROR,"分析文件时，文件类型未知！"));
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
	//1:开启电源，2：关闭电源 (电大多媒体取电)
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
	// 考勤机 机号
	//obj->AddField(F_LVOL3,record->TerminalID);
	// 读头机号
	//obj->AddField(F_LVOL1,record->ReaderID);
	obj->AddField(F_LVOL2,0);
	obj->AddField(F_LVOL3,0);
	if(record->ReaderID == 0)
		obj->AddField(F_LVOL1,record->TerminalID);
	else
	{
		// 考勤机 机号
		obj->AddField(F_LVOL3,record->TerminalID);
		// 读头机号
		obj->AddField(F_LVOL1,record->ReaderID);
	}
	// 机型
	obj->AddField(F_SBANK_CODE,KSG_JSB_DEV);
	// 汇多设备
	vendor = KsgGetGateway()->get_vendor_config(KSG_HD_DEV);
	if(vendor)
	{
		obj->AddField(F_LSERIAL0,vendor->_vendor_id);
	}
	else
		ACE_DEBUG((LM_ERROR,"汇多硬件类型未知"));
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
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			continue;
		}
		if(!obj->SendRequest(1000))
		{
			if(!obj->GetReturnCode())
				return 0;
			else
			{
				ACE_DEBUG((LM_ERROR,"上传考勤记录失败，返回[%d][%s]",
					obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
			}
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"上传考勤记录时请求后台失败[%s]",obj->GetErrMsg().c_str()));
		}
		// 等一会再试
		KSGThreadUtil::Sleep(300);
	}
	return -1;
}
//保存脱机流水记录
int HDRecordFileReader::SaveTradeRecord(TRADERECORDSTRUCT *trade,int posdatatype,int crc_status /* =0 */)
{
	int crc_err = crc_status;
	int revflag=0;
	char devphyid[21]= {0};
	sprintf(devphyid,"%010d",trade->TerminalSN);
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"实时消费流水KsgGetDrtpPool失败,设备序列号[%s]设备流水号[%d]",devphyid,trade->TraceOfPOS));
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
	obj->AddField(F_LVOL0,cRecordType);				//记录类型
	obj->AddField(F_LVOL2,0);						//联机流水标志:1联机0脱机
	obj->AddField(F_LSERIAL0,revflag);				//数据类型
	obj->AddField(F_LSERIAL1,posdatatype);			//数据类型
	obj->AddField(F_LVOL2,0);						//联机流水标志1联机0脱机
	obj->AddField(F_LVOL4,trade->TraceOfPOS);		// 流水号
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SPHONE3,devphyid);
	obj->AddField(F_STX_PWD,"");

	if(transmark == E_999_SUBISIDY)
	{
		// 如果是补助流水
		obj->AddField(F_LBANK_ACC_TYPE,trade->SubsidyNo); // 补助批次号
	}
	else
		obj->AddField(F_LBANK_ACC_TYPE,19); // 通讯版本与 39 兼容

	obj->AddField(F_LBANK_ACC_TYPE2,0); // 科目收费
	char crc[5] = {0};
	xutil::StringUtil::Hex2Str(trade->MAC,2,crc); // CRC 校验
	obj->AddField(F_SBANK_CODE2,crc);
	obj->AddField(F_LVOL6,trade->IndexOfEW); // 钱包号
	obj->AddField(F_LVOL5,trade->CardNumber); // 交易卡号
	obj->AddField(F_LVOL3,trade->OperatorID); // 操作员号
	/*
	 1. 消费时, 交易金额是 负值 , 管理费是 正值
	 2. 充值时, 交易金额是 正值
	 3. 消费冲正时, 交易金额是 正值 , 管理费是 正值
	 4. 充值冲正时,交易金额是 负值
	 */
	//ACE_DEBUG((LM_DEBUG,"补采流水: 设备[%s],出卡值[%d],交易金额[%d]",long_sn,trade->Balance,trade->Amount));
	obj->AddField(F_LVOL9,trade->Balance);				// 入卡值
	trade->Amount = ABS(trade->Amount) + ABS(trade->AdditionalMoney); // 加上搭伙费
	if(revflag)
	{
		obj->AddField(F_LVOL8,-ABS(trade->Amount));			// 交易金额
		obj->AddField(F_LVOL1,-ABS(trade->AdditionalMoney)); // 管理费
		obj->AddField(F_LVOL10,trade->Balance);				// 入卡值
	}
	else
	{
		obj->AddField(F_LVOL8,ABS(trade->Amount));	//交易金额
		obj->AddField(F_LVOL1,ABS(trade->AdditionalMoney)); // 管理费
		obj->AddField(F_LVOL10,trade->Balance - ABS(trade->Amount)); // 出卡值

	}
	obj->AddField(F_LVOL7,trade->TraceOfEW); // 钱包水号号
	char dt_buf[12] = {0};
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade->Year,trade->Month,trade->Day);
	obj->AddField(F_SPOST_CODE,dt_buf);
	ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",trade->Hour,trade->Minute,trade->Second);
	obj->AddField(F_SPOST_CODE2,dt_buf);
	if(crc_err)
	{
		// 如果CRC校验失败,保存的记录标志为失败
		transmark = E_999_FAILED;
	}
	obj->AddField(F_LVOL11,trade->ConsumeMode);		//消费模式
	obj->AddField(F_LVOL12,transmark);

	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_ERROR,"实时消费流水:连接DRTP失败,设备序列号[%s]设备流水号[%d]DRTP错误码[%d][%s]",devphyid,trade->TraceOfPOS,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	// 发送流水
	ACE_DEBUG((LM_TRACE,"实时消费流水发送到DRTP,设备序列号[%s]设备流水号[%d]",devphyid,trade->TraceOfPOS));
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"实时消费流水发送失败,设备序列号[%s]设备流水号[%d]DRTP错误码[%d][%s]",devphyid,trade->TraceOfPOS,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	int ret = obj->GetReturnCode();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"实时流水保存失败,设备序列号[%s]设备流水号[%d]错误码[%d][%s]",devphyid,trade->TraceOfPOS,ret,obj->GetReturnMsg().c_str()));
		return ret;
	}
	ACE_DEBUG((LM_TRACE,"实时消费流水保存成功,设备序列号[%s]设备流水号[%d]",devphyid,trade->TraceOfPOS));
	return 0;
}
//保存补采的POS流水
int HDRecordFileReader::SavePosRecord(BYTE* buf)
{
	TRADERECORDSTRUCT trade;
	int crc_err = 0;
	memset(&trade,0,sizeof trade);
	if(HDParsePosRecord(buf,&trade))
	{
		// CRC 错误要删除
		// 不删除,还是要上传
		//return 0;
		if(!bColHisSeri)	//采集历史流水不用校验
		{
			ACE_DEBUG((LM_ERROR,"POS流水记录校验错误"));
			crc_err = 1;
		}
	}
	return SaveTradeRecord(&trade,POSDATATYPE_COLLPOS,crc_err);
}

HDRecordFileReader_Lock_Guard::HDRecordFileReader_Lock_Guard(int devid)
	:_devid(devid),_is_owner(0)
{	
	ACE_DEBUG((LM_TRACE,"锁定CCU dev[%d]",_devid));
	if(!HDRecordFileReader::lock_ccu(_devid))
		_is_owner = 1;
}
HDRecordFileReader_Lock_Guard::~HDRecordFileReader_Lock_Guard()
{
	if(_is_owner == 1)
	{
		if(HDRecordFileReader::free_ccu_lock(_devid))
		{
			ACE_DEBUG((LM_ERROR,"释放CCU文件锁失败,dev[%d]",_devid));
		}
	}
	_is_owner = 0;
}
int HDRecordFileReader_Lock_Guard::is_owner()
{
	return (_is_owner == 1);
}
///////////////////////////////////////////////////////////////////////////////
// CCU 在线通知
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
		ACE_DEBUG((LM_ERROR,"CCU [%s] 不存在!",phyid));
		return -1;
	}
	if(node->GetDeviceType() != KSG_HD_SERVER_DEV
		&& node->GetDeviceType() != KSG_HD_KQ_CCU)
	{
		ACE_DEBUG((LM_ERROR,"收到设备[%s]在线通知，但是该设备不是CCU！",phyid));
		return -1;
	}
	// 记录设备状态信息
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
		ACE_DEBUG((LM_ERROR,"发送应答失败"));
	}
	/*
	// 主动应答
	filepath = HDA_FILENAME_PRECORD1;
	ret = DoFile(FILEID_PRECORD1,req->AdditionalData2+FILEID_PRECORD1*RECORD_SECT_LEN
		,node,req,filepath);

	if(!ret)
	{
		//成功
		ACE_DEBUG((LM_INFO,"处理CCU[%s]流水记录文件1成功",phyid));
	}
	filepath = HDA_FILENAME_PRECORD2;
	ret = DoFile(FILEID_PRECORD2,req->AdditionalData2+FILEID_PRECORD2*RECORD_SECT_LEN
		,node,req,filepath);

	if(!ret)
	{
		// 成功
		ACE_DEBUG((LM_INFO,"处理CCU[%s]流水记录文件2成功",phyid));
	}
	*/
	
	filepath = HDA_FILENAME_ARECORD1;
	ret = DoFile(FILEID_ARECORD1,req->AdditionalData2+FILEID_ARECORD1*RECORD_SECT_LEN
		,node,req,filepath);
	if(!ret)
	{
		// 成功
		ACE_DEBUG((LM_INFO,"处理CCU[%s]考勤记录文件1成功",phyid));
	}
	filepath = HDA_FILENAME_ARECORD2;
	ret = DoFile(FILEID_ARECORD2,req->AdditionalData2+FILEID_ARECORD2*RECORD_SECT_LEN
		,node,req,filepath);
	if(!ret)
	{
		// 成功
		ACE_DEBUG((LM_INFO,"处理CCU[%s]考勤记录文件1成功",phyid));
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
	1. CCU 在线通知到达
	2. 检查两个记录文件
	3. 如果本地存在记录文件,重新采集入库
	4. 如果CCU中有记录文件需要采集,FTP下载后采集入库
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
		ACE_DEBUG((LM_ERROR,"不支持的CCU的记录类型,ccu[%s]fileid[%d]",devid,fileid));
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
		ACE_DEBUG((LM_DEBUG,"清除CCU上记录文件"));
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
			ACE_DEBUG((LM_ERROR,"连接CCU失败dev[%s]",devid));
		}
		else if(HDSendBuffer(handler,data,packlen,&tv))
		{
			need_free = true;
			ACE_DEBUG((LM_ERROR,"发送删除记录包指令失败,dev[%s]",devid));
		}
		else
		{
			KSGThreadUtil::Sleep(100);
			if((packlen = HDRecvBuffer(handler,data,sizeof data,&tv)) <= 0)
			{
				need_free = true;
				ACE_DEBUG((LM_ERROR,"清除CCU记录文件失败,dev[%s]",devid));
			}
			else if(UnPackResponseStruct(resp,&msg_type,data,packlen))
			{
				ACE_DEBUG((LM_ERROR,"清除CCU记录文件请求应答失败"));
			}
			else if(resp->ResponseCode != RC_SUCCESS)
				//&& resp->ResponseCode != 28 // 记录文件原本就是空的
				//|| resp->TerminalSN != req->TerminalSN)
			{
				ACE_DEBUG((LM_ERROR,"删除CCU[%s]记录文件失败[%x]返回码[%d]"
					,devid,fileid,resp->ResponseCode));
				// add 2007-8-31 , 如果清除 CCU 记录文件失败，需要重新断开连接
				need_free = true;
				// FIXME : 是否要删除记录文件先
				// XXX: 不删除,可以采集
			}
			else
			{
				ACE_DEBUG((LM_NOTICE,"清除 CCU 记录文件成功!dev[%s]",devid));
			}
		}
		if(handler != ACE_INVALID_HANDLE)
			node->GetDevice()->release_handler(node,&handler,need_free);
		//if(retries <= 0)
		//{
		//	ACE_DEBUG((LM_ERROR,"请求CCU失败"));
		//	// XXX: 还是要继续入库.
		//	//return -1;
		//}
		// 导入流水
		//ACE_DEBUG((LM_DEBUG,"开始分析流水"));
		// 如果无法删除流水文件，还是先导入流水先
		HDRecordFileReader reader(filepath,node->GetDevId(),record_type);
		ret = reader.ReadFile();
		if(ret)
		{
			ACE_DEBUG((LM_DEBUG,"读取流水失败[%d]",ret));
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"分析流水完成"));
		}
	}
	else if(ret > 0)
	{
		// 无记录或未关闭
		if(KSGOSUtil::FileExists(filepath))
		{
			ACE_DEBUG((LM_DEBUG,"分析历史流水"));
			HDRecordFileReader reader(filepath,node->GetDevId(),record_type);
			ret = reader.ReadFile();
			if(ret)
			{
				ACE_DEBUG((LM_DEBUG,"读取流水失败[%d]",ret));
			}
			else
			{
				ACE_DEBUG((LM_TRACE,"分析流水完成"));
			}
		}
		else
		{
			ACE_DEBUG((LM_TRACE,"未找到本地记录文件"));
		}
	}
	else
	{
		// 错误
		//ACE_DEBUG((LM_ERROR,"处理文件失败"));
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
			ACE_DEBUG((LM_ERROR,"创建目录失败[%s]",basepath.c_str()));
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
			ACE_DEBUG((LM_ERROR,"创建目录失败[%s]",basepath.c_str()));
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
			// 空记录文件, 删除
			if(ACE_OS::unlink(filepath.c_str()))
			{
				ACE_DEBUG((LM_ERROR,"删除空记录文件失败!!!"));
				// 表示文件已存在
				return 1;
			}
			// 正常
			ACE_DEBUG((LM_DEBUG,"发现本地空记录文件,删除之!"));
			return 0;
		}
		*/
		// 表示文件已存在
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
				ACE_ERROR_RETURN((LM_ERROR,"写入文件[%s]失败",record->file_path),-1);
			else
				record->filp = p;
		}
		return ACE_OS::fwrite(buffer,size,nmemb,record->filp);
	}
	if(!record->file_path)
	{
		ACE_DEBUG((LM_ERROR,"未指定文件路径!"));
	}
	ACE_ERROR_RETURN((LM_ERROR,"调用错误"),-1);
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
	// 下载流水文件
	std::string datafile = filepath;
	char user_pwd[256] = "";
	CURL *curl;
	CURLcode res;

	BYTE file_index = *data;
	BYTE file_flag = 0x00;
	if(file_index == fileid)
	{
		// 检查记录文件 1
		BUF_2_INT(recordcnt,data + 1);
		file_flag = *(data + 5);
		ACE_DEBUG((LM_TRACE,"CCU Notice idx[%d] [记录数%d]",file_index,recordcnt));
		// 检查临时目录
		ret = CheckDownloadPath(devid,filepath);
		if(ret > 0)
		{
			ACE_DEBUG((LM_TRACE,"本地文件已经存在!"));
			// 文件已经存在,可能正在使用中
			return ret;
		}
		else if(ret < 0)
		{
			// 创建目录失败
			ACE_DEBUG((LM_ERROR,"创建目录失败"));
			return ret;
		}
		if(file_flag != FILE_CLOSE)
		{
			ACE_DEBUG((LM_TRACE,"CCU正在使用该记录文件 ... "));
			return -1;
		}
		// 没有记录
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
	
	// 下载文件
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
		ACE_DEBUG((LM_ERROR,"不支持的CCU的记录类型,ccu[%s]fileid[%d]",devid.c_str(),fileid));
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
			ACE_DEBUG((LM_INFO,"FTP下载文件时检测到本地文件正在使用中！！dev[%d]",node->GetDevId()));
			return -1;
		}
		// 采集流水
		do{
			ret = -1;
			ACE_DEBUG((LM_DEBUG,"开始下载记录文件"));
			curl = curl_easy_init();
			if(!curl)
			{
				ACE_DEBUG((LM_ERROR,"申请 CURL 连接资源失败!"));
				continue;
			}
			ACE_DEBUG((LM_DEBUG,"下载CCU URL[%s]",ipstr.c_str()));
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
			// 设置登陆用户名与密码
			ACE_DEBUG((LM_INFO,"CCU [%s]",user_pwd));
			curl_easy_setopt(curl ,CURLOPT_USERPWD,user_pwd);
			// 设置连接超时时间为 10 秒
			curl_easy_setopt(curl, CURLOPT_TIMEOUT,10);
			// 设置 FTP 超时时间为 10 秒
			curl_easy_setopt(curl, CURLOPT_FTP_RESPONSE_TIMEOUT,10);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			curl = NULL;
			if(myfile.filp)
			{
				ACE_DEBUG((LM_DEBUG,"关闭文件句柄!"));
				ACE_OS::fclose(myfile.filp);
				myfile.filp = NULL;
			}
			if(CURLE_OK != res)
			{
				ACE_DEBUG((LM_ERROR,"下载CCU[%s]记录文件[%s]失败,CURL返回错误[%d][%s]"
					,node->GetPhyId().c_str(),datafile.c_str(),res,ftp_msg));
			}
			else if((rec_file_len = ACE_OS::filesize(filepath.c_str())) == 0)
			{
				// 下载的文件为空,删除之
				ACE_DEBUG((LM_NOTICE,"下载的记录文件为空,但CCU记录文件不为空!"));
				if(ACE_OS::unlink(filepath.c_str()))
				{
					ACE_DEBUG((LM_ERROR,"删除空记录文件失败!"));
				}
				ret = -2;
			}
			else
			{
				// 如果文件大小有问题,只要足够大就先采下来.
				if(rec_file_len != recordlen * recordcnt)
				{
					ACE_DEBUG((LM_ERROR,"dev[%s]下载记录文件大小与请求包中文件大小不一致except[%d]received[%d]"
						,node->GetPhyId().c_str(),recordcnt * recordlen,rec_file_len));
					
					// 重新下载记录文件,直到成功为止
					ACE_OS::unlink(filepath.c_str());
					// 等待5 秒重试
					KSGThreadUtil::Sleep(5000);
				}
				else
				{
					ACE_DEBUG((LM_DEBUG,"下载CCU记录文件成功!"));
					ret = 0;
				}
			}
		}while(--retries > 0 && ret != 0);

		if(retries <= 0 && ret != 0)
		{
			ACE_DEBUG((LM_ERROR,"下载CCU记录文件错误,文件大小与请求包中大小不一致"));
		}
	}
	catch(...)
	{
		// 下载文件失败,返回 ERROR
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
	// 默认返回一般错误
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"充值交易失败,设备 [%s] 不存在!",phyid));
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		return 1;
	}
	term_no = req->TerminalID;
	/*
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"充值交易失败,设备机号不正确[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// 返回错误
		return 1;
	}
	*/
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// 如果是充值交易
		obj->SetRequestHeader(950072);
		obj->AddField(F_LWITHDRAW_FLAG,node->GetDevId());
		obj->AddField(F_LSERIAL0,req->TraceOfPOS); // 流水号
		obj->AddField(F_LVOL4,req->CardNumber); // 交易卡号

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
		obj->AddField(F_LVOL7,num); // 入卡金额

		BUF_2_SHORT(snum,req->AdditionalData2+offset);
		obj->AddField(F_LVOL5,snum); //充值次数
		offset+=2;

		offset += 2; // 
		xutil::StringUtil::Hex2Str(req->AdditionalData2+offset,4,buffer);
		buffer[8] = 0;
		obj->AddField(F_SBANK_PWD,buffer); // 随机数
		offset += 4;

		memset(buffer,0,sizeof buffer);
		xutil::StringUtil::Hex2Str(req->AdditionalData2+offset,4,buffer);
		obj->AddField(F_SSTOCK_CODE,buffer); //MAC1
		offset += 4;

		
		memset(buffer,0,sizeof buffer);
		xutil::StringUtil::Hex2Str(req->AdditionalData2+offset,8,buffer);
		obj->AddField(F_SNAME,buffer); // 物理卡号
		offset += 8;

		memset(buffer,0,sizeof buffer);
		xutil::StringUtil::BCD2Str(req->AdditionalData2+offset,6,buffer);
		obj->AddField(F_SSTATION0,buffer); // PSAM 卡终端号

		offset = 0;
		BUF_2_INT(num,req->AdditionalData3+offset);
		obj->AddField(F_LVOL1,num); // 批次号号
		offset += 4;

		BUF_2_INT(num,req->AdditionalData3+offset);
		obj->AddField(F_LVOL2,num); // 授权码
		offset += 4;

		memset(buffer,0,sizeof buffer);
		memcpy(buffer,req->AdditionalData3+offset,8);
		obj->AddField(F_SEMP_NO,buffer); // 操作员号

		obj->AddField(F_LVOL8,req->Amount); // 充值金额
		if(req->ManageFee == 0x01) // 电信手机卡
		{
			obj->AddField(F_LVOL5,req->TraceOfEW-1); // 充值次数
			obj->AddField(F_LVOL7,req->AdditionalAmount1 - req->Amount); // 充值金额
		}


		ACE_DEBUG((LM_DEBUG,"充值交易,流水正在提交到后台..."));
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_ERROR,"连接DRTP失败，重试!!!"));
			return 1;
		}
		if(!obj->SendRequest(2000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"充值交易失败,设备[%s][%d]错误码[%d][%s]"
					,phyid,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				resp.SetFieldValue(FIELD_RESPONSECODE,1);
			}
			else
			{
				// 设置返回值
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lvol10);
					resp.SetFieldValue(FIELD_POSTRACE,data->lcert_code);
					resp.SetFieldValue(FIELD_RESPONSECODE,data->lcert_code);
					byte temp[64] = {0};
					xutil::StringUtil::Str2Hex(data->semail,temp,8);
					resp.SetFieldValue(FIELD_ADDITIONALDATA2,temp,8);
					ACE_DEBUG((LM_INFO,"充值mac[%s]",data->semail));
					ACE_DEBUG((LM_INFO,"充值交易完成!!dev[%s]serialno[%d]rc[%d]",phyid,req->TraceOfPOS,
						data->lcert_code));
				}
			}
		}
		return 1;

#if 0
		obj->SetRequestHeader(849003);
		obj->AddField(F_LVOL4,req->TraceOfPOS); // 流水号
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		EncodeTermSN(req->TerminalSN,sn);
		obj->AddField(F_SDATE1,sn);
		obj->AddField(F_STX_PWD,"");
		obj->AddField(F_LBANK_ACC_TYPE,19); // 通讯版本与 39 兼容
		obj->AddField(F_LBANK_ACC_TYPE2,0); // 科目收费
		char crc[5] = "";
		xutil::StringUtil::Hex2Str(req->mac,2,crc); // CRC 校验
		obj->AddField(F_SBANK_CODE2,crc);
		obj->AddField(F_LVOL6,req->IndexOfEW-1); // 钱包号
		obj->AddField(F_LVOL5,req->CardNumber); // 交易卡号
		obj->AddField(F_LVOL3,req->OperatorID); // 操作员号
		/*
		1. 消费时, 交易金额是 负值 , 管理费是 正值
		2. 充值时, 交易金额是 正值
		3. 消费冲正时, 交易金额是 正值 , 管理费是 正值
		4. 充值冲正时,交易金额是 负值
		*/
		obj->AddField(F_LVOL9,req->AdditionalAmount1); //入卡值 
		obj->AddField(F_LVOL10,req->AdditionalAmount1 + req->Amount); // 出卡值
		obj->AddField(F_LVOL8,ABS(req->Amount)); // 交易金额

		obj->AddField(F_LVOL7,req->TraceOfEW); // 钱包水号号
		char dt_buf[12] = "";
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
		obj->AddField(F_SPOST_CODE,dt_buf);
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
		obj->AddField(F_SPOST_CODE2,dt_buf);
		obj->AddField(F_LVOL12,250);

		ACE_DEBUG((LM_DEBUG,"充值交易,流水正在提交到后台..."));
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水
		if(!obj->SendRequest(2000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"充值交易失败,设备[%s][%d]错误码[%d][%s]"
					,sn,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				// 根据后台的错误码来处理
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
				// 设置返回值
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lvol10);
					resp.SetFieldValue(FIELD_POSTRACE,data->lcert_code);
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
					ACE_DEBUG((LM_INFO,"充值交易成功!!dev[%s]serialno[%d]",sn,req->TraceOfPOS));
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
	// 默认返回一般错误
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
		ACE_DEBUG((LM_ERROR,"充值冲正交易失败,设备 [%s] 不存在!",phyid));
		return 1;
	}
	term_no = req->TerminalID;
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"充值冲正交易失败,设备机号不正确[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// 返回错误
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
			// 连接失败
			ACE_DEBUG((LM_INFO,"充值冲正交易失败,连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水

		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"充值冲正交易失败,[%s][%d]错误码[%d][%s]"
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
				ACE_DEBUG((LM_INFO,"充值冲正完成!!dev[%s]serialno[%d]rc[%d]",phyid,req->TraceOfPOS,rc));
			}
		}
#else
		// 如果是充值交易
		obj->SetRequestHeader(849004);
		obj->AddField(F_LVOL4,req->TraceOfPOS); // 流水号
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		EncodeTermSN(req->TerminalSN,sn);
		obj->AddField(F_SDATE1,sn);
		obj->AddField(F_LVOL5,req->CardNumber); // 交易卡号
		obj->AddField(F_LVOL3,req->OrgTransTrace);
		char dt_buf[12] = "";
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
		obj->AddField(F_SPOST_CODE,dt_buf);
		ACE_OS::sprintf(dt_buf,"%.02d%.02d%.02d",
			req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
		obj->AddField(F_SPOST_CODE2,dt_buf);
		ACE_DEBUG((LM_DEBUG,"正在冲正..."));
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"充值冲正交易失败,连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水

		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"充值冲正交易失败,[%s][%d]错误码[%d][%s]"
					,sn,req->TraceOfPOS,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				// 根据后台的错误码来处理
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
				ACE_DEBUG((LM_INFO,"充值冲正交易成功!!dev[%s]serialno[%d]",sn,req->TraceOfPOS));
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
	// 默认返回一般错误
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
		ACE_DEBUG((LM_ERROR,"申请补助交易失败,设备 [%s] 不存在!",phyid));
		return 1;
	}
	term_no = req->TerminalID;
	if(term_no != node->GetTermId())
	{
		ACE_DEBUG((LM_ERROR,"申请补助交易失败,设备机号不正确[%d][%s]"
			,node->GetDevId(),node->get_name().c_str()));
		// 返回错误
		return 1;
	}

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(849006);

		obj->AddField(F_LVOL5,req->CardNumber);
		// 查询未领取的
		obj->AddField(F_SSTATUS1,"2");
		obj->AddField(F_LVOL1,req->IndexOfEW-1); // 钱包号
		BUF_2_SHORT_LE(seqno,req->AdditionalData1);
		obj->AddField(F_LVOL3,seqno);
		ACE_DEBUG((LM_DEBUG,"发送查询补助请求..."));
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水
		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"申请补助交易失败,[%d][%d]错误码[%d][%s]"
					,req->CardNumber,seqno,obj->GetReturnCode()
					,obj->GetReturnMsg().c_str()));
				return 1;
			}
			else
			{
				// 设置返回值
				double money = 0;
				
				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					money = data->damt0;
					seqno = static_cast<unsigned short>(data->lvol3);
					// 补贴金额
					int t = data->lvol9;
					resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,t);
					char buf[10] = "";

					SHORT_2_BUF_LE(seqno,buf);
					ACE_OS::memcpy(buf+2,buf,2);
					// 补助批次号
					resp.SetFieldValue(FIELD_ADDITIONALDATA1,buf,sizeof(unsigned long));
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
				}
				if(seqno > 0)
					ACE_DEBUG((LM_INFO,"查询补助返回结果，批次号[%d][%.2f]",seqno,money));
				else
					ACE_DEBUG((LM_ERROR,"查询补助返回批次号"));
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
	ACE_DEBUG((LM_DEBUG,"实时消费流水:设备序列号[%s]设备流水号[%d]",phyno,req->TraceOfPOS));
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_TERMINALID,req->TerminalID);
	resp.SetFieldValue(FIELD_TRANSAMOUNT,req->Amount);
	KSGDeviceNode *node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyno);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"消费POS机未注册,phyid[%s]",phyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_HD_POS_DEV
		&& node->GetDeviceType() != KSG_HD_PENSTOCK)
	{
		ACE_DEBUG((LM_ERROR,"POS[%s]不是消费机!",phyno));
		return 1;
	}
	//
	trade.TerminalSN = req->TerminalSN;
	// 卡号
	trade.CardNumber = req->CardNumber;
	// 钱包号
	trade.IndexOfEW = req->IndexOfEW-1;
	// 钱包流水号
	trade.TraceOfEW = req->TraceOfEW;
	// 交易金额
	trade.Amount = req->Amount;
	// 卡余额
	trade.Balance = req->AdditionalAmount1;
	// POS 流水号
	trade.TraceOfPOS = req->TraceOfPOS;
	// 交易时间
	trade.Year = req->DateTime.Year;
	trade.Month = req->DateTime.Month;
	trade.Day = req->DateTime.Day;
	trade.Hour = req->DateTime.Hour;
	trade.Minute = req->DateTime.Minute;
	trade.Second = req->DateTime.Second;
	// 消费模式
	trade.ConsumeMode = req->AdditionalData1[1];
	// 记录类型
	trade.RecordType = req->AdditionalData1[0];
	unsigned short shopid=0;
	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	trade.OperatorID =shopid;
	//管理费
	trade.AdditionalMoney = req->ManageFee;
	// 商户号
	//BUF_2_SHORT_LE(trade.shop_id,req->AdditionalData1+4);
	// 餐次号
	//trade.dinner_id = req->AdditionalData1[6];
	// MAC 校验码
	ACE_OS::memcpy(trade.MAC,req->mac,2);
	HDRecordFileReader reader("",0);
	// 保存流水
	int ret=reader.SaveTradeRecord(&trade,POSDATATYPE_POSREALTIME);
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"保存实时消费流水失败,ret[%d]设备序列号[%s]设备流水号[%d]",ret,phyno,trade.TraceOfPOS));
		return 1;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,req->AdditionalData2,4);//增加指针
	return 1; 
}

//! 实时消费
HD_REGISTER_HANDLER(MT_TRADE1,HDPOS_Consume);
int HDPOS_Consume::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	this->set_resp_need_mac();
	return HD_POS_Consume_Response(req,resp,peer);
}
//! TCP POS 机消费撤销
HD_REGISTER_HANDLER(MT_CANCELTRADE1,HDPOS_Consume_Cancel);
int HDPOS_Consume_Cancel::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	this->set_resp_need_mac();
	return HD_POS_Consume_Response(req,resp,peer);
}
//CPU卡：保存批上送单条脱机流水
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
	ACE_DEBUG((LM_DEBUG,"批上送消费流水:设备序列号[%s]设备流水号[%d]",phyid,pos_seri));
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
		ACE_DEBUG((LM_ERROR,"批上送消费流水KsgGetDrtpPool失败,设备序列号[%s]设备流水号[%d]",phyid,pos_seri));
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

	if(purse_id==1)					// 大钱包消费
	{
		obj->SetRequestHeader(950056);
		obj->AddField(F_LVOL0,cRecordType);					//交易标志
		obj->AddField(F_LVOL2,0);							//联机流水标志1联机0脱机
		obj->AddField(F_LSERIAL0,revflag);					//冲正标志
		obj->AddField(F_LSERIAL1,POSDATATYPE_POSAUTOSEND);	//数据类型,实时脱机流水		
		
		obj->AddField(F_LSAFE_LEVEL,mend_amount);			//补写金额
		//obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_SSTATION0,termno);					//终端机编号
		obj->AddField(F_SSTATUS2,1);						//交易类型
		obj->AddField(F_SSTATUS3,0);						//流水来源
		obj->AddField(F_SSTATUS4,0);						//提示信息码
		obj->AddField(F_SCUST_NO,tac);						//交易验证码
		obj->AddField(F_LVOL3,shopid);						//商户号
	}
	else							// 小钱包：自助复印，水控...
	{
		obj->SetRequestHeader(930031);
		if(transmark==209)				// 汇多脱机小钱包消费只有两种类型：209(成功),241(灰记录)
			transmark=153;				// 正常消费流水
		else
			transmark=255;				// 水控中途拔卡流水
	}
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_LVOL5,cardid);						//交易卡号	//
	obj->AddField(F_LVOL6,purse_id);
	obj->AddField(F_LVOL7,trade_cnt);					//交易次数
	obj->AddField(F_LVOL9,in_bala);						//入卡值
	trade_fee = ABS(trade_fee) + ABS(manage_fee);
	if(revflag)
	{
		//冲正
		obj->AddField(F_LVOL10,in_bala);		// 出卡值
		obj->AddField(F_LVOL8,-ABS(trade_fee));				//交易金额
		obj->AddField(F_LVOL1,-ABS(manage_fee));				//手续费
	}
	else
	{
		obj->AddField(F_LVOL10,in_bala-ABS(trade_fee));		// 出卡值
		obj->AddField(F_LVOL8,ABS(trade_fee));				//交易金额
		obj->AddField(F_LVOL1,ABS(manage_fee));				//手续费
	}
	obj->AddField(F_LVOL4,pos_seri);					//pos流水号
	obj->AddField(F_SPOST_CODE,date);					//日期
	obj->AddField(F_SPOST_CODE2,time);					//时间
	obj->AddField(F_LVOL12,transmark);					//交易标记
	obj->AddField(F_SPHONE3,phyid,strlen(phyid));		//终端序列号
	ACE_DEBUG((LM_DEBUG,"批上送消费流水:设备序列号[%s]钱包号[%d]",phyid,purse_id));

	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_ERROR,"批上送消费流水连接DRTP失败,设备序列号[%s]设备流水号[%d]DRTP错误码[%d][%s]",phyid,pos_seri,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	// 发送流水
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"批上送消费流水发送到DRTP失败,设备序列号[%s]设备流水号[%d]DRTP错误码[%d][%s]",phyid,pos_seri,obj->GetErrCode(),obj->GetErrMsg().c_str()));
		return 1;
	}
	int ret = obj->GetReturnCode();
	if(ret)
	{
		ACE_DEBUG((LM_ERROR,"批上送消费流水保存失败,设备序列号[%s]设备流水号[%d]错误码[%d][%s]",phyid,pos_seri,ret,obj->GetReturnMsg().c_str()));
		return ret;
	}
	return 0;
}
// CPU卡：POS机脱机记录批上送
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
	// 默认返回一般错误
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
		ACE_DEBUG((LM_INFO,"前置机中该设备[%s]不存在!",phyid));
		return 1;
	}
	
	//上送流水，转phyid
	EncodeTermSN(req->TerminalSN,phyid);

	int cardtype = node->card_type();
	devtype = HDA_SYSTEMIDOFALL & (req->Address);

	if(node->GetDeviceType() == KSG_POS_DEV
		|| node->GetDeviceType() == KSG_HD_PENSTOCK)						// 消费pos机, 水控器
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
				ACE_DEBUG((LM_ERROR,"批上送第%d条记录失败!!设备序列号[%s],错误码[%d]",count+1,phyid,ret));
				return 1;
			}
			/*	自助复印上送的流水最多为470个字节，10条
			count++;
			if(count>7)
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,2);
				ACE_DEBUG((LM_ERROR,"批上送记录长度[%d]错误,设备序列号[%s]",datalen,phyid));
				return 1;
			}
			*/
		}

		ACE_DEBUG((LM_DEBUG,"批上送流水成功,数据长度[%d]设备序列号[%s]记录数量[%d]条",datalen,phyid,count));
		resp.SetFieldValue(FIELD_ADDITIONALDATA2,req->AdditionalData2,4);//读指针
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	}
	else if(node->GetDeviceType() == KSG_JSB_DEV)				// 考勤机
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
				// 保存流水失败
				ACE_DEBUG((LM_ERROR,"保存考勤机批上送的流水失败！phyno[%s]",phyid));
				return 1;
			}
			count++;
		}

		if(offset >= req->LenOfAdditionalData1)
		{
			ACE_DEBUG((LM_TRACE,"保存设备批上送的流水成功！[%d]",count));
			resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
			ret = TASK_SUCCESS;
		}
	}
	else
	{
		ACE_DEBUG((LM_ERROR,"保存汇多充值POS流水忽略！设备物理ID[%s]设备类型[%s]错误",
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
		ACE_DEBUG((LM_ERROR,"考勤机未注册,phyid[%s]",phyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_JSB_DEV)
	{
		ACE_DEBUG((LM_ERROR,"POS[%s]不是考勤!",phyno));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID)
	{
		ACE_DEBUG((LM_ERROR,"考勤机机号不正确,上传机号[%d]",req->TerminalID));
		return 1;
	}
	// 上传考勤流水

	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		obj->SetRequestHeader(950101);
		//设备 ID 号
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_LVOL0,node->GetDevId());
		KsgCardPhyNo_dec2hex(req->CardNumber,card_phyno);
		obj->AddField(F_SDATE1,card_phyno);
		int reader_id = req->AdditionalData1[0];
		obj->AddField(F_LVOL1,reader_id);
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水
		if(!obj->SendRequest(1000))
		{
			if(obj->GetReturnCode())
			{
				ACE_DEBUG((LM_ERROR,"考勤请求失败,[%s]错误码[%d][%s]"
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
	// POS 请求更新黑名单
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
	// 检查请求的合法性
	//EncodeTermSN(req->TerminalSN,devphyno);
	ACE_OS::sprintf(devphyno,"%.010d",req->TerminalSN);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(devphyno);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"更新黑名单请求时设备不存在[%s]",devphyno));
		return 1;
	}
	if(node->GetDeviceType() != KSG_HD_POS_DEV)
	{
		ACE_DEBUG((LM_ERROR,"更新黑名单请求时设备[%s]不是消费机",devphyno));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID
		|| node->GetConnType() != KSGDeviceURL::dctModem)
	{
		ACE_DEBUG((LM_ERROR,"更新黑名单请求时设备[%s]机号不正确,或连接方式错误!"
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
		// 连接失败
		ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
		return 1;
	}
	// 请求黑名单
	// 更新当前的设备黑名单版本
	DecodeVersionNum(req->VerOfList,max_vol);
	
	obj->SetRequestHeader(950010);
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_SCUST_LIMIT2,KsgGetGateway()->GetConfig()->_dynaKey.c_str());
	obj->AddField(F_LVOL1,blk_card_cnt);
	obj->AddField(F_LVOL5,node->GetDevId());
	obj->AddField(F_SCUST_LIMIT,max_vol);
	if(obj->SendRequest(5000))
	{
		// 发送指令失败
		ACE_DEBUG((LM_DEBUG,"接收指令超时等待结束!"));
		return -1;
	}
	if(obj->GetReturnCode())
	{
		ACE_DEBUG((LM_ERROR,"下载黑名单失败，返回[%d][%s]",
			obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
		return -1;
	}
	count = 0;
	ACE_OS::memset(blk_buf,0,sizeof blk_buf);
	ACE_OS::memset(max_vol,0,sizeof max_vol);
	while(obj->HasMoreRecord() && count < blk_card_cnt)
	{
		ST_PACK * data = obj->GetNextRecord();
		// 下载指令
		int flag = data->lvol3;
		int devid = data->lvol5;
		int cardid = data->lvol2;
		char curr_vol[13] = "";
		ACE_OS::strcpy(curr_vol,data->sname);
		if(ACE_OS::strncmp(curr_vol,max_vol,12)>0)
		{
			ACE_OS::strcpy(max_vol,curr_vol);
		}
		// 增删标志
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
		ACE_DEBUG((LM_DEBUG,"设备[%s]请求更新黑名单,后台黑名单版本已经全部更新",devphyno));
		return 1;
	}
	ACE_DEBUG((LM_DEBUG,"设备[%s]请求更新黑名单,一共更新[%d]条",devphyno,count));
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,blk_buf,count*card_len);
	unsigned long encode_ver = EncodeVersionNum(max_vol); // 压缩版本号
	resp.SetFieldValue(FIELD_VERSIONOFLIST,encode_ver);	// 黑名单版本号
	return 1;

}

// pos机向后台签到(CPU卡)
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

	// 默认返回一般错误
	resp.SetFieldValue(FIELD_RESPONSECODE,2);					//网络故障
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	
	sprintf(date,"%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);
	
	/*
	for(int i=0;i<14;i++)			// 后台黑名单为12位
	{
		blkVersion[i] = req->AdditionalData1[i];
	}
	*/
	memcpy(blkVersion,req->AdditionalData1,14);
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	ACE_DEBUG((LM_DEBUG,"POS机签到,设备序列号[%s]终端机编号[%s]",phyid,term_no));

	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);				//pos机未启用
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
		return 1;
	}
	if(node->GetTermId()!=req->TerminalID)
	{
		ACE_DEBUG((LM_WARNING,"设备终端[%s]机号与系统不符,终端机号[%d],系统[%d]",phyid,req->TerminalID,node->GetTermId()));
	}
	if(GetDeviceAddress(node) != req->Address)
	{
		ACE_DEBUG((LM_ERROR,"设备终端[%s]地址与系统不符,终端地址[%d],系统[%d]",phyid,req->Address,GetDeviceAddress(node)));
		resp.SetFieldValue(FIELD_RESPONSECODE,25);					//网络故障
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"设备签到KsgGetDrtpPool错误"));
		return 1;
	}
	// 设备签到
	if(node->GetDeviceType() == KSG_999_DEV_ADDPOS)	// 充值机
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
			// 连接失败
			ACE_DEBUG((LM_ERROR,"连接DRTP失败,设备序列号[%s]DRTP错误码[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		// 发送流水
		if(obj->SendRequest(1000))
		{
			ACE_DEBUG((LM_ERROR,"发送签到请求失败,设备序列号[%s]DRTP错误码[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		ret = obj->GetReturnCode();
		if(ret)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,1);
			ACE_DEBUG((LM_ERROR,"签到失败!设备序列号[%s],后台返回错误码[%d]",phyid,ret));
			return 1;
		}
		if(!obj->HasMoreRecord())
		{
			ACE_DEBUG((LM_ERROR,"签到失败!,后台无数据返回"));
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

		ACE_DEBUG((LM_INFO,"充值终端签到成功!序列号[%s]操作员[%s]批次号[%d]",phyid,data->semp_no,data->lvol1));

	}
	else
	{  // 消费机
		obj->SetRequestHeader(950050);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SPHONE3,phyid);					//终端序列号
		obj->AddField(F_SPOST_CODE,date);				//日期
		obj->AddField(F_SPOST_CODE2,time);				//时间
		//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_LVOL5,req->OperatorID);			//操作员卡号
		obj->AddField(F_SSTATION0,term_no);				//终端机编号
		obj->AddField(F_SNAME,blkVersion+2);			//黑名单
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_ERROR,"连接DRTP失败,设备序列号[%s]DRTP错误码[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		// 发送流水
		if(obj->SendRequest(1000))
		{
			ACE_DEBUG((LM_ERROR,"发送签到请求失败,设备序列号[%s]DRTP错误码[%d][%s]",phyid,obj->GetErrCode(),obj->GetErrMsg().c_str()));
			return 1;
		}
		ret = obj->GetReturnCode();
		if(ret)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,ret);
			ACE_DEBUG((LM_ERROR,"签到失败!设备序列号[%s],后台返回错误码[%d]",phyid,ret));
			return 1;
		}
		if(!obj->HasMoreRecord())
		{
			ACE_DEBUG((LM_ERROR,"签到失败!,后台无数据返回"));
			return 1;
		}
		resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
		ST_PACK *data = obj->GetNextRecord();
		unsigned char ucPosVersion[7]={0};
		int offset=0;
		ucPosVersion[offset]=data->lvol0;								//设备工作模式0联机1脱机模式
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
		resp.SetFieldValue(FIELD_ADDITIONALDATA3,ucPosVersion,6);	//设备工作模式
		SHORT_2_BUF_LE(data->lvol3,shopid);
		resp.SetFieldValue(FIELD_ADDITIONALDATA4,shopid,2);			//商户号
		if(node->GetDeviceType() == KSG_999_DEV_JSB)				// 充值机
			resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion);
		else
		{
			sprintf(blkVersion,"20%s",data->sname);				//转为14位
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
		ACE_DEBUG((LM_INFO,"消费终端签到成功!设备序列号[%s]黑名单版本[%s]商户号[%d]",phyid,blkVersion,data->lvol3));
	}
	
	return 1;
}

// 联机消费/联机消费冲正
HD_REGISTER_HANDLER(MT_ONLINE_CONSUME,HDOnlineConsumeHandler);
int HDOnlineConsumeHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	int ret;
	int i = 0;
	char term_no[17]={0};
	int onlineflag=0;	//联机标志
	int revflag=0;		//冲正标志
	int transtype=0;	//交易类型
	int tradefee = 0; // 交易金额
	int shopid = 0;
	char phyid[12] = {0};
	char date[7] ={0};
	char time[7] ={0};	
	char tradetype[2]={0};
	char blkVersion[15]={0};
	char addData[8]={0};
	ACE_DEBUG((LM_DEBUG,"联机消费开始"));
	// 默认返回一般错误
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);
	resp.SetFieldValue(FIELD_CARDNUMBER,req->CardNumber);
	resp.SetFieldValue(FIELD_TRANSAMOUNT,req->Amount);
	resp.SetFieldValue(FIELD_RESERVEFIELD,req->ManageFee);
//	SYSTEMTIME st; //定义存放时间的结构体
//	GetSystemTime(&st);
//	ACE_DEBUG((LM_DEBUG,"联机消费开始1:%02d%02d%02d%03d",st.wHour+8,st.wMinute,st.wSecond,st.wMilliseconds));

	sprintf(date,"%02d%02d%02d",req->DateTime.Year,req->DateTime.Month,req->DateTime.Day);
	sprintf(time,"%02d%02d%02d",req->DateTime.Hour,req->DateTime.Minute,req->DateTime.Second);

	unsigned long transmark=0;	//交易标记
	onlineflag = req->AdditionalData1[0] ;
	unsigned char cRecordType  = req->AdditionalData1[1];
	transtype=req->AdditionalData1[2];
	//ACE_DEBUG((LM_DEBUG,"联机消费标志[%d]",onlineflag));
	//tradetype[0] = req->AdditionalData1[2] + 0x30;
	for(i=0;i<14;i++)
	{
		//sprintf(blkVersion+i,"%c",req->AdditionalData1[3+i]);		//比较耗时
		blkVersion[i] = req->AdditionalData1[3+i];
	}
	ACE_DEBUG((LM_DEBUG,"联机消费,黑名单[%s]",blkVersion));
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);

	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);
	ACE_DEBUG((LM_DEBUG,"联机消费，终端机编号[%s]",term_no));

	BUF_2_SHORT_LE(shopid,req->AdditionalData4);
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
		return 1;
	}
	node->update_time();
	
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"取drtp连接池失败!"));
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
	obj->AddField(F_LVOL9, req->AdditionalAmount1);					//入卡值
	int nManageFee=req->ManageFee;
	ACE_DEBUG((LM_DEBUG,"amount[%d],managefee[%d]",req->Amount,nManageFee));
	tradefee = ABS(req->Amount) + ABS(nManageFee);
	if(revflag)
	{
		//冲正或取消
		obj->AddField(F_LVOL10, req->AdditionalAmount1);			// 出卡值
		obj->AddField(F_LVOL8,-ABS(tradefee));						//交易金额
		obj->AddField(F_LVOL1,-ABS(nManageFee));						//手续费
	}
	else
	{
		//消费
		obj->AddField(F_LVOL10,req->AdditionalAmount1 - ABS(tradefee));	// 出卡值
		obj->AddField(F_LVOL8,ABS(tradefee));								//交易金额
		obj->AddField(F_LVOL1,ABS(nManageFee));								//手续费
	}
	obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
	obj->AddField(F_LSERIAL0,revflag);					//冲正标志
	obj->AddField(F_LSERIAL1,POSDATATYPE_POSONLINE);	//数据类型
	obj->AddField(F_LVOL0,cRecordType);					//交易标志
	obj->AddField(F_LVOL2,onlineflag);					//联机流水标志:1联机0脱机
	obj->AddField(F_LVOL3,shopid);						//商户号
	obj->AddField(F_LVOL4,req->TraceOfPOS);				//POS流水号
	obj->AddField(F_LVOL5,req->CardNumber);				//交易卡号
	obj->AddField(F_LVOL7,req->TraceOfEW);				//交易次数
	obj->AddField(F_SPHONE3,phyid);						//终端序列号
	obj->AddField(F_LSAFE_LEVEL,req->OrgTransTrace);	//补助序号
	obj->AddField(F_SPOST_CODE,date);					//日期
	obj->AddField(F_SPOST_CODE2,time);					//时间
	//obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
	obj->AddField(F_SSTATION0,term_no);					//终端机编号
	//ACE_DEBUG((LM_DEBUG,"联机消费，手续费[%d]",req->ManageFee));
	obj->AddField(F_LVOL12,transmark);					//交易标志
	//obj->AddField(F_SSTATUS2,tradetype);				//交易类型
	obj->AddField(F_SNAME,blkVersion+2);				//黑名单

	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_ERROR,"连接DRTP失败，重试!!!"));
		return 1;
	}
	ACE_DEBUG((LM_DEBUG,"SendRequest"));
	// 发送流水
	if(obj->SendRequest(500))
	{
		ACE_DEBUG((LM_ERROR,"发送请求失败，重试!!!"));
		return 1;
	}
	ACE_DEBUG((LM_DEBUG,"GetResponse"));
	ret = obj->GetReturnCode();
	if(ret)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,ret);
		ACE_DEBUG((LM_ERROR,"联机消费失败!!dev[%s],后台返回错误码[%d]",phyid,ret));		
		return 1;
	}
	if(!obj->HasMoreRecord())
	{
		if(revflag)
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
			ACE_DEBUG((LM_DEBUG,"联机消费冲正成功!!dev[%s]",phyid));
			return 1;
		}
		else
		{
			resp.SetFieldValue(FIELD_RESPONSECODE,1);
			ACE_DEBUG((LM_ERROR,"联机消费失败!!dev[%s],后台返回没有数据",phyid));		
			return 1;
		}
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	ST_PACK *data = obj->GetNextRecord();
	//resp.SetFieldValue(FIELD_ORGTRANSTRACE,0);								//补助号
	//resp.SetFieldValue(FIELD_ORGTRANSTRACE,data->lsafe_level);			//补助号
	//if(data->lsafe_level)
	//	resp.SetFieldValue(FIELD_ADDITIONALAMOUNTS,data->lsafe_level2);	//补助金额

	//resp.SetFieldValue(FIELD_RESPONSECODE,2);	//后台错误码
	/*
	if(data->lbank_acc_type2)
	{
		ACE_DEBUG((LM_DEBUG,"联机消费，补扣金额[%d]",data->lbank_acc_type2));
		resp.SetFieldValue(FIELD_VERSIONOFLIST,data->lbank_acc_type2);	//补扣金额
	}
	*/
	addData[0] = data->lvol2;		
	if(data->lvol2)
	{
		ACE_DEBUG((LM_DEBUG,"黑卡联机消费!!dev[%s],卡号[%d]锁卡信息[%s]",phyid,req->CardNumber,data->vsmess));
	}
	else
	{
		ACE_DEBUG((LM_DEBUG,"联机消费成功!!dev[%s]",phyid));
	}
	addData[1] = data->lbank_acc_type;
		//以后添加，可以补采流水
	ACE_DEBUG((LM_DEBUG,"更新黑名单标志[%d]",data->lbank_acc_type));
	// 1为补采刚刚消费的记录，2为补采上一条记录
	INT_2_BUF_LE(data->lvol4,addData+2);
	addData[6] = 0x00;
	//addData[6] = data->sstatus4[0] - 0x30;	
	resp.SetFieldValue(FIELD_ADDITIONALDATA1,addData,7);
	return 1;
}

// 采集CPU卡上流水
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
	// 默认返回一般错误
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
	ACE_DEBUG((LM_DEBUG,"上送CPU卡流水，tac[%s]",tac));

	onlineflag = 0;//req->AdditionalData1[0];
	unsigned char cRecordType= req->AdditionalData1[1];

	ACE_DEBUG((LM_DEBUG,"上送CPU卡流水，消费标志[%d]",cRecordType));

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
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"获取drtp连接失败!"));
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
	obj->AddField(F_LVOL0,cRecordType);					//交易标志
	obj->AddField(F_LVOL2,0);					//联机流水标志:1联机0脱机
	obj->AddField(F_LSERIAL0,revflag);					//冲正标志
	obj->AddField(F_LSERIAL1,POSDATATYPE_COLLCARD);		//数据类型
	obj->AddField(F_SPHONE3,phyid);						//终端序列号
	obj->AddField(F_LVOL3,shopid);						//商户号
	obj->AddField(F_LVOL4,req->TraceOfPOS);				//pos流水号
	obj->AddField(F_LVOL5,req->CardNumber);				//交易卡号	//
	obj->AddField(F_LVOL7,req->TraceOfEW);				//交易次数
	obj->AddField(F_LVOL9,req->AdditionalAmount1);	//入卡值
	//obj->AddField(F_LVOL1,-req->ManageFee);			//ManageFee是无符号变量,一元负运算符应用于无符号类型，结果仍为无符号类型
	int nManageFee=req->ManageFee;
	ACE_DEBUG((LM_DEBUG,"amount[%d],manageFee[%d]",req->Amount,nManageFee));
	transfee = ABS(req->Amount) + ABS(nManageFee);
	if(revflag)
	{
		obj->AddField(F_LVOL10,req->AdditionalAmount1); // 出卡值,与入卡值一致
		obj->AddField(F_LVOL8,-ABS(transfee));			//交易金额
		obj->AddField(F_LVOL1,-ABS(nManageFee));			//手续费
		
	}
	else
	{
		obj->AddField(F_LVOL10,req->AdditionalAmount1 - ABS(transfee)); // 出卡值
		obj->AddField(F_LVOL8,ABS(transfee));					//交易金额
		obj->AddField(F_LVOL1,ABS(nManageFee));					//手续费
	}
	obj->AddField(F_LVOL12,transmark);					//交易标志
	obj->AddField(F_SPOST_CODE,date);					//日期
	obj->AddField(F_SPOST_CODE2,time);					//时间
	//obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
	obj->AddField(F_SSTATION0,term_no);					//终端机编号
//	obj->AddField(F_LVOL2,onlineflag);					//联机标志
//	obj->AddField(F_SSTATUS2,tradetype);				//交易类型
	obj->AddField(F_SSTATUS3,seriorigin);				//流水来源
	obj->AddField(F_SSTATUS4,tripcode);					//提示信息码
	obj->AddField(F_SCUST_NO,tac);						//交易验证码
	
	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_ERROR,"连接DRTP失败!!!"));
		return 1;
	}
	// 发送流水
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"发送请求失败!!!"));
		return 1;
	}
	ret = obj->GetReturnCode();
	if(ret)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,ret);
		ACE_DEBUG((LM_ERROR,"采集CPU卡内流水成功,dev[%s],后台返回错误码[%d]",phyid,ret));
		return 1;
	}
	resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);
	ACE_DEBUG((LM_DEBUG,"采集CPU卡内流水成功!!dev[%s]",phyid));
	return 1;
}

// 联机充值/联机充值冲正
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
	// 默认返回一般错误
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
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
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
	obj->AddField(F_SPHONE3,phyid);						//终端序列号
	obj->AddField(F_LVOL5,req->CardNumber);				//交易卡号
	obj->AddField(F_LVOL7,req->TraceOfEW);				//交易次数
	obj->AddField(F_LVOL8,req->Amount);					//交易金额
	obj->AddField(F_LVOL9,req->AdditionalAmount1);		//入卡值
	obj->AddField(F_LVOL4,req->TraceOfPOS);				//pos流水号
	obj->AddField(F_SPOST_CODE,date);					//日期
	obj->AddField(F_SPOST_CODE2,time);					//时间
	//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
	obj->AddField(F_SSTATION0,term_no);					//终端机编号
	obj->AddField(F_LVOL1,req->ManageFee);				//手续费
	obj->AddField(F_LVOL2,onlineflag);					//联机标志
	obj->AddField(F_LVOL12,revflag);				//冲正标志
	obj->AddField(F_SSTATUS2,tradetype);				//交易类型
	obj->AddField(F_SNAME,blkVersion+2);				//黑名单
	obj->AddField(F_LVOL0,tradeseri);					//ED/EP联机交易序号
	obj->AddField(F_SSTATUS3,dlk1);						//密钥版本号
	obj->AddField(F_SSTATUS4,dlk2);						//算法标志
	obj->AddField(F_SSTOCK_CODE,rannum);				//伪随机数
	obj->AddField(F_SSTOCK_CODE2,mac1);					//MAC1
	obj->AddField(F_LVOL3,shopid);						//商户号
	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_INFO,"连接DRTP失败!!!"));
		return 1;
	}
	// 发送流水
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_INFO,"发送充值请求失败!!!"));
		return 1;
	}
	ret = obj->GetReturnCode();
	if(ret)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,ret);
		ACE_DEBUG((LM_ERROR,"联机充值失败!!dev[%s],后台返回错误码[%d]",phyid,ret));
		return 1;
	}
	if(!obj->HasMoreRecord())
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,1);
		ACE_DEBUG((LM_ERROR,"联机充值失败!!dev[%s],后台无返回数据",phyid));
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
		for (i=0;i<4;i++)			//日期
		{
			memset(temp,0,sizeof temp);
			memcpy(temp,data+2*i,2);
			addData3[i] = strtoul(temp,NULL,10);
		}
		for (i=0;i<3;i++)			//时间
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
	ACE_DEBUG((LM_DEBUG,"联机充值成功!!dev[%s]",phyid));
	return 1;
}

// 下载黑名单
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
	// 默认返回一般错误
	this->set_resp_need_mac();
	resp.SetFieldValue(FIELD_RESPONSECODE,2);
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);

	for(i=0;i<14;i++)
	{
		//sprintf(blkVersion+i,"%c",req->AdditionalData1[i]);
		blkVersion[i] = req->AdditionalData1[i];
	}
	ACE_DEBUG((LM_DEBUG,"下载黑名单,pos机上送黑名单号[%s]!",blkVersion));
	ACE_OS::sprintf(phyid,"%.010d",req->TerminalSN);
	
	xutil::StringUtil::BCD2Str(req->PIN,6,term_no);

	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		resp.SetFieldValue(FIELD_RESPONSECODE,20);
		ACE_DEBUG((LM_ERROR,"设备 [%s] 不存在!",phyid));
		return 1;
	}
	node->update_time();
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(obj)
	{
		// 转换物理卡号
		EncodeTermSN(req->TerminalSN,phyid);
		obj->SetRequestHeader(950007);
		obj->AddField(F_LCERT_CODE,KsgGetGateway()->GetConfig()->_gwId);
		obj->AddField(F_SCERT_NO,phyid);				//终端序列号
		//		obj->AddField(F_SHOLDER_TYPE,req->MerchantID);		//HD
		obj->AddField(F_SSTATION0,term_no);				//终端机编号
		obj->AddField(F_SNAME,blkVersion+2);			//黑名单
		obj->AddField(F_LVOL1,9);						//取黑名单条数
		strcpy(old_blkver,blkVersion);
		if(obj->Connect())
		{
			// 连接失败
			ACE_DEBUG((LM_ERROR,"连接DRTP失败，重试!!!"));
			return 1;
		}
		// 发送流水
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
					resp.SetFieldValue(FIELD_RESPONSECODE,RC_SUCCESS);		//无黑名单
					return 1;
				}
				resp.SetFieldValue(FIELD_ADDITIONALDATA1,blkVersion);
				resp.SetFieldValue(FIELD_ADDITIONALDATA3,addData,5*i);
				ACE_DEBUG((LM_DEBUG,"下载黑名单成功!!dev[%s],blkversion[%s]",phyid,blkVersion));
			}
			else
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,ret);
				ACE_DEBUG((LM_ERROR,"下载黑名单失败!!dev[%s],后台返回错误码[%d]",phyid,ret));
			}
		}
	}
	return 1;
}

// 在线通知
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
		ACE_DEBUG((LM_DEBUG,"设备不存在[%s]",phyid));
		return 1;
	}
	else
	{
		// 记录设备状态信息
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
			// 连接失败
			ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
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
				
				ACE_DEBUG((LM_DEBUG,"在线通知成功!!dev[%s],blkversion[%s]",phyid,blkversion));
			}
			else
			{
				resp.SetFieldValue(FIELD_RESPONSECODE,ret);
				ACE_DEBUG((LM_ERROR,"在线通知失败!!dev[%s],后台返回错误码[%d]",phyid,ret));
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
	
	ACE_DEBUG((LM_DEBUG,"在线通知成功!!dev[%s],blkversion[%s]",phyid,blkversion));
	
	return 1;
}

// GCU 在线通知
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
	ACE_DEBUG((LM_INFO,"收到设备[%s]在线通知",phyid));
	KSGDeviceNode* node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(!node)
	{
		ACE_DEBUG((LM_ERROR,"GCU [%s] 不存在!",phyid));
		return -1;
	}
	if(node->GetDeviceType() != "9003")
	{
		ACE_DEBUG((LM_ERROR,"收到设备[%s]在线通知，但是该设备不是GCU！",phyid));
		return -1;
	}
	// 记录设备状态信息
	node->SetState(KSGDeviceNode::dsOnline);
	node->update_time();

	ACE_Time_Value tv = KSGGetTaskTimeoutIntval();
	
	resp.SetFieldValue(FIELD_TERMINALSN,req->TerminalSN);
	resp.SetFieldValue(FIELD_ADDRESS,req->Address);

	MYDATETIMESTRUCT now = HDDEV::HDGetDataTime();
	resp.SetFieldValue(FIELD_DATEANDTIME,(char*)&now,sizeof now);
	resp.SetFieldValue(FIELD_ADDITIONALDATA2,buf,16);

	memcpy(buf,req->AdditionalData2,16);		// 文件版本信息
	memcpy(temp,buf,4);							// 门禁时段版本号
	BUF_2_INT(version,temp);
	sprintf(sversion,"%d",version);
	node->set_param(param_timesect,sversion);

	memcpy(temp,buf+4,4);							// 工作日门禁规则版本号
	BUF_2_INT(version,temp);
	sprintf(sversion,"%d",version);
	node->set_param(param_weekno,sversion);	
	
	return 0;
}

//汇多GCU上送门禁事件
HD_REGISTER_HANDLER(MT_SENDACCESSEVENT1,HDGCURequestHandler);
int HDGCURequestHandler::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer)
{
	ACE_DEBUG((LM_DEBUG,"汇多GCU上送门禁事件"));
	KSGDeviceNode *node;
	char phyid[20];
	EncodeTermSN(req->TerminalSN,phyid);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_ERROR,"汇多设备上送门禁事件，GCU不存在[%s]",phyid));
		return -1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_INFO,"申请DRTP失败，重试!!!"));
		return -1;
	}
	if(obj->Connect())
	{
		ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
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
	obj->AddField(F_LVOL1,device_id);					// 读头号，对应1-4个门
	obj->AddField(F_LVOL2,node->GetDevId());			// GCU ID 号

	int cardno = req->CardNumber;						// 交易卡号
	obj->AddField(F_LVOL0,cardno);			

	char temp[20] = "";
	int transmask = req->AdditionalData2[1];			// GCU 操作结果
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

	ACE_DEBUG((LM_DEBUG,"汇多GCU上送门禁流水,GCU ID[%d],门号[%d],交易卡号[%d],GCU操作结果[%s],日期时间[%s]"
		,node->GetDevId(),device_id,cardno,temp,date_str));

	int retries = 3;
	while(retries-->0)
	{
		if(!obj->SendRequest(5000))
		{
			if(!obj->GetReturnCode())
			{
				ACE_DEBUG((LM_DEBUG,"汇多GCU上送门禁流水到后台成功"));
				return 1;
			}
			else
			{
				ACE_DEBUG((LM_ERROR,"汇多GCU上送门禁流水到后台失败，返回[%d][%s]",
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
	ACE_DEBUG((LM_DEBUG,"电大多媒体取电"));
	char card_phyno[9]="";
	char tmp[2]="";
	KSGDeviceNode *node;
	char phyid[20]="";
	char transmark[8]="";
	EncodeTermSN(req->TerminalSN,phyid);
	node = KsgGetGateway()->GetDeviceManager()->FindDevice(phyid);
	if(node == NULL)
	{
		ACE_DEBUG((LM_ERROR,"电大多媒体取电，设备不存在[%s]",phyid));
		return -1;
	}
	if(node->GetDeviceType() != KSG_JSB_DEV)
	{
		ACE_DEBUG((LM_ERROR,"设备[%s]不是考勤机!",phyid));
		return 1;
	}
	if(node->GetTermId() != req->TerminalID)
	{
		ACE_DEBUG((LM_ERROR,"考勤机机号不正确,上传机号[%d]",req->TerminalID));
		return 1;
	}
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_INFO,"申请DRTP失败，重试!!!"));
		return -1;
	}
	if(obj->Connect())
	{
		ACE_DEBUG((LM_INFO,"连接DRTP失败，重试!!!"));
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

	tmp[0] = req->AdditionalData1[0];					//关闭电源0x02，开启电源0x01
	sprintf(transmark,"%d",HDA_SYSTEMIDOFATT1_1 + tmp[0]);
	obj->AddField(F_SEMP_NO,transmark);

	ACE_DEBUG((LM_DEBUG,"电大多媒体取电,设备 ID[%d],物理卡号[%s],transmark[%s]",node->GetDevId(),card_phyno,transmark));

	////////调试用
	/*
	tmp[0] = 0x01;					// 允许取电		
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
				ACE_DEBUG((LM_DEBUG,"电大多媒体取电,后台成功"));

				if(obj->HasMoreRecord())
				{
					ST_PACK *data = obj->GetNextRecord();
					if(data->lvol1 == 0xFF)
						tmp[0] = 0x01;					// 允许取电						
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
				ACE_DEBUG((LM_ERROR,"电大多媒体取电,后台失败，返回[%d][%s]",
					obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
				break;
			}			
		}
	}

	return -1;
}

} // end of namespace
