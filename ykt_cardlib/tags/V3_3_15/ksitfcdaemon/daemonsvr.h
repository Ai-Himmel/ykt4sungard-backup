#ifndef _KSDAEMONSVR_H_
#define _KSDAEMONSVR_H_

#include "kscardmsg.h"

class KsCardDaemonSvr : public wxThread
{
private:
	static KsCardDaemonSvr* instance_;
	int svrport_;
	wxSocketServer *server_;
	wxSocketBase* cltsock_;
	KsCardMsg requestMsg_;
	KsCardMsgRecv msgrecv_;
	KsCardDaemonSvr();
	void freeCltSocket();
	int do_process_msg();
	/** \brief ·¢ËÍÓ¦´ð
	*/
	int send_response(KsCardMsg &resp);
public:
	~KsCardDaemonSvr();
	int StartServer(int port);
	int StopServer();
	static void FreeSvr();
	static KsCardDaemonSvr* instance();
	int process_loop(long timeout /*= 300*/);
	virtual void* Entry();
	virtual void OnExit();
	int run_as_thr();
};


#endif // _KSDAEMONSVR_H_
