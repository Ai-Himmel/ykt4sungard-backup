#include "ks_mfcard.h"
#include "global_func.h"
#include "des.h"
#include <time.h>
#include <fstream>
//static ks_mfcard_type g_CardType;

static const unsigned char statickey[17]="3230303530313331";



#define ZERO_BLOCK(m) do{ (m)=0; } while(0)
#define SET_BLOCK(m,b) do { (m) |= (1 << (b)); } while(0)
#define CLR_BLOCK(m,b) do { (m) &= (^(1 << (b))); } while(0)
#define ISSET_BLOCK(m,b) (((m) & (1<<(b))) != 0)

#define EASY_SET_BLOCK(m,of) do {int _b=(of)/16;ZERO_BLOCK(m); SET_BLOCK(m,_b); } while(0)

#define IS_LOAD_KEY() do { int r = testLoadKey(); if(r) return r; }while(0)

FILE * ks_mfcard_type::g_dump_file = NULL;
ks_mfcard_type::ks_mfcard_type():CCardType(),m_isLoadKey(0),m_lastLoginSect(MF_MAX_SECTNO),m_keyType(0),m_lldfSect(MF_MAX_SECTNO)
{
	this->set_cardtype_name("ks_mfcard.dll");
	memset(m_initSectMap,'0',sizeof m_initSectMap);
	memset(m_recycleSectMap,'1',sizeof m_recycleSectMap);
	m_mfcard = &m_cardinfo; 
	memset(&m_cardinfo,0,sizeof m_cardinfo);
	memset(&m_cardSect,0,sizeof m_cardSect);
	memset(m_offlinewaterkey,0,sizeof m_offlinewaterkey);
	memset(m_lldfKey,0,sizeof m_lldfKey);
	iPsamPowerOnCnt=0;
	m_secdPackSect = 0;
	m_offlinewater = 0;
	this->m_defaultCardType = KS_MFCARD;
}

void ks_mfcard_type::GetSupportCardType(unsigned int cardTypes[],int &cnt)
{
	int i = 0;
	cardTypes[i++] = 0x0200;
	cardTypes[i++] = 0x0300;
	cardTypes[i++] = 0x0400;
	cardTypes[i++] = 0x0409;
	cnt = i;
}
int ks_mfcard_type::InitCardTypeDLL()
{
	char param[512] = "";
	int maxlen;
	int ret=0;
	
	if(m_license->get_public_int_param("kscardlib.mfcard.maxsect",&m_maxSectNo))
	{
		return -1;
	}
	if(m_license->get_public_int_param("kscardlib.mfcard.minsect",&m_minSectNo))
	{
		return -1;
	}
	maxlen = sizeof(param)-1;
	memset(param,0,sizeof param);
	if(m_license->get_public_param("kscardlib.mfinit.sect",param,maxlen))
	{
		return -1;
	}
	strcpy(m_initSectMap,param);

	memset(param,0,sizeof param);
	if(m_license->get_public_param("kscardlib.mfrecycle.sect",param,maxlen))
	{
		return -1;
	}
	strcpy(m_recycleSectMap,param);

	m_license->get_public_int_param("kscardlib.mfcard.alg",&m_keyAlg);
	m_license->get_public_int_param("kscardlib.mfcard.ver",&m_cardVer);

	if(m_cardVer != 2008 && m_cardVer != 2009 && m_cardVer != 2010)
		return -1;

	m_license->get_public_int_param("kscardlib.mfcard.secdpacksect",&m_secdPackSect);
	m_secdPackSect = (m_secdPackSect>0)?m_secdPackSect:5;

	m_license->get_public_int_param("kscardlib.mfcard.offlinewater",&m_offlinewater);
	m_offlinewater = (m_offlinewater>0)?m_offlinewater:10;

	m_license->get_public_int_param("kscardlib.mfcard.mainsect",&m_mainPackSect);

	m_license->get_public_int_param("kscardlib.mfcard.init.keytype",&ret);
	if(ret == 0)
		m_initKeyType = MF_KEYA;
	else
		m_initKeyType = MF_KEYB;
	
	memset(param,0,sizeof param);
	if(m_license->get_public_param("kscardlib.mfcard.init.loginkey",param,12))
	{
		memset(m_initLoginKey,0xFF,sizeof m_initLoginKey);
	}
	else
	{
		hex2dec(param,12,m_initLoginKey,ret);
	}
	
	memset(param,0,sizeof param);
	if(m_license->get_public_param("kscardlib.mfcard.offlinewaterkey",param,16))
		memset(m_offlinewaterkey,0xFF,sizeof m_offlinewaterkey);
	else
		hex2dec(param,16,m_offlinewaterkey,ret);

	if(m_keyAlg == 2)
	{
		if(m_license->get_public_param("kscardlib.cmcc.enterpricecode",this->strEnterpriceCode_,19))
		{
			SET_ERR("未设置企业ID号");
			return -1;
		}
		if(m_license->get_public_int_param("kscardlib.cmcc.enterprice.appid",&enterpriceAppID_))
		{
			SET_ERR("未设置企业自定义索引号");
			return -1;
		}
	}
	else if(m_keyAlg == 0)
	{
		if(m_license->get_public_int_param("kscardlib.mfcard.keycard",&m_keyType))
		{
			SET_ERR("为设置授权卡类型，默认["<<m_keyType<<"]");
		}
	}
	// 深圳领路达方水控
	if(m_license->get_public_int_param("dlmu.hot.sect",&m_lldfSect))
	{
		m_lldfSect = MF_MAX_SECTNO;
	}
	if(m_lldfSect != MF_MAX_SECTNO)
	{
		if(m_license->get_public_param("dlmu.hot.key",param,16))
		{
			SET_ERR("未设置深圳领路达方水控密钥");
			return -1;
		}
		hex2dec(param,12,this->m_lldfKey,maxlen);
	}
	ret = CCardType::InitCardTypeDLL();
	if(ret)
		return ret;
	initAllCardDef();
	return 0;
}
int ks_mfcard_type::testLoadKey()
{
	if(this->m_keyAlg == 0)
	{
		if(this->m_CardKeys.bLoad ==0 && this->m_isLoadKey == 0)
		{
			SET_ERR("Mifare1密钥未装载");
			return KS_UNAUTH_TERM;
		}
		if(this->m_isLoadKey == 0)
		{
			memset(m_mainkey,0,sizeof m_mainkey);
			memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
			m_isLoadKey = 1;
		}
	}
	return 0;
}
int ks_mfcard_type::testCardExists(char *szCardPhyID)
{
	int nRet;
	unsigned char buffer[16] = {0};
	if(this->m_lastLoginSect >= 0 && this->m_lastLoginSect < MF_MAX_SECTNO)
	{
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,m_lastLoginSect*4,buffer);
	}
	else
	{
		nRet = this->LoginCardSect(0);
	}
	if(nRet)
		return -1;
	strcpy(szCardPhyID,this->m_szCardUID);
	return 0;
}

int ks_mfcard_type::doSuccessRequestCard()
{
	unsigned char decphyno[4];
	int len,i;
	m_lastLoginSect = MF_MAX_SECTNO;
	hex2dec(this->m_szCardUID,8,decphyno,len);
	for(i=0;i<4;++i)
		m_OriginPhyNo[3-i] = decphyno[i];
	for(i = 0;i < MF_MAX_SECTNO;++i)
	{
		memset(m_cardSect[i].block_buffer,0,sizeof m_cardSect[i].block_buffer);
		m_cardSect[i].has_read = 0;
	}
	this->m_lastLoginSect = MF_MAX_SECTNO;
	this->m_defaultCardType = KS_MFCARD;
	return 0;
}

int ks_mfcard_type::doSubRequestCard(char *szCardPhyID)
{
	int nRet=0;
	char phyno[17] = {0};
	nRet=m_Reader->request_card(m_ReaderPara,phyno,KS_MFCARD);
	if(nRet)
	{
		SET_ERR("寻卡错误 "<<m_Reader->GetErrMsg(NULL));
		return nRet;
	}

	if(szCardPhyID)
		strcpy(szCardPhyID,phyno);

	strcpy(m_szCardUID,phyno);
	return doSuccessRequestCard();
}

int ks_mfcard_type::LoadKeysFromKeyCard(const char *sKeyCardPwd)
{
	if(m_keyType == 1)
	{
		// 读取授权卡
		int nRet,i;
		char strphyno[17],temp[16];
		unsigned char keya[6],keyb[6],phyno[8];
		unsigned char buffer[16];
		int sectno,blockno,key_block,key_pos;
		// 需要重新读卡了
		memset(m_szCardUID,0,sizeof(m_szCardUID));
		nRet = m_Reader->request_card(m_ReaderPara,strphyno,KS_MFCARD);
		if(nRet)
		{
			SET_ERR("寻卡错误"<<m_Reader->GetErrMsg(NULL));
			return nRet;
		}

		hex2dec(strphyno,8,phyno,nRet);
		for(i=0;i<4;++i)
			phyno[7-i] = phyno[i];
		memcpy(phyno,phyno+4,4);
		// 读取授权卡
		// 7 扇区
		sectno = 7;
		memcpy(keya,phyno,4);
		sprintf(temp,"%02X",sectno);
		memcpy(keya+4,temp,2);
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
		if(nRet)
		{
			SET_ERR("授权卡登录扇区错误");
			return nRet;
		}
		blockno = sectno * 4 + 1;
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
		if(nRet)
		{
			SET_ERR("读取授权卡扇区失败");
			return nRet;
		}
		key_block = buffer[6]-'0';
		key_pos = buffer[7] - '0';


		// 15 扇区
		sectno=15;
		memcpy(keya,phyno,4);
		sprintf(temp,"%02X",sectno);
		memcpy(keya+4,temp,2);
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,keya);
		if(nRet)
		{
			SET_ERR("授权卡登录扇区错误");
			return nRet;
		}
		
		blockno = sectno * 4 + 2;
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
		if(nRet)
		{
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
		if(nRet)
		{
			SET_ERR("授权卡登录扇区错误");
			return nRet;
		}
		blockno = 4 * sectno + key_block;
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
		if(nRet)
		{
			SET_ERR("读取授权卡扇区失败");
			return nRet;
		}
		memcpy(m_mainkey,buffer+key_pos,8);
		m_isLoadKey = 1;
		return 0;
	}
	else
	{
		int ret;
		ret = CCardType::LoadKeysFromKeyCard(sKeyCardPwd);
		if(ret)
		{
			return ret;
		}
		if(m_keyAlg==0) // 采用老的模式
		{
			memset(m_mainkey,0,sizeof m_mainkey);
			memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
			m_isLoadKey = 1;
		}
		return 0;
	}
}
int ks_mfcard_type::PublishKeyCard (unsigned char* sMasterKey,const char* sPin)
{
	if(m_keyType == 1)
	{
		SET_ERR("不支持发行M1授权卡");
		return KS_NOTSUPPORT;
	}
	else
	{
		return CCardType::PublishKeyCard(sMasterKey,sPin);
	}
}
int ks_mfcard_type::SetKeyCard(ks_cardtype_base *c)
{
	int ret;
	ret = CCardType::SetKeyCard(c);
	if(ret)
		return ret;
	if(m_keyAlg==0) // 采用老的模式
	{
		memset(m_mainkey,0,sizeof m_mainkey);
		memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
		m_isLoadKey = 1;
	}
	return 0;
}
int ks_mfcard_type::VerifyPin(const char* sPin)
{
	return 0;
}
void ks_mfcard_type::Caloffwaterkey(unsigned char *serialno,int sectno,unsigned char *mkey,unsigned char *keya)
{
	int i,j;
	unsigned char plain[6];
	memcpy(plain,serialno,4);
	plain[4] = sectno;
	plain[5] = ~plain[4];

	for(i = 0;i < 6; ++i)
	{
		keya[i] = plain[i];
		for(j = 0;j < 6;++j)
			keya[i] ^= plain[j] ^ mkey[j];
	}
}
int ks_mfcard_type::InitUserCard(const char *sShowCardNo)
{
	int i,j,block,nRet;
	byte keya[6],keyb[6],buffer[16],ctrlbit[4],keya_ro_ctrlbit[4];
	byte init_keya[6],data_buffer[16];
	char datetime[20]="";
	char temp[10] = "";
	char str_keyA[13]="";
	char str_keyB[13]="";
	char str_Phycardid[10]="";
	dec2hex(m_OriginPhyNo,4,str_Phycardid);
	IS_LOAD_KEY();

	if(this->RequestCard(NULL))
	{
		SET_ERR("请放卡");
		return KS_REQUESTCARD;
	}
	memcpy(init_keya,m_initLoginKey,6);
	memcpy(ctrlbit,MF1_INIT_CTRLBIT,4);
	memcpy(keya_ro_ctrlbit,MF1_KEYA_RO_CTRLBIT,4);
	if(CalcMFSectKey(0,&(m_cardSect[0])))
	{
		SET_ERR("初始化Mifare1扇区，计算keyb失败");
		return KS_LOGINCARD;
	}
	memcpy(keyb,m_cardSect[0].key,6);

	m_lastLoginSect = MF_MAX_SECTNO;
	for(i=m_minSectNo;i< m_maxSectNo;++i)
	{
		// 不初始化
		if(m_initSectMap[i] == '0') continue;
		if(CalcCardKeyA(i,&(m_cardSect[i])))
		{
			SET_ERR("初始化Mifare1扇区["<<i<<"]计算keya失败");
			return KS_LOGINCARD;
		}
		memcpy(keya,m_cardSect[i].key,6);
		memcpy(buffer,keya,6);
		// 0 扇区， keya 只读 keyb 可读可写
		if(i == 0)
			memcpy(buffer+6,keya_ro_ctrlbit,4);
		else // 其它扇区 keya,keyb 可读可写，但keyb 可以修改密钥，keya不行
			memcpy(buffer+6,ctrlbit,4);
		memcpy(buffer+10,keyb,6);
		dec2hex(keya,6,str_keyA);
		dec2hex(keyb,6,str_keyB);
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,m_initKeyType,init_keya);
		if(nRet)
		{
			if(RequestCard(NULL))
			{
				SET_ERR("初始化Mifare1扇区["<<i<<"]登录失败");
				return KS_LOGINCARD;
			}
			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
			if(nRet)
			{
				SET_ERR("初始化Mifare1扇区["<<i<<"],无法初始化，可能已被使用！");
				return KS_LOGINCARD;
			}
			// 可以登录，应该是已经被初始化
			continue;
		}
		else
		{
			// 需要写卡钱包类容
			for(block=0;block < 3;++block)
			{
				if(i == 3) // 钱包索引
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
				}
			}
			nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
			if(nRet)
			{
				SET_ERR("初始化扇区["<<i<<"]写密钥失败，请重试");
				return KS_WRITECARD;
			}
		}
	}
	return 0;
}

