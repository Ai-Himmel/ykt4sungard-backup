// ks_cqzy_cardtype.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


#include "ks_cqzy_cardtype.h"
#include "des.h"
#include "global_func.h"
#include "mystring.h"


#define INVALID_KEY_LEN  -1	//长度无效
#define INVALID_DATA_LEN  -2	//长度无效

static unsigned char block_sum(const unsigned char *d,int len) {
    unsigned char sum = 0;
    for(int i=0; i < len; i ++)
        sum += d[i];

    return sum;
}

static int GetCurrentDateTime(char *datetime) {
    time_t t;
    t = time(NULL);
    struct tm * tx = localtime(&t);
    sprintf(datetime,"%04d%02d%02d%02d%02d%02d",tx->tm_year+1900,tx->tm_mon+1,tx->tm_mday,
            tx->tm_hour,tx->tm_min,tx->tm_sec);
    return 0;
}

unsigned char ks_cqzy_cardtype::DACK1[] = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";

ks_cqzy_cardtype::ks_cqzy_cardtype():CCardType() {

    set_cardtype_name("ks_cqzy_cardtype.dll");
    memset(m_mainkey,0,sizeof m_mainkey);
    m_mfcard = &m_cardinfo;
    m_secdPackSect = 0;
    m_is_params_load = 0;

    memset(m_mf_serialno,0,sizeof m_mf_serialno);
    m_lastLoginSect = -1;
}

ks_cqzy_cardtype::~ks_cqzy_cardtype() {
}

int ks_cqzy_cardtype::InitCardTypeDLL() {
    int p;
    char key[32]="";
    if(m_license == NULL)
        return -1;

    if(m_is_params_load)
        return 0;

    if(CCardType::InitCardTypeDLL()) {
        SET_ERR("调用CCardType::InitCardTypeDLL失败");
        return -1;
    }

    m_secdPackSect = 9; // 水控钱包扇区
    if(m_license->get_public_int_param("kscardlib.mfcard.secdpacksect",&m_secdPackSect)) {
        SET_ERR("未设置水控钱包扇区");
        return -1;
    }

    m_is_params_load = 1;
    return 0;
}


static int do_get_szroad_keya(const uint8* mainkey,const uint8 *text,uint8* key) {
    key[0] = mainkey[0]+text[0];
    key[1] = mainkey[1]+text[1];
    key[2] = mainkey[2]|text[2];
    key[3] = mainkey[3]^text[3];
    key[4] = mainkey[4]^text[0] + 0x18;
    key[5] = mainkey[5]&text[3] + 0x40;
    return 0;
}

