/********************************************************************
	created:	2003/09/25
	created:	25:9:2003   20:33
	filename: 	E:\linux\ksappsvr\drtp_di.h
	file path:	E:\linux\ksappsvr
	file base:	drtp_di
	file ext:	h
	author:		������
	
	purpose:	Ϊ�˴����¡���ͨѶƽ̨�ӿڣ�����ͳһ�Ľӿڣ�ֻ���ڲ���ɹ���
   ���ݰ汾��ͬ����ͬ��
*********************************************************************/
#ifndef _DRTP_DI_
#define _DRTP_DI_

#include "comstru.h"
#include "tcp.h"
#include "mutex.h"

#define TCP_BLOCK_SIZE 1024

#ifndef INVALID_SOCKET
#define INVALID_SOCKET (-1)       
#endif

#ifndef NULL
#define NULL 0
#endif


void reverse(void *data,int len);

/* ****** Updated by CHENYH at 2003-9-25 22:41:41 ****** 
  ��Ӧ������Ϣģʽ����Ҫ���������У�����
  �ɷ���·�ɱ��irouter���ڵǼǵ�ʱ���¼��RECIEVEDATA->SourceNo��,
  Ŀ��˵�nDest,Ŀ��Ǽǵ�nFunctionNo
*/


bool DRTPInitialize(int nrouters=1);
void DRTPUninitialize();


class CDRTPClient
{
public:
	bool IsOpenning();
#define DRTPCLIENTID 660215
	int classdataid;

   // ������: Receive
   // ���  : ������ 2004-3-17 15:05:05
   // ����  : ͨѶ�ͻ��˵ȴ�����������Ӧ������
   // ����  : int 
   /*
               <0 ���մ���
               -100: �յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! Ӧ�ý���ͨѶ����ͷ����%d>ʵ�ʳ���%d!
               -99:  �յ����ݲ�����ͨѶƽ̨����Ҳ��������ͬ�����⣬����ر�����! ͨѶ��ͷ���ݸ�ʽ�Ƿ�
               -98:  �������ݵĻ��峤��(%d)���㣬�������ݰ�����Ϊ:(%d)���رձ����ӣ�������ͨѶƽ̨��������!
               -90:  ���յ�ϵͳ��ͷ����޶�ʱ��(%u)��ղ���ʵ�ʵ�Ӧ�����ݰ�(ʵ���յ�%d<��Ҫ���ݳ���%u)

               -1: û���յ����ݣ�����Ӧ�û�����ʹ�ã����ùرգ�Ҳ�ɹر��������Ӵ���
               ����<0: 
                  ֹͣ���գ��������Ѿ����ر�!;
                  ͨѶ�ӿ��ڵȴ���������ʱ�����%d-%s!
                  ͨѶ�ӿ��ڽ�������ʱ�����%d-%s!
                  ͨѶ�ӿ��ڵȴ���������ʱ,ͨѶ�ӿڱ��Է��ر�%d-%s!
               =0:   ���szMsg��Ϣ�������������޷��ʹ�Ŀ���ַ�����յ�һ��û�а����Ӧ�����ݰ�
               >0:   OK, �յ�Ӧ�����ݰ�������Ϊ%d
   */
   // ����  : void *recvbuf      ����Ӧ�����ݵĻ���
   // ����  : int recvbufsize    �������Ĵ�С
   // ����  : char *szMsg        ���մ������Ϣ
   // ����  : int nMsgSize       ��Ϣ�������Ĵ�С
   // ����  : unsigned int wtime �ȴ����յĳ�ʱʱ�䣨���룩
	int Receive(void *recvbuf,int &recvbufsize,char *szMsg,int nMsgSize=256,int wtime=1000);

   // ������: Send
   // ���  : ������ 2004-3-17 15:06:47
   // ����  : �ͻ��˷�������
   // ����  : bool true �ɹ����ͣ����ǲ�һ�����͵�Ŀ��Ӧ�öˣ�
   // ����  : H_DRTPCLI linkidx           �ͻ������Ӿ��  ��DRTPCConnect����
   // ����  : unsigned short branchno     ����˵�Ŀ��ڵ��
   // ����  : unsigned short function     ����˵�ͨѶ���ܺ�
   // ����  : void *senddata              ��Ҫ���͵�����
   // ����  : int senddatalen             ��Ҫ���͵����ݳ���
   // ����  : char *szMsg                 ���ʹ���ʱ������Ϣ
   // ����  : int nMsgSize                ���մ�����Ϣ�Ļ�������С            
   // ����  : bool bDesign                �Ƿ��������ݷ��͵��ϴη��ͳɹ���Ŀ���
	bool Send(unsigned short branchno,unsigned short function,void *senddata,int senddatalen,char *szMsg,int nMsgSize=256,bool bDesign=true);

