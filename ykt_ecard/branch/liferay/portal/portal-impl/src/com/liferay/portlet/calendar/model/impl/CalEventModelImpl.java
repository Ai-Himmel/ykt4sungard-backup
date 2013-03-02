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

package com.liferay.portlet.calendar.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.calendar.model.CalEvent;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="CalEventModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>CalEvent</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.calendar.service.model.CalEvent
 * @see com.liferay.portlet.calendar.service.model.CalEventModel
 * @see com.liferay.portlet.calendar.service.model.impl.CalEventImpl
 *
 */
public class CalEventModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "CalEvent";
	public static final Object[][] TABLE_COLUMNS = {
			{ "uuid_", new Integer(Types.VARCHAR) },
			

			{ "eventId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "title", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "startDate", new Integer(Types.TIMESTAMP) },
			

			{ "endDate", new Integer(Types.TIMESTAMP) },
			

			{ "durationHour", new Integer(Types.INTEGER) },
			

			{ "durationMinute", new Integer(Types.INTEGER) },
			

			{ "allDay", new Integer(Types.BOOLEAN) },
			

			{ "timeZoneSensitive", new Integer(Types.BOOLEAN) },
			

			{ "type_", new Integer(Types.VARCHAR) },
			

			{ "repeating", new Integer(Types.BOOLEAN) },
			

			{ "recurrence", new Integer(Types.CLOB) },
			

			{ "remindBy", new Integer(Types.VARCHAR) },
			

			{ "firstReminder", new Integer(Types.INTEGER) },
			

			{ "secondReminder", new Integer(Types.INTEGER) }
		};
	public static final String TABLE_SQL_CREATE = "create table CalEvent (uuid_ VARCHAR(75) null,eventId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,title VARCHAR(75) null,description STRING null,startDate DATE null,endDate DATE null,durationHour INTEGER,durationMinute INTEGER,allDay BOOLEAN,timeZoneSensitive BOOLEAN,type_ VARCHAR(75) null,repeating BOOLEAN,recurrence TEXT null,remindBy VARCHAR(75) null,firstReminder INTEGER,secondReminder INTEGER)";
	public static final String TABLE_SQL_DROP = "drop table CalEvent";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.calendar.model.CalEvent"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.calendar.model.CalEvent"));

	public CalEventModelImpl() {
	}

	public long getPrimaryKey() {
		return _eventId;
	}

	public void setPrimaryKey(long pk) {
		setEventId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_eventId);
	}

	public String getUuid() {
		return GetterUtil.getString(_uuid);
	}

	public void setUuid(String uuid) {
		if ((uuid != null) && (uuid != _uuid)) {
			_uuid = uuid;
		}
	}

	public long getEventId() {
		return _eventId;
	}

	public void setEventId(long eventId) {
		if (eventId != _eventId) {
			_eventId = eventId;
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

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public String getTitle() {
		return GetterUtil.getString(_title);
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			_title = title;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
		}
	}

	public Date getStartDate() {
		return _startDate;
	}

	public void setStartDate(Date startDate) {
		if (((startDate == null) && (_startDate != null)) ||
				((startDate != null) && (_startDate == null)) ||
				((startDate != null) && (_startDate != null) &&
				!startDate.equals(_startDate))) {
			_startDate = startDate;
		}
	}

	public Date getEndDate() {
		return _endDate;
	}

	public void setEndDate(Date endDate) {
		if (((endDate == null) && (_endDate != null)) ||
				((endDate != null) && (_endDate == null)) ||
				((endDate != null) && (_endDate != null) &&
				!endDate.equals(_endDate))) {
			_endDate = endDate;
		}
	}

	public int getDurationHour() {
		return _durationHour;
	}

	public void setDurationHour(int durationHour) {
		if (durationHour != _durationHour) {
			_durationHour = durationHour;
		}
	}

	public int getDurationMinute() {
		return _durationMinute;
	}

	public void setDurationMinute(int durationMinute) {
		if (durationMinute != _durationMinute) {
			_durationMinute = durationMinute;
		}
	}

	public boolean getAllDay() {
		return _allDay;
	}

	public boolean isAllDay() {
		return _allDay;
	}

	public void setAllDay(boolean allDay) {
		if (allDay != _allDay) {
			_allDay = allDay;
		}
	}

	public boolean getTimeZoneSensitive() {
		return _timeZoneSensitive;
	}

	public boolean isTimeZoneSensitive() {
		return _timeZoneSensitive;
	}

	public void setTimeZoneSensitive(boolean timeZoneSensitive) {
		if (timeZoneSensitive != _timeZoneSensitive) {
			_timeZoneSensitive = timeZoneSensitive;
		}
	}

	public String getType() {
		return GetterUtil.getString(_type);
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			_type = type;
		}
	}

	public boolean getRepeating() {
		return _repeating;
	}

	public boolean isRepeating() {
		return _repeating;
	}

	public void setRepeating(boolean repeating) {
		if (repeating != _repeating) {
			_repeating = repeating;
		}
	}

	public String getRecurrence() {
		return GetterUtil.getString(_recurrence);
	}

	public void setRecurrence(String recurrence) {
		if (((recurrence == null) && (_recurrence != null)) ||
				((recurrence != null) && (_recurrence == null)) ||
				((recurrence != null) && (_recurrence != null) &&
				!recurrence.equals(_recurrence))) {
			_recurrence = recurrence;
		}
	}

	public String getRemindBy() {
		return GetterUtil.getString(_remindBy);
	}

	public void setRemindBy(String remindBy) {
		if (((remindBy == null) && (_remindBy != null)) ||
				((remindBy != null) && (_remindBy == null)) ||
				((remindBy != null) && (_remindBy != null) &&
				!remindBy.equals(_remindBy))) {
			_remindBy = remindBy;
		}
	}

	public int getFirstReminder() {
		return _firstReminder;
	}

	public void setFirstReminder(int firstReminder) {
		if (firstReminder != _firstReminder) {
			_firstReminder = firstReminder;
		}
	}

	public int getSecondReminder() {
		return _secondReminder;
	}

	public void setSecondReminder(int secondReminder) {
		if (secondReminder != _secondReminder) {
			_secondReminder = secondReminder;
		}
	}

	public CalEvent toEscapedModel() {
		if (isEscapedModel()) {
			return (CalEvent)this;
		}
		else {
			CalEvent model = new CalEventImpl();

			model.setEscapedModel(true);

			model.setUuid(Html.escape(getUuid()));
			model.setEventId(getEventId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setTitle(Html.escape(getTitle()));
			model.setDescription(Html.escape(getDescription()));
			model.setStartDate(getStartDate());
			model.setEndDate(getEndDate());
			model.setDurationHour(getDurationHour());
			model.setDurationMinute(getDurationMinute());
			model.setAllDay(getAllDay());
			model.setTimeZoneSensitive(getTimeZoneSensitive());
			model.setType(Html.escape(getType()));
			model.setRepeating(getRepeating());
			model.setRecurrence(Html.escape(getRecurrence()));
			model.setRemindBy(Html.escape(getRemindBy()));
			model.setFirstReminder(getFirstReminder());
			model.setSecondReminder(getSecondReminder());

			model = (CalEvent)Proxy.newProxyInstance(CalEvent.class.getClassLoader(),
					new Class[] { CalEvent.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		CalEventImpl clone = new CalEventImpl();

		clone.setUuid(getUuid());
		clone.setEventId(getEventId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setTitle(getTitle());
		clone.setDescription(getDescription());
		clone.setStartDate(getStartDate());
		clone.setEndDate(getEndDate());
		clone.setDurationHour(getDurationHour());
		clone.setDurationMinute(getDurationMinute());
		clone.setAllDay(getAllDay());
		clone.setTimeZoneSensitive(getTimeZoneSensitive());
		clone.setType(getType());
		clone.setRepeating(getRepeating());
		clone.setRecurrence(getRecurrence());
		clone.setRemindBy(getRemindBy());
		clone.setFirstReminder(getFirstReminder());
		clone.setSecondReminder(getSecondReminder());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		CalEventImpl calEvent = (CalEventImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getStartDate(), calEvent.getStartDate());

		if (value != 0) {
			return value;
		}

		value = getTitle().toLowerCase().compareTo(calEvent.getTitle()
														   .toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		CalEventImpl calEvent = null;

		try {
			calEvent = (CalEventImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = calEvent.getPrimaryKey();

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

	private String _uuid;
	private long _eventId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _title;
	private String _description;
	private Date _startDate;
	private Date _endDate;
	private int _durationHour;
	private int _durationMinute;
	private boolean _allDay;
	private boolean _timeZoneSensitive;
	private String _type;
	private boolean _repeating;
	private String _recurrence;
	private String _remindBy;
	private int _firstReminder;
	private int _secondReminder;
}