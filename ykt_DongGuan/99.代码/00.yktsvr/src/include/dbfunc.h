#ifndef __DB_FUNC_H_
#define __DB_FUNC_H_
//#ifdef __cplusplus
//extern "C" {
//#endif
#include "pubdb.h"
#include "cpack.h"
#include "cpucard.h"

int getNewUniqNo(char *sTypeCode,int *iUniqno,int iMinVal=1);
//int getNewVocNo(int iType,char  *sVocNo);
//int GetNewCardAccno(char *cardaccno);
//int GetNewShopAccno(char *shopaccno);
//int GetNewNetAccno(char *netaccno);
int IsActNoInvalid(char *actno);
/**
* @brief ���ɰ汾�ţ��汾�Ÿ�ʽ yymmdd + 6λ��������6λ����0)
*
* @param sTypeCode - �汾�����ͣ���Ӧ������ű��е����ͣ�
* @param volume - [out] ���ɵİ汾�ţ�12λ�ַ���
*
* @return - �ɹ�����0��ʧ�ܷ�������SQLCODE
*/
int GetNewVolume(char *sTypeCode,char * volume);

//��������	:  ����999�豸����ID��ѯ�豸ID
//����		:   phyid 	char[9]�������豸ID
//���		:   devid  	int *	���豸ID
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
int GetDevIdByDevPhyId(int *devid,char *phyid);
int GetDevusageByDeviceID(int deviceid,int *devusage);

int SetLogicDate(const int dateNum);
/*
	����: ȡȫ�ֲ���
	����������ȫ�ֲ���ID�������ݿ��в���ֵȡ������buf��
	����: ����
	����: int       	0���ɹ��� ��0��SQLCODE
	����: int ParaID      	ȫ�ֲ�����ID�����������ο�ȫ�ֲ����궨��
	����: char* buf      	�洢ȫ�ֲ���ֵ��char buf[100]
*/
int GetSysParaVal(const int ParaID,char* const buf);
/*
	����: ����ȫ�ֲ���
	����������ȫ�ֲ���ID����buf�е����ݸ������ݿ��в���ֵ
	����: ����
	����: int       	0���ɹ��� ��0��SQLCODE
	����: int ParaID      	ȫ�ֲ�����ID�����������ο�ȫ�ֲ����궨��
	����: char* buf      	�洢ȫ�ֲ���ֵ��char buf[100]
*/
int SetSysParaVal(int ParaID,char* buf);

int  get_errcode_msg(int ecode,char *emsg);
//����������ˮ��״̬�ͷ�����
//int  UpdCosumelogBySerialNo(int  serialno,T_t_tif_cosume_log *pCosumelog);
//���¿�������ˮ��״̬�ͷ�����
//int  UpdCardmessBySerialNo(int  serialno,T_t_tif_cardmess *pCardmess);

//int  UpdTradeserialBySerialNo(int  serialno,T_t_tif_tradeserial *pTradeserial);
//��������	:�����豸ID�����ڡ�ʱ��,��ѯ�̻��豸���õ��̻�ID
//����		:   devid 	int��		�����豸ID
//����		:   txdate 	char[11]����������
//����		:   txtime 	char[9]��	����ʱ��
//���		:   shpid 	int��		�̻�ID
//����		:   fee_code int		�շѿ�Ŀ����
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
//int get_shpId_by_devId_date_time(int  *shpid,int devid,char *txdate,char *txtime,int fee_code);

//��������	: �����̻�ID��ѯ�̻����õ��ͻ���
//����		:   shpid 	int���̻�ID
//���		:   custid  	int *	���ͻ���
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
//int  get_customid_by_shpid(int *custid,int shpid);

//��������	: ���ݿͻ��ź��ʻ�����ѯ�ʻ���õ��˺�
//����		:   devid 	int��		�����豸ID
//����		:   txdate 	char[11]����������
//����		:   txtime 	char[9]��	����ʱ��
//���		:   actno  	char[17]	�ʺ�
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
//int get_actno_by_devId_date_time(char *actno,int devid,char *txdate,char *txtime);