int ks_cqzy_cardtype::szroad_water_publishcard(ks_water_pack_t *pack) {
    int j=0;
    int nRet = 0;
    int sectno = 0;

    //IS_LOAD_KEY();

    sectno = m_secdPackSect;

    if((nRet = LoginCardSect(sectno))!=0) {
        SET_ERR("登录扇区["<<sectno<<"]失败");
        return nRet;
    }

    byte data_buffer0[16]= {0};

    // 发卡号(流水号), 十六进制表示, 0字节为高位, 1字节为低位,2字节为中位
    int cardno = pack->cardno;

    data_buffer0[0] = (byte)(cardno >> 16); // 卡号
    data_buffer0[1] = (byte)(cardno);
    data_buffer0[2] = (byte)(cardno >> 8);

    data_buffer0[3] = 1; // 卡类

    int custno = pack->custno; // 人员编号
    data_buffer0[10] = (byte)(custno >> 24);
    data_buffer0[11] = (byte)(custno >> 16);
    data_buffer0[12] = (byte)(custno >> 8);
    data_buffer0[13] = (byte)(custno);
    data_buffer0[14] = 0;

    data_buffer0[15] = block_sum(data_buffer0, 15); // 校验和

    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,data_buffer0);
    if(nRet) {
        SET_ERR("第["<<sectno*4<<"]块写卡内容失败");
        return KS_WRITECARD;
    }

    byte data_buffer1[16]= {0};
    data_buffer1[15] = block_sum(data_buffer1, 15); // 校验和

    // 写钱包
    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,data_buffer1);
    if(nRet) {
        SET_ERR("第["<<sectno*4+1<<"]块写卡内容失败");
        return KS_WRITECARD;
    }

    // 写备份块
    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,data_buffer1);
    if(nRet) {
        SET_ERR("第["<<sectno*4+2<<"]块写卡内容失败");
        return KS_WRITECARD;
    }

    return 0;
}
int ks_cqzy_cardtype::szroad_water_recyclecard() {
    int j,nRet;
    int sectno = 0;

    //IS_LOAD_KEY();

    sectno = m_secdPackSect;

    if((nRet = LoginCardSect(sectno))!=0)
        return nRet;

    byte buffer[16] = {0};
    memset(buffer,0,sizeof buffer);
    for(j = 0; j<3; ++j) {
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+j,buffer);
        if(nRet) {
            SET_ERR("初始化扇区["<<sectno<<"]写数据失败，请重试");
            return KS_WRITECARD;
        }
    }

    return 0;
}
int ks_cqzy_cardtype::szroad_water_readmoney(ks_water_pack_t *pack) {
    int nRet = 0;
    int sectno = 0;

    //IS_LOAD_KEY();

    sectno = m_secdPackSect;
    if((nRet = LoginCardSect(sectno))!=0)
        return nRet;

    byte data_buffer1[16]= {0}; // 小钱包

    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+1,data_buffer1);
    if(nRet) {
        SET_ERR("读扇区"<<sectno<<"数据失败");
        return KS_READCARD;
    }

    byte data_crc = block_sum(data_buffer1, 15); // 校验和

    if(data_crc != data_buffer1[15]) {	// 校验和，从备钱包恢复
        data_crc = 0;

        memset(data_buffer1,0,sizeof data_buffer1);
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,data_buffer1);
        if(nRet) {
            SET_ERR("读备份扇区"<<sectno<<"数据失败");
            return KS_READCARD;
        }

        data_crc = block_sum(data_buffer1, 15); // 校验和

        if(data_crc != data_buffer1[15] )		// 备份块也有问题
            return KS_PURSECRCERR;

        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4 + 1,data_buffer1);
        if(nRet) {
            SET_ERR("写扇区"<<sectno<<"数据失败");
            return KS_WRITECARD;
        }
    }
    // 金额
    pack->money = (data_buffer1[2] << 16) + (data_buffer1[1] << 8) + data_buffer1[0];

    // 上次充值时间
    char datetime[20]= {0};
    bcd2asc(&data_buffer1[6], 6, datetime);

    sprintf(pack->addtime,"20%s",datetime);

    // 充值次数（大端）
    pack->addcount = (data_buffer1[12] << 8)+data_buffer1[13];

    return 0;
}
int ks_cqzy_cardtype::szroad_water_writemoney(ks_water_pack_t *pack) {
    //IS_LOAD_KEY();

    int nRet = 0;
    int sectno = m_secdPackSect;
    if((nRet = LoginCardSect(sectno))!=0)
        return nRet;

    byte data_buffer1[16]= {0}; // 小钱包

    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4 + 1,data_buffer1);
    if(nRet) {
        SET_ERR("读扇区"<<sectno<<"数据失败");
        return KS_READCARD;
    }

    byte data_crc = block_sum(data_buffer1, 15); // 校验和

    if(data_crc != data_buffer1[15] ) {	// 主钱包校验和不对或数据全为0，校验备份钱包，以免读钱包有问题
        data_crc = 0;
        memset(data_buffer1,0,sizeof data_buffer1);
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,data_buffer1);
        if(nRet) {
            SET_ERR("读扇区"<<sectno<<"数据失败");
            return KS_READCARD;
        }

        data_crc = block_sum(data_buffer1, 15); // 校验和

        if(data_crc != data_buffer1[15] )		// 备份块也有问题
            return KS_PURSECRCERR;
    }

    // 余额(小端)
    int money = pack->money;

    data_buffer1[0] = (byte)(money);
    data_buffer1[1] = (byte)(money >> 8);
    data_buffer1[2] = (byte)(money >> 16);

    // 上次消费额

    // 上次充值时间
    char datetime[20]= {0};
    int ucBCDlen = 0;
    GetCurrentDateTime(datetime);
    asc2bcd(&datetime[2], 12, &data_buffer1[6], ucBCDlen);

    // 充值次数（大端）
    int cnt = (data_buffer1[12] << 8)+data_buffer1[13] + 1;
    data_buffer1[12] = (byte)(cnt >> 8);
    data_buffer1[13] = (byte)cnt;

    data_buffer1[15] = block_sum(data_buffer1, 15); // 校验和

    int nRet1 = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,data_buffer1);
    int nRet2 = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,data_buffer1);

    if(nRet1 || nRet2) {
        SET_ERR("写扇区"<<sectno<<"数据失败");
        return KS_WRITECARD;
    }

    return 0;
}


