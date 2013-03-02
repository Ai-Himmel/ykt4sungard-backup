#include <string.h>
#include <stdio.h>
#include "errdef.h"
#include "pubdb.h"
#include "pubfunc.h"
#include "fdsqc.h"
#include "dbfunc_foo.h"
#include "dbfunc.h"

#include "bank_account.h"

// 工商银行，上海分行接口
static int icbc_write_head(settle_account_head_t *head)
{
	char data_buf[512];
	char temp[256] = "";
	int len,offset,ret;
	int i_bala;

	offset = 0;
	// 标志 1字节
	data_buf[offset++] = 'F';
	// 委托单位代码,5字节
	//ret = GetParameter(GLOBAL_ISBP_ENTRUST_CODE,temp);
	//memcpy(data_buf+offset,temp,5);
	memcpy(data_buf+offset,head->trans_no,5);
	offset+=5;
	// 业务代理编号后两位
	memset(temp,0,sizeof temp);
	/*
	ret = GetParameter(GLOBAL_ISBP_CREBIT_CODE,temp);
	if(ret)
		return ret;
	*/
	sprintf(temp,"%.05d",head->trans_code);
	len = strlen(temp);
	if(len < 2)
		return E_SYSPARAM_ERROR; // 业务代码小于 2 字节
	memcpy(data_buf+offset,temp+len-2,2);
	offset+=2;
	// 批号 5字节
	//ret = get_isbp_serial_no(bala_date,temp);
	//if(ret)
	//	return ret;
	sprintf(temp,"%.05d",head->serial_no);
	memcpy(data_buf+offset,temp,5);
	offset+=5;
	// 委托单位帐号,20字节
	memset(temp,0,sizeof temp);
	//ret = GetParameter(GLOBAL_ISBP_BANKCODE,temp);
	//if(ret)
	//	return ret;
	des2src(temp,head->bank_account);
	len = strlen(temp);
	if(len <= 20)
		memcpy(data_buf+offset,temp,len);
	else
		return E_SYSPARAM_ERROR; // 账号长度超过 20 字节
	if(len < 20)
		memset(data_buf+offset+len,' ',20-len);
	offset+=20;

	// 借方金额合计 15
	i_bala = D2I(head->debit_money*100.0);
	sprintf(data_buf+offset,"%.015d",i_bala);
	offset+=15;
	// 借方笔数合计 6
	if(head->debit_count > 999999)
		return E_QUERY_RECORDS_EXCEED; // 记录数太多
	sprintf(data_buf+offset,"%.06d",head->debit_count);
	offset+=6;
	// 贷方金额合计 15
	i_bala = D2I(head->credit_money*100);
	sprintf(data_buf+offset,"%.015d",i_bala);
	offset+=15;
	// 贷方笔数合计 6
	if(head->credit_count > 999999)
		return E_QUERY_RECORDS_EXCEED; // 记录数太多
	sprintf(data_buf+offset,"%.06d",head->credit_count);
	offset+=6;

	// 委托日期 8字节
	memcpy(data_buf+offset,head->account_date,8);
	offset+=8;
	// 单位名称 40字节
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
	// 换行
	data_buf[offset++] = '\n';
	//
	//writelog(LOG_ERR,"头:%s",data_buf);
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
	// 起始标志
	data_buf[offset++] = 'T';
	// 银行账号, 20字节
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
		// 不空格
		memset(data_buf+offset,' ',20-len);
		offset += 20-len;
	}
	// 金额 单位分 , 15字节
	i_bala = D2I(detail->account_money*100.0);
	sprintf(data_buf+offset,"%.015d",i_bala);
	offset += 15;
	// 借贷标志, 0 贷 1 借
	data_buf[offset++] = (detail->debit_flag == IS_YES) ? '1' : '0';
	// 受托日期
	memcpy(data_buf+offset,detail->account_date,8);
	offset+=8;
	// 原委托日期
	memcpy(data_buf+offset,detail->account_date,8);
	offset+=8;
	//帐户名,40字节
	des2src(temp,detail->account_name);
	len = strlen(temp);
	if(len <= 40)
		memcpy(data_buf+offset,temp,len);
	if(len < 40)
		memset(data_buf+offset+len,' ',40-len);
	offset+=40;
	// 入账标识
	data_buf[offset++] = '0';
	strcpy(data_buf+offset,detail->comments);
	offset+=strlen(detail->comments);
	// 换行
	data_buf[offset++] = '\n';
	//writelog(LOG_ERR,"内容:%s",data_buf);
	if(fwrite(data_buf,offset,1,detail->fp)==1)
		return 0;

	return E_FILE_ACCESS;
}

// 写头信息
int bank_account_write_head(settle_account_head_t *head)
{
	if(head->bank_code == BANK_CODE_ICBC_SH)
		return icbc_write_head(head);
	return E_ACCOUNT_NOT_SUPPORT;
}

// 写明细信息
int bank_account_write_detail(settle_account_t *detail)
{
	if(detail->bank_code == BANK_CODE_ICBC_SH)
		return icbc_write_detail(detail);
	return E_ACCOUNT_NOT_SUPPORT;
}

