// SvrLink.h: interface for the CSvrLink class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
#define AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_

#include "tcp.h"
#include "cxpack.h"
#include "bupub.h"
#include "comstru.h"

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef _WINDOWS
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define END_FIELD -1

typedef struct
{
   int sno;  // �״ε���ExtCall������souceno
   int dno;  // �״ε���ExtCall������destno
   int fno;  // �״ε���ExtCall������funcno
   int bno;  // �״ε���ExtCall������batchno
   ST_PACKHEAD ahead;  // Ӧ�𷵻ص�ͷ���ݱ�����
} ST_PDKEEP;


class BUPUB_API CSvrLink  
{
public:
   int  bccBFuncNo;        // ���ӵ�BCCע���ͨѶ���ܺ�
   int  bccID;             // ���ӵ�BCC���>0
   int iThisProcID;        // ��BULink�ı��
   
   bool bExit;             // �Ƿ�Ҫ�˳�...
   ST_PACKHEAD head;       // ��ǰʹ�õ�CPACK��ͷ����parmbit��
   ST_PDKEEP xcdata;       // ���ڱ���ExtCall��ExtCallNext��������

   unsigned int m_lastrcvtick;   // �ϴδ�BCC�յ���Ϣʱ��㣬����tc2_tc1()�����ж�
private:
   unsigned char iGRFrame;     // ֡��
   unsigned int iLastReqType;  // �ϴλ򱾴ε��õĹ��ܺ�
   int iLastRetCode;  // �ϴδ������ĳɹ���ʧ�ܣ�����֪ͨBCC
   ST_PACKHEAD reqhead;    // �������ͷ�������Ա���ҵ�����м���ֶε�����
   char eMsg[256];
   CTcpSocket linksock;    // ��������ĵ�TCPIP����
   short svr_hs1;          // �������ģ�short��1�������ж��Ƿ��뱾ҵ��Ԫ������������ͬ
   char buf[MAXMSG+sizeof(MSGHEAD)+50];     // ������ʼ����Ϣͷ
   char iAnswerMode;       // ��ǰ��Ч��Ӧ��ģʽ����AM_AUTO / AM_CONFIRM
   TRUSERID ruserid;       // �������ύ�Ŀͻ���ID
   
public:

   // ������: SetCol
   // ���  : ������ 2005-9-27 11:50:57
   // ����  : ���ô˺�Ӧ����е���Ч�ֶ�
   // ����  : int ���ر����õ���Ч�ֶθ���
   // ����  : TRUSERID *handle[IN]: ����Ϊ�˼��ݣ�ʵ����Ч
   // ����  : ...[IN]: �����õ���Ч�ֶ�λͼ(���)�嵥����END_FIELD����
	int SetCol(TRUSERID *handle,...);

   // ������: BCCMsgLogOut
   // ���  : ������ 2005-9-27 19:31:25
   // ����  : ��BCC���������BU���ı���־��Ϣ
   // ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
   // ����  : int logid[IN]������־��ID��
   // ����  : char *pFormat[IN]���ı���־�ĸ�ʽ����
   // ����  : ... [IN]����pFormat����Ĳ����б�
	int BCCMsgLogOut(int logid, char *pFormat, ...);

   // ������: Error_Deal
   // ���  : ������ 2005-9-27 11:45:17
   // ����  : ��������Ϣ��д��vsmess����һ���Եķ��ظ�����
   // ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
   // ����  : int retcode[IN]��������
   // ����  : char *omsg [OUT]����������vsmess�ֶε���Ϣ��
   // ����  : char *pFormat [IN]��������Ϣ�Ĳ�����ʽ�����ο�sprintf˵��
   // ����  : ... [IN]: pFormat��ʽ����Ĳ����б�
	int Error_Deal(int retcode, char *omess, char *pFormat,...);

   // ������: GetRequestHead
   // ���  : ������ 2005-9-27 11:43:11
   // ����  : ��ԭʼ�������ͷ���Ƶ�phead
   // ����  : void 
   // ����  : ST_PACKHEAD *phead[OUT]: ��Ÿ��Ƶİ�ͷ
	void GetRequestHead(ST_PACKHEAD *phead);

