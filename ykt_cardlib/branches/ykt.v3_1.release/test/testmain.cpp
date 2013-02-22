#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#  include <wx/wx.h>
#endif

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <wx/socket.h>

#define KSCARD_TEST_SUITE "kscardlibtest"

int main(int argc, char* argv[])
{
	wxInitialize();
	wxSocketBase::Initialize();
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());
	runner.run("",true);
	wxUninitialize();
	return 0;
}