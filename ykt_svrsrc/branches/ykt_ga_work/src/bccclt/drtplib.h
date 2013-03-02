/* ------------------------------------------------------------------------- */
/*
drtplib.h

�������ڣ�	2003/9/13
���ߣ�		qzh
�汾��Ϣ��	V4.0.1
���ܣ�      ͨѶƽ̨�ӿں���
*/
/* ------------------------------------------------------------------------- */
#ifndef __DRTPLIB_H__
#define __DRTPLIB_H__

#include "mytypes.h"

#define PROXY_SOCK5        3

typedef struct tag_drtphandle
{
	char buf[28];
}TAG_DRTPHANDLE;

typedef struct tag_drtphandle_ext
{
	char buf[32];
}TAG_DRTPHANDLE_EXT;

#ifdef __cplusplus
extern "C" {
#endif

// ������: DrtpInit
// ���  : qianzhenghua 2005-01-24 12:12:35
// ����  : ��ʼ��ͨѶƽ̨����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int *errcode *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpInit(int *errcode,char *errormessage);

// ������: DrtpSetProxy
// ���  : qianzhenghua 2005-01-24 12:13:30
// ����  : ����SOCKS5���������
// ����  : BOOL 
// ����  : int proxytype ������������ͣ�Ŀǰֻ֧��SOCK5���������
// ����  : char *ip �����������ַ���������
// ����  : int port ����������˿ڣ��������
// ����  : char *user ����������û����������
// ����  : char *pwd ����������û����룬�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpSetProxy(int proxytype,char *ip,int port,char *user,char *pwd,int *errcode,char *errormessage);

// ������: DrtpConnect
// ���  : qianzhenghua 2005-01-24 12:15:31
// ����  : ������ͨѶƽ̨������
// ����  : int �ɹ�ʱ���ش���0�����Ӿ����-1��ʾ��������
// ����  : char *ip ͨѶƽ̨��ַ���������
// ����  : int port ͨѶƽ̨�˿ڣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=-1 �ⲿ�ṩ��SOCK���ӣ�-1��ʾʹ���ڲ���SOCK���ӣ��������
int DrtpConnect(char *ip,int port,int *errcode,char *errormessage,int handle=-1);

// ������: DrtpReConnect
// ���  : qianzhenghua 2005-01-24 12:18:03
// ����  : ��������ͨѶƽ̨
// ����  : BOOL BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpReConnect(int handle,int *errcode,char *errormessage);

// ������: DrtpAddFunction
// ���  : qianzhenghua 2005-01-24 12:19:07
// ����  : ��ͨѶƽ̨ע������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int function ����ţ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=0 ͨѶƽ̨���Ӿ�������������-1��ʾ����������ע������
BOOL DrtpAddFunction(int function,int *errcode,char *errormessage,int handle=0);

// ������: DrtpDelFunction
// ���  : qianzhenghua 2005-01-24 12:20:51
// ����  : ȡ�������ϵķ����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int function ����ţ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=0 ͨѶƽ̨���Ӿ��,-1��������������ȡ������ţ��������
BOOL DrtpDelFunction(int function,int *errcode,char *errormessage,int handle=0);

// ������: DrtpBlind
// ���  : qianzhenghua 2005-01-24 12:23:15
// ����  : ��ֹ�����ϵķ����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,-1�������������Ͻ�ֹ����ţ��������
BOOL DrtpBlind(int *errcode,char *errormessage,int handle=-1);

// ������: DrtpLight
// ���  : qianzhenghua 2005-01-24 12:24:43
// ����  : ���������ϵķ����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,-1�������������ϼ������ţ��������
BOOL DrtpLight(int *errcode,char *errormessage,int handle=-1);

// ������: DrtpCheckMessage
// ���  : qianzhenghua 2005-01-24 12:25:42
// ����  : ���ͨѶƽ̨�������Ƿ�������
// ����  : int ���������ݵ����Ӿ����-1��ʾ�����˴���
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,-1�������������ϼ��,�������
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
int DrtpCheckMessage(int *errcode,char *errormessage,int handle=-1,int timeout=-1);

// ������: DrtpCheckSlotMessage
// ���  : qianzhenghua 2005-01-24 12:25:42
// ����  : ���slot�������Ƿ�������
// ����  : int ���������ݵ�Slot���Ӿ����-1��ʾ�����˴���
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=-1 Slot���Ӿ��,-1��������Slot�����ϼ��,�������
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
int DrtpCheckSlotMessage(int *errcode,char *errormessage,int handle=-1,int timeout=-1);

// ������: DrtpCheckAllMessage
// ���  : qianzhenghua 2005-01-24 12:25:42
// ����  : ����������Ƿ�������
// ����  : int ���������ݵ����Ӿ����-1��ʾ�����˴���
// ����  : int *type ���ӵ����ͣ�1ΪͨѶƽ̨���ӣ�2ΪSLOT���ӣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=-1 ���Ӿ��,-1�������������ϼ��,�������
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
int DrtpCheckAllMessage(int *type,int *errcode,char *errormessage,int handle=-1,int timeout=-1);

// ������: DrtpPostMessage
// ���  : qianzhenghua 2005-01-24 12:29:08
// ����  : ��ͨѶƽ̨��ź͹��ܺŷ�������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int primary ���ȼ���1��5��1Ϊ��ߣ��������
// ����  : int branchno ͨѶƽ̨�ڵ���룬�������
// ����  : int function ����ţ��������
// ����  : char *message ��Ϣ���ݣ����Ϊ8000���������
// ����  : int messagelen ��Ϣ���ݳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle ͨѶƽ̨���Ӿ��,�������
// ����  : int hook=0 �����ı�ǣ��������
// ����  : int ackmode=0 ȷ��ģʽ,���������0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,3--Ӧ�÷���������ȷ��
// ����  : int zip=2 ѹ����ʽ�����������0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
BOOL DrtpPostMessage(int primary,int branchno,int function,char *message,int messagelen,
					 int *errcode,char *errormessage,int handle,int hook=0,
					 int ackmode=0,int zip=2);

// ������: DrtpPostAllMessage
// ���  : qianzhenghua 2005-06-18 12:29:08
// ����  : ��ͨѶƽ̨��ź͹��ܺŹ㲥����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int primary ���ȼ���1��5��1Ϊ��ߣ��������
// ����  : int branchno ͨѶƽ̨�ڵ���룬�������
// ����  : int function ����ţ��������
// ����  : char *message ��Ϣ���ݣ����Ϊ8000���������
// ����  : int messagelen ��Ϣ���ݳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle ͨѶƽ̨���Ӿ��,�������
// ����  : int hook=0 �����ı�ǣ��������
// ����  : int zip=2 ѹ����ʽ�����������0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
BOOL DrtpPostAllMessage(int primary,int branchno,int function,char *message,int messagelen,
					 int *errcode,char *errormessage,int handle,int hook=0,int zip=2);

// ������: DrtpSendMessage
// ���  : qianzhenghua 2005-01-24 12:33:03
// ����  : �������ݵ��̶���ͨѶƽ̨����ڵ�
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : char *message ��Ϣ���ݣ����Ϊ8000���������
// ����  : int messagelen ��Ϣ���ݳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : TAG_DRTPHANDLE *drtphandle ͨѶƽ̨ͨѶ������,�����������DrtpReadMessage��DrtpAttachServer�õ�
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,���������-1Ϊʹ��drtphandle�е����Ӿ��
// ����  : int hook=0 �����ı�ǣ��������
// ����  : int ackmode=0 ȷ��ģʽ,���������0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,3--Ӧ�÷���������ȷ��
// ����  : int primary=-1 ���ȼ���1��5��1Ϊ��ߣ����������-1��ʾʹ��drtphandle�е����ȼ�
// ����  : int zip=2 ѹ����ʽ�����������0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
BOOL DrtpSendMessage(char *message,int messagelen,int *errcode,char *errormessage,
					 TAG_DRTPHANDLE *drtphandle,int handle=-1,int hook=0,int ackmode=0,
					 int primary=-1,int zip=2);

// ������: DrtpTransMessage
// ���  : qianzhenghua 2005-01-24 12:36:19
// ����  : ��ͨѶƽ̨��ź͹��ܺ�ת������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int branchno ͨѶƽ̨�ڵ���룬�������
// ����  : int function ����ţ��������
// ����  : char *message ��Ϣ���ݣ����Ϊ8000���������
// ����  : int messagelen ��Ϣ���ݳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : TAG_DRTPHANDLE *drtphandle *drtphandle ͨѶƽ̨ͨѶ������,�����������DrtpReadMessage��DrtpAttachServer�õ�
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,���������-1Ϊʹ��drtphandle�е����Ӿ��
// ����  : int hook=0 �����ı�ǣ��������
// ����  : int ackmode=0 ȷ��ģʽ,���������0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,3--Ӧ�÷���������ȷ��
// ����  : int primary=-1 ���ȼ���1��5��1Ϊ��ߣ����������-1��ʾʹ��drtphandle�е����ȼ�
// ����  : int zip=2 ѹ����ʽ�����������0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
BOOL DrtpTransMessage(int branchno,int function,char *message,int messagelen,
					  int *errcode,char *errormessage,TAG_DRTPHANDLE *drtphandle,
					  int handle=-1,int hook=0,int ackmode=0,int primary=-1,int zip=2);

// ������: DrtpReadMessage
// ���  : qianzhenghua 2005-01-24 12:39:13
// ����  : ��ȡ�ض������ϵ�����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : char *message ��Ϣ����������Ҫ8192�ĳ��ȣ��������
// ����  : int messagebufsize ��Ϣ�������ĳ��ȣ��������
// ����  : int* messagelen ��Ϣ�ĳ��ȣ��������
// ����  : int handle ͨѶƽ̨���ӣ��������
// ����  : TAG_DRTPHANDLE *drtphandle �����ͨѶƽ̨ͨѶ�����ģ���Ҫ���ⲿ���䣬�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
BOOL DrtpReadMessage(char *message,int messagebufsize,int* messagelen,int handle,
					 TAG_DRTPHANDLE *drtphandle,int *errcode,char *errormessage,
					 int timeout=-1);

// ������: DrtpReadMessageExt
// ���  : qianzhenghua 2005-01-24 12:39:13
// ����  : ��ȡ�ض������ϵ�����
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : char *message ��Ϣ����������Ҫ8192�ĳ��ȣ��������
// ����  : int messagebufsize ��Ϣ�������ĳ��ȣ��������
// ����  : int* messagelen ��Ϣ�ĳ��ȣ��������
// ����  : int handle ͨѶƽ̨���ӣ��������
// ����  : TAG_DRTPHANDLE_EXT *drtphandle �����ͨѶƽ̨ͨѶ�����ģ���Ҫ���ⲿ���䣬�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
BOOL DrtpReadMessageExt(char *message,int messagebufsize,int* messagelen,int handle,
					 TAG_DRTPHANDLE_EXT *drtphandle,int *errcode,char *errormessage,
					 int timeout=-1);

// ������: DrtpAttachServer
// ���  : qianzhenghua 2005-01-24 12:43:01
// ����  : �����ӵ��ض��ķ���
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int branchno ͨѶƽ�Ƚڵ���룬�������
// ����  : int function ͨѶƽ̨����ţ��������
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : TAG_DRTPHANDLE *drtphandle �����ͨѶƽ̨ͨѶ�����ģ���Ҫ���ⲿ���䣬�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpAttachServer(int branchno,int function,int handle,TAG_DRTPHANDLE *drtphandle,
					  int *errcode,char *errormessage);

// ������: DrtpPing
// ���  : qianzhenghua 2005-01-24 12:44:47
// ����  : ���ͨѶƽ̨������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpPing(int handle,int *errcode,char *errormessage);

// ������: DrtpQueryRequest
// ���  : qianzhenghua 2005-01-24 12:45:41
// ����  : ��ѯͨѶƽ̨���ڲ���Ϣ����hi=0 and low=0ʱ����ѯ�������ڵ�ͨѶƽ̨����Ϣ
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int hi �ڲ��ڵ��Ÿ�4�ֽڣ��������
// ����  : int low �ڲ��ڵ��ŵ�4�ֽڣ��������
// ����  : int cmd ��ѯ������,�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle ͨѶƽ̨���Ӿ�����������
BOOL DrtpQueryRequest(int hi,int low,int cmd,int *errcode,char *errormessage,int handle);

// ������: DrtpQueryResult
// ���  : qianzhenghua 2005-01-24 12:48:21
// ����  : ��ȡ��ѯͨѶƽ̨�����Ľ��
// ����  : int ���ش���0��ʾ���������ݣ�0��ʾû�к������ݣ�-1Ϊ�����˴���
// ����  : char* message ��Ų�ѯ����Ļ���������Ҫ8192�ֽڣ��������
// ����  : int messagesize ��Ų�ѯ����Ļ������ĳ��ȣ��������
// ����  : int *messagelen ��ѯ����ĳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
int DrtpQueryResult(char* message,int messagesize,int *messagelen,int *errcode,char *errormessage,int handle,int timeout=-1);

// ������: DrtpGetHook
// ���  : qianzhenghua 2005-01-24 12:50:53
// ����  : ��ȡhook
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : int *hook �������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage  ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpGetHook(int handle,int *hook,int *errcode,char *errormessage);

// ������: DrtpGetHandle
// ���  : qianzhenghua 2005-01-24 12:53:34
// ����  : ��ȡͨѶƽ̨���ӵ�ͨѶ������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : TAG_DRTPHANDLE *drtphandle ͨѶƽ̨ͨѶ������,�е����߷��䣬�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpGetHandle(int handle,TAG_DRTPHANDLE *drtphandle,int *errcode,char *errormessage);

// ������: DrtpClose
// ���  : qianzhenghua 2005-01-24 12:55:04
// ����  : �ر�ͨѶƽ̨������
// ����  : void 
// ����  : int handle=-1 ͨѶƽ̨���Ӿ����handle=-1Ϊ�ر��������ӣ��������
// ����  : bool flag=false ������ȫ���ص����Ƿ��ͷ�ͨѶƽ̨������falseΪ���ͷţ��������
void DrtpClose(int handle=-1,bool flag=false);

// ������: DrtpExit
// ���  : qianzhenghua 2005-01-24 12:55:51
// ����  : �ͷ�ͨѶƽ̨����
// ����  : void 
void DrtpExit();

/*�ڲ�ʹ�õĺ���*/
int DrtpListen(int port,int *errcode,char* errormessage);
int DrtpAccept(int handle,int *errcode,char *errormessage);
BOOL DrtpCheckSSL(int handle,int crypto,int *errcode,char *errormessage);
BOOL DrtpIsLogined(int handle);
void DrtpSetLogined(int handle,char *user,char *pwd);
BOOL DrtpGetUserPwd(int handle,char *user,char *pwd);
BOOL DrtpSetLocation(int handle,int location,int windowsize);
BOOL DrtpGetLocation(int handle,int *location,int *windowsize);
int DrtpNewHandle();
void DrtpDelHandle(int handle);
int DrtpPeerHandle(TAG_DRTPHANDLE *drtphandle);


// ������: DrtpAddSlot
// ���  : qianzhenghua 2005-02-05 11:14:41
// ����  : ��ͨѶƽ̨��ע��ͨѶ��
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int slot ͨѶ�ۺţ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int handle=0 ͨѶƽ̨���Ӿ�������������-1��ʾ����������ע��ͨѶ��
BOOL DrtpAddSlot(int slot,int *errcode,char *errormessage,int handle=0);

// ������: DrtpGetSlotHandle
// ���  : qianzhenghua 2005-02-05 11:18:33
// ����  : ��ȡͨѶ�����½���������
// ����  : int �ɹ�ʱ����������ţ�����-1��ʾ�����˴���
// ����  : int handle ͨѶƽ̨���ӣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
int DrtpGetSlotHandle(int handle,int *errcode,char *errormessage,int timeout=-1);

// ������: DrtpSlotSendMessage
// ���  : qianzhenghua 2005-02-05 11:22:59
// ����  : ʹ��ͨѶ�۷�������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : char *message ��Ϣ���ݣ����Ϊ8000���������
// ����  : int messagelen ��Ϣ���ݳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int slothandle ͨѶ�����Ӿ�����������
// ����  : int zip=2 ѹ����ʽ�����������0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
BOOL DrtpSlotSendMessage(char *message,int messagelen,int *errcode,char *errormessage,
						 int slothandle,int zip=2);

// ������: DrtpSlotReadMessage
// ���  : qianzhenghua 2005-02-05 11:25:39
// ����  : ʹ��ͨѶ�۽�������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : char *message ��Ϣ����������Ҫ8192�ĳ��ȣ��������
// ����  : int messagebufsize ��Ϣ�������ĳ��ȣ��������
// ����  : int* messagelen ��Ϣ�ĳ��ȣ��������
// ����  : int handle ͨѶ�����Ӿ�����������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
BOOL DrtpSlotReadMessage(char *message,int messagebufsize,int* messagelen,int handle,
						 int *errcode,char *errormessage,int timeout=-1);

// ������: DrtpLinkSlot
// ���  : qianzhenghua 2005-02-05 12:43:55
// ����  : ������ͨѶ�۵�����
// ����  : int �ɹ�ʱ����������ţ�����-1��ʾ�����˴���
// ����  : char *ip ͨѶƽ̨ip��ַ���������
// ����  : int port ͨѶƽ̨�˿ڣ��������
// ����  : int branchno  ͨѶƽ̨�ڵ���룬�������
// ����  : int slot ͨѶ�ۺţ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : int timeout=-1 �ȴ����ݵĳ�ʱ����λΪ���룬-1Ϊ���޵ȴ����������
int DrtpLinkSlot(char *ip,int port,int branchno,int slot,int *errcode,
				 char *errormessage,int timeout=-1);

// ������: DrtpCloseConnect
// ���  : Ǯ���� 2005-5-8 17:48:09
// ����  : �ر��ض�������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : int x Ŀ��ڵ��Ÿ�λ,�������,0��ʾ����ڵ�
// ����  : int y Ŀ��ڵ��ŵ�λ,�������,0��ʾ����ڵ�
// ����  : int connectno ���Ӻ�,�������
// ����  : int timestamp ����ʱ��,�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpCloseConnect(int handle,int x,int y,int connectno,int timestamp,int *errcode,char *errormessage);

// ������: DrtpCheckConnect
// ���  : Ǯ���� 2005-5-8 17:48:09
// ����  : ����ض�������
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���Ӿ�����������
// ����  : int x Ŀ��ڵ��Ÿ�λ,�������,0��ʾ����ڵ�
// ����  : int y Ŀ��ڵ��ŵ�λ,�������,0��ʾ����ڵ�
// ����  : int connectno ���Ӻ�,�������
// ����  : int timestamp ����ʱ��,�������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpCheckConnect(int handle,int x,int y,int connectno,int timestamp,int *errcode,char *errormessage);

// ������: DrtpGetConnectInfo
// ���  : Ǯ���� 2005-5-8 17:54:05
// ����  : ��drtphandle�л�ȡԴ������Ϣ
// ����  : void 
// ����  : TAG_DRTPHANDLE *drtphandle DrtpReadMessage�ķ���,Ϊ�������
// ����  : int *x Ŀ��ڵ��Ÿ�λ,�������
// ����  : int *y Ŀ��ڵ��ŵ�λ,�������
// ����  : int *connectno ���Ӻ�,�������
// ����  : int *timestamp ����ʱ��,�������
void DrtpGetConnectInfo(TAG_DRTPHANDLE *drtphandle,int *x,int *y,int *connectno,int *timestamp);


// ������: DrtpGetVersion
// ���  : Ǯ���� 2005-6-18 9:12:55
// ����  : ��ýӿڵİ汾
// ����  : void 
// ����  : char *version �����������Ҫ50���ֽڵĿռ�
void DrtpGetVersion(char *version);


// ������: DrtpGetHandleInfo
// ���  : Ǯ���� 2005-9-6 16:41:13
// ����  : ��ȡ���ӵ��ڲ���Ϣ
// ����  : BOOL handle���ڷ���TRUE,���򷵻�FALSE
// ����  : int handle ͨѶƽ̨���ӣ��������
// ����  : int *branchno ���ӵ�ͨѶƽ̨�ڵ��,�������
// ����  : int *hi ���ӵ�ͨѶƽ̨�ڵ��ڲ���Ÿ�λ,�������
// ����  : int *low ���ӵ�ͨѶƽ̨�ڵ��ڲ���ŵ�λ,�������
// ����  : int *socketno ���ӵ�socket,�������
// ����  : int *timestamp ���ӵĽ���ʱ�����,�������
BOOL DrtpGetHandleInfo(int handle,int *branchno,int *hi,int *low,int *socketno,int *timestamp);

// ������: DrtpSetBusy
// ���  : Ǯ���� 2006-4-11 9:30:11
// ����  : �������ӵ�æµ��־
// ����  : BOOL �ɹ�����TRUE,ʧ�ܷ���FALSE
// ����  : int handle ͨѶƽ̨���ӣ��������,-1��ʾ�������е�����
// ����  : int busy	æµ����������������ڵ���0����λΪ��
// ����  : int multi ���ʣ����������������1
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpSetBusy(int handle,int busy,int multi,int *errcode,char *errormessage);

// ������: DrtpSetBusyExt
// ���  : Ǯ���� 2006-4-11 9:30:11
// ����  : �������ӵ�æµ��־
// ����  : BOOL �ɹ�����TRUE,ʧ�ܷ���FALSE
// ����  : int handle ͨѶƽ̨���ӣ��������,-1��ʾ�������е�����
// ����  : int x Ŀ��ڵ��Ÿ�λ,�������,0��ʾ����ڵ�
// ����  : int y Ŀ��ڵ��ŵ�λ,�������,0��ʾ����ڵ�
// ����  : int connectno ���Ӻ�,�������
// ����  : int timestamp ����ʱ��,�������
// ����  : int busy	æµ����������������ڵ���0����λΪ��
// ����  : int multi ���ʣ����������������1
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
BOOL DrtpSetBusyExt(int handle,int x,int y,int connectno,int timestamp,int busy,int multi,int *errcode,char *errormessage);

#define CERTIFY_BEFORE		1	
//������Ҫ��֤�����ϸ��Է�
#define CERTIFY_AFTER		2
//����Է���������֤����


// ������: CertifyHandle
// ���  : Ǯ���� 2006-4-17 15:25:26
// ����  : ��ҵĴ�����
// ����  : BOOL ͨ������TRUE,���򷵻�FALSE
// ����  : char *certifydata	��֤�����ݣ�������֤�������
// ����  : int  *certifydatalength	���ݵĳ���
typedef BOOL (* CertifyHandle)(char *certifydata,int *certifydatalength);


// ������: DrtpSetCertifyHandle
// ���  : Ǯ���� 2006-4-17 15:21:06
// ����  : ������֤����ӿ�
// ����  : void 
// ����  : int type ��������,���������ֻ����CERTIFY_BEFORE��CERTIFY_AFTER
// ����  : CertifyHandle fhandle ���������������
void DrtpSetCertifyHandle(int type,CertifyHandle fhandle);

// ������: DrtpCertifyOk
// ���  : Ǯ���� 2006-4-17 15:21:06
// ����  : ��֤ͨ������Ӧ
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : char *certifyblock ����֤���ݣ����Ϊ8000���������
// ����  : int certifyblocklen ����֤���ݳ��ȣ��������
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : TAG_DRTPHANDLE *drtphandle ͨѶƽ̨ͨѶ������,�����������DrtpReadMessage��DrtpAttachServer�õ�
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,���������-1Ϊʹ��drtphandle�е����Ӿ��
BOOL DrtpCertifyOk(char *certifyblock,int certifyblocklen,int *errcode,char *errormessage,
					 TAG_DRTPHANDLE *drtphandle,int handle=-1);

// ������: DrtpCertifyFail
// ���  : Ǯ���� 2006-4-17 15:21:06
// ����  : ��֤ͨ������Ӧ
// ����  : BOOL �ɹ�ʱ����TRUE,���򷵻�FALSE
// ����  : int reasoncode ʧ�ܷ��صĴ���
// ����  : char *reasonmsg ʧ�ܷ��ص�����������������������Ϊ300
// ����  : int *errcode ʧ��ʱ���صĴ�����룬Ϊ�������
// ����  : char *errormessage ʧ��ʱ���صĴ���������Ϊ�������,����Ϊ300
// ����  : TAG_DRTPHANDLE *drtphandle ͨѶƽ̨ͨѶ������,�����������DrtpReadMessage��DrtpAttachServer�õ�
// ����  : int handle=-1 ͨѶƽ̨���Ӿ��,���������-1Ϊʹ��drtphandle�е����Ӿ��
BOOL DrtpCertifyFail(int reasoncode,char *reasonmsg,int *errcode,char *errormessage,
					 TAG_DRTPHANDLE *drtphandle,int handle=-1);
#ifdef __cplusplus
}
#endif

#endif