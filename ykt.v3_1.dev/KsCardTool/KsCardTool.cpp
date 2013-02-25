// KsCardTool.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "KsCardTool.h"
#include "KsCardToolDlg.h"
#include "kscard_imp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CKsCardToolApp

BEGIN_MESSAGE_MAP(CKsCardToolApp, CWinApp)
    ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


// CKsCardToolApp ����

CKsCardToolApp::CKsCardToolApp() {
    // TODO: �ڴ˴���ӹ�����룬
    // ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CKsCardToolApp ����

CKsCardToolApp theApp;


// CKsCardToolApp ��ʼ��

BOOL CKsCardToolApp::InitInstance() {
    // ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
    // ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
    //����Ҫ InitCommonControls()�����򣬽��޷��������ڡ�
    InitCommonControls();

    CWinApp::InitInstance();

    if (!AfxSocketInit()) {
        AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
        return FALSE;
    }

    AfxEnableControlContainer();

    // ��׼��ʼ��
    // ���δʹ����Щ���ܲ�ϣ����С
    // ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
    // ����Ҫ���ض���ʼ������
    // �������ڴ洢���õ�ע�����
    // TODO: Ӧ�ʵ��޸ĸ��ַ�����
    // �����޸�Ϊ��˾����֯��
    SetRegistryKey(_T("SunGardһ��ͨ�޸Ŀ�����"));

    if(ks_init()) {
        AfxMessageBox("��ʼ��������ʧ��");
        return FALSE;
    }
    if(ks_licence("","")) {
        AfxMessageBox("��������Ȩʧ��");
        return FALSE;
    }

    CKsCardToolDlg dlg;
    m_pMainWnd = &dlg;
    INT_PTR nResponse = dlg.DoModal();
    if (nResponse == IDOK) {
        // TODO: �ڴ˷��ô����ʱ�á�ȷ�������ر�
        //�Ի���Ĵ���
    } else if (nResponse == IDCANCEL) {
        // TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
        //�Ի���Ĵ���
    }

    // ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
    // ����������Ӧ�ó������Ϣ�á�
    return FALSE;
}
