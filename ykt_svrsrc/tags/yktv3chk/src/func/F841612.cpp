/* --------------------------------------------
 * ��������: F841612.cpp
 * ��������: 2008-03-03
 * ��������: auto creat by wen jian
 * �汾��Ϣ: 1.0.0.0
 * ������: ����ͻ���Ϣ�޸�
 * --------------------------------------------
 * �޸�����:
 * �޸���Ա:
 * �޸�����:
 * �汾��Ϣ:
 * ��ע��Ϣ:
 * --------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpack.h"
#include "errdef.h"
#include "pubdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "dbfunc.h"
#include "busqc.h"
#include "acctrans.h"
#include "dbfunc_foo.h"

int F841612(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{

	char    	stuempno[30+1]="";           	//ѧ�Ż�Ա����
	int		custtype=0;                   		//�ͻ����
	char    	custname[60+1]="";            	//�ͻ�����
	int		area_no=0;                       		//�ͻ���������
	char    	dept_no[30+1]="";        		//���ź�
	char    	dept_name[240+1]="";     		//��������
	char    	class_no[30+1]="";      		//�༶
	char		specialty_no[30+1] = "";		//רҵ
	char    	sex[1+1]="";                  		//�Ա�
	char    	country[30+1]="";                  	//����
	int		people=0;                     		//����
	int		id_type;						//֤������
	char    	id_no[60+1]="";              		//���֤��
	char    	tel[30+1]="";                 		//�绰
	char    	addr[240+1]="";            		//��ַ
	char    	email[60+1]="";                 	//�绰
	char        at_school_status[2]="";			//��У״̬ 1����У��0-��У
	char    	in_school_date[8+1]="";    	//��У����
	char    	out_school_date[8+1]="";    	//Ԥ����У����
	char    	sqlcmd[2048]="";

	int    ret=0;

	CAccTrans *pAccTrans=CAccTrans::getInstance();
	pAccTrans->clear();
	GetCpackDataString(rPack,pAccTrans->cpackdata);
	pAccTrans->trans.transcode=TC_CUSTOMERTMPUPD;
	ret=pAccTrans->addOperDtl(rPack->semp);
	if(ret)
		return ret;

	des2src(stuempno,rPack->scert_no);
	des2src(custname,rPack->sall_name);
	custtype=rPack->lvol0;
	des2src(sex,rPack->sstatus1);
	id_type=rPack->lvol1;
	des2src(id_no,rPack->semail2);		
	des2src(country,rPack->snation_code);
	people=rPack->lvol2;
	des2src(addr,rPack->saddr);
	des2src(tel,rPack->sphone);
	des2src(email,rPack->semail);
	area_no=rPack->lvol3;
	des2src(dept_no,rPack->sphone2);
	des2src(class_no,rPack->sphone3);
	des2src(specialty_no,rPack->spager);
	des2src(at_school_status,rPack->sstatus0);
	des2src(in_school_date,rPack->sdate1);
	des2src(out_school_date,rPack->sdate2);
	if(!strlen(stuempno))
	{
		*pRetCode=E_STUNO_NOT_EXIST;
		goto L_RETU;
	}
	strcpy(sqlcmd,"update ykt_cur.t_customertmp SET  ");
	if(strlen(custname))
		sprintf(sqlcmd+strlen(sqlcmd)," custname='%s',",custname);
	if(custtype)
		sprintf(sqlcmd+strlen(sqlcmd)," custtype=%d,",custtype);
	if(strlen(sex))
		sprintf(sqlcmd+strlen(sqlcmd)," sex='%s',",sex);
	if(id_type)
		sprintf(sqlcmd+strlen(sqlcmd)," id_type=%d,",id_type);
	if(strlen(id_no))
		sprintf(sqlcmd+strlen(sqlcmd)," id_no='%s',",id_no);
	if(strlen(country))
		sprintf(sqlcmd+strlen(sqlcmd)," country='%s',",country);
	if(people)
		sprintf(sqlcmd+strlen(sqlcmd)," people=%d,",people);
	if(strlen(addr))
		sprintf(sqlcmd+strlen(sqlcmd)," addr='%s',",addr);
	if(strlen(tel))
		sprintf(sqlcmd+strlen(sqlcmd)," tel='%s',",tel);
	if(strlen(email))
		sprintf(sqlcmd+strlen(sqlcmd)," email='%s',",email);
	if(area_no)
		sprintf(sqlcmd+strlen(sqlcmd)," area_no=%d,",area_no);
	if(strlen(dept_no))
		sprintf(sqlcmd+strlen(sqlcmd)," dept_no='%s',",dept_no);
	if(strlen(specialty_no))
		sprintf(sqlcmd+strlen(sqlcmd)," specialty_no='%s',",specialty_no);
	if(strlen(class_no))
		sprintf(sqlcmd+strlen(sqlcmd)," class_no='%s',",class_no);
	if(strlen(at_school_status))
		sprintf(sqlcmd+strlen(sqlcmd)," at_school_status='%s',",at_school_status);
	if(strlen(in_school_date))
		sprintf(sqlcmd+strlen(sqlcmd)," in_school_date='%s',",in_school_date);
	if(strlen(out_school_date))
		sprintf(sqlcmd+strlen(sqlcmd)," out_school_date='%s',",out_school_date);
	sqlcmd[strlen(sqlcmd)-1]=0x20; 
	sprintf(sqlcmd+strlen(sqlcmd)," where stuempno='%s' ",stuempno);
	ret=DynamicStmtExecute(sqlcmd);
	if(ret)
	{
		writelog(LOG_ERR,"sql:[%s]",sqlcmd);
		if(DB_NOTFOUND==ret)
			*pRetCode=E_DB_CUSTOMER_TMP_N;
		else
			*pRetCode=E_DB_CUSTOMER_TMP_U;
		goto L_RETU;
	}
	return 0;
L_RETU:
	return -1;
}
