#include "ks_dongguan_psam.h"
#include <vector>
#include <string>
#include "mystring.h"
#include "global_func.h"
#include "des.h"
#include "kscardtype.h"
using namespace std;


DGPSAM::DGPSAM():ks_psamcard_base() {
}
DGPSAM::~DGPSAM() {
}


int DGPSAM::PublishPSAMCard(ST_PSAMCARD* PSAMCard) {
    return KS_NOTSUPPORT;
}
int DGPSAM::CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac) {
    int i=0;
    des_context ctx;
    BYTE uTemp[16];
    // 初始化MAC计算初值 ==> temp
    memset(uTemp, 0, sizeof(uTemp));
    memcpy(uTemp, uRandom, 8 * sizeof(BYTE));
    // 格式化输入值: 填 "80 00 00 ...", 凑8字节长度 ==> buf
    int nBlock=0;
    if(iMacDataLen%8)
        nBlock = iMacDataLen/8 + 1; // 总块数
    else
        nBlock = iMacDataLen/8;
    byte* buf = new byte[nBlock*8+1];
    memset(buf, 0, nBlock*8*sizeof(byte));
    memcpy(buf, uMacData, iMacDataLen*sizeof(byte));
    buf[iMacDataLen] = 0x80;
    des_set_key(&ctx,uKey);
    for (i=0; i<nBlock; i++) {
        // temp .EOR. block[i] ==> temp
        for(int j=0; j<8; j++) {
            uTemp[j] ^= buf[i*8+j];
        }
        // temp ==> DES ==> temp
        des_encrypt(&ctx,uTemp,uTemp);
        if (nKeyLen==3) {
            des_set_key(&ctx,uKey+8);
            des_decrypt(&ctx,uTemp,uTemp);
            des_set_key(&ctx,uKey);
            des_encrypt(&ctx,uTemp,uTemp);
        }
    }
    delete []buf;

    if (nKeyLen == 2) {
        des_set_key(&ctx,uKey+8);
        des_decrypt(&ctx, uTemp,uTemp);
        des_set_key(&ctx,uKey);
        des_encrypt(&ctx,uTemp,uTemp);
    }
    // temp 左四位 ==> MAC
    memcpy(uMac, uTemp, 4 * sizeof(byte));
    return 0;
}

