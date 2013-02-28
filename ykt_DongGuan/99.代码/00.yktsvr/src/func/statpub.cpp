#include <stdio.h>
#include <string.h>

#define	YEAR		4
#define	MONTH		2
#define	DATE		2

int dateConvert(char *str, char *buf) {
	int i;
	
	if( strlen(str) != YEAR + MONTH + DATE ) {
		printf("字符串：%s 长度不合法.\n", str);
		return(-1);
	}
	
	for(i = 0; i < YEAR; i++) {
		buf[i] = str[i];
	}
	
	buf[YEAR] = '-';
	
	for(i = YEAR; i < YEAR + MONTH; i++) {
		buf[i+1] = str[i];
	}
	
	buf[YEAR + MONTH + 1] = '-';
	
	for(i = YEAR + MONTH; i < YEAR + MONTH + DATE; i++) {
		buf[i+2] = str[i];
	}
	
	buf[YEAR + MONTH + DATE + 2] = '\0';
	
	return 0;
}