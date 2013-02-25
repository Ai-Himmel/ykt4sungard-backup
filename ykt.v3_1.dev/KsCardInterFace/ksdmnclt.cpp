///////////////////////////////////////////////////////////////////////////////
///
#ifdef USEWXLIB
#include "std.h"
#endif
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "kscard_imp.h"
#include "json/json.h"
#include "kscardmsg.h"
#include "ksdmnclt.h"
#ifdef USEWXLIB
#include <wx/snglinst.h>
#include "kscardmsg.h"
#endif

extern ST_TRANSPACK staticPayment;
extern ST_TRANSPACK staticRechange;
extern char g_sCardVerNo[20];

#ifdef USEWXLIB
const wxString KsDaemonClient::daemon_app_id = wxT("ksitfcdaemonapp");
#ifdef WIN32
const std::string KsDaemonClient::daemon_app_name = "ksitfcdaemon.exe";
#else
const std::string KsDaemonClient::daemon_app_name = "ksitfcdaemon";
#endif
#endif

const std::string KsDaemonClient::msg_error_file = "faildmsg.txt";

KsDaemonClient::KsDaemonClient(int port):svrport(port),termseqno(0),hasLogin(0),termid(0) {
}
KsDaemonClient::~KsDaemonClient() {
}
/** \breif ǩ��
 * \return ���� 0 ��ʾǩ���ɹ���-1 ��ʾ����daemon���̴���-2 ��ʾǩ��ʧ��
 */
int KsDaemonClient::Login(int force) {
#ifdef USEWXLIB
    if(force == 0 && hasLogin == 1) {
        return IsSvrOk();
    }
    int ret;
    ret = Connect2Daemon();
    if(ret) {
        if(ForceStartDaemon()) {
            return -1;
        }
        ret = Connect2Daemon();
        if(ret) {
            return -1;
        }
    }
    // send login request
    KsCardMsg req,resp;
    req.SetIntPara("data.termid",termid);
    req.SetStrPara("data.samno",samno);
    req.SetMsgType("login");

    ret = SendRequest(req,resp,0);
    if(ret)
        return -2;
    resp.GetIntPara("data.retcode",&(this->retcode));
    resp.GetStrPara("data.retmsg",this->retmsg);
    if(!resp.GetStrPara("authcode",authcode))
        return -2;
    if(!resp.GetIntPara("data.termseqno",&termseqno))
        return -2;

    resp.GetIntPara("data.shopid",&(this->shopid));
    resp.GetStrPara("data.shopname",this->shopname);
    hasLogin = 1;
    return 0;

#else
    return -1;
#endif

}
int KsDaemonClient::SaveMsgToFile(KsCardMsg &req,const std::string filename) {
#ifdef USEWXLIB
    wxString fullname = wxGetCwd() + "/";
    fullname += filename;
    std::ofstream msgfile(fullname.mb_str(),std::ios_base::trunc);
    if(msgfile.bad())
        return -1;
    try {
        msgfile<<req.ToMsg();
    } catch(...) {
        return -1;
    }
    return 0;
#else
    return -1;
#endif
}
int KsDaemonClient::IsCanProcess() {
#ifdef USEWXLIB
    wxString fullname = wxGetCwd() + "/";
    fullname += KsDaemonClient::msg_error_file;

    if(!wxFileExists(fullname))
        return 0;
    KsCardMsg resp;
    return ResendMsgFile(KsDaemonClient::msg_error_file,resp);
#else
    return -1;
#endif
}
int KsDaemonClient::ResendMsgFile(const std::string filename,KsCardMsg &resp) {
#ifdef USEWXLIB
    KsCardMsg req;
    wxString fullname = wxGetCwd() + "/";
    fullname += filename;

    char line[1024];
    std::string msgstring;

    std::ifstream ifs( fullname.mb_str() , std::ifstream::in );
    while(!ifs.eof()) {
        ifs.getline(line,sizeof(line));
        msgstring += line;
    }
    ifs.close();
    req.ParseMsg(msgstring);
    int ret;
    if(!sock.IsConnected()) {
        if(Connect2Daemon())
            return -1;
    }
    int seqno = 0;
    req.GetIntPara("data.termseqno",&seqno);
    if(seqno > this->termseqno) {
        this->termseqno = seqno+1;
    } else if(seqno == this->termseqno) {
        this->termseqno++;
    } else {
        //
    }
    req.SetStrPara("authcode",this->authcode,1);
    ret = SendRequest(req,resp,0);
    if(ret)
        return ret;
    // ���ͳɹ�
    wxRemoveFile(fullname);
    return 0;
#else
    return -1;
#endif
}

