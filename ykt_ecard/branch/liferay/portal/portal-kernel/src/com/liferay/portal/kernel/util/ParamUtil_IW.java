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
 * <a href="ParamUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ParamUtil_IW {
	public static ParamUtil_IW getInstance() {
		return _instance;
	}

	public boolean getBoolean(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getBoolean(req, param);
	}

	public boolean getBoolean(javax.servlet.ServletRequest req,
		java.lang.String param, boolean defaultValue) {
		return ParamUtil.getBoolean(req, param, defaultValue);
	}

	public boolean[] getBooleanValues(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getBooleanValues(req, param);
	}

	public boolean[] getBooleanValues(javax.servlet.ServletRequest req,
		java.lang.String param, boolean[] defaultValue) {
		return ParamUtil.getBooleanValues(req, param, defaultValue);
	}

	public java.util.Date getDate(javax.servlet.ServletRequest req,
		java.lang.String param, java.text.DateFormat df) {
		return ParamUtil.getDate(req, param, df);
	}

	public java.util.Date getDate(javax.servlet.ServletRequest req,
		java.lang.String param, java.text.DateFormat df,
		java.util.Date defaultValue) {
		return ParamUtil.getDate(req, param, df, defaultValue);
	}

	public double getDouble(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getDouble(req, param);
	}

	public double getDouble(javax.servlet.ServletRequest req,
		java.lang.String param, double defaultValue) {
		return ParamUtil.getDouble(req, param, defaultValue);
	}

	public double[] getDoubleValues(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getDoubleValues(req, param);
	}

	public double[] getDoubleValues(javax.servlet.ServletRequest req,
		java.lang.String param, double[] defaultValue) {
		return ParamUtil.getDoubleValues(req, param, defaultValue);
	}

	public float getFloat(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getFloat(req, param);
	}

	public float getFloat(javax.servlet.ServletRequest req,
		java.lang.String param, float defaultValue) {
		return ParamUtil.getFloat(req, param, defaultValue);
	}

	public float[] getFloatValues(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getFloatValues(req, param);
	}

	public float[] getFloatValues(javax.servlet.ServletRequest req,
		java.lang.String param, float[] defaultValue) {
		return ParamUtil.getFloatValues(req, param, defaultValue);
	}

	public int getInteger(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getInteger(req, param);
	}

	public int getInteger(javax.servlet.ServletRequest req,
		java.lang.String param, int defaultValue) {
		return ParamUtil.getInteger(req, param, defaultValue);
	}

	public int[] getIntegerValues(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getIntegerValues(req, param);
	}

	public int[] getIntegerValues(javax.servlet.ServletRequest req,
		java.lang.String param, int[] defaultValue) {
		return ParamUtil.getIntegerValues(req, param, defaultValue);
	}

	public long getLong(javax.servlet.ServletRequest req, java.lang.String param) {
		return ParamUtil.getLong(req, param);
	}

	public long getLong(javax.servlet.ServletRequest req,
		java.lang.String param, long defaultValue) {
		return ParamUtil.getLong(req, param, defaultValue);
	}

	public long[] getLongValues(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getLongValues(req, param);
	}

	public long[] getLongValues(javax.servlet.ServletRequest req,
		java.lang.String param, long[] defaultValue) {
		return ParamUtil.getLongValues(req, param, defaultValue);
	}

	public short getShort(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getShort(req, param);
	}

	public short getShort(javax.servlet.ServletRequest req,
		java.lang.String param, short defaultValue) {
		return ParamUtil.getShort(req, param, defaultValue);
	}

	public short[] getShortValues(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getShortValues(req, param);
	}

	public short[] getShortValues(javax.servlet.ServletRequest req,
		java.lang.String param, short[] defaultValue) {
		return ParamUtil.getShortValues(req, param, defaultValue);
	}

	public java.lang.String getString(javax.servlet.ServletRequest req,
		java.lang.String param) {
		return ParamUtil.getString(req, param);
	}

	public java.lang.String getString(javax.servlet.ServletRequest req,
		java.lang.String param, java.lang.String defaultValue) {
		return ParamUtil.getString(req, param, defaultValue);
	}

	public boolean get(javax.servlet.ServletRequest req,
		java.lang.String param, boolean defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public java.util.Date get(javax.servlet.ServletRequest req,
		java.lang.String param, java.text.DateFormat df,
		java.util.Date defaultValue) {
		return ParamUtil.get(req, param, df, defaultValue);
	}

	public double get(javax.servlet.ServletRequest req, java.lang.String param,
		double defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public float get(javax.servlet.ServletRequest req, java.lang.String param,
		float defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public int get(javax.servlet.ServletRequest req, java.lang.String param,
		int defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public long get(javax.servlet.ServletRequest req, java.lang.String param,
		long defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public short get(javax.servlet.ServletRequest req, java.lang.String param,
		short defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public java.lang.String get(javax.servlet.ServletRequest req,
		java.lang.String param, java.lang.String defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public void print(javax.servlet.ServletRequest req) {
		ParamUtil.print(req);
	}

	public boolean getBoolean(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getBoolean(req, param);
	}

	public boolean getBoolean(javax.portlet.PortletRequest req,
		java.lang.String param, boolean defaultValue) {
		return ParamUtil.getBoolean(req, param, defaultValue);
	}

	public boolean[] getBooleanValues(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getBooleanValues(req, param);
	}

	public boolean[] getBooleanValues(javax.portlet.PortletRequest req,
		java.lang.String param, boolean[] defaultValue) {
		return ParamUtil.getBooleanValues(req, param, defaultValue);
	}

	public java.util.Date getDate(javax.portlet.PortletRequest req,
		java.lang.String param, java.text.DateFormat df) {
		return ParamUtil.getDate(req, param, df);
	}

	public java.util.Date getDate(javax.portlet.PortletRequest req,
		java.lang.String param, java.text.DateFormat df,
		java.util.Date defaultValue) {
		return ParamUtil.getDate(req, param, df, defaultValue);
	}

	public double getDouble(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getDouble(req, param);
	}

	public double getDouble(javax.portlet.PortletRequest req,
		java.lang.String param, double defaultValue) {
		return ParamUtil.getDouble(req, param, defaultValue);
	}

	public double[] getDoubleValues(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getDoubleValues(req, param);
	}

	public double[] getDoubleValues(javax.portlet.PortletRequest req,
		java.lang.String param, double[] defaultValue) {
		return ParamUtil.getDoubleValues(req, param, defaultValue);
	}

	public float getFloat(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getFloat(req, param);
	}

	public float getFloat(javax.portlet.PortletRequest req,
		java.lang.String param, float defaultValue) {
		return ParamUtil.getFloat(req, param, defaultValue);
	}

	public float[] getFloatValues(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getFloatValues(req, param);
	}

	public float[] getFloatValues(javax.portlet.PortletRequest req,
		java.lang.String param, float[] defaultValue) {
		return ParamUtil.getFloatValues(req, param, defaultValue);
	}

	public int getInteger(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getInteger(req, param);
	}

	public int getInteger(javax.portlet.PortletRequest req,
		java.lang.String param, int defaultValue) {
		return ParamUtil.getInteger(req, param, defaultValue);
	}

	public int[] getIntegerValues(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getIntegerValues(req, param);
	}

	public int[] getIntegerValues(javax.portlet.PortletRequest req,
		java.lang.String param, int[] defaultValue) {
		return ParamUtil.getIntegerValues(req, param, defaultValue);
	}

	public long getLong(javax.portlet.PortletRequest req, java.lang.String param) {
		return ParamUtil.getLong(req, param);
	}

	public long getLong(javax.portlet.PortletRequest req,
		java.lang.String param, long defaultValue) {
		return ParamUtil.getLong(req, param, defaultValue);
	}

	public long[] getLongValues(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getLongValues(req, param);
	}

	public long[] getLongValues(javax.portlet.PortletRequest req,
		java.lang.String param, long[] defaultValue) {
		return ParamUtil.getLongValues(req, param, defaultValue);
	}

	public short getShort(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getShort(req, param);
	}

	public short getShort(javax.portlet.PortletRequest req,
		java.lang.String param, short defaultValue) {
		return ParamUtil.getShort(req, param, defaultValue);
	}

	public short[] getShortValues(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getShortValues(req, param);
	}

	public short[] getShortValues(javax.portlet.PortletRequest req,
		java.lang.String param, short[] defaultValue) {
		return ParamUtil.getShortValues(req, param, defaultValue);
	}

	public java.lang.String getString(javax.portlet.PortletRequest req,
		java.lang.String param) {
		return ParamUtil.getString(req, param);
	}

	public java.lang.String getString(javax.portlet.PortletRequest req,
		java.lang.String param, java.lang.String defaultValue) {
		return ParamUtil.getString(req, param, defaultValue);
	}

	public boolean get(javax.portlet.PortletRequest req,
		java.lang.String param, boolean defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public java.util.Date get(javax.portlet.PortletRequest req,
		java.lang.String param, java.text.DateFormat df,
		java.util.Date defaultValue) {
		return ParamUtil.get(req, param, df, defaultValue);
	}

	public double get(javax.portlet.PortletRequest req, java.lang.String param,
		double defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public float get(javax.portlet.PortletRequest req, java.lang.String param,
		float defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public int get(javax.portlet.PortletRequest req, java.lang.String param,
		int defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public long get(javax.portlet.PortletRequest req, java.lang.String param,
		long defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public short get(javax.portlet.PortletRequest req, java.lang.String param,
		short defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public java.lang.String get(javax.portlet.PortletRequest req,
		java.lang.String param, java.lang.String defaultValue) {
		return ParamUtil.get(req, param, defaultValue);
	}

	public void print(javax.portlet.PortletRequest req) {
		ParamUtil.print(req);
	}

	private ParamUtil_IW() {
	}

	private static ParamUtil_IW _instance = new ParamUtil_IW();
}