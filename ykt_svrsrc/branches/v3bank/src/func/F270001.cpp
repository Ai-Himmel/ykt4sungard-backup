/* ----------------------------------------------------------
 * �������ڣ�2009-03-22
 * �������ߣ��Ž�
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��Ͼ������������п���
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
#include "bank.h"

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
int BankCardRelation(tagBankCardRelation* BCR);

int F270001(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	int ret=0;
	
	if(Is_out_of_service())
	{
	    strcpy(szMsg,"�������з���ʱ��");			
	    return 8888;
	}
	switch(rPack->sstatus0[0])
	{
	case 'Q':	                                                                        //���п���ѯ
			ret=Bank_Query(handle,rPack,pRetCode,szMsg);
			break;
	default:
		ret=Bank_Query(handle,rPack,pRetCode,szMsg);
		break;
	}

	return 0;
}
