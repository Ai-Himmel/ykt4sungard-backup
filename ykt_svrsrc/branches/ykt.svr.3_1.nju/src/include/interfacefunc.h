#ifndef __INTERFACEFUNC_H
#define __INTERFACEFUNC_H
#include "pubdb.h"

//核对前置机系统密钥
int ChkDynKey(int sysid,char *key);
//根据物理设备ID取终端编号
int GetDeviceidByDevphyid(char *devphyid,int* deviceid);
//根据设备ID取设备机型代码
int GetDevtypecodeByDeviceid(int deviceid,char *devtypecode);
//根据设备编号查询商户号
int GetShopidByDeviceid(int deviceid,char *transdate,char *transtime,int* shopid);
//根据设备编号更新设备版本号
int GetDevCardVerNoByDeviceid(int deviceid,char *cardverno);
int UpdDevCardVerNoByDeviceid(int deviceid,char *cardverno);
int UpdDevRunstatusByDeviceid(int deviceid,char *runstatus);
int CardStatusInfoReadbyCardno(int cardno,T_t_card *card);
int DeviceStatusInfoReadbyDevphyid(char* devphyid,int* deviceid,char *status,char* runstatus);
int DeviceStatusInfoReadbyDeviceid(int deviceid,char* devphyid,char *status,char* runstatus);
int CardAccInfoReadbyAccno(char* cardaccno,T_t_account *account);
int ShopAccReadbyShopid(int shopid,char *shopaccno,int *shoptype,char *status);
#endif
