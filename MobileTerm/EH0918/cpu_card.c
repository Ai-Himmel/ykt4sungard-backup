/****************************************************************************
*
*文件(File):         cpu_card.c
*
*修改(Modify):       2011-10-26 09:41:41
*
*作者(Author):       USER
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
*
*
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011-10-26 09:41:41           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"
int get_4byte_int(unsigned char *value_str)
{
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

unsigned short get_2byte_int(unsigned char *value_str)
{
	int r=0,t=0;
	t = value_str[0];
	r = t << 8;
	r |= value_str[1];
	return (short)r;
}

void set_4byte_int(unsigned char *value_str,int num)
{
	value_str[0]=(num>>24)&0xFF;
	value_str[1]=(num>>16)&0xFF;
	value_str[2]=(num>>8)&0xFF;
	value_str[3]=num&0xFF;
}
void mydec2hex(const unsigned char *uDecBuf,int iDecLen,char *sHexStr)	//解压
{
	int i=0;
	int k=0;
	for(i=0;i<iDecLen;i++)
	{
		k=uDecBuf[i];
		sprintf(&sHexStr[2*i],"%02X",k);
	}
}
void myhex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int* iDecBUfLen)	//压缩
{
	int i=0;
	unsigned long ul;
	char sHexTmp[3];
	int offset=0;
	int dlen=iHexLen/2;

	memset(sHexTmp,0,sizeof(sHexTmp));
	if(iHexLen%2)
	{
		sHexTmp[0]='0';
		sHexTmp[1]=sHexStr[0];
		ul=strtoul(sHexTmp,NULL,16);
		uDecBuf[0]=(unsigned char)ul;
		offset++;
	}
	for(i=0;i<dlen;i++)
	{
		memcpy(sHexTmp,&sHexStr[2*i+offset],2);
		ul=strtoul(sHexTmp,NULL,16);
		uDecBuf[i+offset]=(unsigned char)ul;
	}
	*iDecBUfLen=i+offset;
}
/***********************************************************************
		module		:	[CPU卡消费]
		function		:	[CPU卡初始化]
  		return		:	[0：成功
						其他：失败]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[CPU_CARD]
		date			:	[11/09/05]
 		author		:	[chen-zhengkai]
************************************************************************/

void bcd2str(unsigned char *bcd,unsigned char len,unsigned char *str)
{
	unsigned char i;
	for(i = 0;i < len; ++i)
	{
		str[i<<1] = ((bcd[i] >> 4) & 0x0F) + 0x30;
		str[(i<<1)+1] = (bcd[i] & 0x0F) + 0x30;
	}

}



void bcd2asc(const unsigned char *uBcdBuf,int iBcdLen,char *sAscStr)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<iBcdLen;i++)
	{
		hch=(uBcdBuf[i]&0x0F);
		lch=(uBcdBuf[i]&0xF0);
		lch=lch>>4;
		sAscStr[2*i]=lch+'0';
		sAscStr[2*i+1]=hch+'0';
	}
}

void getCardNo(unsigned char *bcd,unsigned char len,unsigned char *str)
{
     unsigned char szFieldVal[256] = {0};
     bcd2asc(bcd,len,szFieldVal);
     int  num = 0;
     for(num=0;num<len*2;num++)
     {
         if(szFieldVal[num]!='0')
             break;
     }
     
     strcpy(str,szFieldVal+num);
}

