/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.common.taglib;

import com.liferay.util.BrowserSniffer;
import com.liferay.util.LocaleUtil;
import com.liferay.util.PwdGenerator;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Locale;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="InputDateTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class InputDateTag extends TagSupport {

	public int doEndTag() throws JspTagException {
		try {
			FastStringBuffer sb = new FastStringBuffer();

			String namespace =
				PwdGenerator.getPassword(PwdGenerator.KEY3, 4) +
					StringPool.UNDERLINE;

			String jsCalendarObj = namespace + "jsCalendarObj";
			String jsOnClick = namespace + "jsOnClick";
			String jsOnClose = namespace + "jsOnClose";
			String jsOnSelect = namespace + "jsOnSelect";
			String imageInputId = namespace + "imageInputId";

			// JavaScript

			sb.append("<script language=\"JavaScript\">");

			sb.append("var ").append(jsCalendarObj).append(" = new Calendar(false, null, ").append(jsOnSelect).append(", ").append(jsOnClose).append(");");
			sb.append(jsCalendarObj).append(".weekNumbers = false;");
			sb.append(jsCalendarObj).append(".firstDayOfWeek = ").append(_firstDayOfWeek).append(";");
			sb.append(jsCalendarObj).append(".setTtDateFormat(\"%A, %B %e, %Y\");");
			sb.append(jsCalendarObj).append(".setRange(").append(_yearRangeStart).append(", ").append(_yearRangeEnd).append(");");

			sb.append("function ").append(jsOnClick).append("(id) {");
			sb.append(jsCalendarObj).append(".create();");

			sb.append("var monthValue = 0;");
			sb.append("var yearValue = 0;");

			if (Validator.isNull(_monthAndYearParam)) {
				sb.append("monthValue = document.").append(_formName).append(".").append(_monthParam).append(".value;");
				sb.append("yearValue = document.").append(_formName).append(".").append(_yearParam).append(".value;");
			}
			else {
				sb.append("var monthAndYearValue = document.").append(_formName).append(".").append(_monthAndYearParam).append(".value;");
				sb.append("var monthAndYearPos = monthAndYearValue.indexOf(\"_\");");

				sb.append("if (monthAndYearPos != -1) {");
				sb.append("monthValue = monthAndYearValue.substring(0, monthAndYearPos);");
				sb.append("yearValue = monthAndYearValue.substring(monthAndYearPos + 1, monthAndYearValue.length);");
				sb.append("}");
			}

			sb.append("var dayValue = document.").append(_formName).append(".").append(_dayParam).append(".value;");

			sb.append("if (monthValue == \"\") {");
			sb.append("monthValue = 0;");
			sb.append("}");

			sb.append("if (yearValue == \"\") {");
			sb.append("yearValue = ").append(_yearRangeStart).append(";");
			sb.append("}");

			sb.append("if (dayValue == \"\") {");
			sb.append("dayValue = 1;");
			sb.append("}");

			sb.append(jsCalendarObj).append(".setDate(new Date(yearValue, monthValue, dayValue));");
			sb.append(jsCalendarObj).append(".showAtElement(document.getElementById('").append(imageInputId).append("'), 'br');");
			sb.append("}");

			sb.append("function ").append(jsOnClose).append("(cal) {");
			sb.append("cal.hide();");
			sb.append("}");

			sb.append("function ").append(jsOnSelect).append("(cal) {");
			sb.append("if (cal.dateClicked) {");

			if (Validator.isNull(_monthAndYearParam)) {
				sb.append("setSelectedValue(document.").append(_formName).append(".").append(_monthParam).append(", cal.date.getMonth());");
				sb.append("setSelectedValue(document.").append(_formName).append(".").append(_yearParam).append(", cal.date.getFullYear());");
			}
			else {
				sb.append("setSelectedValue(document.").append(_formName).append(".").append(_monthAndYearParam).append(", cal.date.getMonth() + '_' + cal.date.getFullYear());");
			}

			sb.append("setSelectedValue(document.").append(_formName).append(".").append(_dayParam).append(", cal.date.getDate());");
			sb.append("cal.callCloseHandler();");
			sb.append("}");
			sb.append("}");

			sb.append("</script>");

			if (Validator.isNull(_monthAndYearParam)) {
				displayMonth(sb);
				displayDay(sb);
				displayYear(sb);
			}
			else {
				displayMonthAndYear(sb);
				displayDay(sb);
			}

			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			if (!BrowserSniffer.is_ns_4(req)) {
				sb.append("<img align=\"absmiddle\" border=\"0\" hspace=\"0\" id=\"").append(imageInputId).append("\" src=\"").append(_calendarImage).append("\" vspace=\"0\" onClick=\"").append(jsOnClick).append("('").append(jsCalendarObj).append("');\">");
			}

			pageContext.getOut().print(sb.toString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
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

	public void setLocale(String locale) {
		_locale = LocaleUtil.fromLanguageId(locale);
	}

	public void setCalendarImage(String calendarImage) {
		_calendarImage = calendarImage;
	}

	protected void displayMonth(FastStringBuffer sb) {
		int[] monthIds = CalendarUtil.getMonthIds();
		String[] months = CalendarUtil.getMonths(_locale);

		sb.append("<select name=\"").append(_monthParam).append("\">");

		if (_monthNullable) {
			sb.append("<option value=\"\"></option>");
		}

		for (int i = 0; i < months.length; i++) {
			sb.append("<option ");

			if (_monthValue == monthIds[i]) {
				sb.append("selected");
			}

			sb.append(" value=\"").append(monthIds[i]).append("\">");
			sb.append(months[i]);
			sb.append("</option>");
		}

		sb.append("</select> ");
	}

	protected void displayDay(FastStringBuffer sb) {
		sb.append("<select name=\"").append(_dayParam).append("\">");

		if (_dayNullable) {
			sb.append("<option value=\"\"></option>");
		}

		for (int i = 1; i <= 31; i++) {
			sb.append("<option ");

			if (_dayValue == i) {
				sb.append("selected");
			}

			sb.append(" value=\"").append(i).append("\">");
			sb.append(i);
			sb.append("</option>");
		}

		sb.append("</select> ");
	}

	protected void displayYear(FastStringBuffer sb) {
		sb.append("<select name=\"").append(_yearParam).append("\">");

		if (_yearNullable) {
			sb.append("<option value=\"\"></option>");
		}

		for (int i = _yearRangeStart; i <= _yearRangeEnd; i++) {
			sb.append("<option ");

			if (_yearValue == i) {
				sb.append("selected");
			}

			sb.append(" value=\"").append(i).append("\">");
			sb.append(i);
			sb.append("</option>");
		}

		sb.append("</select> ");
	}

	protected void displayMonthAndYear(FastStringBuffer sb) {
		int[] monthIds = CalendarUtil.getMonthIds();
		String[] months = CalendarUtil.getMonths(_locale, "MMM");

		sb.append("<select name=\"").append(_monthAndYearParam).append("\">");

		if (_monthAndYearNullable) {
			sb.append("<option value=\"\"></option>");
		}

		for (int i = _yearRangeStart; i <= _yearRangeEnd; i++) {
			for (int j = 0; j < months.length; j++) {
				sb.append("<option ");

				if ((_monthValue == monthIds[j]) && (_yearValue == i)) {
					sb.append("selected");
				}

				sb.append(" value=\"");
				sb.append(monthIds[j]);
				sb.append("_");
				sb.append(i);
				sb.append("\">");
				sb.append(months[j]);
				sb.append(" ");
				sb.append(i);
				sb.append("</option>");
			}
		}

		sb.append("</select> ");
	}

	private String _formName;
	private String _monthParam;
	private int _monthValue;
	private boolean _monthNullable;
	private String _dayParam;
	private int _dayValue;
	private boolean _dayNullable;
	private String _yearParam;
	private int _yearValue;
	private boolean _yearNullable;
	private int _yearRangeStart = (new GregorianCalendar()).get(Calendar.YEAR);
	private int _yearRangeEnd = _yearRangeStart + 10;
	private String _monthAndYearParam;
	private boolean _monthAndYearNullable;
	private int _firstDayOfWeek = Calendar.SUNDAY - 1;
	private Locale _locale = Locale.getDefault();
	private String _calendarImage;

}