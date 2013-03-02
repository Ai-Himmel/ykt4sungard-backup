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

package com.liferay.portlet.ratings.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.ratings.model.RatingsStats;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

/**
 * <a href="RatingsStatsModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>RatingsStats</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.ratings.service.model.RatingsStats
 * @see com.liferay.portlet.ratings.service.model.RatingsStatsModel
 * @see com.liferay.portlet.ratings.service.model.impl.RatingsStatsImpl
 *
 */
public class RatingsStatsModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "RatingsStats";
	public static final Object[][] TABLE_COLUMNS = {
			{ "statsId", new Integer(Types.BIGINT) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "totalEntries", new Integer(Types.INTEGER) },
			

			{ "totalScore", new Integer(Types.DOUBLE) },
			

			{ "averageScore", new Integer(Types.DOUBLE) }
		};
	public static final String TABLE_SQL_CREATE = "create table RatingsStats (statsId LONG not null primary key,classNameId LONG,classPK LONG,totalEntries INTEGER,totalScore DOUBLE,averageScore DOUBLE)";
	public static final String TABLE_SQL_DROP = "drop table RatingsStats";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.ratings.model.RatingsStats"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.ratings.model.RatingsStats"));

	public RatingsStatsModelImpl() {
	}

	public long getPrimaryKey() {
		return _statsId;
	}

	public void setPrimaryKey(long pk) {
		setStatsId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_statsId);
	}

	public long getStatsId() {
		return _statsId;
	}

	public void setStatsId(long statsId) {
		if (statsId != _statsId) {
			_statsId = statsId;
		}
	}

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		if (classNameId != _classNameId) {
			_classNameId = classNameId;
		}
	}

	public long getClassPK() {
		return _classPK;
	}

	public void setClassPK(long classPK) {
		if (classPK != _classPK) {
			_classPK = classPK;
		}
	}

	public int getTotalEntries() {
		return _totalEntries;
	}

	public void setTotalEntries(int totalEntries) {
		if (totalEntries != _totalEntries) {
			_totalEntries = totalEntries;
		}
	}

	public double getTotalScore() {
		return _totalScore;
	}

	public void setTotalScore(double totalScore) {
		if (totalScore != _totalScore) {
			_totalScore = totalScore;
		}
	}

	public double getAverageScore() {
		return _averageScore;
	}

	public void setAverageScore(double averageScore) {
		if (averageScore != _averageScore) {
			_averageScore = averageScore;
		}
	}

	public RatingsStats toEscapedModel() {
		if (isEscapedModel()) {
			return (RatingsStats)this;
		}
		else {
			RatingsStats model = new RatingsStatsImpl();

			model.setEscapedModel(true);

			model.setStatsId(getStatsId());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setTotalEntries(getTotalEntries());
			model.setTotalScore(getTotalScore());
			model.setAverageScore(getAverageScore());

			model = (RatingsStats)Proxy.newProxyInstance(RatingsStats.class.getClassLoader(),
					new Class[] { RatingsStats.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		RatingsStatsImpl clone = new RatingsStatsImpl();

		clone.setStatsId(getStatsId());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setTotalEntries(getTotalEntries());
		clone.setTotalScore(getTotalScore());
		clone.setAverageScore(getAverageScore());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		RatingsStatsImpl ratingsStats = (RatingsStatsImpl)obj;

		long pk = ratingsStats.getPrimaryKey();

		if (getPrimaryKey() < pk) {
			return -1;
		}
		else if (getPrimaryKey() > pk) {
			return 1;
		}
		else {
			return 0;
		}
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		RatingsStatsImpl ratingsStats = null;

		try {
			ratingsStats = (RatingsStatsImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = ratingsStats.getPrimaryKey();

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

	private long _statsId;
	private long _classNameId;
	private long _classPK;
	private int _totalEntries;
	private double _totalScore;
	private double _averageScore;
}