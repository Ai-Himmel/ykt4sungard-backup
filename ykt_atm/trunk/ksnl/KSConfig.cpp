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

// ���ر�������
void CKSConfig::LoadKSNLConfig(const CString& basePath)
{
	string fileName = string(basePath) + CKSConfig::ms_configFile;
	CCIniFile inifile(fileName);
	CKsnlApp * app = (CKsnlApp*)AfxGetApp();
	//	CString cs;                                             // ����
	// ��ȡknls.ini�ļ�
	string v = inifile.ReadString("GLOBAL","NLCONF","");
	m_NLConfigFile.Format("%s",v.c_str());                  // v����GLOBAL����NLCONF�µ�ֵnl8900face.ini
//	AfxMessageBox(v.c_str());
	v = inifile.ReadString("COM","RFCOM","");
	m_RFComPort.Format("%s",v.c_str());
	v = inifile.ReadString("COM","ICCOM","");
	m_ICComPort.Format("%s",v.c_str());
	v = inifile.ReadString("GLOBAL","PICPATH","pic\\");
	m_picPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());	
	v = inifile.ReadString("GLOBAL","KSCOM","KS_SMTCard.dll");
//	AfxMessageBox("����KS_SMTCard.dll���!!!");               // ���Բ���
	/*	m_KSComDLLPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());*/
	m_CardDLLPath.Format("%s%s",(LPSTR)(LPCTSTR)basePath,v.c_str());
	v = inifile.ReadString("GLOBAL","SYSCFG","system.ini");
	m_NLSysCfgFile.Format("%s",v.c_str());
	m_idleTime = inifile.ReadInteger("GLOBAL","IDLETIME",10);
	// ��ȡ��������
	v = inifile.ReadString("GLOBAL","FONTNAME","����");
	m_fontName.Format("%s",v.c_str());
//	AfxMessageBox(m_fontName);
	v = inifile.ReadString("GLOBAL","FONTCOLOR","0xFF0000");
	int color = strtoul(v.c_str(),NULL,16);
	m_fontColor = MAKECOLOR(color);
	m_fontSize = inifile.ReadInteger("GLOBAL","FONTSIZE",24);
	// ������һ��menuid��, ��param�ṹ�д�����number
//	m_menuId = app->m_param.number;
 	//////////////////////////////////////////////////////////////////////////
// 	CString cs;
//  cs.Format("%d", m_menuId);
// 	AfxMessageBox(cs);
	//////////////////////////////////////////////////////////////////////////
	// ��ȡ���й�������
	vector<string> sections;
	inifile.ReadSections(sections);
	vector<string>::iterator iter;
	for (iter = sections.begin();iter != sections.end();++iter)
	{
		string sect = *iter;
		if(sect.substr(0,4) == "FUNC") 
		{
			// �ж�menuid��Ϊ1����Ϊ0�������
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
						// ��������, ���λ�����ж��Ƿ���أ����ؼ���λ��, ������ȡ��������ѯ���������صȵ�
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

// �������ù���
int CKSConfig::LoadFunction(const map<string,string> &rec)
{
	// ���ع�������
	map<string,string>::const_iterator iter;
	for (iter = rec.begin();iter != rec.end();++iter)
	{
		// 
	}
	return 0;
}

// ���� nl8900 ������
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

// ��ʼ�����й�����
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
	// ��func�������ж϶�ȡ�Ĺ������Ƿ�Ӧ����ӽ�ȥ
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
						m_workflows.AddWorkflow(new CKSSubsidyWorkFlow(dlg));	               // ������ȡ  
					}
						else if (v == "Sreissuecard") 
					{
						m_workflows.AddWorkflow(new CKSSreissueWorkFlow(dlg));			   // ��ѯ����
					}
//	             	else if (v == "CancelSreissuecard") 
//					{
//��ʱû��						m_workflows.AddWorkflow(new CKSCancelSreissueWorkFlow(dlg));			   // ��ѯ����
//					}

					else if (v == "qrysubsidy") 
					{
						m_workflows.AddWorkflow(new CKSQuerySubsidyWorkflow(dlg));			   // ��ѯ����
					}
					else if (v == "ModifyCardInfo")
					{
						m_workflows.AddWorkflow(new CKModifyCardInfoWorkflow(dlg));			   // ���¿���Ϣ
					}
					else if (v == "QueryMendCard")											   
					{
//xiao						m_workflows.AddWorkflow(new CKQueryMendCardWorkflow(dlg));			   // ��ѯ��д����Ϣ
					}
					else if (v == "MendCard")
					{
//xiao						m_workflows.AddWorkflow(new CKMendCardWorkflow(dlg));				   // ��д����Ϣ
					}
					else if (v == "board_reckon")
					{
//xiao						m_workflows.AddWorkflow(new CKRemainBoardReckonWorkFlow(dlg));		   // ʣ���������		
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
//						m_workflows.AddWorkflow(new CKSQueryWaterVolumnWorkFlow(dlg));		   // ��ѯˮ��
					}
					else if (v == "qryTrfAct")
					{
//						m_workflows.AddWorkflow(new CKSQueryTransferAccoutsWorkFlow(dlg));	   // ��ѯת����ϸ	
					}
					else if (v == "waterpacketrf")
					{
//						m_workflows.AddWorkflow(new CKSWaterPacketTransferWorkFlow(dlg));	   // ˮ��Ǯ��ת��
					}
					else if (v == "InitCard")
					{
//						m_workflows.AddWorkflow(new CKSInitCardWorkFlow(dlg));				   // �����㿨
					}
					else if (v == "cancel")
					{
//						m_workflows.AddWorkflow(new CKSCancelTermCardWorkFlow(dlg));		   // ȡ�����㿨	
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
//						m_workflows.AddWorkflow(new CKSQueryEleTransferAccoutsWorkFlow(dlg));  // ��ѯ���ת��				
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
//						m_workflows.AddWorkflow(new CKNetChargeTransferWorkFlow(dlg));		   // �����շ�	
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
	m_workflows.AddWorkflow(new CKSExitWorkFlow(dlg));						   // �˳�
}

// ɾ�����е�workflow
void CKSConfig::ReleaseWorkflows(void)
{
	m_workflows.Clear();
}
CDRTPHelper* CKSConfig::CreateDrtpHelper()
{
	CDRTPHelper * ret = new CDRTPHelper((LPCTSTR)m_drtpServer,m_drtpPort,m_drtpFuncNo);
	return ret;
}
