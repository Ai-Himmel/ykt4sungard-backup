// ykt_prepose.cpp : �������̨Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "socket.h" 
#include "readfile.h"
#include "Data.h"
#include "writelog.h"
#include "dump.h"
vector<SSocketInfo> vecSocketInfo;
 CRITICAL_SECTION g_cs;//
// �����˳�������
bool g_bExit = false;
char remotehost[21]="";		//�Է�������ip
int port=0;
int remoteport=0;
int connsqlsign=1;
char httppath[256]="";
char managerId[200] = "";
char managerPass[200] = "";
char school[200]="";
char	g_sCommRec[256];
char	m_CurPath[256];
char  localip[256];
char  runpath[256]="";
char Connectstr[512];
bool diabwork=false;
int exnum=0;
HANDLE hSemaphore;
_ConnectionPtr m_pConnection;
_RecordsetPtr pPtr;
CMyLog		  m_CLog;	
typedef char * (__stdcall *fCommand)(char *, char *, char *, int, char *);
typedef char * (__stdcall *fInit)();
extern HINSTANCE hinstLib = NULL;
void DoWorkThred(void *num); 
extern char * sendnetpay(char *sendstr);
struct Foo 
{ 
Foo() { cout << "before main" << endl;} 
~Foo() 
{
	//m_pConnection.Release();
	// pPtr.Release();
	cout << "after main" << endl;
} 
}; 

Foo smallFoo; 

char * sendnetpay(char *sendstr)
{
	char * str ="";
	char logstr[1024]="";
	fCommand command;
 if (hinstLib != NULL) {
            /*Ѱ��fCommand�ӿڵĵ�ַ*/
            command = (fCommand) GetProcAddress(hinstLib, "fCommandTS");        
            if (NULL != command) {
				/*����fCommand�ӿڷ�����������*/ 
				strcat(logstr,"�û�����");
				strcat(logstr,managerId);
				strcat(logstr,"  ���룺");
				strcat(logstr,managerPass);
				strcat(logstr,"  ip��");
				strcat(logstr,remotehost);
				strcat(logstr,"  ���ݣ�");
				strcat(logstr,sendstr);
				WriteLog(logstr);
                str = (command) (managerId, managerPass, remotehost, remoteport, sendstr);  
			}
   }
	return str;
}

void DoWorkThred(void *num)
{ 
	void *n=num;
    printf("Thread %d is executing.....\n",num);
	int ret=0;
	socketopt sock;
	char log[1024]="";
	char ss[30]="";
	while(!g_bExit)
	{
		  if (diabwork)
				{
					Sleep(1000);
					continue;
				}
		try
		{     
				for(int i = 0; i < vecSocketInfo.size(); i++)
				{   
				  
					if (vecSocketInfo.size()<=0)
						break;
					if ((vecSocketInfo[i].ThreadNo==0)||(vecSocketInfo[i].ThreadNo==(int)num) )
					{
						//��ֹ�߳�ͬʱִ��ͬһip������������
						if (vecSocketInfo[i].ThreadNo==0)
						{
							
							if (vecSocketInfo[i].ThreadNo==0)
							{
							vecSocketInfo[i].ThreadNo=(int)num;
							}
							
						}
						if  (vecSocketInfo[i].eCurOp==WaitData)
						{  
							vecSocketInfo[i].eCurOp==Working;
							WriteLog("ִ�й�����");
							exnum++;
							sock.DoGetKstData(vecSocketInfo,i) ;
							exnum--;
							break;
						}
					 }

				}
				
				Sleep(1000);
		}
		 catch (exception& e)
		{
			cout << "Standard exception: " << e.what() << endl;
		}

	 }
	printf("Thread is exit.....\n");
	_endthread();

}


void WriteLog( char* msg)
{
    char mcPath[256];
	char sCurPath[256];
	CData			 cData;
	memset(sCurPath,0,sizeof sCurPath);
	strcpy(sCurPath,cData.GetCurPath());
	memset(mcPath,0,sizeof mcPath);
	strcpy(mcPath,sCurPath);
	if( !strlen(msg) ) return ;	
	strcat(mcPath,"\\Sys");
	m_CLog.WriteSysLog(mcPath,msg);
}
void Writedata( char* filename, char* msg)
{
    char mcPath[256];
	char sCurPath[256];
	CData			 cData;
	memset(sCurPath,0,sizeof sCurPath);
	strcpy(sCurPath,cData.GetCurPath());
	memset(mcPath,0,sizeof mcPath);
	strcpy(mcPath,sCurPath);
	if( !strlen(msg) ) return ;	
	strcat(mcPath,"\\data");
	m_CLog.Writedata(mcPath,filename,msg);
}

void Readdata( char* filename, char* msg)
{
    char mcPath[256];
	char sCurPath[256];
	CData			 cData;
	memset(sCurPath,0,sizeof sCurPath);
	strcpy(sCurPath,cData.GetCurPath());
	memset(mcPath,0,sizeof mcPath);
	strcpy(mcPath,sCurPath);
	strcat(mcPath,"\\data");
	m_CLog.readdata(mcPath,filename,msg);
}

