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

import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.servlet.ServletContextProvider;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.portlet.PortletContextImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.RenderResponseImpl;
import com.liferay.util.servlet.UploadServletRequest;

import java.io.IOException;

import javax.portlet.GenericPortlet;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="LiferayServletContextProvider.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author James Schopp
 * @author Michael Young
 *
 */
public class LiferayServletContextProvider implements ServletContextProvider {

	public ServletContext getServletContext(GenericPortlet portlet) {
		PortletContextImpl portletCtxImpl =
			(PortletContextImpl)portlet.getPortletContext();

		return getServletContext(portletCtxImpl.getServletContext());
	}

	public ServletContext getServletContext(ServletContext ctx) {
		return new LiferayServletContext(ctx);
	}

	public HttpServletRequest getHttpServletRequest(
		GenericPortlet portlet, PortletRequest req) {

		HttpServletRequest httpReq = null;

		if (req instanceof ActionRequestImpl) {
			httpReq = ((ActionRequestImpl)req).getHttpServletRequest();

	        String contentType = httpReq.getHeader(HttpHeaders.CONTENT_TYPE);

	        if ((contentType != null) &&
	            (contentType.startsWith(ContentTypes.MULTIPART_FORM_DATA))) {

	        	try {
	        		httpReq = new UploadServletRequest(httpReq);
	        	}
	        	catch (IOException ioe) {
	        	}

	        	httpReq = new LiferayStrutsRequestImpl(httpReq);
	        }
	        else {
	        	httpReq = new LiferayStrutsRequestImpl((ActionRequestImpl)req);
	        }
		}
		else {
			httpReq = new LiferayStrutsRequestImpl((RenderRequestImpl)req);
		}

		return httpReq;
	}

	public HttpServletResponse getHttpServletResponse(
		GenericPortlet portlet, PortletResponse res) {

		if (res instanceof RenderResponseImpl) {
			return ((RenderResponseImpl)res).getHttpServletResponse();
		}
		else {
			return ((ActionResponseImpl)res).getHttpServletResponse();
		}
	}

}