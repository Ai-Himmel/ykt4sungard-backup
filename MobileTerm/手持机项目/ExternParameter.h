/****************************************************************************
*
*文件(File):         ExternParameter.h
*
*修改(Modify):       2011-10-28 9:05:16
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
| V1.00  2011-10-28 9:05:16          Rain 
----------------------------------------------------------------------------
****************************************************************************/
#include <API.h>
 #include "WiFi/WiFi.h"


 extern u16 G_HandleID;//连接句柄
 extern char G_AddrIP[16]; 	 //本机IP
 extern char RBackInfo[32];	 // 回调函数保存信息  无用
 extern char G_ServerIp[16];	 //服务器IP
 extern char G_ServerPort[5];	 //服务器端口
 extern char G_Ssid[16];		 //路由器SSID
 extern char G_Psk[16];		 //路由器PSK
 
 //uchar G_Chid;		   //通讯信道
 extern char G_GateWay[16];	 //网关
 extern char G_NetMask[16];	 //子网掩码
 extern char G_Hostport[5];	 //本机端口号
 extern uint G_BackColor;		 //背景颜色
 extern uint G_FontColor;		 //前景颜色
 extern uint G_ThemeColor; 	 //主题颜色
 extern uint G_AutoSleep;		 //自动关机时间
 extern uint G_AutoElClose;	 //背光自动关闭时间
 extern char G_KeySound;		 //按键音是否开启
 
 extern uchar G_Changle; 	 //信道选择
 extern uchar G_TransRate;	 //通讯速率
 
 extern uchar G_AddrIPLen;	 //ip地址长度
 extern uchar G_SsidLen; 	 //SSID长度
 extern uchar G_ServerIpLen; //服务器IP长度
 extern uchar G_NetMaskLen;  //子网掩码长度
 extern uchar G_GateWayLen;  //网关长度
 extern uchar G_PskLen; 	 //路由器密码长度
 extern uchar G_ServerPortLen;//服务器端口长度
 extern uchar G_LocalSite;
 
 extern uchar G_PassWord[16];	   //开机密码
 extern uchar G_PassWordStatus;
 extern uchar G_PassWordLen;
 extern uchar G_WifiPowerTime;

 
 extern uchar Receive_Ip[16];//接收原IP与端口
 extern uchar Receive_Port[5];
 extern uchar ReceiveMaincode;//站点
 extern u16 SerialReceiveLen;
 extern uchar Check_CardOk;
 
 
 //union	 sDatasUnion  xdata SerialUnion;
 //uchar	 SerialReceiveLen;
 
 
 extern uchar UID[4];
 

