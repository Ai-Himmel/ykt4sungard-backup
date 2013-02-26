#define OutErr(a) cout<< (a) << endl<< "出错代码：" << WSAGetLastError() << endl<< "出错文件："<< __FILE__<< endl<< "出错行数：" << __LINE__ << endl 
#define OutMsg(a) cout << (a) << endl

#ifndef   BU_ALD_H_H 
#define   BU_ALD_H_H


// 命令定义
#define CMD_READ 1 // 读取状态
#define CMD_SEND 2 // 回复请求
#define CMD_WAIT 3  // 没有用
// 标志目前的SOCKET该做什么
enum ECurOp
{RecvData,WaitData,Working, ExecCmd};


typedef struct tagCommand
{
 int CommandID;  // 命令ID
 DWORD DataSize;  // 后接数据的大小
}SCommand;

typedef struct tagSocketInfo
{
  SOCKET sock;
  ECurOp eCurOp;
  SCommand cmd;
  int ThreadNo;
  char *data;
}SSocketInfo;

typedef struct Agd_ThirdPay_JJLink
{
	char ecard_id[30];
	char request_time[20];
	char ecard_num[20];
	char username[50];
	char fullname[50];
	char amount[30];
	char ecard_machine_id[20];
	char ecard_ip[20];
    char inpayamount_id[20];
    char reply_time[20];
	char ack_time[20];
	char status[10];
	char update_time[20];
	char messages[1024];
}Agd_ThirdPay;
class socketopt
{
public:
	SSocketInfo sockInfo;
	void DoRecvData(vector<SSocketInfo> &vecSockInfo, int idx);	
	void DoExecCmd(vector<SSocketInfo> &vecSockInfo, int idx);
	void DoGetKstData(vector<SSocketInfo> &vecSockInfo, int idx);
	int RecvFix(SOCKET socket, char *data, DWORD len);
	int SendFix(SOCKET socket, char *data, DWORD len);
	
};

#endif