int ks_mfcard_type::RestoreFactorySettings()
{
	int i,j,nRet;
	byte keya[6],keyb[6],buffer[16],origin_ctrlbit[4];
	byte init_keya[6],buffer2[16];

	IS_LOAD_KEY();

	if(this->RequestCard(NULL))
	{
		SET_ERR("请放卡");
		return KS_REQUESTCARD;
	}
	memcpy(init_keya,m_initLoginKey,6);
	if(this->m_initKeyType == MF_KEYA)
	{
		memcpy(origin_ctrlbit,MF1_ORIGIN_CTRLBIT,4);
	}
	else
	{
		memcpy(origin_ctrlbit,MF1_INIT_CTRLBIT,4);
	}
	if(CalcMFSectKey(0,&(m_cardSect[0])))
	{
		SET_ERR("初始化Mifare1扇区，计算keyb失败");
		return KS_LOGINCARD;
	}
	memcpy(keyb,m_cardSect[0].key,6);

	memcpy(buffer,init_keya,6);
	memcpy(buffer+6,origin_ctrlbit,4);
	memcpy(buffer+10,init_keya,6);
	m_lastLoginSect = MF_MAX_SECTNO;
	for(i=m_minSectNo;i< m_maxSectNo;++i)
	{
		// 不回收
		if(m_recycleSectMap[i] == '0') continue;

		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
		if(nRet)
		{
			if(RequestCard(NULL))
			{
				SET_ERR("初始化Mifare1扇区["<<i<<"]登录失败");
				return KS_LOGINCARD;
			}
			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,init_keya);
			if(nRet)
			{
				SET_ERR("初始化Mifare1扇区["<<i<<"],无法回收，可能已被使用！");
				return KS_LOGINCARD;
			}
			// 可以登录，应该是已经被初始化
			continue;
		}
		else
		{
			for(j = 0;j<3;++j)
			{
				if(i == 0 && j == 0) continue; // 0 扇区 0 块 不用写
				memset(buffer2,0,sizeof buffer2);
				nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+j,buffer2);
				if(nRet)
				{
					SET_ERR("初始化扇区["<<i<<"]写数据失败，请重试");
					return KS_WRITECARD;
				}
			}
			nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
			if(nRet)
			{
				SET_ERR("初始化扇区["<<i<<"]写密钥失败，请重试");
				return KS_WRITECARD;
			}
		}
	}
	return 0;
}
int ks_mfcard_type::GetDpsCnt()
{
	return 0;
}
int ks_mfcard_type::GetPayCnt()
{
	return 0;
}
int ks_mfcard_type::GetBalance()
{
	return 0;
}
int ks_mfcard_type::GetRandomNum(byte *uRandomNum)
{
	return 0;
}
unsigned char* ks_mfcard_type::PbocDiverKey( unsigned char cardno[9], unsigned char key_in[17], unsigned char key_out[17] )
{
	return NULL;
}
int ks_mfcard_type::CalcSessionKey(unsigned char *ucRandom,unsigned char *ucKey,unsigned char *ucSessionKey)
{
	return 0;
}
int ks_mfcard_type::EncryptKey(const unsigned char *uKey,int nKeyLen,unsigned char *uData,int iDataLen,unsigned char *uOutData,int& iOutLen)
{
	return 0;
}
int ks_mfcard_type::CalcMac(unsigned char *uRandom,unsigned char *uKey,int nKeyLen,const unsigned char *uMacData,int iMacDataLen,unsigned char *uMac)
{
	return 0;
}
int ks_mfcard_type::CalcSafeMac4Sam(ks_cardtype_base *cardtype,const char *szCmdbuf,char *szMac)
{
	return 0;
}
int ks_mfcard_type::CalcSafeMac(const char* szCmdBuf,char *szMac)
{
	return 0;
}
int ks_mfcard_type::CalcKeyFromSAMKeyA(unsigned char *cipherData)
{
	int i,ret;
	char szCmd[256];
	ks_cpu_cmd_t cmd;
	unsigned char uResp[256];
	unsigned char sPlain[8];
	unsigned char uRespLen;
	static unsigned char prePhyNo[4] = {0};
	static unsigned char preCipherData[16] = {0};
	if(memcmp(prePhyNo,m_OriginPhyNo,4) == 0)
	{
		memcpy(cipherData,preCipherData,8);
		return 0;
	}
	for(i = 0; i < 4; i++)
	{
		sPlain[i] = m_OriginPhyNo[i];
		sPlain[i+4] = ~m_OriginPhyNo[i];
	}

	byte rlen,rbuff[256]={0};
	byte ucRespData[256]={0};
	//m_PSAMReaderPara->cpuport=1;
	//上电复位
	ret = m_PSAMCardType->ResetPSAM();
	if(ret)
	{
		return ret;
	}
	// select dir 
	//\x00\xA4\x00\x00\x02\xDF\x04
	//sprintf(szCmd,"00A4000002DF04");
	//ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
	ret=m_PSAMCardType->selectADFBySFI("DF04");
	if(ret)
	{
		SET_ERR(this->GetLastErrMsg(NULL));
		return ret;
	}
	// delivery key
	sprintf(szCmd,"801A270208%s",statickey);
	ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
	if(ret)
	{
		SET_ERR(this->GetLastErrMsg(NULL));
		return ret;
	}
	
	// cipher data
	memset(szCmd,0,sizeof szCmd);
	sprintf(szCmd,"80FA000008");
	cmd.send_len = strlen(szCmd);
	dec2hex(sPlain,8,szCmd+cmd.send_len);

	ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
	if(ret)
	{
		SET_ERR(this->GetLastErrMsg(NULL));
		return ret;
	}
	// get response
	memcpy(prePhyNo,m_OriginPhyNo,4);
	memcpy(cipherData,uResp,8);
	memcpy(preCipherData,cipherData,8);
	return 0;
}
int ks_mfcard_type::CalcKeyFromSAMKeyB(unsigned char *cipherData)
{
	int i,ret;
	char szCmd[256];
	ks_cpu_cmd_t cmd;
	unsigned char uResp[256];
	unsigned char sPlain[8];
	unsigned char uRespLen;
	static unsigned char prePhyNo[4] = {0};
	static unsigned char preCipherData[16] = {0};
	if(memcmp(prePhyNo,m_OriginPhyNo,4) == 0)
	{
		memcpy(cipherData,preCipherData,8);
		return 0;
	}

	for(i = 0; i < 4; i++)
	{
		sPlain[i] = m_OriginPhyNo[i];
		sPlain[i+4] = ~m_OriginPhyNo[i];
	}

	byte rlen,rbuff[256]={0};
	byte ucRespData[256]={0};
	
	//m_PSAMReaderPara->cpuport=1;
	//上电复位
	ret = m_PSAMCardType->ResetPSAM();
	if(ret)
	{
		return ret;
	}
	// select dir 
	//\x00\xA4\x00\x00\x02\xDF\x04
	//sprintf(szCmd,"00A4000002DF04");
	//ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
	ret=m_PSAMCardType->selectADFBySFI("DF04");
	if(ret)
	{
		SET_ERR(this->GetLastErrMsg(NULL));
		return ret;
	}
	// delivery key
	sprintf(szCmd,"801A270108%s",statickey);
	ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
	if(ret)
	{
		SET_ERR(this->GetLastErrMsg(NULL));
		return ret;
	}
	
	// cipher data
	memset(szCmd,0,sizeof szCmd);
	sprintf(szCmd,"80FA000008");
	cmd.send_len = strlen(szCmd);
	dec2hex(sPlain,8,szCmd+cmd.send_len);

	ret = m_PSAMCardType->Adpu4HexSAM(szCmd,strlen(szCmd),uResp,uRespLen);
	if(ret)
	{
		SET_ERR(this->GetLastErrMsg(NULL));
		return ret;
	}
	// get response
	
	memcpy(prePhyNo,m_OriginPhyNo,4);
	memcpy(cipherData,uResp,8);
	memcpy(preCipherData,cipherData,8);

	return 0;
}

int ks_mfcard_type::CalcCardKeyA(int sectno,mf_sect_t *sect)
{
	static byte presentCardNo[4] = "";
	static byte presentKey[6]="";

	if(sectno == 0)
	{
		memcpy(sect->key,"\x01\x02\x03\x04\x05\x06",6);
		sect->key_type = MF_KEYA;
		return 0;
	}
	if (m_offlinewater !=0 && sectno == m_offlinewater)			// 脱机水控扇区号
	{
		Caloffwaterkey(m_OriginPhyNo,sectno,m_offlinewaterkey,sect->key);
		sect->key_type = MF_KEYA;
		return 0;
	}
	if(memcmp(presentCardNo,this->m_OriginPhyNo,4))
	{
		unsigned char sCipher[17]; 
		unsigned int  startpos = 0;
		if(m_keyAlg == 0) // 
		{
			memset(sCipher,0,sizeof sCipher);
			if(encryptKeyA(this->m_mainkey,sCipher))
			{
				SET_ERR("计算密钥KEYB错误");
				return -1;
			}
		}
		else if(m_keyAlg == 1)
		{
			memset(sCipher,0,sizeof sCipher);
			if(CalcKeyFromSAMKeyA(sCipher))
			{
				SET_ERR("PSAM卡计算密钥错误");
				return -1;
			}
		}
		else if(m_keyAlg == 2)
		{
			memset(sCipher,0,sizeof sCipher);
			if(CalcKeyFromSAMKeyACMCC(sCipher))
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
int ks_mfcard_type::FormatCard()
{
	return -1;
}
int ks_mfcard_type::ReadBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData)
{
	return 0;
}
int ks_mfcard_type::ReadBinaryFile4Mac(byte ucSFI,byte ucOffset,byte ucLength,byte *ucRes)
{
	return 0;
}
int ks_mfcard_type::UpdateBinaryFile(byte ucSFI,byte ucOffset,byte ucLength,byte *ucData)
{
	return 0;
}

int ks_mfcard_type::CalcMFSectKey(int sectno,mf_sect_t *sect)
{
	unsigned int  i;
	unsigned char sPlain[9];
	unsigned char sCipher[17];
	unsigned int  startpos=0;
	static byte presentKey[6]="";
	if((sectno == m_lldfSect || sectno == m_lldfSect+1) && m_lldfSect != MF_MAX_SECTNO)
	{
		memcpy(sect->key,this->m_lldfKey,6);
		if(memcmp(sect->key,"\xFF\xFF\xFF\xFF\xFF\xFF",6)==0)
		sect->key_type = MF_KEYA;
		else
			sect->key_type = MF_KEYB;
	}
	else
	{
		if(memcmp(this->m_OriginPhyNo,m_presentPhyNo,4))
		{
			if(m_keyAlg == 0)
			{
				memset(sCipher,0,sizeof sCipher);
				if(encryptKeyB(this->m_mainkey,sCipher))
				{
					SET_ERR("计算密钥KEYB错误");
					return -1;
				}
			}
			else if(m_keyAlg == 1)
			{
				memset(sCipher,0,sizeof sCipher);
				if(CalcKeyFromSAMKeyB(sCipher))
				{
					SET_ERR("PSAM卡计算密钥错误");
					return -1;
				}
			}
			else if(m_keyAlg == 2)
			{
				memset(sCipher,0,sizeof sCipher);
				if(CalcKeyFromSAMKeyBCMCC(sCipher))
				{
					SET_ERR("PSAM卡计算密钥错误");
					return -1;
				}
			}
			else
				return -1;
			memcpy(sCipher+8,sCipher,8);
			startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
			memcpy(sect->key,sCipher+startpos,6);
			sect->key_type = MF_KEYB;
			memcpy(presentKey,sect->key,6);
			memcpy(m_presentPhyNo,this->m_OriginPhyNo,4);
		}
		else
		{
			memcpy(sect->key,presentKey,6);
			sect->key_type = MF_KEYB;
		}
	}
	return 0;
}

int ks_mfcard_type::encryptKeyA(unsigned char *key,unsigned char *sCipher)
{
	unsigned int i;
	unsigned char sPlain[9];	

	des_context ctx;
	memset(sPlain, 0, sizeof(sPlain));	

	for(i = 0; i < 4; i++)
	{
		sPlain[i] = m_OriginPhyNo[i];
		sPlain[i+4] = ~m_OriginPhyNo[i];
	}
	
	memset(&ctx,0,sizeof ctx);
	des_set_key(&ctx,key);
	des_encrypt(&ctx,sPlain,sCipher);
	return 0;
}
int ks_mfcard_type::encryptKeyB(unsigned char *key,unsigned char *sCipher)
{
	unsigned char sPlain[9];
	unsigned char sKey[17];
	des3_context ctx;
	int i;

	memset(sPlain,0,sizeof(sPlain));
	memset(sKey,0,sizeof(sKey));
	for(i=0;i<4;i++)
	{
		sPlain[i]=~m_OriginPhyNo[i];
		sPlain[i+4]=m_OriginPhyNo[i];
	}
	for(i=0;i<8;i++)
	{
		sKey[i]=key[i];
		sKey[i+8]=~key[i];
	}
	memset(&ctx,0,sizeof ctx);
	//encrypt_3des(sKey,16,sPlain,8,sCipher);
	des3_set_2keys(&ctx,sKey,sKey+8);
	des3_encrypt(&ctx,sPlain,sCipher);
	return 0;
}

int ks_mfcard_type::calcCMCCMainKey(unsigned char *key)
{
	char szCmd[256];
	std::string sCmd;
	byte uResp[256];
	ks_cpu_cmd_t cmd;
	std::vector<std::string> vCmd;
	int nRet;
	unsigned char uRespLen;

	//sprintf(szCmd,"00A4040010D1560001018000000000000100000000");
	//vCmd.push_back(szCmd); 
	nRet=m_PSAMCardType->selectADFByName("D1560001018000000000000100000000");
	if(nRet)
		return nRet;

	//  分散密钥
	sprintf(szCmd,"801A040108");
	sCmd = szCmd;
	// 1 级分散
	sCmd += this->strEnterpriceCode_;
	sprintf(szCmd,"03%02X",this->enterpriceAppID_);
	sCmd += szCmd;
	vCmd.push_back(sCmd);

	// 加密计算密钥
	sCmd = "80FA020008";
	sCmd += (char*)statickey;
	
	vCmd.push_back(sCmd);

	std::vector<std::string>::iterator iter;
	for(iter = vCmd.begin();iter != vCmd.end();++iter)
	{
		std::string sCmd = *iter;
		nRet = m_PSAMCardType->Adpu4HexSAM(sCmd.c_str(),sCmd.length(),uResp,uRespLen);
		if(nRet)
		{
			SET_ERR("执行指令失败,ret["<<nRet<<"]");
			return -1;
		}
	}
	memcpy(key,uResp,8);
	return 0;
}

int ks_mfcard_type::CalcKeyFromSAMKeyACMCC(unsigned char *cipherData)
{
	int nRet;
	unsigned char mainKey[8];

	nRet = calcCMCCMainKey(mainKey);
	if(nRet)
	{
		SET_ERR("计算种子密钥错误");
		return nRet;
	}
	nRet = this->encryptKeyA(mainKey,cipherData);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}
int ks_mfcard_type::CalcKeyFromSAMKeyBCMCC(unsigned char *cipherData)
{
	int nRet;
	unsigned char mainKey[8];

	nRet = calcCMCCMainKey(mainKey);
	if(nRet)
	{
		SET_ERR("计算种子密钥错误");
		return nRet;
	}
	nRet = this->encryptKeyB(mainKey,cipherData);
	if(nRet)
	{
		return nRet;
	}
	return 0;
}
int ks_mfcard_type::LoginCardSect(int sectno)
{
	int nRet;
	if(m_lastLoginSect == sectno)
		return 0;
	
	m_lastLoginSect = MF_MAX_SECTNO;
	nRet = CalcMFSectKey(sectno,&(m_cardSect[sectno]));
	if(nRet)
	{
		SET_ERR("计算M1卡密钥错误");
		return -1;
	}
	//CalcCardKeyA(sectno,&(m_cardSect[sectno]));
	nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno
		,m_cardSect[sectno].key_type,m_cardSect[sectno].key);
	if(nRet)
	{
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

// 登录费率参数卡
int ks_mfcard_type::LoginLegacyWaterCardSect(int sectno,bool bPublish)
{	
	int nRet;
	byte keyA[6]="";

	GenLegacyWaterKeyA(keyA);
	if(!bPublish)						// 回收卡，先用KeyB登录，不行再用出厂密钥登录
	{
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keyA);	// keyA 与keyB相同
		if(nRet)						// 失败，再用出厂密钥登录
		{

			if(nRet=RequestCard(NULL))
				return nRet;

			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_initLoginKey);
			if(nRet)
			{
				SET_ERR("登录Mifare1扇区["<<sectno<<"]失败！");
				return KS_LOGINCARD;
			}
		}
	}
	else							// 发行，先用出厂密钥登录
	{
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_initLoginKey);
		if(nRet)						
		{

			if(nRet=RequestCard(NULL))
				return nRet;

			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keyA);
			if(nRet)
			{
				SET_ERR("登录Mifare1扇区["<<sectno<<"]失败！");
				return KS_LOGINCARD;
			}
		}
	}

	return 0;
}

