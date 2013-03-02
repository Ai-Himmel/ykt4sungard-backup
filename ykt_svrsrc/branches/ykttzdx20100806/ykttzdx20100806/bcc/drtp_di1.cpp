/********************************************************************
	created:	2003/09/27
	created:	27:9:2003   15:33
	filename: 	E:\linux\ksappsvr\drtp_di1.cpp
	file path:	E:\linux\ksappsvr
	file base:	drtp_di1
	file ext:	cpp
	author:		������
	
	purpose:	����ԭ����ͨѶƽ̨�汾�Ľӿڣ����뼯�н��׼��ݵİ汾
            20040420: �޸�bByteReverse��trueʱ�򣬶�CRC������жϵĴ���
*********************************************************************/
#include "stdafx.h"
#include "comstru.h"
#include "mutex.h"
#include "tcp.h"

/* ****** Updated by CHENYH at 2003-10-27 16:41:00 ****** 
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <netinet/in.h> 
#include <arpa/inet.h> 
#include <sys/select.h>
#include <sys/time.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ipc.h>
#include <pthread.h>
*/

#include "drtp_di.h"

bool bByteReverse = false;

enum DRTPERRORS 
{
};

const char *szDRTPErrors[]=
{
   "û���㹻����Դ��������!\tNo enough resource to build connection!",
   "��������Ӿ��Ϊ��!\tInput link handle is null!",
   "û����Ҫע��Ĺ��ܺţ����ܽ�����������!",
   "ͨѶ��������̫��������ʧ��!",
   ""
};

void CopyString(const char *source,char *dest,int destsize)
{
   int i;
   if (dest==NULL||destsize<=1||source==NULL)
      return;
   for (i=0;i<destsize-1;i++)
   {
      if (source[i]=='\0') break;
      dest[i]=source[i];
   }
   dest[i]='\0';
}

void reverse(void *data,int len)
{
   unsigned char *p=(unsigned char *)data;
   unsigned char buf[16];
   int i;
   
   memcpy(buf,data,len);
   for (i=0;i<len;i++)
   {
      p[i]=buf[len-i-1];
   }
}

unsigned int CRC(void *pData, long DataLen)
{
	unsigned short acc = 0, i;
	unsigned char* Data = (unsigned char*) pData;
	while(DataLen--)
	{
		acc = acc ^ (*Data++ << 8);
		for(i = 0; i++ < 8; )
			if(acc & 0x8000)
				acc = (acc << 1) ^ 0x1021;
			else
				acc <<= 1;
	}

	// Swap High and Low byte
	i = ( (unsigned short) ( ((unsigned char)acc) << 8) ) | ((unsigned short)(acc >> 8));

	return i;
}

void ReverseSysHead(SYS_HEAD *phead)
{
   int i;
   reverse(&(phead->Function),sizeof(phead->Function));
   reverse(&(phead->DestNo),sizeof(phead->DestNo));
   reverse(&(phead->UserDataRealSize),sizeof(phead->UserDataRealSize));
   reverse(&(phead->UserDataSize),sizeof(phead->UserDataSize));
   reverse(&(phead->LastConnectTime),sizeof(phead->LastConnectTime));
   for (i=0;i<MAXROUTERCOUNT;i++)
   {
      reverse(phead->RouterIn+i,sizeof(phead->RouterIn[0]));
      reverse(phead->RouterOut+i,sizeof(phead->RouterOut[0]));
   }
   // reverse(&(phead->CRC),sizeof(phead->CRC));  ��һ��Ҫ�ڴ˺�Ÿ�ֵ
}


// ������: DRTPInitialize
// ���  : ������ 2003-9-27 15:53:46
// ����  : ͨѶƽ̨�ĳ�ʼ��
// ����  : bool 
// ����  : int nrouters
bool DRTPInitialize(int nrouters)
{
   bByteReverse = (htons(1)==1);
   return(true);
}


// ������: DRTPUninitialize
// ���  : ������ 2003-9-27 16:02:33
// ����  : ����ͨѶƽ̨�ӿڵ�ʹ��
// ����  : void 
void DRTPUninitialize()
{
}

