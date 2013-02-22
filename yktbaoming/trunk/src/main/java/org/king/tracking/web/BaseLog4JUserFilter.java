/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.tracking.web.BaseLog4JUserFilter.java
 * 创建日期： 2006-6-8 19:31:09
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-8 19:31:09      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.tracking.web;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.MDC;

import javax.servlet.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.io.IOException;


/**
 * <p> BaseLog4JUserFilter.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="BaseLog4JUserFilter.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-8
 * 
 *
 */
public abstract class BaseLog4JUserFilter implements Filter {
	
	protected final static String DEFAULT_USERID = "anonymous";

	/* (non-Javadoc)
	 * @see javax.servlet.Filter#init(javax.servlet.FilterConfig)
	 */
	public void init(FilterConfig arg0) throws ServletException {

	}

	/* (non-Javadoc)
	 * @see javax.servlet.Filter#doFilter(javax.servlet.ServletRequest, javax.servlet.ServletResponse, javax.servlet.FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response,
			FilterChain chain) throws IOException, ServletException {
		 HttpSession session = ((HttpServletRequest) request).getSession();

	        if (session == null || getUserId(session) == null)
	            MDC.put(getPropertyName(), DEFAULT_USERID);
	        else
	            MDC.put(getPropertyName(), getUserId(session));

	        chain.doFilter(request, response);


	}
	
    /**
     * 设定MDC中userid的变量名，可在子类重载
     */
    protected String getPropertyName() {
        return "userId";
    }


	/* (non-Javadoc)
	 * @see javax.servlet.Filter#destroy()
	 */
	public void destroy() {

	}
	
    /**
     * 回调函数，在子类实现userid的获取
     */
    abstract protected String getUserId(HttpSession session);


}
