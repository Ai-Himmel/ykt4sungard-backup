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

import java.text.DateFormat;

import java.util.Date;

/**
 * <a href="GetterUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GetterUtil {

	public static final boolean DEFAULT_BOOLEAN = false;

	public static final boolean[] DEFAULT_BOOLEAN_VALUES = new boolean[0];

	public static final double DEFAULT_DOUBLE = 0.0;

	public static final double[] DEFAULT_DOUBLE_VALUES = new double[0];

	public static final float DEFAULT_FLOAT = 0;

	public static final float[] DEFAULT_FLOAT_VALUES = new float[0];

	public static final int DEFAULT_INTEGER = 0;

	public static final int[] DEFAULT_INTEGER_VALUES = new int[0];

	public static final long DEFAULT_LONG = 0;

	public static final long[] DEFAULT_LONG_VALUES = new long[0];

	public static final short DEFAULT_SHORT = 0;

	public static final short[] DEFAULT_SHORT_VALUES = new short[0];

	public static final String DEFAULT_STRING = StringPool.BLANK;

	public static String[] BOOLEANS = {"true", "t", "y", "on", "1"};

	public static boolean getBoolean(String value) {
		return getBoolean(value, DEFAULT_BOOLEAN);
	}

	public static boolean getBoolean(String value, boolean defaultValue) {
		return get(value, defaultValue);
	}

	public static boolean[] getBooleanValues(String[] values) {
		return getBooleanValues(values, DEFAULT_BOOLEAN_VALUES);
	}

	public static boolean[] getBooleanValues(
		String[] values, boolean[] defaultValue) {

		if (values == null) {
			return defaultValue;
		}

		boolean[] booleanValues = new boolean[values.length];

		for (int i = 0; i < values.length; i++) {
			booleanValues[i] = getBoolean(values[i]);
		}

		return booleanValues;
	}

	public static Date getDate(String value, DateFormat df) {
		return getDate(value, df, new Date());
	}

	public static Date getDate(String value, DateFormat df, Date defaultValue) {
		return get(value, df, defaultValue);
	}

	public static double getDouble(String value) {
		return getDouble(value, DEFAULT_DOUBLE);
	}

	public static double getDouble(String value, double defaultValue) {
		return get(value, defaultValue);
	}

	public static double[] getDoubleValues(String[] values) {
		return getDoubleValues(values, DEFAULT_DOUBLE_VALUES);
	}

	public static double[] getDoubleValues(
		String[] values, double[] defaultValue) {

		if (values == null) {
			return defaultValue;
		}

		double[] doubleValues = new double[values.length];

		for (int i = 0; i < values.length; i++) {
			doubleValues[i] = getDouble(values[i]);
		}

		return doubleValues;
	}

	public static float getFloat(String value) {
		return getFloat(value, DEFAULT_FLOAT);
	}

	public static float getFloat(String value, float defaultValue) {
		return get(value, defaultValue);
	}

	public static float[] getFloatValues(String[] values) {
		return getFloatValues(values, DEFAULT_FLOAT_VALUES);
	}

	public static float[] getFloatValues(
		String[] values, float[] defaultValue) {

		if (values == null) {
			return defaultValue;
		}

		float[] floatValues = new float[values.length];

		for (int i = 0; i < values.length; i++) {
			floatValues[i] = getFloat(values[i]);
		}

		return floatValues;
	}

	public static int getInteger(String value) {
		return getInteger(value, DEFAULT_INTEGER);
	}

	public static int getInteger(String value, int defaultValue) {
		return get(value, defaultValue);
	}

	public static int[] getIntegerValues(String[] values) {
		return getIntegerValues(values, DEFAULT_INTEGER_VALUES);
	}

	public static int[] getIntegerValues(String[] values, int[] defaultValue) {
		if (values == null) {
			return defaultValue;
		}

		int[] intValues = new int[values.length];

		for (int i = 0; i < values.length; i++) {
			intValues[i] = getInteger(values[i]);
		}

		return intValues;
	}

	public static long getLong(String value) {
		return getLong(value, DEFAULT_LONG);
	}

	public static long getLong(String value, long defaultValue) {
		return get(value, defaultValue);
	}

	public static long[] getLongValues(String[] values) {
		return getLongValues(values, DEFAULT_LONG_VALUES);
	}

	public static long[] getLongValues(String[] values, long[] defaultValue) {
		if (values == null) {
			return defaultValue;
		}

		long[] longValues = new long[values.length];

		for (int i = 0; i < values.length; i++) {
			longValues[i] = getLong(values[i]);
		}

		return longValues;
	}

	public static short getShort(String value) {
		return getShort(value, DEFAULT_SHORT);
	}

	public static short getShort(String value, short defaultValue) {
		return get(value, defaultValue);
	}

	public static short[] getShortValues(String[] values) {
		return getShortValues(values, DEFAULT_SHORT_VALUES);
	}

	public static short[] getShortValues(
		String[] values, short[] defaultValue) {

		if (values == null) {
			return defaultValue;
		}

		short[] shortValues = new short[values.length];

		for (int i = 0; i < values.length; i++) {
			shortValues[i] = getShort(values[i]);
		}

		return shortValues;
	}

	public static String getString(String value) {
		return getString(value, DEFAULT_STRING);
	}

	public static String getString(String value, String defaultValue) {
		return get(value, defaultValue);
	}

	public static boolean get(String value, boolean defaultValue) {
		if (value != null) {
			try {
				value = value.trim();

				if (value.equalsIgnoreCase(BOOLEANS[0]) ||
					value.equalsIgnoreCase(BOOLEANS[1]) ||
					value.equalsIgnoreCase(BOOLEANS[2]) ||
					value.equalsIgnoreCase(BOOLEANS[3]) ||
					value.equalsIgnoreCase(BOOLEANS[4])) {

					return true;
				}
				else {
					return false;
				}
			}
			catch (Exception e) {
			}
		}

		return defaultValue;
	}

	public static Date get(String value, DateFormat df, Date defaultValue) {
		try {
			Date date = df.parse(value.trim());

			if (date != null) {
				return date;
			}
		}
		catch (Exception e) {
		}

		return defaultValue;
	}

	public static double get(String value, double defaultValue) {
		try {
			return Double.parseDouble(_trim(value));
		}
		catch (Exception e) {
		}

		return defaultValue;
	}

	public static float get(String value, float defaultValue) {
		try {
			return Float.parseFloat(_trim(value));
		}
		catch (Exception e) {
		}

		return defaultValue;
	}

	public static int get(String value, int defaultValue) {
		try {
			return Integer.parseInt(_trim(value));
		}
		catch (Exception e) {
		}

		return defaultValue;
	}

	public static long get(String value, long defaultValue) {
		try {
			return Long.parseLong(_trim(value));
		}
		catch (Exception e) {
		}

		return defaultValue;
	}

	public static short get(String value, short defaultValue) {
		try {
			return Short.parseShort(_trim(value));
		}
		catch (Exception e) {
		}

		return defaultValue;
	}

	public static String get(String value, String defaultValue) {
		if (value != null) {
			value = value.trim();
			value = StringUtil.replace(value, "\r\n", "\n");

			return value;
		}

		return defaultValue;
	}

	private static String _trim(String value) {
		if (value != null) {
			value = value.trim();

			StringMaker sm = new StringMaker();

			char[] charArray = value.toCharArray();

			for (int i = 0; i < charArray.length; i++) {
				if ((Character.isDigit(charArray[i])) ||
					(charArray[i] == '-' && i == 0) ||
					(charArray[i] == '.')) {

					sm.append(charArray[i]);
				}
			}

			value = sm.toString();
		}

		return value;
	}

}