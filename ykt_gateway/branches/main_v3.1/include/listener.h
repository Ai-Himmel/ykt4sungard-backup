#ifndef _KSG_LISTENER_H_
#define _KSG_LISTENER_H_

#include "ksglobal.h"
#include <ace/Task.h>
#include <map>
#include <set>
#include <ace/Singleton.h>
#include "factory.h"

class KSG_Server_Listener
{
public:
	KSG_Server_Listener(){}
	virtual ~KSG_Server_Listener(){}
	virtual int start_listen() = 0;
	virtual int stop_listen() = 0;
};

class KSG_Listener_Utils
{
public:
	typedef AbstractObject<int,KSG_Server_Listener> ListenerClassMap;
	typedef ListenerClassMap::CreatorType ListenerCreatorType;
	int register_listener(int id,ListenerCreatorType creator);
	KSG_Server_Listener* create_listener(int id);
private:
	ListenerClassMap _listener_classes;
};
//! proactor task
class KSG_Listener_Task : public ACE_Task<ACE_MT_SYNCH>
{
public:

	KSG_Listener_Task();
	virtual ~KSG_Listener_Task();
	virtual int start_task(int max_task) = 0;
	virtual int stop_task();
	int start_listener(int id);
private:
	typedef std::map<int,KSG_Server_Listener*> listener_map_type;
	listener_map_type _listeners;
protected:
	virtual int init_listener(KSG_Server_Listener *l)
	{return 0;}
};

typedef ACE_Singleton<KSG_Listener_Utils,ACE_Null_Mutex> KSG_LISTENER_UTILS;

#define KSG_ADD_LISTENER_CLASS(id,clazz) \
	bool clazz::clazz##Registered = KSG_LISTENER_UTILS::instance()->register_listener(id, \
	reinterpret_cast<KSG_Listener_Utils::ListenerCreatorType>(clazz::clazz##CreateObject))

#endif // _KSG_LISTENER_H_