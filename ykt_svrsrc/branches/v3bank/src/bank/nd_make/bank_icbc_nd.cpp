/* ----------------------------------------------------------
 * �������ƣ�bank_icbc_nd.cpp
 * �������ڣ�2010-11-05 14:58
 * �������ߣ�xlh
 * �汾��Ϣ��1.0.0.0
 * �����ܣ��Ĵ�ũ�������нӿ�
 * ----------------------------------------------------------
 * ----------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "pubdef.h"
#include "pubfunc.h"
#include "profile.h"
#include "bank_interface.h"
#include "bank_icbc_nd.h"
#include "tcp.h"
#include "bank.h"


#define STRLENCPY(des,src,len) strncpy(des,src,strlen(src)>len?len:strlen(src))

static void leftzstr(int len, char *intstr, char *outstr)
{
    int totallength = 0;
    int strlength = 0;
    strlength = strlen(intstr);
    totallength = len - strlength;
    for (int i = 0; i < totallength; i++)
    {
        strcat(outstr, " ");
    }
    strcat(outstr, intstr);
}
static void leftzstrzero(int len, char *intstr, char *outstr)
{
    int totallength = 0;
    int strlength = 0;
    strlength = strlen(intstr);
    totallength = len - strlength;
    for (int i = 0; i < totallength; i++)
    {
        strcat(outstr, "0");
    }
    strcat(outstr, intstr);
}
static void rithtzstr(int len, char *intstr, char *outstr)
{
    int totallength = 0;
    int strlength = 0;
    strlength = strlen(intstr);
    totallength = len - strlength;
    strcat(outstr, intstr);
    for (int i = 0; i < totallength; i++)
    {
        strcat(outstr, " ");
    }
}
//����ͨ�ýӿڹ淶���з�װ�������еĽӿ�
int Bank_CheckLine()
{
    return 0;
}
int Bank_Query(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char packlen[6] = "";
    char len[5] = "";
    int strlens = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    char temp[512] = "";
    char temp1[512] = "";
    char sendstr[1024] = "";
    char schoolCode[15] = "";
    int step = 0;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    char buf[256] = " ";
    char tmp[8] = "";
    des2src(host, rPack->scust_auth);                   // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1;                             // �ȴ����г�ʱʱ��
    //******************************************************************
    //��ͷ
    //******************************************************************
    QUERY_REQ query;
    memset(&query, 0x20, sizeof query);         // ���ո�
    QUERY_ANS ans;
    //******************************************************************
    //����
    //******************************************************************
    des2src(schoolCode, rPack->sphone2);
    writelog(LOG_ERR, "schoolCode=[%s] ", schoolCode);
    memcpy(query.body.DCC_CODE, QUERY_CODE, 6);  //������
    memset(temp, 0, sizeof temp);
    rithtzstr(10, schoolCode, temp);
    memcpy(query.body.DCC_SCHID, temp, 10);  //ѧУ����
    writelog(LOG_ERR, "schoolcode is [%s] ", query.body.DCC_SCHID);
    memset(temp, 0, sizeof temp);
    rithtzstr(8, rPack->sdate0, temp);
    memcpy(query.body.DCC_DATE, temp , 8); //��������
    memset(temp, 0, sizeof temp);
    memset(temp1, 0, sizeof temp1);
    sprintf(temp1, "%d", rPack->lvol6);
    rithtzstr(8, temp1, temp);
    memcpy(query.body.DCC_TERM, temp, 8); //�ն˺�
    memset(temp, 0, sizeof temp);
    leftzstrzero(6, "1000", temp);
    memcpy(query.body.DCC_LS, temp, 6);                      //һ��ͨ��ѯû����ˮ��
    memset(temp, 0, sizeof temp);
    rithtzstr(18, rPack->sphone, temp);
    memcpy(query.body.DCC_ID_NO, temp, 18); //ѧ����
    memset(temp, 0, sizeof temp);
    rithtzstr(20, rPack->scust_limit2, temp);
    memcpy(query.body.DCC_ACC_NO, temp, 20); //���п���
    writelog(LOG_ERR, "query.body.DCC_ACC_NO=[%s]", query.body.DCC_ACC_NO);
    memcpy(query.body.DCC_TYPE, "I", 1); //֤������
    memset(temp, 0, sizeof temp);
    rithtzstr(20, rPack->scust_auth2, temp);
    memcpy(query.body.DCC_NO, temp, 20); //֤������
    memset(temp, 0, sizeof temp);
    rithtzstr(20, rPack->scust_limit, temp);
    memcpy(query.body.DCC_NAME, temp, 20); //����
    memset(temp, 0, sizeof temp);
    rithtzstr(32, "test", temp);
    memcpy(query.body.DCC_DDP_RMRK, temp, 32); //ע��
    memset(temp, 0, sizeof temp);
    rithtzstr(32, "test", temp);
    memcpy(query.body.DCC_DEP_RMRK, temp, 32); //ע��
    memset(temp, 0, sizeof temp);
    rithtzstr(32, "test", temp);
    memcpy(query.body.DCC_DRW_RMRK, temp, 32); //ע��
    writelog(LOG_ERR, "Connect to bank ip_addr[%s],port[%d] ", host, port);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        return E_TRANS_CONNECT;
    }
    //���ͽṹ����������⣬���в�����������
    memset(sendstr, 0, sizeof(sendstr));
    memset(temp, 0, sizeof(temp));
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_CODE, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_SCHID, 10);
    strcat(temp, temp1);
    step = step + 10;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_DATE, 8);
    strcat(temp, temp1);
    step = step + 8;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_TERM, 8);
    strcat(temp, temp1);
    step = step + 8;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_LS, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_ID_NO, 18);
    strcat(temp, temp1);
    step = step + 18;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_ACC_NO, 20);
    strcat(temp, temp1);
    step = step + 20;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_TYPE, 1);
    strcat(temp, temp1);
    step = step + 1;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_NO, 20);
    strcat(temp, temp1);
    step = step + 20;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, query.body.DCC_NAME, 20);
    strcat(temp, temp1);
    step = step + 20;
    strlens = strlen(temp);
    sprintf(len, "%d", strlens);
    leftzstrzero(4, len, packlen);
    writelog(LOG_ERR, "query packlen[%s]", packlen);
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, packlen, 4);
    memset(sendstr, 0, sizeof(sendstr));
    rithtzstr(108, temp1, sendstr);
    strcat(sendstr, temp1);
    memcpy(sendstr + 108, temp, strlen(temp));
    writelog(LOG_ERR, "query sendstr[%s]", sendstr);
    ret = tcpsocket.Send(sendstr, strlens + 108);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    memset(temp, 0, sizeof temp);
    ret = tcpsocket.Recv(temp, 108, timeout);
//  writelog(LOG_ERR,"temp[%s]",temp);
    memcpy(ans.head.PACKLEN, temp, 4);
    memcpy(ans.head.RespCode, temp + 4, 4);
    memcpy(ans.head.RespMess, temp + 8, 100);
//  writelog(LOG_ERR,"recvhead len[%d]",ret);
    memset(temp, 0, sizeof temp);
    memcpy(temp, ans.head.PACKLEN, 4);
//  writelog(LOG_ERR,"temp[%s]",temp);
    strlens = atoi(temp);
    if (strlens == 0)
    {
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespMess, 100);
        memcpy(szMsg, temp, 100);
        writelog(LOG_ERR, "RespMess[%s]", temp);
        *pRetCode = E_TRANS_BANK_RECVERR;
        goto r_ret;
    }
    writelog(LOG_ERR, "PACKLEN[%d]", strlens);
    ret = tcpsocket.Recv((char*)&ans.body, strlens, timeout);
    tcpsocket.Close();
    writelog(LOG_ERR, "trans recv[%s],recvlen[%d]", ans.body.DCC_ID_NO, ret);
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_SEMP, F_LVOL1, F_SDATE0, F_DAMT0, F_DAMT1, F_SALL_NAME, F_SBANK_ACC, F_SBANK_ACC2, F_SCUST_AUTH, F_SCUST_AUTH2, F_SBANK_CODE, 0);
    if (ret != strlens)
    {
        out_pack->lvol1 = -1;                           //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        strcpy(szMsg, "�����������ݴ���");
        goto r_ret;
    }
    if (strncmp(ans.head.RespCode, "0000", 4) != 0)
    {
        memcpy(szMsg, ans.head.RespMess, 100);
        *pRetCode = E_TRANS_BANK_RECVERR;
        goto r_ret;  // ���ж˴������
    }
    else
    {
        out_pack->lvol1 = 1;// ǰ�ý��
        memcpy(out_pack->semp, ans.body.DCC_CODE, sizeof ans.body.DCC_CODE);                                          //���ܺ�
        memcpy(out_pack->sdate0, ans.body.DCC_DATE, sizeof ans.body.DCC_DATE);                      // ����
        memcpy(out_pack->scust_auth, ans.body.DCC_LS, sizeof ans.body.DCC_LS);                  //���� ��ˮ��
        memcpy(out_pack->scust_auth2, ans.body.DCC_ID_NO, sizeof ans.body.DCC_ID_NO);           //ѧ��
        memcpy(out_pack->sbank_acc, ans.body.DCC_ACC_NO, sizeof ans.body.DCC_ACC_NO);           //���п���
        memcpy(out_pack->sbank_code, ans.body.DCC_TYPE, sizeof ans.body.DCC_TYPE);          //֤������
        memcpy(out_pack->sbank_acc2, ans.body.DCC_NO, sizeof ans.body.DCC_NO);              //֤������
        memcpy(out_pack->sall_name, ans.body.DCC_NAME, sizeof ans.body.DCC_NAME);               //����
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_BAL, 18);
        if (strlen(temp) > 0)
        {
            out_pack->damt0 = atof(temp) / 100;                                      //�ʺ����
        }
        else
        {
            out_pack->damt0 = 0;
        }
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_AVL_BAL, 18);
        if (strlen(temp) > 0)
        {
            out_pack->damt1 = atof(temp) / 100;                   //�������
        }
        else
        {
            out_pack->damt1 = 0;
        }
        memcpy(out_pack->vsmess, ans.body.DCC_MEMO, sizeof ans.body.DCC_MEMO);                              //��ע
        PutRow(handle, out_pack, pRetCode, szMsg);
    }
    return 0;
r_ret:
    {
        PutRow(handle, out_pack, pRetCode, szMsg);
        return E_TRANS_BANK_RECVERR;
    }
}


int Bank_Trans(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char packlen[6] = "";
    char len[5] = "";
    int strlens = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    char temp[512] = "";
    char temp1[512] = "";
    char sendstr[1024] = "";
    int step = 0;
    double amt = 0.0;
    int testlen = 0;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    char logstr[256] = "";
    char buf[256] = " ";
    char tmp[8] = "";
    des2src(host, rPack->scust_auth);                   // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1;                             // �ȴ����г�ʱʱ��
    TRANS_REQ tran;
    TRANS_ANS ans;
    memset(&tran, 0x20, sizeof tran);       // ���ո�
    memset(&ans, 0x20, sizeof ans);         // ���ո�
    //******************************************************************
    //��ͷ
    //******************************************************************
    memcpy(tran.head.PACKLEN, packlen, 4); //���ױ��ĳ���
    //******************************************************************
    //����
    //******************************************************************
    memcpy(tran.body.DCC_CODE, TRANS_CODE, 6);  //������
    memset(temp, 0, sizeof temp);
    rithtzstr(10, rPack->sphone2, temp);
    memcpy(tran.body.DCC_SCHID, temp, 10);  //ѧУ����
    writelog(LOG_ERR, "schoolcode is [%s] ", tran.body.DCC_SCHID);
    memset(temp, 0, sizeof temp);
    rithtzstr(8, rPack->sdate0, temp);
    memcpy(tran.body.DCC_DATE, temp, 8); //��������
    memcpy(logstr, tran.body.DCC_DATE, sizeof tran.body.DCC_DATE);
    writelog(LOG_ERR, "DCC_DATE is [%s] ", logstr);
    memset(temp1, 0, sizeof temp1);
    memset(temp, 0, sizeof temp);
    sprintf(temp1, "%d", rPack->lvol6);
    rithtzstr(8, temp1, temp);
    memcpy(tran.body.DCC_TERM, temp, 8); //�ն˺�
    memcpy(logstr, tran.body.DCC_TERM, sizeof tran.body.DCC_TERM);
    writelog(LOG_ERR, "DCC_TERM is [%s] ", logstr);
    memset(temp, 0, sizeof temp);
    leftzstrzero(6, rPack->sholder_ac_no + 8, temp);
    memcpy(tran.body.DCC_LS, temp, 6);                      //һ��ͨ��ѯû����ˮ��
    memset(temp, 0, sizeof temp);
    rithtzstr(18, rPack->sphone, temp);
    memcpy(tran.body.DCC_ID_NO, temp, 18); //ѧ����
    memcpy(logstr, tran.body.DCC_ID_NO, sizeof tran.body.DCC_ID_NO);
    writelog(LOG_ERR, "DCC_ID_NO is [%s] ", logstr);
    memset(temp, 0, sizeof temp);
    rithtzstr(20, rPack->scust_limit2, temp);
    memcpy(tran.body.DCC_ACC_NO, temp, 20); //���п���
    memcpy(logstr, tran.body.DCC_ACC_NO, sizeof tran.body.DCC_ACC_NO);
    writelog(LOG_ERR, "DCC_ACC_NO is [%s] ", logstr);
    memcpy(tran.body.DCC_TYPE, "I", 1); //֤������
    memset(temp, 0, sizeof temp);
    rithtzstr(20, rPack->scust_auth2, temp);
    memcpy(tran.body.DCC_NO, temp, 20); //֤������
    memcpy(logstr, tran.body.DCC_NO, sizeof tran.body.DCC_NO);
    writelog(LOG_ERR, "sfz DCC_NO is [%s] ", logstr);
    memset(temp, 0, sizeof temp);
    rithtzstr(20, rPack->scust_limit, temp);
    memcpy(tran.body.DCC_NAME, temp, 20); //����
    memcpy(logstr, tran.body.DCC_NAME, sizeof tran.body.DCC_NAME);
    writelog(LOG_ERR, "DCC_NAME is [%s] ", logstr);
    memset(temp, 0, sizeof temp);
    memset(temp, 0, sizeof temp1);
    sprintf(temp1, "%d", 100 * (int)rPack->damt0); //���׽��
    leftzstr(18, temp1, temp);
    memcpy(tran.body.DCC_AMT, temp, 18); //���׽��
    memcpy(logstr, tran.body.DCC_AMT, sizeof tran.body.DCC_AMT);
    writelog(LOG_ERR, "DCC_AMT is [%s] ", logstr);
    memset(temp, 0, sizeof temp);
    rithtzstr(32, "test", temp);
    writelog(LOG_ERR, "DCC_DDP_RMRK[%s]", temp);
    memcpy(tran.body.DCC_DDP_RMRK, temp, 32); //ע��
    memset(temp, 0, sizeof temp);
    rithtzstr(32, "test", temp);
    writelog(LOG_ERR, "DCC_DEP_RMRK[%s]", temp);
    memcpy(tran.body.DCC_DEP_RMRK, temp, 32); //ע��
    memset(temp, 0, sizeof temp);
    rithtzstr(32, "test", temp);
    writelog(LOG_ERR, "DCC_DRW_RMRK[%s]", temp);
    memcpy(tran.body.DCC_DRW_RMRK, temp, 32); //ע��
    //writelog(LOG_ERR,"PACKLEN[%s]",tran.head.PACKLEN);
    memcpy(temp, tran.body.DCC_CODE, sizeof tran.body.DCC_CODE);
    //writelog(LOG_ERR," DCC_CODE[%s],DCC_SCHID[%s],DCC_DATE[%s],DCC_ID_NO[%s],DCC_ACC_NO[%s]",tran.body.DCC_CODE,tran.body.DCC_SCHID,tran.body.DCC_DATE,tran.body.DCC_ID_NO,tran.body.DCC_ACC_NO);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        return E_TRANS_CONNECT;
    }
//���ͽṹ����������⣬���в�����������
    memset(sendstr, 0, sizeof(sendstr));
    memset(temp, 0, sizeof(temp));
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_CODE, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_SCHID, 10);
    strcat(temp, temp1);
    step = step + 10;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_DATE, 8);
    strcat(temp, temp1);
    step = step + 8;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_TERM, 8);
    strcat(temp, temp1);
    step = step + 8;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_LS, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_ID_NO, 18);
    strcat(temp, temp1);
    step = step + 18;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_ACC_NO, 20);
    strcat(temp, temp1);
    step = step + 20;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_TYPE, 1);
    strcat(temp, temp1);
    step = step + 1;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_NO, 20);
    strcat(temp, temp1);
    step = step + 20;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_NAME, 20);
    strcat(temp, temp1);
    step = step + 20;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_AMT, 18);
    strcat(temp, temp1);
    step = step + 18;
    strlens = strlen(temp);
    sprintf(len, "%d", strlens);
    leftzstrzero(4, len, packlen);
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, packlen, 4);
    rithtzstr(108, temp1, sendstr);
    memcpy(sendstr + 108, temp, strlen(temp));
    writelog(LOG_ERR, "query sendstr[%s]", sendstr);
    ret = tcpsocket.Send(sendstr, strlens + 108);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    testlen = sizeof ans.head ;
    //ret = tcpsocket.Recv((char*)&ans.head, sizeof ans.head, timeout);
    memset(temp, 0, sizeof temp);
    ret = tcpsocket.Recv(temp, 108, timeout);
    writelog(LOG_ERR, "temp[%s]ret[%d]", temp, ret);
    memset(&ans, 0, sizeof ans);
    memcpy(ans.head.PACKLEN, temp, 4);
    memcpy(ans.head.RespCode, temp + 4, 4);
    memcpy(ans.head.RespMess, temp + 8, 100);
    memset(temp, 0, sizeof temp);
    memcpy(temp, ans.head.PACKLEN, 4);
    writelog(LOG_ERR, "�յ��İ��峤��[%s]", temp);
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_SEMP, F_LVOL1, F_DAMT0, F_SCUST_AUTH, F_SBANK_ACC, F_SBANK_ACC2, F_SBRANCH_CODE0, F_SALL_NAME, F_VSMESS, F_SPHONE, F_SPHONE2, F_SCUST_AUTH2, F_SDATE0, 0);
    strlens = atoi(temp);
    if (strlens == 0)
    {
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespMess, 100);
        memcpy(szMsg, temp, 100);
        writelog(LOG_ERR, "RespMess[%s]", temp);
        *pRetCode = E_TRANS_BANK_BODYLENERR;
        goto r_ret;
    }
    writelog(LOG_ERR, "lenbody[%d]", strlens);
    ret = tcpsocket.Recv((char*)&ans.body, strlens, timeout);
    tcpsocket.Close();
    /*
    if (ret!=strlens)
    {
        out_pack->lvol1 = -1;                           //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        strcpy(szMsg,"�����������ݴ���");
        goto r_ret;
    }
    */
    if (strncmp(ans.head.RespCode, "0000", 4) != 0)
    {
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespMess, 100);
        memcpy(szMsg, temp, 100);
        writelog(LOG_ERR, "RespMess[%s]", temp);
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespCode, sizeof ans.head.RespCode);
        writelog(LOG_ERR, "ans.head.RespCode[%s]", temp);
        writelog(LOG_ERR, "ans.head.RespMess[%s]", ans.head.RespMess);
        goto r_ret;  // ���ж˴������
    }
    else
    {
        out_pack->lvol1 = 1;
        memcpy(out_pack->semp, ans.body.DCC_CODE, sizeof ans.body.DCC_CODE);                                   //���ܺ�
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_CODE, sizeof ans.body.DCC_CODE);
        writelog(LOG_ERR, "ans.body.DCC_CODE[%s]", temp);
        memcpy(out_pack->sdate0, ans.body.DCC_DATE, sizeof ans.body.DCC_DATE);                      // ����
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_DATE, sizeof ans.body.DCC_DATE);
        writelog(LOG_ERR, "ans.body.DCC_DATE[%s]", temp);
        memcpy(out_pack->sphone, ans.body.DCC_BANK_LS, sizeof ans.body.DCC_BANK_LS);                //���� ��ˮ��
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_BANK_LS, sizeof ans.body.DCC_BANK_LS);
        writelog(LOG_ERR, "ans.body.DCC_BANK_LS[%s]", temp);
        memcpy(out_pack->sphone2, ans.body.DCC_LS, sizeof ans.body.DCC_LS);                 //���� ��ˮ��
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_LS, sizeof ans.body.DCC_LS);
        writelog(LOG_ERR, "ans.body.DCC_LS[%s]", temp);
        memcpy(out_pack->scust_auth2, ans.body.DCC_ID_NO, sizeof ans.body.DCC_ID_NO);           //ѧ��
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_ID_NO, sizeof ans.body.DCC_ID_NO);
        writelog(LOG_ERR, "ans.body.DCC_ID_NO[%s]", temp);
        memcpy(out_pack->sbank_acc, ans.body.DCC_ACC_NO, sizeof ans.body.DCC_ACC_NO);           //���п���
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_ACC_NO, sizeof ans.body.DCC_ACC_NO);
        writelog(LOG_ERR, "ans.body.DCC_ACC_NO[%s]", temp);
        memcpy(out_pack->sbranch_code0, ans.body.DCC_TYPE, sizeof ans.body.DCC_TYPE);       //֤������
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_TYPE, sizeof ans.body.DCC_TYPE);
        writelog(LOG_ERR, "ans.body.DCC_TYPE[%s]", temp);
        memcpy(out_pack->sbank_acc2, ans.body.DCC_NO, sizeof ans.body.DCC_NO);              //֤������
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_NO, sizeof ans.body.DCC_NO);
        writelog(LOG_ERR, "ans.body.DCC_NO[%s]", temp);
        memcpy(out_pack->sall_name, ans.body.DCC_NAME, sizeof ans.body.DCC_NAME);               //����
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_NAME, sizeof ans.body.DCC_NAME);
        writelog(LOG_ERR, "ans.body.DCC_NO[%s]", temp);
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_AMT, 18);
        if (strlen(temp) > 0)
        {
            out_pack->damt0 = atof(temp) / 100;                     //���
        }
        else
        {
            out_pack->damt0 = 0;
        }
        memcpy(out_pack->vsmess, "ת��ʧ�ܣ�������ȡ����", sizeof out_pack->vsmess);                             //��ע
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_MEMO, sizeof ans.body.DCC_MEMO);
        writelog(LOG_ERR, "ans.body.DCC_MEMO[%s]", temp);
        PutRow(handle, out_pack, pRetCode, szMsg);
    }
    return 0;