int KsDaemonClient::SendRequest(KsCardMsg &req,KsCardMsg &resp,int logfaild /*= 1*/) {
#ifdef USEWXLIB
    if(!sock.IsConnected())
        return -1;
    std::stringstream content;
    std::string buf = req.ToMsg();
    content<<std::setfill('0')<< std::setw(5)<<buf.length()<<buf;
    buf = content.str();
    if(sock.WaitForWrite(0,300)) {
        sock.Write(buf.c_str(),buf.length());
        KsCardMsgRecv recv;
        recv.Reset();
        recv.SetClient(&sock);
        for(;;) {
            if(sock.WaitForRead(5,0)) {
                int ret = recv.RecvData(resp);
                if(ret==0)
                    return 0;
                else if(ret == 1)
                    continue;
                else {
                    sock.Close();
                    wxString msg = wxString::Format("RecvData error,ret=%d",ret);
                    wxLogError(msg);
                    if(logfaild)
                        SaveMsgToFile(req,KsDaemonClient::msg_error_file);
                    this->retcode = 99;
                    this->retmsg = "�����ŷ�����ʧ��";
                    return -1;
                }
            } else {
                sock.Close();
                if(logfaild)
                    SaveMsgToFile(req,KsDaemonClient::msg_error_file);
                this->retcode = 99;
                this->retmsg = "�����ŷ�����ʧ��";
                return -1;
            }
        }
    }
    this->retcode = 99;
    this->retmsg = "�����ŷ�����ʧ��";
    return -1;
#else
    return -1;
#endif
}
int KsDaemonClient::ForceStartDaemon() {
#ifdef USEWXLIB
    wxSingleInstanceChecker* ck = new wxSingleInstanceChecker(KsDaemonClient::daemon_app_id);
    if(ck->IsAnotherRunning()) {
        delete ck;
        return 0;
    }
    delete ck;
    wxString appname = wxGetCwd() + "/";
    appname += KsDaemonClient::daemon_app_name;
    long pid = wxExecute(appname);
    if(pid<=0)
        return -1;
    wxThread::Sleep(3000);
    return 0;
#else
    return 0;
#endif
}
int KsDaemonClient::Connect2Daemon() {
#ifdef USEWXLIB
    wxIPV4address addr;
    addr.LocalHost();
    addr.Service(svrport);
    if(sock.IsOk()) {
        sock.Close();
    }
    sock.Connect(addr,false);
    try {
        if(!sock.WaitOnConnect(10)) {
            wxLogError(wxT("���ӷ�����ʧ�ܣ�"));
            return -1;
        }
        if(!sock.IsConnected()) {
            wxLogError(wxT("���ӷ�����ʧ�ܣ�"));
            sock.Close();
            return -1;
        } else {
            wxLogMessage(wxT("���ӷ������ɹ�"));
            return 0;
        }
    } catch(std::exception) {
        return -1;
    }
#else
    return -1;
#endif
}
/** \breif ���ѳ�ʼ��
 * \param trans - ���Ѳ���
 * \return ���� 0 ��ʾ�ɹ���-1 ��ʾʧ��
 */
