#ifndef _IMPORTDEF_H_
#define _IMPORTDEF_H_
/** 
 * ģ����					39�ֳֻ���̬��
 * �ļ���					importdef.h
 * �ļ�ʵ�ֹ���				39�ֻ��ӿں������붨��
 * ����						����
 * �汾						V0.1
 * ����						2005-10-17
 * ��ע
 * $Id$
 */

#ifdef __cplusplus
extern "C" {
#endif

#define DCLR_SMCFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name;

#define DEF_SMCFUNC(name) \
	LP##name name = NULL;

#define LOAD_SMCFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if( NULL == name) \
		return -1;

//////////////////////////////////////////////////////////////////////////
//�ӿں���
/** 
 * @brief ����39�ṩ�Ľӿڶ�̬��
 * 
 * @return �ɹ����� 0 ��ʧ�ܷ��� -1
 */
int LoadSmartCom411SCJ();
/** 
 * @brief �ͷ�39��̬��
 */
void CloseSmartCom411SCJ();
//////////////////////////////////////////////////////////////////////////
// ���뺯��
DCLR_SMCFUNC(int,IniCom,(int ComPort,int BaudRate));
DCLR_SMCFUNC(int,CloseCom,(int ComPort));
DCLR_SMCFUNC(int,ReadId,(int ComPort,unsigned char *id,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,SetCommision,(int ComPort,int Addr,unsigned char * Commision,unsigned char *newcommision,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,WriteJh,(int ComPort,unsigned char *id, int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,ReadDate,(int ComPort,int Addr, unsigned char *Buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,UpRecordOne,(int ComPort,int Addr,unsigned char * commision,unsigned char *buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,EndUpRecordOne,(int ComPort,int Addr,unsigned char * commision,unsigned char *serialno,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,UpHisBySerial,(int ComPort,int Addr,unsigned char *commision,unsigned char *serialno,unsigned char *buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,ReadType,(int ComPort,unsigned char *buffer,int Addr, int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,SetWorkKey,(int ComPort, int Addr, unsigned char *commision, unsigned char *key,
			 int level, unsigned char *level_Array));
DCLR_SMCFUNC(int,EmptyFlash,(int ComPort,int Addr,unsigned char *commision,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,WriteId,(int ComPort,unsigned char *id,int level,unsigned char *level_array));
DCLR_SMCFUNC(int,UserUpParam,(int ComPort,int Addr,unsigned char * Commision,unsigned char* Buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,DownDelBlack,(int ComPort,int Addr,unsigned char * Commision,int &num,unsigned char *buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,DownDelBAll,(int ComPort,int Addr,unsigned char * Commision,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,DownBlackCard,(int ComPort,int Addr,unsigned char * Commision,int &num,unsigned char *Buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,DownBlackVersion,(int ComPort,int Addr,unsigned char * Commision,unsigned char* Buffer,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,UpBlackVersion,(int ComPort,int Addr,unsigned char* Buffer, int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,DownBlackExpire,(int ComPort,int Addr,unsigned char *commision,unsigned char*date,int level,unsigned char *level_Array));
DCLR_SMCFUNC(int,UpBlackExpire,(int ComPort,int Addr,unsigned char * commision,unsigned char *date, int level,unsigned char *level_Array));

#ifdef __cplusplus
}
#endif

#endif // _IMPORTDEF_H_
