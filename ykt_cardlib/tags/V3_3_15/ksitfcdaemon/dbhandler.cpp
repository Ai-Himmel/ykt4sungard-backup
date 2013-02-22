///////////////////////////////////////////////////////////////////////////////
////
#include "std.h"
#include "kscardmsg.h"
#include "dbhandler.h"

///////////////////////////////////////////////////////////////////////////////
const wxString TransDB::db_file_name_=wxT("kstrans.db");

TransDB::TransDB():dbfile_(wxT("")),db_(NULL)
{
}
TransDB::~TransDB()
{
	freeDB();
}
int TransDB::Open(const char *basepath)
{
	dbfile_ = basepath;
	dbfile_ += wxT("/") + TransDB::db_file_name_;
	if(!wxFileExists(dbfile_))
		return -1;
	freeDB();
	db_ = new wxSQLite3Database();
	db_->Open(dbfile_);
	return 0;
}
void TransDB::freeDB()
{
	if(NULL != db_)
	{
		if(db_->IsOpen())
			db_->Close();
		delete db_;
		db_ = NULL;
	}
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
			  TAC VARCHAR(8),STATUS INTEGER, \
			  PRIMARY KEY (TERMID,TERMSEQNO,TRANSDATE) )");

	db_ = new wxSQLite3Database();
	db_->Open(dbfile_);

	db_->ExecuteUpdate(sql);

	sql = wxT("CREATE TABLE TRANSTERM (TERMID INTEGER NOT NULL, TERMSEQNO INTEGER, \
			  PRIMARY KEY (TERMID) )");

	db_->ExecuteUpdate(sql);
	return 0;
}
int TransDB::Login(int termid,int *termseqno)
{
	wxString sql;
	int seqno;
	sql = wxString::Format("SELECT TERMSEQNO FROM TRANSTERM WHERE TERMID=%d",termid);
	wxSQLite3ResultSet rt = db_->ExecuteQuery(sql);

	if(rt.NextRow())
	{
		seqno = rt.GetInt(0);
	}
	else
	{
		seqno = 1;
		sql = wxString::Format("INSERT INTO TRANSTERM(TERMID,TERMSEQNO) VALUES(%d,%d)",
			termid,seqno);
		if(db_->ExecuteUpdate(sql) != 1)
		{
			return -1;
		}
	}
	*termseqno = seqno;
	return 0;
}
int TransDB::Init4Purchase(KsCardMsg &trans)
{
	int termid,termseqno,cardbefbal,paycnt,cardno;
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
	if(!trans.GetStrPara("data.transdate",transdate))
		return -1;
	if(!trans.GetStrPara("data.transtime",transtime))
		return -1;
	if(!trans.GetStrPara("data.samno",samno))
		return -1;
	if(!trans.GetStrPara("data.cardphyid",cardphyid))
		return -1;
	wxString sql;
	sql = wxString::Format(wxT("INSERT INTO TRANSDTL(TERMID,TMERSEQNO,TRANSDATE,TRANSTIME,SAMNO,\
			  CARDBEFBAL,PAYCNT,CARDNO,CARDPHYID,STATUS) VALUES ( \
			  %d,%d,'%s','%s','%s',%d,%d,%d,'%s',1)"),
			  termid,termseqno,transdate.c_str(),transtime.c_str(),samno.c_str(),cardbefbal,
			  paycnt,cardno,cardphyid);
	int row = db_->ExecuteUpdate(sql);
	if(row <= 0)
		return -1;
	return 0;
}
int TransDB::Debit4Purchase(KsCardMsg &trans)
{
	int termid,termseqno,samseqno;
	std::string transdate,tac;


	if(!trans.GetIntPara("data.termid",&termid))
		return -1;
	if(!trans.GetIntPara("data.termseqno",&termseqno))
		return -1;
	if(!trans.GetIntPara("data.samseqno",&samseqno))
		return -1;
	if(!trans.GetStrPara("data.transdate",transdate))
		return -1;
	if(!trans.GetStrPara("data.tac",tac))
		return -1;

	db_->Begin();
	wxSQLite3Transaction t(db_);
	if(!t.IsActive())
		return -1;
	wxString sql;
	sql = wxString::Format(wxT("UPDATE TRANSDTL SET TAC='%s',STATUS=%d, \
		      SAMSEQNO=%d WHERE TERMID=%d AND TMERSEQNO=%d AND TRANSDATE='%s' "),
			  tac.c_str(),2,samseqno,termid,termseqno,transdate.c_str());
	int row = db_->ExecuteUpdate(sql);
	if(row <= 0)
	{
		t.Rollback();
		return -1;
	}
	sql = wxString::Format(wxT("UPDATE TRANSTERM SET TERMSEQNO=%d WHERE TERMID=%d"),
		termseqno+1,termid);
	row = db_->ExecuteUpdate(sql);
	if(row<=0)
	{
		t.Rollback();
		return -1;
	}
	t.Commit();
	return 0;
}
///////////////////////////////////////////////////////////////////////////////
InfoDB::InfoDB()
{
}
InfoDB::~InfoDB()
{
}
int InfoDB::Open(const char *basepath)
{
	return -1;
}