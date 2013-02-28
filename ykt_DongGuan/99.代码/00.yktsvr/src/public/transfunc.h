/* --------------------------------------------
 * ��������: 2010-06-17
 * ��������: �Ž�
 * �汾��Ϣ: 3.0.0.0
 * ������: �����״�����ģ��
 * --------------------------------------------*/
#ifndef TRANSFUNC_H_
#define TRANSFUNC_H_
#include "cpack.h"
#include "pubdb.h"
int CheckCardCntExist(int cardno,int cardcnt,int transdate);
int UpdateCardBitmap(int cardno,int cardcnt,char type);
int GetNewListVerno(char* listverno);
#if 0
int StopBalance();
int Startup();
int Cpack2Posdtl(ST_PACK *rPack,T_t_posdtl& posdtl);
int UpdPosdtlStatusByRowid(char *rowid,int errcode,char *status);
int UpdBusdtlStatusByRowid(char *rowid,int errcode,char *status);
int UpdPosdtlStatus(char *transdate,char *devphyid,int devseqno,int errcode,char *status);
int UpdCardBalByAccno(char *accno,double cardbal,int transflag,int cardcnt,int revflag,int offlineflag);
int UpdateTransdtlCurRevFlag(char *accdate,int termid,int termseqno);
int UpdateTransdtlHisRevFlag(char *transdtlname,char *accdate,int termid,int termseqno);
int UpdateTransdtlRevFlag(char *accdate,int termid,int termseqno);
//����ʧ����ˮ
//������;�ο�����ʧ����ˮ
int SaveConsumeFailTransdtl(T_t_posdtl& posdtl);
//����������ˮ
int SaveLockCardTransdtl(T_t_posdtl& posdtl);
//��������ȡ��
int PosTransCancelProcess(T_t_posdtl& posdtl);
//�ѻ�����
int PosOfflineTransProcess(T_t_posdtl& posdtl);
int UpdAllUnGetSubsidy(int cardno);

int OnlineTransRev(char *oldaccdate,int oldtermid,int oldtermseqno);
int AccTransRev(char *oldaccdate,int oldtermid,int oldtermseqno);

int GetTransPackStatus(char *packetid,char *reqid,T_t_transpack* transpack);
int UpdTranspackStatus(char *packetid,char *reqid,const T_t_transpack& transpack);
int SaveCardTransInfo();
#endif
#endif