// 登录汇多水控参数卡
int ks_mfcard_type::LoginHDWaterParamCardSect(int sectno,bool bPublish)
{
	int nRet;
	byte keyA[6]="";
	GenHdWaterParamKeyA(keyA);
	if(!bPublish)						// 回收卡，先用KeyB登录，不行再用出厂密钥登录
	{
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keyA);	//keyB 登录
		if(nRet)						// 失败，再用出厂密钥登录
		{

			if(nRet=RequestCard(NULL))
				return nRet;
			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_initLoginKey);
			if(nRet)
			{
				SET_ERR("登录Mifare1扇区["<<sectno<<"]失败！");
				return KS_LOGINCARD;
			}
		}
	}
	else							// 发行，先用出厂密钥登录
	{
		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_initLoginKey);
		if(nRet)						
		{

			if(nRet=RequestCard(NULL))
				return nRet;

			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keyA);	//keyB 登录
			if(nRet)
			{
				SET_ERR("登录Mifare1扇区["<<sectno<<"]失败！");
				return KS_LOGINCARD;
			}
		}
	}

	return 0;
}
int ks_mfcard_type::ReadCard()
{
	IS_LOAD_KEY();

	int sectno,nRet,block,i;
	byte crc_num,crc_or;
	byte buffer[16];
	memset(&m_cardSect,0,sizeof m_cardSect);
	std::map<int,EFBUF>::iterator iter;
	for(iter=m_EFMap.begin();iter != m_EFMap.end();++iter)
	{
		sectno = iter->first;
		if(!iter->second.ReadFieldSet.size())
			continue;
		if(m_cardSect[sectno].has_read == 0)
		{
			if((nRet = LoginCardSect(sectno))!=0)
			{
				SET_ERR("登录扇区"<<sectno<<"失败");
				return nRet;
			}
			// read card
			for(block = 0;block < 4;++block)
			{
				memset(buffer,0xFF,sizeof buffer);
				if(m_cardinfo.block_info[sectno].block_used[block] == 1)
				{
					nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+block,buffer);
					if(nRet)
					{
						SET_ERR("读扇区"<<sectno<<"第"<<block<<"块数据失败");
						return KS_READCARD;
					}
					if(m_cardinfo.block_info[sectno].block_crc[block] == MF_BLK_CRC_SUM)
					{
						for(i=0,crc_num=0,crc_or=0;i<15;++i)
						{
							crc_num += buffer[i];
							crc_or |= buffer[i];
						}
						if(crc_num != buffer[15] || crc_or == 0)
						{
							SET_ERR("读取扇区"<<sectno<<"第"<<block<<"块校验错误");
							return KS_READCARD;
						}
					}
					else if(m_cardinfo.block_info[sectno].block_crc[block] == MF_BLK_CRC_SUM_ALLOW_ZERO)
					{
						for(i=0,crc_num=0;i<15;++i)
							crc_num += buffer[i];
						if(crc_num != buffer[15])
						{
							SET_ERR("读取扇区"<<sectno<<"第"<<block<<"块校验错误");
							return KS_READCARD;
						}
					}
					else if(m_cardinfo.block_info[sectno].block_crc[block] == MF_BLK_CRC_OR)
					{
						for(i=0,crc_num=0;i<15;++i)
							crc_num |= buffer[i];
						if(crc_num != buffer[15])
						{
							SET_ERR("读取扇区"<<sectno<<"第"<<block<<"块校验错误");
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
int ks_mfcard_type::WriteCard()
{
	IS_LOAD_KEY();
	int sectno,nRet,blockno,i,offset,len;
	byte buffer[16];
	int block_write_flag[MF_MAX_BLOCK];
	byte real_write_buffer[MF_MAX_BLOCK_SIZE];

	//memset(block_write_flag,0,sizeof block_write_flag);
	memset(real_write_buffer,0,sizeof real_write_buffer);
	std::map<int,EFBUF>::iterator iter;
	for(iter=m_EFMap.begin();iter != m_EFMap.end();++iter)
	{
		sectno = iter->first;
		// 钱包相关扇区不要写数据
		if(sectno > 3 && sectno < m_maxSectNo)
			continue;
		EFBUF buf = iter->second;
		if(buf.WriteFieldSet.empty())
			continue;
		if((nRet=LoginCardSect(sectno)))
			return nRet;
		// 登录成功，写卡信息
		memset(block_write_flag,0,sizeof block_write_flag);
		memset(real_write_buffer,0,sizeof real_write_buffer);
		std::set<int>::iterator iter;
		for(iter = buf.WriteFieldSet.begin();iter != buf.WriteFieldSet.end();++iter)
		{
			int writefld = *iter;
			offset = m_FieldVect[writefld].offset;
			len = m_FieldVect[writefld].length;
			blockno = 0;
			for(blockno = 0;blockno < MF_MAX_BLOCK;++blockno)
			{
				if(ISSET_BLOCK(m_FieldVect[writefld].blockno,blockno))
					block_write_flag[blockno] = 1;
			}
			for(blockno = 0;blockno < MF_MAX_BLOCK;++blockno)
			{
				if(ISSET_BLOCK(m_FieldVect[writefld].blockno,blockno))
				{
					if(m_cardSect[sectno].has_read == 0)
					{
						// 需要先读取扇区
						for(i = 0;i<3;++i)
						{
							memset(buffer,0,sizeof buffer);
							nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+i,buffer);
							if(nRet)
							{
								SET_ERR("读卡Mifare1扇区["<<sectno<<"]失败");
								return KS_READCARD;
							}
							memcpy(m_cardSect[sectno].block_buffer+16*i,buffer,16);
						}
						m_cardSect[sectno].has_read = 1;
						memcpy(real_write_buffer,m_cardSect[sectno].block_buffer,MF_MAX_BLOCK_SIZE);
					}
					else
					{
						memcpy(real_write_buffer,m_cardSect[sectno].block_buffer,MF_MAX_BLOCK_SIZE);
						break;
					}
				}
			}
			//memcpy(real_write_buffer+offset,m_cardSect[sectno].write_buffer+offset,len);
		}
		for(iter = buf.WriteFieldSet.begin();iter != buf.WriteFieldSet.end();++iter)
		{
			int writefld = *iter;
			offset = m_FieldVect[writefld].offset;
			len = m_FieldVect[writefld].length;
			memcpy(real_write_buffer+offset,m_cardSect[sectno].write_buffer+offset,len);
		}
		memcpy(m_cardSect[sectno].write_buffer,real_write_buffer,16);
		for(blockno=0;blockno<3;++blockno)
		{
			if(block_write_flag[blockno] == 1)
			{
				// 写卡
				if(m_cardinfo.block_info[sectno].block_crc[blockno] == MF_BLK_CRC_SUM_ALLOW_ZERO
					|| m_cardinfo.block_info[sectno].block_crc[blockno] == MF_BLK_CRC_SUM)
				{
					for(i=0,real_write_buffer[16*sectno+15]=0;i<15;++i)
					{
						real_write_buffer[16*sectno+15] += real_write_buffer[16*sectno+i];
					}
					memcpy(m_cardSect[sectno].block_buffer+16*sectno,real_write_buffer+16*sectno,16);
					memcpy(m_cardSect[sectno].write_buffer+16*sectno,real_write_buffer+16*sectno,16);
				}
				nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+blockno,real_write_buffer+16*blockno);
				if(nRet)
				{
					SET_ERR("写Mifare1扇区["<<sectno<<"]块["<<blockno<<"]失败");
					return KS_WRITECARD;
				}
			}
		}
	}
	return 0;
}
int ks_mfcard_type::SetFieldVal(int FieldID,const char *fieldval)
{
	int sectno,offset,len,num,data_len,i;
	char temp[10];
	byte buff[256] = {0};
	if(FieldID>CF_END||FieldID<CF_START)
	{
		SET_ERR("SetFieldVal:字段索引"<<FieldID<<"不存在");
		return -1;
	}

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
	}
	sectno = m_FieldVect[FieldID].fid;
	
	len = m_FieldVect[FieldID].length;
	offset = m_FieldVect[FieldID].offset;
	data_len = strlen(fieldval);
	memset(m_cardSect[sectno].write_buffer+offset,0x00,len);
	memset(buff,0x00,len);
	switch(m_FieldVect[FieldID].type)
	{
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
		if(strlen(fieldval)==12)
		{
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
		if(len == 3)
		{
			for(i=0;i<3;++i)
			{
				memcpy(temp,fieldval+2+i*2,2);
				buff[i] = atoi(temp);
			}
		}
		else if(len == 4)
		{
			for(i=0;i<4;++i)
			{
				memcpy(temp,fieldval+i*2,2);
				buff[i] = atoi(temp);
			}
		}
		else
		{
			SET_ERR("SetFieldVal:字段索引"<<FieldID<<":数据定义错误");
			return -1;
		}
		break;
	case FT_HEX_TIME:
		if(len == 2)
		{
			for(i=0;i<2;++i)
			{
				memcpy(temp,fieldval+i*2,2);
				buff[i] = atoi(temp);
			}
			buff[2] = 0;
		}
		else if(len == 3)
		{
			for(i=0;i<3;++i)
			{
				memcpy(temp,fieldval+i*2,2);
				buff[i] = atoi(temp);
			}
		}
		else 
		{
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
int ks_mfcard_type::GetFieldVal(int FieldID,char *fieldval)
{
	int sectno,offset,len,num;
	byte temp[10];
	if(FieldID>CF_END||FieldID<CF_START)
	{
		SET_ERR("GetFieldVal:字段索引"<<FieldID<<"不存在");
		return -1;
	}

	std::set<int>::iterator it;
	it=m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.find(FieldID);
	if(it==m_EFMap[m_FieldVect[FieldID].fid].ReadFieldSet.end())
	{
		SET_ERR("GetFieldVal:字段索引"<<FieldID<<"未设置读");
		return -1;
	}
	sectno = m_FieldVect[FieldID].fid;
	if(m_cardSect[sectno].has_read == 0)
	{
		SET_ERR("GetFieldVal:字段索引"<<FieldID<<"未读取");
		fieldval[0]=0;
		return -1;
	}
	len = m_FieldVect[FieldID].length;
	offset = m_FieldVect[FieldID].offset;
	switch(m_FieldVect[FieldID].type)
	{
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
		if(len > 0)
		{
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
		if(len == 3)
		{
			temp[0] = 20;
			memcpy(temp+1,m_cardSect[sectno].block_buffer+offset,len);
		}
		else if(len == 4)
		{
			memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
		}
		else
		{
			SET_ERR("GetFieldVal:字段索引"<<FieldID<<":数据定义错误");
			return -1;
		}
		sprintf(fieldval,"%02d%02d%02d%02d",temp[0],temp[1],temp[2],temp[3]);
		break;
	case FT_HEX_TIME:
		if(len == 2)
		{
			memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
			temp[2] = 00;
		}
		else if(len == 3)
		{
			memcpy(temp,m_cardSect[sectno].block_buffer+offset,len);
		}
		else 
		{
			SET_ERR("GetFieldVal:字段索引"<<FieldID<<":数据定义错误");
			return -1;
		}
		sprintf(fieldval,"%02d%02d%02d",temp[0],temp[1],temp[2]);
		break;
	}
	return 0;
}
char * ks_mfcard_type::GetErrMsgByErrCode( int nErrCode,char *sErrInfo)
{
	return "";
}
int ks_mfcard_type::SelectADF()
{
	return 0;
}

int ks_mfcard_type::MFTransaction(ST_TRANSPACK *transpack,int transtype)
{
	int nRet,sectno,blockno,i,offset;
	int nCardBala,nCardPayCnt,nDayTotal;
	char datetime[24] = "";
	byte buffer[16],buffer2[16],buffer3[16];
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
		/*
		this->SetFieldReadMode(CF_CARDBAL);
		this->SetFieldReadMode(CF_PAYCNT);
		this->SetFieldReadMode(CF_DAYSUMAMT);
		this->SetFieldReadMode(CF_TRANSDATE);
		this->SetFieldReadMode(CF_TRANSTIME);
		*/
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
int  ks_mfcard_type::AddMoney(ST_TRANSPACK *transpack)
{
	return MFTransaction(transpack,1);
}
int  ks_mfcard_type::PayMoney(ST_TRANSPACK *transpack)
{
	return MFTransaction(transpack,0);	
}
int ks_mfcard_type::GetCurrentDateTime(char *datetime)
{
	time_t t;
	t = time(NULL);
	struct tm * tx = localtime(&t);
	sprintf(datetime,"%04d%02d%02d%02d%02d%02d",tx->tm_year+1900,tx->tm_mon+1,tx->tm_mday,
		tx->tm_hour,tx->tm_min,tx->tm_sec);
	return 0;
}
int  ks_mfcard_type::ExtAuth(const char *cardphyid,int keyidx)
{
	return -1;
}
int  ks_mfcard_type::Adpu(const unsigned char *ucCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen)
{
	return -1;
}
int  ks_mfcard_type::Adpu4Hex(const char *szCmd,unsigned char ucSendLen,unsigned char *ucRespData,unsigned char &ucRespLen)
{
	return -1;
}
int  ks_mfcard_type::VerifyCardPasswd(const char *cardphyid,const char* sCardPasswd,int& iIsPass)
{
	return -1;
}
void ks_mfcard_type::SetMifare1Key(const char *sCipherKey)
{
	AuthDLL(sCipherKey,1);
}
int ks_mfcard_type::AuthDLL(const char *key,int flag)
{
	byte ucWorkKey[8];
	int len;
	
	unsigned int  i;
	unsigned long ul;
	char temp[3];
	unsigned char plain[9];
	unsigned char statkey[9];

	hex2dec(key,16,ucWorkKey,len);

	if(flag == 1)
	{	
		memset(temp,0,sizeof(temp));
		memset(plain,0,sizeof(plain));
		memset(statkey,0,sizeof(statkey));
		memcpy(plain,ucWorkKey,8);
		for(i=0;i<8;i++)
		{
			memcpy(temp,&statickey[2*i],2);
			ul=strtoul(temp,NULL,16);
			statkey[i]=ul;
			plain[i]=~plain[i];
			m_mainkey[i]=plain[i]^statkey[i];
		}
	}
	else
		memcpy(m_mainkey,ucWorkKey,8);
	m_isLoadKey = 1;
	return 0;
}

int ks_mfcard_type::InitForTrans(ST_TRANSPACK *trans,int trans_type)
{
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

int ks_mfcard_type::initAllCardDef()
{
	

	// 0 扇区
	m_cardinfo.block_info[0].block_used[0] = 0;
	m_cardinfo.block_info[0].block_used[1] = 1;
	m_cardinfo.block_info[0].block_used[2] = 1;
	// 1 扇区
	m_cardinfo.block_info[1].block_used[0] = 1;
	m_cardinfo.block_info[1].block_used[1] = 1;
	m_cardinfo.block_info[1].block_crc[1] = MF_BLK_CRC_SUM_ALLOW_ZERO;
	m_cardinfo.block_info[1].block_used[2] = 1;
	// 2 扇区
	m_cardinfo.block_info[2].block_used[0] = 1;
	m_cardinfo.block_info[2].block_used[1] = 1;
	m_cardinfo.block_info[2].block_used[2] = 1;
	// 3 扇区
	m_cardinfo.block_info[3].block_used[0] = 1;
	m_cardinfo.block_info[3].block_used[1] = 0;
	m_cardinfo.block_info[3].block_used[2] = 1;
	// 4 扇区
	m_cardinfo.block_info[4].block_used[0] = 1;
	m_cardinfo.block_info[4].block_crc[0] = MF_BLK_CRC_SUM;
	m_cardinfo.block_info[4].block_used[1] = 0;
	m_cardinfo.block_info[4].block_used[2] = 1;
	m_cardinfo.block_info[4].block_crc[2] = 0;
	// 5 扇区
	m_cardinfo.block_info[5].block_used[0] = 1;
	m_cardinfo.block_info[5].block_crc[0] = MF_BLK_CRC_SUM_ALLOW_ZERO;
	m_cardinfo.block_info[5].block_used[1] = 0;
	m_cardinfo.block_info[5].block_used[2] = 1;
	m_cardinfo.block_info[5].block_crc[2] = MF_BLK_CRC_SUM_ALLOW_ZERO;

	m_FieldVect.clear();

	EF_FIELD EField;
	memset(&EField,0,sizeof(EField));
	EField.unused=1;
	//先初始化为0
	for(int i=0;i<=CF_END;i++)
		m_FieldVect.push_back(EField);

	PERINFO perinfo;
	PUBLICINFO publicinfo;
	IDINFO idinfo;
	PACKAGEINFO packageinfo;
	PACKAGEIDXINFO packageidxinfo;
	
	//发行方标识
	m_FieldVect[CF_PUBLISHID].unused=1;

	//显示卡号
	m_FieldVect[CF_SHOWCARDNO].unused=0;
	m_FieldVect[CF_SHOWCARDNO].offset = (perinfo.show_card_no)-(byte*)&perinfo;
	m_FieldVect[CF_SHOWCARDNO].length = sizeof(perinfo.show_card_no);
	m_FieldVect[CF_SHOWCARDNO].fid = 1;
	EASY_SET_BLOCK(m_FieldVect[CF_SHOWCARDNO].blockno,m_FieldVect[CF_SHOWCARDNO].offset);
	//SET_BLOCK(m_FieldVect[CF_SHOWCARDNO].blockno,m_FieldVect[CF_SHOWCARDNO].offset);
	m_FieldVect[CF_SHOWCARDNO].type=FT_BCD_LAPDZERO;

	//卡号
	m_FieldVect[CF_CARDNO].unused=0;
	m_FieldVect[CF_CARDNO].offset = perinfo.card_no-(byte*)&perinfo;
	m_FieldVect[CF_CARDNO].length = sizeof(perinfo.card_no);
	m_FieldVect[CF_CARDNO].fid = 1;
	EASY_SET_BLOCK(m_FieldVect[CF_CARDNO].blockno,m_FieldVect[CF_CARDNO].offset);
	m_FieldVect[CF_CARDNO].type=FT_INT24;

	if(m_cardVer > 2008)
	{
		//卡状态
		m_FieldVect[CF_CARDSTATUS].unused=0;
		m_FieldVect[CF_CARDSTATUS].offset = &perinfo.card_status - (byte*)&perinfo;
		m_FieldVect[CF_CARDSTATUS].length = sizeof(perinfo.card_status);
		m_FieldVect[CF_CARDSTATUS].fid = 1;
		EASY_SET_BLOCK(m_FieldVect[CF_CARDSTATUS].blockno,m_FieldVect[CF_CARDSTATUS].offset);
		m_FieldVect[CF_CARDSTATUS].type=FT_INT8;
	}	

	//补助批次号
	m_FieldVect[CF_SUBSIDYNO].unused=0;
	m_FieldVect[CF_SUBSIDYNO].offset = packageinfo.subsidy_no - (byte*)&packageinfo;
	m_FieldVect[CF_SUBSIDYNO].length = sizeof(packageinfo.subsidy_no);
	m_FieldVect[CF_SUBSIDYNO].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_SUBSIDYNO].blockno,m_FieldVect[CF_SUBSIDYNO].offset);
	m_FieldVect[CF_SUBSIDYNO].type=FT_INT16;

	//启用日期
	m_FieldVect[CF_STARTDATE].unused=1;
	//有效期
	m_FieldVect[CF_EXPIREDATE].unused=0;
	m_FieldVect[CF_EXPIREDATE].offset = perinfo.expired_date-(byte*)&perinfo;
	m_FieldVect[CF_EXPIREDATE].length = sizeof(perinfo.expired_date);
	m_FieldVect[CF_EXPIREDATE].fid=1;
	EASY_SET_BLOCK(m_FieldVect[CF_EXPIREDATE].blockno,m_FieldVect[CF_EXPIREDATE].offset);
	m_FieldVect[CF_EXPIREDATE].type=FT_HEX_DATE;
	//卡结构版本
	m_FieldVect[CF_CARDSTRUCTVER].unused=1;
	
	//收费类别
	m_FieldVect[CF_FEETYPE].unused=0;
	m_FieldVect[CF_FEETYPE].offset = &(perinfo.fee_type) - (byte*)&perinfo;
	m_FieldVect[CF_FEETYPE].length = sizeof(perinfo.fee_type);
	m_FieldVect[CF_FEETYPE].fid = 1;
	EASY_SET_BLOCK(m_FieldVect[CF_FEETYPE].blockno,m_FieldVect[CF_FEETYPE].offset);
	m_FieldVect[CF_FEETYPE].type=FT_INT8;
	//卡类型
	m_FieldVect[CF_CARDTYPE].unused=1;

	//姓名
	m_FieldVect[CF_NAME].unused=0;
	m_FieldVect[CF_NAME].offset = publicinfo.cust_name - (byte*)&publicinfo;
	m_FieldVect[CF_NAME].length = sizeof(publicinfo.cust_name);
	m_FieldVect[CF_NAME].fid = 2;
	EASY_SET_BLOCK(m_FieldVect[CF_NAME].blockno,m_FieldVect[CF_NAME].offset);
	m_FieldVect[CF_NAME].type=FT_ANSI;
	//身份证号
	m_FieldVect[CF_IDNO].unused=0;
	m_FieldVect[CF_IDNO].offset = publicinfo.id_card - (byte*)&publicinfo;
	m_FieldVect[CF_IDNO].length = sizeof(publicinfo.id_card);
	ZERO_BLOCK(m_FieldVect[CF_IDNO].blockno);
	SET_BLOCK(m_FieldVect[CF_IDNO].blockno,0);
	SET_BLOCK(m_FieldVect[CF_IDNO].blockno,1);
	m_FieldVect[CF_IDNO].fid=2;
	m_FieldVect[CF_IDNO].type=FT_ANSI;
	//证件类型
	m_FieldVect[CF_IDTYPE].unused=0;
	m_FieldVect[CF_IDTYPE].offset = publicinfo.id_code - (byte*)&publicinfo;
	m_FieldVect[CF_IDTYPE].length = sizeof(publicinfo.id_code);
	EASY_SET_BLOCK(m_FieldVect[CF_IDTYPE].blockno,m_FieldVect[CF_IDTYPE].offset);
	m_FieldVect[CF_IDTYPE].fid=2;
	m_FieldVect[CF_IDTYPE].type=FT_ANSI;

	//单次累计最大限额
	m_FieldVect[CF_SINGLEMAXAMT].unused=0;
	m_FieldVect[CF_SINGLEMAXAMT].offset = perinfo.limit_once - (byte*)&perinfo;
	m_FieldVect[CF_SINGLEMAXAMT].length = sizeof(perinfo.limit_once);
	EASY_SET_BLOCK(m_FieldVect[CF_SINGLEMAXAMT].blockno,m_FieldVect[CF_SINGLEMAXAMT].offset);
	m_FieldVect[CF_SINGLEMAXAMT].fid=1;
	m_FieldVect[CF_SINGLEMAXAMT].type=FT_INT16;
	//日累计最大限额
	m_FieldVect[CF_DAYMAXAMT].unused=0;
	m_FieldVect[CF_DAYMAXAMT].offset = perinfo.limit_day - (byte*)&perinfo;
	m_FieldVect[CF_DAYMAXAMT].length = sizeof(perinfo.limit_day);
	EASY_SET_BLOCK(m_FieldVect[CF_DAYMAXAMT].blockno,m_FieldVect[CF_DAYMAXAMT].offset);
	m_FieldVect[CF_DAYMAXAMT].fid=1;
	m_FieldVect[CF_DAYMAXAMT].type=FT_INT24;
	//卡密码
	m_FieldVect[CF_CARDPWD].unused=0;
	m_FieldVect[CF_CARDPWD].offset = perinfo.pin - (byte*)&perinfo;
	m_FieldVect[CF_CARDPWD].length = sizeof(perinfo.pin);
	m_FieldVect[CF_CARDPWD].fid = 1;
	EASY_SET_BLOCK(m_FieldVect[CF_CARDPWD].blockno,m_FieldVect[CF_CARDPWD].offset);
	m_FieldVect[CF_CARDPWD].type=FT_BCD;	
	//m_FieldVect[CF_CARDPWD].rw=RW_W;

	//客户类别
	m_FieldVect[CF_CUSTTYPE].unused=1;

	//客户号
	m_FieldVect[CF_CUSTID].unused=1;

	//学工号
	m_FieldVect[CF_STUEMPNO].unused=0;
	m_FieldVect[CF_STUEMPNO].offset = idinfo.stuemp_no - (byte*)&idinfo;
	m_FieldVect[CF_STUEMPNO].length = sizeof(idinfo.stuemp_no);
	m_FieldVect[CF_STUEMPNO].fid = 0;
	ZERO_BLOCK(m_FieldVect[CF_STUEMPNO].blockno);
	SET_BLOCK(m_FieldVect[CF_STUEMPNO].blockno,1);
	SET_BLOCK(m_FieldVect[CF_STUEMPNO].blockno,2);
	m_FieldVect[CF_STUEMPNO].type=FT_ANSI;
	//校区
	//m_FieldVect[CF_SCHOOLCODE].unused=0;
	//m_FieldVect[CF_SCHOOLCODE].offset = &UserInfo.ucSchoolCode - (byte*)&PrivateApp;
	//m_FieldVect[CF_SCHOOLCODE].length = sizeof(PrivateApp.ucSchoolCode);
	//m_FieldVect[CF_SCHOOLCODE].fid=0x1B;
	//m_FieldVect[CF_SCHOOLCODE].type=FT_INT8;
	//部门代码
	m_FieldVect[CF_DEPTCODE].unused=0;
	m_FieldVect[CF_DEPTCODE].offset = publicinfo.dept_code - (byte*)&publicinfo;
	m_FieldVect[CF_DEPTCODE].length = sizeof(publicinfo.dept_code);
	m_FieldVect[CF_DEPTCODE].fid = 2;
	EASY_SET_BLOCK(m_FieldVect[CF_DEPTCODE].blockno,m_FieldVect[CF_DEPTCODE].offset);
	m_FieldVect[CF_DEPTCODE].type=FT_ANSI;
	//性别
	m_FieldVect[CF_SEX].unused=0;
	m_FieldVect[CF_SEX].offset = &publicinfo.sex - (byte*)&publicinfo;
	m_FieldVect[CF_SEX].length = sizeof(publicinfo.sex);
	m_FieldVect[CF_SEX].fid = 2;
	EASY_SET_BLOCK(m_FieldVect[CF_SEX].blockno,m_FieldVect[CF_SEX].offset);
	m_FieldVect[CF_SEX].type=FT_ANSI;


	/////////////////////////////////////////////////////

	//卡版本号
	m_FieldVect[CF_CARDVERNO].unused=0;
	m_FieldVect[CF_CARDVERNO].offset = packageidxinfo.black_ver - (byte*)&packageidxinfo;
	m_FieldVect[CF_CARDVERNO].length = sizeof(packageidxinfo.black_ver);
	m_FieldVect[CF_CARDVERNO].fid = 3;
	EASY_SET_BLOCK(m_FieldVect[CF_CARDVERNO].blockno,m_FieldVect[CF_CARDVERNO].offset);
	m_FieldVect[CF_CARDVERNO].type=FT_BCD;

	//卡状态
	if(m_cardVer == 2008)
	{
		m_FieldVect[CF_CARDSTATUS].unused=0;
		m_FieldVect[CF_CARDSTATUS].offset = &packageidxinfo.black_flag - (byte*)&packageidxinfo;
		m_FieldVect[CF_CARDSTATUS].length = sizeof(packageidxinfo.black_flag);
		m_FieldVect[CF_CARDSTATUS].fid = 3;
		EASY_SET_BLOCK(m_FieldVect[CF_CARDSTATUS].blockno,m_FieldVect[CF_CARDSTATUS].offset);
		m_FieldVect[CF_CARDSTATUS].type=FT_INT8;
	}
	else
	{
		m_FieldVect[CF_BLACKFLAG].unused=0;
		m_FieldVect[CF_BLACKFLAG].offset = &packageidxinfo.black_flag - (byte*)&packageidxinfo;
		m_FieldVect[CF_BLACKFLAG].length = sizeof(packageidxinfo.black_flag);
		m_FieldVect[CF_BLACKFLAG].fid = 3;
		EASY_SET_BLOCK(m_FieldVect[CF_BLACKFLAG].blockno,m_FieldVect[CF_BLACKFLAG].offset);
		m_FieldVect[CF_BLACKFLAG].type=FT_INT8;
	}

	//////////////////////////////////////////////////////
	//卡余额
	m_FieldVect[CF_CARDBAL].unused=0;
	m_FieldVect[CF_CARDBAL].offset = packageinfo.balance-(byte*)&packageinfo;
	m_FieldVect[CF_CARDBAL].length =sizeof(packageinfo.balance);
	m_FieldVect[CF_CARDBAL].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_CARDBAL].blockno,m_FieldVect[CF_CARDBAL].offset);
	m_FieldVect[CF_CARDBAL].type=FT_LT_INT24;
	m_FieldVect[CF_CARDBAL].rw=RW_R;
	// 当日累计交易金额
	m_FieldVect[CF_DAYSUMAMT].unused=0;
	m_FieldVect[CF_DAYSUMAMT].offset = packageinfo.total_per_day-(byte*)&packageinfo;
	m_FieldVect[CF_DAYSUMAMT].length =sizeof(packageinfo.total_per_day);
	m_FieldVect[CF_DAYSUMAMT].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_DAYSUMAMT].blockno,m_FieldVect[CF_DAYSUMAMT].offset);
	m_FieldVect[CF_DAYSUMAMT].type=FT_LT_INT24;
	m_FieldVect[CF_DAYSUMAMT].rw=RW_R;
	// 最后一次交易日期
	m_FieldVect[CF_TRANSDATE].unused=0;
	m_FieldVect[CF_TRANSDATE].offset = packageinfo.tx_date-(byte*)&packageinfo;
	m_FieldVect[CF_TRANSDATE].length =sizeof(packageinfo.tx_date);
	m_FieldVect[CF_TRANSDATE].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_TRANSDATE].blockno,m_FieldVect[CF_TRANSDATE].offset);
	m_FieldVect[CF_TRANSDATE].type=FT_HEX_DATE;
	m_FieldVect[CF_TRANSDATE].rw=RW_R;
	// 最后一次交易时间
	m_FieldVect[CF_TRANSTIME].unused=0;
	m_FieldVect[CF_TRANSTIME].offset = packageinfo.tx_time-(byte*)&packageinfo;
	m_FieldVect[CF_TRANSTIME].length =sizeof(packageinfo.tx_time);
	m_FieldVect[CF_TRANSTIME].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_TRANSTIME].blockno,m_FieldVect[CF_TRANSTIME].offset);
	m_FieldVect[CF_TRANSTIME].type=FT_HEX_TIME;
	m_FieldVect[CF_TRANSTIME].rw=RW_R;
	//消费次数
	m_FieldVect[CF_PAYCNT].unused=0;
	m_FieldVect[CF_PAYCNT].offset =packageinfo.total_count-(byte*)&packageinfo;
	m_FieldVect[CF_PAYCNT].length =sizeof(packageinfo.total_count);
	m_FieldVect[CF_PAYCNT].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_PAYCNT].blockno,m_FieldVect[CF_PAYCNT].offset);
	m_FieldVect[CF_PAYCNT].type=FT_INT16;
	m_FieldVect[CF_PAYCNT].rw=RW_R;
	//充值次数
	m_FieldVect[CF_DPSCNT].unused=0;
	m_FieldVect[CF_DPSCNT].offset =packageinfo.total_count-(byte*)&packageinfo;
	m_FieldVect[CF_DPSCNT].length =sizeof(packageinfo.total_count);
	m_FieldVect[CF_DPSCNT].fid=4;
	EASY_SET_BLOCK(m_FieldVect[CF_DPSCNT].blockno,m_FieldVect[CF_DPSCNT].offset);
	m_FieldVect[CF_DPSCNT].type=FT_INT16;
	m_FieldVect[CF_DPSCNT].rw=RW_R;

	m_EFMap.clear();

	EFBUF efbuf;

	efbuf.FileSize=sizeof(IDINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[0]=efbuf;

	efbuf.FileSize=sizeof(PERINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[1]=efbuf;

	efbuf.FileSize=sizeof(PUBLICINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[2]=efbuf;

	efbuf.FileSize=sizeof(PACKAGEIDXINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[3]=efbuf;

	efbuf.FileSize=sizeof(PACKAGEINFO);
	efbuf.ReadRight=FRR_FREE;
	efbuf.WriteRight=FRW_MAC;
	m_EFMap[4]=efbuf;
	return 0;
}

int ks_mfcard_type::checkCardType(int ct)
{
	switch(ct)
	{
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

int ks_mfcard_type::GetTransProve(int nTransFlag,short CardCnt,unsigned char *sMac,unsigned char *sTac)
{
	int nRet,sectno,i;
	byte buffer[16];
	byte crc_sum,crc_or;
	IS_LOAD_KEY();

	sectno = 4;
	if(m_cardVer <= 2010)
	{
		// 充值与消费二合一
		if(this->LoginCardSect(sectno))
		{
			SET_ERR("登录钱包扇区错误");
			return KS_LOGINCARD;
		}
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno * 4,buffer);
		if(nRet)
		{
			SET_ERR("读取钱包失败!");
			return KS_READCARD;
		}
		for(i = 0,crc_sum = 0,crc_or = 0;i < 15 ;++i)
		{
			crc_sum += buffer[i];
			crc_or |= buffer[i];
		}
		if(buffer[15] != crc_sum || crc_or == 0)
		{
			SET_ERR("钱包格式错误");
			return -1;
		}
		int cnt = buffer[3] * 256 + buffer[4];
		if(cnt != CardCnt)
		{
			SET_ERR("期望交易次数["<<CardCnt<<"]实际交易次数["<<cnt<<"]");
			return -1;
		}
		SET_ERR("卡钱包交易次数相同");
		return 0;
	}
	else
	{
		//
		return -1;
	}
}

//////////////////////////////////////////////////////////////////////////
// 发行水控卡
int ks_mfcard_type::water_publishcard(int watertype,ks_water_pack_t *pack)
{
	switch(watertype)
	{
	case KS_LEGACY_WATER:
		return legacy_water_publishcard(pack);
	case KS_HD_WATER:
		return hd_water_publishcard(pack);
	case KS_SZLLDF_WATER:
		return lldf_water_publishcard(pack);
	default:
		SET_ERR("不支持的水控类型["<<watertype<<"]");
		return -1;
	}
	return -1;
}

// 回收水控卡
int ks_mfcard_type::water_recyclecard(int watertype)
{
	switch(watertype)
	{
	case KS_LEGACY_WATER:
		return legacy_water_recyclecard();
	case KS_HD_WATER:
		return hd_water_recyclecard();
	case KS_SZLLDF_WATER:
		return lldf_water_recyclecard();
	default:
		SET_ERR("不支持的水控类型["<<watertype<<"]");
		return -1;
	}
	return -1;	
}

// 读取水控钱包余额
int ks_mfcard_type::water_readmoney(int watertype,ks_water_pack_t *pack)
{
	switch(watertype)
	{
	case KS_LEGACY_WATER:
		return legacy_water_readmoney(pack);
	case KS_HD_WATER:
		return hd_water_readmoney(pack);
	case KS_SZLLDF_WATER:
		return lldf_water_readmoney(pack);
	default:
		SET_ERR("不支持的水控类型["<<watertype<<"]");
		return -1;
	}
	return -1;	
}

// 写水控钱包余额
int ks_mfcard_type::water_writemoney(int watertype,ks_water_pack_t *pack)
{
	switch(watertype)
	{
	case KS_LEGACY_WATER:
		return legacy_water_writemoney(pack);
	case KS_HD_WATER:
		return hd_water_writemoney(pack);
	case KS_SZLLDF_WATER:
		return lldf_water_writemoney(pack);
	default:
		SET_ERR("不支持的水控类型["<<watertype<<"]");
		return -1;
	}
	return -1;		
}
///  深圳领路达方水控
int ks_mfcard_type::lldf_water_publishcard(ks_water_pack_t *pack)
{
	int sectno,nRet,blockno;
	unsigned char buffer[16];
	sectno = this->m_lldfSect;
	if(sectno == MF_MAX_SECTNO)
		return KS_NOTSUPPORT;

	sectno = this->m_lldfSect + 1;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}
	memset(buffer,0,sizeof buffer);
	
	// 主钱包
	blockno = sectno * 4;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控主钱包失败");
		return -1;
	}
	set_2byte_int(buffer+6,pack->money);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控主钱包失败");
		return -1;
	}
	// 备钱包
	blockno = sectno * 4 + 2;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控备钱包失败");
		return -1;
	}
	set_2byte_int(buffer+6,pack->money);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控备钱包失败");
		return -1;
	}
	// 写成功标志
	blockno = sectno * 4 + 1;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控钱包控制块失败");
		return -1;
	}
	buffer[0] = 'O';
	buffer[1] = 'K';
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控钱包控制块失败");
		return -1;
	}
	// 更新前一扇区
	sectno = this->m_lldfSect;
	// 
	blockno = sectno * 4 + 2;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控主钱包失败");
		return -1;
	}
	set_2byte_int(buffer+2,pack->money);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控主钱包失败");
		return -1;
	}
	return 0;
}
int ks_mfcard_type::lldf_water_recyclecard()
{
	int sectno,nRet,blockno;
	unsigned char buffer[16];
	sectno = this->m_lldfSect;
	if(sectno == MF_MAX_SECTNO)
		return KS_NOTSUPPORT;

	sectno = this->m_lldfSect + 1;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}
	memset(buffer,0,sizeof buffer);
	
	// 主钱包
	blockno = sectno * 4;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控主钱包失败");
		return -1;
	}
	set_2byte_int(buffer+6,0);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控主钱包失败");
		return -1;
	}
	// 备钱包
	blockno = sectno * 4 + 2;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控备钱包失败");
		return -1;
	}
	set_2byte_int(buffer+6,0);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控备钱包失败");
		return -1;
	}
	// 写成功标志
	blockno = sectno * 4 + 1;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控钱包控制块失败");
		return -1;
	}
	buffer[0] = 'O';
	buffer[1] = 'K';
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控钱包控制块失败");
		return -1;
	}
	// 更新前一扇区
	sectno = this->m_lldfSect;
	// 
	blockno = sectno * 4 + 2;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控主钱包失败");
		return -1;
	}
	set_2byte_int(buffer+2,0);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控主钱包失败");
		return -1;
	}
	return 0;
}
int ks_mfcard_type::lldf_water_readmoney(ks_water_pack_t *pack)
{
	int sectno,nRet,blockno,total_money,current_money;
	unsigned char buffer[16]={0},buffer1[16]={0},ctrlbuffer[16]={0};
	sectno = this->m_lldfSect;
	if(sectno == MF_MAX_SECTNO)
		return KS_NOTSUPPORT;

	// 更新钱包
	sectno = this->m_lldfSect + 1;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}
	memset(buffer,0,sizeof buffer);
	// 主钱包
	blockno = sectno * 4;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控主钱包失败");
		return -1;
	}
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+2,buffer1);
	if(nRet)
	{
		SET_ERR("读取水控备钱包失败");
		return -1;
	}
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+1,ctrlbuffer);
	if(nRet)
	{
		SET_ERR("读取水控钱包控制块失败");
		return -1;
	}
	if(memcmp(buffer,buffer1,16)!=0)
	{
		if(ctrlbuffer[0] != 'O' || ctrlbuffer[1] != 'K')
		{
			memcpy(buffer,buffer1,16); // 以备为准
		}
	}

	current_money=get_2byte_int(buffer+6);
	pack->money = current_money;
	pack->totalmoney = current_money;
	return 0;
}
int ks_mfcard_type::lldf_water_writemoney(ks_water_pack_t *pack)
{
	int sectno,nRet,blockno,total_money,current_money;
	unsigned char buffer[16]={0},buffer1[16]={0},ctrlbuffer[16]={0};
	char msg[256]={0};
	sectno = this->m_lldfSect;
	if(sectno == MF_MAX_SECTNO)
		return KS_NOTSUPPORT;
	if(pack->money > 0x7FFF) 
	{
		SET_ERR("转账金额超过上限");
		return -1;
	}

	// 更新钱包
	sectno = this->m_lldfSect + 1;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}
	memset(buffer,0,sizeof buffer);
	// 主钱包
	blockno = sectno * 4;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控主钱包失败");
		return -1;
	}
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+2,buffer1);
	if(nRet)
	{
		SET_ERR("读取水控备钱包失败");
		return -1;
	}
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+1,ctrlbuffer);
	if(nRet)
	{
		SET_ERR("读取水控钱包控制块失败");
		return -1;
	}
	if(memcmp(buffer,buffer1,16)!=0)
	{
		if(ctrlbuffer[0] != 'O' || ctrlbuffer[1] != 'K')
		{
			memcpy(buffer,buffer1,16); // 以备为准
		}
	}

	//current_money=get_2byte_int(buffer+5);
	current_money=pack->money;
	pack->totalmoney = current_money;
	set_2byte_int(buffer+6,current_money);

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("写水控主钱包失败");
		return -1;
	}
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+2,buffer);
	if(nRet)
	{
		SET_ERR("写水控主钱包失败");
		return -1;
	}
	ctrlbuffer[0] = 'O';
	ctrlbuffer[1] = 'K';
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+1,ctrlbuffer);
	if(nRet)
	{
		SET_ERR("写水控钱包控制块失败");
		return -1;
	}
	
	// 更新水控前一扇区
	sectno = m_lldfSect;
	nRet=this->LoginCardSect(sectno);
	if(nRet)
	{
		SET_ERR("登录水控钱包失败");
		return -1;
	}
	blockno = sectno * 4 + 2;
	memset(buffer,0,sizeof buffer);
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("读取水控参数失败");
		return -1;
	}
	set_2byte_int(buffer+2,current_money);
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(nRet)
	{
		SET_ERR("更新水控参数失败");
		return -1;
	}
	dec2hex(buffer,16,msg);
	//SET_ERR("lldf["<<msg<<"]");
	return 0;
}
/// 联机通用水控
int ks_mfcard_type::legacy_water_publishcard(ks_water_pack_t *pack)
{
	int j=0,nRet = 0;
	int sectno = 0;						
	int money = 0;
	byte data_buffer[16],data_buffer2[16];
	char datetime[20]="";
	char temp[10] = "";
	
	if(this->m_keyAlg ==0)
	{
		if(this->m_CardKeys.bLoad ==0 && m_isLoadKey == 0)
		{
			SET_ERR("Mifare1密钥未装载");
			return KS_UNAUTH_TERM;
		}
	}
	
	memset(data_buffer,0,sizeof data_buffer);


	sectno = m_secdPackSect;
	if((nRet = LoginCardSect(sectno))!=0)
	{		
		SET_ERR("登录扇区["<<sectno<<"]失败");
		return nRet;
	}
	money = pack->money;
	data_buffer[0] = money % 256;						// 这样算有问题，只是money值太小，没暴露
	data_buffer[1] = money / 256;
	data_buffer[2] = money / 256 / 256;
	data_buffer[3] = 0;
	data_buffer[4] = 1;
	GetCurrentDateTime(datetime);
	for(j=0;j<5;++j)
	{
		memset(temp,0,sizeof temp);
		memcpy(temp,datetime+2+j*2,2);
		data_buffer[5+j] = atoi(temp);
	}
	for(j=0,data_buffer[15]=0;j<15;++j)
		data_buffer[15] += data_buffer[j];

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,data_buffer);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4<<"]块写卡内容失败");
		return KS_WRITECARD;
	}

	memset(data_buffer2,0,sizeof data_buffer2);
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,data_buffer2);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4<<"]块读卡内容失败");
		return KS_READCARD;
	}

	if(memcmp(data_buffer,data_buffer2,16) != 0)
		return KS_WRITECARD;
	
	
	return 0;
}
int ks_mfcard_type::legacy_water_recyclecard()
{
	
	int j,nRet;
	int sectno = 0;
	byte init_keya[6],origin_ctrlbit[4];
	byte buffer[16],buffer2[16];

	//if(watertype == KS_LEGACY_WATER)									// 三九水控
	sectno = m_secdPackSect;									
	
	if(this->m_keyAlg ==0)
	{
		if(this->m_CardKeys.bLoad ==0 && m_isLoadKey == 0)
		{
			SET_ERR("Mifare1密钥未装载");
			return KS_UNAUTH_TERM;
		}
	}
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;
	
	memset(buffer2,0,sizeof buffer2);
	for(j = 0;j<3;++j)
	{
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+j,buffer2);
		if(nRet)
		{
			SET_ERR("初始化扇区["<<sectno<<"]写数据失败，请重试");
			return KS_WRITECARD;
		}
	}

	return 0;
}
int ks_mfcard_type::legacy_water_readmoney(ks_water_pack_t *pack)
{
	int j,nRet;
	int sectno = 0;
	byte buffer[16],data_crc=0,data_or=0,data_xor = 0;

	IS_LOAD_KEY();
	
	sectno = m_secdPackSect;						
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer);
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}
	for(j=0,data_crc=0,data_or=0;j<15;j++)
	{
		data_crc += buffer[j];
		data_or |= buffer[j];
	}

	//if(data_crc != buffer[15] || data_or == 0)	// 校验和不对或数据全为0，从备钱包恢复
	if(data_crc != buffer[15])
	{
		data_crc = 0;
		data_or = 0;
		memset(buffer,0,sizeof buffer);
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
		if(nRet)
		{
			SET_ERR("读扇区"<<sectno<<"数据失败");
			return KS_READCARD;
		}
		for(j=0;j<15;j++)
		{
			data_crc += buffer[j];
			data_or |= buffer[j];
		}

		if(data_crc != buffer[15] )		// 备份块也有问题
			return KS_PURSECRCERR;

		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer);	
		if(nRet)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}
	}

	pack->money = buffer[0] + buffer[1]*256 + buffer[2]*256*256;
	return 0;
}
int ks_mfcard_type::legacy_water_writemoney(ks_water_pack_t *pack)
{
	int j,nRet,money,cnt;
	int sectno = 0,money_hig,money_low,old_money,old_addmoney,old_addcnt;
	byte buffer[16],buffer2[16],data_crc=0,data_or=0,data_xor=0;
	char datetime[20]="";
	char temp[10] = "";
	
	IS_LOAD_KEY();

	sectno = m_secdPackSect;						
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer);
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}
	for(j=0;j<15;j++)
	{
		data_crc += buffer[j];
		data_or |= buffer[j];
	}

	if(data_crc != buffer[15] )	// 主钱包校验和不对或数据全为0，校验备份钱包，以免读钱包有问题
	{
		data_crc = 0;
		data_or = 0;
		memset(buffer,0,sizeof buffer);
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
		if(nRet)
		{
			SET_ERR("读扇区"<<sectno<<"数据失败");
			return KS_READCARD;
		}
		for(j=0;j<15;j++)
		{
			data_crc += buffer[j];
			data_or |= buffer[j];
		}
		if(data_crc != buffer[15] )		// 备份块也有问题
			return KS_PURSECRCERR;
	}
	else		// 先备份数据
	{
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
		if(nRet)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}
	}

	// 写新数据
	money = pack->money;
	buffer[0] = money % 256;
	buffer[1] = money / 256;
	buffer[2] = money / 256 / 256;
	cnt = buffer[3]*256+buffer[4] + 1;
	buffer[3] = cnt/256;
	buffer[4] = cnt%256;

	// 传入的是卡余额而不是消费金额,日累计消费额怎么加起来的？？
	GetCurrentDateTime(datetime);
	for(j=0;j<5;++j)
	{
		memset(temp,0,sizeof temp);
		memcpy(temp,datetime+2+j*2,2);
		buffer[5+j] = atoi(temp);
	}

	for(j=0,buffer[15]=0;j<15;++j)
		buffer[15] += buffer[j];

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer);	
	if(nRet)
	{
		SET_ERR("写扇区"<<sectno<<"数据失败");
		return KS_WRITECARD;
	}

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer2);	
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}

	if(memcmp(buffer,buffer2,16)!=0)
	{
		SET_ERR("Mifare1写水控余额错误");
		return KS_WRITEPURSE;
	}

	// 电大修改黑卡标志
	sectno = 3;					// 第3扇区第2块写黑卡标志
	memset(buffer2,0,sizeof buffer2);
	data_or = 0;
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer2);	
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}
	for (j=0;j<16;j++)
		data_or |= buffer2[j];
	if(data_or == 0)				// 数据全是0
	{
		buffer2[0] = 1;
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer2);	
		if(nRet)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}
	}
	return 0;
}
// 汇多脱机水控
int ks_mfcard_type::hd_water_publishcard(ks_water_pack_t *pack)
{
	int j=0,nRet = 0;
	int sectno = 0;						
	int money = 0;
	byte data_buffer[16],data_buffer2[16];
	char datetime[20]="";
	char temp[10] = "";
	
	if(this->m_keyAlg ==0)
	{
		if(this->m_CardKeys.bLoad ==0 && m_isLoadKey == 0)
		{
			SET_ERR("Mifare1密钥未装载");
			return KS_UNAUTH_TERM;
		}
	}
	
	memset(data_buffer,0,sizeof data_buffer);
	
	sectno = m_offlinewater;								// 没配置的话就是10扇区
	if((nRet = LoginCardSect(sectno))!=0)
	{		
		SET_ERR("登录扇区["<<sectno<<"]失败");
		return nRet;
	}
	//卡余额
	money = pack->money;
	int money_low = money%(256*256);
	data_buffer[0] = money / 256 / 256;
	data_buffer[1] = money_low / 256;
	data_buffer[2] = money_low % 256;
	//累计充值金额
	int money_high = data_buffer[0];		// 高2位的值
	data_buffer[3] = money_high/256;
	data_buffer[4] = money_high%256;
	data_buffer[5] = data_buffer[1];
	data_buffer[6] = data_buffer[2];
	//水价1
	data_buffer[7] = pack->price1/256;
	data_buffer[8] = pack->price1%256;
	//水价2
	data_buffer[9] = pack->price2/256;
	data_buffer[10] = pack->price2%256;
	//水价3
	data_buffer[11] = pack->price3/256;
	data_buffer[12] = pack->price3%256;
	//充值次数
	data_buffer[13] = 0;
	if(pack->money>0)
		data_buffer[14] = 1;
	else
		data_buffer[14] = 0;
	for (j=0;j<15;j++)
		data_buffer[15]^=data_buffer[j];

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,data_buffer);		// 写主钱包
	if(nRet)
	{
		SET_ERR("第["<<sectno*4<<"]块写卡内容失败");
		return KS_WRITECARD;
	}
	
	// 校验钱包数据是否写正确
	memset(data_buffer2,0,sizeof data_buffer2);		
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,data_buffer2);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4<<"]块读卡内容失败");
		return KS_READCARD;
	}

	if(memcmp(data_buffer,data_buffer2,16) != 0)
		return KS_WRITECARD;
	
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,data_buffer);		// 写备钱包
	if(nRet)
	{
		SET_ERR("第["<<sectno*4+1<<"]块写卡内容失败");
		return KS_WRITECARD;
	}
	memset(data_buffer,0,sizeof data_buffer);
	//卡号
	data_buffer[0] = pack->cardno/256/256;
	int cardno_low = pack->cardno%(256*256);
	data_buffer[1] = cardno_low/256;
	data_buffer[2] = cardno_low%256;
	//类别
	data_buffer[3] = pack->cardtype;
	//有效期
	char tmp[3]="";
	memcpy(tmp,pack->expireddate+2,2);		// 年
	data_buffer[4] = atoi(tmp);
	memcpy(tmp,pack->expireddate+4,2);		// 月
	data_buffer[5] = atoi(tmp);
	memcpy(tmp,pack->expireddate+6,2);		// 日
	data_buffer[6] =  atoi(tmp);
	//标志
	data_buffer[7] = pack->lockflag;
	memcpy(data_buffer+8,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF",7);
	for (j=0;j<15;j++)
		data_buffer[15]^= data_buffer[j];
	
	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,data_buffer);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4+2<<"]块写卡内容失败");
		return KS_WRITECARD;
	}
	
	// 校验基本信息是否写正确
	memset(data_buffer2,0,sizeof data_buffer2);
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,data_buffer2);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4+2<<"]块读卡内容失败");
		return KS_READCARD;
	}

	if(memcmp(data_buffer,data_buffer2,16) != 0)
		return KS_WRITECARD;

	
	return 0;
}
int ks_mfcard_type::hd_water_recyclecard()
{
	
	int j,nRet;
	int sectno = 0;
	byte init_keya[6],origin_ctrlbit[4];
	byte buffer[16],buffer2[16];
									
	//if(watertype == KS_HD_WATER)									// 汇多
	sectno = m_offlinewater;		
	
	if(this->m_keyAlg ==0)
	{
		if(this->m_CardKeys.bLoad ==0 && m_isLoadKey == 0)
		{
			SET_ERR("Mifare1密钥未装载");
			return KS_UNAUTH_TERM;
		}
	}
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;

	memset(buffer2,0,sizeof buffer2);
	for(j = 0;j<3;++j)
	{
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+j,buffer2);
		if(nRet)
		{
			SET_ERR("初始化扇区["<<sectno<<"]写数据失败，请重试");
			return KS_WRITECARD;
		}
	}

	return 0;
}
int ks_mfcard_type::hd_water_readmoney(ks_water_pack_t *pack)
{
	int j,nRet;
	int sectno = 0;
	byte buffer[16],data_crc=0,data_or=0,data_xor = 0;

	IS_LOAD_KEY();
	
	sectno = m_offlinewater;					
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer);
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}
	for(j=0;j<15;j++)
		data_xor^= buffer[j];
	if(data_xor != buffer[15])										// 校验不对，从备钱包恢复
	{
		memset(buffer,0,sizeof buffer);
		data_xor = 0;
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);
		if(nRet)
		{
			SET_ERR("读扇区"<<sectno<<"数据失败");
			return KS_READCARD;
		}
		for(j=0;j<15;j++)
			data_xor^= buffer[j];

		if(data_crc != buffer[15] )		// 备份块也有问题
			return KS_PURSECRCERR;
		
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer);	// 写备份块到主钱包块
		if(nRet)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}
	}
	pack->money = buffer[0]*256*256+buffer[1]*256+buffer[2];
	pack->totalmoney = (buffer[3]*256+buffer[4])*256*256 + buffer[5]*256+buffer[6];
	pack->price1 = buffer[7]*256+buffer[8];
	pack->price2 = buffer[9]*256+buffer[10];
	pack->price3 = buffer[11]*256+buffer[12];
	pack->addcount = buffer[13]*256 + buffer[14];
	
	memset(buffer,0,sizeof buffer);
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}
	
	pack->cardno = buffer[0]*256*256 + buffer[1]*256 + buffer[2];
	pack->cardtype = buffer[3];
	sprintf(pack->expireddate,"20%02d%02d%02d",buffer[4],buffer[5],buffer[6]);
	pack->lockflag = buffer[7];
	return 0;
}
int ks_mfcard_type::hd_water_writemoney(ks_water_pack_t *pack)
{
	int j,nRet,money,cnt;
	int sectno = 0,money_hig,money_low,old_money,old_addmoney,old_addcnt;
	byte buffer[16],buffer2[16],data_crc=0,data_or=0,data_xor=0;
	char datetime[20]="";
	char temp[10] = "";
	
	IS_LOAD_KEY();

	
	sectno = m_offlinewater;						
	if((nRet = LoginCardSect(sectno))!=0)
		return nRet;
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer);
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}
	for(j=0,data_xor = 0;j<15;j++)
		data_xor^= buffer[j];
	if(data_xor != buffer[15])	//主钱包有问题，校验备份钱包
	{
		memset(buffer,0,sizeof buffer);
		nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);
		if(nRet)
		{
			SET_ERR("读扇区"<<sectno<<"数据失败");
			return KS_READCARD;
		}
		for(j=0,data_xor = 0;j<15;j++)
			data_xor^= buffer[j];
		if(data_xor != buffer[15] )		// 备份块也有问题
			return KS_PURSECRCERR;
	}
	else		// 先备份数据
	{
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);
		if(nRet)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}
	}
	// 写新数据
	old_money = buffer[0]*256*256+buffer[1]*256+buffer[2];

	buffer[0] = pack->money/256/256;
	money_low = pack->money%(256*256);
	buffer[1] = money_low/256;
	buffer[2] = money_low%256;

	if(pack->money > old_money)				// 充值，要累积充值金额，次数
	{
		old_addmoney = (buffer[3]*256+buffer[4])*256*256 + buffer[5]*256+buffer[6];
		old_addmoney += pack->money - old_money;
		money_hig = old_addmoney /256/256;
		buffer[3] = money_hig/256;
		buffer[4] = money_hig%256;
		money_low = old_addmoney%(256*256);
		buffer[5] = money_low/256;
		buffer[6] = money_low%256;
		
		old_addcnt = buffer[13]*256+buffer[14];
		old_addcnt++;
		buffer[13] = old_addcnt/256;
		buffer[14] = old_addcnt%256;
	}
	//水价1
	buffer[7] = pack->price1/256;
	buffer[8] = pack->price1%256;
	//水价2
	buffer[9] = pack->price2/256;
	buffer[10] = pack->price2%256;
	//水价3
	buffer[11] = pack->price3/256;
	buffer[12] = pack->price3%256;

	for(j=0,buffer[15]=0;j<15;++j)
		buffer[15] ^= buffer[j];

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer);	
	if(nRet)
	{
		SET_ERR("写扇区"<<sectno<<"数据失败");
		return KS_WRITECARD;
	}

	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer2);	
	if(nRet)
	{
		SET_ERR("读扇区"<<sectno<<"数据失败");
		return KS_READCARD;
	}

	if(memcmp(buffer,buffer2,16)!=0)
	{
		SET_ERR("Mifare1写水控余额错误");
		return KS_WRITEPURSE;
	}

	// 更新有效期
	memset(buffer,0,sizeof buffer);		
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4+2<<"]块读卡内容失败");
		return KS_READCARD;
	}
	//有效期
	char tmp[3]="";
	memcpy(tmp,pack->expireddate+2,2);		// 年
	buffer[4] = atoi(tmp);
	memcpy(tmp,pack->expireddate+4,2);		// 月
	buffer[5] = atoi(tmp);
	memcpy(tmp,pack->expireddate+6,2);		// 日
	buffer[6] =  atoi(tmp);
	//标志
	buffer[7] = pack->lockflag;
	for (j=0,buffer[15]=0;j<15;j++)
		buffer[15]^= buffer[j];

	nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4+2<<"]块写卡内容失败");
		return KS_WRITECARD;
	}

	// 校验基本信息是否写正确
	memset(buffer2,0,sizeof buffer2);
	nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+2,buffer2);
	if(nRet)
	{
		SET_ERR("第["<<sectno*4+2<<"]块读卡内容失败");
		return KS_READCARD;
	}

	if(memcmp(buffer,buffer2,16) != 0)
		return KS_WRITECARD;

	
	return 0;
}