   // ������: GetAnswerHead
   // ���  : ������ 2005-9-27 11:42:29
   // ����  : ����ǰӦ���ͷ���Ƶ�phead
   // ����  : void 
   // ����  : ST_PACKHEAD *phead[OUT]: ��Ÿ��Ƶİ�ͷ
	void GetAnswerHead(ST_PACKHEAD *phead);

   // ������: RATransfer
   // ���  : ������ 2005-9-16 0:49:26
   // ����  : ͨ��RA�������õ�Ŀ��������������ת��
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : ST_CPACK *rpack[IN]: ���������ΪNULL��ʾ���ύ����BU��ԭʼ����ת��
   // ����  : ST_PACK *pArrays=NULL[IN]: ������ĺ�����¼
	int RATransfer(ST_CPACK *rpack=NULL, ST_PACK *pArrays=NULL);

   // ������: ExtTransfer
   // ���  : ������ 2005-9-16 0:47:34
   // ����  : ��Ŀ��Ӧ�÷�����ת������
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : int destno[IN]: Ŀ��Ӧ�÷��������ӵ�ͨѶƽ̨�ڵ��(BRANCH/YYBDM)
   // ����  : int funcno[IN]: Ŀ��Ӧ�÷�����ע���ͨѶ���ܺ�
   // ����  : ST_CPACK *rpack[IN]: ���������ΪNULL��ʾ���ύ����BU��ԭʼ����ת��
   // ����  : ST_PACK *pArrays=NULL[IN]: ������ĺ�����¼
	int ExtTransfer(unsigned short destno, unsigned short funcno, ST_CPACK *rpack=NULL, ST_PACK *pArrays=NULL);

   // ������: IntTransfer
   // ���  : ������ 2005-9-15 23:56:24
   // ����  : �������ת����BCC��ָ����BU��
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : char *szBUGroupID[IN]: ָ����BU������
   // ����  : ST_CPACK *rpack[IN]: ���������ΪNULL��ʾ���ύ����BU��ԭʼ����ת��
   // ����  : ST_PACK *pArrays=NULL[IN]: ������ĺ�����¼
	int IntTransfer(char *szBUGroupID, ST_CPACK *rpack=NULL,ST_PACK *pArrays=NULL);

   // ������: RACallNext
   // ���  : ������ 2005-9-16 0:12:39
   // ����  : ���ϴ�RACall��Ŀ���ȡ�������ݰ������ϴ��յ���Ӧ�����apack->head.nextflag==1
   // ����  : int >=0: ��ʾ�ɹ��յ�Ӧ���; 
   //             <0: ʧ�ܣ�
   //             -2: �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
   //             -1: ��������ͨѶ����Ĵ���
   // ����  : int waittime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *apack[OUT]: Ӧ���
   // ����  : ST_PACK *pArrays[OUT]: Ӧ��������ݼ�¼
	int RACallNext(int acktime, ST_CPACK *apack, ST_PACK *pArrays);

   // ������: RACall
   // ���  : ������ 2005-9-16 0:11:29
   // ����  : ͨ��RA�������õ�Ŀ�������ڵ���������ܷ���
   // ����  : int >=0: ��ʾ�ɹ��յ�Ӧ���; 
   //             <0: ʧ�ܣ�
   //             -2: �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
   //             -1: ��������ͨѶ����Ĵ���
   // ����  : int acktime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *rpack[IN]: �����
   // ����  : ST_CPACK *apack[OUT]: Ӧ���
   // ����  : ST_PACK *pArrays[OUT]: Ӧ��������ݼ�¼
	int RACall(int acktime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays);

   // ������: IntCallNext
   // ���  : ������ 2005-9-16 0:09:25
   // ����  : ���ϴ�IntCallָ����BU��ȡ�������ݰ������ϴ��յ���Ӧ�����apack->head.nextflag==1
   // ����  : int ==0: ��ʾ�ɹ��յ�Ӧ���; 
   //             <0: ʧ�ܣ�
   //             -2: �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
   //             -1: ��������ͨѶ����Ĵ���
   // ����  : int waittime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *apack[OUT]: Ӧ���
   // ����  : ST_PACK *pArrays[OUT]: Ӧ��������ݼ�¼
	int IntCallNext(int waittime, ST_CPACK *apack, ST_PACK *pArrays);

