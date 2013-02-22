#include "ks_yncs_cardtype.h"
#include "des.h"
#include "global_func.h"
#include "mystring.h"


#define INVALID_KEY_LEN  -1	//������Ч
#define INVALID_DATA_LEN  -2	//������Ч

#define MAX_USED_SECTNO 16

//static ks_yncs_cardtype g_CardType;

static void set_3byte_money(unsigned char *buffer,int money)
{
	buffer[0] = money & 0xFF;
	buffer[1] = (money / 256) % 256;
	buffer[2] = (money / 256 / 256) % 256;
}
static int get_3byte_money(unsigned char *buffer)
{
	int t;
	t = buffer[0] + buffer[1] * 256 + buffer[2] * 256 * 256;
	return t;
}
static void set_4byte_money(unsigned char *buffer,int money)
{
	buffer[0] = money & 0xFF;
	buffer[1] = (money / 256) % 256;
	buffer[2] = (money / 256 / 256) % 256;
	buffer[4] = (money/256/256/256) % 256;
}
static int get_4byte_money(unsigned char *buffer)
{
	int t;
	t = buffer[0] + buffer[1] * 256 + buffer[2] * 256 * 256 + buffer[3] * 256 * 256 * 256;
	return t;
}


unsigned char ks_yncs_cardtype::DACK1[] = "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF";

ks_yncs_cardtype::ks_yncs_cardtype():CCardType(),m_hd_water_sect(-1),m_xt_water_sect(-1),m_is_params_load(0)
	,m_xt_water_max_money(0)
{
	set_cardtype_name("ks_yncs_cardtype.dll");
    //memcpy(m_hd_mainkey,"\x45\x56\x67\xa1\xb2\xc3\x00\x00",8);
    memset(m_mainkey,0,sizeof m_mainkey);
	memset(m_xt_param_keya,0,sizeof m_xt_param_keya);
    m_mfcard = &m_cardinfo; 
}

ks_yncs_cardtype::~ks_yncs_cardtype()
{
}

int ks_yncs_cardtype::InitCardTypeDLL()
{
	int p;
	char key[32]="";
	if(m_license == NULL)
		return -1;

	if(m_is_params_load)
		return 0;

	if(CCardType::InitCardTypeDLL())
	{
		SET_ERR("����CCardType::InitCardTypeDLLʧ��");
		return -1;
	}

	if(m_license->get_public_int_param("kscardlib.mfcard.maxsect",&m_max_sectno))
	{
		SET_ERR("δ���ó�ʼ�������������");
		return -1;
	}
	if(m_license->get_public_int_param("kscardlib.mfcard.minsect",&m_min_sectno))
	{
		SET_ERR("δ���ó�ʼ����С������");
		return -1;
	}
	
	if(m_license->get_public_int_param("yncs.xt.sect",&p))
	{
		return -1;
	}
	m_xt_water_sect = p;

	if(m_license->get_public_int_param("yncs.hd.sect",&p))
	{
		return -1;
	}
	m_hd_water_sect = p;

	memset(key,0,sizeof key);
	if(m_license->get_public_param("yncs.hd.key",key,sizeof(key)-1))
	{
		return -1;
	}
	hex2dec(key,16,m_hd_mainkey,p);


	memset(key,0,sizeof key);
	if(m_license->get_public_param("yncs.hd.param.keya",key,sizeof(key)-1))
	{
		return -1;
	}
	hex2dec(key,12,m_hd_paramkeya,p);

	memset(key,0,sizeof key);
	if(m_license->get_public_param("yncs.hd.param.keyb",key,sizeof(key)-1))
	{
		return -1;
	}
	hex2dec(key,12,m_hd_paramkeyb,p);

	if(m_license->get_public_int_param("yncs.hd.param.sect",&p))
	{
		return -1;
	}
	m_hd_param_sect = p;

	if(m_license->get_public_int_param("yncs.xt.maxmoney",&m_xt_water_max_money))
	{
		return -1;
	}

	memset(key,0,sizeof key);
	if(m_license->get_public_param("yncs.xt.waterkey",key,sizeof(key)-1))
	{
		return -1;
	}
	hex2dec(key,12,m_xt_param_keya,p);

	m_is_params_load = 1;
	return 0;
}

int ks_yncs_cardtype::encrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
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
int ks_yncs_cardtype::dencrypt_des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
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
int ks_yncs_cardtype::encrypt_3des(unsigned char* key,long keylen,unsigned char *data,short datalen,unsigned char *Des_result)
{
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
void ks_yncs_cardtype::gen_hd_water_keya(int sectno,unsigned char *serialno,unsigned char *keya)
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
			keya[i] ^= plain[j] ^ m_hd_mainkey[j];
	}
    
}
int ks_yncs_cardtype::gen_user_card_keyA(unsigned char *key,unsigned char *text,unsigned char *keyA)
{
// gen_user_card_keyA�������keyA��des_code�������ucDesData��һ���Ķ���
	unsigned int i;
	/*	unsigned int j;*/
	unsigned char sPlain[9];	
	unsigned char sCipher[17]; 
	unsigned int  startpos = 0;
	unsigned char ucRawData[256];
	unsigned char ucDesData[256] = "";
	unsigned char ucdata[17];
	int iTemp = 0;
	memset(sPlain, 0, sizeof(sPlain));	
	memset(sCipher, 0, sizeof(sCipher));
	memset(ucDesData, 0, sizeof(ucDesData));
	memset(ucdata, 0, sizeof(ucdata));
	memset(ucRawData, 0, sizeof(ucRawData));
	memset(ucDesData, 0, sizeof(ucDesData));
	memcpy(ucRawData, text, 4);
	for(i = 0; i < 4; i++)
	{
		sPlain[i] = text[i];
		sPlain[i+4] = ~text[i];
	}

	encrypt_des(key, 8, sPlain, 8, sCipher);
	memcpy(sCipher + 8, sCipher, 8);
	startpos=(sCipher[0] + sCipher[1] + sCipher[2] + sCipher[3] + sCipher[4] + sCipher[5] + sCipher[6] + sCipher[7]) ;
	startpos%=7;      // sCipher[17]6079813C4F1A2F92, startpos = 4
	memcpy(keyA, sCipher + startpos, 6);
	return 0;
    
}
int ks_yncs_cardtype::CalcCardKeyA(int sectno,unsigned char *key)
{
	memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
	// ���ˮ��Ǯ����Կ��ʹ���ѻ�ˮ����Կ���㷽��
    if(sectno == m_hd_water_sect)
    {
		gen_hd_water_keya(sectno,m_mf_serialno,key);
    }
    else if(sectno == m_xt_water_sect) // ����ˮ����Կ��ʹ�ù̶���Կ 0x010203040506
    {
        memcpy(key,"\x01\x02\x03\x04\x05\x06",6);
    }
    else
    {
		if(m_CardKeys.bLoad != 1)
		{
			SET_ERR("������δ��Ȩ");
			return -1;
		}
        gen_user_card_keyA(m_mainkey,m_mf_serialno,key); // ���ñ�׼�㷨����
    }
	return 0;
}

