/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.tracking.web.filter.Log4JUserFilter.java
 * 创建日期： 2006-6-8 19:35:03
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-8 19:35:03      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.tracking.web.filter;

import javax.servlet.Filter;
import javax.servlet.http.HttpSession;

import org.king.tracking.web.BaseLog4JUserFilter;

/**
 * <p> Log4JUserFilter.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="Log4JUserFilter.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-8
 * 
 *
 */
public class Log4JUserFilter extends BaseLog4JUserFilter implements Filter {

	/* (non-Javadoc)
	 * @see org.king.tracking.web.BaseLog4JUserFilter#getUserId(javax.servlet.http.HttpSession)
	 */
	protected String getUserId(HttpSession session) {
		  String userId = (String)session.getAttribute("account");
	        if (userId == null)
	            return null;
	        else
	            return userId;

	}

}
