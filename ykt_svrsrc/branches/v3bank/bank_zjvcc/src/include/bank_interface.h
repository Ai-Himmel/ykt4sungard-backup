#ifndef	__BANK_INTERFACE_H__
#define	__BANK_INTERFACE_H__#include "cpack.h"#include "bupub.h"
//#ifdef __cplusplus
//extern "C" {
//#endif#define 	TRADE_TRANS			240001		//����ת��#define	TRADE_REVERSE			240002		 //���п�ת�˹��ܳ���#define    BANK_QUERYBALA			240003		// ��ѯ���п����#define 	BANK_BIND				240004		//���п���#define 	BANK_UNBIND			240005		//���п������typedef struct{	char transtype;		//��������	char stuempno[31];	//ѧ��	char custname[31];	//����	char idno[31];		//���֤��	char bankcardno[21];//���п���	int  retcode;		//������	char retmsg[256];	//������}BankCardRelation;
///////////////////////////////int Bank_Trans(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Reverse(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Querybala(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Bind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_UnBind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Querybind(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_SignIn(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);int Bank_Checkacc(TRUSERID *handle,ST_PACK *rPack,int *pRetCode,char *szMsg);
//#ifdef __cplusplus
//}
//#endif

#endif

