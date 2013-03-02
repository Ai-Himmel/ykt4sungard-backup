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

package com.liferay.util.dao.hibernate;

import com.liferay.util.GetterUtil;
import com.liferay.util.SystemProperties;

import com.opensymphony.oscache.base.CacheEntry;

import java.util.Properties;

import org.hibernate.cache.Cache;
import org.hibernate.cache.CacheException;
import org.hibernate.cache.CacheProvider;
import org.hibernate.cache.Timestamper;
import org.hibernate.util.StringHelper;

/**
 * <a href="OSCacheProvider.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Mathias Bogaert
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class OSCacheProvider implements CacheProvider {

	public static final String OSCACHE_REFRESH_PERIOD = "refresh.period";

	public static final String OSCACHE_CRON = "cron";

	public Cache buildCache(String region, Properties properties)
		throws CacheException {

		int refreshPeriod = GetterUtil.get(
			SystemProperties.get(
				StringHelper.qualify(region, OSCACHE_REFRESH_PERIOD)),
			CacheEntry.INDEFINITE_EXPIRY);

		String cron = SystemProperties.get(
			StringHelper.qualify(region, OSCACHE_CRON));

		return new OSCache(refreshPeriod, cron, region);
	}

	public boolean isMinimalPutsEnabledByDefault() {
		return false;
	}

	public long nextTimestamp() {
		return Timestamper.next();
	}

	public void start(Properties properties) throws CacheException {
	}

	public void stop() {
	}

}