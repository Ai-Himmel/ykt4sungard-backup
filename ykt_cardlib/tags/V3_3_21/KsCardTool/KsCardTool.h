// KsCardTool.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CKsCardToolApp:
// �йش����ʵ�֣������ KsCardTool.cpp
//

class CKsCardToolApp : public CWinApp
{
public:
	CKsCardToolApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CKsCardToolApp theApp;
