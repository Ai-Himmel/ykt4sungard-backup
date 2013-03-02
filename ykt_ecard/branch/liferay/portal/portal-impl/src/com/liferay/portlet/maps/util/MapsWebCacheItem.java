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

package com.liferay.portlet.maps.util;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.webcache.WebCacheException;
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portlet.maps.model.MapsAddress;
import com.liferay.util.Http;
import com.liferay.util.HttpUtil;
import com.liferay.util.Time;

/**
 * <a href="MapsWebCacheItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MapsWebCacheItem implements WebCacheItem {

	public MapsWebCacheItem(String street, String csz) {
		_street = street;
		_csz = csz;
	}

	public Object convert(String key) throws WebCacheException {
		MapsAddress map = null;

		String street = "";
		String city = "";
		String state = "";
		String zip = "";

		try {
			street = _street;

			int pos = _csz.indexOf(StringPool.COMMA);

			if (pos != -1) {
				city = _csz.substring(0, pos).trim();

				state = _csz.substring(pos + 1, _csz.length()).trim();
			}
			else {
				zip = _csz;
			}
		}
		catch (Exception e) {
			return map;
		}

		try {
			StringMaker url = new StringMaker();

			url.append("http://www.mapquest.com/maps/map.adp?country=US");
			url.append("&address=");
			url.append(HttpUtil.encodeURL(street));
			url.append("&city=");
			url.append(HttpUtil.encodeURL(city));
			url.append("&state=");
			url.append(HttpUtil.encodeURL(state));
			url.append("&zipcode=");
			url.append(HttpUtil.encodeURL(zip));

			String text = Http.URLtoString(url.toString());

			int mapDirectPos = text.indexOf(
				"GetMapDataDirect=");

			if (mapDirectPos != -1) {
				mapDirectPos = mapDirectPos + 17;
			}
			else {
				return map;
			}

			String mapDirect = text.substring(
				mapDirectPos, text.indexOf("\"", mapDirectPos));

			mapDirect = HttpUtil.decodeURL(mapDirect);

			map = new MapsAddress(street, city, state, zip, mapDirect);
		}
		catch (Exception e) {
			throw new WebCacheException(e);
		}

		return map;
	}

	public long getRefreshTime() {
		return _REFRESH_TIME;
	}

	private static final long _REFRESH_TIME = Time.DAY * 90;

	private String _street;
	private String _csz;

}