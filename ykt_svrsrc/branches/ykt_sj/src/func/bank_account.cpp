#include <string.h>
#include <stdio.h>
#include "errdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "dbfunc.h"

#include "bank_account.h"

// �������У��Ϻ����нӿ�
static int icbc_write_head(settle_account_head_t *head)
{
	char data_buf[512];
	char temp[256] = "";
	int len,offset,ret;
	int i_bala;

	offset = 0;
	// ��־ 1�ֽ�
	data_buf[offset++] = 'F';
	// ί�е�λ����,5�ֽ�
	//ret = GetParameter(GLOBAL_ISBP_ENTRUST_CODE,temp);
	//memcpy(data_buf+offset,temp,5);
	memcpy(data_buf+offset,head->trans_no,5);
	offset+=5;
	// ҵ������ź���λ
	memset(temp,0,sizeof temp);
	/*
	ret = GetParameter(GLOBAL_ISBP_CREBIT_CODE,temp);
	if(ret)
		return ret;
	*/
	sprintf(temp,"%.05d",head->trans_code);
	len = strlen(temp);
	if(len < 2)
		return E_SYSPARAM_ERROR; // ҵ�����С�� 2 �ֽ�
	memcpy(data_buf+offset,temp+len-2,2);
	offset+=2;
	// ���� 5�ֽ�
	//ret = get_isbp_serial_no(bala_date,temp);
	//if(ret)
	//	return ret;
	sprintf(temp,"%.05d",head->serial_no);
	memcpy(data_buf+offset,temp,5);
	offset+=5;
	// ί�е�λ�ʺ�,20�ֽ�
	memset(temp,0,sizeof temp);
	//ret = GetParameter(GLOBAL_ISBP_BANKCODE,temp);
	//if(ret)
	//	return ret;
	des2src(temp,head->bank_account);
	len = strlen(temp);
	if(len <= 20)
		memcpy(data_buf+offset,temp,len);
	else
		return E_SYSPARAM_ERROR; // �˺ų��ȳ��� 20 �ֽ�
	if(len < 20)
		memset(data_buf+offset+len,' ',20-len);
	offset+=20;

	// �跽���ϼ� 15
	i_bala = D2I(head->debit_money*100.0);
	sprintf(data_buf+offset,"%.015d",i_bala);
	offset+=15;
	// �跽�����ϼ� 6
	if(head->debit_count > 999999)
		return E_QUERY_RECORDS_EXCEED; // ��¼��̫��
	sprintf(data_buf+offset,"%.06d",head->debit_count);
	offset+=6;
	// �������ϼ� 15
	i_bala = D2I(head->credit_money*100);
	sprintf(data_buf+offset,"%.015d",i_bala);
	offset+=15;
	// ���������ϼ� 6
	if(head->credit_count > 999999)
		return E_QUERY_RECORDS_EXCEED; // ��¼��̫��
	sprintf(data_buf+offset,"%.06d",head->credit_count);
	offset+=6;

	// ί������ 8�ֽ�
	memcpy(data_buf+offset,head->account_date,8);
	offset+=8;
	// ��λ���� 40�ֽ�
	//ret = GetParameter(GLOBAL_ISBP_NAME,temp);
	//if(ret)
	//	return ret;
	des2src(temp,head->account_name);
	len = strlen(temp);
	if(len <= 40)
		memcpy(data_buf+offset,temp,len);
	if(len < 40)
		memset(data_buf+offset+len,' ',40-len);
	offset += 40;
	// ����
	data_buf[offset++] = '\n';
	//
	//writelog(LOG_ERR,"ͷ:%s",data_buf);
	if(fwrite(data_buf,offset,1,head->fp) == 1)
		return 0;
	return E_FILE_ACCESS;
}

static int icbc_write_detail(settle_account_t *detail)
{
	//
	char data_buf[512];
	int len,offset;
	int i_bala;
	char temp[41] = "";

	offset=0;
	// ��ʼ��־
	data_buf[offset++] = 'T';
	// �����˺�, 20�ֽ�
	len = strlen(detail->bank_account);
	if(len > 20)
	{
		memcpy(data_buf+offset,detail->bank_account,20);
		offset += 20;
	}
	else
	{
		memcpy(data_buf+offset,detail->bank_account,len);
		offset += len;
		// ���ո�
		memset(data_buf+offset,' ',20-len);
		offset += 20-len;
	}
	// ��� ��λ�� , 15�ֽ�
	i_bala = D2I(detail->account_money*100.0);
	sprintf(data_buf+offset,"%.015d",i_bala);
	offset += 15;
	// �����־, 0 �� 1 ��
	data_buf[offset++] = (detail->debit_flag == IS_YES) ? '1' : '0';
	// ��������
	memcpy(data_buf+offset,detail->account_date,8);
	offset+=8;
	// ԭί������
	memcpy(data_buf+offset,detail->account_date,8);
	offset+=8;
	//�ʻ���,40�ֽ�
	des2src(temp,detail->account_name);
	len = strlen(temp);
	if(len <= 40)
		memcpy(data_buf+offset,temp,len);
	if(len < 40)
		memset(data_buf+offset+len,' ',40-len);
	offset+=40;
	// ���˱�ʶ
	data_buf[offset++] = '0';
	strcpy(data_buf+offset,detail->comments);
	offset+=strlen(detail->comments);
	// ����
	data_buf[offset++] = '\n';
	//writelog(LOG_ERR,"����:%s",data_buf);
	if(fwrite(data_buf,offset,1,detail->fp)==1)
		return 0;

	return E_FILE_ACCESS;
}

// дͷ��Ϣ
int bank_account_write_head(settle_account_head_t *head)
{
	if(head->bank_code == BANK_CODE_ICBC_SH)
		return icbc_write_head(head);
	return E_ACCOUNT_NOT_SUPPORT;
}

// д��ϸ��Ϣ
int bank_account_write_detail(settle_account_t *detail)
{
	if(detail->bank_code == BANK_CODE_ICBC_SH)
		return icbc_write_detail(detail);
	return E_ACCOUNT_NOT_SUPPORT;
}

