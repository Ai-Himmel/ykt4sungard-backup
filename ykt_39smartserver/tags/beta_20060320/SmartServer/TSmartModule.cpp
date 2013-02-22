// TSmartModule.cpp: implementation of the TSmartModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartModule.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*==================================================================
//*原型: TSmartModule::TSmartModule()
//*功能: 将设备档案结构转为设备打包信息结构
//*参数: 略
//*返回: 无
//*说明: 业务功能插件
//*==================================================================
TSmartModule::TSmartModule()
{
	m_bBusy = false ;

	m_hModule = NULL ;
	lstrcpy(m_sFileName, "");

	m_InitModuleDLL = NULL ;
//	m_ReadSmartDocInfo = NULL ;
	m_DestoryModuleDLL = NULL ;
	m_CreateTaskBuffer = NULL ;
	m_SmartTaskProcess = NULL ;
//	m_ReleaseSmartDoc = NULL ;

	ZeroMemory(&m_Support, sizeof(m_Support));
}

TSmartModule::~TSmartModule()
{
	Destory();
}

//*==================================================================
//*原型: void TSmartModule::Initialized(LPCTSTR pszFileName)
//*功能: 初始化SmartModule
//*参数: 略
//*返回: 无
//*说明: 业务功能插件
//*==================================================================
void TSmartModule::Initialized(LPCTSTR pszFileName)
{
	m_hModule = LoadLibrary(pszFileName);
	if( m_hModule == NULL )
	{
		TCHAR szText[384];
		delete this;

		wsprintf(szText, "不能装入业务功能动态库%s!", pszFileName);
		throw TException(szText, GetLastError());
	}

	m_InitModuleDLL = (lpfnInitModule)GetProcAddress(m_hModule, "InitModuleDLL");
	m_DestoryModuleDLL = (lpfnDestoryModule)GetProcAddress(m_hModule, "DestoryModuleDLL");
	m_CreateTaskBuffer = (lpfnCreateTaskBuffer)GetProcAddress(m_hModule, "CreateTaskBuffer");
	m_SmartTaskProcess = (lpfnSmartTaskProcess)GetProcAddress(m_hModule, "SmartTaskProcess");

	if( !m_InitModuleDLL || !m_DestoryModuleDLL || 
		!m_CreateTaskBuffer || !m_SmartTaskProcess )
	{
		throw TException("非法的业务功能动态库!");
	}

	long nFlag = 0 ;

	if( m_InitModuleDLL(&SmartFunction, &m_Support) != RET_OK )
	{
		throw TException("业务功能动态库初始化失败!");
	}

	if( m_Support.nTaskCount <= 0 )
	{
		throw TException("非法的业务功能动态库!");
	}
}

//*==================================================================
//*原型: void TSmartModule::Destory()
//*功能: 释放SmartModule
//*参数: 略
//*返回: 无
//*说明: 业务功能插件
//*==================================================================
void TSmartModule::Destory()
{
	if( m_hModule != NULL )
	{
		try
		{
			m_DestoryModuleDLL();
		}
		catch(...)
		{
			;
		}

		FreeLibrary(m_hModule);
		m_hModule = NULL ;
	}
}

