#include "afxwin.h"
#ifndef _KSMSGDRAWER_H_
#define _KSMSGDRAWER_H_

#if _MSC_VER > 1000
#pragma once
#endif 

#include <map>

template<class T>
class CMsgLine
{
private:
	T m_msg;
	int m_posx,m_posy;
	int m_lineno;
	int m_size_offset;
public:
	CMsgLine(T msg,int line,int offset)
	{
		m_msg = msg;
		m_lineno = line;
		m_size_offset = offset;
	}
	CMsgLine()
		:m_lineno(0),m_size_offset(0)
	{
		// 
	}
	CMsgLine(const CMsgLine & msg)
	{
		m_msg = msg.m_msg;
		m_lineno = msg.m_lineno;
		m_size_offset = msg.m_size_offset;
	}
	CMsgLine& operator = (const CMsgLine & rhl)
	{
		m_msg = rhl.m_msg;
		m_lineno = rhl.m_lineno;
		m_size_offset = rhl.m_size_offset;
		return *this;
	}
	bool operator == (const CMsgLine & rhl)
	{
		return m_lineno = rhl.m_lineno;
	}
	bool operator > (const CMsgLine & rhl)
	{
		return m_lineno > rhl.m_lineno;
	}
	bool operator < (const CMsgLine & rhl)
	{
		return m_lineno < rhl.m_lineno;
	}
	~CMsgLine()
	{
		//
	}
	int GetLineno() const {return m_lineno;}
	int GetSizeOffset()const {return m_size_offset;}
	T GetMsg() const {return m_msg;}
};

class KSMsgDrawer
{
private:
	typedef CMsgLine<CString> cstring_msg;
	typedef std::map<int,typename cstring_msg > cstr_vector;
	cstr_vector m_msgList;
	cstr_vector m_displayMsgList;
	int m_maxLineNo;
	bool m_showMessage;
public:
	CString m_fontName;
	int m_fontSize;
public:
	void AddMessageLine(const CString & msg,int lineno = 0,int size_offset = 0);
	int GetMaxLineNo() const {return m_maxLineNo;}
	void DisplayMessage();
	void ClearMessageLine() { m_msgList.clear(); }
	void DisplayMessages(CDC* pDC,const CRect & client);
	void Reset();
	void ShowTipMessage(const CString& msg);
	bool IsMsgShowing()const {return m_showMessage;}
};

#endif // _KSMSGDRAWER_H_