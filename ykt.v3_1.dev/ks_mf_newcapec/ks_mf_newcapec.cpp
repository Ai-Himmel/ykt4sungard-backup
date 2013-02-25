#include "Windows.h"
#include "ks_mf_newcapec.h"
#include "global_func.h"
#include "des.h"
#include <time.h>
#include <fstream>
#include "yktclt.h"
#include "math.h"

unsigned char const CRC8Table[256] = {
    0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
    0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
    0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
    0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
    0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
    0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
    0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
    0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
    0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
    0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
    0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
    0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
    0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
    0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
    0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
    0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};


/**********************************************************************
函数名称: unsigned char CRC8 ( unsigned char *buffer, unsigned char len, unsigned char mode )
函数作用: 计算CRC8校验码
函数输入: unsigned char *pbuffer	-	要校验数据首地址
		  unsigned char len			-	要校验数据长度
		  unsigned char mode		-	模式 0-只返回校验码
		  								     1-返回校验码, 把校验码附加到校验数据最后位置
函数返回值:
		  返回CRC8校验码 ;
**********************************************************************/
static unsigned char CRC8( unsigned char *pbuffer, unsigned char len, unsigned char mode ) {
    unsigned char CrcValue, ByteValue ;
    unsigned char i ;

    CrcValue = 0 ;
    for ( i=0; i<len; i++ ) {
        ByteValue = pbuffer[i] ;
        CrcValue = CRC8Table[CrcValue ^ ByteValue] ;
    }

    if ( mode == 1 ) {
        pbuffer[len] = CrcValue ;
    }
    return CrcValue ;
}


static const unsigned char statickey[17]="3230303530313331";

#define ZERO_BLOCK(m) do{ (m)=0; } while(0)
#define SET_BLOCK(m,b) do { (m) |= (1 << (b)); } while(0)
#define CLR_BLOCK(m,b) do { (m) &= (^(1 << (b))); } while(0)
#define ISSET_BLOCK(m,b) (((m) & (1<<(b))) != 0)

#define EASY_SET_BLOCK(m,of) do {int _b=(of)/16;ZERO_BLOCK(m); SET_BLOCK(m,_b); } while(0)
//#define EASY_SET_BLOCK(m,of) do {m=(of)/16;} while(0)


#define IS_LOAD_KEY() do { int r = testLoadKey(); if(r) return r; }while(0)

// 转换时判断字符串的有效性
int my_atou(const char* str) {
    int len = strlen(str);

    int ret = 0;

    for(int i=0; i < len; i ++) {
        char c = str[len -i-1];
        if(c > '9' || c < '0')
            return 0;

        ret += (int)((c-'0') * pow((double)10,i));
    }

    return ret;
}
/*
static const char* HEX = "0123456789ABCDEF";

static void asc2idno(const char *sAscStr,int iAscLen,unsigned char *uBcdBuf,int& uBcdBufLen)
{
	int i=0;
	int offset=0;
	int len=iAscLen/2;
	unsigned char lch,hch;

	for(i=0;i<len;i++)
	{
		lch=sAscStr[2*i+offset]- HEX;
		hch=sAscStr[2*i+offset+1]-'0';
		lch=lch<<4;
		hch=hch&0x0F;
		lch=lch&0xF0;
		uBcdBuf[i+offset]=hch|lch;
	}
	uBcdBufLen=i+offset;
}
static void idno2asc(const unsigned char *uBcdBuf,int iBcdLen,char *sAscStr)
{
	int i;
	unsigned char lch,hch;

	for(i=0;i<iBcdLen;i++)
	{
		hch=(uBcdBuf[i]&0x0F);
		lch=(uBcdBuf[i]&0xF0);
		lch=lch>>4;
		sAscStr[2*i]=lch+'0';
		sAscStr[2*i+1]=hch+'0';
	}
}

*/


int DbgOut(char *fmt, ...) {
    static char sprint_buf[1024];
    va_list args;
    int n;
    va_start(args, fmt);
    n = vsprintf(sprint_buf, fmt, args);
    va_end(args);
    OutputDebugString(sprint_buf);
    return n;
}

static void set_6byte_int(unsigned char *value_str,__int64 num) {
    value_str[0]=(num>>40)&0xFF;
    value_str[1]=(num>>32)&0xFF;
    value_str[2]=(num>>24)&0xFF;
    value_str[3]=(num>>16)&0xFF;
    value_str[4]=(num>>8)&0xFF;
    value_str[5]=num&0xFF;
}

__int64 get_6byte_int(unsigned char *value_str) {
    __int64 r=0,t=0;
    t = value_str[0];
    r |= t << 40;
    t = value_str[1];
    r |= t << 32;
    t = value_str[2];
    r |= t << 24;
    t = value_str[3];
    r |= t << 16;
    t = value_str[4];
    r |= t << 8;
    r |= value_str[5];
    return r;
}


#define DEBUG(fmt, ...)/* \
            DbgOut("[%s@%s:%d] " fmt"\n", strrchr (__FILE__, '\\') == 0 ?  \
                                       __FILE__ : strrchr (__FILE__, '\\') + 1, \
									   __FUNCTION__, \
                                       __LINE__, __VA_ARGS__);*/



FILE * ks_mf_newcapec_type::g_dump_file=NULL;
ks_mf_newcapec_type::ks_mf_newcapec_type():CCardType(),m_isLoadKey(0),m_lastLoginSect(MF_MAX_SECTNO),m_keyType(0) {
    this->set_cardtype_name("ks_mf_newcapec.dll");
    memset(m_initSectMap,'0',sizeof m_initSectMap);
    memset(m_recycleSectMap,'1',sizeof m_recycleSectMap);
    m_mfcard = &m_cardinfo;
    memset(&m_cardinfo,0,sizeof m_cardinfo);
    memset(&m_cardSect,0,sizeof m_cardSect);
    iPsamPowerOnCnt=0;
    this->m_defaultCardType = KS_MFCARD;
}

void ks_mf_newcapec_type::GetSupportCardType(unsigned int cardTypes[],int &cnt) {
    int i = 0;
    cardTypes[i++] = 0x0200;
    cardTypes[i++] = 0x0300;
    cardTypes[i++] = 0x0400;
    cardTypes[i++] = 0x0409;
    cnt = i;
}
int ks_mf_newcapec_type::InitCardTypeDLL() {
    //CommInit("192.168.108.128", 4000,700);

    char param[512] = "";
    int maxlen;
    int ret=0;

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
    if(m_keyAlg == KA_1ST) {
        if(m_license->get_public_int_param("kscardlib.mfcard.keycard",&m_keyType)) {
            SET_ERR("为设置授权卡类型，默认["<<m_keyType<<"]");
        }
    }
    m_license->get_public_int_param("kscardlib.mfcard.ver",&m_cardVer);

    if(m_cardVer != 2008 && m_cardVer != 2009 && m_cardVer != 2010)
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


    ret = CCardType::InitCardTypeDLL();
    if(ret)
        return ret;
    initAllCardDef();
    return 0;
}
int ks_mf_newcapec_type::testLoadKey() {
    if(this->m_keyAlg == KA_1ST) {
        if(this->m_CardKeys.bLoad ==0 && this->m_isLoadKey == 0) {
            SET_ERR("Mifare1密钥未装载");
            return KS_UNAUTH_TERM;
        }
        if(this->m_isLoadKey == 0) {
            memset(m_mainkey,0,sizeof m_mainkey);
            memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
            m_isLoadKey = 1;
        }
    }
    return 0;
}
int ks_mf_newcapec_type::testCardExists(char *szCardPhyID) {
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

int ks_mf_newcapec_type::doSuccessRequestCard() {
    unsigned char decphyno[4];
    int len,i;
    m_lastLoginSect = MF_MAX_SECTNO;
    hex2dec(this->m_szCardUID,8,decphyno,len);
    for(i=0; i<4; ++i)
        m_OriginPhyNo[3-i] = decphyno[i];
    for(i = 0; i < MF_MAX_SECTNO; ++i) {
        memset(m_cardSect[i].block_buffer,0,sizeof m_cardSect[i].block_buffer);
        m_cardSect[i].has_read = 0;
    }
    this->m_lastLoginSect = MF_MAX_SECTNO;
    this->m_defaultCardType = KS_MFCARD;
    return 0;
}

int ks_mf_newcapec_type::doSubRequestCard(char *szCardPhyID) {
    int nRet=0;
    char phyno[17] = {0};
    nRet=m_Reader->request_card(m_ReaderPara,phyno,KS_MFCARD);
    if(nRet) {
        SET_ERR("寻卡错误 "<<m_Reader->GetErrMsg(NULL));
        return nRet;
    }

    if(szCardPhyID)
        strcpy(szCardPhyID,phyno);

    strcpy(m_szCardUID,phyno);
    return doSuccessRequestCard();
}

int ks_mf_newcapec_type::RecycleKeyCard() {
    if(m_keyType == 1) {
        // 读取授权卡
        int nRet,key_sectno;
        char strphyno[17],temp[16];
        unsigned char keya[6],phyno[4],keyb[6];
        unsigned char buffer[18],buffer_data[18];
        int sectno,blockno;
        // 需要重新读卡了
        memset(m_szCardUID,0,sizeof(m_szCardUID));
        nRet = m_Reader->request_card(m_ReaderPara,strphyno,KS_MFCARD);
        if(nRet) {
            SET_ERR("寻卡错误"<<m_Reader->GetErrMsg(NULL));
            return nRet;
        }

        hex2dec(strphyno,8,phyno,nRet);
        // 读取授权卡 7 扇区
        sectno = 7;
        memcpy(keya,phyno,4);
        sprintf(temp,"%02X",sectno);
        memcpy(keya+4,temp,2);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }
        blockno = sectno * 4 + 1;
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
        if(nRet) {
            SET_ERR("读取授权卡扇区失败");
            return nRet;
        }
        memcpy(keyb,buffer,6);
        // 15 扇区
        sectno=15;
        sprintf(temp,"%02X",sectno);
        memcpy(keya+4,temp,2);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }

        blockno = sectno * 4 + 2;
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
        if(nRet) {
            SET_ERR("读取授权卡扇区失败");
            return nRet;
        }
        //////////////////////////////////////////////////////////////////////////
        //
        memset(temp,0,sizeof temp);
        memcpy(temp,buffer+14,2);
        key_sectno = strtoul(temp,NULL,16);
        memset(buffer,0,sizeof buffer);
        memset(buffer_data,0,sizeof buffer_data);
        memcpy(buffer,m_initLoginKey,6);
        memcpy(buffer+6,MF1_ORIGIN_CTRLBIT,4);
        memcpy(buffer+10,m_initLoginKey,6);
        for(sectno=0; sectno<32; sectno++) {
            // 登录各个扇区
            if(sectno==key_sectno) {
                nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keyb);
                if(nRet) {
                    SET_ERR("授权卡登录扇区错误");
                    return nRet;
                }
                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer_data);
                if(nRet) {
                    SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
                    return KS_WRITECARD;
                }
            } else {
                sprintf(temp,"%02X",sectno);
                memcpy(keya+4,temp,2);
                nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keya);
                if(nRet) {
                    SET_ERR("授权卡登录扇区错误");
                    return nRet;
                }
                if(sectno==7) {	// 第1块
                    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer_data);
                    if(nRet) {
                        SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
                        return KS_WRITECARD;
                    }
                }
                if(sectno==15) {	//第二块
                    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer_data);
                    if(nRet) {
                        SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
                        return KS_WRITECARD;
                    }
                }
            }
            // 初始化各个扇区第3块
            nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+3,buffer);
            if(nRet) {
                SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
                return KS_WRITECARD;
            }
        }
    }
    return 0;
}

int ks_mf_newcapec_type::LoadKeysFromKeyCard(const char *sKeyCardPwd) {
    if(m_keyType == 1) {
        // 读取授权卡
        int nRet;
        char strphyno[17],temp[16];
        unsigned char keya[6],phyno[8];
        unsigned char buffer[18];
        int sectno,blockno,key_block,key_pos;
        // 需要重新读卡了
        memset(m_szCardUID,0,sizeof(m_szCardUID));
        nRet = m_Reader->request_card(m_ReaderPara,strphyno,KS_MFCARD);
        if(nRet) {
            SET_ERR("寻卡错误"<<m_Reader->GetErrMsg(NULL));
            return nRet;
        }

        hex2dec(strphyno,8,phyno,nRet);
        // 读取授权卡 7 扇区
        sectno = 7;
        memcpy(keya,phyno,4);
        sprintf(temp,"%02X",sectno);
        memcpy(keya+4,temp,2);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }
        blockno = sectno * 4 + 1;
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
        if(nRet) {
            SET_ERR("读取授权卡扇区失败");
            return nRet;
        }
        key_block = buffer[6]-'0';
        key_pos = buffer[7] - '0';


        // 15 扇区
        sectno=15;
        sprintf(temp,"%02X",sectno);
        memcpy(keya+4,temp,2);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }

        blockno = sectno * 4 + 2;
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
        if(nRet) {
            SET_ERR("读取授权卡扇区失败");
            return nRet;
        }
        //////////////////////////////////////////////////////////////////////////
        //
        memset(temp,0,sizeof temp);
        memcpy(temp,buffer+14,2);
        sectno = strtoul(temp,NULL,16);
        memcpy(keya,buffer+8,6);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }
        blockno = 4 * sectno + key_block;
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
        if(nRet) {
            SET_ERR("读取授权卡扇区失败");
            return nRet;
        }
        memcpy(m_mainkey,buffer+key_pos,8);
        m_isLoadKey = 1;
        return 0;
    } else {
        int ret;
        ret = CCardType::LoadKeysFromKeyCard(sKeyCardPwd);
        if(ret) {
            return ret;
        }
        if(m_keyAlg==0) { // 采用老的模式
            memset(m_mainkey,0,sizeof m_mainkey);
            memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
            m_isLoadKey = 1;
        }
        return 0;
    }
}

