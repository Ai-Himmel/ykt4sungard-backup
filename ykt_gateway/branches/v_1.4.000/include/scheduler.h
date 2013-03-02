#ifndef _SCHEDULAR_H_
#define _SCHEDULAR_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "ksglobal.h"
#include "thread.h"
#include "xutils/xsingleton.h"
#include "factory.h"
#include <boost/functional.hpp>
#include <algorithm>
#include <assert.h>
#include <map>
#include <list>

//typedef KSGObserverable<KSGMultiThreadmModel<300> > DefaultObserverable;

class KSGScheduler : public KSGObserverable<KSGScheduler,KSGMultiThreadmModel<1000> > 
{
private:
	bool _terminated;
	int _schdId;
public:
	KSGScheduler():_schdId(0),_terminated(false){}
	KSGScheduler(int id):_schdId(id),_terminated(false){}
	virtual ~KSGScheduler() {}
	virtual void Run() = 0;
	inline bool IsTerminated() const
	{
		return _terminated;
	}
	inline void Terminate()
	{
		_terminated = true;
	}
	inline int GetSchdId() const
	{
		return _schdId;
	}

};

typedef KSGObserver<KSGScheduler,KSGMultiThreadmModel<1000> > KSGMTObserver;

class SchedulerRunner : public KSGThreadExec<SchedulerRunner>
{
private:
	KSGScheduler * _schd;
public:
	SchedulerRunner(KSGScheduler* s):_schd(s){}
	virtual void Run()
	{
		if(_schd)
			_schd->Run();
	}
};

template<class T = SchedulerRunner>
class KSGSchedulerGroup
{
protected:
	typedef T SchdRunner;
public:
	typedef std::map<KSGScheduler*,T*> SchdThreadMap;
private:
	SchdThreadMap _schds;
	inline SchdRunner* FindRunner(KSGScheduler* schd)
	{
		typename SchdThreadMap::iterator i = _schds.find(schd);
		if(i != _schds.end())
			return i->second;
		return NULL;
	}
	void TerminateRunner(typename SchdThreadMap::value_type& runner)
	{
		KSGScheduler* s = runner.first;
		SchdRunner* r = runner.second;
		s->Terminate();
		r->Terminate();
	}
	void FreeSchd(typename SchdThreadMap::value_type& runner)
	{
		KSGScheduler* s = runner.first;
		SchdRunner* r = runner.second;
		delete r;
		FreeScheduler(s);
	}
	inline void StartSchd(typename SchdThreadMap::value_type& runner)
	{
		SchdRunner* r = runner.second;
		if(r->IsSuspend())
			r->Start();
	}
protected:
	inline void ClearMap()
	{
		_schds.clear();
	}
	virtual void FreeScheduler(KSGScheduler * schd)
	{
		delete schd;
	}
public:
	KSGSchedulerGroup(){}
	virtual ~KSGSchedulerGroup(){}
	void NewScheduler(KSGScheduler* schd,bool autoStart=true)
	{
		SchdRunner* runner = FindRunner(schd);
		if(runner)
		{
			throw IdentifireAlreadyExists();
		}
		runner = new SchdRunner(schd);
		_schds.insert(typename SchdThreadMap::value_type(schd,runner));
		if(autoStart)
			runner->Start();
	}
	void TerminateAll()
	{
		std::for_each(_schds.begin(),_schds.end(),
			boost::bind(&KSGSchedulerGroup::TerminateRunner,this,_1));
	}
	void TerminateSchd(KSGScheduler* schd)
	{
		SchdRunner* runner = FindRunner(schd);
		if(runner)
		{
			runner->Terminate();
			schd->Terminate();
		}
	}
	virtual void ClearAll()
	{
		TerminateAll();
		std::for_each(_schds.begin(),_schds.end(),
			boost::bind(&KSGSchedulerGroup::FreeSchd,this,_1));
		ClearMap();
	}
	void StartAll()
	{
		Traversal(boost::bind(&KSGSchedulerGroup::StartSchd,this,_1));
	}
	void StartScheduler(KSGScheduler* schd)
	{
		SchdRunner* runner = FindRunner(schd);
		if(runner && runner->IsSuspend())
		{
			runner->Start();
		}
	}
	void Traversal(boost::function1<void,typename SchdThreadMap::value_type&> func)
	{
		std::for_each(_schds.begin(),_schds.end(),func);
	}
};

class KSGSchedulerGrpFactory : public KSGSchedulerGroup<SchedulerRunner>
{
public:
	typedef std::list<int> SchedulerIdList;
	typedef AbstractObject<int,KSGScheduler> SchedulerClassMap;
	typedef SchedulerClassMap::CreatorType SchedulerCreatorType;
private:
	SchedulerClassMap _schedulers;
	SchedulerIdList _ids;
	inline void AddObserver(KSGMTObserver* obs,SchdThreadMap::value_type& value)
	{
		KSGScheduler* schd = value.first;
		schd->Attach(obs);
	}
	void StartSchdById(int id);
	void FreeRunner(SchdThreadMap::value_type& value);

public:
	KSGSchedulerGrpFactory()
	{}
	virtual ~KSGSchedulerGrpFactory()
	{
		ClearAll();
	}
	bool RegisterScheduler(int id,SchedulerClassMap::CreatorType cr)
	{
		try
		{
			_schedulers.Register(id,cr);
			_ids.push_back(id);
			return true;
		}
		catch(...)
		{
			return false;
		}
	}
	void AddScheduler(const SchedulerIdList& ids);
	void AddAllScheduler();
	
	virtual void ClearAll();
	void AddObserver(KSGMTObserver* obs)
	{
		Traversal(boost::bind(&KSGSchedulerGrpFactory::AddObserver,this,obs,_1));
	}
};

typedef ACE_Singleton<KSGSchedulerGrpFactory,ACE_Null_Mutex> SchedulerGroup;

#define KSG_ADD_SCHD_CLASS(id,clazz) \
	bool clazz::clazz##Registered = SchedulerGroup::Instance().RegisterScheduler(id, \
	reinterpret_cast<KSGSchedulerGrpFactory::SchedulerCreatorType>(clazz::clazz##CreateObject))

#endif // _SCHEDULAR_H_

