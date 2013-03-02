#ifndef _THREAD_TEST_H_
#define _THREAD_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <thread.h>

class ThreadTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(ThreadTest);
	CPPUNIT_TEST(testThread);
	CPPUNIT_TEST(testThread2);
	CPPUNIT_TEST_SUITE_END();
private:
	class TestExecThread : public KSGThreadExec<TestExecThread>
	{
	public:
		int value;
		TestExecThread():value(10)
		{
		}
		virtual void Run()
		{
			while(!IsTerminated())
			{
				value = 20;
				Sleep(500);
			}
		}
	};
	class TestFreeThread : public KSGThreadExec<TestFreeThread>
	{
	private:
		bool * _pvalue;
	public:
		TestFreeThread(bool* p):KSGThreadExec(true,true),_pvalue(p)
		{

		}
		virtual ~TestFreeThread()
		{
			*_pvalue = true;	
		}
		virtual void Run()
		{
			Sleep(500);
		}
	};
	TestExecThread * pThread;
	void testThread()
	{	
		pThread->Start();
		KSGThreadUtil::Sleep(1000);
		CPPUNIT_ASSERT(pThread->value == 20);
	}
	void testThread2()
	{
		// 
		bool value = false;
		TestFreeThread * p = new TestFreeThread(&value);
		p->Start();
		Sleep(1000);
		CPPUNIT_ASSERT(value);
		value = false;
		{
			TestFreeThread  p1(&value);
			p1.Start();
			Sleep(1000);
			CPPUNIT_ASSERT(!value);
		}
		CPPUNIT_ASSERT(value);
	}
public:
	void setUp()
	{
		pThread = new TestExecThread;
	}
	void tearDown()
	{
		pThread->Terminate();
		delete pThread;
	}
};
#endif // _THREAD_TEST_H_