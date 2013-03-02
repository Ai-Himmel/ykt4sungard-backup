// DRTPRouter.h: interface for the CDrtpRouter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRTPROUTER_H__D446F7AD_BB7F_4907_BE94_9A07D3FF9B26__INCLUDED_)
#define AFX_DRTPROUTER_H__D446F7AD_BB7F_4907_BE94_9A07D3FF9B26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "mutex.h"

#ifdef DRTP_V3
typedef HANDLE CLI_HANDLE;
#elif defined DRTP_V3X
#include "tcp.h"
typedef CTcpSocket CLI_HANDLE;
#define MAXROUTERCOUNT  6  /*·�ɼ���*/
/* ���´����������ֽڶ���ʹ�õ� */
#ifdef WIN32
#define __PACKED__ 
#pragma pack(push,1)
#else
#ifdef __GNUC__
#define __PACKED__	__attribute__ ((packed))
//#pragma pack(push,1)
#else
#ifdef HP_UX
#define __PACKED__
#pragma pack 1
#else
#define __PACKED__
#pragma options align=packed
#endif
#endif
#endif

/*������ ��������:2000.6.12 */
typedef struct _SYS_HEAD   /*�������ݰ�ͷ Ver=2 */
{
	unsigned char     Ver;	/*�������ݰ��汾��,��1��ʼ,4.0�汾��Ϊ1*/
	/*5.0ϵͳ�汾��Ϊ2 */ 
	unsigned char     MessageType;   	/*��Ϣ���ͣ�����ϵͳ��Ӧ����Ϣ */
	/*Ӧ�ù���ע��	1 */
	/*Ӧ�ù���ע�� 	2 */
	/*��ѯ����״̬ 	3 */
	/*��ѯ������־	4 */
	/*�û���������Ŀ������ 	5 */
	/*�û�����Ŀ�����ؽ�� 	6 */
	/*����Ự��Կ 7	 ����Public Key */
	/*���ػỰ��Կ 8	Session Key ��Public Key���ܺ������ */
	/*���ĻỰ��Կ 9 �µĻỰ��Կ�ļ������ϴλỰ��Կ */
	/*10 */
	/*11 */
	unsigned char     CompressFlag;	/*ѹ����ǣ���������USER_BLOCK */
	/*0-  ����û��ѹ�� */
	/*1-  ����ѹ��	   */
	unsigned char     RouterIndex;	/*���ݰ�����·�ɵ���ţ����͵����ݰ�ÿ����һ��*/
	/*·�ɾͼ�һ�����ص����ݰ�ÿ����һ��·�ɾͼ�һ��*/
	/*·����ྭ��6����������Ϊ�Ѱ����� */
	unsigned char	   RouterDesignate;/*·��ָ����� */
	/*0�ǲ�ָ���������ܺ����� */
	/*1ָ�����ܣ����ϴ�����·������Ŀ�ĵ� */
	unsigned char	   FunctionPriority;/*���ܺ����ȼ�,0Ϊȱʡ����0Ϊ�û��Զ��� */
	/*1Ϊ���ȼ����ڱ�׼ */
	/*2Ϊ��׼���ȼ�		*/
	/*3Ϊ���ȼ����ڱ�׼	*/
	unsigned short 	Function; 	    /*�����ܺţ�Ӧ����·��ֻע�������ܺ� */
	/*�ӹ��ܺ���Ӧ�ø������	*/
	/*�罻����Ϊ1��ʵʱ��ѯΪ2����ѯ��ʷΪ3 */
	/*	unsigned short    SourceNo; */
	unsigned short    DestNo;/*Ŀ�����ر�ţ�Ӫҵ�����룩 */
	unsigned short    UserDataSize;   /*���ݱ�ͷ���ŵ�Ӧ������USER_BLOCK���� */
	unsigned short    UserDataRealSize;/*Ӧ�����ݵ���ʵ���ȣ����ݼӽ��ܻ�ѹ��ǰ�ĳ��� */
	unsigned short 	RouterIn[MAXROUTERCOUNT];	/*·����Ϣ����·�� */
	unsigned short    RouterOut[MAXROUTERCOUNT];  /*·����Ϣ���·�� */
	int	 			   LastConnectTime;/*ʱ����,��Ч���ݰ���ʱ��Ӧ�ñ�CONNECT��ʱ��� */
	/*�ͻ�CONNECTʱ����,��λΪ*/
	unsigned int      CRC;           /*���ݰ�ͷSYS_HEAD��32λcrcֵ */
} __PACKED__ SYS_HEAD;

#ifdef WIN32
#pragma pack(pop)
#else
#ifdef __GNUC__
#else
#ifdef HP_UX
#pragma pack 0
#else
#pragma options align=reset
#endif
#endif
#endif
#undef __PACKED__

#else
typedef int CLI_HANDLE;
#endif

#define MAXIPLENGTH 64

class CDrtpClient  
{
public:
   time_t m_lasttime;   // �ϴ�ͨ�������ӽ�����Ч���շ����ݵ�ʱ��㣬time(NULL)
   CMUTEX m_mutex;
   CLI_HANDLE m_handle;
#ifdef DRTP_V3X
	int sendpack(SYS_HEAD *pHead,void *senddata,int senddatalen);
#endif
   
public:
	bool Broad(int destno, int funcno, char *sbuf, int sblen, char *errmsg);
	int Receive(char *rbuf, int rbsize,char *errmsg,int waittime);
	void Close();
	bool Send(int destno,int funcno,char *sbuf, int sblen, char *errmsg);
	bool Connect(char *ip, int port, char *errmsg);
	bool IsOpenning();
	CDrtpClient();
	virtual ~CDrtpClient();

};

typedef std::list<CDrtpClient *> CLILIST;

class CDrtpRouter  
{
public:
   char m_IP[MAXIPLENGTH];
   int  m_port;

private:
   CLILIST m_CliList;

public:
	int Broad(int branchno, int funcno, char *sbuf, int sblen, char *errmsg);
	int CLISendReceive(int branchno, int funcno,int timeout, char *sbuf, int sblen, char *rbuf, int rbsize, char *errmsg);
	CDrtpRouter();
	virtual ~CDrtpRouter();

};


#endif // !defined(AFX_DRTPROUTER_H__D446F7AD_BB7F_4907_BE94_9A07D3FF9B26__INCLUDED_)