int ks_cqzy_cardtype::encrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result) {
    des_context ctx;
    if(keylen != 8)
        return INVALID_KEY_LEN;
    if(datalen != 8)
        return INVALID_DATA_LEN;

    memset(&ctx,0,sizeof ctx);
    des_set_key(&ctx,key);
    des_encrypt(&ctx,data,Des_result);
    return 0;

}
int ks_cqzy_cardtype::dencrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result) {
    des_context ctx;
    if(keylen != 8)
        return INVALID_KEY_LEN;
    if(datalen != 8)
        return INVALID_DATA_LEN;
    memset(&ctx,0,sizeof ctx);
    des_set_key(&ctx,key);
    des_decrypt(&ctx,data,Des_result);
    return 0;

}
int ks_cqzy_cardtype::encrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result) {
    unsigned char szkey[9];
    unsigned char szplain[9];
    unsigned char szcipher[9];
    if(keylen != 16)
        return INVALID_KEY_LEN;
    if(datalen != 8)
        return INVALID_DATA_LEN;


    memset(szkey,0,sizeof(szkey));
    memset(szplain,0,sizeof(szplain));
    memset(szcipher,0,sizeof(szcipher));

    memcpy(szkey,key,8);
    memcpy(szplain,data,8);

    encrypt_des(szkey,8,szplain,8,szcipher);

    memcpy(szkey,key+8,8);
    dencrypt_des(szkey,8,szcipher,8,szplain);

    memcpy(szkey,key,8);
    encrypt_des(szkey,8,szplain,8,szcipher);

    memcpy(Des_result,szcipher,8);
    return 0;

}

int ks_cqzy_cardtype::CalcCardKeyA(int sectno,unsigned char *key) {
    // 将KeyA 设置成 凯路算法 计算的KeyA
    static byte szroad_mainkey[6];
    szroad_mainkey[0] = 0xe5;
    szroad_mainkey[1] = 0x66;
    szroad_mainkey[2] = 0x3b;
    szroad_mainkey[3] = 0x7e;
    szroad_mainkey[4] = 0xf6;
    szroad_mainkey[5] = 0xda;

    // 凯路水控钱包密钥A
    do_get_szroad_keya(szroad_mainkey, m_mf_serialno, key);

    return 0;
}

int ks_cqzy_cardtype::gen_user_card_keyB(unsigned char *key,unsigned char *text,unsigned char *keyB) {
    unsigned int  i;
    unsigned char sPlain[9];
    unsigned char sCipher[17];
    unsigned int  startpos=0;
    unsigned char sKey[17];

    memset(sPlain,0,sizeof(sPlain));
    memset(sCipher,0,sizeof(sCipher));
    memset(sKey,0,sizeof(sKey));
    for(i=0; i<4; i++) {
        sPlain[i]=~text[i];
        sPlain[i+4]=text[i];
    }
    for(i=0; i<8; i++) {
        sKey[i]=key[i];
        sKey[i+8]=~key[i];
    }
    encrypt_3des(sKey,16,sPlain,8,sCipher);
    memcpy(sCipher+8,sCipher,8);
    startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
    memcpy(keyB,sCipher+startpos,6);
    return 0;

}

