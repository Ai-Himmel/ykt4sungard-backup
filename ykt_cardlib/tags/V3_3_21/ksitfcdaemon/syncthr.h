#ifndef _KSSYNCTHREAD_H_
#define _KSSYNCTHREAD_H_

#include "globaldef.h"
#include "kscardmsg.h"

class KsSyncThr : public wxThread
{
private:
	static const int CHK_HEARTBEAT_INTVAL;
	static const int UPLOAD_SERAIL_INTVAL;
	static const int SYNC_BLACKCARD_INTVAL;
	static const int ONLINE_INTERVAL;
	static KsSyncThr* instance_;

	long sync_blackcard_interval_;
	long upload_serial_interval_;
	int svronline_;
	wxStopWatch svrofflineTime_;
	KsSyncThr();
	wxStopWatch checkSvrHeartBeatTime_;
	wxStopWatch uploadSerialTime_;
	wxStopWatch syncBlackCardTime_;
	void DoMainLoop();
	void SyncBlackCard();
	void UploadSerial();
	void ChkHeartBeat();
	KsCardDaemonCfg* global_cfg_;
	wxCriticalSection m_Chkcritsect;
	void UpdateSvrStatus(int online);
public:
	~KsSyncThr();
	static KsSyncThr* instance();
	static void FreeAll();
	int start_thr();
	int stop_thr();
	virtual void *Entry();
	virtual void OnExit();
	void SetConfig(KsCardDaemonCfg* cfg);
	int InitYKTSvr(const char *apppath);
	int IsOnline();
};

class KsYktSvrUtil
{
private:
	static KsCardDaemonCfg* global_cfg_;
	static int isYKTSvrOK_;
public:
	KsYktSvrUtil()
	{
	}
	static int IsYKTSvrOK();
	/** \breif 初始化一卡通后台服务
	* \param path - 程序配置目录
	* \param cfg - 全局配置参数
	* \return 返回 0 表示成功，其它表示失败
	*/
	static int InitYKTSvr(const char *path,KsCardDaemonCfg* cfg);
	/** \breif 同步系统黑名单
	* \return 返回 0 表示成功，-1 表示失败，1 表示无黑名单,-2 表示通讯故障
	*/
	static int SyncBlackCard();
	/** \breif 上传流水
	* \return 返回 0 表示成功，-1 表示失败，1 表示无流水上传,-2 表示通讯故障
	*/
	static int UploadSerial();
	/** \breif 检查系统状态
	* \return 返回 0 表示成功, -1 表示失败,-2 表示通讯故障
	*/
	static int ChkHeartBeat();
	/** \breif 向后台签到
	* \param msg - 签到参数
	*          输入   data.termid - 终端号
	*          输出   data.shopid - 商户号
	*                 data.shopname - 商户名
	* \return 返回 0 表示签到成功 -1 表示签到失败，-2 表示通讯故障
	*/
	static int LoginDevice(KsCardMsg &msg);
};
#endif //_KSSYNCTHREAD_H_
