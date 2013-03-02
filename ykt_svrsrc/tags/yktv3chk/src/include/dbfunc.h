#ifndef __DB_FUNC_H_
#define __DB_FUNC_H_
//#ifdef __cplusplus
//extern "C" {
//#endif
#include "pubdb.h"
#include "cpack.h"

// ����Ӱ������
#ifdef ESQL_DB2
#define EFFECT_ROWS sqlca.sqlerrd[3]
#elif defined ESQL_ORA
#define EFFECT_ROWS sqlca.sqlerrd[3]
#endif


int getNewUniqNo(char *sTypeCode,int *iUniqno);
int getNewVocNo(int iType,char  *sVocNo);
int getNewActno(char *sNewActno);
int IsActNoInvalid(char *actno);
int GetActnoByCardIdAndPurseId(char *actno,int cardid,int purseid);

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
/*
	����: ȡϵͳ�߼�����
	����: ����
	����: int       	0���ɹ��� ��0��SQLCODE
	����: char *buf	      	�洢�õ����߼����ڣ���ʽ��08/18/2004��char buf[10]
*/
int GetLogicDate(char * const buf);
/*
	����: ����ϵͳ�߼�����
	����: ����
	����: int       	0���ɹ���  ��0��SQLCODE
	����: int dateNum      	��ǰ�߼����ڻ��������ӣ�������/���٣�������������,Ϊ����
*/
int SetLogicDate(const int dateNum);
/*
	����: ȡȫ�ֲ���
	����������ȫ�ֲ���ID�������ݿ��в���ֵȡ������buf��
	����: ����
	����: int       	0���ɹ��� ��0��SQLCODE
	����: int ParaID      	ȫ�ֲ�����ID�����������ο�ȫ�ֲ����궨��
	����: char* buf      	�洢ȫ�ֲ���ֵ��char buf[100]
*/
int GetParameter(const int ParaID,char* const buf);
/*
	����: ����ȫ�ֲ���
	����������ȫ�ֲ���ID����buf�е����ݸ������ݿ��в���ֵ
	����: ����
	����: int       	0���ɹ��� ��0��SQLCODE
	����: int ParaID      	ȫ�ֲ�����ID�����������ο�ȫ�ֲ����궨��
	����: char* buf      	�洢ȫ�ֲ���ֵ��char buf[100]
*/
int SetParameter(int ParaID,char* buf);

int  get_errcode_msg(int ecode,char *emsg);
int  UpdMsgStatByMsgId(T_t_tif_meslist *meslist);
//����������ˮ��״̬�ͷ�����
//int  UpdCosumelogBySerialNo(int  serialno,T_t_tif_cosume_log *pCosumelog);
//���¿�������ˮ��״̬�ͷ�����
//int  UpdCardmessBySerialNo(int  serialno,T_t_tif_cardmess *pCardmess);

int  UpdTradeserialBySerialNo(int  serialno,T_t_tif_tradeserial *pTradeserial);
//��������	:�����豸ID�����ڡ�ʱ��,��ѯ�̻��豸���õ��̻�ID
//����		:   devid 	int��		�����豸ID
//����		:   txdate 	char[11]����������
//����		:   txtime 	char[9]��	����ʱ��
//���		:   shpid 	int��		�̻�ID
//����		:   fee_code int		�շѿ�Ŀ����
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
int get_shpId_by_devId_date_time(int  *shpid,int devid,char *txdate,char *txtime,int fee_code);

//��������	: �����̻�ID��ѯ�̻����õ��ͻ���
//����		:   shpid 	int���̻�ID
//���		:   custid  	int *	���ͻ���
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
int  get_customid_by_shpid(int *custid,int shpid);

//��������	: ���ݿͻ��ź��ʻ�����ѯ�ʻ���õ��˺�
//����		:   devid 	int��		�����豸ID
//����		:   txdate 	char[11]����������
//����		:   txtime 	char[9]��	����ʱ��
//���		:   actno  	char[17]	�ʺ�
//����ֵ	:   0	 --�ɹ�
//����ֵ	:  �ǣ�--��Ӧ�Ĵ�����
int get_actno_by_devId_date_time(char *actno,int devid,char *txdate,char *txtime);

