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
	// 配置文件路径
	static std::string ms_configFile;
	// NL8900配置路径
	CString m_NLConfigFile;
	// 系统配置路径
	CString m_NLSysCfgFile;
	// 背景图片路径
	CString m_bkPicFile;
	void LoadConfig(const CString& basePath);
private:
	// 加载本地配置
	void LoadKSNLConfig(const CString& basePath);
public:
	// RF射频卡读取串口
	CString m_RFComPort;
	// 磁条IC卡串口
	CString m_ICComPort;
private:
	// 加载配置功能
	int LoadFunction(const std::map<std::string,std::string> &rec);
	// 加载 nl8900 的配置
	void LoadNL8900Config(const CString & basePath);
	// 加载系统配置
	void LoadSystemCfg(const CString& basePath);
public:
	// 等待时间
	int m_idleTime;
	// DRTP 
	CString m_drtpServer;
	int m_drtpPort;
	int m_drtpFuncNo;
	// 左边按键图片
	CString m_leftBtnPic;
	int m_leftBtnPicWidth;
	int m_leftBtnPicHeight;
	// 右边按键图片
	CString m_rightBtnPic;
	int m_rightBtnPicWidth;
	int m_rightBtnPicHeight;
	// 图片路径
	CString m_picPath;
	CFG_DIB m_bkImg;
	CFG_DIB m_leftBtnImg;
	CFG_DIB m_rightBtnImg;
	// 字体属性
	CString m_fontName;
	COLORREF m_fontColor;
	int m_fontSize;
	// 读入水控选择项
	int m_menuId;
	// 读卡动态库
/*	CString m_KSComDLLPath;*/
	CString m_CardDLLPath;
	// SYSTEM
	CString m_systemNo;
	// 工作密钥
	CString m_workKey;
	CString m_ICCardkey;
	//
	CKSWorkflowManager<CKSWorkflow> m_workflows;

	CDRTPHelper* CreateDrtpHelper();

private:
	// 初始化所有工作流
	void InitWorkflows(void);
	CKSWorkflow *CreateWorkflowFactory(const std::string &wf_name);
	// 删除所有的workflow
	void ReleaseWorkflows(void);
};

#endif // _CKSCONFIG_H_