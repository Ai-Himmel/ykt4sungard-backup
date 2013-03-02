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

package com.liferay.portlet.cszsearch.util;

import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.cszsearch.model.CSZAddress;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Time;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="Zip4WebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Zip4WebCacheItem implements WebCacheItem {

	public Zip4WebCacheItem(String street, String cityAndState) {
		_street = street;
		_cityAndState = cityAndState;
	}

	public Object convert(String key) throws WebCacheException {
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
				"http://zip4.usps.com/zip4/zcl_0_results.jsp?visited=1&" +
					"pagenumber=all&firmname=&urbanization=&address1=&" +
						"address2=" + HttpUtil.encodeURL(street) + "&city=" +
							HttpUtil.encodeURL(city) + "&state=" + state +
								"&zip5=" + zip);

			if (text.indexOf("headers=\"full\"") > -1) {
				int x = text.indexOf("<td headers=\"full\"");
				x = text.indexOf(">", x) + 1;

				int y = text.indexOf("<br />", x);

				street = text.substring(x, y).trim();

				x = y + 6;

				y = text.indexOf("&nbsp;", x);

				city = text.substring(x, y).trim();

				x = y + 6;

				y = text.indexOf("&nbsp;", x);

				state = text.substring(x, y).trim();

				x = y + 12;

				y = text.indexOf("<br />", x);

				zip = text.substring(x, y).trim();

				list.add(new CSZAddress(street, city, state, zip));
			}
			else if (text.indexOf("headers=\"units\"") > -1) {
				int x = text.indexOf("<!-- **");
				int y = text.lastIndexOf("<!-- **");

				BufferedReader br = new BufferedReader(
					new StringReader(text.substring(x, y)));

				String line = null;

				while ((line = br.readLine()) != null) {
					if (line.indexOf("headers=\"zip\"") > -1) {
						zip = br.readLine().trim();

						list.add(new CSZAddress(street, city, state, zip));
					}
				}

				br.close();
			}
		}
		catch (IOException ioe) {
			throw new WebCacheException(ioe);
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