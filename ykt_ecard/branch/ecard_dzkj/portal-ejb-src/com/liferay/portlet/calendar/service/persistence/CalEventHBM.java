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

package com.liferay.portlet.calendar.service.persistence;

import java.util.Date;

/**
 * <a href="CalEventHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventHBM {
	protected CalEventHBM() {
	}

	protected CalEventHBM(String eventId) {
		_eventId = eventId;
	}

	protected CalEventHBM(String eventId, String groupId, String companyId,
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

	protected void setPrimaryKey(String pk) {
		_eventId = pk;
	}

	protected String getEventId() {
		return _eventId;
	}

	protected void setEventId(String eventId) {
		_eventId = eventId;
	}

	protected String getGroupId() {
		return _groupId;
	}

	protected void setGroupId(String groupId) {
		_groupId = groupId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
	}

	protected String getUserName() {
		return _userName;
	}

	protected void setUserName(String userName) {
		_userName = userName;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getTitle() {
		return _title;
	}

	protected void setTitle(String title) {
		_title = title;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected Date getStartDate() {
		return _startDate;
	}

	protected void setStartDate(Date startDate) {
		_startDate = startDate;
	}

	protected Date getEndDate() {
		return _endDate;
	}

	protected void setEndDate(Date endDate) {
		_endDate = endDate;
	}

	protected int getDurationHour() {
		return _durationHour;
	}

	protected void setDurationHour(int durationHour) {
		_durationHour = durationHour;
	}

	protected int getDurationMinute() {
		return _durationMinute;
	}

	protected void setDurationMinute(int durationMinute) {
		_durationMinute = durationMinute;
	}

	protected boolean getAllDay() {
		return _allDay;
	}

	protected void setAllDay(boolean allDay) {
		_allDay = allDay;
	}

	protected boolean getTimeZoneSensitive() {
		return _timeZoneSensitive;
	}

	protected void setTimeZoneSensitive(boolean timeZoneSensitive) {
		_timeZoneSensitive = timeZoneSensitive;
	}

	protected String getType() {
		return _type;
	}

	protected void setType(String type) {
		_type = type;
	}

	protected String getLocation() {
		return _location;
	}

	protected void setLocation(String location) {
		_location = location;
	}

	protected String getStreet() {
		return _street;
	}

	protected void setStreet(String street) {
		_street = street;
	}

	protected String getCity() {
		return _city;
	}

	protected void setCity(String city) {
		_city = city;
	}

	protected String getState() {
		return _state;
	}

	protected void setState(String state) {
		_state = state;
	}

	protected String getZip() {
		return _zip;
	}

	protected void setZip(String zip) {
		_zip = zip;
	}

	protected String getPhone() {
		return _phone;
	}

	protected void setPhone(String phone) {
		_phone = phone;
	}

	protected boolean getRepeating() {
		return _repeating;
	}

	protected void setRepeating(boolean repeating) {
		_repeating = repeating;
	}

	protected String getRecurrence() {
		return _recurrence;
	}

	protected void setRecurrence(String recurrence) {
		_recurrence = recurrence;
	}

	protected String getRemindBy() {
		return _remindBy;
	}

	protected void setRemindBy(String remindBy) {
		_remindBy = remindBy;
	}

	protected int getFirstReminder() {
		return _firstReminder;
	}

	protected void setFirstReminder(int firstReminder) {
		_firstReminder = firstReminder;
	}

	protected int getSecondReminder() {
		return _secondReminder;
	}

	protected void setSecondReminder(int secondReminder) {
		_secondReminder = secondReminder;
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