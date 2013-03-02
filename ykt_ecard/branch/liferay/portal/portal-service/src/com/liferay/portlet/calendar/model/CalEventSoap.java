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

package com.liferay.portlet.calendar.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="CalEventSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.calendar.service.http.CalEventServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.calendar.service.http.CalEventServiceSoap
 *
 */
public class CalEventSoap implements Serializable {
	public static CalEventSoap toSoapModel(CalEvent model) {
		CalEventSoap soapModel = new CalEventSoap();

		soapModel.setUuid(model.getUuid());
		soapModel.setEventId(model.getEventId());
		soapModel.setGroupId(model.getGroupId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setTitle(model.getTitle());
		soapModel.setDescription(model.getDescription());
		soapModel.setStartDate(model.getStartDate());
		soapModel.setEndDate(model.getEndDate());
		soapModel.setDurationHour(model.getDurationHour());
		soapModel.setDurationMinute(model.getDurationMinute());
		soapModel.setAllDay(model.getAllDay());
		soapModel.setTimeZoneSensitive(model.getTimeZoneSensitive());
		soapModel.setType(model.getType());
		soapModel.setRepeating(model.getRepeating());
		soapModel.setRecurrence(model.getRecurrence());
		soapModel.setRemindBy(model.getRemindBy());
		soapModel.setFirstReminder(model.getFirstReminder());
		soapModel.setSecondReminder(model.getSecondReminder());

		return soapModel;
	}

	public static CalEventSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			CalEvent model = (CalEvent)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (CalEventSoap[])soapModels.toArray(new CalEventSoap[0]);
	}

	public CalEventSoap() {
	}

	public long getPrimaryKey() {
		return _eventId;
	}

	public void setPrimaryKey(long pk) {
		setEventId(pk);
	}

	public String getUuid() {
		return _uuid;
	}

	public void setUuid(String uuid) {
		_uuid = uuid;
	}

	public long getEventId() {
		return _eventId;
	}

	public void setEventId(long eventId) {
		_eventId = eventId;
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

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		_title = title;
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		_description = description;
	}

	public Date getStartDate() {
		return _startDate;
	}

	public void setStartDate(Date startDate) {
		_startDate = startDate;
	}

	public Date getEndDate() {
		return _endDate;
	}

	public void setEndDate(Date endDate) {
		_endDate = endDate;
	}

	public int getDurationHour() {
		return _durationHour;
	}

	public void setDurationHour(int durationHour) {
		_durationHour = durationHour;
	}

	public int getDurationMinute() {
		return _durationMinute;
	}

	public void setDurationMinute(int durationMinute) {
		_durationMinute = durationMinute;
	}

	public boolean getAllDay() {
		return _allDay;
	}

	public boolean isAllDay() {
		return _allDay;
	}

	public void setAllDay(boolean allDay) {
		_allDay = allDay;
	}

	public boolean getTimeZoneSensitive() {
		return _timeZoneSensitive;
	}

	public boolean isTimeZoneSensitive() {
		return _timeZoneSensitive;
	}

	public void setTimeZoneSensitive(boolean timeZoneSensitive) {
		_timeZoneSensitive = timeZoneSensitive;
	}

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		_type = type;
	}

	public boolean getRepeating() {
		return _repeating;
	}

	public boolean isRepeating() {
		return _repeating;
	}

	public void setRepeating(boolean repeating) {
		_repeating = repeating;
	}

	public String getRecurrence() {
		return _recurrence;
	}

	public void setRecurrence(String recurrence) {
		_recurrence = recurrence;
	}

	public String getRemindBy() {
		return _remindBy;
	}

	public void setRemindBy(String remindBy) {
		_remindBy = remindBy;
	}

	public int getFirstReminder() {
		return _firstReminder;
	}

	public void setFirstReminder(int firstReminder) {
		_firstReminder = firstReminder;
	}

	public int getSecondReminder() {
		return _secondReminder;
	}

	public void setSecondReminder(int secondReminder) {
		_secondReminder = secondReminder;
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