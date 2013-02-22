#ifndef _DEF_H_
#define _DEF_H_
/** 
 * ģ����					ͨ��ǰ��
 * �ļ���					def.h
 * �ļ�ʵ�ֹ���				ͨ��ǰ�����ݽṹ����
 * ����						����
 * �汾						V0.1
 * ����						2005-08-18
 * ��ע
 * $Id$
 */

//{{{ define constants
#define IP_LEN  15
#define MAC_LEN	18
#define CRC_LEN 16
#define MODULE_NAME_LEN 256
#define MAX_PATH_LEN 1024
//}}}

//{{{ ϵͳ����
#define INI_SVR_SECT "SERVER"
#define INI_SVR_PORT "PORT"
#define INI_MODULE_SECT "MODULE"
#define INI_MODULE_PATH "PATH"
//}}}



//{{{ ��ϵͳ�ṹ 
typedef struct 
{
	char ip[IP_LEN + 1];			// IP 
	char mac[MAC_LEN + 1];			// MAC ��ַ	
	int port;						// �˿�
}ksf_server_conf;
//}}}

/* {{{ Э�鱨�ĵ� XML ��ʽ
 	
 	<!DOCTYPE	card-info[
 		<!ELEMENT	card-info(card)*>
 		<!ELEMENT	card(phy-id,cardid,stuempno?,blk-version,flag)>
 		<!ELEMENT	flag(0|1)>	
 	]>
 	
	<card-info>
   		<card>
   			<phy-id>������ID</phy-id>
   			<cardid>���׿���</cardid>
   			<stuempno>ѧ����</stuempno>
   			<blk-version>�汾��</blk-version>
   			<flag>��־</flag>
   		</card>
   		...
   		...
	</card-info>
}}}*/

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
#ifndef SUNOS
#pragma pack(push,1)
#endif
#else
#pragma options align=packed
#endif
//{{{ ���Ľṹ
typedef struct 
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
}__PACKED__ ksf_card_info;
//}}}

//{{{ ���Ľ��ܺ�Ľṹ
typedef struct 
{
	long length;					// ���ݶγ���
	int func_no;					// ���ܺ�
	long count;						// ���ݶ��а����� CARD ��Ϣ����
	char data[1];					// ���ݶΣ�����Ϊ���ܺ������,�� '\0' ��Ϊ��β��
}__PACKED__ ksf_xml_data;
//}}}
#ifndef WIN32
#ifndef __GNUC__
#pragma options align=reset
#else
#ifndef SUNOS
#pragma pack(pop)
#endif
#endif
#else
#pragma pack(pop)
#endif

//{{{ ���ش������ṹ
typedef enum {RET_OK = 1,RET_FAILD} ksf_ret_result;
typedef struct 
{
	ksf_ret_result ret;
	int pack_index;				// ����İ��� index
}ksf_card_result;
//}}}

//{{{ ��ϵͳ Plugin �ṹ
struct ksf_plugin_module
{
	char module_name[MODULE_NAME_LEN +1];			// ģ������
	char module_path[MAX_PATH_LEN + 1];					// ģ��·��
	char date[9];									// ����
	char author[256];								// ������
	short major_ver,minor_ver;						// ���汾�š��ΰ汾��
	int (* module_init)(void);						// ģ���ʼ������ָ��
	int (* module_release)(void);					// ģ���ͷź���ָ��
	int (* module_receive)(ksf_server_conf * svr_conf,
						ksf_xml_data * date,
						ksf_card_result * ret);	// ģ�������ܺ��������뱣������
};
//}}}

#define def(r,name,arg) \
	typedef r (*lp##name) arg; \
	static lp##name name; 

#define load(dll,name) \
	name = (lp##name)GetProcAddress(dll,#name); \
	if( !name ) \
		err_code = true;

#endif // _DEF_H_
