// bankComm.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CbankCommApp:
// �йش����ʵ�֣������ bankComm.cpp
//

class CbankCommApp : public CWinApp
{
public:
	CbankCommApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CbankCommApp theApp;
