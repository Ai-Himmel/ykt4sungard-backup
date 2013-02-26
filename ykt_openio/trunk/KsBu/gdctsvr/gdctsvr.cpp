#include "gdctsvr.h"


/*
设计想法：
1. 主线程启动后，先向讯源服务签到，签到成功后启动两个子线程：A和B
2. A线程负责接收所有BU 发送过来的请求，并保存到请求队列中
3. B 线程负责从请求队列中读取消息，并向讯源服务器发送请求；B 线程从讯源服务器上收到应答后直接应答给BU
4. B 线程在没有任何请求时，每 10s 向讯源服务器发送心跳请求
5. 当请求队列中的消息数超过30个时，请求将被拒绝
*/


KSG_GDCT_Server g_server;

int main()
{
	//1 读取参数
	//2 向讯源服务器签到
	//3 创建 A , B 线程
	//4 进入主循环

	if(server.start_server()!=0)
	{
		return -1;
	}
	while(server.is_running())
	{
		Sleep(10);
	}
}