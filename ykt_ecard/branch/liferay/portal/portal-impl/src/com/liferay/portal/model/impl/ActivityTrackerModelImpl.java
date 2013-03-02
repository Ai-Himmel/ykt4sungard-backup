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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.ActivityTracker;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="ActivityTrackerModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ActivityTracker</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.ActivityTracker
 * @see com.liferay.portal.service.model.ActivityTrackerModel
 * @see com.liferay.portal.service.model.impl.ActivityTrackerImpl
 *
 */
public class ActivityTrackerModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ActivityTracker";
	public static final Object[][] TABLE_COLUMNS = {
			{ "activityTrackerId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "classNameId", new Integer(Types.BIGINT) },
			

			{ "classPK", new Integer(Types.BIGINT) },
			

			{ "activity", new Integer(Types.VARCHAR) },
			

			{ "extraData", new Integer(Types.CLOB) },
			

			{ "receiverUserId", new Integer(Types.BIGINT) },
			

			{ "receiverUserName", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table ActivityTracker (activityTrackerId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,classNameId LONG,classPK LONG,activity VARCHAR(75) null,extraData TEXT null,receiverUserId LONG,receiverUserName VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table ActivityTracker";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portal.model.ActivityTracker"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.ActivityTracker"));

	public ActivityTrackerModelImpl() {
	}

	public long getPrimaryKey() {
		return _activityTrackerId;
	}

	public void setPrimaryKey(long pk) {
		setActivityTrackerId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_activityTrackerId);
	}

	public long getActivityTrackerId() {
		return _activityTrackerId;
	}

	public void setActivityTrackerId(long activityTrackerId) {
		if (activityTrackerId != _activityTrackerId) {
			_activityTrackerId = activityTrackerId;
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

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
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

	public String getActivity() {
		return GetterUtil.getString(_activity);
	}

	public void setActivity(String activity) {
		if (((activity == null) && (_activity != null)) ||
				((activity != null) && (_activity == null)) ||
				((activity != null) && (_activity != null) &&
				!activity.equals(_activity))) {
			_activity = activity;
		}
	}

	public String getExtraData() {
		return GetterUtil.getString(_extraData);
	}

	public void setExtraData(String extraData) {
		if (((extraData == null) && (_extraData != null)) ||
				((extraData != null) && (_extraData == null)) ||
				((extraData != null) && (_extraData != null) &&
				!extraData.equals(_extraData))) {
			_extraData = extraData;
		}
	}

	public long getReceiverUserId() {
		return _receiverUserId;
	}

	public void setReceiverUserId(long receiverUserId) {
		if (receiverUserId != _receiverUserId) {
			_receiverUserId = receiverUserId;
		}
	}

	public String getReceiverUserName() {
		return GetterUtil.getString(_receiverUserName);
	}

	public void setReceiverUserName(String receiverUserName) {
		if (((receiverUserName == null) && (_receiverUserName != null)) ||
				((receiverUserName != null) && (_receiverUserName == null)) ||
				((receiverUserName != null) && (_receiverUserName != null) &&
				!receiverUserName.equals(_receiverUserName))) {
			_receiverUserName = receiverUserName;
		}
	}

	public ActivityTracker toEscapedModel() {
		if (isEscapedModel()) {
			return (ActivityTracker)this;
		}
		else {
			ActivityTracker model = new ActivityTrackerImpl();

			model.setEscapedModel(true);

			model.setActivityTrackerId(getActivityTrackerId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setClassNameId(getClassNameId());
			model.setClassPK(getClassPK());
			model.setActivity(Html.escape(getActivity()));
			model.setExtraData(Html.escape(getExtraData()));
			model.setReceiverUserId(getReceiverUserId());
			model.setReceiverUserName(Html.escape(getReceiverUserName()));

			model = (ActivityTracker)Proxy.newProxyInstance(ActivityTracker.class.getClassLoader(),
					new Class[] { ActivityTracker.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ActivityTrackerImpl clone = new ActivityTrackerImpl();

		clone.setActivityTrackerId(getActivityTrackerId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setClassNameId(getClassNameId());
		clone.setClassPK(getClassPK());
		clone.setActivity(getActivity());
		clone.setExtraData(getExtraData());
		clone.setReceiverUserId(getReceiverUserId());
		clone.setReceiverUserName(getReceiverUserName());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ActivityTrackerImpl activityTracker = (ActivityTrackerImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(),
				activityTracker.getCreateDate());

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

		ActivityTrackerImpl activityTracker = null;

		try {
			activityTracker = (ActivityTrackerImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = activityTracker.getPrimaryKey();

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