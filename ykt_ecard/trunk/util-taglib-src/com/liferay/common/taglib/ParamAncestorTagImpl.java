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

package com.liferay.common.taglib;

import com.liferay.portal.util.WebKeys;
import com.liferay.util.servlet.DynamicServletRequest;
import com.liferay.util.servlet.StringServletResponse;

import java.util.LinkedHashMap;
import java.util.Map;

import javax.servlet.ServletContext;
import javax.servlet.ServletRequest;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.tagext.BodyTagSupport;

/**
 * <a href="ParamAncestorTagImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class ParamAncestorTagImpl
	extends BodyTagSupport implements ParamAncestorTag {

	public void addParam(String name, String value) {
		if (_params == null) {
			_params = new LinkedHashMap();
		}

		String[] values = (String[])_params.get(name);

		if (values == null) {
			values = new String[] {value};
		}
		else {
			String[] newValues = new String[values.length + 1];

			System.arraycopy(values, 0, newValues, 0, values.length);

			newValues[newValues.length - 1] = value;

			values = newValues;
		}

		_params.put(name, values);
	}

	public void clearParams() {
		if (_params != null) {
			_params.clear();
		}
	}

	public Map getParams() {
		return _params;
	}

	public ServletContext getServletContext() {
		ServletRequest req = pageContext.getRequest();

		return (ServletContext)req.getAttribute(WebKeys.CTX);
	}

	public ServletRequest getServletRequest() {
		ServletRequest req = pageContext.getRequest();

		if (_params != null) {
			req = new DynamicServletRequest((HttpServletRequest)req, _params);
		}

		return req;
	}

	public StringServletResponse getServletResponse() {
		return new StringServletResponse(
			(HttpServletResponse)pageContext.getResponse());
	}

	private Map _params;

}