/****************************************************************************
*
*�ļ�(File):         vst_db.c
*
*�޸�(Modify):       2011/7/21 14:24:37
*
*����(Author):       USER
*
*����(Compile):      ����ƽ̨(Smart Platform)
*
*����(Description):
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
void db_init();				//��ʼ�����ݿ�
/***********************************************************************
		module		:	[���ݲ�ѯ����]
		function		:	[������ݿ⣬���Ƿ���Ҫ��ʼ��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
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
	//�������ݿ����ʼ��ַ�����������ݿ����Ѿ��е����ݱ��������
	if ( DB_init_sys_param(0) != DATA_TABLE_NUM ) {	
		DispStr_CE(0,0,"���ݿ�δ����ʼ��",DISP_CENTER);	
		need_init = 1;
	}
	if (need_init) {
		DispStr_CE(0,4,"����OK���� - ��ʼ��",DISP_CENTER);
		DispStr_CE(0,10,"�������� - ȡ��",DISP_CENTER);
		ret = delay_and_wait_key(0,EXIT_KEY_ALL,0);
		if (ret == (long)EXIT_KEY_OK || ret == (long)EXIT_KEY_ENTER) {
			db_init();	//��ʼ�����ݿ�
		}
	}
}
/***********************************************************************
		module		:	[���ݲ�ѯ����]
		function	:	[���ݿ��ʼ��]
  		return		:	[��]
		comment		:	[ȫ����ͨ����]
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
	const char retStr[] = "�����������";
	char disbuf[30] = {0};
	short ret = 0;
	DispStr_CE(0,6,"���ݿ��ʼ����",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,"�����ĵȴ�...",DISP_CENTER);

	DB_init_sys_param(0);		//�������ݿ���ʼ��ַ
	ret = DB_erase_db_sys();	//��ʽ�����ݿ�
	if (ret) {
			DispStr_CE(0,6,"���ݿ��ʼ��ʧ��",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,retStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
			return;
	}
	ret = DB_format_db(0, BLOCKSIZE, DATASIZE);	//��ʼ�����ݿ⣬������
	if (ret) {	/*Debug	begin*/
		sprintf(disbuf,"Create Err:%d",ret);
		DispStr_CE(0,6,disbuf,DISP_CENTER|DISP_CLRSCR);			
		delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
		return;
	}	/*Debug	end*/
	ret = DB_init_sys_param(0);	//������ݿ�ϵͳ���ڵ���DB_check_format()�����
	if (ret != DATA_TABLE_NUM) {
		DispStr_CE(0,6,"���ݿ��ʼ��ʧ��",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,10,retStr,DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		return;
	}
	else {
		ret = DB_check_format(0, BLOCKSIZE, DATASIZE);	//����ĸ�ʽ�Ƿ���ȷ
		if (ret) {	/*Debug	begin*/
			sprintf(disbuf,"Check Table %d Err:%d",0,ret);
			DispStr_CE(0,6,disbuf,DISP_CENTER|DISP_CLRSCR);
			delay_and_wait_key( 0, EXIT_KEY_ALL, 0 );
			return;
		}	/*Debug	end*/
		DispStr_CE(0,6,"���ݿ��ʼ���ɹ�",DISP_CENTER|DISP_CLRSCR);
		DispStr_CE(0,10,retStr,DISP_CENTER);
		delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
	}
}
/***********************************************************************
		module		:	[���ݲ�ѯ����]
		function		:	[���ݿ��ʼ�����˵����ã�]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
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
	DispStr_CE(0,2,"��ʼ���ᶪʧ��������",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,6,"������",DISP_CENTER);
	DispStr_CE(0,10,"����OK��������",DISP_CENTER);
	DispStr_CE(0,14,"������������",DISP_CENTER);
	ret = delay_and_wait_key(0,EXIT_KEY_ALL,0);
	if (ret == (long)EXIT_KEY_OK || ret == (long)EXIT_KEY_ENTER) {
		db_init();
	}
}
/***********************************************************************
		module		:	[���ݲ�ѯ����]
		function		:	[ɾ�����м�¼]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
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
	const char retStr[] = "�����������";
	
	if ( adminPassword(0) ) {
		return;
	}
	
	DispStr_CE(0,4,"ȷ��ɾ������������",DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,8,"����OK��������",DISP_CENTER);
	DispStr_CE(0,12,"������������",DISP_CENTER);
	ret = delay_and_wait_key(0,EXIT_KEY_ALL,0);
	if (ret == (long)EXIT_KEY_OK || ret == (long)EXIT_KEY_ENTER) {
		eraseRet = DB_erase_filesys(0);
		if (!eraseRet) {
			DispStr_CE(0,6,"���м�¼��ɾ��",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,retStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		}
		else {
			DispStr_CE(0,6,"FLASH����,�����Ӳ�����",DISP_CENTER|DISP_CLRSCR);
			DispStr_CE(0,10,retStr,DISP_CENTER);
			delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
		}
	}
}
/***********************************************************************
		module		:	[���ݲ�ѯ����]
		function		:	[��ѯ�Ѽ�¼��]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
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
	db_cnt = DB_count_records(0);	//���ؼ�¼������
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
	sprintf(dspBuf,"�Ѵ洢%d����¼", counter);
	DispStr_CE(0,6,dspBuf,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
/***********************************************************************
		module		:	[���ݲ�ѯ����]
		function		:	[��ѯʣ������]
  		return		:	[��]
		comment	:	[ȫ����ͨ����]
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
	sprintf(dspBuf,"���ܴ洢%d����¼", db_cap_left);
	DispStr_CE(0,6,dspBuf,DISP_CENTER|DISP_CLRSCR);
	DispStr_CE(0,10,"�����������",DISP_CENTER);
	delay_and_wait_key( 3, EXIT_KEY_ALL, 0 );
}
