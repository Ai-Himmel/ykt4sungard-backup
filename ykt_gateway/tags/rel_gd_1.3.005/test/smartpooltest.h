#ifndef _SMARTPOOL_TEST_H_
#define _SMARTPOOL_TEST_H_

#include <cppunit/extensions/HelperMacros.h>

#include <smartpool.h>
#include <xutils/functor.h>
#include <functional>
#include <algorithm>

#include <boost/functional.hpp>

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
	struct TestObject
	{
		TestObject(int i):_index(i)
		{}
		int _index;
	};
	struct TestObject2
	{
		int _name;
	};
	typedef ResourcePool<TestObject> TestPool;
	typedef ResourcePool<TestObject2> TestPool2;
	TestPool _pool;
	void setupPool(int count)
	{
		boost::function0<TestObject*> func;
		func = xutil::bind1param<TestObject*>(std::mem_fun(&SmartPoolTest::CreateTestObject),this);
		_pool.Init(count,func);
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
		_pool.Free();
		setupPool(1);
		TestPool::SmartObject obj,obj2;
		obj = _pool.Alloc();
		CPPUNIT_ASSERT_EQUAL(0,_pool.Count());
		obj2 = _pool.Alloc();
	}
	void testFree()
	{
		_pool.Free();
		CPPUNIT_ASSERT_EQUAL(0,_pool.Count());
		setupPool(10);
		CPPUNIT_ASSERT_EQUAL(10,_pool.Count());
	}
	void test2Pool()
	{
		TestPool pool2;
		boost::function0<TestObject*> func;
		func = xutil::bind1param<TestObject*>(std::mem_fun(&SmartPoolTest::CreateTestObject),this);
		pool2.Init(5,func);
		{
			TestPool::SmartObject obj;
			_pool.Alloc(obj);
			TestPool::SmartObject obj2;
			pool2.Alloc(obj2);
			
			CPPUNIT_ASSERT(obj != obj2);
			obj = obj2;
		}
		CPPUNIT_ASSERT(_pool.Count() == 10);
		CPPUNIT_ASSERT(pool2.Count() == 5);

		pool2.Free();
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
		return new TestObject(index++);
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
		_pool.Free();
	}

};

#endif	// _SMARTPOOL_TEST_H_