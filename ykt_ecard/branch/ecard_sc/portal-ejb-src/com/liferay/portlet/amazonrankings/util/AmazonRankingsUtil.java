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

package com.liferay.portlet.amazonrankings.util;

import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebCachePool;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.amazonrankings.model.AmazonRankings;
import com.liferay.util.StringPool;

import java.util.List;
import java.util.Vector;

/**
 * <a href="AmazonRankingsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class AmazonRankingsUtil {

	public static String getAmazonKey() {
		return _instance._getAmazonKey();
	}

	public static AmazonRankings getAmazonRankings(String isbn) {
		WebCacheable wc = new AmazonRankingsConverter(isbn);

		return (AmazonRankings)WebCachePool.get(
			AmazonRankingsUtil.class.getName() + StringPool.PERIOD + isbn, wc);
	}

	private AmazonRankingsUtil() {
		_amazonLicenseKeys = new Vector();

		for (int i = 0; i < 1000; i++) {
			String key = PropsUtil.get(PropsUtil.AMAZON_LICENSE + i);

			if (key == null) {
				break;
			}
			else {
				_amazonLicenseKeys.add(key);
			}
		}
	}

	private String _getAmazonKey() {
		if (_amazonLicenseKeys.size() > 0) {
			_amazonLicenseCount++;

			if (_amazonLicenseCount >= _amazonLicenseKeys.size()) {
				_amazonLicenseCount = 0;
			}

			return (String)_amazonLicenseKeys.get(_amazonLicenseCount);
		}
		else {
			return null;
		}
	}

	private static AmazonRankingsUtil _instance = new AmazonRankingsUtil();

	private List _amazonLicenseKeys;
	private int _amazonLicenseCount;

}