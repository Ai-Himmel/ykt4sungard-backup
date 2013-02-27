package com.kingstargroup.filter;

import java.io.IOException;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import com.kingstargroup.Constants;
import com.kingstargroup.form.MapUserTable;
import com.kingstargroup.utils.RequestUtil;
import com.kingstargroup.utils.StringUtil;



/**
 * <p>Intercepts Login requests for "Remember Me" functionality.</p>
 *
 * <p>
 * <a href="LoginFilter.java.html"><i>View Source</i></a>
 * </p>
 *
 * @author <a href="mailto:jianfeng.luo@kingstargroup.com">luojf</a>
 * @version $Revision: 1.10 $ $Date: 2004/09/29 10:24:38 $
 *
 * @web.filter display-name="Login Filter" name="loginFilter"
 * @web.filter-init-param name="enabled" value="${rememberMe.enabled}"
 */
public final class LoginFilter implements Filter {
    //~ Instance fields ========================================================

    private transient final Log log = LogFactory.getLog(LoginFilter.class);
    private FilterConfig config = null;
    private boolean enabled = true;

    //~ Methods ================================================================

 public void doFilter(ServletRequest req, ServletResponse resp,
                         FilterChain chain)
                  throws IOException, ServletException {

	 /*        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) resp;

        // See if the user has a remember me cookie
        Cookie c = RequestUtil.getCookie(request, Constants.LOGIN_COOKIE);

         context = config.getServletContext().getAttribute();
        UserManager mgr = (UserManager) context.getBean("userManager");

        // Check to see if the user is logging out, if so, remove all
        // login cookies
        if (request.getRequestURL().indexOf("logout") != -1 &&
                request.getRemoteUser() != null) {
            // make sure user's session hasn't timed out
            if (request.getRemoteUser() != null) {
                if (log.isDebugEnabled()) {
                    log.debug("logging out '" + request.getRemoteUser() + "'");
                }

                mgr.removeLoginCookies(request.getRemoteUser());
                RequestUtil.deleteCookie(response, c, request.getContextPath());
                request.getSession().invalidate();
				ContextHolder.setContext(null);
            }
        } else if (c != null && enabled) {
            String loginCookie = mgr.checkLoginCookie(c.getValue());

            if (loginCookie != null) {
                RequestUtil.setCookie(response, Constants.LOGIN_COOKIE,
                                      loginCookie,
                                      request.getContextPath());
                loginCookie = StringUtil.decodeString(loginCookie);

                String[] value = StringUtils.split(loginCookie, '|');

                User user = mgr.getUser(value[0]);

                // authenticate user without displaying login page
                String route = "/authorize?j_username=" +
                               user.getUserCode() + "&j_password=" +
                               user.getPassword();

                request.setAttribute("encrypt", "false");
                request.getSession(true).setAttribute("cookieLogin",
                                                      "true");

                if (log.isDebugEnabled()) {
                    log.debug("I remember you '" + user.getUserCode() +
                              "', attempting to authenticate...");
                }

                RequestDispatcher dispatcher =
                    request.getRequestDispatcher(route);
                dispatcher.forward(request, response);

                return;
            }
        }

        chain.doFilter(req, resp); */
    }


    /**
     * Initialize controller values of filter.
     */
    public void init(FilterConfig config) {
        this.config = config;

        String param = config.getInitParameter("enabled");
        enabled = Boolean.valueOf(param).booleanValue();

        if (log.isDebugEnabled()) {
            log.debug("Remember Me enabled: " + enabled);
        }

        config.getServletContext()
              .setAttribute("rememberMeEnabled",
                            config.getInitParameter("enabled"));
    }

    /**
     * destroy any instance values other than config *
     */
    public void destroy() {
    }
}
