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
	/** \breif ǩ��
	 * \param force - 1 ��ʾǿ��ǩ��
	 * \return ���� 0 ��ʾǩ���ɹ���-1 ��ʾ����daemon���̴���-2 ��ʾǩ��ʧ��
	 */
	int Login(int force);
	/** \breif ���ѳ�ʼ��
	 * \param trans - ���Ѳ���
	 * \param cardver - ����ǰ�������汾��
	 * \return ���� 0 ��ʾ�ɹ���-1 ��ʾʧ��, -2 ��ʾ����ʧ�ܣ�-3 ��ʾ���ѹ�ʧ
	 */
	int PreparePay(ST_TRANSPACK &trans,const std::string& cardverno);
	/** \breif ����ȷ��
	 * \param trans - ���Ѳ���
	 * \param writeflag - д��״̬ 1 ��ʾд���ɹ���2 ��ʾ��;�ο���5 ��ʾд��ʧ��
	 * \return ���� 0 ��ʾ�ɹ���-1 ��ʾʧ��, -2 ��ʾ����ʧ��, -3 ��ʾ���󷵻ش���
	 */
	int ConfirmPay(ST_TRANSPACK &trans,int writeflag);
	/** \breif �жϷ���״̬
	 * \return ���� 0 ��ʾ����������-1 ��ʾ����δ����
	 */
	int IsSvrOk();
	/** \breif �жϵ�¼�ɹ�
	 * \return ���� 0 ��ʾ�ѵ�¼��-1 ��ʾδ��¼
	 */
	int IsLogin();
	/** \breif ��鿨״̬
	 * \param cardno - ����
	 * \param statuscode - ��״̬��
	 * \param statusinfo - ��״̬��Ϣ
	 * \return ����0 ��ʾ���óɹ���������ʾʧ��
	 */
	int GetCardStatus(int cardno,const std::string &cardverno,char *statuscode,char *statusinfo);
	/** \breif ���ѳ���
	 * \return ���� 0 ��ʾ
	 */
	int CancelPay(ST_TRANSPACK &trans,const std::string &cardverno);
};

#endif // _KS_DAEMONCLIENT_H_
