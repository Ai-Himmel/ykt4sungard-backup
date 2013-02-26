#include "loaddll.h"
#include "DllFunErrCode.h"
#include "gdctpub.h"
#include "profile.h"

static int GetSysParam(const char *para,char *value)
{
	int ret;
	ST_CPACK aPack,sPack;
	memset(&sPack,0,sizeof sPack);
	memset(&aPack,0,sizeof aPack);

	ResetNormalCPack(&sPack,0,1);
	SetHeadCol(&sPack,F_SNAME,F_SNAME2,0);
	sPack.head.RequestType = 850007;
	strcpy(sPack.pack.sname,"GDCT");
	strcpy(sPack.pack.sname2,para);
	ret = ExtCall(0,g_mainsvr_drtpno,g_mainsvr_func,0,3,&sPack,&aPack,NULL);
	if(ret>=0)
	{
		if(aPack.head.retCode!=0)
			return aPack.head.retCode;
		strncpy(value,aPack.pack.vsvarstr0,128);
		return 0;
	}
	else
	{
		return -1;
	}
}
bool ReadIni1(char *inifile)
{
	TIniFile tf;
	
	printf("Begin to read ini-file:%s...\n",inifile);
	if (!tf.Open(inifile))
		return false;

	g_mainsvr_func = tf.ReadInt("GDCT", "GDCT_MAIN_FUNC", 0);
	g_mainsvr_drtpno = tf.ReadInt("GDCT", "GDCT_MAIN_DRTPNO", 0);
	/*
	tf.ReadString("GDCT", "GDCT_PSWD", "",g_gdct_pswd, sizeof(g_gdct_pswd));
	tf.ReadString("GDCT", "GDCT_PHONE_NUM", "",g_gdct_phone_num, sizeof(g_gdct_phone_num));
	g_timeout = tf.ReadInt("GDCT","GDCT_TIMEOUT",1000);
	*/
	tf.Close();
	
	return(true);
}


CLoadDll::CLoadDll(void) : m_h_data_info_dll(NULL)
{
}

CLoadDll::~CLoadDll(void)
{
}

int CLoadDll::LoadDataInfo(std::string str_dll_name)
{

	if(!ReadIni1((char*)str_dll_name.c_str()))
		return -1000;			// 读取配置文件出错
	return 0;
}

void CLoadDll::UnLoadAllDll()
{
	return ;
}
int CLoadDll::Init()
{
	char temp[129] = "";
	GetSysParam("svrpswd",temp);
	strcpy(g_gdct_pswd,temp);

	GetSysParam("phonenum",temp);
	strcpy(g_gdct_phone_num,temp);

	GetSysParam("timeout",temp);
	g_timeout = atoi(temp);

	memset(temp,0,sizeof temp);
	GetSysParam("transsvrip",temp);
	strcpy(g_xunyuan_svrip,temp);

	memset(temp,0,sizeof temp);
	GetSysParam("transsvrport",temp);
	g_xunyuan_svrport=atoi(temp);

	return 0;
}