char cpuCard_ReSet();
char cpucardReadcard()
{
	char retchar = 0;
	short ret = 0;	//执行结果
	unsigned char 	SW1;
	unsigned char	SW2;
	unsigned short	SW = 0;
	unsigned short	rev_len = 0;
	unsigned char	phyNo[8] = {0};
	unsigned char	rev_buf[128] = {0};
	unsigned char	send_buf[128] = {0};
	unsigned char	send_tmp[128] = {0};
	unsigned char	rev_temp[256] = {0};
	unsigned char	date_buf[8] = {0};	//交易日期
	unsigned char	time_buf[6] = {0};	//交易时间
	//unsigned char	devID[8] = {0};	//物理设备ID
	unsigned char	devCnt[8] = {0};	//设备流水号
	unsigned char	devCnt_4bytes[4] = {0};	//设备流水号4字节
	int				devCnt_int = 0;	//设备流水号int
	int				devCnt_len = 0;	//设备流水长度
	unsigned char	DisperFac[14] = {0};	//分散因子
	unsigned char	secCode[9] = {0};		//密钥
	unsigned char	db[20] = {0};
	int send_len = 0;
	char atr[200] = {0};
	int atrLen = 0;
	char tempStr[50] = {0};
	unsigned char randomNum[8] = {0};	//伪随机数
	unsigned char TransNum[4] = {0};	//交易序号
	unsigned char moneyStr[4] = {0};		//交易金额
	unsigned char moneyStr8[8] = {0};	//交易金额
	unsigned char leftMoney[8] = {0};	//钱包余额
	unsigned char leftMoney4[4] = {0};	//钱包余额
	int leftMoney_int = 0;		//钱包余额
	unsigned char moneyLeft[8]	= {0};	//交易后金额
	unsigned char moneyLeft_4bytes[4] = {0};	//交易后金额
	int	moneyLeft_int = 0;		//交易后金额
	//int	moneyLeft_len = 0;	
	unsigned short clk_sel[4] = {ICC_CLOCK_16M, ICC_CLOCK_8M, ICC_CLOCK_4M, ICC_CLOCK_2M};
	unsigned short atr_fidi[2] = {0x11, 0x13};
	char  debugMessage[255] = {0};
	int i, j, k;
	int left_len = 0;
	typ_TIME		ttime;	//时间结构
	typ_DATE	tdate;	//日期结构
	USER_INFO	tempInfo;
	//手持机设备ID
	if ( eeprom_read(tempInfo.device_id, 8, EEPROM_OFFSET_PHYID) ) {
		debugFun("EEPROM-error1");
	}
	//手持机流水
	if ( eeprom_read(devCnt, 8, EEPROM_OFFSET_PHYCNT) ) {
		debugFun("EEPROM-error2");
	}
	myhex2dec(devCnt, 8, devCnt_4bytes, &devCnt_len);
	devCnt_int = get_4byte_int(devCnt_4bytes);
	//memcpy(tempInfo.device_id, devID, 8);
	retchar = cpuCard_init(phyNo);	//CPU卡初始化，读卡，物理ID
	memcpy(tempInfo.phyNo, phyNo, 8);	//将物理卡号存入记录数据结构
	//debugFun(phyNo);
	Sys_Delay_MS(20);
	if (retchar != 0) {
		return -1;
	}

        int iIndex = 0;
	//选择目录
	memset(send_buf, 0 , sizeof(send_buf));
	memset(rev_buf, 0, sizeof(rev_buf));
	hex2dec("D156000001BDF0CACBB4EFD6A7B8B6", 30, send_buf, &send_len);
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xA4, 0x04, 0x00, 0x0F,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		debugFun("错误代码:001");
		return -1;
	}
	mydec2hex(rev_buf, rev_len, rev_temp);
	memcpy(DisperFac, rev_temp+80, 14);
	//debugFun(DisperFac);
	//读取透明文件
	memset(rev_buf, 0, sizeof(rev_buf));
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xB0, 0x96, 0x00, 0x00,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		debugFun("错误代码:002");
		return -1;                                      
	}
	//读取用户基本信息 
	
        memset(send_buf, 0 , sizeof(send_buf));
        memset(rev_buf, 0, sizeof(rev_buf));

        ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xB0, 0x96,0x00, 0x00,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);

        if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) )
        {
		debugFun("交易卡号获取失败");
		return -1;
        }

	//读取姓名 
	
	char szName[256] = {0};
	memcpy(szName,rev_buf,32);
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"姓名： %s",szName);
	DispStr_CE(0,4,debugMessage,DISP_POSITION);
	
	//读取证件号码 
        char szUserID[256] = {0};
	memcpy(szUserID,rev_buf+32,32);
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"证件号码： %s",szUserID);
	DispStr_CE(0,6,debugMessage,DISP_POSITION);
	
	//读取用户性别 
        if(1 == rev_buf[65])
        {
	     DispStr_CE(0,8,"性别： 男",DISP_POSITION);
        }	

        if(2 == rev_buf[65])
        {
	     DispStr_CE(0,8,"性别： 女",DISP_POSITION);
        }
        
        //读取学工号
        
        char szStump[21] = {0};
        memcpy(szStump,rev_buf+66,20);
        memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"学工号： %s",szStump);
	DispStr_CE(0,10,debugMessage,DISP_POSITION);
	
	
	 //部门代码
        char szDepCode[21] = {0};
        memcpy(szDepCode,rev_buf+86,20);
        memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"部门代码： %s",szDepCode);
	DispStr_CE(0,12,debugMessage,DISP_POSITION);
	
	
	//客户类型 
        char szCusType[2] = {0};
        memcpy(szCusType,rev_buf+106,1);
        memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"客户类型： %d",szCusType[0]);
	DispStr_CE(0,14,debugMessage,DISP_POSITION);
        
	        
        //选择主目录
	/*memset(send_buf, 0 , sizeof(send_buf));
	memset(rev_buf, 0, sizeof(rev_buf));
	hex2dec("3F00", 4, send_buf, &send_len);
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xA4, 0x00, 0x00, 0x02,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		debugFun("选择主目录错误:001");
		return -1;
	}
	
	//选择子目录
	SW1 = -1; 
        SW2 = -1;
	memset(send_buf, 0 , sizeof(send_buf));
	memset(rev_buf, 0, sizeof(rev_buf));
	hex2dec("D156000001BDF0CACBB4EFD6A7B8B6", 30, send_buf, &send_len);
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xA4, 0x04, 0x00, 0x0F,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
                sprintf(debugMessage,"%d%d",SW1,SW2);
                debugFun(debugMessage);
		debugFun("错误代码:001");
		return -1;
	} */
	
	SW1 = -1; 
        SW2 = -1;
        memset(rev_buf, 0, sizeof(rev_buf));
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xB0, 0x95, 0x00, 0x00,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
                
                sprintf(debugMessage,"%d%d",SW1,SW2);
                debugFun(debugMessage);
		debugFun("错误代码:002");
		return -1;                                      
	}
	//读取交易卡号 
	
        memset(send_buf, 0 , sizeof(send_buf));
        memset(rev_buf, 0, sizeof(rev_buf));

        ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xB0, 0x95,0x00, 0x00,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);

        if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) )
        {
		debugFun("交易卡号获取失败");
		return -1;
        }
        
         //读取交易卡号
	//bcd2str(rev_buf,10,tempInfo.cardNum);
	getCardNo(rev_buf,10,tempInfo.cardNum);
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"交易卡号：%s",tempInfo.cardNum);
	DispStr_CE(0,16,debugMessage,DISP_POSITION);
	
	//读取卡状态 
	unsigned char szCardState[2] = {0};
	//bcd2str(rev_buf+20,1,szCardState);
	memcpy(szCardState,rev_buf+20,1);
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"卡状态：%d",szCardState[0]);
	DispStr_CE(0,18,debugMessage,DISP_POSITION);
	
	//读取卡结构版本 
	char szCardVersion[2] = {0};
	strncpy(szCardVersion,rev_buf+35,1);
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"卡结构版本：%d",szCardVersion[0]);
	DispStr_CE(0,20,debugMessage,DISP_POSITION);
        
        delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
	return 0;
}


void set_2byte_int(unsigned char *value_str,int num)
{
	value_str[0]=(num>>8)&0xFF;
	value_str[1]=num&0xFF;
}


