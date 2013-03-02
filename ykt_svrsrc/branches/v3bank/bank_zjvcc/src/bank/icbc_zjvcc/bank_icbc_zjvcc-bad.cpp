/* ----------------------------------------------------------
 * 程序名称：bank_icbc_zjvcc.cpp
 * 创建日期：2011-09-08
 * 程序作者：聂龙海
 * 版本信息：1.0.0.0
 * 程序功能：工商银行-浙商职接口
 * ----------------------------------------------------------*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "assert.h"

#include "shem.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "d3des.h"
#include "mac.h"
#include "bank.h"
#include "bank_interface.h"
#include "tcp_update.h"


static void GenMsgHead(char *msghead,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf,"AreaNo","");								//地区代码
	AddXmlItemStr(buf,"ChanNo","");								//渠道代码
	AddXmlItemInt(buf, "TerminalNo", rPack->lvol6);					//终端编号
	AddXmlItemStr(buf,"TransNo",rPack->sholder_ac_no);			//交易流水号
	AddXmlItemStr(buf,"TransDate",rPack->sdate0);				//交易日期
	AddXmlItemStr(buf,"TransTime",rPack->stime0);					//交易时间
	AddXmlItemStr(buf,"BankNo","");								//机构代码
	AddXmlItemStr(buf,"TellerNo","");								//柜员代码
	AddXmlItemInt(buf, "FuncTionFlag", 1);							//处理标志
	AddXmlItemStr(msghead, "MsgHead", buf);						// 全包含在MsgHead 中	
	writelog(LOG_DEBUG,"msghead[%s] ",msghead);
}

// 充值包体
static void GenMsgBodyTrans(char *msgbody,ST_PACK *rPack)	
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//学校代码
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//校园卡卡号(使用学工号)
	AddXmlItemStr(buf, "CusName", rPack->scust_limit);				//客户姓名
	AddXmlItemInt(buf, "SignFlag", 1);								//签约标志
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// 银行卡号
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// 交易金额

	AddXmlItemStr(msgbody, "MsgBody", buf);						//全包含在MsgBody 中	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

// 冲正包体
static void GenMsgBodyTransRev(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//学校代码
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//校园卡卡号(使用学工号)
	AddXmlItemDbl(buf, "Amount", rPack->damt0);					// 交易金额
	AddXmlItemStr(buf, "RSeqNo", rPack->sholder_ac_no);			//交易流水号

	AddXmlItemStr(msgbody, "MsgBody", buf);						//全包含在MsgBody 中	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenMsgBodyQuery(char *msgbody,ST_PACK *rPack)
{
	char buf[1024]="";
	AddXmlItemStr(buf, "SchoolCode", SCHOOLCODE_AHUT);			//学校代码
	AddXmlItemStr(buf, "IcCard", rPack->sphone);					//校园卡卡号(使用学工号)
	AddXmlItemInt(buf, "SignFlag", 1);								//签约标志
	AddXmlItemStr(buf, "ActNo", rPack->scust_limit2);				// 银行卡号

	AddXmlItemStr(msgbody, "MsgBody", buf);						//全包含在MsgBody 中	
	writelog(LOG_DEBUG,"msgbody[%s] ",msgbody);
}

static void GenTransReqMSG(char *msg,char *transcode,char *msghead,char *msgbody)
{
	char len_buf[16]="";
	char transcont[2048]="";
	char *trans_head="<TranRequest>";
	char *trans_tail="</TranRequest>";

	int transhead_len = strlen(trans_head);
	int msghead_len = strlen(msghead);
	int msgbody_len = strlen(msgbody);
	int transtail_len = strlen(trans_tail);
	int xmlhead_len = strlen(XML_HEAD);

	int transcont_len =   transhead_len + msghead_len + msgbody_len + transtail_len;

	memcpy(transcont,trans_head,transhead_len);
	memcpy(transcont+transhead_len,msghead,msghead_len);
	memcpy(transcont+transhead_len+msghead_len,msgbody,msgbody_len);
	memcpy(transcont+transhead_len+msghead_len+msgbody_len,trans_tail,transtail_len);

	sprintf(len_buf,"%08d",4 + xmlhead_len + transcont_len);
	memcpy(msg,len_buf,8);											// 8位长度
	memcpy(msg+8,transcode,4);										// 4位交易码
	memcpy(msg+12,XML_HEAD,xmlhead_len);							// xml 头
	memcpy(msg + xmlhead_len +12,transcont,transcont_len);				// 交易内容(msghead + msgbody)
	writelog(LOG_DEBUG,"msg[%s] ",msg);
}





// 打印调试信息
#define set_msg(buf, fmt, ...)\
{\
	sprintf(buf, fmt, ## __VA_ARGS__);\
	printf(buf);\
}

//static void set_msg_log(char *szMsg,int ret)

//打印和写日志调试信息
#define set_msg_log(buf, fmt, ...)\
{\
	set_msg(buf, fmt, ## __VA_ARGS__);\
	writelog(LOG_ERR,buf);\
}





#define MAX 2048
typedef struct
{
	char campus_no[12+1];	//1   学校编号 aaaaaaaaaaaaaaaaaaaaaa
	char txcode[5+1]; //2        交易代码      
	char userno[12+1]; //3        客户编号，每笔转帐的唯一标识（必须有，如学号） 
	char usernoalias[18+1];//4  身份证号
	char acctperi[5+1];//5 账期
	char acctno[20+1];//6	银行账号或卡号
	char due_amount[10+1];//7	交易金额（格式：180.00）
	char pay_amount[10+1]; //8成功金额或余额 
	char custname[20+1]; //9/////客户名
	char site[5+1]; //10交易网点	111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	char teller[5+1];	//11	交易柜员 1111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	char time[14+1];//12	交易时间,日期＋时间
	char comporder[8+1];	//13公司方流水  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	char bankorder[8+1];	//14银行方流水
	char comp_o_order[8+1];//15公司方原交易流水  
	char bank_o_order[8+1];//16银行方原交易流水  	
	char note[50+1];	//17附加信息  
	char result[3+1];//18	交易成功或失败	00：成功	01：失败   
	char retmessage[50+1];	//19错误信息 
}Message;


static void print_msg(Message *Msg)
{
	printf("学校编号 campus_no:    [%s]\n", Msg->campus_no);
	printf("交易代码 txcode:       [%s]\n", Msg->txcode);
	printf("客户编号 userno:       [%s]\n", Msg->userno);
	printf("客户子编号 usernoalias:[%s]\n", Msg->usernoalias);
	printf("账期 acctperi:         [%s]\n", Msg->acctperi);
	printf("账号 acctno:           [%s]\n", Msg->acctno);
	printf("交易金额 due_amount:   [%s]\n", Msg->due_amount);
	printf("余额 pay_amount:       [%s]\n", Msg->pay_amount);
	printf("客户姓名 custname:     [%s]\n", Msg->custname);
	printf("交易网点 site:         [%s]\n", Msg->site);
	printf("交易柜员 teller:       [%s]\n", Msg->teller);
	printf("交易日期＋时间 time:   [%s]\n", Msg->time);
	printf("公司方流水 comporder:  [%s]\n", Msg->comporder);
	printf("银行方流水 bankorder:  [%s]\n", Msg->bankorder);
	printf("公司方原交易流水 comp_o_order: [%s]\n", Msg->comp_o_order);
	printf("银行方原交易流水 bank_o_order: [%s]\n", Msg->bank_o_order);
	printf("附加信息 note:         [%s]\n", Msg->note);
	printf("响应码 result:         [%s]\n", Msg->result);
	printf("错误信息 retmessage:   [%s]\n", Msg->retmessage);
	return;
}



static void print_send_msg(Message *Msg)
{
	printf("\n==================== 发送报文开始 =====================\n");
	print_msg(Msg);
	printf("====================== 发送报文结束 ======================\n");
	return; 
}

static void print_recv_msg(Message *Msg)
{
	printf("===================== 银行返回报文开始 =====================\n");
	print_msg(Msg);
	printf("===================== 银行返回报文结束 ======================\n");
	return; 
}


static void getdata(Message *Msg,ST_PACK *rPack)
{
// 	char trade_date[9]={0}; // 交易日期 
// 	char trade_time[7]={0}; // 交易时间
	//set_msg(Msg->campus_no,"%s","001");	//1学校编号
	//des2src(Msg->txcode,"20200"); //2交易代码
// 	des2src(Msg->userno, rPack->sphone);	//3 学工号
// 	des2src(Msg->usernoalias, rPack->scust_auth2);// 4身份证号
// 	des2src(Msg->acctperi, rPack->vsmess); //5 对账日期
// 	des2src(Msg->acctno, rPack->scust_limit2);//6 银行卡号
// 	set_msg(Msg->due_amount,"%0.2f",rPack->damt0); //7交易金额（格式：180.00）x
// 	//8
// 	des2src(Msg->custname, rPack->scust_limit );//9 客户名
// 	set_msg(Msg->site,"%d",rPack->lvol6);  //10
// 	set_msg(Msg->teller,"%d",rPack->lvol6); //11
// 	des2src(trade_date, rPack->sdate0); //12 交易日期
// 	des2src(trade_time, rPack->stime0); //12 交易时间
// 	set_msg(Msg->time,"%s%s",trade_date,trade_time); //12	交易时间,日期＋时间
// 	des2src(Msg->comporder, rPack->sholder_ac_no); //13

	snprintf(Msg->userno, sizeof(Msg->userno), "%d", rPack->lvol2); //3 客户号
	snprintf(Msg->usernoalias, sizeof(Msg->usernoalias), "%s", rPack->scust_auth2); // 身份证号
	snprintf(Msg->acctno, sizeof(Msg->acctno), "%s", rPack->scust_limit2); // 银行卡号
	snprintf(Msg->custname, sizeof(Msg->custname), "%s", rPack->scust_limit); // 客户名
	snprintf(Msg->acctperi, sizeof(Msg->acctperi), "%s", rPack->sdate0); // 交易日期
	if(strlen(Msg->acctperi) == 0)// 没有提供日期
		getsysdate(Msg->acctperi);
	snprintf(Msg->due_amount, sizeof(Msg->due_amount), "%.2f", rPack->damt0);// 交易金额
	snprintf(Msg->site, sizeof(Msg->site), "%d", rPack->lvol6);// 终端ID
	getsysdatetime(Msg->time); // 交易日期＋时间
	if(strlen(rPack->sholder_ac_no) > 8) // 一卡通交易参考号
	{
		// 一卡通交易参考号 去除 yyMMDD, 作为系统跟踪号
		int serial = atoi(&rPack->sholder_ac_no[8]);
		snprintf(Msg->comporder, sizeof(Msg->comporder), "%06d", serial); // 公司方流水
		snprintf(Msg->comp_o_order, sizeof(Msg->comp_o_order), "%06d", serial); // 公司方流水
	}
	snprintf(Msg->bankorder, sizeof(Msg->bankorder), rPack->sname); // 银行方流水
	snprintf(Msg->bank_o_order, sizeof(Msg->bank_o_order), rPack->sname); // 银行方原交易流水
	//print_send_msg(Msg); // 打印发送报文

}


static void struct2str(Message *j,char *buf)  //拼装
{
	sprintf(buf,"&|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|#",		
		j->campus_no, //1
		j->txcode, //2
		j->userno, //3
		j->usernoalias, //4
		j->acctperi, //5
		j->acctno, //6
		j->due_amount, //7
		j->pay_amount, //8
		j->custname, //9
		j->site, //10
		j->teller, //11
		j->time, //12
		j->comporder, //13
		j->bankorder, //14
		j->comp_o_order, //15
		j->bank_o_order, //16
		j->note, //17
		j->result, //18
		j->retmessage); //19

}


void str2struct(char *buf,Message *j)
{
	int len,i;
	char *p,*q,*str[20];
	len=strlen(buf);
	//q=strstr(buf,"&")+1;
	q=buf+1;
	for(i=1;q<buf+len-1;i++)
	{
		p=strstr(q,"|");
		*p++=0;
		str[i]=p;
		q=p;
	}
	strcpy(j->campus_no,str[1]);	//1   学校编号 aaaaaaaaaaaaaaaaaaaaaa
	strcpy(j->txcode,str[2]); //2        交易代码      
	strcpy(j->userno,str[3]); //3        客户编号，每笔转帐的唯一标识（必须有，如学号） 
	strcpy(j->usernoalias,str[4]);//4  身份证号
	strcpy(j->acctperi,str[5]);//5 账期
	strcpy(j->acctno,str[6]);//6	银行账号或卡号
	strcpy(j->due_amount,str[7]);//7	交易金额（格式：180.00）
	strcpy(j->pay_amount,str[8]); //8成功金额或余额 
	strcpy(j->custname,str[9]); //9/////客户名
	strcpy(j->site,str[10]); //10交易网点	111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	strcpy(j->teller,str[11]);	//11	交易柜员 1111111111xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	strcpy(j->time,str[12]);//12	交易时间,日期＋时间
	strcpy(j->comporder,str[13]);	//13公司方流水  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
	strcpy(j->bankorder,str[14]);	//14银行方流水
	strcpy(j->comp_o_order,str[15]);//15公司方原交易流水  
	strcpy(j->bank_o_order,str[16]);//16银行方原交易流水  	
	strcpy(j->note,str[17]);	//17附加信息  
	strcpy(j->result,str[18]);//18	交易成功或失败	00：成功	01：失败   
	strcpy(j->retmessage,str[19]);	//19错误信息 
}


static bool send(CTcpSocket *SockNode,char *send_buf,char *szMsg)
{
	int ret=0;
	int send_len=strlen(send_buf);
	char buf[2048]={0};
	ret=SockNode->Send(send_buf,send_len);
	if (ret<=0)
	{
		SockNode->Close();
		set_msg_log(szMsg,"发送数据至银行出错,错误代码[%d]\n",ret);
		return false;
	}
	set_msg_log(buf, "发送数据到银行, 长度[%d] 数据[%s]\n", send_len, send_buf);
	return true;
}


static bool connect(CTcpSocket *SockNode,char *bank_ip,int bank_port,int bank_delay,char *szMsg)
{
	char buf[2048]={0};
	int ret=0;
	alarm(bank_delay/1000);
	ret=SockNode->ConnectTcp(bank_ip, bank_port);
	if(!ret)
	{
		alarm(0);
		SockNode->Close();
		set_msg_log(szMsg,"连接银行服务器失败,错误代码[%d],银行IP[%s],银行PORT[%d]\n",ret,bank_ip, bank_port);
		return false;
	}
	alarm(0);
	set_msg_log(buf, "连接银行服务器成功\n");
	return true;
}



static void get_ip_port(char *ip,int *port,ST_PACK *rPack)
{
	sprintf(ip, "%s",rPack->scust_auth); // 银行服务器IP
	*port = rPack->lvol0; // 银行服务器Port     
}

static void initialize(char *type,char *bank_ip,int *bank_port,Message *send_Msg,ST_PACK *rPack,char *send_buf)
{
	get_ip_port(bank_ip,bank_port,rPack); //银行服务器IP和银行服务器Port 
	getdata(send_Msg,rPack); //获取数据
	strcpy(send_Msg->txcode,type); //初始化发送数据交易代码
	struct2str(send_Msg,send_buf);  //拼装
	print_send_msg(send_Msg); // 打印发送报文
}



static bool receive(CTcpSocket *SockNode,char *recv_buf,int max_len,int bank_delay,char *szMsg)
{
	 	int ret=0;
		int recv_len = 0;
		char buf[2048]={0};
		// 接受数据
		while(1)
		{
			ret= SockNode->RecvDesignedLen(recv_buf,max_len,bank_delay);
			if (ret<=0)
			{
				SockNode->Close();
				set_msg_log(szMsg,"接收银行返回数据出错或超时,错误代码[%d]\n",ret);
				return false; // 接收时候出错，或超时
			}
			max_len -= ret;
			recv_len += ret; // 已接受数据长度
			if(recv_buf[recv_len -1] == '#')
			{
				SockNode->Close();
				break;
			}
		}
		recv_buf[recv_len] = 0; // 字符串结束
		set_msg_log(buf, "接收到银行返回数据, 长度[%d] 数据[%s]\n", recv_len, recv_buf);
		if(recv_buf[0] != '&') // 检查起始标志
		{
			set_msg_log(szMsg,"银行返回数据格式，起始标志错误\n");
			return false; // 报文格式错误
		}
		return true;
}


static bool is_success(char *recv_buf,Message *recv_Msg,char *szMsg)
{
	str2struct(recv_buf,recv_Msg);   // 解析银行返回的数据	
	print_recv_msg(recv_Msg);
	if(strcmp(recv_Msg->result,"00")!=0)
	{
		set_msg(szMsg,"银行返回交易失败，代码[%s] 错误信息[%s]\n",recv_Msg->result, recv_Msg->retmessage);
		return false;
	}
	set_msg(szMsg,"银行返回交易成功\n");	
	return true;
}


static bool result(char *type,Message *recv_Msg,TRUSERID *handle,int *pRetCode,char *szMsg)
{
	double amt;
	ST_CPACK aPack;	
	ST_PACK *out_pack = &(aPack.pack);
	ResetNormalCPack(&aPack,0,1);
	SetCol(handle,0);
	if(strcmp(type,"20210")==0) //20210：公司方发起查询卡余额
	{
		SetCol(handle,F_LVOL1,F_DAMT0,F_DAMT1,F_SALL_NAME, F_VSMESS,0);
		amt = atof(recv_Msg->pay_amount);// 取账面余额
		out_pack->damt0=amt;// 取账面余额
		out_pack->damt1=amt;// 
		out_pack->lvol1=1; // 正常处理
		des2src(out_pack->sall_name, recv_Msg->acctno); // 银行帐号
		des2src(out_pack->vsmess, szMsg);
		PutRow(handle,out_pack,pRetCode,szMsg);
	}
	else if(strcmp(type,"20200")==0||strcmp(type,"20201")==0) //20200：公司发起联机转账扣款  20201：公司发起联机转账扣款反交易
	{
		SetCol(handle,F_LVOL1,F_SPHONE, F_VSMESS,0);
		out_pack->lvol1=1; // 正常处理
		des2src(out_pack->vsmess, szMsg);
		des2src(out_pack->sphone, recv_Msg->bankorder);// 银行端流水号
		PutRow(handle,out_pack,pRetCode,szMsg);
	}
	else if(strcmp(type,"10000")==0||strcmp(type,"10001")==0) //10000：新增委托关系  10001：撤销委托关系
	{
		SetCol(handle,F_SCARD0, F_VSMESS,F_VSVARSTR0, F_LSAFE_LEVEL, 0);
		out_pack->lsafe_level = 0;
		des2src(out_pack->scard0, recv_Msg->acctno);
		des2src(out_pack->vsmess, szMsg);
		des2src(out_pack->vsvarstr0, szMsg);
		PutRow(handle,out_pack,pRetCode,szMsg);
	}	
	else
	{
		set_msg(szMsg,"功能未实现, 代码[%d]\n",type);
		writelog(LOG_ERR,szMsg);
		return false;
	}
	return true;
}

static int Bank_Process(char *type , TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char bank_ip[20]={0}; // 银行IP
	int bank_port=0;
	Message send_Msg={"0005",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	Message recv_Msg={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	char send_buf[MAX]={0};
	char recv_buf[MAX]={0};
	CTcpSocket  SockNode;
	int	bank_delay = 40000; // 对账请求，时间需要可能较长
	initialize(type,bank_ip,&bank_port,&send_Msg,rPack,send_buf);  //初始化发送数据
	
	//生成包头
	GenMsgHead(msghead,rPack);

	//生成查询包体
	GenMsgBodyQuery(msgbody,rPack);

	// 生成查询报文
	GenTransReqMSG(msg,QUERY_BALA,msghead,msgbody);
	
	
	
	
	if(connect(&SockNode,bank_ip,bank_port,bank_delay,szMsg)==false){return E_TRANS_BANK_NETERR;}; //连接银行
	if(send(&SockNode,send_buf,szMsg)==false){return E_TRANS_BANK_NETERR;} //发送数据到银行
	if(receive(&SockNode,recv_buf,sizeof(recv_buf),bank_delay,szMsg)==false){return E_TRANS_BANK_NOANSWER;} //接收银行返回信息
	if(is_success(recv_buf,&recv_Msg,szMsg)==false){return E_TRANS_BANK_RECVERR;}  //判断银行返回交易是否成功
	if(result(type,&recv_Msg,handle,pRetCode,szMsg)==false){return E_TRANS_FUNC_NONSUPPORT;}  //返回结果
	return 0;
}

// 查询余额
int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 查询余额 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(0 ,handle,rPack,pRetCode,szMsg);
	return Bank_Process("20210",handle,rPack,pRetCode,szMsg);
}

// 转账
int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 圈存转账 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(1, handle,rPack,pRetCode,szMsg);
	return Bank_Process("20200",handle,rPack,pRetCode,szMsg);
}




// 冲正
int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 转账冲正 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(2, handle,rPack,pRetCode,szMsg);
	return Bank_Process("20201",handle,rPack,pRetCode,szMsg);
}

// 签约
/*
int Bank_Bind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 签约 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	// return Bank_Process(3, handle,rPack,pRetCode,szMsg);
	return Bank_Process("10000",handle,rPack,pRetCode,szMsg);
}
*/
// 解约
/*
int Bank_UnBind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 解约 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(4, handle,rPack,pRetCode,szMsg);
	return Bank_Process("10001",handle,rPack,pRetCode,szMsg);
}
*/
// 修改校验码
int Bank_ChangePin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 修改校验码 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(5, handle,rPack,pRetCode,szMsg);
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}

// 重置校验码
int Bank_ResetPin(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 重置校验码 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(6, handle,rPack,pRetCode,szMsg);
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}

// 对账
int Bank_Checkacc(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	char* msg = "收到 对账 请求\n";
	printf(msg);
	writelog(LOG_INFO,msg);
	//return Bank_Process(7, handle,rPack,pRetCode,szMsg);
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}


// 查询绑定
int Bank_Querybind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg)
{
	set_msg(szMsg,"Bank_Querybind 功能未实现, 代码[%c]\n",rPack->sstatus0[0] );
	writelog(LOG_ERR,szMsg);
	//return E_TRANS_FUNC_NONSUPPORT;
	return Bank_Process("00000",handle,rPack,pRetCode,szMsg);
}

int Bank_Transfer(INNER_TRANS_REQUEST*, int)
{
	return E_TRANS_FUNC_NONSUPPORT;

}

int Bank_QueryBalance(INNER_TRANS_REQUEST*, double*)
{
	return E_TRANS_FUNC_NONSUPPORT;
}

