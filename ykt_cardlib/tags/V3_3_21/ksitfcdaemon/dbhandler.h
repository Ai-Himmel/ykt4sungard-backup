#ifndef _DBHANDLER_H_
#define _DBHANDLER_H_

#include <wx/wxsqlite3.h>
#include "globaldef.h"

///////////////////////////////////////////////////////////////////////////////
class DBUtil
{
protected:
	wxString dbfile_;
	wxSQLite3Database *db_;
	int sqlErrCode_;
	wxString sqlErrMsg_;
	void freeDB();
	virtual void GetDBFileName(wxString &dbfile) = 0;
	void LogSQLiteError(const wxSQLite3Exception &ex);
	KsCardDaemonCfg *global_cfg_;
	static const wxString dbKey_;
public:
	DBUtil();
	virtual ~DBUtil();
	virtual int Open(const char *basepath);
	virtual int IsOpen();
	virtual int InitDB(const char *basepath) = 0;
	wxString GetErrInfo();
	void SetConfig(KsCardDaemonCfg *cfg);
};

class TransDB : public DBUtil
{
private:
	static const wxString db_file_name_;
	enum {DTLUNUPLOAD = 0,DTLUPLOAD};
	TransDB();
	wxCriticalSection m_Chkcritsect;
	int doCheckDtl();
	int doBackupDtl();
	int doBackupDBAndNew();
protected:
	virtual void GetDBFileName(wxString &dbfile);
	friend class KsCardProcessor;
public:
	virtual ~TransDB();
	virtual int InitDB(const char *basepath);
	virtual int IsOpen();
	int Init4Purchase(KsCardMsg &trans);
	int Debit4Purchase(KsCardMsg &trans);
	/** \breif 读卡器签到
	 * \param device - 签到设备信息
	 * \param createnew - 是否创建新记录, 0 表示不创建 1 表示创建
	 */
	int Login(KsCardMsg &device,int createnew);
	/** \brief 获取未上传流水
	* \param trans - 流水数据类容
	* \return 返回 0 表示读取成功，-1表示读取失败，1表示无记录
	*/
	int GetTransDtl(KsCardMsg &trans);
	/** \brief 确认上传一笔流水
	* \param trans - 流水数据类容
	* \return 返回 0 表示确认成功，-1表示确认失败，1表示无对应记录
	*/
	int ConfirmTransDtl(KsCardMsg &trans);
	/** \breif 撤销流水
	 * \return 0 表示成功，-1 表示失败, 1 表示无要冲正流水
	 */
	int CancelTransDtl(KsCardMsg &trans);
	/** \breif 检查本地未上传的流水
	 */
	int CheckTransDtl();
	/** \breif 判断是否允许消费
	 * \return 返回 0 表示允许，其它表示不允许
	 */
	int CanDoTrans();
	/** \breif 备份数据库
	 * \return 返回 0 表示允许，其它表示不允许
	 */
	int BackupDatabase();
};

#define CARDSTATUS_NORMAL 0 // 正常
#define CARDSTATUS_LOST   1 // 挂失
class CardVerInfo;
class InfoDB : public DBUtil
{
private:
	InfoDB();
	static const wxString db_file_name_;
	friend class KsCardProcessor;
protected:
	virtual void GetDBFileName(wxString &dbfile);
public:
	virtual ~InfoDB();
	int InitDB(const char *basepath);
	int AddNewCard(const CardVerInfo& cardver);
	int IsBlackCard(CardVerInfo& cardver);
	int GetMaxCardVer(std::string &cardverno);

};
#endif // _DBHANDLER_H_
