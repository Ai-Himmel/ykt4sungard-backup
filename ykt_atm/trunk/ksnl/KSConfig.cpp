#include "stdafx.h"
#include <string>
#include ".\ksconfig.h"
#include "CIniFile.h"
#include "ksnl.h"

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
	CKsnlApp * app = (CKsnlApp*)AfxGetApp();
	//	CString cs;                                             // 测试
	// 读取knls.ini文件
	string v = inifile.ReadString("GLOBAL","NLCONF","");
	m_NLConfigFile.Format("%s",v.c_str());                  // v代表GLOBAL里面NLCONF下的值nl8900face.ini
//	AfxMessageBox(v.c_str());
	v = inifile.ReadString("COM","RFCOM","");
	m_RFComPort.Format("%s",v.c_str());
	v = inifile.ReadString("COM","ICCOM","");
	m_ICComPort.Format("%s",v.c_str());
	v = inifile.ReadString("GLOBAL","PICPATH","pic\\");
	m_picPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());	
	v = inifile.ReadString("GLOBAL","KSCOM","KS_SMTCard.dll");
//	AfxMessageBox("加载KS_SMTCard.dll完毕!!!");               // 测试部分
	/*	m_KSComDLLPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());*/
	m_CardDLLPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());
	v = inifile.ReadString("GLOBAL","SYSCFG","system.ini");
	m_NLSysCfgFile.Format("%s",v.c_str());
	m_idleTime = inifile.ReadInteger("GLOBAL","IDLETIME",10);
	// 读取字体属性
	v = inifile.ReadString("GLOBAL","FONTNAME","宋体");
	m_fontName.Format("%s",v.c_str());
//	AfxMessageBox(m_fontName);
	v = inifile.ReadString("GLOBAL","FONTCOLOR","0xFF0000");
	int color = strtoul(v.c_str(),NULL,16);
	m_fontColor = MAKECOLOR(color);
	m_fontSize = inifile.ReadInteger("GLOBAL","FONTSIZE",24);
	// 传进来一个menuid号, 从param结构中传来的number
//	m_menuId = app->m_param.number;
 	//////////////////////////////////////////////////////////////////////////
