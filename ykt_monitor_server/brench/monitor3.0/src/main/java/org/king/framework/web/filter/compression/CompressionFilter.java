package org.king.framework.web.filter.compression;

import java.io.IOException;
import java.io.PrintStream;
import java.util.Enumeration;
import javax.servlet.Filter;
import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class CompressionFilter
  implements Filter
{
  private FilterConfig config = null;

  private int minThreshold = 128;
  protected int compressionThreshold;
  private int debug = 0;

  public void init(FilterConfig filterConfig)
  {
    config = filterConfig;

    if (filterConfig != null) {
      String value = filterConfig.getInitParameter("debug");

      if (value != null)
        debug = Integer.parseInt(value);
      else {
        debug = 0;
      }

      String str = filterConfig.getInitParameter("compressionThreshold");

      if (str != null) {
        compressionThreshold = Integer.parseInt(str);

        if ((compressionThreshold != 0) && (compressionThreshold < minThreshold))
        {
          if (debug > 0) {
            System.out.println("compressionThreshold should be either 0 - no compression or >= " + minThreshold);

            System.out.println("compressionThreshold set to " + minThreshold);
          }

          compressionThreshold = minThreshold;
        }
      } else {
        compressionThreshold = 0;
      }
    } else {
      compressionThreshold = 0;
    }
  }

  public void destroy()
  {
    config = null;
  }

  public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
    throws IOException, ServletException
  {
    if (debug > 0) {
      System.out.println("@doFilter");
    }

    if (compressionThreshold == 0) {
      if (debug > 0) {
        System.out.println("doFilter gets called, but compressionTreshold is set to 0 - no compression");
      }

      chain.doFilter(request, response);

      return;
    }

    boolean supportCompression = false;

    if ((request instanceof HttpServletRequest)) {
      if (debug > 1) {
        System.out.println("requestURI = " + ((HttpServletRequest)request).getRequestURI());
      }

      String s = ((HttpServletRequest)request).getParameter("gzip");

      if ("false".equals(s)) {
        if (debug > 0) {
          System.out.println("got parameter gzip=false --> don't compress, just chain filter");
        }

        chain.doFilter(request, response);

        return;
      }

      Enumeration e = ((HttpServletRequest)request).getHeaders("Accept-Encoding");

      while (e.hasMoreElements()) {
        String name = (String)e.nextElement();

        if (name.indexOf("gzip") != -1) {
          if (debug > 0) {
            System.out.println("supports compression");
          }

          supportCompression = true;
        }
        else if (debug > 0) {
          System.out.println("no support for compresion");
        }
      }

    }

    if (!supportCompression) {
      if (debug > 0) {
        System.out.println("doFilter gets called wo compression");
      }

      chain.doFilter(request, response);

      return;
    }
    if ((response instanceof HttpServletResponse)) {
      CompressionServletResponseWrapper wrappedResponse = new CompressionServletResponseWrapper((HttpServletResponse)response);

      wrappedResponse.setDebugLevel(debug);
      wrappedResponse.setCompressionThreshold(compressionThreshold);

      if (debug > 0) {
        System.out.println("doFilter gets called with compression");
      }
      try
      {
        chain.doFilter(request, wrappedResponse);
      } finally {
        wrappedResponse.finishResponse();
      }

      return;
    }
  }

  public void setFilterConfig(FilterConfig filterConfig)
  {
    init(filterConfig);
  }

  public FilterConfig getFilterConfig()
  {
    return config;
  }
}