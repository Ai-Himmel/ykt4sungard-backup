#ifndef _KSG_DRTPPOOL_H_
#define _KSG_DRTPPOOL_H_

#include "DRTPHelper.h"
#include "thread.h"
#include "smartpool.h"

class KSG_DRTP_Creator
{
private:
	int max_;
public:
	KSG_DRTP_Creator();
	virtual int get_max();
	void set_max(int num)
	{
		max_ = num;
	}
	virtual CDRTPHelper *create_new();
	virtual void delete_one(CDRTPHelper *p);
};

//<! DRTP »º´æ³ØÀàÐÍ
typedef KSG_SmartPool<CDRTPHelper,
KSG_Resource_Pool_Allocator<CDRTPHelper,KSGMultiThreadmModel<1000>,KSG_DRTP_Creator> > DRTPPoolType;

#endif // _KSG_DRTPPOOL_H_
