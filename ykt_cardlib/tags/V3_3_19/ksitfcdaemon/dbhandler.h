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
	/** \breif ������ǩ��
	 * \param device - ǩ���豸��Ϣ
	 * \param createnew - �Ƿ񴴽��¼�¼, 0 ��ʾ������ 1 ��ʾ����
	 */
	int Login(KsCardMsg &device,int createnew);
	/** \brief ��ȡδ�ϴ���ˮ
	* \param trans - ��ˮ��������
	* \return ���� 0 ��ʾ��ȡ�ɹ���-1��ʾ��ȡʧ�ܣ�1��ʾ�޼�¼
	*/
	int GetTransDtl(KsCardMsg &trans);
	/** \brief ȷ���ϴ�һ����ˮ
	* \param trans - ��ˮ��������
	* \return ���� 0 ��ʾȷ�ϳɹ���-1��ʾȷ��ʧ�ܣ�1��ʾ�޶�Ӧ��¼
	*/
	int ConfirmTransDtl(KsCardMsg &trans);
	/** \breif ������ˮ
	 * \return 0 ��ʾ�ɹ���-1 ��ʾʧ��, 1 ��ʾ��Ҫ������ˮ
	 */
	int CancelTransDtl(KsCardMsg &trans);
	/** \breif ��鱾��δ�ϴ�����ˮ
	 */
	int CheckTransDtl();
	/** \breif �ж��Ƿ���������
	 * \return ���� 0 ��ʾ����������ʾ������
	 */
	int CanDoTrans();
	/** \breif �������ݿ�
	 * \return ���� 0 ��ʾ����������ʾ������
	 */
	int BackupDatabase();
};

#define CARDSTATUS_NORMAL 0 // ����
#define CARDSTATUS_LOST   1 // ��ʧ
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
