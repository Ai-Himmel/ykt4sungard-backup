#ifndef _KSG_HD_SVR_H_
#define _KSG_HD_SVR_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "taskcode.h"
#include "F8583.h"
#include "factory.h"
#include "device.h"
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

namespace HDDEV
{
	extern MYDATETIMESTRUCT HDGetDataTime();
	unsigned long DecodeTermSN(const char * sn);
	void EncodeTermSN(unsigned long termid,char* sn);

	unsigned long SN2LongNum(const char* sn);
	void SN2Char(unsigned long termid,char* sn);

	unsigned long EncodeVersionNum(const char* version);
	int DecodeVersionNum(unsigned long num,char* ver);

	size_t PackRequestStruct(HD8583STRUCT& req,MESSAGETYPE msg_type
		,void* buf,size_t maxlen,bool with_crc = false);
	int UnPackResponseStruct(HD8583STRUCT& resp,MESSAGETYPE* msg_type,
		void* buf,size_t buflen);

	int HDSendBuffer(ACE_HANDLE handler,char* buf,size_t buflen
		,ACE_Time_Value* timeout);
	int HDRecvBuffer(ACE_HANDLE handler,char* buf,size_t maxbuf
		,ACE_Time_Value* timeout);

	int HDParsePosRecord(BYTE* buf,TRADERECORDSTRUCT* trade);

	int HDConvertCardPhyNo(unsigned int dec_no,char phy_no[9]);

	unsigned short GetDeviceAddress(KSGDeviceNode* node);
	
	//! CCU 侦听服务的 Handler
	class HDCCUSvrHandler : public ACE_Svc_Handler<ACE_SOCK_STREAM,ACE_MT_SYNCH>
	{
	private:
		static const int MAX_MESBUF_LEN = _DEFAULT_MAX_LEN;
		ACE_Time_Value _max_timeout_sec;
		int _close_time;
		ACE_Thread_Mutex _mutex;
		void dec_close_time();
		void delete_self(ACE_HANDLE handler);
	public:
		HDCCUSvrHandler();
		virtual int open(void*);
		virtual int handle_input(ACE_HANDLE fd);
		virtual int handle_timeout(const ACE_Time_Value &time, const void *);
		virtual int handle_close(ACE_HANDLE handler, ACE_Reactor_Mask mask);
		virtual int svc();
		//virtual int close(u_long flags);
	protected:
		virtual ~HDCCUSvrHandler();
	};

	//////////////////////////////////////////////////////////////////
	// 定义 ACE Proactor Framework 使用的 Handler
	class HD_CCU_Request_Handler;
	//! CCU asynchronize acceptor
	class HD_CCU_Acceptor : public KSG_Proactor_Acceptor
	{
	public:
		DECLARE_FACTORY_CREATOR(HD_CCU_Acceptor)
		HD_CCU_Acceptor();
		virtual ~HD_CCU_Acceptor();
		virtual int validate_connection(const ACE_Asynch_Accept::Result& result
			, const ACE_INET_Addr &remote, const ACE_INET_Addr& local);
		virtual int start_listen();
		virtual int stop_listen();
	protected:
		virtual KSG_Proactor_Handler* new_handler();
		KSG_Proactor_Check_Handler *_check_handle;
		long _schd_id;
	};
	//! CCU asynchronize handler
	class HDResponseHandler;
	class HD_CCU_Request_Handler : public KSG_Proactor_Handler
	{
	public:
		HD_CCU_Request_Handler(HD_CCU_Acceptor* acceptor = NULL);
		virtual ~HD_CCU_Request_Handler();
		
	protected:
		enum { MAX_MESBUF_LEN = _DEFAULT_MAX_LEN , MSG_BUF_LEN_HEADER = 2};
		HDResponseHandler *_request_handler;
		virtual void handle_read_stream(const ACE_Asynch_Read_Stream::Result &result);
		virtual void handle_write_stream(const ACE_Asynch_Write_Stream::Result &result);
		virtual int on_open(ACE_HANDLE new_handle, ACE_Message_Block &message_block);
		int process_request(ACE_Message_Block *mblk,int data_len);
		virtual int on_free_handler();
		int _pack_index;
		void reset_request();
	};

	///////////////////////////////////////////////////////////////////
	/// for reactor framework
	typedef ACE_Acceptor<HDCCUSvrHandler,ACE_SOCK_ACCEPTOR> CCUSvrAcceptor;
	typedef ACE_Singleton<ACE_Reactor,ACE_Null_Mutex> REACTOR;

