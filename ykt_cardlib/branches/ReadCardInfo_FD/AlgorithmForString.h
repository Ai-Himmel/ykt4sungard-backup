#ifndef _ALGORITHM_FOR_STRING_
#define _ALGORITHM_FOR_STRING_

static char iniDllFilePathBuf[512] = "";

// ʮ����תbcdѹ����ʽ(���ַ�������)
int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len);

// bcdѹ��תʮ������ʽ(���ַ�������)
int bcd2dec(unsigned char *sBcdStr,int bcd_len,unsigned char *sDecStr);

// ʮ����ת16����(�����ַ�������)
void dec2hex(unsigned char *sDec,int dec_len,char *sHex);

// 16����תʮ����(�����ַ�������)
void hex2dec(char *sHex,unsigned char * sDec,int dec_len);

// bcdѹ��תʮ������ʽ(���ַ�������, �����������ı�)
int  bcd2decA(unsigned char *sBcdStr, int bcd_len, char *sDecStr);

// ��ȡ�����ļ�
void GetIniFile(char *FilePathBuf, const char *PurposeFileBuf);

// ��ȡ�����ļ�
void GetIniFileA(char *FilePathBuf);

#endif	//_ALGORITHM_FOR_STRING_