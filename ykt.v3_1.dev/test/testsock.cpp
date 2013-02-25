#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include "json/json.h"
#include "../ksitfcdaemon/std.h"
#include "../ksitfcdaemon/kscardmsg.h"
#include <cppunit/extensions/HelperMacros.h>

#define TEST_PORT 10001

class Client {
private:
    wxSocketClient* clt;
public:
    Client() {
        clt = new wxSocketClient(wxSOCKET_NOWAIT);
    }
    ~Client() {
        clt->Close();
        delete clt;
    }
    int Connect() {
        wxIPV4address addr;
        addr.LocalHost();
        addr.Service(TEST_PORT);
        clt->Connect(addr,false);
        try {
            if(!clt->WaitOnConnect(10)) {
                wxLogError(wxT("连接服务器失败！"));
                return -1;
            }
            if(!clt->IsConnected()) {
                wxLogError(wxT("连接服务器失败！"));
                clt->Close();
                return -1;
            } else {
                wxLogMessage(wxT("连接服务器成功"));
                return 0;
            }
        } catch(std::exception &ex) {
            return -1;
        }
    }
    int Send(KsCardMsg& req,KsCardMsg &resp) {
        std::stringstream content;
        std::string buf = req.ToMsg();
        content<<std::setfill('0')<< std::setw(5)<<buf.length()<<buf;
        buf = content.str();
        if(clt->WaitForWrite(0,300)) {
            clt->Write(buf.c_str(),buf.length());
            KsCardMsgRecv recv;
            recv.Reset();
            recv.SetClient(clt);
            for(;;) {
                if(clt->WaitForRead(2,0)) {
                    int ret = recv.RecvData(resp);
                    if(ret==0)
                        return 0;
                    else if(ret == 1)
                        continue;
                    else {
                        wxString msg = wxString::Format("RecvData error,ret=%d",ret);
                        wxLogError(msg);
                        return -1;
                    }
                } else
                    return -1;
            }
        }
        return -1;
    }
};

class TestDaemonSock: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestDaemonSock);
    CPPUNIT_TEST(testMsg);
    CPPUNIT_TEST(testPurchase);
    CPPUNIT_TEST_SUITE_END();
public:
    static const int g_termid = 24;
    static const char g_samno[];
    void setUp() {
    }
    void tearDown() {
    }
    ///////////////////////////////////////////////////
public:
    void testMsg() {

        KsCardMsg req,resp;
        req.SetMsgType("login");
        req.SetIntPara("data.termid",g_termid);
        req.SetStrPara("data.samno",g_samno);

        Client clt;
        int ret;
        ret = clt.Connect();
        CPPUNIT_ASSERT(ret == 0);
        ret = clt.Send(req,resp);
        CPPUNIT_ASSERT(ret == 0);

        std::string value;
        bool rc;

        rc = resp.GetStrPara("authcode",value);
        CPPUNIT_ASSERT(rc == true);

        //////////////////////////////////////////////////////////
        req.Reset();
        resp.Reset();
        req.SetMsgType("login");
        req.SetIntPara("data.term",g_termid);
        req.SetStrPara("data.samno",g_samno);
        ret = clt.Send(req,resp);
        CPPUNIT_ASSERT(ret != 0);
    }

    void testPurchase() {
        int termid = g_termid,retcode;
        std::string retmsg;
        KsCardMsg req,resp;
        req.SetMsgType("login");
        req.SetIntPara("data.termid",termid);
        req.SetStrPara("data.samno",g_samno);

        Client clt;
        int ret;
        ret = clt.Connect();
        CPPUNIT_ASSERT(ret == 0);
        ret = clt.Send(req,resp);
        CPPUNIT_ASSERT(ret == 0);

        std::string authcode;
        int termseqno;
        bool rc;

        rc = resp.GetStrPara("authcode",authcode);
        CPPUNIT_ASSERT(rc == true);
        rc = resp.GetIntPara("data.termseqno",&termseqno);
        CPPUNIT_ASSERT(rc == true);

        //////////////////////////////////////////////////////////
        req.Reset();
        resp.Reset();
        req.SetMsgType("init4purchase");
        req.SetStrPara("authcode",authcode);
        req.SetIntPara("data.termid",termid);
        req.SetIntPara("data.termseqno",termseqno);
        req.SetIntPara("data.cardno",100);
        req.SetStrPara("data.cardverno","20101231000001");
        req.SetIntPara("data.amount",10);
        req.SetIntPara("data.befbala",10000);
        req.SetIntPara("data.paycnt",2);
        req.SetStrPara("data.samno",g_samno);
        req.SetStrPara("data.termdate","20110107");
        req.SetStrPara("data.termtime","140449");
        req.SetStrPara("data.cardphyid","AB1022BC");

        ret = clt.Send(req,resp);
        CPPUNIT_ASSERT(ret == 0);

        rc = resp.GetIntPara("data.retcode",&retcode);
        CPPUNIT_ASSERT(rc == true);
        rc = resp.GetStrPara("data.retmsg",retmsg);
        CPPUNIT_ASSERT(rc == true);
        CPPUNIT_ASSERT_MESSAGE(retmsg,retcode == 0);

        CPPUNIT_ASSERT(retcode == 0);

        int resptermid,resptermseqno;
        rc = resp.GetIntPara("data.termid",&resptermid);
        CPPUNIT_ASSERT(rc == true);

        rc = resp.GetIntPara("data.termseqno",&resptermseqno);
        CPPUNIT_ASSERT(rc == true);

        CPPUNIT_ASSERT(resptermid == termid);
        CPPUNIT_ASSERT(resptermseqno == termseqno);

        //////////////////////////////////////////////////////////
        req.Reset();
        resp.Reset();
        req.SetMsgType("debit4purchase");
        req.SetStrPara("authcode",authcode);
        req.SetIntPara("data.termid",termid);
        req.SetIntPara("data.termseqno",termseqno);
        req.SetStrPara("data.termdate","20110107");
        req.SetStrPara("data.tac","01020304");
        req.SetIntPara("data.samseqno",123);
        req.SetIntPara("data.status",1);

        ret = clt.Send(req,resp);
        CPPUNIT_ASSERT(ret == 0);

        rc = resp.GetIntPara("data.retcode",&retcode);
        CPPUNIT_ASSERT(rc == true);
        rc = resp.GetStrPara("data.retmsg",retmsg);
        CPPUNIT_ASSERT(rc == true);
        CPPUNIT_ASSERT_MESSAGE(retmsg,retcode == 0);

        rc = resp.GetIntPara("data.termid",&resptermid);
        CPPUNIT_ASSERT(rc == true);

        rc = resp.GetIntPara("data.termseqno",&resptermseqno);
        CPPUNIT_ASSERT(rc == true);

        CPPUNIT_ASSERT(resptermid == termid);
        CPPUNIT_ASSERT(resptermseqno == termseqno);
    }
};
const char TestDaemonSock::g_samno[]="000000000015";

CPPUNIT_TEST_SUITE_REGISTRATION(TestDaemonSock);
