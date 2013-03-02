#include "stdafx.h"
#include "thread.h"
#include <xutils/functor.h>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <functional>

using namespace std;


//////////////////////////////////////////////////////////////////////////
// KSGThreadUtil
boost::xtime KSGThreadUtil::Delay(long msecs)
{
	const int MILLISECONDS_PER_SECOND = 1000;
	const int NANOSECONDS_PER_SECOND = 1000000000;
	const int NANOSECONDS_PER_MILLISECOND = 1000000;
	long secs,nsecs;

	boost::xtime xt;
	boost::xtime_get (&xt, boost::TIME_UTC);
	/*
	if (boost::TIME_UTC != boost::xtime_get (&xt, boost::TIME_UTC))
	BOOST_ERROR ("boost::xtime_get != boost::TIME_UTC");
	*/
	nsecs = xt.nsec;
	secs = msecs / MILLISECONDS_PER_SECOND;
	msecs = msecs % MILLISECONDS_PER_SECOND;

	msecs += nsecs / NANOSECONDS_PER_MILLISECOND;
	secs += msecs / MILLISECONDS_PER_SECOND;
	nsecs += (msecs % MILLISECONDS_PER_SECOND) * NANOSECONDS_PER_MILLISECOND;
	xt.nsec = nsecs % NANOSECONDS_PER_SECOND;
	xt.sec += secs + (nsecs / NANOSECONDS_PER_SECOND);

	return xt;
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