int ks_yncs_cardtype::gen_user_card_keyB(unsigned char *key,unsigned char *text,unsigned char *keyB)
{
	unsigned int  i;
	unsigned char sPlain[9];
	unsigned char sCipher[17];
	unsigned int  startpos=0;
	unsigned char sKey[17];

	memset(sPlain,0,sizeof(sPlain));
	memset(sCipher,0,sizeof(sCipher));
	memset(sKey,0,sizeof(sKey));
	for(i=0;i<4;i++)
	{
		sPlain[i]=~text[i];
		sPlain[i+4]=text[i];
	}
	for(i=0;i<8;i++)
	{
		sKey[i]=key[i];
		sKey[i+8]=~key[i];
	}
	encrypt_3des(sKey,16,sPlain,8,sCipher);
	memcpy(sCipher+8,sCipher,8);
	startpos=(sCipher[0]+sCipher[1]+sCipher[2]+sCipher[3]+sCipher[4]+sCipher[5]+sCipher[6]+sCipher[7])%7;
	memcpy(keyB,sCipher+startpos,6);
	return 0;
    
}

int ks_yncs_cardtype::CalcCardKeyB(int sectno,unsigned char *key)
{
	if(m_CardKeys.bLoad != 1)
	{
		SET_ERR("������δ��Ȩ");
		return -1;
	}
	memcpy(m_mainkey,this->m_CardKeys.LDACK,8);
	gen_user_card_keyB(m_mainkey,(unsigned char*)m_mf_serialno,key);
	return 0;
}

int ks_yncs_cardtype::doInitUserCard(const char *sShowCardNo)
{
    int i,block,nRet;
    byte keya[6],keyb[6],buffer[16],ctrlbit[4];
    byte init_keya[6],data_buffer[16];
	char datetime[20]="";
	char temp[10] = "";

	if(m_CardKeys.bLoad !=1)
	{
		SET_ERR("Mifare1��Կδװ��");
		return KS_UNAUTH_TERM;
	}
	memcpy(init_keya,"\xFF\xFF\xFF\xFF\xFF\xFF",6);
	memcpy(ctrlbit,"\x7F\x07\x88\x00",4);
    if(CalcCardKeyB(0,keyb))
	{
		return KS_LOGINCARD;
	}

	m_lastLoginSect = MF_MAX_SECTNO;
	for(i = m_min_sectno ;i < m_max_sectno; ++i)
	{
		if(CalcCardKeyA(i,keya))
		{
			SET_ERR("��������["<<i<<"]��Կʧ��");
			return KS_LOGINCARD;
		}

		memcpy(buffer,keya,6);
		memcpy(buffer+6,ctrlbit,4);
		memcpy(buffer+10,keyb,6);

		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,init_keya);
		if(nRet)
		{
			if(doRequestMFCard(NULL))
			{
				SET_ERR("��ʼ��Mifare1����["<<i<<"]��¼ʧ��");
				return KS_LOGINCARD;
			}
			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
			if(nRet)
			{
				SET_ERR("��ʼ��Mifare1����["<<i<<"],�޷���ʼ���������ѱ�ʹ�ã�");
				return KS_LOGINCARD;
			}
			// ���Ե�¼��Ӧ�����Ѿ�����ʼ��
			continue;
		}
		else
		{
			// ��Ҫд��Ǯ����
            if(i == m_hd_water_sect || i == m_xt_water_sect)
            {
                for(block=0;block < 3;++block)
                {
                    memset(data_buffer,0, sizeof data_buffer);
                    nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+block,data_buffer);
                    if(nRet)
                    {
                        SET_ERR("��ʼ������["<<i<<"]д������ʧ�ܣ�������");
                        return KS_WRITECARD;
                    }
                }
            }
            nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
            if(nRet)
            {
                SET_ERR("��ʼ������["<<i<<"]д��Կʧ�ܣ�������");
                return KS_WRITECARD;
			}
		}
	}
	return 0;
    
}
int ks_yncs_cardtype::doRequestMFCard(char *szPhyno)
{
	int nRet,i;
	char phyno[32] = {0};
	unsigned char decphy[10]={0};
	nRet = m_Reader->request_card(m_ReaderPara,phyno,KS_MFCARD);
	if(nRet)
	{
		SET_ERR("����M1��ʧ��");
		return nRet;
	}
	if(szPhyno)
		strcpy(szPhyno,phyno);
	hex2dec(phyno,8,decphy,nRet);
	for(i = 0;i < 4; ++i)
		this->m_mf_serialno[i] = decphy[3-i];
	return 0;
}
int ks_yncs_cardtype::initCPUCard(const char *sShowCardNo)
{
	int nRet=0;
	int iLen=0;
	byte ucCardPhyID[9]={0};
	if(!m_CardKeys.bLoad)
	{
		SetLastErrMsg("��Կδװ��");
		return -1;
	}
	//Ѱ��
	nRet=RequestCard();
	if(nRet)
	{
		return nRet;
	}
	if(strlen(m_szCardUID)==8)
		strcat(m_szCardUID,"80000000");
	if(strlen(m_szCardUID)!=16)
	{
		SET_ERR("������ID["<<m_szCardUID<<"]���ȴ���");
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
	if(NULL!=sShowCardNo && strlen(sShowCardNo)>10)
	{
		SET_ERR("��ʾ����["<<sShowCardNo<<"���ȴ���");
		return -1;
	}
	memset(ucShowCardNo,0,sizeof(ucShowCardNo));

	if(NULL!=sShowCardNo && strlen(sShowCardNo)>0)
	{
		strcpy((char*)ucShowCardNo,sShowCardNo);
	}

	CARDKEYS  LocalCardKeys;	
	memset(&LocalCardKeys,0,sizeof(LocalCardKeys));

	PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,LocalCardKeys.DPK1);			//����1
	PbocDiverKey(ucCardPhyID,m_CardKeys.DPK1,LocalCardKeys.DPK2);			//����2
	PbocDiverKey(ucCardPhyID,m_CardKeys.DLK1,LocalCardKeys.DLK1);			//Ȧ��1
	PbocDiverKey(ucCardPhyID,m_CardKeys.DLK2,LocalCardKeys.DLK2);			//Ȧ��2
	PbocDiverKey(ucCardPhyID,m_CardKeys.DTAC,LocalCardKeys.DTAC);			//�ڲ���ԿTAC
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK,LocalCardKeys.DACK);			//Ӧ��������Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DUK,LocalCardKeys.DUK);				//PIN����
	PbocDiverKey(ucCardPhyID,m_CardKeys.DRPK,LocalCardKeys.DRPK);			//PIN��װ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DAMK,LocalCardKeys.DAMK);			//ά����Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK1,LocalCardKeys.DACK1);			//�ⲿ��֤1
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK2,LocalCardKeys.DACK2);			//�ⲿ��֤2
	PbocDiverKey(ucCardPhyID,m_CardKeys.DACK3,LocalCardKeys.DACK3);			//�ⲿ��֤3
	PbocDiverKey(ucCardPhyID,m_CardKeys.LDACK,LocalCardKeys.LDACK);			//СǮ���ⲿ��֤��Կ
	PbocDiverKey(ucCardPhyID,m_CardKeys.LDAMK,LocalCardKeys.LDAMK);			//СǮ��ά����Կ
	//ȡ�����`
	memset(ucRespData,0,sizeof(ucRespData));
	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;
	unsigned char ucSendData[256]={0};
	unsigned char ucCCK[17]={0};
	memset(ucCCK, 0xFF,sizeof ucCCK);
	nRet=ExecExtAuthCmd(ucCCK);
	if(nRet)
	{
		if(0x6A88!=nRet)
		{
			if(0x63 == nRet>>8)
			{
				int iLen=0;
				hex2dec(szHexKSCCK,32,ucCCK,iLen);
				nRet=ExecExtAuthCmd(ucCCK);
				if(nRet)
				{
					return nRet;
				}
				else
				{
					SET_ERR("�ÿ���ʹ��,�������·������Ȼ��ոÿ�");
					return -1;
				}
			}
			return nRet;
		}
	}
	//ɾ��MF�µ�Ŀ¼���ļ�
	sCmd="800E000000";
	cmd.send_buf=(byte*)sCmd.c_str();
	cmd.send_len=sCmd.size();
	cmd.cmd_type=1;//16����
	nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	//DIR�ļ�
	sCmd="00A4000000";
	CmdVector.push_back(sCmd);
	//������Կ�ļ�
	sCmd="80E00000073F004001AAFFFF";
	CmdVector.push_back(sCmd);
	//д���������Կ
	sCmd = "80D401001539F0AAAAAA";		//ʮ�����Ի���
	sCmd += szHexKSCCK;
	CmdVector.push_back(sCmd);

	//Ŀ¼�����ļ� EF01
