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
import com.liferay.portal.kernel.webcache.WebCacheItem;
import com.liferay.portal.kernel.webcache.WebCachePoolUtil;

import java.util.List;

/**
 * <a href="CSZUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CSZUtil {

	public static List getCSZAddressByCityAndState(String cityAndState) {
		WebCacheItem wci = new CityStateWebCacheItem(cityAndState);

		return (List)WebCachePoolUtil.get(
			CSZUtil.class.getName() + ".cs." + cityAndState, wci);
	}

	public static List getCSZAddressByZip(String zip) {
		WebCacheItem wci = new ZipWebCacheItem(zip);

		return (List)WebCachePoolUtil.get(
			CSZUtil.class.getName() + ".zip." + zip, wci);
	}

	public static List getCSZAddressByZip4(String street, String cityAndState) {
		WebCacheItem wci = new Zip4WebCacheItem(street, cityAndState);

		return (List)WebCachePoolUtil.get(
			CSZUtil.class.getName() + ".zip4." + street + StringPool.PERIOD +
				cityAndState,
			wci);
	}

}