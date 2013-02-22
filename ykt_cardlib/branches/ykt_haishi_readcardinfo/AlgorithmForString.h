#ifndef _ALGORITHM_FOR_STRING_
#define _ALGORITHM_FOR_STRING_

static char iniDllFilePathBuf[512] = "";

// 十进制转bcd压缩形式(对字符串而言)
int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);

// bcd压缩转十进制形式(对字符串而言)
int bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr);

// 十进制转16进制(对于字符串而言)
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);

// 16进制转十进制(对于字符串而言)
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);

// bcd压缩转十进制形式(对字符串而言, 第三个参数改变)
int  bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr);

// 获取配置文件
void GetIniFile(char *FilePathBuf, const char *PurposeFileBuf);

// 获取配置文件
void GetIniFileA(char *FilePathBuf);

#endif	//_ALGORITHM_FOR_STRING_