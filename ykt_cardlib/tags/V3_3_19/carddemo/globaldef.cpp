/////////////////////////////////////////////////////////////////////////
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include "std.h"
#include "globaldef.h"
#include "kscard_imp.h"

LogMessage* LogMessage::instance_=NULL;
LogMessage* LogMessage::instance()
{
	if(instance_ == NULL)
	{
		instance_ = new LogMessage();
	}
	return instance_;
}
LogMessage::LogMessage():text_(NULL),svrport(0),svrmainfunc(0)
{
	//
	wxFileInputStream input(wxT("cpucard.ini"));
	wxFileConfig config(input);
	config.SetPath(wxT("/SERVER"));
	wxString value;
	config.Read(wxT("IP"),&value,wxT(""));
	strcpy(svrip,value.c_str());
	long lv;
	config.Read(wxT("PORT"),&lv,0);
	svrport = lv;
	config.Read(wxT("FUNC"),&lv,0);
	svrmainfunc = lv;
}
void LogMessage::SetLogView(wxTextCtrl *text)
{
	text_ = text;
}
void LogMessage::Log(const wxString &msg)
{
	(*text_)<<msg<<"\n";
}
void LogMessage::LogCardMsg(const wxString &msg /*= wxT("")*/)
{
	char cardmsg[512]={0};
	ks_geterrmsg(cardmsg);
	(*text_)<<msg<<" :"<<cardmsg<<"\n"; 
}