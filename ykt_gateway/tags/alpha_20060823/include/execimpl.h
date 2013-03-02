#ifndef _KSG_EXECIMPL_H_
#define _KSG_EXECIMPL_H_

#include "executor.h"
#include "deviceinterface.h"

class AddBlackCardExec : public KSGTaskExecutor
{
public:
	DECLARE_FACTORY_CREATOR(AddBlackCardExec)

	AddBlackCardExec()
	{}
	virtual int ExecuteTask(CDRTPHelper* drtp,TaskPointerType task);
};
#endif // _KSG_EXECIMPL_H_