CDRTPClient::CDRTPClient()
{
   classdataid = DRTPCLIENTID;
}

CDRTPClient::~CDRTPClient()
{
   Close();
}


bool CDRTPClient::Connect(char *routerip, int port, char *szMsg, int nMsgSize)
{
   int trys;
   char buf[1024];
   CPMUTEX amutex(&m_mutex);
   for (trys=0;trys<3;trys++)
   {
      if (m_socket.ConnectTcp(routerip,(short)port))
         break;
   }
   if (trys>=3)
   {
      sprintf(buf,"������ͨѶƽ̨������<%s> �˿�<%d>��������!",routerip,port);
      CopyString(buf,szMsg,nMsgSize);
      m_socket.Close();
      return(false);
   }
   sprintf(buf,"��ͨѶƽ̨������<%s> �˿�<%d>��������!",routerip,port);
   CopyString(buf,szMsg,nMsgSize);
   return(true);
}

bool CDRTPClient::Close()
{
//   CPMUTEX amutex(&m_mutex);
   m_socket.Close();
   return(true);
}

bool CDRTPClient::Send(unsigned short branchno, unsigned short function, void *senddata, int senddatalen, char *szMsg, int nMsgSize, bool bDesign)
{
   SYS_HEAD head;
   int rtn;
   char buf[1024];

   CPMUTEX amutex(&m_mutex);
   memset(&head,0,sizeof(SYS_HEAD));
   if (bDesign && (m_recvhead.MessageType==6))
   {
      memcpy(&head,&m_recvhead,sizeof(head));
      head.RouterDesignate = 1;
   }
   head.Ver = 2;
   head.CompressFlag = 0;
   head.DestNo = branchno;
   head.Function = function;
   head.FunctionPriority = 2;
   head.MessageType = 5;
   head.UserDataRealSize = head.UserDataSize = senddatalen;
   rtn = sendpack(&head,senddata,senddatalen);
   if (rtn<=0)
   {
      CopyString("���ݷ���ʧ�ܣ��������Ѿ����ر�!",szMsg,nMsgSize);
      return(false);
   }
   else
   {
      sprintf(buf,"���ݷ��ͳɹ���ʵ�ʳ���:%d",rtn);
      CopyString(buf,szMsg,nMsgSize);
      return(true);
   }
}