	class HDResponseHandler;
	//typedef xutil::SingletonHolder<AbstractObject<MESSAGETYPE,HDResponseHandler>, MTTheadModel> HDCCUProcessUnits;
	typedef ACE_Singleton<AbstractObject<MESSAGETYPE,HDResponseHandler>,ACE_Thread_Mutex> HDCCUProcessUnits;
	//! 汇多业务处理接口
	class HDResponseHandler
	{
	public:
		HDResponseHandler(MESSAGETYPE code):_requestCode(code),_resp_need_mac(false)
		{}
		virtual ~HDResponseHandler(){}
		virtual int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer) = 0;
		virtual int DoFinish(ACE_HANDLE peer) {return 0;}
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
		friend class HD_CCU_Request_Handler;
	};

	// 回响测试
	class HDReechoHandler1 : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDReechoHandler1)
	public:
		HDReechoHandler1():HDResponseHandler(MT_REECHO1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! 充值机授权卡签到
	class HDEnrollHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDEnrollHandler)
	public:
		HDEnrollHandler():HDResponseHandler(MT_SIGNIN1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! 请求工作密钥
	class HDInitKeyHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDInitKeyHandler)
	public:
		HDInitKeyHandler():HDResponseHandler(MT_INITKEY1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! 请求终端消费记录
	class HDQueryPosTrade : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDQueryPosTrade)
	public:
		HDQueryPosTrade():HDResponseHandler(MT_QUERYHISTORYTRADE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! 终端在线通知
	class HDOnlineNotice : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDOnlineNotice)
	public:
		HDOnlineNotice():HDResponseHandler(MT_ONLINENOTICE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! POS充值请求
	class HDAddNotice : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDAddNotice)
	public:
		HDAddNotice():HDResponseHandler(MT_DEPOSIT1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! POS充值失败冲正
	class HDAddCancelNotice : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDAddCancelNotice)
	public:
		HDAddCancelNotice():HDResponseHandler(MT_ROLLBACK1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! POS领取补助
	class HDCheckSubsidyNotice : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDCheckSubsidyNotice)
	public:
		HDCheckSubsidyNotice():HDResponseHandler(MT_ALLOWANCE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! TCP POS 机消费
	class HDPOS_Consume : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDPOS_Consume)
	public:
		HDPOS_Consume():HDResponseHandler(MT_TRADE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! tcp POS 消费撤销
	class HDPOS_Consume_Cancel : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDPOS_Consume_Cancel)
	public:
		HDPOS_Consume_Cancel():HDResponseHandler(MT_CANCELTRADE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! TCP POS 机脱机流水批上送
	class HDPOS_Consume_Upload : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDPOS_Consume_Upload)
	public:
		HDPOS_Consume_Upload():HDResponseHandler(MT_BATCHSENDRECORD1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! POS 机更新黑名单
	class HDPOS_Check_Blackcard : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDPOS_Check_Blackcard)
	public:
		HDPOS_Check_Blackcard():HDResponseHandler(MT_UPDATELIST1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! 读取并上传消费流水记录
	class HDRecordFileReader 
	{
	public:
		static int test_lock_ccu(int devid);
		static int lock_ccu(int devid);
		static int free_ccu_lock(int devid);
		typedef enum {POS_RECORD = 1,ATTENDENT_RECORD} HD_RECORD_TYPE;

	private:
		std::string _filepath;
		int _device_id;
		ACE_HANDLE _file_handler;
		int ReadPosRecord();
		int DoReadRecordFile();
		int DoSaveRecord(BYTE *buf);
		size_t LoadIndex();
		int SaveIndex(size_t index);
		//////////////////////////////////////////////////////////////////////////
		// static 
		static ACE_Thread_Mutex _s_file_lock_mutex;
		typedef std::set<int> CCU_DEVICE_LOCK_TYPE;
		static CCU_DEVICE_LOCK_TYPE _s_device_lock;
		HD_RECORD_TYPE _record_type;
	public:
		static const int MAX_RECORD_BUF_LEN = 100;
		static const int RECORD_BUF_LEN = 47;
		static const int ARECORD_BUF_LEN = 14;
		HDRecordFileReader(const std::string& filepath,int device_id,HD_RECORD_TYPE rtype = POS_RECORD)
			:_filepath(filepath),_file_handler(ACE_INVALID_HANDLE),_device_id(device_id),_record_type(rtype)
		{}
		~HDRecordFileReader();
		int ReadFile();
		int SavePosRecord(BYTE* buf);
		int SaveTradeRecord(TRADERECORDSTRUCT *trade,int crc_status = 0);

		int SaveAttendRecord(ATTENDRECORDSTRUCT *record);
		int SaveAttendBuffer(BYTE *buf);
	};
	class HDRecordFileReader_Lock_Guard 
	{
	private:
		int _devid;
		int _is_owner;
	public:
		HDRecordFileReader_Lock_Guard(int devid);
		~HDRecordFileReader_Lock_Guard();
		int is_owner();
	};

	class HDDownloadBlkCard 
	{
	public:
		HDDownloadBlkCard()
		{}
		~HDDownloadBlkCard()
		{}
		int DownloadBlackCard(BYTE addflag,KSGDeviceNode* node,KSGDeviceNode::Task* task);
	};
	//! CCU在线通知
	class HDCCUNoticeHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDCCUNoticeHandler)
	private:
		static const int RECORD_SECT_LEN = 6;
		int CheckFile(int fileid,BYTE* data,const std::string& devid,std::string& filepath);
		int CheckDownloadPath(const std::string& devid,std::string& filepath);
		void ClearCCUFile(int fileid);
		int DoFile(int fileid,BYTE* filebuf,KSGDeviceNode* node
			,HD8583STRUCT& req,std::string& filepath);
		struct record_file
		{
			const char * file_path;
			FILE * filp;
		};
	public:
		static int ftp_writer(void *buffer, size_t size, size_t nmemb, void *stream);
		static int ftp_curl_debug(CURL * curl, curl_infotype info, char * msg, size_t len, void * param);
		HDCCUNoticeHandler():HDResponseHandler(MT_CCUONLINENOTICE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	
	//! 考勤机上送记录
	class HDKQRequestHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDKQRequestHandler)
	public:
		HDKQRequestHandler():HDResponseHandler(MT_SENDATTENDEVENT1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	inline bool _RegisterHDResponseHandler(MESSAGETYPE id,AbstractObject<int,HDResponseHandler>::CreatorType cr)
	{
		HDCCUProcessUnits::instance()->Register(id,cr);
		return true;
	}

#define HD_REGISTER_HANDLER(id,clazz) \
	bool clazz::clazz##Registered = _RegisterHDResponseHandler(id,\
	reinterpret_cast<AbstractObject<int,HDResponseHandler>::CreatorType>(clazz::clazz##CreateObject))
}
 

#endif // _KSG_HD_SVR_H_
