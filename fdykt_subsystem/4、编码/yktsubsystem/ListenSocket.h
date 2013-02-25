#if !defined(AFX_LISTENSOCKET_H__85485EB3_5924_4375_A98E_0282454E6024__INCLUDED_)
#define AFX_LISTENSOCKET_H__85485EB3_5924_4375_A98E_0282454E6024__INCLUDED_
/** 
 * 模块名						外接子系统
 * 文件名						ListenSocket.h
 * 文件实现功能					服务侦听Socket类
 * 作者							汤成
 * 版本							V0.1
 * 日期							2005-07-02
 * 备注
 * $Id: ListenSocket.h 15 2005-08-22 02:39:12Z cash $
 */

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//


class CYktsubsystemDoc;

/////////////////////////////////////////////////////////////////////////////
// CListenSocket command target

/** 
 * @brief 系统侦听Socket
 */
class CListenSocket : public CAsyncSocket
{
private:
	/** 
	 * @brief Document类的指针
	 */
	CYktsubsystemDoc * m_pDoc;
	/** 
	 * @brief 检查IP是否为允许的IP地址
	 * 
	 * @param inaddr - IP地址
	 * 
	 * @return 
	 */
	BOOL IsAllowAddr(SOCKADDR * inaddr);
// Attributes
public:

// Operations
public:
	/** 
	 * @brief Constructor
	 * 
	 * @param pDoc - Document类的指针
	 */
	CListenSocket(CYktsubsystemDoc * pDoc);
	/** 
	 * @brief Destructor
	 */
	virtual ~CListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListenSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__85485EB3_5924_4375_A98E_0282454E6024__INCLUDED_)
