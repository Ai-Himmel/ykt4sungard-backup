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

import com.liferay.portal.model.Group;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.Base64;
import com.liferay.util.Time;
import com.liferay.util.cal.Recurrence;

import java.util.Date;

/**
 * <a href="CalEvent.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.19 $
 *
 */
public class CalEvent extends CalEventModel {

	public static final String[] TYPES =
		PropsUtil.getArray(PropsUtil.CALENDAR_EVENT_TYPES);

	public static final String BIRTHDAY = "birthday";

	public static final String REMIND_BY_NONE = "none";

	public static final String REMIND_BY_EMAIL = "email";

	public static final String REMIND_BY_SMS = "sms";

	public static final String REMIND_BY_AIM = "aim";

	public static final String REMIND_BY_ICQ = "icq";

	public static final String REMIND_BY_MSN = "msn";

	public static final String REMIND_BY_YM = "ym";

	public static final long[] REMINDERS = {
		Time.MINUTE * 5, Time.MINUTE * 15, Time.MINUTE * 30, Time.HOUR,
		Time.HOUR * 2, Time.HOUR * 3, Time.HOUR * 6, Time.HOUR * 12, Time.DAY,
		Time.DAY * 2, Time.DAY * 3, Time.DAY * 4, Time.DAY * 5, Time.DAY * 6,
		Time.DAY * 7, Time.DAY * 8, Time.DAY * 9, Time.DAY * 10, Time.DAY * 11,
		Time.DAY * 12, Time.DAY * 13, Time.DAY * 14
	};

	public CalEvent() {
		super();
	}

	public CalEvent(String eventId) {
		super(eventId);
	}

	public CalEvent(String eventId, String groupId, String companyId,
					String userId, String userName, Date createDate,
					Date modifiedDate, String title, String description,
					Date startDate, Date endDate, int durationHour,
					int durationMinute, boolean allDay,
					boolean timeZoneSensitive, String type, String location,
					String street, String city, String state, String zip,
					String phone, boolean repeating, String recurrence,
					String remindBy, int firstReminder, int secondReminder) {

		super(eventId, groupId, companyId, userId, userName, createDate,
			  modifiedDate, title, description, startDate, endDate,
			  durationHour, durationMinute, allDay, timeZoneSensitive, type,
			  location, street, city, state, zip, phone, repeating, recurrence,
			  remindBy, firstReminder, secondReminder);

		setRecurrence(recurrence);
	}

	public boolean isGroupEvent() {
		if (getGroupId().equals(Group.DEFAULT_PARENT_GROUP_ID)) {
			return false;
		}
		else {
			return true;
		}
	}

	public boolean isSystemEvent() {
		if (getGroupId().equals(getCompanyId())) {
			return true;
		}
		else {
			return false;
		}
	}

	public void setRecurrence(String recurrence) {
		_recurrenceObj = (Recurrence)Base64.stringToObject(recurrence);

		super.setRecurrence(recurrence);
	}

	public Recurrence getRecurrenceObj() {
		return _recurrenceObj;
	}

	public void setRecurrenceObj(Recurrence recurrenceObj) {
		_recurrenceObj = recurrenceObj;

		super.setRecurrence(Base64.objectToString(recurrenceObj));
	}

	private Recurrence _recurrenceObj = null;

}