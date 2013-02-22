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
BOOL DrtpInit(int *errcode,char *errormessage);

/*
����SOCKS5���������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
ip:�����������ַ
port:����������˿�
*/
BOOL DrtpSetProxy(int proxytype,char *ip,int port,char *user,char *pwd,int *errcode,char *errormessage);

/*
������ͨѶƽ̨������
�ɹ�ʱ���ش���0�����Ӿ��,���򷵻�-1,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
ip:ͨѶƽ̨��ַ
port:ͨѶƽ̨�˿�
*/
int DrtpConnect(char *ip,int port,int *errcode,char *errormessage,int handle=-1);

/*
��������ͨѶƽ̨
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpReConnect(int handle,int *errcode,char *errormessage);

/*
��ͨѶƽ̨ע������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
function:�����
handle:ͨѶƽ̨���Ӿ��,handle=-1,��������������ע������
*/
BOOL DrtpAddFunction(int function,int *errcode,char *errormessage,int handle=0);

/*
ȡ����ͨѶƽ̨�ϵķ����
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
function:�����
handle:ͨѶƽ̨���Ӿ��,handle=-1,��������������ȡ�������
*/
BOOL DrtpDelFunction(int function,int *errcode,char *errormessage,int handle=0);

/*
��ֹ������ͨѶƽ̨�ϵķ���
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��,handle=-1,�������������Ͻ�ֹ����
*/
BOOL DrtpBlind(int *errcode,char *errormessage,int handle=-1);

/*
����������ͨѶƽ̨�ϵķ���
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��,handle=-1,�������������ϼ������
*/
BOOL DrtpLight(int *errcode,char *errormessage,int handle=-1);

/*
����������Ƿ�������,
�ɹ�ʱ���ش���0�����Ӿ��,���򷵻�-1,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��
*/
int DrtpCheckMessage(int *errcode,char *errormessage,int handle);

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
zip��ѹ����ʽ��0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
*/
BOOL DrtpPostMessage(int primary,int branchno,int function,char *message,
					 int messagelen,int *errcode,char *errormessage,
					 int handle,int hook=0,int ackmode=0,int zip=2);

/*
�������ݵ��̶���ͨѶƽ̨����ڵ�,
����̶��Ľڵ㣬������ͨ��DrtpAttach��õģ���������һ���յ������ݵķ��ͽڵ�
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
primary:���ݵ����ȼ�,��Ϊ1,2,3,4,5
message:���͵�����
messagelen:���͵����ݵĳ���
drtphandle:ͨѶƽ̨ͨѶ������,��DrtpReadMessage��DrtpAttachServer�õ�
handle:ͨѶƽ̨���Ӿ��,-1Ϊʹ��drtphandle�е����Ӿ��
hook:�����ı��
ackmode:ȷ��ģʽ,0--����Ҫȷ��,1--�����ͨѶƽ̨����ȷ��,2--�յ��ͨѶƽ̨����ȷ��,
				3--Ӧ�÷���������ȷ��
zip��ѹ����ʽ��0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
*/
BOOL DrtpSendMessage(char *message,int messagelen,int *errcode,
					 char *errormessage,TAG_DRTPHANDLE *drtphandle,int hook=0,
					 int handle=-1,int ackmode=0,int primary=-1,int zip=2);

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
zip��ѹ����ʽ��0����ѹ����1��ѹ����2����ͨѶƽָ̨��ѹ��
*/
BOOL DrtpTransMessage(int branchno,int function,char *message,
					  int messagelen,int *errcode,char *errormessage,
					  TAG_DRTPHANDLE *drtphandle,int hook=0,int ackmode=0,int primary=-1,int zip=2);

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
BOOL DrtpReadMessage(char *message,int messagebufsize,int* messagelen,
					 int handle,TAG_DRTPHANDLE *drtphandle,
					 int *errcode,char *errormessage,int timeout=-1);

/*
�����ӵ��ض��ķ���
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
branchno:ͨѶƽ̨���(��ͨѶƽ̨�ı������)
function:�����
handle:ͨѶƽ̨���Ӿ��
drtphandle:ͨѶƽ̨ͨѶ������,�е����߷���
*/
BOOL DrtpAttachServer(int branchno,int function,int handle,
					  TAG_DRTPHANDLE *drtphandle,
					  int *errcode,char *errormessage);

/*
���ͨѶƽ̨������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpPing(int handle,int *errcode,char *errormessage);

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
BOOL DrtpQueryRequest(int hi,int low,int cmd,int *errcode,char *errormessage,int handle);

/*
��ȡ��ѯͨѶƽ̨�����Ľ��
�ɹ�ʱ���� >= 0,���򷵻�-1,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ,����0,��ʾ����û�м�¼
message:���Խ������ݵ�buffer
messagebufsize:�������ݵ�buffer�ĳ���
messagelen:��ȡ�������ݵĳ���
timeout:�������ĳ�ʱʱ��(��λ�Ǻ���)��-1Ϊ������
handle:ͨѶƽ̨���Ӿ��
*/
int DrtpQueryResult(char* message,int messagesize,int *messagelen,int *errcode,char *errormessage,int handle,int timeout=-1);

/*
��ȡhook
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
drtphandle:ͨѶƽ̨ͨѶ������,��DrtpReadMessage��DrtpAttachServer�õ�
hook:��������
*/
BOOL DrtpGetHook(int handle,int *hook,int *errcode,char *errormessage);

/*
��ȡͨѶƽ̨���ӵ�ͨѶ������
�ɹ�ʱ����TRUE,���򷵻�FALSE,��ʧ��ʱ,errcode���Ǵ������,errormessage���Ǵ�����Ϣ
drtphandle:ͨѶƽ̨ͨѶ������,�е����߷���
handle:ͨѶƽ̨���Ӿ��
*/
BOOL DrtpGetHandle(int handle,TAG_DRTPHANDLE *drtphandle,int *errcode,char *errormessage);

/*
�ر�ͨѶƽ̨������
handle:ͨѶƽ̨���Ӿ����handle=-1Ϊ�ر���������
flag:������ȫ���ص����Ƿ��ͷ�ͨѶƽ̨����
*/
void DrtpClose(int handle=-1,bool flag=false);

/*
�ͷ�ͨѶƽ̨����
*/
void DrtpExit();

/*�ڲ�ʹ�õĺ���*/
int DrtpListen(int port,int *errcode,char* errormessage);
int DrtpAccept(int handle,int *errcode,char *errormessage);
BOOL DrtpCheckSSL(int handle,int crypto,int *errcode,char *errormessage);
BOOL DrtpIsLogined(int handle);
void DrtpSetLogined(int handle,char *user,char *pwd);
BOOL DrtpGetUserPwd(int handle,char *user,char *pwd);
BOOL DrtpSetLocation(int handle,int location);
BOOL DrtpGetLocation(int handle,int *location);
int DrtpNewHandle();
void DrtpDelHandle(int handle);
int DrtpPeerHandle(TAG_DRTPHANDLE *drtphandle);

#ifdef __cplusplus
}
#endif

#endif