// 	CString cs;
//  cs.Format("%d", m_menuId);
// 	AfxMessageBox(cs);
	//////////////////////////////////////////////////////////////////////////
	// 读取所有功能配置
	vector<string> sections;
	inifile.ReadSections(sections);
	vector<string>::iterator iter;
	for (iter = sections.begin();iter != sections.end();++iter)
	{
		string sect = *iter;
		if(sect.substr(0,4) == "FUNC") 
		{
			// 判断menuid号为1或者为0则读出来
// 			if (
// 				m_menuId == inifile.ReadInteger(sect.c_str(), "menuid", -2) || 0 == inifile.ReadInteger(sect.c_str(), "menuid", -2) || 
// 				m_menuId == inifile.ReadInteger(sect.c_str(), "menuid", -2) || m_menuId == inifile.ReadInteger(sect.c_str(), "menuid", -2)
// 				)
//			{
				v = inifile.ReadString(sect.c_str(),"func","");
		//		AfxMessageBox(sect.c_str());
				if(!v.empty())
				{
					CKSWorkflow * workflow = m_workflows.FindWorkflow(CString(v.c_str()));
					if(workflow != NULL)
					{
						// 加载配置, 这个位置来判断是否加载，加载几个位置, 比如领取补贴，查询补贴，返回等等
						v = inifile.ReadString(sect.c_str(),"text","");
						workflow->m_funcText.Format("%s",v.c_str());
						v = inifile.ReadString(sect.c_str(),"key","");
						workflow->m_key.Format("%s",v.c_str());
						workflow->m_posX = inifile.ReadInteger(sect.c_str(),"posx",-1);
						workflow->m_posY = inifile.ReadInteger(sect.c_str(),"posy",-1);
					}
				}
//			}
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
	CKsnlApp * app = (CKsnlApp*)AfxGetApp();
	CDialog * dlg = (CDialog *)AfxGetMainWnd();
	string fileName = string(app->m_appPath) + CKSConfig::ms_configFile;
	CCIniFile inifile(fileName);
	//dlg->ShowTipMessage("dd");
	srand((unsigned int)time(NULL));
	dlg->Invalidate(FALSE);
	//////////////////////////////////////////////////////////////////////////
	// 用func名字来判断读取的工作流是否应该添加进去
	vector<string> sections;
	inifile.ReadSections(sections);
	vector<string>::iterator iter;
	//////////////////////////////////////////////////////////////////////////
	for (iter = sections.begin(); iter != sections.end(); ++iter)
	{
		string sect = *iter;
		if (sect.substr(0, 4) == "FUNC")
		{
			string 	v = inifile.ReadString(sect.c_str(),"func","");
			if (!v.empty())
			{
				if (app->m_param.number == 1)
				{
					if (v == "subsidy")
					{
						m_workflows.AddWorkflow(new CKSSubsidyWorkFlow(dlg));	               // 补助领取  
					}
						else if (v == "Sreissuecard") 
					{
						m_workflows.AddWorkflow(new CKSSreissueWorkFlow(dlg));			   // 查询补贴
					}
//	             	else if (v == "CancelSreissuecard") 
//					{
//暂时没用						m_workflows.AddWorkflow(new CKSCancelSreissueWorkFlow(dlg));			   // 查询补贴
//					}

					else if (v == "qrysubsidy") 
					{
						m_workflows.AddWorkflow(new CKSQuerySubsidyWorkflow(dlg));			   // 查询补贴
					}
					else if (v == "ModifyCardInfo")
					{
						m_workflows.AddWorkflow(new CKModifyCardInfoWorkflow(dlg));			   // 更新卡信息
					}
					else if (v == "QueryMendCard")											   
					{
//xiao						m_workflows.AddWorkflow(new CKQueryMendCardWorkflow(dlg));			   // 查询补写卡信息
					}
					else if (v == "MendCard")
					{
//xiao						m_workflows.AddWorkflow(new CKMendCardWorkflow(dlg));				   // 补写卡信息
					}
					else if (v == "board_reckon")
					{
//xiao						m_workflows.AddWorkflow(new CKRemainBoardReckonWorkFlow(dlg));		   // 剩余搭伙费清算		
					}
					else 
					{
						//
					}
				}
				else if (app->m_param.number == 2)
				{
					if (v == "QueryNetCharge")
					{
//xiao						m_workflows.AddWorkflow(new CKQueryNetChargeWorkFlow(dlg));	
					}
					else if (v == "NetCharge")
					{
						m_workflows.AddWorkflow(new CKNetChargeTransferWorkFlow(dlg));
					}
					else
					{
						//
					}
					/*
					if (v == "qrywatervol")
					{
//						m_workflows.AddWorkflow(new CKSQueryWaterVolumnWorkFlow(dlg));		   // 查询水量
					}
					else if (v == "qryTrfAct")
					{
//						m_workflows.AddWorkflow(new CKSQueryTransferAccoutsWorkFlow(dlg));	   // 查询转帐明细	
					}
					else if (v == "waterpacketrf")
					{
//						m_workflows.AddWorkflow(new CKSWaterPacketTransferWorkFlow(dlg));	   // 水控钱包转帐
					}
					else if (v == "InitCard")
					{
//						m_workflows.AddWorkflow(new CKSInitCardWorkFlow(dlg));				   // 做定点卡
					}
					else if (v == "cancel")
					{
//						m_workflows.AddWorkflow(new CKSCancelTermCardWorkFlow(dlg));		   // 取消定点卡	
					}
					else 
					{
						//
					}
					*/
				}
				else if (app->m_param.number == 3)
				{
					if (v == "ElePackAccTrf") 
					{
//						m_workflows.AddWorkflow(new CKSQueryEleTransferAccoutsWorkFlow(dlg));  // 查询电控转帐				
					}
					else
					{
						//
					}
				}
				else if (app->m_param.number == 4)
				{
					if (v == "NetCharge")
					{
//						m_workflows.AddWorkflow(new CKNetChargeTransferWorkFlow(dlg));		   // 网络收费	
					}
					else
					{
						//
					}
				}
				else
				{
					//
				}
			}
		}
	}
	m_workflows.AddWorkflow(new CKSExitWorkFlow(dlg));						   // 退出
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