//��齻���Ƿ��Ѿ�����
//int IsExistCosumelogDetail(T_t_tif_cosume_log *p);
//int IsExistCardMessDetail(T_t_tif_cardmess *p);
//�õ��̻��շѱ������ֵ
//int GetMaxFeeRatioFromShop(double* maxfeeratio);
//�̻�������������ȡ�������������������ѽ��ϲ���һ����¼��
//int DB_v_tif_shopdeptfee_open_select_by_c5();
//int DB_v_tif_shopdeptfee_fetch_select_by_c5(T_t_tif_report_shop_balance *pv_tif_shopdeptfee);
//int DB_v_tif_shopdeptfee_close_select_by_c5();
////��Ŀ����Ķ�Ӧ��ͼ��������ȡ�����ͬ������
//int DB_v_tif_acttype_trade_open_select_by_c5();
//int DB_v_tif_acttype_trade_fetch_select_by_c5(T_t_tif_subject_balance *pv_tif_acttype);
//int DB_v_tif_acttype_close_select_by_c5();
//�޸��豸ǩ�������豸״̬��־���޸�Ϊδǩ��
int DB_t_device_update_by_subsystem_type(int v_sysid,int v_status);
//�޸Ŀ�״̬(����Ϣ)
//int UpdateCardState(int cardno,int state_type,char flag);
//����ѧ�ŵõ����Ľ��׿���
int get_cardno_by_stuempno(char *stuempno,int *cardno);
int IsExistOtherNormalCardByCustid(int custid,int cardno);
//�ж��Ƿ��й���
int IsExistCardByCustomId(int custom_id);
int IsExistCardByPhyCardNo(char *phycardno);
//�õ���ʧ����
//int GetLostCardIdByCustomId_TypeId(int customid,int type_id,int *o_card_id);
//�õ���ʧ����4
int GetLostCardIdByCustomId(int customid,int *o_card_id);
//�����ʽ������Ч��
int GetCardValiddate(int custtype,char *logicdate,char *validdate);
//��ÿ�״̬
int GetCardState(int cardid,char  *status1);
//��ù�ʧ������Ч����
int GetLostCardValiddate(char *logicdate,char *validdate);
//�жϿͻ��Ƿ���������Ĺ�����ʱ��
int IsExistNormalTmpCardByCustid(int custid);
//�жϿͻ��Ƿ���������Ŀ�
int IsExistNormalCardByCustid(int customid);
//�жϿ��Ƿ��Ѿ�ʹ��
int IsExistCardByPhyCardNo(char *phycardno);
//�жϿͻ��Ƿ���ڷǹ�ʧ״̬�Ŀ�
//�����ʻ����͵õ��������ʻ��ĸ���
int Get_Account_Count_by_AccType(double *count,int acctype);
//�����˻����͵õ��������˻����ܽ��
int Get_Account_SumMoney_by_AccType(double *SumMoney,int acctype);
//�����̻��˻��Ŀͻ����жϸ��̻��Ƿ�Ϊ���������̻�--by hhd
int JudgeShopAccountType(int custid,int * indep_yes_no);
int  UpdateCardLossInfoState(int cardno,int before_state, int after_state);
int IsExistDeviceByShopId(int shop_id,char *logicdate);
int IsExistSameShopName(char *shop_name,int shop_id);
int GetTempPersonId(char  *sTmpId);
//�˶���ϵͳ��Կ
int chk_dyn_key(int system_id,char *key);
int chk_card_pwd(char *stu_no,char *card_pwd);
int chk_card_pwd_by_showcardno(char  *showcardno,char *card_pwd,int *card_no);
int get_max_black_list_version(char blackver[13]);
int get_subsysid_by_phyid(char *devphyid,int *subsys_id);
//int get_subsysid_by_deviceid(int deviceid,int* subsysid);
//int get_devinfo_by_phyid(char *devphyid,T_t_device *pt_pif_device);
int IsNoWorkTimeByDevId(int dev_id);
//int getdata(T_t_tif_tradeserial *pTradeserial,T_t_tif_rcvdtl *pRcvdtl);
//int process930030(T_t_tif_tradeserial *pTradeserial);
//int process930031(T_t_tif_tradeserial *pTradeserial);
//int process930033(T_t_tif_tradeserial *pTradeserial);
//int process930034(T_t_tif_tradeserial *pTradeserial);
//int process930036(T_t_tif_tradeserial *pTradeserial);
int chk_oper_pwd(char *oper_no,char *oper_pwd);
int get_datetime_from_db(char *dbdate,char* dbtime);
/************************************************************
 * д���������ݣ���ͨ��ǰ������ϵͳ����
 * Ŀǰֻ��Ҫ��2, 9 ���ֱ�־
 * @param cardid - ���׿���
 * @param flag - �������: 2 ע��9. ����
 *			   2 : CANCEL_BLACKLIST
 *			   9 : BLACK_BLACKLIST
 * @return - 0 ��ʾ�ɹ������򷵻ش���ԭ��Ĵ�����
*************************************************************/
int InsertToBlkList(int cardid,int flag);
/**
* @brief д��ͻ���Ϣ���¼�¼����ͨ��ǰ������ϵͳ����
*
* @param cardid - ���׿���
* @param flag - ��������
*				 ������Ϣ CUTUPD_UPDATE
*				 ע���ͻ� CUTUPD_CANCEL
*				 �����ͻ� CUTUPD_ADD
*
* @return - 0 ��ʾ�ɹ�,���򷵻ش����SQLCODE��
*/
int InsertToCutUpdList(int cardid,int flag,char phyno[9]);
//�жϿͻ��Ƿ���ڶ���״̬�Ŀ�
int IsExistFreezeCardByCustomId(int customid);
int get_latest_lost_date_by_card_no(int card_no,char *lost_date);
/*
 * �����еı�־Ϊ1 �ļ���ʼ��Ϊ0
*/
int InitializeSyskey();
//������Ա�Ƿ���ڣ�״̬�Ƿ�����
int chk_oper(char *oper_no);

