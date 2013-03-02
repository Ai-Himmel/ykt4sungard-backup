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

package com.liferay.portlet;

import java.util.Locale;

import javax.portlet.ActionResponse;
import javax.portlet.PortletResponse;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpServletResponseWrapper;

/**
 * <a href="PortletServletResponse.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletServletResponse extends HttpServletResponseWrapper {

	public PortletServletResponse(HttpServletResponse res,
								  PortletResponse portletResponse) {

		super(res);

		_portletResponse = portletResponse;

		if (_portletResponse instanceof ActionResponse) {
			_action = true;
		}
		else {
			_action = false;
		}
	}

	public String encodeRedirectUrl(String url) {
		return encodeRedirectURL(url);
	}

	public String encodeRedirectURL(String url) {
		return null;
	}

	public String encodeUrl(String path) {
		return encodeURL(path);
	}

	public String encodeURL(String path) {
		if (_action) {
			throw new UnsupportedOperationException();
		}
		else {
			RenderResponse res = (RenderResponse)_portletResponse;

			return res.encodeURL(path);
		}
	}

	public Locale getLocale() {
		if (_action) {
			return null;
		}
		else {
			RenderResponse res = (RenderResponse)_portletResponse;

			return res.getLocale();
		}
	}
	public int getBufferSize() {
		if (_action) {
			return 0;
		}
		else {
			RenderResponse res = (RenderResponse)_portletResponse;

			return res.getBufferSize();
		}
	}

	public boolean isCommitted() {
		if (_action) {
			return false;
		}
		else {
			RenderResponse res = (RenderResponse)_portletResponse;

			return res.isCommitted();
		}
	}

	private PortletResponse _portletResponse;
	private boolean _action;

}