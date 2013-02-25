#include "ks_ctcardtype.h"
#include "global_func.h"
#include "des.h"
#include <time.h>
#include <assert.h>
#include "yktclt.h"
//static ks_ctcardtype g_CardType;

static const unsigned char statickey[17]="3230303530313331";


#define ZERO_BLOCK(m) do{ (m)=0; } while(0)
#define SET_BLOCK(m,b) do { (m) |= (1 << (b)); } while(0)
#define CLR_BLOCK(m,b) do { (m) &= (^(1 << (b))); } while(0)
#define ISSET_BLOCK(m,b) (((m) & (1<<(b))) != 0)

#define EASY_SET_BLOCK(m,of) do {int _b=(of)/16;ZERO_BLOCK(m); SET_BLOCK(m,_b); } while(0)

#define IS_LOAD_KEY() do { int r = testLoadKey(); if(r) return r; }while(0)


ks_ctcardtype::ks_ctcardtype():CCardType(),m_isLoadKey(0),m_lastLoginSect(MF_MAX_SECTNO)
    ,m_packageIdxSect(9),m_packageSect(1),ctAppID_(3),m_recordSectBegin(2),m_lastRecIdx(-1) {
    this->set_cardtype_name("ks_ctcardtype.dll");
    memset(m_initSectMap,'0',sizeof m_initSectMap);
    memset(m_recycleSectMap,'1',sizeof m_recycleSectMap);
    m_mfcard = &m_cardinfo;
    memset(&m_cardinfo,0,sizeof m_cardinfo);
    memset(&m_cardSect,0,sizeof m_cardSect);
    m_defaultCardType = KS_SIMCARD;
}

void ks_ctcardtype::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
    int i = 0;
    cardTypes[i++] = 0x0504;
    cardTypes[i++] = 0x0300;
    cardTypes[i++] = 0x0400;
    cnt = i;
}

int ks_ctcardtype::InitCardTypeDLL() {
    char param[512] = "";
    int maxlen;
    int ret=0;
    int i;


    if(m_license->get_public_int_param("kscardlib.mfcard.maxsect",&m_maxSectNo)) {
        return -1;
    }
    if(m_license->get_public_int_param("kscardlib.mfcard.minsect",&m_minSectNo)) {
        return -1;
    }
    maxlen = sizeof(param)-1;
    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.mfinit.sect",param,maxlen)) {
        return -1;
    }
    strcpy(m_initSectMap,param);

    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.mfrecycle.sect",param,maxlen)) {
        return -1;
    }
    strcpy(m_recycleSectMap,param);

    m_license->get_public_int_param("kscardlib.mfcard.alg",&m_keyAlg);
    m_license->get_public_int_param("kscardlib.mfcard.ver",&m_cardVer);

    if(m_cardVer != 2010)
        return -1;


    m_license->get_public_int_param("kscardlib.mfcard.mainsect",&m_mainPackSect);

    m_license->get_public_int_param("kscardlib.mfcard.init.keytype",&ret);
    if(ret == 0)
        m_initKeyType = MF_KEYA;
    else
        m_initKeyType = MF_KEYB;

    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.mfcard.init.loginkey",param,12)) {
        memset(m_initLoginKey,0xFF,sizeof m_initLoginKey);
    } else {
        hex2dec(param,12,m_initLoginKey,ret);
    }

    memset(param,0,sizeof param);
    if(m_license->get_public_param("kscardlib.usercode",param,12)) {
        return -1;
    }
    if(strlen(param) != 12)
        return -1;
    memset(strUserCode_,0,sizeof strUserCode_);
    sprintf(strUserCode_,param,12);

    ret = CCardType::InitCardTypeDLL();
    if(ret)
        return ret;
    // ��ʼ������λ
    for(i= 0; i < sizeof(m_ctrlBit)/sizeof(m_ctrlBit[0]); ++i) {
        if( i == 5 || i == 6 || i == 7) {
            memcpy(m_ctrlBit[i].newCtrlBit,"\x78\x77\x88\x00",4);
            m_ctrlBit[i].readKey = MF_KEYA | MF_KEYB;
            m_ctrlBit[i].writeKey = MF_KEYB;
        } else if(i == 1) {
            memcpy(m_ctrlBit[i].newCtrlBit,"\x08\x77\x8F\x69",4);
            m_ctrlBit[i].readKey = MF_KEYA | MF_KEYB;
            m_ctrlBit[i].writeKey = MF_KEYB;
            m_ctrlBit[i].decKey = MF_KEYA | MF_KEYB;
            m_ctrlBit[i].incKey = MF_KEYB;
        } else if(i == 0 || i == 2 || i == 3 || i == 4 || i == 9 || i == 8) {
            memcpy(m_ctrlBit[i].newCtrlBit,"\x7F\x07\x88\x00",4);
            m_ctrlBit[i].readKey = MF_KEYA | MF_KEYB;
            m_ctrlBit[i].writeKey = MF_KEYA | MF_KEYB;
        } else {
            memcpy(m_ctrlBit[i].newCtrlBit,"\xFF\x07\x80\x69",4);
            m_ctrlBit[i].readKey = MF_KEYA | MF_KEYB;
            m_ctrlBit[i].writeKey = MF_KEYA | MF_KEYB;
        }

        if(m_initKeyType == MF_KEYA)
            memcpy(m_ctrlBit[i].orignCtrlBit,"\xFF\x07\x80\x69",4);
        else
            memcpy(m_ctrlBit[i].orignCtrlBit,"\xFF\x07\x80\x69",4);
    }
    initAllCardDef();
    return 0;
}
int ks_ctcardtype::testLoadKey() {
    if(this->m_CardKeys.bLoad ==0) {
        SET_ERR("Mifare1��Կδװ��");
        return KS_UNAUTH_TERM;
    }
    return 0;
}
int  ks_ctcardtype::OpenPort() {
    int nRet;
    ks_cpu_cmd_t cmd;
    byte uResp[256] = {0};
    char szCmd[256] = {0};
    nRet = CCardType::OpenPort();
    if(nRet) {
        return nRet;
    }
    // �޸�RF ����
    sprintf(szCmd,"90B00180180000000000000000000000000800000300A2000000000000");
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char *)szCmd;
    cmd.recv_buf = uResp;
    cmd.send_len = strlen(szCmd);
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("����RF����ʧ��");
        return nRet;
    }
    // ѡ��Ӧ��
    sprintf(szCmd,"A0A40400104163636F756E74657220417070000000");
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (unsigned char *)szCmd;
    cmd.recv_buf = uResp;
    cmd.send_len = strlen(szCmd);
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("ѡ��Ӧ��ʧ��");
        return nRet;
    }
    return 0;
}
int ks_ctcardtype::RequestCard(char* szCardPhyID/* =NULL */) {
    int nRet=0;
    int i;
    byte decphyno[8]= {0};
    char currentPhyNo[20] = {0};

    m_lastLoginSect = MF_MAX_SECTNO;
    memset(m_ErrMsg,0,sizeof(m_ErrMsg));
    m_lastRecIdx = -1;
    nRet=m_Reader->request_card(m_ReaderPara,currentPhyNo,m_defaultCardType);
    if(nRet) {
        SET_ERR("Ѱ������,"<<m_Reader->GetErrMsg(NULL)<<"]type : "<<m_defaultCardType);
        return nRet;
    }
    nRet = this->checkCardType(m_Reader->card_type());
    if(nRet) {
        SET_ERR("Ѱ������,��֧�ֿ�����type["<<m_Reader->card_type()<<"]");
        return nRet;
    }

    if(szCardPhyID)
        strcpy(szCardPhyID,currentPhyNo);

    if(strcmp(m_szCardUID,currentPhyNo)!=0) {
        memset(m_cardSect,0,sizeof m_cardSect);
    } else {
        // �����ͬһ�ſ���Ѱ������Ҫ���û���
        for(i = 0; i < MF_MAX_SECTNO; ++i) {
            memset(m_cardSect[i].block_buffer,0,sizeof m_cardSect[i].block_buffer);
            memset(m_cardSect[i].write_buffer,0,sizeof m_cardSect[i].write_buffer);
            m_cardSect[i].has_read = 0;
        }
    }
    strcpy(m_szCardUID,currentPhyNo);
    this->m_lastLoginSect = MF_MAX_SECTNO;

    return 0;
}

int ks_ctcardtype::LoadKeysFromKeyCard(const char *sKeyCardPwd) {
    int ret;
    ret = CCardType::LoadKeysFromKeyCard(sKeyCardPwd);
    if(ret) {
        return ret;
    }
    if(m_keyAlg==0) { // �����ϵ�ģʽ
        memset(m_mainkey,0,sizeof m_mainkey);
        memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
        m_isLoadKey = 1;
    }
    return 0;
}
int ks_ctcardtype::SetKeyCard(ks_cardtype_base *c) {
    int ret;
    ret = CCardType::SetKeyCard(c);
    if(ret)
        return ret;
    if(m_keyAlg==0) { // �����ϵ�ģʽ
        memset(m_mainkey,0,sizeof m_mainkey);
        memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
        m_isLoadKey = 1;
    }
    return 0;
}
int ks_ctcardtype::VerifyPin(const char* sPin) {
    return 0;
}
unsigned char ks_ctcardtype::CalcCRC8(const unsigned char *data,int len) {
    unsigned char crc8=0;
    crc8 = calc_crc8(data,len);
    return crc8;
}
int ks_ctcardtype::CheckCRC8(const unsigned char *data,int len,unsigned char crc8) {
    unsigned char crc=0;
    crc = CalcCRC8(data,len);
    if(crc == crc8)
        return 0;
    return -1;
}
int ks_ctcardtype::InitUserCard(const char *sShowCardNo) {
    int i,j,block,nRet;
    byte keya[6],keyb[6],buffer[16];
    byte init_keya[6],data_buffer[16];
    char datetime[20]="";
    char temp[10] = "";

    if(this->RequestCard(NULL)) {
        SET_ERR("��ſ�");
        return KS_REQUESTCARD;
    }
    memcpy(init_keya,m_initLoginKey,6);

    m_lastLoginSect = MF_MAX_SECTNO;
    for(i=m_minSectNo; i< m_maxSectNo; ++i) {
        // ����ʼ��
        if(m_initSectMap[i] == '0') continue;
        //
        if(CalcCardKeyA(i,&(m_cardSect[i]))) {
            SET_ERR("��ʼ��Mifare1����["<<i<<"]����keyaʧ��");
            return KS_LOGINCARD;
        }
        memcpy(keya,m_cardSect[i].key,6);
        if(CalcCardKeyB(i,&(m_cardSect[i]))) {
            SET_ERR("��ʼ��Mifare1����������keybʧ��");
            return KS_LOGINCARD;
        }
        memcpy(keyb,m_cardSect[i].key,6);

        memcpy(buffer,keya,6);
        memcpy(buffer+6,m_ctrlBit[i].newCtrlBit,4);
        memcpy(buffer+10,keyb,6);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,m_initKeyType,init_keya);
        if(nRet) {
            if(RequestCard(NULL)) {
                SET_ERR("��ʼ��Mifare1����["<<i<<"]��¼ʧ��");
                return KS_LOGINCARD;
            }
            KS_MF_KEYTYPE t = (m_initKeyType == MF_KEYA) ? MF_KEYB : MF_KEYA;
            nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,t,keyb);
            if(nRet) {
                SET_ERR("��ʼ��Mifare1����["<<i<<"],�޷���ʼ���������ѱ�ʹ�ã�");
                return KS_LOGINCARD;
            }
            // ���Ե�¼��Ӧ�����Ѿ�����ʼ��
            continue;
        } else {
            // ��Ҫд��Ǯ������
            for(block=0; block < 3; ++block) {
                // 0 ����
                if(i == 0)
                    continue;
                if(i == m_packageSect) { // Ǯ��
                    if(block==0 || block==1) {
                        memcpy(data_buffer,"\x00\x00\x00\x00\xFF\xFF\xFF\xFF\x00\x00\x00\x00\x00\xFF\x00\xFF",16);
                    } else {
                        memset(data_buffer,0,sizeof data_buffer);
                        memcpy(data_buffer,"\x00\x00\x00\x00\xFF\xFF\xFF\xFF",8);
                    }
                } else {
                    memset(data_buffer,0,sizeof data_buffer);
                }
                if(m_cardinfo.block_info[i].block_crc[block] == MF_CRC8) {
                    data_buffer[15] = CalcCRC8(data_buffer,15);
                }
                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+block,data_buffer);
                if(nRet) {
                    SET_ERR("��ʼ������["<<i<<"]д������ʧ�ܣ�������");
                    return KS_WRITECARD;
                }
            }
            nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
            if(nRet) {
                SET_ERR("��ʼ������["<<i<<"]д��Կʧ�ܣ�������");
                return KS_WRITECARD;
            }
        }
    }
    return 0;
}

