#ifndef _DEF_H_
#define _DEF_H_

/** 
 * @file def.h
 * @brief ͨ��ǰ�����ݽṹ����
 * @author ����
 * @date 2005-06-28
 * $Id: def.h 27 2005-09-06 08:52:48Z cheng.tang $
 */
//{{{ define constants
#define IP_LEN  15
#define MAC_LEN	18
#define CRC_LEN 16
#define MODULE_NAME_LEN 256
#define MAX_PATH_LEN 1024
//}}}

#ifdef WIN32
#define MODULE_EXPORT __declspec(dllexport)
#else
#define MODULE_EXPORT
#endif
//{{{ ��ϵͳ�ṹ 
struct ksf_server_conf
{
	char ip[IP_LEN + 1];			// IP 
	char mac[MAC_LEN + 1];			// MAC ��ַ	
	int port;						// �˿�
};
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

//{{{ ���Ľ��ܺ�Ľṹ
struct ksf_xml_data
{
	long length;					// ���ݶγ���
	int func_no;					// ���ܺ�
	long count;						// ���ݶ��а����� CARD ��Ϣ����
	char data[1];					// ���ݶΣ�����Ϊ���ܺ������,�� '\0' ��Ϊ��β��
}__PACKED__;
//}}}

#if defined(WIN32) || defined(__GNUC__)
#pragma pack()
#else
#pragma options align=reset
#endif

//{{{ ���ش������ṹ
typedef enum {RET_OK = 1,RET_FAILD} ksf_ret_result;
struct ksf_card_result
{
	ksf_ret_result ret;
	int pack_index;				// ����İ��� index
};
//}}}

#ifdef CALLBACK_API
#undef CALLBACK_API
#endif
#define CALLBACK_API WINAPI
//{{{ ��ϵͳ Plugin �ṹ
typedef int (CALLBACK_API* lp_module_init)(void);
typedef int (CALLBACK_API* lp_module_release)(void);
typedef int (CALLBACK_API* lp_module_receive)(ksf_server_conf *,
										   ksf_xml_data * ,
										   ksf_card_result *);
struct ksf_plugin_module
{
	char module_name[MODULE_NAME_LEN +1];			// ģ������
	char module_path[MAX_PATH_LEN + 1];					// ģ��·��
	char date[9];									// ����
	char author[256];								// ������
	short major_ver,minor_ver;						// ���汾�š��ΰ汾��
	lp_module_init module_init;						// ģ���ʼ������ָ��
	lp_module_release module_release;				// ģ���ͷź���ָ��
	lp_module_receive module_receive;	// ģ�������ܺ��������뱣������
};
//}}}

#define def(r,name,arg) \
	typedef r (WINAPI *lp##name) arg; \
	static lp##name name; 

#define load(dll,name) \
	name = (lp##name)GetProcAddress(dll,#name); \
	if( !name ) \
		err_code = true;

#endif // _DEF_H_
