#include "ksinterface.h"
#include "logfile.h"
#include "CIniFile.h"


/************************************************************************
��ģ����Ƶ�Ŀ���Ǵ�ѧ������Ȧ����������ͨҵ�����Ҫ
�������ͨ�ṩ�˿�����̬�⣬��Ҫʹ�ö�������д����
����Ȧ��������ֶ������Ƚ����ѣ�������Ҫ��װ������ҵ��Ĳ���
************************************************************************/

//////////////////////////////////////////////////////////////////////////
// CardDLL ���ֶ���
DEF_CARD_DLLFUNC(ConnectMF);
DEF_CARD_DLLFUNC(CloseMF);
DEF_CARD_DLLFUNC(Load_Dll);
DEF_CARD_DLLFUNC(Load_WorkKey);
DEF_CARD_DLLFUNC(ReadCardNO);
DEF_CARD_DLLFUNC(ReadBalance);
DEF_CARD_DLLFUNC(SMT_SetNormalFlagByBlkVerion);
DEF_CARD_DLLFUNC(SMT_WritePersonalPassword);
DEF_CARD_DLLFUNC(ReadSerial);
DEF_CARD_DLLFUNC(SMT_PacketSetMoney);
DEF_CARD_DLLFUNC(SMT_TransWaterPacket);
DEF_CARD_DLLFUNC(SMT_ReadWaterPackInfo2);
DEF_CARD_DLLFUNC(SMT_WriteWaterPackInfo2);
DEF_CARD_DLLFUNC(ReadCardInfo);
DEF_CARD_DLLFUNC(SMT_ReadWaterPackInfo_XT);
DEF_CARD_DLLFUNC(SMT_TransWaterPacket_XT);
DEF_CARD_DLLFUNC(JD2XT_Card);
DEF_CARD_DLLFUNC(XT2JD_Card);
DEF_CARD_DLLFUNC(SMT_GetCOMHandle);


//////////////////////////////////////////////////////////////////////////
// ���ͨ���ֶ���
DEF_YCT_DLLFUNC(ConfigParamters);
DEF_YCT_DLLFUNC(Common_Initialize_RW);
DEF_YCT_DLLFUNC(Common_Destroy_RW);
DEF_YCT_DLLFUNC(QueryBalance);
DEF_YCT_DLLFUNC(CashIncrease);

HANDLE g_yct_reader = NULL;

