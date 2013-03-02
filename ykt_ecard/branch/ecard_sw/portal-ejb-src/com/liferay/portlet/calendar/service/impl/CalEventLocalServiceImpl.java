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

package com.liferay.portlet.calendar.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.im.AIMConnector;
import com.liferay.portal.im.ICQConnector;
import com.liferay.portal.im.MSNConnector;
import com.liferay.portal.im.YMConnector;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.CompanyServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portlet.calendar.NoSuchEventException;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.service.persistence.CalEventFinder;
import com.liferay.portlet.calendar.service.persistence.CalEventUtil;
import com.liferay.portlet.calendar.service.spring.CalEventLocalService;
import com.liferay.util.Base64;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Time;
import com.liferay.util.Validator;
import com.liferay.util.cal.Duration;
import com.liferay.util.cal.Recurrence;
import com.liferay.util.mail.MailMessage;

import java.text.DateFormat;

import java.util.Calendar;
import java.util.GregorianCalendar;
import java.util.Iterator;

import javax.mail.internet.InternetAddress;

/**
 * <a href="CalEventLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class CalEventLocalServiceImpl implements CalEventLocalService {

	// Business methods

	public void checkReminders() throws PortalException, SystemException {
		Iterator itr = CalEventFinder.findByRemindBy().iterator();

		while (itr.hasNext()) {
			CalEvent event = (CalEvent)itr.next();

			User user = UserLocalServiceUtil.getUserById(event.getUserId());

			Calendar now = new GregorianCalendar(
				user.getTimeZone(), user.getLocale());
			if (!event.isTimeZoneSensitive()) {
				Calendar temp = new GregorianCalendar();
				temp.setTime(Time.getDate(now));
				now = temp;
			}

			Calendar startCal = null;
			if (event.isTimeZoneSensitive()) {
				startCal = new GregorianCalendar(
					user.getTimeZone(), user.getLocale());
			}
			else {
				startCal = new GregorianCalendar();
			}
			startCal.setTime(event.getStartDate());

			long diff =
				(startCal.getTime().getTime() - now.getTime().getTime()) /
				Time.MINUTE;

			if ((diff == (event.getFirstReminder() / Time.MINUTE)) ||
				(diff == (event.getSecondReminder() / Time.MINUTE))) {

				_remindUser(event, user);
			}
		}
	}

	public void checkSystemEvents(String companyId)
		throws PortalException, SystemException {

		// Delete birthdays

		CalEventUtil.removeByC_U_T(
			companyId, User.getDefaultUserId(companyId), CalEvent.BIRTHDAY);

		// Add birthdays

		/*Iterator itr = CompanyLocalServiceUtil.getUsers(companyId).iterator();

		while (itr.hasNext()) {
			User user = (User)itr.next();

			updateBirthday(user.getUserId());
		}*/
	}

	public void deleteAllByGroup(String groupId)
		throws PortalException, SystemException {

		CalEventUtil.removeByGroupId(groupId);

		CalEventLocalUtil.clearEventsPool(groupId);
	}

	public void deleteAllByUser(String userId)
		throws PortalException, SystemException {

		CalEventUtil.removeByG_U(Group.DEFAULT_PARENT_GROUP_ID, userId);

		deleteBirthday(userId);

		CalEventLocalUtil.clearEventsPool(userId);
	}

	public void deleteBirthday(String userId)
		throws PortalException, SystemException {

		User user = UserLocalServiceUtil.getUserById(userId);

		String defaultUserId = User.getDefaultUserId(user.getCompanyId());
		String description = userId;

		try {
			CalEvent event = CalEventUtil.findByC_U_D_T(
				user.getCompanyId(), defaultUserId, description,
				CalEvent.BIRTHDAY);

			CalEventUtil.remove(event.getEventId());

			CalEventLocalUtil.clearEventsPool(event.getGroupId());
		}
		catch (NoSuchEventException nsee) {
		}
	}

	public void deleteEvent(String eventId)
		throws PortalException, SystemException {

		CalEvent event = CalEventUtil.findByPrimaryKey(eventId);

		CalEventUtil.remove(eventId);

		if (event.isGroupEvent()) {
			CalEventLocalUtil.clearEventsPool(event.getGroupId());
		}
		else {
			CalEventLocalUtil.clearEventsPool(event.getUserId());
		}
	}

	public CalEvent updateBirthday(String userId)
		throws PortalException, SystemException {

		// Temporarily disable auto updating of birthdays

		if (true) {
			return null;
		}

		User user = UserLocalServiceUtil.getUserById(userId);

		CalEvent event = null;

		String defaultUserId = User.getDefaultUserId(user.getCompanyId());
		String title = user.getFullName() + "'s Birthday";
		String description = userId;

		Calendar createDate = new GregorianCalendar(1970, 1, 1);

		try {
			event = CalEventUtil.findByC_U_D_T(
				user.getCompanyId(), defaultUserId, description,
				CalEvent.BIRTHDAY);
		}
		catch (NoSuchEventException nsee) {
			String eventId = Long.toString(CounterServiceUtil.increment(
				CalEvent.class.getName()));

			event = CalEventUtil.create(eventId);

			event.setCreateDate(createDate.getTime());
		}

		Calendar birthday = new GregorianCalendar();
		birthday.setTime(user.getBirthday());
		birthday.set(Calendar.HOUR_OF_DAY, 0);
		birthday.set(Calendar.MINUTE, 0);
		birthday.set(Calendar.SECOND, 0);
		birthday.set(Calendar.MILLISECOND, 0);

		Recurrence recurrence = new Recurrence(
			birthday, new Duration(1, 0, 0, 0), Recurrence.YEARLY);

		event.setGroupId(user.getCompanyId());
		event.setCompanyId(user.getCompanyId());
		event.setUserId(defaultUserId);
		event.setUserName(user.getFullName());
		event.setModifiedDate(createDate.getTime());
		event.setTitle(title);
		event.setDescription(description);
		event.setStartDate(birthday.getTime());
		event.setDurationHour(24);
		event.setDurationMinute(0);
		event.setAllDay(true);
		event.setTimeZoneSensitive(false);
		event.setType(CalEvent.BIRTHDAY);
		event.setRepeating(true);
		event.setRecurrence(Base64.objectToString(recurrence));
		event.setRemindBy(CalEvent.REMIND_BY_NONE);

		CalEventUtil.update(event);

		CalEventLocalUtil.clearEventsPool(event.getGroupId());

		return event;
	}

	// Private methods

	private void _remindUser(CalEvent event, User user) {
		String remindBy = GetterUtil.getString(event.getRemindBy());

		if (remindBy.equals(CalEvent.REMIND_BY_NONE)) {
			return;
		}

		try {
			Company company =
				CompanyServiceUtil.getCompany(user.getCompanyId());

			String emailSubject =
				company.getName() + " Calendar Event Reminder";

			DateFormat dateFormat = DateFormat.getDateTimeInstance(
				DateFormat.LONG, DateFormat.LONG, user.getLocale());
			dateFormat.setTimeZone(user.getTimeZone());

			String emailBody = ContentUtil.get(
				"content/en_US/calendar_event_reminder.tmpl");
			emailBody = StringUtil.replace(
				emailBody,
				new String[] {"[$USER_NAME$]",
							  "[$ADMIN_NAME$]", "[$ADMIN_EMAIL_ADDRESS$]",
							  "[$COMPANY_NAME$]",
							  "[$EVENT_TITLE$]",
							  "[$EVENT_START_DATE$]"},
				new String[] {user.getFullName(),
							  company.getAdminName(), company.getEmailAddress(),
							  company.getShortName(),
							  event.getTitle(),
							  dateFormat.format(event.getStartDate())});

			InternetAddress emailTo = null;

			if (remindBy.equals(CalEvent.REMIND_BY_EMAIL)) {
				emailTo = new InternetAddress(
					user.getEmailAddress(), user.getFullName());
			}
			else if (remindBy.equals(CalEvent.REMIND_BY_SMS)) {
				emailTo = new InternetAddress(
					user.getSmsId(), user.getFullName());
			}

			if (emailTo != null) {
				MailServiceUtil.sendEmail(new MailMessage(
					new InternetAddress(
						company.getEmailAddress(), company.getAdminName()),
					emailTo, emailSubject, emailBody));
			}

			if (remindBy.equals(CalEvent.REMIND_BY_AIM) &&
				Validator.isNotNull(user.getAimId())) {

				AIMConnector.send(user.getAimId(), emailBody);
			}
			else if (remindBy.equals(CalEvent.REMIND_BY_ICQ) &&
					 Validator.isNotNull(user.getIcqId())) {

				ICQConnector.send(user.getIcqId(), emailBody);
			}
			else if (remindBy.equals(CalEvent.REMIND_BY_MSN) &&
					 Validator.isNotNull(user.getMsnId())) {

				MSNConnector.send(user.getMsnId(), emailBody);
			}
			else if (remindBy.equals(CalEvent.REMIND_BY_YM) &&
					 Validator.isNotNull(user.getYmId())) {

				YMConnector.send(user.getYmId(), emailBody);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}