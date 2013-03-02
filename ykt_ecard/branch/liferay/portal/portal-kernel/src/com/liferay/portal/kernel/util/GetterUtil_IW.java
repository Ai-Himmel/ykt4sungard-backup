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

/**
 * <a href="GetterUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GetterUtil_IW {
	public static GetterUtil_IW getInstance() {
		return _instance;
	}

	public boolean getBoolean(java.lang.String value) {
		return GetterUtil.getBoolean(value);
	}

	public boolean getBoolean(java.lang.String value, boolean defaultValue) {
		return GetterUtil.getBoolean(value, defaultValue);
	}

	public boolean[] getBooleanValues(java.lang.String[] values) {
		return GetterUtil.getBooleanValues(values);
	}

	public boolean[] getBooleanValues(java.lang.String[] values,
		boolean[] defaultValue) {
		return GetterUtil.getBooleanValues(values, defaultValue);
	}

	public java.util.Date getDate(java.lang.String value,
		java.text.DateFormat df) {
		return GetterUtil.getDate(value, df);
	}

	public java.util.Date getDate(java.lang.String value,
		java.text.DateFormat df, java.util.Date defaultValue) {
		return GetterUtil.getDate(value, df, defaultValue);
	}

	public double getDouble(java.lang.String value) {
		return GetterUtil.getDouble(value);
	}

	public double getDouble(java.lang.String value, double defaultValue) {
		return GetterUtil.getDouble(value, defaultValue);
	}

	public double[] getDoubleValues(java.lang.String[] values) {
		return GetterUtil.getDoubleValues(values);
	}

	public double[] getDoubleValues(java.lang.String[] values,
		double[] defaultValue) {
		return GetterUtil.getDoubleValues(values, defaultValue);
	}

	public float getFloat(java.lang.String value) {
		return GetterUtil.getFloat(value);
	}

	public float getFloat(java.lang.String value, float defaultValue) {
		return GetterUtil.getFloat(value, defaultValue);
	}

	public float[] getFloatValues(java.lang.String[] values) {
		return GetterUtil.getFloatValues(values);
	}

	public float[] getFloatValues(java.lang.String[] values,
		float[] defaultValue) {
		return GetterUtil.getFloatValues(values, defaultValue);
	}

	public int getInteger(java.lang.String value) {
		return GetterUtil.getInteger(value);
	}

	public int getInteger(java.lang.String value, int defaultValue) {
		return GetterUtil.getInteger(value, defaultValue);
	}

	public int[] getIntegerValues(java.lang.String[] values) {
		return GetterUtil.getIntegerValues(values);
	}

	public int[] getIntegerValues(java.lang.String[] values, int[] defaultValue) {
		return GetterUtil.getIntegerValues(values, defaultValue);
	}

	public long getLong(java.lang.String value) {
		return GetterUtil.getLong(value);
	}

	public long getLong(java.lang.String value, long defaultValue) {
		return GetterUtil.getLong(value, defaultValue);
	}

	public long[] getLongValues(java.lang.String[] values) {
		return GetterUtil.getLongValues(values);
	}

	public long[] getLongValues(java.lang.String[] values, long[] defaultValue) {
		return GetterUtil.getLongValues(values, defaultValue);
	}

	public short getShort(java.lang.String value) {
		return GetterUtil.getShort(value);
	}

	public short getShort(java.lang.String value, short defaultValue) {
		return GetterUtil.getShort(value, defaultValue);
	}

	public short[] getShortValues(java.lang.String[] values) {
		return GetterUtil.getShortValues(values);
	}

	public short[] getShortValues(java.lang.String[] values,
		short[] defaultValue) {
		return GetterUtil.getShortValues(values, defaultValue);
	}

	public java.lang.String getString(java.lang.String value) {
		return GetterUtil.getString(value);
	}

	public java.lang.String getString(java.lang.String value,
		java.lang.String defaultValue) {
		return GetterUtil.getString(value, defaultValue);
	}

	public boolean get(java.lang.String value, boolean defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	public java.util.Date get(java.lang.String value, java.text.DateFormat df,
		java.util.Date defaultValue) {
		return GetterUtil.get(value, df, defaultValue);
	}

	public double get(java.lang.String value, double defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	public float get(java.lang.String value, float defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	public int get(java.lang.String value, int defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	public long get(java.lang.String value, long defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	public short get(java.lang.String value, short defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	public java.lang.String get(java.lang.String value,
		java.lang.String defaultValue) {
		return GetterUtil.get(value, defaultValue);
	}

	private GetterUtil_IW() {
	}

	private static GetterUtil_IW _instance = new GetterUtil_IW();
}