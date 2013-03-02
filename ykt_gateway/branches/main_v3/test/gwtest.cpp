// gwtest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
//#include "smartpooltest.h"
//#include "devicetest.h"
//#include "osutiltest.h"
#include "threadtest.h"
//#include "iostest.h"
#include "testsocket.h"



int _tmain(int argc, _TCHAR* argv[])
{
	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry(GWTEST_SUITE);
	runner.addTest(registry.makeTest());
	runner.run("",true);
	return 0;
}

