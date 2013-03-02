// gwtest.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "smartpooltest.h"
#include "devicetest.h"
#include "osutiltest.h"
#include "threadtest.h"
#include "iostest.h"
#include "testsocket.h"


int main(int argc, char* argv[])
{
	CppUnit::TextTestRunner runner;
	runner.addTest(SmartPoolTest::suite());
	runner.addTest(DeviceTest::suite());
	runner.addTest(KSGOSUtilTest::suite());
	runner.addTest(ThreadTest::suite());
	runner.addTest(TestISO8583Msg::suite());
	runner.run("",true);
	return 0;
}

