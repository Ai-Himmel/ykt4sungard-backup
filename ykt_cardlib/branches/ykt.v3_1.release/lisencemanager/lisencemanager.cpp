// lisencemanager.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "lisencemanager.h"
#include "lisencemanagerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ClisencemanagerApp

BEGIN_MESSAGE_MAP(ClisencemanagerApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// ClisencemanagerApp ����

ClisencemanagerApp::ClisencemanagerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� ClisencemanagerApp ����

ClisencemanagerApp theApp;


// ClisencemanagerApp ��ʼ��

BOOL ClisencemanagerApp::InitInstance()
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
	TCHAR app_path[1025];
	TCHAR *p;
	GetModuleFileName(NULL,app_path,sizeof(app_path)/sizeof(TCHAR)-1);
	p = _tcsrchr(app_path,'\\');
	if(p != NULL)
	{
		*p = 0;
	}
	m_apppath = app_path;
	ClisencemanagerDlg dlg;
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


void ConvertWCS2MBS(LPCTSTR input,DWORD inlen,char *output,DWORD &outlen)
{
#ifdef _UNICODE
	size_t t = 0;
	wcstombs_s(&t,output,outlen,input,outlen);
	outlen = t;
#else
	memcpy(output,input,inlen);
	outlen = inlen;
#endif
}
void ConvertMBS2WCS(const char *input,DWORD inlen,LPSTR output,DWORD &outlen)
{
#ifdef _UNICODE
	size_t t = 0;
	mbstowcs_s(&t,output,outlen,input,outlen);
	outlen = t;
#else
	memcpy(output,input,inlen);
	outlen = inlen;
#endif
}