#ifndef _KSCARDMSG_H_
#define _KSCARDMSG_H_

#define EKS_SUCCESS        0  //�ɹ�
#define EKS_DATABASE       1  //���ݿ����
#define EKS_SYSTEM         2  //ϵͳ�쳣
#define EKS_SEQNOREPEAT    10 //��ˮ���ظ�
#define EKS_AUTHCODEERR    11 //��Ȩ�����
#define EKS_UNUPLDSERI	   12 //�ѻ���ˮ������������
#define EKS_CARDLOST       13 //���ѹ�ʧ
#define EKS_LOGIN		   14 //ǩ��ʧ��
#define EKS_ALREADYCANCEL  15 //��ˮ�ѳ���
#define EKS_CANCELDTLNOTEXIST 16 //������ˮδ�ҵ�
#define EKS_CANCELDTLERROR 17 //������ˮ״̬�쳣

class KsCardMsg
{
private:
	typedef std::map<std::string,std::string> PARA_MAP_TYPE;
	PARA_MAP_TYPE msg_field_;
	std::string msgtype_;
	int parseLevel_;
	bool parseJsonData(const std::string& rootname,Json::Value &root);
public:
	KsCardMsg();
	~KsCardMsg();
	KsCardMsg(const KsCardMsg &rhs);
	virtual KsCardMsg& operator=(const KsCardMsg &rhs);
	void Reset();
	bool ParseMsg(const std::string &msg);
	std::string ToMsg();
	std::string MsgType() const;
	void SetMsgType(const std::string &msgtype);
	bool GetStrPara(const std::string &para_name,std::string &para_value) const;
	bool GetIntPara(const std::string &para_name,int *para_value) const;
	bool SetStrPara(const std::string &para_name,const std::string &para_value,int force = 0);
	bool SetIntPara(const std::string &para_name,int para_value,int force = 0);
};

#if defined(__WXBASE__) || defined(__WXMSW__)
class KsCardMsgRecv
{
private:
	static const size_t max_msgbuf_len = 4096;
	static const size_t msg_header_len = 5;
	char msgbuf_[max_msgbuf_len];
	size_t msg_recvlen_;
	size_t msg_length_;
	wxSocketClient* sock_;
public:
	KsCardMsgRecv();
	~KsCardMsgRecv();
	void Reset();
	int SetClient(void *client);
	/** \brief ��������
	* \para msg - ���ݰ�
	* \return ����<0 ��ʾ����-2 ��ʾ��Ҫ�ر�socket, ���� 0 ��ʾ�ѽ��յ��������ݰ� , ���� 1 ��ʾ������������
	*/
	int RecvData(KsCardMsg &msg);
};
#endif

#endif // _KSCARDMSG_H_
