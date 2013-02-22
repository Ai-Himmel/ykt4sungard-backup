#pragma once

#include <windows.h>
#include <string>
using namespace std;

#define ERR_OPEN_FILE -1

class CFileClass
{
public:
	CFileClass(void);
	~CFileClass(void);

	enum
	{
		modeCreate		= 0x1,
		modeRead		= 0x2,
		modeWrite       = 0x4,
		shareDenyNone   = 0x8,
	};

	enum
	{
		begin     = FILE_BEGIN,
		end		  = FILE_END,
		current   = FILE_CURRENT,
	};
	
	enum
	{
		c_new     = CREATE_NEW,
		c_always  = CREATE_ALWAYS,
		o_exist   = OPEN_EXISTING,
		o_always  = OPEN_ALWAYS,
		t_exist	  = TRUNCATE_EXISTING,
	};

	bool IsOpen();
	void Close();
	void SetEnd();
	void SeekToEnd();
	DWORD GetPosition();
	DWORD GetLength();
	DWORD Read(void *pBuf, int bufSize);
	BOOL FlushBuffers();
	DWORD Write(void *pData, int size);
	DWORD Seek(int dwSize, int mode);
	string GetLine();
	bool Open(LPCSTR lpFile, int mode);
	bool Open(const string &sfile, int mode);
	void SetModeFlag(DWORD access_mode, DWORD create_mode);
	void SetFlushDelay(int flush_delay_second);
	BOOL FileExist(TCHAR *str_file);
	BOOL SetMoveFile(TCHAR *src_file, TCHAR *dest_file);	// Դ�ļ���Ŀ���ļ���·��

private:
	HANDLE                m_hFile;
	string                m_sBuffer;                // ������
	DWORD				  m_amode;					// ��д����
	DWORD				  m_cmode;					// �ļ���־
	bool                  m_set_flag;				// ����ģʽ��־
	time_t                m_last_time;				// ˢ���ϴ�ʱ��
	int					  m_flash_delay;			// ˢ����ʱ, ��λ��
};
