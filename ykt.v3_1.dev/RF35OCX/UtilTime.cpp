#include "stdafx.h"
#include ".\utiltime.h"

CUtilTime::CUtilTime(void) {
}

CUtilTime::~CUtilTime(void) {
}

int CUtilTime::GetLocalTime(char time_msg[20]) {
    struct tm tmloc;
    time_t curtime;

    time(&curtime);
    memcpy(&tmloc, localtime(&curtime), sizeof(tmloc));
    sprintf(time_msg,"20%02d%02d%02d%02d%02d%02d",
            tmloc.tm_year - 100,
            tmloc.tm_mon + 1,
            tmloc.tm_mday,
            tmloc.tm_hour,
            tmloc.tm_min,
            tmloc.tm_sec
           );
    return 0;
}
