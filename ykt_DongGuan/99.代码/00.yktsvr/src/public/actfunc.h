/* --------------------------------------------
 * ��������: 2010-08-10
 * ��������: �Ž�
 * �汾��Ϣ: 3.0.0.0
 * ������: ���������ģ��
 * --------------------------------------------*/
#ifndef ACTFUNC_H_
#define ACTFUNC_H_
#include "cpack.h"
#include "pubdb.h"
#include "acctrans.h"

#define VTSTATUS_MAKE		1	//ƾ֤¼��
#define VTSTATUS_CHECK		2	//ƾ֤����
#define VTSTATUS_ENTRY		3	//ƾ֤����

#define VTSOURCE_SYSTEM		0	//ϵͳ
#define VTSOURCE_MANMADE	1	//�ֹ�

#define AUTH_VOUCHERMAKE 	100	//ƾ֤¼��
#define AUTH_VOUCHERCHECK 	110	//ƾ֤���˼�ȡ��
#define AUTH_VOUCHERBOOK 	120	//ƾ֤����
#define AUTH_SHOPSUBJECT	130	//��Ŀӳ��

#define MAPTYPE_CARDACCNO	1	//���˻�
#define MAPTYPE_FORGIFT		2	//Ѻ���˻�
#define MAPTYPE_INCOMING	8	//�����Ŀ
#define MAPTYPE_PAYMENT		9	//֧����Ŀ
int CheckOperAuth(char *opercode,int authtype);
//��ȡ�µ�ƾ֤��
int GetNewVoucherNo(int periodyear,int periodmonth,int vouchertype,int* voucherno);
//ȡ��Чƾ֤����С��ƾ֤��
int GetInvalidMinVoucherNo(int vouchertype,int periodyear,int periodmonth,int& voucherno,int& voucherid);
//ƾ֤����
int VoucherAcctProcess(int voucherid);
int CheckExistUnEntryVoucher(int settledate,int& existflag);
//int GenSuperSubjSubjectMonthData(unsigned int superSubjno);
//int BatchGenSubjectMonth();
int LogoutOper();
//int GetAccShopid(int leafshopid,int* accshopid);
//int GetShopSubjnoByShopid(int shopid,char *subjno);
//int GetSubjnoByMapType(int maptype,char *subjno);
//int UpdShopaccSubjno(int accshopid,char *subjno);
//�����ϵͳ��һ��ʹ�ã������ڳ�����뵱ǰ����Ƿ���ͬ
int CheckFirstSubjBalBalance();
int VoucherEntryBaseCheck(int vouchertype, int periodyear, int periodmonth, int voucherno);
//ƾ֤������
int VouchernoReset(int periodmonth);
int MakeDayStatVoucher();

#endif
