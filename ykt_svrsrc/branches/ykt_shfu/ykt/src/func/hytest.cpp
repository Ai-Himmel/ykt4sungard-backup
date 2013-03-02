/* --------------------------------------------
 * 程序名称: 
 * 创建日期: 2008/08/11
 * 程序作者: 王彦兵
 * 版本信息: 1.0.0.0
 * 程序功能:  ceshi 
 * --------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include "pubdef.h"
#include "errdef.h"
#include "pubfunc.h"
#include "pubdb.h"
#include "dbfunc.h"
#include "dbfunc_foo.h"
#include "fdsqc.h"

static int do_calc_shop_balance(int shop_id,double * balance)
{
	int ret;
	double free_bala = 0;
	int rows;
	T_v_cif_shop_tree shop_node;
	T_t_aif_account account;
	T_t_cif_shop shop;

	printf("shop_tree_open_select_by_c1_and_shop_id[%d]\n",shop_id);
	ret = DB_v_cif_shop_tree_open_select_by_c1_and_shop_id(shop_id);
	if(ret)
	{
		printf("查询商户信息失败[%d]",ret);
		if(DB_NOTFOUND == 0)
			return E_SHOP_HAVE_SUB_NODE;
		else
			return E_DB_SHOP_R;
	}
	rows = 0;
	while(1)
	{
		memset(&shop_node,0,sizeof shop_node);
		printf("tree_fetch_select before\n");
		ret = DB_v_cif_shop_tree_fetch_select_by_c1(&shop_node);
		if(ret)
		{
			if(DB_NOTFOUND == ret)
			{
				if(rows > 0)
					break;
				else
					return E_FAN_SHOP_HAS_NO_LEAF;
			}
			return E_DB_SHOP_R;
		}
		printf("shop_tree_fetch_select_by_c1 ,shop_id[%d]\n",shop_node.leaf_id);
		rows++;
		memset(&shop,0,sizeof shop);
		printf("cif_shop_read before\n");
		ret = DB_t_cif_shop_read_by_shop_id(shop_node.leaf_id,&shop);
		if(ret)
		{
			DB_v_cif_shop_tree_close_select_by_c1();
			if(DB_NOTFOUND == ret)
				return E_DB_SHOP_N;
			else
				return E_DB_SHOP_R;
		}
		memset(&account,0,sizeof account);
		printf("aif_account_read before\n");
		ret = DB_t_aif_account_read_by_customer_id_and_act_type(
			shop.cut_id,ACCTYPE_SHOPMAIN,&account);
		if(ret)
		{
			DB_v_cif_shop_tree_close_select_by_c1();
			if(DB_NOTFOUND == ret)
				return E_DB_ACCOUNT_N;
			else
				return E_DB_ACCOUNT_R;
		}
		free_bala += account.last_bala;
		printf("free_bala[%f]\n",free_bala);
	}
	*balance = free_bala;
	printf("balance[%f]\n",*balance);
	return 0;
}

int main(int argc,char *argv[])
{
	int ret=0;
	char *p = NULL;
	char dbname[256]="";
	char dbuser[256]="";
	char dbpwd[256]="";
	int shop_id = 0;
	double balance = 0;
	int cnt = 0;


	openlog("COL_SERI",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL4);
	//打开数据库连接
	p=getenv("YKT_DBNAME");
	if(p==NULL)
	{
		perror("get ENV VAR YKT_DBNAME ERR\n");
		writelog(LOG_ERR,"get ENV VAR YKT_DBNAME ERR");
		exit(1);
	}
	des2src(dbname,p);
	p=getenv("YKT_USER");
	if(p==NULL)
	{
		perror("get ENV VAR YKT_USER ERR\n");
		writelog(LOG_ERR,"get ENV VAR YKT_USER ERR");
		exit(2);
	}
	des2src(dbuser,p);
	p=getenv("YKT_PWD");
	if(p==NULL)
	{
		perror("get ENV VAR YKT_PWD ERR\n");
		writelog(LOG_ERR,"get ENV VAR YKT_PWD ERR");
		exit(3);
	}
	des2src(dbpwd,p);

	while(1)
	{
		ret=db_connect(dbname,dbuser,dbpwd);
		if(ret)
		{
			db_chk_err(__FILE__,__LINE__,&sqlca);
			writelog(LOG_ERR,"connect to database err dbname[%s]",dbname);
			sleep(10);
			if(cnt<=3)
			{
				cnt++;
				continue;
			}
			else
			{
				printf("连接数据库失败!\n");
		      		return(-100);
			}
	   	}
		else
		{
			printf("连接数据库成功!\n");
			break;
		}
	}

	if(argc !=2)
	{
		printf("格式错误请输入商户号\n");
		goto L_RET;
	}
	else
	{
		shop_id = atoi(argv[1]);
		printf("商户号[%d]\n",shop_id);
	}
	ret=do_calc_shop_balance(shop_id, &balance);
	if(ret)
	{
		printf("do_calc_shop_balance ret[%d]\n",ret);
		goto L_RET;
	}

	printf("测试执行成功!\n");
L_RET:
	db_disconnect();
	closelog();
	return 0;
}
