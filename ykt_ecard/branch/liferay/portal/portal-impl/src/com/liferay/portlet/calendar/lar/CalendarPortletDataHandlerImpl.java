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

package com.liferay.portlet.calendar.lar;

import com.liferay.portal.kernel.lar.PortletDataContext;
import com.liferay.portal.kernel.lar.PortletDataException;
import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.lar.PortletDataHandlerBoolean;
import com.liferay.portal.kernel.lar.PortletDataHandlerControl;
import com.liferay.portal.kernel.lar.PortletDataHandlerKeys;
import com.liferay.portal.kernel.util.CalendarFactoryUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.portlet.calendar.service.CalEventLocalServiceUtil;
import com.liferay.portlet.calendar.service.persistence.CalEventUtil;

import com.thoughtworks.xstream.XStream;

import java.util.Calendar;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.portlet.PortletPreferences;

import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

/**
 * <a href="CalendarPortletDataHandlerImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Bruno Farache
 *
 */
public class CalendarPortletDataHandlerImpl implements PortletDataHandler {

	public PortletPreferences deleteData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {

			// Events

			if (!context.addPrimaryKey(
					CalendarPortletDataHandlerImpl.class, "deleteData")) {

				CalEventLocalServiceUtil.deleteEvents(context.getGroupId());
			}
			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public String exportData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = DocumentHelper.createDocument();

			Element root = doc.addElement("calendar-data");

			root.addAttribute("group-id", String.valueOf(context.getGroupId()));

			// Events

			List events = CalEventUtil.findByGroupId(context.getGroupId());

			Iterator itr = events.iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent) itr.next();

				if (context.addPrimaryKey(
						CalEvent.class, event.getPrimaryKeyObj())) {

					itr.remove();
				}
				else {
					event.setUserUuid(event.getUserUuid());
				}
			}

			String xml = xStream.toXML(events);

			Element el = root.addElement("calendar-events");

			Document tempDoc = PortalUtil.readDocumentFromXML(xml);

			el.content().add(tempDoc.getRootElement().createCopy());

			return doc.asXML();
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	public PortletDataHandlerControl[] getExportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_events};
	}

	public PortletDataHandlerControl[] getImportControls()
		throws PortletDataException {

		return new PortletDataHandlerControl[] {_events};
	}

	public PortletPreferences importData(
			PortletDataContext context, String portletId,
			PortletPreferences prefs, String data)
		throws PortletDataException {

		try {
			XStream xStream = new XStream();

			Document doc = PortalUtil.readDocumentFromXML(data);

			Element root = doc.getRootElement();

			// Events

			Element el = root.element("calendar-events").element("list");

			Document tempDoc = DocumentHelper.createDocument();

			tempDoc.content().add(el.createCopy());

			List events = (List) xStream.fromXML(tempDoc.asXML());

			Iterator itr = events.iterator();

			while (itr.hasNext()) {
				CalEvent event = (CalEvent) itr.next();

				importEvent(context, event);
			}

			return null;
		}
		catch (Exception e) {
			throw new PortletDataException(e);
		}
	}

	protected void importEvent(PortletDataContext context, CalEvent event)
		throws Exception {

		long userId = context.getUserId(event.getUserUuid());
		long plid = context.getPlid();

		Date startDate = event.getStartDate();

		int startDateMonth = 0;
		int startDateDay = 0;
		int startDateYear = 0;
		int startDateHour = 0;
		int startDateMinute = 0;

		if (startDate != null) {
			Calendar startCal = CalendarFactoryUtil.getCalendar();

			startCal.setTime(startDate);

			startDateMonth = startCal.get(Calendar.MONTH);
			startDateDay = startCal.get(Calendar.DATE);
			startDateYear = startCal.get(Calendar.YEAR);
			startDateHour = startCal.get(Calendar.HOUR);
			startDateMinute = startCal.get(Calendar.MINUTE);
		}

		Date endDate = event.getEndDate();

		int endDateMonth = 0;
		int endDateDay = 0;
		int endDateYear = 0;

		if (endDate != null) {
			Calendar endCal = CalendarFactoryUtil.getCalendar();

			endCal.setTime(endDate);

			endDateMonth = endCal.get(Calendar.MONTH);
			endDateDay = endCal.get(Calendar.DATE);
			endDateYear = endCal.get(Calendar.YEAR);
		}

		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		CalEvent existingEvent = null;

		if (context.getDataStrategy().equals(
				PortletDataHandlerKeys.DATA_STRATEGY_MIRROR)) {

			existingEvent = CalEventUtil.fetchByUUID_G(
				event.getUuid(), context.getGroupId());

			if (existingEvent == null) {
				CalEventLocalServiceUtil.addEvent(
					event.getUuid(), userId, plid, event.getTitle(),
					event.getDescription(), startDateMonth, startDateDay,
					startDateYear, startDateHour, startDateMinute, endDateMonth,
					endDateDay, endDateYear, event.getDurationHour(),
					event.getDurationMinute(), event.getAllDay(),
					event.getTimeZoneSensitive(), event.getType(),
					event.getRepeating(), event.getRecurrenceObj(),
					event.getRemindBy(), event.getFirstReminder(),
					event.getSecondReminder(), addCommunityPermissions,
					addGuestPermissions);
			}
			else {
				CalEventLocalServiceUtil.updateEvent(
					userId, existingEvent.getEventId(), event.getTitle(),
					event.getDescription(), startDateMonth, startDateDay,
					startDateYear, startDateHour, startDateMinute, endDateMonth,
					endDateDay, endDateYear, event.getDurationHour(),
					event.getDurationMinute(), event.getAllDay(),
					event.getTimeZoneSensitive(), event.getType(),
					event.getRepeating(), event.getRecurrenceObj(),
					event.getRemindBy(), event.getFirstReminder(),
					event.getSecondReminder());
			}
		}
		else {
			CalEventLocalServiceUtil.addEvent(
				userId, plid, event.getTitle(), event.getDescription(),
				startDateMonth, startDateDay, startDateYear, startDateHour,
				startDateMinute, endDateMonth, endDateDay, endDateYear,
				event.getDurationHour(), event.getDurationMinute(),
				event.getAllDay(), event.getTimeZoneSensitive(),
				event.getType(), event.getRepeating(), event.getRecurrenceObj(),
				event.getRemindBy(), event.getFirstReminder(),
				event.getSecondReminder(), addCommunityPermissions,
				addGuestPermissions);
		}
	}

	private static final String _NAMESPACE = "calendar";

	private static final PortletDataHandlerBoolean _events =
		new PortletDataHandlerBoolean(_NAMESPACE, "events", true, true);

}