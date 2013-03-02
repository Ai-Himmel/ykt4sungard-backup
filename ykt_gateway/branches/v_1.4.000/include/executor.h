#ifndef _KSG_EXECUTOR_H_
#define _KSG_EXECUTOR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "device.h"
#include "DRTPHelper.h"

//! ָ��ִ����
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
	//! ִ��ָ���
	/*!
	 \param task ָ��
	 \return ���� 0 ��ʾִ�гɹ� �����򷵻�ִ�д����롣-1 ��ʾ�޷������ָ��
	 */
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task)
	{
		return -1;
	}
};

#endif // _KSG_EXECUTOR_H_