int ks_cqzy_cardtype::CalcCardKeyB(int sectno,unsigned char *key) {
    if(m_CardKeys.bLoad != 1) {
        SET_ERR("读卡器未授权");
        return -1;
    }
    memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
    gen_user_card_keyB(m_mainkey,(unsigned char*)m_mf_serialno,key);
    return 0;
}

int ks_cqzy_cardtype::doInitUserCard(const char *sShowCardNo) {
    int i,block,nRet;
    byte keya[6],keyb[6],buffer[16],ctrlbit[4];
    byte init_keya[6],data_buffer[16];
    char datetime[20]="";
    char temp[10] = "";

    if(m_CardKeys.bLoad !=1) {
        SET_ERR("Mifare1密钥未装载");
        return KS_UNAUTH_TERM;
    }
    memcpy(init_keya,"\xFF\xFF\xFF\xFF\xFF\xFF",6);
    memcpy(ctrlbit,"\x7F\x07\x88\x00",4);
    if(CalcCardKeyB(0,keyb)) {
        return KS_LOGINCARD;
    }

    if(CalcCardKeyA(m_secdPackSect,keya)) {
        SET_ERR("计算扇区["<<i<<"]密钥失败");
        return KS_LOGINCARD;
    }

    memcpy(buffer,keya,6);
    memcpy(buffer+6,ctrlbit,4);
    memcpy(buffer+10,keyb,6);

    nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,m_secdPackSect,MF_KEYA,init_keya);
    if(nRet) {
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,m_secdPackSect,MF_KEYB,keya);
        if(nRet) {
            SET_ERR("初始化Mifare1扇区["<<m_secdPackSect<<"],无法初始化，可能已被使用！");
            return KS_LOGINCARD;
        }
    }

    // 初始化
    for(block=0; block < 3; ++block) {
        memset(data_buffer,0, sizeof data_buffer);
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,m_secdPackSect*4+block,data_buffer);
        if(nRet) {
            SET_ERR("初始化扇区["<<i<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }
    }

    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,m_secdPackSect*4+3,buffer);
    if(nRet) {
        SET_ERR("初始化扇区["<<i<<"]写密钥失败，请重试");
        return KS_WRITECARD;
    }

    m_lastLoginSect = m_secdPackSect;
    return 0;

}
int ks_cqzy_cardtype::doRequestMFCard(char *szPhyno) {
    int nRet,i;
    char phyno[32] = {0};
    unsigned char decphy[10]= {0};
    nRet = m_Reader->request_card(m_ReaderPara,phyno,KS_MFCARD);
    if(nRet) {
        SET_ERR("连接M1卡失败");
        return nRet;
    }
    if(szPhyno)
        strcpy(szPhyno,phyno);
    hex2dec(phyno,8,decphy,nRet);
    for(i = 0; i < 4; ++i)
        this->m_mf_serialno[i] = decphy[3-i];
    return 0;
}
int ks_cqzy_cardtype::initCPUCard(const char *sShowCardNo) {
    int nRet=0;
    int iLen=0;
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

    int ret=0;
    vector<string> CmdVector;
    string sTmp;
    string sCmd;
    char sHexStr[64];
    byte rlen=0;
    unsigned char ucRespData[256];
    unsigned char ucRespLen=0;
    unsigned char ucShowCardNo[11];
    if(NULL!=sShowCardNo && strlen(sShowCardNo)>10) {
        SET_ERR("显示卡号["<<sShowCardNo<<"长度错误");
        return -1;
    }
    memset(ucShowCardNo,0,sizeof(ucShowCardNo));

    if(NULL!=sShowCardNo && strlen(sShowCardNo)>0) {
        strcpy((char*)ucShowCardNo,sShowCardNo);
    }

    CARDKEYS  LocalCardKeys;
    memset(&LocalCardKeys,0,sizeof(LocalCardKeys));

    PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,LocalCardKeys.DPK1);			//消费1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,LocalCardKeys.DPK2);			//消费2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,LocalCardKeys.DLK1);			//圈存1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DLK2,LocalCardKeys.DLK2);			//圈存2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,LocalCardKeys.DTAC);			//内部密钥TAC
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK,LocalCardKeys.DACK);			//应用主控密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DUK,LocalCardKeys.DUK);				//PIN解锁
    PbocDiverKey(ucCardPhyID,m_CardKeys.DRPK,LocalCardKeys.DRPK);			//PIN重装
    PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,LocalCardKeys.DAMK);			//维护密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,LocalCardKeys.DACK1);			//外部认证1
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK2,LocalCardKeys.DACK2);			//外部认证2
    PbocDiverKey(ucCardPhyID,m_CardKeys.DACK3,LocalCardKeys.DACK3);			//外部认证3
    PbocDiverKey(ucCardPhyID,m_CardKeys.LDACK,LocalCardKeys.LDACK);			//小钱包外部认证密钥
    PbocDiverKey(ucCardPhyID,m_CardKeys.LDAMK,LocalCardKeys.LDAMK);			//小钱包维护密钥
    //取随机数`
    memset(ucRespData,0,sizeof(ucRespData));
    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    cmd.recv_buf=ucRespData;
    unsigned char ucSendData[256]= {0};
    unsigned char ucCCK[17]= {0};
    memset(ucCCK, 0xFF,sizeof ucCCK);
    nRet=ExecExtAuthCmd(ucCCK);
    if(nRet) {
        if(0x6A88!=nRet) {
            if(0x63 == nRet>>8) {
                int iLen=0;
                hex2dec(szHexKSCCK,32,ucCCK,iLen);
                nRet=ExecExtAuthCmd(ucCCK);
                if(nRet) {
                    return nRet;
                } else {
                    SET_ERR("该卡已使用,如需重新发行请先回收该卡");
                    return -1;
                }
            }
            return nRet;
        }
    }
    //删除MF下的目录及文件
    sCmd="800E000000";
    cmd.send_buf=(byte*)sCmd.c_str();
    cmd.send_len=sCmd.size();
    cmd.cmd_type=1;//16进制
    nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
    if(nRet) {
        if(cmd.cmd_retcode) {
            SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
            return cmd.cmd_retcode;
        } else {
            SET_ERR(m_Reader->GetErrMsg(NULL));
            return nRet;
        }
    }
    //DIR文件
    sCmd="00A4000000";
    CmdVector.push_back(sCmd);
    //创建密钥文件
    sCmd="80E00000073F004001AAFFFF";
    CmdVector.push_back(sCmd);
    //写入根主控密钥
    sCmd = "80D401001539F0AAAAAA";		//十次重试机会
    sCmd += szHexKSCCK;
    CmdVector.push_back(sCmd);

    //目录数据文件 EF01
