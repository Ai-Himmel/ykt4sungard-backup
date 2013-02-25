#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "ucs2code.h"


int EncodeUCS2(unsigned char *SourceBuf,unsigned char *DestBuf) {
    int len,i,j=0;
    wchar_t wcbuf[255];

    setlocale(LC_ALL,"");
    len = mbstowcs(wcbuf,(const char*)SourceBuf,255); /* convert mutibytes string to wide charater string */
    for (i=0; i<len; i++) {
        DestBuf[j++] = wcbuf[i]>>8;     /* height byte */
        DestBuf[j++] = wcbuf[i]&0xff;   /* low byte */
    }
    return len*2;
}

int DecodeUCS2(unsigned char *SourceBuf,unsigned char *DestBuf,int len) {
    wchar_t wcbuf[255];
    int i;

    setlocale(LC_ALL,"");
    for( i=0; i<len/2; i++ ) {
        wcbuf[i]=SourceBuf[2*i];    // height byte
        wcbuf[i]=(wcbuf[i]<<8)+SourceBuf[2*i+1];    // low byte
    }
    return wcstombs((char*)DestBuf,wcbuf,len); /* convert wide charater string to mutibytes string */
}