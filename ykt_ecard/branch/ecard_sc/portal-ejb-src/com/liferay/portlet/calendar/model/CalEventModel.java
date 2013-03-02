/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="CalEventModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.80 $
 *
 */
public class CalEventModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.calendar.model.CalEvent"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.calendar.model.CalEvent"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_EVENTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.eventId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_GROUPID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.groupId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.userName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TITLE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.title"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.description"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.type"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_LOCATION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.location"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_STREET = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.street"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CITY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.city"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_STATE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.state"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ZIP = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.zip"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PHONE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.phone"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_RECURRENCE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.recurrence"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_REMINDBY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.calendar.model.CalEvent.remindBy"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.calendar.model.CalEventModel"));

	public CalEventModel() {
	}

	public CalEventModel(String eventId) {
		_eventId = eventId;
		setNew(true);
	}

	public CalEventModel(String eventId, String groupId, String companyId,
		String userId, String userName, Date createDate, Date modifiedDate,
		String title, String description, Date startDate, Date endDate,
		int durationHour, int durationMinute, boolean allDay,
		boolean timeZoneSensitive, String type, String location, String street,
		String city, String state, String zip, String phone, boolean repeating,
		String recurrence, String remindBy, int firstReminder,
		int secondReminder) {
		_eventId = eventId;
		_groupId = groupId;
		_companyId = companyId;
		_userId = userId;
		_userName = userName;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_title = title;
		_description = description;
		_startDate = startDate;
		_endDate = endDate;
		_durationHour = durationHour;
		_durationMinute = durationMinute;
		_allDay = allDay;
		_timeZoneSensitive = timeZoneSensitive;
		_type = type;
		_location = location;
		_street = street;
		_city = city;
		_state = state;
		_zip = zip;
		_phone = phone;
		_repeating = repeating;
		_recurrence = recurrence;
		_remindBy = remindBy;
		_firstReminder = firstReminder;
		_secondReminder = secondReminder;
	}

	public String getPrimaryKey() {
		return _eventId;
	}

	public String getEventId() {
		return _eventId;
	}

	public void setEventId(String eventId) {
		if (((eventId == null) && (_eventId != null)) ||
				((eventId != null) && (_eventId == null)) ||
				((eventId != null) && (_eventId != null) &&
				!eventId.equals(_eventId))) {
			if (!XSS_ALLOW_EVENTID) {
				eventId = Xss.strip(eventId);
			}

			_eventId = eventId;
			setModified(true);
		}
	}

	public String getGroupId() {
		return _groupId;
	}

	public void setGroupId(String groupId) {
		if (((groupId == null) && (_groupId != null)) ||
				((groupId != null) && (_groupId == null)) ||
				((groupId != null) && (_groupId != null) &&
				!groupId.equals(_groupId))) {
			if (!XSS_ALLOW_GROUPID) {
				groupId = Xss.strip(groupId);
			}

			_groupId = groupId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
			setModified(true);
		}
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			if (!XSS_ALLOW_USERNAME) {
				userName = Xss.strip(userName);
			}

			_userName = userName;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public String getTitle() {
		return _title;
	}

	public void setTitle(String title) {
		if (((title == null) && (_title != null)) ||
				((title != null) && (_title == null)) ||
				((title != null) && (_title != null) && !title.equals(_title))) {
			if (!XSS_ALLOW_TITLE) {
				title = Xss.strip(title);
			}

			_title = title;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public int getDurationHour() {
		return _durationHour;
	}

	public void setDurationHour(int durationHour) {
		if (durationHour != _durationHour) {
			_durationHour = durationHour;
			setModified(true);
		}
	}

	public int getDurationMinute() {
		return _durationMinute;
	}

	public void setDurationMinute(int durationMinute) {
		if (durationMinute != _durationMinute) {
			_durationMinute = durationMinute;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			if (!XSS_ALLOW_TYPE) {
				type = Xss.strip(type);
			}

			_type = type;
			setModified(true);
		}
	}

	public String getLocation() {
		return _location;
	}

	public void setLocation(String location) {
		if (((location == null) && (_location != null)) ||
				((location != null) && (_location == null)) ||
				((location != null) && (_location != null) &&
				!location.equals(_location))) {
			if (!XSS_ALLOW_LOCATION) {
				location = Xss.strip(location);
			}

			_location = location;
			setModified(true);
		}
	}

	public String getStreet() {
		return _street;
	}

	public void setStreet(String street) {
		if (((street == null) && (_street != null)) ||
				((street != null) && (_street == null)) ||
				((street != null) && (_street != null) &&
				!street.equals(_street))) {
			if (!XSS_ALLOW_STREET) {
				street = Xss.strip(street);
			}

			_street = street;
			setModified(true);
		}
	}

	public String getCity() {
		return _city;
	}

	public void setCity(String city) {
		if (((city == null) && (_city != null)) ||
				((city != null) && (_city == null)) ||
				((city != null) && (_city != null) && !city.equals(_city))) {
			if (!XSS_ALLOW_CITY) {
				city = Xss.strip(city);
			}

			_city = city;
			setModified(true);
		}
	}

	public String getState() {
		return _state;
	}

	public void setState(String state) {
		if (((state == null) && (_state != null)) ||
				((state != null) && (_state == null)) ||
				((state != null) && (_state != null) && !state.equals(_state))) {
			if (!XSS_ALLOW_STATE) {
				state = Xss.strip(state);
			}

			_state = state;
			setModified(true);
		}
	}

	public String getZip() {
		return _zip;
	}

	public void setZip(String zip) {
		if (((zip == null) && (_zip != null)) ||
				((zip != null) && (_zip == null)) ||
				((zip != null) && (_zip != null) && !zip.equals(_zip))) {
			if (!XSS_ALLOW_ZIP) {
				zip = Xss.strip(zip);
			}

			_zip = zip;
			setModified(true);
		}
	}

	public String getPhone() {
		return _phone;
	}

	public void setPhone(String phone) {
		if (((phone == null) && (_phone != null)) ||
				((phone != null) && (_phone == null)) ||
				((phone != null) && (_phone != null) && !phone.equals(_phone))) {
			if (!XSS_ALLOW_PHONE) {
				phone = Xss.strip(phone);
			}

			_phone = phone;
			setModified(true);
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
			setModified(true);
		}
	}

	public String getRecurrence() {
		return _recurrence;
	}

	public void setRecurrence(String recurrence) {
		if (((recurrence == null) && (_recurrence != null)) ||
				((recurrence != null) && (_recurrence == null)) ||
				((recurrence != null) && (_recurrence != null) &&
				!recurrence.equals(_recurrence))) {
			if (!XSS_ALLOW_RECURRENCE) {
				recurrence = Xss.strip(recurrence);
			}

			_recurrence = recurrence;
			setModified(true);
		}
	}

	public String getRemindBy() {
		return _remindBy;
	}

	public void setRemindBy(String remindBy) {
		if (((remindBy == null) && (_remindBy != null)) ||
				((remindBy != null) && (_remindBy == null)) ||
				((remindBy != null) && (_remindBy != null) &&
				!remindBy.equals(_remindBy))) {
			if (!XSS_ALLOW_REMINDBY) {
				remindBy = Xss.strip(remindBy);
			}

			_remindBy = remindBy;
			setModified(true);
		}
	}

	public int getFirstReminder() {
		return _firstReminder;
	}

	public void setFirstReminder(int firstReminder) {
		if (firstReminder != _firstReminder) {
			_firstReminder = firstReminder;
			setModified(true);
		}
	}

	public int getSecondReminder() {
		return _secondReminder;
	}

	public void setSecondReminder(int secondReminder) {
		if (secondReminder != _secondReminder) {
			_secondReminder = secondReminder;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new CalEvent(getEventId(), getGroupId(), getCompanyId(),
			getUserId(), getUserName(), getCreateDate(), getModifiedDate(),
			getTitle(), getDescription(), getStartDate(), getEndDate(),
			getDurationHour(), getDurationMinute(), getAllDay(),
			getTimeZoneSensitive(), getType(), getLocation(), getStreet(),
			getCity(), getState(), getZip(), getPhone(), getRepeating(),
			getRecurrence(), getRemindBy(), getFirstReminder(),
			getSecondReminder());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		CalEvent calEvent = (CalEvent)obj;
		int value = 0;
		value = getStartDate().compareTo(calEvent.getStartDate());

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

		CalEvent calEvent = null;

		try {
			calEvent = (CalEvent)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = calEvent.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _eventId;
	private String _groupId;
	private String _companyId;
	private String _userId;
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
	private String _location;
	private String _street;
	private String _city;
	private String _state;
	private String _zip;
	private String _phone;
	private boolean _repeating;
	private String _recurrence;
	private String _remindBy;
	private int _firstReminder;
	private int _secondReminder;
}