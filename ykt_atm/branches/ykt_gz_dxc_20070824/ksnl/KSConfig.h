#ifndef _CKSCONFIG_H_
#define _CKSCONFIG_H_

#pragma once
#include "afxwin.h"
#pragma warning(disable : 4996 4017)
#include <string>
#include <vector>
#include <map>
#include "FG_DIB.h"
#include "KSWorkflow.h"
#include "DRTPHelper.h"

class CKSConfig
{
public:
	CKSConfig(void);
	~CKSConfig(void);
	// �����ļ�·��
	static std::string ms_configFile;
	// NL8900����·��
	CString m_NLConfigFile;
	// ϵͳ����·��
	CString m_NLSysCfgFile;
	// ����ͼƬ·��
	CString m_bkPicFile;
	void LoadConfig(const CString& basePath);
private:
	// ���ر�������
	void LoadKSNLConfig(const CString& basePath);
public:
	// RF��Ƶ����ȡ����
	CString m_RFComPort;
	// ����IC������
	CString m_ICComPort;
private:
	// �������ù���
	int LoadFunction(const std::map<std::string,std::string> &rec);
	// ���� nl8900 ������
	void LoadNL8900Config(const CString & basePath);
	// ����ϵͳ����
	void LoadSystemCfg(const CString& basePath);
public:
	// �ȴ�ʱ��
	int m_idleTime;
	// DRTP 
	CString m_drtpServer;
	int m_drtpPort;
	int m_drtpFuncNo;
	// ��߰���ͼƬ
	CString m_leftBtnPic;
	int m_leftBtnPicWidth;
	int m_leftBtnPicHeight;
	// �ұ߰���ͼƬ
	CString m_rightBtnPic;
	int m_rightBtnPicWidth;
	int m_rightBtnPicHeight;
	// ͼƬ·��
	CString m_picPath;
	CFG_DIB m_bkImg;
	CFG_DIB m_leftBtnImg;
	CFG_DIB m_rightBtnImg;
	// ��������
	CString m_fontName;
	COLORREF m_fontColor;
	int m_fontSize;
	// ����ˮ��ѡ����
	int m_menuId;
	// ������̬��
/*	CString m_KSComDLLPath;*/
	CString m_CardDLLPath;
	// SYSTEM
	CString m_systemNo;
	// ������Կ
	CString m_workKey;
	CString m_ICCardkey;
	//
	CKSWorkflowManager<CKSWorkflow> m_workflows;

	CDRTPHelper* CreateDrtpHelper();

private:
	// ��ʼ�����й�����
	void InitWorkflows(void);
	CKSWorkflow *CreateWorkflowFactory(const std::string &wf_name);
	// ɾ�����е�workflow
	void ReleaseWorkflows(void);
};

#endif // _CKSCONFIG_H_