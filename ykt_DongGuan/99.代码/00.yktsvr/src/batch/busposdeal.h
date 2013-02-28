#ifndef _BUSPOSDEAL_H_
#define _BUSPOSDEAL_H_

#include <string>


enum {
EBUS_SUCCESS=0,     //成功
EBUS_TAC,           //TAC验证失败
EBUS_CARDCANCEL,    //卡已注销
EBUS_CARDNOTEXIST,  //卡号不存在
EBUS_CARDLOST,      //卡已挂失
EBUS_SHOPNOTEXIST,  //商户不存在
EBUS_SHOPCANCEL,    //商户已注销
EBUS_SHORTBAL,      //账户余额不足
EBUS_CARDCNTERR,	//卡交易次数错误
};

typedef std::vector<int> INT_VECTOR_TYPE;
typedef std::vector<T_t_posdtl> POSDTL_VECTOR_TYPE;
typedef std::vector<T_t_unit> UNIT_VECTOR_TYPE;
typedef std::map<std::string,std::string> VALUE_MAP_TYPE;




class BusGetFileProcess
{
private:
	std::string dl_filename_;
	T_t_pkg tPkg;
	T_t_unit tUnit;
	T_t_pkgfile tPkgfile;
	
	int doGetDataFilePath(std::string& file_path,int drtpno);
	int doChkFileExists(const std::string& file_name);
	int doDownloadRecord(std::string& dest_path);
	int doParseRecord(const std::string& dest_file,std::string& sqlfile);
	void doReplace(std::string &str,const std::string &pattern,const std::string &value);
	int doInsertPkg(std::string &sql);
	int doUpdPkg(std::string &sql);
	int doInsertPkgFile(std::string &sql);
	int doOneLine(std::string &line);
	void getPkgNo(const std::string& sqlpath,std::string& pkgno);
	int doImportSQL(FILE *sqlfile);
	int doFinishCheck();
	int doImportPosDtl();
	int doCheckProcessAndLock();
	int lockFile(const char * filename);
	int getMD5File(const std::string& filename,std::string& md5Filename,std::string &localMD5File);
	int doCheckDownloadFile(const std::string& pkgFile,const std::string& md5File);
	int doRemoveDownloadFile(const std::string& pkgFile,const std::string& md5File);
	std::string getMD5FileName(const std::string &filename);
	void getFileNameExt(const std::string &filename,std::string& fname,std::string& extname);
	int removeSuccessFile(const std::string &pkgfile,const std::string &sqlfile);
public:
	BusGetFileProcess():dl_filename_("")
	{
	}
	~BusGetFileProcess()
	{
	}
	int dowork();
};

class BusCheckProcess
{
	typedef std::map<int,int> SHOP_MAP_TYPE;
private:
	T_t_settlectl tSettlectl;
	T_t_pkg tPkg;
	T_t_pkgfile tPkgfile;
	INT_VECTOR_TYPE pkgfilesVec;
	SHOP_MAP_TYPE all_shop_;
	
	int doGetPOSDTLVec(POSDTL_VECTOR_TYPE &vec,char st);
	int doSendToEncSvr(T_t_posdtl &posdtl);
	int doCheckTAC(T_t_posdtl &posdtl);
	int doDealPOSDtl(T_t_posdtl &posdtl);
	int doSaveCardDtl(T_t_posdtl &posdtl,T_t_card &tCard);
	int doBatchPOSDTL(POSDTL_VECTOR_TYPE &vec);
	int doBatchChkTacPOSDTL(POSDTL_VECTOR_TYPE &vec);
	int doProcessPOSDtl(int fileid);
	int doProcessPkgFile(int fileid);
	int doProessPkg(int pkgid);
	int doCutOff();
	int doCheckShop(T_t_posdtl &posdtl);
	int doCreateFeedback(int pkgid);
	int doUploadFeedbackFile(int unitno,const std::string &fdfile);
	
public:
	BusCheckProcess()
	{
	}
	~BusCheckProcess()
	{
	}
	int doProcessAllPkg();
	int doCheckAllFeedback();
};

class BusUnitsCfg
{
private:
	UNIT_VECTOR_TYPE units_;
	VALUE_MAP_TYPE unitcfg_;
private:
	BusUnitsCfg():unitno(-1),settle_date(20000101),last_date(20000101),
		svrport(0),svrdrtpno(0),svrmainfunc(0)
	{
	}
	static BusUnitsCfg* instance_;
	static const char unit_cfg_para_names[][64];
public:
	int unitno;
	int settle_date;
	int last_date;
	std::string svrip;
	int svrport;
	int svrdrtpno;
	int svrmainfunc;
	std::string process_cmd;
	std::string process_dir;
	std::string feedback_cmd;
	int is_main_svr_;
public:
	static BusUnitsCfg& instance();
	static void free();
	~BusUnitsCfg()
	{
	}
	int doLoadUnitCfgAndSave(const std::string& paraname);
	int doGetUnitCfgStr(const std::string& paraname,std::string& paraval);
	int doGetUnitCfgInt(const std::string& paraname,int *paraval);
	int getUnitCfgStrWithUnitno(int unitno,const std::string& paraname,std::string& paraval);
	int getUnitCfgIntWithUnitno(int unitno,const std::string& paraname,int *paraval);
	int getUnitCfgStr(const std::string& paraname,std::string& paraval);
	int getUnitCfgInt(const std::string& paraname,int *paraval);
	int loadUnitCfg(T_t_unit &tUnit);
	int loadUnits();
	int findUnits(int unitno,T_t_unit &tUnit);
	int doLoadCfg(int unitno);
	void doCheckUnitsWork();
};




#endif // _BUSPOSDEAL_H_