int ks_mf_newcapec_type::IsLoadKeys() {
    return (m_isLoadKey==1);
}

int ks_mf_newcapec_type::ReadNewcapecInfoFromDB(byte* buffer) {
    int nRet=0;
    if(!KS_YKT_Clt::IsInitialized()) {
        SET_ERR("系统通讯模块未初始化");
        return -1;
    }
    // 向后台发起请求
    KS_YKT_Clt clt;
    bool bRet=false;

    T_NEWCAPEC_CARD* pDate = (T_NEWCAPEC_CARD*)buffer;

    bRet=clt.SetStringFieldByName("sname",m_szCardUID); // 卡物理ID
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetStringFieldByName("sstatus0",""); // 读写类型
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    if(!clt.SendRequest(950037,5000)) {
        // TODO : 可能是超时
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
        SET_ERR(errmsg);
        return -1;
    }
    if((nRet = clt.GetReturnCode())!=0) {
        // 充值失败
        char sErrMsg[256]= {0};
        clt.GetReturnMsg(sErrMsg);
        SET_ERR(sErrMsg);
        return 0; // 忽略记录不存在的错误
    }

    clt.GetNextPackage();

    bRet=clt.GetIntFieldByName("lvol0",&pDate->apptype);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol1",&pDate->feetype);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol2",&pDate->custtype);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol3",&pDate->custid);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol4",&pDate->idtype);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol5",&pDate->dpscnt);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol6",&pDate->transdate);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol7",&pDate->daymaxamt);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol8",&pDate->publishid);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol9",&pDate->showcardno);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol10",&pDate->subsidyno);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol11",&pDate->cardstruct);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    bRet=clt.GetIntFieldByName("lvol12",&pDate->schoolcode);
    if(!bRet) {
        SET_ERR("读取通讯数据包错误");
        return -1;
    }

    return 0;
}

int ks_mf_newcapec_type::WriteNewcapecInfoIntoDB(byte* buffer) {
    int nRet=0;
    if(!KS_YKT_Clt::IsInitialized()) {
        SET_ERR("系统通讯模块未初始化");
        return -1;
    }
    // 向后台发起请求
    KS_YKT_Clt clt;
    bool bRet=false;

    T_NEWCAPEC_CARD* pDate = (T_NEWCAPEC_CARD*)buffer;

    bRet=clt.SetStringFieldByName("sname",m_szCardUID); // 卡物理ID
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetStringFieldByName("sstatus0","A"); // 读写类型
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol0",pDate->apptype);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol1",pDate->feetype);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol2",pDate->custtype);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol3",pDate->custid);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol4",pDate->idtype);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol5",pDate->dpscnt);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol6",pDate->transdate);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol7",pDate->daymaxamt);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol8",pDate->publishid);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol9",pDate->showcardno);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol10",pDate->subsidyno);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol11",pDate->cardstruct);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    bRet=clt.SetIntFieldByName("lvol12",pDate->schoolcode);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }

    if(!clt.SendRequest(950037,5000)) {
        // TODO : 可能是超时
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
        SET_ERR(errmsg);
        return -1;
    }
    if((nRet = clt.GetReturnCode())!=0) {
        // 充值失败
        char sErrMsg[256]= {0};
        clt.GetReturnMsg(sErrMsg);
        SET_ERR(sErrMsg);
        return nRet;
    }
    return 0;

}


int ks_mf_newcapec_type::SaveKeys() {
    int nRet=0;
    if(!IsLoadKeys()) {
        SET_ERR("密钥未装载");
        return -1;
    }
    if(!KS_YKT_Clt::IsInitialized()) {
        SET_ERR("系统通讯模块未初始化");
        return -1;
    }
    // 向后台发起请求
    KS_YKT_Clt clt;
    char sKeyHexStr[33];
    bool bRet=false;

    byte encrypt_mainkey[8 +1]= {0};

    if( decrypt_work_key(m_mainkey,encrypt_mainkey) != 0) { // 加密传输
        SET_ERR("计算密钥失败！");
        return -1;
    }

    memset(sKeyHexStr,0,sizeof(sKeyHexStr));
    dec2hex(encrypt_mainkey,8,sKeyHexStr); // 转换成字符串

    bRet=clt.SetStringFieldByName("sname2",sKeyHexStr);
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }	// 请求
    //设置为添加类型
    bRet=clt.SetStringFieldByName("sstatus0","A");
    if(!bRet) {
        SET_ERR("设置通讯数据包错误");
        return -1;
    }
    if(!clt.SendRequest(950049,5000)) {
        // TODO : 可能是超时
        char szMsg[512]= {0};
        char errmsg[512]= {0};
        clt.GetReturnMsg(szMsg);
        sprintf(errmsg,"与主机通讯错误:%s,返回码:%d",szMsg,clt.GetReturnCode());
        SET_ERR(errmsg);
        return -1;
    }
    if((nRet = clt.GetReturnCode())!=0) {
        // 充值失败
        char sErrMsg[256]= {0};
        clt.GetReturnMsg(sErrMsg);
        SET_ERR(sErrMsg);
        return nRet;
    }
    return 0;
}


int ks_mf_newcapec_type::LoadKeys4Clone(const char sKeyCardPin[7]) {
    if(IsLoadKeys())
        return 0;
    else
        return LoadKeysFromKeyCard(sKeyCardPin);
}
int ks_mf_newcapec_type::IsLoadCloneKeys() {
    return (m_isLoadKey==1);
}
int ks_mf_newcapec_type::CloneKeyCard(const char sCloneCardPin[7]) {
    if(!IsLoadCloneKeys()) {
        SET_ERR("密钥未装载");
        return -1;
    }
    return PublishKeyCard (m_mainkey,sCloneCardPin);
}

int ks_mf_newcapec_type::NewAuthCard_Init_Sect(unsigned char PhyNo[4]) {
    int sectno,nRet;
    unsigned char buf[16] = "";
    unsigned char card_key[6] = "";
    char temp[3]="";
    char strphyno[17]="";
    memcpy(card_key,PhyNo,sizeof(PhyNo));
    // 读取一次卡,以免用户同时放多张卡
    for(sectno = 0; sectno < 32; ++sectno) {
        sprintf(temp,"%02X",sectno);
        memcpy(card_key+4,temp,2);

        //////////////////////////////////////////////////////////////////////////
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_initLoginKey);
        if(nRet) {
            nRet = m_Reader->request_card(m_ReaderPara,strphyno,KS_MFCARD);
            if(nRet)
                return nRet;
            nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,card_key);
            if(nRet) {
                SET_ERR("授权卡登录扇区错误");
                return nRet;
            }
        }

        //////////////////////////////////////////////////////////////////////////
        memcpy(buf,card_key,6);
        memcpy(buf+6,MF1_INIT_CTRLBIT,sizeof(MF1_INIT_CTRLBIT));
        memcpy(buf+10,card_key,6);
        // 写扇区信息
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+3,buf);
        if(nRet) {
            SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }
    }
    return 0;
}

int ks_mf_newcapec_type::PublishKeyCard (unsigned char* sMasterKey,const char* sPin) {
    if(m_keyType == 1) {
        int nRet,i;
        int keysectno =27;
        char strphyno[17];
        unsigned char phyno[4];
        unsigned char buffer[16];
        unsigned char AUTH_CARD_SEED[8] = "";
        int sectno;

        memset(m_szCardUID,0,sizeof(m_szCardUID));
        nRet = m_Reader->request_card(m_ReaderPara,strphyno,KS_MFCARD);
        if(nRet) {
            SET_ERR("寻卡错误"<<m_Reader->GetErrMsg(NULL));
            return nRet;
        }
        strcpy(m_szCardUID,strphyno);
        hex2dec(strphyno,8,phyno,nRet);
        for(i=0; i<4; ++i)
            m_OriginPhyNo[3-i] = phyno[i];

        // 计算密钥
        unsigned char auth_key[8] = "";

        if(!m_isLoadKey) {	// 发行密钥卡
            memcpy(auth_key,sMasterKey,8);

            /*
            if( decrypt_work_key(sMasterKey,auth_key) != 0)
            {
            	SET_ERR("计算密钥失败！"<<m_Reader->GetErrMsg(NULL));
            	return -1;
            }*/
        } else
            memcpy(auth_key,m_mainkey,8);		//克隆密钥卡

        // 初始化所有扇区
        if( NewAuthCard_Init_Sect(phyno)!= 0) {
            return -1;
        }

        srand((unsigned)time( NULL ));
        for(i = 0; i < sizeof(AUTH_CARD_SEED); ++i) {
            AUTH_CARD_SEED[i] = rand() % 255;
        }

        unsigned char auth_key_a[8] = "";
        unsigned char auth_key_b[8] = "";
        unsigned char card_key[6]="";
        char temp[3]="";
        if(encryptKeyA(AUTH_CARD_SEED,auth_key_a) != 0 ) {
            SET_ERR("生成密钥A失败！"<<m_Reader->GetErrMsg(NULL));
            return -2;
        }
        if(encryptKeyB(AUTH_CARD_SEED,auth_key_b) != 0) {
            SET_ERR("生成密钥B失败！"<<m_Reader->GetErrMsg(NULL));
            return -2;
        }
        // 第 7 扇区
        sectno = 7;
        memset(buffer,0,sizeof(buffer));
        memcpy(buffer,auth_key_b,6);
        sprintf((char*)buffer+6,"%01X",0);
        //buf[6] = (char)pri_block;
        sprintf((char*)buffer+7,"%01X",4);
        //buf[7] = (char)pri_startpos;
        memcpy(card_key,phyno,sizeof(phyno));
        sprintf(temp,"%02X",sectno);
        memcpy(card_key+4,temp,2);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,card_key);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }

        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);
        if(nRet) {
            SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }

        //////////////////////////////////////////////////////////////////////////
        // 第 15 扇区
        sectno = 15;
        memset(buffer,0,sizeof(buffer));
        memcpy(buffer+8,auth_key_a,6);
        sprintf(temp,"%02X",keysectno);
        memcpy(buffer+14,temp,2);

        sprintf(temp,"%02X",sectno);
        memcpy(card_key+4,temp,2);

        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,card_key);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
        if(nRet) {
            SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }

        //////////////////////////////////////////////////////////////////////////
        // 第 pri_sect 扇区
        sectno = keysectno;
        memset(buffer,0,sizeof(buffer));
        memcpy(buffer+4,auth_key,sizeof(auth_key));

        sprintf(temp,"%02X",sectno);
        memcpy(card_key+4,temp,2);
        // 写密钥
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,card_key);
        if(nRet) {
            SET_ERR("授权卡登录扇区错误");
            return nRet;
        }
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer);
        if(nRet) {
            SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }

        // 写控制位
        memset(buffer,0,sizeof(buffer));
        memcpy(buffer,auth_key_a,6);
        memcpy(buffer+6,MF1_KEYA_RO_CTRLBIT,4);
        memcpy(buffer+10,auth_key_b,6);

        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+3,buffer);
        if(nRet) {
            SET_ERR("初始化扇区["<<sectno<<"]写卡内容失败，请重试");
            return KS_WRITECARD;
        }
        return 0;
    } else {
        return CCardType::PublishKeyCard(sMasterKey,sPin);
    }
}

int ks_mf_newcapec_type::SetKeyCard(ks_cardtype_base *c) {
    int ret;
    ret = CCardType::SetKeyCard(c);
    if(ret)
        return ret;
    if(m_keyAlg==0) { // 采用老的模式
        memset(m_mainkey,0,sizeof m_mainkey);
        memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
        m_isLoadKey = 1;
    }
    return 0;
}


static void SetCompactDate(const char* str, byte buff[2]) {
    char temp[10]= {0};
    strncpy(temp,str+2,2);
    int year = atoi(temp);

    strncpy(temp,str+4,2);
    int month = atoi(temp);

    strncpy(temp,str+6,2);
    int day = atoi(temp);

    //[year:7][month:4][day:5]
    int date = (year << 9) + (month << 5) + day;
    buff[0] = (byte)(date >> 8);
    buff[1] = (byte)(date);

    return;
}


