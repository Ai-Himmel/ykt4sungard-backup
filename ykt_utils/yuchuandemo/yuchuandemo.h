// yuchuandemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//
#ifndef _YUCHUANDEMO_H_
#define _YUCHUANDEMO_H_


#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������
#include "yuchuandef.h"

// CyuchuandemoApp:
// �йش����ʵ�֣������ yuchuandemo.cpp
//

class CyuchuandemoApp : public CWinApp
{
public:
	CyuchuandemoApp();

private:
	int LoadAllDLL();
// ��д
	public:
	virtual BOOL InitInstance();


// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CyuchuandemoApp theApp;

#endif // _YUCHUANDEMO_H_

