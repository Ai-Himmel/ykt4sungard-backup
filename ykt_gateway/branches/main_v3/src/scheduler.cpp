
#include "scheduler.h"
#include "taskqueue.h"
#include "ksgexception.h"
#include "ksgateway.h"
#include <boost/functional.hpp>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
// KSGSchedulerGroup
bool KSGScheduler::IsTerminated() const
{
	return (_terminated || !KsgGetGateway()->is_running());
}

////////////////////////////////////////////////////////////////////
// 
void KSGSchedulerGrpFactory::AddScheduler(const SchedulerIdList &ids)
{
	std::for_each(ids.begin(),ids.end(),
		boost::bind(&KSGSchedulerGrpFactory::StartSchdById,this,_1));
}
void KSGSchedulerGrpFactory::AddAllScheduler()
{
	AddScheduler(_ids);
}
void KSGSchedulerGrpFactory::StartSchdById(int id)
{
	try
	{
		KSGScheduler* schd = _schedulers.Create(id);
		NewScheduler(schd,false);
	}
	catch(KSGException& )
	{

	}
}

void KSGSchedulerGrpFactory::ClearAll()
{
	TerminateAll();
	Traversal(boost::bind(&KSGSchedulerGrpFactory::FreeRunner,this,_1));
	ClearMap();
}
void KSGSchedulerGrpFactory::FreeRunner(SchdThreadMap::value_type& value)
{
	SchdRunner* runner = value.second;
	delete runner;
}
