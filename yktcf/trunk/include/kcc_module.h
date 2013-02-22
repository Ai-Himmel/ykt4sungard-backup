#ifndef _KCC_MODULE_H_
#define _KCC_MODULE_H_
/** 
 * ģ����				ͨ��ǰ��
 * �ļ���				kcc_module.h
 * �ļ�ʵ�ֹ���			����ͨ��ǰ��ģ��ṹ
 * ����					����
 * �汾					V0.1
 * ����					2005-08-18
 * ��ע
 * $Id$
 */

#include "drtp.h"
#include "def.h"

#ifdef __cplusplus
extern "C" {
#endif
	/** 
	 * @brief ģ������ö�ٱ���
	 */
	typedef enum {
		KMT_COMMON = 0,  // ͨ��ģ��
		KMT_PER_SVR		 // ÿ����ϵͳ��Ҫ���������ģ��
	}kcc_module_type;

	/** 
	 * @brief ģ��ṹ
	 */
	struct kcc_module_config
	{
		/** 
		 * @brief ���汾��
		 */
		int major;
		/** 
		 * @brief �ΰ汾��
		 */
		int minor;
		/** 
		* @brief Build ��
		*/
		char build[15];
		/** 
		 * @brief ģ�鷢������
		 */
		char date[9];
		/** 
		 * @brief ģ������
		 */
		char module_name[50 + 1];
		/** 
		 * @brief ����ģ��Ľӿں���������ΪNULL
		 * 
		 */
		int (*kcc_m_load)();
		/** 
		 * @brief ж��ģ��Ľӿں���������ΪNULL
		 * 
		 */
		int (*kcc_m_unload)();
		/** 
		 * @brief ȡ��ģ�����ͨ��ǰ�õĹ��ܺ�
		 * @return - ���ܺ�
		 */
		long (*kcc_m_get_func_no)();
		/** 
		 * @brief ��������� CPACK ���Ľӿ�
		 * 
		 * @param svr - ��ǰ��ϵͳ�ṹ
		 * @param rpack - [in out]CPACK �ṹ
		 *
		 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
		 */
		int (*kcc_m_request_cpack)(struct kcc_server_config* svr,
								   ST_CPACK* rpack);
		/** 
		 * @brief �������ݰ�ͷ�ӿں������� XML ͷ
		 * 
		 * @param svr - ��ǰ��ϵͳ�ṹ
		 * @param buf - [out] �����buffer
		 * @param len - buffer �ĳ���
		 *
		 * @return - �ɹ�����buffer�ĳ��ȣ�ʧ�ܷ��� -1
		 */
		int (*kcc_m_format_header)(struct kcc_server_config* svr,
								   char* buf,int len);
		/** 
		 * @brief �������ݰ��Ľ�β�ӿ�
		 * 
		 * @param svr - ��ǰ��ϵͳ�ṹ
		 * @param buf - [out] �����buffer
		 * @param len - buffer �����ɵ��ֽ���
		 *
		 * @return - �ɹ�����buffer�еĳ��ȣ�ʧ�ܷ��� -1
		 */
		int (*kcc_m_format_tail)(struct kcc_server_config * svr,
								 char *buf,int len);

        /** 
		 * @brief �������ݰ����������ӿ�
		 * 
		 * @param svr - ��ǰ��ϵͳ�ṹ
		 * @param buf - [in out] CPACK �ṹ
		 *
		 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
		 */
        int (*kcc_send_third_part_cpack)(struct kcc_server_config* svr,								 
                                         ST_CPACK* rpack, ST_PACK *tmp_pack);

        /** 
		 * @brief ͨ�� ��ϵͳ ���ص�ֵ���� CPACK��
		 * 
		 * @param rpack - CPACK ��
		 * @param svr - ��ϵͳ�ṹ
		 * @param ret - ��ϵͳ ���ؽ���ṹ
		 *
		 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
		 */
        int (*kcc_recv_third_part_cpack)(ST_CPACK* rpack, struct kcc_server_config* svr,								 
                                         ksf_card_result* ret);
		/** 
		 * @brief �ӷ��ص�CPACK���ݰ����������ݰ�
		 * 
		 * @param svr - ��ǰ��ϵͳ�ṹ
		 * @param pack - CPACK ���ݰ�
		 * @param buf - [out] �����buffer
		 * @param len - buffer ������������ֽ�����
		 * 
		 * @return - �ɹ�����buffer��ʵ���ֽ�����ʧ�ܷ��� -1
		 */
		int (*kcc_m_format_cpack)(struct kcc_server_config * svr,
								  ST_PACK* pack, char* buf,int len);
		/** 
		 * @brief ͨ�� ��ϵͳ ���ص�ֵ���� CPACK��
		 * 
		 * @param rpack - CPACK ��
		 * @param svr - ��ϵͳ�ṹ
		 * @param ret - ��ϵͳ ���ؽ���ṹ
		 *
		 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
		 */
		int (*kcc_m_make_return_cpack)(ST_CPACK* rpack,
									   struct kcc_server_config* svr,
									   ksf_card_result* ret);
		/** 
		 * @brief ȡ��ģ������
		 * 
		 * @return - ����ģ������
		 */
		kcc_module_type (*kcc_m_get_module_type)();
	};


#ifdef __cplusplus
}
#endif

#endif // _KCC_MODULE_H_
