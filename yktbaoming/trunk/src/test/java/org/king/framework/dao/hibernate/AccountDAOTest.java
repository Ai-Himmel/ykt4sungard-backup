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

import java.util.List;

//import org.king.classmanage.dao.DepartmentDAO;
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
