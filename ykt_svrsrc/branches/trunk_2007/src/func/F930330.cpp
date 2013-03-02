/* ----------------------------------------------------------
 * 程序名称：F900330.cpp
 * 创建日期：2008-10-21
 * 程序作者：hlq
 * 版本信息：1.0.0.0
 * 程序功能：生成车库管理系统对接文件(客户信息)
 * ----------------------------------------------------------
 */


#define _IN_SQC_
ESQL #include <string.h>
ESQL #include <stdio.h>
ESQL #include "errdef.h"
ESQL #include "pubdb.h"
ESQL #include "pubfunc.h"
ESQL #include "fdsqc.h"
ESQL #include "dbfunc_foo.h"
ESQL #include "dbfunc.h"
ESQL #include "bank_account.h"


static settle_account_head_t g_bank_head;
static int g_trade_flag = 0;
static FILE *g_filep = NULL;
static char g_bala_begin[9];
static char g_bala_end[9];


static int select_customer_info(char *cut_type){
	EXEC SQL BEGIN DECLARE SECTION;
	char hi_cut_type[60]="";
	char ho_physical_no[40+1] = "";
	char ho_stuemp_no[21]="";
	char ho_cut_name[60+1]="";
	char ho_dept_name[100+1]=""
	sqlint16	indication=0;
	EXEC SQL END DECLARE SECTION;

	int ret=0;
	int nrows = 0,i;
	int customer_array_len = 64;
	int *customer_array = NULL;


	des2src(hi_cut_type,*cut_type);


	EXEC SQL DECLARE customer_cur CURSOR FOR
	select t.physical_no,s.stuemp_no,s.cut_name,r.dept_name 
	from t_cif_customer s 
	left join t_pif_card t on t.cosumer_id=s.cut_id 
	left join t_cif_dept r on s.classdept_no=r.dept_code 
	where s.cut_type in (:hi_cut_type) and t.state_id<>'2000'
	order by s.stuemp_no;

	if(SQLCODE)
	{
		CHECK_DB_ERR;
		return E_DB_CURSOR_DECLARE;
	}

	EXEC SQL OPEN customer_cur;
	if(SQLCODE)
	{
		CHECK_DB_ERR;
		return E_DB_CURSOR_OPEN;
	}
	customer_array = (int *)malloc(customer_array_len);
	while(1)
	{
		// 初始化宿主变量
		memset(ho_physical_no , 0, sizeof(ho_physical_no));
		memset(ho_stuemp_no,0,sizeof ho_stuemp_no);
		memset(ho_cut_name,0,sizeof ho_cut_name);
		memset(ho_dept_name,0,sizeof ho_dept_name);
		

		EXEC SQL FETCH customer_cur INTO
			:ho_physical_no:indication,
			:ho_stuemp_no:indication,
			:ho_cut_name:indication,
			:ho_dept_name:indication,

		ret=SQLCODE;
		if (ret)
		{
			CHECK_DB_ERR;
			EXEC SQL  CLOSE customer_cur;
			if(DB_NOTFOUND==ret)
			{
				if(0==nrows)
				{
					writelog(LOG_DEBUG,"fetch customer info no data [%d]",ret);
					break;
				}
				else
					break;
			}
			else
			{
				writelog(LOG_ERR,"fetch customer info err [%d]",ret);
				free(customer_array);
				return E_DB_T_REPORT_SHOP_BALANCE_R;
			}
		}

	

	}
}


int F900330(TRUSERID *handle,int iRequest,ST_PACK *in_pack,int *pRetCode,char *szMsg)
{
	char cut_type[60]="";
	char sysdatetime[16] = "";
	char full_path[512]="";
	char file_name[128]="";
	

	char hi_operator[10+1]="";
	char entrust_code[256]="";

	char serial_no[10] = "";
	char logic_date[9] = "";
	int trade_flag = 0;
	ST_CPACK aPack;
	ST_PACK *out_pack;
	settle_account_t detail;

	int i=0;
	int ret=0;
	int head_len=0;
	//char * pch;

	// 准备处理结果中在ST_PACK中使用的字段

	des2src(hi_operator, in_pack->scust_no);
	GetLogicDate(logic_date);
	g_trade_flag = in_pack->lvol0;

	memset(&g_bank_head,0,sizeof g_bank_head);

	

	// 
	ret = GetParameter(20001,cut_type);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}

	 getsysdatetime(sysdatetime);
	
	// 下载路径
	ret = GetParameter(GLOBAL_DOWNLOAD_PATH,full_path);
	if(ret)
	{
		*pRetCode = ret;
		goto L_RETU;
	}
	strcat(full_path,"/");
	sprintf(file_name,"CUSTINFO%s.txt",sysdatetime);
	strcat(full_path,file_name);
	if((g_filep = fopen(full_path,"wb"))==NULL)
	{
		sprintf(szMsg,"can't write file [%s]",full_path);
		*pRetCode = E_FILE_ACCESS;
		goto L_RETU;
	}
	//g_bank_head.fp = g_filep;
	// 执行业务


	// 先写一次头, 预留空间
	if((ret = bank_account_write_head(&g_bank_head))==0)
	{
		des2src(detail.account_date,g_bank_head.account_date);
		// 查询数据
		if((ret = select_by_shop_balance(1,&detail)) == 0)
		{
			fseek(g_filep,SEEK_SET,0L);
			// 重写一次头
			ret = bank_account_write_head(&g_bank_head);
		}
	}

	fclose(g_filep);
	g_filep = NULL;

	if(ret)
	{
		writelog(LOG_ERR,"生成 ISBP 报盘文件失败!ret[%d]",ret);
		*pRetCode = ret;
		goto L_RETU;
	}
	writelog(LOG_DEBUG,"generate isbp file success,date[%s],operator[%s],serial_no[%d]",
			 g_bank_head.account_date,hi_operator,g_bank_head.serial_no);
	out_pack = &(aPack.pack);
	memset(&aPack,0,sizeof aPack);
	SetCol(handle,0);
	SetCol(handle,F_LVOL0,F_DAMT0,F_LVOL1,F_DAMT1,F_VSVARSTR0,0);
	out_pack->lvol0 = g_bank_head.debit_count;
	out_pack->damt0 = g_bank_head.debit_money;
	out_pack->lvol1 = g_bank_head.credit_count;
	out_pack->damt1 = g_bank_head.credit_money;
	des2src(out_pack->vsvarstr0,file_name);
	PutRow(handle,out_pack,pRetCode,szMsg);
	return 0;

L_RETU:
	return -1;
}




