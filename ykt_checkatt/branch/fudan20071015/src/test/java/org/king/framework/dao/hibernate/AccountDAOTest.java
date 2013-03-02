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

	public void setAccountDAO(AccountDAO accountDAO) {
		this.accountDAO = accountDAO;
	}
	
	public void testGetAccount() throws Exception {
		account = accountDAO.get("0");
		assertNotNull(account);
	}
	
	public void testUpdateAccount()throws Exception {
		account = accountDAO.get("0");
		log.debug(account);
		account.setName("�����޸�");
		
		accountDAO.save(account);
		
		assertEquals(account.getName(), "�����޸�");
		
		
	}
	public void testAddAndRemoveAccount() throws Exception {
		account = new Account();
		account.setName("����1");
		account.setPassword("password");
		accountDAO.save(account);
		
		assertNotNull(account.getName());
		accountDAO.delete(account);
		endTransaction();
        
	}

	
}