//	sCmd="80E0000107AA0310F0F0FFFF";
//	CmdVector.push_back(sCmd);
	//��DF02
	sCmd="80E0DF021838009DF0AA957FFFD15600000145415359454E5452590000";
	CmdVector.push_back(sCmd);
	//��DF03
	sCmd="80E0DF03173811C8F0AA957FFFD156000001BDF0CACBB4EFD6A7B8B6";
	CmdVector.push_back(sCmd);
	//��DF04
	sCmd="80E0DF0418380330F0AA957FFFD156000001BDF0CACBB4EFC7AEB0FC32";
	CmdVector.push_back(sCmd);
	//ѡ��DF02
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
	//ѡ��DF03
	sCmd="00A404000FD156000001BDF0CACBB4EFD6A7B8B6";
	CmdVector.push_back(sCmd);
	//������Կ�ļ�
	sCmd="80E00000073F013001FFFFFF";//��Ҫ���Ȩ��FF�����޸�
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��ԿACK
#if 1 // �����ƽ�ְ�Ͽ��ṹ�汾
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
	//д��������Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DPK1,16,sHexStr);
	sCmd="80D40101153EF00C0100";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��������Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DPK2,16,sHexStr);
	sCmd="80D40102153EF00D0100";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��������Կ3
	//memset(sHexStr,0,sizeof(sHexStr));
	//dec2hex(g_MainKey.DPK3,16,sHexStr);
	//sCmd="80D40103153EF0020100";
	//sCmd+=sHexStr;
	//CmdVector.push_back(sCmd);
	//д��Ȧ����Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DLK1,16,sHexStr);
	sCmd="80D40101153FF00E0200";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��Ȧ����Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DLK2,16,sHexStr);
	sCmd="80D40102153FF00F0200";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ڲ���֤��Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DTAC,16,sHexStr);
	sCmd="80D401001534F00E0300";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д�����������Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DUK,16,sHexStr);
	sCmd="80D401001537F00EFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��PIN��װ��Կ��Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DRPK,16,sHexStr);
	sCmd="80D401011538F00EFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��Կ1
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK1,16,sHexStr);
	sCmd="80D401011539F00E2233";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��Կ2
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK2,16,sHexStr);
	sCmd="80D401021539F00EBB33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д���ⲿ��֤��Կ3
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK3,16,sHexStr);
	sCmd="80D401031539F00ECC33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��Ӧ��ά����Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DAMK,16,sHexStr);
	sCmd="80D401011536F00BFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д�����
	sCmd="80D40100083AF0EF1133000000";
	CmdVector.push_back(sCmd);
	//����Ӧ�û����ļ� 0015
	sCmd="80E0001507A80038F0F0FFFE";
	CmdVector.push_back(sCmd);
	//д����ʾ����
	CmdVector.push_back("SHOWCARDNO");
	//�ֿ��˻����ļ� 0016
	sCmd="80E0001607A80070F0F0FFFE";
	CmdVector.push_back(sCmd);
	//���׹����ļ� 0012
	sCmd="80E0001207A80040F0F0FFFE";//����0x40
	CmdVector.push_back(sCmd);
	//18������ϸ
	sCmd="80E00018072E3217F0FFFFFF";
	CmdVector.push_back(sCmd);
	//Ǯ��
	sCmd="80E0EF02072F0208F0F0FF18";
	CmdVector.push_back(sCmd);
	//������ϸ�ļ�
	//sCmd="80E0000207AE0A28F0F0FFFE";
	//CmdVector.push_back(sCmd);
	//����Ǯ�������ļ�
	sCmd="80E0000107AE3228F0F0FFFE";
	CmdVector.push_back(sCmd);
	//�����ļ�, ��ȫ״̬Ϊ F2 �� ������ڵ��� 2
	sCmd="80E0001907A80010F2F0FF0A";
	CmdVector.push_back(sCmd);

	//;DF04
	sCmd="00A4040010D156000001BDF0CACBB4EFC7AEB0FC32";
	CmdVector.push_back(sCmd);

	sCmd="80E00000073F00D801AAFFFF";
	CmdVector.push_back(sCmd);
	//������Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.DACK,16,sHexStr);
	sCmd="80D401001539F0AAAA66";
	sCmd +=sHexStr;
	CmdVector.push_back(sCmd);
	//СǮ���ļ�
	sCmd="80E0 0001 07 A80007F4F0FF0A";
	CmdVector.push_back(sCmd);
	//д��СǮ���ⲿ��֤��Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.LDACK,16,sHexStr);
	sCmd="80D401011539F0024433";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);
	//д��СǮ��Ӧ��ά����Կ
	memset(sHexStr,0,sizeof(sHexStr));
	dec2hex(LocalCardKeys.LDAMK,16,sHexStr);
	sCmd="80D401011536F00AFF33";
	sCmd+=sHexStr;
	CmdVector.push_back(sCmd);

	for(int i=0;i<CmdVector.size();i++)
	{
		string& sSendData=CmdVector[i];
		if(sSendData=="SHOWCARDNO")
		{
			char szMac[9]={0};
			//����MAC
			memset(sHexStr,0,sizeof(sHexStr));
			dec2hex(ucShowCardNo,10,sHexStr);		//���ݿ�
			sSendData="04D6950A";
			sSendData+=ltohex(14);	//����+4�ֽ�MAC
			sSendData+=sHexStr;		
			ret=CalcSafeMac4Sam(sSendData.c_str(),szMac);
			if(ret)
			{
				return ret;
			}
			sSendData+=szMac;
		}

		string_replace(sSendData," ","");
		string_replace(sSendData,"\t","");
		cmd.send_buf=(byte*)sSendData.c_str();
		cmd.send_len=sSendData.size();
		cmd.cmd_type=1;//16����
		nRet=m_Reader->cpucard_cmd(m_ReaderPara,&cmd,KS_CPUCARD);
		if(nRet)
		{
			if(cmd.cmd_retcode)
			{
				SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
				return cmd.cmd_retcode;
			}
			else
			{
				SET_ERR(m_Reader->GetErrMsg(NULL));
				return nRet;
			}
		}
	}
	nRet = this->selectADFBySFI("3F00",1);
	return nRet;
}
int ks_yncs_cardtype::InitUserCard(const char *sShowCardNo)
{
    int nRet;
    nRet = initCPUCard(sShowCardNo);
    if(nRet)
        return nRet;
	
	nRet = doRequestMFCard(NULL);
	if(nRet)
		return nRet;

    nRet=doInitUserCard(sShowCardNo);
	if(nRet)
	{
		SET_ERR("��ʼ��M1����ʧ��,ret["<<nRet<<"]");
	}
	return nRet;
}
int ks_yncs_cardtype::doRestoreUsetCard()
{

	int i,block,nRet;
    byte keya[6],keyb[6],buffer[16],ctrlbit[4];
    byte data_buffer[16];
	char datetime[20]="";
	char temp[10] = "";

	if(m_CardKeys.bLoad !=1)
	{
		SET_ERR("Mifare1��Կδװ��");
		return KS_UNAUTH_TERM;
	}
	memcpy(ctrlbit,"\xFF\x07\x80\x69",4);

	if(CalcCardKeyB(0,keyb))
	{
		return KS_LOGINCARD;
	}
	memcpy(keya,"\xFF\xFF\xFF\xFF\xFF\xFF",6);

	m_lastLoginSect = MF_MAX_SECTNO;
	for(i = m_min_sectno ;i < m_max_sectno; ++i)
	{

		memset(buffer,0xFF,16);
		memcpy(buffer+6,ctrlbit,4);

		nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYB,keyb);
		if(nRet)
		{
			if(doRequestMFCard(NULL))
			{
				SET_ERR("����Mifare1����["<<i<<"]��¼ʧ��");
				return KS_LOGINCARD;
			}
			nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,keya);
			if(nRet)
			{
				SET_ERR("����Mifare1����["<<i<<"],�޷����գ������ѱ�ʹ�ã�");
				return KS_LOGINCARD;
			}
			// ���Ե�¼��Ӧ�����Ѿ�����ʼ��
			continue;
		}
	
		// ��Ҫд��Ǯ����
        if(i == m_hd_water_sect || i == m_xt_water_sect)
        {
            for(block=0;block < 3;++block)
            {
                memset(data_buffer,0, sizeof data_buffer);
                nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+block,data_buffer);
                if(nRet)
                {
                    SET_ERR("��������["<<i<<"]д������ʧ�ܣ�������");
                    return KS_WRITECARD;
                }
            }
        }
        nRet = m_Reader->write_block(m_ReaderPara,m_mfcard,i*4+3,buffer);
        if(nRet)
        {
            SET_ERR("��������["<<i<<"]д��Կʧ�ܣ�������");
            return KS_WRITECARD;
		}
	}
    
	return 0;
}
int ks_yncs_cardtype::RestoreFactorySettings()
{
    int nRet;
    nRet = CCardType::RestoreFactorySettings();
    if(nRet)
        return nRet;
	nRet = doRequestMFCard(NULL);
	if(nRet)
		return nRet;

	nRet = doRestoreUsetCard();
	if(nRet)
	{
		SET_ERR("����M1����ʧ��,nRet["<<nRet<<"]");
	}
    return nRet;
}


