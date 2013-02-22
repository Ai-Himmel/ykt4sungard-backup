// TSmartModule.h: interface for the TSmartModule class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TSMARTMODULE_H__35641BB5_6F2A_4E21_86BF_3869AE52F21E__INCLUDED_)
#define AFX_TSMARTMODULE_H__35641BB5_6F2A_4E21_86BF_3869AE52F21E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAC_TYPE_ARRAY_SIZE    32
#define TASK_ARRAY_SIZE  12

//************************************************************************************
//*名称: TSmartModule
//*功能: 业务层模块类
//************************************************************************************
class TSmartModule  
{
protected:
	bool    m_bBusy ;
	HMODULE m_hModule;
	TCHAR   m_sFileName[MAX_PATH];

	TSSmartSupport m_Support;

public:
	lpfnInitModule			  m_InitModuleDLL;
	lpfnDestoryModule         m_DestoryModuleDLL;
	lpfnCreateTaskBuffer      m_CreateTaskBuffer;
	lpfnSmartTaskProcess      m_SmartTaskProcess; 

public:
	TSmartModule();
	virtual ~TSmartModule();

	void Initialized(LPCTSTR pszFileName);
	void Destory();
	bool IsSupport(char *pszTaskCode, char *pszMacType);
	bool IsSupportReadDoc();

	bool IsSameModule(LPCTSTR pszFileName);

	void SetBusy(bool bBusy);
	bool IsBusy() const;
};

//************************************************************************************
//*名称: TSmartModuleManager
//*功能: 业务层模块管理类
//************************************************************************************
class TSmartModuleManager
{
protected:
	TList   m_list;
	TLock   m_lock;

public:
	TSmartModuleManager();
	virtual ~TSmartModuleManager();

	void Initialized();
	void Destory();

	void AddModule(LPCTSTR pszFileName);
	void DelModule(LPCTSTR pszFileName);

	long SmartTaskProcess(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
	long CreateTaskBuffer(TSSmartDocEx *pDocEx, TSSmartTask *pTask, TSCmdBuffer *pBuffer);
};

#endif // !defined(AFX_TSMARTMODULE_H__35641BB5_6F2A_4E21_86BF_3869AE52F21E__INCLUDED_)