//	sCmd="80E0000107AA0310F0F0FFFF";
//	CmdVector.push_back(sCmd);
    //建DF02
    sCmd="80E0DF021838009DF0AA957FFFD15600000145415359454E5452590000";
    CmdVector.push_back(sCmd);
    //建DF03
    sCmd="80E0DF03173811C8F0AA957FFFD156000001BDF0CACBB4EFD6A7B8B6";
    CmdVector.push_back(sCmd);
    //建DF04
    sCmd="80E0DF0418380330F0AA957FFFD156000001BDF0CACBB4EFC7AEB0FC32";
    CmdVector.push_back(sCmd);
    //选择DF02
    sCmd="00A4040010D15600000145415359454E5452590000";
    CmdVector.push_back(sCmd);
    sCmd="80E00000073F004001AAFFFF";
    CmdVector.push_back(sCmd);
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DACK,16,sHexStr);
    sCmd="80D401001539F0AAAA66 ";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);

    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DAMK,16,sHexStr);
    sCmd="80D401001536F0AAFF33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);

    //EF15
    sCmd="80E0001507A8003CF0F0FFFE";
    CmdVector.push_back(sCmd);
    //选择DF03
    sCmd="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
    CmdVector.push_back(sCmd);
    //创建密钥文件
    sCmd="80E00000073F013001FFFFFF";//需要最高权限FF才能修改
    CmdVector.push_back(sCmd);
    //写入外部认证密钥ACK
