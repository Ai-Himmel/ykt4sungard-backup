#include <iostream>
#include <map>
#include <ostream>
#include <fstream>
#include <sstream>
#include <list>

#include "kslicense.h"

#ifdef WIN32
	#include "XGetOpt.h"
#else
	#include <getopt.h>
#endif

using namespace std;

#define ERR_LOG(x) do{ stringstream _m;_m<<x; this->error(_m); }while(0)

class KsLcsReader
{
private:
	string appName_;
	string keyFile_;
	string lcsFile_;
	ks_cardlib_license license_;
	inline void printUsage();
	bool fileExists(const std::string &fileName);
	int readLcsFile();
	void error(const stringstream &msg);
	int loadPubKey();
	int dumpHeader();
public:
	KsLcsReader();
	~KsLcsReader();
	int run(int argc,char * const argv[]);
};
KsLcsReader::KsLcsReader()
{
}
KsLcsReader::~KsLcsReader()
{
}
bool KsLcsReader::fileExists(const std::string &fileName)
{
	ifstream ifs(fileName.c_str(),ios_base::in|ios_base::binary);
	if(ifs.fail())
		return false;
	return true;
}
int KsLcsReader::run(int argc,char * const argv[])
{
	int c;
	appName_ = argv[0];
	while((c = getopt(argc,argv,"k:l:"))!=EOF)
	{
		switch(c)
		{
		case 'k':
			keyFile_ = optarg;
			break;
		case 'l':
			lcsFile_ = optarg;
			break;
		default:
			printUsage();
			exit(-1);
			break;
		}
	}
	if(lcsFile_.length() == 0)
	{
		printUsage();
		return -1;
	}
	return readLcsFile();
}
int KsLcsReader::dumpHeader()
{
	char paramvalue[512]={0};
	int maxlen = sizeof(paramvalue) - 1;
	int ret = license_.get_public_param(ks_cardlib_license::LCNS_VERSION,paramvalue,maxlen);
	if(ret)
	{
		ERR_LOG("Cannot get LCNS_VERSION parameter");
		return -1;
	}
	string version = paramvalue;
	memset(paramvalue,0,sizeof paramvalue);
	ret = license_.get_public_param(ks_cardlib_license::LCNS_CUST_ID,paramvalue,maxlen);
	if(ret)
	{
		ERR_LOG("Cannot get LCNS_CUST_ID parameter");
		return -1;
	}
	string custid = paramvalue;

	memset(paramvalue,0,sizeof paramvalue);
	ret = license_.get_public_param(ks_cardlib_license::LCNS_EXPIRED_DATE,paramvalue,maxlen);
	if(ret)
	{
		ERR_LOG("Cannot get LCNS_EXPIRED_DATE parameter");
		return -1;
	}
	string expired = paramvalue;
	
	cout<<"KS License Version: "<<version<<" Expired: "<<expired<<" Cust: "<<custid<<endl;
	return 0;
}
int KsLcsReader::readLcsFile()
{
	if(!fileExists(lcsFile_))
	{
		ERR_LOG("Cannot open license file <"<<lcsFile_<<">");
		return -1;
	}
	if(loadPubKey())
		return -1;
	int ret = license_.load_license_file(lcsFile_.c_str());
	if(ret)
	{
		ERR_LOG("Cannot load license file ret["<<ret<<"]");
		return -1;
	}
	std::list<ks_cllcns_param_t> params;
	ret = license_.get_all_parameters(params);
	if(ret)
	{
		ERR_LOG("Get all params error,ret["<<ret<<"]");
		return -1;
	}
	if(dumpHeader())
	{
		return -1;
	}
	std::list<ks_cllcns_param_t>::const_iterator iter = params.begin();
	for(;iter != params.end();++iter)
	{
		ks_cllcns_param_t p = *iter;
		if(p.param_name == ks_cardlib_license::LCNS_VERSION
			|| p.param_name == ks_cardlib_license::LCNS_CUST_ID
			|| p.param_name == ks_cardlib_license::LCNS_EXPIRED_DATE)
			continue;
		cout<<""<<p.param_flag<<","
			<<p.param_name<<","
			<<p.param_summary<<","
			<<p.param_value<<endl;
	}
	return 0;
}
void KsLcsReader::error(const stringstream &msg)
{
	cout<<msg.str()<<endl;
}

inline void KsLcsReader::printUsage()
{
	cout<<"Usage: "<<std::endl;
	cout<<appName_.c_str()
		<<" [-k public key file ] -l license file"
		<<std::endl;
}
int KsLcsReader::loadPubKey()
{
	if(keyFile_.length() == 0)
	{
		keyFile_ = "pub.key";
	}
	if(!fileExists(keyFile_))
	{
		ERR_LOG("Cannot open Public Key file <"<<keyFile_<<">");
		return -1;
	}
	int ret = license_.load_public_key_file(keyFile_.c_str());
	if(ret)
	{
		ERR_LOG("Cannot load pubkey ret=["<<ret<<"]");
		return -1;
	}
	return 0;
}
int main(int argc,char * const argv[])
{
	KsLcsReader reader;
	exit(reader.run(argc,argv));
	return 0;
}