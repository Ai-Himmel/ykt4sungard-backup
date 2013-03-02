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

package com.liferay.util.bridges.jsf.sun;

import java.io.IOException;
import java.io.InputStream;

import java.net.MalformedURLException;
import java.net.URL;

import java.security.Principal;

import java.util.Iterator;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import javax.faces.context.ExternalContext;

import javax.servlet.ServletContext;

/**
 * <a href="LiferayServletContextAdapter.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Neil Griffin
 *
 */
public class LiferayServletContextAdapter extends ExternalContext {

	public LiferayServletContextAdapter(ServletContext servletContext) {
		_servletContext = servletContext;
	}

	public Map getApplicationMap() {
		if (_applicationMap == null) {
			_applicationMap = new LiferayApplicationMap(_servletContext);
		}

		return _applicationMap;
	}

	public String getAuthType() {
		return null;
	}

	public Object getContext() {
		return null;
	}

	public void dispatch(String string) throws IOException {
	}

	public String encodeActionURL(String string) {
		return null;
	}

	public String encodeNamespace(String string) {
		return null;
	}

	public String encodeResourceURL(String string) {
		return null;
	}

	public String getInitParameter(String string) {
		return null;
	}

	public Map getInitParameterMap() {
		return null;
	}

	public void log(String string) {
	}

	public void log(String string, Throwable throwable) {
	}

	public void redirect(String string) throws IOException {
	}

	public String getRemoteUser() {
		return null;
	}

	public Object getRequest() {
		return null;
	}

	public String getRequestContextPath() {
		return null;
	}

	public Map getRequestCookieMap() {
		return null;
	}

	public Map getRequestHeaderMap() {
		return null;
	}

	public Map getRequestHeaderValuesMap() {
		return null;
	}

	public Locale getRequestLocale() {
		return null;
	}

	public Iterator getRequestLocales() {
		return null;
	}

	public Map getRequestMap() {
		return null;
	}

	public Map getRequestParameterMap() {
		return null;
	}

	public Iterator getRequestParameterNames() {
		return null;
	}

	public Map getRequestParameterValuesMap() {
		return null;
	}

	public String getRequestPathInfo() {
		return null;
	}

	public String getRequestServletPath() {
		return null;
	}

	public URL getResource(String string) throws MalformedURLException {
		return null;
	}

	public InputStream getResourceAsStream(String string) {
		return null;
	}

	public Set getResourcePaths(String string) {
		return null;
	}

	public Object getResponse() {
		return null;
	}

	public Object getSession(boolean b) {
		return null;
	}

	public Map getSessionMap() {
		return null;
	}

	public boolean isUserInRole(String string) {
		return false;
	}

	public Principal getUserPrincipal() {
		return null;
	}

	private ServletContext _servletContext;
	private LiferayApplicationMap _applicationMap;

}