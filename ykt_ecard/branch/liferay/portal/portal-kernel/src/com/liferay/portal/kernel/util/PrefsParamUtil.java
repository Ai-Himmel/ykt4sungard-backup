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

import javax.portlet.PortletPreferences;

import javax.servlet.ServletRequest;

/**
 * <a href="PrefsParamUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PrefsParamUtil {

	public static boolean getBoolean(
		PortletPreferences prefs, ServletRequest req, String param) {

		return getBoolean(prefs, req, param, GetterUtil.DEFAULT_BOOLEAN);
	}

	public static boolean getBoolean(
		PortletPreferences prefs, ServletRequest req, String param,
		boolean defaultValue) {

		String prefsValue = prefs.getValue(param, null);

		boolean getterUtilValue = GetterUtil.getBoolean(
			prefsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static double getDouble(
		PortletPreferences prefs, ServletRequest req, String param) {

		return getDouble(prefs, req, param, GetterUtil.DEFAULT_DOUBLE);
	}

	public static double getDouble(
		PortletPreferences prefs, ServletRequest req, String param,
		double defaultValue) {

		String prefsValue = prefs.getValue(param, null);

		double getterUtilValue = GetterUtil.getDouble(
			prefsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static int getInteger(
		PortletPreferences prefs, ServletRequest req, String param) {

		return getInteger(prefs, req, param, GetterUtil.DEFAULT_INTEGER);
	}

	public static int getInteger(
		PortletPreferences prefs, ServletRequest req, String param,
		int defaultValue) {

		String prefsValue = prefs.getValue(param, null);

		int getterUtilValue = GetterUtil.getInteger(
			prefsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static long getLong(
		PortletPreferences prefs, ServletRequest req, String param) {

		return getLong(prefs, req, param, GetterUtil.DEFAULT_LONG);
	}

	public static long getLong(
		PortletPreferences prefs, ServletRequest req, String param,
		long defaultValue) {

		String prefsValue = prefs.getValue(param, null);

		long getterUtilValue = GetterUtil.getLong(
			prefsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static String getString(
		PortletPreferences prefs, ServletRequest req, String param) {

		return getString(prefs, req, param, GetterUtil.DEFAULT_STRING);
	}

	public static String getString(
		PortletPreferences prefs, ServletRequest req, String param,
		String defaultValue) {

		String prefsValue = prefs.getValue(param, null);

		String getterUtilValue = GetterUtil.getString(
			prefsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

}