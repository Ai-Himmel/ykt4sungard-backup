#ifndef _GLOBAL_FUNC_H_
#define _GLOBAL_FUNC_H_

short get_2byte_int(unsigned char *value_str);
int get_3byte_int(unsigned char *value_str);
int get_4byte_int(unsigned char *value_str);
void set_2byte_int(unsigned char *value_str,int num);
void set_3byte_int(unsigned char *value_str,int num);
void set_4byte_int(unsigned char *value_str,int num);




// 1.字符串转换类
//////////////////////////////////////////////////////////////////////////
//十进制asc码字符串转换为bcd保存的数组
void asc2bcd(const char *sAscStr,int iAscLen,unsigned char *uBcdBuf,int& uBcdBufLen);
void bcd2asc(const unsigned char *uBcdBuf,int iBcdLen,char *sAscStr);
void dec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr);
void hex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int& iDecBUfLen);

int calc_sum(const unsigned char *d,int len);
int check_buffer_sum(const unsigned char *d,int datalen,unsigned char sum);

int calc_or(const unsigned char *d,int len);
int calc_xor(const unsigned char *d,int len);
int check_buffer_or(const unsigned char *d,int datalen,unsigned char or);
int check_buffer_xor(const unsigned char *d,int datalen,unsigned char xor);

int get_current_datetime(char dt[15]);

#endif // _GLOBAL_FUNC_H_
