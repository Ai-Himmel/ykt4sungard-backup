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

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.LocaleUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Time;
import com.liferay.util.lang.FastStringBuffer;

import java.text.NumberFormat;

import java.util.Locale;
import java.util.TimeZone;

import javax.servlet.jsp.JspTagException;
import javax.servlet.jsp.tagext.TagSupport;

/**
 * <a href="InputTimeZoneTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class InputTimeZoneTag extends TagSupport {

	public int doEndTag() throws JspTagException {
		try {
			FastStringBuffer sb = new FastStringBuffer();

			NumberFormat nf = NumberFormat.getInstance();
			nf.setMinimumIntegerDigits(2);

			String[] timeZones = PropsUtil.getArray(PropsUtil.TIME_ZONES);

			sb.append("<select name=\"").append(_name).append("\">");

			if (_nullable) {
				sb.append("<option value=\"\"></option>");
			}

			for (int i = 0; i < timeZones.length; i++) {
				TimeZone tz = TimeZone.getTimeZone(timeZones[i]);

				int rawOffset = tz.getRawOffset();

				String offset = StringPool.BLANK;

				if (rawOffset > 0) {
					offset = "+";
				}

				if (rawOffset != 0) {
					String offsetHour = nf.format(rawOffset / Time.HOUR);
					String offsetMinute = nf.format(
						Math.abs(rawOffset % Time.HOUR) / Time.MINUTE);

					offset += offsetHour + ":" + offsetMinute;
				}

				sb.append("<option ");

				if (_value.equals(tz.getID())) {
					sb.append("selected");
				}

				sb.append(" value=\"").append(tz.getID()).append("\">");
				sb.append("(GMT ").append(offset).append(") &nbsp;").append(
					tz.getDisplayName(_daylight, _style, _locale));
				sb.append("</option>");
			}

			sb.append("</select>");

			pageContext.getOut().print(sb.toString());

			return EVAL_PAGE;
		}
		catch (Exception e) {
			throw new JspTagException(e.getMessage());
		}
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

	public void setStyle(int style) {
		_style = style;
	}

	public void setLocale(String locale) {
		_locale = LocaleUtil.fromLanguageId(locale);
	}

	private String _name;
	private String _value = TimeZone.getDefault().getID();
	private boolean _nullable;
	private boolean _daylight;
	private int _style = TimeZone.SHORT;
	private Locale _locale = Locale.getDefault();

}