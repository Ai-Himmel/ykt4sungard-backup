#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <signal.h>
#include <pthread.h>
#include <ext/hash_map>
#include "cpack.h"
#include "pubfunc.h"
#include "bupub.h"
#include "errdef.h"
#include "logfile.h"
#include "profile.h"
#include "bank.h"
#include "tcp.h"

using namespace __gnu_cxx;
//extern int debug;
ST_BANK_CONFIG g_Bank;
THIRD_PART_BANK_CONFIG g_third_part_bank;
#define TIME_OUT1 					5000
#define TIME_OUT2 					500
#define TIME_DELAY					1
#define HASH_MAX_NUM				999999
#define HASH_MIN_NUM				500001

#define HRBZH_PACKET_HEAD 			88
#define HRBZH_STR_PACKET_LENGTH 	4
#define HRBZH_MSG_TYPE_START 		5
#define HRBZH_SERIAL_START 			31
#define HRBZH_SERIAL_LENGTH			6
#define HRBZH_APPEND_START 			31
#define HRBZH_APPEND_LENGTH			6
#define HRBZH_MSG_TYPE_LEGNTH 		4
#define TIME_SLEEP 					1

#define BYTE_LENGTH1				4

#define     BANK_HRBZH_TRADE_CODE_SIGN_IN		    "0100"
#define     BANK_HRBZH_TRADE_CODE_QUERYBALANCE		"0240"	
#define     BANK_HRBZH_TRADE_CODE_TRANS		    	"0200"	
#define     BANK_HRBZH_TRADE_CODE_DETRANS		    "0400"	

#define FILE_NAME1 "serial_no.txt"
char serial_no[7] = "";

typedef CTcpSocket* CTcpSocketPoint;
hash_map<int, CTcpSocketPoint> hmap_collect, hmap_used_collect;
typedef pair<int, CTcpSocketPoint> dword_pair;

CTcpSocket server_socket, remote_socket, bank_socket;

pthread_mutex_t mutex; 			//= PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t flag; 			//= PTHREAD_COND_INITIALIZER;
//pthread_cond_t flag2; 			//= PTHREAD_COND_INITIALIZER;

struct timespec delay;

static int hash_count = 0; 
static int last_hash_szie = 0;
int bank_transfer_flag = 0;
char recv_msg[2048] = "";
int local_serial_no = 0;

#ifdef DEBUG
#define	TRACE	printf
#else
#define	TRACE	NULL
#endif

void Trace_8583_Package(char *_8583_buf, int _8583_length, int format, char *msg)
{
	int count = 1;
	printf("%s\n", msg);
	printf("---------------------------------------------------------------------------\n");

	for	(int jj = 0; jj < _8583_length; jj += 16)
	{
		if (10 == format)
		{
			printf("[%d] BYTE DEC 16 bit %d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d\n", count,
			_8583_buf[jj], _8583_buf[jj + 1], _8583_buf[jj + 2], _8583_buf[jj + 3], _8583_buf[jj + 4], _8583_buf[jj + 5], 
			_8583_buf[jj + 6], _8583_buf[jj + 7], _8583_buf[jj + 8], _8583_buf[jj + 9], _8583_buf[jj + 10], _8583_buf[jj + 11], 
			_8583_buf[jj + 12], _8583_buf[jj + 13], _8583_buf[jj + 14], _8583_buf[jj + 15]);
			count++;
		}
		else
		{
			printf("[%d] BYTE HEX 16 bit %02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X:%02X\n", count,
			_8583_buf[jj], _8583_buf[jj + 1], _8583_buf[jj + 2], _8583_buf[jj + 3], _8583_buf[jj + 4], _8583_buf[jj + 5], 
			_8583_buf[jj + 6], _8583_buf[jj + 7], _8583_buf[jj + 8], _8583_buf[jj + 9], _8583_buf[jj + 10], _8583_buf[jj + 11], 
			_8583_buf[jj + 12], _8583_buf[jj + 13], _8583_buf[jj + 14], _8583_buf[jj + 15]);
			count++;
		}
	}
	printf("---------------------------------------------------------------------------\n");

	return ;
}

