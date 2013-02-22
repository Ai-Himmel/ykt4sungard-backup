#pragma once

class CDate
{
public:
	BOOL setDate(char *pBegin,char *pEnd);
	char *getNextDate();
	BOOL isEnd();
	CDate();
	~CDate();
private:
	int getDate();
	BOOL isLeapYear(int year);
	char m_beginDate[9];
	char m_endDate[9];
	char m_currDate[9];
	int m_year;
	int m_month;
	int m_day;

};