int DGPSAM::RecyclePSAMCard() {
    return KS_NOTSUPPORT;
}
int DGPSAM::ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) {
    int nRet=0;
    char	szCmd[256];
    byte respLen;
    sprintf(szCmd,"00B0%02X%02X%02X",0x80+ucSFI,ucOffset,ucLength);
    nRet = this->Adpu4HexSAM(szCmd,strlen(szCmd),ucData,respLen);
    if(nRet) {
        SET_ERR(GetErrMsgByErrCode(nRet,NULL));
        return nRet;
    }
    return 0;
}
int DGPSAM::ReadPSAMCard(ST_PSAMCARD* PSAMCard) {
    char szBuf[256];
    string sCmd,sMsg;
    int i;
    int ret;
    byte ucRespData[256],ucRespLen;

    memset(ucRespData,0,sizeof(ucRespData));
    ret=this->selectADFBySFI(MF_SFI);
    if(ret) {
        SET_ERR("选择目录3F00失败");
        return ret;
    }

    memset(ucRespData,0,sizeof(ucRespData));
    ret=ReadBinaryFile4Sam(0x15,0x00,14,ucRespData);
    if(ret) {
        SET_ERR("读PSAM卡0x15文件失败");
        return ret;
    }
    ST_PSAMCARD15 Psam15;
    memcpy(&Psam15,ucRespData,sizeof(Psam15));

    memset(szBuf,0,sizeof(szBuf));
    if(Psam15.ucCardNo[0]!=0xFF) {
        bcd2asc(Psam15.ucCardNo,sizeof(Psam15.ucCardNo),szBuf);
        for(i=0; i<19; i++) {
            if(szBuf[i]!='0')
                break;
        }
        strcpy(PSAMCard->sCardNo,szBuf+i);
        PSAMCard->nCardVer=(int)Psam15.ucCardVerNo;
        PSAMCard->nCardType=(int)Psam15.ucCardType;
    }
    //读取终端编号
    memset(ucRespData,0,sizeof(ucRespData));
    ret=ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
    if(ret) {
        SET_ERR("读PSAM卡0x16文件失败");
        return ret;
    }
    memset(szBuf,0,sizeof(szBuf));
    bcd2asc(ucRespData,6,szBuf);

    strcpy(PSAMCard->sTermID,szBuf);

    ret=ReadBinaryFile4Sam(0x17,0x00,25,ucRespData);
    if(ret) {
        SET_ERR("读PSAM卡0x17文件失败");
        return ret;
    }
    ST_PSAMCARD17 Psam17;
    memcpy(&Psam17,ucRespData,sizeof(Psam17));
    PSAMCard->nKeyIndex=(int)Psam17.ucKeyIndex;

    bcd2asc(Psam17.ucPublishID,sizeof(Psam17.ucPublishID),szBuf);
    for(i=0; i<15; i++) {
        if(szBuf[i]!='0')
            break;
    }
    strcpy(PSAMCard->sPublishID,szBuf+i);

    memset(szBuf,0,sizeof(szBuf));
    bcd2asc(Psam17.ucUserID,sizeof(Psam17.ucUserID),szBuf);

    for(i=0; i<15; i++) {
        if(szBuf[i]!='0')
            break;
    }
    strcpy(PSAMCard->sUserID,szBuf+i);
    bcd2asc(Psam17.ucStartDate,sizeof(Psam17.ucStartDate),PSAMCard->sStartDate);
    bcd2asc(Psam17.ucExpireDate,sizeof(Psam17.ucExpireDate),PSAMCard->sExpireDate);
    //	PSAMCard->nCardNo= Psam17.
    ret=this->selectADFBySFI("3F01");
    if(ret) {
        SET_ERR("选择目录3F01失败");
        return ret;
    }
    memset(ucRespData,0,sizeof(ucRespData));
    ret=ReadBinaryFile4Sam(0x19,0x00,4,ucRespData);
    if(ret) {
        SET_ERR("读PSAM卡0x18文件失败");
        return ret;
    }
    for(i=0; i<4; i++)
        if(ucRespData[i]==0xFF)
            ucRespData[i]=0;
    PSAMCard->nTermSeqno=get_4byte_int(ucRespData);
    return 0;
}
int DGPSAM::ResetPSAM() {
    int ret=0;
    unsigned char rlen[24];
    unsigned char rbuff[256];
    if(m_PSAMSlot == m_ReaderPara->cpuport
            && m_PowerOn == 1)
        return 0;
    if(m_ReaderPara->cpuport < 1 || m_ReaderPara->cpuport > 4) {
        SET_ERR("SAM卡座参数错误port["<<m_ReaderPara->cpuport<<"]");
        return -1;
    }
    ret=m_Reader->cpucard_poweron(m_ReaderPara,KS_PSAM,rlen,rbuff);
    if(ret) {
        SET_ERR("SAM卡座上电复位错误SAMNO["<<m_ReaderPara->cpuport<<"]ret["<<ret<<"]");
        return ret;
    }
    m_PSAMSlot = m_ReaderPara->cpuport;
    m_PowerOn = 1;
    return 0;
}