void *RecvBankData(void *data)
{
	int ret = 0;
	int packet_length = 0;
	char str_packet_length[10] = "";
	CTcpSocket recv_bank_socket, bank_socket, *tmp_tcp_socket;
	char remote_ip[25] = "";
	bool bank_flag = false;
	char recv_bank_msg[2048] = "";
	int ykt_send_count = 0;
		
	writelog(LOG_ERR,"take into thread func RecvBankData");

	bank_flag = recv_bank_socket.Create(AF_INET, SOCK_STREAM); 
	if (!bank_flag)
	{
		writelog(LOG_INFO,"create recv bank socket failed ret = [%d]", bank_flag);
		return NULL;
	}

	writelog(LOG_INFO,"create recv bank socket success ret = [%d]", bank_flag);
	writelog(LOG_INFO,"recv bank bind socket ip = [%s], port = [%d]", g_third_part_bank.listen_ip, g_third_part_bank.listen_port);
	bank_flag = recv_bank_socket.Listen(g_third_part_bank.listen_port, g_third_part_bank.listen_ip);
	if (!bank_flag)
	{
		writelog(LOG_INFO,"create recv bank listen socket failed ret = [%d]", bank_flag);
		recv_bank_socket.Close();
		return NULL;
	}

	writelog(LOG_INFO,"create recv bank listen socket success ip = [%s], port = [%d]",g_third_part_bank.listen_ip, g_third_part_bank.listen_port);	
	while(true)
	{
		memset(recv_bank_msg, 0, sizeof(recv_bank_msg));
		memset(str_packet_length, 0, sizeof(str_packet_length));
		bank_flag = recv_bank_socket.Accept(bank_socket, remote_ip);
		writelog(LOG_INFO,"recv bank socket remote ip = [%s]", remote_ip);
		if (!bank_flag)
		{
			writelog(LOG_INFO,"accpet bank socket failed ret = [%d]", bank_flag);
		}
		
		ret = bank_socket.Recv(recv_bank_msg, HRBZH_PACKET_HEAD, TIME_OUT1);
		if (ret != HRBZH_PACKET_HEAD)
		{
			writelog(LOG_INFO,"recv bank packet head failed = [%d]", ret);
			continue ;
		}

		memcpy(str_packet_length, recv_bank_msg + HRBZH_PACKET_HEAD - HRBZH_STR_PACKET_LENGTH, HRBZH_STR_PACKET_LENGTH);
		packet_length = atoi(str_packet_length);
		writelog(LOG_INFO,"packet_length = [%d]", packet_length);

		ret = bank_socket.Recv(recv_bank_msg + HRBZH_PACKET_HEAD, packet_length, TIME_OUT1);
		if (ret != packet_length)
		{
			writelog(LOG_INFO,"recv bank packet length failed = [%d]", ret);
			continue ;
		}

//		Trace_8583_Package(recv_bank_msg, HRBZH_PACKET_HEAD + packet_length, 0, "zh recv bank msg");	
		memset(str_packet_length, 0, sizeof(str_packet_length));
		memcpy(str_packet_length, recv_bank_msg + HRBZH_APPEND_START, HRBZH_APPEND_LENGTH);
		ykt_send_count = atoi(str_packet_length);
		writelog(LOG_INFO,"ykt send count = [%d]", ykt_send_count);

		if (hmap_collect.find(ykt_send_count) != hmap_collect.end())
		{
			tmp_tcp_socket = hmap_collect[ykt_send_count];
		}
		else
		{
			continue ;
		}

		if (tmp_tcp_socket)
		{
			ret = tmp_tcp_socket->Send(recv_bank_msg, packet_length + HRBZH_PACKET_HEAD);
			if (ret < 0)
			{
				writelog(LOG_INFO,"send ykt server failed = [%d] recv_bank_msg = [%s]", ret, recv_bank_msg);
			}
			tmp_tcp_socket->Close();
			if (hmap_collect.size())
			{
				delete tmp_tcp_socket;
				hmap_collect[ykt_send_count] = NULL;
				hmap_collect.erase(ykt_send_count);			
			}
			tmp_tcp_socket = NULL;
			writelog(LOG_INFO,"erase hash item = [%d], hash map count = [%d]", ykt_send_count, hmap_collect.size());
		}
	}

	return NULL;
}

