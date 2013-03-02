
#ifndef __H_SMART_THREAD_H__
#define __H_SMART_THREAD_H__

#include <process.h>

//******************************************************************************
//*����: TThread
//*����: WIN32�̻߳���
//******************************************************************************
class CTThread
{
	public:
		BOOL	m_bShutdown;	//ֹͣ�߳�
		BOOL	m_bSuspend;		//�����߳�
		HANDLE	m_hThread;		//�߳�ID
		DWORD	m_dwThreadID;
		BOOL	m_bStart;		//�����̱߳�ʶ
	protected:
		virtual void Run()=0;
		void OnShutdown();
		void OnStart();			//�������̱߳�ʶ��

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