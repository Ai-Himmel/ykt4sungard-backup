#ifndef _KCC_HEAD_H_
#define _KCC_HEAD_H_
/** 
 * ģ����					ͨ��ǰ��
 * �ļ���					kcchead.h
 * �ļ�ʵ�ֹ���				������ϵͳ�ṹ
 * ����						����
 * �汾						V0.1
 * ����						2005-08-18
 * ��ע
 * $Id$
 */


#include <dlfcn.h>
#include "def.h"
#include "kcc_module.h"

//#define ip conf.ip
//#define mac conf.mac
//#define port conf.port

#ifdef __cplusplus
extern "C" {
#endif
	/** 
	 * @brief ��ϵͳ����ṹ
	 */
	struct kcc_server_config 
	{
		/** 
		 * @brief ��ϵͳ���
		 */
		int server_no;
		/** 
		* @brief ��ǰ��ϵͳ�Ƿ���Ҫ����,0 ��ʾ����Ҫ,1��ʾ��Ҫ
		*/
		int needsend;
		/** 
		* @brief ��ǰ��ϵͳʹ�õļ����㷨
		*/
		int enc_type;
		/** 
		 * @brief ��ϵͳ�ṹ
		 */
		ksf_server_conf conf;
		/** 
		 * @brief ָ����һ����ϵͳ�ṹ
		 */
		struct kcc_server_config * pnext;
	};


	/** 
	 * @brief ģ��ӿں���
	 */
	typedef int (*lpkcc_get_module_info)(struct kcc_module_config * config);

	/** 
	 * @brief dl �������
	 */
	typedef void * dlhandle;

	/** 
	 * @brief ģ������ṹ
	 */
	struct kcc_module_list
	{
		/** 
		* @brief ģ���ļ���
		*/
		char file[128];
		/** 
		 * @brief ָ����һ��ģ���ָ��
		 */
		struct kcc_module_list * pnext;
		/** 
		 * @brief ģ��������
		 */
		int index;
		/** 
		 * @brief ģ��ṹ
		 */
		struct kcc_module_config module;
		/** 
		* @brief ��ǰMODULE��MD5
		*/
		char md5str[16];
		/** 
		* @brief ģ��״̬,0 ��ʾ��Ч,-1��ʾ��Ч
		*/
		int status;
		/** 
		 * @brief ģ�� dl ���
		 */
		dlhandle handle;
		/** 
		 * @brief ģ��ӿں���ָ��
		 */
		lpkcc_get_module_info get_module_info;
	};


#ifdef __cplusplus
}
#endif

#endif // _KCC_HEAD_H_
