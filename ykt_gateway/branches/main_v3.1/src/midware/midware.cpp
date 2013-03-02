#include "ksglobal.h"
#include "midware/midware.h"
#include "hddev/hddef.h"
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
#include "tinyxml.h"
#include "taskdef.h"


namespace MIDSVR{


	



	KSG_ADD_LISTENER_CLASS(KSG_MID_LISTENER,MID_Acceptor);
	MID_Acceptor::MID_Acceptor():_check_handle(NULL),_schd_id(-1)
	{
	}
	MID_Acceptor::~MID_Acceptor()
	{
	}

	int MID_Acceptor::validate_connection(const ACE_Asynch_Accept::Result& result 
		, const ACE_INET_Addr &remote, const ACE_INET_Addr& local)
	{
		// TODO : 增加对客户端连接的合法性检验
		return 0;
	}
	KSG_Proactor_Handler* MID_Acceptor::new_handler()
	{
		ACE_DEBUG((LM_DEBUG,"创建新的连接..."));
		return new MID_Request_Handler(this);
	}

	int MID_Acceptor::start_listen()
	{
		// 端口从后台中读取
		std::string value;
		int port = 12000;
		if(KsgGetSystemParam(MID_SYSPARAM_LISTEN_PORT,value))
		{
			ACE_DEBUG((LM_INFO,"获取侦听端口号失败,使用默认端口[%d]",port));
		}
		else
		{
			port = ACE_OS::atoi(value.c_str());
		}
		if(open(ACE_INET_Addr(port),0,1,ACE_DEFAULT_ASYNCH_BACKLOG
			,1,ACE_Proactor::instance(),0) == -1 )
		{
			ACE_DEBUG((LM_ERROR,"工行网银侦听服务启动失败"));
			return -1;
		}
		_check_handle = new KSG_Proactor_Check_Handler(this);
		_schd_id = ACE_Proactor::instance()->schedule_timer(
			*_check_handle,NULL,ACE_Time_Value::zero,ACE_Time_Value(10));
		ACE_DEBUG((LM_INFO,"侦听线程ThreadId[%u]端口[%d]\n",ACE_OS::thr_self(),port));
		return 0;
	}

	int MID_Acceptor::stop_listen()
	{
		if(_schd_id > -1)
			ACE_Proactor::instance()->cancel_timer(_schd_id);
		if(_check_handle)
			delete _check_handle;
		close();
		return 0;
	}