int ks_mf_newcapec_type::PublishOperCard(const char * BatchNo, const char * BatchSeqNo, const char *ExpDate, const char *OperAcc, const char *OperName, const char *OperPwd, const char *StationNo) {
    // 写1块
    OPERBLK1 blk1 = {0};
    blk1.carduse = 1;

    // 帐号 INT24
    int	inum = my_atou(OperAcc);
    if(inum <= 0 || inum >= 0xFFFFFF) {
        SET_ERR("操作员帐号错误，请输入1-16777215数字格式");
        return KS_PARAMERR;
    }

    set_3byte_int(blk1.account,inum);

    // 卡批次号
    inum = my_atou(BatchNo);
    if(inum <= 0 || inum >= 0xFF) {
        SET_ERR("卡批次号错误，请输入1-255数字格式");
        return KS_PARAMERR;
    }

    blk1.cardbatchno = inum;

    // 卡批次序号  INT16
    inum = my_atou(BatchSeqNo);
    if(inum <= 0 || inum >= 0xFFFF ) {
        SET_ERR("卡批次序号错误，请输入1-65535数字格式");
        return KS_PARAMERR;
    }

    set_2byte_int(blk1.cardseqno,inum);

    // 卡密码 ,BCD
    if(strlen(OperPwd) != 6 || my_atou(OperPwd) == 0) {
        SET_ERR("操作员密码错误，请使用6位数字");
        return KS_PARAMERR;
    }

    int out_len = 3;
    asc2bcd(OperPwd,6,blk1.cardpwd,out_len);

    // 工作站编号
    inum = my_atou(StationNo);
    if(inum <= 0 || inum >= 0xFF) {
        SET_ERR("工作站编号错误，请输入1-255数字格式");
        return KS_PARAMERR;
    }

    blk1.station = (byte)inum;
    blk1.crc = CRC8((byte*)&blk1,15,0);


    // 写2块
    OPERBLK2 blk2 = {0};
    blk2.cardstatus = 0xF1;
    // 失效期， 压缩16进制
    if(my_atou(ExpDate) == 0 || strlen(ExpDate) != 8) {
        SET_ERR("失效日期错误，请使用yyyymmdd格式");
        return KS_PARAMERR;
    }

    SetCompactDate(ExpDate, blk2.expiredate);
    blk2.rights = 0xFF;

    int len = strlen(OperName);
    if(len <= 0 || len >= 10) {
        SET_ERR("操作员姓名错误,长度为0-9个字符");
        return KS_PARAMERR;
    }
    strncpy(blk2.name ,OperName, sizeof(blk2.name) );
    blk2.crc = CRC8((byte*)&blk2,15,0);


    int nRet = 0;
    byte keya[6],keyb[6],buffer[16],ctrlbit[4],keya_ro_ctrlbit[4];
    byte init_keya[6];
    char datetime[20]="";
    char temp[10] = "";
    char str_keyA[13]="";
    char str_keyB[13]="";
    char str_Phycardid[10]="";
    dec2hex(m_OriginPhyNo,4,str_Phycardid);
    IS_LOAD_KEY();

    if(this->RequestCard(NULL)) {
        SET_ERR("请放卡");
        return KS_REQUESTCARD;
    }
    memcpy(init_keya,m_initLoginKey,6);
    memcpy(ctrlbit,MF1_INIT_CTRLBIT,4);
    memcpy(keya_ro_ctrlbit,MF1_KEYA_RO_CTRLBIT,4);

    mf_sect_t sect = {0};

    if(CalcCardKeyA(0,&sect)) {
        SET_ERR("初始化Mifare1扇区[0]计算keya失败");
        return KS_LOGINCARD;
    }
    memcpy(keya,sect.key,6);
    memcpy(buffer,keya,6);
    memcpy(buffer+6,ctrlbit,4);

    if(CalcMFSectKey(0,&sect)) {
        SET_ERR("初始化Mifare1扇区[0]，计算keyb失败");
        return KS_LOGINCARD;
    }
    memcpy(keyb,sect.key,6);
    memcpy(buffer+10,keyb,6);
    dec2hex(keya,6,str_keyA);
    dec2hex(keyb,6,str_keyB);
    nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,0,m_initKeyType,init_keya);
    if(nRet) {
        if(RequestCard(NULL)) {
            SET_ERR("寻卡失败");
            return KS_LOGINCARD;
        }
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,0,MF_KEYB,keyb);
        if(nRet) {
            SET_ERR("初始化Mifare1扇区[0],无法初始化，可能已被使用！");
            return KS_LOGINCARD;
        }
        // 可以登录，应该是已经被初始化
    }

    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,1,(byte*)&blk1);
    if(nRet) {
        SET_ERR("初始化扇区[1]写卡内容失败，请重试");
        return KS_WRITECARD;
    }

    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,2, (byte*)&blk2);
    if(nRet) {
        SET_ERR("初始化扇区[2]写卡内容失败，请重试");
        return KS_WRITECARD;
    }

    // 写3块
    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,3,buffer);
    if(nRet) {
        SET_ERR("初始化扇区[3]写密钥失败，请重试");
        return KS_WRITECARD;
    }

    return 0;
}

int ks_mf_newcapec_type::InitUserCard(const char *sShowCardNo) {
    int i,block,nRet;
    byte keya[6],keyb[6],buffer[16],ctrlbit[4],keya_ro_ctrlbit[4];
    byte init_keya[6],data_buffer[16];
    char datetime[20]="";
    char temp[10] = "";
    char str_keyA[13]="";
    char str_keyB[13]="";
    char str_Phycardid[10]="";
    dec2hex(m_OriginPhyNo,4,str_Phycardid);
    IS_LOAD_KEY();

    if(this->RequestCard(NULL)) {
        SET_ERR("请放卡");
        return KS_REQUESTCARD;
    }
    memcpy(init_keya,m_initLoginKey,6);
    memcpy(ctrlbit,MF1_INIT_CTRLBIT,4);
    memcpy(keya_ro_ctrlbit,MF1_KEYA_RO_CTRLBIT,4);


    m_lastLoginSect = MF_MAX_SECTNO;
    for(i=m_minSectNo; i< m_maxSectNo; ++i) {
        // 不初始化
        if(m_initSectMap[i] == '0')
            continue;

        if(CalcCardKeyA(i,&(m_cardSect[i]))) {
            SET_ERR("初始化Mifare1扇区["<<i<<"]计算keya失败");
            return KS_LOGINCARD;
        }
        memcpy(keya,m_cardSect[i].key,6);
        memcpy(buffer,keya,6);
        memcpy(buffer+6,ctrlbit,4);

        if(CalcMFSectKey(i,&(m_cardSect[i]))) {
            SET_ERR("初始化Mifare1扇区，计算keyb失败");
            return KS_LOGINCARD;
        }
        memcpy(keyb,m_cardSect[i].key,6);
        memcpy(buffer+10,keyb,6);
        dec2hex(keya,6,str_keyA);
        dec2hex(keyb,6,str_keyB);
        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,m_initKeyType,init_keya);
        if(nRet) {
            if(RequestCard(NULL)) {
                SET_ERR("初始化Mifare1扇区["<<i<<"]登录失败");
                return KS_LOGINCARD;
            }
            nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
            if(nRet) {
                SET_ERR("初始化Mifare1扇区["<<i<<"],无法初始化，可能已被使用！");
                return KS_LOGINCARD;
            }
            // 可以登录，应该是已经被初始化
            continue;
        } else {
            // 需要写卡钱包类容
            for(block=0; block < 3; ++block) {
                memset(data_buffer,0,sizeof(data_buffer));

                if(i == 0 && block == 0) {
                    continue; // 0 扇区 0 块 不用写
                } else if(i==0 && block == 1) {
                    data_buffer[0] = 9; // 卡用途
                    data_buffer[1] = (char)(1<<4);
                } else if(i==1 && (block == 0 || block == 1)) { // 新开普当天
                    time_t t;
                    t = time(NULL);
                    struct tm * tx = localtime(&t);
                    data_buffer[14] = (byte)tx->tm_mday; // 新开普当天
                }

                // 写卡
                if(m_cardinfo.block_info[i].block_crc[block] == MF_CRC8) {
                    byte crc8 = CRC8(data_buffer,15,0);
                    data_buffer[15] = crc8;
                }

                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+block,data_buffer);
                if(nRet) {
                    SET_ERR("初始化扇区["<<i<<"]写卡内容失败，请重试");
                    return KS_WRITECARD;
                }

                /*
                else if(i == 3) // 钱包索引
                {
                	if(block!=0)
                		continue;
                	memcpy(data_buffer,"\x00\x04\x00\x05\x00\x06\xFF\xFF",8);
                	memset(data_buffer+8,0xFF,8);
                }
                else if(i == 4 || i == 5) // 大钱包、小钱包
                {
                	if(block == 1) continue;
                	memset(data_buffer,0,sizeof data_buffer);
                	GetCurrentDateTime(datetime);
                	for(j=0;j<5;++j)
                	{
                		memset(temp,0,sizeof temp);
                		memcpy(temp,datetime+2+j*2,2);
                		data_buffer[5+j] = atoi(temp);
                	}
                	for(j=0,data_buffer[15]=0;j<15;++j)
                		data_buffer[15] += data_buffer[j];
                }
                else
                {
                	if(i == 0 && block == 0) continue; // 0 扇区 0 块 不用写
                	memset(data_buffer,0,sizeof data_buffer);
                }
                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+block,data_buffer);
                if(nRet)
                {
                	SET_ERR("初始化扇区["<<i<<"]写卡内容失败，请重试");
                	return KS_WRITECARD;
                }*/
            }
            nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
            if(nRet) {
                SET_ERR("初始化扇区["<<i<<"]写密钥失败，请重试");
                return KS_WRITECARD;
            }
        }
    }

    // 初始化库中的数据
    T_NEWCAPEC_CARD init_card_info = {0};
    memset(&init_card_info, 0, sizeof(init_card_info));
    init_card_info.apptype = 1;
    init_card_info.showcardno = atoi(sShowCardNo);

    nRet = WriteNewcapecInfoIntoDB((byte*)&init_card_info);
    if(nRet) {
        return KS_WRITECARD;
    }

    SetFieldVal(CF_CARDBAL,"0");
    SetFieldVal(CF_TOTALAMT,"0");
    SetFieldVal(CF_DPSCNT,"0");
    SetFieldVal(CF_DAYSUMAMT,"0");
    SetFieldVal(CF_CARDNO,"0");
    SetFieldVal(CF_CARDSTATUS,"0");

    if(this->WriteCard()) {
        SET_ERR("写卡失败");
        return KS_WRITECARD;
    }

    return 0;
}

int ks_mf_newcapec_type::RestoreFactorySettings() {
    int i,j,nRet;
    byte keyb[6],buffer[16],origin_ctrlbit[4];
    byte init_keya[6],buffer2[16];

    IS_LOAD_KEY();

    if(this->RequestCard(NULL)) {
        SET_ERR("请放卡");
        return KS_REQUESTCARD;
    }
    memcpy(init_keya,m_initLoginKey,6);
    if(this->m_initKeyType == MF_KEYA) {
        memcpy(origin_ctrlbit,MF1_ORIGIN_CTRLBIT,4);
    } else {
        memcpy(origin_ctrlbit,MF1_INIT_CTRLBIT,4);
    }


    memcpy(buffer,init_keya,6);
    memcpy(buffer+6,origin_ctrlbit,4);
    memcpy(buffer+10,init_keya,6);
    m_lastLoginSect = MF_MAX_SECTNO;
    for(i=m_minSectNo; i< m_maxSectNo; ++i) {
        // 不回收
        if(m_recycleSectMap[i] == '0') continue;

        if(CalcMFSectKey(i,&(m_cardSect[i]))) {
            SET_ERR("初始化Mifare1扇区，计算keyb失败");
            return KS_LOGINCARD;
        }
        memcpy(keyb,m_cardSect[i].key,6);

        nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
        if(nRet) {
            if(RequestCard(NULL)) {
                SET_ERR("初始化Mifare1扇区["<<i<<"]登录失败");
                return KS_LOGINCARD;
            }
            nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,init_keya);
            if(nRet) {
                SET_ERR("初始化Mifare1扇区["<<i<<"],无法回收，可能已被使用！");
                return KS_LOGINCARD;
            }
            // 可以登录，应该是已经被初始化
            continue;
        } else {
            for(j = 0; j<3; ++j) {
                if(i == 0 && j == 0) continue; // 0 扇区 0 块 不用写
                memset(buffer2,0,sizeof buffer2);
                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+j,buffer2);
                if(nRet) {
                    SET_ERR("初始化扇区["<<i<<"]写数据失败，请重试");
                    return KS_WRITECARD;
                }
            }
            nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
            if(nRet) {
                SET_ERR("初始化扇区["<<i<<"]写密钥失败，请重试");
                return KS_WRITECARD;
            }
        }
    }
    return 0;
}