int ks_ctcardtype::RestoreFactorySettings() {
    int i,j,nRet;
    byte keyb[6],buffer[16],origin_ctrlbit[4];
    byte init_keya[6],buffer2[16];

    if(this->RequestCard(NULL)) {
        SET_ERR("��ſ�");
        return KS_REQUESTCARD;
    }
    memcpy(init_keya,m_initLoginKey,6);
    m_lastLoginSect = MF_MAX_SECTNO;

    for(i=m_minSectNo; i< m_maxSectNo; ++i) {
        // ������
        if(m_recycleSectMap[i] == '0') continue;
        if(CalcCardKeyB(i,&(m_cardSect[i]))) {
            SET_ERR("��ʼ��Mifare1����������keybʧ��");
            return KS_LOGINCARD;
        }

        memcpy(origin_ctrlbit,m_ctrlBit[i].orignCtrlBit,4);
        memcpy(keyb,m_cardSect[i].key,6);

        memcpy(buffer,init_keya,6);
        memcpy(buffer+6,origin_ctrlbit,4);
        memcpy(buffer+10,init_keya,6);
        /*
        if(i == 8)
        {
        	if(CalcCardKeyA(i,&(m_cardSect[i])))
        	{
        		SET_ERR("��ʼ��Mifare1����������keyaʧ��");
        		return KS_LOGINCARD;
        	}
        	nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,m_cardSect[i].key);
        }
        else
        */
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
        if(nRet) {
            if(RequestCard(NULL)) {
                SET_ERR("��ʼ��Mifare1����["<<i<<"]��¼ʧ��");
                return KS_LOGINCARD;
            }
            nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,init_keya);
            if(nRet) {
                SET_ERR("��ʼ��Mifare1����["<<i<<"],�޷����գ������ѱ�ʹ�ã�");
                return KS_LOGINCARD;
            }
            // ���Ե�¼��Ӧ�����Ѿ�����ʼ��
            continue;
        } else {
            for(j = 0; j<3; ++j) {
                if(i == 0) continue; // 0 ���� 0 �� ����д
                memset(buffer2,0,sizeof buffer2);
                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+j,buffer2);
                if(nRet) {
                    SET_ERR("��ʼ������["<<i<<"]д����ʧ�ܣ�������");
                    return KS_WRITECARD;
                }
            }
            nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
            if(nRet) {
                SET_ERR("��ʼ������["<<i<<"]д��Կʧ�ܣ�������");
                return KS_WRITECARD;
            }
        }
    }
    return 0;
}
int ks_ctcardtype::GetDpsCnt() {
    return KS_NOTSUPPORT;
}

int ks_ctcardtype::GetPayCnt() {
    return KS_NOTSUPPORT;
}

int ks_ctcardtype::checkPackageBuffer(const unsigned char *buffer) {
    int i;
    for(i = 0; i < 4; ++i) {
        if(buffer[i] != ((~buffer[4+i])&0xFF)
                || buffer[i] != buffer[8+i])
            return -1;
    }
    return 0;
}

int ks_ctcardtype::GetBalance(int &balance) {
    int nRet,i;
    int sectno,blockno;
    char szCmd[256];
    byte uResp[256];
    ks_cpu_cmd_t cmd;
    byte buffer1[16] = {0} ,buffer2[16] = {0};
    sectno = this->m_packageSect;
    blockno = sectno * 4;

    if(m_cardSect[sectno].has_read == 0) {
        nRet = this->LoginCardSect(sectno,KEYRIGHT_DEC);
        if(nRet) {
            SET_ERR("��¼Ǯ������ʧ��");
            return KS_LOGINCARD;
        }
        for(i = 0; i < 3; ++i) {
            nRet = MFReadCard(blockno+i,buffer1);
            if(nRet) {
                SET_ERR("��ȡ��Ǯ������");
                return KS_READCARD;
            }
        }
    }
    memcpy(buffer1,m_cardSect[sectno].block_buffer,16);
    memcpy(buffer2,m_cardSect[sectno].block_buffer+16,16);

    if(checkPackageBuffer(buffer1)) {
        // ��鱸Ǯ��
        if(checkPackageBuffer(buffer2)) {
            SET_ERR("��Ǯ������");
            return KS_PURSEERROR;
        }
        // restore
        sprintf(szCmd,"4002050100");
        memset(&cmd,0,sizeof cmd);
        cmd.send_buf = (byte*)szCmd;
        cmd.send_len = strlen(szCmd);
        cmd.recv_buf = uResp;
        cmd.cmd_type = 1;
        nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
        if(nRet) {
            SET_ERR("restore��Ǯ��ʧ��");
            return KS_READCARD;
        }
        // transfer
        sprintf(szCmd,"4002060000");
        memset(&cmd,0,sizeof cmd);
        cmd.send_buf = (byte*)szCmd;
        cmd.send_len = strlen(szCmd);
        cmd.recv_buf = uResp;
        cmd.cmd_type = 1;
        nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
        if(nRet) {
            SET_ERR("transfer��Ǯ��ʧ��");
            return KS_WRITECARD;
        }
        memcpy(buffer1,buffer2,16);
        memcpy(m_cardSect[sectno].block_buffer,m_cardSect[sectno].block_buffer+16,16);
    }
    int bal = 0;
    // ��ȡ�����
    memcpy(&bal,buffer1,4);
    balance = bal;
    return 0;

}
int ks_ctcardtype::GetRandomNum(byte *uRandomNum) {
    return 0;
}
int ks_ctcardtype::CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey) {
    return 0;
}
int ks_ctcardtype::EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen) {
    return 0;
}
int ks_ctcardtype::CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac) {
    return 0;
}
int ks_ctcardtype::CalcSafeMac4Sam(const char *szCmdbuf,char *szMac) {
    return 0;
}
int ks_ctcardtype::CalcSafeMac(const char* szCmdBuf,char *szMac) {
    return 0;
}
int ks_ctcardtype::CalcKeyFromSAM(int keytype,int keyidx,unsigned char *cipherData) {
    int i,ret;
    char szCmd[256];
    ks_cpu_cmd_t cmd;
    unsigned char uResp[256];
    unsigned char uRespLen;

    ret = m_PSAMCardType->ResetPSAM();
    if(ret) {
        return ret;
    }
    // select dir
    //sprintf(szCmd,"00A4000002DF03");
    //ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    ret=m_PSAMCardType->selectADFBySFI("DF03");
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
    }

    // delivery key
    sprintf(szCmd,"801A%02X%02X08%s%02X00",keytype,keyidx,this->strUserCode_,this->ctAppID_);
    ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }

    // cipher data
    memset(szCmd,0,sizeof szCmd);
    sprintf(szCmd,"80FA000008%s",this->m_szCardUID);
    cmd.send_len = strlen(szCmd);

    ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }
    memcpy(cipherData,uResp,8);
    return 0;
}

int ks_ctcardtype::CalcCardKeyA(int sectno,mf_sect_t *sect) {
    int nRet;
    unsigned char startpos = 0;
    int saveKeySect=0,keyIndex=-1;
    mf_sect_t *baseSect;
    if(sectno == 0) {
        memcpy(sect->key,"\xA0\xA1\xA2\xA3\xA4\xA5",6);
        memcpy(sect->newKeyA,sect->key,6);
        sect->key_type = MF_KEYA;
        return 0;
    }
    if(sectno == 1 || sectno == 2 || sectno == 3 || sectno == 4
            || sectno == 6 || sectno == 8 || sectno == 9) {
        // ������Կ
        //nRet = CalcKeyFromSAM(0x28,5,sCipher);
        saveKeySect = 1;
        keyIndex = 5;
    } else if(sectno == 5 || sectno == 7) {
        // ������Կ , ��װ����Կ
        //nRet = CalcKeyFromSAM(0x28,3,sCipher);
        saveKeySect = 5;
        keyIndex = 3;
    }
    baseSect = &(m_cardSect[saveKeySect]);

    if(strcmp(presentCardPhyNo_,m_szCardUID)
            || (baseSect->keyFlag & MF_KEYA) == 0) {
        unsigned char sCipher[16] = {0};
        nRet = 0;

        if(keyIndex > -1) {
            nRet = CalcKeyFromSAM(0x28,keyIndex,sCipher);
        } else {
            // ��������
            memset(sCipher,0xFF,sizeof sCipher);
            nRet = 0;
        }
        if(nRet) {
            SET_ERR("������Կ����");
            return -1;
        }


        memcpy(sCipher+8,sCipher,8);
        startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
        memcpy(baseSect->key,sCipher+startpos,6);
        strcpy(presentCardPhyNo_,m_szCardUID);

        memcpy(baseSect->newKeyA,baseSect->key,6);
        baseSect->keyFlag |= MF_KEYA;
        baseSect->key_type = MF_KEYA;
        CopySectKey(sect,baseSect,MF_KEYA);
    } else {
        CopySectKey(sect,baseSect,MF_KEYA);
        sect->key_type = MF_KEYA;
        //memcpy(sect->key,sect->newKeyA,6);
    }
    return 0;
}
void ks_ctcardtype::CopySectKey(mf_sect_t *dest,const mf_sect_t *src,int t) {

    if(t == MF_KEYA) {
        memcpy(dest->newKeyA,src->newKeyA,sizeof(dest->newKeyA));
        memcpy(dest->key,src->newKeyA,sizeof(dest->key));
    } else {
        memcpy(dest->newKeyB,src->newKeyB,sizeof(dest->newKeyB));
        memcpy(dest->key,src->newKeyB,sizeof(dest->key));
    }
    dest->key_type = src->key_type;
    dest->keyFlag |= t;
}
int ks_ctcardtype::FormatCard() {
    return -1;
}
int ks_ctcardtype::ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) {
    return 0;
}
int ks_ctcardtype::ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes) {
    return 0;
}
int ks_ctcardtype::UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData) {
    return 0;
}
int ks_ctcardtype::calcDepositeKeyFromSvr(unsigned char *sCphier) {
    char sErrMsg[256] = {0};
    char szMac[32]= {0};
    int len,nRet;
    KS_YKT_Clt clt;
    clt.SetIntFieldByName("lsafe_level",0); 	// ��������
    clt.SetStringFieldByName("sstation1",this->m_szCardUID); 	// ������
    clt.SetIntFieldByName("lvol5",2); // ��־
    // ��ֵ��ȡ mac2
    if(!clt.SendRequest(846313,5000)) {
        // TODO : �����ǳ�ʱ
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"������ͨѶ����:%s,������:%d",szMsg,clt.GetReturnCode());
        SET_ERR(errmsg);
        return -1;
    }
    if((nRet = clt.GetReturnCode())!=0) {
        // ��ֵʧ��
        clt.GetReturnMsg(sErrMsg);
        SET_ERR(sErrMsg);
        //DEBUG_LOG(("����ʧ�ܴ�����[%d]������Ϣ[%s]",nRet,transpack->sErrMsg));
        return nRet;
    }
    if(clt.HasMoreRecord()) {
        clt.GetNextPackage();

        //	clt.GetIntFieldByName("lserial1",(int*)&(transpack->nHostSeqno)); // ��̨��ˮ��
        //	clt.GetIntFieldByName("lvol0",&ret_data); // ���׿���
        GET_PACK_STR(clt,"semail",szMac);
    } else {
        //DEBUG_LOG(("��ֵʧ��cardid[%d],ret[%X]",transpack->nCardNo,nRet));
        // ���ص�����������
        SET_ERR("��������������");
        return -1;
    }
    if(strlen(szMac) != 16) {
        SET_ERR("����������Կ����");
        return -1;
    }
    hex2dec(szMac,strlen(szMac),sCphier,len);
    return 0;
}

