#include "ksdevice.h"
#include "rwcard_dll.h"
//#define  Declspec _declspec(dllexport)
////#define RW_DLL_ extern "C" __declspec(dllexport)
//extern "C" Declspec void KSAPI SetErrMsg(const char *errmsg,const char *file,int line);
//extern "C" Declspec char* KSAPI GetErrMsg(char *errmsg);
//extern "C" Declspec char* KSAPI GetErrMsgByErrCode(int nErrCode,char* sErrMsg);
//extern "C" Declspec int KSAPI open_device(ks_reader_dev_t *dev);
//extern "C" Declspec int KSAPI close_device(ks_reader_dev_t *dev);
//extern "C" Declspec int KSAPI get_decard_slot(ks_reader_dev_t *dev,int SAMID);
//extern "C" Declspec int KSAPI request_card(ks_reader_dev_t *dev,char* phyid,KS_CARD_TYPE t);
//extern "C" Declspec int KSAPI halt(ks_reader_dev_t *dev);
//extern "C" Declspec int KSAPI beep(ks_reader_dev_t *dev);
//extern "C" Declspec int KSAPI beeperr(ks_reader_dev_t *dev);
//extern "C" Declspec int KSAPI login_card(ks_reader_dev_t *dev,ks_card_info_t *card,int sect_no, KS_MF_KEYTYPE keytype,const uint8 *key);
//extern "C" Declspec int KSAPI read_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,uint8 *block);
//extern "C" Declspec int KSAPI write_block(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,const uint8 *block);
//extern "C" Declspec int KSAPI decrement_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount);
//extern "C" Declspec int KSAPI increment_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no,int amount);
//extern "C" Declspec int KSAPI transform_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no);
//extern "C" Declspec int KSAPI restore_card(ks_reader_dev_t *dev,ks_card_info_t *card,int block_no);
//extern "C" Declspec int KSAPI procard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd);
//extern "C" Declspec int KSAPI cpucard_poweron(ks_reader_dev_t *dev,KS_CARD_TYPE t,uint8 *len,uint8 *buf);
//extern "C" Declspec int KSAPI reset(ks_reader_dev_t *dev,size_t msec);
//extern "C" Declspec int KSAPI cpucard_setpara(ks_reader_dev_t *dev);
//extern "C" Declspec int KSAPI cpucard_cmd(ks_reader_dev_t *dev,ks_cpu_cmd_t *cmd,KS_CARD_TYPE t);
//extern "C" Declspec int KSAPI config_card(ks_reader_dev_t *dev,KS_CPUCARD_TYPE t);
//extern "C" Declspec int KSAPI card_type();
//extern "C" Declspec void KSAPI set_logger(void *para);
//extern "C" Declspec int KSAPI register_device_op(ks_device_op_t *op);
//RW_DLL_ void myhex2dec(const char *sHexStr,int iHexLen,unsigned char *uDecBuf,int& iDecBUfLen);