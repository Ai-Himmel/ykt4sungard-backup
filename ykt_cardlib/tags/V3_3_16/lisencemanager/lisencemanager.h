// lisencemanager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// ClisencemanagerApp:
// �йش����ʵ�֣������ lisencemanager.cpp
//

class ClisencemanagerApp : public CWinApp
{
public:
	ClisencemanagerApp();
	CString m_apppath;

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern ClisencemanagerApp theApp;

extern void ConvertWCS2MBS(LPCTSTR input,DWORD inlen,char *output,DWORD &outlen);
extern void ConvertMBS2WCS(const char *input,DWORD inlen,LPSTR output,DWORD &outlen);

