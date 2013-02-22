#ifndef MYTIME_H
#define MYTIME_H

#include <time.h>

#ifndef __cplusplus
#define __cplusplus
#endif
inline char *getSysDate(char *date=NULL)
{
	time_t t;
	struct tm *ptm;
	static char szDate[11] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szDate, 9, "%Y%m%d", ptm);
	if (date)
		strcpy(date, szDate);
	return szDate;
}
inline char *getSysTime(char *v_time=NULL)
{
	time_t t;
	struct tm *ptm;
	static char szTime[10] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szTime, 7, "%H%M%S", ptm);
	if (v_time)
		strcpy(v_time, szTime);
	return szTime;
}
inline char *getSysDateTime(char *v_datetime=NULL)
{
	time_t t;
	struct tm *ptm;
	static char szDatetime[16] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szDatetime, 15, "%Y%m%d%H%M%S", ptm);
	if (v_datetime)
		strcpy(v_datetime, szDatetime);
	return szDatetime;
}
inline char *getSysTimestamp(char *v_timestamp=NULL)
{
	static char szSysTimestamp[28] = "";
	time_t t;
	struct timeval tv;
	struct timezone tz;
	struct tm *ptm;

	char systime[20] = "";

	gettimeofday(&tv, &tz);
	t=tv.tv_sec;
	ptm=localtime(&t);
	strftime(systime,15,"%Y%m%d%H%M%S",ptm);
	sprintf(szSysTimestamp, "%s%06d", systime, tv.tv_usec);
	if (v_timestamp)
		strcpy(v_timestamp, szSysTimestamp);
	return szSysTimestamp;
}

inline char *getFmtSysDate(char *v_date=NULL)
{
	time_t t;
	struct tm *ptm;
	static char szDate[12] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szDate, 11, "%Y-%m-%d", ptm);
	if (v_date)
		strcpy(v_date, szDate);
	return szDate;
}
inline char *getFmtSysTime(char *v_time=NULL)
{
	time_t t;
	struct tm *ptm;
	static char szTime[10] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szTime, 9, "%H.%M.%S", ptm);
	if (v_time)
		strcpy(v_time, szTime);
	return szTime;
}
inline char *getFmtSysDateTime(char *v_datetime=NULL)
{
        static char szDateTime[21] = "";
        time_t t;
        struct timeval tv;
        struct timezone tz;
        struct tm *ptm;

        gettimeofday(&tv, &tz);
        t=tv.tv_sec;
        ptm=localtime(&t);
        strftime(szDateTime,20,"%Y-%m-%d %H:%M:%S",ptm);
	if (v_datetime)
		strcpy(v_datetime, szDateTime);
	return szDateTime;
}


inline char *getFmtSysTimestamp(char *v_timestamp=NULL)
{
	static char szTimestamp[28] = "";
	time_t t;
	struct timeval tv;
	struct timezone tz;
	struct tm *ptm;
	char systime[20] = "";

	gettimeofday(&tv, &tz);
	t=tv.tv_sec;
	ptm=localtime(&t);
	strftime(systime,20,"%Y-%m-%d-%H.%M.%S",ptm);
	sprintf(szTimestamp, "%s.%06d", systime, tv.tv_usec);
	if (v_timestamp)
		strcpy(v_timestamp, szTimestamp);
	return szTimestamp;
}
inline char *getPacketID(char *v_packetid=NULL)
{
	static char packet_id[28] = "";
	time_t t;
	struct timeval tv;
	struct timezone tz;
	struct tm *ptm;
	char systime[20] = "";

	gettimeofday(&tv, &tz);
	t=tv.tv_sec;
	ptm=localtime(&t);
	strftime(systime,7,"%H%M%S",ptm);
	sprintf(packet_id, "%s%06d", systime, tv.tv_usec);
	if (v_packetid)
		strcpy(v_packetid, packet_id);
	return packet_id;
}
#endif
