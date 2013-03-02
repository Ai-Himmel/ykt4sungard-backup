#ifndef _SMARTPOOL_TEST_H_
#define _SMARTPOOL_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include <xutils/functor.h>
#include <functional>
#include <algorithm>
#include <boost/functional.hpp>

#include "thread.h"
#include "smartpool.h"
#include "ksgexception.h"
//#include "drtppool.h"
#include <gmock/gmock.h>


struct TestObject
{
	TestObject():_index(0)
	{}
	int _index;
};
struct TestObject2
{
	TestObject2(){}
	int _name;
};


class SmartPoolAllocTestObject
{
private:
	typedef TestObject ObjectType;
public:
	void OnNewCheck(ObjectType *p);
	void OnDeleteCheck(ObjectType *p);
};


class Test_Creator_TestObject2 
{
public:
	Test_Creator_TestObject2()
	{
	}
	void set_max(int num) {}
	int get_max() { return 5; }
	TestObject2 * create_new()
	{
		return new TestObject2;
	}
	void delete_one(TestObject2 *p)
	{
		delete p;
	}
};

class SmartPoolTest : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( SmartPoolTest );
	CPPUNIT_TEST(testAlloc);
	CPPUNIT_TEST_EXCEPTION(testExhaustAlloc,NoneResourceException);
	CPPUNIT_TEST(testFree);
	CPPUNIT_TEST(test2Pool);
	CPPUNIT_TEST(testSmartObject);
	CPPUNIT_TEST_SUITE_END();
private:
	
	typedef KSG_SmartPool<TestObject,
		KSG_Memory_Pool_Allocator<TestObject,KSGMultiThreadmModel<10000>,SmartPoolAllocTestObject> > TestPool;
	TestPool _pool;

	typedef KSG_SmartPool<TestObject2,
		KSG_Resource_Pool_Allocator<TestObject2,KSGMultiThreadmModel<10000>,Test_Creator_TestObject2> > TestDRTPPool;

	TestDRTPPool drtppool_;

	void setupPool(int count)
	{
		/*
		boost::function0<TestObject*> func;
		func = xutil::bind1param<TestObject*>(std::mem_fun(&SmartPoolTest::CreateTestObject),this);
		_pool.Init(count,func);
		*/
		drtppool_.Init(count);

	}
protected:
	void testAlloc()
	{
		TestPool::SmartObject obj;
		TestPool::SmartObject obj2;
		obj = _pool.Alloc();
		obj = _pool.Alloc();
		CPPUNIT_ASSERT_EQUAL(9,_pool.Count());
		_pool.Alloc(obj2);
		CPPUNIT_ASSERT_EQUAL(8,_pool.Count());
	}
	void testExhaustAlloc()
	{
		CPPUNIT_ASSERT_EQUAL(10,_pool.Count());
		setupPool(1);
		TestPool::SmartObject obj,obj2;
		obj = _pool.Alloc();
		CPPUNIT_ASSERT_EQUAL(0,_pool.Count());
		obj2 = _pool.Alloc();
	}
	void testFree()
	{
		CPPUNIT_ASSERT_EQUAL(0,_pool.Count());
		setupPool(10);
		CPPUNIT_ASSERT_EQUAL(10,_pool.Count());
	}
	void test2Pool()
	{
		
	}
	void testSmartObject()
	{
		TestPool::SmartObject obj;
		CPPUNIT_ASSERT(!obj);
		obj = _pool.Alloc();
		CPPUNIT_ASSERT(obj);
	}
public:
	TestObject* CreateTestObject()
	{
		static int index = 0;
		return new TestObject();
	}
	TestObject2* CreateTestObject2()
	{
		return new TestObject2;
	}
	void setUp()
	{
		setupPool(10);
	}
	void tearDown()
	{
	}

};

#endif	// _SMARTPOOL_TEST_H_