//*==================================================================
//*原型: bool IsSupport(char *pszTaskCode, char *pszMacType)
//*功能: 支持任务表
//*参数: 略
//*返回: 无
//*说明: 业务功能插件
//*==================================================================
bool TSmartModule::IsSupport(char *pszTaskCode, char *pszMacType)
{
	for(long i=0; i< m_Support.nTaskCount; i++)
	{
		//支持此任务
		if( !strcmp(m_Support.TaskCode[i], pszTaskCode) )
		{
			//机型为空, 表示支持所有的机型
			if( m_Support.nMacCount <= 0 )
			{
				return true;
			}
			else
			{
				//查找是否有支持的机型
				for(long k=0; k<m_Support.nMacCount; k++)
				{
					if( !strcmp(m_Support.MacType[k], pszMacType) )
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}

//*==================================================================
//*原型: bool IsSupportReadDoc()
//*功能: 是否为读档案参数的主表
//*参数: 略
//*返回: 无
//*说明: 保留
//*==================================================================
bool TSmartModule::IsSupportReadDoc()
{
	return true;
}

//*==================================================================
//*原型: bool IsSameModule(LPCTSTR pszFileName)
//*功能: 是否为同名的Module
//*参数: 略
//*返回: 无
//*说明: 保留
//*==================================================================
bool TSmartModule::IsSameModule(LPCTSTR pszFileName)
{
	return (lstrcmp(m_sFileName, pszFileName)==0?true:false);
}

bool TSmartModule::IsBusy() const 
{
	return m_bBusy;
}

void TSmartModule::SetBusy(bool bBusy)
{
	m_bBusy = bBusy ;
}


//*==================================================================
//*原型: TSmartModuleManager::TSmartModuleManager()
//*功能: 业务DLL管理类
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*==================================================================
TSmartModuleManager::TSmartModuleManager()
{
	m_list.Clear();
}

//*==================================================================
//*原型: TSmartModuleManager::TSmartModuleManager()
//*功能: 业务DLL管理类
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*==================================================================
TSmartModuleManager::~TSmartModuleManager()
{
	Destory();
}

void TSmartModuleManager::Initialized()
{

}

//*==================================================================
//*原型: void TSmartModuleManager::Destory()
//*功能: 销毁
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*==================================================================
void TSmartModuleManager::Destory()
{
	m_lock.Lock();
	for(long i=0; i< m_list.GetCount(); i++)
	{
		TSmartModule *pModule = (TSmartModule*)m_list[i];
		if( pModule != NULL )
		{
			if( !pModule->IsBusy() )
			{
				pModule->Destory();
			}
			else
			{
				Sleep(100);
				pModule->Destory();
			}
			delete pModule;
		}
	}
	m_list.Clear();
	m_lock.Unlock();
}

//*==================================================================
//*原型: void TSmartModuleManager::AddModule(LPCTSTR pszFileName)
//*功能: 加入一个业务DLL
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*==================================================================
void TSmartModuleManager::AddModule(LPCTSTR pszFileName)
{
	TSmartModule *pModule = new TSmartModule;
	if( pModule == NULL )
	{
		throw TException("系统内存不足, 装入业务插件时失败!", GetLastError());
	}

	pModule->Initialized(pszFileName);

	m_lock.Lock();
	m_list.Add(pModule);
	m_lock.Unlock();
}

//*==================================================================
//*原型: void TSmartModuleManager::DelModule(LPCTSTR pszFileName)
//*功能: 删除一个业务DLL
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*      本版本不支持业务DLL的热拔插. (因此此函数保留)
//*==================================================================
void TSmartModuleManager::DelModule(LPCTSTR pszFileName)
{
	m_lock.Lock();

	for(long i=0; i< m_list.GetCount(); i++)
	{
		TSmartModule *pModule = (TSmartModule*)m_list[i];
		if( pModule != NULL )
		{
			if( pModule->IsSameModule(pszFileName) )
			{
				pModule->Destory();
				delete pModule;
				m_list.Remove(pModule);
				break;
			}
		}
	}

	m_lock.Unlock();
}


//*==================================================================
//*原型: long TSmartModuleManager::CreateTaskBuffer(TSSmartDocEx *pDocEx, ..)
//*功能: 任务建包
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*==================================================================
long TSmartModuleManager::CreateTaskBuffer(TSSmartDocEx *pDocEx, 
										   TSSmartTask *pTask, 
										   TSCmdBuffer *pBuffer)
{
	TSmartModule *pModule = NULL;
	for(long i=0; i< m_list.GetCount(); i++)
	{
		pModule = (TSmartModule*)m_list[i];
		if( pModule != NULL )
		{
			if( pModule->IsSupport(pTask->szTaskCode, pDocEx->pChildDoc[0]->m_szMacCode) )
			{
				return pModule->m_CreateTaskBuffer(pDocEx, pTask, pBuffer);
			}
		}
	}
//	ReportLog("任务%s, 设备:%ld: 不支持该任务!!", pTask->szTaskCode, (unsigned long)pDocEx->pChildDoc[0]->m_nAuthID);

	return RET_NG;
}

//*==================================================================
//*原型: long TSmartModuleManager::SmartTaskProcess(TSSmartDocEx *pDocEx,...)
//*功能: 任务处理
//*参数: 略
//*返回: 无
//*说明: 业务DLL管理类
//*==================================================================
long TSmartModuleManager::SmartTaskProcess(TSSmartDocEx *pDocEx, 
										   TSSmartTask *pTask, 
										   TSCmdBuffer *pBuffer)
{
	TSmartModule *pModule = NULL;
	for(long i=0; i< m_list.GetCount(); i++)
	{
		pModule = (TSmartModule*)m_list[i];
		if( pModule != NULL )
		{
			if( pModule->IsSupport(pTask->szTaskCode, pDocEx->pChildDoc[0]->m_szMacCode) )
			{
				return pModule->m_SmartTaskProcess(pDocEx, pTask, pBuffer);
			}
		}
	}

	return RET_NG;
}

