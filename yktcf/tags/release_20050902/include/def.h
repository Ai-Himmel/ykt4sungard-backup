#ifndef _DEF_H_
#define _DEF_H_
/** 
 * 模块名					通用前置
 * 文件名					def.h
 * 文件实现功能				通用前置数据结构定义
 * 作者						汤成
 * 版本						V0.1
 * 日期						2005-08-18
 * 备注
 * $Id$
 */

//{{{ define constants
#define IP_LEN  15
#define MAC_LEN	18
#define CRC_LEN 16
#define MODULE_NAME_LEN 256
#define MAX_PATH_LEN 1024
//}}}

//{{{ 系统配置
#define INI_SVR_SECT "SERVER"
#define INI_SVR_PORT "PORT"
#define INI_MODULE_SECT "MODULE"
#define INI_MODULE_PATH "PATH"
//}}}



//{{{ 子系统结构 
typedef struct 
{
	char ip[IP_LEN + 1];			// IP 
	char mac[MAC_LEN + 1];			// MAC 地址	
	int port;						// 端口
}ksf_server_conf;
//}}}

/* {{{ 协议报文的 XML 格式
 	
 	<!DOCTYPE	card-info[
 		<!ELEMENT	card-info(card)*>
 		<!ELEMENT	card(phy-id,cardid,stuempno?,blk-version,flag)>
 		<!ELEMENT	flag(0|1)>	
 	]>
 	
	<card-info>
   		<card>
   			<phy-id>卡物理ID</phy-id>
   			<cardid>交易卡号</cardid>
   			<stuempno>学工号</stuempno>
   			<blk-version>版本号</blk-version>
   			<flag>标志</flag>
   		</card>
   		...
   		...
	</card-info>
}}}*/

// 加密算法
// 不加密
#define ENC_TYPE_NONE	0
// 使用 AES 128 算法加密
#define ENC_TYPE_AES128 1

/* 以下代码是用来字节对齐使用的 */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#else	// __GNUC__
#define __PACKED__	__attribute__ ((packed))
#endif	// __GNUC__
#else	// WIN32
#define __PACKED__ 
#endif	// WIN32

// 以下的定义的包会字节对齐
#if defined(WIN32) || defined(__GNUC__)
#ifndef SUNOS
#pragma pack(push,1)
#endif
#else
#pragma options align=packed
#endif
//{{{ 报文结构
typedef struct 
{
	long length;					// 数据段长度
	int func_no;					// 功能号
	int pack_index;					// 包的序号 从 0 开始
	long count;						// 数据段中包含的 CARD 信息个数
	int next_pack;					// 后继数据包数量，如果为 0 表示没有后继包
	char enc_type;					// 加密算法，0 表示无加密,1 表示128位AES
	char padded;					// 如果是加密，表示是否被补位，1:是 0:不是
	char CRC[CRC_LEN];				// CRC 校验代码
	char data[1];					// 数据段，数据段的内容是加密的
}__PACKED__ ksf_card_info;
//}}}

//{{{ 报文解密后的结构
typedef struct 
{
	long length;					// 数据段长度
	int func_no;					// 功能号
	long count;						// 数据段中包含的 CARD 信息个数
	char data[1];					// 数据段，内容为解密后的内容,以 '\0' 作为结尾符
}__PACKED__ ksf_xml_data;
//}}}
#ifndef WIN32
#ifndef __GNUC__
#pragma options align=reset
#else
#ifndef SUNOS
#pragma pack(pop)
#endif
#endif
#else
#pragma pack(pop)
#endif

//{{{ 返回处理结果结构
typedef enum {RET_OK = 1,RET_FAILD} ksf_ret_result;
typedef struct 
{
	ksf_ret_result ret;
	int pack_index;				// 处理的包的 index
}ksf_card_result;
//}}}

//{{{ 子系统 Plugin 结构
struct ksf_plugin_module
{
	char module_name[MODULE_NAME_LEN +1];			// 模块名称
	char module_path[MAX_PATH_LEN + 1];					// 模块路径
	char date[9];									// 日期
	char author[256];								// 发行人
	short major_ver,minor_ver;						// 主版本号、次版本号
	int (* module_init)(void);						// 模块初始化函数指针
	int (* module_release)(void);					// 模块释放函数指针
	int (* module_receive)(ksf_server_conf * svr_conf,
						ksf_xml_data * date,
						ksf_card_result * ret);	// 模块主功能函数，用与保存数据
};
//}}}

#define def(r,name,arg) \
	typedef r (*lp##name) arg; \
	static lp##name name; 

#define load(dll,name) \
	name = (lp##name)GetProcAddress(dll,#name); \
	if( !name ) \
		err_code = true;

#endif // _DEF_H_
