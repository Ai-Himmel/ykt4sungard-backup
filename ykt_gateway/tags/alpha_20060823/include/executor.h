#ifndef _KSG_EXECUTOR_H_
#define _KSG_EXECUTOR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "device.h"
#include "DRTPHelper.h"

//! 指令执行器
class KSGTaskExecutor
{

public:
	typedef KSGTask<KSGDeviceNode> TaskType;
	typedef TaskType* TaskPointerType;
	//! constructor
	KSGTaskExecutor()
	{
	}
	//! destructor
	virtual ~KSGTaskExecutor()
	{}
	//! 执行指令函数
	/*!
	 \param task 指令
	 \return 返回 0 表示执行成功 ，否则返回执行错误码。-1 表示无法处理的指令
	 */
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
	{
		return -1;
	}
};

#endif // _KSG_EXECUTOR_H_

