#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
char *getsystime(char *v_time)
{
	time_t t;
	struct tm *ptm;
	static char szTime[10] = "";

	time(&t);
	ptm = localtime(&t);

	strftime(szTime, 7, "%S", ptm);
	if (v_time)
	strcpy(v_time, szTime);
	return szTime;
}
int main(int argc, char * argv [ ])
{
	  char  testt[9]="";
	  getsystime(testt);
	  printf(testt);
}
