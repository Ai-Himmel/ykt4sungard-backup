#include "stdafx.h"
#include "socket.h"
#include "md5.h"
#include "tcp.h"
#include "publicfunc.h"
#include "bu_ald.h"
#include "bu_yzzsjsw.h"
#include "bu_agdcgdk.h"
#include "bu_agdsjsw.h"

///////////////////////////////////////////////////////////////////////
//
// 函数名       : RemoveByIndex
// 功能描述     : 根据 index 来删除 VECTOR 里的元素
// 参数         : vector<T> &vec [in]
// 参数         : int nIdx   [in]
// 返回值       : void 
//
///////////////////////////////////////////////////////////////////////
template<class T>
void EraseByIndex(vector<T> &vec, int nIdx)
{
  bool excwork=true;
 vector<T>::iterator it;
 it = vec.begin() + nIdx;
 
  diabwork=true;
  while (excwork)
  { 
	  Sleep(1000);
     if (exnum>0)
		continue;
	 excwork=false;
	  EnterCriticalSection(&g_cs);
	 vec.erase(it);
	  LeaveCriticalSection(&g_cs);
  }
 
  diabwork=false;
}

char *getsockerr(int errcode)
{
	
switch(errcode)  
	{
      case   10004:   return   "Interrupted   system   call";   break;     
      case   10009:   return   "Bad   file   number";   break;     
	  case   10013:   return   "Permission   denied";   break;     
      case   10014:   return   "Bad   address";   break;     
      case   10022:   return   "Invalid   argument   (not   bind)";   break;     
      case   10024:   return   "Too   many   open   files";   break;     
      case   10035:   return   "Operation   would   block";   break;     
      case   10036:   return   "Operation   now   in   progress";   break;     
      case   10037:   return   "Operation   already   in   progress";   break;     
      case   10038:   return   "Socket   operation   on   non-socket";   break;     
      case   10039:   return   "Destination   address   required";   break;     
      case   10040:   return   "Message   too   long";   break;     
      case   10041:   return   "Protocol   wrong   type   for   socket";   break;     
      case   10042:   return   "Bad   protocol   option";   break;     
      case   10043:   return   "Protocol   not   supported";   break;     
      case   10044:   return   "Socket   type   not   supported";   break;     
      case   10045:   return   "Operation   not   supported   on   socket";   break;     
      case   10046:   return   "Protocol   family   not   supported";   break;     
      case   10047:   return   "Address   family   not   supported   by   protocol   family";   break;     
      case   10048:   return   "Address   already   in   use";   break;     
      case   10049:   return   "Can't   assign   requested   address";   break;     
      case   10050:   return   "Network   is   down";   break;     
      case   10051:   return   "Network   is   unreachable";   break;     
      case   10052:   return   "Net   dropped   connection   or   reset";   break;     
      case   10053:   return   "Software   caused   connection   abort";   break;     
      case   10054:   return   "Connection   reset   by   peer";   break;     
      case   10055:   return   "No   buffer   space   available";   break;     
      case   10056:   return   "Socket   is   already   connected";   break;     
      case   10057:   return   "Socket   is   not   connected";   break;     
      case   10058:   return   "Can't   send   after   socket   shutdown";   break;     
      case   10059:   return   "Too   many   references,   can't   splice";   break;     
      case   10060:   return   "Connection   timed   out";   break;     
      case   10061:   return   "Connection   refused";   break;     
      case   10062:   return   "Too   many   levels   of   symbolic   links";   break;     
      case   10063:   return   "File   name   too   long";   break;     
      case   10064:   return   "Host   is   down";   break;     
      case   10065:   return   "No   Route   to   Host";   break;     
      case   10066:   return   "Directory   not   empty";   break;     
      case   10067:   return   "Too   many   processes";   break;     
      case   10068:   return   "Too   many   users";   break;     
      case   10069:   return   "Disc   Quota   Exceeded";   break;     
      case   10070:   return   "Stale   NFS   file   handle";   break;     
      case   10091:   return   "Network   SubSystem   is   unavailable";   break;     
      case   10092:   return   "WINSOCK   DLL   Version   out   of   range";   break;     
      case   10093:   return   "Successful   WSASTARTUP   not   yet   performed";   break;     
      case   10071:   return   "Too   many   levels   of   remote   in   path";   break;     
      case   11001:   return   "Host   not   found";   break;     
      case   11002:   return   "Non-Authoritative   Host   not   found";   break;     
      case   11003:   return   "Non-Recoverable   errors:   FORMERR,   REFUSED,   NOTIMP";   break;     
      case   11004:   return   "Valid   name,   no   data   record   of   requested   type";   break; 
	  default: return ""; break;
	}


}



	
///////////////////////////////////////////////////////////////////////
//
// 函数名       : RecvFixa
// 功能描述     : 接收指定长度的数据，考虑非阻塞socket的情况
// 参数         : SOCKET socket [in]
// 参数         : char *data [in]
// 参数         : DWORD len  [in]
// 参数         : DWORD *retlen [out]
// 返回值       : bool 
//
///////////////////////////////////////////////////////////////////////
int socketopt::RecvFix(SOCKET socket, char *data, DWORD len)
{
	int retlen = 0;
	int nLeft = 8;
	int nRead = 0;
	char *pBuf = data;
    char err[1024]="";
	string st;
	char s[40];
	nRead = recv(socket, pBuf, nLeft, 0);
    if(nRead == SOCKET_ERROR || nRead == 0)
    {
		strcpy(err,getsockerr(WSAGetLastError()));
		cout<<"sockerr:"<<err<<endl;
		if(WSAEWOULDBLOCK == WSAGetLastError())
		{
		}
		else
	    return nRead;
	 }
	memcpy(s,pBuf,40);
	char seps[]=":"   ;   
	char *token   =NULL;   
	token=strtok(s,seps);   
	while(token!=NULL)   
    {   
		token= strtok(NULL,seps);
		if (token!=NULL)
		{
		nLeft=atoi(token);
		}
		else
		{
			 return -1;
		}
		break;
    }
	nLeft=nLeft+strlen(token)+2;
    nLeft=nLeft-nRead;
	pBuf += nRead;
	retlen += nRead;
	while(nLeft > 0)
	{
		nRead = recv(socket, pBuf, nLeft, 0);
		if(nRead == SOCKET_ERROR || nRead == 0)
		{
		 if(WSAEWOULDBLOCK == WSAGetLastError())
			continue;
			else
		 return nRead;
		 }
		nLeft -= nRead;
		retlen += nRead;
		pBuf += nRead;
   }
  return nRead;
  //
}



