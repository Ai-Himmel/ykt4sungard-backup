#include "ks_zjvcc_cardtype.h"
#include <assert.h>
#include "global_func.h"
#include "mystring.h"
#include "des.h"

#define UPDATE_DACK 1

//握奇出厂密钥, DF03 应用主控密钥
static unsigned char INIT_CCK[] = "\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22\x22";

ks_zjvcc_cardtype::ks_zjvcc_cardtype() {
    set_cardtype_name("ks_zjvcc_cardtype.dll");
    m_defaultCardType = KS_SIMCARD;

    m_EFMap[0x19].ReadRight=FRR_EXTAUTH; // 握奇只支持 外部认证+明文 读取
}

//用PSAM卡计算DF03下的修改文件的MAC
int ks_zjvcc_cardtype::CalcSafeMac4Sam(const char *szCmdbuf,char *szMac) {
    int ret;
    unsigned char uRandom[8]= {0};
    char szRandom[17] = {0};
    ret = this->GetRandomNum8(uRandom);
    if(ret)
        return ret;
    dec2hex(uRandom,8,szRandom);
    strcpy(this->m_szRandomNum,szRandom);
    return m_PSAMCardType->CalcSafeMac4Sam(this,szCmdbuf,szMac);
}

// 握奇外部认证使用8字节随机数
int ks_zjvcc_cardtype::GetRandomNum8(byte *uRandomNum) {
    byte ucResp[256]= {0};
    byte ucRespLen = 0;

    int nRet = Adpu((BYTE*)"\x00\x84\x00\x00\x08",5, ucResp, ucRespLen);
    if(nRet)
        return nRet;

    memcpy(uRandomNum,ucResp,8);
    memset(m_szRandomNum,0,sizeof m_szRandomNum);
    dec2hex(uRandomNum,8,this->m_szRandomNum);
    return 0;
}

// 握奇外部认证使用8字节随机数
int ks_zjvcc_cardtype::ExecExtAuthCmd8(byte ucExtAuthKey[16],int nKeyIndex) {
    byte ucRandom[9]= {0};

    int nRet=GetRandomNum8(ucRandom);
    if(nRet)
        return nRet;

    des3_context ctx3;
    des3_set_2keys( &ctx3, ucExtAuthKey,ucExtAuthKey+8);
    byte ucBuff[64]= {0};
    des3_encrypt(&ctx3,ucRandom,ucBuff);

    byte ucSendData[256]= {0};
    memcpy(ucSendData,"\x00\x82\x00\x00\x08",5);
    ucSendData[3]=nKeyIndex;
    memcpy(ucSendData+5,ucBuff,8);

    byte ucRespData[256]= {0};
    byte ucRespLen = 0;

    return Adpu(ucSendData,0x0D, ucRespData, ucRespLen);
}

int ks_zjvcc_cardtype::ExtAuth(const char *cardphyid,int keyidx) {
    string sCmd;
    unsigned char ucRespData[512]= {0};
    unsigned char ucRandom[9]= {0};
    char sRandomHex[17]= {0};
    char encrypt_random[24] = {0};
    int nRet;

    nRet=SelectADF();
    if(nRet)
        return nRet;
    nRet=GetRandomNum8(ucRandom); // 握奇外部认证使用8字节随机数
    if(nRet)
        return nRet;

    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    cmd.recv_buf=ucRespData;

    dec2hex(ucRandom,8,sRandomHex);
    nRet = CalcExtAuthEncrypt4Sam(cardphyid,keyidx,sRandomHex,encrypt_random);
    if(nRet) {
        return nRet;
    }
    sCmd = "008200"+ltohex(keyidx)+"08";
    sCmd += encrypt_random;

    cmd.cmd_type=1;
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,m_defaultCardType);
    if(nRet) {
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    return 0;
}