int ks_mfcard_type::water_publishparamcard(int watertype,ks_water_param_t *param)
{
	int ret = 0,j=0;
	int sectno = 0;
	int watersect=0;
	byte buffer[16]="";
	byte ctldata[16]="";
	byte workkey[8]="";
	if(watertype ==	KS_HD_WATER)		// 汇多水控卡
	{
		sectno = 15;
		watersect = m_offlinewater;
		if((ret = LoginHDWaterParamCardSect(sectno))!=0)
			return ret;
		
		memset(buffer,0,sizeof buffer);			
		memcpy(buffer,m_offlinewaterkey,8);					//钱包种子密钥
		buffer[8] = param->minmoney/256;					//预警金额
		buffer[9] = param->minmoney%256;

		buffer[10] = param->maxmoney/256/256;				//钱包上限
		buffer[11] = param->maxmoney/256;	
		buffer[12] = param->maxmoney%256;		

		buffer[13] = param->unit/256;						//计费单位
		buffer[14] = param->unit%256;						//计费单位

		for(j=0;j<15;j++)
			buffer[15] ^= buffer[j];

		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4,buffer);			// 第0块
		if(ret)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}

		memset(buffer,0,sizeof buffer);
		buffer[0]= param->transmoney/256;				//单次转账金额
		buffer[1]= param->transmoney%256;
		buffer[2]= 1;									//水价索引
		buffer[3]= watersect;							//水控钱包扇区
		buffer[4]= param->cardflag;						//水控卡标志
		memcpy(buffer+5,"\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF",10);
		for(j=0;j<15;j++)
			buffer[15] ^= buffer[j];

		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);		//第1块
		if(ret)
		{
			SET_ERR("写扇区"<<sectno<<"数据失败");
			return KS_WRITECARD;
		}
		
		GenHdWaterParamKeyA(ctldata);
		memcpy(ctldata+6,MF1_INIT_CTRLBIT,4);
		memcpy(ctldata+10,ctldata,6);
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+3,ctldata);		//第3块
		if(ret)
		{
			SET_ERR("写扇区"<<sectno<<"控制数据失败");
			return KS_WRITECARD;
		}		
	}
	else
		return KS_NOTSUPPORT;
	return 0;
}
int ks_mfcard_type::water_recycleparamcard(int watertype)
{
	int j,nRet,sectno = 0;
	byte buffer[16],ctldata[16];

	memset(buffer,0,sizeof buffer);
	memset(ctldata,0,sizeof ctldata);

	memcpy(ctldata,m_initLoginKey,6);
	memcpy(ctldata+6,MF1_ORIGIN_CTRLBIT,4);
	memcpy(ctldata+10,m_initLoginKey,6);
	
	
	if(watertype == KS_LEGACY_WATER)			// 老的水控费率卡
	{
		for(sectno=0;sectno<32;sectno++)
		{
			if((nRet = LoginLegacyWaterCardSect(sectno,false))!=0)
				return nRet;
			for(j = 0;j<3;++j)
			{
				if(sectno==0 && j==0)
					continue;
				nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+j,buffer);
				if(nRet)
				{
					SET_ERR("回收扇区["<<sectno<<"]写数据失败，请重试");
					return KS_WRITECARD;
				}
			}
			nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+3,ctldata);
			if(nRet)
			{
				SET_ERR("回收扇区["<<sectno<<"]写控制数据失败，请重试");
				return KS_WRITECARD;
			}
		}
	}
	else if(watertype == KS_HD_WATER)			// 汇多水控费率卡
	{
		sectno = 15;
		if((nRet = LoginHDWaterParamCardSect(sectno,false))!=0)
			return nRet;
		for(j = 0;j<3;++j)
		{
			nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+j,buffer);
			if(nRet)
			{
				SET_ERR("回收扇区["<<sectno<<"]写数据失败，请重试");
				return KS_WRITECARD;
			}
		}
		nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,sectno*4+3,ctldata);
		if(nRet)
		{
			SET_ERR("回收扇区["<<sectno<<"]写控制数据失败，请重试");
			return KS_WRITECARD;
		}
	}
	else
		return KS_NOTSUPPORT;	

	return 0;
}

