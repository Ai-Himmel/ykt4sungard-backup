// yuchuandemo.h : PROJECT_NAME 应用程序的主头文件
//
#ifndef _YUCHUANDEMO_H_
#define _YUCHUANDEMO_H_


#pragma once

#ifndef __AFXWIN_H__
	#error 在包含用于 PCH 的此文件之前包含“stdafx.h”
#endif

#include "resource.h"		// 主符号
#include "yuchuandef.h"

// CyuchuandemoApp:
// 有关此类的实现，请参阅 yuchuandemo.cpp
//

class CyuchuandemoApp : public CWinApp
{
public:
	CyuchuandemoApp();

private:
	int LoadAllDLL();
// 重写
	public:
	virtual BOOL InitInstance();


// 实现

	DECLARE_MESSAGE_MAP()
};

extern CyuchuandemoApp theApp;

#endif // _YUCHUANDEMO_H_

