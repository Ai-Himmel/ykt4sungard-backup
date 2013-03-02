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

package com.liferay.filters.header;

import com.liferay.portal.kernel.servlet.BaseFilter;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;

import java.io.IOException;

import java.text.DateFormat;
import java.text.SimpleDateFormat;

import java.util.Calendar;
import java.util.Enumeration;
import java.util.GregorianCalendar;
import java.util.Locale;
import java.util.TimeZone;

import javax.servlet.FilterChain;
import javax.servlet.FilterConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="HeaderFilter.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class HeaderFilter extends BaseFilter {

	public void init(FilterConfig config) throws ServletException {
		super.init(config);

		_config = config;
		_timeZone = TimeZone.getTimeZone(_TIME_ZONE);
	}

	public void doFilter(
			ServletRequest req, ServletResponse res, FilterChain chain)
		throws IOException, ServletException {

		HttpServletResponse httpRes = (HttpServletResponse)res;

		Enumeration enu = _config.getInitParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			String value = _config.getInitParameter(name);

			if (name.equals(_EXPIRES) && Validator.isNumber(value)) {
				int seconds = GetterUtil.getInteger(value);

				Calendar cal = new GregorianCalendar();

				cal.add(Calendar.SECOND, seconds);

				DateFormat dateFormat = new SimpleDateFormat(
					_DATE_FORMAT, Locale.US);

				dateFormat.setTimeZone(_timeZone);

				value = dateFormat.format(cal.getTime());
			}

			httpRes.addHeader(name, value);
		}

		doFilter(HeaderFilter.class, req, res, chain);
	}

	private static final String _DATE_FORMAT = "EEE, dd MMM yyyy HH:mm:ss z";

	private static final String _EXPIRES = "Expires";

	private static final String _TIME_ZONE = "GMT";

	private FilterConfig _config;
	private TimeZone _timeZone;

}