/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.framework.service.impl.AccountServiceImplTest.java
 * 创建日期： 2006-4-19 9:53:10
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 9:53:10      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.framework.service.impl;

import java.util.ArrayList;

import org.jmock.Mock;
import org.king.framework.service.BaseServiceTestCase;
import org.king.security.dao.AccountDAO;
import org.king.security.domain.Account;
import org.king.security.service.impl.AccountServiceImpl;

/**
 * <p> AccountServiceImplTest.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="AccountServiceImplTest.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 *
 */
public class AccountServiceImplTest extends BaseServiceTestCase {
    //	~ Instance fields ========================================================
	private AccountServiceImpl accountService = new AccountServiceImpl();
	private Mock accountDAO = null;
	
    //~ Methods ================================================================

    protected void setUp() throws Exception {
        super.setUp();
        accountDAO = new Mock(AccountDAO.class);
        accountService.setAccountDAO((AccountDAO)accountDAO.proxy());
    }
	
    public void testFindAccountByName() throws Exception{
    	Account testData = new Account("1");
    	ArrayList accountList = new ArrayList();
    	accountList.add(testData);
    	String hql = "from Account a where a.name='1' order by a.name";
    	accountDAO.expects(once()).method("find").with(eq(hql)).will(returnValue(accountList));
    	
    	Account account = accountService.findAccountByName("1");
    	assertTrue(account != null);
    	accountDAO.verify();
    	
    }
	
}