int ks_ctcardtype::calcDepositeKeyLocal(unsigned char *sCphier) {
    char szData[256] = {0};
    byte uData[256]= {0},uResp[256]= {0},uCardKey[16]= {0};
    int len;
    des3_context des3;
    // 1 ����ɢ
    sprintf(szData,"%s%02X00",this->strUserCode_,this->ctAppID_);
    hex2dec(szData,strlen(szData),uData,len);
    PbocDiverKey(uData,m_CardKeys.DLK1,uCardKey);

    // ����
    strcpy(szData,m_szCardUID);
    len = strlen(szData);
    if(len < 16) {
        strcat(szData,"80");
        do {
            len = strlen(szData);
            if(len < 16) {
                strcat(szData,"00");
                len+=2;
            }
        } while(len == 16);
    }
    hex2dec(szData,strlen(szData),uData,len);
    memset(&des3,0,sizeof des3);
    des3_set_2keys(&des3,uCardKey,uCardKey+8);
    des3_encrypt(&des3,uData,sCphier);
    return 0;
}
int ks_ctcardtype::CalcCardKeyB(int sectno,mf_sect_t *sect) {
    unsigned char sCipher[17] = {0};
    int nRet;
    unsigned int  startpos=0;
    mf_sect_t *baseSect;


    if(sectno == 1) {
        baseSect = &(m_cardSect[1]);
    } else {
        baseSect = &(m_cardSect[2]);
    }

    if(strcmp(m_szCardUID,presentCardPhyNo_)
            || (baseSect->keyFlag & MF_KEYB) == 0) {
        nRet = 0;
        // TODO : calc keyb
        if(sectno == 1) {
            // �����ֵ��Կ
            if(testLoadKey()) {
                // �Ӻ�̨����
                nRet = calcDepositeKeyFromSvr(sCipher);
            } else {
                // ���ؼ���
                nRet = calcDepositeKeyLocal(sCipher);
            }
        } else {
            nRet = CalcKeyFromSAM(0x28,1,sCipher);
        }
        if(nRet) {
            SET_ERR("������Կ����");
            return -1;
        }
        memcpy(sCipher+8,sCipher,8);
        startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
        memcpy(baseSect->key,sCipher+startpos,6);
        baseSect->key_type = MF_KEYB;
        strcpy(presentCardPhyNo_,m_szCardUID);
        memcpy(baseSect->newKeyB,baseSect->key,6);
        baseSect->keyFlag |= MF_KEYB;
        CopySectKey(sect,baseSect,MF_KEYB);
    } else {
        CopySectKey(sect,baseSect,MF_KEYB);
        sect->key_type = MF_KEYB;
    }
    return 0;
}

int ks_ctcardtype::LoginCardSect(int sectno,int kt /*= KEYRIGHT_WRITE*/) {
    int nRet;
    int keytype;
    int keyright;

    if(kt == KEYRIGHT_WRITE) {
        keyright = m_ctrlBit[sectno].writeKey;
    } else if(kt == KEYRIGHT_INC) {
        keyright = m_ctrlBit[sectno].incKey;
    } else if(kt == KEYRIGHT_DEC) {
        keyright = m_ctrlBit[sectno].decKey;
    } else if(kt == KEYRIGHT_READ) {
        keyright = m_ctrlBit[sectno].readKey;
    } else {
        SET_ERR("������Ȩ��");
        return KS_LOGINCARD;
    }

    if((keyright & MF_KEYA) != 0) {
        keytype = MF_KEYA;
    } else if((keyright & MF_KEYB) != 0) {
        keytype = MF_KEYB;
    } else {
        SET_ERR("������Ȩ��");
        return KS_LOGINCARD;
    }

    if(m_lastLoginSect == sectno && m_lastLoginKeyType == keytype)
        return 0;

    m_lastLoginSect = MF_MAX_SECTNO;
    if(keytype == MF_KEYA)
        nRet = CalcCardKeyA(sectno,&(m_cardSect[sectno]));
    else
        nRet = CalcCardKeyB(sectno,&(m_cardSect[sectno]));

    if(nRet) {
        SET_ERR("����M1����Կ����");
        return KS_LOGINCARD;
    }
    nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno
                                ,m_cardSect[sectno].key_type,m_cardSect[sectno].key);
    if(nRet) {
        SET_ERR("��¼Mifare1����"<<sectno<<"ʧ��["<<nRet<<"]");
        m_lastLoginSect	=-1;
        return KS_LOGINCARD;
    }
    m_lastLoginSect = sectno;
    m_lastLoginKeyType = keytype;
    return 0;
}

