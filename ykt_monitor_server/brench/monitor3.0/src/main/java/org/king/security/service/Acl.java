/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.service.Acl.java
 * 创建日期： 2006-4-19 22:56:56
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-19 22:56:56      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.security.service;

import java.util.Collection;
import java.util.Map;

import org.king.security.domain.Account;

/**
 * <p> Acl.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="Acl.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-19
 * 
 *
 */
public interface Acl {
   
	/**
	 * 判断是否是受保护的资源
	 * @param url
	 * @return
	 */
	public boolean isProtectedResource(String url);

    /**
     * 得到所有受保护的资源
     * @return
     */
	public Collection getProtectedResources();

   /**
    * 设置保护资源
    * @param map
    */
	public void setProtectedResourcesMap(Map map);

	/**
	 * 判断是否有权限
	 * @param url
	 * @param account
	 * @return
	 */
	public boolean hasRight(String url, Account account);
}