struct {
	int errcode;
	const char *errmsg;
}g_yct_errmsg[] = {
	{0x00,"�����ɹ�"},
	{0x60,"û�а�װSAM��"},
	{0x61,"SAM����ʼ�������δ��ʼ��"},
	{0x62,"SAMУ��PIN����"},
	{0x63,"SAM�������뽻�����Ͳ�ƥ��"},
	{0x64,"SAM��ѡ���ļ�����"},
	{0x65,"SAM������"},
	{0x66,"SAM��д����"},
	{0x67,"SAM����֤����"},
	{0x68,"SAM��ȡ���������"},
	{0x69,"SAM��DES�������"},
	{0x6A,"SAM������Ǯ����Կ����"},
	{0x71,"PKI��RSA�������"},
	{0x72,"PKI��DES�������"},
	{0x7E,"SAM��ִ��APDU�������"},
	{0x7F,"SAM��������ʱ"},
	{0x80,"û�п�"},
	{0x81,"ѡ��Ƭ����"},
	{0x82,"ͣ�ÿ�Ƭ����"},
	{0x83,"��֤��Ƭ����"},
	{0x84,"��Ƭ������"},
	{0x85,"��Ƭд����"},
	{0x86,"��Ƭд������;�ж�"},
	{0x87,"��ֵ��Ƭ����Ӧ"},
	{0x90,"���Ǳ�ϵͳ��Ƭ"},
	{0x91,"��Ƭ������Ч��"},
	{0x92,"���д����Ӧ�ô������"},
	{0x93,"�Ƿ���"},
	{0x94,"��������"},
	{0x95,"Ǯ������"},
	{0x96,"Ǯ����������"},
	{0x97,"Ǯ��δ����"},
	{0x98,"Ǯ����ͣ��"},
	{0x99,"Ǯ���������ƻ�"},
	{0x9A,"Ǯ��������"},
	{0x9F,"������Ϣ�����ƻ�"},
	{0xAF,"��Ƭ������ʱ"},
	{0x55,"����û��ִ��"},
	{0xCC,"���׹��̳����жϣ�����û�����"},
	{0xFF,"����ʧ��/��֤ʧ��"},
	{0xB0,"���ײ�����;�ж�"},
	{0xB1,"����ʧ��"},
	{0xB2,"ǰһ��ָ��δִ�л�ִ��ʧ��"},
	{0xC1,"������ֵ���󱻾ܾ�"},
	{0xC2,"������ֵ��֤ʧ��"},
	{0xC3,"���׽���ύ����"},
	{0xCE,"������ֵЭ�����"},
	{0xCF,"���ײ�����ʱ"},
	{0xE0,"MIFAREӲ����ʼ������"},
	{0xE1,"SAMӲ����ʼ������"},
	{0xE2,"�������"},
	{0xE3,"��������"},
	{0xE4,"У��ʹ���"},
	{0xE5,"��·ͨѶ��ʱ"},
	{0xE6,"�ڲ�Flashд����"},
	{0xD0,"Զ�̶�д��ִ�д�"},
	{0x30,"����ͷ��"},
	{0x31,"��Ƭ��һ��"},
	{0x32,"��ˮ�Ų�һ��"},
	{0x33,"MAC��"},
	{0x3F,"��֧�ֵ�����"},
	{1001,"���ڴ򿪴���"},
	{1051,"ͨѶ��ʱ"},
	{1002,"�رվ������"},
	{1003,"IP��ַ����"},
	{1004,"������̻�ID����"},
	{1005,"Ŀ¼����"},
	{1006,"�����ļ�����������д�����ɽ��׼�¼©��,"},
	{1007,"�ȴ���ֵ�źų���һ������������,"},
	{1101,"��������ʧ��"},
	{1102,"ͨѶУ�����"},
	{1012,"δ���ò���"},
	{1013,"����δ��"},
	{1014,"�ظ��򿪴���"},
	{-1,"�������Ӵ���"},
	{1300,"��ʼ��ʱ��ѡ��������,���ֵ�����ѣ�������������δѡ����"},
	{1301,"��ֵ���Ϊ0���˹��ܿ�������ֻ��PKI��������²�ѯ���"},
	{1200,"������Ʊ��������ʧ��"},
	{1201,"��¼��Ʊ��������ʧ��"},
	{1202,"EƱ���ʻ����ͨ�۷Ѵ���"},
	{1203,"EƱ���ʻ����ͨ�۷�ȷ�ϴ���"},
	{1204,"EƱ���ʻ����ͨ��������"},
	{1205,"Υ��ҵ��������ֵ�����Ϲ淶,"},
	{0x9106,"��ȡ��ֵ��Կ����"},
	{0x00,"�ɹ�"},
	{0xFF,"ϵͳ����Ҫ������"},
	{0x11,"��Ʊ���Ͳ���"},
	{0x12,"�����Ͳ���"},
	{0x13,"����������"},
	{0x14,"�ն˽��û�ISAM_IDΪ��"},
	{0x15,"�����Ų�����"},
	{0x16,"��������"},
	{0x17,"Ʊ��������Ч��"},
	{0x21,"û�и�����������Ʊ�ײ�"},
	{0x22,"��·�Ŵ���"},
	{0x2F,"��������"},
	{0x30,"����ͷ��"},
	{0x31,"��Ƭ��һ��"},
	{0x32,"��ˮ�Ų�һ��"},
	{0x33,"MAC��"},
	{0x3F,"��������"},
	{0x41,"���ױ���û�н�����ѯ����"},
	{0x42,"��γ��ִ���"},
	{0x43,"��ЧƱ��"},
	{0x44,"����ԭ��������Ϣ������"},
	{0x45,"�ظ���ֵ"},
	{0x46,"��ֵ������������"},
	{0x47,"�ظ���ֵ"},
	{0x48,"���ڷ���ʱ��"},
	{0x49,"��������"},
	{0x50,"�ʺű�����"},
	{0x51,"�����ն�ÿ���޶�"},
	{0x52,"�ʺ�����"},
	{0x53,"��ֵǰ�������Ч"},
	{0x5F,"��������"},
	{0xA1,"��Ʊ��ֵ������ϵͳ����Ҫ������"},
	{0x99,"ϵͳ����"},
	{0xFFFFFFFF,"δ֪����"}
};

