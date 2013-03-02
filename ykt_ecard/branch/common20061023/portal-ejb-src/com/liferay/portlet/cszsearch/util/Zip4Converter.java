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
import com.liferay.util.Http;
import com.liferay.util.StringPool;
import com.liferay.util.Time;

import java.io.IOException;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="Zip4Converter.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class Zip4Converter implements WebCacheable {

	public Zip4Converter(String street, String cityAndState) {
		_street = street;
		_cityAndState = cityAndState;
	}

	public Object convert(String id) throws ConverterException {
		List list = new ArrayList();

		String street = _street;
		String city = "";
		String state = "";
		String zip = "";

		try {
			String csz = _cityAndState;

			int pos = csz.indexOf(StringPool.COMMA);

			if (pos != -1) {
				city = csz.substring(0, pos).trim();
				state = csz.substring(pos + 1, csz.length()).trim();
			}
			else {
				zip = csz;
			}
		}
		catch (Exception e) {
			return list;
		}

		try {
			String text = Http.URLtoString(
				"http://zip4.usps.com/zip4/zip4_responseA.jsp?" +
				"urbanization=&firm=" +
				"&address=" + Http.encodeURL(street) +
				"&address1=" + Http.encodeURL(street) +
				"&address2=&city=" + Http.encodeURL(city) +
				"&state=" + state +
				"&zipcode=" + zip);

			int y = text.indexOf("<span class=\"utilitybar\">");
			y = text.lastIndexOf("<br>", y) - 1;

			int x = text.lastIndexOf("class=\"mainText\">", y);
			x = text.indexOf(">", x) + 1;

			text = text.substring(x, y);

			x = text.indexOf("<br>");
			y = text.indexOf("&nbsp;");

			street = text.substring(0, x - 1);
			city = text.substring(x + 4, y);

			x = y + 6;
			y = text.indexOf("&nbsp;", x);

			state = text.substring(x, y);
			zip = text.substring(y + 6, text.length());

			list.add(new CSZAddress(street, city, state, zip));
		}
		catch (IOException ioe) {
			throw new ConverterException(ioe);
		}
		catch (Exception e) {
		}

		return list;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY * 90;

	private String _street;
	private String _cityAndState;

}