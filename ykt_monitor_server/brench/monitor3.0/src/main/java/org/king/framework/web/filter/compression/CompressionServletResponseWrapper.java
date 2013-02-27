package org.king.framework.web.filter.compression;

import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintStream;
import java.io.PrintWriter;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServletResponseWrapper;

public class CompressionServletResponseWrapper extends HttpServletResponseWrapper
{
  protected static final String info = "CompressionServletResponseWrapper";
  protected HttpServletResponse origResponse = null;

  protected PrintWriter writer = null;

  protected ServletOutputStream stream = null;

  protected String contentType = null;

  protected int threshold = 0;

  private int debug = 0;

  public CompressionServletResponseWrapper(HttpServletResponse response)
  {
    super(response);
    origResponse = response;

    if (debug > 1)
      System.out.println("CompressionServletResponseWrapper constructor gets called");
  }

  public void setCompressionThreshold(int threshold)
  {
    if (debug > 1) {
      System.out.println("setCompressionThreshold to " + threshold);
    }

    this.threshold = threshold;
  }

  public void setContentLength(int length)
  {
  }

  public void setContentType(String contentType)
  {
    if (debug > 1) {
      System.out.println("setContentType to " + contentType);
    }

    this.contentType = contentType;
    origResponse.setContentType(contentType);
  }

  public void setDebugLevel(int debug)
  {
    this.debug = debug;
  }

  public ServletOutputStream getOutputStream()
    throws IOException
  {
    if (writer != null) {
      throw new IllegalStateException("getWriter() has already been called for this response");
    }

    if (stream == null) {
      stream = createOutputStream();
    }

    if (debug > 1) {
      System.out.println("stream is set to " + stream + " in getOutputStream");
    }

    return stream;
  }

  public PrintWriter getWriter()
    throws IOException
  {
    if (writer != null) {
      return writer;
    }

    if (stream != null) {
      throw new IllegalStateException("getOutputStream() has already been called for this response");
    }

    stream = createOutputStream();

    if (debug > 1) {
      System.out.println("stream is set to " + stream + " in getWriter");
    }

    String charEnc = origResponse.getCharacterEncoding();

    if (debug > 1) {
      System.out.println("character encoding is " + charEnc);
    }

    if (charEnc != null)
      writer = new PrintWriter(new OutputStreamWriter(stream, charEnc));
    else {
      writer = new PrintWriter(stream);
    }

    return writer;
  }

  public ServletOutputStream createOutputStream()
    throws IOException
  {
    if (debug > 1) {
      System.out.println("createOutputStream gets called");
    }

    CompressionResponseStream stream = new CompressionResponseStream(origResponse);

    stream.setDebugLevel(debug);
    stream.setBuffer(threshold);

    return stream;
  }

  public void finishResponse()
  {
    try
    {
      if (writer != null) {
        writer.close();
      }
      else if (stream != null)
        stream.close();
    }
    catch (IOException e)
    {
    }
  }

  public void flushBuffer()
    throws IOException
  {
    if (debug > 1) {
      System.out.println("flush buffer @ CompressionServletResponseWrapper");
    }

    ((CompressionResponseStream)stream).flush();
  }

  private static String getCharsetFromContentType(String type)
  {
    if (type == null) {
      return null;
    }

    int semi = type.indexOf(";");

    if (semi == -1) {
      return null;
    }

    String afterSemi = type.substring(semi + 1);
    int charsetLocation = afterSemi.indexOf("charset=");

    if (charsetLocation == -1) {
      return null;
    }
    String afterCharset = afterSemi.substring(charsetLocation + 8);
    String encoding = afterCharset.trim();

    return encoding;
  }
}