int DGPSAM::ReadPSAMTermno(char *sTermno) {
    int nRet=0;
    string sCmd,sMsg;
    char szTermno[13]= {0};
    byte rbuff[256]= {0};
    byte ucRespData[256]= {0};

    //上电复位
    nRet=this->ResetPSAM();
    if(nRet) {
        SET_ERR("SAM卡座上电复位错误["<<m_ReaderPara->cpuport<<"]");
        return nRet;
    }
    nRet=this->selectADFBySFI(MF_SFI);
    if(nRet)
        return nRet;
    //读取终端编号
    nRet=ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
    if(nRet) {
        return nRet;
    }
    bcd2asc(ucRespData,6,szTermno);
    strcpy(sTermno,szTermno);
    return 0;
}
int DGPSAM::CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac) {
    string sCmd;
    unsigned char uCmd[256],uResp[256],nRespLen;
    int ret;
    char temp[20]="";
    if(strlen(transpack->sCardPhyID)!=16) {
        if(strlen(transpack->sCardPhyID)==8) {
            strcat(transpack->sCardPhyID,"80000000");
        } else {
            SET_ERR("物理卡号长度错误");
        }
    }
    if(strlen(transpack->sTermno)!=12) {
        SET_ERR("终端编号长度错误");
        return -1;
    }
    if(strlen(transpack->sTransDate)!=8) {
        SET_ERR("交易日期长度错误");
        return -1;
    }
    if(strlen(transpack->sTransTime)!=6) {
        SET_ERR("交易时间长度错误");
        return -1;
    }
    if(transpack->nTransAmt==0) {
        SET_ERR("交易金额不能为0");
        return -1;
    }

    ret=this->selectADFBySFI("3F01");
    if(ret) {
        return ret;
    }
    memset(uCmd,0,sizeof uCmd);
    memset(uResp,0,sizeof uResp);
    sCmd = "807000001C";
    sCmd += transpack->sRandom;
    sprintf(temp,"%04X",transpack->nPayCardCnt);
    sCmd += temp;
    sprintf(temp,"%08X",transpack->nTransAmt);
    sCmd += temp;
    if(transpack->nTransType == ks_cardtype_base::TRNS_TYPE_PURCHASE
            || transpack->nTransType == ks_cardtype_base::TRNS_TYPE_POSTPAID) {
        sCmd += "06";
    } else if(transpack->nTransType == ks_cardtype_base::TRNS_TYPE_CAPP_PURCHASE) {
        sCmd += "09";
    } else if(transpack->nTransType == ks_cardtype_base::TRNS_TYPE_GRAYLOCK) {
        sCmd += "92";
    } else {
        return -1;
    }
    sCmd += transpack->sTransDate;
    sCmd += transpack->sTransTime;
    // 密钥版本 + 算法标识
    sCmd += "0100";
    sCmd += transpack->sCardPhyID;
    ret=Adpu4HexSAM((char*)sCmd.c_str(),sCmd.size(),uResp,nRespLen);
    if(ret) {
        return ret;
    }

    dec2hex(uResp+4,4,sMac);
    transpack->nTermSeqno = get_4byte_int(uResp);
    return 0;
}

int DGPSAM::CalcSafeMac(const char *cmd,int len,char *sMac) {
    return 0;
}
int DGPSAM::CalcDepositMac(ST_TRANSPACK *transpack) {
    return 0;
}
int DGPSAM::CalcConsumeMac(ST_TRANSPACK *transpack) {
    return 0;
}

