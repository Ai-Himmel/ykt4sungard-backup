/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.dao.AccountDAO.java
 * 创建日期： 2006-4-20 9:48:00
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-20 9:48:00      ljf        创建文件，实现基本功能
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
import org.king.security.domain.Account;

/**
 * <p> AccountDAO.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="AccountDAO.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 *
 */

public interface AccountDAO extends DAO {

	public List find(MyQuery myQuery);
	
	public List find(String query);
	 
	public Account get(Serializable id);
	
	public List getAll();
	
	public void save(Account transientInstance);
	
    public void update(Account transientInstance);
    
    public void delete(Account persistentInstance);
    
    //自定义方法
    
    public Account findAccountByName(String name);
}
