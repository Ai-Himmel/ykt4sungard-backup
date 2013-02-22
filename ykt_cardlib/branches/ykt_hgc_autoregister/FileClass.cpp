#include "stdafx.h"
#include ".\fileclass.h"
#include <time.h>

CFileClass::CFileClass(void)
{
	m_hFile = NULL;
	m_set_flag = false;
	m_amode = 0;
	m_cmode = 0;
	m_flash_delay = 0;
}

CFileClass::~CFileClass(void)
{
	Close();
}

bool CFileClass::IsOpen()
{
	return m_hFile == NULL? false:true;
}

void CFileClass::Close()
{
	if (m_hFile) { CloseHandle(m_hFile); }
	m_hFile = NULL;
	m_last_time = time(NULL);
}

void CFileClass::SetEnd()
{
	if (m_hFile) { SetEndOfFile(m_hFile); }
}

void CFileClass::SeekToEnd()
{
	if (m_hFile) { SetFilePointer(m_hFile, 0, NULL, FILE_END); }
}

DWORD CFileClass::GetPosition()        
{
	if (m_hFile) 
	{ 
		return SetFilePointer(m_hFile, 0, NULL, FILE_CURRENT); 
	}
	else
		return 0;
}

DWORD CFileClass::GetLength()        
{
	DWORD  dwRet      = 0;
	DWORD  dwCurrent  = 0;

	if (m_hFile)
	{
		dwCurrent = GetPosition();
		dwRet = SetFilePointer(m_hFile, 0, NULL, FILE_END);
		SetFilePointer(m_hFile, dwCurrent, NULL, FILE_BEGIN);
		return dwRet;
	}
	else
		return 0;
}

DWORD CFileClass::Read(void *pBuf, int bufSize) 
{
	DWORD dwRead = 0;
	if (m_hFile) { ReadFile(m_hFile, pBuf, bufSize, &dwRead, NULL); }
	return dwRead;
}

BOOL CFileClass::FlushBuffers()
{
	if (m_hFile) 
		return FlushFileBuffers(m_hFile);
	else 
		return FALSE;
}

DWORD CFileClass::Write(void *pData, int size) 
{
	DWORD dwWrite = 0;
	DWORD dwError = 0;
	time_t current_time;
	time(&current_time);

	if (m_hFile)
	{
		if (!WriteFile(m_hFile, pData, size, &dwWrite, NULL))
			dwError = GetLastError();
		else
		{
			if (current_time - m_last_time > m_flash_delay)
			{
				FlushBuffers();
				m_last_time = current_time;
			}
		}
	}
		
	return dwWrite;
}

DWORD CFileClass::Seek(int dwSize, int mode)
{
	if (m_hFile) { return SetFilePointer(m_hFile, dwSize, NULL, mode); }	
	return 0;
}

string CFileClass::GetLine()
{
	if (!m_hFile)
		return "";

	string sRet = "";
	string::size_type nPos;
	DWORD dwRead = 0;
	DWORD dwStart = 0;
	char szData[512 * 1024]= "";

	// 如果缓冲区空了或者缓冲区没有找到回车换行则从文件中读取数据
LOOP: while((m_sBuffer.empty() || (nPos = m_sBuffer.find("\n", dwStart)) == string::npos))
	  {
		  if (dwRead != 0)
			  dwStart += dwRead;
		  //如果读文件到末尾则返回
		  if (!ReadFile(m_hFile, szData, sizeof(szData), &dwRead, NULL))
		  {
			  if (!m_sBuffer.empty())
			  {
				  sRet = m_sBuffer;
				  m_sBuffer.erase();
			  }
			  return sRet;
		  }
		  else if (dwRead == 0)
		  {
			  return sRet;
		  }
		  else
		  {
			  NULL;
		  }
		  
		  m_sBuffer.append(szData, dwRead);
	  }

	  sRet.append(m_sBuffer.data(), nPos);
	  m_sBuffer.erase(0, nPos + 2);
	  
	  if (sRet.empty())
		  goto LOOP;

	  return sRet;
}

bool CFileClass::Open(LPCSTR lpFile, int mode)
{
	if (false == m_set_flag)
	{
		m_cmode = mode;
		if (m_cmode & modeRead)
			m_amode = GENERIC_READ;

		if (m_cmode & modeWrite) 
			m_amode |=GENERIC_WRITE;

		if (m_cmode & modeCreate) 
		{
			m_amode = GENERIC_READ | GENERIC_WRITE;
			m_cmode = CREATE_ALWAYS;
		}
		else
			m_cmode = OPEN_EXISTING;	
	}

	m_set_flag = false;
	time(&m_last_time);

	m_hFile = CreateFile(lpFile, m_amode, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, m_cmode, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hFile != INVALID_HANDLE_VALUE) { return TRUE; }
	
	m_hFile = NULL;
	return FALSE;
}

bool CFileClass::Open(const string &sfile, int mode)
{
	return Open(sfile.c_str(), mode);
}

void CFileClass::SetModeFlag(DWORD access_mode, DWORD create_mode)
{
	m_amode = access_mode;
	m_cmode = create_mode;
	m_set_flag = true;
}

void CFileClass::SetFlushDelay(int flush_delay_second)
{
	m_flash_delay = flush_delay_second;
}

BOOL CFileClass::FileExist(TCHAR *str_file)
{
	return (INVALID_FILE_ATTRIBUTES != GetFileAttributes(str_file));
}

BOOL CFileClass::SetMoveFile(TCHAR *src_file, TCHAR *dest_file)
{
	return ::MoveFile(src_file, dest_file);
}