#include "stdafx.h"
#include "CDate.h"
//#include "stdio.h"

CDate::CDate()
{
	memset(m_beginDate,0,sizeof(m_beginDate));
	memset(m_endDate,0,sizeof(m_endDate));
	memset(m_currDate,0,sizeof(m_currDate));
	m_year = 0;
	m_month = 0;
	m_day = 0;

}

CDate::~CDate()
{
}

char *CDate::getNextDate()
{
	int date = getDate();

	if(m_day>date)
	{
		m_day = 1;
		m_month++;
	}
	if(m_month>12)
	{
		m_month = 1;
		m_year++;
	}
	
	sprintf(m_currDate,"%d%02d%02d",m_year,m_month,m_day);
	m_day++;
	return m_currDate;
}
BOOL CDate::isEnd()
{
	if(strncmp(m_currDate,m_endDate,8) == 0)
		return true;
	return false;
}
BOOL CDate::isLeapYear(int year)
{
	if((year%4 == 0 && year %100 != 0) || (year % 400 == 0))
		return true;
	return false;
}

BOOL CDate::setDate(char *pBegin,char *pEnd)
{
	char buf[9];
	sprintf(buf,"%4s",pEnd);
	buf[4] = 0;
	m_year = atoi(buf);
	if (m_year < 0)
		return false;
	sprintf(buf,"%s",pEnd+4);
	buf[2] = 0;
	m_month = atoi(buf);
	if (m_month<1 || m_month>12 )
		return false;
	sprintf(buf,"%s",pEnd+6);
	buf[2] = 0;
	m_day = atoi(buf);
	int day = getDate();
	if(m_day>day || m_day <1)		//指定的结束日期不合法
		return false;
	memcpy(m_endDate,pEnd,8);

	sprintf(buf,"%s",pBegin);
	buf[4] = 0;
	m_year = atoi(buf);
	if (m_year < 0)
		return false;
	sprintf(buf,"%s",pBegin+4);
	buf[2] = 0;
	m_month = atoi(buf);
	if (m_month<1 || m_month>12 )
		return false;
	sprintf(buf,"%s",pBegin+6);
	buf[2] = 0;
	m_day = atoi(buf);
	day = getDate();
	if(m_day>day || m_day <1)		//指定的开始日期不合法
		return false;
	memcpy(m_beginDate,pBegin,8);
	return true;
}

int CDate::getDate()
{
	int date;
	BOOL bIsLeapYear = isLeapYear(m_year);
	switch(m_month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		if (bIsLeapYear)
			return 29;
		else 
			return 28;
	default:
		return -1;
	}
}