int	 ks_yncs_cardtype::AuthDLL(const char *key,int flag)
{
    return 0;
}

int ks_yncs_cardtype::loginCard(int sectno)
{
	byte key[6];
	int nRet;
	if(sectno == m_lastLoginSect)
		return 0;
	// TODO: login card
	nRet = this->CalcCardKeyA(sectno,key);
	if(nRet)
	{
		SET_ERR("��¼����["<<sectno<<"]����keyʧ��");
		return -1;
	}
	nRet = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,key);
	if(nRet)
	{
		SET_ERR("��¼����["<<sectno<<"]ʧ��");
		return -1;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// ˮ����غ���
int ks_yncs_cardtype::hd_water_login_fix(ks_water_pack_t *pack)
{
	int sectno,ret,blockno;
	char param_value[256] = "";
	ks_mf_cardkey_t card_key;
	//ks_mf_init_cardkey_t init_key;
	unsigned char ctrlbit[4]={0};
	unsigned char keya[6]={0},keyb[6]={0},loginkey[6]={0};
	unsigned char buffer[16];
    KS_MF_KEYTYPE loginkeyflag=MF_KEYA;
	char phyid[21];

	memcpy(ctrlbit,"\x7F\x07\x88\x00",4);

	sectno = m_hd_water_sect;

	ret = loginCard(sectno);
	if(ret)
	{
		if(doRequestMFCard(phyid))
			return KS_REQUESTCARD;
        
        memcpy(loginkey,"\xFF\xFF\xFF\xFF\xFF\xFF",6);
        if(CalcCardKeyB(sectno,m_cardkey[sectno].key))
        {
            SET_ERR("������Կ����");
            return KS_LOGINCARD;
        }
		memcpy(keyb,m_cardkey[sectno].key,6);
		
		if(m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,loginkeyflag,loginkey)!=0)
		{
			TRACE2_LOG(("����[%d]keya��¼ʧ��",sectno));
            if(doRequestMFCard(phyid))
                return KS_REQUESTCARD;
            if(m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYB,keyb)!=0)
            {
                TRACE2_LOG(("����[%d]keyb��¼ʧ��",sectno));
                return KS_LOGINCARD;
            }
		}
        
		CalcCardKeyA(sectno,m_cardkey[sectno].key);
		memcpy(keya,m_cardkey[sectno].key,6);

		memcpy(buffer,keya,6);
		memcpy(buffer+6,ctrlbit,4);
		memcpy(buffer+10,keyb,6);
		blockno = sectno * 4;
		if(m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+3,buffer)!=0)
		{
			TRACE2_LOG(("����[%d]д��Կʧ��",sectno));
			return KS_WRITECARD;
		}
        return loginCard(sectno);
	}
	return 0;
}

