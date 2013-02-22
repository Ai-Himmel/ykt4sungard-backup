///////////////////////////////////////////////////////////////////////////////
////
#include "std.h"
#include "kscardmsg.h"
#include "svrrequest.h"
#include "dbhandler.h"
#include "globaldef.h"

///////////////////////////////////////////////////////////////////////////////
const wxString DBUtil::dbKey_ = wxT("SUNGARDkardinterface");
DBUtil::DBUtil():db_(NULL),dbfile_(wxT("")),sqlErrCode_(0),global_cfg_(NULL)
{
}
DBUtil::~DBUtil()
{
	freeDB();
}
void DBUtil::freeDB()
{
	if(NULL != db_)
	{
		if(db_->IsOpen())
			db_->Close();
		delete db_;
		db_ = NULL;
	}
}
int DBUtil::Open(const char *basepath)
{
	wxString fn;
	GetDBFileName(fn);
	dbfile_ = basepath;
	dbfile_ += wxT("/") + fn;
	if(!wxFileExists(dbfile_))
		return -1;
	freeDB();
	db_ = new wxSQLite3Database();
	db_->Open(dbfile_,DBUtil::dbKey_);
	return 0;
}
int DBUtil::IsOpen()
{
	return ((db_ != NULL) && db_->IsOpen() == true) ? 0 : -1;
}
void DBUtil::LogSQLiteError(const wxSQLite3Exception &ex)
{
	this->sqlErrCode_ = ex.GetErrorCode();
	this->sqlErrMsg_ = ex.GetMessage();
}
wxString DBUtil::GetErrInfo()
{
	wxString info = wxString::Format("%d:",this->sqlErrCode_);
	info += this->sqlErrMsg_;
	return info;
}
void DBUtil::SetConfig(KsCardDaemonCfg *cfg)
{
	global_cfg_ = cfg;
}
///////////////////////////////////////////////////////////////////////////////
const wxString TransDB::db_file_name_=wxT("kstrans.db");

TransDB::TransDB():DBUtil()
{
}
TransDB::~TransDB()
{
}
void TransDB::GetDBFileName(wxString &dbfile)
{
	dbfile = TransDB::db_file_name_;
}
int TransDB::InitDB(const char *basepath)
{
	dbfile_ = basepath;
	dbfile_ += wxT("/") + TransDB::db_file_name_;
	if(wxFileExists(dbfile_))
	{
		if(!wxRemoveFile(dbfile_))
			return -1;
	}
	freeDB();
	wxString sql;
	sql = wxT("CREATE TABLE TRANSDTL(TERMID INTEGER NOT NULL,\
			  TERMSEQNO INTEGER NOT NULL,TRANSDATE VARCHAR(8) NOT NULL,\
			  TRANSTIME VARCHAR(6) NOT NULL, \
			  SAMNO VARCHAR(12), SAMSEQNO INTEGER, AMOUNT INTEGER, \
			  CARDBEFBAL INTEGER, PAYCNT INTEGER, CARDNO INTEGER, CARDPHYID VARCHAR(20), \
			  TAC VARCHAR(8),STATUS INTEGER,UPLOADFLAG INTEGER, TRANSCODE INTEGER, \
			  PRIMARY KEY (TERMID,TERMSEQNO,TRANSDATE) )");

	db_ = new wxSQLite3Database();
	db_->Open(dbfile_);

	db_->ExecuteUpdate(sql);

	sql = wxT("CREATE TABLE TRANSTERM (TERMID INTEGER NOT NULL, TERMSEQNO INTEGER, \
			  DEVPHYID VARCHAR(20),SHOPID INTEGER,SHOPNAME VARCHAR(60),PRIMARY KEY (TERMID) )");

	db_->ExecuteUpdate(sql);
	return 0;
}
int TransDB::IsOpen()
{
	wxCriticalSectionLocker locker(m_Chkcritsect);
	return DBUtil::IsOpen();
}
/** \breif 读卡器签到
 * \param device - 签到设备信息
 * \param createnew - 是否创建新记录, 0 表示不创建 1 表示创建
 */