	#define MID_MTU 1024
	MID_Request_Handler::~MID_Request_Handler()
	{
	}
	MID_Request_Handler::MID_Request_Handler(
		MID_Acceptor* acceptor /* = NULL */)
		:KSG_Proactor_Handler(acceptor),_request_handler(NULL)
	{
	}
	int MID_Request_Handler::on_open(ACE_HANDLE new_handle
		, ACE_Message_Block &message_block)
	{
		ACE_Message_Block *new_mb;
		ACE_NEW_NORETURN(new_mb,ACE_Message_Block(MAX_MESBUF_LEN));
		if(_reader.read(*new_mb,MID_MTU) != 0)
		{
			int err = ACE_OS::last_error();
			ACE_DEBUG((LM_ERROR,"读取连接数据失败![%d][%s]"
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


	int MID_Request_Handler::on_free_handler()
	{
		_request_handler = NULL;
		return 0;
	}
	
	void MID_Request_Handler::handle_write_stream(
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
		//if(_send_count == 0)
		//	free_handler();
		update_io_time();
		reset_request();
	}

	void MID_Request_Handler::reset_request()
	{
		if(_mblk){
		_mblk->reset();
		}
		/*_pack_index = 0;
		if(_reader.read(*_mblk,MID_MTU) != 0)
		{
			int err = ACE_OS::last_error();
			ACE_DEBUG((LM_ERROR,"读取连接数据失败![%d][%s]"
				,err,ACE_OS::strerror(err)));
			free_handler();
			return;
		}*/
	}

	void MID_Request_Handler::handle_read_stream(
		const ACE_Asynch_Read_Stream::Result &result)
	{
		static ACE_CDR::UShort data_len;
		ACE_Message_Block & mb = result.message_block();
		_recv_count--;
		if(!result.success() || result.bytes_transferred() == 0)
		{
			// 认为接收数据失败
			ACE_DEBUG((LM_ERROR,"读取数据失败!!"));
			free_handler();
			return;
		}
		else
		{
			ACE_DEBUG((LM_DEBUG,"开始处理数据..."));
			// 读取数据完成
			update_io_time();
			/*if(_pack_index == 0)
			{
				ACE_InputCDR cdr(&mb);
				cdr >> data_len;
				ACE_DEBUG((LM_DEBUG,"读取第一个包"));
			}
			_pack_index++*/;
			//char *buff=mb.rd_ptr(); 
			
			//ACE_HEX_DUMP((LM_INFO,buff,mb.length()));
			//ACE_DEBUG((LM_INFO,"datalen[%d]",data_len));
			
			//if(mb.length() - MSG_BUF_LEN_HEADER >= data_len )
			//{
				// 读取完成,处理业务
				//ACE_DEBUG((LM_INFO,"处理数据包，长度[%d]",(data_len+MSG_BUF_LEN_HEADER)));
			if( process_request(&mb,data_len+MSG_BUF_LEN_HEADER)<= 0 )
			{
				// 处理失败或者不需要应答
				free_handler();
			}
			return;
			//}
			// 认为数据有问题
			// 继续读取
			/*if(mb.length() >= 65535)
			{
				ACE_DEBUG((LM_ERROR,"数据包长度不合法!!!!"));
				free_handler();
				return;
			}
			//ACE_HEX_DUMP((LM_INFO,mb.rd_ptr(),mb.length()));
			//ACE_DEBUG((LM_INFO,"继续读取数据...len[%d]",(data_len - (mb.length()-MSG_BUF_LEN_HEADER))));
			if( _reader.read(mb,MID_MTU)!=0)
				//,data_len - mb.length() + MSG_BUF_LEN_HEADER) != 0)
			{
				ACE_DEBUG((LM_ERROR,"读取 CCU 数据失败!!"));
				free_handler();
				return;
			}
			_recv_count++;*/
		}
	}

	int MID_Request_Handler::process_request(ACE_Message_Block *mblk,int data_len)
	{
		HD8583STRUCT req;
		HD8583STRUCT resp;
		MIDSVR::MESSAGETYPE msg_type;
		char * buffer = mblk->rd_ptr();
		//int len=mblk->length()+1;
		char xmldata[500]="";
		memcpy(xmldata,(const void *)mblk->rd_ptr(),mblk->length());
		
	
		MID_GetXmlData(xmldata);
		int TrxCode=GetParamIntVal("TrxCode");
		std::string TrxDate=GetParam("TrxDate");
		std::string TrxTime=GetParam("TrxTime");
		switch(TrxCode){
			case 1000:
				msg_type=MID_POLICYCHECK;
				break;
			case 2000:
				msg_type=MID_INCBLC;
				break;
		}
		//ACE_DEBUG((LM_INFO,"业务处理中..."));
		// 数据段长度超过允许范围,忽略请求
		//ACE_HEX_DUMP((LM_DEBUG,buffer,data_len));
		if(0)//UnPackResponseStruct(req,&msg_type,buffer,data_len) != 0)
		{
			ACE_ERROR((LM_ERROR,"数据包不合法"));
			return -1;
		}
		ACE_DEBUG((LM_INFO,"TrxCode[%d]",TrxCode));
		ACE_DEBUG((LM_INFO,"TrxDate[%s]",TrxDate.c_str()));
		ACE_DEBUG((LM_INFO,"TrxTime[%s]",TrxTime.c_str()));
		ACE_DEBUG((LM_INFO,"xmldata[%s]",xmldata));
		try
		{
			_request_handler = MIDProcessUnits::instance()->Create(msg_type);
			if(_request_handler)
			{
				_request_handler->_remote_addr = this->_remote_addr;
				_request_handler->set_resp_need_mac(false);
				resp.Init();
				int result = _request_handler->DoResponse(req,resp,handle(),_params);
				int pos;
				if(result > 0)
				{
					// send back
					mblk->reset();
					
					//char trxCode[6]="01001";

					std::string response;
					response=std::string(xmldata);
					pos=response.find("<Version>")+9;
					response.replace(pos,10,"VXYKCZ1.0",9);
					pos=response.find("/TrxTime>");
					pos=pos+9;
					response.insert(pos,std::string("<RetCode>")+GetParam("RetCode")+std::string("</RetCode><ErrMsg>                    </ErrMsg>"));
					pos=response.find("/TrxSerNo>")+10;
					response.insert(pos,std::string("<HostTrxId>0               </HostTrxId>"));
					pos=response.find("<TrxCode>")+9;
					switch(msg_type){
						case MID_POLICYCHECK:
							
							//trxCode[6]="01001";
							
							//pos1=response.find("</TrxCode>");
							response.replace(pos,5,"01001",5);
							break;
						case MID_INCBLC:
							response.replace(pos,5,"02001",5);
							break;
					}
					ACE_OS::memcpy(mblk->wr_ptr(),response.c_str(),ACE_OS::strlen(response.c_str()));
					mblk->wr_ptr(ACE_OS::strlen(response.c_str())); 

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
					/*buffer = mblk->wr_ptr();
					len = (int)PackRequestStruct(resp,msg_type,buffer,mblk->size()
						,_request_handler->resp_need_mac());
					mblk->wr_ptr(len);
					ACE_HEX_DUMP((LM_DEBUG,buffer,mblk->length()));
					ACE_DEBUG((LM_DEBUG,"数据包长度[%d]",mblk->length()));
					
					_send_count++;*/
					_params.clear();
					return 0;
				}
				else if(result == 0)
				{
					// OK
					mblk->reset();
					int pos;
					
					std::string response;
					response=std::string(xmldata);
					response=std::string(xmldata);
					pos=response.find("<Version>")+9;
					response.replace(pos,10,"VXYKCZ1.0",9);
					pos=response.find("/TrxTime>");
					pos=pos+9;
					response.insert(pos,std::string("<RetCode>00000</RetCode><ErrMsg>                    </ErrMsg>"));
					
					
					pos=response.find("<TrxCode>")+9;
					switch(msg_type){
						case MID_POLICYCHECK:
							
							//trxCode[6]="01001";
							
							//pos1=response.find("</TrxCode>");
							response.replace(pos,5,"01001",5);
							break;
						case MID_INCBLC:
							response.replace(pos,5,"02001",5);
							pos=response.find("<TrxSerNo>")+10;
							response.insert(pos,std::string("<HostTrxId>")+GetParam("HostTrxId")+std::string("</HostTrxId>"));
							break;
					}
					//mblk->copy(xmldata);
					ACE_OS::memcpy(mblk->wr_ptr(),response.c_str(),ACE_OS::strlen(response.c_str()));
					mblk->wr_ptr(ACE_OS::strlen(response.c_str())); 
					//mblk->wr_ptr(ACE_OS::strlen(xmldata));
					//rspon = mblk->wr_ptr();
					//memcpy(rspon,xmldata,strlen(xmldata));
					if(_writer.write(*mblk,mblk->length()) !=0 )
					{
						ACE_DEBUG((LM_ERROR,"发送应答包失败"));
						return -1;
					}
					ACE_DEBUG((LM_INFO,"~~~处理成功"));
					//free_handler();
					_params.clear();
					return 0;
				}
				else
				{
					// error
					_params.clear();
					ACE_DEBUG((LM_ERROR,"处理请求失败，返回码[%d]",result));
				}
			}
			else
			{
				_params.clear();
				ACE_ERROR((LM_ERROR,"不能处理请求代码[%c]",msg_type));
			}	
		}
		catch(...)
		{
			// 捕获所有的异常
			_params.clear();
			ACE_ERROR((LM_ERROR,"处理请求异常,请求代码[%02x]",msg_type));
		}	
		return -1;
	}
///////////



void MID_Request_Handler::PutParam(const std::string& key,const std::string& val)
{
	KeyValueMap::iterator i = _params.find(key);
	if( i == _params.end() )
	{
		_params.insert(KeyValueMap::value_type(key,val));
		
		return;
	}
	//_params.insert(KeyValueMap::value_type)
	//i->second = val;
}

std::string MID_Request_Handler::GetParam(const std::string& key) const
throw(KeyNotFoundException)
{
	KeyValueMap::const_iterator i = _params.find(key);
	if(i == _params.end())
	{
		throw KeyNotFoundException();
	}
	return i->second;
}

int MID_Request_Handler::GetParamIntVal(const std::string& key) const
throw(KeyNotFoundException)
{
	try
	{
		std::string val = GetParam(key);
		return ACE_OS::atoi(val.c_str());
	}
	catch(KeyNotFoundException& e)
	{
		throw e;
	}
}

int MID_Request_Handler::MID_GetXmlData(char * data){
	TiXmlDocument doc;
	doc.Parse(data);
	
	TiXmlNode* root = doc.FirstChild("ROOT");
	if(!root){
		ACE_ERROR((LM_ERROR,"数据不合法"));

		return -1;
	}
	TiXmlNode* elem = root->FirstChild();
	while(elem!=NULL)
	{
		//elem->f
		TiXmlNode* t = elem->FirstChild();
		if(t)
			PutParam(elem->Value(),t->Value());
		else
			PutParam(elem->Value(),"");
		elem = elem->NextSibling();
	}
	return 0;

	}

std::string MIDResponseHandler::GetParam(const std::string& key,const KeyValueMap map) const
throw(KeyNotFoundException)
{
	KeyValueMap::const_iterator i = map.find(key);
	if(i == map.end())
	{
		throw KeyNotFoundException();
	}
	return i->second;
}

int MIDResponseHandler::GetParamIntVal(const std::string& key,const KeyValueMap map) const
throw(KeyNotFoundException)
{
	try
	{
		std::string val = GetParam(key,map);
		return ACE_OS::atoi(val.c_str());
	}
	catch(KeyNotFoundException& e)
	{
		throw e;
	}
}

MID_REGISTER_HANDLER(MID_POLICYCHECK,Mid_Policy_Check);
int Mid_Policy_Check::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer,KeyValueMap &map){
	
	//char *Version;
	std::string Version,TrxDate,TrxTime;
	
	Version=GetParam("StaffId",map);
	TrxDate=GetParam("UnivercityId",map);
	/*TrxTime=GetParam("TrxTime",map);*/
	ACE_DEBUG((LM_INFO,"学号%s\n",Version.c_str()));
	ACE_DEBUG((LM_INFO,"学校代码%s\n",TrxDate.c_str()));
	/*ACE_DEBUG((LM_INFO,"鉴权处理成功%s\n",TrxTime));*/
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"KsgGetDrtpPool失败"));
		return 1;
	}
	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_ERROR,"连接DRTP失败"));
		return 1;
	}
	obj->SetRequestHeader(849008);
	
	obj->AddField(F_LVOL0,0);
	//obj->AddField(F_LVOL1,node->GetDevId());
	obj->AddField(F_SCUST_AUTH,GetParam("StaffId",map).c_str());
	obj->AddField(F_SCUST_NO,GetParam("UnivercityId",map).c_str());
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"SendRequest失败，重试!!!"));
		return 1;
	}
	if(obj->GetReturnCode())
	{
		char code[6];
		map.insert(KeyValueMap::value_type(std::string("RetCode"),ACE_OS::itoa(obj->GetReturnCode(),code,5)));
		ACE_DEBUG((LM_ERROR,"鉴权请求失败,错误码[%d][%s]"
			,obj->GetReturnCode(),obj->GetReturnMsg().c_str()));
		return 1;
	}
	if(obj->HasMoreRecord())
	{
		ST_PACK *data = obj->GetNextRecord();
		
	}
	return 0;
}

