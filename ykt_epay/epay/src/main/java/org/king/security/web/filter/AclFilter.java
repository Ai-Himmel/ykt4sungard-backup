/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.security.web.filter.AclFilter.java
 * 创建日期： 2006-4-20 13:12:18
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-4-20 13:12:18      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 *
 */
package org.king.security.web.filter;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.framework.service.ServiceLocator;
import org.king.security.service.Acl;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

/**
 * <p>
 * AclFilter.java
 * </p>
 * <p>
 * {功能说明}
 * </p>
 * <p/>
 * <p>
 * <a href="AclFilter.java.html"><i>查看源代码</i></a>
 * </p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-4-20
 */
public class AclFilter implements Filter {
    /**
     * Logger for this class
     */
    private static final Logger logger = Logger.getLogger(AclFilter.class);

    /**
     * Acl DAO, responsible for reading acl configuration from file
     */
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
        acl = (Acl) ServiceLocator.getInstance().getService("acl");
    }

    /*
      * (non-Javadoc)
      *
      * @see javax.servlet.Filter#doFilter(javax.servlet.ServletRequest,
      *      javax.servlet.ServletResponse, javax.servlet.FilterChain)
      */

    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest hreq = (HttpServletRequest) request;
        String context = hreq.getContextPath();
        if (context == null || context.trim().equals("")) context = "/";
        int i = 1;
        if (context.equals("/")) i = 0;
        String url = "";

        String[] urls = StringUtils.split(hreq.getRequestURI(), "/");

        for (; i < urls.length - 1; i++) {
            url = urls[i] + "/";
        }
        url += urls[(urls.length - 1)];

        // check login
        List<String> list = new ArrayList<String>();
        list.add("loginAction.do");
        list.add("payManager.do");
        list.add("activate.do");
        list.add("epay.do");
        list.add("activateAction.do");
        if (!isLogin(hreq)&&!list.contains(url)) {
            config.getServletContext().getRequestDispatcher("/index.do").forward(request, response);
            return;
        }
        if("epay.do".equals(url)){
        	config.getServletContext().getRequestDispatcher("/payManager.do?method=createepay").forward(request, response);
            return;
        }
//        if (acl.isProtectedResource(url)) {
//            //todo 获取当前登录用户
//        	String acctype = (String) hreq.getSession().getAttribute("acctype");
//            if (!acl.hasRight(url, acctype)) {
//                config.getServletContext().getRequestDispatcher("/noRight.do?method=noRight").forward(request, response);
//                return;
//            }
//        }
        logger.info(url);
        chain.doFilter(request, response);
    }

    public void destroy() {
        config = null;
        acl = null;

    }

    private boolean isLogin(HttpServletRequest hreq) {
        boolean isLogin;
        HttpSession session = hreq.getSession();
        isLogin = (session != null) && !session.isNew() && (session.getAttribute("accno") != null);
        return isLogin;
    }
}