#if 1 // 兼容云交职老卡结构版本
    sCmd="80D401001539F0FF2233"; //FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF";
    dec2hex(DACK1,16,sHexStr);
    sCmd+=sHexStr;
#else
    /*
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DACK,16,sHexStr);
    sCmd="80D401001539F0FFFF33";
    sCmd+=sHexStr;
    */
#endif
    CmdVector.push_back(sCmd);
    //////////////////////////////////////////////////////////////////////
    //写入消费密钥1
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DPK1,16,sHexStr);
    sCmd="80D40101153EF00C0100";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入消费密钥2
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DPK2,16,sHexStr);
    sCmd="80D40102153EF00D0100";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入消费密钥3
    //memset(sHexStr,0,sizeof(sHexStr));
    //dec2hex(g_MainKey.DPK3,16,sHexStr);
    //sCmd="80D40103153EF0020100";
    //sCmd+=sHexStr;
    //CmdVector.push_back(sCmd);
    //写入圈存密钥1
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DLK1,16,sHexStr);
    sCmd="80D40101153FF00E0200";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入圈存密钥2
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DLK2,16,sHexStr);
    sCmd="80D40102153FF00F0200";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入内部认证密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DTAC,16,sHexStr);
    sCmd="80D401001534F00E0300";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入解锁口令密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DUK,16,sHexStr);
    sCmd="80D401001537F00EFF33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入PIN重装密钥密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DRPK,16,sHexStr);
    sCmd="80D401011538F00EFF33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入外部认证密钥1
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DACK1,16,sHexStr);
    sCmd="80D401011539F00E2233";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入外部认证密钥2
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DACK2,16,sHexStr);
    sCmd="80D401021539F00EBB33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入外部认证密钥3
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DACK3,16,sHexStr);
    sCmd="80D401031539F00ECC33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入应用维护密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DAMK,16,sHexStr);
    sCmd="80D401011536F00BFF33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入口令
    sCmd="80D40100083AF0EF1133000000";
    CmdVector.push_back(sCmd);
    //公共应用基本文件 0015
    sCmd="80E0001507A80038F0F0FFFE";
    CmdVector.push_back(sCmd);
    //写入显示卡号
    CmdVector.push_back("SHOWCARDNO");
    //持卡人基本文件 0016
    sCmd="80E0001607A80070F0F0FFFE";
    CmdVector.push_back(sCmd);
    //交易规则文件 0012
    sCmd="80E0001207A80040F0F0FFFE";//长度0x40
    CmdVector.push_back(sCmd);
    //18交易明细
    sCmd="80E00018072E3217F0FFFFFF";
    CmdVector.push_back(sCmd);
    //钱包
    sCmd="80E0EF02072F0208F0F0FF18";
    CmdVector.push_back(sCmd);
    //补助明细文件
    //sCmd="80E0000207AE0A28F0F0FFFE";
    //CmdVector.push_back(sCmd);
    //电子钱包消费文件
    sCmd="80E0000107AE3228F0F0FFFE";
    CmdVector.push_back(sCmd);
    //密码文件, 安全状态为 F2 ， 必须大于等于 2
    sCmd="80E0001907A80010F2F0FF0A";
    CmdVector.push_back(sCmd);

    //;DF04
    sCmd="00A4040010D156000001BDF0CACBB4EFC7AEB0FC32";
    CmdVector.push_back(sCmd);

    sCmd="80E00000073F00D801AAFFFF";
    CmdVector.push_back(sCmd);
    //主控密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.DACK,16,sHexStr);
    sCmd="80D401001539F0AAAA66";
    sCmd +=sHexStr;
    CmdVector.push_back(sCmd);
    //小钱包文件
    sCmd="80E0 0001 07 A80007F4F0FF0A";
    CmdVector.push_back(sCmd);
    //写入小钱包外部认证密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.LDACK,16,sHexStr);
    sCmd="80D401011539F0024433";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);
    //写入小钱包应用维护密钥
    memset(sHexStr,0,sizeof(sHexStr));
    dec2hex(LocalCardKeys.LDAMK,16,sHexStr);
    sCmd="80D401011536F00AFF33";
    sCmd+=sHexStr;
    CmdVector.push_back(sCmd);

    for(int i=0; i<CmdVector.size(); i++) {
        string& sSendData=CmdVector[i];
        if(sSendData=="SHOWCARDNO") {
            char szMac[9]= {0};
            //计算MAC
            memset(sHexStr,0,sizeof(sHexStr));
            dec2hex(ucShowCardNo,10,sHexStr);		//数据库
            sSendData="04D6950A";
            sSendData+=ltohex(14);	//数据+4字节MAC
            sSendData+=sHexStr;
            ret=CalcSafeMac4Sam(sSendData.c_str(),szMac);
            if(ret) {
                return ret;
            }
            sSendData+=szMac;
        }

        string_replace(sSendData," ","");
        string_replace(sSendData,"\t","");
        cmd.send_buf=(byte*)sSendData.c_str();
        cmd.send_len=sSendData.size();
        cmd.cmd_type=1;//16进制
        nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
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
    nRet = this->selectADFBySFI("3F00",1);
    return nRet;
}
int ks_cqzy_cardtype::InitUserCard(const char *sShowCardNo) {
    int nRet;
    nRet = initCPUCard(sShowCardNo);
    if(nRet)
        return nRet;

    nRet = doRequestMFCard(NULL);
    if(nRet)
        return nRet;

    nRet=doInitUserCard(sShowCardNo);
    if(nRet) {
        SET_ERR("初始化M1扇区失败,ret["<<nRet<<"]");
    }
    return nRet;
}
int ks_cqzy_cardtype::doRestoreUsetCard() {

    int block,nRet;
    byte keya[6],keyb[6],buffer[16],ctrlbit[4];
    byte data_buffer[16];
    char datetime[20]="";
    char temp[10] = "";

    if(m_CardKeys.bLoad !=1) {
        SET_ERR("Mifare1密钥未装载");
        return KS_UNAUTH_TERM;
    }
    memcpy(ctrlbit,"\xFF\x07\x80\x69",4);

    if(CalcCardKeyB(0,keyb)) {
        return KS_LOGINCARD;
    }
    memcpy(keya,"\xFF\xFF\xFF\xFF\xFF\xFF",6);

    m_lastLoginSect = -1;

    memset(buffer,0xFF,16);
    memcpy(buffer+6,ctrlbit,4);

    nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,m_secdPackSect,MF_KEYB,keyb);
    if(nRet) {
        if(doRequestMFCard(NULL)) {
            SET_ERR("回收Mifare1扇区["<<m_secdPackSect<<"]登录失败");
            return KS_LOGINCARD;
        }
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,m_secdPackSect,MF_KEYA,keya);
        if(nRet) {
            SET_ERR("回收Mifare1扇区["<<m_secdPackSect<<"],无法回收，可能已被使用！");
            return KS_LOGINCARD;
        }
    }

    for(block=0; block < 3; ++block) {
        memset(data_buffer,0, sizeof data_buffer);
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,m_secdPackSect*4+block,data_buffer);
        if(nRet) {
            SET_ERR("回收扇区["<<m_secdPackSect<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }
    }

    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,m_secdPackSect*4+3,buffer);
    if(nRet) {
        SET_ERR("回收扇区["<<m_secdPackSect<<"]写密钥失败，请重试");
        return KS_WRITECARD;
    }

    return 0;
}
int ks_cqzy_cardtype::RestoreFactorySettings() {
    int nRet;
    nRet = CCardType::RestoreFactorySettings();
    if(nRet)
        return nRet;
    nRet = doRequestMFCard(NULL);
    if(nRet)
        return nRet;

    nRet = doRestoreUsetCard();
    if(nRet) {
        SET_ERR("回收M1部分失败,nRet["<<nRet<<"]");
    }
    return nRet;
}


