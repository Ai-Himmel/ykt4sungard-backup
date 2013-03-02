#ifndef _KSG_MID_SVR_H_
#define _KSG_MID_SVR_H_


#include "taskcode.h"
#include "F8583.h"
#include "factory.h"
#include "device.h"
#include "midware/middef.h"
#include "hddev/hddef.h"
#include "proactor_def.h"
#include "xutils/xsingleton.h"
#include "thread.h"
#include <ace/OS.h>
#include <ace/SOCK_Stream.h>
#include <ace/Svc_Handler.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Reactor.h>
#include <ace/Null_Mutex.h>
#include <ace/Thread_Mutex.h>
#include <ace/OS_NS_Thread.h>
#include <ace/Singleton.h>
#include <curl/curl.h>
#include <set>
#define _DEFAULT_MAX_LEN 1024 << 0



namespace MIDSVR{
	typedef std::map<std::string,std::string> KeyValueMap;
	int MID_GetXmlData(ACE_Message_Block *mblk,char * data);

	class MID_Acceptor : public KSG_Proactor_Acceptor
	{
	public:
		DECLARE_FACTORY_CREATOR(MID_Acceptor)
		MID_Acceptor();
		virtual ~MID_Acceptor();
		virtual int validate_connection(const ACE_Asynch_Accept::Result& result
			, const ACE_INET_Addr &remote, const ACE_INET_Addr& local);
		virtual int start_listen();
		virtual int stop_listen();
	protected:
		virtual KSG_Proactor_Handler* new_handler();
		KSG_Proactor_Check_Handler *_check_handle;
		long _schd_id;
	};
	class MIDResponseHandler;
	class MID_Request_Handler : public KSG_Proactor_Handler
	{
	public:
		MID_Request_Handler(MID_Acceptor* acceptor = NULL);
		virtual ~MID_Request_Handler();
		
	protected:
		enum { MAX_MESBUF_LEN = _DEFAULT_MAX_LEN , MSG_BUF_LEN_HEADER = 2};
		MIDResponseHandler *_request_handler;
		virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
		virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);
		virtual int on_open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);
		int process_request(ACE_Message_Block *mblk,int data_len);
		virtual int on_free_handler();
		int _pack_index;
		void reset_request();
		int MID_GetXmlData(char * data);
		std::string WIN32_CALL_CONVERTION GetParam(const std::string& key) const throw(KeyNotFoundException);
		int WIN32_CALL_CONVERTION GetParamIntVal(const std::string& key) const throw(KeyNotFoundException);
	private:
		//<! 参数表类型
		
		KeyValueMap  _params;
		void PutParam(const std::string& key,const std::string& val);
	};

	class MIDResponseHandler
	{
	public:
		MIDResponseHandler(MESSAGETYPE code):_requestCode(code),_resp_need_mac(false)
		{}
		virtual ~MIDResponseHandler(){}
		virtual int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer,KeyValueMap &map) = 0;
		virtual int DoFinish(ACE_HANDLE peer) {return 0;}
		std::string WIN32_CALL_CONVERTION GetParam(const std::string& key,KeyValueMap map) const throw(KeyNotFoundException);
		int WIN32_CALL_CONVERTION GetParamIntVal(const std::string& key,KeyValueMap map) const throw(KeyNotFoundException);
		void convertFromString(double &value, const std::string &s) {
		  std::stringstream ss(s);
		  ss >> value;
		}





		MESSAGETYPE GetRequestCode() const
		{
			return _requestCode;
		}
		void set_resp_need_mac(bool need = true)
		{
			_resp_need_mac = need;
		}
		bool resp_need_mac() const
		{
			return _resp_need_mac;
		}
	private:
		MESSAGETYPE _requestCode;
		bool _resp_need_mac;
	protected:
		ACE_INET_Addr _remote_addr;
		friend class MID_Request_Handler;
	};
	

	class Mid_Policy_Check : public MIDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(Mid_Policy_Check)
	public:
		Mid_Policy_Check():MIDResponseHandler(MID_POLICYCHECK){}
		~Mid_Policy_Check(){}


		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer,KeyValueMap &map);
	};

	class Mid_Increase_Balance : public MIDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(Mid_Increase_Balance)
	public:
		Mid_Increase_Balance():MIDResponseHandler(MID_INCBLC){}
		~Mid_Increase_Balance(){}


		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer,KeyValueMap &map);
	};

	class MIDResponseHandler;
	//typedef xutil::SingletonHolder<AbstractObject<MESSAGETYPE,HDResponseHandler>, MTTheadModel> HDCCUProcessUnits;
	typedef ACE_Singleton<AbstractObject<MESSAGETYPE,MIDResponseHandler>,ACE_Thread_Mutex> MIDProcessUnits;

	inline bool _RegisterMIDResponseHandler(MESSAGETYPE id,AbstractObject<int,MIDResponseHandler>::CreatorType cr)
		{
			MIDProcessUnits::instance()->Register(id,cr);
			return true;
		}

	#define MID_REGISTER_HANDLER(id,clazz) \
		bool clazz::clazz##Registered = _RegisterMIDResponseHandler(id,\
		reinterpret_cast<AbstractObject<int,MIDResponseHandler>::CreatorType>(clazz::clazz##CreateObject))
	

}
#endif