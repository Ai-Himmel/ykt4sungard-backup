/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.dao.MenuDAO.java
 * �������ڣ� 2006-4-20 11:13:11
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-20 11:13:11      ljf        �����ļ���ʵ�ֻ�������
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
import org.king.security.domain.Menu;

/**
 * <p> MenuDAO.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="MenuDAO.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */
public interface MenuDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Menu get(Serializable id);
	
	public List getAll();
	
	public void save(Menu transientInstance);
	
    public void update(Menu transientInstance);
    
    public void delete(Menu persistentInstance);
    
    //�Զ��巽��
}