int ks_yncs_cardtype::hd_water_readmoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno;
	unsigned char buffer[16],buffer2[16];
	char param_value[256] = "";
	
	sectno = m_hd_water_sect;

#if 1
	ret = loginCard(sectno);
#else
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("��Կδװ��",-1);
		return KS_NOTAUTH;
	}
	ret = hd_water_login_fix(pack);
#endif

	if(ret)
		return ret;

	blockno = sectno * 4;

	memset(buffer,0xFF,sizeof buffer);
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer))
	{
		return KS_READCARD;
	}
	if(check_buffer_xor(buffer,15,buffer[15]))
	{
		if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+1,buffer))
		{
			return KS_READCARD;
		}
		if(check_buffer_xor(buffer,15,buffer[15]))
		{
			return KS_PURSEERROR;
		}
	}
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+2,buffer2))
	{
		return KS_READCARD;
	}
	if(check_buffer_xor(buffer2,15,buffer2[15]))
	{
		return KS_PURSEERROR;
	}
	pack->money = get_3byte_int(buffer);
	pack->totalmoney = get_4byte_int(buffer+3);
	pack->price1 = get_2byte_int(buffer+7);
	pack->price2 = get_2byte_int(buffer+9);
	pack->price3 = get_2byte_int(buffer+11);
	pack->addcount = get_2byte_int(buffer+13);
	
	pack->custno = get_3byte_int(buffer2);
	pack->cardtype = buffer2[3];
	pack->expireddate[0] = '2';
	pack->expireddate[1] = '0';
	bcd2asc(buffer2+4,3,pack->expireddate+2);
	pack->lockflag = buffer2[7];
	return 0;
}
int ks_yncs_cardtype::hd_water_writemoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno,offset;
	unsigned char buffer[16],buffer2[16];
	char param_value[256] = "";
	
	sectno = m_hd_water_sect;
#if 1
	ret = loginCard(sectno);
#else
	if(!ks_checkloadkeys())
	{
		ks_setlasterr("��Կδװ��",-1);
		return KS_NOTAUTH;
	}
	ret = hd_water_login_fix(pack);
#endif
	if(ret)
		return ret;

	blockno = sectno * 4;

	memset(buffer,0xFF,sizeof buffer);
	offset = 0;
	set_3byte_int(buffer,pack->money);
	offset+=3;
	set_4byte_int(buffer+offset,pack->totalmoney);
	offset+=4;
	set_2byte_int(buffer+offset,pack->price1);
	offset+=2;
	set_2byte_int(buffer+offset,pack->price2);
	offset+=2;
	set_2byte_int(buffer+offset,pack->price3);
	offset+=2;
	set_2byte_int(buffer+offset,pack->addcount);
	buffer[15] = calc_xor(buffer,15);

	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(!m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer2))
	{
		if(memcmp(buffer,buffer2,16)!=0)
			return KS_WRITECARD;
	}
	else
		return KS_UNCONFIRM;

	memset(buffer,0xFF,sizeof buffer);
	offset = 0;
	set_3byte_int(buffer,pack->cardno);
	offset+=3;
	buffer[offset]=(unsigned char)pack->cardtype;
	offset++;
	asc2bcd(pack->expireddate+2,6,buffer+offset,ret);
	offset+=3;
	buffer[offset] = pack->lockflag;
	buffer[15] = calc_xor(buffer,15);
	ret = m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+2,buffer);
	if(!m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+2,buffer2))
	{
		if(memcmp(buffer,buffer2,16)!=0)
			return KS_WRITECARD;
	}
	else
		return KS_UNCONFIRM;
	return 0;
}

