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

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.taglib.util.IncludeTag;

import java.util.Calendar;

import javax.servlet.ServletRequest;
import javax.servlet.jsp.JspException;

/**
 * <a href="InputDateTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class InputDateTag extends IncludeTag {

	public int doStartTag() throws JspException {
		ServletRequest req = pageContext.getRequest();

		req.setAttribute(
			"liferay-ui:input-date:disableNamespace",
			String.valueOf(_disableNamespace));
		req.setAttribute("liferay-ui:input-date:formName", _formName);
		req.setAttribute("liferay-ui:input-date:monthParam", _monthParam);
		req.setAttribute(
			"liferay-ui:input-date:monthValue", String.valueOf(_monthValue));
		req.setAttribute(
			"liferay-ui:input-date:monthNullable",
			String.valueOf(_monthNullable));
		req.setAttribute("liferay-ui:input-date:dayParam", _dayParam);
		req.setAttribute(
			"liferay-ui:input-date:dayValue", String.valueOf(_dayValue));
		req.setAttribute(
			"liferay-ui:input-date:dayNullable", String.valueOf(_dayNullable));
		req.setAttribute("liferay-ui:input-date:yearParam", _yearParam);
		req.setAttribute(
			"liferay-ui:input-date:yearValue", String.valueOf(_yearValue));
		req.setAttribute(
			"liferay-ui:input-date:yearNullable",
			String.valueOf(_yearNullable));
		req.setAttribute(
			"liferay-ui:input-date:yearRangeStart",
			String.valueOf(_yearRangeStart));
		req.setAttribute(
			"liferay-ui:input-date:yearRangeEnd",
			String.valueOf(_yearRangeEnd));
		req.setAttribute(
			"liferay-ui:input-date:monthAndYearParam", _monthAndYearParam);
		req.setAttribute(
			"liferay-ui:input-date:monthAndYearNullable",
			String.valueOf(_monthAndYearNullable));
		req.setAttribute(
			"liferay-ui:input-date:firstDayOfWeek",
			String.valueOf(_firstDayOfWeek));
		req.setAttribute("liferay-ui:input-date:imageInputId", _imageInputId);
		req.setAttribute(
			"liferay-ui:input-date:disabled", String.valueOf(_disabled));

		return EVAL_BODY_BUFFERED;
	}

	public void setDisableNamespace(boolean disableNamespace) {
		_disableNamespace = disableNamespace;
	}

	public void setFormName(String formName) {
		_formName = formName;
	}

	public void setMonthParam(String monthParam) {
		_monthParam = monthParam;
	}

	public void setMonthValue(int monthValue) {
		_monthValue = monthValue;
	}

	public void setMonthNullable(boolean monthNullable) {
		_monthNullable = monthNullable;
	}

	public void setDayParam(String dayParam) {
		_dayParam = dayParam;
	}

	public void setDayValue(int dayValue) {
		_dayValue = dayValue;
	}

	public void setDayNullable(boolean dayNullable) {
		_dayNullable = dayNullable;
	}

	public void setYearParam(String yearParam) {
		_yearParam = yearParam;
	}

	public void setYearValue(int yearValue) {
		_yearValue = yearValue;
	}

	public void setYearNullable(boolean yearNullable) {
		_yearNullable = yearNullable;
	}

	public void setYearRangeStart(int yearRangeStart) {
		_yearRangeStart = yearRangeStart;
	}

	public void setYearRangeEnd(int yearRangeEnd) {
		_yearRangeEnd = yearRangeEnd;
	}

	public void setMonthAndYearParam(String monthAndYearParam) {
		_monthAndYearParam = monthAndYearParam;
	}

	public void setMonthAndYearNullable(boolean monthAndYearNullable) {
		_monthAndYearNullable = monthAndYearNullable;
	}

	public void setFirstDayOfWeek(int firstDayOfWeek) {
		_firstDayOfWeek = firstDayOfWeek;
	}

	public void setImageInputId(String imageInputId) {
		_imageInputId = imageInputId;
	}

	public void setDisabled(boolean disabled) {
		_disabled = disabled;
	}

	protected String getDefaultPage() {
		return _PAGE;
	}

	private static final String _PAGE = "/html/taglib/ui/input_date/page.jsp";

	private boolean _disableNamespace;
	private String _formName = "fm";
	private String _monthParam;
	private int _monthValue = -1;
	private boolean _monthNullable;
	private String _dayParam;
	private int _dayValue;
	private boolean _dayNullable;
	private String _yearParam;
	private int _yearValue;
	private boolean _yearNullable;
	private int _yearRangeStart;
	private int _yearRangeEnd;
	private String _monthAndYearParam = StringPool.BLANK;
	private boolean _monthAndYearNullable;
	private int _firstDayOfWeek = Calendar.SUNDAY - 1;
	private String _imageInputId;
	private boolean _disabled;

}