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

package com.liferay.portal.kernel.dao;

import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;

import java.text.DateFormat;

import java.util.Calendar;

import javax.portlet.PortletRequest;

import javax.servlet.ServletRequest;

/**
 * <a href="DAOParamUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DAOParamUtil {

	// Servlet Request

	public static boolean getBoolean(ServletRequest req, String param) {
		return GetterUtil.getBoolean(getString(req, param));
	}

	public static int getInteger(ServletRequest req, String param) {
		return GetterUtil.getInteger(getString(req, param));
	}

	public static String getISODate(ServletRequest req, String param) {
		int month = ParamUtil.getInteger(req, param + "Month");
		int day = ParamUtil.getInteger(req, param + "Day");
		int year = ParamUtil.getInteger(req, param + "Year");
		int hour = ParamUtil.getInteger(req, param + "Hour", -1);
		int minute = ParamUtil.getInteger(req, param + "Minute", -1);
		int amPm = ParamUtil.getInteger(req, param + "AmPm");

		if ((month >= 0) && (day > 0) && (year > 0)) {
			Calendar cal = CalendarFactoryUtil.getCalendar();

			if ((hour == -1) || (minute == -1)) {
				cal.set(year, month, day);
			}
			else {
				if (amPm == Calendar.PM) {
					hour += 12;
				}

				cal.set(year, month, day, hour, minute, 0);
			}

			DateFormat isoFormat = DateUtil.getISOFormat();

			return isoFormat.format(cal.getTime());
		}
		else {
			return null;
		}
	}

	public static String getLike(ServletRequest req, String param) {
		return getLike(req, param, null, true);
	}

	public static String getLike(
		ServletRequest req, String param, String defaultValue) {

		return getLike(req, param, defaultValue, true);
	}

	public static String getLike(
		ServletRequest req, String param, boolean toLowerCase) {

		return getLike(req, param, null, toLowerCase);
	}

	public static String getLike(
		ServletRequest req, String param, String defaultValue,
		boolean toLowerCase) {

		String value = req.getParameter(param);

		if (value != null) {
			value = value.trim();

			if (toLowerCase) {
				value = value.toLowerCase();
			}
		}

		if (Validator.isNull(value)) {
			value = defaultValue;
		}
		else {
			value = StringPool.PERCENT + value + StringPool.PERCENT;
		}

		return value;
	}

	public static long getLong(ServletRequest req, String param) {
		return GetterUtil.getLong(getString(req, param));
	}

	public static short getShort(ServletRequest req, String param) {
		return GetterUtil.getShort(getString(req, param));
	}

	public static String getString(ServletRequest req, String param) {
		String value = ParamUtil.getString(req, param);

		if (Validator.isNull(value)) {
			return null;
		}
		else {
			return value;
		}
	}

	// Portlet Request

	public static boolean getBoolean(PortletRequest req, String param) {
		return GetterUtil.getBoolean(getString(req, param));
	}

	public static int getInteger(PortletRequest req, String param) {
		return GetterUtil.getInteger(getString(req, param));
	}

	public static String getISODate(PortletRequest req, String param) {
		int month = ParamUtil.getInteger(req, param + "Month");
		int day = ParamUtil.getInteger(req, param + "Day");
		int year = ParamUtil.getInteger(req, param + "Year");
		int hour = ParamUtil.getInteger(req, param + "Hour", -1);
		int minute = ParamUtil.getInteger(req, param + "Minute", -1);
		int amPm = ParamUtil.getInteger(req, param + "AmPm");

		if ((month >= 0) && (day > 0) && (year > 0)) {
			Calendar cal = CalendarFactoryUtil.getCalendar();

			if ((hour == -1) || (minute == -1)) {
				cal.set(year, month, day);
			}
			else {
				if (amPm == Calendar.PM) {
					hour += 12;
				}

				cal.set(year, month, day, hour, minute, 0);
			}

			DateFormat isoFormat = DateUtil.getISOFormat();

			return isoFormat.format(cal.getTime());
		}
		else {
			return null;
		}
	}

	public static String getLike(PortletRequest req, String param) {
		return getLike(req, param, null, true);
	}

	public static String getLike(
		PortletRequest req, String param, String defaultValue) {

		return getLike(req, param, defaultValue, true);
	}

	public static String getLike(
		PortletRequest req, String param, boolean toLowerCase) {

		return getLike(req, param, null, toLowerCase);
	}

	public static String getLike(
		PortletRequest req, String param, String defaultValue,
		boolean toLowerCase) {

		String value = req.getParameter(param);

		if (value != null) {
			value = value.trim();

			if (toLowerCase) {
				value = value.toLowerCase();
			}
		}

		if (Validator.isNull(value)) {
			value = defaultValue;
		}
		else {
			value = StringPool.PERCENT + value + StringPool.PERCENT;
		}

		return value;
	}

	public static long getLong(PortletRequest req, String param) {
		return GetterUtil.getLong(getString(req, param));
	}

	public static short getShort(PortletRequest req, String param) {
		return GetterUtil.getShort(getString(req, param));
	}

	public static String getString(PortletRequest req, String param) {
		String value = ParamUtil.getString(req, param);

		if (Validator.isNull(value)) {
			return null;
		}
		else {
			return value;
		}
	}

}