int TransDB::Login(KsCardMsg &device,int createnew)
{
	if(IsOpen())
		return -1;
	int termid,shopid;
	std::string shopname,devphyid;

	if(!device.GetIntPara("data.termid",&termid))
		return -1;
	shopid=0;
	device.GetIntPara("data.shopid",&shopid);
	device.GetStrPara("data.shopname",shopname);
	device.GetStrPara("data.devphyid",devphyid);
	wxSQLite3Transaction t(db_);
	try
	{
		wxString sql;
		int seqno,dtlseqno;
		sql = wxString::Format("SELECT TERMSEQNO,SHOPID,SHOPNAME FROM TRANSTERM WHERE TERMID=%d",termid);
		wxSQLite3ResultSet rt = db_->ExecuteQuery(sql);

		if(rt.NextRow())
		{
			seqno = rt.GetInt(0);
			if(shopid == 0)
			{
				shopid = rt.GetInt(1);
				shopname = rt.GetAsString(2).mb_str();
				device.SetIntPara("data.shopid",shopid);
				device.SetStrPara("data.shopname",shopname);
			}
			sql = wxString::Format(wxT("SELECT MAX(TERMSEQNO) FROM TRANSDTL WHERE TERMID=%d"),termid);
			wxSQLite3ResultSet rt = db_->ExecuteQuery(sql);
			if(rt.NextRow())
			{
				if(rt.IsNull(0))
					dtlseqno = 0;
				else
					dtlseqno = rt.GetInt(0);
			}
			else
				dtlseqno = 0;

			seqno = (seqno > dtlseqno) ? (seqno):(dtlseqno);
			sql = wxString::Format("UPDATE TRANSTERM SET SHOPID=%d,SHOPNAME='%s',DEVPHYID='%s', \
								   TERMSEQNO=%d WHERE TERMID=%d",shopid,shopname.c_str(),devphyid.c_str(),
								   seqno,termid);

			if(db_->ExecuteUpdate(sql) != 1)
			{
				t.Rollback();
				return -1;
			}

		}
		else
		{
			if(createnew)
			{
				seqno = 0;
				sql = wxString::Format("INSERT INTO TRANSTERM(TERMID,TERMSEQNO,SHOPID,SHOPNAME,DEVPHYID)\
									   VALUES(%d,%d,%d,'%s','%s')",
					termid,seqno,shopid,shopname.c_str(),devphyid.c_str());
				if(db_->ExecuteUpdate(sql) != 1)
				{
					t.Rollback();
					return -1;
				}
			}
			else
			{
				return -1;
			}
		}
		device.SetIntPara("data.termseqno",seqno+1);
		global_cfg_->devphyid_ = devphyid;
		t.Commit();
		return 0;
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		t.Rollback();
		return -1;
	}
}
int TransDB::Init4Purchase(KsCardMsg &trans)
{
	if(IsOpen())
		return -1;
	int termid,termseqno,cardbefbal,paycnt,cardno,amount,status,transcode;
	std::string transdate,transtime,samno,cardphyid;

	if(!trans.GetIntPara("data.termid",&termid))
	{
		return -1;
	}
	if(!trans.GetIntPara("data.termseqno",&termseqno))
		return -1;
	if(!trans.GetIntPara("data.befbala",&cardbefbal))
		return -1;
	if(!trans.GetIntPara("data.paycnt",&paycnt))
		return -1;
	if(!trans.GetIntPara("data.cardno",&cardno))
		return -1;
	if(!trans.GetStrPara("data.termdate",transdate))
		return -1;
	if(!trans.GetStrPara("data.termtime",transtime))
		return -1;
	if(!trans.GetStrPara("data.samno",samno))
		return -1;
	if(!trans.GetStrPara("data.cardphyid",cardphyid))
		return -1;
	if(!trans.GetIntPara("data.amount",&amount))
		return -1;
	if(!trans.GetIntPara("data.status",&status))
		return -1;
	if(!trans.GetIntPara("data.transcode",&transcode))
		return -1;
	try
	{
		wxString sql;
		sql = wxString::Format(wxT("INSERT INTO TRANSDTL(TERMID,TERMSEQNO,TRANSDATE,TRANSTIME,SAMNO,\
				  CARDBEFBAL,PAYCNT,CARDNO,CARDPHYID,AMOUNT,STATUS,UPLOADFLAG,TRANSCODE) VALUES ( \
				  %d,%d,'%s','%s','%s',%d,%d,%d,'%s',%d,%d,%d,%d)"),
				  termid,termseqno,transdate.c_str(),transtime.c_str(),samno.c_str(),cardbefbal,
				  paycnt,cardno,cardphyid.c_str(),amount,status,DTLUNUPLOAD,transcode);
		int row = db_->ExecuteUpdate(sql);
		if(row <= 0)
			return -1;
		return 0;
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
int TransDB::Debit4Purchase(KsCardMsg &trans)
{
	if(IsOpen())
		return -1;
	int termid,termseqno,samseqno,status;
	std::string transdate,tac;


	if(!trans.GetIntPara("data.termid",&termid))
		return -1;
	if(!trans.GetIntPara("data.termseqno",&termseqno))
		return -1;
	if(!trans.GetIntPara("data.samseqno",&samseqno))
		return -1;
	if(!trans.GetStrPara("data.termdate",transdate))
		return -1;
	if(!trans.GetStrPara("data.tac",tac))
		return -1;
	if(!trans.GetIntPara("data.status",&status))
		return -1;
	try
	{
		wxSQLite3Transaction t(db_);
		//db_->Begin();
		//if(!t.IsActive())
		//	return -1;
		wxString sql;
		sql = wxString::Format(wxT("UPDATE TRANSDTL SET TAC='%s',STATUS=%d, \
				  SAMSEQNO=%d WHERE TERMID=%d AND TERMSEQNO=%d AND TRANSDATE='%s' "),
				  tac.c_str(),status,samseqno,termid,termseqno,transdate.c_str());
		int row = db_->ExecuteUpdate(sql);
		if(row <= 0)
		{
			t.Rollback();
			return -1;
		}
		sql = wxString::Format(wxT("UPDATE TRANSTERM SET TERMSEQNO=%d WHERE TERMID=%d"),
			termseqno,termid);
		row = db_->ExecuteUpdate(sql);
		if(row<=0)
		{
			t.Rollback();
			return -1;
		}
		t.Commit();
		return 0;
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
int TransDB::GetTransDtl(KsCardMsg &trans)
{
	if(IsOpen())
		return -1;
	int termid,termseqno,cardbefbal,paycnt,cardno,amount,status,samseqno,transcode;
	std::string transdate,transtime,samno,cardphyid,tac;
	try
	{
		wxString sql = wxString::Format(wxT("SELECT TERMID,TERMSEQNO,TRANSDATE,TRANSTIME,CARDNO,\
						   CARDPHYID,PAYCNT,CARDBEFBAL,AMOUNT,TAC,STATUS,SAMNO,\
						   SAMSEQNO,TRANSCODE FROM TRANSDTL WHERE UPLOADFLAG=%d AND STATUS<>%d \
						   ORDER BY TRANSDATE,TRANSTIME LIMIT 1"),
						   DTLUNUPLOAD,DTLST_INIT);
		wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
		if(set.NextRow())
		{
			termid = set.GetInt("TERMID");
			termseqno = set.GetInt("TERMSEQNO");
			transdate = set.GetAsString("TRANSDATE").mb_str();
			transtime = set.GetAsString("TRANSTIME").mb_str();
			cardno = set.GetInt("CARDNO");
			cardphyid = set.GetAsString("CARDPHYID").mb_str();
			paycnt = set.GetInt("PAYCNT");
			cardbefbal = set.GetInt("CARDBEFBAL");
			amount = set.GetInt("AMOUNT");
			tac = set.GetAsString("TAC").mb_str();
			status = set.GetInt("STATUS");
			samno = set.GetAsString("SAMNO").mb_str();
			samseqno = set.GetInt("SAMSEQNO");
			transcode = set.GetInt("TRANSCODE");
			
			trans.SetIntPara("data.termid",termid);
			trans.SetIntPara("data.termseqno",termseqno);
			trans.SetStrPara("data.termdate",transdate);
			trans.SetStrPara("data.termtime",transtime);
			trans.SetIntPara("data.cardno",cardno);
			trans.SetStrPara("data.cardphyid",cardphyid);
			trans.SetIntPara("data.paycnt",paycnt);
			trans.SetIntPara("data.befbala",cardbefbal);
			trans.SetIntPara("data.amount",amount);
			trans.SetStrPara("data.tac",tac);
			trans.SetIntPara("data.status",status);
			trans.SetStrPara("data.samno",samno);
			trans.SetIntPara("data.samseqno",samseqno);
			trans.SetStrPara("data.devphyid",samno);
			trans.SetIntPara("data.transcode",transcode);
			return 0;
		}
		else
		{
			// 无记录
			return 1;
		}

	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
int TransDB::ConfirmTransDtl(KsCardMsg &trans)
{
	if(IsOpen())
		return -1;
	int termid,termseqno;
	std::string transdate;

	try
	{
		if(!trans.GetIntPara("data.termid",&termid))
			return -1;
		if(!trans.GetIntPara("data.termseqno",&termseqno))
			return -1;
		if(!trans.GetStrPara("data.termdate",transdate))
			return -1;
		wxString sql = wxString::Format(wxT("UPDATE TRANSDTL SET UPLOADFLAG=%d WHERE \
						   TERMID=%d AND TERMSEQNO=%d AND TRANSDATE='%s' "),
						   DTLUPLOAD,termid,termseqno,transdate.c_str());

		int row = db_->ExecuteUpdate(sql);
		
		if(row == 1)
		{
			return 0;
		}
		else
		{
			// 无记录
			return 1;
		}

	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
/** \breif 撤销流水
 * \return 0 表示成功，-1 表示失败, 1 表示无要冲正流水
 */
int TransDB::CancelTransDtl(KsCardMsg &trans)
{
	if(IsOpen())
		return -1;
	int termid,termseqno,canceltermseqno,amount,status,paycnt,retcode;
	std::string termdate,canceltermdate,termtime;
	try
	{
		wxSQLite3Transaction t(db_);

		if(!trans.GetIntPara("data.termid",&termid))
			return -1;
		if(!trans.GetIntPara("data.termseqno",&termseqno))
			return -1;
		if(!trans.GetStrPara("data.termdate",termdate))
			return -1;
		if(!trans.GetStrPara("data.termtime",termtime))
			return -1;
		if(!trans.GetIntPara("data.canceltermseqno",&canceltermseqno))
			return -1;
		if(!trans.GetStrPara("data.canceltermdate",canceltermdate))
			return -1;

		wxString sql;
		sql = wxString::Format(wxT("SELECT AMOUNT,PAYCNT,STATUS FROM TRANSDTL WHERE \
								   TRANSDATE='%s' AND TERMID=%d AND TERMSEQNO=%d "),
								   canceltermdate.c_str(),termid,canceltermseqno);
		int row = 0;
		wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
		if(set.NextRow())
		{
			amount = set.GetInt(0);
			paycnt = set.GetInt(1);
			status = set.GetInt(2);

			if(status == DTLST_CANCEL)
			{
				retcode = EKS_ALREADYCANCEL;
			}
			else if(status == DTLST_SUCCESS)
			{
				retcode = 0;
				sql = wxString::Format(wxT("UPDATE TRANSDTL SET STATUS=%d WHERE \
										   TRANSDATE='%s' AND TERMID=%d AND TERMSEQNO=%d"),
										   DTLST_CANCEL,canceltermdate.c_str(),termid,canceltermseqno);
				row = db_->ExecuteUpdate(sql);
				if(row != 1)
				{
					t.Rollback();
					retcode = EKS_DATABASE;
				}
				else
				{
					// 写入冲正流水
					KsCardMsg newtrans = trans;
					newtrans.SetIntPara("data.amount",-amount);
					newtrans.SetIntPara("data.paycnt",paycnt);
					newtrans.SetIntPara("data.status",DTLST_INIT);
					retcode = Init4Purchase(newtrans);
					if(retcode)
					{
						t.Rollback();
						return -1;
					}
					sql = wxString::Format(wxT("UPDATE TRANSTERM SET TERMSEQNO=%d WHERE TERMID=%d"),
						termseqno,termid);
					row = db_->ExecuteUpdate(sql);
					if(row!=1)
					{
						t.Rollback();
						return -1;
					}
					t.Commit();
					trans.SetIntPara("data.amount",amount);
				}
			}
			else
			{
				retcode = EKS_CANCELDTLERROR;
			}
			trans.SetIntPara("data.retcode",retcode);
			return 0;
		}
		else
		{
			// 无要冲正的记录
			return 1;
		}
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
int TransDB::doCheckDtl()
{
	if(IsOpen())
		return -1;
	wxString transdate,transtime;
	try
	{
		wxDateTime now = wxDateTime::Now();
		wxTimeSpan span(0,10,0,0);
		now -= span;

		transdate = now.Format("%Y%m%d");
		transtime = now.Format("%H%M%S");
		int row1;
		// 更新未确认的消费流水为中途拔卡
		wxString sql = wxString::Format(wxT("UPDATE TRANSDTL SET STATUS=%d WHERE \
											STATUS=%d AND TRANSDATE<='%s' AND TRANSTIME <='%s' AND TRANSCODE=%d"),
											DTLST_UNCONFIRM,DTLST_INIT,transdate.c_str(),transtime.c_str(),
											TC_PURCHASE);


		row1 = db_->ExecuteUpdate(sql);

		sql = wxString::Format(wxT("UPDATE TRANSDTL SET STATUS=%d WHERE \
									STATUS=%d AND TRANSDATE<='%s' AND TRANSTIME <='%s' AND TRANSCODE=%d"),
									DTLST_SUCCESS,DTLST_INIT,transdate.c_str(),transtime.c_str(),
									TC_CANCELPURCHASE);
		int row2 = db_->ExecuteUpdate(sql);

		if(row1 == 0 && row2 == 0)
			return 1;
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
	return 0;
}
int TransDB::doBackupDBAndNew()
{
	if(!DBUtil::IsOpen())
	{
		wxString datestr = wxDateTime::Now().Format("%Y%m%d%H%M%S");
		wxString target = dbfile_ + datestr;
		if(wxFileExists(target))
		{
			return -1;
		}
		db_->Backup(target,DBUtil::dbKey_);
		try
		{
			wxString sql = wxString::Format(wxT("DELETE FROM TRANSDTL WHERE UPLOADFLAG=%d"),DTLUPLOAD);
			db_->ExecuteUpdate(sql);
			return 0;
		}
		catch(wxSQLite3Exception  &ex)
		{
			LogSQLiteError(ex);
			wxLogError(GetErrInfo());
			return -1;
		}
		return 0;
	}
	return -1;
}
int TransDB::doBackupDtl()
{
	wxCriticalSectionLocker locker(m_Chkcritsect);
	try
	{
		wxString sql;
		sql = wxString::Format(wxT("SELECT COUNT(*) FROM TRANSDTL WHERE UPLOADFLAG=%d"),
			DTLUNUPLOAD);
		wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
		if(set.NextRow())
		{
			int cnt = set.GetInt(0);
			if(cnt > 0)
			{
				// 不需要备份
				return 0;
			}
			// 备份数据库
			sql = wxT("SELECT COUNT(*) FROM TRANSDTL");
			wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
			if(set.NextRow())
			{
				cnt = set.GetInt(0);
				if(cnt > global_cfg_->maxBackupDtlCount_ && global_cfg_->maxBackupDtlCount_ > 0)
				{
					return doBackupDBAndNew();
				}
			}
		}
		// 不需要备份
		return 0;
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
int TransDB::CanDoTrans()
{
	try
	{

		wxString sql;
		
		if(global_cfg_->maxOfflineDtlCount_ > 0)
		{
			sql = wxString::Format(wxT("SELECT COUNT(*) FROM TRANSDTL WHERE UPLOADFLAG=%d"),
				DTLUNUPLOAD);
			wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
			if(set.NextRow())
			{
				int cnt = set.GetInt(0);
				if(cnt >= global_cfg_->maxOfflineDtlCount_)
					return -1;
			}
			return 0;
		}
		
		if(global_cfg_->maxOfflineDtlDay_ > 0)
		{
			wxDateTime now = wxDateTime::Now();
			wxDateSpan span(0,0,global_cfg_->maxOfflineDtlDay_);
			now -= span;

			wxString datestr = now.Format("%Y%m%d");
			sql = wxString::Format(wxT("SELECT COUNT(*) FROM TRANSDTL WHERE UPLOADFLAG=%d AND TRANSDATE<='%s' "),
				DTLUNUPLOAD,datestr.mb_str());
			wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
			if(set.NextRow())
			{
				int cnt = set.GetInt(0);
				if(cnt > 0)
					return -1;
			}
			return 0;
		}
		return 0;
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
/** \breif 检查本地未上传的流水
 */
int TransDB::CheckTransDtl()
{
	int ret;
	ret = doCheckDtl();
	if(ret == 1)
	{
		return 0;//doBackupDtl();
	}
	return ret;
}
int TransDB::BackupDatabase()
{
	return doBackupDtl();
}
///////////////////////////////////////////////////////////////////////////////
const wxString InfoDB::db_file_name_=wxT("ksinfo.db");
InfoDB::InfoDB():DBUtil()
{
}
InfoDB::~InfoDB()
{
}
void InfoDB::GetDBFileName(wxString &dbfile)
{
	dbfile = InfoDB::db_file_name_;
}
int InfoDB::InitDB(const char *basepath)
{
	dbfile_ = basepath;
	dbfile_ += wxT("/") + InfoDB::db_file_name_;
	if(wxFileExists(dbfile_))
	{
		if(!wxRemoveFile(dbfile_))
			return -1;
	}
	freeDB();
	wxString sql;
	sql = wxT("CREATE TABLE BLACKCARD(CARDNO INTEGER,CARDPHYID VARCHAR(20),FLAG INTEGER,\
			  CARDVERNO VARCHAR(14), PRIMARY KEY(CARDNO) )");

	db_ = new wxSQLite3Database();
	db_->Open(dbfile_);

	db_->ExecuteUpdate(sql);

	sql = wxT("CREATE UNIQUE INDEX IDX_CARDVERNO ON BLACKCARD(CARDVERNO ASC) ");

	db_->ExecuteUpdate(sql);

	sql = wxT("CREATE INDEX IDX_CARDPHYID ON BLACKCARD(CARDPHYID ASC) ");
	db_->ExecuteUpdate(sql);

	return 0;
}
int InfoDB::GetMaxCardVer(std::string &cardverno)
{
	if(IsOpen())
		return -1;

	try
	{
		wxString sql = wxT("SELECT MAX(CARDVERNO) FROM BLACKCARD");

		wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
		if(set.NextRow())
		{
			if(set.IsNull(0))
			{
				cardverno = "000000000000";
			}
			else
			{
				cardverno = set.GetAsString(0).c_str();
			}
			return 0;
		}
		else
		{
			cardverno="";
			return -1;
		}
	}
	catch(wxSQLite3Exception  &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
}
int InfoDB::AddNewCard(const CardVerInfo& cardver)
{
	if(IsOpen())
		return -1;
	try
	{
		db_->Begin();
		wxString sql;
		
		sql = wxString::Format(wxT("DELETE FROM BLACKCARD WHERE CARDNO=%d "),
												cardver.cardno_);
		db_->ExecuteUpdate(sql);
		if(cardver.flag_ != CARDSTATUS_NORMAL)
		{
			wxString sql = wxString::Format(wxT("INSERT INTO BLACKCARD(CARDNO,CARDPHYID,FLAG,\
												CARDVERNO)VALUES(%d,'%s',%d,'%s') "),
												cardver.cardno_,cardver.cardphyid_.c_str(),
												cardver.flag_,cardver.cardverno_.c_str());
			int row = db_->ExecuteUpdate(sql);
			if(row==1)
			{
				db_->Commit();
				return 0;
			}
			else
			{
				db_->Rollback();
				return -1;
			}
		}
		db_->Commit();
		return 0;
	}
	catch(wxSQLite3Exception &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		db_->Rollback();
		return -1;
	}
}
int InfoDB::IsBlackCard(CardVerInfo& cardver)
{
	if(IsOpen())
		return -1;
	try
	{
		wxString sql = wxString::Format(wxT("SELECT FLAG,CARDVERNO FROM BLACKCARD WHERE CARDNO=%d"),
			cardver.cardno_);

		wxSQLite3ResultSet set = db_->ExecuteQuery(sql);
		if(set.NextRow())
		{
			wxString cardverno,inputcardver;
			
			cardver.flag_ = set.GetInt(0);
			
			cardverno = set.GetAsString(1);
			if(cardverno.Length() == 12)
			{
				cardverno = "20" + cardverno;
			}
			inputcardver = cardver.cardverno_.c_str();

			if(cardver.flag_ != CARDSTATUS_NORMAL 
				&& cardverno >= inputcardver)
			{
				// 黑卡
				cardver.flag_ = CARDSTATUS_LOST;
				return 0;
			}
			else
			{
				cardver.flag_ = CARDSTATUS_NORMAL;
			}
		}
		else
		{
			cardver.flag_ = CARDSTATUS_NORMAL;
			return 0;
		}

	}
	catch(wxSQLite3Exception &ex)
	{
		LogSQLiteError(ex);
		wxLogError(GetErrInfo());
		return -1;
	}
	return 0;
}