int ks_yncs_cardtype::hd_water_publishcard(ks_water_pack_t *pack)
{	
	int ret;
	if(this->m_CardKeys.bLoad == 0)
	{
		SET_ERR("��Կδװ��");
		return -1;
	}
	ret = hd_water_login_fix(pack);
	if(ret)
	{
		SET_ERR("����ʧ��");
		return -1;
	}
	return hd_water_writemoney(pack);
}
int ks_yncs_cardtype::hd_water_recyclecard()
{
	int sectno,ret,blockno;
	unsigned char buffer[16];
	char param_value[256] = "";
	
	sectno = m_hd_water_sect;

	ret = loginCard(sectno);
	if(ret)
		return ret;

	blockno = sectno * 4;
	memset(buffer,0,sizeof buffer);
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer))
	{
		return KS_WRITECARD;
	}
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+1,buffer))
	{
		return KS_WRITECARD;
	}
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+2,buffer))
	{
		return KS_WRITECARD;
	}
	return 0;
}
int ks_yncs_cardtype::hd_water_publishparamcard(ks_water_param_t *param)
{
	int ret,block_no,len,offset,sect,watersect;
	unsigned char param_key_a[] = {0x23,0x55,0x33,0x78,0x12,0xAB};
	unsigned char param_key_b[] = {0x34,0x22,0x35,0x23,0x45,0x34};
	unsigned char param_init_key[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	unsigned char seed_key[8];
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	char param_value[128];
	unsigned char buffer[16];
	char phyid[9];

	// ��ȡ���������Ĳ�����Ϣ
	// param card keya
	
	memcpy(param_key_a,m_hd_paramkeya,6);
	memcpy(param_key_b,m_hd_paramkeyb,6);
	memcpy(seed_key,m_hd_mainkey,8);
	sect = m_hd_param_sect;
	block_no = sect*4;


	watersect = m_hd_water_sect;

	// ��¼����
	if(m_Reader->login_card(m_ReaderPara,m_mfcard,sect,MF_KEYA,param_key_a)!=0)
	{
		ret = doRequestMFCard(phyid);
		if(ret)
			return KS_REQUESTCARD;
		// ��¼ ������ 15 ��������
		if(m_Reader->login_card(m_ReaderPara,m_mfcard,sect,MF_KEYA,param_init_key)!=0)
		{
			TRACE2_LOG(("��ʼ��������ÿ�ʧ�ܣ����������޷���ʼ��,��ȷ�ϸ�������Կ"));
			return KS_LOGINCARD;
		}
		memcpy(buffer,param_key_a,6);
		memcpy(buffer+6,new_ctrl_bit,4);
		memcpy(buffer+10,param_key_b,6);
		if(m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+3,buffer)!=0)
		{
			TRACE2_LOG(("д������ÿ�ʧ�ܣ���ȷ�ϸ������ɶ�д"));
			return KS_WRITECARD;
		}
	}
	
	// д������
	offset = 0;
	memcpy(buffer,seed_key,8);
	offset += 8;
	set_2byte_int(buffer+offset,param->minmoney);
	offset += 2;
	set_3byte_int(buffer+offset,param->maxmoney);
	offset += 3;
	set_2byte_int(buffer+offset,param->unit);
	offset += 2;
	buffer[15] = calc_xor(buffer,offset);
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,block_no,buffer)!=0)
	{
		TRACE2_LOG(("д������ÿ�ʧ�ܣ���ȷ�ϸÿ�[%d]�ɶ�д",block_no));
		return KS_WRITECARD;
	}
	memset(buffer,0xFF,16);
	offset = 0;
	set_2byte_int(buffer+offset,param->transmoney);
	offset += 2;
	buffer[offset++] = param->priceindex;
	buffer[offset++] = watersect;
	buffer[offset++] = 0;
	buffer[15] = calc_xor(buffer,15);
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+1,buffer)!=0)
	{
		TRACE2_LOG(("д������ÿ�ʧ�ܣ���ȷ�ϸÿ�[%d]�ɶ�д",block_no+1));
		return KS_WRITECARD;
	}
	return 0;
}

int ks_yncs_cardtype::hd_water_recycleparamcard()
{
	return KS_NOTSUPPORT;
}

//////////////////////////////////////////////////////////////////////////
// ���쿨�ṹ

int ks_yncs_cardtype::xt_water_recyclecard()
{
	int sectno,ret,blockno;
	unsigned char buffer[16];
	char param_value[256] = "";

	sectno = m_xt_water_sect;

	blockno = sectno * 4;
	ret = loginCard(sectno);
	if(ret)
		return ret;
	memset(buffer,0,sizeof buffer);
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer))
	{
		return KS_WRITECARD;
	}
	if(m_Reader->write_block(m_ReaderPara,m_mfcard,blockno+1,buffer))
	{
		return KS_WRITECARD;
	}
	return 0;
}
int ks_yncs_cardtype::xt_water_readmoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno;
	unsigned char buffer[16];
	char param_value[256] = "";
	
	sectno = m_xt_water_sect;
	blockno = sectno * 4;

	TRACE2_LOG(("������ˮ��Ǯ��"));
	ret = loginCard(sectno);
	if(ret)
		return ret;
	memset(buffer,0,sizeof buffer);
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer))
	{
		return KS_READCARD;
	}
	if(check_buffer_sum(buffer,15,buffer[15]))
	{
		if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+1,buffer))
		{
			return KS_READCARD;
		}
		if(check_buffer_sum(buffer,15,buffer[15]))
		{
			return KS_PURSEERROR;
		}
	}
	pack->money = get_3byte_money(buffer);
	pack->totalmoney = get_3byte_money(buffer+4);
	pack->custno = get_4byte_money(buffer+10);
	return 0;
}
int ks_yncs_cardtype::xt_water_writemoney(ks_water_pack_t *pack)
{
	int sectno,ret,blockno,offset;
	unsigned char buffer[16],buffer2[16];
	char param_value[256] = "";
	
	sectno = m_xt_water_sect;
	if(pack->money > m_xt_water_max_money)
	{
		SET_ERR("����ˮ����������["<<m_xt_water_max_money<<"]");
		return KS_EXCEEDMONEY;
	}

		blockno = sectno *4;


	ret = loginCard(sectno);
	if(ret)
		return ret;
	offset = 0;
	memset(buffer,0,sizeof buffer);
	set_3byte_money(buffer,pack->money);
	offset+=3;
	offset++;
	set_3byte_money(buffer+offset,pack->totalmoney);
	offset+=3;
	offset+=3;
	pack->custno = 1;
	set_4byte_money(buffer+offset,pack->custno);
	buffer[15] = calc_sum(buffer,15);
	//TRACE2_LOG(("дǮ��[%d]",sectno));
	m_Reader->write_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer2))
	{
		return KS_UNCONFIRM;
	}
	if(memcmp(buffer,buffer2,16)!=0)
		return KS_WRITECARD;
	TRACE2_LOG(("дǮ��[%d]���",sectno));
	//}
	return 0;
}

