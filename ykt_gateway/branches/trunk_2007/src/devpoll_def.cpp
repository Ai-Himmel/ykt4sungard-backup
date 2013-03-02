#include "devpoll_def.h"

//#ifndef WIN32
//////////////////////////////////////////////////////////////////////////
// KSG_Reactor_Handler
KSG_Reactor_Handler::KSG_Reactor_Handler():_message(NULL)
{
	//empty
}
KSG_Reactor_Handler::~KSG_Reactor_Handler()
{
	//empty
	if(_message)
		_message->release();
}

int KSG_Reactor_Handler::handle_input(ACE_HANDLE handle)
{
	ACE_Message_Block *mb;
	if(!_message)
	{
		ACE_NEW_RETURN(mb,ACE_Message_Block(BUFSIZ+1),-1);
		
	}
	int ret;
	ssize_t bytes_read = 0;
	do
	{
		ret = 0;
		bytes_read = this->peer().recv(mb->wr_ptr(),mb->size() - mb->length());
		if(bytes_read == -1)
		{
			if(errno == EWOULDBLOCK)
			{
				break;
			}
			else
			{
				mb->release();
				mb = NULL;
				ACE_ERROR((LM_ERROR,"接收数据失败！！"));
				ret = -1;
				break;
			}
		}
		else if(bytes_read == 0)
		{
			break;
		}
	} while(1);
	
	_message = mb;
	return ret;
}

int KSG_Reactor_Handler::handle_close(ACE_HANDLE , ACE_Reactor_Mask )
{
	return -1;
}

int KSG_Reactor_Handler::handle_output(ACE_HANDLE fd )
{
	return -1;
}

int KSG_Reactor_Handler::handle_timeout(const ACE_Time_Value &time
										, const void * act)
{
	return -1;
}

//#endif 
