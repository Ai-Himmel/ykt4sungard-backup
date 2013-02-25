/****************************************************************************
*
*�ļ�(File):         MyFristPos.c
*
*�޸�(Modify):       2011-10-28 9:03:02
*
*����(Author):       Rain
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
*
*e-mail          :  rain_mcu@163.com
*
*1..ARM ��Ŀ�ļ�(ARM Project):MyFristPos.dsp 
*2..��Ŀ����������ļ�(project binary output  file):MyFristPos.bin
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011-10-28 9:03:02           Rain 
----------------------------------------------------------------------------
****************************************************************************/

/*�ڴ����Ӵ���(TODO: add  code here)*/

#include <API.h>
#include "MyDefine.c"
#include "WiFi/WiFi.h"
#include "WiFi/NaNoWiFiConst.h"
#include "WiFi/WiFiPubFuncs.h"
#include <unistd.h>

extern int Open_WifiModel();
extern  int CPU_test();
extern int Wifi_Connect(char bbit,u16 *Handle,char *HostIpAddr,char *HostPort,char ConnectType);
extern void GetSysParameter();
extern  void SetSysParameter();
extern  void ReadParameter();
extern unsigned long WiFi_MsgDisplay(char *WiFiMsg,
                              u16   WiFiMsgID,
                              u8    WiFiMsgType);
extern void RunPassWord();

static void Sys_main();






 
 u16 G_HandleID;//���Ӿ��
 char G_AddrIP[16]; 	 //����IP
 char RBackInfo[32];	 // �ص�����������Ϣ  ����
 char G_ServerIp[16];	 //������IP
 char G_ServerPort[5];	 //�������˿�
 char G_Ssid[16];		 //·����SSID
 char G_Psk[16];		 //·����PSK
 
 //uchar G_Chid;		   //ͨѶ�ŵ�
 char G_GateWay[16];	 //����
 char G_NetMask[16];	 //��������
 char G_Hostport[5];	 //�����˿ں�
 uint G_BackColor;		 //������ɫ
 uint G_FontColor;		 //ǰ����ɫ
 uint G_ThemeColor; 	 //������ɫ
 uint G_AutoSleep;		 //�Զ��ػ�ʱ��
 uint G_AutoElClose;	 //�����Զ��ر�ʱ��
 char G_KeySound;		 //�������Ƿ���
 
 uchar G_Changle=0; 	 //�ŵ�ѡ��
 uchar G_TransRate=13;	 //ͨѶ����
 
 uchar G_AddrIPLen=14;	 //ip��ַ����
 uchar G_SsidLen=7; 	 //SSID����
 uchar G_ServerIpLen=13; //������IP����
 uchar G_NetMaskLen=13;  //�������볤��
 uchar G_GateWayLen=12;  //���س���
 uchar G_PskLen=12; 	 //·�������볤��
 uchar G_ServerPortLen=4;//�������˿ڳ���
 uchar G_LocalSite;
 
 uchar G_PassWord[16];	   //��������
 uchar G_PassWordStatus;
 uchar G_PassWordLen;
 uchar G_WifiPowerTime;

 
 uchar Receive_Ip[16];//����ԭIP��˿�
 uchar Receive_Port[5];
 uchar ReceiveMaincode;//վ��
 u16 SerialReceiveLen;
 uchar Check_CardOk;
 

 //union	 sDatasUnion  xdata SerialUnion;
 //uchar	 SerialReceiveLen;
 
 
 uchar UID[4];

 

 int main(void)
 {
 	 char main_str[10];
	 Disp_Init(DISP_INIT_ON);//��ʾ��ʼ�� ������ʾ
	 if(3000 > SYS_Read_Vol())
	 {
		 DispStr_E(0,16,"��������",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		 Sys_Delay_MS(1000);
		 Sys_Power_Sleep(2);
	 }
	 ReadParameter();//������ʼ��
	 Disp_Set_Color(SET_BACK_COLOR,G_BackColor);//�������� ǳ�� 
	 Disp_Set_Color(SET_CLEAR_COLOR,G_BackColor);//G_BackColor
	 Disp_Set_Color(SET_FONT_COLOR,G_FontColor);//ǰ����ɫ
	 Disp_Set_Color(SET_SELECT_COLOR,G_ThemeColor);//������ɫ
	 Sys_Auto_Poweroff_Set((ushort)G_AutoSleep);//30���Զ��ػ�
	 EL_Set_Timeout((ushort)G_AutoElClose);//������Զ��ر�ʱ��7�� 
	 //WatchDog_Set(25);	//���ÿ��Ź� 
	 if(G_KeySound)
	 {
		 KEY_Init(KEY_AUTO_EL_ON|KEY_BEEP_KEY);//������ʼ��
	 }
	 else
	 {
		 KEY_Init(KEY_AUTO_EL_ON);//������ʼ��
	 }
	 //WriteParameter(E_PassWordAddr,sss,3);
	 //WriteParameter(E_PassWordLenAddr,&ss,1);
	 if(KEY_Read()==KEY_F2)
	 {
		sprintf(main_str,"%s",G_PassWord);
		DispStr_CE(0,4,main_str,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		delay_and_wait_key (1,EXIT_KEY_F1,120);
	 }
	 if(G_PassWordStatus)
	 {
		 RunPassWord();
	 }
	 Disp_Icon_Battery_Time_Set(1,ICON_AT_TAIL);
	 CWiFi_SetMSGCallBack((WiFiMSG_CALLBACK)WiFi_MsgDisplay);//���ûص�����
	 Open_WifiModel();
	 Sys_main();
	 return 1;
 }
 

 static void Sys_main()
 {
	 BROWINFO main_menu;
	 char main_str[]=" 1.ϵͳ����    "
					 " 2.ϵͳ��ѯ    "
					 " 3.CPU������   ";
					 
	 
	 int select;
	 main_menu.iStr=main_str;//����ַ���
	 main_menu.lPtr = 0;//��ʼ��ʾ��
	 main_menu.cPtr = 0;//��ʼѡ����
	 while(1)
	 {
		
		DispStr_CE(0,1,"ϵͳ���˵�",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		main_menu.mInt=3;//��ʾ������
		main_menu.lineMax=15;//ÿ����ʾ����ַ��� 
		main_menu.startLine=3;//��ʼ�� 
		main_menu.dispLines=3;//
		main_menu.sFont=0;	//0 -������
		main_menu.numEnable=1;//�Ƿ�������̷���� 1-����
		main_menu.qEvent=(EXIT_KEY_F1);
		main_menu.autoexit =120;
		select=EXT_Brow_Select(&main_menu);
		switch(select)
		{
			 case 0:
				 SetSysParameter();//����ϵͳ����
				 break;
			 case 1:
				 GetSysParameter();//��ѯϵͳ����
				 break;
			 case 2:
				 CPU_test();
				 break;
			 default:
				 //return;
				 break;
		}
	 }
	 return ;
					 
 }
 
 


