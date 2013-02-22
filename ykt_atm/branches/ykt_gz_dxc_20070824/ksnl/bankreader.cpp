#include "StdAfx.h"
#include "bankreader.h"
#include "ksnl.h"
#include "logfile.h"
#include "CIniFile.h"
#include "ksutil.h"

DEF_DLLFUNC_STATIC(int,gOpenCom,(int nPort))
DEF_DLLFUNC_STATIC(int,gCloseCom,(void))
DEF_DLLFUNC_STATIC(int,ZTCloseMagCard,(void))
DEF_DLLFUNC_STATIC(int,ZTMagCardRead,(char *pchTrk2,char *pchTrk3))
DEF_DLLFUNC_STATIC(int,ZTMagCardStart,(int nTrackNum))

KSBankReader::KSBankReader()
:port_(0),h_magdll(NULL)
{
	//empty
}
KSBankReader::~KSBankReader()
{
	close();
	if(h_magdll)
	{
		FreeLibrary(h_magdll);
		h_magdll = NULL;
	}
}
int KSBankReader::load_dllfunc()
{
	if(h_magdll)
	{
		return 0;
	}
	h_magdll = LoadLibrary("MagCard.dll");
	if(h_magdll == NULL)
		return -1;
	LOAD_DLLFUNC(h_magdll,gOpenCom);
	LOAD_DLLFUNC(h_magdll,gCloseCom);
	LOAD_DLLFUNC(h_magdll,ZTCloseMagCard);
	LOAD_DLLFUNC(h_magdll,ZTMagCardRead);
	LOAD_DLLFUNC(h_magdll,ZTMagCardStart);
	return 0;
}
int KSBankReader::open()
{
	int ret,portnum;
	if(port_ > 0)
		return 0;
	CKsnlApp *app = (CKsnlApp*)AfxGetApp();
	if(!app)
		return -1;
	CString file_path;
	file_path.Format("%s\\ksnl.ini",app->m_appPath);
	CCIniFile inifile((LPCTSTR)file_path);
	std::string  iccom = inifile.ReadString("COM","ICCOM","");
	if(iccom.empty())
		return -1;

	if(load_dllfunc())
	{
		AfxMessageBox("加载磁卡读卡库失败!");
		return -1;
	}
	portnum = atoi(iccom.substr(3).c_str());
	// TODO : 打开银行卡读卡器
#if 0
	port_ = portnum;
	ret = 0;
#else
	ret = gOpenCom(portnum);
	if(!ret)
		port_ = portnum;
	//if(ret)
	//	return -1;
#endif // 
	DEBUG_LOG(("打开银行卡计卡器[%s]ret[%d]",iccom.c_str(),ret));
	
	return ret;
}
int KSBankReader::close()
{
	int ret = 0;
	if(port_ > 0)
	{
#if 0
#else
		ret = gCloseCom();
#endif 
		port_ = 0;
	}
	return ret;
}
int KSBankReader::ReadBankCard(int timeout,char *bank_no)
{
	int ret,retries;
	char trace2[128] = "";
	char trace3[128] = "";
	if(port_ <= 0)
		return -2;
	
#if 0
	strcpy(bank_no,"96691020030202");
	Sleep(2000);
#else
	// TODO : 读银行卡号
	DEBUG_LOG(("读取银行卡第二磁道"));
	ret = ZTMagCardStart(2);
	if(!ret)
	{
		retries = timeout * 1000 / 100;
		while(retries-->0)
		{
			ret = ZTMagCardRead(trace2,trace3);
			if(1==ret)
			{
				if(strlen(trace2) > 0)
				{
					// 读取成功
					ZTCloseMagCard();
					strncpy(bank_no,trace2,19);
					return 0;
				}
			}
			else if(-1==ret)
			{
				AfxMessageBox("磁条读卡器读取数据失败");
				return -1;
			}
			Sleep(100);
		}
		ZTCloseMagCard();
		return -1;
	}
#endif
	return ret;
}