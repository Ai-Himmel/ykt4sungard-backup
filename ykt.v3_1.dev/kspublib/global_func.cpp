#include "global_func.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

unsigned short get_2byte_int(unsigned char *value_str) {
    int r=0,t=0;
    t = value_str[0];
    r = t << 8;
    r |= value_str[1];
    return (short)r;
}
int get_3byte_int(unsigned char *value_str) {
    int r=0,t=0;
    t = value_str[0];
    r = t << 16;
    t = value_str[1];
    r |= t << 8;
    r |= value_str[2];
    return r;
}
int get_4byte_int(unsigned char *value_str) {
    int r=0,t=0;
    t = value_str[0];
    r = t << 24;
    t = value_str[1];
    r |= t << 16;
    t = value_str[2];
    r |= t << 8;
    r |= value_str[3];
    return r;
}
void set_2byte_int(unsigned char *value_str,int num) {
    value_str[0]=(num>>8)&0xFF;
    value_str[1]=num&0xFF;
}
void set_3byte_int(unsigned char *value_str,int num) {
    value_str[0]=(num>>16)&0xFF;
    value_str[1]=(num>>8)&0xFF;
    value_str[2]=num&0xFF;
}
void set_4byte_int(unsigned char *value_str,int num) {
    value_str[0]=(num>>24)&0xFF;
    value_str[1]=(num>>16)&0xFF;
    value_str[2]=(num>>8)&0xFF;
    value_str[3]=num&0xFF;
}

// 1.字符串转换类
//////////////////////////////////////////////////////////////////////////
//十进制asc码字符串转换为bcd保存的数组
void asc2bcd(const char *sAscStr,int iAscLen,unsigned char *uBcdBuf,int& uBcdBufLen) {
    int i=0;
    int offset=0;
    int len=iAscLen/2;
    unsigned char lch,hch;
    if(iAscLen%2) {
        lch=0;
        hch=sAscStr[0]-'0';
        hch=hch&0x0F;
        uBcdBuf[0]=hch|lch;
        offset++;
    }
    for(i=0; i<len; i++) {
        lch=sAscStr[2*i+offset]-'0';
        hch=sAscStr[2*i+offset+1]-'0';
        lch=lch<<4;
        hch=hch&0x0F;
        lch=lch&0xF0;
        uBcdBuf[i+offset]=hch|lch;
    }
    uBcdBufLen=i+offset;
}
void bcd2asc(const unsigned char *uBcdBuf,int iBcdLen,char *sAscStr) {
    int i;
    unsigned char lch,hch;

    for(i=0; i<iBcdLen; i++) {
        hch=(uBcdBuf[i]&0x0F);
        lch=(uBcdBuf[i]&0xF0);
        lch=lch>>4;
        sAscStr[2*i]=lch+'0';
        sAscStr[2*i+1]=hch+'0';
    }
}

void dec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr) {
    int i=0;
    int k=0;
    for(i=0; i<iDecLen; i++) {
        k=uDecBuf[i];
        sprintf(&sHexStr[2*i],"%02X",k);
    }
}
void hex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int& iDecBUfLen) {
    int i=0;
    unsigned long ul;
    char sHexTmp[3];
    int offset=0;
    int dlen=iHexLen/2;

    memset(sHexTmp,0,sizeof(sHexTmp));
    if(iHexLen%2) {
        sHexTmp[0]='0';
        sHexTmp[1]=sHexStr[0];
        ul=strtoul(sHexTmp,NULL,16);
        uDecBuf[0]=(unsigned char)ul;
        offset++;
    }
    for(i=0; i<dlen; i++) {
        memcpy(sHexTmp,&sHexStr[2*i+offset],2);
        ul=strtoul(sHexTmp,NULL,16);
        uDecBuf[i+offset]=(unsigned char)ul;
    }
    iDecBUfLen=i+offset;
}

int calc_sum(const unsigned char *d,int len) {
    unsigned char t;
    int i;
    for(t=0,i=0; i < len; ++i)
        t += d[i];

    //hex2dec(
    return t;
}

int get_current_datetime(char dt[15]) {
    time_t now;
    struct tm *t;

    time(&now);
    t = localtime(&now);

    sprintf(dt,"%04d%02d%02d%02d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,
            t->tm_hour,t->tm_min,t->tm_sec);

    return 0;

}

int check_buffer_sum(const unsigned char *d,int datalen,unsigned char sum) {
    int i;
    unsigned char t1,t2;
    for(t1=0,t2=0,i=0; i<datalen; ++i) {
        t1 += d[i];
        t2 |= d[i];
    }
    if(t1==sum && t2 != 0)
        return 0;
    return -1;
}


int calc_or(const unsigned char *d,int len) {
    unsigned char t;
    int i;
    for(i=0,t=0; i < len; ++i)
        t |= d[i];
    return t;
}
int calc_xor(const unsigned char *d,int len) {
    unsigned char t;
    int i;
    for(i=1,t=d[0]; i< len ; ++i)
        t ^= d[i];
    return t;
}

int check_buffer_or(const unsigned char *d,int datalen,unsigned char orbyte) {
    unsigned char t;
    t = calc_or(d,datalen);
    return (t == orbyte) ? 0 : -1;
}

int check_buffer_xor(const unsigned char *d,int datalen,unsigned char xorbyte) {
    unsigned char t;
    t = calc_xor(d,datalen);
    return (t == xorbyte) ? 0 : -1;
}

static unsigned char statickey[17]="3230303530313331";
int	encrypt_work_key(unsigned char* text,unsigned char* mtext) {
    unsigned int  i;
    unsigned long ul;
    char temp[3];
    unsigned char plain[9];
    unsigned char statkey[9];

    memset(temp,0,sizeof(temp));
    memset(plain,0,sizeof(plain));
    memset(statkey,0,sizeof(statkey));
    memcpy(plain,text,8);
    for(i=0; i<8; i++) {
        memcpy(temp,&statickey[2*i],2);
        ul=strtoul(temp,NULL,16);
        statkey[i]=ul;
        plain[i]=~plain[i];
        mtext[i]=plain[i]^statkey[i];
    }
    return 0;
}

int	decrypt_work_key(unsigned char* text,unsigned char* mtext) {
    unsigned int  i;
    unsigned long ul;
    char temp[3];
    unsigned char statkey[9];

    memset(temp,0,sizeof(temp));
    memset(statkey,0,sizeof(statkey));
    for(i=0; i<8; i++) {
        memcpy(temp,&statickey[2*i],2);
        ul=strtoul(temp,NULL,16);
        statkey[i]=ul;
        mtext[i]=text[i]^statkey[i];
        mtext[i]=~mtext[i];
    }
    return 0;
}
unsigned char calc_crc8(const unsigned char *d,int len) {
    unsigned char crc;
    unsigned char i;
    crc = 0;
    while(len--) {
        crc ^= *d++;
        for(i = 0; i < 8; i++) {
            if(crc & 0x01) {
                crc = (crc >> 1) ^ 0x8C;
            } else crc >>= 1;
        }
    }
    return crc;
}
