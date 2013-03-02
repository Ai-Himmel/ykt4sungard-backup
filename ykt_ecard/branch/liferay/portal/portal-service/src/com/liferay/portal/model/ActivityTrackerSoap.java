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

package com.liferay.portal.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="ActivityTrackerSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.ActivityTrackerServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.ActivityTrackerServiceSoap
 *
 */
public class ActivityTrackerSoap implements Serializable {
	public static ActivityTrackerSoap toSoapModel(ActivityTracker model) {
		ActivityTrackerSoap soapModel = new ActivityTrackerSoap();

		soapModel.setActivityTrackerId(model.getActivityTrackerId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setClassNameId(model.getClassNameId());
		soapModel.setClassPK(model.getClassPK());
		soapModel.setActivity(model.getActivity());
		soapModel.setExtraData(model.getExtraData());
		soapModel.setReceiverUserId(model.getReceiverUserId());
		soapModel.setReceiverUserName(model.getReceiverUserName());

		return soapModel;
	}

	public static ActivityTrackerSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			ActivityTracker model = (ActivityTracker)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ActivityTrackerSoap[])soapModels.toArray(new ActivityTrackerSoap[0]);
	}

	public ActivityTrackerSoap() {
	}

	public long getPrimaryKey() {
		return _activityTrackerId;
	}

	public void setPrimaryKey(long pk) {
		setActivityTrackerId(pk);
	}

	public long getActivityTrackerId() {
		return _activityTrackerId;
	}

	public void setActivityTrackerId(long activityTrackerId) {
		_activityTrackerId = activityTrackerId;
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

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		_userName = userName;
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	public long getClassNameId() {
		return _classNameId;
	}

	public void setClassNameId(long classNameId) {
		_classNameId = classNameId;
	}

	public long getClassPK() {
		return _classPK;
	}

	public void setClassPK(long classPK) {
		_classPK = classPK;
	}

	public String getActivity() {
		return _activity;
	}

	public void setActivity(String activity) {
		_activity = activity;
	}

	public String getExtraData() {
		return _extraData;
	}

	public void setExtraData(String extraData) {
		_extraData = extraData;
	}

	public long getReceiverUserId() {
		return _receiverUserId;
	}

	public void setReceiverUserId(long receiverUserId) {
		_receiverUserId = receiverUserId;
	}

	public String getReceiverUserName() {
		return _receiverUserName;
	}

	public void setReceiverUserName(String receiverUserName) {
		_receiverUserName = receiverUserName;
	}

	private long _activityTrackerId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private long _classNameId;
	private long _classPK;
	private String _activity;
	private String _extraData;
	private long _receiverUserId;
	private String _receiverUserName;
}