#include "listener.h"

//////////////////////////////////////////////////////////////////////////
int KSG_Listener_Utils::register_listener(int id,ListenerCreatorType creator)
{
	_listener_classes.Register(id,creator);
	return 0;
}
KSG_Server_Listener* KSG_Listener_Utils::create_listener(int id)
{
	return _listener_classes.Create(id);
}
///////////////////////////////////////////////////////////////////////////
// KSG_Listener_Task 

KSG_Listener_Task::KSG_Listener_Task()
{
	//
}
KSG_Listener_Task::~KSG_Listener_Task()
{
	
}
int KSG_Listener_Task::stop_task()
{
	// 释放所有 acceptor 以及 连接
	listener_map_type::const_iterator iter;
	for(iter = _listeners.begin(); iter != _listeners.end();++iter)
	{
		KSG_Server_Listener * pl = iter->second;
		if(pl)
		{
			ACE_DEBUG((LM_DEBUG,"关闭 Listener!"));
			pl->stop_listen();
			delete pl;
		}
	}
	_listeners.clear();
	return 0;
}

int KSG_Listener_Task::start_listener(int id)
{
	KSG_Server_Listener *pl = NULL;
	listener_map_type::const_iterator iter = _listeners.find(id);
	if( iter != _listeners.end())
		pl = iter->second;
	else
		pl = KSG_LISTENER_UTILS::instance()->create_listener(id);
	if(!pl)
		return -1;
	if(init_listener(pl))
		return -1;
	_listeners.insert(listener_map_type::value_type(id,pl));	
	return pl->start_listen();
}