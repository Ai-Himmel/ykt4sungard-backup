#ifndef _CARDTYPE_MANAGER_H_
#define _CARDTYPE_MANAGER_H_

#include <map>
#include <vector>
#include <sstream>
#include "kscardtype.h"
#include "kslicense.h"

typedef std::vector<HMODULE> HANDLE_VEC;

class CardTypeManager
{
public:
	typedef unsigned int CARDTYPE_ID;
private:
	typedef std::map<CARDTYPE_ID,ks_cardtype_base *> CARDTYPE_MAP;
	typedef std::vector<ks_cardtype_base *>CARDTYPE_VEC;
	
	int errorCode_;
	std::stringstream errorMsg_;
	ks_cardtype_base *cpuCardType_;
	ks_cardtype_base *LastcpuCardType_;
	ks_psamcard_base *psamCardType_;
	CARDTYPE_ID cpuCardTypeId_;
	CARDTYPE_MAP cardTypeMap_;
	CARDTYPE_VEC cardTypeVec_;
	HANDLE_VEC cardTypeHandle_;
	static CardTypeManager *instance_;
private:
	int registerDLL(HMODULE h,ks_cardtype_base *& c);
	int loadDLL(const char *cardtype,ks_cardtype_base *& c);
	int doLoadAllDLL(ks_cardlib_license *lic,const char *baseDir);
	int addSupportTypes(ks_cardtype_base *c,const char *cardtype);
	int doLoadPSAMDLL(ks_cardlib_license *lic,const char *baseDir);
	int loadPSAM(const char *cardtype,ks_psamcard_base *& p);
	int registerPSAMDLL(HMODULE h,ks_psamcard_base *& c);
public:
	static const int MAX_CARDTYPE = 4;
	CardTypeManager();
	~CardTypeManager();
	void freeAll();
	static CardTypeManager* instance();
	// 根据 license 的配置加载卡类型库
	int loadCardTypeDLL(ks_cardlib_license *lic,const char *baseDir);
	// 根据卡类型获取卡类型库
	ks_cardtype_base *getCardType(CARDTYPE_ID id) const;
	ks_psamcard_base *getPSAMCardType() const;
	void setErrorMsg(const char *errmsg,const char *defaultmsg=NULL);
	const char* getErrorMsg(char *msg,const char* defaultmsg=NULL);
	int supportCardType(int t) const;
	int getCardTypeCount() const { return cardTypeVec_.size(); }
	ks_cardtype_base *getCardTypeByIdx(size_t idx);
	int initComm(const char *ip,int port,int func);
	int getCardTypeCode();
	/////////////////////////////////////////////////
public:
	int requestCard(char *phyId);
	ks_cardtype_base *getLastCardType(bool req = true);
	CARDTYPE_ID getLastCardTypeId() const { return cpuCardTypeId_; }
};

/////////////////////////////////////////////////////////////////////

class CardReaderManager
{
private:
	static const int MAX_READER = 2;
	static const int MAX_READER_TYPE = 3;
	ks_device_op_t reader_[MAX_READER];
	int readerOpen_[MAX_READER];
	ks_device_op_t *readerType_[MAX_READER_TYPE];
	ks_reader_dev_t readerPara_[MAX_READER_TYPE];
	ks_reader_dev_t cardTypeReaderPara_[CardTypeManager::MAX_CARDTYPE];
	int cardTypeReaderNo_[CardTypeManager::MAX_CARDTYPE];
	int readerNo_[MAX_READER_TYPE];
	int errorCode_;
	int m_bPortOpen;
	std::stringstream errorMsg_;
	HANDLE_VEC readerHandle_;
	int iLastCardType;
	int beepReader_;
private:
	int registerDLL(HMODULE h,ks_device_op_t *op);
	int loadDLL(const char *path,ks_device_op_t *op);
	
	int doLoadReaderDLL(ks_cardlib_license *lic,const char *baseDir);
	int doInitCardType(ks_cardlib_license *lic,CardTypeManager * manager);
	int loadPara(ks_cardlib_license *lic);

	ks_reader_dev_t *getReaderParaByType(ks_cardtype_base::READER_TYPE t);
	int findReaderPortAndBaud(int no,int &port,int &baud);
	int doOpenPort(int no,int port,int baud);
public:
	CardReaderManager();
	~CardReaderManager();
	void freeAll();
	// 加载读卡器库
	int loadReaderDLL(ks_cardlib_license *lic,const char *baseDir);
	// 初始化
	int initAllCardType(ks_cardlib_license *lic,CardTypeManager *manager);
	// 读卡器接口
	ks_device_op_t *getReaderByType(ks_cardtype_base::READER_TYPE t);
	// 读卡器接口
	ks_device_op_t *getReaderByNo(size_t no);
	ks_device_op_t *getReaderByIdx(int idx);
	// 读卡器参数
	ks_reader_dev_t *getReaderParaByNo(int no);
	ks_reader_dev_t *getPSAMReaderPara();
	ks_reader_dev_t *getKeyCardReaderPara();
	//ks_reader_dev_t *getCardTypePara(ks_cardtype_base *c,ks_cardtype_base::READER_TYPE t);
	size_t getReaderCount() const { return readerHandle_.size(); }
	void setErrorMsg(const char *errmsg,const char *defaultmsg=NULL);
	const char* getErrorMsg(char *msg,const char* defaultmsg=NULL);
	void setReaderPortByNo(int no,int port,int baud);
	int openPort(int no,int port,int baud);
	void closePort();
	int beep();
	int beeperr();

};

#endif // _CARDTYPE_MANAGER_H_
