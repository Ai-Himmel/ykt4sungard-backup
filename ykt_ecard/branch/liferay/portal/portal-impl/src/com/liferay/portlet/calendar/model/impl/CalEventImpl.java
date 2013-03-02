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

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.cal.DayAndPosition;
import com.liferay.portal.kernel.cal.Duration;
import com.liferay.portal.kernel.cal.Recurrence;
import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.util.Time;

/**
 * <a href="CalEventImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalEventImpl extends CalEventModelImpl implements CalEvent {

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

	public CalEventImpl() {
	}

	public String getUserUuid() throws SystemException {
		return PortalUtil.getUserValue(getUserId(), "uuid", _userUuid);
	}

	public void setUserUuid(String userUuid) {
		_userUuid = userUuid;
	}

	public void setRecurrence(String recurrence) {
		_recurrenceObj = null;

		super.setRecurrence(recurrence);
	}

	/**
	 * @deprecated
	 */
	public Recurrence getRecurrenceObj() {
		if (_recurrenceObj == null) {
			String recurrence = getRecurrence();

			if (Validator.isNotNull(recurrence)) {
				Object obj = Base64.stringToObject(recurrence);

				if (obj instanceof Recurrence) {
					_recurrenceObj = (Recurrence)obj;
				}
				else if (obj instanceof com.liferay.util.cal.Recurrence) {
					com.liferay.util.cal.Recurrence oldRecurrence =
						(com.liferay.util.cal.Recurrence)obj;

					com.liferay.util.cal.Duration oldDuration =
						oldRecurrence.getDuration();

					Duration duration = new Duration(
						oldDuration.getDays(), oldDuration.getHours(),
						oldDuration.getMinutes(), oldDuration.getSeconds());

					duration.setWeeks(oldDuration.getWeeks());
					duration.setInterval(oldDuration.getInterval());

					_recurrenceObj = new Recurrence(
						oldRecurrence.getDtStart(), duration,
						oldRecurrence.getFrequency());

					com.liferay.util.cal.DayAndPosition[] oldDayPos =
						oldRecurrence.getByDay();

					DayAndPosition[] dayPos = null;

					if (oldDayPos != null) {
						dayPos = new DayAndPosition[oldDayPos.length];

						for (int i = 0; i < oldDayPos.length; i++) {
							dayPos[i] = new DayAndPosition(
								oldDayPos[i].getDayOfWeek(),
								oldDayPos[i].getDayPosition());
						}
					}

					_recurrenceObj.setByDay(dayPos);
					_recurrenceObj.setByMonth(oldRecurrence.getByMonth());
					_recurrenceObj.setByMonthDay(oldRecurrence.getByMonthDay());
					_recurrenceObj.setInterval(oldRecurrence.getInterval());
					_recurrenceObj.setOccurrence(oldRecurrence.getOccurrence());
					_recurrenceObj.setWeekStart(oldRecurrence.getWeekStart());
					_recurrenceObj.setUntil(oldRecurrence.getUntil());
				}
			}
		}

		return _recurrenceObj;
	}

	public void setRecurrenceObj(Recurrence recurrenceObj) {
		_recurrenceObj = recurrenceObj;

		super.setRecurrence(Base64.objectToString(recurrenceObj));
	}

	private String _userUuid;
	private Recurrence _recurrenceObj = null;

}