/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2007
 * �ļ���    IDeptService.java
 * �������ڣ� 2007-6-5 ����02:25:34
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 *  2007-6-5 ����02:25:34     ��ʤ        �����ļ���ʵ�ֻ�������
 * ============================================================
 */
package org.king.quarters.service;

import java.util.List;

import org.king.quarters.domain.TabSsManager;

public interface IManagerService {

	public boolean addOrUpdateDept(TabSsManager manager);
	public List getManagers();
	public TabSsManager getManager(String managerId);
	
}
