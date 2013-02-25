/****************************************************************************
*
*文件(File):         MyDefine.c
*
*修改(Modify):       2011-10-28 9:04:26
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
| V1.00  2011-10-28 9:04:26           Rain 
----------------------------------------------------------------------------
****************************************************************************/


//#define OPEN_WARNING_BEEP 

#define uchar unsigned char 
#define uint unsigned int 
#define ushort unsigned short

#define E_IpAddr                 0      //ip地址的起始地址共16字节
#define E_SsidAddr               16     //预留16字节 
#define E_PskAddr                32     //预留16字节
#define E_ChidAddr               48     //通信信道 1字节
#define E_GateWayAddr            49     //网关 16字节
#define E_NetMaskAddr            65     //子网掩码16字节
#define E_PortAddr               81     //端口号5字节  int型
#define E_TransRateAddr          86     //通讯速率1字节
#define E_BackColorAddr          87     //背景颜色2字节
#define E_FontColorAddr          89     //前景颜色2字节
#define E_ThemeColorAddr         142       //2字节
#define E_LocalSiteAddr          144    //本机站点1字节
#define E_AutoSleepAddr          150     //自动关机时间2字节
#define E_AutoElCloseAddr        92     //背光自动关闭时间1字节
#define E_KeySondAddr            93     //按键声音1字节

#define E_ServerIpAddr           94     //服务器IP16字节
#define E_ServerPortAddr         110    //服务器端口5字节

#define E_SsidLenAddr            115    //SSID长度1字节
#define E_PskLenAddr             116    //PSK长度 1字节
#define E_IpLenAddr              117    //IP长度 1字节
//#define E_PortLenAddr                    118   
#define E_ServerIpLenAddr        119    //服务器IP地址
#define E_ServerPortLenAddr      120    //服务器端口长度地址
#define E_GateWayLenAddr         121	   //网关长度地址
#define E_NetMaskLenAddr         123    //子网掩码长度地址
#define E_PassWordAddr           124    //开机密码地址 16字节
#define E_PassWordLenAddr        140    //开机密码长度地址1字节
#define E_PassWordStatusAddr     141    //开机密码状态
#define E_WifiPowerModleAddr     145    //wifi掉电休眠时间



#define DISP_STATUS_INF           0     //是否显示设置信息
#define DISP_OK_DELAY_TIME        2		//设置成功显示持续时间
#define DISP_ESC_DELAY_TIME       1		//取消设置显示持续时间
#define DISP_CHECK_DELAY_TIME     4

#define STX                       2		//Start 
#define ETX                       3		//End  

#define SendDateLen               4
#ifdef  OPEN_WARNING_BEEP 
#define OK_WARNING_BEEP           1
#define ERR_WARNING_BEEP          3
#else
#define OK_WARNING_BEEP           0
#define ERR_WARNING_BEEP          0
#endif
#define RECEIVE_DATE_ERR          -1
#define CRC_CHECK_ERR             -2
#define UID_CHECK_ERR             -3
#define SITE_CHECK_ERR            -4
#define CARD_CHECK_ERR            -5
#define READ_NET_ERR              -6
#define RECEIVE_DATE_OK            0

#define CZ_COMMAND_WORD_H          0x02   //命令字高地址
#define CZ_COMMAND_WORD_L          0x12   //命令字低地址

//extern u16 G_HandleID;//连接句柄
  /*
struct	sDatasStruct//通讯数据格式
{
	uchar	AddrH;//地址高
	uchar	AddrL;//地址低
	uchar	DatasLen;//数据长度
	uchar	Datas[1021];//数据包
};
union	sDatasUnion
{
	uchar	S_DatasBuffer[1024];
	struct	sDatasStruct	S_DatasStruct;
};

      */




