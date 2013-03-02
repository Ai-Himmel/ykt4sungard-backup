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

package com.liferay.portal.servlet;

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.servlet.DynamicServletRequest;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.List;
import java.util.Set;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="NamespaceServletRequest.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * This class ensures that portlet attributes and parameters are private to the
 * portlet.
 * </p>
 *
 * @author Brian Myunghun Kim
 *
 */
public class NamespaceServletRequest extends DynamicServletRequest {

	static Set reservedAttrs = CollectionFactory.getHashSet();

	static {
		reservedAttrs.add(JavaConstants.JAVAX_PORTLET_CONFIG);
		reservedAttrs.add(JavaConstants.JAVAX_PORTLET_PORTLET);
		reservedAttrs.add(JavaConstants.JAVAX_PORTLET_REQUEST);
		reservedAttrs.add(JavaConstants.JAVAX_PORTLET_RESPONSE);
	}

	public static final String[] CUSTOM_RESERVED_ATTRS = PropsUtil.getArray(
		PropsUtil.REQUEST_SHARED_ATTRIBUTES);

	public NamespaceServletRequest(HttpServletRequest req, String attrNamespace,
								   String paramNamespace) {

		this(req, attrNamespace, paramNamespace, true);
	}

	public NamespaceServletRequest(HttpServletRequest req, String attrNamespace,
								   String paramNamespace, boolean inherit) {

		super(req, inherit);

		_attrNamespace = attrNamespace;
		_paramNamespace = paramNamespace;
	}

	public Object getAttribute(String name) {
		Object value = super.getAttribute(_attrNamespace + name);

		if (value == null) {
			value = super.getAttribute(name);
		}

		return value;
	}

	public Enumeration getAttributeNames() {
		List names = new ArrayList();

		Enumeration enu = super.getAttributeNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith(_attrNamespace)) {
				names.add(
					name.substring(_attrNamespace.length(), name.length()));
			}
		}

		return Collections.enumeration(names);
	}

	public void setAttribute(String name, Object value) {
		if (_isReservedParam(name)) {
			super.setAttribute(name, value);
		}
		else {
			super.setAttribute(_attrNamespace + name, value);
		}
	}

	public void setAttribute(
		String name, Object value, boolean privateRequestAttribute) {

		if (!privateRequestAttribute) {
			super.setAttribute(name, value);
		}
		else {
			setAttribute(name, value);
		}
	}

	public void removeAttribute(String name) {
		if (_isReservedParam(name)) {
			super.removeAttribute(name);
		}
		else {
			super.removeAttribute(_attrNamespace + name);
		}
	}

	public String getParameter(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		String value = super.getParameter(name);

		if (value == null) {
			value = super.getParameter(_paramNamespace + name);
		}

		return value;
	}

	private boolean _isReservedParam(String name) {
		if (reservedAttrs.contains(name)) {
			return true;
		}
		else {
			for (int i = 0; i < CUSTOM_RESERVED_ATTRS.length; i++) {
				if (name.startsWith(CUSTOM_RESERVED_ATTRS[i])) {
					return true;
				}
			}
		}

		return false;
	}

	private String _attrNamespace;
	private String _paramNamespace;

}