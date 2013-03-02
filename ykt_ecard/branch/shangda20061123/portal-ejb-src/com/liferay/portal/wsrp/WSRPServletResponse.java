/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.wsrp;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.Serializable;
import java.io.StringWriter;
import java.io.UnsupportedEncodingException;

import java.util.Locale;

import javax.servlet.ServletOutputStream;
import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="WSRPServletResponse.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.6 $
 *
 */
public class WSRPServletResponse implements HttpServletResponse, Serializable {

	public static final int DEFAULT_STATUS_CODE = 200;

	public WSRPServletResponse() {
		_statusCode = DEFAULT_STATUS_CODE;
		_locale = new Locale("en", "US");

		setContentType("text/html");
	}

	public void setBufferSize(int size) {
	}

	public int getBufferSize() {
		return 4096;
	}

	public void setCharacterEncoding(String encoding) {
		_encoding = encoding;
	}

	public String getCharacterEncoding() {
		return _encoding;
	}

	public boolean isCommitted() {
		return false;
	}

	public void setContentLength(int size) {
	}

	public void setContentType(String contentType) {
		_contentType = contentType;
	}

	public String getContentType() {
		return _contentType;
	}

	public void setDateHeader(String name, long dateValue) {
	}

	public void setHeader(String name, String value) {
	}

	public void setIntHeader(String name, int value) {
	}

	public void setLocale(Locale locale) {
		_locale = locale;
	}

	public java.util.Locale getLocale() {
		return _locale;
	}

	public ServletOutputStream getOutputStream() {
		_callGetOutputStream = true;

		return _sos;
	}

	public void setStatus(int statusCode) {
		_statusCode = statusCode;
	}

	public void setStatus(int statusCode, String message) {
		_statusCode = statusCode;
		_statusMessage = message;
	}

	public String getString() throws UnsupportedEncodingException {
		if (_callGetOutputStream) {
			return _baos.toString();
		}
		else if (_callGetWriter) {
			return _sw.toString();
		}
		else {
			return "";
		}
	}

	public PrintWriter getWriter() {
		_callGetWriter = true;

		return _pw;
	}

	public void addCookie(Cookie cookie) {
	}

	public void addDateHeader(String name, long dateValue) {
	}

	public void addHeader(String name, String value) {
	}

	public void addIntHeader(String name, int value) {
	}

	public boolean containsHeader(String headerName) {
		return false;
	}

	public String encodeRedirectURL(String url) {
		return url;
	}

	public String encodeRedirectUrl(String url) {
		return encodeRedirectURL(url);
	}

	public String encodeURL(String url) {
		return url;
	}

	public String encodeUrl(String url) {
		return encodeURL(url);
	}

	public void flushBuffer() {
	}

	public void reset() {
	}

	public void resetBuffer() {
	}

	public void sendError(int errorCode) throws IOException {
	}

	public void sendError(int errorCode, String message) throws IOException {
	}

	public void sendRedirect(String location) {
		_redirectURI = location;
	}

	private ByteArrayOutputStream _baos = new ByteArrayOutputStream();
	private Locale _locale;
	private ServletOutputStream _sos = new ServletOutputStream() {
		public void write(int b) throws IOException {
			_baos.write(b);
		}
	};

	private String _encoding;
	private String _redirectURI;
	private String _statusMessage;
	private StringWriter _stringWriter;
	private StringWriter _sw = new StringWriter();
	private PrintWriter _pw = new PrintWriter(_sw);
	private boolean _callGetOutputStream;
	private boolean _callGetWriter;
	private boolean _isFinished;
	private int _statusCode;
	private String _contentType;

}