char * DGPSAM::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
    switch( nErrCode) {
    case 0x9000:
    case 0x0000:
        sprintf(m_ErrMsg,"Err-%04X:成功",nErrCode);
        break;
    case 0x6200:
        sprintf(m_ErrMsg,"Err-%04X:读卡设备中卡未插入到位",nErrCode);
        break;
    case 0x6281:
        sprintf(m_ErrMsg,"Err-%04X:回送的数据可能错误",nErrCode);
        break;
    case 0x6283:
        sprintf(m_ErrMsg,"Err-%04X:选择文件无效，文件或密钥校验错误",nErrCode);
        break;
    case 0x63C1:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有1次机会",nErrCode);
        break;
    case 0x63C2:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有2次机会",nErrCode);
        break;
    case 0x63C3:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有3次机会",nErrCode);
        break;
    case 0x63C4:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有4次机会",nErrCode);
        break;
    case 0x63C5:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有5次机会",nErrCode);
        break;
    case 0x63C6:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有6次机会",nErrCode);
        break;
    case 0x63C7:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有7次机会",nErrCode);
        break;
    case 0x63C8:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有8次机会",nErrCode);
        break;
    case 0x63C9:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有9次机会",nErrCode);
        break;
    case 0x63CA:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有10次机会",nErrCode);
        break;
    case 0x63CB:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有11次机会",nErrCode);
        break;
    case 0x63CC:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有12次机会",nErrCode);
        break;
    case 0x63CD:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有13次机会",nErrCode);
        break;
    case 0x63CE:
        sprintf(m_ErrMsg,"Err-%04X:密码错,还有14次机会",nErrCode);
        break;
    case 0x6400:
        sprintf(m_ErrMsg,"Err-%04X:状态标志未改变",nErrCode);
        break;
    case 0x6581:
        sprintf(m_ErrMsg,"Err-%04X:写EEPROM不成功",nErrCode);
        break;
    case 0x6700:
        sprintf(m_ErrMsg,"Err-%04X:指令的命令长度不正确",nErrCode);
        break;
    case 0x6900:
        sprintf(m_ErrMsg,"Err-%04X:CLA与线路保护要求不匹配",nErrCode);
        break;
    case 0x6901:
        sprintf(m_ErrMsg,"Err-%04X:无效的状态",nErrCode);
        break;
    case 0x6981:
        sprintf(m_ErrMsg,"Err-%04X:命令与文件结构不相容",nErrCode);
        break;
    case 0x6982:
        sprintf(m_ErrMsg,"Err-%04X:不满足写或修改卡片的安全状态",nErrCode);
        break;
    case 0x6983:
        sprintf(m_ErrMsg,"Err-%04X:密钥已经被锁死",nErrCode);
        break;
    case 0x6984:
        sprintf(m_ErrMsg,"Err-%04X:随机数无效,请先取随机数",nErrCode);
        break;
    case 0x6985:
        sprintf(m_ErrMsg,"Err-%04X:使用条件不满足",nErrCode);
        break;
    case 0x6986:
        sprintf(m_ErrMsg,"Err-%04X:不满足命令执行条件,当前文件不是EF",nErrCode);
        break;
    case 0x6987:
        sprintf(m_ErrMsg,"Err-%04X:无安全报文或MAC丢失",nErrCode);
        break;
    case 0x6988:
        sprintf(m_ErrMsg,"Err-%04X:安全报文数据MAC不正确",nErrCode);
        break;
    case 0x6A80:
        sprintf(m_ErrMsg,"Err-%04X:数据域参数错误",nErrCode);
        break;
    case 0x6A81:
        sprintf(m_ErrMsg,"Err-%04X:功能不支持或卡中无MF或卡片已经锁定",nErrCode);
        break;
    case 0x6A82:
        sprintf(m_ErrMsg,"Err-%04X:卡片中文件未找到",nErrCode);
        break;
    case 0x6A83:
        sprintf(m_ErrMsg,"Err-%04X:卡片中记录未找到",nErrCode);
        break;
    case 0x6A84:
        sprintf(m_ErrMsg,"Err-%04X:文件无足够空间",nErrCode);
        break;
    case 0x6A86:
        sprintf(m_ErrMsg,"Err-%04X:参数P1P2错误",nErrCode);
        break;
    case 0x6A87:
        sprintf(m_ErrMsg,"Err-%04X:无安全报文",nErrCode);
        break;
    case 0x6A88:
        sprintf(m_ErrMsg,"Err-%04X:密钥未找到",nErrCode);
        break;
    case 0x6B00:
        sprintf(m_ErrMsg,"Err-%04X:在达到Le/Lc字节之前文件结束,偏移量错误",nErrCode);
        break;
    case 0x6D00:
        sprintf(m_ErrMsg,"Err-%04X:无效的INS",nErrCode);
        break;
    case 0x6E00:
        sprintf(m_ErrMsg,"Err-%04X:无效的CLA",nErrCode);
        break;
    case 0x6F00:
        sprintf(m_ErrMsg,"Err-%04X:数据无效",nErrCode);
        break;
    case 0x6FF0:
        sprintf(m_ErrMsg,"Err-%04X:读卡器系统错误",nErrCode);
        break;
    case 0xFFFF:
        sprintf(m_ErrMsg,"Err-%04X:无法判断的错误",nErrCode);
        break;
    case 0x9210:
        sprintf(m_ErrMsg,"Err-%04X:卡片该DF下内存不足",nErrCode);
        break;
    case 0x9220:
        sprintf(m_ErrMsg,"Err-%04X:文件ID已存在",nErrCode);
        break;
    case 0x9240:
        sprintf(m_ErrMsg,"Err-%04X:卡片内存问题",nErrCode);
        break;
    case 0x9302:
        sprintf(m_ErrMsg,"Err-%04X:MAC错误",nErrCode);
        break;
    case 0x9303:
        sprintf(m_ErrMsg,"Err-%04X:应用已被锁定",nErrCode);
        break;
    case 0x9400:
        sprintf(m_ErrMsg,"Err-%04X:没有选择当前的EF文件ID",nErrCode);
        break;
    case 0x9401:
        sprintf(m_ErrMsg,"Err-%04X:金额不足",nErrCode);
        break;
    case 0x9402:
        sprintf(m_ErrMsg,"Err-%04X:超出范围或没有该记录",nErrCode);
        break;
    case 0x9403:
        sprintf(m_ErrMsg,"Err-%04X:密钥未找到",nErrCode);
        break;
    case 0x9404:
        sprintf(m_ErrMsg,"Err-%04X:EF的文件ID没有找到",nErrCode);
        break;
    case 0x9406:
        sprintf(m_ErrMsg,"Err-%04X:所需的MAC不可用",nErrCode);
        break;
    case 0x9802:
        sprintf(m_ErrMsg,"Err-%04X:没有所要的密钥",nErrCode);
        break;
    case 0x9804:
        sprintf(m_ErrMsg,"Err-%04X:存在条件没有满足或MAC错",nErrCode);
        break;
    case 0x9810:
        sprintf(m_ErrMsg,"Err-%04X:的应用被锁定",nErrCode);
        break;
    case 0x9835:
        sprintf(m_ErrMsg,"Err-%04X:没有取随机数",nErrCode);
        break;
    case 0x9840:
        sprintf(m_ErrMsg,"Err-%04X:该KEY被锁住",nErrCode);
        break;
    default:
        sprintf(m_ErrMsg,"Err-%04X:不知道的错误",nErrCode);
        break;
    }
    if(sErrInfo)
        strcpy(sErrInfo,m_ErrMsg);
    return m_ErrMsg;
}
int DGPSAM::CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac) {
    char szBuf[512];

    string sCmd,sMacData;
    vector<string> CmdVector;
    int nRet;
    int nCmdLen;
    byte uCmd[256];
    byte uResp[256];

    nRet=this->selectADFBySFI("3F01");
    if(nRet)
        return nRet;
    sCmd="801A280208";
    sCmd+=cardtype->m_appSerialNo;
    if(strlen(cardtype->m_appSerialNo)==8)
        sCmd+="80000000";
    CmdVector.push_back(sCmd);

    memset(szBuf,0,sizeof(szBuf));
    int nCmdBufLen=strlen(szCmdbuf);
    memcpy(szBuf,szCmdbuf,nCmdBufLen);
    nCmdBufLen/=2;
    if( nCmdBufLen%8 )
        memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);
    else
        memcpy(szBuf+nCmdBufLen*2,"8000000000000000",16);

    sMacData=cardtype->m_szRandomNum;
    sMacData+=szBuf;

    int nMacDataLen=sMacData.size()/2;
    const char *pBuf=sMacData.c_str();
    int nBlockLen=0x30;
    if(nMacDataLen>nBlockLen) {
        sCmd="80FA0700";
        sCmd+=ltohex(nBlockLen);
        sCmd.append(pBuf,nBlockLen*2);
        CmdVector.push_back(sCmd);
        pBuf+=nBlockLen*2;
        nMacDataLen -= nBlockLen;
        if(nMacDataLen>nBlockLen) {
            sCmd="80FA0300";
            sCmd+=ltohex(nBlockLen);
            sCmd.append(pBuf,nBlockLen*2);
            CmdVector.push_back(sCmd);
            nMacDataLen -= nBlockLen;
            pBuf+=nBlockLen*2;
        }
        sCmd="80FA0100";
        sCmd+=ltohex(nMacDataLen);
        sCmd.append(pBuf,nMacDataLen*2);
        CmdVector.push_back(sCmd);
    } else {
        sCmd="80FA0500";
        sCmd+=ltohex(nMacDataLen);
        sCmd+=sMacData;
        CmdVector.push_back(sCmd);
    }
    //sCmd="00C0000004";
    //CmdVector.push_back(sCmd);

    ks_cpu_cmd_t cmd;
    for(int i=0; i<CmdVector.size(); i++) {
        sCmd=CmdVector[i];
        if("ATR"==sCmd) {
            unsigned char rlen;
            nRet= m_Reader->cpucard_poweron(m_ReaderPara,KS_PSAM,&rlen,uResp);
            if(nRet) {
                SET_ERR("SAM卡座上电复位错误,PSAM卡计算MAC失败 请检查PSAM卡是否正确安装");
                return nRet;
            }
            continue;
        }
        hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
        int nRet=0;
        memset(&cmd,0,sizeof cmd);
        cmd.cmd_type = 0;
        cmd.send_len = nCmdLen;
        cmd.send_buf = uCmd;
        cmd.recv_buf = uResp;
        nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
        if(nRet) {
            if(cmd.cmd_retcode) {
                SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL)<<",PSAM卡计算MAC失败");
                return cmd.cmd_retcode;
            } else {
                SET_ERR(m_Reader->GetErrMsg(NULL)<<",PSAM卡计算MAC失败");
                return nRet;
            }
        }
    }
    dec2hex(uResp,4,szMac);
    return 0;
}

