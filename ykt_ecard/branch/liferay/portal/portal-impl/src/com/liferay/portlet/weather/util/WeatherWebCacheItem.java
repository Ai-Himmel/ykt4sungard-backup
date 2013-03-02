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

package com.liferay.portlet.weather.util;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.weather.model.Weather;
import com.liferay.util.Html;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Time;

/**
 * <a href="WeatherWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WeatherWebCacheItem implements WebCacheItem {

	public WeatherWebCacheItem(String zip) {
		_zip = zip;
	}

	public Object convert(String key) throws WebCacheException {
		Weather weather = null;

		try {
			String text = Html.stripComments(Http.URLtoString(
				"http://weather.yahoo.com/search/weather2?p=" +
					HttpUtil.encodeURL(_zip)));

			int x = text.indexOf("forecast-temperature");

			x = text.indexOf("h3>", x) + 3;

			int y = text.indexOf("&deg;", x);

			float temperature = GetterUtil.getFloat(text.substring(x, y));

			x = text.indexOf("background:url(", x);
			x = text.indexOf("http://", x);

			y = text.indexOf(".png", x) - 1;

			String iconURL = text.substring(x, y) + "s.png";

			weather = new Weather(_zip, iconURL, temperature);
		}
		catch (Exception e) {
			throw new WebCacheException(_zip);
		}

		return weather;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.MINUTE * 20;

	private String _zip;

}