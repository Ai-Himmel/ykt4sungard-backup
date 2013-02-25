/****************************************************************************
*
*文件(File):         wifi_con.c
*
*修改(Modify):       2011/7/25 15:39:59
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
| V1.00  2011/7/25 15:39:59           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"

static char  g_RBackInfo[32];       //..回调函数显示 
u16 g_pHandle[1] = {0};	//wifi连接句柄

char wifi_init();	//WIFI初始化
void wifinet_set();	//网络设置子菜单
unsigned long WiFi_MsgDisplay(char *WiFiMsg, u16 WiFiMsgID, u8 WiFiMsgType);	//回调函数（显示
void InputData(char *pShowMsg, char *pRtnInfo, char alphaInput);		//..获得键盘输入数据
void setIP();		//设置IP
void setNetMask();	//设置子网掩码
void setGateway();	//设置网关
void setServerIP();	//设置服务器IP
void setServerPort();	//设置服务器端口
void setServerSSID();	//设置SSID
void setPassword();	//设置密码
void clearPSK();		//清空安全设置
void connectWifi();	//连接网络
void disConnect();	//断开连接
void resetWifi();	//重启模块
void sendRecords();	//发送数据（菜单调用）
//char sendRecords(char* data_buffer, int bufferMax)	//发送数据
/***********************************************************************
		module		:	[WIFI]
		function		:	[wifi上传菜单]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void wifi_upload_menu()
{
	int select = -1;
	//int conStatus = 0;		//连接状态，0：连接正常
	char db_menu_str[] =	"1. 启动连接"
							"2. 上传数据"
							"3. 网络设置"
							"4. 断开连接"
							"5. 重启模块";

	BROWINFO	info;
	info.iStr = db_menu_str;		//浏览内容指针
	info.lPtr = 0;					//显示内容iStr的起始显示行
	info.cPtr = 0;					//当前选择行

	while (1) {
		//以下BROWINFO结构成员变量必须参与循环，有可能会被EXT_Brow_Select函数改变
//		 conStatus = CWiFi_GetRepStatus(g_pHandle[0]);
//		 if (!conStatus) {
//		 	strncpy(db_menu_str, "1. 断开连接（已连接）", 21);
//		}
//		else {
//			strncpy(db_menu_str, "1. 启动连接（未连接）", 21);
//		}
		info.startLine = 2;				//在LCD上的显示起始行
		info.dispLines = 5;				//在LCD上的显示行数
		info.mInt = 5;					//显示内容的总行数
		info.lineMax = 11;				//每行最大字符数
		info.sFont = 0;					//7x9大字体显示
		info.numEnable = 0;				//是否允许数字键代替方向控制
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //可导致函数退出的事件标志
		info.autoexit = 1200;			//自动退出的时间
		//菜单
		Disp_Clear();
		DispStr_CE(0, 0, "wifi传输菜单", DISP_CENTER);
		select = EXT_Brow_Select(&info);

		switch (select) {
			case 0:		//启动连接，断开连接
				connectWifi();	//启动连接
				break;
			case 1:		//上传数据
				sendRecords();
				break;
			case 2:		//网络设置
				wifinet_set();
				break;
			case 3:		//断开连接
				disConnect();
				break;
			case 4:		//重启模块
				resetWifi();
				break;
			default:	//降低CPU占用率，降低能耗
				if (info.qEvent == EXIT_KEY_F1  || EXIT_AUTO_QUIT 
                                || EXIT_KEY_POWER || EXIT_KEY_CANCEL) { //返回上级菜单 
					return;
				}
				Sys_Power_Sleep(3);
				break;
		}
	}
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[断开连接]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void disConnect()
{
	CWiFi_Disconnect(g_pHandle[0]);
	DispStr_CE(0,6,"连接已断开",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键返回",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[重启模块]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void resetWifi()
{
	CWiFi_CloseMould();
	CWiFi_OpenMould();
	DispStr_CE(0,6,"模块已重启",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键返回",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[wifi初始化（开机调用）]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
void wifiInit_open()
{
	char ret = 0;	//wifi初始化结果
	char errBuf[25] = {0};	//错误信息
	char retBuf[] = "按任意键返回";	//返回信息
	
	DispStr_CE(0,6,"WIFI初始化中",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"请耐心等待...",DISP_CENTER);
	ret = wifi_init();
	switch ((int)ret) {
		case -1:
			strcpy(errBuf, "模块初始化失败");
			break;
		case -2:
			strcpy(errBuf, "模块连接失败");
			break;
		case -3:
			strcpy(errBuf, "电源设置失败");
			break;
		case -4:
			strcpy(errBuf, "信道设置失败");
			break;
		case -5:
			strcpy(errBuf, "通信速率设置失败");
			break;
	}
	if (ret) {
		DispStr_CE(0,6,errBuf,DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,8,retBuf,DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[wifi初始化]
  		return		:	[0:成功
  						-1:模块初始化失败
  						-2:模块连接失败
  						-3:电源设置失败
  						-4:信道设置失败
  						-5:通信速率设置失败
  		]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/25]
 		author		:	[chen-zhengkai]
************************************************************************/
char wifi_init()
{
	char ret = 0;
	short MinVol          = 0;
	if(MinVol > SYS_Read_Vol()) {
		DispStr_E(0,6,"电量过低",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
		Sys_Delay_MS(1000);
		Sys_Power_Sleep(2);
	}
	CWiFi_SetMSGCallBack((WiFiMSG_CALLBACK)WiFi_MsgDisplay);	//回调函数必须有，否则蓝屏
	if (CWiFi_InitModule(0,0) != NaNo_OK) {		//初始化模块
		ret = -1;
	}
	if (CWiFi_ConnState(0) != NaNo_OK) {	//模块连接状态
		ret = -2;
	}
	if (CWiFi_SetPowerMode(10,2,120) != NaNo_OK) {	//设置电源
		ret = -3;
	}
	if ( CWiFi_SetWiFiChanle(0) != NaNo_OK) {		//信道设置失败
		ret = -4;
	}
	if (CWiFi_SetWiFiTransRate(0) != NaNo_OK) {	//设置通信速率
		ret = -5;
	}
	return ret;
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[回调(显示)函数]
  		return		:	[]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
unsigned long WiFi_MsgDisplay(char *WiFiMsg,
                              u16   WiFiMsgID,
                              u8    WiFiMsgType)
{
    memset(g_RBackInfo,0x00,32);
    //sprintf(&RBackInfo[0], " MID:%d,TID:%d,%s\n", WiFiMsgID,WiFiMsgType,WiFiMsg);
    sprintf(&g_RBackInfo[0], "%s",WiFiMsg);
    return 0;
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[WIFI网络设置子菜单]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void wifinet_set()
{
	int select = -1;
	char db_menu_str[] =		"1. 设置本机IP  "
							"2. 设置子网掩码"
							"3. 设置网关    "
							"4. 设置服务器IP"
							"5. 设置端口    "
							"6. 设置ssid    "
							"7. 设置密码    "
							"8. 清空安全设置";

//	if ( adminPassword(0) ) {
//		return;
//	}
	BROWINFO	info;
	info.iStr = db_menu_str;		//浏览内容指针
	info.lPtr = 0;					//显示内容iStr的起始显示行
	info.cPtr = 0;					//当前选择行

	while (1) {
		//以下BROWINFO结构成员变量必须参与循环，有可能会被EXT_Brow_Select函数改变
		info.startLine = 0;				//在LCD上的显示起始行
		info.dispLines = 7;				//在LCD上的显示行数
		info.mInt = 8;					//显示内容的总行数
		info.lineMax = 15;				//每行最大字符数
		info.sFont = 0;					//7x9大字体显示
		info.numEnable = 0;				//是否允许数字键代替方向控制
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //可导致函数退出的事件标志
		info.autoexit = 1200;			//自动退出的时间
		//菜单
		Disp_Clear();
		select = EXT_Brow_Select(&info);

		switch (select) {
			case 0:		//设置本机IP
				setIP();
				break;
			case 1:		//设置子网掩码
				setNetMask();
				break;
			case 2:		//设置网关
				setGateway();
				break;
			case 3:		//设置服务器IP
				setServerIP();
				break;
			case 4:		//设置端口
				setServerPort();
				break;
			case 5:		//设置SSID
				setServerSSID();
				break;
			case 6:		//设置密码
				setPassword();
				break;
			case 7:		//清空安全设置
				clearPSK();
				break;
			default:	//降低CPU占用率，降低能耗
				if (info.qEvent == EXIT_KEY_F1  || EXIT_AUTO_QUIT 
                                || EXIT_KEY_POWER || EXIT_KEY_CANCEL) { //返回上级菜单 
					return;
				}
				Sys_Power_Sleep(3);
				break;
		}
	}
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[设置IP]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setIP()
{
	char plIPAddr[16];
	char retStr[16] = {0};
	memset(plIPAddr,0x00,16);
	CWiFi_GetLocalAddress(plIPAddr);	
	InputData((char*)"本机IP",plIPAddr, 0);
	if (NaNo_OK == CWiFi_SetLocalAddress(plIPAddr)) {
		strcpy(retStr, "设置成功");
	}
	else {
		strcpy(retStr, "设置失败");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 ); 
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[设置子网掩码]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setNetMask()
{
	char netMask[16];
	char retStr[16] = {0};
	memset(netMask,0x00,16);
	CWiFi_GetLocalNetMask(netMask);	
	InputData((char*)"子网掩码",netMask, 0);
	if (NaNo_OK == CWiFi_SetLocalNetMask(netMask)) {
		strcpy(retStr, "设置成功");
	}
	else {
		strcpy(retStr, "设置失败");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 ); 
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[设置网关]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setGateway()
{
	char geteWay[16];
	char retStr[16] = {0};
	memset(geteWay,0x00,16);
	CWiFi_GetGatewayAddress(geteWay);	
	InputData((char*)"网关",geteWay, 0);
	if (NaNo_OK == CWiFi_SetGatewayAddress(geteWay)) {
		strcpy(retStr, "设置成功");
	}
	else {
		strcpy(retStr, "设置失败");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 ); 
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[设置连接服务器IP]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void setServerIP()
{
	char retStr[20] = {0};
	char ret = -2;	//设置失败
	unsigned char serverIPAdd[25] = {0};	//服务器IP

	memset(serverIPAdd,0x00,16);

	if (eeprom_read(serverIPAdd, 16, EEPROM_OFFSET_SERVERIPADD)) {
		ret = -1;	//读取失败
	}
	if (ret != -1) {
		InputData((char*)"服务器IP",serverIPAdd, 0);
		if (serverIPAdd[0] != 0) {	//判断字符串不为空
			if (eeprom_write(serverIPAdd, strlen(serverIPAdd)+1, EEPROM_OFFSET_SERVERIPADD)) {
				ret = -2;	//设置失败
			}
			else {
				ret = 0;	//设置成功
			}
		}
	}

	if (!ret) {
		strcpy(retStr, "设置成功");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM访问失败");
	}
	else if (ret == -2) {
		strcpy(retStr, "设置失败");
	}	
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[设置连接服务器端口]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
void setServerPort()
{
	char serverPort[10] = {0};
	char retStr[20] = {0};
	char ret = -2;	//设置失败
	//strcpy(dspBuf, "端口设置成功");

	if (eeprom_read(serverPort, 8, EEPROM_OFFSET_SERVERPORT)) {
		ret = -1;
	}
	if (ret != -1) {
		 InputData((char*)"服务器端口", serverPort, 0);
		if (serverPort[0] != 0) {	//判断字符串不为空
			if (eeprom_write(serverPort, 8, EEPROM_OFFSET_SERVERPORT)) {
				ret = -2;	//设置失败
			}
			else {
				ret = 0;	//设置成功
			}
		}
	}
	 if (!ret) {
		strcpy(retStr, "设置成功");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM访问失败");
	}
	else if (ret == -2) {
		strcpy(retStr, "设置失败");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[设置连接服务器SSID]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
void setServerSSID()
{
	char pUserName[20] = {0};
	char retStr[20] = {0};
	char ret = -2;	//设置失败
	//strcpy(dspBuf, "端口设置成功");

	if (eeprom_read(pUserName, 16, EEPROM_OFFSET_SERVERSSID)) {
		ret = -1;
	}
	if (ret != -1) {
		 InputData((char*)"SSID", pUserName, 1);
		if (pUserName[0] != 0) {	//判断字符串不为空
			if (eeprom_write(pUserName, 16, EEPROM_OFFSET_SERVERSSID)) {
				ret = -2;	//设置失败
			}
			else {
				ret = 0;	//设置成功
			}
		}
	}
	 if (!ret) {
		strcpy(retStr, "设置成功");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM访问失败");
	}
	else if (ret == -2) {
		strcpy(retStr, "设置失败");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[设置连接服务器密码]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
void setPassword()
{
	char password[20] = {0};
	char retStr[20] = {0};
	char ret = -2;	//设置失败
	
	if (eeprom_read(password, 16, EEPROM_OFFSET_SEVPASSWORD)) {
		ret = -1;
	}
	if (ret != -1) {
		 InputData((char*)"密码", password, 1);
		if (password[0] != 0) {	//判断字符串不为空
			if (eeprom_write(password, 16, EEPROM_OFFSET_SEVPASSWORD)) {
				ret = -2;	//设置失败
			}
			else {
				ret = 0;	//设置成功
			}
		}
	}
	 if (!ret) {
		strcpy(retStr, "设置成功");
	}
	else if (ret == -1) {
		strcpy(retStr, "EEPROM访问失败");
	}
	else if (ret == -2) {
		strcpy(retStr, "设置失败");
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[清空安全设置]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/08/24]
 		author		:	[chen-zhengkai]
************************************************************************/
int CNaNoWiFi_ClearRoutePSK()
{
    return 0;
}



void clearPSK()
{
	if(NaNo_OK == CNaNoWiFi_ClearRoutePSK()) {
		DispStr_CE(0,4,"清除成功",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	else {
		DispStr_CE(0,4,"清除失败",DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	}
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[连接网络]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
void connectWifi()
{
	//u16 pHandle[1] = {0};	//wifi连接句柄
	//unsigned char pHandle_char[2] = {0};	//wifi连接句柄存放数组
	char dspBuf[20] = {0};
	char serverPort[20] = {0};
	unsigned char serverIPAdd[16] = {0};
	
	//CWiFi_OpenMould();
	if (eeprom_read(serverIPAdd, sizeof(serverIPAdd), EEPROM_OFFSET_SERVERIPADD)) {
		strcpy(dspBuf, "读取IP失败");
	}
	if (eeprom_read(serverPort, 8, EEPROM_OFFSET_SERVERPORT)) {
		strcpy(dspBuf, "读取端口失败");
	}
	else if(NaNo_OK == CWiFi_Connect(g_pHandle, (char*)serverIPAdd, serverPort, 0)) {
		strcpy(dspBuf, "连接成功");
		//shortTochar(g_pHandle, pHandle_char);
		//eeprom_write(pHandle_char, sizeof(pHandle_char), EEPROM_OFFSET_WIFI_HANDLE);
	}
	else {
		//..注：若连接失败，则需要30秒后再次连接
		strcpy(dspBuf, "连接失败");
		CWiFi_ConnState(0);
	}

	DispStr_CE(0,6,dspBuf,DISP_CENTER|DISP_NORMAL|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键继续",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[输入数据]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/26]
 		author		:	[chen-zhengkai]
************************************************************************/
void InputData(char *pShowMsg, char *pRtnInfo, char alphaInput)             //..获得键盘输入数据 
{
	GETSTR_PARAM   gs;
	char           strbuf[50];
	memset(strbuf,0x00,50);
	memcpy(strbuf,pRtnInfo,strlen(pRtnInfo));
	memset(pRtnInfo,0x00,strlen(pRtnInfo));

	DispStr_CE(0,2,pShowMsg,DISP_POSITION|DISP_REVERSE|DISP_CLRSCR);
	gs.qx = 0;
	gs.qy = 4;
	gs.alpha = alphaInput;       //..是否允许输字母、符号， 0：不允许，1：可以  
	gs.sFont = 0;
	gs.pPrompt = "";
	gs.csChar = '_';
	gs.pwChar = 0;
	gs.spChar = '.';
	gs.pStr = strbuf;	//store the input words
	gs.maxNum = 1024;
	gs.minNum = 1;
	gs.minValue = -1;
	gs.maxValue = -1;
	gs.retNum = strlen(strbuf);
	gs.qEvent = EXIT_KEY_F1;
	if ( GetStr_E(&gs) ) {
		return;
	}
	memcpy(pRtnInfo,strbuf,strlen(strbuf));
}
/***********************************************************************
		module		:	[WIFI]
		function		:	[发送数据]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date			:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
void sendRecords()
{
	char retStr[20] = {0};
	char temp[20] = {0};
	int templen = 0;
	//unsigned char data_buffer[1000] = {0};	//要传送的数据
	unsigned char aBuffer[200] = {0};	
	unsigned char rb8583[50] = {0};
	unsigned char send_buf[200] = {0};	//每次上传数据数组
	int send_len = 0;
	//unsigned char* pdBuffer = NULL;		//每次上传数据指针
	USER_INFO* pinfo = NULL;
	char infotemp[10] = {0};
	unsigned long	db_cnt = 0;					//数据库记录数
	unsigned short	send_cnt = 0;				//上传次数
	char* pTemp = NULL;
	char	rec_flag = 0;
	
	strcpy(retStr, "数据上传成功");
	db_cnt = DB_count_records(0);	//返回数据库已记录的条数(包括已删除)
	if (!db_cnt) {
		strcpy(retStr, "数据库无记录");
	}
	else {
		DispStr_CE(0,6,"连接上传中",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,8,"请耐心等待",DISP_CENTER);
		DispStr_CE(0,10,"按F1退出...",DISP_CENTER);

	//	for (send_cnt = 0; send_cnt < db_cnt; send_cnt++) {
			pinfo = (USER_INFO*)DB_jump_to_record(ATTENDANCE_INDEX, send_cnt, &rec_flag);
			if (rec_flag) {	//记录被删除
	//			continue;
			}
			dec2hex(pinfo->phyNo, 4, infotemp);
			memcpy(rb8583, infotemp,  8);		//物理卡号
			//memcpy(rb8583+8, pinfo->time, 16);	//考勤时间
			atd_pack(aBuffer, rb8583, 24);
			hex2dec(aBuffer, 58, (unsigned char*)send_buf, &send_len);
			//send_len = 58;
#if 0
			if (NaNo_OK !=  CWiFi_Write(g_pHandle[0], send_buf,  send_len+1) ){	//注：长度必须多一字符
				strcpy(retStr, "数据上传失败");
				break;
			}
#else
			char tempBuf[300] = {0};
			//memcpy(tempBuf, "008A600031000008000038000001C00010000001090931201104084444444444444444444431323334353630303031393930323130333131343030313030303139390072A00000000386980701202020202020203030303030303030303030303030303030303030303030303030303030304646303130303030303130312020202020203030303030303030", sizeof("008A600031000008000038000001C00010000001090931201104084444444444444444444431323334353630303031393930323130333131343030313030303139390072A00000000386980701202020202020203030303030303030303030303030303030303030303030303030303030304646303130303030303130312020202020203030303030303030"));
			memcpy(tempBuf, "ABCDEFGHIJK", 11);
			int m = strlen(tempBuf);
			//hex2dec(tempBuf, strlen(tempBuf), (unsigned char*)send_buf,  &m);
			if (NaNo_OK !=  CWiFi_Write(g_pHandle[0], tempBuf,  11+1) ){	//注：长度必须多一字符
				strcpy(retStr, "数据上传失败");
		//		break;
			}
#endif
			if( KEY_F1 == KEY_Read()) {
				strcpy(retStr, "数据上传中断");
			//	break;
			}
			Sys_Delay_MS(100);	//延时100毫秒
	//	}
	}
	DispStr_CE(0,6,retStr,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按任意键返回",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[WIFI]
		function	:	[发送数据]
  		return		:	[0:发送成功
  						-1:没有数据
  						-2:发送失败
  						-3:上传中断]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[WIFI]
		date		:	[11/07/27]
 		author		:	[chen-zhengkai]
************************************************************************/
#if 0
char sendRecords(char* data_buffer, int bufferMax)
{
	unsigned char* pdBuffer = data_buffer;		//每次上传数据指针
	unsigned char send_buffer[1024] = {0};		//每次上传数据数组
	unsigned long	db_cnt = 0;					//数据库记录数
	unsigned short	send_cnt = 0;				//上传次数
	unsigned int	send_length = 0;			//上传数组长度（每次上传最多1000）
	db_cnt = DB_count_records(0);	//返回数据库已记录的条数(包括已删除)
	
	if (!db_cnt) {
		return -1;
	}
	db_to_str(data_buffer, bufferMax, db_cnt);	//数据库记录变字符串
	send_length = db_cnt*sizeof(USER_INFO);		//要发送的数据长度
	send_cnt	= send_length/MAX_SEND_BUFFER;	//要发送数据的次数，每次最多发送1000字节
	if (send_cnt%MAX_SEND_BUFFER) {
		send_cnt++;
	}
	while (send_cnt) {
		memcpy(send_buffer, pdBuffer, MAX_SEND_BUFFER);
		if (NaNo_OK ==  CWiFi_Write(g_HandleID,/*send_buffer,strlen(send_buffer)+1*/ "abcdefg", 8)) {	//注：长度必须多一字符
			send_cnt--;
			pdBuffer += MAX_SEND_BUFFER;
			memset(send_buffer, 0x00, 1024);
		}
		else {
			return -2;
		}
		if( KEY_F1 == KEY_Read()) {	//按F1退出
			return -3;
			break;
		}
		Sys_Delay_MS(100);	//延时100毫秒
	}
	return 0;
}
#endif