void Deledata( char* filename)
{
    char mcPath[256];
	char sCurPath[256];
	CData			 cData;
	memset(sCurPath,0,sizeof sCurPath);
	strcpy(sCurPath,cData.GetCurPath());
	memset(mcPath,0,sizeof mcPath);
	strcpy(mcPath,sCurPath);
	if( !strlen(filename) ) return ;	
	strcat(mcPath,"\\data");
	m_CLog.deldata(mcPath,filename);
}

///////////////////////////////////////////////////////////////////////
//
// ������       : BindServer
// ��������     : �󶨶˿�
// ����         : int nPort
// ����ֵ       : SOCKET 
//
///////////////////////////////////////////////////////////////////////
SOCKET BindServer(int nPort)
{
	int ret=0;
	 // ����socket 

	// ��ʼ��WINSOCK
	 WSADATA wsd;
	 if( WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
	 {
	   cout <<  "Winsock��ʼ��ʧ��" << endl;
	   return -1 ;
	 }
	 SOCKET sServer = socket(AF_INET, SOCK_STREAM, 0);
	 // �󶨶˿�
	 struct sockaddr_in servAddr;
	 servAddr.sin_family = AF_INET;
	 servAddr.sin_port = htons(nPort);
	 servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	 ret=bind(sServer, (struct sockaddr *)&servAddr, sizeof(servAddr));
	if (ret)
	 {
		 printf("bing failed\n%d\n",WSAGetLastError);
		 WriteLog("bind Failed!");
		 OutErr("bind Failed!");
		 return NULL;
	 }

	 // ���ü�������Ϊ200
	 if(listen(sServer, 200) != 0)
	 {
	  OutErr("listen Failed!");
	  return NULL;
	 }
	 return sServer;
}
///////////////////////////////////////////////////////////////////////
//
// ������       : AcceptClient
// ��������     : 
// ����         : SOCKET sServer [in]
// ����         : LPSTR lpszIP  [out] ���ؿͻ��˵�IP��ַ 
// ����ֵ       : SOCKET   [out] ���ؿͻ��˵�socket
//
///////////////////////////////////////////////////////////////////////
SOCKET AcceptClient(SOCKET sListen, LPSTR lpszIP)
{
	 struct sockaddr_in cliAddrTmp;
	 int cliAddrSize = sizeof(struct sockaddr_in);
	 SOCKET sClient = accept(sListen, (struct sockaddr *)&cliAddrTmp, &cliAddrSize);
	 if(sClient == INVALID_SOCKET)
	 {
	  OutErr("accept failed!");
	  return NULL;
	 }
	 sprintf(lpszIP, "%s", inet_ntoa(cliAddrTmp.sin_addr));
	 return sClient;
}
int _tmain(int argc, _TCHAR* argv[])
{
	int ret=0;
	char		buf[512];
	char logstr[1024]="";
	CData		mData;
 	FileBase	mfile;
	int totalnum=0;
	try
	{
//	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);
	fInit init;
    //service ip
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","localip",buf);
	mData.trim(buf);
	strcpy(localip,buf);
    memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","runpath",buf);
	mData.trim(buf);
	strcpy(runpath,buf);
	
	//service port
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","port",buf);
	mData.trim(buf);
	port=atol(buf);
    //remorte ip
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","remotehost",buf);
	mData.trim(buf);
	strcpy(remotehost,buf);
	//http
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","http",buf);
	mData.trim(buf);
	strcpy(httppath,buf);
	//Connectstr
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","Connectstr",buf);
	mData.trim(buf);
	strcpy(Connectstr,buf);
	//useid
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","managerId",buf);
	mData.trim(buf);
	strcpy(managerId,buf);
	//passwd
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","managerPass",buf);
	mData.trim(buf);
	strcpy(managerPass,buf);
	//school
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","school",buf);
	mData.trim(buf);
	strcpy(school,buf);
	//remorte port
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","remoteport",buf);
	mData.trim(buf);
	remoteport=atol(buf);
	//total thread
	memset(buf,0,sizeof buf);
	mfile.GetProfileStr("system.ini","service","totalnum",buf);
	mData.trim(buf);
	totalnum=atol(buf);
#ifdef YUNZZSJSW
	//load dll
	//*******************************************************
	  //  �ƽ�ְ�ϻ�����
	//*******************************************************
	hinstLib = LoadLibrary("samspiclient");
	if (hinstLib != NULL) 
	{
		//�����߳��е���fInit�������г�ʼ��
		init = (fInit) GetProcAddress(hinstLib, "fInit");
		if (init != NULL) 
		{
			(init) ();
		}
		else
		{
		return 0;
		}
	}
#endif	

	socketopt sock;
	InitializeCriticalSection(&g_cs);
	SOCKET sockListen =BindServer(port);
	ULONG NonBlock = 1;
	ret=ioctlsocket(sockListen, FIONBIO, &NonBlock);
	SOCKET sockClient;
	FD_SET fdRead;
	FD_SET fdWrite;
	_bstr_t connnect=Connectstr;
	 for(int i=1;i<=totalnum;i++)
	 {
		_beginthread(DoWorkThred,0,(void *) i);
	  }


	 while(!g_bExit)
	{
		if (diabwork)
		{
			Sleep(1000);
			continue;
		}

#ifdef AGDCGDK
		        ::CoInitialize(NULL);///��ʼ��COM��
				if (connsqlsign==1)
				{
						ret=m_pConnection.CreateInstance("ADODB.Connection");//����ʵ������HRESULT �������ifһ�¿����ɹ���
				if (ret)
				{
					WriteLog("Create Instance failed!");
					return -1;
				}
   				if (FAILED(pPtr.CreateInstance("ADODB.Recordset")))
				{
					WriteLog("Create Instance failed!");
					return -1;
				}
		
				m_pConnection->ConnectionString=Connectstr;
				try
				{    
						printf("�����������ݿ�.....\n");
						if (FAILED(m_pConnection->Open(connnect,"","",-1)))
						{ 
							WriteLog("�޷��������ݿ⣡");
						}
						else
						{
							connsqlsign=0;
							WriteLog("�������ݿ�ɹ���");
							printf("�������ݿ�ɹ�.....\n");
							
						}
						m_pConnection->Close();
						m_pConnection->Release();
				}
				catch(_com_error e)
				{
					printf("���ݿ������쳣.....\n");
					WriteLog("���ݿ������쳣��");
					
				}
		}


#endif
		 // ÿ�ε���select֮ǰ��Ҫ�Ѷ�����д�����
		 FD_ZERO(&fdRead);
	     FD_ZERO(&fdWrite);
  
		// ���úö�����д��
		 FD_SET(sockListen, &fdRead);
		
		 for(size_t i = 0; i < vecSocketInfo.size(); i++)
		 {
			 if (diabwork)
			{
				Sleep(1000);
				continue;
			}
			
			if (vecSocketInfo.size()<=0)
			break;
	
			FD_SET(vecSocketInfo[i].sock, &fdRead);
			FD_SET(vecSocketInfo[i].sock, &fdWrite);
			
		 }
         
		// ����select����
		  ret=(select(0, &fdRead, &fdWrite, NULL, NULL) == SOCKET_ERROR);
		  if (ret)
		  {
			  printf("bing failed\n%d\n",WSAGetLastError);
			  OutErr("select() Failed!  û�пɽ������ݣ�");
				  cout<<"û�пɽ������ݣ�"<<endl;
			  Sleep(1000);
			  continue; 
		  }

		 // ˵�����Խ���������
		 if(FD_ISSET(sockListen, &fdRead))
		 {
			 char szClientIP[50];
			 sockClient = AcceptClient(sockListen, szClientIP);
			 cout <<  " �����Ͽͻ�IP:"<<szClientIP<< endl;
			 ioctlsocket(sockClient, FIONBIO, &NonBlock);
			 SSocketInfo sockInfo;
			 sockInfo.sock = sockClient;
			 sockInfo.cmd.DataSize=0;
			 sockInfo.eCurOp =RecvData;
			 sockInfo.ThreadNo=0;
			 // �ѽ��յ������socket�����Լ��Ķ�����
			 EnterCriticalSection(&g_cs);	
			 vecSocketInfo.push_back(sockInfo);
			 LeaveCriticalSection(&g_cs);
        }
         
		for(size_t i = 0; i < vecSocketInfo.size(); i++)
		{
		
			if (diabwork)
		{
			Sleep(1000);
			continue;
		}
			 if (vecSocketInfo.size()<=0)
				break;
		// ����ɶ�
			 if(FD_ISSET(vecSocketInfo[i].sock, &fdRead))
				{
				 switch(vecSocketInfo[i].eCurOp)
				  {
						 case RecvData:
						{	
							 WriteLog("�������ݣ�");
							// exnum=exnum+1;
							 sock.DoRecvData(vecSocketInfo, (int)i);
							// exnum=exnum-1;
			   				
						}
						default:
						break;
					}
				}
    			if (vecSocketInfo.size()<=0)
				break;
				 // �����д
				 if(FD_ISSET(vecSocketInfo[i].sock, &fdWrite))
				 {
					switch(vecSocketInfo[i].eCurOp)
					 {
						case ExecCmd:
							{  	
							WriteLog("ִ�����ݣ�");
							exnum++;
							sock.DoExecCmd(vecSocketInfo, (int)i);
							exnum--;
							vecSocketInfo[i].ThreadNo=0;		
							}
						default:
						break;
					 }
				 }
		}
		
	}

     DeleteCriticalSection(&g_cs);
	 WSACleanup();
#ifdef AGDCGDK
	 m_pConnection.Release();
	 pPtr.Release();
#endif




			}
			  catch (exception& e)//������bug
				  {
					   strcpy(logstr,e.what());
						WriteLog(logstr);
				  } 




	return 0;
}

