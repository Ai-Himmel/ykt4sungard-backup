/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.framework.dao.hibernate.AccountDAOTest.java
 * 创建日期： 2006-4-17 12:35:45
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-17 12:35:45      ljf        创建文件，实现基本功能
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
 * <p> {功能说明} </p>
 *
 * <p><a href="AccountDAOTest.java.html"><i>查看源代码</i></a></p>  
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
		account.setName("测试修改");
		
		accountDAO.save(account);
		
		assertEquals(account.getName(), "测试修改");
		
		
	}
	public void testAddAndRemoveAccount() throws Exception {
		account = new Account();
		account.setName("测试1");
		account.setPassword("password");
		accountDAO.save(account);
		
		assertNotNull(account.getName());
		accountDAO.delete(account);
		endTransaction();
        
	}

	
}
