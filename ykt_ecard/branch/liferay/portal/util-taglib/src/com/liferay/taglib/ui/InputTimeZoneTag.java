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

package com.liferay.taglib.ui;

import com.liferay.portal.kernel.util.TimeZoneUtil;
import com.liferay.taglib.util.IncludeTag;

import java.util.TimeZone;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="InputTimeZoneTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputTimeZoneTag extends IncludeTag {

	public int doStartTag() throws JspException {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:input-time-zone:name", _name);
		req.setAttribute("liferay-ui:input-time-zone:value", _value);
		req.setAttribute(
			"liferay-ui:input-time-zone:nullable", String.valueOf(_nullable));
		req.setAttribute(
			"liferay-ui:input-time-zone:daylight", String.valueOf(_daylight));
		req.setAttribute(
			"liferay-ui:input-time-zone:displayStyle",
			String.valueOf(_displayStyle));
		req.setAttribute(
			"liferay-ui:input-time-zone:disabled", String.valueOf(_disabled));

		return EVAL_BODY_BUFFERED;
	}

	public void setName(String name) {
		_name = name;
	}

	public void setValue(String value) {
		_value = value;
	}

	public void setNullable(boolean nullable) {
		_nullable = nullable;
	}

	public void setDaylight(boolean daylight) {
		_daylight = daylight;
	}

	public void setDisplayStyle(int displayStyle) {
		_displayStyle = displayStyle;
	}

	public void setDisabled(boolean disabled) {
		_disabled = disabled;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE =
		"/html/taglib/ui/input_time_zone/page.jsp";

	private String _name;
	private String _value = TimeZoneUtil.getDefault().getID();
	private boolean _nullable;
	private boolean _daylight;
	private int _displayStyle = TimeZone.LONG;
	private boolean _disabled;

}