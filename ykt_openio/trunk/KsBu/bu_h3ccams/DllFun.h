/********************************************************
* 文件内容: 实现与第三方对接时候进行动态加载动态库
* 文件名:	DllFun.h
* 说明:		动态加载数据结构在此,静态加载由第三方给出.h文件
* 创建:		李翔
* 时间:		2007-07-02
* 修改原因: 
**********************************************************/

#ifndef _DLL_FUN_H_
#define _DLL_FUN_H_
#pragma once

#include "DllFunErrCode.h"
#include "PersonInfoApi.h"
#include <Windows.h>

#ifndef _DYNAMIC_LOAD		// 声明动态加载第三方动态库		
#define _DYNAMIC_LOAD
#endif

#ifndef SYNJONES_FUNC		// 声明加载新中新函数		
#define SYNJONES_FUNC
#endif

#ifdef __cplusplus
extern "C" {
#endif

/************************************************************************/
/* 对接第三方名单信息结构                                          
/************************************************************************/
#pragma pack(1)
typedef struct _Data_Info 
{
	int      cut_id;                //客户ID号
	char	 physical_no[9];		//物理卡号
	char	 old_physical_no[9];	//老物理卡号(换卡的时候将老物理卡号传出)
	int		 card_state;			//卡状态, 将state_id和card_flag归结到一个标志上
	int      cut_type;				//客户类别, 客户的身份, 本科对应11, 研究生对应13等等
	char     cut_type_name[51];		//客户类别名称, 本科生, 研究生这样
	char	 cut_name[61];			//客户姓名
	char     volume[13];			//更新版本号(070403102045), 一卡通数据库总是取最新的版本号的数据传送给贵方，例如我方发现有人挂失，state_id字段发生变化，则会将此人的版本号增大，然后发送的时候以这个最大的版本号所标识的记录来发送给对方.
	char 	 classdept_name[101];	//联系人部门名称, 生物系,化学系等等
	char 	 stuemp_no[21];			//学工号
	char	 sex[2];				//性别(1为男, 2为女)
	int  	 card_id;				//交易卡号
	int 	 type_id;				//卡类别: (1正式卡, 2临时卡, 3非记名临时
									//卡, 4VIP记名临时卡, 5记名临时卡)
	char 	 show_id[11];			//显示卡号	
	int      area;					//客户所在区域
	char     area_name[51];			//客户所在区域
	char	 main_id[21];			//身份证号
	char	 reg_time[31];			//用户注册时间
	char	 can_time[31];			//用户注销时间, 不太准确，应该由学校给出
//	double   curBalance;			//卡当前可用余额
//	char	 state_id[5];			//卡状态(4个字节) 注册1000, 注销2000,换
									//卡3000，挂失1100，冻结1010, 写卡失败
									//1001, 挂失冻结1110, 挂失冻结写卡失败1111
//	int      cut_state;				//客户状态(1为注册, 2为注销)
//	double   frozenBalance;		    //冻结余额
//	int      acc_current_state;     //帐户当前状态, 1注册, 2注销, 3冻结
//	int      card_flag;				//卡片状态类型,发新卡需要用到(1 退卡状态, 2 新
									//发卡状态, 3 换过的旧卡状态, 4 换新卡状态, -1表示不属于此类卡)
}Data_Info;

typedef struct _Save_Info
{
	int		cut_id;		//客户ID号(帐号)
	int     save_Money;	//转帐金额,精确到分
	int     save_type;	//0=存钱,1=冲正
}Save_Info;

#pragma pack()

/************************************************************************/
/* 加载动态库宏定义                                                                     
/************************************************************************/
#define DCLR_DLLFUNC(r,name,arg) \
	typedef r (__stdcall * LP##name) arg; \
	extern LP##name name

#define DEF_DLLFUNC(name) \
	LP##name name = NULL

#define LOAD_DLLFUNC(handle,name) \
	name = (LP##name)GetProcAddress(handle,#name); \
	if (NULL == name) \
	{ \
		::FreeLibrary(handle); \
		handle = NULL; \
		return DLLFUN_ERR_NO_FUNADDRESS; \
	}

/************************************************************************/
/* 加载动态库函数, 对接第三方信息名单
/************************************************************************/
// 水控转账
DCLR_DLLFUNC(int,GetDataInfo,(Data_Info *in_pack, int *errcode));
DCLR_DLLFUNC(int,SaveInfo,(Save_Info *in_pack, int *errcode));
//#ifdef SYNJONES_FUNC
DCLR_DLLFUNC(int,InitDB,());
//#else
//	NULL;
//#endif
DCLR_DLLFUNC(int,CloseDB,());

// 电控转账
DCLR_DLLFUNC(float,CNectDB,(bool is_connect));
DCLR_DLLFUNC(int,GetRoomName,(int room_code, char *room_name));
DCLR_DLLFUNC(int,SellElec,(int room_code, int money, char *room_name));
DCLR_DLLFUNC(int,GetDBStatus,());
DCLR_DLLFUNC(int,GetRemainE,(int nRoomCode,char * sElecDate));
//DCLR_DLLFUNC(float,GetEPrice,());

DCLR_DLLFUNC(int, GetPersonInfo,(PERSON_INFO *in_pack, int *errcode));

// 对接接口定义
// 以下为兼容旧版接口
#define IP_LEN  15
#define MAC_LEN	18
#define CRC_LEN 16
#define MODULE_NAME_LEN 256
#define MAX_PATH_LEN 1024

#pragma pack(1)
struct ksf_server_conf
{
	char ip[IP_LEN + 1];			// IP 
	char mac[MAC_LEN + 1];			// MAC 地址	
	int port;						// 端口
};
struct ksf_xml_data
{
	long length;					// 数据段长度
	int func_no;					// 功能号
	long count;						// 数据段中包含的 CARD 信息个数
	char data[1];					// 数据段，内容为解密后的内容,以 '\0' 作为结尾符
};


typedef enum {RET_OK = 1,RET_FAILD} ksf_ret_result;
struct ksf_card_result
{
	ksf_ret_result ret;
	int pack_index;				// 处理的包的 index
};
#pragma pack()

typedef int (WINAPI* lp_module_init)(void);
typedef int (WINAPI* lp_module_release)(void);
typedef int (WINAPI* lp_module_receive)(ksf_server_conf *,
											  ksf_xml_data * ,
											  ksf_card_result *);
struct ksf_plugin_module
{
	char module_name[MODULE_NAME_LEN +1];			// 模块名称
	char module_path[MAX_PATH_LEN + 1];					// 模块路径
	char date[9];									// 日期
	char author[256];								// 发行人
	short major_ver,minor_ver;						// 主版本号、次版本号
	lp_module_init module_init;						// 模块初始化函数指针
	lp_module_release module_release;				// 模块释放函数指针
	lp_module_receive module_receive;	// 模块主功能函数，用与保存数据
};



DCLR_DLLFUNC(int, registe_module, (ksf_plugin_module * module));
DCLR_DLLFUNC(int, unregiste_module, (ksf_plugin_module * module));

extern ksf_plugin_module g_global_module;

#ifdef __cplusplus
}
#endif

#endif