int	 ks_cqzy_cardtype::AuthDLL(const char *key,int flag) {
    return 0;
}

int ks_cqzy_cardtype::LoginCardSect(int sectno) {
    byte key[6];
    int nRet;
    //if(sectno == m_lastLoginSect)
    //return 0;
    // TODO: login card
    nRet = this->CalcCardKeyA(sectno,key);
    if(nRet) {
        SET_ERR("登录扇区["<<sectno<<"]计算key失败");
        return -1;
    }
    nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,key);
    if(nRet) {
        SET_ERR("登录扇区["<<sectno<<"]失败");
        return -1;
    }
    return 0;
}

int ks_cqzy_cardtype::water_publishcard(int watertype,ks_water_pack_t *pack) {
    if(this->doRequestMFCard(NULL)) {
        return KS_REQUESTCARD;
    }
    switch(watertype) {
    case KS_SZROAD_WATER:
        return szroad_water_publishcard(pack);
    default:
        return KS_NOTSUPPORT;
    }
}
int ks_cqzy_cardtype::water_recyclecard(int watertype) {
    if(this->doRequestMFCard(NULL)) {
        return KS_REQUESTCARD;
    }
    switch(watertype) {
    case KS_SZROAD_WATER:
        return szroad_water_recyclecard();
    default:
        return KS_NOTSUPPORT;
    }
}
int ks_cqzy_cardtype::water_readmoney(int watertype,ks_water_pack_t *pack) {
    memset(pack, 0, sizeof(ks_water_pack_t));

    if(this->doRequestMFCard(NULL)) {
        return KS_REQUESTCARD;
    }
    switch(watertype) {
    case KS_SZROAD_WATER:
        return szroad_water_readmoney(pack);
    default:
        return KS_NOTSUPPORT;
    }
}
int ks_cqzy_cardtype::water_writemoney(int watertype,ks_water_pack_t *pack) {
    if(this->doRequestMFCard(NULL)) {
        return KS_REQUESTCARD;
    }
    switch(watertype) {
    case KS_SZROAD_WATER:
        return szroad_water_writemoney(pack);
    default:
        return KS_NOTSUPPORT;
    }
}
int ks_cqzy_cardtype::water_publishparamcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}
int ks_cqzy_cardtype::water_recycleparamcard(int watertype) {
    return KS_NOTSUPPORT;
}

