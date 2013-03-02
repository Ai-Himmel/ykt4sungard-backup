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
import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.blogs.model.BlogsStatsUser;
import com.liferay.portlet.ratings.NoSuchEntryException;
import com.liferay.portlet.ratings.model.RatingsEntry;
import com.liferay.portlet.ratings.model.RatingsStats;
import com.liferay.portlet.ratings.service.base.RatingsEntryLocalServiceBaseImpl;

import java.util.Date;
import java.util.List;

/**
 * <a href="RatingsEntryLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RatingsEntryLocalServiceImpl
	extends RatingsEntryLocalServiceBaseImpl {

	public RatingsEntry getEntry(long userId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return ratingsEntryPersistence.findByU_C_C(
			userId, classNameId, classPK);
	}

	public List getEntries(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return ratingsEntryPersistence.findByC_C(classNameId, classPK);
	}

	public RatingsEntry updateEntry(
			long userId, String className, long classPK, double score)
		throws PortalException, SystemException {

		boolean newEntry = false;

		long classNameId = PortalUtil.getClassNameId(className);
		double oldScore = 0;
		Date now = new Date();

		RatingsEntry entry = null;

		try {
			entry = ratingsEntryPersistence.findByU_C_C(
				userId, classNameId, classPK);

			oldScore = entry.getScore();

			entry.setModifiedDate(now);
			entry.setScore(score);

			ratingsEntryPersistence.update(entry);

			// Stats

			RatingsStats stats = ratingsStatsLocalService.getStats(
				className, classPK);

			stats.setTotalScore(stats.getTotalScore() - oldScore + score);
			stats.setAverageScore(
				stats.getTotalScore() / stats.getTotalEntries());

			ratingsStatsPersistence.update(stats);
		}
		catch (NoSuchEntryException nsee) {
			newEntry = true;

			User user = userPersistence.findByPrimaryKey(userId);

			long entryId = counterLocalService.increment();

			entry = ratingsEntryPersistence.create(entryId);

			entry.setCompanyId(user.getCompanyId());
			entry.setUserId(user.getUserId());
			entry.setUserName(user.getFullName());
			entry.setCreateDate(now);
			entry.setModifiedDate(now);
			entry.setClassNameId(classNameId);
			entry.setClassPK(classPK);
			entry.setScore(score);

			ratingsEntryPersistence.update(entry);

			// Stats

			RatingsStats stats = ratingsStatsLocalService.getStats(
				className, classPK);

			stats.setTotalEntries(stats.getTotalEntries() + 1);
			stats.setTotalScore(stats.getTotalScore() + score);
			stats.setAverageScore(
				stats.getTotalScore() / stats.getTotalEntries());

			ratingsStatsPersistence.update(stats);
		}

		// Blogs entry

		if (className.equals(BlogsEntry.class.getName())) {
			BlogsEntry blogsEntry = blogsEntryPersistence.findByPrimaryKey(
				classPK);

			BlogsStatsUser blogsStasUser =
				blogsStatsUserLocalService.getStatsUser(
					blogsEntry.getGroupId(), blogsEntry.getUserId());

			int ratingsTotalEntries = blogsStasUser.getRatingsTotalEntries();
			double ratingsTotalScore = blogsStasUser.getRatingsTotalScore();
			double ratingsAverageScore = blogsStasUser.getRatingsAverageScore();

			if (newEntry) {
				ratingsTotalEntries++;
				ratingsTotalScore += score;
			}
			else {
				ratingsTotalScore = ratingsTotalScore - oldScore + score;
			}

			ratingsAverageScore = ratingsTotalScore / ratingsTotalEntries;

			blogsStasUser.setRatingsTotalEntries(ratingsTotalEntries);
			blogsStasUser.setRatingsTotalScore(ratingsTotalScore);
			blogsStasUser.setRatingsAverageScore(ratingsAverageScore);

			blogsStatsUserPersistence.update(blogsStasUser);
		}

		return entry;
	}

}