void *SendBankData(void *data)
{
	int ret = 0;
	int packet_length = 0;
	int local_serial_no = 0;
	int _length = 0;
	bool socket_flag = false;
	char str_packet_length[10] = "";
	char remote_ip[25] = "";
	bool bank_flag = false;
	CTcpSocket *tmp_tcp_socket = NULL;
	CTcpSocket *accept_tcp_socket = NULL;
	char transfer_msg[2048] = "";
	char local_date[9] = "";
	char local_time[7] = "";
	
	hash_map<int, CTcpSocketPoint>::iterator p_iter, tmp_iter, recv_iter, tmp_iter2, p_main_iter;
	writelog(LOG_ERR,"take into thread func SendBankData");
			
	while(true)
	{
		getsystime(local_time);
		//writelog(LOG_ERR,"hmap_collect size = [%d], last hash size = [%d], local_time =[%s]", hmap_collect.size(), last_hash_szie, local_time);
		// AM 1:00  - 1:01 clear all hash items
		if ((memcmp(local_time, "0100", sizeof(char) * BYTE_LENGTH1) > 0) && (memcmp(local_time, "0101", sizeof(char) * BYTE_LENGTH1) < 0))			
		{
			for (p_main_iter = hmap_collect.begin(); p_main_iter != hmap_collect.end(); p_main_iter++)
			{
				accept_tcp_socket = p_main_iter->second;
				if (accept_tcp_socket)
				{
					delete accept_tcp_socket;
					accept_tcp_socket = NULL;
				}
			}

			// if hash size big than zero that need to be cleared
			if (hmap_collect.size()) 
			{ 
				hmap_collect.clear(); 
				writelog(LOG_INFO,"clear all hash items, hash size = [%d], systime = [%s]", hmap_collect.size(), local_time);
			}			
			else { continue; }
		}

		if (0 == hmap_collect.size())			// return hash_map count
		{
			usleep(TIME_OUT2);
			last_hash_szie = 0;
			continue;
		}
		
		if (last_hash_szie == hmap_collect.size())
		{
			sleep(TIME_DELAY);
			/*
			hmap_collect.clear();
			*/
			last_hash_szie = 0;
			continue ;
		}

//		for (p_iter = hmap_collect.begin(); p_iter != hmap_collect.end(); p_iter++)
		for (p_iter = hmap_collect.begin(); p_iter != hmap_collect.end();)
		{	
			tmp_iter2 = p_iter++;
			last_hash_szie = hmap_collect.size();
			memset(transfer_msg, 0, sizeof(transfer_msg));
			memset(str_packet_length, 0, sizeof(str_packet_length));
			tmp_tcp_socket = tmp_iter2->second;			// get rand socket point from hash table
			CTcpSocket *bank_socket = NULL;

			// recv data from ykt server
			if (NULL == tmp_tcp_socket)
			{
				writelog(LOG_INFO,"tmp_tcp_socket is null");
				goto L_END;
			}
			
			ret = tmp_tcp_socket->Recv(transfer_msg, HRBZH_PACKET_HEAD, TIME_OUT1);
			if (ret != HRBZH_PACKET_HEAD)
			{
				writelog(LOG_INFO,"recv packet head failed = [%d], transfer_msg = [%s]", ret, transfer_msg);
				goto L_END;
			}

			memcpy(str_packet_length, transfer_msg + HRBZH_PACKET_HEAD - HRBZH_STR_PACKET_LENGTH, HRBZH_STR_PACKET_LENGTH);
			packet_length = atoi(str_packet_length);
			
			// recv data from ykt server
			ret = tmp_tcp_socket->Recv(transfer_msg + HRBZH_PACKET_HEAD, packet_length, TIME_OUT1);
			if (ret != packet_length)
			{
				writelog(LOG_INFO,"recv packet length failed = [%d]", ret);
				goto L_END;
			}

			// sign in and query 
			if (
				0 == memcmp(transfer_msg + 1 + HRBZH_STR_PACKET_LENGTH, BANK_HRBZH_TRADE_CODE_SIGN_IN, HRBZH_STR_PACKET_LENGTH)
				|| 
				0 == memcmp(transfer_msg + 1 + HRBZH_STR_PACKET_LENGTH, BANK_HRBZH_TRADE_CODE_QUERYBALANCE, HRBZH_STR_PACKET_LENGTH)
				)
			{
				// modify msg head and input serial in msg head
				memset(str_packet_length, 0, sizeof(str_packet_length));
				sprintf(str_packet_length, "%06d", tmp_iter2->first);			// serial_no
				memcpy(transfer_msg + HRBZH_APPEND_START, str_packet_length, HRBZH_APPEND_LENGTH);
				writelog(LOG_INFO,"hrbzh head serial data = [%s]", str_packet_length);
			
				memset(str_packet_length, 0, sizeof(str_packet_length));
				memcpy(str_packet_length, transfer_msg + HRBZH_PACKET_HEAD + 12, 2);
				sprintf(transfer_msg + HRBZH_PACKET_HEAD + 30 + atoi(str_packet_length), "%06d", tmp_iter2->first);
				local_serial_no = tmp_iter2->first;
			}
			// trans
			else if (0 == memcmp(transfer_msg + 1 + HRBZH_STR_PACKET_LENGTH, BANK_HRBZH_TRADE_CODE_TRANS, HRBZH_STR_PACKET_LENGTH))
			{
				// get serial from packet
				memset(str_packet_length, 0, sizeof(str_packet_length));
				memcpy(str_packet_length, transfer_msg + HRBZH_PACKET_HEAD + 20, 2);
				_length = atoi(str_packet_length);
				memset(str_packet_length, 0, sizeof(str_packet_length));
				memcpy(str_packet_length, transfer_msg + HRBZH_PACKET_HEAD + 50 + _length, 6);
				local_serial_no = atoi(str_packet_length);
				writelog(LOG_INFO,"local serial no = [%d]", local_serial_no);
			}
			// detrans
			else if (0 == memcmp(transfer_msg + 1 + HRBZH_STR_PACKET_LENGTH, BANK_HRBZH_TRADE_CODE_DETRANS, HRBZH_STR_PACKET_LENGTH))
			{
				memset(str_packet_length, 0, sizeof(str_packet_length));
				sprintf(str_packet_length, "%06d", tmp_iter2->first);			// serial_no
				memcpy(transfer_msg + HRBZH_APPEND_START, str_packet_length, HRBZH_APPEND_LENGTH);
				writelog(LOG_INFO,"hrbzh head serial data = [%s]", str_packet_length);
			
				memset(str_packet_length, 0, sizeof(str_packet_length));
				memcpy(str_packet_length, transfer_msg + HRBZH_PACKET_HEAD + 20, 2);
				_length = atoi(str_packet_length);
				memset(str_packet_length, 0, sizeof(str_packet_length));
				sprintf(transfer_msg + HRBZH_PACKET_HEAD + 50 + _length, "%06d", tmp_iter2->first);
				local_serial_no = tmp_iter2->first;
			}

			// create new hash node from old
			if (local_serial_no != tmp_iter2->first)
			{			
				// drop old hash node
				// change socket address to new hash map node
				hmap_collect.insert(dword_pair(local_serial_no, tmp_tcp_socket));
				writelog(LOG_INFO,"insert recv bank socket hash serial no = [%d]", local_serial_no);
				hmap_collect.erase(tmp_iter2);
			}
			
			bank_socket = new CTcpSocket();
			alarm(TIME_DELAY);
			// connect to bank server
			socket_flag = bank_socket->ConnectTcp(g_third_part_bank.bank_ip, g_third_part_bank.bank_port);
			if (!socket_flag)
			{
				writelog(LOG_INFO,"connect bank ip failed = [%d], bank ip = [%s], bank port = [%d]", socket_flag, g_third_part_bank.bank_ip, g_third_part_bank.bank_port);
				bank_flag = false;
				goto L_BANK;
			}

			writelog(LOG_INFO,"connect bank ip successful bank ip = [%s], bank port = [%d]", g_third_part_bank.bank_ip, g_third_part_bank.bank_port);
	
			Trace_8583_Package(transfer_msg, HRBZH_PACKET_HEAD + packet_length, 0, "zh send bank msg");
			// send to bank server
			ret = bank_socket->Send(transfer_msg, packet_length + HRBZH_PACKET_HEAD);
			if (ret < 0)
			{
				writelog(LOG_INFO,"send bank ip failed = [%d] transfer_msg = [%s]", ret, transfer_msg);
				bank_flag = false;
				goto L_BANK;
			}
	
			bank_flag = true;			
			sleep(TIME_DELAY);						// send so fast that may be sleep for a while
L_BANK:
			if (bank_socket)
			{
				bank_socket->Close();
				delete bank_socket;
				bank_socket = NULL;	
			}

			if (bank_flag) { continue; }
L_END:
			if (tmp_tcp_socket)
			{
				tmp_tcp_socket->Close();
				writelog(LOG_INFO,"tmp_tcp_socket address is [%X]", tmp_tcp_socket);
				if (hmap_collect.size()) { delete tmp_tcp_socket; }
				tmp_tcp_socket = NULL;
			}

			if (hmap_collect.size()) 
			{
				hmap_collect.erase(tmp_iter2);
				writelog(LOG_INFO,"erase invaild hash map iter");
			}
			sleep(TIME_DELAY);
		}
	}
	
	return NULL;
}

