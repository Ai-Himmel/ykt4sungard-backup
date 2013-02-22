#include "StdAfx.h"
#include "KSMsgDrawer.h"

void KSMsgDrawer::DisplayMessages(CDC * pDC,const CRect & client)
{
	if(!m_showMessage)
		return;
	// ��������
	LOGFONT lf;
	memset(&lf,0,sizeof lf);
	lf.lfCharSet = GB2312_CHARSET;
	strcpy(lf.lfFaceName,m_fontName);
	lf.lfHeight = m_fontSize;
	lf.lfWeight = FW_BOLD;

	CFont font;
	CFont *oldFont;
	font.CreateFontIndirect(&lf);
	oldFont = pDC->SelectObject(&font);
	// ���ֻ��һ�о;���
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
			pDC->SelectObject(oldFont);						// ����ӽ���������Դ���
			font.DeleteObject();
			lf.lfHeight = m_fontSize + msg.GetSizeOffset();
			font.CreateFontIndirect(&lf);
			//pDC->SelectObject(&font);						// ���ص�
			oldFont = pDC->SelectObject(&font);				// ���µ�������Դ��ӽ���
		}
		CSize size = pDC->GetTextExtent(msg_str);
		RECT textRect;
		textRect.left = (client.Width() - size.cx) / 2;
		if(textRect.left < 1)
			textRect.left = 1;
		textRect.right = textRect.left + size.cx;
		if (textRect.right >= client.right )
			textRect.right = client.right - 1;
		textRect.top = line_top + (lineno - last_line) * size.cy;
		textRect.bottom = client.bottom;
		pDC->DrawText(msg_str,&textRect,DT_CENTER|DT_SINGLELINE);
		last_line = msg.GetLineno();
		line_top = textRect.top + size.cy;
	}
	pDC->SelectObject(oldFont);								 // ���վ�������Դ
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
			//���ҵ����з�
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
}