   // ������: IntCall
   // ���  : ������ 2005-9-16 0:02:34
   // ����  : ������һ��ָ��BU����ù���
   // ����  : int ==0: ��ʾ�ɹ��յ�Ӧ���; 
   //             <0: ʧ�ܣ�
   //             -2: �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
   //             -1: ��������ͨѶ����Ĵ���
   // ����  : char *szBUGroupID[IN]: ָ����BU������
   // ����  : int waittime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *rpack[IN]: �����
   // ����  : ST_CPACK *apack[OUT]: Ӧ���
   // ����  : ST_PACK *pArrays[OUT]: Ӧ��������ݼ�¼
	int IntCall(char *szBUGroupID, int waittime, ST_CPACK *rpack, ST_CPACK *apack, ST_PACK *pArrays);

   // ������: UpdateRegFunction
   // ���  : ������ 2005-9-15 23:59:26
   // ����  : ��BCCע�������BU���ṩ�ķ����ܺ�
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : unsigned int reqtype[IN]: ���ܺţ���ST_PACKHEAD::RequestType
   // ����  : char *rtname[IN]: �����ܵļ�����
   // ����  : char *programmer[IN]: �����ܿ�����Ա˵��
   // ����  : int priority=1[IN]: �����ܵ����ȼ���[1,2,3]
   // ����  : bool bstop=false[IN]: �������Ƿ���ͣ����
	int UpdateRegFunction(unsigned int reqtype,char *rtname,char *programmer,int priority=1,bool bstop=false);


   /* ****** Comment by CHENYH at 2005-7-6 20:45:17 ****** 
   ����Ϊ�����ڴ�����������
   �ⲿ�ֵĹ����ڴ��ʵ����ͨ��SMOpenBlock��������BU������BCC��
   ���ڴ�飬ͨ���ڴ����ݵĽ����ﵽһ��BCC�¸���BU�ܹ����ʺ��޸�
   ��Щ�ڴ��е����ݡ��ﵽ���ݹ����Ŀ�ġ�
   ��BCC������ʱ��ʵ���ϴ�����100���������Ͷ��峤�ȵĹ����ڴ���Դ��
   Ϊ�˿�����Э����������Щ�����ڴ���Դ�ж�������һ�����������Զ�����
   ���ж�ռʽ���ʡ�
   ����һ��BCC�¹ҽӵ�����BU��������ƿ��Թ�ͬʹ����100����Դ��
   ��ȻҲ����ҪԤ�ȶ�����ʹ�÷�ʽ�����ݽṹ��
   ����ĺ�����Ϊ��ҵ����ֱ�ӹ�ϵ�ļܹ����֣������������Ķ��壬
   ��Ҫ����ϵͳ�ڽ�������BU��ʱ��������Ӧ����ơ�
   *******************************************************/
   // ������: CSvrLink::SMInterlockedAdd
   // ���  : ������ 2005-7-6 11:08:58
   // ����  : �ڹ����ڴ����ָ����λ����Ϊ�������ж�ռ�ӷ�����
   // ����  : int ���ض�ռ�ӷ�������ֵ��
   //          Ϊ0x80000000����������ϵͳ���������
   //          Ϊ0x80000001����������ڲ�������
   //          ���������������Ϊ�ж�
   // ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
   // ����  : unsigned int offset��[IN] ���ݵ�ƫ��λ��
   // ����  : int increment��[IN] ��������
	int SMInterlockedAdd(int smh,unsigned int offset,int increment=1);

   // ������: CSvrLink::SMRead
   // ���  : ������ 2005-7-6 10:21:43
   // ����  : ��ָ�������ڴ�ռ��ж�ȡ�ֲ���ȫ��������
   // ����  : int -2/-1000:�����ڴ������� 
   //             -1:�ڴ�ռ�û�з��䣻 
   //              0:��ȡλ��offset�����Ѿ�����Ŀռ�  
   //             >0:��ȡ���ݳ��ȣ������ֵ<ָ����ֵ������Ϊ������
   //             -20: �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
   //             <-100: ���ڸ������
   //             -101:���Է������رգ�
   //             -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
   //             -102:��Ϊ��·��������رգ�
   //             -103:�ڽ������ݵ�ʱ�򣬳�������ر�
   //             -1001: ���ȹ�����ÿ�εĳ���length<=8180
   // ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
   // ����  : void *rbuf��[OUT] ��ȡ���ݻ���
   // ����  : unsigned int offset��[IN] ��ȡ���ݴ���ڹ����ڴ���ƫ��λ��
   // ����  : unsigned int rblen��[IN] ��ȡ���ݿ鳤�ȣ�ע��<8180
   // ����  : bool bRLock: [IN] �Ƿ���Ҫ������
   int SMRead(int smh, void *rbuf, unsigned int offset,unsigned int rblen,bool bRLock=false);

