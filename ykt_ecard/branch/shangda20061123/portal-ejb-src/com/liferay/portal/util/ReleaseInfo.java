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

package com.liferay.portal.util;

import com.liferay.util.GetterUtil;

import java.text.DateFormat;

import java.util.Date;

/**
 * <a href="ReleaseInfo.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.784 $
 *
 */
public class ReleaseInfo {

	static String name = "Liferay Portal";

	static {
		if (PropsUtil.get(PropsUtil.PORTAL_RELEASE).equals("enterprise")) {
			name += " Enterprise";
		}
		else {
			name += " Professional";
		}
	}

	static String version = "3.5.0";

	static String codeName = "Simeon";

	static String build = "2215";

	static String date = "July 25, 2005";

	static String releaseInfo =
		name + " " + version + " (" + codeName + " / Build " + build + " / " +
			date + ")";

	static String serverInfo = name + " / " + version;

	public static final String getVersion() {
		return version;
	}

	public static final String getCodeName() {
		return codeName;
	}

	public static final int getBuildNumber() {
		return Integer.parseInt(build);
	}

	public static final Date getBuildDate() {
		DateFormat df = DateFormat.getDateInstance(DateFormat.LONG);

		return GetterUtil.getDate(date, df);
	}

	public static final String getReleaseInfo() {
		return releaseInfo;
	}

	public static final String getServerInfo() {
		return serverInfo;
	}

}