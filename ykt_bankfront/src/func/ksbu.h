#ifndef _KSBU_H_
#define _KSBU_H_
//	#ifdef __cplusplus
//	extern "C" {
//	#endif

int ERR_DEAL(char *msg,int retcode);

//	#ifdef __cplusplus
//	}
//	#endif
#include <map>
#include <string>
using namespace std;

typedef struct{
	string  bankName;
	string  bankCode;
	string  corpID;
	string  corpPwd;
	string  signUrl;
	string  bankUrl;
}CFG_BANK;


typedef 	map<string,CFG_BANK>  CFGBANKMAP;

typedef struct
{
	CFGBANKMAP  cfgBankMap;
}BankXmlFileCfg;
//int LoadXmlCfgFile(char *xmlcfgfile,BankXmlFileCfg& XmlFileCfg);
extern BankXmlFileCfg  bankXmlFileCfg;
#endif // _KSBU_H_