int ks_cqzy_cardtype::water_read_paramcard(int watertype,ks_water_param_t *param) {
    return KS_NOTSUPPORT;
}

int ks_cqzy_cardtype::checkCardType(int ct) {
    switch(ct) {
    case KS_CPUCARD:
    case KS_FIXCARD:
        m_CardTypeCode = 0x0104;
        return 0;
    case KS_MFCARD:
        m_CardTypeCode = 0x0200;
        return 0;
    default:
        return -1;
    }
}
int ks_cqzy_cardtype::ExtAuth(const char *cardphyid,int keyidx) {
    string sCmd;
    unsigned char ucRespData[512]= {0};
    unsigned char ucRandom[9]= {0};
    unsigned char sRandomHex[17]= {0};
    char encrypt_random[24] = {0};
    int nRet;
    des3_context ctx;

    nRet=GetRandomNum(ucRandom);
    if(nRet)
        return nRet;

    ks_cpu_cmd_t cmd;
    memset(&cmd,0,sizeof(cmd));
    cmd.recv_buf=ucRespData;

    // 云交职卡外部认证密钥为 FF
    memset(&ctx,0,sizeof ctx);
    des3_set_2keys(&ctx,DACK1,DACK1+8);
    des3_encrypt(&ctx,ucRandom,sRandomHex);
    dec2hex(sRandomHex,8,encrypt_random);

    ///
    sCmd = "0082000008";
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
//////////////////////////////////////////////////////////////////////////

int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_cqzy_cardtype();
    return 0;
}