int ks_ctcardtype::ReadCard() {
    int sectno,nRet,block,i;
    byte crc_num,crc_or;
    byte buffer[16];
    std::map<int,EFBUF>::iterator iter;
    for(iter=m_EFMap.begin(); iter != m_EFMap.end(); ++iter) {
        sectno = iter->first;
        if(sectno == RECORD_SECTNO)
            continue;
        if(!iter->second.ReadFieldSet.size())
            continue;
        if(m_cardSect[sectno].has_read == 0) {
            if((nRet = LoginCardSect(sectno,KEYRIGHT_READ))!=0)
                return nRet;
            // read card
            for(block = 0; block < 4; ++block) {
                memset(buffer,0xFF,sizeof buffer);
                if(m_cardinfo.block_info[sectno].block_used[block] == 1) {
                    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+block,buffer);
                    if(nRet) {
                        SET_ERR("������"<<sectno<<"����ʧ��");
                        return KS_READCARD;
                    }
                    if(m_cardinfo.block_info[sectno].block_crc[block] == MF_BLK_CRC_SUM) {
                        for(i=0,crc_num=0,crc_or=0; i<15; ++i) {
                            crc_num += buffer[i];
                            crc_or |= buffer[i];
                        }
                        if(crc_num != buffer[15] || crc_or == 0) {
                            SET_ERR("��ȡ��������["<<sectno<<"]У�����");
                            return KS_READCARD;
                        }
                    } else if(m_cardinfo.block_info[sectno].block_crc[block] == MF_BLK_CRC_SUM_ALLOW_ZERO) {
                        for(i=0,crc_num=0; i<15; ++i)
                            crc_num += buffer[i];
                        if(crc_num != buffer[15]) {
                            SET_ERR("��ȡ��������["<<sectno<<"]У�����");
                            return KS_READCARD;
                        }
                    } else if(m_cardinfo.block_info[sectno].block_crc[block] == MF_BLK_CRC_OR) {
                        for(i=0,crc_num=0; i<15; ++i)
                            crc_num |= buffer[i];
                        if(crc_num != buffer[15]) {
                            SET_ERR("��ȡ��������["<<sectno<<"]У�����");
                            return KS_READCARD;
                        }
                    } else if(m_cardinfo.block_info[sectno].block_crc[block] == MF_CRC8) {
                        if(CheckCRC8(buffer,15,buffer[15])) {
                            SET_ERR("��ȡ��������["<<sectno<<"]У�����");
                            return KS_READCARD;
                        }
                    }
                }
                memcpy(m_cardSect[sectno].block_buffer+16*block,buffer,16);
            }
            m_cardSect[sectno].has_read = 1;
        }
    }
    return 0;
}
int ks_ctcardtype::WriteCard() {
    int sectno,nRet,blockno,i,offset,len;
    byte buffer[16];
    int block_write_flag[MF_MAX_BLOCK];
    byte real_write_buffer[MF_MAX_BLOCK_SIZE];

    //memset(block_write_flag,0,sizeof block_write_flag);
    memset(real_write_buffer,0,sizeof real_write_buffer);
    std::map<int,EFBUF>::iterator iter;
    for(iter=m_EFMap.begin(); iter != m_EFMap.end(); ++iter) {
        sectno = iter->first;
        // Ǯ�����������Ҫд����
        //if(sectno > 3 && sectno < m_maxSectNo)
        //	continue;
        if(sectno >= 0 && sectno <=4)
            continue;
        if(sectno == RECORD_SECTNO)
            continue;
        EFBUF buf = iter->second;
        if(buf.WriteFieldSet.empty())
            continue;
        if(iter->second.WriteRight == FRW_NULL)
            continue;
        if((nRet=LoginCardSect(sectno)))
            return nRet;
        // ��¼�ɹ���д����Ϣ
        memset(block_write_flag,0,sizeof block_write_flag);
        memset(real_write_buffer,0,sizeof real_write_buffer);
        std::set<int>::iterator iter;
        for(iter = buf.WriteFieldSet.begin(); iter != buf.WriteFieldSet.end(); ++iter) {
            int writefld = *iter;
            offset = m_FieldVect[writefld].offset;
            len = m_FieldVect[writefld].length;
            blockno = 0;
            for(blockno = 0; blockno < MF_MAX_BLOCK; ++blockno) {
                if(ISSET_BLOCK(m_FieldVect[writefld].blockno,blockno))
                    block_write_flag[blockno] = 1;
            }
            for(blockno = 0; blockno < MF_MAX_BLOCK; ++blockno) {
                if(ISSET_BLOCK(m_FieldVect[writefld].blockno,blockno)) {
                    if(m_cardSect[sectno].has_read == 0) {
                        // ��Ҫ�ȶ�ȡ����
                        for(i = 0; i<3; ++i) {
                            memset(buffer,0,sizeof buffer);
                            nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+i,buffer);
                            if(nRet) {
                                SET_ERR("����Mifare1����["<<sectno<<"]ʧ��");
                                return KS_READCARD;
                            }
                            memcpy(m_cardSect[sectno].block_buffer+16*i,buffer,16);
                        }
                        m_cardSect[sectno].has_read = 1;
                        memcpy(real_write_buffer,m_cardSect[sectno].block_buffer,MF_MAX_BLOCK_SIZE);
                    } else {
                        memcpy(real_write_buffer,m_cardSect[sectno].block_buffer,MF_MAX_BLOCK_SIZE);
                        break;
                    }
                }
            }
            //memcpy(real_write_buffer+offset,m_cardSect[sectno].write_buffer+offset,len);
        }
        for(iter = buf.WriteFieldSet.begin(); iter != buf.WriteFieldSet.end(); ++iter) {
            int writefld = *iter;
            offset = m_FieldVect[writefld].offset;
            len = m_FieldVect[writefld].length;
            memcpy(real_write_buffer+offset,m_cardSect[sectno].write_buffer+offset,len);
        }
        memcpy(m_cardSect[sectno].write_buffer,real_write_buffer,16);
        for(blockno=0; blockno<3; ++blockno) {
            if(block_write_flag[blockno] == 1) {
                // д��
                if(m_cardinfo.block_info[sectno].block_crc[blockno] == MF_BLK_CRC_SUM_ALLOW_ZERO
                        || m_cardinfo.block_info[sectno].block_crc[blockno] == MF_BLK_CRC_SUM) {
                    for(i=0,real_write_buffer[16*blockno+15]=0; i<15; ++i) {
                        real_write_buffer[16*blockno+15] += real_write_buffer[16*blockno+i];
                    }
                } else if(m_cardinfo.block_info[sectno].block_crc[blockno] == MF_CRC8) {
                    real_write_buffer[16*blockno+15] = this->CalcCRC8(real_write_buffer+16*blockno,15);
                }
                memcpy(m_cardSect[sectno].block_buffer+16*blockno,real_write_buffer+16*blockno,16);
                memcpy(m_cardSect[sectno].write_buffer+16*blockno,real_write_buffer+16*blockno,16);

                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+blockno,real_write_buffer+16*blockno);
                if(nRet) {
                    SET_ERR("дMifare1����["<<sectno<<"]��["<<blockno<<"]ʧ��");
                    return KS_WRITECARD;
                }
            }
        }
    }
    return 0;
}
int ks_ctcardtype::SetFieldVal(int FieldID,const char *fieldval) {
    int sectno,offset,len,num,data_len,i;
    char temp[64];
    byte buff[256]= {0};
    if(FieldID>CF_END||FieldID<CF_START) {
        SET_ERR("SetFieldVal:�ֶ�����"<<FieldID<<"������");
        return -1;
    }

    std::set<int>::iterator it;
    it=m_EFMap[m_FieldVect[FieldID].fid].WriteFieldSet.find(FieldID);
    if(it==m_EFMap[m_FieldVect[FieldID].fid].WriteFieldSet.end()) {
        SET_ERR("SetFieldVal:�ֶ�����"<<FieldID<<"δ����д");
        return -1;
    }

    sectno = m_FieldVect[FieldID].fid;

    len = m_FieldVect[FieldID].length;
    offset = m_FieldVect[FieldID].offset;
    data_len = strlen(fieldval);
    memset(m_cardSect[sectno].write_buffer+offset,0x00,len);
    memset(buff,0x00,len);
    switch(m_FieldVect[FieldID].type) {
    case FT_ANSI:
        memcpy(buff,fieldval,data_len);
        break;
    case FT_BCD:
        asc2bcd(fieldval,len*2,buff,data_len);
        break;
    case FT_BCD_LAPDZERO:
        if( data_len % 2 == 0)
            num = data_len / 2;
        else
            num = data_len / 2 + 1;
        if(num > len)
            num = len;
        if(num > 0)
            asc2bcd(fieldval,num*2,buff+(len-num),data_len);
        break;
    case FT_BCD_LPAD20:
        if(strlen(fieldval)==12) {
            sprintf(temp,"20%s",fieldval);
        }
        asc2bcd(temp,data_len*2,buff,num);
        break;
    case FT_INT8:
        num = atoi(fieldval);
        buff[0]=num % 256;
        break;
    case FT_INT16:
        num = atoi(fieldval);
        set_2byte_int(buff,num);
        break;
    case FT_INT24:
        num = atoi(fieldval);
        set_3byte_int(buff,num);
        break;
    case FT_INT32:
        num = atoi(fieldval);
        set_4byte_int(buff,num);
        break;
    case FT_LT_INT16:
        num = atoi(fieldval);
        buff[0]= num % 256;
        buff[1] = (num / 256) % 256;
        break;
    case FT_LT_INT24:
        num = atoi(fieldval);
        buff[0] = num % 256;
        buff[1] = (num / 256) % 256;
        buff[2] = (num / 256 / 256) % 256;
        break;
    case FT_LT_INT32:
        num = atoi(fieldval);
        buff[0] = num % 256;
        buff[1] = (num / 256) % 256;
        buff[2] = (num / 256 / 256) % 256;
        buff[3] = (num / 256 / 256) % 256;
        break;
    case FT_HEX_DATE:
        memset(temp,0,sizeof temp);
        if(len == 3) {
            for(i=0; i<3; ++i) {
                memcpy(temp,fieldval+2+i*2,2);
                buff[i] = atoi(temp);
            }
        } else if(len == 4) {
            for(i=0; i<4; ++i) {
                memcpy(temp,fieldval+i*2,2);
                buff[i] = atoi(temp);
            }
        } else {
            SET_ERR("SetFieldVal:�ֶ�����"<<FieldID<<":���ݶ������");
            return -1;
        }
        break;
    case FT_HEX_TIME:
        if(len == 2) {
            for(i=0; i<2; ++i) {
                memcpy(temp,fieldval+i*2,2);
                buff[i] = atoi(temp);
            }
            buff[2] = 0;
        } else if(len == 3) {
            for(i=0; i<3; ++i) {
                memcpy(temp,fieldval+i*2,2);
                buff[i] = atoi(temp);
            }
        } else {
            SET_ERR("SetFieldVal:�ֶ�����"<<FieldID<<":���ݶ������");
            return -1;
        }
        break;
    default:
        SET_ERR("SetFieldVal:�ֶ�����"<<FieldID<<":�������ʹ���");
        return -1;
    }
    memcpy(m_cardSect[sectno].write_buffer+offset,buff,m_FieldVect[FieldID].length);
    SetFieldWriteMode(FieldID);
    return 0;
}
int ks_ctcardtype::GetFieldVal(int FieldID,char *fieldval) {
    int sectno,offset,len,num;
    TRANSINFO info;
    byte temp[10];
    if(FieldID>CF_END||FieldID<CF_START) {
        SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<"������");
        return -1;
    }
    memset(&info,0,sizeof info);

    if(FieldID == CF_SUBSIDYNO) {
        strcpy(fieldval,"0");
        return 0;
    }
    /*
    switch(FieldID)
    {
    case CF_LOCKTERMID:
    	FieldID = CF_TERMID;
    	break;
    case CF_LOCKTRANSDATE:
    	FieldID = CF_TRANSDATE;
    	break;
    case CF_LOCKTRANSTIME:
    	FieldID = CF_TRANSDATE;
    	break;
    default:
    	break;
    }
    */
    std::set<int>::iterator it;
    it=m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.find(FieldID);
    if(it==m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.end()) {
        SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<"δ���ö�");
        return -1;
    }
    // ��ȡ����ˮ
    switch(FieldID) {
    case CF_TRANSDATE:
    case CF_TRANSTIME:
    case CF_TERMID:
    case CF_TRANSAMT:
    case CF_CARDCNT:
    case CF_TRANSTYPE:
    case CF_LOCKTERMID:
    case CF_LOCKTRANSDATE:
    case CF_LOCKTRANSTIME:
        if(this->GetLastRecord()) {
            SET_ERR("��ȡ���һ�����ݴ���");
            return -1;
        }
        sectno = (m_lastRecIdx / 3) + this->m_recordSectBegin;
        len = m_FieldVect[FieldID].length;
        offset = m_FieldVect[FieldID].offset + (m_lastRecIdx % 3 * 16) ;
        break;
    default:
        sectno = m_FieldVect[FieldID].fid;
        len = m_FieldVect[FieldID].length;
        offset = m_FieldVect[FieldID].offset;
        break;
    }


    if(m_cardSect[sectno].has_read == 0) {
        SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<"δ��ȡ");
        fieldval[0]=0;
        return -1;
    }
    if(FieldID == CF_CARDBAL) {
        len = GetBalance(num);
        if(len)
            return len;
        sprintf(fieldval,"%d",num);
        return 0;
    }
    if(FieldID == CF_PAYCNT || FieldID == CF_DPSCNT) {
        len = GetBalance(num);
        if(len)
            return len;
        len = this->MFTransCheck(info,num);
        if(len!=0)
            return len;
        if(FieldID == CF_PAYCNT)
            num = get_2byte_int(info.paycnt);
        else
            num = get_2byte_int(info.dpscnt);
        sprintf(fieldval,"%d",num);
        return 0;
    }

    switch(m_FieldVect[FieldID].type) {
    case FT_ANSI:
        memcpy(fieldval,m_cardSect[sectno].block_buffer+offset,len);
        fieldval[len] = 0;
        break;
    case FT_BCD:
        bcd2asc(m_cardSect[sectno].block_buffer+offset,len,fieldval);
        fieldval[len*2] = 0;
        break;
    case FT_BCD_LPAD20:
        bcd2asc(m_cardSect[sectno].block_buffer+offset,len,fieldval+2);
        fieldval[0] = '2';
        fieldval[1] = '0';
        fieldval[len*2+2] = 0;
        break;
    case FT_BCD_LAPDZERO:
        num = offset;
        while(m_cardSect[sectno].block_buffer[num] == 0x00 && num < (offset+len))  num++;
        len -= (num-offset);
        if(len > 0) {
            bcd2asc(m_cardSect[sectno].block_buffer+num,len,fieldval);
        }
        fieldval[len*2] = 0;
        break;
    case FT_INT8:
        sprintf(fieldval,"%d",m_cardSect[sectno].block_buffer[offset]);
        break;
    case FT_INT16:
        num = get_2byte_int(m_cardSect[sectno].block_buffer+offset);
        sprintf(fieldval,"%d",num);
        break;
    case FT_INT24:
        num = get_3byte_int(m_cardSect[sectno].block_buffer+offset);
        sprintf(fieldval,"%d",num);
        break;
    case FT_INT32:
        num = get_4byte_int(m_cardSect[sectno].block_buffer+offset);
        sprintf(fieldval,"%d",num);
        break;
    case FT_LT_INT16:
        num = m_cardSect[sectno].block_buffer[offset];
        num += m_cardSect[sectno].block_buffer[offset+1] * 256;
        sprintf(fieldval,"%d",num);
        break;
    case FT_LT_INT24:
        num = m_cardSect[sectno].block_buffer[offset];
        num += m_cardSect[sectno].block_buffer[offset+1] * 256;
        num += m_cardSect[sectno].block_buffer[offset+2] * 256*256;
        sprintf(fieldval,"%d",num);
        break;
    case FT_LT_INT32:
        num = m_cardSect[sectno].block_buffer[offset];
        num += m_cardSect[sectno].block_buffer[offset+1] * 256;
        num += m_cardSect[sectno].block_buffer[offset+2] * 256*256;
        num += m_cardSect[sectno].block_buffer[offset+2] * 256*256*256;
        sprintf(fieldval,"%d",num);
        break;
    case FT_HEX_DATE:
        if(len == 3) {
            temp[0] = 20;
            memcpy(temp+1,m_cardSect[sectno].block_buffer+offset,len);
        } else if(len == 4) {
            memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
        } else {
            SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<":���ݶ������");
            return -1;
        }
        sprintf(fieldval,"%02d%02d%02d%02d",temp[0],temp[1],temp[2],temp[3]);
        break;
    case FT_HEX_TIME:
        if(len == 2) {
            memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
            temp[2] = 00;
        } else if(len == 3) {
            memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
        } else {
            SET_ERR("GetFieldVal:�ֶ�����"<<FieldID<<":���ݶ������");
            return -1;
        }
        sprintf(fieldval,"%02d%02d%02d",temp[0],temp[1],temp[2]);
        break;
    }
    if(CF_TRANSDATE == FieldID || CF_LOCKTRANSDATE == FieldID) {
        char datetime[20]= {0};
        GetLastTransDate(fieldval,datetime);
        strcpy(fieldval,datetime);
    }
    return 0;
}
void ks_ctcardtype::GetLastTransDate(const char *day,char *date) {
    int dayval = 0;
    time_t t;
    t = time(NULL);
    struct tm * tx = localtime(&t);

    dayval = atoi(day);
    if(dayval <= tx->tm_mday) {
        sprintf(date,"%04d%02d%02d",tx->tm_year+1900,tx->tm_mon+1,dayval);
    } else {
        if(tx->tm_mon == 0) {
            sprintf(date,"%04d12%02d",tx->tm_year+1900-1,dayval);
        } else {
            sprintf(date,"%04d%02d%02d",tx->tm_year+1900,tx->tm_mon,dayval);
        }
    }
}
char * ks_ctcardtype::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
    return "";
}

