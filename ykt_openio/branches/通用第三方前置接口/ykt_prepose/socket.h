#define OutErr(a) cout<< (a) << endl<< "������룺" << WSAGetLastError() << endl<< "�����ļ���"<< __FILE__<< endl<< "����������" << __LINE__ << endl 
#define OutMsg(a) cout << (a) << endl

#ifndef   BU_ALD_H_H 
#define   BU_ALD_H_H


// �����
#define CMD_READ 1 // ��ȡ״̬
#define CMD_SEND 2 // �ظ�����
#define CMD_WAIT 3  // û����
// ��־Ŀǰ��SOCKET����ʲô
enum ECurOp
{RecvData,WaitData,Working, ExecCmd};


typedef struct tagCommand
{
 int CommandID;  // ����ID
 DWORD DataSize;  // ������ݵĴ�С
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