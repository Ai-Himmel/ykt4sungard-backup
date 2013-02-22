/** 
 * 模块名				更新客户信息名单模块
 * 文件名				newcard.c
 * 文件实现功能			更新客户信息时生成的名单
 * 作者					汤成
 * 版本					V0.1
 * 日期					2005-09-05
 * 备注
 * $Id$
 */

#include <stdlib.h>
#include <string.h>

#include "newcard.h"
#include "kcc_util.h"
#include "drtpcall.h"

#define MAX_BLACK 128 << 1

static char gs_MaxVolume[13] = "";
/*
static struct blkversion_struct
{
	int server;
	char blkversion[20];
	struct blkversion_struct * next;
}gs_blkver[MAX_BLACK];

static int gs_blk_count = 0;

static struct blkversion_struct* blk_get_version(int server)
{
	int i;
	for(i = 0;i < gs_blk_count;++i)
	{
		if(gs_blkver[i].server == server)
		{
			return &gs_blkver[i];
		}
	}
	return NULL;
}

static struct blkversion_struct* blk_put_version(int server)
{
	int i;
	for(i = 0;i < gs_blk_count;++i)
	{
		if(gs_blkver[i].server == server)
		{
			return &gs_blkver[i];
		}
	}
	gs_blkver[gs_blk_count].server = server;
	kcc_memclr(gs_blkver[gs_blk_count].blkversion,
			   sizeof(gs_blkver[gs_blk_count].blkversion));
	gs_blk_count++;
	return &gs_blkver[gs_blk_count-1];
}
*/

static long kcc_get_func_no()
{
	return 400002;
}

static int kcc_request_cpack(struct kcc_server_config* svr,
							 ST_CPACK* rpack)
{
	char tmp[12] = "";
	//blk_put_version(svr->server_no);
	rpack->head.RequestType = 940004;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	sprintf(tmp,"%d",2);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL6,tmp);
	return 0;
}

static int kcc_format_header(struct kcc_server_config* svr,
							 char* buf,int len)
{
	kcc_memclr(gs_MaxVolume,sizeof gs_MaxVolume);
	kcc_strcpy(buf,"<card-info>");
	return kcc_strlen("<card-info>");
}

static int kcc_format_tail(struct kcc_server_config * svr,
						   char *buf,int len)
{
	kcc_strcpy(buf,"</card-info>");
	return kcc_strlen("</card-info>");
}

static int kcc_format_cpack(struct kcc_server_config * svr,
							ST_PACK* pack, char* buf,int len)
{
	char tmp[1024] = "";
	//struct blkversion_struct * p;
	int readlen;
	//int flag;
	sprintf(tmp,"<card><name>%s</name><card-id>%d</card-id><phy-id>%s</phy-id>"\
			"<stuemp>%s</stuemp><dept>%s</dept>"\
			"<dname>%s</dname><spc-fld>%s</spc-fld><exp-date>%s</exp-date><sex>%d</sex>"\
			"<cut-type>%d</cut-type><ctname>%s</ctname><date>%s</date>"\
			"<fee-type>%d</fee-type><flag>%d</flag></card>",
			pack->vsvarstr2,
			pack->lvol2,pack->sname,pack->sname2,pack->scust_no,pack->vsvarstr0,pack->scust_auth,
			pack->sdate0,pack->lvol3,pack->lvol4,pack->vsvarstr1,pack->sdate1,pack->lvol5,0);
	// 取得最大版本
	if(kcc_strncmp(pack->sholder_ac_no,gs_MaxVolume,sizeof gs_MaxVolume) > 0)
	{
		kcc_strncpy(gs_MaxVolume,pack->sholder_ac_no,sizeof gs_MaxVolume);
	}
	readlen = len > kcc_strlen(tmp) ? kcc_strlen(tmp):len;
	kcc_strncpy(buf,tmp,readlen);
	return readlen;
}
static int kcc_make_return_cpack(ST_CPACK* rpack,
								 struct kcc_server_config* svr,
								 ksf_card_result* ret)
{
	char tmp[20] = "";
	//struct blkversion_struct * p;
	rpack->head.RequestType = 940003;
	rpack->head.recCount = 1;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	/*
	kcc_memclr(tmp,sizeof(tmp));
	if((p = blk_get_version(svr->server_no)) != NULL)
	{
		kcc_strcpy(tmp,p->blkversion);
		kcc_memclr(p->blkversion,sizeof(p->blkversion));
	}
	*/
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
	"20050713",
	"更新客户信息",
	kcc_load_module,
	NULL,
	kcc_get_func_no,
	kcc_request_cpack,
	kcc_format_header,
	kcc_format_tail,
	kcc_format_cpack,
	kcc_make_return_cpack,
	kcc_get_module_type
};

int kcc_get_module_info(struct kcc_module_config * c)
{
	memcpy(c,&module,sizeof(kcc_module_config));
	return 0;
}
