#ifndef _SERVERS_H_
#define _SERVERS_H_

#include <dlfcn.h>
#include <sys/types.h>
#include "def.h"
#include "kcchead.h"
#include "kcc_module.h"

#ifdef __cplusplus
extern "C" {
#endif

	/** 
	* @brief ɾ����ϵͳ�б�
	* 
	*/
	void kcc_release_server_list();
	/** 
	 * @brief ��ʼ����ϵͳ����ĺ���
	 * 
	 * @return - ���� 0 ��ʾ�ɹ������� -1 ��ʾʧ��
	 */
	int kcc_init_server_list();

	/** 
	 * @brief ������
	 */
	void kcc_do_main();

	/** 
	 * @brief �����ǰϵͳ������ģ��
	 */
	void kcc_clear_modules();

	/** 
	 * @brief ����ģ�飬�ڼ���֮ǰ�ú�������� kcc_clear_modules ����
	 * 
	 * @return 0 ��ʾ���سɹ���-1 ��ʾ����ʧ��
	 */
	int kcc_init_modules();

	/** 
	* @brief ���ӽ��̴������ӽ����б���ɾ��
	* 
	* @param pid 
	*/
	void kcc_remove_pid_from_process(pid_t pid);
	/** 
	* @brief ֹͣ�������
	*/
	void kcc_stop_server();
#ifdef __cplusplus
}
#endif

#endif // _SERVERS_H_
