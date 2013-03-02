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

package com.liferay.portlet.stocks.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.spring.PortletPreferencesServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.WebCachePool;
import com.liferay.portal.util.WebCacheable;
import com.liferay.portlet.stocks.model.Stocks;
import com.liferay.util.StringPool;

import javax.portlet.PortletPreferences;

import javax.servlet.http.HttpServletRequest;

/**
 * <a href="StocksUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 *
 */
public class StocksUtil {

	public static PortletPreferences getPreferences(HttpServletRequest req)
		throws PortalException, SystemException {

		PortletPreferences prefs = PortletPreferencesServiceUtil.getPreferences(
			PortalUtil.getCompanyId(req),
			PortalUtil.getPortletPreferencesPK(req, PortletKeys.STOCKS));

		return prefs;
	}

	public static Stocks getStocks(String symbol) {
		WebCacheable wc = new StocksConverter(symbol);

		return (Stocks)WebCachePool.get(
			StocksUtil.class.getName() + StringPool.PERIOD + symbol, wc);
	}

}