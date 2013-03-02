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

package com.liferay.portlet.jcvs.servlet;

import java.io.InputStream;

import java.net.MalformedURLException;
import java.net.URL;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.Set;

import javax.servlet.RequestDispatcher;
import javax.servlet.Servlet;
import javax.servlet.ServletContext;
import javax.servlet.ServletException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JCVSServletContext.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class JCVSServletContext implements ServletContext {

	public JCVSServletContext(ServletContext ctx) {
		_ctx = ctx;
	}

	public Object getAttribute(String name) {
		return _ctx.getAttribute(name);
	}

	public Enumeration getAttributeNames() {
		return _ctx.getAttributeNames();
	}

	public ServletContext getContext(String uripath) {
		return _ctx.getContext(uripath);
	}

	public String getInitParameter(String name) {
		return _ctx.getInitParameter(name);
	}

	public Enumeration getInitParameterNames() {
		return _ctx.getInitParameterNames();
	}

	public int getMajorVersion() {
		return _ctx.getMajorVersion();
	}

	public String getMimeType(String file) {
		return _ctx.getMimeType(file);
	}

	public int getMinorVersion() {
		return _ctx.getMinorVersion();
	}

	public RequestDispatcher getNamedDispatcher(String name) {
		return _ctx.getNamedDispatcher(name);
	}

	public String getRealPath(String path) {
		return _ctx.getRealPath(path);
	}

	public RequestDispatcher getRequestDispatcher(String path) {
		return _ctx.getRequestDispatcher(path);
	}

	public URL getResource(String path) throws MalformedURLException {
		return _ctx.getResource(path);
	}

	public InputStream getResourceAsStream(String path) {
		return _ctx.getResourceAsStream(path);
	}

	public Set getResourcePaths(String path) {
		return _ctx.getResourcePaths(path);
	}

	public String getServerInfo() {
		return _ctx.getServerInfo();
	}

	public Servlet getServlet(String name) throws ServletException {
		return null;
	}

	public String getServletContextName() {
		return _ctx.getServletContextName();
	}

	public Enumeration getServletNames() {
		return Collections.enumeration(new ArrayList());
	}

	public Enumeration getServlets() {
		return Collections.enumeration(new ArrayList());
	}

	public void log(Exception exception, String msg) {
		_log.info(msg, exception);
	}

	public void log(String msg) {
		_log.info(msg);
	}

	public void log(String msg, Throwable throwable) {
		_log.info(msg, throwable);
	}

	public void removeAttribute(String name) {
		_ctx.removeAttribute(name);
	}

	public void setAttribute(String name, Object object) {
		_ctx.setAttribute(name, object);
	}

	private static final Log _log = LogFactory.getLog(JCVSServletContext.class);

	private ServletContext _ctx;

}