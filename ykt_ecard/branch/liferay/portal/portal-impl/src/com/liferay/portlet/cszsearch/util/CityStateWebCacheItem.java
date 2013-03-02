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
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.cszsearch.model.CSZAddress;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Time;

import java.io.BufferedReader;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="CityStateWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CityStateWebCacheItem implements WebCacheItem {

	public CityStateWebCacheItem(String cityAndState) {
		_cityAndState = cityAndState;
	}

	public Object convert(String key) throws WebCacheException {
		List list = new ArrayList();

		String cityAndState = _cityAndState;
		String city = null;
		String state = null;

		try {
			int pos = cityAndState.indexOf(StringPool.COMMA);

			city = cityAndState.substring(0, pos);
			state = cityAndState.substring(
				pos + 1, cityAndState.length()).trim();
		}
		catch (Exception e) {
			return list;
		}

		try {
			String text = Http.URLtoString(
				"http://zip4.usps.com/zip4/zcl_1_results.jsp?pagenumber=all" +
					"&city=" + HttpUtil.encodeURL(city) + "&state=" +
						HttpUtil.encodeURL(state));

			int x = text.indexOf("<!-- **");
			int y = text.lastIndexOf("<!-- **");

			BufferedReader br = new BufferedReader(
				new StringReader(Html.stripHtml(text.substring(x, y))));

			String line = null;

			while ((line = br.readLine()) != null) {
				line = line.trim();

				if (!line.equals("")) {

					if (Validator.isNumber(line)) {
						list.add(new CSZAddress(null, city, state, line));
					}
				}
			}

			br.close();
		}
		catch (Exception e) {
			throw new WebCacheException(e);
		}

		return list;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY * 90;

	private String _cityAndState;

}