   // ������: CSvrLink::SMWrite
   // ���  : ������ 2005-7-4 20:13:07
   // ����  : д�ֲ���ȫ�����ݵ�ָ���Ĺ����ڴ��
   // ����  : int -2/-1000:�����ڴ������� 
   //             -1:�ڴ�ռ�û�з��䣻 
   //              0:д��λ��offset�����Ѿ�����Ŀռ�  
   //             >0:д�����ݳ��ȣ������ֵ<ָ����ֵ������Ϊ������
   //             -20: �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
   //             <-100: ���ڸ������
   //             -101:���Է������رգ�
   //             -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
   //             -102:��Ϊ��·��������رգ�
   //             -103:�ڽ������ݵ�ʱ�򣬳�������ر�
   //             -1001: ���ȹ�����ÿ�εĳ���length<=8180
   // ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
   // ����  : void *wdata��[IN] д���ǵ����ݿ�
   // ����  : unsigned int offset��[IN] ���ݴ���ڹ����ڴ���ƫ��λ��
   // ����  : unsigned int length��[IN] ���ݿ鳤�ȣ�ע��<8180
   // ����  : bool bWLock: [IN] �Ƿ���Ҫ����д
	int SMWrite(int smh,void *wdata,unsigned int offset,unsigned int length,bool bWLock=true);

   // ������: CSvrLink::SMOpenBlock
   // ���  : ������ 2005-7-4 15:52:14
   // ����  : �������һ�����������ڴ��
   // ����  : int 
   //          >=0: �ɹ������ظù����ڴ�ľ���ţ�
   //          -1: �����ڴ�飨������Ѿ�������
   //          -2: �Ѿ���Ҫ�Ĺ����ڴ�鳤���Ѿ�������BCC�޶���
   //          -3: Ҫ��ĳ��ȳ����Ѿ�����Ĺ����ڴ泤��
   //          -20: �ȴ���ʱ��BCCû���ܹ���1��֮����Ӧ
   //          <100: ���ڸ������-101:���Է������رգ�-110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����-102:��Ϊ��·��������رգ�-103:�ڽ������ݵ�ʱ�򣬳�������ر�
   // ����  : char *name : �����ڴ������
   // ����  : unsigned int length: �����ڴ��ĳ���
	int SMOpenBlock(char *name,unsigned int length);
   /*******************************************************/

   /* ****** Commented by CHENYH at 2005-7-6 20:34:21 ******/
   /* ��������������Ϊ�������Ͽ������ĶԹ����ڴ������ͽ�������
      ������Щ������Ϊ��������ʹ�ã�����������Ҫ�����ڴ�Ŀռ�
      ��ˣ������������еĹ�����Դ������Բ���SMOpenBlock���ṩ��
      ��BCC��ʵ����������ʱ��ʹ������޿ռ����������Դ��
      ����Ϊ0��99����ʹ��SMOpenBlock��ʱ���Ǵ�0�ſ�ʼʹ�õģ�
      ����ǵ����ġ����ԣ��������Ϊ�����񣬽���ֱ�Ӵ�99�ſ�ʼ
      ��Ϊ������ƾ������Ȼ����Ϊû��ʹ��SMOpenBlockҲ��û�о����
      �����ڴ�ռ��������
   *******************************************************/
   // ������: CSvrLink::SMUnlock
   // ���  : ������ 2005-7-6 20:28:47
   // ����  : �Ա�BU�����Ĺ����ڴ�����
   // ����  : int -2/-1000:�����ڴ������� 
   //             1: �����ɹ�
   //             <-100: ���ڸ������
   //                -101:���Է������رգ�
   //                -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
   //                -102:��Ϊ��·��������رգ�
   //                -103:�ڽ������ݵ�ʱ�򣬳�������ر�
   //                -1001: ���ȹ�����ÿ�εĳ���length<=8180
   // ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
   //          ע������ĿǰΪ������ϵͳ�ȶ����ǣ�Ŀǰһ��BUͬʱֻ�ܶ�һ��
   //             �����ڴ����м����������һ����ͼ������ʱ��
   //             �����Ѿ��������Ļ��������ͷ�
	int SMUnlock(int smh);

