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

package com.liferay.util.servlet;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.util.CollectionFactory;
import com.liferay.util.ListUtil;
import com.liferay.util.PwdGenerator;

import java.util.Collections;
import java.util.Enumeration;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpSession;

/**
 * <a href="NullSession.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class NullSession implements HttpSession {

	public NullSession() {
		_attributes = CollectionFactory.getSyncHashMap();
		_creationTime = System.currentTimeMillis();
		_id =
			NullSession.class.getName() + StringPool.POUND +
				PwdGenerator.getPinNumber();
		_lastAccessedTime = _creationTime;
		_maxInactiveInterval = 0;
		_servletContext = null;
		_new = true;
	}

	public Object getAttribute(String name) {
		return _attributes.get(name);
	}

	public Enumeration getAttributeNames() {
		return Collections.enumeration(_attributes.keySet());
	}

	public long getCreationTime() {
		return _creationTime;
	}

	public String getId() {
		return _id;
	}

	public long getLastAccessedTime() {
		return _lastAccessedTime;
	}

	public int getMaxInactiveInterval() {
		return _maxInactiveInterval;
	}

	public ServletContext getServletContext() {
		return _servletContext;
	}

	/**
	 * @deprecated
	 */
	public javax.servlet.http.HttpSessionContext getSessionContext() {
		return null;
	}

	public Object getValue(String name) {
		return getAttribute(name);
	}

	public String[] getValueNames() {
		List names = ListUtil.fromEnumeration(getAttributeNames());

		return (String[])names.toArray(new String[0]);
	}

	public void invalidate() {
		_attributes.clear();
	}

	public boolean isNew() {
		return _new;
	}

	public void putValue(String name, Object value) {
		setAttribute(name, value);
	}

	public void removeAttribute(String name) {
		_attributes.remove(name);
	}

	public void removeValue(String name) {
		removeAttribute(name);
	}

	public void setAttribute(String name, Object value) {
		_attributes.put(name, value);
	}

	public void setMaxInactiveInterval(int maxInactiveInterval) {
		_maxInactiveInterval = maxInactiveInterval;
	}

	private Map _attributes;
	private long _creationTime;
	private String _id;
	private long _lastAccessedTime;
	private int _maxInactiveInterval;
	private ServletContext _servletContext;
	private boolean _new;

}