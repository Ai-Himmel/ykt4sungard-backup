#include "card_business.h"
#include "ks_gg.h"

void dec2hex(unsigned char *sDec,int dec_len,char *sHex)
{
	int i=0;
    int k=0;
	for(i=0;i<dec_len;i++)
	{
        k=sDec[i];
        sprintf(&sHex[2*i],"%02X",k);
	}
}

void hex2dec(char *sHex,unsigned char * sDec,int dec_len)
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];

	memset(sHexTmp,0,sizeof(sHexTmp));
	for(i=0;i<dec_len;i++)
	{
		memcpy(sHexTmp,&sHex[2*i],2);
		ul=strtoul(sHexTmp,NULL,16);
		sDec[i]=(unsigned char)ul;
	}
}

int dec2bcd(unsigned char *sDecStr,unsigned char *sBcdStr,int bcd_len)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		lch=sDecStr[2*i]-'0';
		hch=sDecStr[2*i+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		sBcdStr[i]=hch|lch;
	}
	return 0;
}

int bcd2dec(unsigned char *sBcdStr,int bcd_len,char *sDecStr)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<bcd_len;i++)
	{
		hch=(sBcdStr[i]&0x0F);
		lch=(sBcdStr[i]&0xF0);
		lch=lch>>4;
		sDecStr[2*i]=lch+'0';
		sDecStr[2*i+1]=hch+'0';
	}
	return 0;
}

/*
交易卡号 3 字节
卡余额 3 字节
交易次数 2 字节
*/
unsigned char SMT_UCWORKINGKEY[256]="";

static int Login_Card(int sector)
{
	unsigned char ucSerialNo[5], ucKeyA[6];
	int ret;
	char msg[128] = "";
	ret = MF_ReadSeriesNo(ucSerialNo);
	if (ret < 0)
	{
		return -4;
	}

    gen_user_card_keyA(SMT_UCWORKINGKEY, ucSerialNo, ucKeyA);
	ret = SMT_Login_With_UserKey(sector, ucKeyA, 0);
	if(ret != 0)
	{
		return -5;
	}

	return 0;
}

/**
 \param cardid - 交易卡号
 \param bala - 卡余额
 \param cnt - 卡中交易次数
 \return 0 表示成功，－1 表示读卡失败，－2 表示挂失卡，－3表示卡钱包损坏
*/
int read_m1card(unsigned char *cardid,unsigned char *bala,unsigned char *cnt)
{
	int ret = 0;
	int nPacketNo = 1;
	int sector = 0;
	int i;
	unsigned char ucBuffer[16] = "";
	unsigned char ucBuf1[16] = "";
	unsigned char ucBuf2[16] = "";
	unsigned char ucCheck = 0;
	unsigned char ucORCheck = 0;
	char err_msg[128] = "";
	
	ret = Login_Card(1);
	if(ret != 0) { return ret; }

	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if (ret != 0) 
	{
		return -1; 
	}
	
	//nDealCardNo[0] = ucBuffer[0] * 256 * 256 + ucBuffer[1] * 256 + ucBuffer[2];	// 交易卡号
    memcpy(cardid, ucBuffer, 3); // 读取交易卡号

  	ret = Login_Card(3);
	if (ret != 0) { return ret; }

	ret = SMT_ReadBlock(3, 0, ucBuffer);
	if (ret != 0) 
	{
		return -1; 
	}

	if (ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
		return -6; //钱包不允许使用
	}

	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //钱包所在扇区
	if (sector < 4)
	{
		return -7;
	}

	ret = Login_Card(sector);
	if (ret != 0) { return ret; }

	ret = SMT_ReadBlock(sector, 0, ucBuf1);
	if (ret != 0) 
	{
		return -1; 
	}

	ucCheck = 0;
	ucORCheck = 0;
	for (i = 0; i < 15; i++) 
	{ 
		ucCheck += ucBuf1[i]; 
		ucORCheck |= ucBuf1[i];
	}

	if (ucCheck == ucBuf1[15])
	{
		if(0x00 == ucCheck && 0x00 == ucORCheck)
			return -1;
		memcpy(bala, ucBuf1, 3);	// 卡余额
      	memcpy(cnt, ucBuf1 + 3, 2);	// 交易次数
	}
	else
	{
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
		if (ret != 0) 
		{
			return -1; 
		}

		ucCheck = 0;
		ucORCheck = 0;
		for(i = 0; i < 15; i++) 
		{ 
			ucCheck += ucBuf2[i]; 
			ucORCheck |= ucBuf2[i];
		}

		if(ucCheck == ucBuf2[15])
		{
			if(0x00 == ucCheck && 0x00 == ucORCheck)
				return -1;
      		memcpy(bala, ucBuf2, 3);
      		memcpy(cnt, ucBuf2 + 3, 2);
			return 0;
		}
		else
		{
			return -3;
		}
	}

	return 0;
}

