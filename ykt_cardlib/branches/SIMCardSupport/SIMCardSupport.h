// SIMCardSupport.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CSIMCardSupportApp:
// �йش����ʵ�֣������ SIMCardSupport.cpp
//

class CSIMCardSupportApp : public CWinApp
{
public:
	CSIMCardSupportApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSIMCardSupportApp theApp;
