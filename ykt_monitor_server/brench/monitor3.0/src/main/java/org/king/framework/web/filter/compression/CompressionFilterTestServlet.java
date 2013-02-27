package org.king.framework.web.filter.compression;

import java.io.IOException;
import java.util.Enumeration;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class CompressionFilterTestServlet extends HttpServlet
{
  public void doGet(HttpServletRequest request, HttpServletResponse response)
    throws ServletException, IOException
  {
    ServletOutputStream out = response.getOutputStream();
    response.setContentType("text/plain");

    Enumeration e = request.getHeaders("Accept-Encoding");

    while (e.hasMoreElements()) {
      String name = (String)e.nextElement();
      out.println(name);

      if (name.indexOf("gzip") != -1)
        out.println("gzip supported -- able to compress");
      else {
        out.println("gzip not supported");
      }
    }

    out.println("Compression Filter Test Servlet");
    out.close();
  }
}