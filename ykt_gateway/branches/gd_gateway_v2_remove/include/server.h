#ifndef _KSG_SERVER_H_
#define _KSG_SERVER_H_

#include <map>
#include <list>
#include <ace/ACE.h>
#include <ace/Task_Ex_T.h>


class KSG_Server_Worker;

class KSG_Request_Msg;
// 任务处理管理器
class KSG_Server_Manager : public ACE_Task_Ex<ACE_MT_SYNCH,KSG_Request_Msg>
{
private:
	int frozen_;
	int stopped_;

public:
	
public:
	KSG_Server_Manager();
	~KSG_Server_Manager();
	int start_all(int thrdcnt);
	int stop_all();
	int svc();

private:
	int finish_request(KSG_Server_Worker *worker,KSG_Request_Msg *msg);
	int peek_request(KSG_Request_Msg **msg);
	int report_suspend(KSG_Server_Worker *worker);
};

class KSG_Request_Msg
{
private:
	ACE_Time_Value start_time_;
protected:
	KSG_Request_Msg();
	friend class KSG_Server_Manager;
public:
	enum {rmp_lower = 1,rmp_normal,rmp_higher};
	// 接口定义
public:
	KSG_Request_Msg(const KSG_Request_Msg &rhs);
	KSG_Request_Msg& operator=(const KSG_Request_Msg &rhs);
	~KSG_Request_Msg();

	ACE_Time_Value start_time() const;

};

#endif // _KSG_SERVER_H_
