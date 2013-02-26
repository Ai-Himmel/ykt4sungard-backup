/*******************************************************************************

	file name : PersonInfoApi.h
    Auther : Skaen
    Function : PersonInfo Call Api        

********************************************************************************/


#ifndef _PersonInfoAPI_H
#define _PersonInfoAPI_H

#include<windows.h>

#ifdef __cplusplus
#define DLLAPI                         extern "C" __declspec (dllexport)
#else
#define DLLAPI                         extern __declspec (dllexport)
#endif

typedef struct _SL_PERSON_INFO 
{
	char 	 show_id[11];		//显示卡号
	char 	 classdept_name[101];	//联系人部门名称
	char 	 stuemp_no[21];		//学工号
	int  	 card_id;		//交易卡号
	int 	 type_id;		//卡类别: (1正式卡, 2临时卡, 3非记名临时
					//卡, 4VIP记名临时卡, 5记名临时卡)
	int      cut_id;                //客户ID号
	char     cut_type_name[51];	//客户类别名称
	int      cut_state;		//客户状态(1为注册, 2为注销)
	int      area;			//客户所在区域(学校制定)
	char	 main_id[21];		//身份证号
	char	 state_id[5];		//卡状态(4个字节) 注册1000, 注销2000,换
					//卡3000，挂失1100，冻结1010, 写卡失败
					//1001, 挂失冻结1110, 挂失冻结写卡失败1111 
	char	 reg_time[31];		//用户注册时间
	char	 can_time[31];		//用户注销时间, 此为有效期时间
	char	 cut_name[61];		//客户名称
	char	 sex[2];		//性别(1为男, 2为女)
	char	 physical_no[41];	//物理卡号
	char     volume[13];		//更新版本号(070403102045), 一卡通数据库总是取最新的版本号的数据传送给贵方，
					//例如我方发现有人挂失，state_id字段发生变化，则会将此人的版本号增大，
					//然后发送的时候以这个最大的版本号所标识的记录来发送给对方.
}PERSON_INFO;

DLLAPI int CALLBACK GetPersonInfo(PERSON_INFO *in_pack, int *errcode);

DLLAPI int CALLBACK CloseDB();


#endif