static const char * do_find_yct_error(int e)
{
	int i;
	static char dummy_msg[2] = "";
	for(i = 0;i < sizeof(g_yct_errmsg)/sizeof(g_yct_errmsg[0]);++i)
	{
		if(e == g_yct_errmsg[i].errcode)
		{
			return g_yct_errmsg[i].errmsg;
		}
	}
	return dummy_msg;
}

static void str2hex(const char *str,int len,unsigned char *hex)
{
	int i;
	char temp[3] = "";
	for(i =0;i < len;i+=2)
	{
		memcpy(temp,str+i,2);
		hex[i/2] = (unsigned char)strtoul(temp,NULL,16);
	}
}

static void str2bcd(const char *str,int len,char *bcd)
{
	int i;
	char temp[3] = "";
	for(i =0;i < len;i+=2)
	{
		bcd[i/2] = ((str[i]-'0') << 4) & 0xF0;
		bcd[i/2] |= (str[i+1]-'0') & 0x0F;
	}
}
//////////////////////////////////////////////////////////////////////////
// ��������
static HMODULE g_carddll = NULL;
static HMODULE g_yctdll = NULL;
static char g_modulepath[1024];

KSYkt_Log_Writer g_logger("ksinterface");

static struct {
	char yct_svr_ip[20];
	int yct_svr_port;
	char yctyp_svr_ip[20];
	int yctyp_svr_port;
	char eplink_svr_ip[20];
	int eplink_svr_port;
	char yct_reader_id[20];
	int reader_port;
	int reader_baud;
	int yct_reader_open;
	int psamslot;
	char pincode[30];
	unsigned char initkey[30];
	int hdversion;
	char svrcode[10];
}g_yct_param;

#define STRCOPY(d,s) do { strncpy((d),(s),sizeof(d)-1); }while(0)

//////////////////////////////////////////////////////////////////////////
// ��ʼ������
static int do_load_card_dll()
{
	if(g_carddll == NULL)
	{
		g_carddll = LoadLibrary("carddll.dll");
		if(g_carddll == NULL)
		{
			DEBUG_LOG(("����CardDLLʧ��"));
			return -1;
		}
	}
	LOAD_CARD_DLLFUNC(g_carddll,ConnectMF);
	LOAD_CARD_DLLFUNC(g_carddll,CloseMF);
	LOAD_CARD_DLLFUNC(g_carddll,Load_Dll);
	LOAD_CARD_DLLFUNC(g_carddll,Load_WorkKey);
	LOAD_CARD_DLLFUNC(g_carddll,ReadCardNO);
	LOAD_CARD_DLLFUNC(g_carddll,ReadBalance);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_SetNormalFlagByBlkVerion);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_WritePersonalPassword);
	LOAD_CARD_DLLFUNC(g_carddll,ReadSerial);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_PacketSetMoney);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_TransWaterPacket);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_ReadWaterPackInfo2);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_WriteWaterPackInfo2);
	LOAD_CARD_DLLFUNC(g_carddll,ReadCardInfo);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_ReadWaterPackInfo_XT);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_TransWaterPacket_XT);
	LOAD_CARD_DLLFUNC(g_carddll,JD2XT_Card);
	LOAD_CARD_DLLFUNC(g_carddll,XT2JD_Card);
	LOAD_CARD_DLLFUNC(g_carddll,SMT_GetCOMHandle);
	return 0;
}

