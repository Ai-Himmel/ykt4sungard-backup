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

import java.util.Collections;
import java.util.Enumeration;
import java.util.Locale;
import java.util.Map;
import java.util.Vector;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletRequestWrapper;

/**
 * <a href="WSRPServletRequest.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.5 $
 *
 */
public class WSRPServletRequest extends HttpServletRequestWrapper {

	public WSRPServletRequest(HttpServletRequest req, Locale locale,
		String mimeType, Map parameters) {
		super(req);

		_locale = locale;
		_mimeType = mimeType;
		_parameters = parameters;
	}

	public String getContentType() {
		return _mimeType;
	}

	public Locale getLocale() {
		return _locale;
	}

	public Enumeration getLocales() {
		Vector v = new Vector();
		v.add(_locale);

		return v.elements();
	}

	public String getParameter(String name) {
		String[] values = (String[]) getParameterMap().get(name);

		if (values == null) {
			return null;
		}
		else {
			return values[0];
		}
	}

	public Map getParameterMap() {
		return _parameters;
	}

	public Enumeration getParameterNames() {
		return Collections.enumeration(getParameterMap().keySet());
	}

	public String[] getParameterValues(String name) {
		return (String[]) getParameterMap().get(name);
	}

	private Locale _locale;
	private Map _parameters;
	private String _mimeType;

}