void reverse2byte(const char * pSrc, char *pDes)
{
     int i = 0;
     for(i=0; i<4; i++)
     {
         memcpy(pDes+i*2,pSrc+6-i*2,2);
     }
}
char cpucardCum_neiyi(int money, int* leftM)
{
	int debugFlag=1;
        char retchar = 0;
	short ret = 0;	//执行结果
	unsigned char 	SW1;
	unsigned char	SW2;
	unsigned short	SW = 0;
	unsigned short	rev_len = 0;
	unsigned char	phyNo[8] = {0};
	unsigned char	rev_buf[128] = {0};
	unsigned char	send_buf[128] = {0};
	unsigned char	send_tmp[128] = {0};
	unsigned char	rev_temp[256] = {0};
	unsigned char	date_buf[8] = {0};	//交易日期
	unsigned char	time_buf[6] = {0};	//交易时间
	//unsigned char	devID[8] = {0};	//物理设备ID
	unsigned char	devCnt[8] = {0};	//设备流水号
	unsigned char	devCnt_4bytes[4] = {0};	//设备流水号4字节
	int				devCnt_int = 0;	//设备流水号int
	int				devCnt_len = 0;	//设备流水长度
	unsigned char	DisperFac[14] = {0};	//分散因子
	unsigned char	secCode[9] = {0};		//密钥
	unsigned char	db[20] = {0};
	int send_len = 0;
	char atr[200] = {0};
	int atrLen = 0;
	char tempStr[50] = {0};
	unsigned char randomNum[8] = {0};	//伪随机数
	unsigned char TransNum[4] = {0};	//交易序号
	unsigned char moneyStr[4] = {0};		//交易金额
	unsigned char moneyStr8[8] = {0};	//交易金额
	unsigned char leftMoney[8] = {0};	//钱包余额
	unsigned char leftMoney4[4] = {0};	//钱包余额
	int leftMoney_int = 0;		//钱包余额
	unsigned char moneyLeft[8]	= {0};	//交易后金额
	unsigned char moneyLeft_4bytes[4] = {0};	//交易后金额
	int	moneyLeft_int = 0;		//交易后金额
	//int	moneyLeft_len = 0;	
	unsigned short clk_sel[4] = {ICC_CLOCK_16M, ICC_CLOCK_8M, ICC_CLOCK_4M, ICC_CLOCK_2M};
	unsigned short atr_fidi[2] = {0x11, 0x13};
	char  debugMessage[255] = {0};
	int i, j, k;
	int left_len = 0;
	typ_TIME		ttime;	//时间结构
	typ_DATE	tdate;	//日期结构
	USER_INFO	tempInfo;
	//手持机设备ID
	if ( eeprom_read(tempInfo.device_id, 8, EEPROM_OFFSET_PHYID) ) {
		debugFun("EEPROM-error1");
	}
	//手持机流水
	if ( eeprom_read(devCnt, 8, EEPROM_OFFSET_PHYCNT) ) {
		debugFun("EEPROM-error2");
	}
	myhex2dec(devCnt, 8, devCnt_4bytes, &devCnt_len);
	devCnt_int = get_4byte_int(devCnt_4bytes);
	//memcpy(tempInfo.device_id, devID, 8);
	retchar = cpuCard_init(phyNo);	//CPU卡初始化，读卡，物理ID
	
	char szPhysical[9] = {0};
	reverse2byte(phyNo, szPhysical);
	memcpy(tempInfo.phyNo, szPhysical, 8);	//将物理卡号存入记录数据结构
	
	//debugFun(phyNo);
	//debugFun(szPhysical);
	Sys_Delay_MS(20);
	if (retchar != 0) {
		return -1;
	}

        int iIndex = 0;
	//选择目录
	memset(send_buf, 0 , sizeof(send_buf));
	memset(rev_buf, 0, sizeof(rev_buf));
	hex2dec("D156000001BDF0CACBB4EFD6A7B8B6", 30, send_buf, &send_len);
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xA4, 0x04, 0x00, 0x0F,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		debugFun("错误代码:001");
		return -1;
	}
	mydec2hex(rev_buf, rev_len, rev_temp);
	memcpy(DisperFac, rev_temp+80, 14);
	
	//debugFun(DisperFac);
	//读取透明文件
	memset(rev_buf, 0, sizeof(rev_buf));
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xB0, 0x95, 0x00, 0x00,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		debugFun("错误代码:002");
		return -1;                                      
	}
	//读取交易卡号 
	
	for(iIndex = 0; iIndex < 5; iIndex ++)
	{
             memset(send_buf, 0 , sizeof(send_buf));
             memset(rev_buf, 0, sizeof(rev_buf));

	     ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x00, 0xB0, 0x95,0x00, 0x00,
					send_buf, 0 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);

             if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		debugFun("交易卡号获取失败");
		return -1;
             }
	}
	
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"APDU,CardState=%d",rev_len);
	//debugFun(debugMessage);
	//读取交易卡号
	//bcd2str(rev_buf,10,tempInfo.cardNum);
	getCardNo(rev_buf,10,tempInfo.cardNum);
	
        //memset(debugMessage,0,sizeof(debugMessage));
	//sprintf(debugMessage,"APDU,CardNO=%s",tempInfo.cardNum);
	//debugFun(debugMessage);
	
	//读取卡状态 
	unsigned char szCardState[2] = {0};
	//bcd2str(rev_buf+20,1,szCardState);
	memcpy(szCardState,rev_buf+20,1);
	/*
        memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"APDU,CardState=%d",szCardState[0]);
	debugFun(debugMessage);
	*/
	//读取卡结构版本 
	char szCardVersion[2] = {0};
	//bcd2str(rev_buf+35,1,szCardVersion);
	strncpy(szCardVersion,rev_buf+35,1);
	/*
	memset(debugMessage,0,sizeof(debugMessage));
	sprintf(debugMessage,"APDU,CardVersion=%d",szCardVersion[0]);
	debugFun(debugMessage);
	*/
	
	
	//psam卡初始化                   
	ICC_interface_power(ICC_POWER_ON);
	ret = ICC_select_sock(ICC_SOCK_AUX1);
	if (ret) {
		debugFun("找不到卡槽");
		return -1;
	}