static int do_load_yct_dll()
{
	char config_file[1024];
	if(g_yctdll == NULL)
	{
		g_yctdll = LoadLibrary("AdvanSta.dll");
		if(g_yctdll == NULL)
		{
			DEBUG_LOG(("�������ͨAdvanStaʧ��"));
			return -1;
		}
	}
	LOAD_YCT_DLLFUNC(g_yctdll,ConfigParamters);
	LOAD_YCT_DLLFUNC(g_yctdll,Common_Initialize_RW);
	LOAD_YCT_DLLFUNC(g_yctdll,Common_Destroy_RW);
	LOAD_YCT_DLLFUNC(g_yctdll,QueryBalance);
	LOAD_YCT_DLLFUNC(g_yctdll,CashIncrease);
	// �������ͨ���� 
	sprintf(config_file,"%s\\carddll.ini",g_modulepath);
	CCIniFile init(config_file);
	std::string v;
	v = init.ReadString("YCT","svrip","");
	STRCOPY(g_yct_param.yct_svr_ip,v.c_str());
	g_yct_param.yct_svr_port = init.ReadInteger("YCT","svrport",0);
	v = init.ReadString("YCT","yp_svrip","");
	STRCOPY(g_yct_param.yctyp_svr_ip,v.c_str());
	g_yct_param.yctyp_svr_port = init.ReadInteger("YCT","yp_svrport",0);
	v = init.ReadString("YCT","eplink_svrip","");
	STRCOPY(g_yct_param.eplink_svr_ip,v.c_str());
	g_yct_param.eplink_svr_port = init.ReadInteger("YCT","eplink_svrport",0);

	DEBUG_LOG(("��ȡ���ͨ����,���ͨ[%s:%d],��Ʊ[%s:%d],��Ʊ��[%s:%d]",
		g_yct_param.yct_svr_ip,g_yct_param.yct_svr_port,
		g_yct_param.yctyp_svr_ip,g_yct_param.yct_svr_port,
		g_yct_param.eplink_svr_ip,g_yct_param.eplink_svr_port));

	v = init.ReadString("YCT","DEVICEID","");
	STRCOPY(g_yct_param.yct_reader_id,v.c_str());

	//////////////////////////////////////////////////////////////////////////
	g_yct_param.psamslot = init.ReadInteger("YCT","psam_slot",0);
	v = init.ReadString("YCT","pincode","");
	STRCOPY(g_yct_param.pincode,v.c_str());

	v = init.ReadString("YCT","initkey","");
	str2hex(v.c_str(),16,g_yct_param.initkey);

	g_yct_param.hdversion = init.ReadInteger("YCT","hdversion",0);

	v = init.ReadString("YCT","svrcode","");
	str2bcd(v.c_str(),4,g_yct_param.svrcode);

	DEBUG_LOG(("���ͨ����,psam[%d]hdversion[%d]",g_yct_param.psamslot,g_yct_param.hdversion));

	return 0;
}

static int do_initialize()
{
	GetModuleFileName(NULL,g_modulepath,sizeof(g_modulepath)-1);
	char * p = strrchr(g_modulepath,'\\');
	if(p != NULL)
	{
		*p = '\0';
	}
	g_logger.openlog(g_modulepath);
	memset(&g_yct_param,0,sizeof g_yct_param);
	if(do_load_card_dll())
		return -1;
	if(do_load_yct_dll())
		return -1;
	return 0;
}
static int g_is_initialized = do_initialize();