/**
 \param cardid - 交易卡号，交易前读取的交易卡号作为这个参数传入，这个函数负责检
查是不是同一张卡
 \param bala - 卡金额，表示充值后卡的余额。
 \param retries - 表示重试次数
 \return 0 表示成功 ， －1表示写卡失败，－3表示卡钱包损坏，－4表示不是同一张卡
 */
int add_m1card(unsigned char *cardid, unsigned char *bala, int retries)
{
	int ret = 0;
	int nPacketNo = 1;
	int sector = 0;
	int i;
	unsigned char ucBuffer[16] = "";
	unsigned char ucBuf1[16] = "";
	unsigned char ucBuf2[16] = "";
	unsigned char ucCheck = 0;

	ret = Login_Card(1);
	if(ret != 0) { return ret; }

	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if(ret != 0) { return -1; } //读卡失败

   if (memcmp(cardid, ucBuffer, 3) != 0) { return -4; }

   ret = Login_Card(3);
	if(ret != 0) { return ret; }

	ret = SMT_ReadBlock(3, 0, ucBuffer);
	if(ret != 0) { return -1; }

	if(ucBuffer[(nPacketNo - 1) * 2] != 0x00)
	{
		return -6; //钱包不允许使用
	}

	sector = ucBuffer[(nPacketNo - 1) * 2 + 1]; //钱包所在扇区
	if(sector < 4)
	{
		return -7;
	}

	ret = Login_Card(sector);
	if(ret != 0) { return ret; }

	ret = SMT_ReadBlock(sector, 0, ucBuf1);
	if(ret != 0) { return -1; }

	ucCheck = 0;
	for(i = 0; i < 15; i++) { ucCheck += ucBuf1[i]; }

	if(ucCheck == ucBuf1[15])
	{
   	memcpy(bala, ucBuf1, 3);	// 卡余额
	}
	else
	{
		ret = SMT_ReadBlock(sector, 2, ucBuf2);
		if(ret != 0) { return -1; }
		ucCheck = 0;
		for(i = 0; i < 15; i++) { ucCheck += ucBuf2[i]; }

		if(ucCheck == ucBuf2[15])
		{
      	memcpy(bala, ucBuf2, 3);
			return 0;
		}
		else
		{
			return -3;
		}
	}

	return 0;
}

/**
 \brief - 读卡器授权，圈存机签到后通过该函数对读卡器授权
 \param portno - 读卡器串口号
 \param cardkey - 圈存机签到时从后台获取的密钥
 \return 0 表示成功 ，－1表示打开读卡器失败，－2表示授权密钥不正确
 */
int auth_m1card(int portno, const char *cardkey)
{
	unsigned char ucCryptWorkKey[17] = "";
    char temp_card_key[17] = "";
	memset(SMT_UCWORKINGKEY, 0, sizeof(SMT_UCWORKINGKEY));
    memcpy(temp_card_key, cardkey, sizeof(temp_card_key));
	hex2dec(temp_card_key, ucCryptWorkKey, 8);
	encrypt_work_key(ucCryptWorkKey, SMT_UCWORKINGKEY);
	return 0;
}

/**
 \brief - 关闭读卡器，关闭之后需要重新调用 auth_m1card 打开读卡器并授权
 \return 0 表示成功 ，－1表示失败
 */
int close_card_reader()
{
	return 0;
}

int test_func(char *msg)
{
	memcpy(msg, "hellow smart card!", 25);
	return 0;
}

