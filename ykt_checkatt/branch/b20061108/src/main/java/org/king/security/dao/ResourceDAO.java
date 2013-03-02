/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.dao.ResourceDAO.java
 * �������ڣ� 2006-4-20 12:20:47
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-20 12:20:47      ljf        �����ļ���ʵ�ֻ�������
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
import org.king.security.domain.Resource;

/**
 * <p> ResourceDAO.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="ResourceDAO.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */
public interface ResourceDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Resource get(Serializable id);
	
	public List getAll();
	
	public void save(Resource transientInstance);
	
    public void update(Resource transientInstance);
    
    public void delete(Resource persistentInstance);
    
    //�Զ��巽��
}