//////////////////////////////////////////////////////////////////////////
// ��װ CardDLL ����
int CARDAPI ConnectMF(int port, int baud)
{
	g_yct_param.reader_port = port;
	g_yct_param.reader_baud = baud;
	return CardConnectMF(port,baud);
}
int CARDAPI CloseMF()
{
	return CardCloseMF();
}
static int do_load_yct()
{
	int ret;
	ret = YCTConfigParamters(g_yct_param.yct_svr_ip,g_yct_param.yct_svr_port,
		g_yct_param.yctyp_svr_ip,g_yct_param.yctyp_svr_port,
		g_yct_param.eplink_svr_ip,g_yct_param.eplink_svr_port,
		g_yct_param.yct_reader_id);
	if(ret)
	{
		DEBUG_LOG(("�������ͨ[ConfigParamters]����,[%d:%s]",ret,do_find_yct_error(ret)));
		return -1;
	}
	DEBUG_LOG(("�������ͨ[ConfigParamters]�ɹ�"));
	return 0;
}
int CARDAPI Load_Dll()
{
	/*
	1. ����һ��ͨ carddll �Ĳ���
	2. ���� yct �Ĳ���
	3. 
	*/
	int ret;
	ret = CardLoad_Dll();
	if(ret)
	{
		DEBUG_LOG(("����CardDLL[LoadDll]ʧ��ret[%d]",ret));
		return ret;
	}
	ret = do_load_yct();
	if(ret)
		return ret;
	DEBUG_LOG(("����Load_Dll�ɹ�"));
	return 0;
}
int CARDAPI Load_WorkKey(char *ascWorkKey)
{
	return CardLoad_WorkKey(ascWorkKey);
}
int CARDAPI ReadBalance(int nPacketNo,int *nBalance,int *nCnt)
{
	return CardReadBalance(nPacketNo,nBalance,nCnt);
}

int CARDAPI ReadCardNO(int *nCardNo)
{
	return CardReadCardNO(nCardNo);
}
int CARDAPI SMT_SetNormalFlagByBlkVerion(char *blkversion)
{
	return CardSMT_SetNormalFlagByBlkVerion(blkversion);
}
int CARDAPI SMT_WritePersonalPassword(unsigned char newpwd[3])
{
	return CardSMT_WritePersonalPassword(newpwd);
}
int CARDAPI ReadSerial(unsigned char *serial)
{
	return CardReadSerial(serial);
}

int CARDAPI SMT_PacketSetMoney(int nPacketNo,int nMoney)
{
	return CardSMT_PacketSetMoney(nPacketNo,nMoney);
}

int CARDAPI SMT_TransWaterPacket(int main_money,WATER_PACK_INFO3* info)
{
	return CardSMT_TransWaterPacket(main_money,info);
}

int CARDAPI SMT_ReadWaterPackInfo2(WATER_PACK_INFO3* info)
{
	return CardSMT_ReadWaterPackInfo2(info);
}
int CARDAPI SMT_WriteWaterPackInfo2(WATER_PACK_INFO3* info)
{
	return CardSMT_WriteWaterPackInfo2(info);
}

int CARDAPI ReadCardInfo(TPublishCard *pc)
{
	return CardReadCardInfo(pc);
}

int CARDAPI SMT_ReadWaterPackInfo_XT(WATER_PACK_INFO3* info)
{
	return CardSMT_ReadWaterPackInfo_XT(info);
}
int CARDAPI SMT_TransWaterPacket_XT(int main_money,WATER_PACK_INFO3* info)
{
	return CardSMT_TransWaterPacket_XT(main_money,info);
}
int CARDAPI JD2XT_Card()
{
	return CardJD2XT_Card();
}
int CARDAPI XT2JD_Card()
{
	return CardXT2JD_Card();
}