int twrite_m1card(int nPacketNo, unsigned long nMoney, unsigned char *cardid, unsigned char *bala, unsigned char *cnt)
{
	int ret,sector;
    	unsigned long i;
	unsigned char ucBuffer[16] = "";
	unsigned char ucBuf1[16] = "";
	unsigned char ucBuf2[16] = "";
	unsigned char ucBufTmp[16] = "";
	unsigned char ucCheck;
	unsigned char ucSerialNo[5] = "";
	unsigned long inter_cnt = 0;
	unsigned long input_cnt = 0;
	unsigned long bal = 0, bin0 = 0, bin1 = 0, bin2 = 0, bin3 = 0;
	
	char err_msg[128] = "";
   
	struct tm tmloc;
	time_t curtime;
	time(&curtime);

/*	ret = Login_Card(1);
	if(ret != 0) { return ret; }

	ret = SMT_ReadBlock(1, 0, ucBuffer);
	if(ret != 0) { return -1; } //读卡失败

   	if (memcmp(cardid, ucBuffer, 3) != 0) { return -4; }
*/   
	if (nPacketNo < 1)
		return -1;
	if (nMoney < 0)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)	return ret;
				
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;
	
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; 
	sector = ucBuffer[(nPacketNo-1)*2+1];
	
	ret = Login_Card(sector);
	if (ret != 0)
		return ret;
	
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)	
		return -6;
	
	ucCheck = 0;
	for(i=0;i<15;i++)
		ucCheck+=ucBuf1[i];
	if(ucCheck == ucBuf1[15])
	{
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
		for (i = 1; i < (ucBufTmp[3] + 1); i++)
		bin1 += 256;

		for (i=1; i < (ucBufTmp[4] + 1); i++)
		bin2 += 1;
				
		inter_cnt = bin0 + bin1 + bin2;

		bin1 = 0;
		bin2 = 0;
		for (i = 1; i < (cnt[0] + 1); i++)
		bin1 += 256;

		for (i=1; i < (cnt[1] + 1); i++)
		bin2 += 1;
				
		input_cnt = bin0 + bin1 + bin2;
		if (input_cnt > inter_cnt) { return -13; }
			
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)	
			return -8;

		i = nMoney;
		/*
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		*/
		ucBuf1[0] = bala[0];
		ucBuf1[1] = bala[1];
		ucBuf1[2] = bala[2];
		
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;

		memcpy(&tmloc, localtime(&curtime), sizeof(tmloc));
		if (tmloc.tm_mday != ucBuf1[7])								
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		
		ucBuf1[5] = (BYTE)(tmloc.tm_year - 100);                       
		ucBuf1[6] = (BYTE)(tmloc.tm_mon + 1);								
		ucBuf1[7] = (BYTE)(tmloc.tm_mday);									
		ucBuf1[8] = (BYTE)(tmloc.tm_hour);									
		ucBuf1[9] = (BYTE)(tmloc.tm_min);								
		ucBuf1[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
		
		return 0;
	}
	else
	{
		for (i = 1; i < (ucBufTmp[3] + 1); i++)
		bin1 += 256;

		for (i=1; i < (ucBufTmp[4] + 1); i++)
		bin2 += 1;
				
		inter_cnt = bin0 + bin1 + bin2;

		bin1 = 0;
		bin2 = 0;
		for (i = 1; i < (cnt[0] + 1); i++)
		bin1 += 256;

		for (i=1; i < (cnt[1] + 1); i++)
		bin2 += 1;
				
		input_cnt = bin0 + bin1 + bin2;
		if (input_cnt > inter_cnt) { return -13; }
		
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		for(i=0;i<15;i++)	
			ucCheck+=ucBuf2[i];
		if(ucCheck != ucBuf2[15])	
			return 2;
		i = nMoney;
		/*
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		*/
		ucBuf2[0] = bala[0];
		ucBuf2[1] = bala[1];
		ucBuf2[2] = bala[2];

		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
		
		memcpy(&tmloc, localtime(&curtime), sizeof(tmloc));
		if (tmloc.tm_mday != ucBuf2[7])                               
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tmloc.tm_year - 100);					
		ucBuf2[6] = (BYTE)(tmloc.tm_mon + 1);							
		ucBuf2[7] = (BYTE)(tmloc.tm_mday);								
		ucBuf2[8] = (BYTE)(tmloc.tm_hour);								
		ucBuf2[9] = (BYTE)(tmloc.tm_min);
		ucBuf2[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if (ret != 0)	
			return -12;
	}
	
	return 0;
}

