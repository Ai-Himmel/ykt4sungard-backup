package org.king.framework.web.filter;

import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import java.io.IOException;

public class EncodingFilter
        implements Filter {
    private FilterConfig filterConfig = null;

    private String encoding = null;

    private boolean ignore = true;

    public final void destroy() {
        encoding = null;
        filterConfig = null;
    }

    public final void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {
        if ((ignore) || (request.getCharacterEncoding() == null)) {
            String encoding1 = selectEncoding(request);

            if (encoding1 != null) {
                request.setCharacterEncoding(encoding1);
            }

        }

        chain.doFilter(request, response);
    }

    public final void init(FilterConfig arg0)
            throws ServletException {
        filterConfig = arg0;
        encoding = filterConfig.getInitParameter("encoding");

        String value = filterConfig.getInitParameter("ignore");

        if (value == null)
            ignore = true;
        else if (value.equalsIgnoreCase("true"))
            ignore = true;
        else if (value.equalsIgnoreCase("yes"))
            ignore = true;
        else
            ignore = false;
    }

    protected final String selectEncoding(ServletRequest request) {
        return encoding;
    }
}