int ks_mfcard_type::water_read_paramcard(int watertype,ks_water_param_t *param)
{
	int ret = 0,j=0;
	int sectno = 0,data_xor=0;
	byte buffer[16]="";
	byte workkey[8]="";
	if(watertype == KS_HD_WATER)
	{
		sectno = 15;
		if((ret = LoginHDWaterParamCardSect(sectno))!=0)
			return ret;

		ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4,buffer);	
		if(ret)
		{
			SET_ERR("读扇区"<<sectno<<"数据失败");
			return KS_READCARD;
		}
		for(j=0,data_xor=0;j<15;j++)
			data_xor^= buffer[j];
		if(data_xor != buffer[15])
			return KS_PURSECRCERR;
			
		//memcpy(workkey,buffer,8);
		encrypt_work_key(buffer,workkey);
		dec2hex(workkey,8,param->workkey);

		param->minmoney = buffer[8]*256+buffer[9];
		param->maxmoney = buffer[10]*256*256+buffer[11]*256+buffer[12];
		param->unit = buffer[13]*256+buffer[14];

		memset(buffer,0,sizeof buffer);
		ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sectno*4+1,buffer);	
		if(ret)
		{
			SET_ERR("读扇区"<<sectno<<"数据失败");
			return KS_READCARD;
		}
		for(j=0,data_xor=0;j<15;j++)
			data_xor^= buffer[j];
		if(data_xor != buffer[15])
			return KS_PURSECRCERR;

		param->transmoney = buffer[0]*256+buffer[1];
		param->priceindex = buffer[2];
		param->watersect = buffer[3];
		param->cardflag = buffer[4];
	}
	else 
		return KS_NOTSUPPORT;	
	
	return 0;
}
void ks_mfcard_type::GenHdWaterParamKeyA(byte keyA[6])
{	
	int len=0;
	char str_keyA[13]="2355337812AB";
	hex2dec(str_keyA,12,keyA,len);
}
void ks_mfcard_type::GenLegacyWaterKeyA(byte keyA[6])
{
	unsigned char i;	
	unsigned int BCC;

	BCC = 0;
	for(i=0;i<4;i++)
		BCC += m_OriginPhyNo[i];

	memcpy(keyA,m_OriginPhyNo,4);
	keyA[4] =(unsigned char)(BCC>>8);
	keyA[5]	=(unsigned char)BCC;
	return;
}
void ks_mfcard_type::GenLegacyWaterCtlBlock(byte ctldata[16])
{
	byte keyA[6];
	GenLegacyWaterKeyA(keyA);
	memcpy(ctldata,keyA,6);
	memcpy(ctldata+6,MF1_INIT_CTRLBIT,4);
	memcpy(ctldata+10,keyA,6);
}


