#ifndef _TEST_SOCKET_H_
#define _TEST_SOCKET_H_

#include <cppunit/extensions/HelperMacros.h>

#include <thread.h>

class TestSocket : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestSocket);
	CPPUNIT_TEST(testServer);
	CPPUNIT_TEST_SUITE_END();
private:
	static class ClientSocket : public KSGThreadExec<ClientSocket>
	{
	public:
		virtual void Run()
		{
			
		}
	};
	void testServer()
	{

	}
public:

};
#endif // _TEST_SOCKET_H_