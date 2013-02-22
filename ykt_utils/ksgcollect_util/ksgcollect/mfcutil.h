#ifndef _KSG_MFCUTIL_H_
#define _KSG_MFCUTIL_H_

#pragma once

class CDirDialog
{
public:
	CDirDialog();
	~CDirDialog();
	int DoModal(CWnd *pParent = NULL);

	CString   m_strPath;  
	CString   m_strInitDir;  
	CString   m_strSelDir;  
	CString   m_strWindowTitle;  
	int     m_iImageIndex; 
};

#endif // _KSG_MFCUTIL_H_
