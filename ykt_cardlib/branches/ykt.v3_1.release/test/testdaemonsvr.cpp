
#include <map>
#include <string>
#include "json/json.h"
#include "../ksitfcdaemon/std.h"
#include "../ksitfcdaemon/daemonsvr.h"
#include <cppunit/extensions/HelperMacros.h>


class TestDaemonSvr: public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestDaemonSvr);
	CPPUNIT_TEST(testMsg);
	CPPUNIT_TEST(testMsg2);
	CPPUNIT_TEST(testMsg3);
	CPPUNIT_TEST(testMsg4);
	CPPUNIT_TEST(testMsg5);
	//CPPUNIT_TEST(testMsg6);
	CPPUNIT_TEST_SUITE_END();
public:
	void setUp()
	{
	}
	void tearDown()
	{
	}
	///////////////////////////////////////////////////
public:
	void testMsg()
	{
		bool rc;
		KsCardMsg msg;
		rc = msg.ParseMsg("{\"msgtype\":\"login\"}");
		CPPUNIT_ASSERT(rc==true);

		CPPUNIT_ASSERT(msg.MsgType()=="login");

	}
	void testMsg2()
	{
		bool rc;
		KsCardMsg msg;
		rc = msg.ParseMsg("{\"msgtype\":\"init4crebit\",\"data\":{\"refno\":\"12345\",\"cardno\":\"4444\"}}");
		CPPUNIT_ASSERT(rc==true);

		CPPUNIT_ASSERT(msg.MsgType()=="init4crebit");
		std::string value;

		rc = msg.GetStrPara("data.refno",value);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(value=="12345");

		rc = msg.GetStrPara("data.cardno",value);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(value=="4444");

		msg.Reset();
		rc = msg.ParseMsg("{\"msgtype\":\"login\"}");
		CPPUNIT_ASSERT(rc==true);

		CPPUNIT_ASSERT(msg.MsgType()=="login");

	}
	void testMsg3()
	{
		bool rc;
		KsCardMsg msg,msg1;
		msg.SetMsgType("reload");
		msg.SetIntPara("data.cardno",1233);
		msg.SetStrPara("data.refno","1233455");
		std::string content = msg.ToMsg();
		

		rc = msg1.ParseMsg(content);
		CPPUNIT_ASSERT(msg1.MsgType()=="reload");
		std::string value;

		rc = msg1.GetStrPara("data.refno",value);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(value=="1233455");

		int ivalue;
		rc = msg1.GetIntPara("data.cardno",&ivalue);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(ivalue==1233);
	}
	void testMsg4()
	{
		bool rc;
		KsCardMsg msg,msg1;
		msg.SetMsgType("adduser");
		msg.SetIntPara("data.cardno",1233);
		msg.SetStrPara("data.comment","中国上海\"杨浦区\"");
		msg.SetStrPara("data.name","张三");
		std::string content = msg.ToMsg();
		

		rc = msg1.ParseMsg(content);
		CPPUNIT_ASSERT(msg1.MsgType()=="adduser");
		std::string value;

		rc = msg1.GetStrPara("data.comment",value);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(value=="中国上海\"杨浦区\"");

		rc = msg1.GetStrPara("data.name",value);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(value=="张三");

		int ivalue;
		rc = msg1.GetIntPara("data.cardno",&ivalue);
		CPPUNIT_ASSERT(rc == true);
		CPPUNIT_ASSERT(ivalue==1233);
	}
	void testMsg5()
	{
		bool rc;
		KsCardMsg msg;
		rc = msg.ParseMsg("{\"msgtype\":\"init4crebit\",\"data\":{\"refno\":\"12345\",\"cardno\":\"4444\"\
						  ,\"trans\":{\"date\":\"20110105\",\"time\":\"150000\" } }}");
		CPPUNIT_ASSERT(rc==false);
	}
	void testMsg6()
	{
		KsCardMsg msg,msg1;
		msg.SetMsgType("adduser");
		msg.SetIntPara("data.cardno",1233);
		msg.SetStrPara("data.trans.addr","中国上海\"杨浦区\"");
		msg.SetStrPara("data.trans.name","张三");
		std::string content = msg.ToMsg();
		CPPUNIT_ASSERT(content.empty());
	}
};


CPPUNIT_TEST_SUITE_REGISTRATION(TestDaemonSvr);