#if 1
	for (i = 0; i < 3; i++) {
		ret = ICC_cpucard_ATR(atr, &atrLen, ICC_CLOCK_4M, ICC_VOLTAGE_3, 0x11, ICC_CPUC_ATR_FLAG_LONGATR);	//卡片上电
		if (ret == 0) {
			break;
		}
	}
	//char s[30] = {0};
	if (ret) {
		//sprintf(s, "psam ret:%d", ret);
		debugFun("psam上电失败");
		return -1;
	}
#endif
	if ((ICC_cpucard_get_param())->isT1) {
		debugFun("卡片是t1协议");
		return -1;
	}
	//读取透明文件（psam）
	ret = ICC_T0_TPDU(1 , 0x00 ,0xB0, 0x96, 0x00 , 0x06,  rev_buf, &SW);
	if (ret) {
		debugFun("读取透明文件失败");
		return -1;
	}
	if ( !(SW == 0x9000 || (SW >> 8) == 0x61) ) {	//执行不成功
		debugFun("读取透明文件出错");
		return -1;
	}
	mydec2hex(rev_buf, 6, tempStr);
	
	
	//读取余额 
	int iCount = 0; 
	
                     
        for(iCount = 0; iCount < 3; iCount ++)
        {     
              memset(send_buf, 0 , sizeof(send_buf));
              memset(rev_buf, 0, sizeof(rev_buf));             
              ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x80, 0x5C, 0x00,0x02, 0x00,
					send_buf, 0x04 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
              if(-4 == ret)
              {
                    continue;
              }
              
	      if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
                  memset(debugMessage,0,sizeof(debugMessage));
                  sprintf(debugMessage,"%d",ret);  
                  debugFun(debugMessage);  
		  debugFun("获取余额失败");
		  return -1;
               }
               else
               {
                    debugFun("获取余额成功");
                    break; 
               }               

	}
	
	if(-4 == ret)
        {
              debugFun("获取余额等待数据超时");
        }
	
	//消费初始化
	SW1 = -1; 
        SW2 = -1;
	memset(send_tmp, 0, sizeof(send_tmp));
	strcpy(send_tmp, "01");
	set_4byte_int(moneyStr, money);
	mydec2hex(moneyStr, 4, moneyStr8);
	memcpy(send_tmp+2, moneyStr8, 8);	//交易金额
	strcat(send_tmp, tempStr);
	hex2dec(send_tmp, 22, send_buf, &send_len);
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x80, 0x50, 0x01, 0x02, 0x0B,
					send_buf, 0x0F , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
					
	if ( (SW1==0x65)&&(SW2==0x81) ) {
		debugFun("写EEPROM不成功");
	}
	
	if ( (SW1==0x62)&&(SW2==0x83) ) {  
		debugFun("选择文件无效");
	}
	
	if ( (SW1==0x69)&&(SW2==0x82) ) {
		debugFun("不满足安全状态");
	}
	
	if ( (SW1==0x6A)&&(SW2==0x82) ) {
		debugFun("文件未找到");
	}
	if ( (SW1==0x69)&&(SW2==0x85) ) {
		debugFun("使用条件不满足");
	}
	
	if ( (SW1==0x6A)&&(SW2==0x81) ) {
		debugFun("功能不支持");
	}
	
	if ( (SW1==0x94)&&(SW2==0x01) ) {
		debugFun("金额不足");
	}
	
	if ( (SW1==0x94)&&(SW2==0x03) ) {
		debugFun("密钥索引不支持");
	}
	
	
        if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {   
 
                memset(debugMessage,0,sizeof(debugMessage));
                sprintf(debugMessage,"%d",ret);  
                debugFun(debugMessage);   
                
                sprintf(debugMessage,"%d%d",SW1,SW2); 
                debugFun(debugMessage);                                 
		debugFun("错误代码:004");
		return -1;
	}
	
	//mydec2hex(rev_buf, rev_len, rev_temp);
	int  iTransNum = 0;
	mydec2hex(rev_buf+11, 4, randomNum);	//随机数
	//strncpy(TransNum, &(rev_buf[rev_len+4]), 2);	//交易序号
	//memcpy(tempInfo.cardCnt, TransNum, 2);	//卡交易次数
	//memcpy(leftMoney, &(rev_temp[48]), 8);	//钱包余额
	//memcpy(tempInfo.leftMoney, leftMoney, 8);	//交易前金额
	//debugFun(leftMoney);
	//myhex2dec(leftMoney, 8, leftMoney4, &left_len);
	//dblen(leftMoney, 8);
	iTransNum = get_2byte_int(rev_buf+4);
	
	sprintf(TransNum,"%04X",iTransNum);
	debugFun(debugMessage); 
	if (debugFlag)
        {
	   char szKey[5] = {0};
           mydec2hex(rev_buf+9, 2, szKey);
           memset(debugMessage,0,sizeof(debugMessage));
           sprintf(debugMessage,"密钥：%s",szKey); 
	   debugFun(debugMessage);
        }
	leftMoney_int= get_4byte_int(rev_buf);
	/*
	memset(debugMessage,0,sizeof(debugMessage));
        sprintf(debugMessage,"%d",leftMoney_int);  
        debugFun(debugMessage);
        */ 
	//交易后金额
	moneyLeft_int =leftMoney_int- money;
	*leftM = moneyLeft_int;
	set_4byte_int(moneyLeft_4bytes , moneyLeft_int);
	mydec2hex(moneyLeft_4bytes, 4, moneyLeft);
	memcpy(tempInfo.moneyLeft, moneyLeft, 8);
	//debugFun(&(rev_temp[rev_len*2-8]));
	//选择PSAM目录
	memset(send_buf, 0, sizeof(send_buf));
	hex2dec("D156000001BDF0CACBB4EFD6A7B8B6FF", 32, send_buf, &send_len);
	ret = ICC_T0_TPDU(0 , 0x00 ,0xA4, 0x04, 0x00 , 0x0F,  send_buf, &SW);
	if (ret) {
		debugFun("选择命令失败");
		return -1;
	}
	
        if ( (SW >> 8) != 0x61) {	//执行不成功
	                
	        sprintf(debugMessage,"%04x",SW);  
                debugFun(debugMessage);
		debugFun("选择目录出错");
		return -1;
	} 
 
	//接收数据
	 ret = ICC_T0_TPDU(1,0x00,0xC0,0x00,0x00, 0x0F ,rev_buf, &SW);
	if (ret) {
		debugFun("获取数据失败");
		return -1;
	}
	if ( !(SW == 0x9000 || (SW >> 8) == 0x61) ) {	//执行不成功
		debugFun("获取数据不成功");
		return -1;
	}
	//PSAM计算密钥（PSAM消费初始化）
	memset(send_buf, 0, sizeof(send_buf));
	memset(send_tmp, 0, sizeof(send_tmp));
	memset(tempStr, 0, sizeof(tempStr));
	memcpy(send_tmp, randomNum, 8);		//随机数
  
	if (debugFlag){
           memset(debugMessage,0,sizeof(debugMessage));
	   sprintf(debugMessage,"随机数randomNum=%s",randomNum);
	   debugFun(debugMessage);
        }
	
	memcpy(send_tmp+8, TransNum, 4);		//交易序号
	set_4byte_int(moneyStr, money);
	mydec2hex(moneyStr, 4, moneyStr8);      
	if (debugFlag){
           memset(debugMessage,0,sizeof(debugMessage));
	   sprintf(debugMessage,"随机数moneyStr8=%s",moneyStr8);
	   debugFun(debugMessage);
        }
	memcpy(send_tmp+12, moneyStr8, 8);	//交易金额
	memcpy(send_tmp+20, "06", 2);		//交易类型标识
	RTC_Get_Time(&ttime);		//获取现在时间
	RTC_Get_Date(&tdate);		//获取当前日期
	sprintf(date_buf, "%04d%02d%02d", tdate.year, tdate.month, tdate.day);
	memcpy(tempInfo.cum_date, date_buf, 8);		//交易日期
	memcpy(send_tmp+22, date_buf, 8);		//交易日期
	if (debugFlag){
           memset(debugMessage,0,sizeof(debugMessage));
	   sprintf(debugMessage,"date_buf=%s",date_buf);
	   debugFun(debugMessage);
        }
	sprintf(time_buf, "%02d%02d%02d", ttime.hour, ttime.min, ttime.sec);
	memcpy(send_tmp+30, time_buf, 6);		//交易时间
	if (debugFlag){
           memset(debugMessage,0,sizeof(debugMessage));
	   sprintf(debugMessage,"time_buf=%s",time_buf);
	   debugFun(debugMessage);
        }
	memcpy(send_tmp+36, "0100", 4);	//消费密钥版本，算法标识
	memcpy(send_tmp+40, szPhysical, 8);	//分散密钥前7字节
	if (debugFlag){
           memset(debugMessage,0,sizeof(debugMessage));
	   sprintf(debugMessage,"szPhysical=%s",szPhysical);
	   debugFun(debugMessage);
        }
	memcpy(send_tmp+48, "80000000", 8);	//分散密钥后9字节
	//00000000
	myhex2dec(send_tmp, strlen(send_tmp), send_buf, &send_len);
	ret = ICC_T0_TPDU(0 , 0x80 ,0x70, 0x00, 0x00 , 0x1E,  send_buf, &SW);
	if (ret) {
		debugFun("计算MAC失败");
		return -1;
	}
	if ( !(SW == 0x9000 || (SW >> 8) == 0x61) ) {	//执行不成功
	          memset(debugMessage,0,sizeof(debugMessage));
	          sprintf(debugMessage,"%04x",SW);  
                debugFun(debugMessage);
		debugFun("计算MAC出错");
		return -1;
	}
	//获取密钥
	memset(rev_temp, 0, sizeof(rev_temp));
	ret = ICC_T0_TPDU(1,0x00,0xC0,0x00,0x00, 0x08 ,rev_temp, &SW);
	if (ret) {
		debugFun("获取密钥失败");
		return -1;
	}
	if ( !(SW == 0x9000 || (SW >> 8) == 0x61) ) {	//执行不成功
		debugFun("获取密钥失败");
		return -1;
	}
	mydec2hex(rev_temp, 8, rev_buf);
	char szTermno[256] = {0};
	memcpy(szTermno, rev_buf, 8);
	memcpy(secCode, rev_buf+8, 8);
	//debugFun(secCode);
	//消费
	memset(send_buf, 0, sizeof(send_buf));
	memset(send_tmp, 0, sizeof(send_tmp));
	//memcpy(send_tmp, "05000000014703", 14);	//企业ID，子应用索引号
	memcpy(send_tmp+14, szTermno, 8);	//终端交易序号
	memcpy(send_tmp+22, date_buf, 8);	//交易日期
	memcpy(send_tmp+30, time_buf, 6);	//交易时间
	memcpy(send_tmp+36, secCode, 8);	//交易密钥
	myhex2dec(send_tmp, strlen(send_tmp), send_buf, &send_len);
	ret = ISO14443_APDU_Exchange_Ex(1, 0xff, 0xFF, 0x80, 0x54, 0x01, 0x00, 0x0F,
					send_buf, 0x08 , (unsigned char *)rev_buf, &rev_len,
					&SW1,&SW2);
	if ( (ret!=RCX_OK)||(SW1!=0x90)||(SW2!=0x00) ) {
		tempStr[0] = SW1;
		tempStr[1] = SW2;
		mydec2hex(tempStr, 2, db);
		//debugFun("错误代码:005");
		debugFun(db);
		return -1;
	}
	//流水递增
	devCnt_int++;
	set_4byte_int(devCnt_4bytes, devCnt_int);
	mydec2hex(devCnt_4bytes, 4, devCnt);
	if ( eeprom_write(devCnt, 8, EEPROM_OFFSET_PHYCNT) ) {
		debugFun("EEPROM-error3");
	}
	memcpy(tempInfo.device_cnt, devCnt, 8);
	//添加记录到数据库
	//debugFun(phyNo);
	//debugFun(tempInfo.phyNo);
	memcpy(tempInfo.cum_money, moneyStr8, 8);	//交易金额
	//debugFun(tempInfo.cum_money);
	//memcpy(tempInfo.cum_date, date_buf, 8);		//交易日期
	//debugFun(date_buf);
	memcpy(tempInfo.cum_time, time_buf, 6);		//交易时间
	//debugFun(tempInfo.cum_time);
	ret = DB_add_record(ATTENDANCE_INDEX,  (void *)(&tempInfo));	//把记录添加到数据库中
	//debugFun((unsigned char*)(&tempInfo)+8);
	if ( !ret ) {
		//记录添加失败
		DispStr_CE(0,12,"记录添加失败",DISP_CENTER);
		DispStr_CE(0,14,"按任意键返回",DISP_CENTER);
		delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
	}
	//debugFun(send_tmp+12);
	//debugFun(time_buf);
	//debugFun(debugStr);
	return 0;
}
/***********************************************************************
		module		:	[CPU卡消费]
		function		:	[CPU卡初始化]
  		return		:	[0：成功
						其他：失败]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[CPU_CARD]
		date			:	[11/09/05]
 		author		:	[chen-zhengkai]
************************************************************************/
char cpuCard_init(unsigned char* phn)
{
	unsigned char 	ATQ[4];       
	unsigned char 	sno[12]; 
	unsigned char phyNo[4];
	unsigned char 	databuf[32];
	char 	tmpbuf[100];
	char	hintstr1[20];
	char	hintstr2[20];
	int		read_ok = 0;		
	int		timer_no = 0;
	int		ret = 0;
	int		trycnt = 0;
	unsigned short	atslen;
	unsigned char 	sak;  		
	char		retchar;
	char temp[10] = {0};	
	
	strcpy(hintstr1,"请在%d秒内刷卡");
	strcpy(hintstr2,"未读到合法卡!");
	
	RCX_Init(CARD_TYPE_14443A);
	RCX_Adjust_RxGain(0x00);	//important!!!
	
	Disp_Clear();
	
	ret = User_Timer_Get();
	if(ret>0)
	{
		timer_no = ret;
		User_Timer_Start(timer_no,1);
	}
	else
	{		
		DispStr_CE(0,4,"not enough timer",DISP_CENTER|DISP_CLRLINE);
		ret = -1;
		goto end;
	}
	//读ATQ
	KEY_Flush_FIFO();
	memset(ATQ,0,sizeof(ATQ)); 
	for( trycnt=11; trycnt>0; )	
	{
		if(!User_Timer_Read(timer_no))
		{			
			sprintf(tmpbuf,hintstr1,--trycnt);
			DispStr_CE(0,0,tmpbuf,DISP_CENTER|DISP_CLRLINE);
			User_Timer_Start(timer_no,64);
  		}
  	
		retchar = CardTypeARequest(PICC_REQALL,ATQ);
		if ( retchar==RCX_OK )
		{
			read_ok = 1;
			break;
		}
		if(KEY_Read()==KEY_F1)
		{
			break;
		}			
	}
	User_Timer_End(timer_no);	//释放定时器
	KEY_Flush_FIFO();
	
	if ( !read_ok )
	{		
		warning_beep(1);
		DispStr_CE(0,3,hintstr2,DISP_CENTER|DISP_CLRSCR);		
		ret = -2;
		goto end;
	}
	
	//sprintf(tmpbuf,"ATQ:%02X %02X",ATQ[0],ATQ[1]);
	//DispStr_CE(0,0,tmpbuf,DISP_POSITION|DISP_CLRSCR|DISP_5x7);
	
	Sys_Delay_MS(10);
		
	//防冲突,选择
	memset(sno,0,sizeof(sno));
	retchar = CardTypeAAnticoll(PICC_ANTICOLL1,sno);	
	retchar |= CardTypeASelect(PICC_ANTICOLL1,sno,&sak);
	memcpy(phyNo, sno, 4);
	if(retchar!=RCX_OK)
	{
		//sprintf(tmpbuf,"Sel 1 Err:%d",retchar);
		//DispStr_CE(0,2,tmpbuf,DISP_CENTER);
		ret = -3;
		goto end;		
	}
	//sprintf(tmpbuf,"Sel1:%02X%02X%02X%02X SAK:%02X",sno[0],sno[1],sno[2],sno[3],sak);
	//DispStr_CE(0,1,tmpbuf,DISP_POSITION|DISP_5x7);
	if(sak&0x04)
	{		
		retchar = CardTypeAAnticoll(PICC_ANTICOLL2,sno+4);			
		retchar |= CardTypeASelect(PICC_ANTICOLL2,sno+4,&sak);
		memcpy(phyNo, sno+4, 4);
		if(retchar!=RCX_OK)
		{			
			//sprintf(tmpbuf,"Sel 2 Err:%d",retchar);
			//DispStr_CE(0,4,tmpbuf,DISP_CENTER);
			ret = -4;
			goto end;
		}
		//sprintf(tmpbuf,"Sel2:%02X%02X%02X%02X SAK:%02X",sno[4],sno[5],sno[6],sno[7],sak);
		//DispStr_CE(0,2,tmpbuf,DISP_POSITION|DISP_5x7);		
	}
	if(sak&0x04)
	{		
		retchar = CardTypeAAnticoll(PICC_ANTICOLL3,sno+8);			
		retchar |= CardTypeASelect(PICC_ANTICOLL3,sno+8,&sak);
		memcpy(phyNo, sno+8, 4);
		if(retchar!=RCX_OK)
		{			
			//sprintf(tmpbuf,"Sel 3 Err:%d",retchar);
			//DispStr_CE(0,4,tmpbuf,DISP_CENTER);
			ret = -5;
			goto end;;
		}
		//sprintf(tmpbuf,"Sel3:%02X%02X%02X%02X SAK:%02X",sno[8],sno[9],sno[10],sno[11],sak);
		//DispStr_CE(0,3,tmpbuf,DISP_POSITION|DISP_5x7);			
	}
	if((sak&0x24)==0)
	{
		//DispStr_CE(0,6,"no ISO14443-4",DISP_CENTER);		//错这行//add by chen
		ret = -6;
		goto end;
	}
	
	//RATS
	retchar = CardTypeARATS(0,databuf,&atslen);
	if(retchar!=RCX_OK)
	{  	
		//sprintf(tmpbuf,"RATS Error:%d",retchar);
		//DispStr_CE(0,6,tmpbuf,DISP_POSITION);		
		ret = -7;
		goto end;
	}
	//sprintf(tmpbuf,"ATS:%02X %02X %02X %02X",databuf[0],databuf[1],databuf[2],databuf[3]);
	//DispStr_CE(0,4,tmpbuf,DISP_POSITION|DISP_5x7);
	
	ret = 0;
	goto ok;
		
end:	
	RCX_Close();
	delay_and_wait_key(0,EXIT_KEY_ALL,0);
	
ok:
	mydec2hex(phyNo, 4, temp);
	memcpy(phn, temp, 8);
	//debugFun(phn);		
	return ret;
}