r_ret:
    {
        return E_TRANS_BANK_RECVERR;
    }
}

int Bank_Reverse(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char packlen[6] = "";
    char len[5] = "";
    int strlens = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    char temp[512] = "";
    char temp1[512] = "";
    char sendstr[1024] = "";
    int step = 0;
    double amt = 0.0;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    char buf[256] = " ";
    char tmp[8] = "";
    des2src(host, rPack->scust_auth);                   // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1;                             // �ȴ����г�ʱʱ��
    RECTRANS_REQ   tran;
    RECTRANS_ANS  ans;
    memset(&tran, 0x20, sizeof tran);       // ���ո�
    memset(&ans, 0x20, sizeof ans);         // ���ո�
    strlens = sizeof tran.body;
    sprintf(len, "%d", strlens);
    //writelog(LOG_ERR,"len[%s]",len);
    leftzstrzero(4, len, packlen);
    //******************************************************************
    //��ͷ
    //******************************************************************
    memcpy(tran.head.PACKLEN, packlen, 4); //��������
    //writelog(LOG_ERR,"PACKLEN[%s]",tran.head.PACKLEN);
    //******************************************************************
    //����
    //******************************************************************
    memcpy(tran.body.DCC_CODE, REV_TRANS_CODE, 6);  //������
    memset(temp, 0, sizeof temp);
    rithtzstr(10, rPack->sphone2, temp);
    memcpy(tran.body.DCC_SCHID, temp, 10);  //ѧУ����
    //writelog(LOG_ERR,"DCC_CODE[%s]",tran.body.DCC_CODE);
    writelog(LOG_ERR, "schoolcode is [%s] ", tran.body.DCC_SCHID);
    memset(temp, 0, sizeof temp);
    rithtzstr(8, rPack->sdate0, temp);
    memcpy(tran.body.DCC_DATE, temp, 8); //��������
    memset(temp, 0, sizeof temp);
    memset(temp1, 0, sizeof temp1);
    sprintf(temp1, "%d", rPack->lvol6);
    rithtzstr(8, temp1, temp);
    memcpy(tran.body.DCC_TERM, temp, 8); //�ն˺�
    memset(temp, 0, sizeof temp);
    leftzstrzero(6, rPack->sholder_ac_no + 8, temp);
    memcpy(tran.body.DCC_LS, temp, 6);                      //һ��ͨ��ˮ��
    memset(temp, 0, sizeof temp);
    memset(temp1, 0, sizeof temp1);
    leftzstrzero(9, rPack->sname, temp1);
    rithtzstr(20, temp1, temp);
    memcpy(tran.body.DCC_BANK_LS, temp, 20);                      //������ˮ��
    memset(temp, 0, sizeof temp);
    rithtzstr(40, "test", temp);
    memcpy(tran.body.DCC_MEMO, temp, 40); //ע��
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        return E_TRANS_CONNECT;
    }
    //���ͽṹ����������⣬���в�����������
    memset(sendstr, 0, sizeof(sendstr));
    memset(temp, 0, sizeof(temp));
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_CODE, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_SCHID, 10);
    strcat(temp, temp1);
    step = step + 10;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_DATE, 8);
    strcat(temp, temp1);
    step = step + 8;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_TERM, 8);
    strcat(temp, temp1);
    step = step + 8;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_LS, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_BANK_LS, 20);
    strcat(temp, temp1);
    step = step + 20;
    strlens = strlen(temp);
    sprintf(len, "%d", strlens);
    memset(packlen, 0, sizeof(packlen));
    leftzstrzero(4, len, packlen);
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, packlen, 4);
    rithtzstr(108, temp1, sendstr);
    memcpy(sendstr + 108, temp, strlen(temp));
    writelog(LOG_ERR, "sendstr[%s]", sendstr);
    ret = tcpsocket.Send(sendstr, strlens + 108);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    //ret = tcpsocket.Recv((char*)&ans.head, sizeof ans.head, timeout);
    memset(temp, 0, sizeof temp);
    ret = tcpsocket.Recv(temp, sizeof ans.head, timeout);
    writelog(LOG_ERR, "ret[%d] temp[%s]", ret, temp);
    memcpy(ans.head.PACKLEN, temp, 4);
    memcpy(ans.head.RespCode, temp + 4, 4);
    memcpy(ans.head.RespMess, temp + 8, 100);
    memset(temp, 0, sizeof temp);
    memcpy(temp, ans.head.PACKLEN, 4);
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_LVOL1, F_SDATE0, F_SEMP, F_SCERT_NO, F_SALL_NAME, F_VSMESS, 0);
    strlens = atoi(temp);
    if (strlens == 0)
    {
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespMess, 100);
        memcpy(szMsg, temp, 100);
        writelog(LOG_ERR, "RespMess[%s]", temp);
        *pRetCode = E_TRANS_BANK_RECVERR;
        goto r_ret;
    }
    writelog(LOG_ERR, "lenbody[%d]", strlens);
    ret = tcpsocket.Recv((char*)&ans.body, strlens, timeout);
    tcpsocket.Close();
    writelog(LOG_INFO, "trans DCC_BANK_LS[%s],recvlen[%d]", ans.body.DCC_BANK_LS, ret);
    if (ret != strlens)
    {
        out_pack->lvol1 = -1;                           //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        strcpy(szMsg, "�����������ݴ���");
        goto r_ret;
    }
    if (strncmp(ans.head.RespCode, "0000", 4) != 0)
    {
        memcpy(szMsg, ans.head.RespMess, 100);
        *pRetCode = E_TRANS_BANK_RECVERR;
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespCode, sizeof ans.head.RespCode);
        writelog(LOG_ERR, "ans.head.RespCode[%s]", temp);
        writelog(LOG_ERR, "ans.head.RespMess[%s]", ans.head.RespMess);
        goto r_ret;  // ���ж˴������
    }
    else
    {
        out_pack->lvol1 = 1;
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_CODE, sizeof ans.body.DCC_CODE);
        writelog(LOG_ERR, "ans.body.RespCode[%s]", temp);
        memcpy(out_pack->semp, ans.body.DCC_CODE, sizeof ans.body.DCC_CODE);                                   //���ܺ�
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_DATE, sizeof ans.body.DCC_DATE);
        writelog(LOG_ERR, "ans.body.DCC_DATE[%s]", temp);
        memcpy(out_pack->sdate0, ans.body.DCC_DATE, sizeof ans.body.DCC_DATE);                      // ����
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_BANK_LS, sizeof ans.body.DCC_BANK_LS);
        writelog(LOG_ERR, "ans.body.DCC_BANK_LS[%s]", temp);
        memcpy(out_pack->sall_name, ans.body.DCC_BANK_LS, sizeof ans.body.DCC_BANK_LS);             //������ˮ
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.body.DCC_MEMO, sizeof ans.body.DCC_MEMO);
        writelog(LOG_ERR, "ans.body.DCC_MEMO[%s]", temp);
        memcpy(out_pack->vsmess, ans.body.DCC_MEMO, sizeof ans.body.DCC_MEMO);                              //��ע
        PutRow(handle, out_pack, pRetCode, szMsg);
    }
    return 0;
