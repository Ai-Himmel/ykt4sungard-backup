// ksinterface_demo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "ksinterface_demo.h"
#include "ksinterface_demoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(Load_Dll);
DEF_DLLFUNC(Load_WorkKey);
DEF_DLLFUNC(ReadSerial);
DEF_DLLFUNC(ReadBalance);


DEF_DLLFUNC(QueryBalance);
DEF_DLLFUNC(CashIncrease);


// Cksinterface_demoApp

BEGIN_MESSAGE_MAP(Cksinterface_demoApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// Cksinterface_demoApp ����

Cksinterface_demoApp::Cksinterface_demoApp():m_interface_(NULL)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� Cksinterface_demoApp ����

Cksinterface_demoApp theApp;


// Cksinterface_demoApp ��ʼ��

BOOL Cksinterface_demoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	if(load_dll()!=0)
	{
		return FALSE;
	}
	Cksinterface_demoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
		//�Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//�Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	// ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int Cksinterface_demoApp::load_dll()
{
	if(m_interface_ != NULL)
		return 0;
	m_interface_ = LoadLibrary("ksinterface.dll");
	if(m_interface_ == NULL)
	{
		AfxMessageBox(_T("����ksinterface.dllʧ��"));
		return -1;
	}
	LOAD_DLLFUNC(m_interface_,ConnectMF);
	LOAD_DLLFUNC(m_interface_,CloseMF);
	LOAD_DLLFUNC(m_interface_,Load_Dll);
	LOAD_DLLFUNC(m_interface_,Load_WorkKey);
	LOAD_DLLFUNC(m_interface_,ReadSerial);
	LOAD_DLLFUNC(m_interface_,ReadBalance);
	LOAD_DLLFUNC(m_interface_,QueryBalance);
	LOAD_DLLFUNC(m_interface_,CashIncrease);
	if(Load_Dll())
	{
		return -1;
	}
	return 0;
}