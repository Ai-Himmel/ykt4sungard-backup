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

package com.liferay.portal.util;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portlet.PortalPreferences;
import com.liferay.portlet.PortletPreferencesFactoryUtil;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="SessionTreeJSClicks.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SessionTreeJSClicks {

	public static final String CLASS_NAME = SessionTreeJSClicks.class.getName();

	public static void closeNode(
		HttpServletRequest req, String treeId, String nodeId) {

		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String openNodesString = prefs.getValue(CLASS_NAME, treeId);

			openNodesString = StringUtil.remove(openNodesString, nodeId);

			prefs.setValue(CLASS_NAME, treeId, openNodesString);
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public static void closeNodes(HttpServletRequest req, String treeId) {
		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String openNodesString = StringPool.BLANK;

			prefs.setValue(CLASS_NAME, treeId, openNodesString);
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public static String getOpenNodes(HttpServletRequest req, String treeId) {
		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			return prefs.getValue(CLASS_NAME, treeId);
		}
		catch (Exception e) {
			_log.error(e, e);

			return null;
		}
	}

	public static void openNode(
		HttpServletRequest req, String treeId, String nodeId) {

		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String openNodesString = prefs.getValue(CLASS_NAME, treeId);

			openNodesString = StringUtil.add(openNodesString, nodeId);

			prefs.setValue(CLASS_NAME, treeId, openNodesString);
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public static void openNodes(
		HttpServletRequest req, String treeId, String[] nodeIds) {

		try {
			PortalPreferences prefs =
				PortletPreferencesFactoryUtil.getPortalPreferences(req);

			String openNodesString = prefs.getValue(CLASS_NAME, treeId);

			for (int i = 0; i < nodeIds.length; i++) {
				openNodesString = StringUtil.add(openNodesString, nodeIds[i]);
			}

			prefs.setValue(CLASS_NAME, treeId, openNodesString);
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private static Log _log = LogFactory.getLog(SessionTreeJSClicks.class);

}