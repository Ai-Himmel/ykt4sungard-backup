#ifndef _USR_TYPDEF_H_
#define _USR_TYPDEF_H_
#include <sys/types.h>
//#include "inc.h"

#define A2E 1     /*ASCII TO EBCDIC*/
#define E2A 0     /*EBCDIC TO ASCII*/
#define NC  2     /*NO TRANSLATE NEED*/
#define ASCII "IBM-037"
#define EBCDIC "ISO8859-1"
//#define debug 0 
#define TXNCENTER 99
#define SETTLECENTER 88
#define REST_TIME 3
/* MAXMSGSIZE message size,it is the maximum size of a 8583 package,
* if this define is modified,please remember to modify the 
* MAX_BUF_SIZE in tb_struct.h and MAX_MSG_SIZE in global.h */
#define MAXMSGSIZE  2500 
/* the structure of 8583 message */
#define OUTSIDE_NO_TYPE_BOC 1
struct OrgDat
{
	char msgType[5];
 	char txnDatTim[11];
 	unsigned long tracNum;
 	char          acqInstID[12];     /*32*/
	char          forInst[12];       /*33*/
 } ;

struct prvData
{
 char receNum[3];
 char checkNum[11];
 char beginDate[9];
 char endDate[9];
 char despTime[3];
 char despDollor[3];
 char despType[3];
 char accountType[3];
 char inqueNum[9];
 char exchangeCode[9];
 char despNum[3];
 char accountTyp1[2];
 char Reserved[32];
 char backData[913];
};

typedef struct 
{
	//银行转帐
	//2，4，8，11，19，21，23，32，41，42，43，52-前对其
	//3，4，7，8，11，12，13，17，25，32，39，41，42，43，103
	//余额查询
	//2，3，4，8，11，12，13，19，21，23，25，32，41，42，43
	//2，3，4，7，8，11，12，13，25，28，39，41，42，43，103
	//冲正--自己的流水号
	//2,4,8,11,19,21,23,32,41,42,43,52,90
	//2,4,8,11,19,21,23,32,41,42,43,52,90
	char          msgType[5];
	unsigned long bitMapExt ;  /*bitmap extend*/
	char          priActNum[30];  /*2--*/  /*priamary account*/
	char          procCode[6];	/*3--*/
	char	         txnAmunt[12]; 	/*4--*/	/*total*//*总金额 分为单位 */
	double        txnAmunt1; 	/*5*/	/*本金*/
	double        txnAmunt2; 	/*6*/

	char          txnDatTim[11];    /*7*/ 	 /*交易时间日期*/
	char 		  companyid[9];		/*8*/        	/*公司代码*/
	char		 tracAudNum[20] ;      /*11--*/			/*流水号*/
	char          txnLocTim[7];     /*12*/			
	char          txnLocDat[8+1];     /*13--*/
	char		  bala_date[4+1];		/*15--*/	/*结账日期*/
	char          datCap[5];        /*17*/			/*主机交易时间*/
	char	      ctTxnCod[5];	/*18*/			/*CT交易代码*/
	char	      teller[5];	/*19*/			/*柜员00*/
	char	      supervisor[4];	/*20*/			/*主管*/
	char	      srvTyp[4];	/*108-21*/			/*服务类型*/
	char	      actTyp[4];	/*01-23*/			/*帐户类别*/
	int           pSrvCdCod;        /*25*/			/*服务点代码*/
	char	      dealCir[3];	/*26*/			/*处理周期*/
	char	      bankid;		/*27*/			/*银行ID*/
	char		trade_fee[9+1];	/*28--*/	/*交易手续费*/
	//unsigned long mainTrcNo;        /*28*/			/*银行流水*/
	char	      pinDat1[9];	/*29*/			/*密码*/
	char	      zipcod[9];	/*30*/			/*邮政编码*/
	char          acqInstID[6+1];    /*32--*/			/*收单机构号*/
	char          forInst[12];      /*33*/			/*向前机构号*/
	char	      cusnam[29];	/*34*/			/*姓名*/
	
	char          field37[20+1];      /*37--*/  		/*授权号REQ*/
	char 	      field38[7];	/*38*/  		/*授权号RES*/
	char          rspCod[3];        /*39*/			/*回复码*/
	char		  feememo[4];		/*40*/		/*摘要*/
	char          termID[9];        /*00-41*/			/*终端号*/
	char          idenCod[16];      /*42*/			/*交易网点号*/
	char	      agtcus[31];        /*43*/ /*userid*/	/*客户标识 left is filled with 0 to fullfill 19 bytes */
	char          addRspDat[26];    /*44*/			/*第二标识*/
	char	      addInf45[77];	/*45*/			/*附加数据*/
	char 	      field47[500];	     /*47   change 999 to 500*/ 
	char			field48[20+1];		/*48--*/   /**/
	struct   prvData  prvData;	/*48*/
	char          txnCuuCod[4];     /*49*/			/*货币代码*/
	char		 pinDat[8];		/*52*/
	//unsigned long pinDat;           /*52*/			/*PINDAT*/
	double        addAmunt;         /*54*/ /*滞纳金*/
	char	      batchid;		/*66*/			/*转批量标志*/
	char          netMngInfo[4];    /*70*/		/*301 TEST INFO*/
												/*001 LOGIN*/
												/*002 LOGOUT */
	char	      feeDat[11];	/*78*/			/*交费日期*/
	char	      openDate[11];	/*74*/			/*开户日期*/
	char	      firstTxnDate[11]; /*75*/			/*初始交易日期*/
	char	      stopTxnDate[11];  /*76*/			/*截止交易日期*/
	char	      batchDealDate[11];/*77*/			/*转批量日期*/
	struct OrgDat OrgDatElm;        /*90*/			/*原始交易信息*/
	char          recvIntID[12];    /*100*/			/*接收机构号*/
	char          chkAct[29];       /*102*/ 		/*附加帐号*/
	char	      addAcNo103[29];	/*103*/ /*bank acno*/   /*银行帐号*/
	char	      bankCode[6+1];	/*104*/	
	char	      englishNam[61];	/*105*/			/*英语名字*/
	char	      personID[106];	/*106*/			/*身份证*/
	char	      cusAddr[61];	/*107*/			/*通讯地址*/
	char	      teleNo[21];	/*108*/			/*电话*/
	char	      receiptNo[16];	/*109*/			/*收据号码*/
	unsigned char mac[8];           /*128*/			/* MAC 校验*/
	char mac1[17];
	char mac2[17];
} MSG8583;

/* the message structure in message queue */
typedef struct  
{
	char apcode[4];
	int msgLen;
	char acqInstID[12];
	char termID[9];
	char srvuID[9];
	unsigned long trcno;
	char msg[2*MAXMSGSIZE+200];
} MQ_MSG8583;
int Pack8583(unsigned char *buf, MSG8583 TransMsg,int convDirect);
//int Pack8583(char *buf,MSG8583 msg,int convDirect);
int UnPack8583(unsigned char *buf,MSG8583 *TransMsg,int convDirect);
int  translate(int convDirect,char *inbuf,char *outbuf);
int init8583(MSG8583 *msg);
int reverse(long trcno2,int reqid);
void Disp8583(MSG8583 msg8583);
#endif