///////////////////////////////////////////////////////////////////////
//
// 函数名       : DoRecvData
// 功能描述     : DoRecvCmd 已经获得了指令，接下来就要获得执行指令所需要的数据
// 参数         : vector<SSocketInfo> &vecSockInfo [in]
// 参数         : int idx      [in]                    
// 返回值       : void 
//
///////////////////////////////////////////////////////////////////////
void socketopt::DoRecvData(vector<SSocketInfo> &vecSockInfo, int idx)
{	 
	//exnum++;
	 SSocketInfo *sockInfo = &vecSockInfo[idx];
	 // 为数据分配空间，开始无法确定大少，预分配100k	
	 sockInfo->cmd.DataSize=10240;
	 sockInfo->data = new char[sockInfo->cmd.DataSize + 1];
	 memset(sockInfo->data, 0, sockInfo->cmd.DataSize + 1);
	 
	 // 接收数据
	 int nRet = RecvFix(sockInfo->sock, sockInfo->data, sockInfo->cmd.DataSize);
	 if(nRet == SOCKET_ERROR || nRet == 0)
	 {
		  OutMsg("客户端已退出。");	
		  delete [] sockInfo->data;
		  sockInfo->data=NULL;
		  closesocket(sockInfo->sock);	
		  sockInfo->sock = INVALID_SOCKET;  
		  EraseByIndex(vecSockInfo, idx);
		//  exnum--;
		  return;
	 }
		sockInfo->eCurOp = WaitData;
	//	exnum--;
}

