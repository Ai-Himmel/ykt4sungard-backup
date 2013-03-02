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

#define _DEFAULT_MAX_LEN 1024 << 4

namespace HDDEV
{
	extern MYDATETIMESTRUCT HDGetDataTime();
	unsigned long DecodeTermSN(const char * sn);
	void EncodeTermSN(unsigned long termid,char* sn);

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

	unsigned short GetDeviceAddress(KSGDeviceNode* node);
	
	//! CCU ��������� Handler
	class HDCCUSvrHandler : public ACE_Svc_Handler<ACE_SOCK_STREAM,ACE_MT_SYNCH>
	{
	private:
		static const int MAX_MESBUF_LEN = _DEFAULT_MAX_LEN;
		int _close_time;
		ACE_Thread_Mutex _mutex;
		void dec_close_time();
		void delete_self();
	public:
		HDCCUSvrHandler():_close_time(2)
		{
		}
		virtual int open(void*);
		virtual int handle_input(ACE_HANDLE fd);
		virtual int handle_timeout(const ACE_Time_Value &time, const void *);
		virtual int handle_close(ACE_HANDLE handler, ACE_Reactor_Mask mask);
		virtual int svc();
		virtual int close(u_long flags);
	private:
		virtual ~HDCCUSvrHandler()
		{

		}
	};

	typedef ACE_Acceptor<HDCCUSvrHandler,ACE_SOCK_ACCEPTOR> CCUSvrAcceptor;
	typedef ACE_Singleton<ACE_Reactor,ACE_Null_Mutex> REACTOR;

	class HDResponseHandler;
	typedef xutil::SingletonHolder<AbstractObject<MESSAGETYPE,HDResponseHandler>, MTTheadModel> HDCCUProcessUnits;
	//! ���ҵ����ӿ�
	class HDResponseHandler
	{
	public:
		HDResponseHandler(MESSAGETYPE code):_requestCode(code)
		{}
		virtual ~HDResponseHandler(){}
		virtual int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer) = 0;
		MESSAGETYPE GetRequestCode() const
		{
			return _requestCode;
		}
	private:
		MESSAGETYPE _requestCode;
	};

	// �������
	class HDReechoHandler1 : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDReechoHandler1)
	public:
		HDReechoHandler1():HDResponseHandler(MT_REECHO1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};

	//! �豸ǩ��
	class HDEnrollHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDEnrollHandler)
	public:
		HDEnrollHandler():HDResponseHandler(MT_SIGNIN1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! ��������Կ
	class HDInitKeyHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDInitKeyHandler)
	public:
		HDInitKeyHandler():HDResponseHandler(MT_INITKEY1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	//! ��ȡ���ϴ�������ˮ��¼
	class HDRecordFileReader 
	{
	private:
		std::string _filepath;
		ACE_HANDLE _file_handler;
		int ReadPosRecord();
		int DoReadRecordFile();
		size_t LoadIndex();
		int SaveIndex(size_t index);
	public:
		static const int RECORD_BUF_LEN = 47;
		HDRecordFileReader(const std::string& filepath)
			:_filepath(filepath),_file_handler(ACE_INVALID_HANDLE)
		{}
		~HDRecordFileReader();
		int ReadFile();
		int SavePosRecord(BYTE* buf);
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
	//! CCU����֪ͨ
	class HDCCUNoticeHandler : public HDResponseHandler
	{
		DECLARE_FACTORY_CREATOR(HDCCUNoticeHandler)
	private:
		int CheckFile(int fileid,BYTE* data,const std::string& devid,std::string& filepath);
		int CheckDownloadPath(const std::string& devid,std::string& filepath);
		void ClearCCUFile(int fileid);
		int DoFile(int fileid,BYTE* filebuf,KSGDeviceNode* node
			,HD8583STRUCT& req,std::string& filepath);
	public:
		HDCCUNoticeHandler():HDResponseHandler(MT_CCUONLINENOTICE1)
		{}
		int DoResponse(HD8583STRUCT& req,HD8583STRUCT& resp,ACE_HANDLE peer);
	};
	

	inline bool _RegisterHDResponseHandler(MESSAGETYPE id,AbstractObject<int,HDResponseHandler>::CreatorType cr)
	{
		HDCCUProcessUnits::Instance().Register(id,cr);
		return true;
	}

#define HD_REGISTER_HANDLER(id,clazz) \
	bool clazz::clazz##Registered = _RegisterHDResponseHandler(id,\
	reinterpret_cast<AbstractObject<int,HDResponseHandler>::CreatorType>(clazz::clazz##CreateObject))
}
 

#endif // _KSG_HD_SVR_H_
