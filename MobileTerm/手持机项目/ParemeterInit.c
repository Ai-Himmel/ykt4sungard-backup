/****************************************************************************
*
*文件(File):         ParemeterInit.c
*
*修改(Modify):       2011-10-26 15:31:51
*
*作者(Author):       Rain
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
*
*e-mail          :  rain_mcu@163.com
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011-10-28 9:02:51           Rain 
----------------------------------------------------------------------------
****************************************************************************/

#include <API.h>
#include "MyDefine.c" 
#include "ExternParameter.h" 


void ReadParameter()
{
	//char ReadBuf[16];
	char i;
	uchar UreadBuf[16];
	uint TempBuf;
	char temp_buf[16];
	EEPROM_Init(EEPROM_ON);//open eeprom
//                   长度读取
//                IP

	EEPROM_Read_Byte(E_IpLenAddr,&G_AddrIPLen);//
	EEPROM_Read_Byte(E_ServerIpLenAddr,&G_ServerIpLen);
	EEPROM_Read_Byte(E_PskLenAddr,&G_PskLen);
	EEPROM_Read_Byte(E_NetMaskLenAddr,&G_NetMaskLen);
	EEPROM_Read_Byte(E_GateWayLenAddr,&G_GateWayLen);
	EEPROM_Read_Byte(E_SsidLenAddr,&G_SsidLen);
	EEPROM_Read_Byte(E_ServerPortLenAddr,&G_ServerPortLen);
	EEPROM_Read_Byte(E_PassWordLenAddr,&G_PassWordLen);
	EEPROM_Read_Byte(E_PassWordStatusAddr,&G_PassWordStatus);//开机密码状态
	EEPROM_Read_Byte(E_LocalSiteAddr,&G_LocalSite);//站点号
	EEPROM_Read_Byte(E_WifiPowerModleAddr,&G_WifiPowerTime);
	memset(temp_buf,0x00,16);
	//sprintf(temp_buf,"%d",G_PassWordLen);
	//DispStr_CE(0,6,temp_buf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
/***********************************************/
//				IP
/***********************************************/
	for(i=0;i<G_AddrIPLen;i++)
	{
		EEPROM_Read_Byte(E_IpAddr+i,UreadBuf+i);//
	}
	memcpy(G_AddrIP,UreadBuf,G_AddrIPLen);

/***********************************************/
//                         SSID
	for(i=0;i<G_SsidLen;i++)
	{
		EEPROM_Read_Byte(E_SsidAddr+i,UreadBuf+i);
	//	if(temp=='!')
	//	{
	//		break;
	//	}
	//	*(G_Ssid+i)=temp;
	}
	memcpy(G_Ssid,UreadBuf,G_SsidLen);
	//DispStr_CE(0,4,G_Ssid,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);


/**********************************************/
//				PSK
	for(i=0;i<G_PskLen;i++)
	{
		EEPROM_Read_Byte(E_PskAddr+i,UreadBuf+i);
	}
	memcpy(G_Psk,UreadBuf,G_PskLen);
	//DispStr_CE(0,4,G_Psk,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
/*********************************************/
//                     Chid
	EEPROM_Read_Byte(E_ChidAddr,UreadBuf);
	G_Changle=(uchar)UreadBuf[0];

/********************************************/
//                      TransRate
	EEPROM_Read_Byte(E_TransRateAddr,UreadBuf);
	G_TransRate=(uchar)UreadBuf[0];
/********************************************/
//                      Gateway
	for(i=0;i<G_GateWayLen;i++)
	{
		EEPROM_Read_Byte(E_GateWayAddr+i,UreadBuf+i);
	}
	memcpy(G_GateWay,UreadBuf,G_GateWayLen);
	//DispStr_CE(0,4,G_GateWay,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
/********************************************/
//                  NetMask
	for(i=0;i<G_NetMaskLen;i++)
	{
		EEPROM_Read_Byte(E_NetMaskAddr+i,UreadBuf+i);
	}
	memcpy(G_NetMask,UreadBuf,G_NetMaskLen);
	//DispStr_CE(0,4,G_NetMask,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
/*******************************************/
//                 BackColor
	memset(UreadBuf,0x00,16);
	EEPROM_Read_Byte(E_BackColorAddr,UreadBuf);	
	EEPROM_Read_Byte(E_BackColorAddr+1,UreadBuf+1);
	TempBuf=(uint)UreadBuf[0];
	TempBuf=TempBuf<<8;
	G_BackColor=TempBuf+(uint)UreadBuf[1];
	//memset(temp_buf,0x00,16);
/******************************************/
//                FontColor
	memset(UreadBuf,0x00,16);
	EEPROM_Read_Byte(E_FontColorAddr,UreadBuf);	
	EEPROM_Read_Byte(E_FontColorAddr+1,UreadBuf+1);
	TempBuf=(uint)UreadBuf[0];
	TempBuf=TempBuf<<8;
	G_FontColor=TempBuf+(uint)UreadBuf[1];
/*******************************************/
//                ThemeColor
	memset(UreadBuf,0x00,16);
	EEPROM_Read_Byte(E_ThemeColorAddr,UreadBuf);	
	EEPROM_Read_Byte(E_ThemeColorAddr+1,UreadBuf+1);
	TempBuf=(uint)UreadBuf[0];
	TempBuf=TempBuf<<8;
	G_ThemeColor=TempBuf+(uint)UreadBuf[1];
/******************************************/
//              AutoSleep
	EEPROM_Read_Byte(E_AutoSleepAddr,UreadBuf);	
	EEPROM_Read_Byte(E_AutoSleepAddr+1,UreadBuf+1);
	TempBuf=(uint)UreadBuf[0];
	TempBuf=TempBuf<<8;
	G_AutoSleep=TempBuf+(uint)UreadBuf[1];
	
/******************************************/
//              AutoElClose
	EEPROM_Read_Byte(E_AutoElCloseAddr,UreadBuf);	
	//EEPROM_Read_Byte(E_AutoElCloseAddr+1,UreadBuf+1);
	G_AutoElClose=(uint)UreadBuf[0];
/******************************************/
//			Keysound
	EEPROM_Read_Byte(E_KeySondAddr,UreadBuf);	
	G_KeySound=UreadBuf[0];

//******************************************/
//                ServerIP
	for(i=0;i<G_ServerIpLen;i++)
	{
		EEPROM_Read_Byte(E_ServerIpAddr+i,UreadBuf+i);
	}
	memcpy(G_ServerIp,UreadBuf,G_ServerIpLen);
//	DispStr_CE(0,4,G_ServerIp,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
//******************************************/
//               ServerPort
	for(i=0;i<G_ServerPortLen;i++)
	{
		EEPROM_Read_Byte(E_ServerPortAddr+i,UreadBuf+i);
	}
	
	memcpy(G_ServerPort,UreadBuf,G_ServerPortLen);
	//DispStr_CE(0,4,G_ServerPort,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
//*****************************************/
//                    password
	for(i=0;i<G_PassWordLen;i++)
	{
		EEPROM_Read_Byte(E_PassWordAddr+i,UreadBuf+i);
	}
	memcpy(G_PassWord,UreadBuf,G_PassWordLen);
	memset(temp_buf,0x00,16);
	//sprintf(temp_buf,"%s",G_PassWord);
	//DispStr_CE(0,4,temp_buf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	//delay_and_wait_key (1,EXIT_KEY_F1,120);
/******************************************/
//	          PassWordStatus
//	EEPROM_Read_Byte(E_PassWordStatusAddr,UreadBuf);
	//G_PassWordStatus=UreadBuf[0];
/******************************************/

	EEPROM_Init(EEPROM_OFF);

}

int WriteParameter(ushort Addr,uchar *Wrdate,char len)
{
	char i;
	int ret=0;
	EEPROM_Init(EEPROM_ON);
	for(i=0;i<len;i++)
	{
		ret=EEPROM_Write_Byte(Addr+i,*(Wrdate+i));
		if(ret)
		{
			EEPROM_Init(EEPROM_OFF);
			return ret;
		}
	}
	EEPROM_Init(EEPROM_OFF);
	return ret;
	
}





