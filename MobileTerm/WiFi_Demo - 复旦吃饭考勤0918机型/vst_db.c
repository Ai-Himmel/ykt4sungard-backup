/****************************************************************************
*
*文件(File):         vst_db.c
*
*修改(Modify):       2011/7/21 14:24:37
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
| V1.00  2011/7/21 14:24:37           USER 
----------------------------------------------------------------------------
****************************************************************************/
#include "in_call.h"
void db_init();				//初始化数据库
/***********************************************************************
		module		:	[数据查询操作]
		function		:	[检查数据库，看是否需要初始化]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[VST_DB]
		date			:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void db_check()
{
	char	need_init = 0;
	long	ret = 0;
	//设置数据库的起始地址，并返回数据库中已经有的数据表的数量。
	if ( DB_init_sys_param(0) != DATA_TABLE_NUM ) {	
		DispStr_CE(0,0,"数据库未经初始化",DISP_CENTER);	
		need_init = 1;
	}
	if (need_init) {
		DispStr_CE(0,4,"按【OK】键 - 初始化",DISP_CENTER);
		DispStr_CE(0,10,"按其它键 - 取消",DISP_CENTER);
		ret = delay_and_wait_key(0,EXIT_KEY_ALL,0);
		if (ret == (long)EXIT_KEY_OK || ret == (long)EXIT_KEY_ENTER) {
			db_init();	//初始化数据库
		}
	}
}
/***********************************************************************
		module		:	[数据查询操作]
		function	:	[数据库初始化]
  		return		:	[无]
		comment		:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[VST_DB]
		date		:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void db_init()
{
	const unsigned short DATASIZE = sizeof(USER_INFO);
	const unsigned short BLOCKSIZE = 10;//(sizeof(USER_INFO)%4) ? (sizeof(USER_INFO)/4+1) : (sizeof(USER_INFO)/4);
	const char retStr[] = "按任意键返回";
	char disbuf[30] = {0};
	short ret = 0;
	DispStr_CE(0,6,"数据库初始化中",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,"请耐心等待...",DISP_CENTER);

	DB_init_sys_param(0);		//设置数据库起始地址
	ret = DB_erase_db_sys();	//格式化数据库
	if (ret) {
			DispStr_CE(0,6,"数据库初始化失败",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,retStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			return;
	}
	ret = DB_format_db(0, BLOCKSIZE, DATASIZE);	//初始化数据库，创建表
	if (ret) {	/*Debug	begin*/
		sprintf(disbuf,"Create Err:%d",ret);
		DispStr_CE(0,6,disbuf,DISP_CENTER|DISP_CLRSCR);			
		delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
		return;
	}	/*Debug	end*/
	ret = DB_init_sys_param(0);	//检查数据库系统，在调用DB_check_format()必须的
	if (ret != DATA_TABLE_NUM) {
		DispStr_CE(0,6,"数据库初始化失败",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,10,retStr,DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return;
	}
	else {
		ret = DB_check_format(0, BLOCKSIZE, DATASIZE);	//检查表的格式是否正确
		if (ret) {	/*Debug	begin*/
			sprintf(disbuf,"Check Table %d Err:%d",0,ret);
			DispStr_CE(0,6,disbuf,DISP_CENTER|DISP_CLRSCR);
			delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
			return;
		}	/*Debug	end*/
		DispStr_CE(0,6,"数据库初始化成功",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,10,retStr,DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[数据查询操作]
		function		:	[数据库初始化（菜单调用）]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[VST_DB]
		date			:	[11/07/21]
 		author		:	[chen-zhengkai]
************************************************************************/
void db_init_menu()
{
	long ret = 0;
	if ( adminPassword(0) ) {
		return;
	}
	DispStr_CE(0,2,"初始化会丢失所有数据",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,6,"继续吗？",DISP_CENTER);
	DispStr_CE(0,10,"按【OK】继续，",DISP_CENTER);
	DispStr_CE(0,14,"按其它键返回",DISP_CENTER);
	ret = delay_and_wait_key(0,EXIT_KEY_ALL,0);
	if (ret == (long)EXIT_KEY_OK || ret == (long)EXIT_KEY_ENTER) {
		db_init();
	}
}
/***********************************************************************
		module		:	[数据查询操作]
		function		:	[删除所有记录]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[VST_DB]
		date			:	[11/07/22]
 		author		:	[chen-zhengkai]
************************************************************************/
void del_Allrecords()
{
	long ret = 0;
	short eraseRet = 0;
	const char retStr[] = "按任意键返回";
	
	if ( adminPassword(0) ) {
		return;
	}
	
	DispStr_CE(0,4,"确认删除所有数据吗？",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"按【OK】继续，",DISP_CENTER);
	DispStr_CE(0,12,"按其它键返回",DISP_CENTER);
	ret = delay_and_wait_key(0,EXIT_KEY_ALL,0);
	if (ret == (long)EXIT_KEY_OK || ret == (long)EXIT_KEY_ENTER) {
		eraseRet = DB_erase_filesys(0);
		if (!eraseRet) {
			DispStr_CE(0,6,"所有记录已删除",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,retStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		}
		else {
			DispStr_CE(0,6,"FLASH错误,请进行硬件检查",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,retStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		}
	}
}
/***********************************************************************
		module		:	[数据查询操作]
		function		:	[查询已记录数]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[VST_DB]
		date			:	[11/07/22]
 		author		:	[chen-zhengkai]
************************************************************************/
void check_recordsCnt()
{
	unsigned long	db_cnt = 0;
	char dspBuf[20] = {0};
	int counter = 0;
	char flag = 0;
	db_cnt = DB_count_records(0);	//返回记录的条数
	int i = 0;
	for(i = 0; i < db_cnt; i++) {
		DB_jump_to_record(0, i, &flag);
		if(flag) {
			continue;
		}
		else {
			counter++;
		}
	}
	sprintf(dspBuf,"已存储%d条记录", counter);
	DispStr_CE(0,6,dspBuf,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,"按任意键返回",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[数据查询操作]
		function		:	[查询剩余容量]
  		return		:	[无]
		comment	:	[全局普通函数]
		machine		:	[EH-0818]
		language	:	[CHN]
 		keyword		:	[VST_DB]
		date			:	[11/07/22]
 		author		:	[chen-zhengkai]
************************************************************************/
void check_dbCapcity()
{
	unsigned long	db_cap_left = 0;
	char	dspBuf[30] = {0};
	
	db_cap_left = DB_capacity(ATTENDANCE_INDEX) - DB_count_records(ATTENDANCE_INDEX);
	sprintf(dspBuf,"还能存储%d条记录", db_cap_left);
	DispStr_CE(0,6,dspBuf,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,"按任意键返回",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