int DGPSAM::CalcExtAuthEncrypt4Sam(ks_cardtype_base *cardtype,int keyidx,const char *szCmdbuf,char *szEncrypt) {
    char szBuf[512];

    string sCmd,sMacData;
    vector<string> CmdVector;
    int nRet=0;
    byte uResp[256]= {0};

    char szCardPhyID[17]= {0};
    strncpy(szCardPhyID,cardtype->m_szCardUID,16);
    if(strlen(szCardPhyID)!=16) {
        if(strlen(szCardPhyID)==8) {
            strcat(szCardPhyID,"80000000");
        } else {
            SET_ERR("计算外部认证时物理卡号长度错误");
            return -1;
        }
    }
    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof cmd);
    cmd.recv_buf=uResp;


    nRet = this->selectADFBySFI("DF03");
    if(nRet)
        return nRet;
    //分散密钥
    sCmd="801A27"+ltohex(keyidx)+"08";
    sCmd+=szCardPhyID;
//	if(strlen(szCardPhyID)==8)
//		sCmd+="80000000";
    CmdVector.push_back(sCmd);

    memset(szBuf,0,sizeof(szBuf));
    int nCmdBufLen=strlen(szCmdbuf);
    memcpy(szBuf,szCmdbuf,nCmdBufLen);
    nCmdBufLen/=2;
    if( nCmdBufLen%8 )
        memcpy(szBuf+nCmdBufLen*2,"8000000000000000",(8-nCmdBufLen%8)*2);

    sMacData=szBuf;

    int nMacDataLen=sMacData.size()/2;
    const char *pBuf=sMacData.c_str();
    int nBlockLen=0x30;
    if(nMacDataLen>nBlockLen) {
        sCmd="80FA0700";
        sCmd+=ltohex(nBlockLen);
        sCmd.append(pBuf,nBlockLen*2);
        CmdVector.push_back(sCmd);
        pBuf+=nBlockLen*2;
        nMacDataLen -= nBlockLen;
        if(nMacDataLen>nBlockLen) {
            sCmd="80FA0300";
            sCmd+=ltohex(nBlockLen);
            sCmd.append(pBuf,nBlockLen*2);
            CmdVector.push_back(sCmd);
            nMacDataLen -= nBlockLen;
            pBuf+=nBlockLen*2;
        }
        sCmd="80FA0100";
        sCmd+=ltohex(nMacDataLen);
        sCmd.append(pBuf,nMacDataLen*2);
        CmdVector.push_back(sCmd);
    } else {
        sCmd="80FA0000";
        sCmd+=ltohex(nMacDataLen);
        sCmd+=sMacData;
        CmdVector.push_back(sCmd);
    }
    //sCmd="00C0000008";
    //CmdVector.push_back(sCmd);

    for(int i=0; i<CmdVector.size(); i++) {
        sCmd=CmdVector[i];
        if("ATR"==sCmd) {
            unsigned char rlen;
            unsigned char rbuff[256];
            nRet= m_Reader->cpucard_poweron(m_ReaderPara,KS_PSAM,&rlen,rbuff);
            if(nRet) {
                SET_ERR("SAM卡座上电复位错误");
                return nRet;
            }
            continue;
        }
        //string_replace(sCmd," ","");
        //hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
        memset(uResp,0,sizeof(uResp));
        cmd.cmd_type = 1;
        cmd.send_len = sCmd.size();
        cmd.send_buf = (byte*)sCmd.c_str();
        cmd.recv_buf = uResp;
        nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
        if(nRet) {
            if(cmd.cmd_retcode) {
                SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
                return cmd.cmd_retcode;
            } else {
                SET_ERR(m_Reader->GetErrMsg(NULL));
                return nRet;
            }
        }
    }
    dec2hex(uResp,8,szEncrypt);
    return 0;
}

int DGPSAM::InitDll(ks_cardlib_license *lic) {
    m_license = lic;
    return 0;
}
////////////////////////////////////////////////////////////////////////
int __stdcall register_sam_op(ks_psamcard_base *&sam) {
    sam = new DGPSAM();
    return 0;
}