///////////////////////////////////////////////////////////////////////
//
// 函数名       : DoGetdate
// 功能描述     : DoGetdate 获得执行指令所需要的数据
// 参数         : vector<SSocketInfo> &vecSockInfo
// 参数         : int idx
// 返回值       : void 
//
///////////////////////////////////////////////////////////////////////
void socketopt::DoGetKstData(vector<SSocketInfo> &vecSockInfo, int idx)
{
	SSocketInfo *sockInfo = &vecSockInfo[idx];
	char Tdata[10240]="";
	char getdata[10240]="";
	int alllen=0;
	int ret=0;
	memcpy(Tdata,vecSockInfo[idx].data,sizeof(Tdata));
	memcpy(getdata,vecSockInfo[idx].data,sizeof(getdata));
	char seps[]=":"   ;   
	char *token   =NULL;
	char dotype[5]="";
	char logstr[1024]="";
	char rcvquerydata[1024]="";
	token=strtok(Tdata,seps);     
	token= strtok(NULL,seps); //报文长度
	alllen=atoi(token);
	token= strtok(NULL,seps); 
	token= strtok(NULL,seps); //标识码
    token= strtok(NULL,seps); 
	token= strtok(NULL,seps); //交易码查询
	if (token!=NULL)
	{
	strcpy(dotype,token);
	}
	else
	{
	vecSockInfo[idx].eCurOp =ExecCmd;
	strncpy(vecSockInfo[idx].data,rcvquerydata,strlen(vecSockInfo[idx].data));
	}
	
#ifdef ALDDK
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	//爱利得电控
	//  查询
    //////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (strncmp(dotype,"1000",4)==0)
	{   
		Do_Aldwork_Que(getdata,vecSockInfo,idx);
	}
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//电控转帐
	//支付
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (strncmp(dotype,"1001",4)==0)
	{
	  Do_Aldwork_Pay(getdata,vecSockInfo,idx);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//电控转帐
	// 冲正
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (strncmp(dotype,"1002",4)==0)
	{
		Do_Aldwork_Rvs(getdata,vecSockInfo,idx);
	}

#elif YUNZZSJSW

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//云交职上机上网对结
	// 查询

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	if (strncmp(dotype,"1000",4)==0)
		{
			Do_Yzzsjsw_Que(getdata,vecSockInfo,idx);		  
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//云交职上机上网对结
	// 支付
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (strncmp(dotype,"1001",4)==0)
	{
	  Do_Yzzsjsw_Pay(getdata,vecSockInfo,idx);	
	}
	
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//云交职上机上网对结
	// 预支付
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (strncmp(dotype,"1002",4)==0)
	{
		Do_yzzsjsw_Propay(getdata,vecSockInfo,idx);		
	}
	
#elif ANGDSJSW
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//安工大上机上网对接
	// 支付
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if (strncmp(dotype,"1000",4)==0)
	{

		Do_Agdsjsw_Que(getdata,vecSockInfo,idx);	
	}

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//安工大上机上网对接
	// 支付确认
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	if (strncmp(dotype,"1001",4)==0)
	{
		Do_Agdsjsw_Pay(getdata,vecSockInfo,idx);
	}
  
#elif AGDCGDK
	//////////////////////////////////////////////////////////////////////
	//常工电控查寻
	//
	/////////////////////////////////////////////////////////////////////

if (strncmp(dotype,"1000",4)==0)
{
	Do_Agdcgdk_Que(getdata,vecSockInfo,idx);	
}

	
	////////////////////////////////////////////////////////////////////
	//常工电控充值
	//
	///////////////////////////////////////////////////////////////////////

if (strncmp(dotype,"1001",4)==0)
	{
	 Do_Agdcgdk_Pay(getdata,vecSockInfo,idx);
	}
#endif

//Sleep(1000);

}

///////////////////////////////////////////////////////////////////////
//
// 函数名       : DoExecCmd
// 功能描述     : 指令和执行指令所需数据都已经准备好了，接下来就可以执行命令
// 参数         : vector<SSocketInfo> &vecSockInfo
// 参数         : int idx
// 返回值       : void 
//
///////////////////////////////////////////////////////////////////////
void socketopt::DoExecCmd(vector<SSocketInfo> &vecSockInfo, int idx)
{
    SSocketInfo *sockInfo = &vecSockInfo[idx];
	socketopt sock;
	SendFix(sockInfo->sock, sockInfo->data,sockInfo->cmd.DataSize);
 
 // 执行完命令后就设置回接收指令状态
	memset(sockInfo->data,0,sizeof sockInfo->data);
	sockInfo->eCurOp = RecvData;
}

///////////////////////////////////////////////////////////////////////
//
// 函数名       : SendFix
// 功能描述     : 发送指定长度的数据，考虑非阻塞socket的情况
// 参数         : SOCKET socket
// 参数         : char *data
// 参数         : DWORD len
// 参数         : DWORD *retlen
// 返回值       : bool 
//
///////////////////////////////////////////////////////////////////////
int socketopt::SendFix(SOCKET socket, char *data, DWORD len)
{
 int retlen = 0;
 int nLeft = len;
 int nWritten = 0;
 const char *pBuf = data;
 while(nLeft > 0)
 {
	  nWritten = send(socket, pBuf, nLeft, 0);
	  if(nWritten == SOCKET_ERROR || nWritten == 0)
	  {
	   if(WSAEWOULDBLOCK == WSAGetLastError())
		continue;
	   else
		return nWritten;
	  } 
	  nLeft -= nWritten;
	  retlen += nWritten;
	  pBuf += nWritten;
 }
 return nWritten;
}




