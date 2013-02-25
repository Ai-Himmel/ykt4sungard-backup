/****************************************************************************
*
*文件(File):         CPUCard.c
*
*修改(Modify):       2011-10-28 9:06:24
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
| V1.00  2011-10-28 9:06:24           Rain 
----------------------------------------------------------------------------
****************************************************************************/
#include <API.h>
#include "MyDefine.c" 
#include "ExternParameter.h" 
#include "MyDefine.c" 


#include "WiFi/WiFi.h"

extern void UdpSendDate();
extern void WaringFdivBeep(uchar f_div,uchar Beep_count);
extern int Wifi_Connect(char bbit,u16 *Handle,char *HostIpAddr,char *HostPort,char ConnectType);
extern void WaringBeep(uchar Beep_count);
extern int Wifi_GetSocketStatus(char bbit,uint HandleID);//查看套接字连接状态;

 int CPU_test()
{
	char retchar;
	unsigned char ATQ[4];
	unsigned char sno[12];
	uchar count=0;
	char read_ok=0;
	int ret ;
	uchar Disp_count=0;
	uint Disp_y=4;
	char 	tmpbuf[16];
	unsigned char 	sak; 
	RCX_Init(CARD_TYPE_14443A);
	RCX_Adjust_RxGain(0x00);  //调整增益
	memset(ATQ,0x00,4);
	DispStr_CE(0,Disp_y,"请刷卡!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	while(1)
	{
		retchar = CardTypeARequest(PICC_REQALL,ATQ);
		if ( retchar==RCX_OK )
		{
			read_ok = 1;
			break;
		}
		if(KEY_Read()==KEY_F1)
		{
			return -1;
		}	
		Disp_count++;
		if(Disp_count==50)
		{
			Disp_count=0;
			Disp_y+=2;
			if(Disp_y>30)
				Disp_y=4;
			DispStr_CE(0,Disp_y,"请刷卡!",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		}
		
	}
	retchar = CardTypeAAnticoll(PICC_ANTICOLL1,sno);	
	retchar |= CardTypeASelect(PICC_ANTICOLL1,sno,&sak);
	if(retchar!=RCX_OK)
	{
		//sprintf(tmpbuf,"Sel 2 Err:%d",retchar);
		DispStr_CE(0,4,"读取错误!",DISP_CENTER|DISP_CLRSCR);
		WaringFdivBeep(6,3);
		ret = -4;
		goto end;
	}
	if(sak&0x04)
	{
		retchar = CardTypeAAnticoll(PICC_ANTICOLL1,sno+4);	
		retchar |= CardTypeASelect(PICC_ANTICOLL1,sno+4,&sak);
		count=1;
		if(retchar!=RCX_OK)
		{
			//sprintf(tmpbuf,"读取错误!",retchar);
			DispStr_CE(0,4,"读取错误!",DISP_CENTER|DISP_CLRSCR);
			WaringFdivBeep(6,3);
			ret = -4;
			goto end;
		}
	}
	if(sak&0x04)
	{
		retchar = CardTypeAAnticoll(PICC_ANTICOLL1,sno+8);	
		retchar |= CardTypeASelect(PICC_ANTICOLL1,sno+8,&sak);
		count=2;
		if(retchar!=RCX_OK)
		{
			//sprintf(tmpbuf,"读取错误!",retchar);
			DispStr_CE(0,4,"读取错误!",DISP_CENTER|DISP_CLRSCR);
			WaringFdivBeep(6,3);
			ret = -4;
			goto end;
		}
	}
	if((sak&0x24)==0)
	{
		DispStr_CE(0,6,"不支持此卡!",DISP_CENTER|DISP_CLRSCR);
		WaringFdivBeep(6,3);
		ret = -6;
		goto end;
	}
	memcpy(UID,sno+4*count,4);
	memset(tmpbuf,0x00,16);
	sprintf(tmpbuf,"%X %X %X %X",UID[0],UID[1],UID[2],UID[3]);
	DispStr_CE(0,8,tmpbuf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	WaringFdivBeep(6,1);
	//delay_and_wait_key(1,EXIT_KEY_ALL,0);
	UdpSendDate();
	ret = 0;
	RCX_Close();
	return ret;	
end:	
	RCX_Close();
	delay_and_wait_key(0,EXIT_KEY_ALL,0);
	return ret;	
}