int write_m1card(int nPacketNo, unsigned long nMoney)
{
	int ret,sector;
   unsigned long i;
	unsigned char ucBuffer[16] = "";
	unsigned char ucBuf1[16] = "";
	unsigned char ucBuf2[16] = "";
	unsigned char ucBufTmp[16] = "";
	unsigned char ucCheck;
	unsigned char ucORCheck;
	unsigned char ucSerialNo[5] = "";
   char err_msg[128] = "";
   
	struct tm tmloc;
	time_t curtime;
	time(&curtime);
	
	if (nPacketNo < 1)
		return -1;
	if (nMoney <= 0)
		return -1;
	ret = Login_Card(3);
	if(ret != 0)	return ret;
				
	ret = SMT_ReadBlock(3,0,ucBuffer);
	if(ret != 0)	return -5;
	
	if(ucBuffer[(nPacketNo-1)*2] != 0x00)
		return 1; 
	sector = ucBuffer[(nPacketNo-1)*2+1];
	
	ret = Login_Card(sector);
	if (ret != 0)
		return ret;
	
	ret = SMT_ReadBlock(sector,0,ucBuf1);
	if(ret != 0)	
		return -6;
	
	ucCheck = 0;
	ucORCheck = 0;
	for(i=0;i<15;i++)
	{
		ucCheck+=ucBuf1[i];
		ucORCheck|=ucBuf1[i];
	}
	
	if(ucCheck == ucBuf1[15])
	{
		if(ucCheck == 0x00 && ucORCheck == 0x00)
		{
			return 2;
		}
		memcpy(ucBufTmp,ucBuf1,sizeof(ucBufTmp));
	
		ret = SMT_WriteBlock(sector,2,ucBufTmp);
		if(ret != 0)
			return -8;
	
		i = nMoney;
		ucBuf1[0] = i%256;
		ucBuf1[1] = i/256;
		ucBuf1[2] = i/256/256;
		i = ucBuf1[3]*256+ucBuf1[4];
		i = i + 1;
		ucBuf1[3] = i/256;
		ucBuf1[4] = i%256;

		memcpy(&tmloc, localtime(&curtime), sizeof(tmloc));
		if (tmloc.tm_mday != ucBuf1[7])								
		{
			ucBuf1[10] = 0;
			ucBuf1[11] = 0;
			ucBuf1[12] = 0;		
		}
		
		ucBuf1[5] = (BYTE)(tmloc.tm_year - 100);                       
		ucBuf1[6] = (BYTE)(tmloc.tm_mon + 1);								
		ucBuf1[7] = (BYTE)(tmloc.tm_mday);									
		ucBuf1[8] = (BYTE)(tmloc.tm_hour);									
		ucBuf1[9] = (BYTE)(tmloc.tm_min);								
		ucBuf1[15]=0;	
		for(i=0;i<15;i++)	
			ucBuf1[15] += ucBuf1[i];
		
		ret = SMT_WriteBlock(sector,0,ucBuf1);
		if(ret != 0)	
			return -8;
		
		return 0;
	}
	else
	{
		ret = SMT_ReadBlock(sector,2,ucBuf2);
		if(ret != 0)	
			return -9;
		ucCheck = 0;
		ucORCheck = 0;
		for(i=0;i<15;i++)
		{
			ucCheck+=ucBuf2[i];
			ucORCheck|=ucBuf2[i];
		}
		if(ucCheck != ucBuf2[15])	
			return 2;
		if(ucCheck == 0x00 && ucORCheck == 0x00)
		{
			return 2;
		}
		i = nMoney;
		ucBuf2[0] = i%256;
		ucBuf2[1] = i/256;
		ucBuf2[2] = i/256/256;
		i = ucBuf2[3]*256+ucBuf2[4];
		i = i + 1;
		ucBuf2[3] = i/256;
		ucBuf2[4] = i%256;
		
		memcpy(&tmloc, localtime(&curtime), sizeof(tmloc));
		if (tmloc.tm_mday != ucBuf2[7])                               
		{
			ucBuf2[10] = 0;
			ucBuf2[11] = 0;
			ucBuf2[12] = 0;		
		}
		ucBuf2[5] = (BYTE)(tmloc.tm_year - 100);					
		ucBuf2[6] = (BYTE)(tmloc.tm_mon + 1);							
		ucBuf2[7] = (BYTE)(tmloc.tm_mday);								
		ucBuf2[8] = (BYTE)(tmloc.tm_hour);								
		ucBuf2[9] = (BYTE)(tmloc.tm_min);
		ucBuf2[15] = 0;	
		for (i = 0; i < 15; i++)	
			ucBuf2[15] += ucBuf2[i];
		ret = SMT_WriteBlock(sector,0,ucBuf2);
		if (ret != 0)	
			return -12;
	}
	
	return 0;
}

