#ifndef _OSUTIL_TEST_H_
#define _OSUTIL_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <osutil.h>
#include <string>

class KSGOSUtilTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(KSGOSUtilTest);
	CPPUNIT_TEST(testGetBaseDir);
	CPPUNIT_TEST_SUITE_END();
private:
	void testGetBaseDir()
	{
		std::string fullpath;
		KSGOSUtil::GetBaseDir(fullpath);
		std::string basename = KSGOSUtil::BaseName(fullpath);
		std::string pathname = KSGOSUtil::GetPathName(fullpath);
		CPPUNIT_ASSERT(basename == "gwtest.exe");
		CPPUNIT_ASSERT(KSGOSUtil::JoinPath(pathname,basename) == fullpath);
		CPPUNIT_ASSERT(KSGOSUtil::JoinPath("c:\\test",basename) == "c:\\test\\gwtest.exe");
		CPPUNIT_ASSERT(KSGOSUtil::JoinPath("c:\\test\\",basename) == "c:\\test\\gwtest.exe");
		CPPUNIT_ASSERT(KSGOSUtil::GetPathName("c:\\test\\gwtest.exe") == "c:\\test");
	}
public:

};
#endif