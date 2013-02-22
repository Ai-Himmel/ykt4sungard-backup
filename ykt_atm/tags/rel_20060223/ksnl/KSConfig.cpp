#include "stdafx.h"
#include <string>
#include ".\ksconfig.h"
#include "CIniFile.h"

#define MAKECOLOR(c) \
	RGB((((c) >>16)& 0xFF),(((c) >> 8) & 0xFF),((c) & 0xFF))

using namespace std;

string CKSConfig::ms_configFile("ksnl.ini");

CKSConfig::CKSConfig(void)
: m_NLConfigFile(_T(""))
, m_bkPicFile(_T(""))
, m_RFComPort(_T(""))
, m_ICComPort(_T(""))
, m_leftBtnPic(_T(""))
, m_rightBtnPic(_T(""))
, m_picPath(_T(""))
{
}

CKSConfig::~CKSConfig(void)
{
	m_bkImg.CloseFile();
	m_leftBtnImg.CloseFile();
	m_rightBtnImg.CloseFile();
	ReleaseWorkflows();
}

void CKSConfig::LoadConfig(const CString& basePath)
{
	InitWorkflows();
	LoadKSNLConfig(basePath);
	LoadNL8900Config(basePath);
	LoadSystemCfg(basePath);
	// XXX: only for debug
	// m_workKey = "4344334539413846";
	//
	CFile pFile;
	if(pFile.Open(m_bkPicFile,CFile::modeRead))
	{
		m_bkImg.ReadFile(&pFile);
		pFile.Close();
	}
	//
	if(pFile.Open(m_leftBtnPic,CFile::modeRead))
	{
		m_leftBtnImg.ReadFile(&pFile);
		pFile.Close();
	}
	
	//
	if(pFile.Open(m_rightBtnPic,CFile::modeRead))
	{
		m_rightBtnImg.ReadFile(&pFile);
		pFile.Close();
	}
	
}

void CKSConfig::LoadSystemCfg(const CString& basePath)
{
	string filename = string(basePath) + (LPCTSTR)m_NLSysCfgFile;
	CCIniFile inifile(filename);

	string v = inifile.ReadString("SYSTEM","HOSTIP","");
	m_drtpServer.Format("%s",v.c_str());

	m_drtpPort = inifile.ReadInteger("SYSTEM","HOSTPORT",4000);
	m_drtpFuncNo = inifile.ReadInteger("SYSTEM","MAINFUNC",9998);

	v = inifile.ReadString("TRANSINFO","DEVID","-1");
	m_systemNo.Format("%s",v.c_str());
	//AfxMessageBox(m_systemNo);
}

// 加载本地配置
void CKSConfig::LoadKSNLConfig(const CString& basePath)
{
	string fileName = string(basePath) + CKSConfig::ms_configFile;
	CCIniFile inifile(fileName);

	string v = inifile.ReadString("GLOBAL","NLCONF","");
	m_NLConfigFile.Format("%s",v.c_str());

	v = inifile.ReadString("COM","RFCOM","");
	m_RFComPort.Format("%s",v.c_str());
	v = inifile.ReadString("COM","ICCOM","");
	m_ICComPort.Format("%s",v.c_str());
	v = inifile.ReadString("GLOBAL","PICPATH","pic\\");
	m_picPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());
	
	v = inifile.ReadString("GLOBAL","KSCOM","KSCardCom.dll");
	m_KSComDLLPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());

	v = inifile.ReadString("GLOBAL","SYSCFG","system.ini");
	m_NLSysCfgFile.Format("%s",v.c_str());

	m_idleTime = inifile.ReadInteger("GLOBAL","IDLETIME",10);
	// 读取字体属性
	v = inifile.ReadString("GLOBAL","FONTNAME","宋体");
	m_fontName.Format("%s",v.c_str());
	v = inifile.ReadString("GLOBAL","FONTCOLOR","0xFF0000");
	int color = strtoul(v.c_str(),NULL,16);
	m_fontColor = MAKECOLOR(color);
	m_fontSize = inifile.ReadInteger("GLOBAL","FONTSIZE",24);

	
	// 读取所有功能配置
	vector<string> sections;
	inifile.ReadSections(sections);
	vector<string>::iterator iter;
	for (iter = sections.begin();iter != sections.end();++iter)
	{
		string sect = *iter;
		if(sect.substr(0,4) == "FUNC")
		{
			v = inifile.ReadString(sect.c_str(),"func","");
			if(!v.empty())
			{
				CKSWorkflow * workflow = m_workflows.FindWorkflow(CString(v.c_str()));
				if(workflow != NULL)
				{
					// 加载配置
					v = inifile.ReadString(sect.c_str(),"text","");
					workflow->m_funcText.Format("%s",v.c_str());
					v = inifile.ReadString(sect.c_str(),"key","");
					workflow->m_key.Format("%s",v.c_str());
					workflow->m_posX = inifile.ReadInteger(sect.c_str(),"posx",-1);
					workflow->m_posY = inifile.ReadInteger(sect.c_str(),"posy",-1);
				}
			}
		}
	}
}

// 加载配置功能
int CKSConfig::LoadFunction(const map<string,string> &rec)
{
	// 加载功能配置
	map<string,string>::const_iterator iter;
	for (iter = rec.begin();iter != rec.end();++iter)
	{
		// 
	}
	return 0;
}

// 加载 nl8900 的配置
void CKSConfig::LoadNL8900Config(const CString & basePath)
{
	string fileName = string(basePath) + (LPCTSTR)m_NLConfigFile;
	CCIniFile iniFile(fileName);

	// background picture
	string v = iniFile.ReadString("msgPic","picName","mainface.bmp");
	m_bkPicFile.Format("%s%s",m_picPath,v.c_str());
	// left button pic
	v = iniFile.ReadString("BSAEBUTTONL","picName","buttonL.bmp");
	m_leftBtnPic.Format("%s%s",(LPSTR)(LPCTSTR)m_picPath,v.c_str());
	m_leftBtnPicWidth = iniFile.ReadInteger("BSAEBUTTONR","nWidth",180);
	m_leftBtnPicHeight = iniFile.ReadInteger("BSAEBUTTONR","nHeight",50);
	// right button pic
	v = iniFile.ReadString("BSAEBUTTONR","picName","buttonR.bmp");
	m_rightBtnPic.Format("%s%s",(LPSTR)(LPCTSTR)m_picPath,v.c_str());
	m_rightBtnPicWidth = iniFile.ReadInteger("BSAEBUTTONR","nWidth",180);
	m_rightBtnPicHeight = iniFile.ReadInteger("BSAEBUTTONR","nHeight",50);
	// 
}

// 初始化所有工作流
void CKSConfig::InitWorkflows(void)
{
	m_workflows.Clear();
	CDialog * dlg = (CDialog *)AfxGetMainWnd();
	//dlg->ShowTipMessage("dd");
	srand((unsigned int)time(NULL));
	dlg->Invalidate(FALSE);
	m_workflows.AddWorkflow(new CKSSubsidyWorkFlow(dlg));
	m_workflows.AddWorkflow(new CKSExitWorkFlow(dlg));
	m_workflows.AddWorkflow(new CKSQuerySubsidyWorkflow(dlg));
}

// 删除所有的workflow
void CKSConfig::ReleaseWorkflows(void)
{
	m_workflows.Clear();
}
CDRTPHelper* CKSConfig::CreateDrtpHelper()
{
	CDRTPHelper * ret = new CDRTPHelper((LPCTSTR)m_drtpServer,m_drtpPort,m_drtpFuncNo);
	return ret;
}
