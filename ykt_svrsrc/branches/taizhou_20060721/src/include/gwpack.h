#ifndef _GW_PACK_H_
#define _GW_PACK_H_

#define MAX_DATALEN	8192 + 1
/* ���´����������ֽڶ���ʹ�õ� */
#ifndef WIN32
#ifndef __GNUC__
#define __PACKED__
#else	// __GNUC__
#define __PACKED__	__attribute__ ((packed))
#endif	// __GNUC__
#else	// WIN32
#define __PACKED__ 
#endif	// WIN32

// ���µĶ���İ����ֽڶ���
#if defined(WIN32) || defined(__GNUC__)
#pragma pack(push,1)
#else
#pragma options align=packed
#endif


//{{{ ���Ľṹ
struct KSG_GW_PACK_t
{
	int length;					// ���ݶγ���
	int func_no;					// ���ܺ�
	int pack_index;					// ������� �� 0 ��ʼ
	long retcode;					// ������Ӧ��
	int next_pack;					// ������ݰ����������Ϊ 0 ��ʾû�к�̰�
	char enc_type;					// �����㷨��0 ��ʾ�޼���,1 ��ʾ128λAES
	char padded;					// ����Ǽ��ܣ���ʾ�Ƿ񱻲�λ��1:�� 0:����
	unsigned char CRC[16];				// CRC У�����
	char data[1];					// ���ݶΣ����ݶε������Ǽ��ܵ�
}__PACKED__;
//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif

#include "tcp.h"

#define IP_MAX_LEN	18

typedef struct 
{
	char server_ip[IP_MAX_LEN+1];
	short server_port;
	CTcpSocket* sock;
}gw_server_info_t;

int SendToServer(gw_server_info_t* svr,int funcno,const char* data);
int RecvFromServer(gw_server_info_t* svr,KSG_GW_PACK_t** resp);

#endif // _GW_PACK_H_

