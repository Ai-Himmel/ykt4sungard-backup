// LoadDll.cpp: implementation of the LoadDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ModifyCardDemo.h"
#include "LoadDll.h"
#include "GlobalDef.h"
#include "CIniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//CExceptionErr err_exce;
//////////////////////////////////////////////////////////////////////////
// import extern dll function
DEF_DLLFUNC(ConnectMF);
DEF_DLLFUNC(CloseMF);
DEF_DLLFUNC(ControlBuzzer);
DEF_DLLFUNC(SMT_ChangeShowCardNo);
DEF_DLLFUNC(SMT_ChangeDealCardNo);
DEF_DLLFUNC(SMT_ReadCardStateInfo);
DEF_DLLFUNC(ReadCardMainKey);
DEF_DLLFUNC(SMT_AutoDll);
DEF_DLLFUNC(ReadCardInfo);
DEF_DLLFUNC(SMT_ChangeCardNo);
DEF_DLLFUNC(InitNewAuthCard);
DEF_DLLFUNC(ResetNewAuthCard);
DEF_DLLFUNC(SMT_ReadAuthorWorkKeyAndFlag);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLoadDll::CLoadDll() : m_h_ks_dll(NULL), m_str_get_dllname("CardDLL.dll")
{

}

CLoadDll::~CLoadDll()
{
	UnLoadKingStarDll();
}

int CLoadDll::LoadKingStarDll()
{
	m_h_ks_dll = ::LoadLibrary(m_str_get_dllname.c_str());
	if (m_h_ks_dll == NULL)
		return err_exce.SearchErr(KS_ERR_LOADLIBRARY);
	
	LOAD_DLLFUNC(m_h_ks_dll,ConnectMF);
	LOAD_DLLFUNC(m_h_ks_dll,CloseMF);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeShowCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeDealCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadCardStateInfo);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardMainKey);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_AutoDll);
	LOAD_DLLFUNC(m_h_ks_dll,ControlBuzzer);
	LOAD_DLLFUNC(m_h_ks_dll,ReadCardInfo);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ChangeCardNo);
	LOAD_DLLFUNC(m_h_ks_dll,InitNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,ResetNewAuthCard);
	LOAD_DLLFUNC(m_h_ks_dll,SMT_ReadAuthorWorkKeyAndFlag);
	return 0;
}

void CLoadDll::UnLoadKingStarDll()
{
	if (m_h_ks_dll)
	{
		::FreeLibrary(m_h_ks_dll);
		m_h_ks_dll = NULL;
	}
	return ;
}

int CLoadDll::LoadAllInfo()
{
	int ret = 0;
	if (ret = LoadKingStarDll())
	{
		UnLoadKingStarDll();
		return ret;
	}
		
	return 0;
}
