/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.security.web.filter.AclFilter.java
 * �������ڣ� 2006-4-20 13:12:18
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-4-20 13:12:18      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 * 
 */
package org.king.security.web.filter;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.framework.service.ServiceLocator;
import org.king.security.domain.Account;
import org.king.security.service.Acl;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

/**
 * <p>
 * AclFilter.java
 * </p>
 * <p>
 * {����˵��}
 * </p>
 * 
 * <p>
 * <a href="AclFilter.java.html"><i>�鿴Դ����</i></a>
 * </p>
 * 
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 * 
 * 
 */
public class AclFilter implements Filter {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(AclFilter.class);

	/** Acl DAO, responsible for reading acl configuration from file */
	private Acl acl;

	/**
	 * The filter configuration object we are associated with. If this value is
	 * null, this filter instance is not currently configured.
	 */
	private FilterConfig config;

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.servlet.Filter#init(javax.servlet.FilterConfig)
	 */
	public void init(FilterConfig filterConfig) throws ServletException {
	       config = filterConfig;

	        ServletContext context = filterConfig.getServletContext();
	        acl = (Acl) ServiceLocator.getInstance().getService("acl");

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.servlet.Filter#doFilter(javax.servlet.ServletRequest,
	 *      javax.servlet.ServletResponse, javax.servlet.FilterChain)
	 */
	public void doFilter(ServletRequest request, ServletResponse response,
			FilterChain chain) throws IOException, ServletException {
		HttpServletRequest hreq = (HttpServletRequest) request;
		String[] urls = StringUtils.split(hreq.getRequestURI(), "/");
		String url = urls[(urls.length - 1)];
		
		logger.debug("���� url: " + url);

		
		// check login
		if (!isLogin(hreq) && acl.isProtectedResource(url)) {
			// String url = "/" + uri + "?" + hreq.getQueryString();
			// hreq.setAttribute( ForumConstants.DEST_URL, url );
			config.getServletContext().getRequestDispatcher("/login.do")
					.forward(request, response);

			return;
		}

		if (acl.isProtectedResource(url)) {
			// get subject
			Account account = (Account) hreq.getSession().getAttribute("accountPerson");

			if (!acl.hasRight(url, account)) {
			
			config.getServletContext().getRequestDispatcher(
						"/noRight.do?method=noRight")
						.forward(request, response);

				return;
			}
		}

		// Pass control on to the next filter
		chain.doFilter(request, response);

	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see javax.servlet.Filter#destroy()
	 */
	public void destroy() {
		config = null;
		acl = null;

	}

	private boolean isLogin(HttpServletRequest hreq) {
		boolean isLogin = false;
		HttpSession session = hreq.getSession();

		isLogin = (session != null) && !session.isNew()
				&& (session.getAttribute("account") != null);

		return isLogin;
	}
}
