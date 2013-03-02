// bulistenthread.h: interface for the CBUListenThread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BULISTENTHREAD_H__D4BCF943_12B8_4662_B6BE_83E5FD3FFD19__INCLUDED_)
#define AFX_BULISTENTHREAD_H__D4BCF943_12B8_4662_B6BE_83E5FD3FFD19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WThread.h"
#include "tcp.h"

class CBUListenThread : public CWThread  
{
private:
   CTcpSocket listensock;

private:
	int Run();

public:
	bool Initialize(int port);
	CBUListenThread();
	virtual ~CBUListenThread();

};

#endif // !defined(AFX_BULISTENTHREAD_H__D4BCF943_12B8_4662_B6BE_83E5FD3FFD19__INCLUDED_)
