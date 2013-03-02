#ifndef _KSG_DEVPOLL_DEF_H_
#define _KSG_DEVPOLL_DEF_H_

//#ifndef WIN32
#include <ace/Dev_Poll_Reactor.h>
#include <ace/Reactor.h>
#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>
#include <ace/Mutex.h>

typedef ACE_Svc_Handler<ACE_SOCK_STREAM, ACE_NULL_SYNCH> SVC_HANDLER;

class KSG_Reactor_Handler : public SVC_HANDLER
{
private:
	ACE_Message_Block *_message;
public:
	KSG_Reactor_Handler();
	virtual ~KSG_Reactor_Handler();
	virtual int handle_input(ACE_HANDLE handle);
	virtual int handle_output(ACE_HANDLE fd /* = ACE_INVALID_HANDLE */);
	virtual int handle_timeout(const ACE_Time_Value &time, const void * act);
	virtual int handle_close(ACE_HANDLE /* = ACE_INVALID_HANDLE */
		, ACE_Reactor_Mask /* = ACE_Event_Handler::ALL_EVENTS_MASK */);
};
//#endif

#endif // _KSG_DEVPOLL_DEF_H_