// ������: CDRTPClient::Receive
// ���  : ������ 2003-9-30 15:34:15
// ����  : ͨѶ�ͻ��˵ȴ�����������Ӧ������
// ����  : int 
/*
            <0 ���մ���
            -100: �յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! Ӧ�ý���ͨѶ����ͷ����%d>ʵ�ʳ���%d!
            -99:  �յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! ͨѶ��ͷ���ݸ�ʽ�Ƿ�
            -98:  �������ݵĻ��峤��(%d)���㣬�������ݰ�����Ϊ:(%d)���رձ����ӣ�������ͨѶƽ̨��������!
            -90:  ���յ�ϵͳ��ͷ����޶�ʱ��(%u)��ղ���ʵ�ʵ�Ӧ�����ݰ�(ʵ���յ�%d<��Ҫ���ݳ���%u)

            ����<0: 
               ֹͣ���գ��������Ѿ����ر�!;
               ͨѶ�ӿ��ڵȴ���������ʱ�����%d-%s!
               ͨѶ�ӿ��ڽ�������ʱ�����%d-%s!
               ͨѶ�ӿ��ڵȴ���������ʱ,ͨѶ�ӿڱ��Է��ر�%d-%s!


            =0:   ���szMsg��Ϣ�������������޷��ʹ�Ŀ���ַ�����յ�һ��û�а����Ӧ�����ݰ�
            >0:   OK, �յ�Ӧ�����ݰ�������Ϊ%d
*/
// ����  : void *recvbuf
// ����  : int recvbufsize
// ����  : char *szMsg
// ����  : int nMsgSize
// ����  : int wtime
int CDRTPClient::Receive(void *recvbuf, int &recvbufsize, char *szMsg, int nMsgSize, int wtime)
{
   int rtn;
   char buf[1024];
   unsigned int crc,crc1;
   SYS_HEAD *phead;
   char *pb;
   if (m_socket.IsFree())
   {
      CopyString("ֹͣ���գ��������Ѿ����ر�!",szMsg,nMsgSize);
      return(-1);
   }


   phead = (SYS_HEAD *)buf;
   memset(recvbuf,0,recvbufsize);
   while (1)
   {
      rtn = m_socket.Recv((char *)phead,sizeof(SYS_HEAD),wtime);
      if (rtn<=0)
      {
         // =0: û�����ݣ�<0:ͨѶ�˿��������ˣ���Ҫ��������
         recvbufsize = 0;
         if (rtn==0)
         {
            CopyString("��ָ����ʱ���û���յ����ݣ�",szMsg,nMsgSize);
         }
         else
         {
            CopyString("�����ӳ���ϵͳ�Զ��ر�������!",szMsg,nMsgSize);
         }
         return(rtn); 
      }
      if (rtn<(int)sizeof(SYS_HEAD))
      {
         // �յ����ݶβ��㣬Ӧ����ͬ�����⣬���ǹر���������Ӷ˿�
         sprintf(buf,"�յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! Ӧ�ý���ͨѶ����ͷ����%d>ʵ�ʳ���%d!",
            sizeof(SYS_HEAD),rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(-100);
      }
      // �Ƿ�ͨ�����CRC���ж��Ƿ�Ϊ��ȷ��SYS_HEAD?
      crc = phead->CRC;
      phead->CRC = 0;
      crc1 = CRC(phead,sizeof(SYS_HEAD));
      if (bByteReverse)
      {
         reverse(&crc,sizeof(crc));
      }
      if (crc1!=crc || phead->Ver!=2)
      {
         sprintf(buf,"�յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! ͨѶ��ͷ���ݸ�ʽ�Ƿ�");
         CopyString(buf,szMsg,nMsgSize);
         return(-99);
      }
      phead->CRC = crc;
      if (bByteReverse)
      {
         // ���ڷ�x86��CPU: ��Ҫת��Ϊ�����ɱ��ϵĸ�ʽ big-endian �͵�ַ���λ�ֽ�
         ReverseSysHead(phead);
      }
      if (recvbufsize<phead->UserDataSize)
      {
         // ���ڽ��ջ��岻����ֻ�йرձ����ӣ���������е����ݣ���������ͨѶƽ̨
         // ����������ԭ����ɵģ�
         /*
         1. ���ջ��峤�Ȳ��㣻�����ڳ����
         2. ���յ��������ݲ���ȷ��
         3. �����еĽ��ջ��������ݲ�ͬ������Ҫreset��ͨѶƽ̨���ӣ�
         */
         sprintf(buf,"�������ݵĻ��峤��(%d)���㣬�������ݰ�����Ϊ:(%d)���رձ����ӣ�������ͨѶƽ̨��������!",
            recvbufsize,phead->UserDataSize);
         CopyString(buf,szMsg,nMsgSize);
         return(-98);
      }
      if (phead->UserDataSize<=0)
      {
         // Ӧ�������ڲ��������ݣ�������Ӧ������
         rtn = 0;
      }
      else
      {
         rtn = m_socket.Recv((char *)recvbuf,phead->UserDataSize,1000); // Ҫ����1�����ڽ��յ�����������
         if (rtn<0)
         {
            return(rtn);
         }
         else if (rtn!=phead->UserDataSize)
         {
            // ͨѶ���������⣬���ǹرձ��������ˣ�������ͨѶƽ̨���Ӱ�
            sprintf(buf,"���յ�ϵͳ��ͷ����޶�ʱ��(%u)��ղ���ʵ�ʵ�Ӧ�����ݰ�(ʵ���յ�%d<��Ҫ���ݳ���%u)",
               wtime,rtn,phead->UserDataSize);
            CopyString(buf,szMsg,nMsgSize);
            return(-90);
         }
      }
      switch (phead->MessageType)
      {
      case 10:
         phead->MessageType = 11;
         phead->UserDataRealSize = phead->UserDataSize = 0;
         sendpack(phead,NULL,0);
         break;
      case 5:  // ��Ӧ��Ϊ�����
      case 6:  // Ӧ��Ϊ6  2003-10-13 added
         recvbufsize = rtn;
         memcpy(&m_recvhead,phead,sizeof(SYS_HEAD));
         sprintf(buf,"�յ�Ӧ�����ݰ�������Ϊ%d",rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(rtn);
      case 12:  // ����֪ͨ��Ϣ��
         //"���ݰ�·��·��̫��");
         //"Ӧ����ע��");
         //"�����쳣,Ŀ���ַ���ɵ���");
         //"·����ע��");
         //"Ӧ�÷�����δע���Ŀ�������޷�����");
         pb = (char *)recvbuf;
         pb[rtn] = '\0';
         recvbufsize = rtn;
         CopyString(pb,szMsg,nMsgSize);
         return(0);  // �޷��ִ������
      }
   }
}




int CDRTPClient::sendpack(SYS_HEAD *phead, void *vdata, int datalen)
{
   int len;
   char *data = (char *)vdata;
   char buf[MAXDATASIZE+100];
   phead->Ver = 2;
   phead->CompressFlag = 0;
   phead->CRC = 0;
   if (data==NULL) 
      datalen = 0;
   phead->UserDataRealSize = phead->UserDataSize = datalen;
   if (bByteReverse)
   {
      // ���ڷ�x86��CPU: big-endian
      ReverseSysHead(phead);
   }
   phead->CRC = CRC(phead,sizeof(SYS_HEAD));
   if (bByteReverse)
   {
      reverse(&(phead->CRC),sizeof(phead->CRC));
   }

   memcpy(buf,phead,sizeof(SYS_HEAD));
   memcpy(buf+sizeof(SYS_HEAD),vdata,datalen);
   len = sizeof(SYS_HEAD)+datalen;
   datalen = m_socket.Send(buf,len);

/* ****** Updated by CHENYH at 2004-2-12 23:10:30 ****** 
   if (datalen<len)
   {
      // Send Error: -1:��·û���������������رգ�-2:��������ʱ��������رգ�
   }
*/
   return(datalen);
}




////////////////////////////////////////////////////////////////////////////////////////////////
CDRTPServer::CDRTPServer()
{
   classdataid = DRTPSERVERID;
   m_recvnullcounts = 0;
   m_mainfuncno = 0;
}

CDRTPServer::~CDRTPServer()
{
}

bool CDRTPServer::Connect(char *routerip, int port, int funcount, unsigned short *functions, char *szMsg, int nMsgSize)
{
   char buf[1024];
   int trys,i;
   unsigned short *pword;
   SYS_HEAD head;
   CPMUTEX amutex(&m_mutex);
   if (funcount<1) 
   {
      CopyString(szDRTPErrors[2],szMsg,nMsgSize);
      return(false);
   }
   for (trys=0;trys<3;trys++)
   {
      if (m_socket.ConnectTcp(routerip,(short)port+2))
         break;
   }
   if (trys>=3)
   {
      sprintf(buf,"������ͨѶƽ̨������<%s> �˿�<%d>��������!",routerip,port);
      CopyString(buf,szMsg,nMsgSize);
      m_socket.Close();
      return(false);
   }
   
   memset(&head,0,sizeof(head));
   head.Ver=2;
   head.MessageType=1;
   head.CompressFlag=0;

   pword = (unsigned short *)buf;
   pword[0] = (unsigned short)funcount;
   for (i=0;i<funcount;i++)
   {
      pword[i+1]=functions[i];
   }

   if (bByteReverse)
   {
      // Not x86:
      reverse(pword,sizeof(unsigned short));
      for (i=0;i<funcount;i++)
      {
         reverse(pword+i+1,sizeof(unsigned short));
      }
   }

   i = sendpack(&head,buf,sizeof(unsigned short)*(funcount+1));
   if (i<=0)
   {
      CopyString("����ע��ʧ��(����ע�Ṧ��ʧ��)!",szMsg,nMsgSize);
      return(false);
   }

   m_recvnullcounts = 0;
   m_mainfuncno = functions[0];
   return (true);  
}

bool CDRTPServer::Close()
{
//   CPMUTEX amutex(&m_mutex);
   m_socket.Close();
   return(true);
}

bool CDRTPServer::Send(SYS_HEAD *pHead, void *senddata, int senddatalen, char *szMsg, int nMsgSize)
{
   char buf[1024];
   CPMUTEX amutex(&m_mutex);
   int rtn;
   if (m_socket.IsFree())
   {
      CopyString("ֹͣ���ͣ��������Ѿ����ر�!",szMsg,nMsgSize);
      return(false);
   }
   if (pHead->MessageType==5)
      pHead->MessageType = 6;
   rtn = sendpack(pHead,senddata,senddatalen);
   if (rtn<=0)
   {
      CopyString("���ݷ���ʧ�ܣ��������Ѿ����ر�!",szMsg,nMsgSize);
      return(false);
   }
   else
   {
      sprintf(buf,"���ݷ��ͳɹ���ʵ�ʳ���:%d",rtn);
      CopyString(buf,szMsg,nMsgSize);
      return(true);
   }
}


// ������: CDRTPServer::Receive
// ���  : ������ 2003-9-29 22:35:31
// ����  : ���޶���ʱ����wtime(����)������ͨѶƽ̨Э�飬����Ӧ�����ݵ�ͷ�;�����������
// ����  : int 
/*
            <-1: ������Ҫ�رձ����ӣ����½�������
               -300  ͨѶƽ̨���ϣ�����5���������ԣ���û�еõ�ͨѶƽ̨��Ӧ����������!
               -100  �յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! Ӧ�ý���ͨѶ����ͷ����%d>ʵ�ʳ���%d!
               -99   �������ݰ�ͷ����ȷ - CRC-������!(%X!=%X)  ???
               -98   �������ݵĻ��峤��(%d)���㣬�������ݰ�����Ϊ:(%d)���رձ����ӣ�������ͨѶƽ̨��������!
                     ����������ԭ����ɵģ�         
                        ���ջ��峤�Ȳ��㣻�����ڳ����
                        ���յ��������ݲ���ȷ��
                        �����еĽ��ջ��������ݲ�ͬ������Ҫreset��ͨѶƽ̨���ӣ�
               -90   ���յ�ϵͳ��ͷ����޶�ʱ��(%u)��ղ���ʵ�ʵ�Ӧ�����ݰ�(ʵ���յ�%d<��Ҫ���ݳ���%u)
               ����  ����ͨѶ�ײ㷵�صĴ���
               -11   ���ܱ��Է��ر� ???
            =-1 �ȴ�ʱ���û���յ�����
            >=0 �յ����ݰ������ص���ʵ�����ݰ�recvbuf�ĳ���
*/
// ����  : SYS_HEAD *pHead  OUT, �����������صİ�ͷ��Ҳ����Ϊ���ڽ������ݵľ��APPHANDLE
// ����  : void *recvbuf  OUT, ��Ž��յ���Ӧ�����ݻ���
// ����  : int recvbufsize IN, ���峤�ȳߴ�
// ����  : char *szMsg  OUT, ���صĽ��մ�����Ϣ NULL������
// ����  : int nMsgSize IN, =0��������Ϣ��>0 ������Ϣ����󳤶�
// ����  : int wtime IN, �ȴ����յĵȴ�ʱ�� (�����) =0 һֱ�ȴ���ֱ�����ӳ������յ���ʽ����
int CDRTPServer::Receive(SYS_HEAD *pHead, void *recvbuf, int &recvbufsize, char *szMsg, int nMsgSize, int wtime)
{
   int rtn;
   char buf[1024];
   unsigned int crc,crc1;

   if (m_socket.IsFree())
   {
      CopyString("ֹͣ���գ��������Ѿ����ر�!",szMsg,nMsgSize);
      return(-1);
   }

   while (1)
   {
      memset(pHead,0,sizeof(SYS_HEAD));
      memset(recvbuf,0,recvbufsize);
      rtn = m_socket.Recv((char *)pHead,sizeof(SYS_HEAD),wtime);
      if (rtn<=0)
      {
         // =0: û�����ݣ�<0:ͨѶ�˿��������ˣ���Ҫ��������
         if (rtn==0)
         {
            recvbufsize = 0;
            // û�����ݣ�
            m_recvnullcounts++;
            if (m_recvnullcounts>5)
            {
               sprintf(buf,"ͨѶƽ̨���ϣ�����5���������ԣ���û�еõ�ͨѶƽ̨��Ӧ����������!");
               CopyString(buf,szMsg,nMsgSize);
               return(-300);
            }
            // ��һ���������԰�:
            pHead = (SYS_HEAD *)buf;
            memset(pHead,0,sizeof(SYS_HEAD));
            pHead->Ver = 2;
            pHead->MessageType = 10;
            pHead->DestNo = 0xFFFF;
            pHead->Function = m_mainfuncno;
            pHead->FunctionPriority = 1;
            Send(pHead,NULL,0,szMsg,nMsgSize);
         }
         return(rtn);
      }
      if (rtn<(int)sizeof(SYS_HEAD))
      {
         // �յ����ݶβ��㣬Ӧ����ͬ�����⣬���ǹر���������Ӷ˿�
         sprintf(buf,"�յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! Ӧ�ý���ͨѶ����ͷ����%d>ʵ�ʳ���%d!",
            sizeof(SYS_HEAD),rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(-100);
      }
      // �Ƿ�ͨ�����CRC���ж��Ƿ�Ϊ��ȷ��SYS_HEAD?
      crc = pHead->CRC;
      pHead->CRC = 0;
      crc1 = CRC(pHead,sizeof(SYS_HEAD));
      if (bByteReverse)
      {
         reverse(&crc,sizeof(crc));
      }
      if (crc1!=crc)
      {
         sprintf(buf,"�������ݰ�ͷ����ȷ - CRC-������!(%X!=%X)",crc,crc1);
         CopyString(buf,szMsg,nMsgSize);
         return(-99);
      }
      pHead->CRC = crc;  // restore...
      
      if (bByteReverse)
      {
         // ���ڷ�x86��CPU: ��Ҫת��Ϊ�����ɱ��ϵĸ�ʽ big-endian �͵�ַ���λ�ֽ�
         ReverseSysHead(pHead);
      }
      if (recvbufsize<(int)pHead->UserDataSize)
      {
         // ���ڽ��ջ��岻����ֻ�йرձ����ӣ���������е����ݣ���������ͨѶƽ̨
         // ����������ԭ����ɵģ�
         /*
         1. ���ջ��峤�Ȳ��㣻�����ڳ����
         2. ���յ��������ݲ���ȷ��
         3. �����еĽ��ջ��������ݲ�ͬ������Ҫreset��ͨѶƽ̨���ӣ�
         */
         sprintf(buf,"�������ݵĻ��峤��(%d)���㣬�������ݰ�����Ϊ:(%u)���رձ����ӣ�������ͨѶƽ̨��������!",
            recvbufsize,pHead->UserDataSize);
         CopyString(buf,szMsg,nMsgSize);
         return(-98);
      }
      if (pHead->UserDataSize<=0)
      {
         // Ӧ�������ڲ��������ݣ�������Ӧ������
         rtn = 0;
      }
      else
      {
         rtn = m_socket.Recv((char *)recvbuf,pHead->UserDataSize,1000);
         if (rtn<0)
         {
            return(rtn);
         }
         else if (rtn!=(int)pHead->UserDataSize)
         {
            // ͨѶ���������⣬���ǹرձ��������ˣ�������ͨѶƽ̨���Ӱ�
            sprintf(buf,"���յ�ϵͳ��ͷ����޶�ʱ��(%d)��ղ���ʵ�ʵ�Ӧ�����ݰ�(ʵ���յ�%d<��Ҫ���ݳ���%u)",
               wtime,rtn,pHead->UserDataSize);
            CopyString(buf,szMsg,nMsgSize);
            return(-90);
         }
      }
      m_recvnullcounts = 0;
      if (pHead->MessageType==10)
      {
         pHead->MessageType = 11;
         pHead->UserDataRealSize = pHead->UserDataSize = 0;
         Send(pHead,NULL,0,szMsg,nMsgSize);
      }
      else if (pHead->MessageType==5)
      {
         recvbufsize = rtn;
         sprintf(buf,"�յ��������ݰ�������Ϊ%d",rtn);
         CopyString(buf,szMsg,nMsgSize);
         return(rtn);
      }
   }
}



int CDRTPServer::sendpack(SYS_HEAD *phead, void *vdata, int datalen)
{
   int len;
   char *data = (char *)vdata;
   char buf[MAXDATASIZE+100];

   phead->Ver = 2;
   phead->CompressFlag = 0;
   phead->CRC = 0;
   if (data==NULL) 
      datalen = 0;
   phead->UserDataRealSize = phead->UserDataSize = datalen;
   if (bByteReverse)
   {
      // ���ڷ�x86��CPU: big-endian
      ReverseSysHead(phead);
   }
   phead->CRC = CRC(phead,sizeof(SYS_HEAD));
   if (bByteReverse)
   {
      reverse(&(phead->CRC),sizeof(phead->CRC));
   }
/* ****** Updated by CHENYH at 2003-12-5 17:19:27 ****** 

   alen = write(m_socket,phead,sizeof(SYS_HEAD));
   if (alen<=0)
      return(alen);
   if (datalen<=0)
      return(sizeof(SYS_HEAD));
   len = 0;
   while (len<datalen)
   {
      alen = datalen-len;
      if (alen>TCP_BLOCK_SIZE)
         alen = TCP_BLOCK_SIZE;
      alen = write(m_socket,data+len,datalen-len);
      if (alen<=0)
      {
         // ��֪���Ƿ����WOULDBLOCK
         return(alen);
      }
      len += alen;
   }
   return(len+sizeof(SYS_HEAD));

*/
   memcpy(buf,phead,sizeof(SYS_HEAD));
   memcpy(buf+sizeof(SYS_HEAD),vdata,datalen);
   len = sizeof(SYS_HEAD)+datalen;

   datalen = m_socket.Send(buf,len);

/* ****** Updated by CHENYH at 2004-2-12 23:10:30 ****** 
   if (datalen<len)
   {
      // Send Error: -1:��·û���������������رգ�-2:��������ʱ��������رգ�
   }
*/
   return(datalen);
}


// ������: CDRTPServer::receivedata
// ���  : ������ 2003-9-28 22:00:04
// ����  : ��wtime�����룩ʱ����ȴ�����ָ�����ȵ�����
// ����  : int <0 �˿ڳ�����Ҫ�������ӣ�0 ��ָ��ʱ����û�����ݿ��Խ��գ�>0�յ����ݵ�ʵ�ʳ��ȣ�Ҳ�п�����ָ��ʱ�����յ������ݳ��Ȳ���
// ����  : void *recvbuf
// ����  : int recvlen ָ���Ľ������ݳ���
// ����  : char *szMsg
// ����  : int nMsgSize
// ����  : unsigned int wtime 0һֱ�Եȴ���ʽ�������ݣ�>0�Ժ��뵥λʱ���ڵȴ�����





bool CDRTPServer::IsOpenning()
{
   return(m_socket.IsFree()==false);
}

bool CDRTPClient::IsOpenning()
{
   return(m_socket.IsFree()==false);
}
