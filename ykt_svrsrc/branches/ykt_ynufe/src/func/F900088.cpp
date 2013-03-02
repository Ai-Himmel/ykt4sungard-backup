/* ----------------------------------------------------------
 * �������ƣ�F900088.sqc
 * �������ڣ�2004-08-27
 * �������ߣ�������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ���ǰ̨���������ɱ������(ǰ̨��������)
 			 ��ϵͳ��ʱ����������ͬ����������߼����죬
 			 ���²�����һϵ�в���
 * ----------------------------------------------------------
 * �޸�����: 2004-09-08
 * �޸���Ա: ������
 * �޸�����: ͳһ�淶����
 * �汾��Ϣ��1.0.0.1
 * ��ע��Ϣ
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/


#define _IN_SQC_                                  
#include "fdsqc.h"                                
#include <string.h>                               
#include <stdio.h>    
#include "errdef.h"  
#include "balance.h"                                                

int F900088(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg) 
{                                                 
     

	char		hi_operator[10+1]; 
	char		szNull[] ="";              
	int 		ret=0;													  

	// ��������Ա����
	Strncpy_t(hi_operator, in_pack->scust_no, sizeof(hi_operator)); 

	// ����������
	trim(hi_operator);
    	if (strcmp (szNull,hi_operator) == 0) 
	{
		*pRetCode=E_INPUT_NOOPERATOR;
		writelog(LOG_ERR,"hi_operator,hi_operator[%s]errcode[%d]!",hi_operator,E_INPUT_NOOPERATOR);
		goto L_RETU;
	}
  
     	//ֹͣ���ʣ������ݿ�ȫ�ֲ������е����ʱ�־
	ret=StopInBalance();
	if(ret)
	{
		writelog(LOG_ERR,"�޸��ս��־����!");
		return ret;
	}
	//���������������
	ret=CreateActiveReport();
	if(ret)
	{
		writelog(LOG_ERR,"������������������!");
		return ret;
	}
	//���ɲ����������
	ret=CreateOperReport();
	if(ret)
	{
		writelog(LOG_ERR,"���ɲ��������ʧ��!");
		return ret;
	}
	//������ͨ�̻����㱨��
	ret=CreateShopReport();
	if(ret)
	{
		writelog(LOG_ERR,"�����̻����㱨��ʧ��!");
		return ret;
	}
	//�����ʲ���ծ����
	ret=CreateRichDebtReport();
	if(ret)
	{
		writelog(LOG_ERR,"�����ʲ���ծ��ʧ��!");
		return ret;
	}

	//�ֶ����ʽ������������񣬽����µ�������ˮ
	ret=Startup();
	if(ret)
	{
		writelog(LOG_ERR,"ϵͳ��������ʧ��!");
		return ret;
	}

  	writelog(LOG_ERR,"Manual balance is succeed![%d]",ret);                                        
   	//ERR_DEAL("���ʳɹ����!",ret);

    return 0;   

	L_RETU:
		return *pRetCode;                                                                                                
                                          
}                                                 
                                                
