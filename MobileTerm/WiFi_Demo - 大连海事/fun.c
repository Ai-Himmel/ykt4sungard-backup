/****************************************************************************
*
*文件(File):         fun.c
*
*修改(Modify):       2011/7/20 14:05:46
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
| V1.00  2011/7/20 14:05:46           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"
/***********************************************************************
		module		:	[菜单操作]
		function		:	[主菜单操作]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/07/20]
 		author		:	[chen-zhengkai]
************************************************************************/
void main_task()
{
	int select = -1;
	char main_menu_str[] =		"1. 考勤打卡  "
							"2. 查询记录  "
							"3. 数据传输  "
							"4. 身份识别  "
							"5. 机器设置  "
							"6. 管理员密码";
	BROWINFO	INFO_main;
	INFO_main.iStr = main_menu_str;			
	INFO_main.lPtr = 0;
	INFO_main.cPtr = 0;
	//Disp_Set_Magnification(2);	//放大字体
	while (1) {
		//以下BROWINFO结构成员变量必须参与循环，有可能会被EXT_Brow_Select函数改变
		INFO_main.startLine = 2;		//在LCD上的显示起始行
		INFO_main.dispLines = 6;		//在LCD上的显示行数
		INFO_main.mInt = 6;			//显示内容的总行数
		INFO_main.lineMax = 13;		//每行最大字符数
		INFO_main.sFont = 0;			//7x9大字体显示
		INFO_main.numEnable = 0;		//是否允许数字键代替方向控制
		INFO_main.qEvent = EXIT_AUTO_QUIT;	 //可导致函数退出的事件标志
		INFO_main.autoexit = 1200;		//自动退出的时间
		//菜单
		Disp_Clear();
		DispStr_CE(0, 0, "主菜单", DISP_CENTER);
		select = EXT_Brow_Select(&INFO_main);
		switch (select) {
			case 0:		//考勤打卡
				workAttendance_task();
				break;
			case 1:		//查询记录
				vstDatabase_task();
				break;
			case 2:		//数据传输
				dataUpload_task();
				break;
			case 3:		//身份识别
				discernID_task();
				break;
			case 4:		//机器设置
				funSet_task();
				break;
			case 5:		//设置管理员密码
				setAdmPsd_task();
				break;
			default:	//降低CPU占用率，降低能耗
				Sys_Power_Sleep(3);
				break;
		}
	}
}
/***********************************************************************
		module		:	[菜单操作]
		function	:	[机器设置菜单操作]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date		:	[11/07/20]
 		author		:	[chen-zhengkai]
************************************************************************/
void funSet_task()
{
	int select = -1;
	char fun_menu_str[] =	"1. 时间设置      "
							"2. 日期设置      "
							"3. 待机时间设置  "
							"4. 背光灯时间设置"
							"5. 按键音设置    "
							"6. 机器参数查询  "
							"7. 读取授权卡    ";
	BROWINFO	info;
	info.iStr = fun_menu_str;		//浏览内容指针
	info.lPtr = 0;					//显示内容iStr的起始显示行
	info.cPtr = 0;					//当前选择行
	

	
	while (1) {
		//以下BROWINFO结构成员变量必须参与循环，有可能会被EXT_Brow_Select函数改变
		info.startLine = 2;				//在LCD上的显示起始行
		info.dispLines = 7;				//在LCD上的显示行数
		info.mInt = 7;					//显示内容的总行数
		info.lineMax = 17;				//每行最大字符数
		info.sFont = 0;					//7x9大字体显示
		info.numEnable = 0;				//是否允许数字键代替方向控制
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //可导致函数退出的事件标志
		info.autoexit = 1200;			//自动退出的时间
		//菜单
		Disp_Clear();
		DispStr_CE(0, 0, "机器设置菜单", DISP_CENTER);
		select = EXT_Brow_Select(&info);
		switch (select) {
			case 0:		//时间设置
				setTime();
				break;
			case 1:		//日期设置
				setDate();
				break;
			case 2:		//待机时间设置
				Set_Auto_Poweroff();
				break;
			case 3:		//背光灯时间设置
				setBacklight();
				break;
			case 4:		//按键音设置
				setKeybeeper();
				break;
			case 5:		//机器参数查询
				break;
			case 6:		//读取授权卡
				getAuthorize();
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
		module		:	[菜单操作]
		function	:	[数据查询菜单操作]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date		:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void vstDatabase_task()
{
	int select = -1;
	char db_menu_str[] =	"1. 查询已记录数      "
							"2. 检查剩余可用记录数"
							"3. 删除所有记录      "
							"4. 初始化数据库      ";
	BROWINFO	info;
	info.iStr = db_menu_str;		//浏览内容指针
	info.lPtr = 0;					//显示内容iStr的起始显示行
	info.cPtr = 0;					//当前选择行

	while (1) {
		//以下BROWINFO结构成员变量必须参与循环，有可能会被EXT_Brow_Select函数改变
		info.startLine = 2;				//在LCD上的显示起始行
		info.dispLines = 6;				//在LCD上的显示行数
		info.mInt = 4;					//显示内容的总行数
		info.lineMax = 21;				//每行最大字符数
		info.sFont = 0;					//7x9大字体显示
		info.numEnable = 0;				//是否允许数字键代替方向控制
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //可导致函数退出的事件标志
		info.autoexit = 1200;			//自动退出的时间
		//菜单
		Disp_Clear();
		DispStr_CE(0, 0, "查询记录菜单", DISP_CENTER);
		select = EXT_Brow_Select(&info);
		switch (select) {
			case 0:		//查询已记录数
				check_recordsCnt();
				break;
			case 1:		//检查剩余可用记录数
				check_dbCapcity();
				break;
			case 2:		//删除所有记录
				del_Allrecords();
				break;
			case 3:		//初始化数据库
				db_init_menu();
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
		module		:	[菜单操作]
		function	:	[数据传输菜单操作]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date		:	[11/07/22]
 		author		:	[chen-zhengkai]
************************************************************************/
void dataUpload_task()
{
	int select = -1;
	char db_menu_str[] =	"1. USB传输 ";
							//"2. WIFI传输";
	BROWINFO	info;
	info.iStr = db_menu_str;		//浏览内容指针
	info.lPtr = 0;					//显示内容iStr的起始显示行
	info.cPtr = 0;					//当前选择行

	while (1) {
		//以下BROWINFO结构成员变量必须参与循环，有可能会被EXT_Brow_Select函数改变
		info.startLine = 0;				//在LCD上的显示起始行
		info.dispLines = 2;				//在LCD上的显示行数
		info.mInt = 1;					//显示内容的总行数
		info.lineMax = 11;				//每行最大字符数
		info.sFont = 0;					//7x9大字体显示
		info.numEnable = 0;				//是否允许数字键代替方向控制
		info.qEvent = EXIT_KEY_F1|EXIT_AUTO_QUIT|EXIT_KEY_POWER|EXIT_KEY_CANCEL;    //可导致函数退出的事件标志
		info.autoexit = 1200;			//自动退出的时间
		//菜单
		Disp_Clear();
		select = EXT_Brow_Select(&info);
		switch (select) {
			case 0:		//USB传输
				usb_upload_menu();
				break;
			case 1:		//WIFI传输
				//wifi_upload_menu();
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
		module		:	[菜单操作]
		function		:	[读取授权卡（获得密钥）]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/07/28]
 		author		:	[chen-zhengkai]
************************************************************************/
void getAuthorize()
{
	if ( !readM1Card(readAuthorizeCard) ) {
		DispStr_CE(0,6,"授权成功",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,10,"按任意键返回",DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[菜单操作]
		function		:	[考勤记录]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/01]
 		author		:	[chen-zhengkai]
************************************************************************/
void workAttendance_task()
{
	//if ( !readM1Card(workAttendance) ) {
	if ( !readM1Card(workAttendance_Dalian) ) {
		DispStr_CE(0,12,"记录成功",DISP_CENTER);
		DispStr_CE(0,14,"按任意键返回",DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[菜单操作]
		function		:	[身份识别]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void discernID_task()
{
	if ( !readM1Card(discernID) ) {
		DispStr_CE(0,14,"按任意键返回",DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[菜单操作]
		function		:	[设置管理员密码]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void setAdmPsd_task()
{
	GETSTR_PARAM 	gs;
	char	cueStr[30] = "请输入新管理员密码";
	char remwrds[] = "(6-8位):";
	char dspBuf[30] = {0};
	const char retStr[] = "按任意键返回";
	char admPsd[9] = {0};
	char psdtmp[9] = {0};
	char ret = 1;

	if ( !adminPassword(1) ) {	//输入旧的管理员密码验证
		DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
		if (input_password(remwrds, psdtmp) ) {
			strcpy(dspBuf, "输入失败");
			ret = 0;
		}
		if (ret) {
			strcpy(cueStr, "请再次输入密码");
			DispStr_CE(0, 0, cueStr, DISP_POSITION|DISP_CLRSCR);
			if ( input_password(remwrds ,admPsd) ) {
				strcpy(dspBuf, "输入失败");
				ret = 0;
			}
		}
		if (ret && strncmp(admPsd, psdtmp, 8) ) {	//两次输入不一致
			strcpy(dspBuf, "两次输入不一致");
			ret = 0;	
		}
		if (ret && eeprom_write(admPsd, sizeof(admPsd), EEPROM_OFFSET_ADM_PSD)) {
			strcpy(dspBuf, "EEPROM读写失败");
			ret = 0;
		}
		if (ret) {
			strcpy(dspBuf, "密码设置成功");
		}
		DispStr_CE(0, 6, dspBuf, DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, retStr, DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[菜单操作]
		function		:	[一次性初始化管理员密码，端口，SSID等]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[MENU]
		date			:	[11/08/02]
 		author		:	[chen-zhengkai]
************************************************************************/
void adminPsd_init()
{
	unsigned char psdctrl[1] = {0};
	if (eeprom_read(psdctrl, 1, EEPROM_OFFSET_ADM_CTRL)) {
		DispStr_CE(0, 6, "EEPROM异常", DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0, 10, "按任意键继续", DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return;
	}
	if ( *psdctrl != 0xA5 ) {	//需要初始化
		*psdctrl = 0xA5;
		if (eeprom_write(psdctrl, 1, EEPROM_OFFSET_ADM_CTRL) || eeprom_write("11111111", 8, EEPROM_OFFSET_ADM_PSD)
		|| eeprom_write("6295", 8, EEPROM_OFFSET_SERVERPORT) ||  eeprom_write("ChinaNet1", 16, EEPROM_OFFSET_SERVERSSID)
		|| eeprom_write("12345678", 16, EEPROM_OFFSET_SEVPASSWORD)) {
			DispStr_CE(0, 6, "EEPROM异常", DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0, 10, "按任意键继续", DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			return;
		}
	}
}