void ks_ctcardtype::Money2String(int money,char *str) {
    byte buffer[4];
    memcpy(buffer,&money,4);
    dec2hex(buffer,4,str);
}
void ks_ctcardtype::String2Money(const char *str,int& money) {
    byte buffer[4];
    int l,m;
    hex2dec(str,8,buffer,l);
    memcpy((void*)&m,buffer,4);
    money = m;
}

void ks_ctcardtype::PackDepositInfo(const DEPOSITINFO &info,unsigned char *buffer) {
    int i;
    memset(buffer,0,16);

    memcpy(buffer,&(info.depositBal),4);
    for(i = 0; i < 4; ++i) {
        buffer[4+i] = (~buffer[i]) & 0xFF;
    }
    i = 8;
    memcpy(buffer+i,&(info.totalDepMoney),4);
    i += 4;
    memcpy(buffer+i,&(info.totalDepCnt),3);
    i += 3;
    buffer[15] = CalcCRC8(buffer,15);
}
void ks_ctcardtype::UnpackDepositInfo(const unsigned char *buffer,DEPOSITINFO &info) {
    int i;
    if(CheckCRC8(buffer,15,buffer[15])) {
        return;
    }

    for(i = 0; i < 4; ++i) {
        if(buffer[i] != ((~buffer[4+i])&0xFF))
            return;
    }
    i = 0;
    memcpy(&(info.depositBal),buffer,4);
    i += 8;
    memcpy(&(info.totalDepMoney),buffer+i,4);
    i += 4;
    memcpy(&(info.totalDepCnt),buffer+i,3);

}

int ks_ctcardtype::MFReadCard(int blockno,unsigned char *buffer) {
    int nRet;
    int sectno,b;
    sectno = blockno / 4;
    b = blockno % 4;

    nRet = this->LoginCardSect(sectno,KEYRIGHT_READ);
    if(nRet) {
        SET_ERR("��¼����ʧ��ret["<<nRet<<"]");
        return KS_LOGINCARD;
    }
    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
    if(nRet) {
        SET_ERR("��������ʧ��block["<<blockno<<"]");
        return KS_READCARD;
    }
    memcpy(m_cardSect[sectno].block_buffer+b*16,buffer,16);
    return 0;
}

int ks_ctcardtype::MFWriteCard(int blockno,const unsigned char *buffer) {
    int nRet;
    int sectno,b;
    sectno = blockno / 4;
    b = blockno % 4;
    nRet = this->LoginCardSect(sectno,KEYRIGHT_WRITE);
    if(nRet) {
        SET_ERR("��¼����ʧ��ret["<<nRet<<"]");
        return KS_LOGINCARD;
    }
    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
    if(nRet) {
        SET_ERR("��������ʧ��block["<<blockno<<"]");
        return KS_READCARD;
    }
    memcpy(m_cardSect[sectno].block_buffer+b*16,buffer,16);
    return 0;
}

int ks_ctcardtype::MFTransaction(ST_TRANSPACK *transpack,int transtype) {
    int nRet,sectno;
    char datetime[24] = "",moneyStr[32] = {0};
    char temp[64] = "";
    char termno[9] = {0};
    char szCmd[64] = {0};
    byte uResp[64] = {0}, buffer1[16] = {0};
    ks_cpu_cmd_t cmd;
    DEPOSITINFO deposit;

    sectno = this->m_packageSect;
    if(transtype == TRANS_DEPOSIT)
        nRet = this->LoginCardSect(sectno,KEYRIGHT_INC);
    else
        nRet = this->LoginCardSect(sectno,KEYRIGHT_DEC);
    if(nRet) {
        return nRet;
    }

    // restore ��Ǯ��
    sprintf(szCmd,"4002050000");
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (byte*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.recv_buf = uResp;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("������Ǯ������");
        return KS_WRITEPURSE;
    }
    // transfer ��Ǯ��
    sprintf(szCmd,"4002060100");
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (byte*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.recv_buf = uResp;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("������Ǯ������");
        return KS_WRITEPURSE;
    }
    //
    Money2String(transpack->nTransAmt,moneyStr);
    // modify by tc 2010-11-11 ������ϵͳʱ��
    sprintf(datetime,"%s%s",transpack->sTransDate+6,transpack->sTransTime);
    // ���ݳ�ֵ�����ѷ�ָ��
    //transpack->sTermno
    if(strlen(transpack->sTermno) != 12) {
        memset(termno,'0',sizeof(termno)-1);
    } else {
        strncpy(termno,transpack->sTermno+4,8);
    }
    if(transtype == TRANS_DEPOSIT) {
        // ��ֵ
        sprintf(szCmd,"4002030010%s%s%s%02X010000",moneyStr,datetime,termno,TRANS_DEPOSIT);
    } else {
        // ����
        sprintf(szCmd,"4002040010%s%s%s%02X010000",moneyStr,datetime,termno,TRANS_CONSUME);
    }
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (byte*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.recv_buf = uResp;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("������Ǯ������ret["<<nRet<<"]code["<<cmd.cmd_retcode<<"]");
        return KS_WRITEPURSE;
    }
    // transfer
    memset(datetime,0,sizeof datetime);
    // modify by tc 2010-11-11 , ����ϵͳʱ��
    //GetTransferDatetime(datetime);
    sprintf(temp,"%s%s",transpack->sTransDate,transpack->sTransTime);
    ConvertTransDatetime(temp,datetime);
    sprintf(szCmd,"4002060007%s",datetime);
    memset(&cmd,0,sizeof cmd);
    cmd.send_buf = (byte*)szCmd;
    cmd.send_len = strlen(szCmd);
    cmd.recv_buf = uResp;
    cmd.cmd_type = 1;
    nRet = m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_MFCARD);
    if(nRet) {
        SET_ERR("������Ǯ������ret["<<nRet<<"]code["<<cmd.cmd_retcode<<"]");
        return KS_WRITEPURSE;
    }

    // ����ǳ�ֵ���ף���Ҫ���³�ֵ��������
    if(transtype == TRANS_DEPOSIT) {
        // ���³�ֵ����
        nRet = MFReadCard(sectno*4+2,buffer1);
        if(nRet) {
            SET_ERR("��ȡ��ֵ��Ϣʧ��");
            return KS_READCARD;
        }
        memset(&deposit,0,sizeof deposit);
        UnpackDepositInfo(buffer1,deposit);
        deposit.depositBal = transpack->nTransAmt;
        deposit.totalDepMoney += deposit.depositBal;
        deposit.totalDepCnt++;
        memset(buffer1,0,sizeof buffer1);
        PackDepositInfo(deposit,buffer1);
        nRet = MFWriteCard(sectno*4+2,buffer1);
        if(nRet) {
            SET_ERR("д��ʧ��block["<<sectno*4+2<<"]");
            return nRet;
        }
    }
    m_cardSect[sectno].has_read = 0;
    return 0;
}
int  ks_ctcardtype::AddMoney(ST_TRANSPACK *transpack) {
    int nRet,sectno,cnt;
    TRANSINFO info;
    byte buffer[16];
    sectno = m_packageIdxSect;
    memset(&info,0,sizeof info);
    nRet = this->MFTransProcess(transpack,TRANS_DEPOSIT,info);
    if(nRet)
        return nRet;

    info.transflag = TRANS_END;
    cnt = get_2byte_int(info.dpscnt) + 1;
    set_2byte_int(info.dpscnt,cnt);
    PackTransInfo(info,buffer);
    nRet = MFWriteCard(sectno*4,buffer);
    if(nRet) {
        SET_ERR("д�����ײ���ʧ��");
        return KS_WRITECARD;
    }
    SET_ERR("��ֵ�ɹ�card["<<transpack->nCardNo<<"]money["<<transpack->nTransAmt
            <<"]dpscnt["<<transpack->nDpsCardCnt<<"]["<<transpack->sTransDate<<transpack->sTransTime
            <<"]");
    return 0;
}

int ks_ctcardtype::UnpackTransInfo(const unsigned char *buffer,TRANSINFO &info) {
    memcpy(&info,buffer,16);
    return 0;
}

int ks_ctcardtype::PackTransInfo(const TRANSINFO &info,unsigned char *buffer) {
    memcpy(buffer,&info,16);
    buffer[15] = CalcCRC8(buffer,15);
    return 0;
}
int ks_ctcardtype::MFTransProcess(ST_TRANSPACK *transpack,int transtype,TRANSINFO &info) {
    byte buffer[16];
    int sectno,nRet,balance;
    sectno = m_packageIdxSect;

    nRet = GetBalance(balance);
    if(nRet) {
        SET_ERR("�������ʧ��["<<nRet<<"]");
        return nRet;
    }

    nRet = MFTransCheck(info,balance);
    if(nRet)
        return nRet;
    if(info.transflag == TRANS_END) {
        info.recidx++;
        info.transflag = TRANS_BEGIN;
    } else {
        SET_ERR("�ָ��ϴ�δ��ɽ���balance["<<balance<<"]");
    }
    // ���������ײ���
    if(info.recidx > 8)
        info.recidx = 0;
    PackTransInfo(info,buffer);
    nRet = MFWriteCard(sectno*4,buffer);
    if(nRet) {
        SET_ERR("д�����ײ���ʧ��");
        return KS_WRITECARD;
    }
    // ����
    nRet = MFTransaction(transpack,transtype);
    if(nRet) {
        SET_ERR("д��Ǯ��ʧ��");
        transpack->cGetProveFlag = 1;
        return KS_WRITEPURSE;
    }
    return 0;

}

