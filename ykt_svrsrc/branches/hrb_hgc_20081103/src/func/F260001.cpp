/* ----------------------------------------------------------
 * �������ƣ�F260001.cpp
 * �������ڣ�2009-03-11
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�������Ȧ���ֹ����˴���
 * ----------------------------------------------------------*/

 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include "pubdef.h"
 #include "errdef.h"
 #include "pubfunc.h"
 #include "pubdb.h"
 #include "dbfunc.h"
 #include "dbfunc_foo.h"
 #include "account.h"
 #include "fdsqc.h"
 #include "profile.h"
 #include "banktype.h"
 #include "../bank/bank.h"


 #define Debug 1


int F240007(TRUSERID * handle, int iRequest, ST_PACK * r_pack, int * pRetCode, char * szMsg);

 static int init(ST_PACK *rPack)	//����ļ����������Ƿ���ȷ
 { 
     return((strlen(rPack->scard0)&&strlen(rPack->scard1)) > 0 ? 0 : E_DB_TRANSBANK_FILE_NOFOUND);
 }

 int F260001(TRUSERID * handle, int iRequest, ST_PACK * r_pack, int * pRetCode, char * szMsg)
 {
  	if((*pRetCode=init(r_pack))) 
   		 return *pRetCode; 
	int ret=0;
    FILE *fp =NULL;
    BANK_COMPARE_RECODE compare_record;			//�����ļ���¼�Ļ�������
	char comp_file_path[256]="";				  	//�ļ�·��
    char file_name[256] ="";  					  	//�ļ���
    char T_date[15]=""; 						 	//��������
    ST_CPACK aPack;							 		//���ⷢ��Ӧ���
    ST_CPACK sPack;  								//���͵����˵����ݰ�
    ST_PACK * out_pack = (ST_PACK*)&(aPack.pack);							
    ST_PACK * send_pack =(ST_PACK*)&(sPack.pack);

    ResetNormalCPack(&sPack,0,1);
    memset(&sPack,0,sizeof sPack);
    ResetNormalCPack(&aPack,0,1);
    memset(&aPack,0,sizeof aPack);

	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_LVOL1,F_SCUST_AUTH,F_SCUST_AUTH2,F_SORDER0,F_SEMP_NO,F_SCUST_TYPE,F_SORDER1,F_SCARD1,0);

   ret = GetParameter(GLOBAL_UPLOAD_PATH,comp_file_path);	//ȡ�ļ���ַ
   if(ret)
   {
   	writelog(LOG_ERR,"��ȡ�ļ���ַ����,err_code=[%d] and error_path=[%s]",ret,comp_file_path);
	goto L_retu;
   }

   if(Debug)
   writelog(LOG_ERR,"comp_file_path= [%s]",comp_file_path);

   strcat(file_name,comp_file_path);
   strcat(file_name,"/");
   strcat(file_name,r_pack->scard0);  	//�ļ���
   strcat(T_date,r_pack->scard1);  		//��������
   if ((fp= fopen(file_name,"rb")) == NULL)
    {
        if(Debug)
		writelog(LOG_ERR,"�����ļ�������! Open Transfer Bank File Error, File Path:[%s]",file_name);
		*pRetCode = E_DB_TRANSBANK_FILE_OPENERR;
		return E_DB_TRANSBANK_FILE_OPENERR;	
    }
    while(1)
    {
    	if(NULL == fgets((char *)(&compare_record),sizeof(BANK_COMPARE_RECODE),fp))
    	{
    	  	writelog(LOG_ERR,"fgets errof local_sn[%s]",compare_record.LocalSn);
			break;
    	}

		if(Debug)
		{
		writelog(LOG_ERR,"scust_auth=[%s]",compare_record.BankCard);
		writelog(LOG_ERR,"ssust_auth2=[%s]",compare_record.BankSn);
		writelog(LOG_ERR,"sorder0=[%s]",compare_record.GDCAccount);
		writelog(LOG_ERR,"semp_no=[%s]",compare_record.LocalSn);
		writelog(LOG_ERR,"scust_type=[%s]",compare_record.TradeCode);
		writelog(LOG_ERR,"sorder1=[%s]", compare_record.TransMomoy);
		writelog(LOG_ERR,"scard1=[%s]",T_date);
		}
	 	send_pack->lvol0=0;
	 	des2src(send_pack->scust_auth,compare_record.BankCard);
	 	des2src(send_pack->scust_auth2,compare_record.BankSn);
	 	des2src(send_pack->sorder0,compare_record.GDCAccount);
	 	des2src(send_pack->semp_no,compare_record.LocalSn);
	 	des2src(send_pack->scust_type,compare_record.TradeCode);
	 	des2src(send_pack->sorder1, compare_record.TransMomoy);
	 	des2src(send_pack->scard1, T_date);	
	 	ret=F240007(handle,iRequest,send_pack,pRetCode,szMsg);
       	if(ret)
       	{
   	    	writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,sPack.head.retCode);
	    	strcpy(szMsg,"���ù��ܺ�:240007 ʧ��,ҵ����ֹ");
	    	goto L_retu;
        }
   }
	
	send_pack->lvol0 = 1;
	strcpy(send_pack->scard1,T_date);
	ret=F240007(handle,iRequest,send_pack,pRetCode,szMsg);
	if(ret>0||*pRetCode!=0)
	{
		if (ret < 0)
		{
			writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,"���ú�̨ҵ��ʧ�ܣ�ҵ����ֹ");
			goto L_retu;
		}
		else
		{
			writelog(LOG_ERR,"Call 240007 error,errcode=[%d],retCode=[%d]",ret,aPack.head.retCode);
			strcpy(szMsg,aPack.pack.vsmess);
			goto L_retu;
		}
	}
		
	if(fclose(fp))
	{
	 	writelog(LOG_ERR,"close file error ,file=[%s]",file_name);
		goto L_retu;
	}
	SetCol(handle,0);
    SetCol(handle,F_VSMESS,0);
   	strcpy(out_pack->vsmess,"���˳ɹ�!");
   	PutRow(handle,out_pack,pRetCode,szMsg);
 	return 0;
L_retu:
	return -1;
}

 