MID_REGISTER_HANDLER(MID_INCBLC,Mid_Increase_Balance);
int Mid_Increase_Balance::DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer,KeyValueMap &map)
{	
	//std::string Version,TrxDate,TrxTime;
	//TrxDate=GetParam("TrxDate",map);
	//ACE_DEBUG((LM_INFO,"充值处理成功%s",TrxDate.c_str()));
	DRTPPoolType::SmartObject obj = KsgGetDrtpPool()->Alloc();
	if(!obj)
	{
		ACE_DEBUG((LM_ERROR,"KsgGetDrtpPool失败"));
		return 1;
	}
	if(obj->Connect())
	{
		// 连接失败
		ACE_DEBUG((LM_ERROR,"连接DRTP失败"));
		return 1;
	}
	obj->SetRequestHeader(849009);
	obj->AddField(F_SCUST_AUTH,GetParam("StaffId",map).c_str());
	obj->AddField(F_SCUST_NO,GetParam("UnivercityId",map).c_str());
	obj->AddField(F_SDATE0,GetParam("TrxDate",map).c_str());
	obj->AddField(F_STIME0,GetParam("TrxTime",map).c_str());
	double d = 0;
	convertFromString(d,GetParam("Amount",map));
	d=d/100.0;
	obj->AddField(F_DAMT0,d);
	obj->AddField(F_LVOL2,GetParamIntVal("TrxSerNo",map));
	obj->AddField(F_SCUST_NO2,"system");
	obj->AddField(F_LVOL3,0);
	if(obj->SendRequest(1000))
	{
		ACE_DEBUG((LM_ERROR,"连接DRTP失败，重试!!!"));
		return 1;
	}
	if(obj->GetReturnCode())
	{
		char code[6];
		map.insert(KeyValueMap::value_type(std::string("RetCode"),ACE_OS::itoa(obj->GetReturnCode(),code,5)));
		ACE_DEBUG((LM_ERROR,"充值请求失败,错误码[%d][%s]"
			,obj->GetReturnCode(),obj->GetReturnMsg().c_str()));

		return 1;
	}
	if(obj->HasMoreRecord())
	{
		ST_PACK *data = obj->GetNextRecord();
		char code[6];
		int HostTrxId=data->lvol1;
		double Amount=data->damt0;
		map.insert(KeyValueMap::value_type(std::string("HostTrxId"),ACE_OS::itoa(HostTrxId,code,16)));
		map.insert(KeyValueMap::value_type(std::string("Amount"),ACE_OS::itoa((int)KSGMathUtil::D4U5(Amount*100),code,5)));
	}
	return 0; 
}

}