int KsDaemonClient::PreparePay(ST_TRANSPACK &trans,const std::string& cardverno) {
#ifdef USEWXLIB
    if(IsSvrOk() || IsLogin() || IsCanProcess())
        return -1;
    KsCardMsg req,resp;
    int ret,termid,termseqno;
    std::string cardstatus;

    wxDateTime now = wxDateTime::Now();

    wxString termdate = now.Format("%Y%m%d");
    wxString termtime = now.Format("%H%M%S");

    strncpy(trans.sTransDate,termdate.c_str(),8);
    strncpy(trans.sTransTime,termtime.c_str(),6);

    req.SetMsgType("init4purchase");
    req.SetStrPara("authcode",authcode);
    req.SetIntPara("data.termid",this->termid);
    req.SetIntPara("data.termseqno",this->termseqno);
    sprintf(trans.sRefNo,"%s%06d",trans.sTransDate,this->termseqno);
    req.SetIntPara("data.cardno",trans.nCardNo);
    req.SetStrPara("data.cardverno",cardverno);
    req.SetIntPara("data.amount",trans.nTransAmt);
    req.SetIntPara("data.befbala",trans.nBefBalance);
    req.SetIntPara("data.paycnt",trans.nPayCardCnt);
    req.SetStrPara("data.samno",this->samno);
    req.SetStrPara("data.termdate",trans.sTransDate);
    req.SetStrPara("data.termtime",trans.sTransTime);
    req.SetStrPara("data.cardphyid",trans.sCardPhyID);

    this->termseqno++;
    ret = SendRequest(req,resp);
    if(ret)
        return -1;
    resp.GetIntPara("data.retcode",&(this->retcode));
    resp.GetStrPara("data.retmsg",this->retmsg);

    if(!resp.GetIntPara("data.termid",&termid))
        return -1;
    if(!resp.GetIntPara("data.termseqno",&termseqno))
        return -1;
    if(!resp.GetStrPara("data.cardstatus",cardstatus))
        return -1;

    if(this->retcode != 0) {

        if(EKS_CARDLOST == retcode || cardstatus != "N")
            return -3;
        return -2;

    }
    if(termid != this->termid || termseqno != this->termseqno-1)
        return -2;
    return 0;
#else
    return -1;
#endif
}
/** \breif ����ȷ��
 * \param trans - ���Ѳ���
 * \param writeflag - д��״̬ 1 ��ʾд���ɹ���2 ��ʾ��;�ο���5 ��ʾд��ʧ��
 * \return ���� 0 ��ʾ�ɹ���-1 ��ʾʧ��
 */
int KsDaemonClient::ConfirmPay(ST_TRANSPACK &trans,int writeflag) {
#ifdef USEWXLIB
    if(IsSvrOk() || IsLogin() || IsCanProcess())
        return -1;
    KsCardMsg req,resp;
    int termid,termseqno;

    req.SetMsgType("debit4purchase");
    req.SetStrPara("authcode",this->authcode);
    req.SetIntPara("data.termid",this->termid);
    req.SetIntPara("data.termseqno",this->termseqno-1);
    req.SetStrPara("data.termdate",trans.sTransDate);
    req.SetStrPara("data.tac",trans.sMac);
    req.SetIntPara("data.samseqno",trans.nTermSeqno);
    req.SetIntPara("data.status",writeflag);

    if(SendRequest(req,resp))
        return -2;

    if(!resp.GetIntPara("data.termid",&termid))
        return -2;
    if(!resp.GetIntPara("data.termseqno",&termseqno))
        return -2;
    if(!resp.GetIntPara("data.retcode",&(this->retcode)))
        return -2;

    if(this->retcode != 0) {
        resp.GetStrPara("data.retmsg",this->retmsg);
        return -3;

    }
    if(termid != this->termid || termseqno != this->termseqno-1)
        return -2;
    return 0;
#else
    int nRet = ks_pay(&trans);
    if(nRet) {
        if(trans.cRetryFlag) {
            nRet = ks_pay(&trans);
            if(nRet) {
                /* modify by tc 2010-11-09
                if(staticPayment.cRetryFlag)
                {
                	//ȡ���ۿ�,�ѿ����ӻ�ȥ
                	int AftBalance=staticPayment.nAftBalance;
                	staticPayment.nAftBalance = staticPayment.nBefBalance;
                	staticPayment.nBefBalance = AftBalance;
                	char cProveFlag=0;
                	KS_CardBalanceInc(&cProveFlag);
                }
                */
                return nRet;
            }
        } else {
            /* modify by tc 2010-11-09
            //ȡ���ۿ�,�ѿ����ӻ�ȥ
            int AftBalance=staticPayment.nAftBalance;
            staticPayment.nAftBalance = staticPayment.nBefBalance;
            staticPayment.nBefBalance = AftBalance;
            char cProveFlag=0;
            KS_CardBalanceInc(&cProveFlag);
            */
            return nRet;
        }
    }
    return 0;
#endif
}
/** \breif �жϷ���״̬
 * \return ���� 0 ��ʾ����������-1 ��ʾ����δ����
 */
int KsDaemonClient::IsSvrOk() {
#ifdef USEWXLIB
    if(sock.IsConnected())
        return 0;
    KsCardMsg req,resp;

    req.SetMsgType("heartbeat");
    req.SetStrPara("authcode",this->authcode);

    if(!sock.IsConnected()) {
        if(this->Connect2Daemon())
            return -1;
    }
    int ret;
    int retcode;
    ret = SendRequest(req,resp);
    if(ret == 0) {
        if(resp.GetIntPara("data.retcode",&retcode)) {
            if(retcode == 0) {
                return 0;
            }
        }
    }
    this->retmsg = "�޷������ŷ�����";
    this->retcode= 99;
    sock.Close();
    hasLogin = 0;
    return -1;
#else
    return 0;
#endif
}
int KsDaemonClient::IsLogin() {
    if(hasLogin == 0) {
        this->retmsg = "δǩ��";
        this->retcode= 99;
        return -1;
    }
    return 0;
}
/** \breif ��鿨״̬
 * \param cardno - ����
 * \param statuscode - ��״̬��
 * \param statusinfo - ��״̬��Ϣ
 */