int ks_yncs_cardtype::xt_water_publishcard(ks_water_pack_t *pack)
{
	return xt_water_writemoney(pack);
}
int ks_yncs_cardtype::do_format_xt_paramcard(ks_water_param_t *param)
{
	int i,ret;
	char phyid[9];
	unsigned char orgin_keya[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	//unsigned char new_keya[] = {0x01,0x02,0x03,0x04,0x05,0x06};

	for(i = 1;i < 15;++i)
	{
		ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,orgin_keya);
		if(ret)
		{
			ret = doRequestMFCard(phyid);
			if(ret)
				return KS_REQUESTCARD;
			ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,m_xt_param_keya);
			if(ret)
			{
				TRACE2_LOG(("�����������ÿ�ʧ�ܣ�����[%d]�޷���¼",i));
				return KS_LOGINCARD;
			}
		}
	}
	TRACE2_LOG(("��ʽ���������ÿ�[%s]�ɹ�",phyid));
	return 0;
}
int ks_yncs_cardtype::do_xt_water_paramcard(ks_water_param_t *param)
{
	int i,ret,block_no;
	char phyid[9];
	unsigned char orgin_keya[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	//unsigned char new_keya[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	unsigned char new_keyb[6];
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	unsigned char data[16],data1[16];
	unsigned char card_key[16];
	memcpy(new_keyb,m_hd_paramkeyb,6);

	memcpy(card_key,m_xt_param_keya,6);
	memcpy(card_key+6,new_ctrl_bit,4);
	memcpy(card_key+10,new_keyb,6);

	//////////////////////////////////////////////////////////////////////////
	// ���ṹ����
	memset(data,0,sizeof data);
	// ����
	data[0] = param->unitmoney % 256;
	data[1] = param->unitmoney / 256;
	// ������
	data[2] = param->watersect % 256;
	// ���������
	data[3] = param->termid % 256;
	data[4] = param->termid / 256;
	// Ԥ��ֵ
	data[5] = param->transmoney % 256;
	// ʣ��������
	data[6] = param->minmoney % 256;
	// ����
	memcpy(data+8,data,2);
	data[10] = data[2];
	memcpy(data+11,data+3,2);
	//data[13] = data[5];
	data[14] = data[6];
	for(i = 0,data[15] = 0;i < 15;++i)
		data[15] += data[i];

	memset(data1,0,sizeof data1);
	memcpy(data1,param->workkey,6);
	memcpy(data1+8,param->workkey,6);
	for(i = 0, data1[15]=0;i < 15;++i)
		data1[15] += data1[i];

	for (i = 1;i < 16;++i)
	{
		block_no = i * 4;
		ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,m_xt_param_keya);
		if(ret)
		{
			ret = doRequestMFCard(phyid);
			if(ret)
				return KS_REQUESTCARD;
			// ���ǳ�ʼ��Կ����Ҫ���³�ʼ��
			ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,orgin_keya);
			if(ret)
			{
				TRACE2_LOG(("��ʼ���������ÿ�ʧ�ܣ�����[%d]�޷���ʼ��,��ȷ�ϸ�������Կ",i));
				return KS_LOGINCARD;
			}

			ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+3,card_key);
			if(ret)
			{
				TRACE2_LOG(("��ʼ���������ÿ�ʧ�ܣ�����[%d]�޷�д����Կ����ȷ�Ͽ�����",i));
				return KS_WRITECARD;
			}
			// ������Կ�����µ�¼
			ret = doRequestMFCard(phyid);
			if(ret)
				return KS_REQUESTCARD;
			ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,m_xt_param_keya);
			if(ret)
			{
				TRACE2_LOG(("��ʼ���������ÿ�����[%d]���޷���¼,��ȷ�ϸ�������Կ",i));
				return KS_LOGINCARD;
			}
		}
		// д���ÿ�����
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no,data);
		if(ret)
		{
			TRACE2_LOG(("д�������������[%d]ʧ��",i));
			return KS_WRITECARD;
		}
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+1,data1);
		if(ret)
		{
			TRACE2_LOG(("д�������������[%d]ʧ��",i));
			return KS_WRITECARD;
		}
	}
	return 0;
}

int ks_yncs_cardtype::do_xt_water_initcard(ks_water_param_t *param)
{
	int i,ret,block_no;
	char phyid[9];
	unsigned char orgin_keya[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	//unsigned char new_keya[] = {0x01,0x02,0x03,0x04,0x05,0x06};
	unsigned char new_keyb[6];
	unsigned char new_ctrl_bit[] = {0x7F,0x07,0x88,0x00};
	unsigned char data[16];
	unsigned char card_key[16];

	memcpy(new_keyb,m_hd_paramkeyb,6);

	memcpy(card_key,m_xt_param_keya,6);
	memcpy(card_key+6,new_ctrl_bit,4);
	memcpy(card_key+10,new_keyb,6);



	//////////////////////////////////////////////////////////////////////////
	// ���ṹ����
	memset(data,0,sizeof data);
	memset(data,0xFA,4);
	for(i = 0,data[15] = 0;i < 15;++i)
		data[15] += data[i];


	ret = this->doRequestMFCard(phyid);
	if(ret)
		return KS_REQUESTCARD;

	for (i = 1;i < 16;++i)
	{
		block_no = i * 4;
		ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,m_xt_param_keya);
		if(ret)
		{
			ret = doRequestMFCard(phyid);
			if(ret)
				return KS_REQUESTCARD;
			// ���ǳ�ʼ��Կ����Ҫ���³�ʼ��
			ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,orgin_keya);
			if(ret)
			{
				TRACE2_LOG(("��ʼ���������㿨ʧ�ܣ�����[%d]�޷���ʼ��,��ȷ�ϸ�������Կ",i));
				return KS_LOGINCARD;
			}

			ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+3,card_key);
			if(ret)
			{
				TRACE2_LOG(("��ʼ���������㿨ʧ�ܣ�����[%d]�޷�д����Կ����ȷ�Ͽ�����",i));
				return KS_WRITECARD;
			}
			// ������Կ�����µ�¼
			ret = doRequestMFCard(phyid);
			if(ret)
				return KS_REQUESTCARD;
			ret = m_Reader->login_card(m_ReaderPara,m_mfcard,i,MF_KEYA,m_xt_param_keya);
			if(ret)
			{
				TRACE2_LOG(("��ʼ���������㿨����[%d]���޷���¼,��ȷ�ϸ�������Կ",i));
				return KS_LOGINCARD;
			}
		}
		// д���ÿ�����
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no,data);
		if(ret)
		{
			TRACE2_LOG(("д�������������[%d]ʧ��",i));
			return KS_WRITECARD;
		}
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+1,data);
		if(ret)
		{
			TRACE2_LOG(("д�������������[%d]ʧ��",i));
			return KS_WRITECARD;
		}
		ret = m_Reader->write_block(m_ReaderPara,m_mfcard,block_no+2,data);
		if(ret)
		{
			TRACE2_LOG(("д�������������[%d]ʧ��",i));
			return KS_WRITECARD;
		}
	}

	return 0;
}
int ks_yncs_cardtype::xt_water_publishparamcard(ks_water_param_t *param)
{
	int ret;
	switch(param->cardflag)
	{
	case 0:
		ret = do_xt_water_paramcard(param);
		break;
	case 1:
		ret = do_xt_water_initcard(param);
		break;
	default:
		return -1;
	}
	return ret;
}
int ks_yncs_cardtype::xt_water_recycleparamcard()
{
	//////////////////////////////////////////////////////////////////////////
	// ���ṹ����
	return KS_NOTSUPPORT;
}

