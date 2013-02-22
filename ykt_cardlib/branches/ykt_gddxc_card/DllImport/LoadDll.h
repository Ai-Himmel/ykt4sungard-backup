// LoadDll.h: interface for the LoadDll class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOADDLL_H__DF23BF22_4355_47A7_8AF0_C4228252E212__INCLUDED_)
#define AFX_LOADDLL_H__DF23BF22_4355_47A7_8AF0_C4228252E212__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class LoadDll  
{
private:
	CString m_str_file_path; 
//	CString m_str_dll_ver;
	CString m_str_get_dllname;
	CComboBox *m_p_cmb_dllname;
	CStatic *m_p_txt_ver_no;
	CStatic *m_p_txt_ver_dcb;
	HINSTANCE m_h_ks_dll;
	
public:
	FindDllFile();
	LoadDll();
//	ReadDllVersion(char *dll_ver);
	int GetInitFile(const char *purpose_file_buf);
	int LoadVersion();
	int LoadKingStarDll();
	void UnLoadKingStarDll();
	virtual ~LoadDll();
};

#endif // !defined(AFX_LOADDLL_H__DF23BF22_4355_47A7_8AF0_C4228252E212__INCLUDED_)
