#ifndef _DRTP_CALL_H_
#define _DRTP_CALL_H_
/** 
 * ģ����				ͨ��ǰ��
 * �ļ���				drtpcall.h
 * �ļ�ʵ�ֹ���			��װDRTP��
 * ����					����
 * �汾					V0.1
 * ����					2005-08-18
 * ��ע
 * $Id$
 */

#include "drtp.h"

#ifdef __cplusplus
extern "C" {
#endif

	/** 
	 * @brief ȡ�� drtp �������һ�� Error Code
	 * 
	 * @return - error code ֵ
	 */
	int kcc_drtp_get_last_err();
	/** 
	 * @brief ȡ�� drtp �������һ�� error message
	 * 
	 * @param msg - message buffer ��� 512 ���ֽ�
	 */
	void kcc_drtp_get_last_err_msg(char * msg);

	/** 
	 * @brief ���õ��� DRTP �������ܺ�
	 * 
	 * @param mainfunc - �����ܺš����Ϊ 0 ��ʹ��ȫ�ֱ��� g_drtp_func_no
	 *					 ��ֵ����ֵ������ϵͳ����������
	 */
	void kcc_drtp_set_main_func(long mainfunc);
	/** 
	 * @brief ��ʼ�� drtp 
	 * 
	 * @return �ɹ����� 0 �� ʧ�ܷ��� -1
	 */
	int kcc_drtp_init();
	/** 
	 * @brief ���� DRTP ������
	 * 
	 * @return - �������Ӿ����ʧ�ܷ��� -1
	 */
	int kcc_drtp_connect();
	/** 
	 * @brief �ر� DRTP ����
	 * 
	 * @param handle - ���Ӿ��
	 * 
	 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
	 */
	int kcc_drtp_close(int handle);
	/** 
	 * @brief �ͷ� DRTP ��Դ
	 * 
	 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
	 */
	int kcc_drtp_uninit();
	/** 
	 * @brief �������� DRTP ���
	 * 
	 * @param handle - DRTP���Ӿ��
	 * 
	 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
	 */
	int kcc_drtp_reconnect(int handle);
	/** 
	 * @brief ���� DRTP Buffer
	 * 
	 * @param handle - DRTP ���Ӿ��
	 * @param buf - �����͵� Buffer 
	 * @param len - �����͵� Buffer �ĳ���
	 * @param mainfunc - DRTP �����ܺ�
	 * 
	 * @return - �ɹ����� 0��ʧ�ܷ��� -1
	 */
	int kcc_drtp_send(int handle,char * buf,int len,int mainfunc);
	/** 
	 * @brief ���� DRTP Buffer
	 * 
	 * @param handle - DRTP ���Ӿ��
	 * @param buf - ���յ�Buffer
	 * @param len - ���յ�Buffer�������
	 * @param timeout - ��ʱʱ��
	 * 
	 * @return - �ɹ����ؽ��պ� buffer ���ȣ�ʧ�ܷ��� -1
	 */
	int kcc_drtp_receive(int handle,char * buf,int len,int timeout);
	/** 
	 * @brief ����CPACK�ֶε�ֵ
	 * 
	 * @param head - CPACK��ͷ
	 * @param pack - CPACK���ݰ�
	 * @param ids - CPACK �ֶα�ʶ
	 * @param data - CPACK �ֶ�ֵ
	 */
	void kcc_drtp_set_value(ST_PACKHEAD *head, ST_PACK *pack,int ids,char *data);

	/** 
	 * @brief initialize CPACK struct
	 * 
	 * @param rpack - cpack struct
	 * @param rec_count - cpack record count
	 * @param req_no - cpack request type
	 * @param max_rec - cpack max record count per pack
	 */
	void kcc_init_cpack(ST_CPACK * rpack,int rec_count,int req_no,int max_rec);

	/** 
	 * @brief ���� CPACK ����ֻ֧�ֵ�������,����ʱ���ϴε���
	 * kcc_drtp_set_main_func ���õ������ܺŷ��Ͱ�
	 *						 ����֮��������ܺžͱ����ó�Ϊȫ��Ĭ�������ܺ�
	 * 
	 * @param handle - DRTP ���Ӿ��
	 * @param rpack - CPACK ��
	 * 
	 * @return - �ɹ����� 0 ��ʧ�ܷ��� -1
	 */
	int kcc_drtp_send_cpack(int handle,ST_CPACK * rpack);
	
	/** 
	 * @brief ���� CPACK ����������100����
	 * 
	 * @param handle -DRTP ���Ӿ��
	 * @param apack - CPACK ��
	 * @param apackarray - �������ݰ� PACK
	 * @param pa_len - apackarray �ĳ��ȣ��ж��ٸ� PACK
	 * 
	 * @return - �ɹ����ؽ��յİ�������ʧ�ܷ��� -1
	 */
	int kcc_drtp_recv_cpack(int handle,ST_CPACK * apack,
							ST_PACK * apackarray,int pa_len);
	/** 
	 * @brief ���� CPACK ����ĺ�������������100����.
	 * 
	 * @param handle - DRTP ���Ӿ��
	 * @param req_no - �����ܺ�
	 * @param apack - �ϴν��պ󷵻ص�CPACK ��
	 * @param apackarray - �������ݰ� PACK
	 * 
	 * @return - �ɹ����ؽ��յ����ݰ��ĳ��ȣ�ʧ�ܷ��� -1��
	 *			 ���û�к��������� 0
	 */
	int kcc_drtp_recv_next_cpack(int handle,int req_no,
								 ST_CPACK *apack,ST_PACK * apackarray);
	/** 
	 * @brief �жϽ��յ�CPACK��ͷ�ķ�����Ϣ
	 * 
	 * @param rpack - ���յ�CPACK��
	 * 
	 * @return - ��ȷ������ 0 
	 *			 �޴˹��ܺ� -1
	 *			 �д���     1
	 */
	int kcc_drtp_valid_cpack(ST_CPACK * rpack);

#ifdef __cplusplus
}
#endif

#endif // _DRTP_CALL_H_
