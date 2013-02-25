#include "ks_cmccpsamcard.h"
#include <vector>
#include <string>
#include "mystring.h"
#include "global_func.h"
#include "des.h"
#include "kscardtype.h"
using namespace std;


ks_cmccpsamcard::ks_cmccpsamcard():ks_psamcard_base(),enterpriceAppID_(0),loadKeyVer_(1) {
    memset(strEnterpriceCode_,0,sizeof strEnterpriceCode_);
    memset(enterpriceCode_,0,sizeof enterpriceCode_);
    memset(mfCardLibName_,0,sizeof mfCardLibName_);

}

ks_cmccpsamcard::~ks_cmccpsamcard() {
}


int ks_cmccpsamcard::PublishPSAMCard(ST_PSAMCARD* PSAMCard) {
    return KS_NOTSUPPORT;
}
int ks_cmccpsamcard::CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac) {
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

int ks_cmccpsamcard::RecyclePSAMCard() {
    return KS_NOTSUPPORT;
}
int ks_cmccpsamcard::ReadBinaryFile4Sam(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) {
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
int ks_cmccpsamcard::ReadPSAMCard(ST_PSAMCARD* PSAMCard) {
    char szBuf[256];
    string sCmd,sMsg;
    int i;
    int ret;
    byte ucRespData[256],ucRespLen,rlen,rbuf[256];

    memset(ucRespData,0,sizeof(ucRespData));
    ret=ReadBinaryFile4Sam(21,0x00,14,ucRespData);
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
    ret=ReadBinaryFile4Sam(22,0x00,6,ucRespData);
    if(ret) {
        SET_ERR("读PSAM卡0x16文件失败");
        return ret;
    }
    memset(szBuf,0,sizeof(szBuf));
    bcd2asc(ucRespData,6,szBuf);
    for(i=0; i<11; i++) {
        if(szBuf[i]!='0')
            break;
    }
    strcpy(PSAMCard->sTermID,szBuf+i);
    return 0;
}

void  hex_a(unsigned char *hex,unsigned char *a,int len) {
    short i;
    unsigned char aHighbit;

    for(i=0; i<len; i++) {
        aHighbit=hex[i]>>4;
        if (aHighbit<0x0a) {
            a[2*i] = 0x30+aHighbit;
        } else {
            a[2*i] = 0x37+aHighbit;
        }
        aHighbit=hex[i]&0x0f;
        if (aHighbit<0x0a) {
            a[2*i+1] = 0x30+aHighbit;
        } else {
            a[2*i+1] = 0x37+aHighbit;
        }
    }
    a[2*i] = 0;
}


int ks_cmccpsamcard::ReadPSAMTermno(char *sTermno) {
    int nRet=0;
    string sCmd,sMsg;
    char szTermno[13]= {0};
    byte rlen,rbuff[256]= {0};
    byte ucRespData[256]= {0};
    //上电复位
    m_PowerOn = 0;
    nRet = this->ResetPSAM();
    if(nRet) {
        SET_ERR("SAM卡座上电复位错误");
        return nRet;
    }
    //读取终端编号
    nRet=ReadBinaryFile4Sam(0x16,0x00,6,ucRespData);
    if(nRet) {
        return nRet;
    }

    hex_a(ucRespData, (byte*)szTermno, 6);

    //bcd2asc(ucRespData,6,szTermno);
    strcpy(sTermno,szTermno);
    return 0;
}
int ks_cmccpsamcard::CalcTransMac4Sam(ST_TRANSPACK *transpack,char *sMac) {
    char szData[256];
    byte uData[256],rlen;
    //ks_cpu_cmd_t cmd;
    int nRet;
    std::string sCmd;

    //sCmd="00A4040010D1560001018000000000000100000000";
    //nRet = this->Adpu4HexSAM(sCmd.c_str(),sCmd.length(),uData,rlen);
    nRet=this->selectADFByName("D1560001018000000000000100000000");
    if(nRet) {
        SET_ERR("选择目录错误["<<GetErrMsgByErrCode(nRet,NULL)<<"]");
        return nRet;
    }

    // 计算MAC1, 2级分散
    sCmd = "8070000024";
    sprintf(szData,"%s%04X%08X06%s%s0100",transpack->sRandom,transpack->nPayCardCnt,
            transpack->nTransAmt,transpack->sTransDate,transpack->sTransTime);
    sCmd += szData;
    // 2级分散
    sprintf(szData,"%s%02X",transpack->sCardPhyID+2,this->loadKeyVer_);
    sCmd += szData;
    // 1级分散
    sprintf(szData,"03%02X800000000000",this->loadKeyVer_);
    sCmd += szData;


    //////////////////////////////////////
    nRet = this->Adpu4HexSAM(sCmd.c_str(),sCmd.length(),uData,rlen);
    if(nRet) {
        SET_ERR("选择目录错误["<<GetErrMsgByErrCode(nRet,NULL)<<"]");
        return nRet;
    }
    transpack->nTermSeqno = get_4byte_int(uData);
    dec2hex(uData+4,4,sMac);
    return 0;
}

int ks_cmccpsamcard::CalcSafeMac(const char *cmd,int len,char *sMac) {
    return 0;
}
int ks_cmccpsamcard::CalcDepositMac(ST_TRANSPACK *transpack) {
    return 0;
}
int ks_cmccpsamcard::CalcConsumeMac(ST_TRANSPACK *transpack) {
    return 0;
}

char * ks_cmccpsamcard::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
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
int ks_cmccpsamcard::CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac) {
    //ks_cpu_cmd_t cmd;
    char szCmd[256] = {0},szData[256] = {0};
    char szCmdTemp[512] = {0};
    unsigned char uResp[256] = {0};
    int szCmdLen;
    int nRet;
    byte respLen;
    std::vector<std::string> vCmd;
    std::string sCmd;

    // select adf
    //sprintf(szCmd,"00A4040010D1560001018000000000000100000000");
    //nRet = this->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,respLen);
    nRet=this->selectADFByName("D1560001018000000000000100000000");
    if(nRet) {
        SET_ERR("执行指令失败,ret["<<nRet<<"]");
        return -1;
    }

    // for sam card


    // 3级分散
    if(strlen(cardtype->m_szRandomNum)<16) {
        int i = strlen(cardtype->m_szRandomNum);
        cardtype->m_szRandomNum[i++] = '8';
        cardtype->m_szRandomNum[i++] = '0';
        while(i<16) cardtype->m_szRandomNum[i++] = '0';
        cardtype->m_szRandomNum[i] = 0;
    }
    sprintf(szCmd,"801A040110%s",cardtype->m_szRandomNum);
    sCmd = szCmd;
    // 2级分散
    sprintf(szData,"%s%02X",cardtype->m_appSerialNo+2,this->loadKeyVer_);
    sCmd += szData;
    // 1级分散
    //sprintf(szData,"%02X%02X800000000000",this->enterpriceAppID_,this->loadKeyVer_);
    //sCmd += szData;

    vCmd.push_back(sCmd);


    memset(szCmdTemp,0,sizeof szCmdTemp);
    strcpy(szCmdTemp,szCmdbuf);
    szCmdLen = strlen(szCmdbuf);
    if((szCmdLen/2) % 8 != 0) {
        strncat(szCmdTemp,"8000000000000000",(8-((szCmdLen/2)%8))*2);
    }
    int nBlockLen=0x30;
    szCmdLen = strlen(szCmdTemp);
    int nCmdLen = szCmdLen / 2;
    if(nCmdLen > nBlockLen) {
        int nBeginPos = 0;
        while(nBeginPos < nCmdLen) {
            memset(szCmd,0,sizeof szCmd);
            if(nBeginPos == 0) {
                // 第一块MAC
                sprintf(szCmd,"80FA0700%02X0000000000000000",nBlockLen+8);
                strncat(szCmd,szCmdTemp+nBeginPos*2,nBlockLen * 2);
                nBeginPos += nBlockLen;
            } else if(nBeginPos + nBlockLen >= nCmdLen) {
                // 最后一块
                sprintf(szCmd,"80FA0100%02X",nCmdLen - nBeginPos);
                strncat(szCmd,szCmdTemp+nBeginPos*2,(nCmdLen - nBeginPos) * 2);
                nBeginPos += nCmdLen - nBeginPos;
            } else {
                // 下一块
                sprintf(szCmd,"80FA0300%02X",nBlockLen);
                strncat(szCmd,szCmdTemp+nBeginPos*2,nBlockLen * 2);
                nBeginPos += nBlockLen;
            }
            vCmd.push_back(szCmd);
        }
    } else {
        sprintf(szCmd,"80FA0500%02X%s",nCmdLen,szCmdTemp);
        vCmd.push_back(szCmd);
    }
    std::vector<std::string>::iterator iter;
    for(iter = vCmd.begin(); iter != vCmd.end(); ++iter) {
        std::string sCmd = *iter;
        /*
        memset(&cmd,0,sizeof cmd);
        cmd.send_buf = (unsigned char*)sCmd.c_str();
        cmd.send_len = sCmd.length();
        cmd.recv_buf = uResp;
        cmd.cmd_type = 1;
        nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
        */
        nRet = this->Adpu4HexSAM(sCmd.c_str(),sCmd.length(),uResp,respLen);
        if(nRet) {
            SET_ERR("执行指令失败,ret["<<nRet<<"]");
            return -1;
        }
    }
    dec2hex(uResp,4,szMac);
    return 0;
}

int ks_cmccpsamcard::CalcExtAuthEncrypt4Sam(ks_cardtype_base *cardtype,int keyidx,const char *szCmdbuf,char *szEncrypt) {
    char szBuf[512];

    string sCmd,sMacData;
    vector<string> CmdVector;
    int nRet=0;
    byte uResp[256]= {0},respLen;

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

    //sCmd="ATR";
    //CmdVector.push_back(sCmd);

    //sCmd="00A4040010D1560001018000000000000100000000";
    //CmdVector.push_back(sCmd);
    nRet=this->selectADFByName("D1560001018000000000000100000000");
    if(nRet) {
        return nRet;
    }
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
            nRet= this->ResetPSAM();
            if(nRet) {
                SET_ERR("SAM卡座上电复位错误");
                return nRet;
            }
            continue;
        }
        //string_replace(sCmd," ","");
        //hex2dec(sCmd.c_str(),sCmd.size(),uCmd,nCmdLen);
        memset(uResp,0,sizeof(uResp));
        /*
        cmd.cmd_type = 1;
        cmd.send_len = sCmd.size();
        cmd.send_buf = (byte*)sCmd.c_str();
        cmd.recv_buf = uResp;
        nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_PSAM);
        */
        nRet = this->Adpu4HexSAM(sCmd.c_str(),sCmd.length(),uResp,respLen);
        if(nRet) {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    dec2hex(uResp,8,szEncrypt);
    return 0;
}
int ks_cmccpsamcard::InitDll(ks_cardlib_license *lic) {
    char param[512] = {0};
    int paramLen = 0,len;
    m_license = lic;

    paramLen = sizeof(param) - 1;
    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.cmcc.enterpricecode",param,paramLen)) {
        SET_ERR("未设置企业ID");
        return -1;
    }
    if(strlen(param) != 12) {
        SET_ERR("企业ID号长度不正确");
        return -1;
    }
    strcpy(strEnterpriceCode_,param);
    hex2dec(param,12,enterpriceCode_,len);
    m_license->get_public_int_param("kscardlib.cmcc.enterprice.appid",&enterpriceAppID_);

    if(enterpriceAppID_< 1 ) { //|| enterpriceAppID_ > 0x1F)
        SET_ERR("企业自定义子应用ID号错误");
        return -1;
    }
    loadKeyVer_ = 1;
    return 0;
}

////////////////////////////////////////////////////////////////////////
int __stdcall register_sam_op(ks_psamcard_base *&sam) {
    sam = new ks_cmccpsamcard();
    return 0;
}