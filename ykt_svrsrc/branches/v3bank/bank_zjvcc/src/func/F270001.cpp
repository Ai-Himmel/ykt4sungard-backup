/* ----------------------------------------------------------
 * �������ڣ�2009-03-22
 * �������ߣ��Ž�
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��Ͼ������������п���

 * �޸�����:	2011-01-14
 * �޸�����:	�����
 * 
 * ----------------------------------------------------------*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include <signal.h>
#include "profile.h"
#include "mypub.h"  
#include "tcp.h"
#include "cpack.h"
#include "svrlink.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "bupub.h"
#include "transinfo.h"
#include "dictionary.h"
#include "shem.h"
#include "bank_interface.h"

extern CSvrLink g_SvrLink;
#ifndef	DEBUG
	#define	DEBUG
#endif

//���п��󶨽ӿ�
//���ܺ�		:270001

//��������  :sstatus0:		'A'  ���� ,'D'  ɾ�� ,'R' ��ѯ
//����		:sall_name
//���֤��	:semail2
//ѧ��		:spage
//���п���	:scard0

//������Ϣ
//������	    : lsafe_level
//������Ϣ:vsvarstr0


// �޸�У����
int Bank_ChangePin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);

// ����У����
int Bank_ResetPin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);


int F270001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	writelog(LOG_INFO,"270001 bind_process type[%s]",rPack->sstatus0);
	switch(rPack->sstatus0[0])
	{
		case 'A':				// ���п���
			return Bank_Bind(handle, rPack, pRetCode, szMsg);
		case 'D':				// ���п������
			return Bank_UnBind(handle, rPack, pRetCode, szMsg);
		case 'C':				// У�����޸�
			return Bank_ChangePin(handle, rPack, pRetCode, szMsg);
		case 'R':				// У��������
			return Bank_ResetPin(handle, rPack, pRetCode, szMsg);			
		default:				// ���п��󶨹�ϵ��ѯ
			return Bank_Querybind(handle, rPack, pRetCode, szMsg);
	}
	return 0;
}

