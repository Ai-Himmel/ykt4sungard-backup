/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.dao.RoleDAO.java
 * �������ڣ� 2006-4-20 9:52:18
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-20 9:52:18      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.dao;

import java.io.Serializable;
import java.util.List;

import org.king.framework.dao.DAO;
import org.king.framework.dao.MyQuery;
import org.king.security.domain.Role;


/**
 * <p>
 * RoleDAO.java
 * </p>
 * <p>
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="RoleDAO.java.html"><i>�鿴Դ����</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 * 
 */
public interface RoleDAO extends DAO {

	public List find(MyQuery myQuery);

	public List find(String query);

	public Role get(Serializable id);

	public List getAll();
	
	public void save(Role transientInstance);

	public void update(Role transientInstance);

	public void delete(Role persistentInstance);
	
	//�Զ��巽��
	
}
