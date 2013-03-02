
#ifndef __H_SMART_THREAD_H__
#define __H_SMART_THREAD_H__

#include <process.h>

//******************************************************************************
//*名称: TThread
//*功能: WIN32线程基类
//******************************************************************************
class CTThread
{
	public:
		BOOL	m_bShutdown;	//停止线程
		BOOL	m_bSuspend;		//挂起线程
		HANDLE	m_hThread;		//线程ID
		DWORD	m_dwThreadID;
		BOOL	m_bStart;		//启动线程标识
	protected:
		virtual void Run()=0;
		void OnShutdown();
		void OnStart();			//将启动线程标识打开

	public:
		CTThread();
		virtual ~CTThread();

		void Start();
		void Shutdown();

		void Terminate(DWORD dwExitCode=0);
		BOOL WaitFor(DWORD dwTimeOut=INFINITE);
		
		void Suspend();
		void Resume();

		BOOL WaitForQuit();

		BOOL IsStart()     const { return m_bStart;   }
		BOOL IsShutdown()  const { return m_bShutdown;}
		BOOL IsSuspend()   const { return m_bSuspend; }
		HANDLE GetHandle() const { return m_hThread;  }

		static unsigned int __stdcall ThreadProc(LPVOID lpvoid);		
};

#endif //SmartThread.h