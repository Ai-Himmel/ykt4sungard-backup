/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.framework.dao.hibernate.AccountDAOTest.java
 * �������ڣ� 2006-4-17 12:35:45
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-17 12:35:45      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.framework.dao.hibernate;

import java.util.List;

//import org.king.classmanage.dao.DepartmentDAO;
import org.king.framework.dao.BaseDaoTestCase;
import org.king.security.dao.AccountDAO;
import org.king.security.domain.Account;



/**
 * <p> AccountDAOTest.java </p>
 * <p> {����˵��} </p>
 *
 * <p><a href="AccountDAOTest.java.html"><i>�鿴Դ����</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-17
 * 
 *
 */
public class AccountDAOTest extends BaseDaoTestCase {

	private Account account = null;
	private AccountDAO accountDAO = null;

//	private DepartmentDAO departmentDAO  = null;
//	
//	public void setDepartmentDAO(DepartmentDAO departmentDAO) {
//		this.departmentDAO = departmentDAO;
//	}



	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}
	
	

//	public void testGetAll() throws Exception {
//		List accounts = departmentDAO.getAll();
//		List accounts1 = departmentDAO.getAll();
//		assertNotNull(account);
//	}

	
}
