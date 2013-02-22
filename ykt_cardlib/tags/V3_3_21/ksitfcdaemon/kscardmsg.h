#ifndef _KSCARDMSG_H_
#define _KSCARDMSG_H_

#define EKS_SUCCESS        0  //成功
#define EKS_DATABASE       1  //数据库错误
#define EKS_SYSTEM         2  //系统异常
#define EKS_SEQNOREPEAT    10 //流水号重复
#define EKS_AUTHCODEERR    11 //授权码错误
#define EKS_UNUPLDSERI	   12 //脱机流水笔数超过上限
#define EKS_CARDLOST       13 //卡已挂失
#define EKS_LOGIN		   14 //签到失败
#define EKS_ALREADYCANCEL  15 //流水已冲正
#define EKS_CANCELDTLNOTEXIST 16 //冲正流水未找到
#define EKS_CANCELDTLERROR 17 //冲正流水状态异常

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
	/** \brief 接收数据
	* \para msg - 数据包
	* \return 返回<0 表示错误，-2 表示需要关闭socket, 返回 0 表示已接收到完整数据包 , 返回 1 表示接续接收数据
	*/
	int RecvData(KsCardMsg &msg);
};
#endif

#endif // _KSCARDMSG_H_