int ReadIniThirdPartBank(THIRD_PART_BANK_CONFIG *p_third_part_bank)
{
	TIniFile tf;

	if (!tf.Open(THIRD_PART_INI_FILE))
	{
		writelog(LOG_ERR,"Cann't open ini file,file's name=[%s]",THIRD_PART_INI_FILE);
		return -1;
	}

	p_third_part_bank->local_port = tf.ReadInt("THIRD_PART", "LOCAL_PORT", 8888);
	tf.ReadString("THIRD_PART","LOCAL_IP","127.0.0.1",p_third_part_bank->local_ip, sizeof(p_third_part_bank->local_ip) - 1);	

	p_third_part_bank->bank_port = tf.ReadInt("THIRD_PART", "BANK_PORT", 7990);
	tf.ReadString("THIRD_PART","BANK_IP","127.0.0.1",p_third_part_bank->bank_ip,sizeof(p_third_part_bank->bank_ip) - 1);

	p_third_part_bank->listen_port = tf.ReadInt("THIRD_PART", "LISTEN_PORT", 7991);
	tf.ReadString("THIRD_PART","LISTEN_IP","127.0.0.1",p_third_part_bank->listen_ip,sizeof(p_third_part_bank->listen_ip) - 1);
	
	p_third_part_bank->bank_id = tf.ReadInt("THIRD_PART", "BANK_ID", BANK_HRBZH);

	writelog(LOG_ERR,"LOCAL_IP=[%s], LOCAL_PORT=[%d], BANK_IP=[%s], BANK_PORT=[%d], LISTEN_IP=[%s], LISTEN_PORT=[%d]", p_third_part_bank->local_ip, p_third_part_bank->local_port, p_third_part_bank->bank_ip, p_third_part_bank->bank_port, p_third_part_bank->listen_ip, p_third_part_bank->listen_port);
	tf.Close();
	return 0;   
}