// 更新出厂KEY
int ks_zjvcc_cardtype::UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKeyType,byte ucKey[16]) {
    int nRet=0;
    byte ucCmd[256]= {0};
    byte ucCmdLen=0;
    byte ucOutBuf[128]= {0};
    int  iOutLen=0;
    int  keylen = 0;
    byte ucMac[4]= {0};
    byte ucSessionKey[17]= {0};
    byte ucRandom[9]= {0};
    byte ucPlainKey[40]= {0};


    // 更新握奇出厂卡的密钥
    memcpy(ucCmd,"\x84\xD4\x00\x00\x1C",5);
    ucCmd[2] = ucKeyType;
    ucCmd[3] = ucKeyIndex;

    keylen = 0;
    ucPlainKey[keylen++] = 16;
    memcpy(ucPlainKey+keylen,ucKey,16);
    keylen += 16;
    memcpy(ucPlainKey+keylen,"\x80\x00\x00\x00\x00\x00\x00",7);
    keylen += 7;

    nRet=GetRandomNum8(ucRandom);
    if(nRet) {
        return nRet;
    }

    //用主控会话密钥加密待加密数据
    EncryptKey(ucMainKey,2,ucPlainKey,keylen,ucOutBuf,iOutLen);

    memcpy(ucCmd+5,ucOutBuf,iOutLen);
    ucCmdLen=iOutLen+5;

    // 计算MAC
    CalcMac(ucRandom,(byte*)ucMainKey,2,ucCmd,ucCmdLen,ucMac);

    memcpy(ucCmd+ucCmdLen,ucMac,4);
    ucCmdLen+=4;

    byte ucRespData[256]= {0};
    byte ucRespLen = 0;

    return Adpu(ucCmd,ucCmdLen, ucRespData, ucRespLen);
}

// 用AID选目录，DF03 已经被电信应用使用
int ks_zjvcc_cardtype::SelectADF() {
    return selectADFByName("D156000001BDF0CACBB4EFD6A7B8B6",1);
}

int ks_zjvcc_cardtype::InitUserCard(const char *sShowCardNo) {
    int nRet=0;
    int iLen=0;
    char sCardPhyID[17]= {0};
    byte ucCardPhyID[9]= {0};
    if(!m_CardKeys.bLoad) {
        SetLastErrMsg("密钥未装载");
        return -1;
    }
    //寻卡
    nRet=RequestCard();
    if(nRet) {
        return nRet;
    }
    if(strlen(m_szCardUID)==8)
        strcat(m_szCardUID,"80000000");
    if(strlen(m_szCardUID)!=16) {
        SET_ERR("卡物理ID["<<m_szCardUID<<"]长度错误");
        return -1;
    }
    hex2dec(m_szCardUID,16,ucCardPhyID,iLen);

    nRet=SelectADF();
    if(nRet) {
        return nRet;
    }

    byte ucData[256] = {0};
    /*
    // 判断卡是否已经初始化
    memset(ucData,0,sizeof ucData);
    nRet=ReadBinaryFile(0x15,0x00,30,ucData);
    if(nRet)
    {
    return nRet;
    }
    if(0x02==ucData[9])
    {
    SET_ERR("该卡已经初始化");
    return -1;
    }
    */
    // 应用外部认证
    nRet = ExecExtAuthCmd8(INIT_CCK);
    if(nRet) {
        return nRet;
    }

    byte ucRes[256]= {0};
    byte ucRespLen = 0;

    byte ucMainKey[16]= {0};
    byte ucDiverKey[16]= {0};

    memcpy(ucMainKey,INIT_CCK,16);	//出厂密钥
    //修改维护密钥1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x36,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改维护密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x01,0x36,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改消费密钥1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x01,0x3E,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改消费密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DPK2,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x02,0x3E,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改充值密钥1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x01,0x3F,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改充值密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DLK2,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x02,0x3F,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改TAC密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x34,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改PIN解锁密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DUK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x37,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改PIN重装密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DRPK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x38,ucDiverKey);
    if(nRet) {
        return nRet;
    }

    //修改外部认证密钥1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x01,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }

    //修改外部认证密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK2,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x02,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }

    memset(ucData,0,sizeof(ucData));
    //初始化0x15
    // 显示卡号
    strncpy((char*)&ucData[10], sShowCardNo, 10);

    //初始化0x15
    nRet=UpdateBinaryFile(0x15,0,56,ucData);
    if(nRet) {
        return nRet;
    }

    memset(ucData,0,sizeof(ucData));

    //初始化0x16
    nRet=UpdateBinaryFile(0x16,0,112,ucData);
    if(nRet) {
        return nRet;
    }

    //初始化0x12
    nRet=UpdateBinaryFile(0x12,0,16,ucData);
    if(nRet) {
        return nRet;
    }

    //初始化0x19
    nRet=UpdateBinaryFile(0x19,0,16,ucData);
    if(nRet) {
        return nRet;
    }

#if UPDATE_DACK==1
    //修改主控密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }
#endif

    return SelectADF();
}

