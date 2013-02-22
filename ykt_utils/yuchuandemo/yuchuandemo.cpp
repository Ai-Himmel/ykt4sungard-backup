// yuchuandemo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "yuchuandemo.h"
#include "AllPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DEF_DLLFUNC(OpenCommAuto);
DEF_DLLFUNC(CloseComm);
DEF_DLLFUNC(JS_GET_RECORD);
DEF_DLLFUNC(JS_SET_Black_Version);
DEF_DLLFUNC(JS_SET_Black);
DEF_DLLFUNC(JS_GetNodeTime);
DEF_DLLFUNC(JS_SET_ONE_Black);
DEF_DLLFUNC(JS_GET_Black_Version);
DEF_DLLFUNC(JS_GET_APPOINTED_RECORD);
DEF_DLLFUNC(JS_SetNodeTime);
DEF_DLLFUNC(JS_GET_SYSTEM_INFO);
DEF_DLLFUNC(JS_SET_SYSTEM_INFO);
DEF_DLLFUNC(JS_SET_Address);
DEF_DLLFUNC(JS_UID_SET_Address);
DEF_DLLFUNC(JS_ShakeHand);
HANDLE g_comhandle;

// CyuchuandemoApp

BEGIN_MESSAGE_MAP(CyuchuandemoApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CyuchuandemoApp ����

CyuchuandemoApp::CyuchuandemoApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CyuchuandemoApp ����

CyuchuandemoApp theApp;


// CyuchuandemoApp ��ʼ��

BOOL CyuchuandemoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
	InitCommonControls();

	//CWinApp::InitInstance();

	//AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	if(LoadAllDLL()!=0)
	{
		AfxMessageBox(_T("�����DLLʧ��"));
		return FALSE;
	}
	//CyuchuandemoDlg dlg;
	CAllPropertySheet dlg(_T("SunGardһ��ͨ-�Demo"));
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

int CyuchuandemoApp::LoadAllDLL()
{
	// ���� DLL ��̬��
	HMODULE h = NULL;
	if((h = LoadLibrary("YC_ISP.dll"))==NULL)
	{
		return -1;
	}
	LOAD_DLLFUNC(h,OpenCommAuto);
	LOAD_DLLFUNC(h,CloseComm);
	LOAD_DLLFUNC(h,JS_GET_RECORD);
	LOAD_DLLFUNC(h,JS_SET_Black_Version);
	LOAD_DLLFUNC(h,JS_SET_Black);
	LOAD_DLLFUNC(h,JS_GetNodeTime);
	LOAD_DLLFUNC(h,JS_SET_ONE_Black);
	LOAD_DLLFUNC(h,JS_GET_Black_Version);
	LOAD_DLLFUNC(h,JS_GET_APPOINTED_RECORD);
	LOAD_DLLFUNC(h,JS_SetNodeTime);
	LOAD_DLLFUNC(h,JS_GET_SYSTEM_INFO);
	LOAD_DLLFUNC(h,JS_SET_SYSTEM_INFO);
	LOAD_DLLFUNC(h,JS_SET_Address);
	LOAD_DLLFUNC(h,JS_UID_SET_Address);
	LOAD_DLLFUNC(h,JS_ShakeHand);

	return 0;
}
