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

package com.liferay.portal.kernel.util;

import javax.portlet.ActionRequest;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

/**
 * <a href="PortalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalUtil {

	public static String getCDNHost() throws Exception {
		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETCDNHOST, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static String getComputerName() throws Exception {
		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETCOMPUTERNAME, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static HttpServletRequest getHttpServletRequest(PortletRequest req)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETHTTPSERVLETREQUEST, req, false);

		if (returnObj != null) {
			return (HttpServletRequest)returnObj;
		}
		else {
			return null;
		}
	}

	public static HttpServletResponse getHttpServletResponse(
			PortletResponse res)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETHTTPSERVLETRESPONSE, res, false);

		if (returnObj != null) {
			return (HttpServletResponse)returnObj;
		}
		else {
			return null;
		}
	}

	public static String getPortletNamespace(String portletId)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETPORTLETNAMESPACE, portletId, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static String getUserPassword(HttpSession ses)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETUSERPASSWORD, ses, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static String getUserPassword(HttpServletRequest req)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETUSERPASSWORD, req, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static String getUserPassword(ActionRequest req)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETUSERPASSWORD, req, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static String getUserPassword(RenderRequest req)
		throws Exception {

		Object returnObj = PortalClassInvoker.invoke(
			_CLASS, _METHOD_GETUSERPASSWORD, req, false);

		if (returnObj != null) {
			return (String)returnObj;
		}
		else {
			return null;
		}
	}

	public static void setPageSubtitle(
			String subtitle, HttpServletRequest req)
		throws Exception {

		PortalClassInvoker.invoke(
			_CLASS, _METHOD_SETPAGESUBTITLE, subtitle, req, false);
	}

	public static void setPageTitle(String title, HttpServletRequest req)
		throws Exception {

		PortalClassInvoker.invoke(
			_CLASS, _METHOD_SETPAGETITLE, title, req, false);
	}

	private static final String _CLASS = "com.liferay.portal.util.PortalUtil";

	private static final String _METHOD_GETCDNHOST = "getCDNHost";

	private static final String _METHOD_GETCOMPUTERNAME = "getComputerName";

	private static final String _METHOD_GETHTTPSERVLETREQUEST =
		"getHttpServletRequest";

	private static final String _METHOD_GETHTTPSERVLETRESPONSE =
		"getHttpServletResponse";

	private static final String _METHOD_GETPORTLETNAMESPACE =
		"getPortletNamespace";

	private static final String _METHOD_GETUSERPASSWORD = "getUserPassword";

	private static final String _METHOD_SETPAGESUBTITLE = "setPageSubtitle";

	private static final String _METHOD_SETPAGETITLE = "setPageTitle";

}