   // ������: Close
   // ���  : ������ 2004-3-17 15:07:36
   // ����  : �ر���ͨѶƽ̨����һ���ͻ�������
   // ����  : bool 
	bool Close();

   // ������: Connect
   // ���  : ������ 2004-3-17 15:07:59
   // ����  : ��ͨѶƽ̨����һ���ͻ�������
   // ����  : char *routerip     ͨѶƽ̨��IP��ַ
   // ����  : int port          ͨѶƽ̨�Ķ˿ں�
   // ����  : char *szMsg        ���Ӵ���ķ�����Ϣ
   // ����  : int nMsgSize=256   ��Ϣ�������Ĵ�С
	bool Connect(char *routerip,int port,char *szMsg,int nMsgSize=256);
	CDRTPClient();
	~CDRTPClient();
protected:
	
private:
#ifdef _DRTP_V4
   long handle;     // DRTP4ʹ�õľ��
#else
	int sendpack(SYS_HEAD *pHead,void *senddata,int senddatalen);
   CTcpSocket m_socket;
   SYS_HEAD m_recvhead;  // �ϴ�Ӧ�����������ͷ
#endif

   CMUTEX m_mutex;
};


class CDRTPServer
{
public:
	bool IsOpenning();

   /* ****** Updated by CHENYH at 2004-3-17 15:00:01 ****** 
   // ���  : ������ 2003-9-29 22:57:39
   // ����  : ���޶���ʱ����wtime(����)������ͨѶƽ̨Э�飬����Ӧ�����ݵ�ͷ�;�����������
   // ����  : int 
               <-1: ������Ҫ�رձ����ӣ����½�������
                  -2000 linkidxΪ��
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
   // ����  : SYS_HEAD *pHead  OUT, �����������صİ�ͷ��Ҳ����Ϊ���ڽ������ݵľ��APPHANDLE
   // ����  : void *recvbuf  OUT, ��Ž��յ���Ӧ�����ݻ���
   // ����  : int recvbufsize IN, ���峤�ȳߴ�
   // ����  : char *szMsg  OUT, ���صĽ��մ�����Ϣ NULL������
   // ����  : int nMsgSize IN, =0��������Ϣ��>0 ������Ϣ����󳤶�
   // ����  : unsigned int wtime IN, �ȴ����յĵȴ�ʱ�� (�����) =0 һֱ�ȴ���ֱ�����ӳ������յ���ʽ����
   */
	int Receive(SYS_HEAD *pHead,void *recvbuf,int &recvbufsize,char *szMsg,int nMsgSize=256,int wtime=5000);

   // ������: Send
   // ���  : ������ 2004-3-17 15:00:38
   // ����  : 
   // ����  : bool 
   // ����  : SYS_HEAD *pHead
   // ����  : void *senddata
   // ����  : int senddatalen
   // ����  : char *szMsg
   // ����  : int nMsgSize=256
	bool Send(SYS_HEAD *pHead,void *senddata,int senddatalen,char *szMsg,int nMsgSize=256);

   // ������: Close
   // ���  : ������ 2004-3-17 15:01:08
   // ����  : �ر�Ӧ�÷���˵�����
   // ����  : bool 
	bool Close();

   // ������: Connect
   // ���  : ������ 2004-3-17 15:01:39
   // ����  : ��ͨѶƽ̨����һ��Ӧ�÷��������
   // ����  : bool               �����Ƿ�ɹ�
   // ����  : char *routerip     ͨѶƽ̨��IP��ַ
   // ����  : int port          ͨѶƽ̨�Ķ˿ں�
   // ����  : int funcount       ע�Ṧ�ܵĸ���
   // ����  : unsigned short *functions �����б�
   // ����  : char *szMsg        ���Ӵ�����Ϣ����
   // ����  : int nMsgSize=256   ��Ϣ�������Ĵ�С
	bool Connect(char *routerip,int port,int funcount,unsigned short *functions,char *szMsg,int nMsgSize=256);
	CDRTPServer();
	~CDRTPServer();

#define DRTPSERVERID  730428
   int classdataid;  // �����ID,�ж��Ƿ����ڱ�������ݽṹ

protected:
	
private:
#ifdef _DRTP_V4
   long handle;   // DRTP4ʹ�õľ��
#else
   int sendpack(SYS_HEAD *pHead,void *data,int datalen);

   unsigned short m_mainfuncno;  // ע��������ܺ�
   int m_recvnullcounts;  // ��Լ��ʱ���û�н��յ��������ݵĴ���
   CTcpSocket m_socket;
#endif

   CMUTEX m_mutex;
};


#endif
