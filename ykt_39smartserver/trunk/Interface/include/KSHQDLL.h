#ifndef	_KSHQDLL_H
#define _KSHQDLL_H

#ifdef  KSHQDLL_EXPORTS
#define KSHQDLL_API __declspec(dllexport)
#else
#define KSHQDLL_API __declspec(dllimport)

#ifdef  _DEBUG
#pragma comment(lib, "..\\lib\\KSHQDLL_D.lib")
#pragma message("Automatically Linking KSHQDLL_D.DLL")
#else
#pragma comment(lib, "..\\lib\\KSHQDLL.lib")
#pragma message("Automatically Linking KSHQDLL.DLL")
#endif
#endif

/* 使用说明:
 *	第1步. 首先调用HQ_Init(), 初始化资源,与通信平台的连接也在此时建立.
 *	第2步. 调用HQ_Start(), 完成后Dll会从行情服务器上取行情,把取到的行情放入本地内存中
 *  第3步. 用HQ_GetRec() 或 HQ_GetnRec()取出本地内存的行情. 如果取出行情后想让DLL
           暂时停止从行情服务器上取行情, 可以调用HQ_Stop(); 如果想恢复,再次调用HQ_Start()
 *  第4步. 程序结束时, 调用HQ_Uninit()释放资源
 *  注意: 如果函数的返回值不是正常的,可以调用HQ_GetErrorNo()取错误代码,HQ_GetErrorMsg()取
          错误信息
	hezhenhua 20040312
 */
#ifdef __cplusplus
extern "C" {
#endif
KSHQDLL_API bool WINAPI HQ_Init(int iHqWay, 
						  HANDLE hWnd, 
						  unsigned int iMsg, 
						  char* strOperCode,
						  unsigned short wDestNo,
						  unsigned short wMainFunc,
						  char* strIP,
						  unsigned short wPort,
						  unsigned short wLocalPort, 
						  unsigned short wRegtimeval);
/*
	参数的取值:
 	iHqWay：1			//以TCP方式（通过通信平台）
 			2			//从UDP方式 （点对点）
 			3			//UDP广播方式 
 
 			hWnd:       //消息接收窗体的句柄，用于DLL向窗体发送消息
 			iMsg：		//DLL向窗体发送消息的消息号
 			strCustNo:	//操作员号(11位)
 			wDestNo:	//行情服务器的结点号
 			wMainFunc:	//行情服务器的主功能号(通常为3001)
 			strIP:		//通信平台(或行情服务器)的IP地址
 			wPort:  	//通信平台(或行情服务器)的端口号(或调用者的端口号)
 			wLocalPort:	//本地端口号或广播端口号
 
 	返回值：true		//初始化成功
 			false		//初始化失败
 注意:如果iHqWay的值为 1:	strOperCode->必填
							wDestNo->行情服务器的结点号(填0即可), 必填
							wMainFunc->行情服务器的主功能号(默认为666), 必填
							strIP->通信平台的IP地址, 必填
							wPort->通信平台的端口, 必填
							wRegtimeval->定时注册的时间间隔, 必填
	 如果iHqWay的值为 2:	strOperCode->操作员号,必填
							strIP->行情服务器的IP地址, 必填
							wPort->行情服务器的端口, 必填
							wLocalPort->调用DLL的程序的本地端口号必填
							wRegtimeval->定时注册的时间间隔, 必填
 	 如果iHqWay的值为 3:	wLocalPort->接收广播的端口号, 必填

   针对不同的iHqWay的取值,必填的参数是必须确保正确的.
   其它不要必填的参数: 如果是数值型的,全部为0;如果是指针或字符串型的,全部为NULL
   广播端口号要和行情服务器或行情转发机保持一致.如无特殊变动
   行情服务器和行情转发机的广播端口为27657
*********************************************************************************
*/   

KSHQDLL_API int WINAPI HQ_GetRec(unsigned char* buf, int isize, int itimeout);
/*
 *	参数说明：
 *		buf:	//指向存放取出的行情的缓冲
 *		isize:	//缓冲的大小
 *		itimeout://队列为空时的超时时间
 *	如果itimeout = 0,当队列为空时,直接返回
 *  如果itimeout > 10, 当队列为空时,会睡眠itimeout毫秒后再返回
 *  如果itimeout在1~10这间,报错后返回
 *
 *	返回值：取出的行情记录的实际的大小
 *		0 行情接收队列为空
 *		< 0 出错
 *		> 0	正确，实际行情记录的大小
 *
 *  说明:如果调用者没有单独开设线程调用本函数做接收, itimeout一定要设为 0
 *		 否则,每取一次记录,就会睡眠1000毫秒	
 ****************************************************************************
 */


KSHQDLL_API int WINAPI HQ_GetnRec (unsigned char* buf, int isize, int *ireccount, int itimeout);
/*
 *	参数说明：
 *		buf:	//指向存放取出的行情的缓冲
 *		isize:	//缓冲的大小
 *		ireccount://实际取出的记录的条数
 *		
 *      hezhenhua 20031205 add
 *		itimeout: //当本地行情队列为空的超时值
 *	返回值：取出的行情记录的实际的大小之和
 *		0 行情接收队列为空
 *		< 0 出错
 *		> 0	正确，实际行情记录的大小
 **************************************************************************
 */

KSHQDLL_API bool WINAPI HQ_Uninit();
/*
 *	资源释放操作, 清空行情接收队列，中断TCP或UDP的连接, 注销
 ************************************************************
 */

KSHQDLL_API int WINAPI  HQ_GetErrorNo();

KSHQDLL_API bool WINAPI HQ_Start();
/*
 *	开始从行情服务器取行情, 在HQ_Init()成功执行这后,要调用HQ_Start才会从
 *  行情服务器上取行情.
 */

KSHQDLL_API void WINAPI HQ_GetErrorMsg(char *msgbuf, int ibufsize);
/*
 *	获得最近一次错误的错误信息
 */

KSHQDLL_API bool WINAPI HQ_Stop();
/*
 *	暂停从行情服务器取行情, 想先暂时停止从行情服务器接收行情时,调用HQ_Stop()
 *  如果想结束程序而释放资源时,只要调用HQ_Uninit()就可以了,不用调用HQ_Stop();
 */

KSHQDLL_API int WINAPI HQ_GetQueSize();
/*
 *	获取本地行情队列的长度
 */

KSHQDLL_API void WINAPI HQ_GetHandle(HANDLE *phandle);
/*
 *	取本条TCP连接的句柄
 */
#ifdef __cplusplus
}
#endif
#endif