int ks_mf_newcapec_type::CalcKeyFromSAMKeyA(unsigned char *cipherData) {
    int i,ret;
    char szCmd[256];
    ks_cpu_cmd_t cmd;
    unsigned char uResp[256];
    unsigned char sPlain[8];
    unsigned char uRespLen;
    static unsigned char prePhyNo[4] = {0};
    static unsigned char preCipherData[16] = {0};
    if(memcmp(prePhyNo,m_OriginPhyNo,4) == 0) {
        memcpy(cipherData,preCipherData,8);
        return 0;
    }
    for(i = 0; i < 4; i++) {
        sPlain[i] = m_OriginPhyNo[i];
        sPlain[i+4] = ~m_OriginPhyNo[i];
    }

    byte rbuff[256]= {0};
    byte ucRespData[256]= {0};
    //m_PSAMReaderPara->cpuport=1;
    //上电复位
    ret = m_PSAMCardType->ResetPSAM();
    if(ret) {
        return ret;
    }
    // select dir
    //\x00\xA4\x00\x00\x02\xDF\x04
    //sprintf(szCmd,"00A4000002DF04");
    //ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    ret=m_PSAMCardType->selectADFBySFI("DF04");
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }
    // delivery key
    sprintf(szCmd,"801A270208%s",statickey);
    ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }

    // cipher data
    memset(szCmd,0,sizeof szCmd);
    sprintf(szCmd,"80FA000008");
    cmd.send_len = strlen(szCmd);
    dec2hex(sPlain,8,szCmd+cmd.send_len);

    ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }
    // get response
    memcpy(prePhyNo,m_OriginPhyNo,4);
    memcpy(cipherData,uResp,8);
    memcpy(preCipherData,cipherData,8);
    return 0;
}
int ks_mf_newcapec_type::CalcKeyFromSAMKeyB(unsigned char *cipherData) {
    int i,ret;
    char szCmd[256];
    ks_cpu_cmd_t cmd;
    unsigned char uResp[256];
    unsigned char sPlain[8];
    unsigned char uRespLen;
    static unsigned char prePhyNo[4] = {0};
    static unsigned char preCipherData[16] = {0};
    if(memcmp(prePhyNo,m_OriginPhyNo,4) == 0) {
        memcpy(cipherData,preCipherData,8);
        return 0;
    }

    for(i = 0; i < 4; i++) {
        sPlain[i] = m_OriginPhyNo[i];
        sPlain[i+4] = ~m_OriginPhyNo[i];
    }

    byte rbuff[256]= {0};
    byte ucRespData[256]= {0};

    //m_PSAMReaderPara->cpuport=1;
    //上电复位
    ret = m_PSAMCardType->ResetPSAM();
    if(ret) {
        return ret;
    }
    // select dir
    //\x00\xA4\x00\x00\x02\xDF\x04
    //sprintf(szCmd,"00A4000002DF04");
    //ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    ret=m_PSAMCardType->selectADFBySFI("DF04");
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }
    // delivery key
    sprintf(szCmd,"801A270108%s",statickey);
    ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }

    // cipher data
    memset(szCmd,0,sizeof szCmd);
    sprintf(szCmd,"80FA000008");
    cmd.send_len = strlen(szCmd);
    dec2hex(sPlain,8,szCmd+cmd.send_len);

    ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
    if(ret) {
        SET_ERR(this->GetLastErrMsg(NULL));
        return ret;
    }
    // get response

    memcpy(prePhyNo,m_OriginPhyNo,4);
    memcpy(cipherData,uResp,8);
    memcpy(preCipherData,cipherData,8);

    return 0;
}

static void CalM1BlkCode( unsigned char *pSN, unsigned char *pKeyCode, unsigned char BlockNo ) {
    unsigned char i, Sector, iSum = 0;
    unsigned char CardSNExt[ 6 ];

    //计算序列号的和
    for ( i = 0; i < 4; i++ ) {
        iSum += pSN[ i ];
    }

    //传进来的是绝对块地址，应该计算扇区号，考虑s50、s70卡
    if( BlockNo < 128 ) {
        Sector = BlockNo / 4;		//s50卡计算扇区号
    } else {
        Sector = 32 + ( BlockNo - 128 ) / 16;	//s70卡计算扇区号
    }

    //先计算SUM = (BYTE)(∑j(0-3)S0j)，S0[4] = SUM + 5EH，S0[5] = SUM – 96H 。
    //由S0打乱顺序组成S1=（S0[3]、S0[1]、S0[4]、S0[5]、S0[0]、 S0[2]），
    CardSNExt[ 0 ] = pSN[ 3 ];
    CardSNExt[ 1 ] = pSN[ 1 ];
    CardSNExt[ 2 ] = iSum + 0x5e;
    CardSNExt[ 3 ] = iSum - 0x96;
    CardSNExt[ 4 ] = pSN[ 0 ];
    CardSNExt[ 5 ] = pSN[ 2 ];
    //用新得出的与卡序列号相关的数组与种子密钥数组计算一区一密keyA密钥
    for( i = 0; i < 6; i++ ) {
        pKeyCode[ i ] =  pKeyCode[ i ] + (CardSNExt[ i ] ^ ( ~Sector ) );
    }
}

int ks_mf_newcapec_type::CalcCardKeyA(int sectno,mf_sect_t *sect) {
    static byte presentCardNo[4] = "";
    static byte presentKey[6]="";

    //byte tt[4] = {0xd2,0xf3,0x32,0x73};
    //byte out[10]={0};
    //memcpy(out,this->m_mainkey,8);

    //CalM1BlkCode(tt, out, 1);


    //if(memcmp(presentCardNo,this->m_OriginPhyNo,4))
    {
        unsigned char sCipher[17]= {0};
        unsigned int  startpos = 0;

        if(m_keyAlg == KA_1ST) { //
            memcpy(sCipher,this->m_mainkey,8);
            CalM1BlkCode(this->m_OriginPhyNo, sCipher, sectno*4);

            /***************/
            /*
            			char tmp[64]={0};
            			char pSN[64] = {0};

            			for(int i=0; i < 4; i ++)
            			{
            				sprintf(tmp, " 0x%X", m_OriginPhyNo[i]);
            				strcat(pSN, tmp);
            			}

            			char pKeyCode[64] = {0};
            			for(int i=0; i < 8; i ++)
            			{
            				sprintf(tmp, " 0x%X", m_mainkey[i]);
            				strcat(pKeyCode, tmp);
            			}

            			char KeyA[64] = {0};
            			for(int i=0; i < 6; i ++)
            			{
            				sprintf(tmp, " 0x%X", sCipher[i]);
            				strcat(KeyA, tmp);
            			}

            			DbgOut("计算KeyA结果CalM1BlkCode(pSN={%s},pKeyCode={%s},BlockNo={%d}) 计算得 KeyA={%s}",
            				pSN, pKeyCode, sectno*4, KeyA );
            */
            /*********************/

            //if(encryptKeyA(this->m_mainkey,sCipher))
            //{
            //	SET_ERR("计算密钥KEYA错误");
            //	return -1;
            //}

        } else if(m_keyAlg == KA_PSAM) {
            memset(sCipher,0,sizeof sCipher);
            if(CalcKeyFromSAMKeyA(sCipher)) {
                SET_ERR("PSAM卡计算密钥错误");
                return -1;
            }
        } else {
            return -1;
        }
        //memcpy(sCipher + 8, sCipher, 8);
        //startpos=(sCipher[0] + sCipher[1] + sCipher[2] + sCipher[3] + sCipher[4] + sCipher[5] + sCipher[6] + sCipher[7]) % 7;      // sCipher[17]6079813C4F1A2F92, startpos = 4
        memcpy(sect->key, sCipher + startpos, 6);
        sect->key_type = MF_KEYA;
        memcpy(presentCardNo,this->m_OriginPhyNo,4);
        memcpy(presentKey,sect->key,6);
    }
    /*
    else
    {
    	sect->key_type = MF_KEYA;
    	memcpy(sect->key,presentKey,6);
    }*/

    return 0;
}

/*
int ks_mf_newcapec_type::CalcCardKeyA(int sectno,mf_sect_t *sect)
{
	static byte presentCardNo[4] = "";
	static byte presentKey[6]="";

	if(memcmp(presentCardNo,this->m_OriginPhyNo,4))
	{
		unsigned char sCipher[17];
		unsigned int  startpos = 0;
		if(m_keyAlg == KA_1ST) //
		{
			memset(sCipher,0,sizeof sCipher);
			if(encryptKeyA(this->m_mainkey,sCipher))
			{
				SET_ERR("计算密钥KEYA错误");
				return -1;
			}
		}
		else if(m_keyAlg == KA_PSAM)
		{
			memset(sCipher,0,sizeof sCipher);
			if(CalcKeyFromSAMKeyA(sCipher))
			{
				SET_ERR("PSAM卡计算密钥错误");
				return -1;
			}
		}
		else
		{
			return -1;
		}
		memcpy(sCipher + 8, sCipher, 8);
		startpos=(sCipher[0] + sCipher[1] + sCipher[2] + sCipher[3] + sCipher[4] + sCipher[5] + sCipher[6] + sCipher[7]) % 7;      // sCipher[17]6079813C4F1A2F92, startpos = 4
		memcpy(sect->key, sCipher + startpos, 6);
		sect->key_type = MF_KEYA;
		memcpy(presentCardNo,this->m_OriginPhyNo,4);
		memcpy(presentKey,sect->key,6);
	}
	else
	{
		sect->key_type = MF_KEYA;
		memcpy(sect->key,presentKey,6);
	}
	return 0;
}
*/

int ks_mf_newcapec_type::CalcMFSectKey(int sectno,mf_sect_t *sect) {
    unsigned char sCipher[17];
    unsigned int  startpos=0;
    static byte presentKey[6]="";

    //if(memcmp(this->m_OriginPhyNo,m_presentPhyNo,4))
    {
        if(m_keyAlg == KA_1ST ) {
            memset(sCipher,0,sizeof sCipher);
            if(encryptKeyB(this->m_mainkey,sCipher)) {
                SET_ERR("计算密钥KEYB错误");
                return -1;
            }
        } else if(m_keyAlg == KA_PSAM) {
            memset(sCipher,0,sizeof sCipher);
            if(CalcKeyFromSAMKeyB(sCipher)) {
                SET_ERR("PSAM卡计算密钥错误");
                return -1;
            }
        } else
            return -1;
        memcpy(sCipher+8,sCipher,8);
        startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
        memcpy(sect->key,sCipher+startpos,6);
        sect->key_type = MF_KEYB;
        memcpy(presentKey,sect->key,6);
        memcpy(m_presentPhyNo,this->m_OriginPhyNo,4);
    }

    /*
    else
    {
    	memcpy(sect->key,presentKey,6);
    	sect->key_type = MF_KEYB;
    }*/

    return 0;
}

int ks_mf_newcapec_type::encryptKeyA(unsigned char *key,unsigned char *sCipher) {
    unsigned int i;
    unsigned char sPlain[9];

    des_context ctx;
    memset(sPlain, 0, sizeof(sPlain));

    for(i = 0; i < 4; i++) {
        sPlain[i] = m_OriginPhyNo[i];
        sPlain[i+4] = ~m_OriginPhyNo[i];
    }

    memset(&ctx,0,sizeof ctx);
    des_set_key(&ctx,key);
    des_encrypt(&ctx,sPlain,sCipher);
    return 0;
}
int ks_mf_newcapec_type::encryptKeyB(unsigned char *key,unsigned char *sCipher) {
    unsigned char sPlain[9];
    unsigned char sKey[17];
    des3_context ctx;
    int i;

    memset(sPlain,0,sizeof(sPlain));
    memset(sKey,0,sizeof(sKey));
    for(i=0; i<4; i++) {
        sPlain[i]=~m_OriginPhyNo[i];
        sPlain[i+4]=m_OriginPhyNo[i];
    }
    for(i=0; i<8; i++) {
        sKey[i]=key[i];
        sKey[i+8]=~key[i];
    }
    memset(&ctx,0,sizeof ctx);
    //encrypt_3des(sKey,16,sPlain,8,sCipher);
    des3_set_2keys(&ctx,sKey,sKey+8);
    des3_encrypt(&ctx,sPlain,sCipher);
    return 0;
}



int ks_mf_newcapec_type::LoginCardSect(int sectno) {
    int nRet;
    if(m_lastLoginSect == sectno)
        return 0;

    m_lastLoginSect = MF_MAX_SECTNO;

    //nRet = CalcMFSectKey(sectno,&(m_cardSect[sectno]));
    //if(nRet)
    //{
    //	SET_ERR("计算M1卡密钥错误");
    //	return -1;
    //}



    CalcCardKeyA(sectno,&(m_cardSect[sectno]));

    nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno
                                ,m_cardSect[sectno].key_type,m_cardSect[sectno].key);
    if(nRet) {
        SET_ERR("登录Mifare1扇区"<<sectno<<"失败");
        char cardkey[16] = {0};
        dec2hex(m_cardSect[sectno].key,6,cardkey);
        m_lastLoginSect	=-1;
        memset(m_presentPhyNo,0,sizeof m_presentPhyNo);
        return KS_LOGINCARD;
    }
    m_lastLoginSect = sectno;
    return 0;
}


