	
//F820701 添加黑名单
//参数说明:卡号,卡状态,黑名单类别,操作员代码
int F820701(int p_Card_id,int p_State_id,char *p_Oper_code,char *szMsg)

//F820702 删除黑名单
//参数说明:记录号,操作员代码
int F820702(int p_Card_id,char *p_Oper_code,char *szMsg) 

//F849001 查询客户信息
//参数说明:客户号,结构(客户信息)
int F849001(int p_Cut_id,struct Customer *p_stCut,char *szMsg) 