void ks_mfcard_type::DumpCardBlockData(int sect,int block,BYTE *buf)
{
	int i;
	char temp[3]="";
	if(g_dump_file)
	{
		fprintf(g_dump_file,"sect[%02d],block[%02d][",sect,block);
		for(i = 0;i < 16;++i)
		{
			fprintf(g_dump_file,"%02X",buf[i]);
		}
		fprintf(g_dump_file,"]\r\n");
	}
}

void ks_mfcard_type::DumpSectData(int watertype)
{
	int nRet=0;
	byte buffer[16];
	if(watertype != KS_LEGACY_WATER)
		return;
	if(g_dump_file==NULL)
	{
		g_dump_file = fopen("dump.txt","a+b");
		if(g_dump_file == NULL)
		{
			return;
		}
	}
	
	for(int sect=0;sect<32;sect++)
	{
		if((nRet = LoginLegacyWaterCardSect(sect,false))!=0)
			continue;;
		for(int j=0;j<4;j++)
		{
			memset(buffer,0,sizeof buffer);
			nRet = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+j,buffer);
			if(nRet)
				continue;
			DumpCardBlockData(sect,sect*4+j,buffer);
		}		
	}

	if(g_dump_file)
	{
		fclose(g_dump_file);
		g_dump_file = NULL;
	}
}
int ks_mfcard_type::water_publish_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate)
{
	if(watertype != KS_LEGACY_WATER)
		return KS_NOTSUPPORT;
	
	int ret = 0;
	int sect = 0;
	int block = 1;
	int block_num = 0;
	short fee_rate_data_length = 0;
	char msg[128] = "";
	BYTE buf[16] = "",ctldata[16]="";
	BYTE right_type_bit[32] = "";
	BYTE check_crc = 0;
	BYTE auth_key[8] = "";
	BYTE temp = 0;
	int offset = 0;
	int right_type_num = 0;

	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate->fee_right_num[right_type_num].right_flag)
			continue;
		fee_rate_data_length += fee_rate->fee_right_num[right_type_num].right_num * 3 + 1;
	}

	BYTE fee_rate_data_buf[512] = "";
	// 数据区长度
	fee_rate_data_buf[0] = fee_rate_data_length >> 8 & 0xff;
	fee_rate_data_buf[1] = fee_rate_data_length & 0xff;

	if((ret = LoginLegacyWaterCardSect(sect))!=0)			// 第0扇区
		return ret;
	memset(buf,0,sizeof buf);
	memcpy(buf, fee_rate->water_card_flag, offset += (sizeof(fee_rate->water_card_flag) -1));
	buf[offset] = fee_rate->packet_num;
	offset += sizeof(fee_rate->packet_num);

	buf[offset] = fee_rate->work_mode;
	offset += sizeof(fee_rate->work_mode);

	//	memset(buf + offset, 0xFF, 16 - offset);						全FF则check_crc越界
	for (int address = 0; address < 15; address++)
	{
		buf[15] += buf[address];
	}
	
	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,1,buf);			// 0扇区第1块
	if(ret)
	{
		SET_ERR("写扇区"<<sect<<"数据失败");
		return KS_WRITECARD;
	}

	memset(buf, 0x00, sizeof(buf));
	encrypt_work_key(fee_rate->main_work_key, auth_key);
	memcpy(buf, auth_key, sizeof(BYTE) * 8);				
	encrypt_work_key(fee_rate->packet_work_key, auth_key);
	memcpy(buf + 8, auth_key, sizeof(BYTE) * 8);

	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,2,buf);			// 0扇区第2块
	if(ret)
	{
		SET_ERR("写扇区"<<sect<<"数据失败");
		return KS_WRITECARD;
	}

	GenLegacyWaterCtlBlock(ctldata);
	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,3,ctldata);			// 0扇区第3块
	if(ret)
	{
		SET_ERR("写扇区"<<sect<<"控制数据失败");
		return KS_WRITECARD;
	}

	sect = 1;			// 第一扇区0块开始以后每个块都能够用
	block = 0;
	offset = 2;
	check_crc = 0;
	// 收费扇区设置
	memset(buf, 0x00, sizeof(buf) - 1);
	for (right_type_num = 0; right_type_num < 256; right_type_num++)
	{
		if (0 == fee_rate->fee_right_num[right_type_num].right_flag)
			continue;
		right_type_bit[(255 - right_type_num) / 8] |= 1 << (right_type_num % 8);
		memcpy(fee_rate_data_buf + offset, &(fee_rate->fee_right_num[right_type_num].right_num), sizeof BYTE);

		check_crc += fee_rate->fee_right_num[right_type_num].right_num;		// 累加效验和
			
		for (int right_num = 0; right_num < fee_rate->fee_right_num[right_type_num].right_num; right_num++)
		{
			memcpy(fee_rate_data_buf + offset + 1, &(fee_rate->fee_right_num[right_type_num].fee_rate[right_num].time_ladder), 1);
			memcpy(fee_rate_data_buf + offset + 2, &(fee_rate->fee_right_num[right_type_num].fee_rate[right_num].deduct_time), 1);
			memcpy(fee_rate_data_buf + offset + 3, &(fee_rate->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee), 1);
			check_crc += fee_rate->fee_right_num[right_type_num].fee_rate[right_num].time_ladder[0] + 
				fee_rate->fee_right_num[right_type_num].fee_rate[right_num].deduct_time[0] +
				fee_rate->fee_right_num[right_type_num].fee_rate[right_num].deduct_fee[0]; 
			offset += 3;	// 里层循环+3
		}
		offset += 1;		// 外层+1添加一个字节的权限费率个数
	}

	// 登陆第一扇区的块0和块1, 写入权限位图
	if((ret = LoginLegacyWaterCardSect(sect))!=0)			// 第1扇区
		return ret;

	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sect*4,right_type_bit);			// 1扇区第0块
	if(ret)
	{
		SET_ERR("写扇区"<<sect<<"数据失败");
		return KS_WRITECARD;
	}
	
	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sect*4+1,right_type_bit+16);		// 1扇区第1块
	if(ret)
	{
		SET_ERR("写扇区"<<sect<<"数据失败");
		return KS_WRITECARD;
	}

	int block_byte_num = 0;
	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;

	block = 2;															// block = 2的时候进来
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// 计算出来的扇区块数目进行比较
	{
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sect*4+block,fee_rate_data_buf + block_byte_num);	
		if(ret)
		{
			SET_ERR("写扇区"<<sect<<"数据失败");
			return KS_WRITECARD;
		}

		block_byte_num += 16;
		++block_num;													// 已经写入一个块
		++block;

		if (block > 2)													// 到控制块了
		{
			ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sect*4+block,ctldata);
			if(ret)
			{
				SET_ERR("写扇区"<<sect<<"控制数据失败");
				return KS_WRITECARD;
			}
			block = 0;
			++sect;

			if((ret = LoginLegacyWaterCardSect(sect))!=0)			// 登录下一个扇区
				return ret;
		}
		// 拷贝剩余数据
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
				//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sect*4+block,fee_rate_data_buf + block_byte_num);
				if(ret)
				{
					SET_ERR("写扇区"<<sect<<"数据失败");
					return KS_WRITECARD;
				}
				break;
			}
			else
			{
				break;
			}
		}
	}

	while (sect<32)
	{
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,sect*4+3,ctldata);
		if(ret)
		{
			SET_ERR("写扇区"<<sect<<"控制数据失败");
			return KS_WRITECARD;
		}
		++sect;

		if((ret = LoginLegacyWaterCardSect(sect))!=0)			// 登录下一个扇区
			return ret;
	}
	return 0;
}