//��齻���Ƿ��Ѿ�����
//int IsExistCosumelogDetail(T_t_tif_cosume_log *p);
//int IsExistCardMessDetail(T_t_tif_cardmess *p);
//�õ��̻��շѱ������ֵ
int GetMaxFeeRatioFromShop(double * maxfeeratio);
//�̻�������������ȡ�������������������ѽ��ϲ���һ����¼��
int DB_v_tif_shopdeptfee_open_select_by_c5();
int DB_v_tif_shopdeptfee_fetch_select_by_c5(T_t_tif_report_shop_balance *pv_tif_shopdeptfee);
int DB_v_tif_shopdeptfee_close_select_by_c5();
//��Ŀ����Ķ�Ӧ��ͼ��������ȡ�����ͬ������
int DB_v_tif_acttype_trade_open_select_by_c5();
int DB_v_tif_acttype_trade_fetch_select_by_c5(T_t_tif_subject_balance *pv_tif_acttype);
int DB_v_tif_acttype_close_select_by_c5();
//�޸��豸ǩ�������豸״̬��־���޸�Ϊδǩ��
int DB_t_device_update_by_subsystem_type(int v_subsystem_id,int v_status);
//�޸Ŀ�״̬(����Ϣ)
int UpdateCardState(int cardno,int state_type,char flag);
//����ѧ�ŵõ����Ľ��׿���
int get_tradecardno_by_stupid(char *stupid,int *cardno);
//�ж��Ƿ��й���
int IsExistCardByCustomId(int custom_id);
int IsExistCardByPhyCardNo(char *phycardno);
//�õ���ʧ����
int GetLostCardIdByCustomId_TypeId(int customid,int type_id,int *o_card_id);
//�õ���ʧ����
int GetLostCardIdByCustomId(int customid,int *o_card_id);
//�����ʽ������Ч��
int GetCardValiddate(int custtype,char *logicdate,char *validdate);
//�����ʱ������Ч��
int GetTempCardValiddate(int card_type,char *logicdate,char *validdate);
//��ÿ�״̬
int GetCardState(int cardid,char  *stateid1);
//��ù�ʧ������Ч����
int GetLostCardValiddate(char *logicdate,char *validdate);
//�жϿͻ��Ƿ��п�
int IsExistCardByCustomId(int custom_id);
//�жϿ��Ƿ��Ѿ�ʹ��
int IsExistCardByPhyCardNo(char *phycardno);
//�жϿͻ��Ƿ������ʱ��
int IsExistTmpCardByCustomId(int customid);
//�жϿͻ��Ƿ���ڷǹ�ʧ״̬�Ŀ�
int IsExistNoLostCardByCustomId(int customid);
//�����ʻ����͵õ��������ʻ��ĸ���
int Get_Account_Count_by_AccType(double *count,int acctype);
//�����˻����͵õ��������˻����ܽ��
int Get_Account_SumMoney_by_AccType(double *SumMoney,int acctype);
//�����̻��˻��Ŀͻ����жϸ��̻��Ƿ�Ϊ���������̻�--by hhd
int JudgeShopAccountType(int custid,int * indep_yes_no);
int  UpdateCardLossInfoState(int cardno,int before_state, int after_state);
int IsExistDeviceByShopId(int shop_id,char *logicdate);
int IsExistSubNodeByShpId(int shop_id);
int IsExistSameShopName(char *shop_name,int shop_id);
int AddMsgLst(T_t_tif_meslist *pMeslist);
int UpdMsgLst(T_t_tif_meslist *pMeslist);
int GetTempPersonId(char  *sTmpId);
//�˶���ϵͳ��Կ
int chk_dyn_key(int system_id,char *key);
int chk_card_pwd(char *stu_no,char *card_pwd);
int chk_card_pwd_by_showcardno(char  *showcardno,char *card_pwd,int *card_no);
int get_max_black_list_version(char blackver[13]);
int get_subsysid_by_phyid(char *devphyid,int *subsys_id);
int get_subsysid_by_devid(int devid,int* subsys_id);
int get_devinfo_by_phyid(char *devphyid,T_t_device *pt_pif_device);
int IsNoWorkTimeByDevId(int dev_id);
int ChkWorkTimeConflict(int shop_id,int deviceid,char *logic_date,char *begin_date,char *end_date,char *begin_time,char *end_time,int id);
int ChkWorkTimeConflict2(int shop_id,int deviceid,char *logic_date,char *begin_date,char *end_date,char *begin_time,char *end_time,int id,int fee_code);
int getdata(T_t_tif_tradeserial *pTradeserial,T_t_tif_rcvdtl *pRcvdtl);
int process930030(T_t_tif_tradeserial *pTradeserial);
int process930031(T_t_tif_tradeserial *pTradeserial);
int process930033(T_t_tif_tradeserial *pTradeserial);
int process930034(T_t_tif_tradeserial *pTradeserial);
int process930036(T_t_tif_tradeserial *pTradeserial);
int DB_t_tif_tradelog_del_all_by_step_commit();
int DB_t_tif_tradeserial_del_all_by_step_commit();
int DB_t_tif_meslist_del_all_by_step_commit();
int DB_t_tif_meslist_del_all_in_03_04_60_by_step_commit();
int IsExistShowCardNo(char *showcardno);
int chk_oper_pwd(char *oper_no,char *oper_pwd);
int get_datetime_from_db(char *dbdate,char* dbtime);
int ChkSavdtl(int card_no,T_t_tif_savdtl *pSavdtl);
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
int Db_t_tif_tradelog_backup_by_bak_date(char* logic_date);
int Db_t_tif_tradeserial_backup_by_bak_date(char* logic_date);
int Db_v_door_txdtl_his_backup();
int Db_t_door_txdtl_del_all_by_step_commit();
int Db_t_tif_report_depttrade_generate();
//���һ��ͨϵͳ�Ƿ񲻴��ڸ�ѧ/����
int IsInexistenceStuEmp(char *stuempno);
int stat_subsidy_amount_by_batchno(char *batchno,int *total_cnt,double *total_amt);
int update_subsidy_info_by_batchno(T_t_subsidy *pSubsidy);
int Db_v_blklst_lost_return_lost_date(int card_no,char *lost_date);
//���ݿ��ŵõ�ѧ��
int get_stuempno_by_card_no(int card_no,char *stuempno);
//����ѧ�ŵõ��ͻ���
int get_custid_by_stuempno(char *stuempno,int* custid);
//����ѧ�Ÿ��¿ͻ����κ�
int UpdCustomerBatch_noByStuemp_no(char *stuempno,char *batchno);
//�õ�Ȧ����ϵͳ����ϵͳid
int GetTransferSystemId();
//ȡ�ö���Ŀͻ���Ϣ,withhold��ʽ��
int DB_t_customer_open_select_with_hold_by_cur3_and_frozen_status(int v_frozen_status);
int DB_t_customer_fetch_select_by_cur3(T_t_customer *pt_cif_customer);
int DB_t_customer_close_select_by_cur3();
int GetCardMaxBlkVerNo(int cardno,char *blkverno);
int chkShowCardNo(char *opercode,int cardtype,char *showcardno);
int getAccDate(char *accdate);
int getTermSeqno(int termid,int* seqno);
int getParaVal(int paraid,char *paraval);
int getCardBookRecordNo(int& recordno);
int getCardVerNo(char *cardverno);
int addCardVerNo(T_t_cardver& cardver);
int getSubsidyCardNo(int custid,int& cardno);
int addoperdtl(ST_PACK *rPack);
int getNewTermID(int& termid);
//#ifdef __cplusplus
//}
//#endif
#endif