int CheckNewCardHook(T_t_customer *customer,int newcardid);
int get_cardno_by_custid(int custid,int* cardno);
//����ѧ�Ÿ��¿ͻ����κ�
//�õ�Ȧ����ϵͳ����ϵͳid
int GetTransferSystemId();
//ȡ�ö���Ŀͻ���Ϣ,withhold��ʽ��
int GetCardMaxBlkVerNo(int cardno,char *blkverno);
int UseShowCardNo(char *opercode,char *showcardno,int& cardtype);
int UseShowCardNoRev(char *showcardno);
int UseShowCardNoBack(char *opercode,char *showcardno);
//int GetSysParaVal(int paraid,char *paraval);
//int getCardBookRecordNo(int& recordno);
int getCardVerNo(char *cardverno);
int addoperdtl(ST_PACK *rPack);
int getNewTermID(int& termid);
int UpdCardVerStatus(int cardno,int cardvertype);
bool IsDatabaseConnect(bool update=false);
int GetShopidByDevphyid(char *devphyid,char *transdate,char *transtime,int& deviceid,int& shopid);
int GetMaxShopFeeRate(double& shopfeerate);
int getTransName(int transtype,char *transname);
int DelCardAccDiffByCardno(int cardno);
//��ȡ���������汾��
int GetMaxBlackCardVerNo(char *cardverno);
int IsIdnoExist(char *idno,char *idtype);
int IsStuempnoExist(char *stuempno);
int UpdateCardExpireDate(int custid,char *expiredate);
//����У�������¿ͻ���
//��ȡǮ�������
int GetPurseMaxBal(int purseno,double& cardmaxbal);
//��������Ч�ʣ�����д�˶�ȡѧ�ŵĺ���
int GetStuempnoByCustid(int custid,char *stuempno);
int GetAccdtlTableName(char *accdate,char *accdtlname);
int GetTransdtlTableName(char *accdate,char *transdtlname);
int chk_cardpwd_by_cardno(int cardno,char *cardpwd);
// CPU ������ MAC2
int calc_cpucard_mac(cpu_trade_t *trade,char *mac,int mode);
int GetAccnoByCardno(int cardno,char *accno);
int GetCardAccInfoByCardNo(int cardno,int* custid,char *cardaccno,char *showcardno);
int GetCustBaseInfoByCustID(int custid,char *custname,char *stuempno,char *deptcode);
//int ReadTransdtlData(char *transdtlname,char *accdate,int termid,int termseqno,T_t_transdtl& transdtl);
int get_cardaddr(int cardno,int ctrlid,int listid,int adddel,int &cardaddr);
int update_cardaddr(int ctrlid,int listid);
int IsExistUnGetSubsidy(int cardno,int* existflag);
int GetCustIDByBankcardno(char *bankcardno,int* custid);
int ChkOperPwd(char *operno,char *operpwd);
int GetStuempnoByAccno(char* accno,char *stuempno);
int GetNewCardno(int deptcode,int* cardno);
int GetNewCardid(int* cardid);
int GetNewCardsn(int year,int factoryid,int apptype,int citycode, char *cardsn);
int GetNewMngrno(char* factorycode,char* cardtypecode,int cardverno,int year,char *cardmngrno);
int GetCardIDByCardasno(char* cardasno,int* cardid);
int GetCardnoByCardasno(char* cardasno,int* cardno);
int GetNewDevno(const char* devkeyid,char* devno);
int GetCardtypename(int cardtype,char* cardtypename);
int GetCustBaseInfo(int custid,char* custname,char* mobile);
int GetNewCardseqno(int cardno,int* cardseqno);
int GetNextRefseqno(int* refseqno);
int GetDevIDBySamno(const char *samno,int* devid);
//#ifdef __cplusplus
//}
//#endif
#endif
