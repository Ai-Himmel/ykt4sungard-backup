// ksgcollect.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CksgcollectApp:
// �йش����ʵ�֣������ ksgcollect.cpp
//

class CksgcollectApp : public CWinApp
{
public:
	CksgcollectApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CksgcollectApp theApp;
