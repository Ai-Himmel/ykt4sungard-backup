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

package com.liferay.portlet.blogs.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="BlogsStatsUserSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.blogs.service.http.BlogsStatsUserServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.blogs.service.http.BlogsStatsUserServiceSoap
 *
 */
public class BlogsStatsUserSoap implements Serializable {
	public static BlogsStatsUserSoap toSoapModel(BlogsStatsUser model) {
		BlogsStatsUserSoap soapModel = new BlogsStatsUserSoap();

		soapModel.setStatsUserId(model.getStatsUserId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setEntryCount(model.getEntryCount());
		soapModel.setLastPostDate(model.getLastPostDate());
		soapModel.setRatingsTotalEntries(model.getRatingsTotalEntries());
		soapModel.setRatingsTotalScore(model.getRatingsTotalScore());
		soapModel.setRatingsAverageScore(model.getRatingsAverageScore());

		return soapModel;
	}

	public static BlogsStatsUserSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			BlogsStatsUser model = (BlogsStatsUser)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (BlogsStatsUserSoap[])soapModels.toArray(new BlogsStatsUserSoap[0]);
	}

	public BlogsStatsUserSoap() {
	}

	public long getPrimaryKey() {
		return _statsUserId;
	}

	public void setPrimaryKey(long pk) {
		setStatsUserId(pk);
	}

	public long getStatsUserId() {
		return _statsUserId;
	}

	public void setStatsUserId(long statsUserId) {
		_statsUserId = statsUserId;
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		_groupId = groupId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public int getEntryCount() {
		return _entryCount;
	}

	public void setEntryCount(int entryCount) {
		_entryCount = entryCount;
	}

	public Date getLastPostDate() {
		return _lastPostDate;
	}

	public void setLastPostDate(Date lastPostDate) {
		_lastPostDate = lastPostDate;
	}

	public int getRatingsTotalEntries() {
		return _ratingsTotalEntries;
	}

	public void setRatingsTotalEntries(int ratingsTotalEntries) {
		_ratingsTotalEntries = ratingsTotalEntries;
	}

	public double getRatingsTotalScore() {
		return _ratingsTotalScore;
	}

	public void setRatingsTotalScore(double ratingsTotalScore) {
		_ratingsTotalScore = ratingsTotalScore;
	}

	public double getRatingsAverageScore() {
		return _ratingsAverageScore;
	}

	public void setRatingsAverageScore(double ratingsAverageScore) {
		_ratingsAverageScore = ratingsAverageScore;
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