int ks_mfcard_type::water_read_legacycard(int watertype,FEE_RATE_CARD_INFO * fee_rate)
{
	if(watertype != KS_LEGACY_WATER)
		return KS_NOTSUPPORT;

	int sect = 0;
	int block = 1;
	int ret = 0;
	int fee_rate_data_length = 0;
	int right_type_num = 0;
	int offset = 0;
	int block_num = 0;
	int block_byte_num = 0;
	BYTE fee_rate_count = 0;
	BYTE buf[17] = "";
	BYTE right_type_bit[33] = "";
	BYTE fee_rate_data_buf[512] = "";
	char msg[128] = "";
	if ((ret=LoginLegacyWaterCardSect(sect,false)) != 0)
	{
		return ret;
	}
	//ret = SMT_ReadBlock(sect, block, buf);
	ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,buf);
	if(ret)
	{
		SET_ERR("读扇区"<<sect<<"数据失败");
		return KS_READCARD;
	}
	memcpy(fee_rate->water_card_flag, buf, sizeof(fee_rate->water_card_flag) - 1);
	memcpy(&(fee_rate->packet_num), buf + 4, sizeof(fee_rate->packet_num));
	memcpy(&(fee_rate->work_mode), buf + 5, sizeof(fee_rate->work_mode));		// 工作地点00:公寓 FF: 浴室
	memcpy(fee_rate->check_crc, buf + 15, sizeof(fee_rate->check_crc) - 1);
	block++;
	memset(buf, 0, sizeof(buf) - 1);
	ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,buf);
	if(ret)
	{
		SET_ERR("读扇区"<<sect<<"数据失败");
		return KS_READCARD;
	}
	memcpy(fee_rate->main_work_key, buf, sizeof(fee_rate->main_work_key) - 1);
	memcpy(fee_rate->packet_work_key, buf + 8, sizeof(fee_rate->packet_work_key) - 1);

	sect = 1;
	block = 0;
	if ((ret=LoginLegacyWaterCardSect(sect,false)) != 0)
	{
		return ret;
	}
	ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,right_type_bit);
	if(ret)
	{
		SET_ERR("读扇区"<<sect<<"数据失败");
		return KS_READCARD;
	}

	block = 1;
	ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,right_type_bit + 16);
	if(ret)
	{
		SET_ERR("读扇区"<<sect<<"数据失败");
		return KS_READCARD;
	}
	block = 2;
	ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,buf);
	if(ret)
	{
		SET_ERR("读扇区"<<sect<<"数据失败");
		return KS_READCARD;
	}
	memcpy(fee_rate->data_length, buf, sizeof(BYTE) * 2);
	//memcpy(&fee_rate_data_length, fee_rate->data_length, sizeof(BYTE) * 2);
	//fee_rate->data_length = ((buf[0] << 8) & 0xff00) | buf[1];
	fee_rate_data_length = ((buf[0] << 8) & 0xff00) | buf[1];
	//	fee_rate_data_length = fee_rate->data_length;
	//	memcpy(&fee_rate_count, buf + 2, sizeof(fee_rate_count));	
	//	fee_rate_data_buf[fee_rate_data_length + 2] = check_crc;
	// block = 2的时候进来
	while (block_num < 1 + (fee_rate_data_length + 2) / 16)				// 计算出来的扇区块数目进行比较
	{

		if ((ret=LoginLegacyWaterCardSect(sect,false)) != 0)
		{
			return ret;
		}
		ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,fee_rate_data_buf + block_byte_num);
		if(ret)
		{
			SET_ERR("读扇区"<<sect<<"数据失败");
			return KS_READCARD;
		}
		block_byte_num += 16;
		++block_num;													// 已经写入一个块
		++block;

		if (block > 2)
		{
			block = 0;
			++sect;
			continue;
		}
		// 拷贝剩余数据
		if ((fee_rate_data_length + 2) / 16 == block_num)
		{
			if ((fee_rate_data_length + 2) % 16 > 0)
			{
				//	block_byte_num += (fee_rate_data_length + 2) % 16;
				ret = m_Reader->read_block(m_ReaderPara,m_mfcard,sect*4+block,fee_rate_data_buf + block_byte_num);
				if(ret)
				{
					SET_ERR("读扇区"<<sect<<"数据失败");
					return KS_READCARD;
				}		
			}
			++block_num;
		}
	}

	memcpy(fee_rate->check_crc, &fee_rate_data_buf[fee_rate_data_length + 2], sizeof(BYTE));

	offset = 2;
	for (right_type_num = 0; right_type_num < 32; right_type_num++)
	{
		if (right_type_bit[31 - right_type_num] != 0)
		{
			for (int bit = 0; bit < 8; bit++)
			{
				if ((right_type_bit[31 - right_type_num] & (1 << bit)) != 0)
				{
					fee_rate->fee_right_num[right_type_num * 8 + bit].right_flag = 1;
					fee_rate->fee_right_num[right_type_num * 8 + bit].right_num = fee_rate_data_buf[offset];
					offset += 1;
					for (int count = 0; count < fee_rate->fee_right_num[right_type_num * 8 + bit].right_num; count++)
					{
						memcpy(&(fee_rate->fee_right_num[right_type_num * 8 + bit].fee_rate[count]), fee_rate_data_buf + offset, sizeof(BYTE) * 3);
						offset += 3;
					}
					//					offset += 1;
				}			
			}
		}
	}
	return 0;
}
/////////////////////////////////////////////////////////////////////////

int KSAPI register_cardtype_op(ks_cardtype_base *&op)
{
	op = new ks_mfcard_type();
	return 0;
}
