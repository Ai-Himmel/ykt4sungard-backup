#include "StdAfx.h"
#include "KSMsgDrawer.h"

void KSMsgDrawer::DisplayMessages(CDC * pDC,const CRect & client)
{
	if(!m_showMessage)
		return;
	// 设置字体
	LOGFONT lf;
	memset(&lf,0,sizeof lf);
	lf.lfCharSet = GB2312_CHARSET;
	strcpy(lf.lfFaceName,m_fontName);
	lf.lfHeight = m_fontSize;
	lf.lfWeight = FW_BOLD;
//	lf.lfWeight = FW_MEDIUM;
	
	CFont font;
	CFont *oldFont;
	font.CreateFontIndirect(&lf);
	oldFont = pDC->SelectObject(&font);
	// 如果只有一行就居中
	int line_top = (m_displayMsgList.size() == 1) ? client.Height() / 2 :
		client.Height() / 3;
	int last_line = 1;

	for(cstr_vector::iterator i = m_displayMsgList.begin();
		i != m_displayMsgList.end();++i)
	{
		cstring_msg msg = (*i).second;
		int lineno = msg.GetLineno();
		if( lineno <= 0)
			continue;

		CString msg_str = msg.GetMsg();
		if(msg.GetSizeOffset() != 0)
		{
			pDC->SelectObject(oldFont);						// 新添加将老字体资源获得
			font.DeleteObject();
			lf.lfHeight = m_fontSize + msg.GetSizeOffset();
			font.CreateFontIndirect(&lf);
			//pDC->SelectObject(&font);						// 隐藏掉
			oldFont = pDC->SelectObject(&font);				// 把新的字体资源添加进来
		}
		CSize size = pDC->GetTextExtent(msg_str);
		RECT textRect;
		if (0 == m_MsgDlgflag)
		{
			textRect.left = client.Width() / 5;
 			textRect.right = client.Width();
			m_drawFormat = DT_LEFT;
		}
		else if (1 == m_MsgDlgflag)
		{
			textRect.left = (client.Width() - size.cx) / 2;
			if(textRect.left < 1)
				textRect.left = 1;
			textRect.right = textRect.left + size.cx;
			if (textRect.right >= client.right )
				textRect.right = client.right - 1;
			m_drawFormat = DT_CENTER;
		}
		else if (2 == m_MsgDlgflag)
		{
			textRect.left = client.Width() / 5;
			textRect.right = client.Width();
// 			if (client.right - textRect.left < size.cx)
// 			{
// 				textRect.left = client.right - size.cx;
// 			}
// 			textRect.right = textRect.left + size.cx;
// 			if (textRect.right >= client.right)
// 			{
// 				textRect.right = client.right - 1;
// 			}
			m_drawFormat = DT_RIGHT;
		}
		else
		{
			// 这个位置因为m_MsgDlgflag没有赋值将不会显示图像
		}
		textRect.top = line_top + (lineno - last_line) * size.cy;
		textRect.bottom = client.bottom;
		pDC->DrawText(msg_str,&textRect,m_drawFormat|DT_SINGLELINE);	
		last_line = msg.GetLineno();
		line_top = textRect.top + size.cy / 2 ;
	}
	pDC->SelectObject(oldFont);
}	

void KSMsgDrawer::AddMessageLine(const CString & msg,int lineno /* = 0 */,int size_offset /* = 0 */)
{
	if(0 != lineno)
	{
		if(m_maxLineNo < lineno)
			m_maxLineNo = lineno;
	}
	else
	{
		lineno = ++m_maxLineNo;
	}
	m_msgList[lineno] = cstring_msg(msg,lineno,size_offset);
}

void KSMsgDrawer::AddMessageLineEx(const CString & msg, int lineno /* = 0 */, int size_offset /* = 0 */, int msgDlgflag)
{
	if(0 != lineno)
	{
		if(m_maxLineNo < lineno)
			m_maxLineNo = lineno;
	}
	else
	{
		lineno = ++m_maxLineNo;
	}
	m_msgList[lineno] = cstring_msg(msg,lineno,size_offset);
	m_MsgDlgflag = msgDlgflag;
}

void KSMsgDrawer::DisplayMessage()
{
	m_displayMsgList = m_msgList;
	m_showMessage = true;
	ClearMessageLine();
}

void KSMsgDrawer::Reset()
{
	m_showMessage = false;
	m_maxLineNo = 0;
	ClearMessageLine();
}

void KSMsgDrawer::ShowTipMessage(const CString& msg)
{
	int i = 0,j = 0;
	int lineno = 0;
	Reset();
	do
	{
		i = msg.Find(_T('\n'),i);
		if(i != -1)
		{
			lineno++;
			//　找到换行符
			if(i - j > 0)
			{
				m_msgList[lineno] = cstring_msg(msg.Mid(j,i - j),lineno,0);
			}
			j = ++i;
		}
		else
			break;
	}while (i < msg.GetLength());
	if(j < msg.GetLength())
	{
		lineno++;
		m_msgList[lineno] = cstring_msg(msg.Mid(j),lineno,0);
	}
	m_maxLineNo = lineno;
	m_MsgDlgflag = DT_CENTER;				// 很重要
}