   // ������: CSvrLink::SMTryLock
   // ���  : ������ 2005-7-6 20:25:17
   // ����  : ���Ŷ�ָ�����ڴ����м���������������������
   // ����  : int -2/-1000:�����ڴ������� 
   //             0: ������������������Դ������BU������
   //             1: �����ɹ�
   //             <-100: ���ڸ������
   //                -101:���Է������رգ�
   //                -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
   //                -102:��Ϊ��·��������رգ�
   //                -103:�ڽ������ݵ�ʱ�򣬳�������ر�
   //                -1001: ���ȹ�����ÿ�εĳ���length<=8180
   // ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
	int SMTryLock(int smh);

   // ������: CSvrLink::SMLock
   // ���  : ������ 2005-7-6 16:07:57
   // ����  : ��ָ���Ĺ����ڴ����б�BUռ�ü���������ģʽ��ֱ���ɹ���ʧ��
   // ����  : int -2/-1000:�����ڴ������� 
   //             1: �����ɹ�
   //             <-100: ���ڸ������
   //                -101:���Է������رգ�
   //                -110/-111:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����
   //                -102:��Ϊ��·��������رգ�
   //                -103:�ڽ������ݵ�ʱ�򣬳�������ر�
   //                -1001: ���ȹ�����ÿ�εĳ���length<=8180
   // ����  : int smh��[IN] �����ڴ�������μ�SMOpenBlock����
	int SMLock(int smh);
   /*******************************************************/

   // ������: SetCol
   // ���  : ������ 2005-7-6 22:28:13
   // ����  : �������ú�����¼�����е������У��ֶΣ�Ϊ��Ч�ֶ�
   //         ���ڱ���������ֱ�ӱ�Ӧ�÷����ܵ��ã���ˣ�������
   //         ����λͼ��ʽ���У�������������ֶ����á�
   //         ���������������ַ�����
   //         1. ��λͼ�б�parmbits[32]�е�����λ��Ϊ0������£�Ϊ�������λͼ��
   //         2. ��λͼ�б�����λΪ1�ģ�����������Чλͼ��
   // ע�⣺�ھ��幦�ܵ��õ�ʱ���ڲ�����λͼʵ���ǿյģ��������Ӧ��XPACKģʽ�£�����ֱ�ӷ���ST_SDPACK��¼��
   //       �����Ҫ����ST_PACK��¼����ô����������Чλͼ��
   // ����  : int ��Чλͼ�����������ε��õ������и���
   // ����  : TRUSERID * puserid: Reserve
   // ����  : unsigned char *parmbits: ����������Чλͼ�б�
	int SetCol(TRUSERID * puserid, unsigned char *parmbits);

   // ������: PutRow
   // ���  : ������ 2005-9-16 0:28:11
   // ����  : �������ύӦ�����ݼ�¼
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : TRUSERID * handle[IN]: ���󷽵ľ��
   // ����  : ST_PACK *pdata[IN]: Ӧ�����ݼ�¼
   // ����  : int retcode[IN]: ��������ķ�����
   // ����  : char *rtnMsg[IN]: ����Ϊ�˼��ݣ�ʵ��û��Ч��
	int PutRow(TRUSERID * handle,ST_PACK *pdata,int retcode,char *rtnMsg);
	int Err_Deal(char *emsg, int retcode);

