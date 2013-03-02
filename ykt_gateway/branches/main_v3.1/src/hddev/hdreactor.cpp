#include "ksglobal.h"
#include "reactor_def.h"
#include "hddev/hdsvr.h"
#include "ksgateway.h"
#include "bit_endian.h"
#include "F8583.h"
#include "hddev/hdreactor.h"
#include "pubfunc.h"
#include <ace/CDR_Stream.h>

DECLARE_NAMESPACE_BEGIN(HDDEV)

//////////////////////////////////////////////////////////////////////////
HD_Service_Request  g_global_hd_request;

int HD_Service_Request::process_request(void *arg,long timeout )
{
	int ret;
	KSG_WORK_SVR_HANDLER * hd = reinterpret_cast<KSG_WORK_SVR_HANDLER*>(arg);
	if(hd==NULL)
		return -1;
	try
	{
		ret = do_request(hd);
		return ret;
	}
	catch (...)
	{
		ACE_DEBUG((LM_ERROR,"处理汇多业务请求失败！"));
		return -1;
	}
}
int HD_Service_Request::do_request(KSG_WORK_SVR_HANDLER *handle)
{
	HD8583STRUCT req;
	HD8583STRUCT resp;
	MESSAGETYPE msg_type;
	ACE_Message_Block *mblk = handle->mblk_;
	ACE_SOCK_Stream peer;
	ACE_Message_Block *resp_buf;
	peer.set_handle(handle->handle_);
	int data_len = mblk->length();
	char * buffer = mblk->rd_ptr();
	int len = 0;
	//ACE_DEBUG((LM_INFO,"业务处理中..."));
	ACE_Time_Value begin = ACE_OS::gettimeofday();
	if(UnPackResponseStruct(req,&msg_type,buffer,data_len) != 0)
	{
		short buflen=0;
		BUF_2_SHORT_LE(buflen,buffer);
		ACE_ERROR((LM_ERROR,"数据包不合法,len[%d]实际长度[%d]",data_len-2,buflen));
		return -1;
	}
	ACE_HEX_DUMP((LM_TRACE,mblk->rd_ptr(),mblk->length()));
	try
	{
		ACE_DEBUG((LM_DEBUG,"业务处理中...[%X]",msg_type));
		resp_buf = NULL;
		_request_handler = HDCCUProcessUnits::instance()->Create(msg_type);
		if(_request_handler)
		{
			peer.get_remote_addr(_request_handler->_remote_addr);
			_request_handler->set_resp_need_mac(false);
			resp.Init();
			int result = _request_handler->DoResponse(req,resp,handle->handle_);
			ACE_DEBUG((LM_DEBUG,"业务处理完成[%X]",msg_type));
			if(result > 0)
			{
				//ACE_NEW_RETURN(resp_buf,ACE_Message_Block(1024),-1);				
				resp_buf = new ACE_Message_Block(1024);
				if(resp_buf == NULL)
				{
					ACE_DEBUG((LM_ERROR,"msgtype[%X]内存分配失败",msg_type));
					return -1;
				}
				// send back
				len = (int)PackRequestStruct(resp,msg_type,resp_buf->wr_ptr(),resp_buf->capacity()
					,_request_handler->resp_need_mac());
				if(len > 0)
					resp_buf->wr_ptr(len);
				ACE_DEBUG((LM_TRACE,"数据包长度[%d]",len));
				//ACE_Time_Value tv(0,100 * 1000);
				ACE_Time_Value tv(2);
				if(len == 0)
				{
					ACE_DEBUG((LM_ERROR,"应答包长度为0,不发送"));
					result = -1;
				}
				else if(peer.send_n(resp_buf,&tv) <=0 )
				{
					ACE_DEBUG((LM_ERROR,"发送应答包失败"));
					result = -1;
				}
				else
				{
					result = 1;
				}
				if(resp_buf->length() > 0)
                    ACE_HEX_DUMP((LM_TRACE,resp_buf->rd_ptr(),resp_buf->length()));
				resp_buf->release();
				resp_buf = NULL;
				ACE_Time_Value end = ACE_OS::gettimeofday();
				end -= begin;
				ACE_UINT64 span;
				end.to_usec(span);
				ACE_DEBUG((LM_INFO,"请求码[%X]处理时间[%uus]",msg_type,(ACE_UINT32)span));
				return result;
				
			}
			else if(result == 0)
			{
				// OK
				ACE_DEBUG((LM_TRACE,"处理成功"));
				return 0;
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
	catch(NullPointerException &ex)
	{
		ACE_ERROR((LM_ERROR,"请求通讯平台连接异常[%02X]",msg_type));
	}
	catch(...)
	{
		// 捕获所有的异常
		ACE_ERROR((LM_ERROR,"处理请求异常,请求代码[%02x]",msg_type));
	}
	if(resp_buf)
		resp_buf->release();
	return -1;
}
//////////////////////////////////////////////////////////////////////////

int HD_Service_Handler::process_request(long timeout)
{
	return -1;
}

int HD_Service_Handler::do_request(ACE_Message_Block *mblk,int data_len)
{
	return -1;
}
int HD_Service_Handler::recv_data(ACE_Message_Block *&blk)
{
	//
	ACE_Time_Value tv(0,200);
	
	static ACE_CDR::UShort data_len;
	size_t recv_len = 0;
	ssize_t recv_head = 0;
	int ret;
	int length = HDResponseHandler::MSG_BUF_LEN_HEADER;
	if(blk == NULL)
	{
		ACE_NEW_RETURN(blk,ACE_Message_Block(HDResponseHandler::MAX_MESBUF_LEN),-1);
		//ACE_DEBUG((LM_INFO,"申请包数据内存"));
		recv_head = this->peer().recv_n(blk->wr_ptr(),length);
		if( recv_head != length)
		{
			ACE_INET_Addr peer_addr;
			this->peer().get_remote_addr(peer_addr);
			ACE_DEBUG((LM_TRACE,"接收数据包包头信息错误...[%s:%d][%d]err[%d]idx[%d]",
				peer_addr.get_host_addr(),peer_addr.get_port_number(),recv_head,
				ACE_OS::last_error(),get_index()));

			return -1;
		}
		blk->wr_ptr(length);

		ACE_InputCDR cdr(blk->rd_ptr(),blk->length());
		cdr>>data_len;

		if(data_len > blk->size() - length)
		{
			ACE_DEBUG((LM_ERROR,"接收数据包长度太长,[%d]bytes",data_len));
			return -1;
		}
		recv_len = data_len - (blk->length()-HDResponseHandler::MSG_BUF_LEN_HEADER);
		ret = recv_from_client(blk,&recv_len);
	}
	else
	{
		ACE_InputCDR cdr(blk->rd_ptr(),blk->length());
		cdr>>data_len;
		recv_len = data_len - (blk->length()-HDResponseHandler::MSG_BUF_LEN_HEADER);
		ret = recv_from_client(blk,&recv_len);
	}
	if(ret<0)
		return -1;
	if( recv_len > 0)
	{
		if(recv_len != 0 &&
			blk->length() - HDResponseHandler::MSG_BUF_LEN_HEADER < data_len)
		{
			// 包不完整,继续读取
			ACE_DEBUG((LM_TRACE,"继续读取后续数据包...header[%d],data[%d],size[%d]"
				,data_len,blk->length(),blk->size()));
			return 0;
		}
		else 
		{
			ACE_DEBUG((LM_TRACE,"接收到完成数据包"));
			return 1;// 完整数据包
		}
	
	}
	else if(recv_len == 0)
	{
		if(ret)
			return -1;
		ACE_DEBUG((LM_INFO,"未读取到数据！"));
		return 0;
	}
	else
		return -1; 
}

int HD_Service_Handler::recv_from_client(ACE_Message_Block *buf,size_t *recv_len)
{
	const size_t max_len = 1040;
	ssize_t l;
	size_t total = 0;
	size_t max_size = buf->size() - buf->length();
	ACE_Time_Value tv(0);
	ACE_INET_Addr peer_addr;
	this->peer().get_remote_addr(peer_addr);
	
	//if(*recv_len < max_size)
	//	max_size = *recv_len;
	l = peer().recv_n(buf->wr_ptr(),max_size,&tv,&total);
	if(l<=0)
	{
		if(l == -1 && ACE_OS::last_error() == ETIME)
		{
		}
		else
		{
			ACE_DEBUG((LM_ERROR,"对方关闭了连接ip[%s]",peer_addr.get_host_addr()));
			return -1;
		}
	}
	if(total > 0)
	{
		buf->wr_ptr(total);
		ACE_DEBUG((LM_TRACE,"读取SOCKET...data[%d],size[%d]",buf->length(),buf->size()));
		*recv_len = total;
		return 0;
	}
	else
	{
		ACE_DEBUG((LM_TRACE,"接收汇多数据错误,ip[%s]",peer_addr.get_host_addr()));
		return -1;
	}
	return -1;
}

int HD_Service_Handler::handle_input(ACE_HANDLE fd )
{
	return KSG_Service_Handler::handle_input(fd);
}
//////////////////////////////////////////////////////////////////////////
//
#ifndef USE_PROACTOR
KSG_ADD_LISTENER_CLASS(KSG_HD_CCU_LISTENER,HD_Service_Acceptor);
#endif // USE_PROACTOR

KSG_Service_Handler* HD_Service_Acceptor::new_handle()
{
	KSG_Service_Handler * hd = NULL;
	try
	{
		hd = new HD_Service_Handler(this->reactor());
	}
	catch (...)
	{
		ACE_DEBUG((LM_EMERGENCY,"不能创建新的连接请求！！！"));
	}
	return hd;
}
int HD_Service_Acceptor::free_handle(KSG_Service_Handler *handle)
{
	delete handle;
	return 0;
}

int HD_Service_Acceptor::start_listen()
{
	// 端口从后台中读取1
	std::string value;
	int port = 6001;
	if(KsgGetSystemParam(HD_SYSPARAM_LISTEN_PORT,value))
	{
		ACE_DEBUG((LM_TRACE,"无法获取CCU侦听端口号,使用默认端口[%d]",port));
	}
	else
	{
		port = ACE_OS::atoi(value.c_str());
	}
	if(open(ACE_INET_Addr(port)) == -1 )
	{
		ACE_DEBUG((LM_ERROR,"汇多CCU侦听服务启动失败\n"));
		return -1;
	}
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

int HD_Service_Acceptor::stop_listen()
{
	handle_close();
	return 0;
}

DECLARE_NAMESPACE_END(HDDEV);