int ks_mf_newcapec_type::ReadCard() {
    IS_LOAD_KEY();

    int sectno,nRet,block;
    byte buffer[16 + 2]= {0};
    //memset(&m_cardSect,0,sizeof m_cardSect);
    std::map<int,EFBUF>::iterator iter;
    for(iter=m_EFMap.begin(); iter != m_EFMap.end(); ++iter) {
        sectno = iter->first;
        if(!iter->second.ReadFieldSet.size())
            continue;
        if(m_cardSect[sectno].has_read == 0) {
            // 需要先读取扇区
            if(sectno == 3) { // 3伪扇区，从数据库读取填充
                nRet = ReadNewcapecInfoFromDB(m_cardSect[sectno].block_buffer);
                if(nRet) {
                    SET_ERR("读卡 伪扇区["<<sectno<<"]失败");
                    return KS_READCARD;
                }
            } else {
                if((nRet = LoginCardSect(sectno))!=0) {
                    SET_ERR("登录扇区"<<sectno<<"失败");
                    return nRet;
                }
                // read card
                for(block = 0; block < 4; ++block) {
                    memset(buffer,0xFF,sizeof buffer);
                    if(m_cardinfo.block_info[sectno].block_used[block] == 1) {
                        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+block,buffer);
                        if(nRet) {
                            // 如果主钱包区读取错误，则尝试从1扇区1块读取备份数据,并重写主钱包区
                            if(sectno == 1 && block == 0) {
                                nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);
                                if(nRet) {
                                    SET_ERR("读扇区"<<sectno<<"第1块数据失败");
                                    return KS_READCARD;
                                }

                                unsigned char crc8 = CRC8(buffer, 15, 0);
                                if(crc8 != buffer[15]) {
                                    SET_ERR("读取扇区"<<sectno<<"第1块校验错误");
                                    return KS_READCARD;
                                }

                                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+ 0,buffer);
                                if(nRet) {
                                    SET_ERR("写Mifare1扇区["<<sectno<<"]钱包块失败");
                                    return KS_WRITECARD;
                                }
                            } else {
                                SET_ERR("读扇区"<<sectno<<"第"<<block<<"块数据失败");
                                return KS_READCARD;
                            }


                        }
                        if(m_cardinfo.block_info[sectno].block_crc[block] == MF_CRC8) {
                            byte crc8 = CRC8(buffer, 15, 0);
                            if(crc8 != buffer[15]) {
                                // 如果主钱包区读取错误，则尝试从1扇区1块读取备份数据,并重写主钱包区
                                if(sectno == 1 && block == 0) {
                                    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);
                                    if(nRet) {
                                        SET_ERR("读扇区"<<sectno<<"第1块数据失败");
                                        return KS_READCARD;
                                    }

                                    crc8 = CRC8(buffer, 15, 0);
                                    if(crc8 != buffer[15]) {
                                        SET_ERR("读取扇区"<<sectno<<"第1块校验错误");
                                        return KS_READCARD;
                                    }

                                    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+ 0,buffer);
                                    if(nRet) {
                                        SET_ERR("写Mifare1扇区["<<sectno<<"]钱包块失败");
                                        return KS_WRITECARD;
                                    }
                                } else {
                                    SET_ERR("读取扇区"<<sectno<<"第"<<block<<"块校验错误");
                                    return KS_READCARD;
                                }
                            }
                        }
                    }
                    memcpy(m_cardSect[sectno].block_buffer+16*block,buffer,16);
                }
            } // 读取扇区
            m_cardSect[sectno].has_read = 1;
        }
    }
    return 0;
}

// 新开普补助钱包
static int subsidyamt = 0;
// 新开普总额
static int totalamt = 0;

int ks_mf_newcapec_type::WriteCard() {
    IS_LOAD_KEY();
    int sectno,nRet,blockno,i,offset,len;
    byte buffer[18]= {0};
    int block_write_flag[MF_MAX_BLOCK];
    byte real_write_buffer[MF_MAX_BLOCK_SIZE];

    //memset(block_write_flag,0,sizeof block_write_flag);
    memset(real_write_buffer,0,sizeof real_write_buffer);
    std::map<int,EFBUF>::iterator iter;
    for(iter=m_EFMap.begin(); iter != m_EFMap.end(); ++iter) {
        sectno = iter->first;
        // 钱包相关扇区不要写数据
        if(sectno > 3 && sectno < m_maxSectNo)
            continue;
        EFBUF buf = iter->second;
        if(buf.WriteFieldSet.empty())
            continue;

        if(sectno != 3) { // 伪扇区读写不需要登录
            if((nRet=LoginCardSect(sectno)))
                return nRet;
        }

        // 登录成功，写卡信息
        memset(block_write_flag,0,sizeof block_write_flag);
        memset(real_write_buffer,0,sizeof real_write_buffer);
        std::set<int>::iterator iter;

        if(m_cardSect[sectno].has_read == 0) {
            if(sectno == 3) { // 3伪扇区，从数据库读取填充
                nRet = ReadNewcapecInfoFromDB(m_cardSect[sectno].block_buffer);
                if(nRet) {
                    SET_ERR("读卡 伪扇区["<<sectno<<"]失败");
                    return KS_READCARD;
                }
            } else {
                // 需要先读取扇区
                for(i = 0; i<3; ++i) {
                    memset(buffer,0,sizeof buffer);
                    nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+i,buffer);
                    if(nRet) {
                        SET_ERR("读卡Mifare1扇区["<<sectno<<"]失败");
                        return KS_READCARD;
                    }
                    memcpy(m_cardSect[sectno].block_buffer+16*i,buffer,16);
                }
            }

            m_cardSect[sectno].has_read = 1;
        }

        memcpy(real_write_buffer,m_cardSect[sectno].block_buffer,MF_MAX_BLOCK_SIZE);

        //
        for(iter = buf.WriteFieldSet.begin(); iter != buf.WriteFieldSet.end(); ++iter) {
            int writefld = *iter;
            offset = m_FieldVect[writefld].offset;
            len = m_FieldVect[writefld].length;

            if(writefld == CF_SUBSIDYBAL) {
                //3-5补助（高2位给总额） 和 6-8总额：充值+，提现-

                real_write_buffer[offset] = (subsidyamt >> 14)&0xFF;
                real_write_buffer[offset+1] = (subsidyamt >> 6)&0xFF;
                byte v = real_write_buffer[offset+2];
                real_write_buffer[offset+2] = (subsidyamt&0x3F) + (v & 0xC0); // 保留高2位

            } else if(writefld == CF_TOTALAMT) {
                //3-5补助（高2位给总额） 和 6-8总额：充值+，提现-

                byte v = real_write_buffer[offset+2];
                real_write_buffer[offset+2] = (((totalamt >> 24)&3) << 6) + (v & 0x3F); // 保留低6位
                real_write_buffer[offset+3] = (totalamt >> 16)&0xFF;
                real_write_buffer[offset+4] = (totalamt >> 8)&0xFF;
                real_write_buffer[offset+5] = (totalamt)&0xFF;
            } else
                memcpy(real_write_buffer+offset,m_cardSect[sectno].write_buffer+offset,len);
        }

        if(sectno == 3) { // 3伪扇区，写数据库
            nRet = WriteNewcapecInfoIntoDB( real_write_buffer);
            if(nRet) {
                SET_ERR("读卡 伪扇区["<<sectno<<"]失败");
                return KS_WRITECARD;
            }
        } else {
            // 检测哪些块需要写
            for(iter = buf.WriteFieldSet.begin(); iter != buf.WriteFieldSet.end(); ++iter) {
                int writefld = *iter;
                offset = m_FieldVect[writefld].offset;
                len = m_FieldVect[writefld].length;

                for(blockno = 0; blockno < MF_MAX_BLOCK; ++blockno) {
                    if(ISSET_BLOCK(m_FieldVect[writefld].blockno,blockno))
                        block_write_flag[blockno] = 1;
                }
            }

            // 卡真实扇区读写
            for(blockno=0; blockno<3; ++blockno) {
                if(block_write_flag[blockno] == 1) {
                    // 写卡
                    if(m_cardinfo.block_info[sectno].block_crc[blockno] == MF_CRC8) {
                        byte crc8 = CRC8(real_write_buffer+16*blockno,15, 0);
                        *(real_write_buffer+16*blockno + 15) = crc8;
                    }

                    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+blockno,real_write_buffer+16*blockno);
                    if(nRet) {
                        SET_ERR("写Mifare1扇区["<<sectno<<"]块["<<blockno<<"]失败");
                        return KS_WRITECARD;
                    }

                    if(sectno == 1 && blockno == 0) { // 主钱包区，备份到 1扇区 1块
                        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+ 1,real_write_buffer+16*blockno);
                        if(nRet) {
                            SET_ERR("写Mifare1扇区["<<sectno<<"]钱包备份块失败");
                            return KS_WRITECARD;
                        }
                    }
                }
            }
        }

        // 更新缓存
        memcpy(m_cardSect[sectno].block_buffer,real_write_buffer, MF_MAX_BLOCK_SIZE);
    }
    return 0;
}