	int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg);
	int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg,unsigned char nextflag);


   // ������: SetMaxRow
   // ���  : ������ 2005-9-16 0:35:42
   // ����  : ������������¼�� [1,100]
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : int maxrows[IN]: ��������¼�� [1,100]
	int SetMaxRow(int maxrows);

	int SetAnswerMode(char iAnswerMode);
	bool CheckProcCancel();

   // ���¹����ܹ�֧��ͨ�üܹ���(ֻ����cpack.dat��������ȷ��ST_PACK�ṹ�������ʹ��)
   // Added by CHENYH on 2006-3-5 23:28:26  ��Ϊ��ͨ�ù����л�ܹ������£�������ȷ����ST_PACK�Ľṹ
	int ExtCallNext(int acktime, char *abuf, int &alen);
	int ExtCall(int sourceno, int destno, int funcno, int batchno, int acktime, void *rdata, int rdlen, char *abuf, int &alen);
   int PushData(int sourceno, int destno, int funcno, int batchno, char pushmode, int acktime, void  *pdata, int pdlen);
	int PushDataEx(TPUSHDEST *pushdests, int pdcount, void *pdata, int pdlen, char pushmode, int acktime);
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //////////////////////////////////////////////////////////////////////////
   // �����º�����ֻ�ܱ���ȷ��cpack.dat��ST_PACK���ض���Ŀ��ʹ�õ�
   // ----------------------------------------------------------------------
   // ������: ExtCallNext
   // ���  : ������ 2005-9-16 0:18:38
   // ����  : ���ϴ�ExtCall��Ŀ���ȡ�������ݰ������ϴ��յ���Ӧ�����apack->head.nextflag==1
   // ����  : int >=0: ��ʾ�ɹ��յ�Ӧ���; 
   //             <0: ʧ�ܣ�
   //             -2: �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
   //             -1: ��������ͨѶ����Ĵ���
   // ����  : int acktime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *apack[OUT]: Ӧ���
   // ����  : ST_PACK *pArrays[OUT]: Ӧ��������ݼ�¼
	int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays);

   // ������: ExtCall
   // ���  : ������ 2005-9-16 0:14:20
   // ����  : ��ָ����Ӧ�÷����������������
   // ����  : int >=0: ��ʾ�ɹ��յ�Ӧ���; 
   //             <0: ʧ�ܣ�
   //             -2: �ȴ�Ӧ�����ݳ�ʱ�����Դ����ⷢ�����������waittime+1����û�н��յ�Ӧ������  
   //             -1: ��������ͨѶ����Ĵ���
   // ����  : int sourceno[IN]: ͨ���ĸ�ͨѶƽ̨����ţ����������������
   // ����  : int destno[IN]: Ŀ��Ӧ�÷��������ӵ�ͨѶƽ̨�ڵ��(BRANCH/YYBDM)
   // ����  : int funcno[IN]: Ŀ��Ӧ�÷�����ע���ͨѶ���ܺ�
   // ����  : int batchno[IN]: ��Ŀ���Ľ������κ�
   // ����  : int acktime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *rpack[IN]: �����
   // ����  : ST_CPACK *apack[OUT]: Ӧ���
   // ����  : ST_PACK *pArrays[OUT]: Ӧ��������ݼ�¼
	int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays);


   // ������: PushDataEx
   // ���  : ������ 2005-9-16 0:25:40
   // ����  : ����Ŀ��㷢��������Ϣ��
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : TPUSHDEST *pushdests[IN]: Ŀ����б�
   // ����  : int pdcount[IN]: Ŀ������
   // ����  : ST_CPACK *ppack[IN]: ��Ϣ��
   // ����  : char pushmode[IN]: ����ģʽ
   // ����  : int acktime[IN]: ��Ϊģʽ1��ʱ�򣬱���Ϣ����Чʱ�䣨���೤ʱ�����ظ����ͣ�����ȡ����
   int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime,ST_PACK *pArray=NULL);

   // ������: PushData
   // ���  : ������ 2005-9-16 0:21:07
   // ����  : ��ָ����Ŀ��㷢��������Ϣ����
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : int sourceno[IN]: ͨ���ĸ�ͨѶƽ̨����ţ�����������Ϣ
   // ����  : int destno[IN]: Ŀ��Ӧ�÷��������ӵ�ͨѶƽ̨�ڵ��(BRANCH/YYBDM)
   // ����  : int funcno[IN]: Ŀ��Ӧ�÷�����ע���ͨѶ���ܺ�
   // ����  : int batchno[IN]: ��Ŀ���Ľ������κ�
   // ����  : int acktime[IN]: Ӧ�����ݵȴ���ʱʱ�䣬���룩
   // ����  : ST_CPACK *ppack[IN]: ��Ϣ��
   // ����  : char pushmode[IN]: ����ģʽ
   // ����  : int acktime[IN]: ��Ϊģʽ1��ʱ�򣬱���Ϣ����Чʱ�䣨���೤ʱ�����ظ����ͣ�����ȡ����
	int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime,ST_PACK *pArray=NULL);
   //////////////////////////////////////////////////////////////////////////
   
	int ResetAnswerData();
	void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount);
   
	int SetAnswerTimeout(unsigned int atimeout);
	int SetBUError(int errcode,char *szErrMsg);

   // ������: BCCLogOut
   // ���  : ������ 2005-9-27 12:06:12
   // ����  : �ṩBU������Ҫ��¼����־��Ϣͳһ�����BCC�ĸ�����־�ļ���
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : char logtype[IN]: ������־�����ͣ��μ���������
            //#define LT_MSG   'C'     ������־
            //#define LT_CPACK 'P'     CPACK���������־
            //#define LT_UDATA 'U'     �û����ж���������־
   // ����  : int logid[IN]: ����־����Ϣ���
   // ����  : int textlen[IN]: ��Ϣ���ݵĳ���
   // ����  : char *text[IN]: ��Ϣ�����ڴ�
   // ����  : int datalen=0[IN]: ������־�ĳ���
   // ����  : void *data=NULL[IN]: ���ݳ���
	int BCCLogOut(char logtype,int logid,int textlen,char *text,int datalen=0,void *data=NULL);
   
	int PushRowEx(TPUSHDEST *pushdests,int pdcount,ST_PACK *pack,char pushmode,int batchno,int acktime);
	int PushRow(int sourceno,int destno,int funcno,ST_PACK *pack,char pushmode,int batchno,int acktime);

   // ������: PutRowData
   // ���  : ������ 2005-9-27 12:10:43
   // ����  : ����ǰ�����SetColָ������Ч�ֶΣ����һ����¼������
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : ST_PACK *pdata[IN]: �����ST_PACK/ST_SDPACK��¼
   int PutRowData(ST_PACK *pdata);


   // ������: CheckLink
   // ���  : ������ 2005-9-27 12:14:48
   // ����  : ͨ�����Ϳ����ʽ�����BCC�����Ƿ�����
   // ����  : bool true:��ʾ����������false:��ʾ���ӶϿ�
	bool CheckLink();

   // ������: LinkOK
   // ���  : ������ 2005-9-27 12:13:25
   // ����  : �򵥼����BCC����״̬
   // ����  : bool true:��ʾ����������false:��ʾ���ӶϿ�
	bool LinkOK();
   
	int Processing(ST_BUNIT *pBUnit);
	void Close();
	int ToLink(ST_BUNIT *pBUnit);
	CSvrLink();
	virtual ~CSvrLink();

