/* --------------------------------------------
 * 程序名称: F950008.cpp
 * 创建日期: 2007-12-21
 * 程序作者: 汤成
 * 版本信息: 1.0.0.0
 * 程序功能: 下载学校代码参数
 * --------------------------------------------*/
#define _IN_SQC_
#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "acctrans.h"
#include "busqc.h"
#include "pubfunc.h"
#include "dbfunc_foo.h"
#include "rijndael-api-fst.h"

static char g_key_meterial[] = "D801FE1B8A2044CF92F05DCA1300C58D";

//typedef unsigned short uint16;

static const unsigned int  crc16_tab[256] = { 
	0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7, 
	0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef, 
	0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6, 
	0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de, 
	0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 
	0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 
	0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 
	0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 
	0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823, 
	0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b, 
	0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12, 
	0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a, 
	0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41, 
	0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 
	0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 
	0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 
	0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 
	0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067, 
	0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e, 
	0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256, 
	0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d, 
	0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405, 
	0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 
	0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 
	0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 
	0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 
	0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 
	0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92, 
	0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9, 
	0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1, 
	0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8, 
	0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 
};

static uint16  GenerateCRC16(const unsigned char *pBuf, uint16 len)
{
	uint16 crc; 
	unsigned char b, da;
	uint16 charcnt;

	crc = 0; 
	charcnt = 0;
	while (len--)
	{
		da = (unsigned char)(crc / 256); /* 以8位二进制数的形式暂存CRC的高8位 */ 
		crc <<= 8;						 /* 左移8位，相当于CRC的低8位乘以 */ 
		b = pBuf[charcnt];				 // 新移进来的字节值
		crc ^= crc16_tab[da ^ b];		 /* 高8位和当前字节相加后再查表求CRC ，再加上以前的CRC */ 
		charcnt++; 
	}
	return crc;
}

static void src2hex(const char *src_buf,int len,unsigned char *hex_buf)
{
	int i;
	char temp[4] = "";
	for(i = 0;i < len/2; ++i)
	{
		memcpy(temp,src_buf+i*2,2);
		unsigned char t = (unsigned char)strtoul(temp,NULL,16);
		hex_buf[i] = t;
	}
}

static int do_decrypt(char *data,int len,char *out)
{
	keyInstance key_inst;
	cipherInstance cipher_inst;
	unsigned char buf[16] = "";
	unsigned char encrypt_buf[16] = "";
	char crc_buf[12] = "";
	char decrypt_str[128] = "";
	memset(&key_inst,0,sizeof key_inst);
	memset(&cipher_inst,0,sizeof cipher_inst);
	if(makeKey(&key_inst,DIR_DECRYPT,128,g_key_meterial)==FALSE)
	{
		return -1;
	}
	if(cipherInit(&cipher_inst,MODE_CBC,NULL)==FALSE)
	{
		return -1;
	}

	src2hex(data,len,buf);
	len = padDecrypt(&cipher_inst,&key_inst,buf,16,encrypt_buf);
	uint16 crc_code = GenerateCRC16(encrypt_buf,6);
	sprintf(crc_buf,"%.04X",crc_code);
	//std::cout<<"解密类容 : "<<encrypt_buf<<std::endl;
	//std::cout<<"CRC : "<<crc_buf<<std::endl;
	if(strncmp(crc_buf,(char*)encrypt_buf+6,4) == 0)
	{
		// 类容正确
		memcpy(out,encrypt_buf,6);
		return 0;
	}
	
	return -1;
}

static int do_decrypt_school_code(const char *buf,int len,int *school_code)
{
	int ret;
	char school_buf[7] = "";
	ret = do_decrypt((char*)buf,len,school_buf);
	if(ret)
		return -1;
	school_buf[6] = '\0';
	*school_code = strtoul(school_buf,NULL,16);
	return 0;
}

int F950008(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	ST_CPACK aPack;
	ST_PACK* out_pack = &(aPack.pack);

	char buf[256] = "";

	ret = GetSysParaVal(GLOBAL_SCHOOL_CODE,buf);
	//writelog(LOG_DEBUG,"请求参数parameter[%d]",rPack->lvol0);
	if(ret)
	{
		writelog(LOG_ERR,"获取参数失败[%d]",rPack->lvol0);
		*pRetCode = ret;
		goto L_RETU;
	}
	
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,0);

	
	ret = do_decrypt_school_code(buf,strlen(buf),&out_pack->lvol0);
	if(ret)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	if(out_pack->lvol0 == 0)
	{
		*pRetCode = E_INPUT_DATA_INVAILD;
		goto L_RETU;
	}
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;
L_RETU:
	return -1;
}

