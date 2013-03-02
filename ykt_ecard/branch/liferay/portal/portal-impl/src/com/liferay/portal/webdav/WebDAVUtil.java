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

package com.liferay.portal.webdav;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Namespace;

/**
 * <a href="WebDAVUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class WebDAVUtil {

	public static final Namespace DAV_URI = Namespace.get("D", "DAV:");

	public static final int SC_MULTI_STATUS = 207;

	public static String fixPath(String path) {
		if (path.endsWith(StringPool.SLASH)) {
			path = path.substring(0, path.length() - 1);
		}

		return path;
	}

	public static long getCompanyId(String path) {
		return getCompanyId(path, false);
	}

	public static long getCompanyId(String path, boolean fixPath) {
		if (fixPath) {
			path = fixPath(path);
		}

		String[] pathArray = getPathArray(path);

		if (pathArray.length <= 0) {
			return 0;
		}
		else {
			return GetterUtil.getLong(pathArray[0]);
		}
	}

	public static long getDepth(HttpServletRequest req) {
		String value = GetterUtil.getString(req.getHeader("Depth"));

		if (_log.isInfoEnabled()) {
			_log.info("\"Depth\" header is " + value);
		}

		if (value.equals("0")) {
			return 0;
		}
		else {
			return -1;
		}
	}

	public static String getDestination(
		HttpServletRequest req, String rootPath) {

		String headerDestination = req.getHeader("Destination");
		String[] pathSegments = StringUtil.split(headerDestination, rootPath);

		String destination = pathSegments[pathSegments.length - 1];

		if (_log.isDebugEnabled()) {
			_log.debug("Destination " + destination);
		}

		return destination;
	}

	public static String getEntryName(String[] pathArray) {
		if (pathArray.length <= 2) {
			return StringPool.BLANK;
		}
		else {
			return pathArray[pathArray.length - 1];
		}
	}

	public static long getGroupId(String path) {
		return getGroupId(path, false);
	}

	public static long getGroupId(String[] pathArray) {
		if (pathArray.length <= 1) {
			return 0;
		}
		else {
			return GetterUtil.getLong(pathArray[1]);
		}
	}

	public static long getGroupId(String path, boolean fixPath) {
		if (fixPath) {
			path = fixPath(path);
		}

		String[] pathArray = getPathArray(path);

		return getGroupId(pathArray);
	}

	public static String[] getPathArray(String path) {
		return getPathArray(path, false);
	}

	public static String[] getPathArray(String path, boolean fixPath) {
		if (fixPath) {
			path = fixPath(path);
		}

		if (path.startsWith(StringPool.SLASH)) {
			path = path.substring(1, path.length());
		}

		return StringUtil.split(path, StringPool.SLASH);
	}

	public static boolean isGroupPath(String path) {
		return isGroupPath(path, false);
	}

	public static boolean isGroupPath(String path, boolean fixPath) {
		if (fixPath) {
			path = fixPath(path);
		}

		String[] pathArray = getPathArray(path);

		if (pathArray.length == 2) {
			return true;
		}
		else {
			return false;
		}
	}

	public static boolean isOverwrite(HttpServletRequest req) {
		String value = GetterUtil.getString(req.getHeader("Overwrite"));

		if (value.equalsIgnoreCase("F") || !GetterUtil.getBoolean(value)) {
			return false;
		}
		else {
			return true;
		}
	}

	private static Log _log = LogFactory.getLog(WebDAVUtil.class);

}