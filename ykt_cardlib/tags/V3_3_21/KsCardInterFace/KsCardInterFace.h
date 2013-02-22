#ifndef KSCARDINTERFACE_H
#define KSCARDINTERFACE_H
int __stdcall KS_OpenPort(int port, int baud);
//��ͨѶ�˿�
int __stdcall KS_OpenCommPort();
int __stdcall KS_ClosePort();
//���׳ɹ���ʾ�������϶�
void __stdcall KS_Beep();
//���ִ���ʱ������ʹ�øú���ʹ����������һ��
void _stdcall KS_BeepErr();
void __stdcall KS_GetLastErrMsg(char *sMsg);
int __stdcall KS_Init();
int __stdcall KS_RequestCard(char *sCardPhyID);
void __stdcall KS_Reset();
void __stdcall KS_SetReadFieldName(char *sFieldName);
int __stdcall KS_GetFieldVal(char *sFieldName,char *sFieldVal);
int __stdcall KS_ReadCard();
int __stdcall KS_CheckCardStatus();
int __stdcall KS_Halt();
int __stdcall KS_LoadCardKeys(const char *pwd);
//KS_Login�����汾�Ѳ��ã�ʹ��KS_SignIn����
int __stdcall KS_Login(int& nShopID,char sShopName[61]);
//KS_Pay�����汾�Ѳ��ã�ʹ��KS_PayProcess����
int __stdcall KS_Pay(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac);
int __stdcall KS_PayCancel(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefNo,char *sMac);
//ȡ������Ϣ
char* __stdcall KS_GetErrMsg(char *msg);
//ǩ��
int __stdcall KS_SignIn(int* nShopID,char sShopName[61]);
//�����豸�û�ǩ��
int __stdcall KS_UserSignIn(const char *user,const char* passwd);
//�۷�Ԥ����
int __stdcall KS_PayPrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefno,char *sMac);
//�ӿ����
int __stdcall KS_CardBalanceInc(char* cGetProveFlag);
//�ۿ����
int __stdcall KS_CardBalanceDec(char* cGetProveFlag);
//ȡ����ȷ��
int __stdcall KS_GetProve(char* cReWriteCardFlag);
//����ȷ��ʧ�ܴ���,����ۿ������;�ο�,����û�ж���,�����һ�º�������
int __stdcall KS_UnProveProcess();
//��ʽ�ύ��������
int __stdcall KS_PayProcess();
//���ѳ���
int __stdcall KS_PayCancelProcess(const char *sRefNo,const char *sMac,const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt);
//��ȡ��״̬
int __stdcall KS_GetCardStatus(int cardno,char *statuscode,char *statusinfo);

//��ֵԤ����
int __stdcall KS_RechangePrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt,int nTransAmt,char *sRefno,char *sMac);
//����ϵͳ��ֵ
int __stdcall KS_RechangeProcess(int nRechangeAmt);
#endif

