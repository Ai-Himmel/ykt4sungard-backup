#ifndef __DB_PUB_INCLUDE__
#define __DB_PUB_INCLUDE__
#ifdef __cplusplus
extern "C" {
#endif
#include <sql.h>
#include <sqlca.h>
#include "account_stru.h"
#include "actdaysum_stru.h"
#include "authcard_stru.h"
#include "bankcomp_stru.h"
#include "blacksht_stru.h"
#include "cadlosinf_stru.h"
#include "card_stru.h"
#include "cardlist_stru.h"
#include "cardstrut_stru.h"
#include "cfgsplit_stru.h"
#include "cfgtxfee_stru.h"
#include "coshis_stru.h"
#include "cursyspara_stru.h"
#include "customer_stru.h"
#include "customtmp_stru.h"
#include "cutinfoupd_stru.h"
#include "cutrelation_stru.h"
#include "cutrltntmp_stru.h"
#include "cuttypefee_stru.h"
#include "dept_stru.h"
#include "device_stru.h"
#include "devworktime_stru.h"
#include "difftransfer_stru.h"
#include "doordevhld_stru.h"
#include "doorholiday_stru.h"
#include "feetype_stru.h"
#include "group_stru.h"
#include "groupmem_stru.h"
#include "histrlog_stru.h"
#include "histrserial_stru.h"
#include "meslist_stru.h"
#include "operright_stru.h"
#include "photo_stru.h"
#include "phototmp_stru.h"
#include "phydevice_stru.h"
#include "rcvdtl_stru.h"
#include "rptactive_stru.h"
#include "rptbanktransfer_stru.h"
#include "rptcardbalance_stru.h"
#include "rpterr_stru.h"
#include "rptoper_stru.h"
#include "rptrichdebt_stru.h"
#include "rptshpbalance_stru.h"
#include "rpttranscomp_stru.h"
#include "savdtl_stru.h"
#include "sbparams_stru.h"
#include "shp_stru.h"
#include "shppos_stru.h"
#include "shpposlog_stru.h"
#include "spefee_stru.h"
#include "subbalance_stru.h"
#include "subject_stru.h"
#include "subsidy_stru.h"
#include "subsidytmp_stru.h"
#include "subslog_stru.h"
#include "subsys_stru.h"
#include "subupd_stru.h"
#include "syskey_stru.h"
#include "tradelog_stru.h"
#include "tradeserial_stru.h"
#include "trdcdshp_stru.h"
#include "txdtl_stru.h"
#include "v1rptcar_stru.h"
#include "v2rpterr_stru.h"
#include "vrptactive_stru.h"
#include "vrptoper_stru.h"
#include "vrpttot_stru.h"
#include "vshpdptfee_stru.h"
#include "warrant_stru.h"
#include "waterinf_stru.h"
extern int g_dbchkerr;
void db_trim(char *str);
int db_chk_err(char file[],int line,struct sqlca *caPointer);
int db_connect(char *v_dbname,char *v_user,char *v_passwd);
int db_disconnect();
int db_commit();
int db_rollback();
int DynamicStmtExecute(char *stmt);
#ifdef __cplusplus
}
#endif
#endif
