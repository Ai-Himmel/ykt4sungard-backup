#include "ks_ct_liaoning.h"
#include <assert.h>
#include "global_func.h"

#define UPDATE_DACK 0

#pragma pack(1)
typedef struct {
    byte ucCardStatus;		//卡状态	CHAR
    byte ucCardVerNo[7];	//黑名单版本号 BCD
    byte ucAppType;			//应用类型
    byte ucAppVer;			//应用版本
    byte ucCardNo[10];		//交易卡号
    byte ucStartDate[4];	    //启用日期
    byte ucExpireDate[4];	//截止日期
    byte ucFeeType;			//收费类别
    byte ucCardType;		//卡类别
    byte ucShowCardNo[10];		//显示卡号
    byte ucSubsidyNo[4];		//补助批次号
    byte ucIssueID[2];		//发卡方ID
    byte ucReserve1[18];   // 保留
} PUBINFO;
typedef struct {
    byte ucCustName[20];  //姓名
    byte ucStuempNo[20];  //学工号
    byte ucSchoolCode;		//校区
    byte ucCustId[4];		// 客户号 int32
    byte ucCustType;		//客户类别
    byte ucSex;		// 性别
    byte ucReserve1[17]; //保留
} PERSONINFO;
typedef struct {
    byte ucCardPwd[6]; //卡密码
    byte ucIDType;	//证件类型
    byte ucIDNo[32]; //证件号码
    byte ucDeptCode[20]; //部门代码
    byte ucReserve1[5]; //保留
} PWDINFO;
typedef struct {
    byte ucMaxPerDay[3]; //日累计消费限额
    byte ucMaxPerOnce[3]; //单次消费限额
    byte ucTotalDaily[3]; //当日累计消费额
    byte ucLastTermNo[6]; //最后消费PSAM卡终端号
    byte ucLastTransDate[4]; // 最后交易日期
    byte ucLastTransTime[3]; // 最后交易时间
    byte ucReserve1[42]; //保留
} CONSUMEPARAINFO;
#pragma pack()
//////////////////////////////////////////////////////////////////////
ks_ctln_cardtype::ks_ctln_cardtype() {
    set_cardtype_name("ks_ct_liaoning.dll");
    m_defaultCardType = KS_SIMCARD;
    // verify definition
    assert(sizeof(PUBINFO) == 64);
    assert(sizeof(PERSONINFO) == 64);
    assert(sizeof(PWDINFO) == 64);
    assert(sizeof(CONSUMEPARAINFO) == 64);

    m_sDefaultPin="1234";
    EF_FIELD EField;
    memset(&EField,0,sizeof(EField));
    //先初始化为0
    if(m_FieldVect.size())
        m_FieldVect.clear();
    if(m_EFMap.size())
        m_EFMap.clear();
    EField.unused=1;
    for(int i=0; i<=CF_END; i++)
        m_FieldVect.push_back(EField);

    PUBINFO thePubInfo;
    PERSONINFO thePerInfo;
    PWDINFO thePwd;
    CONSUMEPARAINFO thePara;

    //卡状态
    m_FieldVect[CF_CARDSTATUS].unused=FIELD_USED;
    m_FieldVect[CF_CARDSTATUS].offset = &thePubInfo.ucCardStatus - (byte*)&thePubInfo;
    m_FieldVect[CF_CARDSTATUS].length = sizeof(thePubInfo.ucCardStatus);
    m_FieldVect[CF_CARDSTATUS].fid=0x15;
    m_FieldVect[CF_CARDSTATUS].type=FT_INT8;
    //卡版本号
    m_FieldVect[CF_CARDVERNO].unused=FIELD_USED;
    m_FieldVect[CF_CARDVERNO].offset = thePubInfo.ucCardVerNo - (byte*)&thePubInfo;
    m_FieldVect[CF_CARDVERNO].length = sizeof(thePubInfo.ucCardVerNo);
    m_FieldVect[CF_CARDVERNO].fid=0x15;
    m_FieldVect[CF_CARDVERNO].type=FT_BCD_LPAD20;
    //应用类型
    m_FieldVect[CF_APPTYPE].unused=FIELD_USED;
    m_FieldVect[CF_APPTYPE].offset = &thePubInfo.ucAppType-(byte*)&thePubInfo;
    m_FieldVect[CF_APPTYPE].length = sizeof(thePubInfo.ucAppType);
    m_FieldVect[CF_APPTYPE].fid=0x15;
    m_FieldVect[CF_APPTYPE].type=FT_INT8;
    //卡号
    m_FieldVect[CF_CARDNO].unused= FIELD_USED;
    m_FieldVect[CF_CARDNO].offset = thePubInfo.ucCardNo-(byte*)&thePubInfo;
    m_FieldVect[CF_CARDNO].length = sizeof(thePubInfo.ucCardNo);
    m_FieldVect[CF_CARDNO].fid=0x15;
    m_FieldVect[CF_CARDNO].type=FT_BCD_LAPDZERO;
    //补助批次号
    m_FieldVect[CF_SUBSIDYNO].unused= FIELD_USED;
    m_FieldVect[CF_SUBSIDYNO].offset = thePubInfo.ucSubsidyNo - (byte*)&thePubInfo;
    m_FieldVect[CF_SUBSIDYNO].length = sizeof(thePubInfo.ucSubsidyNo);
    m_FieldVect[CF_SUBSIDYNO].fid=0x15;
    m_FieldVect[CF_SUBSIDYNO].type=FT_INT32;
    //启用日期
    m_FieldVect[CF_STARTDATE].offset = thePubInfo.ucStartDate-(byte*)&thePubInfo;
    m_FieldVect[CF_STARTDATE].length = sizeof(thePubInfo.ucStartDate);
    m_FieldVect[CF_STARTDATE].fid=0x15;
    m_FieldVect[CF_STARTDATE].type=FT_BCD;
    //有效期
    m_FieldVect[CF_EXPIREDATE].unused= FIELD_USED;
    m_FieldVect[CF_EXPIREDATE].offset = thePubInfo.ucExpireDate-(byte*)&thePubInfo;
    m_FieldVect[CF_EXPIREDATE].length = sizeof(thePubInfo.ucExpireDate);
    m_FieldVect[CF_EXPIREDATE].fid=0x15;
    m_FieldVect[CF_EXPIREDATE].type=FT_BCD;
    //卡结构版本
    m_FieldVect[CF_CARDSTRUCTVER].unused = FIELD_USED;
    m_FieldVect[CF_CARDSTRUCTVER].offset = &thePubInfo.ucAppVer-(byte*)&thePubInfo;
    m_FieldVect[CF_CARDSTRUCTVER].length = sizeof(thePubInfo.ucAppVer);
    m_FieldVect[CF_CARDSTRUCTVER].fid=0x15;
    m_FieldVect[CF_CARDSTRUCTVER].type=FT_INT8;
    //收费类别
    m_FieldVect[CF_FEETYPE].unused = FIELD_USED;
    m_FieldVect[CF_FEETYPE].offset = &thePubInfo.ucFeeType - (byte*)&thePubInfo;
    m_FieldVect[CF_FEETYPE].length = sizeof(thePubInfo.ucFeeType);
    m_FieldVect[CF_FEETYPE].fid=0x15;
    m_FieldVect[CF_FEETYPE].type=FT_INT8;
    //卡类别
    m_FieldVect[CF_CARDTYPE].unused = FIELD_USED;
    m_FieldVect[CF_CARDTYPE].offset = &thePubInfo.ucCardType - (byte*)&thePubInfo;
    m_FieldVect[CF_CARDTYPE].length = sizeof(thePubInfo.ucCardType);
    m_FieldVect[CF_CARDTYPE].fid=0x15;
    m_FieldVect[CF_CARDTYPE].type=FT_INT8;
    //显示卡号
    m_FieldVect[CF_SHOWCARDNO].unused = FIELD_USED;
    m_FieldVect[CF_SHOWCARDNO].offset = thePubInfo.ucShowCardNo - (byte*)&thePubInfo;
    m_FieldVect[CF_SHOWCARDNO].length = sizeof(thePubInfo.ucShowCardNo);
    m_FieldVect[CF_SHOWCARDNO].fid=0x15;
    m_FieldVect[CF_SHOWCARDNO].type=FT_ANSI;
    //发行方标识
    m_FieldVect[CF_PUBLISHID].unused = FIELD_USED;
    m_FieldVect[CF_PUBLISHID].offset = thePubInfo.ucIssueID-(byte*)&thePubInfo;
    m_FieldVect[CF_PUBLISHID].length = sizeof(thePubInfo.ucIssueID);
    m_FieldVect[CF_PUBLISHID].fid=0x15;
    m_FieldVect[CF_PUBLISHID].type=FT_ANSI;
    /////////////////////////////////////////////////////////////////////////////////
    //性别
    m_FieldVect[CF_SEX].unused = FIELD_USED;
    m_FieldVect[CF_SEX].offset = &thePerInfo.ucSex - (byte*)&thePerInfo;
    m_FieldVect[CF_SEX].length = sizeof(thePerInfo.ucSex);
    m_FieldVect[CF_SEX].fid = 0x16;
    m_FieldVect[CF_SEX].type = FT_INT8;
    //姓名
    m_FieldVect[CF_NAME].unused = FIELD_USED;
    m_FieldVect[CF_NAME].offset = thePerInfo.ucCustName - (byte*)&thePerInfo;
    m_FieldVect[CF_NAME].length = sizeof(thePerInfo.ucCustName);
    m_FieldVect[CF_NAME].fid = 0x16;
    m_FieldVect[CF_NAME].type = FT_ANSI;
    //客户类别
    m_FieldVect[CF_CUSTTYPE].unused = FIELD_USED;
    m_FieldVect[CF_CUSTTYPE].offset = &thePerInfo.ucCustType - (byte*)&thePerInfo;
    m_FieldVect[CF_CUSTTYPE].length = sizeof(thePerInfo.ucCustType);
    m_FieldVect[CF_CUSTTYPE].fid=0x16;
    m_FieldVect[CF_CUSTTYPE].type=FT_INT8;
    //客户号
    m_FieldVect[CF_CUSTID].unused = FIELD_USED;
    m_FieldVect[CF_CUSTID].offset = thePerInfo.ucCustId - (byte*)&thePerInfo;
    m_FieldVect[CF_CUSTID].length = sizeof(thePerInfo.ucCustId);
    m_FieldVect[CF_CUSTID].fid=0x16;
    m_FieldVect[CF_CUSTID].type=FT_INT32;
    //学工号
    m_FieldVect[CF_STUEMPNO].unused = FIELD_USED;
    m_FieldVect[CF_STUEMPNO].offset = thePerInfo.ucStuempNo - (byte*)&thePerInfo;
    m_FieldVect[CF_STUEMPNO].length = sizeof(thePerInfo.ucStuempNo);
    m_FieldVect[CF_STUEMPNO].fid=0x16;
    m_FieldVect[CF_STUEMPNO].type=FT_ANSI;
    //校区
    m_FieldVect[CF_SCHOOLCODE].unused = FIELD_USED;
    m_FieldVect[CF_SCHOOLCODE].offset = &thePerInfo.ucSchoolCode - (byte*)&thePerInfo;
    m_FieldVect[CF_SCHOOLCODE].length = sizeof(thePerInfo.ucSchoolCode);
    m_FieldVect[CF_SCHOOLCODE].fid=0x16;
    m_FieldVect[CF_SCHOOLCODE].type=FT_INT8;
    ////////////////////////////////////////////////////////////////////////////////////////////
    //卡密码
    m_FieldVect[CF_CARDPWD].unused = FIELD_USED;
    m_FieldVect[CF_CARDPWD].offset = thePwd.ucCardPwd - (byte*)&thePwd;
    m_FieldVect[CF_CARDPWD].length = sizeof(thePwd.ucCardPwd);
    m_FieldVect[CF_CARDPWD].fid=0x19;
    m_FieldVect[CF_CARDPWD].type=FT_ANSI;
    //身份证号
    m_FieldVect[CF_IDNO].unused = FIELD_USED;
    m_FieldVect[CF_IDNO].offset = thePwd.ucIDNo - (byte*)&thePwd;
    m_FieldVect[CF_IDNO].length = sizeof(thePwd.ucIDNo);
    m_FieldVect[CF_IDNO].fid=0x19;
    m_FieldVect[CF_IDNO].type=FT_ANSI;
    //证件类型
    m_FieldVect[CF_IDTYPE].unused = FIELD_USED;
    m_FieldVect[CF_IDTYPE].offset = &thePwd.ucIDType - (byte*)&thePwd;
    m_FieldVect[CF_IDTYPE].length = sizeof(thePwd.ucIDType);
    m_FieldVect[CF_IDTYPE].fid = 0x19;
    m_FieldVect[CF_IDTYPE].type=FT_INT8;
    //部门代码
    m_FieldVect[CF_DEPTCODE].unused = FIELD_USED;
    m_FieldVect[CF_DEPTCODE].offset = thePwd.ucDeptCode - (byte*)&thePwd;
    m_FieldVect[CF_DEPTCODE].length = sizeof(thePwd.ucDeptCode);
    m_FieldVect[CF_DEPTCODE].fid=0x19;
    m_FieldVect[CF_DEPTCODE].type=FT_ANSI;
    ////////////////////////////////////////////////////////////////////////////////////
    //日累计最大限额
    m_FieldVect[CF_DAYMAXAMT].unused = FIELD_USED;
    m_FieldVect[CF_DAYMAXAMT].offset = thePara.ucMaxPerDay - (byte*)&thePara;
    m_FieldVect[CF_DAYMAXAMT].length = sizeof(thePara.ucMaxPerDay);
    m_FieldVect[CF_DAYMAXAMT].fid = 0x1A;
    m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;
    //单次累计限额(同日累计最大限额)
    m_FieldVect[CF_SINGLEMAXAMT].unused = FIELD_USED;
    m_FieldVect[CF_SINGLEMAXAMT].offset = thePara.ucMaxPerOnce - (byte*)&thePara;
    m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(thePara.ucMaxPerOnce);
    m_FieldVect[CF_SINGLEMAXAMT].fid = 0x1A;
    m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT24;
    //当日累计消费额
    m_FieldVect[CF_DAYSUMAMT].unused = FIELD_USED;
    m_FieldVect[CF_DAYSUMAMT].offset = thePara.ucTotalDaily - (byte*)&thePara;
    m_FieldVect[CF_DAYSUMAMT].length = sizeof(thePara.ucTotalDaily);
    m_FieldVect[CF_DAYSUMAMT].fid = 0x1A;
    m_FieldVect[CF_DAYSUMAMT].type=FT_INT24;
    //交易终端号
    m_FieldVect[CF_TERMID].unused = FIELD_USED;
    m_FieldVect[CF_TERMID].offset = thePara.ucLastTermNo - (byte*)&thePara;
    m_FieldVect[CF_TERMID].length = sizeof(thePara.ucLastTermNo);
    m_FieldVect[CF_TERMID].fid = 0x1A;
    m_FieldVect[CF_TERMID].type=FT_BCD;
    //最后交易日期
    m_FieldVect[CF_TRANSDATE].unused = FIELD_USED;
    m_FieldVect[CF_TRANSDATE].offset = thePara.ucLastTransDate - (byte*)&thePara;
    m_FieldVect[CF_TRANSDATE].length = sizeof(thePara.ucLastTransDate);
    m_FieldVect[CF_TRANSDATE].fid=0x1A;
    m_FieldVect[CF_TRANSDATE].type=FT_BCD;
    //最后交易时间
    m_FieldVect[CF_TRANSTIME].unused = FIELD_USED;
    m_FieldVect[CF_TRANSTIME].offset = thePara.ucLastTransTime - (byte*)&thePara;
    m_FieldVect[CF_TRANSTIME].length = sizeof(thePara.ucLastTransTime);
    m_FieldVect[CF_TRANSTIME].fid=0x1A;
    m_FieldVect[CF_TRANSTIME].type=FT_BCD;
    ////////////////////////////////////////////////////////////////////////////////
    //钱包文件
    //卡余额
    m_FieldVect[CF_CARDBAL].unused=0;
    m_FieldVect[CF_CARDBAL].offset =0;
    m_FieldVect[CF_CARDBAL].length =0;
    m_FieldVect[CF_CARDBAL].fid=MONEY_SFID;
    m_FieldVect[CF_CARDBAL].type=FT_INT32;
    m_FieldVect[CF_CARDBAL].rw=RW_R;
    //消费次数
    m_FieldVect[CF_PAYCNT].unused=0;
    m_FieldVect[CF_PAYCNT].offset =0;
    m_FieldVect[CF_PAYCNT].length =0;
    m_FieldVect[CF_PAYCNT].fid=MONEY_SFID;
    m_FieldVect[CF_PAYCNT].type=FT_INT32;
    m_FieldVect[CF_PAYCNT].rw=RW_R;
    //充值次数
    m_FieldVect[CF_DPSCNT].unused=0;
    m_FieldVect[CF_DPSCNT].offset =0;
    m_FieldVect[CF_DPSCNT].length =0;
    m_FieldVect[CF_DPSCNT].fid=MONEY_SFID;
    m_FieldVect[CF_DPSCNT].type=FT_INT32;
    m_FieldVect[CF_DPSCNT].rw=RW_R;

    // 银行卡号
    m_FieldVect[CF_BANKCARDNO].unused=1;

    EFBUF efbuf;

    memset(efbuf.ReadBuf,0,sizeof(efbuf.ReadBuf));
    memset(efbuf.WriteBuf,0,sizeof(efbuf.WriteBuf));

    // 0x15 公共应用基本文件
    efbuf.FileSize=64;
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[0x15]=efbuf;

    // 0x16 持卡人基本文件
    efbuf.FileSize=64;
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[0x16]=efbuf;

    // 0x19 交易密码文件
    efbuf.FileSize=64;
    efbuf.ReadRight=FRR_MAC;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[0x19]=efbuf;

    // 0x1A 交易参数文件
    efbuf.FileSize=64;
    efbuf.ReadRight=FRR_MAC;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[0x1A]=efbuf;

    //钱包
    efbuf.FileSize=0;
    efbuf.ReadRight=FRR_NULL;
    efbuf.WriteRight=FRW_NULL;
    m_EFMap[MONEY_SFID]=efbuf;


}

