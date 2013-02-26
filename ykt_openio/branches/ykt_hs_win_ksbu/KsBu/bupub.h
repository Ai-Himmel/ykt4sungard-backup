/***********************************************************************************
  ������־��¼
  ������: ������
  �������� 2004-2-7 15:36:16
  �汾: V1.00 
  ˵��: �����sqc������ص�ȫ�ֱ����ͺ�������
 ***********************************************************************************/
#ifndef _PUPUB_H
#define _PUPUB_H

#ifdef BUPUB_EXPORTS
#define BUPUB_API __declspec(dllexport)
#else
#ifdef WIN32
#define BUPUB_API __declspec(dllimport)
#else
#define BUPUB_API 
#endif
#endif


#ifdef __cplusplus
extern "C" {
#endif

#ifndef ENDFIELD
// Ϊ����
#define ENDFIELD -1
#endif

#define SQLID_MAX 30


/* ****** Updated by CHENYH at 2004-2-7 17:54:49 ****** 
���¶���SQC������Ҫ�ĸ�ȫ������
*/

typedef struct
{
   unsigned char buf[48];
} SYSHEAD;

typedef struct
{
   unsigned short SourceNo;         /* ����������ڷ���˵�ͨѶƽ̨��� */
   SYSHEAD syshead;                 /* �������ʱ��Ϊ����˵�ͨѶ��ǿ飬ҵ����벿�ֲ�Ҫ�޸ģ�ֻ������������¿��Լ�¼�����ݿ��У���Ϊ���׶��ύʱ��ʹ�� */
} TRUSERID;    /* �������Ϊ��ͨѶƽ̨�еı�ʶ */

typedef struct
{
   unsigned short SourceNo;         /* ��ʼ����ͨѶƽ̨�ı�� ���μ�TRUSERID::SourceNo��*/
   unsigned short DestNo;           /* ����Ŀ����ͨѶƽ̨��� */
   unsigned short FuncNo;           /* ����Ŀ���ע���ͨѶ���ܺ� */
   unsigned int   BatchNo;          /* ��Ը�Ŀ�������κ� */
} TPUSHDEST;     /* ����Ŀ���Ķ��� */
typedef struct 
{
   char szLogin[SQLID_MAX+1];     // SQL Server login ID
   char szPassword[SQLID_MAX+1];  // SQL Server password
   char szServer[SQLID_MAX+1];    // SQL Server name
   char szDatabase[SQLID_MAX+1];  // SQL Server database to use
   
   
   int bConnected;            // are we connected to SQL Server?  1 as Connected, 0 as Disconnected
   
   // ���һ�δ���ʱ��Ĵ�����Ϣ��
   long lErrorCode;        // = SQLCODE  The SQLCODE field contains the negative SQL Server error code (the ESQL/C standard requires that error codes be negative). 
   long lErrorNumber;      // = SQLERRD1 The SQLERRD1 field contains the error number
   char szErrorMsg[80];    // The SQLERRMC field contains the text of the error message. 
   char szErrorState[6];   // SQLSTATE codes return values that are error, warning, or "no data found" messages. 

} ST_SQLDB;

typedef struct
{
   //bool bReverse;     // ��ǰҵ����Ԫ���ֽ�˳���Ƿ���Ҫ����������Ҫ��CPACK�ֶεȴ����ʱ��ʶ����

   char szSvrIP[20];  // �ϼ�������������ĵ�IP��ַ
   int  iSvrPort;     // �ϼ�������������ĵĿ��Ŷ˿ں�
   int  iHBInterval;  // ���ϼ�������������ķ��Ϳ��еȴ���Ϣ�ļ�����Ժ����

   char  szBUGroupID[12];  // ��ҵ����Ԫ���
   //int iBUnitGourpID; // ��ҵ����Ԫ���

   //TRUSERID *pUserID;  // ��ǰ���ù��ܵ�����ͻ����
   void *pSvrLink;     // ����ָ����BCC�����ӣ��������ͷ�ļ�����.sqc�����Բ�����CSvrLink��ָ��

} ST_BUNIT;  // �Ա�������ϵͳʵ��ֻ��һ��ʵ��������Ϊ��δ��ͳһ����������һ���ṹ��Ҳ��Ϊ�˼��ݽ����ܹ������ҵ����Ԫ

extern ST_BUNIT g_BUnit;  // ��ϵͳ����ESQLԵ�ʣ�ֻ��һ������Ԫʵ��


// ������: SetCol
// ���  : ������ 2004-2-8 23:26:38
// ����  : ���������CPACK���ļ�¼Ϊ0�����ý�Ҫ����Ķ�Ӧ�ֶ�
// ����  : int 
// ����  : void *handle �� ��ʱ�Ͷ�Ӧ�� TRUSERID *, �ڱ�ϵͳû�����壬��Ϊ���̵߳�Ե��
// ����  : ...  �� F_XXXXX ���������ֶ��б���END_FIELD��ʾ����
BUPUB_API int SetCol(TRUSERID *handle,...);


// ������: PutRowData
// ���  : ������ 2004-2-8 23:30:07
// ����  : �������CPACK����������һ��ST_PACK�����¼��ʵ�ʶ�֮ǰ��SetCol������ֶ���Ч��û�ж������Ч
//         ע�⾡��ʹ��PutRow������ʹ�ñ�����
// ����  : int 
// ����  : ST_PACK *pdata  �� ���ӵ�ST_PACK�������
BUPUB_API int PutRowData(ST_PACK *pdata);



// ������: AnswerData
// ���  : ������ 2004-2-8 23:32:42
// ����  : ��ruserid�Ŀͻ��ˣ�������SetCol��PutRow���õ�Ӧ�𷵻ص�����
//          ע�⣺��AnswerMode���μ�SetAnswerMode()����˵����ΪAM_AUTOʱ�򣬲���Ҫ���ñ�����
//          ������Ϊ���滹����ദ�����ǺͿͻ���Ӧ���޹صĻ�������Ե���һ�£�
//          �����ÿͻ��˳�ʱ��ȴ�
// ����  : int 
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
int AnswerData(TRUSERID *ruserid,int retcode,char *szmsg);


// ������: PutRow
// ���  : ������ 2004-2-20 10:03:04
// ����  : һ�������PutRowData �� AnswerData, ���ǲ������Ϸ��� ��Ϊ������а汾���ݣ�
// ����  : int 
// ����  : TRUSERID *handle
// ����  : ST_PACK *pdata
// ����  : int *pRetCode   �п��ܱ�cpackͷ�е�retCode���ظ��ͻ���
// ����  : char *rtnMsg
BUPUB_API int PutRow(TRUSERID *handle,ST_PACK *pdata,int *pRetCode,char *rtnMsg);

#define ADP_ROWS  50
// ������: AnswerDataPart
// ���  : ������ 2004-2-12 12:12:09
// ����  : ��AnswerData���ƣ���������֪ͨ�ͻ��ˣ����и�������ݷ���
//         �����ڽ��д��������ݷ��أ�������������ͬ����Ϊ�˲��ÿͻ��˳�ʱ��ȴ�
//         �ȷ��Ͳ������ݡ����Ѿ���100����¼��Ҫ���أ������м�¼��Ҫ���أ����״��ۼ�ADP_ROWS���͵��ñ�����
//         ע����ù�����󣬶�ͬһ���û��ˣ�����Ҫ�ٵ���AnswerData��AnswerDataPart�ˣ�
//         ��Ϊȡ�������ݺͱ�ҵ��ģ���޹��ˣ�BCC���Զ����û��˽����������ݣ���Ȼ������ģ��������㹻�ٶ�ͨ��
//         PutRow���غ�������
//   ע�⣺��Ϊ�ṩ��SetMaxRow()���������ԣ����õ��������������ͨ��SetMaxRow()�������ɡ�
// ����  : int 
// ����  : TRUSERID *ruserid
// ����  : int retcode
// ����  : char *szmsg
BUPUB_API int AnswerDataPart(TRUSERID *ruserid,int retcode,char *szmsg);

// ������: AnswerDataEx
// ���  : ������ 2004-2-8 23:37:00
// ����  : ��ruserid�Ŀͻ��ˣ�����apack��pArrays���Ӧ�𷵻ص�����
//     ע�⣺������ר��������һ���Ǳ��������󷽷��ͽ����ʱ��ʹ�ã�����֤ͨҵ��ģʽ��ʱ��
// ����  : int 
// ����  : TRUSERID *ruserid  Ŀ��ͻ��˵ı�ʶ
// ����  : ST_CPACK *apack  Ӧ������ͷ���ױ���
// ����  : ST_PACK *pArrays �������ݱ��壬��apack->head.RetCount<=1ʱ����Ч ������дΪNULL
// ����  : int retcode Ӧ�����ݵķ����� ��ӦST_CPACK��ͷ�е�RetCode
// ����  : char *szmsg ���ΪNULL�򡰡�����Ӧ�������У��Ͳ�����vsmess�ֶ�����
BUPUB_API int AnswerDataEx(TRUSERID *ruserid,ST_CPACK *apack,ST_PACK *pArrays,int retcode,char *szmsg);

// ����Ϊ�������ݵ�ʱ��pushmodeѡ�õĲ����� ��mypub.h�ж�����
//#ifndef PM_INACK 
//   #define PM_REMOVE 'X'
//   #define PM_INACK  '0'  /* �ǿɿ����� */
//   #define PM_ACK    '1'  /* �ɿ�����,��Ҫ�Է����պ�����н���ȷ�ϻص� */
//   #define PM_ANSWER '2'  /* �����������ʹ�ã���Ϊ�����͸�Ŀ��㣬�ⲿ���������Ӧ�𷵻ص�ʱ����Ҫ�ٴ��ύ��ԭʼ��BUNIT */
//#endif
// ������: PushData
// ���  : ������ 2004-2-8 23:43:01
// ����  : ��һ����Ϊ����ʽע���Ŀ��㣬�������� 
// ����  : int 
// ����  : int sourceno  ��������ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    �������ݵ�Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ը�Ŀ���Ự���κ�
// ����  : ST_CPACK *ppack  ���͵����ݰ���ppack->head.RetCount<=1�����������ݲ��ܳ���1�������¼
// ����  : char pushmode  ����ģʽ�������������PM_xxx
// ����  : int acktime   ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч  
BUPUB_API int PushData(int sourceno,int destno,int funcno,int batchno,ST_CPACK *ppack,char pushmode,int acktime);


// ������: PushDataEx
// ���  : ������ 2004-2-9 0:10:53
// ����  : ��pushdests�������Ϊ����ʽע��Ŀ�����������
// ����  : int 
// ����  : TPUSHDEST *pushdests �����Ŀ����б�
// ����  : int pdcount  Ŀ���ĸ���
// ����  : ST_CPACK *ppack ���͵Ĳ�����һ����¼�����ݰ� ע���ͷ�ϵ�ppack->head.userdata=batchno(���κ�)
// ����  : char pushmode ����ģʽ�������������PM_xxx
// ����  : int acktime  ȷ�ϻش�����ޣ�����ƣ�����PM_ACK ,PM_ANSWER ��Ч 
BUPUB_API int PushDataEx(TPUSHDEST *pushdests,int pdcount,ST_CPACK *ppack,char pushmode,int acktime);


// ������: ExtCall
// ���  : ������ 2004-3-6 17:47:14
// ����  : ������һ������㷢������Ҫ��Է�����Ӧ�𷵻أ������ܳ������ڲ�ͬϵͳ֮��ĶԽӣ���Ҫ��������Χϵͳ����
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����
// ����  : int sourceno  ʹ�õ�ͨѶƽ̨�ı�ţ��μ�TRUSERID::SourceNo
// ����  : int destno    Ŀ��ͨѶƽ̨���
// ����  : int funcno    Ŀ��������ͨѶƽ̨��ע���ͨѶ���ܺ�
// ����  : int batchno   ��Ŀ���Ự���κ� (���ȷ����Ը�Ŀ��㣬����������������ģʽ�������ֱ����дΪ0)
// ����  : int acktime   ���������Чʱ�䣬�����
// ����  : ST_CPACK *rpack  ���������
// ����  : ST_CPACK *apack  Ŀ���Ӧ������ݷ���
// ����  : ST_PACK *pArrays Ӧ�����ݺ���������
BUPUB_API int ExtCall(int sourceno,int destno,int funcno,int batchno,int acktime,ST_CPACK *rpack,ST_CPACK *apack,ST_PACK *pArrays);

// ������: ExtCallNext
// ���  : ������ 2004-3-8 17:31:47
// ����  : �ڵ���ExtCall֮�󣬷��ֶԷ��������ݻ�û��ȡ���������ñ����ܻ�ȡ��������
// ����  : int >=0:�ɹ������ص�ΪӦ�����ݰ����¼����<0:����-2:�ȴ�����Ӧ��ʱ��-1:����ͨѶ����-3:�Ѿ�ȡ���˺�������
// ����  : int acktime
// ����  : ST_CPACK *apack
// ����  : ST_PACK *pArrays
BUPUB_API int ExtCallNext(int acktime,ST_CPACK *apack,ST_PACK *pArrays);



// ������: ResetNormalCPack
// ���  : ������ 2004-3-11 20:30:59
// ����  : ���ݱ�ҵ�������������һ��CPACK��ͷ��λͼ�����ݶ��������
// ����  : void 
// ����  : ST_CPACK *pack
BUPUB_API void ResetNormalCPack(ST_CPACK *pack,unsigned char nextflag,int recCount);

// ������: CheckProcCancel
// ���  : ������ 2004-3-10 15:44:20
// ����  : ����Ƿ񱾴�������ǰ̨�Ƿ�Ҫ��ֹͣ��ע�⣺�������Ҫ����������Ƿ��и�ֹͣ������ᵼ�µ�1���룬��ʹ�ô���Ч�ʽ���
// ����  : int 1:��ʾǰ̨��Ҫ��ֹͣ�����0:û��
BUPUB_API int CheckProcCancel();

// ������: CT_ERR_DEAL
// ���  : ������ 2004-2-22 16:39:51
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ��Ϊ���뼯�н��׼��ݣ�
// ����  : int 0:�ɹ�������Ϊ��BCCͨѶ�������⣬����ҵ��ȡ������
// ����  : char *msg
// ����  : int retcode
BUPUB_API int CT_ERR_DEAL(char *msg,int retcode);


// ������: Error_Deal
// ���  : ������ 2004-2-22 16:43:34
// ����  : ���ԭ��׼����Ӧ����Ϣ������������ʱ�����ļ��м�¼��������Ϣ ������ϵͳʹ�ñ��������ԭ����ERR_DEAL
//         �ϲ���ԭ����Ҫ��sprintf����omsg
// ����  : int SendMsg������Ϣ
// ����  : int retcode
// ����  : char *omsg  OUT
// ����  : char *pFormat IN
// ����  : ... IN
BUPUB_API int Error_Deal(int retcode,char *omsg,char *pFormat,...);

// ������: SQLDebugLog
// ���  : ������ 2004-3-4 17:45:16
// ����  : ר��Ϊ��SQCʹ�ã���C��ʹ�õģ���¼��Ϣ������LOG��־��
// ����  : void 
// ����  : int errorcode
// ����  : char *pFormat
// ����  : ...
BUPUB_API void SQLDebugLog(int errorcode,char *pFormat,...);


// ������: TextLogOut
// ���  : ������ 2006-1-5 15:35:24
// ����  : ���Ѿ���ʽ���õ��ı���Ϣ�������־�ļ��У����ַ�����������ģʽ�£�Ҫ��SQLDebugLog��һ��
// ����  : void 
// ����  : int errorcode [IN]: ��Ϣ�����
// ����  : char *textlog [IN]: �ı���Ϣ
BUPUB_API void TextLogOut(int errorcode, char *textlog);

/* ****** Updated by CHENYH at 2004-2-7 20:06:13 ****** 
   If your project does not include a .sqc file that includes a main() or WinMain() function, 
   you must explicitly declare SQLCODE in one of your modules. 
   Explicit SQLCODE declarations can occur either inside 
   or outside of a host variable declaration block.
*/
/* ****** Updated by CHENYH at 2004-3-10 13:02:41 ****** 
// ����BCCӦ�����ݴ���ģʽ����CBULinkThread/CSvrLink�е�iAnswerMode
*/
#ifndef AM_AUTO
   #define AM_AUTO     'A'   // һ�������ݾʹ���Զ����͸�����ͻ���
   #define AM_CONFIRM  'C'   // ������ֻ����ҵ����Ҫ��ŷ��͸�����ͻ���,��Ҫ��AnswerData��AnswerDataPart�ŷ���
#endif
extern char iDefaultAnswerMode;   // ��ϵͳȱʡ��Ӧ��ģʽ


// ������: SetAnswerMode
// ���  : ������ 2004-3-10 18:48:18
// ����  : ����Ӧ��ģʽ����AM_xxxx�Ķ��� �������������⹦�ܵ������ʹ��
// ����  : int 
// ����  : char iAnswerMode ��AM_xxxx�Ķ���
BUPUB_API int SetAnswerMode(char iAnswerMode);


// ������: BCCMsgLogOut
// ���  : ������ 2004-3-10 19:31:25
// ����  : ��BCC���������BU���ı���־��Ϣ
// ����  : int 
// ����  : int logid ������־��ID��
// ����  : char *pFormat ���ı���־�ĸ�ʽ����
// ����  : ... ����pFormat������������
BUPUB_API int BCCMsgLogOut(int logid,char *pFormat,...);


// ������: SetMaxRow
// ���  : ������ 2004-3-22 11:41:26
// ����  : ���ñ��ι��ܴ���ʱ��ÿ��Ӧ������ص�����¼����ֻ�Ա��ι��ܴ�����Ч
// ����  : int 
// ����  : int maxrows
BUPUB_API int SetMaxRow(int maxrows);

// ������: SetBUError
// ���  : ������ 2004-3-22 11:42:37
// ����  : ���ñ�BU������Ϣ�������ṩ��ǰ�˳���
// ����  : int 
// ����  : int errcode
// ����  : char *pFormat
// ����  : ...
BUPUB_API int SetBUError(int errcode,char *pFormat,...);


// ������: SetAnswerTimeout
// ���  : ������ 2004-3-22 12:49:02
// ����  : �趨��ҵ��ÿ��Ӧ����ĳ�ʱʱ�䣬�Ժ���ƣ���������������ʱ������Ĵ���
// ����  : int 
// ����  : unsigned int atimeout  ָ���ĳ�ʱʱ�䣨�Ժ���ƣ�
BUPUB_API int SetAnswerTimeout(unsigned int atimeout);


// ������: ResetAnswerData
// ���  : ������ 2004-3-24 22:16:17
// ����  : ��������Ѿ��ύ��Ӧ�����ݣ�����������ִ��һ������������Ϊ����������Retry
// ����  : int 
BUPUB_API int ResetAnswerData();


#ifdef __cplusplus
}
#endif

#undef BUPUB_API

#endif