char cpuCard_ReSet()
{
        unsigned char* phn;
	unsigned char 	ATQ[4];       
	unsigned char 	sno[12]; 
	unsigned char phyNo[4];
	unsigned char 	databuf[32];
	char 	tmpbuf[100];
	char	hintstr1[20];
	char	hintstr2[20];
	int		read_ok = 0;		
	int		timer_no = 0;
	int		ret = 0;
	int		trycnt = 0;
	unsigned short	atslen;
	unsigned char 	sak;  		
	char		retchar;
	char temp[10] = {0};	
	
	strcpy(hintstr1,"请在%d秒内刷卡");
	strcpy(hintstr2,"未读到合法卡!");
	
	//RCX_Init(CARD_TYPE_14443A);
	//RCX_Adjust_RxGain(0x00);	//important!!!
	
	Disp_Clear();
	
	ret = User_Timer_Get();
	if(ret>0)
	{
		timer_no = ret;
		User_Timer_Start(timer_no,1);
	}
	else
	{		
		DispStr_CE(0,4,"not enough timer",DISP_CENTER|DISP_CLRLINE);
		ret = -1;
		goto end;
	}
	//读ATQ
	//KEY_Flush_FIFO();
	memset(ATQ,0,sizeof(ATQ)); 
	for( trycnt=11; trycnt>0; )	
	{
		if(!User_Timer_Read(timer_no))
		{			
			sprintf(tmpbuf,hintstr1,--trycnt);
			//DispStr_CE(0,0,tmpbuf,DISP_CENTER|DISP_CLRLINE);
			User_Timer_Start(timer_no,64);
  		}
  	
		//retchar = CardTypeARequest(PICC_REQALL,ATQ);
		retchar =  RCX_OK;
		if ( retchar==RCX_OK )
		{
			read_ok = 1;
			break;
		}                                       
		if(KEY_Read()==KEY_F1)
		{
			break;
		}			
	}
	User_Timer_End(timer_no);	//释放定时器
	KEY_Flush_FIFO();
	
	if ( !read_ok )
	{		
		warning_beep(1);
		//DispStr_CE(0,3,hintstr2,DISP_CENTER|DISP_CLRSCR);		
		ret = -2;
		goto end;
	}
	
	//sprintf(tmpbuf,"ATQ:%02X %02X",ATQ[0],ATQ[1]);
	//DispStr_CE(0,0,tmpbuf,DISP_POSITION|DISP_CLRSCR|DISP_5x7);
	
	Sys_Delay_MS(10);
		
	//防冲突,选择
	memset(sno,0,sizeof(sno));
	/*retchar = CardTypeAAnticoll(PICC_ANTICOLL1,sno);	
	retchar |= CardTypeASelect(PICC_ANTICOLL1,sno,&sak);*/
	retchar =  RCX_OK;
	memcpy(phyNo, sno, 4);
	if(retchar!=RCX_OK)
	{
		//sprintf(tmpbuf,"Sel 1 Err:%d",retchar);
		//DispStr_CE(0,2,tmpbuf,DISP_CENTER);
		ret = -3;
		goto end;		
	}
	//sprintf(tmpbuf,"Sel1:%02X%02X%02X%02X SAK:%02X",sno[0],sno[1],sno[2],sno[3],sak);
	//DispStr_CE(0,1,tmpbuf,DISP_POSITION|DISP_5x7);
	if(sak&0x04)
	{		
		/*retchar = CardTypeAAnticoll(PICC_ANTICOLL2,sno+4);			
		retchar |= CardTypeASelect(PICC_ANTICOLL2,sno+4,&sak); */
		retchar =  RCX_OK;
		memcpy(phyNo, sno+4, 4);
		if(retchar!=RCX_OK)
		{			
			//sprintf(tmpbuf,"Sel 2 Err:%d",retchar);
			//DispStr_CE(0,4,tmpbuf,DISP_CENTER);
			ret = -4;
			goto end;
		}
		//sprintf(tmpbuf,"Sel2:%02X%02X%02X%02X SAK:%02X",sno[4],sno[5],sno[6],sno[7],sak);
		//DispStr_CE(0,2,tmpbuf,DISP_POSITION|DISP_5x7);		
	}
	if(sak&0x04)
	{		
		/*retchar = CardTypeAAnticoll(PICC_ANTICOLL3,sno+8);			
		retchar |= CardTypeASelect(PICC_ANTICOLL3,sno+8,&sak); */
		retchar =  RCX_OK;
		memcpy(phyNo, sno+8, 4);
		if(retchar!=RCX_OK)
		{			
			//sprintf(tmpbuf,"Sel 3 Err:%d",retchar);
			//DispStr_CE(0,4,tmpbuf,DISP_CENTER);
			ret = -5;
			goto end;;
		}
		//sprintf(tmpbuf,"Sel3:%02X%02X%02X%02X SAK:%02X",sno[8],sno[9],sno[10],sno[11],sak);
		//DispStr_CE(0,3,tmpbuf,DISP_POSITION|DISP_5x7);			
	}
	/*if((sak&0x24)==0)
	{
		//DispStr_CE(0,6,"no ISO14443-4",DISP_CENTER);		//错这行//add by chen
		ret = -6;
		goto end;
	} */
	
	//RATS
	//retchar = CardTypeARATS(0,databuf,&atslen);
	retchar =  RCX_OK;
	if(retchar!=RCX_OK)
	{  	
		//sprintf(tmpbuf,"RATS Error:%d",retchar);
		//DispStr_CE(0,6,tmpbuf,DISP_POSITION);		
		ret = -7;
		goto end;
	}
	//sprintf(tmpbuf,"ATS:%02X %02X %02X %02X",databuf[0],databuf[1],databuf[2],databuf[3]);
	//DispStr_CE(0,4,tmpbuf,DISP_POSITION|DISP_5x7);
	
	ret = 0;
	goto ok;
		
end:	
	RCX_Close();
	delay_and_wait_key(0,EXIT_KEY_ALL,0);
	
ok:
	mydec2hex(phyNo, 4, temp);
	memcpy(phn, temp, 8);
	//debugFun(phn);		
	return ret;
}
/***********************************************************************
		module		:	[CPU卡消费]
		function		:	[CPU卡消费（内医科）]
  		return		:	[0：消费成功
						其他：消费失败]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[CPU_CARD]
		date			:	[11/09/05]
 		author		:	[chen-zhengkai]
************************************************************************/
char consumpionNM()
{
	int moneyInput = 0;	// 金额(单位：分)
	int leftMoney = 0;	//消费前剩余金额（单位：分）
	int leftMM = 0;	//消费后剩余金额
	//float monCum = 0.0	//输入计算金额
	char monIn[20] = {0};		//输入字符串
	char dispMoney[50] = {0};
	char displeft[50] = {0};
	int yuan = 0;
	int jiao = 0;
	int fen = 0;
	//Disp_Clear();
	DispStr_CE(0,0,"输入消费金额(1--10000)",DISP_CENTER|DISP_CLRSCR);
	if ( !input_money(2, 10, 1, 0, 10000, "金额:", &moneyInput, monIn) ) {
		//debugFun(monIn);
		moneyInput = myatomon(monIn);	// 获得消费金额(单位：分)
		if (moneyInput == 0) {
			DispStr_CE(0,12,"输入金额不能为零",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,14,"按任意键返回",DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			return -1;
		}
		if ( !cpucardCum_neiyi(moneyInput, &leftMoney) ) {
			yuan = moneyInput / 100;
			jiao = moneyInput % 100 / 10;
			fen = moneyInput % 10;
			sprintf(dispMoney ,"消费金额%d元%d角%d分", yuan, jiao, fen);
			yuan = leftMoney / 100;
			jiao = leftMoney % 100 / 10;
			fen = leftMoney % 10;
			sprintf(displeft ,"剩余金额%d元%d角%d分", yuan, jiao, fen);
			DispStr_CE(0,10,dispMoney, DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,12,displeft,DISP_CENTER);
			DispStr_CE(0,14,"按任意键返回",DISP_CENTER);
			warning_beep();
			delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
			return 0;		//消费成功
		}
		else {
			return -2;		//消费失败
		}
	}
	else {
		return -1;		//没有输入合法数据
	}
}
/***********************************************************************
		module		:	[CPU卡消费]
		function		:	[判断输入金额是否合法（内医大）]
  		return		:	[0:成功	
  						其它:失败]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[CPU_CARD]
		date			:	[11/10/20]
 		author		:	[chen-zhengkai]
************************************************************************/
int	input_money(int line,int maxNum,int minNum,int minValue,int maxValue,
	                char *pPrompt,int *retValue, char* dBuf)
{
	GETSTR_PARAM 	gs;
	int	ret = 0;
	//char	dBuf[40] = {0};
	
	gs.qx = 0;
	gs.sFont = 0;
	gs.alpha = 0;
	gs.nullEnable = 1;
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = '.';
	gs.pStr = dBuf;
	gs.qEvent = 0;

	gs.qy = line;	//提示语句Y坐标
	gs.maxNum = maxNum;	//最大字符数
	gs.minNum = minNum;		//最小字符数
	gs.minValue = minValue;	//最小值
	gs.maxValue = maxValue;	//最大值
	gs.pPrompt = pPrompt;
	gs.retNum = strlen((char*)dBuf);
	gs.qEvent = EXIT_KEY_F1|EXIT_KEY_CANCEL;
	
	ret = GetStr_E(&gs);
	if (ret == 0) {
		*retValue = gs.retValue;
	}
	return ret;
}
/***********************************************************************
		module		:	[CPU卡消费]
		function		:	[字符串转整数（小数部分2位算整数），例， 1.23456 --> 123]
  		return		:	[浮点数]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[CPU_CARD]
		date			:	[11/10/20]
 		author		:	[chen-zhengkai]
************************************************************************/
int myatomon(char* str)
{
	int ret = 0;
	int i = 0;
	int cnt = 0;
	char flag = 0;
	char num = 0;
	//char money[20] = {0};
	while (str[i] != 0) {
		if (str[i] == '.') {
			num = i;
			i++;
			flag = 1;
			continue;
		}
		ret = ret*10 + (str[i]-'0');
		i++;
		if (flag) {
			cnt++;
			if (cnt == 2) {
				break;
			}
		}
	}
	if (flag) {
		if ( str[num+2] == 0) {
				ret = ret*10;
		}
	}
	else {
		ret = ret*100;
	}
	
	//return ret;
	return ret;
}

