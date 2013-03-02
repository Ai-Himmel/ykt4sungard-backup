#ifndef _KSG_LOCALINTERFACE_H_
#define _KSG_LOCALINTERFACE_H_

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
// ʹ���ֽڶ����,�ṹ���СΪ 16394 ���ֽ�
// ����ṹ�尴4�ֽڶ�����СΪ 16396 ���ֽ�,Ϊ��֤��������ƽ̨��һ����,��ʹ���ֽڶ���
struct t_request_pack 
{
	int datalen;  // ���ݶγ��ȣ��ֽ���
	char data[MAX_DATALEN]; // ���ݰ�����
	int outdatalen; // ������ݳ��ȣ��ֽ���
	char outdata[MAX_DATALEN]; // �����������,���ʧ�ܱ��������Ϣ.
}__PACKED__;

typedef struct t_request_pack request_pack;

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif


#endif // _KSG_LOCALINTERFACE_H_
