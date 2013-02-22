#include "ksinterface.h"
#include "logfile.h"
#include "CIniFile.h"


/************************************************************************
本模块设计的目的是大学城银达圈存机处理羊城通业务的需要
由于羊城通提供了开发动态库，需要使用读卡器读写卡。
银达圈存机对两种读卡器比较困难，我们需要封装对两种业务的操作
************************************************************************/

//////////////////////////////////////////////////////////////////////////
// CardDLL 部分定义
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
// 羊城通部分定义
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
	{0x00,"操作成功"},
	{0x60,"没有安装SAM卡"},
	{0x61,"SAM卡初始化错误或未初始化"},
	{0x62,"SAM校验PIN错误"},
	{0x63,"SAM卡类型与交易类型不匹配"},
	{0x64,"SAM卡选择文件错误"},
	{0x65,"SAM读错误"},
	{0x66,"SAM卡写错误"},
	{0x67,"SAM卡认证错误"},
	{0x68,"SAM卡取随机数错误"},
	{0x69,"SAM卡DES计算错误"},
	{0x6A,"SAM卡生成钱包密钥错误"},
	{0x71,"PKI卡RSA计算错误"},
	{0x72,"PKI卡DES计算错误"},
	{0x7E,"SAM卡执行APDU命令错误"},
	{0x7F,"SAM卡操作超时"},
	{0x80,"没有卡"},
	{0x81,"选择卡片错误"},
	{0x82,"停用卡片错误"},
	{0x83,"认证卡片错误"},
	{0x84,"卡片读错误"},
	{0x85,"卡片写错误"},
	{0x86,"卡片写操作中途中断"},
	{0x87,"充值卡片无响应"},
	{0x90,"不是本系统卡片"},
	{0x91,"卡片超出有效期"},
	{0x92,"城市代码或应用代码错误"},
	{0x93,"非法卡"},
	{0x94,"黑名单卡"},
	{0x95,"钱包余额不足"},
	{0x96,"钱包余额超出上限"},
	{0x97,"钱包未启用"},
	{0x98,"钱包已停用"},
	{0x99,"钱包正本被破坏"},
	{0x9A,"钱包已启用"},
	{0x9F,"公共信息区被破坏"},
	{0xAF,"卡片操作超时"},
	{0x55,"交易没有执行"},
	{0xCC,"交易过程出现中断，交易没有完成"},
	{0xFF,"交易失败/认证失败"},
	{0xB0,"交易操作中途中断"},
	{0xB1,"交易失败"},
	{0xB2,"前一步指令未执行或执行失败"},
	{0xC1,"联机充值请求被拒绝"},
	{0xC2,"联机充值认证失败"},
	{0xC3,"交易结果提交错误"},
	{0xCE,"联机充值协议错误"},
	{0xCF,"交易操作超时"},
	{0xE0,"MIFARE硬件初始化错误"},
	{0xE1,"SAM硬件初始化错误"},
	{0xE2,"命令错误"},
	{0xE3,"参数错误"},
	{0xE4,"校验和错误"},
	{0xE5,"线路通讯超时"},
	{0xE6,"内部Flash写错误"},
	{0xD0,"远程读写器执行错"},
	{0x30,"报文头错"},
	{0x31,"卡片不一致"},
	{0x32,"流水号不一致"},
	{0x33,"MAC错"},
	{0x3F,"不支持的命令"},
	{1001,"串口打开错误"},
	{1051,"通讯超时"},
	{1002,"关闭句柄出错"},
	{1003,"IP地址错误"},
	{1004,"传入的商户ID错误"},
	{1005,"目录错误"},
	{1006,"交易文件已满，继续写这会造成交易记录漏传,"},
	{1007,"等待充值信号出错，一般由网络引起,"},
	{1101,"网络连接失败"},
	{1102,"通讯校验错误"},
	{1012,"未配置参数"},
	{1013,"串口未打开"},
	{1014,"重复打开串口"},
	{-1,"网络连接错误"},
	{1300,"初始化时仅选单个功能,如充值或消费，但操作了其他未选功能"},
	{1301,"充值金额为0！此功能可用来在只有PKI卡的情况下查询余额"},
	{1200,"连接易票联服务器失败"},
	{1201,"登录易票联服务器失败"},
	{1202,"E票联帐户羊城通扣费错误"},
	{1203,"E票联帐户羊城通扣费确认错误"},
	{1204,"E票联帐户羊城通冲正错误"},
	{1205,"违反业务规则，如充值金额不符合规范,"},
	{0x9106,"获取充值密钥错误"},
	{0x00,"成功"},
	{0xFF,"系统错误（要冲正）"},
	{0x11,"月票类型不对"},
	{0x12,"卡类型不对"},
	{0x13,"管理卡被禁用"},
	{0x14,"终端禁用或ISAM_ID为空"},
	{0x15,"管理卡号不存在"},
	{0x16,"黑名单卡"},
	{0x17,"票卡超过有效期"},
	{0x21,"没有附和条件的月票套餐"},
	{0x22,"线路号错误"},
	{0x2F,"其他错误"},
	{0x30,"报文头错"},
	{0x31,"卡片不一致"},
	{0x32,"流水号不一致"},
	{0x33,"MAC错"},
	{0x3F,"其他错误"},
	{0x41,"交易报文没有紧跟查询报文"},
	{0x42,"入参出现错误"},
	{0x43,"无效票卡"},
	{0x44,"卡内原有周期信息不完整"},
	{0x45,"重复充值"},
	{0x46,"充值超过两个周期"},
	{0x47,"重复充值"},
	{0x48,"不在服务时段"},
	{0x49,"参数不足"},
	{0x50,"帐号被禁用"},
	{0x51,"超过终端每天限额"},
	{0x52,"帐号余额不足"},
	{0x53,"充值前后余次无效"},
	{0x5F,"其他错误"},
	{0xA1,"月票充值服务器系统错误（要冲正）"},
	{0x99,"系统错误"},
	{0xFFFFFFFF,"未知错误"}
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
// 公共部分
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
// 初始化部分
static int do_load_card_dll()
{
	if(g_carddll == NULL)
	{
		g_carddll = LoadLibrary("carddll.dll");
		if(g_carddll == NULL)
		{
			DEBUG_LOG(("加载CardDLL失败"));
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
			DEBUG_LOG(("加载羊城通AdvanSta失败"));
			return -1;
		}
	}
	LOAD_YCT_DLLFUNC(g_yctdll,ConfigParamters);
	LOAD_YCT_DLLFUNC(g_yctdll,Common_Initialize_RW);
	LOAD_YCT_DLLFUNC(g_yctdll,Common_Destroy_RW);
	LOAD_YCT_DLLFUNC(g_yctdll,QueryBalance);
	LOAD_YCT_DLLFUNC(g_yctdll,CashIncrease);
	// 加载羊城通参数 
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

	DEBUG_LOG(("读取羊城通参数,羊城通[%s:%d],月票[%s:%d],易票联[%s:%d]",
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

	DEBUG_LOG(("羊城通参数,psam[%d]hdversion[%d]",g_yct_param.psamslot,g_yct_param.hdversion));

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
// 封装 CardDLL 部分
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
		DEBUG_LOG(("调用羊城通[ConfigParamters]错误,[%d:%s]",ret,do_find_yct_error(ret)));
		return -1;
	}
	DEBUG_LOG(("调用羊城通[ConfigParamters]成功"));
	return 0;
}
int CARDAPI Load_Dll()
{
	/*
	1. 加载一卡通 carddll 的参数
	2. 加载 yct 的参数
	3. 
	*/
	int ret;
	ret = CardLoad_Dll();
	if(ret)
	{
		DEBUG_LOG(("加载CardDLL[LoadDll]失败ret[%d]",ret));
		return ret;
	}
	ret = do_load_yct();
	if(ret)
		return ret;
	DEBUG_LOG(("加载Load_Dll成功"));
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
// 封装羊城通接口
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
		DEBUG_LOG(("调用Common_Initialize_RW handle[%08X]",g_yct_reader));
		ret = YCTCommon_Initialize_RW(g_yct_param.reader_port,g_yct_param.reader_baud,
			g_yct_param.psamslot,g_yct_param.pincode,g_yct_param.initkey,g_yct_param.hdversion,
			g_yct_param.svrcode,1);
		if(ret)
		{
			DEBUG_LOG(("调用Common_Initialize_RW失败[%d:%s]",ret,do_find_yct_error(ret)));
			return -1;
		}
		DEBUG_LOG(("调用Common_Initialize_RW成功"));
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
			DEBUG_LOG(("调用Common_Destroy_RW"));
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
		DEBUG_LOG(("调用羊城通QueryBalance失败[%d:%s]",ret,do_find_yct_error(ret)));
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
		DEBUG_LOG(("调用羊城通QueryBalance失败[%d:%s]",ret,do_find_yct_error(ret)));
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
		DEBUG_LOG(("调用羊城通CashIncrease失败[%d:%s]",ret,do_find_yct_error(ret)));
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
		DEBUG_LOG(("调用羊城通CashIncrease失败[%d:%s]",ret,do_find_yct_error(ret)));
		return ret;
	}
	*dwBalance = increase.dwSithBalance;
	return 0;
}
