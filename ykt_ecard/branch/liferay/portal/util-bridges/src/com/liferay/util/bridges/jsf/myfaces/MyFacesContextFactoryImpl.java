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

package com.liferay.util.bridges.jsf.myfaces;

import javax.faces.FacesException;
import javax.faces.context.FacesContext;
import javax.faces.context.FacesContextFactory;
import javax.faces.lifecycle.Lifecycle;

import javax.portlet.PortletContext;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;

import javax.servlet.ServletContext;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;

import org.apache.myfaces.context.servlet.ServletFacesContextImpl;

/**
 * <a href="MyFacesContextFactoryImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Myunghun Kim
 *
 */
public class MyFacesContextFactoryImpl extends FacesContextFactory {

	public FacesContext getFacesContext(
			Object context, Object request, Object response,
			Lifecycle lifecycle)
		throws FacesException {

		if (context == null) {
			throw new NullPointerException("context");
		}

		if (request == null) {
			throw new NullPointerException("request");
		}

		if (response == null) {
			throw new NullPointerException("response");
		}

		if (lifecycle == null) {
			throw new NullPointerException("lifecycle");
		}

		if (context instanceof ServletContext) {
			return new ServletFacesContextImpl(
				(ServletContext)context,
				(ServletRequest)request,
				(ServletResponse)response);
		}

		if (context instanceof PortletContext) {
			return new MyFacesContextImpl(
				(PortletContext)context, (PortletRequest)request,
				(PortletResponse)response);
		}

		throw new FacesException(
			"Unsupported context type " + getClass().getName());
	}

}