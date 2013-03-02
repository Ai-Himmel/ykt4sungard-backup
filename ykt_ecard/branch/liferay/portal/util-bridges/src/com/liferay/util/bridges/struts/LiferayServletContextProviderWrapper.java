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

package com.liferay.util.bridges.struts;

import com.liferay.portal.kernel.servlet.ServletContextProvider;

import javax.portlet.GenericPortlet;
import javax.portlet.PortletContext;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="LiferayServletContextProviderWrapper.java.html"><b><i>View Source
 * </i></b></a>
 *
 * @author Michael Young
 *
 */
public class LiferayServletContextProviderWrapper
	implements org.apache.portals.bridges.common.ServletContextProvider {

	public ServletContext getServletContext(GenericPortlet portlet) {
		ServletContextProvider provider = _getProvider(portlet);

		return provider.getServletContext(portlet);
	}

	public HttpServletRequest getHttpServletRequest(
		GenericPortlet portlet, PortletRequest req) {

		ServletContextProvider provider = _getProvider(portlet);

		return provider.getHttpServletRequest(portlet, req);
	}

	public HttpServletResponse getHttpServletResponse(
		GenericPortlet portlet, PortletResponse res) {

		ServletContextProvider provider = _getProvider(portlet);

		return provider.getHttpServletResponse(portlet, res);
	}

	private ServletContextProvider _getProvider(GenericPortlet portlet) {
		PortletContext portletCtx = portlet.getPortletContext();

		if (_provider == null) {
			_provider = (ServletContextProvider)portletCtx.getAttribute(
				ServletContextProvider.STRUTS_BRIDGES_CONTEXT_PROVIDER);
		}

		return _provider;
	}

	private ServletContextProvider _provider;

}