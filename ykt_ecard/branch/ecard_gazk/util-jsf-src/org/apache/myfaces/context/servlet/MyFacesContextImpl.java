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

package org.apache.myfaces.context.servlet;

import javax.faces.context.ResponseWriter;

import javax.portlet.PortletContext;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;

import org.apache.myfaces.context.ReleaseableExternalContext;

/**
 * <a href="MyFacesContextImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.4 $
 *
 */
public class MyFacesContextImpl extends ServletFacesContextImpl {

	public MyFacesContextImpl(PortletContext portletContext,
							  PortletRequest portletRequest,
							  PortletResponse portletResponse) {

		super(portletContext, portletRequest, portletResponse);
	}

	public void setResponseWriter(ResponseWriter responseWriter) {
		if (responseWriter == null) {
			throw new NullPointerException("responseWriter");
		}

		_responseWriter = responseWriter;
	}

	public ResponseWriter getResponseWriter() {
		return _responseWriter;
	}

	public void release() {
		super.release();

		_responseWriter = null;
	}

	public void setExternalContext(ReleaseableExternalContext extContext) {
		_responseWriter = null;

		super.setExternalContext(extContext);
	}

	private ResponseWriter _responseWriter = null;

}