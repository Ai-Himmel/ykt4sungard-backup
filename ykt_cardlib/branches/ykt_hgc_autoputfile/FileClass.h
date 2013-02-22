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
	BOOL SetMoveFile(TCHAR *src_file, TCHAR *dest_file);	// 源文件和目标文件带路径

private:
	HANDLE                m_hFile;
	string                m_sBuffer;                // 缓冲区
	DWORD				  m_amode;					// 读写内容
	DWORD				  m_cmode;					// 文件标志
	bool                  m_set_flag;				// 设置模式标志
	time_t                m_last_time;				// 刷新上次时间
	int					  m_flash_delay;			// 刷新延时, 单位秒
};
