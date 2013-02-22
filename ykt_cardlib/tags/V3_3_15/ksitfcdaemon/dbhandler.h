#ifndef _DBHANDLER_H_
#define _DBHANDLER_H_

#include <wx/wxsqlite3.h>
///////////////////////////////////////////////////////////////////////////////
class TransDB
{
private:
	wxString dbfile_;
	wxSQLite3Database *db_;
	static const wxString db_file_name_;
	void freeDB();
public:
	TransDB();
	~TransDB();
	int Open(const char *basepath);
	int InitDB(const char *basepath);
	int Init4Purchase(KsCardMsg &trans);
	int Debit4Purchase(KsCardMsg &trans);
	int Login(int termid,int *termseqno);
};

class InfoDB
{
public:
	InfoDB();
	~InfoDB();
	int Open(const char *basepath);
};
#endif // _DBHANDLER_H_
