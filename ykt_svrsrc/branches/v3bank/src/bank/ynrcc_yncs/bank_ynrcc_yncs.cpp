/* ----------------------------------------------------------
 * 程序名称：bank_ynrcc_yncs.cpp
 * 创建日期：2011-07-14
 * 程序作者：王彦兵
 * 版本信息：1.0.0.0
 * 程序功能：云交职-云南省农村信用接口
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include "shem.h"
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_ynrcc_yncs.h"
#include "tcp.h"
#include "d3des.h"


//协议确认，撤销
int Bank_Bind_Process(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg, bool bFlag)
{
    int ret = 0;
    char host[16] = "";     //对方机器的ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    //TODO 生成发送报文
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LSAFE_LEVEL, F_VSVARSTR0, F_SCARD0, 0);
    out_pack->lsafe_level = E_COMMON_ERR;
    des2src(host, rPack->scust_auth);                       // 银行ip
    port = rPack->lvol0;                                // 银行端口
    timeout = rPack->lvol1 * 1000;                          // 等待银行超时时间(毫秒)
    writelog(LOG_INFO, "bank info:  ip_addr[%s],port[%d],timeout[%d] ", host, port, timeout);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "连接银行错误");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // 发送时，端口有问题，包括被关闭
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "发送数据错误");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // 不应该出现这种情况
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    writelog(LOG_DEBUG, "Send ret [%d] ", ret);
    memset(msg, 0, sizeof msg);
    memset(tmp, 0, sizeof tmp);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // 收报文长度
    if (ret != 4)
    {
        writelog(LOG_ERR, "开户接收银行数据长度错误");
        strcpy(szMsg, "开户接收银行数据长度错误");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    writelog(LOG_DEBUG, "开户接收银行数据包长ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // 收报文内容
    if (ret != msglen)
    {
        writelog(LOG_ERR, "开户接收银行数据包体错误");
        strcpy(szMsg, "开户接收银行数据包体错误");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    tcpsocket.Close();
    //TODO 解析银行返回报文
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}


//协议确认
int Bank_Bind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
    return Bank_Bind_Process(handle, rPack, pRetCode, szMsg, true);
}


//协议撤销
int Bank_UnBind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
    return Bank_Bind_Process(handle, rPack, pRetCode, szMsg, false);
}

int Bank_Querybind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
    //return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,QUERY_BIND);
    return 0;
}

//转账
int Bank_Trans(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char host[16] = "";     //对方机器的ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    // TODO 生成发送报文
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SPHONE, 0);
    des2src(host, rPack->scust_auth);                   // 银行ip
    port = rPack->lvol0;                                // 银行端口
    timeout = rPack->lvol1 * 1000;                          // 等待银行超时时间(毫秒)
    writelog(LOG_INFO, "bank info:  ip_addr[%s],port[%d],timeout[%d] ", host, port, timeout);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "连接银行错误");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // 发送时，端口有问题，包括被关闭
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "发送数据错误");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // 不应该出现这种情况
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    writelog(LOG_DEBUG, "Send ret [%d] ", ret);
    memset(msg, 0, sizeof msg);
    memset(tmp, 0, sizeof tmp);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // 收报文长度
    if (ret != 4)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //超时 或 接收数据错误 ，后台应向银行发冲正
        writelog(LOG_ERR, "充值接收银行数据包体错误");
        goto r_ret;
    }
    writelog(LOG_DEBUG, "充值接收银行数据包长ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // 收报文内容
    if (ret != msglen)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //超时 或 接收数据错误 ，后台应向银行发冲正
        writelog(LOG_ERR, "充值接收银行数据包体错误");
        goto r_ret;
    }
    tcpsocket.Close();
    //TODO 解析银行返回报文
r_ret:
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}

// 冲正
int Bank_Reverse(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char host[16] = "";     //对方机器的ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    // TODO 生成发送报文
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SCERT_NO, F_SPHONE, 0);
    des2src(host, rPack->scust_auth);                   // 银行ip
    port = rPack->lvol0;                                // 银行端口
    timeout = rPack->lvol1 * 1000;                              // 等待银行超时时间
    writelog(LOG_INFO, "Connect to bank ip_addr[%s],port[%d] ", host, port);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "连接银行错误");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // 发送时，端口有问题，包括被关闭
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "发送数据错误");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // 不应该出现这种情况
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    memset(msg, 0, sizeof msg);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // 收报文长度
    if (ret != 4)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //超时 或 接收数据错误 ，后台应向银行发冲正
        writelog(LOG_ERR, "冲正接收银行数据包长错误");
        goto r_ret;
    }
    writelog(LOG_DEBUG, "冲正接收银行数据包长ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // 收报文内容
    if (ret != msglen)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //超时 或 接收数据错误 ，后台应向银行发冲正
        writelog(LOG_ERR, "冲正接收银行数据包体错误");
        goto r_ret;
    }
    tcpsocket.Close();
    //TODO 解析银行返回报文
r_ret:
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}

// 查询银行卡余额
int Bank_Querybala(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char host[16] = "";     //对方机器的ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    // TODO 生成发送报文
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SALL_NAME, F_DAMT0, F_DAMT1, 0);
    des2src(host, rPack->scust_auth);                       // 银行ip
    port = rPack->lvol0;                                // 银行端口
    timeout = rPack->lvol1 * 1000;                          // 等待银行超时时间
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "连接银行错误");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // 发送时，端口有问题，包括被关闭
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "发送数据错误");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // 不应该出现这种情况
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    memset(msg, 0, sizeof msg);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // 收报文长度
    if (ret != 4)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //超时 或 接收数据错误 ，后台应向银行发冲正
        writelog(LOG_ERR, "查询余额接收银行数据包长错误");
        goto r_ret;
    }
    writelog(LOG_DEBUG, "查询余额接收银行数据包长ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // 收报文内容
    if (ret != msglen)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //超时 或 接收数据错误 ，后台应向银行发冲正
        writelog(LOG_ERR, "查询余额接收银行数据包体错误");
        goto r_ret;
    }
    tcpsocket.Close();
    //TODO 解析银行返回报文
    writelog(LOG_INFO, "querybala:cutname[%s],actbala[%f],actavlbala[%f]", out_pack->sall_name, out_pack->damt0, out_pack->damt1);
r_ret:
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}


//  对帐请求
int Bank_Checkacc(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    int msglen = 0;
    char host[16] = "";     //对方机器的ip
    char tmp[120] = "";
    short port = 0;
    int timeout = 0;
    unsigned char msg[4096] = "";
    char retcode[5];
    CTcpSocket tcpsocket ;
    // TODO 生成发送报文
    des2src(host, rPack->scust_auth);                       // 银行ip
    port = rPack->lvol0;                                // 银行端口
    timeout = rPack->lvol1 * 1000;                          // 等待银行超时时间(毫秒)
    writelog(LOG_INFO, "bank info:  ip_addr[%s],port[%d],timeout[%d] ", host, port, timeout);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "连接银行错误");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // 发送时，端口有问题，包括被关闭
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "发送数据错误");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // 不应该出现这种情况
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank，CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    writelog(LOG_DEBUG, "Send ret [%d] ", ret);
    memset(msg, 0, sizeof msg);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // 收报文长度
    if (ret != 4)
    {
        writelog(LOG_ERR, "对账接收银行数据长度错误");
        strcpy(szMsg, "对账接收银行数据长度错误");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    writelog(LOG_DEBUG, "对账接收银行数据包长ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // 收报文内容
    if (ret != msglen)
    {
        writelog(LOG_ERR, "对账接收银行数据包体错误");
        strcpy(szMsg, "对账接收银行数据包体错误");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    tcpsocket.Close();
    //TODO 解析银行返回报文
    return 0;
}