int ks_ctcardtype::MFTransCheck(TRANSINFO &info,int balance) {
    byte buffer1[16],buffer2[16];
    int sectno,nRet,transerr,cnt;
    sectno = m_packageIdxSect;
    trans_record_t rec;

    if(m_cardSect[sectno].has_read == 0) {
        // ǿ�ƶ���
        this->SetFieldReadMode(CF_DPSCNT);
        nRet = this->ReadCard();
        if(nRet) {
            return nRet;
        }
    }
    memcpy(buffer1,m_cardSect[sectno].block_buffer,16);
    memcpy(buffer2,m_cardSect[sectno].block_buffer+16,16);
    if(CheckCRC8(buffer1,15,buffer1[15])) {
        // ����������
        if(CheckCRC8(buffer2,15,buffer2[15])) {
            SET_ERR("Ǯ��������ʽ����");
            return KS_PURSEERROR;
        }
        memcpy(buffer1,buffer2,16);
        memcpy(m_cardSect[sectno].block_buffer,buffer1,16); //
    }


    memset(&rec,0,sizeof rec);
    memset(&info,0,sizeof(TRANSINFO));
    // ��齻�׽��̱�ʶ
    UnpackTransInfo(buffer1,info);

    transerr = 1;
    // �����ˮ������������ںϷ���Χ�ͷ��ش���
    if(info.transflag == TRANS_BEGIN) {
        // ��鿨���
        nRet = GetTransRecord(info.recidx,rec);
        if(nRet) {
            return KS_PURSEERROR;
        }
        if(rec.transtype == TRANS_DEPOSIT) {
            if(rec.cardbefbal+rec.amount == balance) {
                // ��ʾ�ϴν����ǳɹ���
                transerr = 0;
            }
        } else if(rec.transtype == TRANS_CONSUME || rec.transtype == TRANS_LOCK) {
            if(rec.cardbefbal - rec.amount == balance) {
                // ��ʾ�ϴν����ǳɹ���
                transerr = 0;
            }
        }
        if(!transerr) {
            // �ϴν��׳ɹ�
            if(TRANS_DEPOSIT == rec.transtype) {
                cnt = get_2byte_int(info.dpscnt) + 1;
                set_2byte_int(info.dpscnt,cnt);
            } else {
                cnt = get_2byte_int(info.paycnt) + 1;
                set_2byte_int(info.paycnt,cnt);
            }
        }
    } else {
        transerr = 0;
    }
    //
    if(transerr == 0) {
        PackTransInfo(info,buffer1);
        nRet = MFWriteCard(sectno*4+1,buffer1);
        if(nRet) {
            SET_ERR("���ݽ��ײ���ʧ��");
            return KS_WRITECARD;
        }
        info.transflag = TRANS_END;
    }
    return 0;
}
int  ks_ctcardtype::PayMoney(ST_TRANSPACK *transpack) {
    int nRet,sectno,cnt;
    TRANSINFO info;
    byte buffer[16];
    sectno = m_packageIdxSect;
    memset(&info,0,sizeof info);
    nRet = this->MFTransProcess(transpack,TRANS_CONSUME,info);
    if(nRet)
        return nRet;

    info.transflag = TRANS_END;
    cnt = get_2byte_int(info.paycnt) + 1;
    set_2byte_int(info.paycnt,cnt);
    PackTransInfo(info,buffer);
    nRet = MFWriteCard(sectno*4,buffer);
    if(nRet) {
        SET_ERR("д�����ײ���ʧ��");
        return KS_WRITECARD;
    }
    SET_ERR("�ۿ�ɹ�card["<<transpack->nCardNo<<"]money["<<transpack->nTransAmt
            <<"]paycnt["<<transpack->nPayCardCnt<<"]["<<transpack->sTransDate<<transpack->sTransTime
            <<"]");
    return 0;
}
int ks_ctcardtype::GetTransRecordBuffer(int recordidx,unsigned char *buffer) {
    int sectno,blockno,nRet;
    if(recordidx <0 || recordidx > 8) {
        SET_ERR("��ˮ��������index["<<recordidx<<"]");
        return -1;
    }
    sectno = m_recordSectBegin + (recordidx / 3);
    blockno = recordidx % 3;

    nRet = this->LoginCardSect(sectno);
    if(nRet) {
        SET_ERR("������ˮ����,��¼ʧ��,sect["<<sectno<<"]");
        return KS_LOGINCARD;
    }

    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4 + blockno,buffer);
    if(nRet) {
        SET_ERR("������ˮ����,����ʧ��,sect["<<sectno<<"]");
        return KS_READCARD;
    }
    return 0;
}
int ks_ctcardtype::GetTransRecord(int recordidx,trans_record_t &rec) {
    byte buffer[16];
    int offset;

    if(GetTransRecordBuffer(recordidx,buffer)) {
        return KS_READCARD;
    }
    offset = 0;
    memcpy(rec.transdate,buffer,4);
    offset += 4;
    memcpy((void*)&rec.cardbefbal,buffer+offset,4);
    offset += 4;
    memcpy((void*)&rec.amount,buffer+offset,3);
    offset += 3;
    rec.transtype = buffer[offset++];
    memcpy(rec.deviceid,buffer+offset,4);
    return 0;
}
int ks_ctcardtype::UpdateTransRecord(int recordidx,trans_record_t &rec) {
    return 0;
}
void ks_ctcardtype::GetTransferDatetime(char *datetime) {
    time_t t;
    t = time(NULL);
    struct tm * tx = localtime(&t);
    sprintf(datetime,"%02d%02d%02d%02d%02d%02d%02d",tx->tm_sec,tx->tm_min,tx->tm_hour,
            tx->tm_wday,tx->tm_mday,tx->tm_mon,tx->tm_year+1900-2008);
    return;
}
void ks_ctcardtype::ConvertTransDatetime(const char *sysDatetime,char *transDatetime) {
    char temp[12] = {0};
    memcpy(transDatetime,sysDatetime+12,2); // sec
    memcpy(transDatetime+2,sysDatetime+10,2); // minute
    memcpy(transDatetime+4,sysDatetime+8,2); // hour
    memcpy(transDatetime+6,"00",2); // week day ( not used )
    memcpy(transDatetime+8,sysDatetime+6,2); // day
    memcpy(transDatetime+10,sysDatetime+4,2); // month
    // year
    memset(temp,0,sizeof temp);
    memcpy(temp,sysDatetime,4);
    int year = atoi(temp);
    sprintf(temp,"%02d",year-2008);
    memcpy(transDatetime+12,temp,2);
}
int ks_ctcardtype::GetCurrentDateTime(char *datetime) {
    time_t t;
    t = time(NULL);
    struct tm * tx = localtime(&t);
    sprintf(datetime,"%04d%02d%02d%02d%02d%02d",tx->tm_year+1900,tx->tm_mon+1,tx->tm_mday,
            tx->tm_hour,tx->tm_min,tx->tm_sec);
    return 0;
}
int  ks_ctcardtype::ExtAuth(const char *cardphyid,int keyidx) {
    return -1;
}
int  ks_ctcardtype::Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen) {
    return -1;
}
int  ks_ctcardtype::Adpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen) {
    return -1;
}
int  ks_ctcardtype::VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass) {
    return -1;
}
void ks_ctcardtype::SetMifare1Key(const char *sCipherKey) {
    AuthDLL(sCipherKey,1);
}
int ks_ctcardtype::AuthDLL(const char *key,int flag) {
    byte ucWorkKey[8];
    int len;

    unsigned int  i;
    unsigned long ul;
    char temp[3];
    unsigned char plain[9];
    unsigned char statkey[9];

    hex2dec(key,16,ucWorkKey,len);

    if(flag == 1) {
        memset(temp,0,sizeof(temp));
        memset(plain,0,sizeof(plain));
        memset(statkey,0,sizeof(statkey));
        memcpy(plain,ucWorkKey,8);
        for(i=0; i<8; i++) {
            memcpy(temp,&statickey[2*i],2);
            ul=strtoul(temp,NULL,16);
            statkey[i]=ul;
            plain[i]=~plain[i];
            m_mainkey[i]=plain[i]^statkey[i];
        }
    } else
        memcpy(m_mainkey,ucWorkKey,8);

    SET_ERR("����CTCARDTYPE��Կ");
    m_isLoadKey = 1;
    return 0;
}

int ks_ctcardtype::InitForTrans(ST_TRANSPACK *trans,int trans_type) {
    // TODO : �жϿ����
    //trans->nBefBalance
    //ClearAllFieldAllMode();
    this->SetFieldReadMode(CF_CARDBAL);
    this->SetFieldReadMode(CF_PAYCNT);
    this->SetFieldReadMode(CF_DAYSUMAMT);
    this->SetFieldReadMode(CF_TRANSDATE);
    this->SetFieldReadMode(CF_TRANSTIME);

    //nRet = ReadCard();
    //if(nRet)
    //	return nRet;
    return 0;
}

