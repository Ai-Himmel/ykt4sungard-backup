#include <stdlib.h>
#include <string.h>
/** 
 * 模块名					查询卡信息
 * 文件名					cardinfo.h
 * 文件实现功能				查询卡信息名单头文件
 * 作者						李翔
 * 版本						V0.1
 * 日期						2007-06-05
 * 备注
 * $Id$
 */
#include "cardinfo.h"
#include "kcc_util.h"
#include "drtpcall.h"

#define MAX_BLACK 128 << 1

static char gs_MaxVolume[13] = "";

static long kcc_get_func_no()
{
	return 400004;
}

static int kcc_request_cpack(struct kcc_server_config* svr,
							 ST_CPACK* rpack)
{
	char tmp[12] = "";
	rpack->head.RequestType = 940010;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	sprintf(tmp,"%d",1);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL6,tmp);
	/*
	char tmp[12] = "";
	rpack->head.RequestType = 847173;
//	sprintf(tmp,"%d",svr->server_no);
	sprintf(tmp,"%d",022027172);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
//	sprintf(tmp,"%ld",kcc_get_func_no());
//	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	*/
	return 0;
}

static int kcc_send_third_part_cpack(struct kcc_server_config* svr,
							 		 ST_CPACK* rpack, ST_PACK *tmp_pack)
{
	char tmp[21] = "";
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SCUST_NO, tmp_pack->scust_no);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_VSVARSTR0, tmp_pack->vsvarstr0);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SNAME2, tmp_pack->sname2);
	sprintf(tmp, "%d", tmp_pack->lvol2);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL2, tmp);
	sprintf(tmp, "%d", tmp_pack->lvol5);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL5, tmp);
	sprintf(tmp, "%d", tmp_pack->lvol6);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL6, tmp);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_VSVARSTR1, tmp_pack->vsvarstr1);
	sprintf(tmp, "%d", tmp_pack->lvol7);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL7, tmp);
	sprintf(tmp, "%d", tmp_pack->lvol8);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL8, tmp);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SCUST_AUTH, tmp_pack->scust_auth);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SPOST_CODE, tmp_pack->spost_code);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SPHONE3, tmp_pack->sphone3);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SPAGER, tmp_pack->spager);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SEMAIL, tmp_pack->semail);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SSTATUS2, tmp_pack->sstatus2);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SNAME, tmp_pack->sname);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SHOLDER_AC_NO, tmp_pack->sholder_ac_no);
    sprintf(tmp, "%d", -1);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL9, tmp);
    sprintf(tmp, "%d", tmp_pack->lvol10);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_LVOL10, tmp);
	sprintf(tmp, "%lf", tmp_pack->damt0);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_DAMT0, tmp);
	sprintf(tmp, "%lf", tmp_pack->damt1);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_DAMT1, tmp);
	kcc_drtp_set_value(&rpack->head, &rpack->pack, F_SCERT_NO, tmp_pack->scert_no);
	
	// 取得最大版本
	if(kcc_strncmp(tmp_pack->sholder_ac_no,gs_MaxVolume,sizeof gs_MaxVolume) > 0)
	{
		kcc_strncpy(gs_MaxVolume,tmp_pack->sholder_ac_no,sizeof gs_MaxVolume);
	}
	return 0;
}

static int kcc_format_header(struct kcc_server_config* svr,
							 char* buf,int len)
{
	return 0;
}


static int kcc_format_tail(struct kcc_server_config * svr,
						   char *buf,int len)
{
	return 0;
}


static int kcc_recv_third_part_cpack(ST_CPACK* rpack,
								 struct kcc_server_config* svr,
								 ksf_card_result* ret)
{
	return 0;
}

static int kcc_format_cpack(struct kcc_server_config * svr,
							ST_PACK* pack, char* buf,int len)
{
	/*
	char tmp[20] = "";
	rpack->head.RequestType = 940003;
	rpack->head.recCount = 1;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_SHOLDER_AC_NO,gs_MaxVolume);
	kcc_write_log(LOG_DEBUG,"server[%d]version[%s]",rpack->pack.lvol0,
				  rpack->pack.sholder_ac_no);
	*/
	return 0;
}

static int kcc_make_return_cpack(ST_CPACK* rpack,
								 struct kcc_server_config* svr,
								 ksf_card_result* ret)
{
	char tmp[20] = "";
	rpack->head.RequestType = 940003;
	rpack->head.recCount = 1;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_SHOLDER_AC_NO,gs_MaxVolume);
	kcc_write_log(LOG_DEBUG,"server[%d]version[%s]",rpack->pack.lvol0,
				  rpack->pack.sholder_ac_no);
	return 0;
}

static kcc_module_type kcc_get_module_type()
{
	return KMT_PER_SVR;
}

static int kcc_load_module()
{
	kcc_memclr(gs_MaxVolume,sizeof gs_MaxVolume);
	return 0;
}

static struct kcc_module_config module = 
{
	1,
	1,
	"1411",
	"20070615",
	"卡状态更新模块",
	kcc_load_module,
	NULL,
	kcc_get_func_no,
	kcc_request_cpack,
	kcc_format_header,
	kcc_format_tail,
	kcc_send_third_part_cpack,
	kcc_recv_third_part_cpack,
	kcc_format_cpack,
	kcc_make_return_cpack,
	kcc_get_module_type
};

int kcc_get_module_info(struct kcc_module_config * c)
{
	memcpy(c,&module,sizeof(kcc_module_config));
	return 0;
}