int ks_zjvcc_cardtype::RestoreFactorySettings() {
    char sCardPhyID[17]= {0};
    byte ucCardPhyID[9]= {0};

    byte ucMainKey[17]= {0};
    byte ucDiverKey[17]= {0};

    string sCmd;
    int nRet=0;
    if(!m_CardKeys.bLoad) {
        SetLastErrMsg("密钥未装载");
        return -1;
    }
    nRet=RequestCard();
    if(nRet) {
        return nRet;
    }

    nRet=SelectADF(); // 选择 DF03
    if(nRet) {
        return nRet;
    }

    if(strlen(m_szCardUID)==8)
        strcat(m_szCardUID,"80000000");

    if(strlen(m_szCardUID)!=16) {
        SET_ERR("卡物理ID["<<m_szCardUID<<"]长度错误");
        return -1;
    }

    int i=0;
    int iLen=0;
    unsigned char ucCCK[17]= {0};

    hex2dec(m_szCardUID,16,ucCardPhyID,iLen);

#if UPDATE_DACK==1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK,ucMainKey);//应用主控密钥
#else
    memcpy(ucMainKey,INIT_CCK,16);	//出厂密钥
#endif

    nRet=ExecExtAuthCmd8(ucMainKey);

    if(nRet) {
        return nRet;
    }

    byte ucData[256] = {0};

    //初始化0x15
    nRet=UpdateBinaryFile(0x15,0,56,ucData);
    if(nRet) {
        return nRet;
    }
    //初始化0x16
    nRet=UpdateBinaryFile(0x16,0,112,ucData);
    if(nRet) {
        return nRet;
    }

    //初始化0x12
    nRet=UpdateBinaryFile(0x12,0,16,ucData);
    if(nRet) {
        return nRet;
    }

    //初始化0x19
    nRet=UpdateBinaryFile(0x19,0,16,ucData);
    if(nRet) {
        return nRet;
    }


    memcpy(ucDiverKey,INIT_CCK,16);	//出厂密钥

    //修改维护密钥1
    nRet=UpdateKey(ucMainKey,0x00,0x36,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改维护密钥2
    nRet=UpdateKey(ucMainKey,0x01,0x36,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改消费密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x3E,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改消费密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x3E,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改充值密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x3F,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改充值密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x3F,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改TAC密钥
    nRet=UpdateKey(ucMainKey,0x00,0x34,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改PIN解锁密钥
    nRet=UpdateKey(ucMainKey,0x00,0x37,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改PIN重装密钥
    nRet=UpdateKey(ucMainKey,0x00,0x38,ucDiverKey);
    if(nRet) {
        return nRet;
    }

    //修改外部认证密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }

    //修改外部认证密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }

#if UPDATE_DACK==1
    //修改主控密钥
    nRet=UpdateKey(ucMainKey,0x00,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }
#endif

    return SelectADF();
}

int ks_zjvcc_cardtype::checkCardType(int ct) {
    switch(ct) {
    case KS_FIXCARD:
        m_CardTypeCode = 0x0104;
    case KS_CPUCARD:
    case KS_SIMCARD:
        m_CardTypeCode = 0x0502;
        return 0;
    default:
        return -1;
    }
}

void ks_zjvcc_cardtype::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
    int i = 0;
    cardTypes[i++] = 0x0502;
    cardTypes[i++] = 0x0300;
    cardTypes[i++] = 0x0400;
    cardTypes[i++] = 0x104;
    cnt = i;
}

int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_zjvcc_cardtype();
    return 0;
}
