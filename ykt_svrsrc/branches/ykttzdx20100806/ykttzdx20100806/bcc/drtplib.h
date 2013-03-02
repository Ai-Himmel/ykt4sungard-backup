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

#ifdef __cplusplus
extern "C" {
#endif

/*
��ʼ��ͨѶƽ̨����
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
*/
BOOL DrtpInit(long *errcode,char *errormessage);

/*
����SOCKS5���������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
ip:�����������ַ
port:����������˿�
*/
BOOL DrtpSetProxy(long proxytype,char *ip,long port,char *user,char *pwd,long *errcode,char *errormessage);

/*
������ͨѶƽ̨������
�ɹ�ʱ���ش���0�����Ӿ��,���򷵻�-1,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
ip:ͨѶƽ̨��ַ
port:ͨѶƽ̨�˿�
*/
long DrtpConnect(char *ip,long port,long *errcode,char *errormessage,long handle=-1);

/*
��������ͨѶƽ̨
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpReConnect(long handle,long *errcode,char *errormessage);

/*
��ͨѶƽ̨ע������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
function:�����
handle:ͨѶƽ̨���Ӿ��,handle=-1,��������������ע������
*/
BOOL DrtpAddFunction(long function,long *errcode,char *errormessage,long handle=0);

/*
ȡ����ͨѶƽ̨�ϵķ����
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
function:�����
handle:ͨѶƽ̨���Ӿ��,handle=-1,��������������ȡ�������
*/
BOOL DrtpDelFunction(long function,long *errcode,char *errormessage,long handle=0);

/*
��ֹ������ͨѶƽ̨�ϵķ���
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��,handle=-1,�������������Ͻ�ֹ����
*/
BOOL DrtpBlind(long *errcode,char *errormessage,long handle=-1);

/*
����������ͨѶƽ̨�ϵķ���
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��,handle=-1,�������������ϼ������
*/
BOOL DrtpLight(long *errcode,char *errormessage,long handle=-1);

/*
����������Ƿ�������,
�ɹ�ʱ���ش���0�����Ӿ��,���򷵻�-1,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��
*/
long DrtpCheckMessage(long *errcode,char *errormessage,long handle);

/*
��ͨѶƽ̨��ź͹��ܺŷ�������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
primary:���ݵ����ȼ�,��Ϊ1,2,3,4,5
branchno:ͨѶƽ̨���(��ͨѶƽ̨�ı������)
function:�����
message:���͵�����
messagelen:���͵����ݵĳ���
handle:ͨѶƽ̨���Ӿ��
hook:�����ı��
ackmode:ȷ��ģʽ,0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,
				3--Ӧ�÷���������ȷ��
*/
BOOL DrtpPostMessage(long primary,long branchno,long function,char *message,
					 long messagelen,long *errcode,char *errormessage,
					 long handle,long hook=0,long ackmode=0);

/*
�������ݵ��̶���ͨѶƽ̨����ڵ�,
����̶��Ľڵ㣬������ͨ��DrtpAttach��õģ���������һ���յ������ݵķ��ͽڵ�
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
primary:���ݵ����ȼ�,��Ϊ1,2,3,4,5
message:���͵�����
messagelen:���͵����ݵĳ���
drtphandle:ͨѶƽ̨ͨѶ������,��DrtpReadMessage��DrtpAttachServer�õ�
hook:�����ı��
ackmode:ȷ��ģʽ,0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,
				3--Ӧ�÷���������ȷ��
*/
BOOL DrtpSendMessage(char *message,long messagelen,long *errcode,
					 char *errormessage,TAG_DRTPHANDLE *drtphandle,long hook=0,
					 long ackmode=0,long primary=-1);

/*
��ͨѶƽ̨��ź͹��ܺ�ת������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
primary:���ݵ����ȼ�,��Ϊ1,2,3,4,5
branchno:ͨѶƽ̨���(��ͨѶƽ̨�ı������)
function:�����
message:���͵�����
messagelen:���͵����ݵĳ���
drtphandle:ͨѶƽ̨ͨѶ������,��DrtpReadMessage��DrtpAttachServer�õ�
hook:�����ı��
ackmode:ȷ��ģʽ,0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,
				3--Ӧ�÷���������ȷ��
*/
BOOL DrtpTransMessage(long branchno,long function,char *message,
					  long messagelen,long *errcode,char *errormessage,
					  TAG_DRTPHANDLE *drtphandle,long hook=0,long ackmode=0,long primary=-1);

/*
��ȡ�ض������ϵ�����
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
message:���Խ������ݵ�buffer
messagebufsize:�������ݵ�buffer�ĳ���
messagelen:��ȡ�������ݵĳ���
timeout:�������ĳ�ʱʱ��(��λ�Ǻ���)��-1Ϊ������
handle:ͨѶƽ̨���Ӿ��
drtphandle:ͨѶƽ̨ͨѶ������,�е����߷���
hook:���������޷�����ʱ���صı��
*/
BOOL DrtpReadMessage(char *message,long messagebufsize,long* messagelen,
					 long handle,TAG_DRTPHANDLE *drtphandle,
					 long *errcode,char *errormessage,long timeout=-1);

/*
�����ӵ��ض��ķ���
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
branchno:ͨѶƽ̨���(��ͨѶƽ̨�ı������)
function:�����
handle:ͨѶƽ̨���Ӿ��
drtphandle:ͨѶƽ̨ͨѶ������,�е����߷���
*/
BOOL DrtpAttachServer(long branchno,long function,long handle,
					  TAG_DRTPHANDLE *drtphandle,
					  long *errcode,char *errormessage);

/*
���ͨѶƽ̨������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpPing(long handle,long *errcode,char *errormessage);

/*
��ѯͨѶƽ̨���ڲ���Ϣ
��hi=0 and low=0ʱ����ѯ�������ڵ�ͨѶƽ̨����Ϣ,
�������(hi,low)��Ӧ��ͨѶƽ̨����Ϣ
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
hi:ͨѶƽ̨�ڵ��Ÿ�4λ
low:ͨѶƽ̨�ڵ��ŵ�4λ
cmd:��ѯ������ָ��(1,2,3,4,5,6,7)
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpQueryRequest(long hi,long low,long cmd,long *errcode,char *errormessage,long handle);

/*
��ȡ��ѯͨѶƽ̨�����Ľ��
�ɹ�ʱ���� >= 0,���򷵻�-1,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ,����0,��ʾ����û�м�¼
message:���Խ������ݵ�buffer
messagebufsize:�������ݵ�buffer�ĳ���
messagelen:��ȡ�������ݵĳ���
timeout:�������ĳ�ʱʱ��(��λ�Ǻ���)��-1Ϊ������
handle:ͨѶƽ̨���Ӿ��
*/
long DrtpQueryResult(char* message,long messagesize,long *messagelen,long *errcode,char *errormessage,long handle,long timeout=-1);

/*
��ȡhook
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
drtphandle:ͨѶƽ̨ͨѶ������,��DrtpReadMessage��DrtpAttachServer�õ�
hook:��������
*/
BOOL DrtpGetHook(long handle,long *hook,long *errcode,char *errormessage);

/*
��ȡͨѶƽ̨���ӵ�ͨѶ������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
drtphandle:ͨѶƽ̨ͨѶ������,�е����߷���
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpGetHandle(long handle,TAG_DRTPHANDLE *drtphandle,long *errcode,char *errormessage);

/*
�ر�ͨѶƽ̨������
handle:ͨѶƽ̨���Ӿ����handle=-1Ϊ�ر���������
flag:������ȫ���ص����Ƿ��ͷ�ͨѶƽ̨����
*/
void DrtpClose(long handle=-1,bool flag=false);

/*
�ͷ�ͨѶƽ̨����
*/
void DrtpExit();

/*�ڲ�ʹ�õĺ���*/
long DrtpListen(long port,long *errcode,char* errormessage,bool local=false);
long DrtpAccept(long handle,long *errcode,char *errormessage);
BOOL DrtpCheckSSL(long handle,long crypto,long *errcode,char *errormessage);
BOOL DrtpIsLogined(long handle);
void DrtpSetLogined(long handle,char *user,char *pwd);
BOOL DrtpGetUserPwd(long handle,char *user,char *pwd);
long DrtpNewHandle();
void DrtpDelHandle(long handle);

#ifdef __cplusplus
}
#endif

#endif