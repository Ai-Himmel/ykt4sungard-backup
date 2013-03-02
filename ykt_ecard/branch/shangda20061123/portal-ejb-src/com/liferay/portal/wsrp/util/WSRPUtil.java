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

package com.liferay.portal.wsrp.util;

import com.liferay.portal.util.PortalUtil;

import java.util.Comparator;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;

import org.apache.wsrp4j.producer.util.ServletAccess;
import org.apache.wsrp4j.util.Modes;
import org.apache.wsrp4j.util.WindowStates;

/**
 * <a href="WSRPUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.4 $
 *
 */
public class WSRPUtil {

	public static String getCompanyId() {
		HttpServletRequest req = WSRPUtil.getHttpServletRequest();

		String companyId = PortalUtil.getCompanyId(req);

		return companyId;
	}

	public static HttpServletRequest getHttpServletRequest() {
		return ServletAccess.getServletRequest();
	}

	public static ServletContext getServletContext() {
		return ServletAccess.getServletContext();
	}

	public static PortletMode fromWsrpMode(String wsrpMode) {
		PortletMode mode = PortletMode.VIEW;

		if (wsrpMode.equals(Modes._edit)) {
			mode = PortletMode.EDIT;
		}
		else if (wsrpMode.equals(Modes._view)) {
			mode = PortletMode.VIEW;
		}
		else if (wsrpMode.equals(Modes._help)) {
			mode = PortletMode.HELP;
		}

		return mode;
	}

	public static WindowState fromWsrpWindowState(String wsrpWindowState) {
		WindowState windowState = WindowState.NORMAL;

		if (wsrpWindowState.equals(WindowStates._maximized)) {
			windowState = WindowState.MAXIMIZED;
		}
		else if (wsrpWindowState.equals(WindowStates._minimized)) {
			windowState = WindowState.MINIMIZED;
		}
		else if (wsrpWindowState.equals(WindowStates._normal)) {
			windowState = WindowState.NORMAL;
		}

		return windowState;
	}

	public static String toWsrpMode(String mode) {
		String wsrpMode = Modes._view;

		if (mode.equals(PortletMode.EDIT.toString())) {
			wsrpMode = Modes._edit;
		}
		else if (mode.equals(PortletMode.VIEW.toString())) {
			wsrpMode = Modes._view;
		}
		else if (mode.equals(PortletMode.HELP.toString())) {
			wsrpMode = Modes._help;
		}

		return wsrpMode;
	}

	public static String toWsrpWindowState(String windowState) {
		String wsrpWindowState = WindowState.NORMAL.toString();

		if (windowState.equals(WindowState.MAXIMIZED.toString())) {
			wsrpWindowState = WindowStates._maximized;
		}
		else if (windowState.equals(WindowState.MINIMIZED.toString())) {
			wsrpWindowState = WindowStates._minimized;
		}
		else if (windowState.equals(WindowState.NORMAL.toString())) {
			windowState = WindowStates._normal;
		}

		return wsrpWindowState;
	}

	public static Comparator getPortletDescriptionComparator() {
		return _portletDescriptionComparator;
	}

	private static final Comparator _portletDescriptionComparator =
		new PortletDescriptionComparator();

}