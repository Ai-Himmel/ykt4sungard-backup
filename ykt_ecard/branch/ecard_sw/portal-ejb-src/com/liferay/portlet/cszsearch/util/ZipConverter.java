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

package com.liferay.portlet.cszsearch.util;

import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.cszsearch.model.CSZAddress;
import com.liferay.util.ConverterException;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.TextFormatter;
import com.liferay.util.Time;

import java.io.BufferedReader;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="ZipConverter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class ZipConverter implements WebCacheable {

	public ZipConverter(String zip) {
		_zip = zip;
	}

	public Object convert(String id) throws ConverterException {
		List list = new ArrayList();

		String city = null;
		String state = null;
		String zip = _zip;

		try {
			String text = Http.URLtoString(
				"http://zip4.usps.com/zip4/zip_responseA.jsp?zipcode=" + zip);

			int x = text.indexOf("<tr valign=\"top\" bgcolor=\"ffffff\">");
			int y = text.lastIndexOf("</tbody>");

			BufferedReader br = new BufferedReader(
				new StringReader(Html.stripHtml(text.substring(x, y))));

			String line = null;
			int count = 0;

			while ((line = br.readLine()) != null) {
				if (!line.trim().equals("")) {
					count++;

					if (count == 1 || count % 4 == 1) {
						city = line;
					}
					else if (count == 2 || count % 4 == 2) {
						state = line;
					}

					if (city != null && state != null) {
						list.add(new CSZAddress(
							null, TextFormatter.formatName(city), state, zip));

						city = null;
						state = null;
					}
				}
			}

			br.close();
		}
		catch (Exception e) {
			throw new ConverterException(e);
		}

		return list;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY * 90;

	private String _zip;

}