private:
   // ������: CSvrLink::SetTRUserID
   // ���  : ������ 2005-8-2 11:25:04
   // ����  : ���ø���Ӧ�����ݽ��շ�����ʾ����PutRow�����ݶ�Ҫ���͸�ָ����
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : TRUSERID *ruserid : ָ����Ӧ�����ݽ��շ�
	int SetTRUserID(TRUSERID *ruserid);

	int SMLockCmd(int smh, short lockmode);
	int DataDone(int retcode,char *szMsg);
	int CallBPFunction(MSGBUF *pmb);

   // ������: CSvrLink::SendMsg
   // ���  : ������ 2004-2-10 21:08:11
   // ����  : ��MSG��ʽ������Ϣ���ݸ���������
   // ����  : int =0:���ͳɹ���<0:����ʱ��˿ڳ������⣬�˿ڱ��رգ�-100:��������ϵĴ�����Ҫ�˲����
   // ����  : short msgtype ��IN ���͵���Ϣ����
   // ����  : unsigned short msglen ��IN ��Ϣ�����ݳ���
   // ����  : void *msgbuf �� IN ��Ϣ���ݻ���
	int SendMsg(short msgtype,unsigned short msglen=0,void *msgbuf=NULL);

   // ������: CSvrLink::RecvMsg
   // ���  : ������ 2004-2-10 22:40:18
   // ����  : ����MSGЭ���������
   // ����  : int -1:���Է������رգ�-10:�����nDesignedSize<=0��-11:�Է��Ǳ�׼MSGЭ��ڻ����ݲ�ͬ����-2:��Ϊ��·��������رգ�0:��ʱ��-3:�ڽ������ݵ�ʱ�򣬳�������ر�
   // ����  : int timeout
	int RecvMsg(int timeout=3000);

	MSGBUF * GetRecvMsg();


};

#undef BUPUB_API

#endif // !defined(AFX_SVRLINK_H__6DD59251_58E5_47D1_B01B_F0DC850FC95C__INCLUDED_)