//////////////////////////////////////////////////////////////////////////
// ��װ���ͨ�ӿ�
class YCT_Reader_Guard
{
private:
	int is_reader_open_;
	int do_open_reader()
	{
		int ret;
		if(is_reader_open_==1)
			return 0;
		CardCloseMF();
		is_reader_open_ = 0;
		DEBUG_LOG(("����Common_Initialize_RW handle[%08X]",g_yct_reader));
		ret = YCTCommon_Initialize_RW(g_yct_param.reader_port,g_yct_param.reader_baud,
			g_yct_param.psamslot,g_yct_param.pincode,g_yct_param.initkey,g_yct_param.hdversion,
			g_yct_param.svrcode,1);
		if(ret)
		{
			DEBUG_LOG(("����Common_Initialize_RWʧ��[%d:%s]",ret,do_find_yct_error(ret)));
			return -1;
		}
		DEBUG_LOG(("����Common_Initialize_RW�ɹ�"));
		is_reader_open_ = 1;
		return 0;
	}
public:
	YCT_Reader_Guard()
	{
		do_open_reader();
	}
	~YCT_Reader_Guard()
	{
		if(is_reader_open_)
		{
			DEBUG_LOG(("����Common_Destroy_RW"));
			YCTCommon_Destroy_RW(g_yct_param.reader_port);
			is_reader_open_ = 0;
			CardConnectMF(g_yct_param.reader_port,g_yct_param.reader_baud);
		}
	}
	int is_opened()
	{
		return is_reader_open_;
	}
};

int CARDAPI QueryBalance(const int nPort,PPURCHSEARCH pPurSearch)
{
	int ret;
	YCT_Reader_Guard guard;
	if(!guard.is_opened())
	{
		return -1;
	}
	ret = YCTQueryBalance(nPort,pPurSearch);
	if(ret)
	{
		DEBUG_LOG(("�������ͨQueryBalanceʧ��[%d:%s]",ret,do_find_yct_error(ret)));
		return ret;
	}
	return 0;
}

static PURCHSEARCH g_purch;
int CARDAPI QueryBalance2(const int nPort,long *phyid,long * balance)
{
	int ret;
	YCT_Reader_Guard guard;
	memset(&g_purch,0,sizeof g_purch);
	if(!guard.is_opened())
	{
		return -1;
	}
	ret = YCTQueryBalance(nPort,&g_purch);
	if(ret)
	{
		DEBUG_LOG(("�������ͨQueryBalanceʧ��[%d:%s]",ret,do_find_yct_error(ret)));
		return ret;
	}
	*phyid = g_purch.dwPhysicalID;
	*balance = g_purch.dwBalance;
	return 0;
}

int CARDAPI CashIncrease(const int nPort, const DWORD dwValue, PPURCHASEINCREASE pIncrease, BOOL bMustCmp)
{
	int ret;
	YCT_Reader_Guard guard;
	if(!guard.is_opened())
	{
		return -1;
	}
	ret = YCTCashIncrease(nPort,dwValue,pIncrease,bMustCmp);
	if(ret)
	{
		DEBUG_LOG(("�������ͨCashIncreaseʧ��[%d:%s]",ret,do_find_yct_error(ret)));
		return ret;
	}
	return 0;
}

int CARDAPI CashIncrease2(const int nPort,const DWORD dwValue,long *dwBalance)
{
	int ret;
	YCT_Reader_Guard guard;
	PURCHASEINCREASE increase;
	if(!guard.is_opened())
	{
		return -1;
	}
	
	memset(&increase,0,sizeof increase);
	increase.dwPhysicalID = g_purch.dwPhysicalID;
	ret = YCTCashIncrease(nPort,dwValue,&increase,TRUE);
	if(ret)
	{
		DEBUG_LOG(("�������ͨCashIncreaseʧ��[%d:%s]",ret,do_find_yct_error(ret)));
		return ret;
	}
	*dwBalance = increase.dwSithBalance;
	return 0;
}
