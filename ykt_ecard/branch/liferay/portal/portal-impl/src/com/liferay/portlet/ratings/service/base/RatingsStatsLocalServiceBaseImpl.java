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

package com.liferay.portlet.ratings.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;

import com.liferay.portlet.ratings.model.RatingsStats;
import com.liferay.portlet.ratings.model.impl.RatingsStatsImpl;
import com.liferay.portlet.ratings.service.RatingsEntryLocalService;
import com.liferay.portlet.ratings.service.RatingsEntryLocalServiceFactory;
import com.liferay.portlet.ratings.service.RatingsEntryService;
import com.liferay.portlet.ratings.service.RatingsEntryServiceFactory;
import com.liferay.portlet.ratings.service.RatingsStatsLocalService;
import com.liferay.portlet.ratings.service.persistence.RatingsEntryPersistence;
import com.liferay.portlet.ratings.service.persistence.RatingsEntryUtil;
import com.liferay.portlet.ratings.service.persistence.RatingsStatsPersistence;
import com.liferay.portlet.ratings.service.persistence.RatingsStatsUtil;

import org.springframework.beans.factory.InitializingBean;

import java.util.List;

/**
 * <a href="RatingsStatsLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class RatingsStatsLocalServiceBaseImpl
	implements RatingsStatsLocalService, InitializingBean {
	public RatingsStats addRatingsStats(RatingsStats model)
		throws SystemException {
		RatingsStats ratingsStats = new RatingsStatsImpl();

		ratingsStats.setNew(true);

		ratingsStats.setStatsId(model.getStatsId());
		ratingsStats.setClassNameId(model.getClassNameId());
		ratingsStats.setClassPK(model.getClassPK());
		ratingsStats.setTotalEntries(model.getTotalEntries());
		ratingsStats.setTotalScore(model.getTotalScore());
		ratingsStats.setAverageScore(model.getAverageScore());

		return ratingsStatsPersistence.update(ratingsStats);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return ratingsStatsPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return ratingsStatsPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public RatingsStats updateRatingsStats(RatingsStats model)
		throws SystemException {
		RatingsStats ratingsStats = new RatingsStatsImpl();

		ratingsStats.setNew(false);

		ratingsStats.setStatsId(model.getStatsId());
		ratingsStats.setClassNameId(model.getClassNameId());
		ratingsStats.setClassPK(model.getClassPK());
		ratingsStats.setTotalEntries(model.getTotalEntries());
		ratingsStats.setTotalScore(model.getTotalScore());
		ratingsStats.setAverageScore(model.getAverageScore());

		return ratingsStatsPersistence.update(ratingsStats);
	}

	public RatingsEntryLocalService getRatingsEntryLocalService() {
		return ratingsEntryLocalService;
	}

	public void setRatingsEntryLocalService(
		RatingsEntryLocalService ratingsEntryLocalService) {
		this.ratingsEntryLocalService = ratingsEntryLocalService;
	}

	public RatingsEntryService getRatingsEntryService() {
		return ratingsEntryService;
	}

	public void setRatingsEntryService(RatingsEntryService ratingsEntryService) {
		this.ratingsEntryService = ratingsEntryService;
	}

	public RatingsEntryPersistence getRatingsEntryPersistence() {
		return ratingsEntryPersistence;
	}

	public void setRatingsEntryPersistence(
		RatingsEntryPersistence ratingsEntryPersistence) {
		this.ratingsEntryPersistence = ratingsEntryPersistence;
	}

	public RatingsStatsPersistence getRatingsStatsPersistence() {
		return ratingsStatsPersistence;
	}

	public void setRatingsStatsPersistence(
		RatingsStatsPersistence ratingsStatsPersistence) {
		this.ratingsStatsPersistence = ratingsStatsPersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public void afterPropertiesSet() {
		if (ratingsEntryLocalService == null) {
			ratingsEntryLocalService = RatingsEntryLocalServiceFactory.getImpl();
		}

		if (ratingsEntryService == null) {
			ratingsEntryService = RatingsEntryServiceFactory.getImpl();
		}

		if (ratingsEntryPersistence == null) {
			ratingsEntryPersistence = RatingsEntryUtil.getPersistence();
		}

		if (ratingsStatsPersistence == null) {
			ratingsStatsPersistence = RatingsStatsUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}
	}

	protected RatingsEntryLocalService ratingsEntryLocalService;
	protected RatingsEntryService ratingsEntryService;
	protected RatingsEntryPersistence ratingsEntryPersistence;
	protected RatingsStatsPersistence ratingsStatsPersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
}