// LoadDll.cpp: implementation of the LoadDll class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <io.h>
#include "DllImport.h"
#include "DllImportDlg.h"
#include "LoadDll.h"
#include "KsDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// import extern dll function
DCLR_KSFUNC(int,SMT_GetDllVersion,(char *ks_ver_no, char *ks_ver_dcb))
DEF_KSFUNC(SMT_GetDllVersion)
//////////////////////////////////////////////////////////////////////////

Load_Dll::Load_Dll() : m_str_file_path(""), m_str_get_dllname(""), m_h_ks_dll(NULL)
{
}

Load_Dll::~Load_Dll()
{
//	::AfxMessageBox("load dllÍË³öÁË");
}

void Load_Dll::FindDllFile()
{
	CFileFind dll_file_finder;
	m_p_cmb_dllname = (CComboBox *)AfxGetMainWnd()->GetDescendantWindow(IDC_COMBO_DLL);
	int str_pos = 1;
	BOOL work_flag = dll_file_finder.FindFile("KS_*.dll");
	while (work_flag)
	{
		work_flag = dll_file_finder.FindNextFile();
		m_p_cmb_dllname->InsertString(str_pos, (LPCTSTR)dll_file_finder.GetFileName());
		++str_pos;
	}

	dll_file_finder.Close();
	if (work_flag = dll_file_finder.FindFile("SmartCom411DXQ.dll"))
	{
		dll_file_finder.FindNextFile();
		m_p_cmb_dllname->InsertString(str_pos, (LPCTSTR)dll_file_finder.GetFileName());
	}
	dll_file_finder.Close();
}


int Load_Dll::GetInitFile(const char *purpose_file_buf)
{
	char path_buf[512] = "";
	int len = GetModuleFileName(NULL, path_buf, sizeof(path_buf));
	if (len <= 0)
	{
		return -1;
	}

	char *path_pos = path_buf + len;
	while (path_pos >= path_buf)
	{
		if (*path_pos == '\\')
		{
			break;
		}
		path_pos--;
	}
	if (path_pos > path_buf)
	{
		*path_pos = '\0';
	}
	if (!strnicmp(path_pos - 4, "\\dll", 4))
	{
		path_pos -= 4;
		*path_pos = '\0';
	}

	m_str_file_path.Format(path_buf);
	m_str_file_path += purpose_file_buf;
	return 0;
}

int Load_Dll::LoadVersion()
{
	int ret = 0;
	char ks_ver_no[20] = "";
	char ks_ver_dcb[80] = "";
	m_p_txt_ver_no = (CStatic *)AfxGetMainWnd()->GetDescendantWindow(IDC_STATIC_VERSION_NO);
	m_p_txt_ver_dcb = (CStatic *)AfxGetMainWnd()->GetDescendantWindow(IDC_STATIC_VERSION_DESCRIBE);
	m_p_cmb_dllname->GetWindowText(m_str_get_dllname);
	if (_access((LPCSTR)(LPCTSTR)m_str_file_path, 0) == -1)
		return KS_ERR_NOINITFILE;

	WritePrivateProfileString("LOADLIBRARY", "DLL1", m_str_get_dllname, m_str_file_path);

	if (ret = LoadKingStarDll())
		return ret ;

	if (ret = SMT_GetDllVersion(ks_ver_no, ks_ver_dcb))
		return KS_ERR_GETVERSION;
	
	m_p_txt_ver_no->SetWindowText(ks_ver_no);
	m_p_txt_ver_dcb->SetWindowText(ks_ver_dcb);
	return 0;	
}

int Load_Dll::LoadKingStarDll()
{	
	m_h_ks_dll = ::LoadLibrary(m_str_get_dllname);
	
	if (m_h_ks_dll == NULL)
		return KS_ERR_LOADLIBRARY;
	
	LOAD_KSFUNC(m_h_ks_dll,SMT_GetDllVersion);
	return 0;	
}

void Load_Dll::UnLoadKingStarDll()
{
	if (m_h_ks_dll)
	{
		::FreeLibrary(m_h_ks_dll);
		m_h_ks_dll = NULL;
	}
	return ;
}