int ks_mf_newcapec_type::SetFieldVal(int FieldID,const char *fieldval) {
    int sectno,offset,len,num,data_len,i;
    char temp[64] = {0};
    byte buff[256] = {0};
    if(FieldID>CF_END||FieldID<CF_START) {
        SET_ERR("SetFieldVal:字段索引"<<FieldID<<"不存在");
        return -1;
    }

    DEBUG("SetFieldVal [%d][%s]",FieldID, fieldval );

    /*
    std::set<int>::iterator it;
    it=m_EFMap[m_FieldVect[FieldID].fid].WriteFieldSet.find(FieldID);
    if(it==m_EFMap[m_FieldVect[FieldID].fid].WriteFieldSet.end())
    {
    	SET_ERR("SetFieldVal:字段索引"<<FieldID<<"未设置写");
    	return -1;
    }

    if(m_cardVer >= 2009)
    {
    	if(FieldID == CF_CARDSTATUS)
    	{
    		this->SetFieldWriteMode(CF_BLACKFLAG);
    		char newval[64] = {0};
    		if(strcmp(fieldval,"0")==0)
    		{
    			strcpy(newval,"255");
    		}
    		else
    		{
    			strcpy(newval,"0");
    		}
    		this->SetFieldVal(CF_BLACKFLAG,newval);
    	}
    }*/

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
    case FT_BCD: {
        memset(temp, 0 , sizeof(temp));
        temp[0] = 0;
        int i=0;
        for(i=0; i < len*2 - data_len; i ++) {
            strcat(temp, "0");
        }

        strncat(&temp[i], fieldval, sizeof(temp)-i);

        if(FieldID == CF_IDNO) {
            char ch = temp[len*2 -1]; // 最后一个字符是否为数字

            if(ch > '9' || ch < '0')
                temp[len*2 -1] = '?';
        }

        asc2bcd(temp,len*2,buff,data_len);
        break;
    }
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
        if(FieldID == CF_CARDSTATUS) {
            if(strcmp(fieldval,"0") == 0)
                buff[0] = 0xF1;
            else if(strcmp(fieldval,"3") == 0)
                buff[0] = 0xF3;
            else {
                buff[0] = (byte)atoi(fieldval);
            }
        } else if(FieldID == CF_SEX) { // 兼容新开普卡定义
            if(strcmp(fieldval,"1") == 0)
                buff[0] = 2;
            else if(strcmp(fieldval,"2") == 0)
                buff[0] = 1;
            else {
                buff[0] = (byte)atoi(fieldval);
            }
        } else {
            num = atoi(fieldval);
            buff[0]=num % 256;
        }

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
    case FT_INT48: {
        __int64 num64 = _atoi64(fieldval);
        set_6byte_int(buff,num64);
    }
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
        *(int*)buff = atoi(fieldval);
        //buff[0] = num % 256;
        //buff[1] = (num / 256) % 256;
        //buff[2] = (num / 256 / 256) % 256;
        //buff[3] = (num / 256 / 256) % 256;
        break;

    case FT_COMPACT_DATE: {
        memset(temp,0,sizeof temp);

        strncpy(temp,fieldval+2,2);
        int year = atoi(temp);

        strncpy(temp,fieldval+4,2);
        int month = atoi(temp);

        strncpy(temp,fieldval+6,2);
        int day = atoi(temp);

        //[year:7][month:4][day:5]
        int date = (year << 9) + (month << 5) + day;
        buff[0] = (byte)(date >> 8);
        buff[1] = (byte)(date);
        break;
    }
    case FT_STUEMPNO: {
        int idx = 0;
        unsigned short bitflg = 0;

        for(i=0; i< data_len && i < 16 && idx < 8; i++) {
            char c0 = fieldval[i];
            char c1 = fieldval[i+1];

            if(c0 >= '0' && c0 <= '9' && c1 >='0' && c1 <= '9') {
                buff[idx++] = (((c0 - '0') << 4) |  (c1 - '0'));
                i ++;
            } else {
                bitflg |= (3 << idx*2);
                buff[idx++] = c0;
            }
        }

        for(; idx< 8; idx++) { // 剩余字节置0
            bitflg |= (3 << idx*2);
            buff[idx] = 0;
        }

        memcpy(&buff[8],&bitflg, 2);

        break;
    }
    case FT_SUBSIDYBAL: {
        //3-5补助（高2位给总额） 和 6-8总额：充值+，提现-
        subsidyamt = atoi(fieldval);
        break;
    }
    case FT_TOTALAMT: {
        //3-5补助（高2位给总额） 和 6-8总额：充值+，提现-
        totalamt = atoi(fieldval);
        break;
    }
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
            SET_ERR("SetFieldVal:字段索引"<<FieldID<<":数据定义错误");
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
            SET_ERR("SetFieldVal:字段索引"<<FieldID<<":数据定义错误");
            return -1;
        }
        break;

    default:
        SET_ERR("SetFieldVal:字段索引"<<FieldID<<":数据类型错误");
        return -1;
    }

    memcpy(m_cardSect[sectno].write_buffer+offset,buff,m_FieldVect[FieldID].length);
    SetFieldWriteMode(FieldID);
    return 0;
}
int ks_mf_newcapec_type::GetFieldVal(int FieldID,char *fieldval) {
    int sectno,offset,len,num;
    char temp[64]= {0};
    if(FieldID>CF_END||FieldID<CF_START) {
        SET_ERR("GetFieldVal:字段索引"<<FieldID<<"不存在");
        return -1;
    }

    std::set<int>::iterator it;
    it=m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.find(FieldID);
    if(it==m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.end()) {
        SET_ERR("GetFieldVal:字段索引"<<FieldID<<"未设置读");
        return -1;
    }
    sectno = m_FieldVect[FieldID].fid;
    if(m_cardSect[sectno].has_read == 0) {
        SET_ERR("GetFieldVal:字段索引"<<FieldID<<"未读取");
        fieldval[0]=0;
        return -1;
    }
    len = m_FieldVect[FieldID].length;
    offset = m_FieldVect[FieldID].offset;

    switch(m_FieldVect[FieldID].type) {
    case FT_ANSI:
        memcpy(fieldval,m_cardSect[sectno].block_buffer+offset,len);
        fieldval[len] = 0;
        break;
    case FT_BCD: {
        bcd2asc(m_cardSect[sectno].block_buffer+offset,len,temp);

        char *p = (char*)temp; // 去除前导'0'
        while(*p == '0')
            p ++;

        temp[len*2] = 0;

        if(FieldID == CF_IDNO) { // 身份证号码必须18位
            char c =  temp[len*2 -1];
            if(c >'9' || c < '0')
                temp[len*2 -1] = 'X';
        }

        strcpy(fieldval, p);
    }
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
        if(FieldID == CF_CARDSTATUS) { // 兼容新开普卡定义
            byte card_status = m_cardSect[sectno].block_buffer[offset];

            int ret_v = 0;

            if(card_status == 0xF1)
                ret_v = 0;
            else if(card_status == 0xF3)
                ret_v = 3;
            else
                ret_v = card_status;

            sprintf(fieldval,"%d",ret_v);
        } else if(FieldID == CF_SEX) { // 兼容新开普卡定义
            byte card_sex = m_cardSect[sectno].block_buffer[offset] & 3;
            int ret_v = 0;

            if(card_sex == 1)
                ret_v = 2;
            else if(card_sex == 2)
                ret_v = 1;
            else
                ret_v = card_sex;

            sprintf(fieldval,"%d",ret_v);
        } else {
            sprintf(fieldval,"%d",m_cardSect[sectno].block_buffer[offset]);
        }
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
    case FT_INT48: {
        __int64 num64 = get_6byte_int(m_cardSect[sectno].block_buffer+offset);
        sprintf(fieldval,"%I64d",num64);
    }
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
        //num = m_cardSect[sectno].block_buffer[offset];
        //num += m_cardSect[sectno].block_buffer[offset+1] * 256;
        //num += m_cardSect[sectno].block_buffer[offset+2] * 256*256;
        //num += m_cardSect[sectno].block_buffer[offset+2] * 256*256*256;
        num = *((int*)&m_cardSect[sectno].block_buffer[offset]);
        sprintf(fieldval,"%d",num);
        break;
    case FT_COMPACT_DATE: {
        // [year:7][month:4][day:5]
        int date = m_cardSect[sectno].block_buffer[offset] << 8;
        date += m_cardSect[sectno].block_buffer[offset+1];

        int year = 2000 + ((date >> 9) & 0x7F);//
        int month = (date >> 5) & 0xF;
        int day = date& 0x1F;

        sprintf(fieldval,"%04d%02d%02d",year, month, day);
        break;
    }
    case FT_SUBSIDYBAL: {
        //3-5补助（高2位给总额） 和 6-8总额：充值+，提现-
        num = (m_cardSect[sectno].block_buffer[offset] << 14);
        num +=  (m_cardSect[sectno].block_buffer[offset+1] << 6);
        num +=  (m_cardSect[sectno].block_buffer[offset+2]&0x3F);

        sprintf(fieldval,"%d",num);
        break;
    }
    case FT_TOTALAMT: {
        //3-5补助（高2位给总额） 和 6-8总额：充值+，提现-
        num = ((m_cardSect[sectno].block_buffer[offset+2] >> 6) << 24);
        num +=  (m_cardSect[sectno].block_buffer[offset+3] << 16);
        num +=  (m_cardSect[sectno].block_buffer[offset+4] << 8);
        num +=  (m_cardSect[sectno].block_buffer[offset+5]);

        sprintf(fieldval,"%d",num);
        break;
    }
    case FT_STUEMPNO: {
        unsigned short bitflg = 0;

        memcpy(&bitflg, &m_cardSect[sectno].block_buffer[offset + 8], 2);
        memset(temp, 0, sizeof(temp));

        int idx = 0;
        for(int i=0; i<8; i++) {
            unsigned char ch =  m_cardSect[sectno].block_buffer[offset + i];

            if(((bitflg >> (i*2))& 3) == 3) { // 字符
                if(ch == 0) // 结束
                    break;

                temp[idx++] = ch;
            } else { // 数字
                temp[idx++] = ((ch >> 4)& 0xF)  + '0';
                temp[idx++] = (ch & 0xF) + '0';
            }
        }

        temp[idx] = 0;
        _snprintf(fieldval, 16, "%s",temp);

        break;
    }


    case FT_HEX_DATE:
        if(len == 3) {
            temp[0] = 20;
            memcpy(temp+1,m_cardSect[sectno].block_buffer+offset,len);
        } else if(len == 4) {
            memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
        } else {
            SET_ERR("GetFieldVal:字段索引"<<FieldID<<":数据定义错误");
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
            SET_ERR("GetFieldVal:字段索引"<<FieldID<<":数据定义错误");
            return -1;
        }
        sprintf(fieldval,"%02d%02d%02d",temp[0],temp[1],temp[2]);
        break;
    }

    DEBUG("GetFieldVal [%d] [%s]",FieldID, fieldval);

    return 0;
}
char * ks_mf_newcapec_type::GetErrMsgByErrCode( int nErrCode,char *sErrInfo) {
    return "";
}

int  ks_mf_newcapec_type::AddMoney(ST_TRANSPACK *transpack) {
    //return MFTransaction(transpack,1);

    char temp[64] = "";
    int nCardBala = 0,nCardCnt = 0,nDayTotal = 0, nTotal = 0, nSubsidyBal = 0;

    this->SetFieldReadMode(CF_CARDBAL);
    this->SetFieldReadMode(CF_DPSCNT);
    this->SetFieldReadMode(CF_SUBSIDYBAL);

    if(this->ReadCard()) {
        SET_ERR("读卡失败");
        return KS_READCARD;
    }

    memset(temp,0,sizeof temp);
    this->GetFieldVal(CF_CARDBAL,temp);
    nCardBala = atoi(temp);

    this->GetFieldVal(CF_DPSCNT,temp);
    nCardCnt = atoi(temp);

    if(nCardBala == transpack->nAftBalance && nCardCnt == transpack->nPayCardCnt+1)
        return 0;

    this->GetFieldVal(CF_SUBSIDYBAL,temp);
    nSubsidyBal = atoi(temp);

    nCardBala += transpack->nTransAmt;
    nCardCnt ++;
    nTotal = nCardBala + nSubsidyBal;

    sprintf(temp, "%d", nCardBala);
    this->SetFieldVal(CF_CARDBAL,temp);

    sprintf(temp, "%d", nCardCnt);
    this->SetFieldVal(CF_DPSCNT,temp);

    sprintf(temp, "%d", nTotal);
    this->SetFieldVal(CF_TOTALAMT,temp);

    if(this->WriteCard()) {
        SET_ERR("写卡失败");
        return KS_WRITECARD;
    }

    return 0;
}

int  ks_mf_newcapec_type::PayMoney(ST_TRANSPACK *transpack) {
    //return MFTransaction(transpack,0);

    char temp[64] = "";
    int nCardBala = 0,nCardCnt = 0,nDayTotal = 0, nTotal = 0, nSubsidyBal = 0;

    this->SetFieldReadMode(CF_CARDBAL);
    this->SetFieldReadMode(CF_PAYCNT);
    //this->SetFieldReadMode(CF_DAYSUMAMT);
    this->SetFieldReadMode(CF_SUBSIDYBAL);

    if(this->ReadCard()) {
        SET_ERR("读卡失败");
        return KS_READCARD;
    }

    memset(temp,0,sizeof temp);
    this->GetFieldVal(CF_CARDBAL,temp);
    nCardBala = atoi(temp);

    this->GetFieldVal(CF_PAYCNT,temp);
    nCardCnt = atoi(temp);

    this->GetFieldVal(CF_DAYSUMAMT,temp);
    nDayTotal = atoi(temp);

    this->GetFieldVal(CF_SUBSIDYBAL,temp);
    nSubsidyBal = atoi(temp);

    if(nCardBala == transpack->nAftBalance && nCardCnt == transpack->nPayCardCnt+1) {
        return 0;
    }
    /*
    this->GetFieldVal(CF_TODAY,temp);

    if(strncmp(temp,transpack->sTransDate,8)!=0)
    	nDayTotal = transpack->nTransAmt; // 不同日，清空日消累计额
    else
    	nDayTotal += transpack->nTransAmt;// 只有消费才更新累计额
    */
    nCardBala -= transpack->nTransAmt;
    nCardCnt ++;
    nTotal = nCardBala + nSubsidyBal;

    sprintf(temp, "%d", nCardBala);
    this->SetFieldVal(CF_CARDBAL,temp);

    sprintf(temp, "%d", nCardCnt);
    this->SetFieldVal(CF_PAYCNT,temp);

    sprintf(temp, "%d", nDayTotal);
    this->SetFieldVal(CF_DAYSUMAMT,temp);

    sprintf(temp, "%d", nTotal);
    this->SetFieldVal(CF_TOTALAMT,temp);

    if(this->WriteCard()) {
        SET_ERR("写卡失败");
        return KS_WRITECARD;
    }

    return 0;
}
/*
int ks_mf_newcapec_type::MFTransaction(ST_TRANSPACK *transpack,int transtype)
{
	int nRet,sectno,blockno,i,offset;
	int nCardBala,nCardPayCnt,nDayTotal;
	char datetime[24] = "";
	byte buffer[16+2],buffer2[16+2],buffer3[16+2];
	char temp[64] = "";
	// 判断读卡先
	sectno = m_FieldVect[CF_CARDBAL].fid;
	this->SetFieldReadMode(CF_TRANSDATE);
	this->SetFieldReadMode(CF_TRANSTIME);
	this->SetFieldReadMode(CF_DAYSUMAMT);
	this->SetFieldReadMode(CF_CARDBAL);
	this->SetFieldReadMode(CF_PAYCNT);
	if(m_cardSect[sectno].has_read == 0)
	{
		// 必须先读卡

		//this->SetFieldReadMode(CF_CARDBAL);
		//this->SetFieldReadMode(CF_PAYCNT);
		//this->SetFieldReadMode(CF_DAYSUMAMT);
		//this->SetFieldReadMode(CF_TRANSDATE);
		//this->SetFieldReadMode(CF_TRANSTIME);

		if(this->ReadCard())
		{
			SET_ERR("读卡失败");
			return KS_READCARD;
		}
	}
	// 读卡成功后判断
	memset(temp,0,sizeof temp);
	this->GetFieldVal(CF_CARDBAL,temp);
	nCardBala = atoi(temp);
	memset(temp,0,sizeof temp);
	this->GetFieldVal(CF_PAYCNT,temp);
	nCardPayCnt = atoi(temp);
	memset(temp,0,sizeof temp);
	this->GetFieldVal(CF_DAYSUMAMT,temp);
	nDayTotal = atoi(temp);
	if(nCardBala == transpack->nAftBalance && nCardPayCnt == transpack->nPayCardCnt+1)
	{
		return 0;
	}
	this->GetFieldVal(CF_TRANSDATE,datetime);
	this->GetFieldVal(CF_TRANSTIME,datetime+8);
	if(strncmp(datetime,transpack->sTransDate,8)!=0)
	{
		if(transtype == 0)
			nDayTotal = transpack->nTransAmt;
		else
			nDayTotal = 0;
	}
	else
	{
		if(transtype == 0) // 只有消费才更新累计额
			nDayTotal += transpack->nTransAmt;
	}

	// 组合成buffer写卡
	memcpy(buffer,m_cardSect[sectno].block_buffer,16);
	nRet = LoginCardSect(sectno);
	if(nRet)
	{
		transpack->cRetryFlag=1;
		SET_ERR("登录卡钱包失败");
		return nRet;
	}
	blockno = sectno * 4;
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+2,buffer);
	if(nRet)
	{
		transpack->cGetProveFlag=1;
		transpack->cRetryFlag=1;
		SET_ERR("写Mifare1卡余额失败");
		return KS_WRITEPURSE;
	}
	memcpy(buffer2,m_cardSect[sectno].block_buffer,16);
	offset = 0;
	buffer2[offset++] = transpack->nAftBalance % 256;
	buffer2[offset++] = transpack->nAftBalance / 256 % 256;
	buffer2[offset++] = transpack->nAftBalance / 256 / 256;
	nCardPayCnt++;
	buffer2[offset++] = nCardPayCnt / 256;
	buffer2[offset++] = nCardPayCnt % 256;
	for(i=0;i<3;++i)
	{
		memset(temp,0,sizeof temp);
		memcpy(temp,transpack->sTransDate+2+i*2,2);
		buffer2[offset+i] = atoi(temp);
	}
	offset+=3;
	for(i=0;i<2;++i)
	{
		memset(temp,0,sizeof temp);
		memcpy(temp,transpack->sTransTime+i*2,2);
		buffer2[offset+i] = atoi(temp);
	}
	offset+=2;
	buffer2[offset++] = nDayTotal % 256;
	buffer2[offset++] = nDayTotal / 256 % 256;
	buffer2[offset++] = nDayTotal / 256 / 256;

	for(i = 0,buffer2[15] = 0;i<15;++i)
		buffer2[15] += buffer2[i];

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer2);

	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer3) != 0)
	{
		transpack->cGetProveFlag=1;
		transpack->cRetryFlag=1;
		// 卡必须重新读取
		m_cardSect[sectno].has_read = 0;
		SET_ERR("读取Mifare1扇区"<<sectno<<"失败");
		return KS_UNCONFIRM;
	}
	if(memcmp(buffer2,buffer3,16)!=0)
	{
		transpack->cGetProveFlag=1;
		transpack->cRetryFlag=1;
		SET_ERR("Mifare1写余额错误");
		return KS_WRITEPURSE;
	}
	// 更新缓存
	memcpy(m_cardSect[sectno].block_buffer,buffer2,16);
	memcpy(m_cardSect[sectno].block_buffer+32,buffer,16);

	return 0;
}
*/

