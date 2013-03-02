/*
 * Copyright 2000-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 

 */

package org.apache.wsrp4j.producer.util;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;

import org.apache.axis.AxisEngine;
import org.apache.axis.MessageContext;
import org.apache.axis.transport.http.HTTPConstants;

public class ServletAccess {

	public static HttpServlet getServlet() {
		MessageContext msgContext = AxisEngine.getCurrentMessageContext();
		HttpServlet servlet = (HttpServlet) msgContext
				.getProperty(HTTPConstants.MC_HTTP_SERVLET);
		return servlet;
	}

	public static ServletContext getServletContext() {
		ServletContext servletContext = getServlet().getServletContext();
		return servletContext;
	}

	public static HttpServletRequest getServletRequest() {
		MessageContext msgContext = AxisEngine.getCurrentMessageContext();
		HttpServletRequest servletRequest = (HttpServletRequest) msgContext
				.getProperty(HTTPConstants.MC_HTTP_SERVLETREQUEST);
		return servletRequest;
	}
}