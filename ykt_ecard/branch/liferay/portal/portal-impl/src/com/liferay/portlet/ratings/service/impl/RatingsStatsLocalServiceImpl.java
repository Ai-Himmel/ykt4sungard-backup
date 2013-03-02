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

package com.liferay.portlet.ratings.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.ratings.NoSuchStatsException;
import com.liferay.portlet.ratings.model.RatingsStats;
import com.liferay.portlet.ratings.service.base.RatingsStatsLocalServiceBaseImpl;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="RatingsStatsLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RatingsStatsLocalServiceImpl
	extends RatingsStatsLocalServiceBaseImpl {

	public void deleteStats(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		try {
			ratingsStatsPersistence.removeByC_C(classNameId, classPK);
		}
		catch (NoSuchStatsException nsse) {
			_log.warn(nsse);
		}

		ratingsEntryPersistence.removeByC_C(classNameId, classPK);
	}

	public RatingsStats getStats(long statsId)
		throws PortalException, SystemException {

		return ratingsStatsPersistence.findByPrimaryKey(statsId);
	}

	public RatingsStats getStats(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		RatingsStats stats = null;

		try {
			stats = ratingsStatsPersistence.findByC_C(classNameId, classPK);
		}
		catch (NoSuchStatsException nsse) {
			long statsId = counterLocalService.increment();

			stats = ratingsStatsPersistence.create(statsId);

			stats.setClassNameId(classNameId);
			stats.setClassPK(classPK);
			stats.setTotalEntries(0);
			stats.setTotalScore(0.0);
			stats.setAverageScore(0.0);

			ratingsStatsPersistence.update(stats);
		}

		return stats;
	}

	private static Log _log =
		LogFactory.getLog(RatingsStatsLocalServiceImpl.class);

}