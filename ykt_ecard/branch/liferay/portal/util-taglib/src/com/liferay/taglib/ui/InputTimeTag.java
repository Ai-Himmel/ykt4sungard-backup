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

import com.liferay.taglib.util.IncludeTag;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="InputTimeTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputTimeTag extends IncludeTag {

	public int doStartTag() throws JspException {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute("liferay-ui:input-time:hourParam", _hourParam);
		req.setAttribute(
			"liferay-ui:input-time:hourValue", String.valueOf(_hourValue));
		req.setAttribute(
			"liferay-ui:input-time:hourNullable",
			String.valueOf(_hourNullable));
		req.setAttribute("liferay-ui:input-time:minuteParam", _minuteParam);
		req.setAttribute(
			"liferay-ui:input-time:minuteValue", String.valueOf(_minuteValue));
		req.setAttribute(
			"liferay-ui:input-time:minuteNullable",
			String.valueOf(_minuteNullable));
		req.setAttribute(
			"liferay-ui:input-time:minuteInterval",
			String.valueOf(_minuteInterval));
		req.setAttribute("liferay-ui:input-time:amPmParam", _amPmParam);
		req.setAttribute(
			"liferay-ui:input-time:amPmValue", String.valueOf(_amPmValue));
		req.setAttribute(
			"liferay-ui:input-time:amPmNullable",
			String.valueOf(_amPmNullable));
		req.setAttribute(
			"liferay-ui:input-time:disabled", String.valueOf(_disabled));

		return EVAL_BODY_BUFFERED;
	}

	public void setHourParam(String hourParam) {
		_hourParam = hourParam;
	}

	public void setHourValue(int hourValue) {
		_hourValue = hourValue;
	}

	public void setHourNullable(boolean hourNullable) {
		_hourNullable = hourNullable;
	}

	public void setMinuteParam(String minuteParam) {
		_minuteParam = minuteParam;
	}

	public void setMinuteValue(int minuteValue) {
		_minuteValue = minuteValue;
	}

	public void setMinuteNullable(boolean minuteNullable) {
		_minuteNullable = minuteNullable;
	}

	public void setMinuteInterval(int minuteInterval) {
		_minuteInterval = minuteInterval;
	}

	public void setAmPmParam(String amPmParam) {
		_amPmParam = amPmParam;
	}

	public void setAmPmValue(int amPmValue) {
		_amPmValue = amPmValue;
	}

	public void setAmPmNullable(boolean amPmNullable) {
		_amPmNullable = amPmNullable;
	}

	public void setDisabled(boolean disabled) {
		_disabled = disabled;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/input_time/page.jsp";

	private String _hourParam;
	private int _hourValue;
	private boolean _hourNullable;
	private String _minuteParam;
	private int _minuteValue;
	private boolean _minuteNullable;
	private int _minuteInterval;
	private String _amPmParam;
	private int _amPmValue;
	private boolean _amPmNullable;
	private boolean _disabled;

}