int ks_yncs_cardtype::water_publishcard(int watertype,ks_water_pack_t *pack)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_publishcard(pack);
	case KS_HD_WATER:
		return hd_water_publishcard(pack);
	default:
		return KS_NOTSUPPORT;
	}
}
int ks_yncs_cardtype::water_recyclecard(int watertype)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_recyclecard();
	case KS_HD_WATER:
		return hd_water_recyclecard();
	default:
		return KS_NOTSUPPORT;
	}
}
int ks_yncs_cardtype::water_readmoney(int watertype,ks_water_pack_t *pack)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_readmoney(pack);
	case KS_HD_WATER:
		return hd_water_readmoney(pack);
	default:
		return KS_NOTSUPPORT;
	}
}
int ks_yncs_cardtype::water_writemoney(int watertype,ks_water_pack_t *pack)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_writemoney(pack);
	case KS_HD_WATER:
		return hd_water_writemoney(pack);
	default:
		return KS_NOTSUPPORT;
	}
}
int ks_yncs_cardtype::water_publishparamcard(int watertype,ks_water_param_t *param)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_publishparamcard(param);
	case KS_HD_WATER:
		return hd_water_publishparamcard(param);
	default:
		return KS_NOTSUPPORT;
	}
}
int ks_yncs_cardtype::water_recycleparamcard(int watertype)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_recycleparamcard();
	case KS_HD_WATER:
		return hd_water_recycleparamcard();
	default:
		return KS_NOTSUPPORT;
	}
}

int ks_yncs_cardtype::water_read_paramcard(int watertype,ks_water_param_t *param)
{
	if(this->doRequestMFCard(NULL))
	{
		return KS_REQUESTCARD;
	}
	switch(watertype)
	{
	case KS_YNCS_XT_WATER:
		return xt_water_readparamcard(watertype,param);
	case KS_HD_WATER:
		return hd_water_readparamcard(watertype,param);
	default:
		return KS_NOTSUPPORT;
	}
}
int ks_yncs_cardtype::hd_water_readparamcard(int watertype,ks_water_param_t *param)
{
	int sectno,ret,blockno,offset;
	int keya;
	sectno = m_hd_param_sect;
	unsigned char buffer[16],xor;
	
	ret = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_hd_paramkeya);
	if(ret)
	{
		SET_ERR("��¼����������["<<sectno<<"]ʧ��");
		return KS_LOGINCARD;
	}

	// ���ṹ����
	memset(buffer,0,sizeof buffer);
	blockno = sectno * 4;
	ret = m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,buffer);
	if(ret)
	{
		SET_ERR("��ȡ��������������ʧ��");
		return KS_READCARD;
	}
	// д������
	offset = 0;
	//memcpy(buffer,seed_key,8);
	offset += 8;
	//
	param->minmoney = get_2byte_int(buffer+offset);
	offset += 2;
	//
	param->maxmoney = get_3byte_int(buffer+offset);
	offset += 3;
	//
	param->unit = get_2byte_int(buffer+offset);
	offset += 2;
	// crc
	xor = calc_xor(buffer,15);
	if(xor != buffer[15])
	{
		SET_ERR("����������У�����");
		return KS_READCARD;
	}
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+1,buffer)!=0)
	{
		SET_ERR("��������ÿ�ʧ��");
		return KS_READCARD;
	}
	//
	offset = 0;
	param->transmoney = get_2byte_int(buffer+offset);
	offset += 2;
	//
	param->priceindex = buffer[offset++];
	//
	param->watersect = buffer[offset++];
	xor = calc_xor(buffer,15);
	if(xor != buffer[15])
	{
		SET_ERR("��������ÿ�ʧ��");
		return KS_READCARD;
	}
	return 0;
}
int ks_yncs_cardtype::xt_water_readparamcard(int watertype,ks_water_param_t *param)
{
	unsigned char data[16],sum;
	int ret,sectno,blockno;
	sectno = 1;
	ret = m_Reader->login_card(m_ReaderPara,m_mfcard,sectno,MF_KEYA,m_xt_param_keya);
	if(ret)
	{
		SET_ERR("��¼����������["<<sectno<<"]ʧ��");
		return KS_LOGINCARD;
	}
	
	blockno = sectno * 4;
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno,data)!=0)
	{
		SET_ERR("��ȡ����������");
		return KS_READCARD;
	}
	// ���ṹ����
	memset(data,0,sizeof data);
	// ����
	param->unitmoney = data[0] + data[1] * 256;
	// ������
	param->watersect = data[2];
	// ���������
	param->termid = data[3] + data[4] * 256;
	// Ԥ��ֵ
	param->transmoney = data[5];
	// ʣ��������
	param->minmoney = data[6];
	// sum
	sum = calc_sum(data,15);
	if(sum != data[15])
	{
		SET_ERR("У��ʹ���");
		return KS_READCARD;
	}
	
	memset(data,0,sizeof data);
	if(m_Reader->read_block(m_ReaderPara,m_mfcard,blockno+1,data)!=0)
	{
		SET_ERR("��ȡ����������");
		return KS_READCARD;
	}
	sum = calc_sum(data,15);
	if(sum != data[15])
	{
		SET_ERR("У��ʹ���");
		return KS_READCARD;
	}
	memcpy(param->workkey,data,6);
	return 0;
}

int ks_yncs_cardtype::checkCardType(int ct)
{
	switch(ct)
	{
	case KS_CPUCARD:
	case KS_FIXCARD:
		m_CardTypeCode = 0x0102;
		return 0;
	case KS_MFCARD:
		m_CardTypeCode = 0x0200;
		return 0;
	default:
		return -1;
	}
}
int ks_yncs_cardtype::ExtAuth(const char *cardphyid,int keyidx)
{
	string sCmd;
	unsigned char ucRespData[512]={0};
	unsigned char ucRandom[9]={0};
	unsigned char sRandomHex[17]={0};
	char encrypt_random[24] = {0};
	int nRet;
	des3_context ctx;
	
	nRet=GetRandomNum(ucRandom);
	if(nRet)
		return nRet;

	ks_cpu_cmd_t cmd;
	memset(&cmd,0,sizeof(cmd));
	cmd.recv_buf=ucRespData;

	// �ƽ�ְ���ⲿ��֤��ԿΪ FF
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
	if(nRet)
	{
		if(cmd.cmd_retcode)
		{
			SET_ERR(GetErrMsgByErrCode(cmd.cmd_retcode,NULL));
			return cmd.cmd_retcode;
		}
		else
		{
			SET_ERR(m_Reader->GetErrMsg(NULL));
			return nRet;
		}
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////////

int KSAPI register_cardtype_op(ks_cardtype_base *&op)
{
	op = new ks_yncs_cardtype();
	return 0;
}
