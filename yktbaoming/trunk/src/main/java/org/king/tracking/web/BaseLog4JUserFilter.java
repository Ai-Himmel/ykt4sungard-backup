/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.tracking.web.BaseLog4JUserFilter.java
 * �������ڣ� 2006-6-8 19:31:09
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-8 19:31:09      ljf        �����ļ���ʵ�ֻ�������
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
 * <p> {����˵��} </p>
 *
 * <p><a href="BaseLog4JUserFilter.java.html"><i>�鿴Դ����</i></a></p>  
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
     * �趨MDC��userid�ı�������������������
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
     * �ص�������������ʵ��userid�Ļ�ȡ
     */
    abstract protected String getUserId(HttpSession session);


}