int ks_ctcardtype::initAllCardDef() {
    int i;

    // 0 ����- Ŀ¼����
    m_cardinfo.block_info[0].block_used[0] = 1;
    m_cardinfo.block_info[0].block_used[1] = 1;
    m_cardinfo.block_info[0].block_used[2] = 1;
    // 1 ���� - Ǯ������
    m_cardinfo.block_info[1].block_used[0] = 1;
    m_cardinfo.block_info[1].block_used[1] = 1;
    m_cardinfo.block_info[1].block_used[2] = 1;
    m_cardinfo.block_info[1].block_crc[2] = MF_CRC8;
    // 2 ���� - ��ˮ���� 1
    m_cardinfo.block_info[2].block_used[0] = 1;
    m_cardinfo.block_info[2].block_used[1] = 1;
    m_cardinfo.block_info[2].block_used[2] = 1;
    // 3 ���� - ��ˮ���� 2
    m_cardinfo.block_info[3].block_used[0] = 1;
    m_cardinfo.block_info[3].block_used[1] = 1;
    m_cardinfo.block_info[3].block_used[2] = 1;
    // 4 ���� - ��ˮ���� 3
    m_cardinfo.block_info[4].block_used[0] = 1;
    m_cardinfo.block_info[4].block_used[1] = 1;
    m_cardinfo.block_info[4].block_used[2] = 1;
    // 5 ���� - ������Ϣ
    m_cardinfo.block_info[5].block_used[0] = 1;
    m_cardinfo.block_info[5].block_used[1] = 1;
    m_cardinfo.block_info[5].block_used[2] = 1;
    // 6 ���� - ���ײ���
    m_cardinfo.block_info[6].block_used[0] = 1;
    m_cardinfo.block_info[6].block_used[1] = 1;
    m_cardinfo.block_info[6].block_crc[1] = MF_CRC8;
    m_cardinfo.block_info[6].block_used[2] = 1;
    // 7 ���� - ������Ϣ2
    m_cardinfo.block_info[7].block_used[0] = 1;
    m_cardinfo.block_info[7].block_used[1] = 1;
    m_cardinfo.block_info[7].block_used[2] = 1;
    // 9 ���� - ��������
    m_cardinfo.block_info[9].block_used[0] = 1;
    m_cardinfo.block_info[9].block_crc[0] = MF_CRC8;
    m_cardinfo.block_info[9].block_used[1] = 1;
    m_cardinfo.block_info[9].block_crc[0] = MF_CRC8;
    m_cardinfo.block_info[9].block_used[2] = 1;


    m_FieldVect.clear();

    EF_FIELD EField;
    memset(&EField,0,sizeof(EField));
    EField.unused=1;
    //�ȳ�ʼ��Ϊ0
    for(int i=0; i<=CF_END; i++)
        m_FieldVect.push_back(EField);

    PERINFO perinfo;
    PUBLICINFO publicinfo;
    PUBLICINFO2 publicinfo2;
    PACKAGEINFO packageinfo;
    TRANSINFO transinfo;
    INDEXINFO indexinfo;
    TRANSDTL TransDtl;

    assert(sizeof(TransDtl) == 16);

    //���з���ʶ
    m_FieldVect[CF_PUBLISHID].unused=1;

    /////////////////////////////////////////////////////////////////
    // 0 section


    //��������
    m_FieldVect[CF_STARTDATE].unused=0;
    m_FieldVect[CF_STARTDATE].offset = indexinfo.startdate - (byte*)&indexinfo;
    m_FieldVect[CF_STARTDATE].length = sizeof(indexinfo.startdate);
    m_FieldVect[CF_STARTDATE].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_STARTDATE].blockno,m_FieldVect[CF_STARTDATE].offset);
    m_FieldVect[CF_STARTDATE].type=FT_BCD;

    /////////////////////////////////////////////
    //  1 section
    //�����
    m_FieldVect[CF_CARDBAL].unused=0;
    m_FieldVect[CF_CARDBAL].offset = packageinfo.balance - (byte*)&packageinfo;
    m_FieldVect[CF_CARDBAL].length = sizeof(packageinfo.balance);
    m_FieldVect[CF_CARDBAL].fid = 1;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDBAL].blockno,m_FieldVect[CF_CARDBAL].offset);
    m_FieldVect[CF_CARDBAL].type=FT_LT_INT32;


    ////////////////////////////////////////////////////////////////////
    ///  5 section
    //ѧ����
    m_FieldVect[CF_STUEMPNO].unused=0;
    m_FieldVect[CF_STUEMPNO].offset = publicinfo.stuempNo - (byte*)&publicinfo;
    m_FieldVect[CF_STUEMPNO].length = sizeof(publicinfo.stuempNo);
    m_FieldVect[CF_STUEMPNO].fid = 5;
    ZERO_BLOCK(m_FieldVect[CF_STUEMPNO].blockno);
    SET_BLOCK(m_FieldVect[CF_STUEMPNO].blockno,0);
    SET_BLOCK(m_FieldVect[CF_STUEMPNO].blockno,1);
    m_FieldVect[CF_STUEMPNO].type=FT_ANSI;

    //����
    m_FieldVect[CF_NAME].unused=0;
    m_FieldVect[CF_NAME].offset = publicinfo.cust_name - (byte*)&publicinfo;
    m_FieldVect[CF_NAME].length = sizeof(publicinfo.cust_name);
    m_FieldVect[CF_NAME].fid = 5;
    EASY_SET_BLOCK(m_FieldVect[CF_NAME].blockno,m_FieldVect[CF_NAME].offset);
    m_FieldVect[CF_NAME].type=FT_ANSI;

    //ְ�����

    //���Ŵ���
    m_FieldVect[CF_DEPTCODE].unused=0;
    m_FieldVect[CF_DEPTCODE].offset = publicinfo.dept_code - (byte*)&publicinfo;
    m_FieldVect[CF_DEPTCODE].length = sizeof(publicinfo.dept_code);
    m_FieldVect[CF_DEPTCODE].fid = 5;
    EASY_SET_BLOCK(m_FieldVect[CF_DEPTCODE].blockno,m_FieldVect[CF_DEPTCODE].offset);
    m_FieldVect[CF_DEPTCODE].type=FT_ANSI;

    // ��ݴ���

    // �Ա�
    m_FieldVect[CF_SEX].unused=0;
    m_FieldVect[CF_SEX].offset = &(publicinfo.sex) - (byte*)&publicinfo;
    m_FieldVect[CF_SEX].length = sizeof(publicinfo.sex);
    m_FieldVect[CF_SEX].fid = 5;
    EASY_SET_BLOCK(m_FieldVect[CF_SEX].blockno,m_FieldVect[CF_SEX].offset);
    m_FieldVect[CF_SEX].type=FT_INT8;

    /////////////////////////////////////////////////
    // 7 section
    // ֤������
    m_FieldVect[CF_IDNO].unused=0;
    m_FieldVect[CF_IDNO].offset = publicinfo2.id_no - (byte*)&publicinfo2;
    m_FieldVect[CF_IDNO].length = sizeof(publicinfo2.id_no);
    m_FieldVect[CF_IDNO].fid = 7;
    EASY_SET_BLOCK(m_FieldVect[CF_IDNO].blockno,m_FieldVect[CF_IDNO].offset);
    m_FieldVect[CF_IDNO].type=FT_ANSI;
    ZERO_BLOCK(m_FieldVect[CF_IDNO].blockno);
    SET_BLOCK(m_FieldVect[CF_IDNO].blockno,0);
    SET_BLOCK(m_FieldVect[CF_IDNO].blockno,1);

    // ֤������
    m_FieldVect[CF_IDTYPE].unused=0;
    m_FieldVect[CF_IDTYPE].offset = &(publicinfo2.id_type) - (byte*)&publicinfo2;
    m_FieldVect[CF_IDTYPE].length = sizeof(publicinfo2.id_type);
    m_FieldVect[CF_IDTYPE].fid = 7;
    EASY_SET_BLOCK(m_FieldVect[CF_IDTYPE].blockno,m_FieldVect[CF_IDTYPE].offset);
    m_FieldVect[CF_IDTYPE].type=FT_ANSI;

    // �����˺�
    m_FieldVect[CF_BANKCARDNO].unused=0;
    m_FieldVect[CF_BANKCARDNO].offset = publicinfo2.bank_card_no - (byte*)&publicinfo2;
    m_FieldVect[CF_BANKCARDNO].length = sizeof(publicinfo2.bank_card_no);
    m_FieldVect[CF_BANKCARDNO].fid = 7;
    EASY_SET_BLOCK(m_FieldVect[CF_BANKCARDNO].blockno,m_FieldVect[CF_BANKCARDNO].offset);
    m_FieldVect[CF_BANKCARDNO].type=FT_BCD_LAPDZERO;

    //�ͻ���
    m_FieldVect[CF_CUSTID].unused=0;
    m_FieldVect[CF_CUSTID].offset = publicinfo2.custid - (byte*)&publicinfo2;
    m_FieldVect[CF_CUSTID].length = sizeof(publicinfo2.custid);
    m_FieldVect[CF_CUSTID].fid = 7;
    EASY_SET_BLOCK(m_FieldVect[CF_CUSTID].blockno,m_FieldVect[CF_CUSTID].offset);
    m_FieldVect[CF_CUSTID].type=FT_INT32;

    //�ͻ����
    m_FieldVect[CF_CUSTTYPE].unused=0;
    m_FieldVect[CF_CUSTTYPE].offset = &(publicinfo2.custtype) - (byte*)&publicinfo2;
    m_FieldVect[CF_CUSTTYPE].length = sizeof(publicinfo2.custid);
    m_FieldVect[CF_CUSTTYPE].fid = 7;
    EASY_SET_BLOCK(m_FieldVect[CF_CUSTTYPE].blockno,m_FieldVect[CF_CUSTTYPE].offset);
    m_FieldVect[CF_CUSTTYPE].type=FT_INT8;

    /////////////////////////////////////////////////////////////////////
    /// 6 section

    // ����
    m_FieldVect[CF_CARDNO].unused=0;
    m_FieldVect[CF_CARDNO].offset = perinfo.card_no-(byte*)&perinfo;
    m_FieldVect[CF_CARDNO].length = sizeof(perinfo.card_no);
    m_FieldVect[CF_CARDNO].fid = 6;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDNO].blockno,m_FieldVect[CF_CARDNO].offset);
    m_FieldVect[CF_CARDNO].type=FT_INT24;

    //�շ����
    m_FieldVect[CF_FEETYPE].unused=0;
    m_FieldVect[CF_FEETYPE].offset = &(perinfo.fee_type) - (byte*)&perinfo;
    m_FieldVect[CF_FEETYPE].length = sizeof(perinfo.fee_type);
    m_FieldVect[CF_FEETYPE].fid = 6;
    EASY_SET_BLOCK(m_FieldVect[CF_FEETYPE].blockno,m_FieldVect[CF_FEETYPE].offset);
    m_FieldVect[CF_FEETYPE].type=FT_INT8;

    //��Ч��
    m_FieldVect[CF_EXPIREDATE].unused=0;
    m_FieldVect[CF_EXPIREDATE].offset = perinfo.expired_date-(byte*)&perinfo;
    m_FieldVect[CF_EXPIREDATE].length = sizeof(perinfo.expired_date);
    m_FieldVect[CF_EXPIREDATE].fid=6;
    EASY_SET_BLOCK(m_FieldVect[CF_EXPIREDATE].blockno,m_FieldVect[CF_EXPIREDATE].offset);
    m_FieldVect[CF_EXPIREDATE].type=FT_HEX_DATE;

    //��ʾ����
    m_FieldVect[CF_SHOWCARDNO].unused=0;
    m_FieldVect[CF_SHOWCARDNO].offset = perinfo.show_card_no-(byte*)&perinfo;
    m_FieldVect[CF_SHOWCARDNO].length = sizeof(perinfo.show_card_no);
    m_FieldVect[CF_SHOWCARDNO].fid=6;
    EASY_SET_BLOCK(m_FieldVect[CF_SHOWCARDNO].blockno,m_FieldVect[CF_SHOWCARDNO].offset);
    m_FieldVect[CF_SHOWCARDNO].type=FT_BCD;

    //������
    m_FieldVect[CF_CARDPWD].unused=0;
    m_FieldVect[CF_CARDPWD].offset = perinfo.pin - (byte*)&perinfo;
    m_FieldVect[CF_CARDPWD].length = sizeof(perinfo.pin);
    m_FieldVect[CF_CARDPWD].fid = 6;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDPWD].blockno,m_FieldVect[CF_CARDPWD].offset);
    m_FieldVect[CF_CARDPWD].type=FT_BCD;

    //�����ۼ�����޶�
    m_FieldVect[CF_SINGLEMAXAMT].unused=0;
    m_FieldVect[CF_SINGLEMAXAMT].offset = perinfo.limit_once - (byte*)&perinfo;
    m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(perinfo.limit_once);
    EASY_SET_BLOCK(m_FieldVect[CF_SINGLEMAXAMT].blockno,m_FieldVect[CF_SINGLEMAXAMT].offset);
    m_FieldVect[CF_SINGLEMAXAMT].fid=6;
    m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT16;
    //���ۼ�����޶�
    m_FieldVect[CF_DAYMAXAMT].unused=0;
    m_FieldVect[CF_DAYMAXAMT].offset = perinfo.limit_day - (byte*)&perinfo;
    m_FieldVect[CF_DAYMAXAMT].length = sizeof(perinfo.limit_day);
    EASY_SET_BLOCK(m_FieldVect[CF_DAYMAXAMT].blockno,m_FieldVect[CF_DAYMAXAMT].offset);
    m_FieldVect[CF_DAYMAXAMT].fid=6;
    m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;

    ////////////////////////////////////////////////////////////////////////
    /// 9 section

    //����ˮָ��
    m_FieldVect[CF_RECORDINDEX].unused=0;
    m_FieldVect[CF_RECORDINDEX].offset = &(transinfo.recidx) - (byte*)&transinfo;
    m_FieldVect[CF_RECORDINDEX].length = sizeof(transinfo.recidx);
    m_FieldVect[CF_RECORDINDEX].fid=9;
    EASY_SET_BLOCK(m_FieldVect[CF_RECORDINDEX].blockno,m_FieldVect[CF_RECORDINDEX].offset);
    m_FieldVect[CF_RECORDINDEX].type=FT_INT8;

    //�����Ѵ���
    m_FieldVect[CF_PAYCNT].unused=0;
    m_FieldVect[CF_PAYCNT].offset = transinfo.paycnt - (byte*)&transinfo;
    m_FieldVect[CF_PAYCNT].length = sizeof(transinfo.paycnt);
    m_FieldVect[CF_PAYCNT].fid=9;
    EASY_SET_BLOCK(m_FieldVect[CF_PAYCNT].blockno,m_FieldVect[CF_PAYCNT].offset);
    m_FieldVect[CF_PAYCNT].type=FT_INT16;

    //���׽��̱�־
    m_FieldVect[CF_TRANSFLAG].unused=0;
    m_FieldVect[CF_TRANSFLAG].offset = &(transinfo.transflag) - (byte*)&transinfo;
    m_FieldVect[CF_TRANSFLAG].length = sizeof(transinfo.transflag);
    m_FieldVect[CF_TRANSFLAG].fid=9;
    EASY_SET_BLOCK(m_FieldVect[CF_TRANSFLAG].blockno,m_FieldVect[CF_TRANSFLAG].offset);
    m_FieldVect[CF_TRANSFLAG].type=FT_INT8;

    //��״̬
    m_FieldVect[CF_CARDSTATUS].unused=0;
    m_FieldVect[CF_CARDSTATUS].offset = &(transinfo.cardstatus) - (byte*)&transinfo;
    m_FieldVect[CF_CARDSTATUS].length = sizeof(transinfo.cardstatus);
    m_FieldVect[CF_CARDSTATUS].fid = 9;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDSTATUS].blockno,m_FieldVect[CF_CARDSTATUS].offset);
    m_FieldVect[CF_CARDSTATUS].type=FT_INT8;

    //�������汾��
    m_FieldVect[CF_CARDVERNO].unused=0;
    m_FieldVect[CF_CARDVERNO].offset = transinfo.blkver - (byte*)&transinfo;
    m_FieldVect[CF_CARDVERNO].length = sizeof(transinfo.blkver);
    m_FieldVect[CF_CARDVERNO].fid = 9;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDVERNO].blockno,m_FieldVect[CF_CARDVERNO].offset);
    m_FieldVect[CF_CARDVERNO].type=FT_BCD;

    //��������ʱ���״���
    m_FieldVect[CF_LOCKCARDCNT].unused=0;
    m_FieldVect[CF_LOCKCARDCNT].offset = transinfo.lockcnt - (byte*)&transinfo;
    m_FieldVect[CF_LOCKCARDCNT].length = sizeof(transinfo.lockcnt);
    m_FieldVect[CF_LOCKCARDCNT].fid=9;
    m_FieldVect[CF_LOCKCARDCNT].type=FT_INT16;

    // ��ֵ����
    m_FieldVect[CF_DPSCNT].unused=0;
    m_FieldVect[CF_DPSCNT].offset = transinfo.dpscnt - (byte*)&transinfo;
    m_FieldVect[CF_DPSCNT].length = sizeof(transinfo.dpscnt);
    m_FieldVect[CF_DPSCNT].fid = 9;
    EASY_SET_BLOCK(m_FieldVect[CF_DPSCNT].blockno,m_FieldVect[CF_DPSCNT].offset);
    m_FieldVect[CF_DPSCNT].type=FT_INT16;

    //���ṹ�汾
    m_FieldVect[CF_CARDSTRUCTVER].unused=1;


    ///////////////////////////////
    // ������ϸ�ļ� SFID = RECORD_SECTNO
    //���׽��(���һ�ν���)
    m_FieldVect[CF_TRANSAMT].unused=0;
    m_FieldVect[CF_TRANSAMT].offset = TransDtl.amount - (byte*)&TransDtl;
    m_FieldVect[CF_TRANSAMT].length = sizeof(TransDtl.amount);
    m_FieldVect[CF_TRANSAMT].fid=RECORD_SECTNO;
    m_FieldVect[CF_TRANSAMT].type=FT_INT24;

    //��������(���һ�ν���)
    m_FieldVect[CF_TRANSTYPE].unused=0;
    m_FieldVect[CF_TRANSTYPE].offset = &(TransDtl.transflag) - (byte*)&TransDtl;
    m_FieldVect[CF_TRANSTYPE].length = sizeof(TransDtl.transflag);
    m_FieldVect[CF_TRANSTYPE].fid=RECORD_SECTNO;
    m_FieldVect[CF_TRANSTYPE].type=FT_INT8;

    //�����ն˻����(���һ�ν���)
    m_FieldVect[CF_TERMID].unused=0;
    m_FieldVect[CF_TERMID].offset = TransDtl.termno - (byte*)&TransDtl;
    m_FieldVect[CF_TERMID].length = sizeof(TransDtl.termno);
    m_FieldVect[CF_TERMID].fid=RECORD_SECTNO;
    m_FieldVect[CF_TERMID].type=FT_BCD;
    //�����ն˻����(��������)
    m_FieldVect[CF_LOCKTERMID].unused=0;
    m_FieldVect[CF_LOCKTERMID].offset = TransDtl.termno - (byte*)&TransDtl;
    m_FieldVect[CF_LOCKTERMID].length = sizeof(TransDtl.termno);
    m_FieldVect[CF_LOCKTERMID].fid=RECORD_SECTNO;
    m_FieldVect[CF_LOCKTERMID].type=FT_BCD;

    //��������(���һ�ν���)
    m_FieldVect[CF_TRANSDATE].unused=0;
    m_FieldVect[CF_TRANSDATE].offset = &TransDtl.transdate - (byte*)&TransDtl;
    m_FieldVect[CF_TRANSDATE].length = sizeof(TransDtl.transdate);
    m_FieldVect[CF_TRANSDATE].fid=RECORD_SECTNO;
    m_FieldVect[CF_TRANSDATE].type=FT_BCD;
    //��������(��������)
    m_FieldVect[CF_LOCKTRANSDATE].unused=0;
    m_FieldVect[CF_LOCKTRANSDATE].offset = &TransDtl.transdate - (byte*)&TransDtl;
    m_FieldVect[CF_LOCKTRANSDATE].length = sizeof(TransDtl.transdate);
    m_FieldVect[CF_LOCKTRANSDATE].fid=RECORD_SECTNO;
    m_FieldVect[CF_LOCKTRANSDATE].type=FT_BCD;

    //����ʱ��(���һ�ν���)
    m_FieldVect[CF_TRANSTIME].unused=0;
    m_FieldVect[CF_TRANSTIME].offset = TransDtl.transtime - (byte*)&TransDtl;
    m_FieldVect[CF_TRANSTIME].length = sizeof(TransDtl.transtime);
    m_FieldVect[CF_TRANSTIME].fid=RECORD_SECTNO;
    m_FieldVect[CF_TRANSTIME].type=FT_BCD;
    //����ʱ��(��������)
    m_FieldVect[CF_LOCKTRANSTIME].unused=0;
    m_FieldVect[CF_LOCKTRANSTIME].offset = TransDtl.transtime - (byte*)&TransDtl;
    m_FieldVect[CF_LOCKTRANSTIME].length = sizeof(TransDtl.transtime);
    m_FieldVect[CF_LOCKTRANSTIME].fid=RECORD_SECTNO;
    m_FieldVect[CF_LOCKTRANSTIME].type=FT_BCD;


    m_EFMap.clear();

    EFBUF efbuf;

    efbuf.FileSize=sizeof(INDEXINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_NULL;
    m_EFMap[0]=efbuf;

    efbuf.FileSize=sizeof(PACKAGEINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[1]=efbuf;

    efbuf.FileSize=sizeof(PUBLICINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[5]=efbuf;

    efbuf.FileSize=sizeof(PERINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[6]=efbuf;

    efbuf.FileSize=sizeof(PUBLICINFO2);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[7]=efbuf;

    efbuf.FileSize=sizeof(TRANSINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[9]=efbuf;


    return 0;
}

int ks_ctcardtype::checkCardType(int ct) {
    switch(ct) {
    case KS_SIMCARD:
        m_CardTypeCode = 0x0504;
        return 0;
    case KS_CPUCARD:
        m_CardTypeCode = 0x0400;
        return 0;
    default:
        return -1;
    }
}

int ks_ctcardtype::GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac) {
    int nRet,balance,cnt;
    TRANSINFO info;

    memset(&info,0,sizeof info);

    cnt = 0;
    nRet = GetBalance(balance);
    if(nRet)
        return nRet;
    nRet = this->MFTransCheck(info,balance);
    if(nRet)
        return nRet;
    if(nTransFlag == 1) {
        cnt = get_2byte_int(info.dpscnt);
    } else if(nTransFlag == 2) {
        cnt = get_2byte_int(info.paycnt);
    }
    if(CardCnt == cnt)
        return 0;
    return KS_WRITEPURSE;
}
int ks_ctcardtype::SelectADF() {
    return 0;
}

int ks_ctcardtype::GetLastRecord() {
    int nRet,balance,sectno,blockno;
    TRANSINFO info;
    unsigned char buffer[16];
    if(m_lastRecIdx > -1)
        return 0;

    nRet = GetBalance(balance);
    if(nRet) {
        SET_ERR("�������ʧ��["<<nRet<<"]");
        return nRet;
    }

    nRet = MFTransCheck(info,balance);
    if(nRet)
        return nRet;
    nRet = this->GetTransRecordBuffer(info.recidx,buffer);
    if(nRet) {
        SET_ERR("������ˮʧ��rec["<<(int)info.recidx<<"]");
        return -1;
    }
    sectno = (info.recidx / 3) + this->m_recordSectBegin;
    blockno = info.recidx % 3;
    m_lastRecIdx = info.recidx;
    memcpy(m_cardSect[sectno].block_buffer + (blockno * 16),buffer,16);
    m_cardSect[sectno].has_read = 1;
    return 0;
}
int ks_ctcardtype::testCardExists(char *szCardPhyID) {
    int nRet;
    unsigned char buffer[16] = {0};
    if(this->m_lastLoginSect >= 0 && this->m_lastLoginSect < MF_MAX_SECTNO) {
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,m_lastLoginSect*4,buffer);
    } else {
        nRet = this->LoginCardSect(0);
    }
    if(nRet)
        return -1;
    strcpy(szCardPhyID,this->m_szCardUID);
    return 0;
}

/////////////////////////////////////////////////////////////////////////

int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_ctcardtype();
    return 0;
}
