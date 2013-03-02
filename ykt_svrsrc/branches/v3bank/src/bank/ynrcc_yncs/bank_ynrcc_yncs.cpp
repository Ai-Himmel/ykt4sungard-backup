/* ----------------------------------------------------------
 * �������ƣ�bank_ynrcc_yncs.cpp
 * �������ڣ�2011-07-14
 * �������ߣ������
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��ƽ�ְ-����ʡũ�����ýӿ�
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


//Э��ȷ�ϣ�����
int Bank_Bind_Process(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg, bool bFlag)
{
    int ret = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    //TODO ���ɷ��ͱ���
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LSAFE_LEVEL, F_VSVARSTR0, F_SCARD0, 0);
    out_pack->lsafe_level = E_COMMON_ERR;
    des2src(host, rPack->scust_auth);                       // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1 * 1000;                          // �ȴ����г�ʱʱ��(����)
    writelog(LOG_INFO, "bank info:  ip_addr[%s],port[%d],timeout[%d] ", host, port, timeout);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "�������д���");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "�������ݴ���");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    writelog(LOG_DEBUG, "Send ret [%d] ", ret);
    memset(msg, 0, sizeof msg);
    memset(tmp, 0, sizeof tmp);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // �ձ��ĳ���
    if (ret != 4)
    {
        writelog(LOG_ERR, "���������������ݳ��ȴ���");
        strcpy(szMsg, "���������������ݳ��ȴ���");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    writelog(LOG_DEBUG, "���������������ݰ���ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // �ձ�������
    if (ret != msglen)
    {
        writelog(LOG_ERR, "���������������ݰ������");
        strcpy(szMsg, "���������������ݰ������");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    tcpsocket.Close();
    //TODO �������з��ر���
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}


//Э��ȷ��
int Bank_Bind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
    return Bank_Bind_Process(handle, rPack, pRetCode, szMsg, true);
}


//Э�鳷��
int Bank_UnBind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
    return Bank_Bind_Process(handle, rPack, pRetCode, szMsg, false);
}

int Bank_Querybind(TRUSERID * handle, ST_PACK * rPack, int * pRetCode, char * szMsg)
{
    //return Bank_Bind_Process(handle, rPack, pRetCode, szMsg,QUERY_BIND);
    return 0;
}

//ת��
int Bank_Trans(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    // TODO ���ɷ��ͱ���
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SPHONE, 0);
    des2src(host, rPack->scust_auth);                   // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1 * 1000;                          // �ȴ����г�ʱʱ��(����)
    writelog(LOG_INFO, "bank info:  ip_addr[%s],port[%d],timeout[%d] ", host, port, timeout);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "�������д���");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "�������ݴ���");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    writelog(LOG_DEBUG, "Send ret [%d] ", ret);
    memset(msg, 0, sizeof msg);
    memset(tmp, 0, sizeof tmp);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // �ձ��ĳ���
    if (ret != 4)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        writelog(LOG_ERR, "��ֵ�����������ݰ������");
        goto r_ret;
    }
    writelog(LOG_DEBUG, "��ֵ�����������ݰ���ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // �ձ�������
    if (ret != msglen)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        writelog(LOG_ERR, "��ֵ�����������ݰ������");
        goto r_ret;
    }
    tcpsocket.Close();
    //TODO �������з��ر���
r_ret:
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}

// ����
int Bank_Reverse(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    // TODO ���ɷ��ͱ���
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SCERT_NO, F_SPHONE, 0);
    des2src(host, rPack->scust_auth);                   // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1 * 1000;                              // �ȴ����г�ʱʱ��
    writelog(LOG_INFO, "Connect to bank ip_addr[%s],port[%d] ", host, port);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "�������д���");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "�������ݴ���");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    memset(msg, 0, sizeof msg);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // �ձ��ĳ���
    if (ret != 4)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        writelog(LOG_ERR, "���������������ݰ�������");
        goto r_ret;
    }
    writelog(LOG_DEBUG, "���������������ݰ���ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // �ձ�������
    if (ret != msglen)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        writelog(LOG_ERR, "���������������ݰ������");
        goto r_ret;
    }
    tcpsocket.Close();
    //TODO �������з��ر���
r_ret:
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}

// ��ѯ���п����
int Bank_Querybala(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    int msglen = 0;
    char retcode[5];
    char tmp[120] = "";
    unsigned char msg[4096] = "";
    // TODO ���ɷ��ͱ���
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SALL_NAME, F_DAMT0, F_DAMT1, 0);
    des2src(host, rPack->scust_auth);                       // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1 * 1000;                          // �ȴ����г�ʱʱ��
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "�������д���");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "�������ݴ���");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    memset(msg, 0, sizeof msg);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // �ձ��ĳ���
    if (ret != 4)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        writelog(LOG_ERR, "��ѯ�������������ݰ�������");
        goto r_ret;
    }
    writelog(LOG_DEBUG, "��ѯ�������������ݰ���ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // �ձ�������
    if (ret != msglen)
    {
        tcpsocket.Close();
        out_pack->lvol1 = -1;                               //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        writelog(LOG_ERR, "��ѯ�������������ݰ������");
        goto r_ret;
    }
    tcpsocket.Close();
    //TODO �������з��ر���
    writelog(LOG_INFO, "querybala:cutname[%s],actbala[%f],actavlbala[%f]", out_pack->sall_name, out_pack->damt0, out_pack->damt1);
r_ret:
    PutRow(handle, out_pack, pRetCode, szMsg);
    return 0;
}


//  ��������
int Bank_Checkacc(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    int msglen = 0;
    char host[16] = "";     //�Է�������ip
    char tmp[120] = "";
    short port = 0;
    int timeout = 0;
    unsigned char msg[4096] = "";
    char retcode[5];
    CTcpSocket tcpsocket ;
    // TODO ���ɷ��ͱ���
    des2src(host, rPack->scust_auth);                       // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1 * 1000;                          // �ȴ����г�ʱʱ��(����)
    writelog(LOG_INFO, "bank info:  ip_addr[%s],port[%d],timeout[%d] ", host, port, timeout);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        strcpy(szMsg, "�������д���");
        return E_TRANS_CONNECT;
    }
    ret = tcpsocket.Send((char*)msg, msglen);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        strcpy(szMsg, "�������ݴ���");
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        tcpsocket.Close();
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    writelog(LOG_DEBUG, "Send ret [%d] ", ret);
    memset(msg, 0, sizeof msg);
    ret = tcpsocket.Recv(tmp, 4, timeout);                  // �ձ��ĳ���
    if (ret != 4)
    {
        writelog(LOG_ERR, "���˽����������ݳ��ȴ���");
        strcpy(szMsg, "���˽����������ݳ��ȴ���");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    writelog(LOG_DEBUG, "���˽����������ݰ���ret[%d],head[%s]", ret, tmp);
    msglen = atoi(tmp);
    ret = tcpsocket.Recv((char*)msg, msglen, timeout);                  // �ձ�������
    if (ret != msglen)
    {
        writelog(LOG_ERR, "���˽����������ݰ������");
        strcpy(szMsg, "���˽����������ݰ������");
        tcpsocket.Close();
        return E_TRANS_BANK_RECVERR;
    }
    tcpsocket.Close();
    //TODO �������з��ر���
    return 0;
}