int ks_mf_newcapec_type::GetCurrentDateTime(char *datetime) {
    time_t t;
    t = time(NULL);
    struct tm * tx = localtime(&t);
    sprintf(datetime,"%04d%02d%02d%02d%02d%02d",tx->tm_year+1900,tx->tm_mon+1,tx->tm_mday,
            tx->tm_hour,tx->tm_min,tx->tm_sec);
    return 0;
}

static int des_decrypt_key(unsigned char *key,unsigned char *out_key) {
    des_context des;
    memset(&des,0,sizeof des);
    des_set_key(&des,(byte*)statickey);
    des_decrypt(&des,key,out_key);
    return 0;
}

void ks_mf_newcapec_type::SetMifare1Key(const char *sCipherKey) {
    AuthDLL(sCipherKey, 1);
    SET_ERR("Mifare1Key["<<sCipherKey<<"]");
    return;
}

int ks_mf_newcapec_type::AuthDLL(const char *key,int flag) {
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
            statkey[i]=(byte)ul;
            plain[i]=~plain[i];
            m_mainkey[i]=plain[i]^statkey[i];
        }
    } else
        memcpy(m_mainkey,ucWorkKey,8);

    m_isLoadKey = 1;
    return 0;
}

ks_mf_newcapec_type::~ks_mf_newcapec_type() {
    m_FieldVect.clear();
    m_EFMap.clear();
}

