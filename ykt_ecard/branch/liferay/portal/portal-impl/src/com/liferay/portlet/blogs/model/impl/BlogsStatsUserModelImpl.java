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

package com.liferay.portlet.blogs.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.blogs.model.BlogsStatsUser;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="BlogsStatsUserModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>BlogsStatsUser</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.blogs.service.model.BlogsStatsUser
 * @see com.liferay.portlet.blogs.service.model.BlogsStatsUserModel
 * @see com.liferay.portlet.blogs.service.model.impl.BlogsStatsUserImpl
 *
 */
public class BlogsStatsUserModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "BlogsStatsUser";
	public static final Object[][] TABLE_COLUMNS = {
			{ "statsUserId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "entryCount", new Integer(Types.INTEGER) },
			

			{ "lastPostDate", new Integer(Types.TIMESTAMP) },
			

			{ "ratingsTotalEntries", new Integer(Types.INTEGER) },
			

			{ "ratingsTotalScore", new Integer(Types.DOUBLE) },
			

			{ "ratingsAverageScore", new Integer(Types.DOUBLE) }
		};
	public static final String TABLE_SQL_CREATE = "create table BlogsStatsUser (statsUserId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,entryCount INTEGER,lastPostDate DATE null,ratingsTotalEntries INTEGER,ratingsTotalScore DOUBLE,ratingsAverageScore DOUBLE)";
	public static final String TABLE_SQL_DROP = "drop table BlogsStatsUser";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.blogs.model.BlogsStatsUser"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.blogs.model.BlogsStatsUser"));

	public BlogsStatsUserModelImpl() {
	}

	public long getPrimaryKey() {
		return _statsUserId;
	}

	public void setPrimaryKey(long pk) {
		setStatsUserId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_statsUserId);
	}

	public long getStatsUserId() {
		return _statsUserId;
	}

	public void setStatsUserId(long statsUserId) {
		if (statsUserId != _statsUserId) {
			_statsUserId = statsUserId;
		}
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public int getEntryCount() {
		return _entryCount;
	}

	public void setEntryCount(int entryCount) {
		if (entryCount != _entryCount) {
			_entryCount = entryCount;
		}
	}

	public Date getLastPostDate() {
		return _lastPostDate;
	}

	public void setLastPostDate(Date lastPostDate) {
		if (((lastPostDate == null) && (_lastPostDate != null)) ||
				((lastPostDate != null) && (_lastPostDate == null)) ||
				((lastPostDate != null) && (_lastPostDate != null) &&
				!lastPostDate.equals(_lastPostDate))) {
			_lastPostDate = lastPostDate;
		}
	}

	public int getRatingsTotalEntries() {
		return _ratingsTotalEntries;
	}

	public void setRatingsTotalEntries(int ratingsTotalEntries) {
		if (ratingsTotalEntries != _ratingsTotalEntries) {
			_ratingsTotalEntries = ratingsTotalEntries;
		}
	}

	public double getRatingsTotalScore() {
		return _ratingsTotalScore;
	}

	public void setRatingsTotalScore(double ratingsTotalScore) {
		if (ratingsTotalScore != _ratingsTotalScore) {
			_ratingsTotalScore = ratingsTotalScore;
		}
	}

	public double getRatingsAverageScore() {
		return _ratingsAverageScore;
	}

	public void setRatingsAverageScore(double ratingsAverageScore) {
		if (ratingsAverageScore != _ratingsAverageScore) {
			_ratingsAverageScore = ratingsAverageScore;
		}
	}

	public BlogsStatsUser toEscapedModel() {
		if (isEscapedModel()) {
			return (BlogsStatsUser)this;
		}
		else {
			BlogsStatsUser model = new BlogsStatsUserImpl();

			model.setEscapedModel(true);

			model.setStatsUserId(getStatsUserId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setEntryCount(getEntryCount());
			model.setLastPostDate(getLastPostDate());
			model.setRatingsTotalEntries(getRatingsTotalEntries());
			model.setRatingsTotalScore(getRatingsTotalScore());
			model.setRatingsAverageScore(getRatingsAverageScore());

			model = (BlogsStatsUser)Proxy.newProxyInstance(BlogsStatsUser.class.getClassLoader(),
					new Class[] { BlogsStatsUser.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		BlogsStatsUserImpl clone = new BlogsStatsUserImpl();

		clone.setStatsUserId(getStatsUserId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setEntryCount(getEntryCount());
		clone.setLastPostDate(getLastPostDate());
		clone.setRatingsTotalEntries(getRatingsTotalEntries());
		clone.setRatingsTotalScore(getRatingsTotalScore());
		clone.setRatingsAverageScore(getRatingsAverageScore());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		BlogsStatsUserImpl blogsStatsUser = (BlogsStatsUserImpl)obj;

		int value = 0;

		if (getEntryCount() < blogsStatsUser.getEntryCount()) {
			value = -1;
		}
		else if (getEntryCount() > blogsStatsUser.getEntryCount()) {
			value = 1;
		}
		else {
			value = 0;
		}

		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		BlogsStatsUserImpl blogsStatsUser = null;

		try {
			blogsStatsUser = (BlogsStatsUserImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = blogsStatsUser.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private long _statsUserId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private int _entryCount;
	private Date _lastPostDate;
	private int _ratingsTotalEntries;
	private double _ratingsTotalScore;
	private double _ratingsAverageScore;
}