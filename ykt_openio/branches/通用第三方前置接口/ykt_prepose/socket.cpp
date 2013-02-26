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
// ������       : RemoveByIndex
// ��������     : ���� index ��ɾ�� VECTOR ���Ԫ��
// ����         : vector<T> &vec [in]
// ����         : int nIdx   [in]
// ����ֵ       : void 
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
// ������       : RecvFixa
// ��������     : ����ָ�����ȵ����ݣ����Ƿ�����socket�����
// ����         : SOCKET socket [in]
// ����         : char *data [in]
// ����         : DWORD len  [in]
// ����         : DWORD *retlen [out]
// ����ֵ       : bool 
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
// ������       : DoRecvData
// ��������     : DoRecvCmd �Ѿ������ָ���������Ҫ���ִ��ָ������Ҫ������
// ����         : vector<SSocketInfo> &vecSockInfo [in]
// ����         : int idx      [in]                    
// ����ֵ       : void 
//
///////////////////////////////////////////////////////////////////////
void socketopt::DoRecvData(vector<SSocketInfo> &vecSockInfo, int idx)
{	 
	//exnum++;
	 SSocketInfo *sockInfo = &vecSockInfo[idx];
	 // Ϊ���ݷ���ռ䣬��ʼ�޷�ȷ�����٣�Ԥ����100k	
	 sockInfo->cmd.DataSize=10240;
	 sockInfo->data = new char[sockInfo->cmd.DataSize + 1];
	 memset(sockInfo->data, 0, sockInfo->cmd.DataSize + 1);
	 
	 // ��������
	 int nRet = RecvFix(sockInfo->sock, sockInfo->data, sockInfo->cmd.DataSize);
	 if(nRet == SOCKET_ERROR || nRet == 0)
	 {
		  OutMsg("�ͻ������˳���");	
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
// ������       : DoGetdate
// ��������     : DoGetdate ���ִ��ָ������Ҫ������
// ����         : vector<SSocketInfo> &vecSockInfo
// ����         : int idx
// ����ֵ       : void 
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
	token= strtok(NULL,seps); //���ĳ���
	alllen=atoi(token);
	token= strtok(NULL,seps); 
	token= strtok(NULL,seps); //��ʶ��
    token= strtok(NULL,seps); 
	token= strtok(NULL,seps); //�������ѯ
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
	//�����õ��
	//  ��ѯ
    //////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (strncmp(dotype,"1000",4)==0)
	{   
		Do_Aldwork_Que(getdata,vecSockInfo,idx);
	}
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���ת��
	//֧��
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if (strncmp(dotype,"1001",4)==0)
	{
	  Do_Aldwork_Pay(getdata,vecSockInfo,idx);
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//���ת��
	// ����
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (strncmp(dotype,"1002",4)==0)
	{
		Do_Aldwork_Rvs(getdata,vecSockInfo,idx);
	}

#elif YUNZZSJSW

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�ƽ�ְ�ϻ������Խ�
	// ��ѯ

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
	if (strncmp(dotype,"1000",4)==0)
		{
			Do_Yzzsjsw_Que(getdata,vecSockInfo,idx);		  
		}
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�ƽ�ְ�ϻ������Խ�
	// ֧��
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (strncmp(dotype,"1001",4)==0)
	{
	  Do_Yzzsjsw_Pay(getdata,vecSockInfo,idx);	
	}
	
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�ƽ�ְ�ϻ������Խ�
	// Ԥ֧��
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	if (strncmp(dotype,"1002",4)==0)
	{
		Do_yzzsjsw_Propay(getdata,vecSockInfo,idx);		
	}
	
#elif ANGDSJSW
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�������ϻ������Խ�
	// ֧��
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if (strncmp(dotype,"1000",4)==0)
	{

		Do_Agdsjsw_Que(getdata,vecSockInfo,idx);	
	}

  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//�������ϻ������Խ�
	// ֧��ȷ��
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	
	if (strncmp(dotype,"1001",4)==0)
	{
		Do_Agdsjsw_Pay(getdata,vecSockInfo,idx);
	}
  
#elif AGDCGDK
	//////////////////////////////////////////////////////////////////////
	//������ز�Ѱ
	//
	/////////////////////////////////////////////////////////////////////

if (strncmp(dotype,"1000",4)==0)
{
	Do_Agdcgdk_Que(getdata,vecSockInfo,idx);	
}

	
	////////////////////////////////////////////////////////////////////
	//������س�ֵ
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
// ������       : DoExecCmd
// ��������     : ָ���ִ��ָ���������ݶ��Ѿ�׼�����ˣ��������Ϳ���ִ������
// ����         : vector<SSocketInfo> &vecSockInfo
// ����         : int idx
// ����ֵ       : void 
//
///////////////////////////////////////////////////////////////////////
void socketopt::DoExecCmd(vector<SSocketInfo> &vecSockInfo, int idx)
{
    SSocketInfo *sockInfo = &vecSockInfo[idx];
	socketopt sock;
	SendFix(sockInfo->sock, sockInfo->data,sockInfo->cmd.DataSize);
 
 // ִ�������������ûؽ���ָ��״̬
	memset(sockInfo->data,0,sizeof sockInfo->data);
	sockInfo->eCurOp = RecvData;
}

///////////////////////////////////////////////////////////////////////
//
// ������       : SendFix
// ��������     : ����ָ�����ȵ����ݣ����Ƿ�����socket�����
// ����         : SOCKET socket
// ����         : char *data
// ����         : DWORD len
// ����         : DWORD *retlen
// ����ֵ       : bool 
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




