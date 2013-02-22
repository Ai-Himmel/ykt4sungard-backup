#include <stdlib.h>
#include <string.h>

#include "module_blk.h"
#include "kcc_util.h"
#include "drtpcall.h"

#define MAX_BLACK 128 << 1

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

static long kcc_get_func_no()
{
	return 400000;
}

static int kcc_request_cpack(struct kcc_server_config* svr,
							 ST_CPACK* rpack)
{
	char tmp[12] = "";
	blk_put_version(svr->server_no);
	rpack->head.RequestType = 940002;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	return 0;
}

static int kcc_format_header(struct kcc_server_config* svr,
							 char* buf,int len)
{
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
	char tmp[512] = "";
	struct blkversion_struct * p;
	int readlen;
	int flag;
	switch(pack->lvol3)
	{
	case 1:
		// 解挂
		flag = 0;
		break;
	case 0:
		// 挂失
		flag = 1;
		break;
	case 2:
		// 注销
		flag = 2;
		break;
	case 9:
		// 换卡
		flag = 9;
		break;
	default:
		return 0;
	}
	sprintf(tmp,"<card><phy-id>%s</phy-id><cardid>%d</cardid> \
			<stuempno>%s</stuempno><blk-version>%s</blk-version> \
			<flag>%d</flag></card>",pack->sname,pack->lvol2,pack->sname2,
			pack->sholder_ac_no,pack->lvol3);
	// 取得最大版本号
	if((p = blk_get_version(svr->server_no)) == NULL)
	{
		p = blk_put_version(svr->server_no);
	}
	if(kcc_strncmp(p->blkversion,pack->sholder_ac_no,
				   sizeof(p->blkversion)) < 0)
	{
		kcc_strncpy(p->blkversion,pack->sholder_ac_no,
					sizeof(p->blkversion));
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
	struct blkversion_struct * p;
	rpack->head.RequestType = 940003;
	rpack->head.recCount = 1;
	sprintf(tmp,"%d",svr->server_no);
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL0,tmp);
	sprintf(tmp,"%ld",kcc_get_func_no());
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_LVOL1,tmp);
	kcc_memclr(tmp,sizeof(tmp));
	if((p = blk_get_version(svr->server_no)) != NULL)
	{
		kcc_strcpy(tmp,p->blkversion);
		kcc_memclr(p->blkversion,sizeof(p->blkversion));
	}
	kcc_drtp_set_value(&rpack->head,&rpack->pack,F_SHOLDER_AC_NO,tmp);
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
	kcc_memclr(gs_blkver,sizeof(gs_blkver));
	gs_blk_count = 0;
	return 0;
}

static struct kcc_module_config module = 
{
	1,
	1,
	"1411",
	"20050713",
	"黑名单管理模块",
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
