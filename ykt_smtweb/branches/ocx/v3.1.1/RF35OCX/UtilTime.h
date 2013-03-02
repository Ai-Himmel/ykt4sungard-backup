#ifndef _UTIL_TIME_H_
#define _UTIL_TIME_H_

#pragma once
#include <time.h>
#include "DataType.h"

class CUtilTime
{
public:
	CUtilTime(void);
	virtual ~CUtilTime(void);
	int GetLocalTime(char time_msg[20]);
};

#endif