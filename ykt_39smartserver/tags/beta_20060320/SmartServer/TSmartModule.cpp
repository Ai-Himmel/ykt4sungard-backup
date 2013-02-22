// TSmartModule.cpp: implementation of the TSmartModule class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TSmartModule.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//*==================================================================
//*ԭ��: TSmartModule::TSmartModule()
//*����: ���豸�����ṹתΪ�豸�����Ϣ�ṹ
//*����: ��
//*����: ��
//*˵��: ҵ���ܲ��
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
//*ԭ��: void TSmartModule::Initialized(LPCTSTR pszFileName)
//*����: ��ʼ��SmartModule
//*����: ��
//*����: ��
//*˵��: ҵ���ܲ��
//*==================================================================
void TSmartModule::Initialized(LPCTSTR pszFileName)
{
	m_hModule = LoadLibrary(pszFileName);
	if( m_hModule == NULL )
	{
		TCHAR szText[384];
		delete this;

		wsprintf(szText, "����װ��ҵ���ܶ�̬��%s!", pszFileName);
		throw TException(szText, GetLastError());
	}

	m_InitModuleDLL = (lpfnInitModule)GetProcAddress(m_hModule, "InitModuleDLL");
	m_DestoryModuleDLL = (lpfnDestoryModule)GetProcAddress(m_hModule, "DestoryModuleDLL");
	m_CreateTaskBuffer = (lpfnCreateTaskBuffer)GetProcAddress(m_hModule, "CreateTaskBuffer");
	m_SmartTaskProcess = (lpfnSmartTaskProcess)GetProcAddress(m_hModule, "SmartTaskProcess");

	if( !m_InitModuleDLL || !m_DestoryModuleDLL || 
		!m_CreateTaskBuffer || !m_SmartTaskProcess )
	{
		throw TException("�Ƿ���ҵ���ܶ�̬��!");
	}

	long nFlag = 0 ;

	if( m_InitModuleDLL(&SmartFunction, &m_Support) != RET_OK )
	{
		throw TException("ҵ���ܶ�̬���ʼ��ʧ��!");
	}

	if( m_Support.nTaskCount <= 0 )
	{
		throw TException("�Ƿ���ҵ���ܶ�̬��!");
	}
}

//*==================================================================
//*ԭ��: void TSmartModule::Destory()
//*����: �ͷ�SmartModule
//*����: ��
//*����: ��
//*˵��: ҵ���ܲ��
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
//*ԭ��: bool IsSupport(char *pszTaskCode, char *pszMacType)
//*����: ֧�������
//*����: ��
//*����: ��
//*˵��: ҵ���ܲ��
//*==================================================================
bool TSmartModule::IsSupport(char *pszTaskCode, char *pszMacType)
{
	for(long i=0; i< m_Support.nTaskCount; i++)
	{
		//֧�ִ�����
		if( !strcmp(m_Support.TaskCode[i], pszTaskCode) )
		{
			//����Ϊ��, ��ʾ֧�����еĻ���
			if( m_Support.nMacCount <= 0 )
			{
				return true;
			}
			else
			{
				//�����Ƿ���֧�ֵĻ���
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
//*ԭ��: bool IsSupportReadDoc()
//*����: �Ƿ�Ϊ����������������
//*����: ��
//*����: ��
//*˵��: ����
//*==================================================================
bool TSmartModule::IsSupportReadDoc()
{
	return true;
}

//*==================================================================
//*ԭ��: bool IsSameModule(LPCTSTR pszFileName)
//*����: �Ƿ�Ϊͬ����Module
//*����: ��
//*����: ��
//*˵��: ����
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
//*ԭ��: TSmartModuleManager::TSmartModuleManager()
//*����: ҵ��DLL������
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
//*==================================================================
TSmartModuleManager::TSmartModuleManager()
{
	m_list.Clear();
}

//*==================================================================
//*ԭ��: TSmartModuleManager::TSmartModuleManager()
//*����: ҵ��DLL������
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
//*==================================================================
TSmartModuleManager::~TSmartModuleManager()
{
	Destory();
}

void TSmartModuleManager::Initialized()
{

}

//*==================================================================
//*ԭ��: void TSmartModuleManager::Destory()
//*����: ����
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
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
//*ԭ��: void TSmartModuleManager::AddModule(LPCTSTR pszFileName)
//*����: ����һ��ҵ��DLL
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
//*==================================================================
void TSmartModuleManager::AddModule(LPCTSTR pszFileName)
{
	TSmartModule *pModule = new TSmartModule;
	if( pModule == NULL )
	{
		throw TException("ϵͳ�ڴ治��, װ��ҵ����ʱʧ��!", GetLastError());
	}

	pModule->Initialized(pszFileName);

	m_lock.Lock();
	m_list.Add(pModule);
	m_lock.Unlock();
}

//*==================================================================
//*ԭ��: void TSmartModuleManager::DelModule(LPCTSTR pszFileName)
//*����: ɾ��һ��ҵ��DLL
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
//*      ���汾��֧��ҵ��DLL���Ȱβ�. (��˴˺�������)
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
//*ԭ��: long TSmartModuleManager::CreateTaskBuffer(TSSmartDocEx *pDocEx, ..)
//*����: ���񽨰�
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
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
//	ReportLog("����%s, �豸:%ld: ��֧�ָ�����!!", pTask->szTaskCode, (unsigned long)pDocEx->pChildDoc[0]->m_nAuthID);

	return RET_NG;
}

//*==================================================================
//*ԭ��: long TSmartModuleManager::SmartTaskProcess(TSSmartDocEx *pDocEx,...)
//*����: ������
//*����: ��
//*����: ��
//*˵��: ҵ��DLL������
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

