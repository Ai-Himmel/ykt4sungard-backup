#ifndef _ENCSVRFUNC_H_
#define _ENCSVRFUNC_H_
#include "BUShm.h"
#include <map>


class SHM_Lock_Guard
{
private:
	CBUShm &shm_;
	int locked_;
public:
	SHM_Lock_Guard(CBUShm &shm):shm_(shm),locked_(0)
	{
	}
	int lock()
	{
		if(shm_.Lock())
		{
			locked_ = 1;
			return 0;
		}
		return -1;
	}	
	~SHM_Lock_Guard()
	{
		if(locked_ == 1)
		{
			shm_.Unlock();
			locked_ = 0;
		}
	}
};

#define BK_SHMLOCK_GUARD(shm) SHM_Lock_Guard shm##shm__(shm); if(shm##shm__.lock()) return
#define BK_SHMLOCK_GUARD_RET(shm,ret) SHM_Lock_Guard shm##shm__(shm); if(shm##shm__.lock()) return (ret)


class BKConfiguration
{
private:
	typedef struct {
		unsigned int vernum;
	}CFGSHM_T;
	static BKConfiguration * instance_;
	typedef std::map<std::string,std::string> VALUE_MAP_TYPE;
	VALUE_MAP_TYPE para_map_;
	CFGSHM_T* cfgshm_;
	CBUShm cfgshm_handle_;
	CFGSHM_T localcfg_;
	BKConfiguration();
	int init_shm();
	void delete_shm();
public:
	~BKConfiguration();
	static BKConfiguration* instance();
	static const char SHMCFG_NAME[];
	int load_config();
	int check_config_ver();
	int save_para(const char *para,const char *value);
	int save_int_para(const char *para,int value); 
	int get_int_para(const char *para,int *value) const;
	int get_string_para(const char *para,char *value) const;
};


class YangjiangDebitComm
{
public:
	YangjiangDebitComm(const char* svrip,int svrport);
	~YangjiangDebitComm();
	int SendRequest(ST_PACK *rPack,char* szMsg);

	const char* host_date() const
	{
		return host_date_;
	}
	const char* host_time() const
	{
		return host_time_;
	}
	const char* mac2() const
	{
		return mac2_;
	}
	
private:
	YangjiangDebitComm(const YangjiangDebitComm&);
	YangjiangDebitComm& operator=(const YangjiangDebitComm&);
	void Reset();
	char host_date_[9];
	char host_time_[7];
	char mac2_[9];
	char svrip_[32];
	int svrport_;
};




#endif // _ENCSVRFUNC_H_

