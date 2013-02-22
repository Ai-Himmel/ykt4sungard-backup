#ifndef _KS_DAEMONCLIENT_H_
#define _KS_DAEMONCLIENT_H_

#include <string>


class KsDaemonClient
{
#ifdef USEWXLIB
	KsCardMsgRecv msgRecv;
	wxSocketClient sock;
	static const std::string daemon_app_name;
	static const wxString daemon_app_id;
#endif
	static const std::string msg_error_file;
private:
	int svrport;
	std::string authcode;
	std::string retmsg;
	int retcode;
	int termseqno;
	int hasLogin;
	int Connect2Daemon();
	int ForceStartDaemon();
	int SendRequest(KsCardMsg &req,KsCardMsg &resp,int logfaild = 1);
	int SaveMsgToFile(KsCardMsg &req,const std::string filename);
	int IsCanProcess();
	int ResendMsgFile(const std::string filename,KsCardMsg &resp);
public:
	int termid;
	std::string samno;
	int shopid;
	std::string shopname;
	std::string GetErrMsg();
public:
	KsDaemonClient(int port);
	~KsDaemonClient();
	void SetPort(int port)
	{
		svrport = port;
	}
	/** \breif 签到
	 * \param force - 1 表示强制签到
	 * \return 返回 0 表示签到成功，-1 表示连接daemon进程错误，-2 表示签到失败
	 */
	int Login(int force);
	/** \breif 消费初始化
	 * \param trans - 消费参数
	 * \param cardver - 卡当前黑名单版本号
	 * \return 返回 0 表示成功，-1 表示失败, -2 表示请求失败，-3 表示卡已挂失
	 */
	int PreparePay(ST_TRANSPACK &trans,const std::string& cardverno);
	/** \breif 消费确认
	 * \param trans - 消费参数
	 * \param writeflag - 写卡状态 1 表示写卡成功，2 表示中途拔卡，5 表示写卡失败
	 * \return 返回 0 表示成功，-1 表示失败, -2 表示请求失败, -3 表示请求返回错误
	 */
	int ConfirmPay(ST_TRANSPACK &trans,int writeflag);
	/** \breif 判断服务状态
	 * \return 返回 0 表示服务正常，-1 表示服务未启动
	 */
	int IsSvrOk();
	/** \breif 判断登录成功
	 * \return 返回 0 表示已登录，-1 表示未登录
	 */
	int IsLogin();
	/** \breif 检查卡状态
	 * \param cardno - 卡号
	 * \param statuscode - 卡状态码
	 * \param statusinfo - 卡状态信息
	 * \return 返回0 表示调用成功，其他表示失败
	 */
	int GetCardStatus(int cardno,const std::string &cardverno,char *statuscode,char *statusinfo);
	/** \breif 消费冲正
	 * \return 返回 0 表示
	 */
	int CancelPay(ST_TRANSPACK &trans,const std::string &cardverno);
};

#endif // _KS_DAEMONCLIENT_H_
