#ifndef _COM_FUN_NETCHARGE_H_
#define _COM_FUN_NETCHARGE_H_

#pragma once
#ifdef __cplusplus
extern "C" {
#endif

int GetAccoutInfo(char *szStuEmpNo, double *dRemainBalance);
int NetChargeTrans(char *szStuEmpNo, double *dRemainBalance, double *dTransBalance,char *oper);

#ifdef __cplusplus
}
#endif

#endif