ks_ctln_cardtype::~ks_ctln_cardtype() {
}

void ks_ctln_cardtype::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
    int i = 0;
    cardTypes[i++] = 0x0502;
    cardTypes[i++] = 0x0300;
    cardTypes[i++] = 0x0400;
    cnt = i;
}

int ks_ctln_cardtype::SelectADF() {
    int nRet;
    return selectADFBySFI("DF03",1);
}

int ks_ctln_cardtype::UpdateKey(const byte ucMainKey[16],byte ucKeyIndex,byte ucKeyType,byte ucKey[16]) {
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

#if 0
    memcpy(ucCmd,"\x84\xD4\x02\x00\x15",5);
    ucCmd[3] = ucKeyIndex;
    memset(ucPlainKey,0,sizeof ucPlainKey);
    keylen = 1;
    ucPlainKey[keylen++]=ucKeyType;
    ucPlainKey[keylen++]=0xF0;
    ucPlainKey[keylen++]=0xF0;
    ucPlainKey[keylen++]=0x33;
    ucPlainKey[keylen++]=0xAA;
    memcpy(ucPlainKey+keylen,ucKey,16);
    keylen += 16;

    ucPlainKey[0] = keylen-1;
    if(keylen % 8 != 0) {
        ucPlainKey[keylen] = 0x80;
        keylen = (keylen / 8 + 1) * 8;
    }
    ucCmd[4] = keylen+4;

#else
    // 更新密钥 方法 1
    // 2010-7-5 tc 目前只能用方法1更新密钥
    memcpy(ucCmd,"\x84\xD4\x00\x00\x1C",5);
    ucCmd[2] = ucKeyType;
    ucCmd[3] = ucKeyIndex;

    keylen = 0;
    ucPlainKey[keylen++] = 16;
    memcpy(ucPlainKey+keylen,ucKey,16);
    keylen += 16;
    memcpy(ucPlainKey+keylen,"\x80\x00\x00\x00\x00\x00\x00",7);
    keylen += 7;
#endif

    nRet=GetRandomNum(ucRandom);
    if(nRet) {
        return nRet;
    }

    //用主控会话密钥加密待加密数据
    EncryptKey(ucMainKey,2,ucPlainKey,keylen,ucOutBuf,iOutLen);

    memcpy(ucCmd+5,ucOutBuf,iOutLen);
    ucCmdLen=iOutLen+5;

    CalcMac(ucRandom,(byte*)ucMainKey,2,ucCmd,ucCmdLen,ucMac);

    memcpy(ucCmd+ucCmdLen,ucMac,4);
    ucCmdLen+=4;

    byte ucRes[256]= {0};
    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    cmd.send_buf=ucCmd;
    cmd.recv_buf=ucRes;
    cmd.send_len=ucCmdLen;
    cmd.cmd_type=0;//16进制

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
int ks_ctln_cardtype::InitUserCard(const char *sShowCardNo) {
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

    byte ucMainKey[16]= {0};
    byte ucDiverKey[16]= {0};
    byte ucData[256] = {0};

    // 判断卡是否已经初始化
    memset(ucData,0,sizeof ucData);
    nRet=ReadBinaryFile(0x15,0x00,30,ucData);
    if(nRet) {
        return nRet;
    }
    if(0x02==ucData[9]) {
        SET_ERR("该卡已经初始化");
        return -1;
    }

    memset(ucMainKey,0x00,16);	//出厂密钥
    //PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucMainKey);
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
    nRet=UpdateKey(ucMainKey,0x01,0x27,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改消费密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DPK2,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x02,0x27,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改充值密钥1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x01,0x26,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改充值密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DLK2,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x02,0x26,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改TAC密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x25,ucDiverKey);
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
    memset(ucData,0,sizeof(ucData));
    //初始化0x15
    ucData[8]=0x01;//应用类型标识
    ucData[9]=0x02;//应用版本号
    ucData[44]=0x06;//发行方标识
    nRet=UpdateBinaryFile(0x15,0,64,ucData);
    if(nRet) {
        return nRet;
    }
    //初始化0x16
    memset(ucData,0,sizeof(ucData));
    nRet=UpdateBinaryFile(0x16,0,64,ucData);
    if(nRet) {
        return nRet;
    }

#if UPDATE_DACK==1
    //修改主控密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }
#endif
    //////////////////////////////////////////////////////////
    nRet = this->selectADFBySFI("DF02");
    if(nRet) {
        return nRet;
    }
    //修改维护密钥1
    memset(ucMainKey,0x00,sizeof ucMainKey);
    PbocDiverKey(ucCardPhyID,m_CardKeys.LDAMK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x36,ucDiverKey);
    if(nRet) {
        return nRet;
    }
    //修改维护密钥2
    PbocDiverKey(ucCardPhyID,m_CardKeys.LDAMK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x01,0x36,ucDiverKey);
    if(nRet) {
        return nRet;
    }
#if UPDATE_DACK==1
    //修改主控密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.LDACK,ucDiverKey);
    nRet=UpdateKey(ucMainKey,0x00,0x39,ucDiverKey);
    if(nRet) {
        return nRet;
    }
#endif
    // 选择主目录
    return this->selectADFBySFI("3F00",1);
}
int ks_ctln_cardtype::RestoreRecord() {
    int nRet;
    char szCmd[128];
    char sMac[9] = {0};
    unsigned char ucResp[256],ucRespLen;
    std::string sCmd;
    sprintf(szCmd,"04DC00%02X1BFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",(0x18<<3)+4);
    nRet = this->CalcSafeMac4Sam(szCmd,sMac);
    if(nRet) {
        SET_ERR("RestoreRecord = CalcSafeMac 失败,ret["<<nRet<<"]");
        return nRet;
    }
    sCmd = szCmd;
    sCmd += sMac;

    memset(ucResp,0,sizeof ucResp);
    nRet = this->Adpu4Hex(sCmd.c_str(),sCmd.length(),ucResp,ucRespLen);
    if(nRet) {
        SET_ERR("RestoreRecord 失败,ret["<<nRet<<"]");
        return nRet;
    }
    return 0;
}
int ks_ctln_cardtype::RestoreFactorySettings() {
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
    /*
    nRet = RestoreRecord();
    if(nRet)
    {
    	SET_ERR("回收记录文件失败,ret["<<hex<<nRet<<"]");
    	return nRet;
    }
    */

    byte ucMainKey[16]= {0};
    byte ucInitKey[16]= {0};
    byte ucData[256] = {0};
    memset(ucData,0,sizeof ucData);
    nRet=ReadBinaryFile(0x15,0x00,30,ucData);
    if(nRet) {
        return nRet;
    }
    if(0x02!=ucData[9]) {
        SET_ERR("该卡已经回收");
        return -1;
    }

#if UPDATE_DACK == 1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,ucMainKey);
#else
    memset(ucMainKey,0x00,16);
#endif


    memset(ucData,0,sizeof(ucData));
    //初始化0x15
    nRet=UpdateBinaryFile(0x15,0,64,ucData);
    if(nRet) {
        return nRet;
    }

    //初始化0x16
    nRet=UpdateBinaryFile(0x16,0,64,ucData);
    if(nRet) {
        return nRet;
    }
    nRet=UpdateBinaryFile(0x19,0,64,ucData);
    if(nRet) {
        return nRet;
    }
    nRet=UpdateBinaryFile(0x1A,0,64,ucData);
    if(nRet) {
        return nRet;
    }
    //应用维护密钥1
    nRet=UpdateKey(ucMainKey,0x00,0x36,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //应用维护密钥2
    nRet=UpdateKey(ucMainKey,0x01,0x36,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //pin 解锁
    nRet=UpdateKey(ucMainKey,0x00,0x37,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //pin 重装
    nRet=UpdateKey(ucMainKey,0x00,0x38,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //消费密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x27,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //消费密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x27,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //圈存密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x26,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //圈存密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x26,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //TAC密钥
    nRet=UpdateKey(ucMainKey,0x00,0x25,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //圈提密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x28,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //圈提密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x28,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //修改透支限额密钥1
    nRet=UpdateKey(ucMainKey,0x01,0x29,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //修改透支限额密钥2
    nRet=UpdateKey(ucMainKey,0x02,0x29,ucInitKey);
    if(nRet) {
        return nRet;
    }
#if UPDATE_DACK == 1
    //主控密钥
    nRet=UpdateKey(ucMainKey,0x00,0x39,ucInitKey);
    if(nRet) {
        return nRet;
    }
#endif
    ////////////////////////////////////////////////////////////////
#if UPDATE_DACK == 1
    PbocDiverKey(ucCardPhyID,m_CardKeys.LDACK,ucMainKey);
#else
    memset(ucMainKey,0x00,16);
#endif
    nRet = this->selectADFBySFI("DF02");
    if(nRet) {
        return nRet;
    }
    //修改维护密钥1
    nRet=UpdateKey(ucMainKey,0x00,0x36,ucInitKey);
    if(nRet) {
        return nRet;
    }
    //修改维护密钥2
    nRet=UpdateKey(ucMainKey,0x01,0x36,ucInitKey);
    if(nRet) {
        return nRet;
    }
#if UPDATE_DACK==1
    //修改主控密钥
    nRet=UpdateKey(ucMainKey,0x00,0x39,ucInitKey);
    if(nRet) {
        return nRet;
    }
#endif
    return 0;
}

int ks_ctln_cardtype::checkCardType(int ct) {
    switch(ct) {
    case KS_MFCARD:
        m_CardTypeCode = 0x0200;
        return 0;
    case KS_SIMCARD:
        m_CardTypeCode = 0x0502;
        return 0;
    default:
        return -1;
    }
}

int  ks_ctln_cardtype::OpenPort() {
    int nRet;
    ks_cpu_cmd_t cmd;
    byte uResp[256] = {0};
    char szCmd[256] = {0};
    nRet = CCardType::OpenPort();
    if(nRet) {
        return nRet;
    }
    // 修改RF 参数
    sprintf(szCmd,"90B0010018000000000000000000000000080000030000010000000000");
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char *)szCmd;
    cmd.recv_buf = uResp;
    cmd.send_len = strlen(szCmd);
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("设置RF参数失败");
        return nRet;
    }
    return 0;
}
/////////////////////////////////////////////////////////////////////////////////
//static ks_ctln_cardtype CardTypeMb;

int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_ctln_cardtype();
    return 0;
}
