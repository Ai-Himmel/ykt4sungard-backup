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

import com.liferay.util.lang.FastStringBuffer;

import java.text.NumberFormat;

import java.util.Calendar;

import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="InputTimeTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class InputTimeTag extends TagSupport {

	public int doEndTag() throws JspTagException {
		try {
			FastStringBuffer sb = new FastStringBuffer();

			// Hour

			sb.append("<select name=\"").append(_hourParam).append("\">");

			if (_hourNullable) {
				sb.append("<option value=\"\"></option>");
			}

			for (int i = 0; i < 12; i++) {
				sb.append("<option ");

				if (_hourValue == i) {
					sb.append("selected");
				}

				sb.append(" value=\"").append(i).append("\">");

				if (i == 0) {
					sb.append(12);
				}
				else {
					sb.append(i);
				}

				sb.append("</option>");
			}

			sb.append("</select> ");

			// Minute

			NumberFormat nf = NumberFormat.getInstance();
			nf.setMinimumIntegerDigits(2);

			sb.append("<select name=\"").append(_minuteParam).append("\">");

			if (_minuteNullable) {
				sb.append("<option value=\"\"></option>");
			}

			for (int i = 0; i < 60; i++) {
				String minute = nf.format(i);

				if ((_minuteInterval == 0) || ((i % _minuteInterval) == 0)) {
					sb.append("<option ");

					if (_minuteValue == i) {
						sb.append("selected");
					}

					sb.append(" value=\"").append(i).append("\">");
					sb.append(":").append(minute);
					sb.append("</option>");
				}
			}

			sb.append("</select> ");

			// AM/PM

			sb.append("<select name=\"").append(_amPmParam).append("\">");

			if (_amPmNullable) {
				sb.append("<option value=\"\"></option>");
			}

			// AM

			sb.append("<option ");

			if (_amPmValue == Calendar.AM) {
				sb.append("selected");
			}

			sb.append(" value=\"").append(Calendar.AM).append("\">");
			sb.append("AM");
			sb.append("</option>");

			// PM

			sb.append("<option ");

			if (_amPmValue == Calendar.PM) {
				sb.append("selected");
			}

			sb.append(" value=\"").append(Calendar.PM).append("\">");
			sb.append("PM");
			sb.append("</option>");

			sb.append("</select>");

			pageContext.getOut().print(sb.toString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
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

}