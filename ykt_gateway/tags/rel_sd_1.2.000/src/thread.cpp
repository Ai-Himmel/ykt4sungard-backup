#include "stdafx.h"
#include "thread.h"
#include <xutils/functor.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

using namespace std;


//////////////////////////////////////////////////////////////////////////
// KSGThreadUtil
boost::xtime KSGThreadUtil::Delay(long msec)
{
	boost::xtime t;
	boost::xtime_get(&t,boost::TIME_UTC);
	t.sec += msec / 1000;
	t.nsec += msec % 1000;
	return t;
}

void KSGThreadUtil::Sleep(long msec)
{
	boost::xtime t = Delay(msec);
	boost::thread::sleep(t);
}

void KSGThreadUtil::yield()
{
	boost::thread::yield();
};