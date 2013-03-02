#ifndef _KSG_HD_DEVNODE_H_
#define _KSG_HD_DEVNODE_H_

#ifdef _MSC_VER
# pragma once
#endif

#include "deviceinterface.h"
#include "scheduler.h"
#include "hddev/hddef.h"
#include "F8583.h"
#include "taskcode.h"
#include "999dev/999devtype.h"
#include "proactor_def.h"

namespace HDDEV
{
	
	//! 汇多POS机设备
	class HDPosDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HDPosDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		HDPosDevice():KSGDevice(KSG_HD_POS_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
	};
	//! 汇多CCU设备
	class HDCCUDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HDCCUDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw ();
	public:
		HDCCUDevice():KSGDevice(KSG_HD_SERVER_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
	};
	//! 汇多充值机设备
	class HDAddPosDevice : public KSGDevice
	{
		DECLARE_FACTORY_CREATOR(HDAddPosDevice)
	protected:
		virtual int make_handler(KSGDeviceNode* node,ACE_HANDLE* handler);
		virtual int close_handler(KSGDeviceNode* node,ACE_HANDLE handler) throw();
	public:
		HDAddPosDevice():KSGDevice(KSG_HD_ADD_POS_DEV)
		{}
		virtual bool Accept(BaseVisitor& guest,KSGDeviceNode* visitor);
		
	};

	//! 汇多采集ＰＯＳ机消费流水
	class IHDCollectSerial : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDCollectSerial)
	private:
		int CollectRecord(HD8583STRUCT& record);
	public:
		IHDCollectSerial():KSGDeviceInterface(TK_COLLSERIAL_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	private:
	};
	//! 采集汇多设备心跳
	class IHDCollectHeardbeat : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDCollectHeardbeat)
	public:
		IHDCollectHeardbeat():KSGDeviceInterface(TK_HEARTBEAT_TASK)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 挂失卡
	class IHDAddBlackCard : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDAddBlackCard)
	public:
		IHDAddBlackCard():KSGDeviceInterface(TK_ADD_BLACKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 解挂卡
	class IHDDelBlackCard : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDDelBlackCard)
	public:
		IHDDelBlackCard():KSGDeviceInterface(TK_DEL_BLACKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//!< 批量下载黑名单
	class IHDBatchDownloadBlkCard : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDBatchDownloadBlkCard)
	private:
		int dowload_blkcard(KSGDeviceNode* node,Task* task,std::string &ret_ver);
	public:
		IHDBatchDownloadBlkCard():KSGDeviceInterface(TK_BATCH_DL_BLKCARD)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 设置设备卡分组
	class IHDSetCardPrivileges :public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDSetCardPrivileges)
	public:
		IHDSetCardPrivileges():KSGDeviceInterface(TK_SET_CARD_PRIVILEGE)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 设置设备管理费
	class IHDSetFeeRate : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDSetFeeRate)
	public:
		IHDSetFeeRate():KSGDeviceInterface(TK_SET_FEE_RATE)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 补采POS机流水
	class IHDCollPosHisSerial : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDCollPosHisSerial)
	public:
		IHDCollPosHisSerial():KSGDeviceInterface(TK_COLL_HIS_SERIAL)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 下传餐次
	class IHDDownloadConCode : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDDownloadConCode)
	public:
		IHDDownloadConCode():KSGDeviceInterface(TK_DL_CONCODE)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};
	//! 下传补助文件
	class IHDDLSubsidyFile : public KSGDeviceInterface
	{
		DECLARE_FACTORY_CREATOR(IHDDLSubsidyFile)
	private:
		int check_subsidy_dir(const char *phyno,std::string &out_path);
	public:
		IHDDLSubsidyFile():KSGDeviceInterface(TK_DL_SUBSIDY_FILE)
		{}
		int ExecuteTask(KSGDeviceNode* node,Task* task);
	};

	class HD_Subsidy_File_Gen
	{
	private:
		static ST_PACK g_out_pack;
		static int g_card_idx_range[];
		int get_card_count_per_pack();
		int get_pack_index(int card_idx);
		int write_buffer(const char *buffer,int buf_len);
		int _pack_index;
		FILE * _fp;
		static const int MAX_CARD_COUNT = 1500000;
		unsigned char char_to_hex(char c);
	public:
		HD_Subsidy_File_Gen():_pack_index(0),_fp(NULL)
		{}
		~HD_Subsidy_File_Gen();
		int open_data_file(const char *file_path,int seqno);
		int put_one_pack(ST_PACK * data);
		int finish();
	};

	//! 汇多设备初始化类
	class HDDeviceLoader : public KSGDeviceLoader
	{
	private:
		void SetupDeviceGroup(KSGDeviceNode* node);
	public:
		int LoadDevice(KSGDeviceManager* manager);
		int Finish(KSGDeviceManager* manager);
	};

	//! 汇多设备接口初始化类
	class HDDevInterfaceLoader : public KSGDeviceInterfaceLoader
	{
	public:
		virtual int LoadInterface(KSGDeviceManager *manager);
	};
	//! 汇多业务层初始化类
	class HDTaskExecutorLoader : public TaskExecutorLoader
	{
	public:
		int LoadExecutor();
	};

	//<! 定义 汇多 设备工厂
	typedef KSGDeviceInterfaceFactory
	<
	TYPELIST_4(DevAbstractObject,HDDeviceLoader,HDDevInterfaceLoader,HDTaskExecutorLoader)
	>::Result KSGHDDevInterfaceFactory;
	//! 汇多侦听服务
	class HDCCUListenScheduler : public KSGScheduler
	{
		DECLARE_FACTORY_CREATOR(HDCCUListenScheduler)
	private:
	public:
		HDCCUListenScheduler();
		virtual ~HDCCUListenScheduler();
		virtual void Run();
	protected:
		void StartListen();
		virtual KSGScheduler& GetObserverable()
		{
			return *this;
		}
	};
}

#endif // _KSG_HD_DEVNODE_H_

