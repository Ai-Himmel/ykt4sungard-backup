#ifndef _SUBSYSTEM_H_
#define _SUBSYSTEM_H_
/** 
 * ģ����			һ��ͨ��ϵͳ
 * �ļ���			subsystem.h
 * �ļ�ʵ�ֹ���		��ϵͳ����
 * ����				����
 * �汾				V1.0
 * ����				2005-07-21
 * ��ע
 * $Id: subsystem.h 15 2005-08-22 02:39:12Z cash $
 */

//{{{ ϵͳ����
#define INI_SVR_SECT "SERVER"
#define INI_SVR_PORT "PORT"
#define INI_SVR_BINDIP "BINDIP"
#define INI_MODULE_SECT "MODULE"
#define INI_MODULE_PATH "PATH"
#define INI_CONNECT_SECT "CONNECT"
#define INI_CONNECT_IP	"ALLOWIP"
#define INI_CONNECT_COUNT "COUNT"
//}}}

// �����㷨
// ������
#define ENC_TYPE_NONE	0
// ʹ�� AES 128 �㷨����
#define ENC_TYPE_AES128 1


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
struct ksf_card_info
{
	long length;					// ���ݶγ���
	int func_no;					// ���ܺ�
	int pack_index;					// ������� �� 0 ��ʼ
	long count;						// ���ݶ��а����� CARD ��Ϣ����
	int next_pack;					// ������ݰ����������Ϊ 0 ��ʾû�к�̰�
	char enc_type;					// �����㷨��0 ��ʾ�޼���,1 ��ʾ128λAES
	char padded;					// ����Ǽ��ܣ���ʾ�Ƿ񱻲�λ��1:�� 0:����
	char CRC[CRC_LEN];				// CRC У�����
	char data[1];					// ���ݶΣ����ݶε������Ǽ��ܵ�
}__PACKED__;
//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif

#endif // _SUBSYSTEM_H_