int KsDaemonClient::GetCardStatus(int cardno,const std::string &cardverno,char *statuscode,char *statusinfo) {
#ifdef USEWXLIB
    if(IsSvrOk() || IsLogin() || IsCanProcess())
        return -1;
    KsCardMsg req,resp;
    std::string cardstatus;

    req.SetMsgType("chkcard");
    req.SetStrPara("authcode",this->authcode);
    req.SetIntPara("data.cardno",cardno);
    req.SetStrPara("data.cardphyid","");
    req.SetStrPara("data.cardverno",cardverno);

    if(SendRequest(req,resp))
        return -1;

    resp.GetIntPara("data.retcode",&(this->retcode));
    resp.GetStrPara("data.retmsg",this->retmsg);
    if(!resp.GetStrPara("data.cardstatus",cardstatus))
        return -1;
    if(cardstatus == "0")
        strcpy(statusinfo,"������");
    else
        strcpy(statusinfo,"����ʧ");
    *statuscode = cardstatus.at(0);
    return 0;
#else
    return ks_getcardstatus(cardno,statuscode,statusinfo);
#endif
}

int KsDaemonClient::CancelPay(ST_TRANSPACK &trans,const std::string &cardverno) {
#ifdef USEWXLIB
    if(IsSvrOk() || IsLogin() || IsCanProcess())
        return -1;
    KsCardMsg req,resp;
    int ret,termid,termseqno,canceltermseqno,amount;
    std::string canceltermdate;

    wxDateTime now = wxDateTime::Now();

    wxString termdate = now.Format("%Y%m%d");
    wxString termtime = now.Format("%H%M%S");

    strncpy(trans.sTransDate,termdate.c_str(),8);
    strncpy(trans.sTransTime,termtime.c_str(),6);

    req.SetMsgType("cancel4purchase");
    req.SetStrPara("authcode",authcode);
    req.SetIntPara("data.termid",this->termid);
    req.SetIntPara("data.termseqno",this->termseqno);
    req.SetIntPara("data.cardno",trans.nCardNo);
    req.SetStrPara("data.cardverno",cardverno);
    req.SetIntPara("data.befbala",trans.nBefBalance);
    req.SetIntPara("data.dpscnt",trans.nDpsCardCnt);
    req.SetStrPara("data.samno",this->samno);
    req.SetStrPara("data.termdate",trans.sTransDate);
    req.SetStrPara("data.termtime",trans.sTransTime);
    req.SetStrPara("data.cardphyid",trans.sCardPhyID);

    canceltermdate = std::string(trans.sRefNo,0,8);
    canceltermseqno = atoi(trans.sRefNo+8);

    req.SetIntPara("data.canceltermseqno",canceltermseqno);
    req.SetStrPara("data.canceltermdate",canceltermdate);

    if(canceltermdate != termdate) {
        // ���첻�ܳ���
        ks_setlasterr("���첻�ܳ���");
        return -1;
    }
    this->termseqno++;
    ret = SendRequest(req,resp);
    if(ret)
        return -1;
    resp.GetIntPara("data.retcode",&(this->retcode));
    resp.GetStrPara("data.retmsg",this->retmsg);
    if(!resp.GetIntPara("data.termid",&termid))
        return -1;
    if(!resp.GetIntPara("data.termseqno",&termseqno))
        return -1;
    if(!resp.GetIntPara("data.amount",&amount))
        return -1;

    if(this->retcode != 0) {
        if(EKS_CARDLOST == retcode)
            return -3;
        return -2;

    }
    if(termid != this->termid || termseqno != this->termseqno-1)
        return -2;
    trans.nTransAmt = amount;
    return 0;
#else
    int nRet=0;
    nRet = ks_paycancel(&trans);
    if(nRet) {
        return nRet;
    }
    return 0;
#endif
}

std::string KsDaemonClient::GetErrMsg() {
    std::stringstream info;
    info<<"C["<<this->retcode<<"]"<<this->retmsg;
    return info.str();
}