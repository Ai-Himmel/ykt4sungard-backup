/* --------------------------------------------
 * ��������: 2011-03-08
 * ��������: ������
 * �汾��Ϣ: 1.0.0.0
 * ������: �̻����ѷֳɱ�(T_SHOPBOARDFEE)��ѯ�����룬ɾ��
 * --------------------------------------------*/
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdio.h>
 #include <string.h>
 #include <string>
 #include <sstream>	
 #include "pubfunc.h"
 #include "pubdb.h"
 #include "pubdef.h"
 #include "errdef.h"
 #include "dbfunc.h"
 #include "busqc.h"
 #include "dbfunc_foo.h"


int F851004(TRUSERID *handle,int iRequest,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	// �������
	if(rPack->lvol0<=0)
	{
		return E_INPUT_DATA_INVAILD;
	}

	// ��ȡ�̻���
	T_t_merch t_merch;
	memset(&t_merch,0,sizeof(t_merch));
	
	int ret=DB_t_merch_read_by_merchid(rPack->lvol0,&t_merch);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCH_N;
		else
			return E_DB_MERCH_R;
	}

	// ��ȡ��ֵ�̻�������
	T_t_merchpara t_merchpara ;
	memset(&t_merchpara,0,sizeof(t_merchpara));

	ret = DB_t_merchpara_read_by_merchid(rPack->lvol0, &t_merchpara);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHPARA_N;
		else
			return E_DB_MERCHPARA_R;
	}

	// ��ȡ��ֵ�̻�������
	T_t_merchwork t_merchwork ;
	memset(&t_merchwork,0,sizeof(t_merchwork));

	ret=DB_t_merchwork_read_by_merchid(rPack->lvol0,&t_merchwork);
	if(ret)
	{
		if(DB_NOTFOUND==ret)
			return E_DB_MERCHWORK_N;
		else
			return E_DB_MERCHWORK_R;
	}

 	// ������Ϣ
	ST_CPACK aPack;
	ST_PACK *outPack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0, F_LVOL1, F_LVOL2, F_LVOL3, F_LVOL4, F_LVOL5, F_LVOL6, F_SBANKNAME,0);
	
	outPack->lvol0 = rPack->lvol0;//��ֵ�̻����
	outPack->lvol1 = t_merchpara.czamtmax;//�̻�������ֵ���
	outPack->lvol2 = t_merchwork.czamt;//��ǰ���
	outPack->lvol3 = t_merchpara.czamtmax + t_merchwork.czamt;//���ö��
	outPack->lvol4 = t_merchwork.czamt < 0 ? -t_merchwork.czamt:0; // ��ǰӦ����
	outPack->lvol5 = t_merchpara.paydate;//���ɿ����� 
	outPack->lvol6 = t_merchpara.billdate;//ÿ���̻��˵���
	des2src(outPack->sbankname,t_merch.merchname); // �̻���

 	PutRow(handle,outPack,pRetCode,szMsg); 
	AnswerData(handle,*pRetCode,szMsg);
	return 0;
}