int	app_flag = 0;
#define APP_FLAG_DAEMON	0x0001
#define APP_FLAG_CONFIG	0x0002
#define APP_FLAG_DEBUG	0x0004
#define APP_FLAG_TERM	0x8000

void sig_handler(int signo)
{
	switch(signo)
	{
	case	SIGINT:
	case	SIGTERM:
		app_flag |= APP_FLAG_TERM;
		break;
	default:
		break;
	}
}

int main(int argc,char *argv[])
{
	FILE *fp = NULL;
	int	_pid = 0;
	int  ret=0;
	int packet_length = 0;
	char str_packet_length[10] = "";
	char remote_ip[128] = "";
	int terminal_id=0;
	int opt;
   	extern int optind;
   	extern char *optarg;
	
	int continue_flag = false;
	bool socket_flag = false;
	pthread_t t1, t2;
//	delay.tv_sec = 0; 
//	delay.tv.nsec = 500000; /* 500,000 nanoseconds = 500 ms */ 

	while ((opt = getopt(argc, argv, "bdvhi:p:f:")) != EOF)
	{
		switch(opt)
		{
		case 'v':
			printf("bank guard version 1.0.2.10\n");
			return 0;
		case 'b':
			app_flag |= APP_FLAG_DAEMON;
			break;
		case 'd':
			app_flag |= APP_FLAG_DEBUG;
//			debug = 2;
			break;
		case 'i':
			app_flag |= APP_FLAG_CONFIG;
			ReadIniThirdPartBank(&g_third_part_bank);
			break;
		case 'p':
			break;
		case 'f':
			break;
		case '?':
		case 'h':
		default:
			printf("usage: %s -options \n", argv[0]);
			printf("\toptions:\n");
			printf("\t-b\t\trun as daemon\n");
			printf("\t-d\t\trun in debug mode, communication content will be printed to stdout\n");
			printf("\t-h\t\tshow this help message\n");
			printf("\t-i inifile\tassign config file\n");
			printf("\t-p ping_interval\tassign the interval between each ping\n");
			printf("\t-f flush_interval\tassign the interval between each database process\n");
			return 0;
		}
	}

 	// 屏蔽信号
	signal(SIGPIPE, sig_handler);
	signal(SIGALRM, sig_handler);
	signal(SIGINT, sig_handler);
	signal(SIGHUP, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGCHLD, sig_handler);

	if((app_flag&APP_FLAG_DAEMON)!= 0)
 	{
 		_pid=fork();
		if(_pid != 0)
			exit(0);
		else if(_pid< 0)
			exit(1);

		setsid();
		_pid=fork();
		if(_pid != 0)
			exit(0);
		else if(_pid< 0)
			exit(1);

		int i;
		for(i=3;i<20;++i)
			close(i);

		//umask(0);
 	}

	openlog("bank",LOG_PID|LOG_CONS|LOG_NDELAY,LOG_LOCAL4);
	ReadIniThirdPartBank(&g_third_part_bank);

	if((app_flag & APP_FLAG_TERM) != 0)
	{
		writelog(LOG_INFO,"收到终止信号，退出");
		return 0;
	}
		
	socket_flag = server_socket.Create(AF_INET, SOCK_STREAM); 
	if (!socket_flag)
	{
		writelog(LOG_ERR,"create ykt socket failed ret = [%d]", socket_flag);
		return 0;
	}
	writelog(LOG_ERR,"create ykt socket success ret = [%d]", socket_flag);
	
	socket_flag = server_socket.Listen(g_third_part_bank.local_port, g_third_part_bank.local_ip);
	if (!socket_flag)
	{
		writelog(LOG_ERR,"create ykt listen socket failed ret = [%d]", socket_flag);
		server_socket.Close();
		return 0;
	}
	writelog(LOG_ERR,"create ykt listen socket success port = [%d], ip = [%s]", g_third_part_bank.local_port, g_third_part_bank.local_ip);

	pthread_create(&t1, NULL, RecvBankData, NULL);
	pthread_create(&t2, NULL, SendBankData, NULL);

	sleep(TIME_SLEEP);
	// main thread, get socket from ykt bank server
	while(true)
	{
		CTcpSocket *remote_socket = new CTcpSocket();
		socket_flag = server_socket.Accept(*remote_socket, remote_ip);
		writelog(LOG_INFO,"remote ip = [%s]", remote_ip);
		if (!socket_flag)
		{
			writelog(LOG_INFO,"accpet socket failed ret = [%d]", ret);
			delete remote_socket;
		}

		if ((fp = fopen(FILE_NAME1, "r+b")) == NULL)
		{
			writelog(LOG_ERR,"Open indirect file error,file=[%s]", FILE_NAME1);
		}

		writelog(LOG_ERR,"Open indirect file successful, file=[%s]", FILE_NAME1);
		// 获取对账文件第一条记录
		if (NULL == fread(serial_no, sizeof(char), sizeof(serial_no) - 1, fp))	
		{
			writelog(LOG_ERR,"file read error");
		}

		if (fclose(fp))
		{
			writelog(LOG_ERR,"read close file error,file=[%s]", FILE_NAME1);
		}
			
		local_serial_no = atoi(serial_no);
	
		if (local_serial_no > HASH_MAX_NUM) { hash_count = HASH_MIN_NUM; }
		else if (0 == local_serial_no) { hash_count = HASH_MIN_NUM; }
		else { NULL; }
			
		hash_count = local_serial_no;
		
		writelog(LOG_ERR, "local_serial_no = [%d]", local_serial_no);
		local_serial_no++;
		memset(serial_no, 0, sizeof(serial_no) - 1);
		sprintf(serial_no, "%06d", local_serial_no);
		writelog(LOG_INFO,"serial_no = [%6.6s]", serial_no);

		if ((fp = fopen(FILE_NAME1, "w+b")) == NULL)
		{
			writelog(LOG_ERR,"Open indirect file error,file=[%s]", FILE_NAME1);
		}
		
		if (NULL == fwrite((char *)serial_no, sizeof(char), sizeof(serial_no) - 1, fp))	
		{
			writelog(LOG_ERR,"file write error");
		}

		if (fclose(fp))
		{
			writelog(LOG_ERR,"write close file error,file=[%s]", FILE_NAME1);
		}
				
		if (hmap_collect.find(hash_count) != hmap_collect.end())
		{
			writelog(LOG_INFO,"erase accpet socket hash count = [%d]", hash_count);
			hmap_collect.erase(hash_count);
		}
		
		hmap_collect.insert(dword_pair(hash_count, remote_socket));			// insert tcp socket
		writelog(LOG_ERR,"accept socket hmap_collect size = [%d]", hmap_collect.size());
		
		hash_count++;
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	writelog(LOG_INFO, "程序正常退出");
	printf("程序正常退出\n");
	return(0);
}

