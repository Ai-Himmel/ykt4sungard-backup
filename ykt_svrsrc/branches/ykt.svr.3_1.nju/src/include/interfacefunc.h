#ifndef __INTERFACEFUNC_H
#define __INTERFACEFUNC_H
#include "pubdb.h"

//�˶�ǰ�û�ϵͳ��Կ
int ChkDynKey(int sysid,char *key);
//���������豸IDȡ�ն˱��
int GetDeviceidByDevphyid(char *devphyid,int* deviceid);
//�����豸IDȡ�豸���ʹ���
int GetDevtypecodeByDeviceid(int deviceid,char *devtypecode);
//�����豸��Ų�ѯ�̻���
int GetShopidByDeviceid(int deviceid,char *transdate,char *transtime,int* shopid);
//�����豸��Ÿ����豸�汾��
int GetDevCardVerNoByDeviceid(int deviceid,char *cardverno);
int UpdDevCardVerNoByDeviceid(int deviceid,char *cardverno);
int UpdDevRunstatusByDeviceid(int deviceid,char *runstatus);
int CardStatusInfoReadbyCardno(int cardno,T_t_card *card);
int DeviceStatusInfoReadbyDevphyid(char* devphyid,int* deviceid,char *status,char* runstatus);
int DeviceStatusInfoReadbyDeviceid(int deviceid,char* devphyid,char *status,char* runstatus);
int CardAccInfoReadbyAccno(char* cardaccno,T_t_account *account);
int ShopAccReadbyShopid(int shopid,char *shopaccno,int *shoptype,char *status);
#endif