r_ret:
    {
        //PutRow(handle,out_pack,pRetCode,szMsg);
        return E_TRANS_BANK_RECVERR;
    }
    // AnswerData(handle,*pRetCode,szMsg);
}

int Bank_Check(TRUSERID *handle, ST_PACK *rPack, int *pRetCode, char *szMsg)
{
    int ret = 0;
    char packlen[6] = "";
    char len[5] = "";
    int strlens = 0;
    char host[16] = "";     //�Է�������ip
    short port = 0;
    int timeout = 0;
    char temp[512] = "";
    char temp1[512] = "";
    char sendstr[1024] = "";
    int step = 0;
    double amt = 0.0;
    ST_CPACK aPack;
    ST_PACK *out_pack = &(aPack.pack);
    CTcpSocket tcpsocket ;
    ResetNormalCPack(&aPack, 0, 1);
    SetCol(handle, 0);
    SetCol(handle, F_SEMP, F_LVOL0, F_DAMT0, F_SDATE1, F_SCERT_NO, F_SALL_NAME, F_VSMESS, 0);
    char buf[256] = " ";
    char tmp[8] = "";
    des2src(host, rPack->scust_auth);                   // ����ip
    port = rPack->lvol0;                                // ���ж˿�
    timeout = rPack->lvol1;                             // �ȴ����г�ʱʱ��
    CHECK_REQ tran;
    CHECK_ANS ans;
    memset(&tran, 0x20, sizeof tran);       // ���ո�
    memset(&ans, 0x20, sizeof ans);         // ���ո�
    strlens = sizeof(tran.body);
    sprintf(len, "%d", strlens);
    leftzstrzero(4, len, packlen);
    //******************************************************************
    //��ͷ
    //******************************************************************
    memcpy(tran.head.PACKLEN, packlen, 4); //��������
    //******************************************************************
    //����
    //******************************************************************
    memcpy(tran.body.DCC_CODE, REV_TRANS_CODE, 6);  //������
    memset(temp, 0, sizeof temp);
    rithtzstr(10, rPack->sphone2, temp);
    memcpy(tran.body.DCC_SCHID, temp, 10);  //ѧУ����
    writelog(LOG_ERR, "schoolcode is [%s] ", tran.body.DCC_SCHID);
    memset(temp, 0, sizeof temp);
    rithtzstr(8, rPack->sdate0, temp);
    memcpy(tran.body.DCC_DATE, temp, 8); //��������
    writelog(LOG_ERR, "DCC_DATE[%s]", tran.body.DCC_DATE);
    ret = tcpsocket.ConnectTcp(host, port);
    if (!ret)
    {
        writelog(LOG_ERR, "Connect to bank error,error code is [%d],ip_addr[%s],port[%d] ", ret, host, port);
        return E_TRANS_CONNECT;
    }
    //���ͽṹ����������⣬���в�����������
    memset(sendstr, 0, sizeof(sendstr));
    memset(temp, 0, sizeof(temp));
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_CODE, 6);
    strcat(temp, temp1);
    step = step + 6;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_SCHID, 10);
    strcat(temp, temp1);
    step = step + 10;
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, tran.body.DCC_DATE, 8);
    strcat(temp, temp1);
    step = step + 8;
    strlens = strlen(temp);
    sprintf(len, "%d", strlens);
    leftzstrzero(4, len, packlen);
    memset(temp1, 0, sizeof(temp1));
    memcpy(temp1, packlen, 4);
    rithtzstr(108, temp1, sendstr);
    memcpy(sendstr + 108, temp, strlen(temp));
    writelog(LOG_ERR, "query sendstr[%s]", sendstr);
    ret = tcpsocket.Send(sendstr, strlens + 108);
    if (ret < 0)
    {
        // ����ʱ���˿������⣬�������ر�
        writelog(LOG_ERR, "Send to bank error,error code is [%d] ", ret);
        return E_TRANS_REQUEST;
    }
    else if (0 == ret) {
        // ��Ӧ�ó����������
        writelog(LOG_ERR, "Send to bank��CTcpSocket.Send should not return this error,error code is[%d]!\n", ret);
        return E_TRANS_REQUEST;
    }
    memset(temp, 0, sizeof(temp));
    ret = tcpsocket.Recv(temp, 108, timeout);
    writelog(LOG_ERR, "trans recvhead[%d]", ret);
    writelog(LOG_ERR, " temp[%s]", temp);
    memcpy(ans.head.PACKLEN, temp, 4);
    memcpy(ans.head.RespCode, temp + 4, 4);
    memcpy(ans.head.RespMess, temp + 8, 100);
    memset(temp, 0, sizeof(temp));
    memcpy(temp, ans.head.PACKLEN, 4);
    strlens = atoi(temp);
    if (strlens == 0)
    {
        memcpy(szMsg, ans.head.RespMess, 100);
        writelog(LOG_ERR, "RespMess[%s]", ans.head.RespMess);
        *pRetCode = E_TRANS_BANK_RECVERR;
        goto r_ret;
    }
    writelog(LOG_ERR, "lenbody[%d]", strlens);
    ret = tcpsocket.Recv((char*)&ans.body, strlens, timeout);
    tcpsocket.Close();;
    //writelog(LOG_INFO,"trans recv[%s],recvlen[%d]",ans.body.DCC_CODE,ret);
    if (ret != strlens)
    {
        out_pack->lvol1 = -1;                           //��ʱ �� �������ݴ��� ����̨Ӧ�����з�����
        strcpy(szMsg, "�����������ݴ���");
        goto r_ret;
    }
    if (strncmp(ans.head.RespCode, "0000", 4) != 0)
    {
        memset(temp, 0, sizeof temp);
        memcpy(temp, ans.head.RespMess, 100);
        memcpy(szMsg, temp, 100);
        writelog(LOG_ERR, "RespMess[%s]", temp);
        *pRetCode = E_TRANS_BANK_RECVERR;
        goto r_ret;  // ���ж˴������
    }
    else
    {
        out_pack->lvol1 = 1;
        memcpy(out_pack->semp, ans.body.DCC_CODE, sizeof out_pack->semp);                                  //���ܺ�
        memcpy(out_pack->sdate0, ans.body.DCC_DATE, sizeof out_pack->sdate0);                   // ����
        memcpy(out_pack->sall_name, ans.body.DCC_FILE, sizeof out_pack->sall_name);             //�ļ�·��
        memcpy(out_pack->vsmess, ans.body.DCC_SCHID, sizeof out_pack->vsmess);                              //ѧУ����
        out_pack->lvol0 = atoi(ans.body.DCC_COUNT);                                             //������
        scanf(ans.body.DCC_SUM, "%lf", &out_pack->damt0);                                   //�ܽ��
        PutRow(handle, out_pack, pRetCode, szMsg);
    }
    return 0;
r_ret:
    {
        return E_TRANS_BANK_RECVERR;
    }
}
