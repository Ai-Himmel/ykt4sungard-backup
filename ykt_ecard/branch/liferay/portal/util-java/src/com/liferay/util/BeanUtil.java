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

package com.liferay.util;

import com.liferay.portal.kernel.util.GetterUtil;

import org.apache.commons.beanutils.PropertyUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="BeanUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class BeanUtil {

	public static boolean getBoolean(Object bean, String param) {
		return getBoolean(bean, param, GetterUtil.DEFAULT_BOOLEAN);
	}

	public static boolean getBoolean(
		Object bean, String param, boolean defaultValue) {

		Boolean beanValue = null;

		if (bean != null) {
			try {
				beanValue =
					(Boolean)PropertyUtils.getSimpleProperty(bean, param);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		if (beanValue == null) {
			return defaultValue;
		}
		else {
			return beanValue.booleanValue();
		}
	}

	public static double getDouble(Object bean, String param) {
		return getDouble(bean, param, GetterUtil.DEFAULT_DOUBLE);
	}

	public static double getDouble(
		Object bean, String param, double defaultValue) {

		Double beanValue = null;

		if (bean != null) {
			try {
				beanValue =
					(Double)PropertyUtils.getSimpleProperty(bean, param);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		if (beanValue == null) {
			return defaultValue;
		}
		else {
			return beanValue.doubleValue();
		}
	}

	public static int getInteger(Object bean, String param) {
		return getInteger(bean, param, GetterUtil.DEFAULT_INTEGER);
	}

	public static int getInteger(
		Object bean, String param, int defaultValue) {

		Integer beanValue = null;

		if (bean != null) {
			try {
				beanValue =
					(Integer)PropertyUtils.getSimpleProperty(bean, param);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		if (beanValue == null) {
			return defaultValue;
		}
		else {
			return beanValue.intValue();
		}
	}

	public static long getLong(Object bean, String param) {
		return getLong(bean, param, GetterUtil.DEFAULT_LONG);
	}

	public static long getLong(
		Object bean, String param, long defaultValue) {

		Long beanValue = null;

		if (bean != null) {
			try {
				beanValue =
					(Long)PropertyUtils.getSimpleProperty(bean, param);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		if (beanValue == null) {
			return defaultValue;
		}
		else {
			return beanValue.longValue();
		}
	}

	public static Object getObject(Object bean, String param) {
		Object beanValue = null;

		if (bean != null) {
			try {
				beanValue = PropertyUtils.getSimpleProperty(bean, param);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		return beanValue;
	}

	public static String getString(Object bean, String param) {
		return getString(bean, param, GetterUtil.DEFAULT_STRING);
	}

	public static String getString(
		Object bean, String param, String defaultValue) {

		String beanValue = null;

		if (bean != null) {
			try {
				beanValue =
					(String)PropertyUtils.getSimpleProperty(bean, param);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		if (beanValue == null) {
			return defaultValue;
		}
		else {
			return beanValue;
		}
	}

	private static Log _log = LogFactory.getLog(BeanUtil.class);

}