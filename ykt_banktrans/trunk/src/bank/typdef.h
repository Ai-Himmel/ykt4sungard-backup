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
	//����ת��
	//2��4��8��11��19��21��23��32��41��42��43��52-ǰ����
	//3��4��7��8��11��12��13��17��25��32��39��41��42��43��103
	//����ѯ
	//2��3��4��8��11��12��13��19��21��23��25��32��41��42��43
	//2��3��4��7��8��11��12��13��25��28��39��41��42��43��103
	//����--�Լ�����ˮ��
	//2,4,8,11,19,21,23,32,41,42,43,52,90
	//2,4,8,11,19,21,23,32,41,42,43,52,90
	char          msgType[5];
	unsigned long bitMapExt ;  /*bitmap extend*/
	char          priActNum[30];  /*2--*/  /*priamary account*/
	char          procCode[6];	/*3--*/
	char	         txnAmunt[12]; 	/*4--*/	/*total*//*�ܽ�� ��Ϊ��λ */
	double        txnAmunt1; 	/*5*/	/*����*/
	double        txnAmunt2; 	/*6*/

	char          txnDatTim[11];    /*7*/ 	 /*����ʱ������*/
	char 		  companyid[9];		/*8*/        	/*��˾����*/
	char		 tracAudNum[20] ;      /*11--*/			/*��ˮ��*/
	char          txnLocTim[7];     /*12*/			
	char          txnLocDat[8+1];     /*13--*/
	char		  bala_date[4+1];		/*15--*/	/*��������*/
	char          datCap[5];        /*17*/			/*��������ʱ��*/
	char	      ctTxnCod[5];	/*18*/			/*CT���״���*/
	char	      teller[5];	/*19*/			/*��Ա00*/
	char	      supervisor[4];	/*20*/			/*����*/
	char	      srvTyp[4];	/*108-21*/			/*��������*/
	char	      actTyp[4];	/*01-23*/			/*�ʻ����*/
	int           pSrvCdCod;        /*25*/			/*��������*/
	char	      dealCir[3];	/*26*/			/*��������*/
	char	      bankid;		/*27*/			/*����ID*/
	char		trade_fee[9+1];	/*28--*/	/*����������*/
	//unsigned long mainTrcNo;        /*28*/			/*������ˮ*/
	char	      pinDat1[9];	/*29*/			/*����*/
	char	      zipcod[9];	/*30*/			/*��������*/
	char          acqInstID[6+1];    /*32--*/			/*�յ�������*/
	char          forInst[12];      /*33*/			/*��ǰ������*/
	char	      cusnam[29];	/*34*/			/*����*/
	
	char          field37[20+1];      /*37--*/  		/*��Ȩ��REQ*/
	char 	      field38[7];	/*38*/  		/*��Ȩ��RES*/
	char          rspCod[3];        /*39*/			/*�ظ���*/
	char		  feememo[4];		/*40*/		/*ժҪ*/
	char          termID[9];        /*00-41*/			/*�ն˺�*/
	char          idenCod[16];      /*42*/			/*���������*/
	char	      agtcus[31];        /*43*/ /*userid*/	/*�ͻ���ʶ left is filled with 0 to fullfill 19 bytes */
	char          addRspDat[26];    /*44*/			/*�ڶ���ʶ*/
	char	      addInf45[77];	/*45*/			/*��������*/
	char 	      field47[500];	     /*47   change 999 to 500*/ 
	char			field48[20+1];		/*48--*/   /**/
	struct   prvData  prvData;	/*48*/
	char          txnCuuCod[4];     /*49*/			/*���Ҵ���*/
	char		 pinDat[8];		/*52*/
	//unsigned long pinDat;           /*52*/			/*PINDAT*/
	double        addAmunt;         /*54*/ /*���ɽ�*/
	char	      batchid;		/*66*/			/*ת������־*/
	char          netMngInfo[4];    /*70*/		/*301 TEST INFO*/
												/*001 LOGIN*/
												/*002 LOGOUT */
	char	      feeDat[11];	/*78*/			/*��������*/
	char	      openDate[11];	/*74*/			/*��������*/
	char	      firstTxnDate[11]; /*75*/			/*��ʼ��������*/
	char	      stopTxnDate[11];  /*76*/			/*��ֹ��������*/
	char	      batchDealDate[11];/*77*/			/*ת��������*/
	struct OrgDat OrgDatElm;        /*90*/			/*ԭʼ������Ϣ*/
	char          recvIntID[12];    /*100*/			/*���ջ�����*/
	char          chkAct[29];       /*102*/ 		/*�����ʺ�*/
	char	      addAcNo103[29];	/*103*/ /*bank acno*/   /*�����ʺ�*/
	char	      bankCode[6+1];	/*104*/	
	char	      englishNam[61];	/*105*/			/*Ӣ������*/
	char	      personID[106];	/*106*/			/*���֤*/
	char	      cusAddr[61];	/*107*/			/*ͨѶ��ַ*/
	char	      teleNo[21];	/*108*/			/*�绰*/
	char	      receiptNo[16];	/*109*/			/*�վݺ���*/
	unsigned char mac[8];           /*128*/			/* MAC У��*/
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


