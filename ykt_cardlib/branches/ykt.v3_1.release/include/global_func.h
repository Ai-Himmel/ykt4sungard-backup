#ifndef _GLOBAL_FUNC_H_
#define _GLOBAL_FUNC_H_

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

unsigned short get_2byte_int(unsigned char *value_str);
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
int check_buffer_or(const unsigned char *d,int datalen,unsigned char orbyte);
int check_buffer_xor(const unsigned char *d,int datalen,unsigned char xorbyte);

unsigned char calc_crc8(const unsigned char *d,int len);

int get_current_datetime(char dt[15]);

int	encrypt_work_key(unsigned char* text,unsigned char* mtext);
int	decrypt_work_key(unsigned char* text,unsigned char* mtext);

#ifndef MIN
#define MIN(x,y) ((x) > (y) ? (y) : (x))
#endif
#ifndef MAX
#define MAX(x,y) ((x) > (y) ? (x) : (y))
#endif
#endif // _GLOBAL_FUNC_H_
