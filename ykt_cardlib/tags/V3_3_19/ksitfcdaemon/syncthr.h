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
	/** \breif ��ʼ��һ��ͨ��̨����
	* \param path - ��������Ŀ¼
	* \param cfg - ȫ�����ò���
	* \return ���� 0 ��ʾ�ɹ���������ʾʧ��
	*/
	static int InitYKTSvr(const char *path,KsCardDaemonCfg* cfg);
	/** \breif ͬ��ϵͳ������
	* \return ���� 0 ��ʾ�ɹ���-1 ��ʾʧ�ܣ�1 ��ʾ�޺�����,-2 ��ʾͨѶ����
	*/
	static int SyncBlackCard();
	/** \breif �ϴ���ˮ
	* \return ���� 0 ��ʾ�ɹ���-1 ��ʾʧ�ܣ�1 ��ʾ����ˮ�ϴ�,-2 ��ʾͨѶ����
	*/
	static int UploadSerial();
	/** \breif ���ϵͳ״̬
	* \return ���� 0 ��ʾ�ɹ�, -1 ��ʾʧ��,-2 ��ʾͨѶ����
	*/
	static int ChkHeartBeat();
	/** \breif ���̨ǩ��
	* \param msg - ǩ������
	*          ����   data.termid - �ն˺�
	*          ���   data.shopid - �̻���
	*                 data.shopname - �̻���
	* \return ���� 0 ��ʾǩ���ɹ� -1 ��ʾǩ��ʧ�ܣ�-2 ��ʾͨѶ����
	*/
	static int LoginDevice(KsCardMsg &msg);
};
#endif //_KSSYNCTHREAD_H_
