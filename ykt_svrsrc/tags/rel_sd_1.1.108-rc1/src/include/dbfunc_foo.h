#ifndef _DBFUNC_FOO_H_
#define _DBFUNC_FOO_H_

#ifdef __cplusplus
extern "C" {
#endif
#include "pubdb.h"
#include "cpack.h"

#ifndef CHECK_DB_ERR
#define CHECK_DB_ERR  db_chk_err(__FILE__,__LINE__,&sqlca)
#endif

int process930105(int devid,int week);
int process930117NoDel(T_t_door_device_cardlist *cardlist,int addflag);
int Get_card_next_serial(int card_id,char *tx_date,int total_cnt,double *in_bala,double *out_bala);
int CheckGatewayDynKey(int sysid,char * dynKey);
int GetDevUsageByDevId(char * devid,int *usage);
int GetDevUsageById(int id,int *usage);
//�õ����������̻��ĸ������ܵ�Ӫҵ��
int GetSumCountIndepShop(double *sum,int *count);
//�õ�����Ա����һ����ֽ��ܺ�,ȥ���ֽ𻮲��ͳ������ײ���
int ReadFromOpenGroupAndRepOper(char *group_no,double *GroupCash);
/////////////////////////////////////////////////////////////////
/// ����ǩ��ʹ�õĺ���
int GetConferenceIDByDev(T_t_door_txdtl* tTxdtl,int *conf,char sign[1]);
int SaveConferenceSerial(T_t_door_txdtl* tTxdtl,int conf,int custid,char sign);

int queryCustidAndExpTime(const char* phyid,int state,int * custid,T_tab_card_info* cardinfo);

int CheckOperatorPwd(const char* operator,const char* pwd);
int CheckShopMealTypeConflict();

int is_oper_has_authcard(char operator[11]);

#ifdef __cplusplus
}
#endif

#endif // _DBFUNC_FOO_H_
