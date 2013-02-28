package org.king.filter;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import java.io.IOException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-11-7
 */
public class EncodingFilter implements Filter {
    private String encoding = null;

    public final void destroy() {
        encoding = null;
    }

    public final void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        if ((request.getCharacterEncoding() == null)) {
            if (getEncoding() != null) {
                request.setCharacterEncoding(getEncoding());
            }
        }
        chain.doFilter(request, response);
    }

    public final void init(FilterConfig filterConfig) throws ServletException {
        encoding = filterConfig.getInitParameter("encoding");
    }

    protected final String getEncoding() {
        return encoding;
    }
}