/****************************************************************************
*
*文件(File):         MyFristPos.c
*
*修改(Modify):       2011-10-28 9:03:02
*
*作者(Author):       Rain
*
*编绎(Compile):      智能平台(Smart Platform)
*
*描述(Description):
*
*e-mail          :  rain_mcu@163.com
*
*1..ARM 项目文件(ARM Project):MyFristPos.dsp 
*2..项目二进制输出文件(project binary output  file):MyFristPos.bin
*
----------------------------------------------------------------------------
|
| Version | Datetime             |   Author    | Description
| --------+----------------------+-------------+----------------------------
|
| V1.00  2011-10-28 9:03:02           Rain 
----------------------------------------------------------------------------
****************************************************************************/

/*在此增加代码(TODO: add  code here)*/

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






 
 u16 G_HandleID;//连接句柄
 char G_AddrIP[16]; 	 //本机IP
 char RBackInfo[32];	 // 回调函数保存信息  无用
 char G_ServerIp[16];	 //服务器IP
 char G_ServerPort[5];	 //服务器端口
 char G_Ssid[16];		 //路由器SSID
 char G_Psk[16];		 //路由器PSK
 
 //uchar G_Chid;		   //通讯信道
 char G_GateWay[16];	 //网关
 char G_NetMask[16];	 //子网掩码
 char G_Hostport[5];	 //本机端口号
 uint G_BackColor;		 //背景颜色
 uint G_FontColor;		 //前景颜色
 uint G_ThemeColor; 	 //主题颜色
 uint G_AutoSleep;		 //自动关机时间
 uint G_AutoElClose;	 //背光自动关闭时间
 char G_KeySound;		 //按键音是否开启
 
 uchar G_Changle=0; 	 //信道选择
 uchar G_TransRate=13;	 //通讯速率
 
 uchar G_AddrIPLen=14;	 //ip地址长度
 uchar G_SsidLen=7; 	 //SSID长度
 uchar G_ServerIpLen=13; //服务器IP长度
 uchar G_NetMaskLen=13;  //子网掩码长度
 uchar G_GateWayLen=12;  //网关长度
 uchar G_PskLen=12; 	 //路由器密码长度
 uchar G_ServerPortLen=4;//服务器端口长度
 uchar G_LocalSite;
 
 uchar G_PassWord[16];	   //开机密码
 uchar G_PassWordStatus;
 uchar G_PassWordLen;
 uchar G_WifiPowerTime;

 
 uchar Receive_Ip[16];//接收原IP与端口
 uchar Receive_Port[5];
 uchar ReceiveMaincode;//站点
 u16 SerialReceiveLen;
 uchar Check_CardOk;
 

 //union	 sDatasUnion  xdata SerialUnion;
 //uchar	 SerialReceiveLen;
 
 
 uchar UID[4];

 

 int main(void)
 {
 	 char main_str[10];
	 Disp_Init(DISP_INIT_ON);//显示初始化 ，打开显示
	 if(3000 > SYS_Read_Vol())
	 {
		 DispStr_E(0,16,"电量过低",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		 Sys_Delay_MS(1000);
		 Sys_Power_Sleep(2);
	 }
	 ReadParameter();//参数初始化
	 Disp_Set_Color(SET_BACK_COLOR,G_BackColor);//背景设置 浅蓝 
	 Disp_Set_Color(SET_CLEAR_COLOR,G_BackColor);//G_BackColor
	 Disp_Set_Color(SET_FONT_COLOR,G_FontColor);//前景颜色
	 Disp_Set_Color(SET_SELECT_COLOR,G_ThemeColor);//主题颜色
	 Sys_Auto_Poweroff_Set((ushort)G_AutoSleep);//30秒自动关机
	 EL_Set_Timeout((ushort)G_AutoElClose);//背光灯自动关闭时间7秒 
	 //WatchDog_Set(25);	//设置看门狗 
	 if(G_KeySound)
	 {
		 KEY_Init(KEY_AUTO_EL_ON|KEY_BEEP_KEY);//按键初始化
	 }
	 else
	 {
		 KEY_Init(KEY_AUTO_EL_ON);//按键初始化
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
	 CWiFi_SetMSGCallBack((WiFiMSG_CALLBACK)WiFi_MsgDisplay);//设置回调函数
	 Open_WifiModel();
	 Sys_main();
	 return 1;
 }
 

 static void Sys_main()
 {
	 BROWINFO main_menu;
	 char main_str[]=" 1.系统设置    "
					 " 2.系统查询    "
					 " 3.CPU卡测试   ";
					 
	 
	 int select;
	 main_menu.iStr=main_str;//浏览字符串
	 main_menu.lPtr = 0;//起始显示行
	 main_menu.cPtr = 0;//初始选择项
	 while(1)
	 {
		
		DispStr_CE(0,1,"系统主菜单",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		main_menu.mInt=3;//显示总行数
		main_menu.lineMax=15;//每行显示最大字符数 
		main_menu.startLine=3;//起始行 
		main_menu.dispLines=3;//
		main_menu.sFont=0;	//0 -大字体
		main_menu.numEnable=1;//是否允许键盘方向键 1-允许
		main_menu.qEvent=(EXIT_KEY_F1);
		main_menu.autoexit =120;
		select=EXT_Brow_Select(&main_menu);
		switch(select)
		{
			 case 0:
				 SetSysParameter();//设置系统参数
				 break;
			 case 1:
				 GetSysParameter();//查询系统参数
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
 
 


