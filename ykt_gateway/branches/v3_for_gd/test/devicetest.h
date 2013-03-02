#ifndef _DEVICE_TEST_H_
#define _DEVICE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <device.h>
#include <ksgateway.h>

class DeviceTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(DeviceTest);
	CPPUNIT_TEST(testDeviceURL);
	CPPUNIT_TEST(testDevicePool);
	CPPUNIT_TEST_SUITE_END();
private:
	void testDeviceURL()
	{
		KSGDeviceURL parser;
		// 1
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP:999//1@10.49.188.40:1001") == 0);
		CPPUNIT_ASSERT(parser.GetManufactor() == "999");
		CPPUNIT_ASSERT(parser.GetConnType() == KSGDeviceURL::dctTCP);
		CPPUNIT_ASSERT(parser.GetDevCode() == "1");
		CPPUNIT_ASSERT(parser.GetConnect() == "10.49.188.40");
		CPPUNIT_ASSERT(parser.GetPort() == 1001);
		// 2
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP:999//15@192.168.0.1") == 0);
		CPPUNIT_ASSERT(parser.GetManufactor() == "999");
		CPPUNIT_ASSERT(parser.GetConnType() == KSGDeviceURL::dctTCP);
		CPPUNIT_ASSERT(parser.GetDevCode() == "15");
		CPPUNIT_ASSERT(parser.GetConnect() == "192.168.0.1");
		CPPUNIT_ASSERT(parser.GetPort() == 10001);
		// 3
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP:hd//0A3F@192.168.12.1:5001") == 0);
		CPPUNIT_ASSERT(parser.GetManufactor() == "hd");
		CPPUNIT_ASSERT(parser.GetConnType() == KSGDeviceURL::dctTCP);
		CPPUNIT_ASSERT(parser.GetDevCode() == "0A3F");
		CPPUNIT_ASSERT(parser.GetConnect() == "192.168.12.1");
		CPPUNIT_ASSERT(parser.GetPort() == 5001);
		// 4
		CPPUNIT_ASSERT(parser.ParseUrl("dev:COM:hd//0A3F@COM:1") == 0);
		CPPUNIT_ASSERT(parser.GetManufactor() == "hd");
		CPPUNIT_ASSERT(parser.GetConnType() == KSGDeviceURL::dctCOM);
		CPPUNIT_ASSERT(parser.GetDevCode() == "0A3F");
		CPPUNIT_ASSERT(parser.GetConnect() == "COM");
		CPPUNIT_ASSERT(parser.GetPort() == 1);
		// 5
		CPPUNIT_ASSERT(parser.ParseUrl("dev:COM:hd//0A3F@COM") == 0);
		CPPUNIT_ASSERT(parser.GetManufactor() == "hd");
		CPPUNIT_ASSERT(parser.GetConnType() == KSGDeviceURL::dctCOM);
		CPPUNIT_ASSERT(parser.GetDevCode() == "0A3F");
		CPPUNIT_ASSERT(parser.GetConnect() == "COM");
		CPPUNIT_ASSERT(parser.GetPort() == 1);
		// 6
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP:hd//0A3F@192.168.12.1:5001:12") == 0);
		CPPUNIT_ASSERT(parser.GetManufactor() == "hd");
		CPPUNIT_ASSERT(parser.GetConnType() == KSGDeviceURL::dctTCP);
		CPPUNIT_ASSERT(parser.GetDevCode() == "0A3F");
		CPPUNIT_ASSERT(parser.GetConnect() == "192.168.12.1");
		CPPUNIT_ASSERT(parser.GetPort() == 5001);
		//////////////////////////////////////////////////////////////////////////
		// failed test
		CPPUNIT_ASSERT(parser.ParseUrl("dev1:COM:hd//0A3F@COM") != 0);
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP2:hd//0A3F@COM") != 0);
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP:hd/0A3F@192.168.1:5001") != 0);
		CPPUNIT_ASSERT(parser.ParseUrl("dev:TCP:hd//0A3F") != 0);
	}

	void testDevicePool()
	{
		//KSGDeviceManager manager(&_gateway);
	}
public:
	void setUp()
	{

	}
	void tearDown()
	{

	}
};
#endif // _DEVICE_TEST_H_