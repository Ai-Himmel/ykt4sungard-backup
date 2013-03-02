#ifndef _ISO_TEST_H_
#define _ISO_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <F8583.h>

class TestISO8583Msg : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestISO8583Msg);
	CPPUNIT_TEST(testHD8583);
	CPPUNIT_TEST_SUITE_END();
private:
	void testHD8583()
	{
		HD8583STRUCT t;
		ISO8583Msg<HD8583STRUCT,HD8583STRUCT::PACK_LENGTH> iso(t);
		unsigned char buf[4];
		iso.InitPack();
		int a = 1000;
		INT_2_BUF(a,buf);
		iso.AddField(FIELD2,buf,4);
		a = 108;
		INT_2_BUF(a,buf);
		iso.AddField(FIELD16,buf,4);
		unsigned char iso8583buf[4096];
		memset(iso8583buf,0,sizeof(iso8583buf));
		int buflen = iso.Pack(iso8583buf,sizeof(iso8583buf));
		CPPUNIT_ASSERT( buflen == (4 + 4 + 8));
		
		iso.InitPack();
		CPPUNIT_ASSERT(t[FIELD2].length_in_byte == 0);
		iso.Unpack(iso8583buf,buflen);
		BUF_2_INT(a,t[FIELD2].data);
		CPPUNIT_ASSERT(a == 1000);
		BUF_2_INT(a,t[FIELD16].data);
		CPPUNIT_ASSERT(a == 108);
	}
public:
};

#endif // _ISO_TEST_H_
