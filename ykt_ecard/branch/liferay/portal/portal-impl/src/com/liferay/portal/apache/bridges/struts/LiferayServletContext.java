/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portal.apache.bridges.struts;

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

/**
 * <a href="LiferayServletContext.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class LiferayServletContext implements ServletContext {

	public LiferayServletContext(ServletContext ctx) {
		_ctx = ctx;
	}

	public Object getAttribute(String name) {
		return _ctx.getAttribute(name);
	}

	public Enumeration getAttributeNames() {
		return _ctx.getAttributeNames();
	}

	public ServletContext getContext(String uriPath) {
		ServletContext refContext = _ctx.getContext(uriPath);

		if (refContext == _ctx) {
			return this;
		}
		else {
			return refContext;
		}
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
		RequestDispatcher dispatcher = _ctx.getNamedDispatcher(name);

		if (dispatcher != null) {
			dispatcher = new LiferayRequestDispatcher(dispatcher, name);
		}

		return dispatcher;
	}

	public String getRealPath(String arg0) {
		return _ctx.getRealPath(arg0);
	}

	public RequestDispatcher getRequestDispatcher(String path) {
		RequestDispatcher dispatcher = _ctx.getRequestDispatcher(path);

		if (dispatcher != null) {
			dispatcher = new LiferayRequestDispatcher(dispatcher, path);
		}

		return dispatcher;
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

	public void log(Exception exception, String message) {
		_ctx.log(message, exception);
	}

	public void log(String message) {
		_ctx.log(message);
	}

	public void log(String message, Throwable t) {
		_ctx.log(message, t);
	}

	public void removeAttribute(String name) {
		_ctx.removeAttribute(name);
	}

	public void setAttribute(String name, Object value) {
		_ctx.setAttribute(name, value);
	}

	public String toString() {
		return _ctx.toString();
	}

	private ServletContext _ctx;

}