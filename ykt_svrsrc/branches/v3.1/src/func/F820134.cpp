/* ----------------------------------------------------------
 * �������ƣ�F820134.c
 * �������ڣ�2004-8-31 09��44
 * �������ߣ���ѫ��
 * �汾��Ϣ��1.0.0.0
 * �����ܣ�������ṹ��Ϣ�ؼ��ֲ�ѯ
            ����  : int 0 ��ʾ�ɹ�����������Ϊ����ʧ��
            ����  : TRUSERID *handle ���������ݵ�ͨѶ����˱�ʶ
            ����  : ST_PACK *rPack ҵ������������
            ����  : int *iRetCode �������ķ��ش��룬0��ʾ�ɹ����������Ǵ���ʧ�ܣ��ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ0
            ����  : char *szMsg �������ķ�����Ϣ���ڱ�ҵ����������֮ǰ���Ѿ�����ʼ��Ϊ��""
 * ----------------------------------------------------------
 * �޸�����: 2004-09-08 16��20
 * �޸���Ա: ����
 * �޸�����: �޸Ĺ淶
 * �汾��Ϣ��1.0.0.1
 * ��ע��Ϣ
 */

#include "busqc.h"
#include <string.h>
#include <stdio.h>
#include "pubfunc.h"
#include "errdef.h"
#include "pubdb.h"
#include "dictionary.h"
#include "cardstrut_stru.h"



int F820134(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	T_t_cardstrut acardstru;
	int v_id=0;
	int nrows=0;
	int r=0;
	
	ST_CPACK aPack;                                
	ST_PACK *out_pack = &(aPack.pack);
	SetCol(handle,F_LVOL3,F_LVOL4,F_LVOL5,F_LVOL6,F_LVOL7,F_LVOL8,F_LVOL9,F_USSET0,F_USSET1,0);
	
	memset(&acardstru,0,sizeof(acardstru));
	
	v_id = in_pack->lvol3;
	
	if(0 == v_id)
	{
		DB_t_cardstrut_open_select_by_c1();
		
		while(1){
			
			memset(&acardstru,0,sizeof(acardstru));
			
			r=DB_t_cardstrut_fetch_select_by_c1(&acardstru);
			if(0 != r)
			{
				if(SC_NOTFOUND==r)
				{
					if(0 == nrows)
					{
						*pRetCode=E_DB_CARDSTRUT_N;
						sprintf(szMsg,"��ѯ������ṹ��Ϣ���޼�¼,SQLCODE=%d\n",r);
						db_chk_err(__FILE__,__LINE__,&sqlca);
   						writelog(LOG_WARNING,szMsg);
						goto L_Ret_if;
					}
				}
				else
				{
					*pRetCode=E_DB_CARDSTRUT_R;
					sprintf(szMsg,"��ȡ������ṹ��Ϣ�����,SQLCODE=%d\n",r);
					db_chk_err(__FILE__,__LINE__,&sqlca);
   					writelog(LOG_WARNING,szMsg);
					goto L_Ret_if;
				}
				break;
			}
      	
      	out_pack->lvol3 =  acardstru.id;
      	out_pack->lvol4 =  acardstru.phytype;
      	out_pack->lvol5 =  acardstru.sectorno;
      	out_pack->lvol6 =  acardstru.blockno;
      	out_pack->lvol7 =  acardstru.begin_addr;
      	out_pack->lvol8 =  acardstru.end_addr;
      	out_pack->lvol9 =  acardstru.bytenum;
      	Strncpy_t((char*)out_pack->usset0,acardstru.define,sizeof(out_pack->usset0));
      	Strncpy_t((char*)out_pack->usset1,acardstru.comments,sizeof(out_pack->usset1));
      	
      	PutRow(handle,out_pack,pRetCode,szMsg); 
      	nrows++;             	
      				
      	if (15 == nrows)
      	{
      		// �������AnswerDataPart��Ϊ�˲���ǰ�˵ȴ�̫��ʱ�䣬����15����¼��ʱ��͸����أ����ں������ݾͲ��ù��ˣ�BCC��ǰ���Զ��Ὣ�������ݲɼ���ȥ
      		AnswerDataPart(handle,*pRetCode,szMsg);
      	}
   	};
   	
   	DB_t_cardstrut_close_select_by_c1();
   	return 0;
   	
   	L_Ret_if:
			DB_t_cardstrut_close_select_by_c1();
			return r;			
	}
	else{
		r=DB_t_cardstrut_read_by_id(v_id,&acardstru);
		if(SC_NOTFOUND==r)
		{
			*pRetCode=E_DB_CARDSTRUT_N;
			sprintf(szMsg,"������ṹ��Ϣ��������Ӧ��¼,SQLCODE=%d\n",r);
			db_chk_err(__FILE__,__LINE__,&sqlca);
      			writelog(LOG_ERR,szMsg);
			goto L_Ret_else;
		}
		else if(0!=r)
		{
			*pRetCode=E_DB_CARDSTRUT_R;
			sprintf(szMsg,"��������Ϣ���ȡ����,SQLCODE=%d\n",r);
                     db_chk_err(__FILE__,__LINE__,&sqlca);
      			writelog(LOG_ERR,szMsg);
			goto L_Ret_else;		
		}
		out_pack->lvol3 =  acardstru.id;
      out_pack->lvol4 =  acardstru.phytype;
      out_pack->lvol5 =  acardstru.sectorno;
      out_pack->lvol6 =  acardstru.blockno;
      out_pack->lvol7 =  acardstru.begin_addr;
      out_pack->lvol8 =  acardstru.end_addr;
      out_pack->lvol9 =  acardstru.bytenum;
      Strncpy_t((char*)out_pack->usset0,acardstru.define,sizeof(out_pack->usset0));
      Strncpy_t((char*)out_pack->usset1,acardstru.comments,sizeof(out_pack->usset1));
      
      PutRow(handle,out_pack,pRetCode,szMsg);
      
      return 0; 
      
      L_Ret_else:
			return r; 		
	}
}
