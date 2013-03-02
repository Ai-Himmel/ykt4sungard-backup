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

import java.util.Properties;

import javax.servlet.ServletRequest;

/**
 * <a href="PropertiesParamUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PropertiesParamUtil {

	public static boolean getBoolean(
		Properties props, ServletRequest req, String param) {

		return getBoolean(props, req, param, GetterUtil.DEFAULT_BOOLEAN);
	}

	public static boolean getBoolean(
		Properties props, ServletRequest req, String param,
		boolean defaultValue) {

		String propsValue = props.getProperty(param, null);

		boolean getterUtilValue = GetterUtil.getBoolean(
			propsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static double getDouble(
		Properties props, ServletRequest req, String param) {

		return getDouble(props, req, param, GetterUtil.DEFAULT_DOUBLE);
	}

	public static double getDouble(
		Properties props, ServletRequest req, String param,
		double defaultValue) {

		String propsValue = props.getProperty(param, null);

		double getterUtilValue = GetterUtil.getDouble(
			propsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static int getInteger(
		Properties props, ServletRequest req, String param) {

		return getInteger(props, req, param, GetterUtil.DEFAULT_INTEGER);
	}

	public static int getInteger(
		Properties props, ServletRequest req, String param, int defaultValue) {

		String propsValue = props.getProperty(param, null);

		int getterUtilValue = GetterUtil.getInteger(
			propsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static long getLong(
		Properties props, ServletRequest req, String param) {

		return getLong(props, req, param, GetterUtil.DEFAULT_LONG);
	}

	public static long getLong(
		Properties props, ServletRequest req, String param, long defaultValue) {

		String propsValue = props.getProperty(param, null);

		long getterUtilValue = GetterUtil.getLong(
			propsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

	public static String getString(
		Properties props, ServletRequest req, String param) {

		return getString(props, req, param, GetterUtil.DEFAULT_STRING);
	}

	public static String getString(
		Properties props, ServletRequest req, String param,
		String defaultValue) {

		String propsValue = props.getProperty(param, null);

		String getterUtilValue = GetterUtil.getString(
			propsValue, defaultValue);

		return ParamUtil.get(req, param, getterUtilValue);
	}

}