int ks_mf_newcapec_type::initAllCardDef() {
    // 0 扇区
    m_cardinfo.block_info[0].block_used[0] = 0;
    m_cardinfo.block_info[0].block_used[1] = 1;
    m_cardinfo.block_info[0].block_crc[1] = MF_CRC8;
    m_cardinfo.block_info[0].block_used[2] = 1;
    m_cardinfo.block_info[0].block_crc[2] = MF_CRC8;
    // 1 扇区
    m_cardinfo.block_info[1].block_used[0] = 1;
    m_cardinfo.block_info[1].block_crc[0] = MF_CRC8;
    m_cardinfo.block_info[1].block_used[1] = 1;
    m_cardinfo.block_info[1].block_crc[1] = MF_CRC8;
    m_cardinfo.block_info[1].block_used[2] = 1;

    // 2 扇区
    m_cardinfo.block_info[2].block_used[0] = 1;
    m_cardinfo.block_info[2].block_used[1] = 1;
    m_cardinfo.block_info[2].block_used[2] = 1;

    m_FieldVect.clear();

    EF_FIELD EField;
    memset(&EField,0,sizeof(EField));
    EField.unused=1;
    //先初始化为0
    for(int i=0; i<=CF_END; i++)
        m_FieldVect.push_back(EField);

    PERINFO perinfo;
    PUBLICINFO publicinfo;
    PACKAGEINFO packageinfo;
    T_NEWCAPEC_CARD newcapecinfo;

    //应用类型（填充）
    m_FieldVect[CF_APPTYPE].unused=0;
    m_FieldVect[CF_APPTYPE].offset = (byte*)&newcapecinfo.apptype - (byte*)&newcapecinfo;
    m_FieldVect[CF_APPTYPE].length =sizeof(newcapecinfo.apptype);
    m_FieldVect[CF_APPTYPE].fid = 3;
    m_FieldVect[CF_APPTYPE].type=FT_LT_INT32;

    // 收费类别（填充）
    m_FieldVect[CF_FEETYPE].unused=0;
    m_FieldVect[CF_FEETYPE].offset = (byte*)&newcapecinfo.feetype - (byte*)&newcapecinfo;
    m_FieldVect[CF_FEETYPE].length =sizeof(newcapecinfo.feetype);
    m_FieldVect[CF_FEETYPE].fid = 3;
    m_FieldVect[CF_FEETYPE].type=FT_LT_INT32;

    // 客户类别（填充）
    m_FieldVect[CF_CUSTTYPE].unused=0;
    m_FieldVect[CF_CUSTTYPE].offset =(byte*)&newcapecinfo.custtype - (byte*)&newcapecinfo;
    m_FieldVect[CF_CUSTTYPE].length =sizeof(newcapecinfo.custtype);
    m_FieldVect[CF_CUSTTYPE].fid = 3;
    m_FieldVect[CF_CUSTTYPE].type=FT_LT_INT32;

    // 客户号（填充）
    m_FieldVect[CF_CUSTID].unused=0;
    m_FieldVect[CF_CUSTID].offset =(byte*)&newcapecinfo.custid - (byte*)&newcapecinfo;
    m_FieldVect[CF_CUSTID].length =sizeof(newcapecinfo.custid);
    m_FieldVect[CF_CUSTID].fid = 3;
    m_FieldVect[CF_CUSTID].type=FT_LT_INT32;

    // 证件类型（填充）
    m_FieldVect[CF_IDTYPE].unused=0;
    m_FieldVect[CF_IDTYPE].offset =(byte*)&newcapecinfo.idtype - (byte*)&newcapecinfo;
    m_FieldVect[CF_IDTYPE].length =sizeof(newcapecinfo.idtype);
    m_FieldVect[CF_IDTYPE].fid = 3;
    m_FieldVect[CF_IDTYPE].type=FT_LT_INT32;

    // 充值交易次数（填充）
    m_FieldVect[CF_DPSCNT].unused=0;
    m_FieldVect[CF_DPSCNT].offset =(byte*)&newcapecinfo.dpscnt - (byte*)&newcapecinfo;
    m_FieldVect[CF_DPSCNT].length =sizeof(newcapecinfo.dpscnt);
    m_FieldVect[CF_DPSCNT].fid = 3;
    m_FieldVect[CF_DPSCNT].type=FT_LT_INT32;

    // 交易日期(最后一次交易)（填充）
    m_FieldVect[CF_TRANSDATE].unused=0;
    m_FieldVect[CF_TRANSDATE].offset =(byte*)&newcapecinfo.transdate - (byte*)&newcapecinfo;
    m_FieldVect[CF_TRANSDATE].length =sizeof(newcapecinfo.transdate);
    m_FieldVect[CF_TRANSDATE].fid = 3;
    m_FieldVect[CF_TRANSDATE].type=FT_LT_INT32;

    // 日消费累计限额（填充）
    m_FieldVect[CF_DAYMAXAMT].unused=0;
    m_FieldVect[CF_DAYMAXAMT].offset =(byte*)&newcapecinfo.daymaxamt - (byte*)&newcapecinfo;
    m_FieldVect[CF_DAYMAXAMT].length =sizeof(newcapecinfo.daymaxamt);
    m_FieldVect[CF_DAYMAXAMT].fid = 3;
    m_FieldVect[CF_DAYMAXAMT].type=FT_LT_INT32;

    // 发行方标志（填充）
    m_FieldVect[CF_PUBLISHID].unused=0;
    m_FieldVect[CF_PUBLISHID].offset = (byte*)&newcapecinfo.publishid - (byte*)&newcapecinfo;
    m_FieldVect[CF_PUBLISHID].length =sizeof(newcapecinfo.publishid);
    m_FieldVect[CF_PUBLISHID].fid = 3;
    m_FieldVect[CF_PUBLISHID].type=FT_LT_INT32;

    //显示卡号（填充）
    m_FieldVect[CF_SHOWCARDNO].unused=0;
    m_FieldVect[CF_SHOWCARDNO].offset =(byte*) &newcapecinfo.showcardno-(byte*)&newcapecinfo;
    m_FieldVect[CF_SHOWCARDNO].length = sizeof(newcapecinfo.showcardno);
    m_FieldVect[CF_SHOWCARDNO].fid = 3;
    m_FieldVect[CF_SHOWCARDNO].type=FT_LT_INT32;

    //补助批次号（填充）
    m_FieldVect[CF_SUBSIDYNO].unused=0;
    m_FieldVect[CF_SUBSIDYNO].offset =(byte*)&newcapecinfo.subsidyno-(byte*)&newcapecinfo;
    m_FieldVect[CF_SUBSIDYNO].length = sizeof(newcapecinfo.subsidyno);
    m_FieldVect[CF_SUBSIDYNO].fid = 3;
    m_FieldVect[CF_SUBSIDYNO].type=FT_LT_INT32;

    //卡结构版本（应用版本）（填充）
    m_FieldVect[CF_CARDSTRUCTVER].unused=0;
    m_FieldVect[CF_CARDSTRUCTVER].offset =(byte*) &newcapecinfo.cardstruct-(byte*)&newcapecinfo;
    m_FieldVect[CF_CARDSTRUCTVER].length = sizeof(newcapecinfo.cardstruct);
    m_FieldVect[CF_CARDSTRUCTVER].fid = 3;
    m_FieldVect[CF_CARDSTRUCTVER].type=FT_LT_INT32;

    //校区代码（填充）
    m_FieldVect[CF_SCHOOLCODE].unused=0;
    m_FieldVect[CF_SCHOOLCODE].offset =(byte*) &newcapecinfo.schoolcode-(byte*)&newcapecinfo;
    m_FieldVect[CF_SCHOOLCODE].length = sizeof(newcapecinfo.schoolcode);
    m_FieldVect[CF_SCHOOLCODE].fid = 3;
    m_FieldVect[CF_SCHOOLCODE].type=FT_LT_INT32;

    // 卡用途（初始化9）
    // 卡版本号（初始化1<<4）
    //卡号
    m_FieldVect[CF_CARDNO].unused=0;
    m_FieldVect[CF_CARDNO].offset = perinfo.cardno-(byte*)&perinfo;
    m_FieldVect[CF_CARDNO].length = sizeof(perinfo.cardno);
    m_FieldVect[CF_CARDNO].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDNO].blockno,m_FieldVect[CF_CARDNO].offset);
    m_FieldVect[CF_CARDNO].type=FT_INT24;


    //单位标志，部门代码
    m_FieldVect[CF_DEPTCODE].unused=0;
    m_FieldVect[CF_DEPTCODE].offset = &perinfo.deptcode - (byte*)&perinfo;
    m_FieldVect[CF_DEPTCODE].length = sizeof(perinfo.deptcode);
    m_FieldVect[CF_DEPTCODE].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_DEPTCODE].blockno,m_FieldVect[CF_DEPTCODE].offset);
    m_FieldVect[CF_DEPTCODE].type=FT_INT8;

    //卡批次号
    m_FieldVect[CF_BATCHNO].unused=0;
    m_FieldVect[CF_BATCHNO].offset = &perinfo.cardbatchno - (byte*)&perinfo;
    m_FieldVect[CF_BATCHNO].length = sizeof(perinfo.cardbatchno);
    m_FieldVect[CF_BATCHNO].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_BATCHNO].blockno,m_FieldVect[CF_BATCHNO].offset);
    m_FieldVect[CF_BATCHNO].type=FT_INT8;

    //卡批次序号
    m_FieldVect[CF_BATCHSEQNO].unused=0;
    m_FieldVect[CF_BATCHSEQNO].offset = perinfo.cardseqno - (byte*)&perinfo;
    m_FieldVect[CF_BATCHSEQNO].length = sizeof(perinfo.cardseqno);
    m_FieldVect[CF_BATCHSEQNO].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_BATCHSEQNO].blockno,m_FieldVect[CF_BATCHSEQNO].offset);
    m_FieldVect[CF_BATCHSEQNO].type=FT_INT16;

    //性别
    m_FieldVect[CF_SEX].unused=0;
    m_FieldVect[CF_SEX].offset = &perinfo.sex - (byte*)&perinfo;
    m_FieldVect[CF_SEX].length = sizeof(perinfo.sex);
    m_FieldVect[CF_SEX].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_SEX].blockno,m_FieldVect[CF_SEX].offset);
    m_FieldVect[CF_SEX].type=FT_INT8;

    // 发卡日
    m_FieldVect[CF_STARTDATE].unused=0;
    m_FieldVect[CF_STARTDATE].offset = perinfo.publishdate-(byte*)&perinfo;
    m_FieldVect[CF_STARTDATE].length = sizeof(perinfo.publishdate);
    m_FieldVect[CF_STARTDATE].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_STARTDATE].blockno,m_FieldVect[CF_STARTDATE].offset);
    m_FieldVect[CF_STARTDATE].type=FT_COMPACT_DATE;

    // 民族代码
    m_FieldVect[CF_NATIONAL].unused=0;
    m_FieldVect[CF_NATIONAL].offset = &perinfo.nationcode-(byte*)&perinfo;
    m_FieldVect[CF_NATIONAL].length = sizeof(perinfo.nationcode);
    m_FieldVect[CF_NATIONAL].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_NATIONAL].blockno,m_FieldVect[CF_NATIONAL].offset);
    m_FieldVect[CF_NATIONAL].type=FT_INT8;

    //卡类型
    m_FieldVect[CF_CARDTYPE].unused=0;
    m_FieldVect[CF_CARDTYPE].offset = &(perinfo.cardtype) - (byte*)&perinfo;
    m_FieldVect[CF_CARDTYPE].length = sizeof(perinfo.cardtype);
    m_FieldVect[CF_CARDTYPE].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDTYPE].blockno,m_FieldVect[CF_CARDTYPE].offset);
    m_FieldVect[CF_CARDTYPE].type=FT_INT8;

    //卡状态
    m_FieldVect[CF_CARDSTATUS].unused=0;
    m_FieldVect[CF_CARDSTATUS].offset = &perinfo.cardstatus - (byte*)&perinfo;
    m_FieldVect[CF_CARDSTATUS].length = sizeof(perinfo.cardstatus);
    m_FieldVect[CF_CARDSTATUS].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDSTATUS].blockno,m_FieldVect[CF_CARDSTATUS].offset);
    m_FieldVect[CF_CARDSTATUS].type=FT_INT8;

    //餐消费限额，填0
    m_FieldVect[CF_SINGLEMAXAMT].unused=0;
    m_FieldVect[CF_SINGLEMAXAMT].offset = (perinfo.tradequota) - (byte*)&perinfo;
    m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(perinfo.tradequota);
    m_FieldVect[CF_SINGLEMAXAMT].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_SINGLEMAXAMT].blockno,m_FieldVect[CF_SINGLEMAXAMT].offset);
    m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT16;

    //卡密码
    m_FieldVect[CF_CARDPWD].unused=0;
    m_FieldVect[CF_CARDPWD].offset = perinfo.tradepin - (byte*)&perinfo;
    m_FieldVect[CF_CARDPWD].length = sizeof(perinfo.tradepin);
    m_FieldVect[CF_CARDPWD].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDPWD].blockno,m_FieldVect[CF_CARDPWD].offset);
    m_FieldVect[CF_CARDPWD].type=FT_BCD;
    //m_FieldVect[CF_CARDPWD].rw=RW_W;

    //黑名单版本
    m_FieldVect[CF_CARDVERNO].unused=0;
    m_FieldVect[CF_CARDVERNO].offset = perinfo.blackver - (byte*)&perinfo;
    m_FieldVect[CF_CARDVERNO].length = sizeof(perinfo.blackver);
    m_FieldVect[CF_CARDVERNO].fid = 0;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDVERNO].blockno,m_FieldVect[CF_CARDVERNO].offset);
    m_FieldVect[CF_CARDVERNO].type=FT_INT48;

    //有效期
    m_FieldVect[CF_EXPIREDATE].unused=0;
    m_FieldVect[CF_EXPIREDATE].offset = perinfo.expiredate-(byte*)&perinfo;
    m_FieldVect[CF_EXPIREDATE].length = sizeof(perinfo.expiredate);
    m_FieldVect[CF_EXPIREDATE].fid=0;
    EASY_SET_BLOCK(m_FieldVect[CF_EXPIREDATE].blockno,m_FieldVect[CF_EXPIREDATE].offset);
    m_FieldVect[CF_EXPIREDATE].type=FT_COMPACT_DATE;

    // 第一扇区

    //卡余额
    m_FieldVect[CF_CARDBAL].unused=0;
    m_FieldVect[CF_CARDBAL].offset = packageinfo.balance-(byte*)&packageinfo;
    m_FieldVect[CF_CARDBAL].length =sizeof(packageinfo.balance);
    m_FieldVect[CF_CARDBAL].fid=1;
    EASY_SET_BLOCK(m_FieldVect[CF_CARDBAL].blockno,m_FieldVect[CF_CARDBAL].offset);
    m_FieldVect[CF_CARDBAL].type=FT_INT24;
    //m_FieldVect[CF_CARDBAL].rw=RW_R;

    // 补助钱包
    m_FieldVect[CF_SUBSIDYBAL].unused=0;
    m_FieldVect[CF_SUBSIDYBAL].offset = (packageinfo.subsidyamt_totalamt) - (byte*)&packageinfo;
    m_FieldVect[CF_SUBSIDYBAL].length = sizeof(packageinfo.subsidyamt_totalamt);
    m_FieldVect[CF_SUBSIDYBAL].fid = 1;
    EASY_SET_BLOCK(m_FieldVect[CF_SUBSIDYBAL].blockno,m_FieldVect[CF_SUBSIDYBAL].offset);
    m_FieldVect[CF_SUBSIDYBAL].type=FT_SUBSIDYBAL;

    // 总额
    m_FieldVect[CF_TOTALAMT].unused=0;
    m_FieldVect[CF_TOTALAMT].offset = (packageinfo.subsidyamt_totalamt) - (byte*)&packageinfo;
    m_FieldVect[CF_TOTALAMT].length = sizeof(packageinfo.subsidyamt_totalamt);
    m_FieldVect[CF_TOTALAMT].fid = 1;
    EASY_SET_BLOCK(m_FieldVect[CF_TOTALAMT].blockno,m_FieldVect[CF_TOTALAMT].offset);
    m_FieldVect[CF_TOTALAMT].type=FT_TOTALAMT;

    //消费次数
    m_FieldVect[CF_PAYCNT].unused=0;
    m_FieldVect[CF_PAYCNT].offset =packageinfo.tradecnt-(byte*)&packageinfo;
    m_FieldVect[CF_PAYCNT].length =sizeof(packageinfo.tradecnt);
    m_FieldVect[CF_PAYCNT].fid=1;
    EASY_SET_BLOCK(m_FieldVect[CF_PAYCNT].blockno,m_FieldVect[CF_PAYCNT].offset);
    m_FieldVect[CF_PAYCNT].type=FT_INT16;
    //m_FieldVect[CF_PAYCNT].rw=RW_R;

    // 宏冲日期（保留）
    // 领款流水（保留）

    // 本日
    m_FieldVect[CF_TODAY].unused=0;
    m_FieldVect[CF_TODAY].offset = &(packageinfo.today) - (byte*)&packageinfo;
    m_FieldVect[CF_TODAY].length = sizeof(packageinfo.today);
    m_FieldVect[CF_TODAY].fid = 1;
    EASY_SET_BLOCK(m_FieldVect[CF_TODAY].blockno,m_FieldVect[CF_TODAY].offset);
    m_FieldVect[CF_TODAY].type=FT_BCD;

    // 日消费额累计
    m_FieldVect[CF_DAYSUMAMT].unused=0;
    m_FieldVect[CF_DAYSUMAMT].offset = (packageinfo.dayamt) - (byte*)&packageinfo;
    m_FieldVect[CF_DAYSUMAMT].length = sizeof(packageinfo.dayamt);
    m_FieldVect[CF_DAYSUMAMT].fid = 1;
    EASY_SET_BLOCK(m_FieldVect[CF_DAYSUMAMT].blockno,m_FieldVect[CF_DAYSUMAMT].offset);
    m_FieldVect[CF_DAYSUMAMT].type=FT_INT24;

    // 餐消费额累计
    m_FieldVect[CF_MEALAMT].unused=0;
    m_FieldVect[CF_MEALAMT].offset = (packageinfo.mealamt) - (byte*)&packageinfo;
    m_FieldVect[CF_MEALAMT].length = sizeof(packageinfo.mealamt);
    m_FieldVect[CF_MEALAMT].fid = 1;
    EASY_SET_BLOCK(m_FieldVect[CF_MEALAMT].blockno,m_FieldVect[CF_MEALAMT].offset);
    m_FieldVect[CF_MEALAMT].type=FT_INT24;

    // 第二扇区
    //姓名
    m_FieldVect[CF_NAME].unused=0;
    m_FieldVect[CF_NAME].offset = publicinfo.custname - (byte*)&publicinfo;
    m_FieldVect[CF_NAME].length = sizeof(publicinfo.custname);
    m_FieldVect[CF_NAME].fid = 2;
    EASY_SET_BLOCK(m_FieldVect[CF_NAME].blockno,m_FieldVect[CF_NAME].offset);
    m_FieldVect[CF_NAME].type=FT_ANSI;

    //学工号
    m_FieldVect[CF_STUEMPNO].unused=0;
    m_FieldVect[CF_STUEMPNO].offset = publicinfo.stuempno - (byte*)&publicinfo;
    m_FieldVect[CF_STUEMPNO].length = sizeof(publicinfo.stuempno);
    m_FieldVect[CF_STUEMPNO].fid = 2;
    EASY_SET_BLOCK(m_FieldVect[CF_STUEMPNO].blockno,m_FieldVect[CF_STUEMPNO].offset);
    m_FieldVect[CF_STUEMPNO].type=FT_STUEMPNO;

    //身份证号 + 图书证条码 新开普没有使用，所以都用来存贮 ASCII身份证号
    m_FieldVect[CF_IDNO].unused=0;
    m_FieldVect[CF_IDNO].offset = publicinfo.idno - (byte*)&publicinfo;
    m_FieldVect[CF_IDNO].length = sizeof(publicinfo.idno);
    ZERO_BLOCK(m_FieldVect[CF_IDNO].blockno);
    SET_BLOCK(m_FieldVect[CF_IDNO].blockno,1);
    SET_BLOCK(m_FieldVect[CF_IDNO].blockno,2);
    m_FieldVect[CF_IDNO].fid=2;
    m_FieldVect[CF_IDNO].type=FT_BCD;

    // 图书证条码 ----> 证件类型
    m_FieldVect[CF_LIBNO].unused=0;
    m_FieldVect[CF_LIBNO].offset = publicinfo.libno - (byte*)&publicinfo;
    m_FieldVect[CF_LIBNO].length = sizeof(publicinfo.libno);
    EASY_SET_BLOCK(m_FieldVect[CF_LIBNO].blockno,m_FieldVect[CF_LIBNO].offset);
    m_FieldVect[CF_LIBNO].fid=2;
    m_FieldVect[CF_LIBNO].type=FT_ANSI;

    m_EFMap.clear();

    EFBUF efbuf;

    efbuf.FileSize=sizeof(PERINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[0]=efbuf;

    efbuf.FileSize=sizeof(PUBLICINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[1]=efbuf;

    efbuf.FileSize=sizeof(PACKAGEINFO);
    efbuf.ReadRight=FRR_FREE;
    efbuf.WriteRight=FRW_MAC;
    m_EFMap[2]=efbuf;

    return 0;
}

int ks_mf_newcapec_type::checkCardType(int ct) {
    switch(ct) {
    case KS_MFCARD:
    case KS_FIXCARD:
        m_CardTypeCode = 0x0200;
        return 0;
    case KS_CPUCARD:
        m_CardTypeCode = 0x0400;
        return 0;
    default:
        return -1;
    }
}

int ks_mf_newcapec_type::GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac) {
    int nRet,sectno,i;
    byte buffer[16];
    byte crc_sum,crc_or;
    IS_LOAD_KEY();

    sectno = 4;
    if(m_cardVer <= 2010) {
        // 充值与消费二合一
        if(this->LoginCardSect(sectno)) {
            SET_ERR("登录钱包扇区错误");
            return KS_LOGINCARD;
        }
        nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno * 4,buffer);
        if(nRet) {
            SET_ERR("读取钱包失败!");
            return KS_READCARD;
        }
        for(i = 0,crc_sum = 0,crc_or = 0; i < 15 ; ++i) {
            crc_sum += buffer[i];
            crc_or |= buffer[i];
        }
        if(buffer[15] != crc_sum || crc_or == 0) {
            SET_ERR("钱包格式错误");
            return -1;
        }
        int cnt = buffer[3] * 256 + buffer[4];
        if(cnt != CardCnt) {
            SET_ERR("期望交易次数["<<CardCnt<<"]实际交易次数["<<cnt<<"]");
            return -1;
        }
        SET_ERR("卡钱包交易次数相同");
        return 0;
    } else {
        //
        return -1;
    }
}

void ks_mf_newcapec_type::DumpCardBlockData(int sect,int block,BYTE *buf) {
    int i;
    char temp[3]="";
    if(g_dump_file) {
        fprintf(g_dump_file,"sect[%02d],block[%02d][",sect,block);
        for(i = 0; i < 16; ++i) {
            fprintf(g_dump_file,"%02X",buf[i]);
        }
        fprintf(g_dump_file,"]\r\n");
    }
}

int ks_mf_newcapec_type::InitForTrans(ST_TRANSPACK *trans,int trans_type) {
    // TODO : 判断卡余额
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

int KSAPI register_cardtype_op(ks_cardtype_base *&op) {
    op = new ks_mf_newcapec_type();
    return 0;
}