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

package com.liferay.portlet.calendar.service;


/**
 * <a href="CalEventLocalServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.calendar.service.CalEventLocalService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.calendar.service.CalEventLocalServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.calendar.service.CalEventLocalService
 * @see com.liferay.portlet.calendar.service.CalEventLocalServiceFactory
 *
 */
public class CalEventLocalServiceUtil {
	public static com.liferay.portlet.calendar.model.CalEvent addCalEvent(
		com.liferay.portlet.calendar.model.CalEvent model)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.addCalEvent(model);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.dynamicQuery(queryInitializer);
	}

	public static java.util.List dynamicQuery(
		com.liferay.portal.kernel.dao.DynamicQueryInitializer queryInitializer,
		int begin, int end) throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.dynamicQuery(queryInitializer, begin, end);
	}

	public static com.liferay.portlet.calendar.model.CalEvent updateCalEvent(
		com.liferay.portlet.calendar.model.CalEvent model)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.updateCalEvent(model);
	}

	public static com.liferay.portlet.calendar.service.persistence.CalEventPersistence getCalEventPersistence() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getCalEventPersistence();
	}

	public static void setCalEventPersistence(
		com.liferay.portlet.calendar.service.persistence.CalEventPersistence calEventPersistence) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setCalEventPersistence(calEventPersistence);
	}

	public static com.liferay.portlet.calendar.service.persistence.CalEventFinder getCalEventFinder() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getCalEventFinder();
	}

	public static void setCalEventFinder(
		com.liferay.portlet.calendar.service.persistence.CalEventFinder calEventFinder) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setCalEventFinder(calEventFinder);
	}

	public static com.liferay.portal.service.persistence.CompanyPersistence getCompanyPersistence() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getCompanyPersistence();
	}

	public static void setCompanyPersistence(
		com.liferay.portal.service.persistence.CompanyPersistence companyPersistence) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setCompanyPersistence(companyPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesPersistence getPortletPreferencesPersistence() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getPortletPreferencesPersistence();
	}

	public static void setPortletPreferencesPersistence(
		com.liferay.portal.service.persistence.PortletPreferencesPersistence portletPreferencesPersistence) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setPortletPreferencesPersistence(portletPreferencesPersistence);
	}

	public static com.liferay.portal.service.persistence.PortletPreferencesFinder getPortletPreferencesFinder() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getPortletPreferencesFinder();
	}

	public static void setPortletPreferencesFinder(
		com.liferay.portal.service.persistence.PortletPreferencesFinder portletPreferencesFinder) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setPortletPreferencesFinder(portletPreferencesFinder);
	}

	public static com.liferay.portal.service.persistence.ResourcePersistence getResourcePersistence() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getResourcePersistence();
	}

	public static void setResourcePersistence(
		com.liferay.portal.service.persistence.ResourcePersistence resourcePersistence) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setResourcePersistence(resourcePersistence);
	}

	public static com.liferay.portal.service.persistence.ResourceFinder getResourceFinder() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getResourceFinder();
	}

	public static void setResourceFinder(
		com.liferay.portal.service.persistence.ResourceFinder resourceFinder) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setResourceFinder(resourceFinder);
	}

	public static com.liferay.portal.service.persistence.UserPersistence getUserPersistence() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getUserPersistence();
	}

	public static void setUserPersistence(
		com.liferay.portal.service.persistence.UserPersistence userPersistence) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setUserPersistence(userPersistence);
	}

	public static com.liferay.portal.service.persistence.UserFinder getUserFinder() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getUserFinder();
	}

	public static void setUserFinder(
		com.liferay.portal.service.persistence.UserFinder userFinder) {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.setUserFinder(userFinder);
	}

	public static void afterPropertiesSet() {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.afterPropertiesSet();
	}

	public static com.liferay.portlet.calendar.model.CalEvent addEvent(
		long userId, long plid, java.lang.String title,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, boolean repeating,
		com.liferay.portal.kernel.cal.Recurrence recurrence,
		java.lang.String remindBy, int firstReminder, int secondReminder,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.addEvent(userId, plid, title, description,
			startDateMonth, startDateDay, startDateYear, startDateHour,
			startDateMinute, endDateMonth, endDateDay, endDateYear,
			durationHour, durationMinute, allDay, timeZoneSensitive, type,
			repeating, recurrence, remindBy, firstReminder, secondReminder,
			addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.calendar.model.CalEvent addEvent(
		java.lang.String uuid, long userId, long plid, java.lang.String title,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, boolean repeating,
		com.liferay.portal.kernel.cal.Recurrence recurrence,
		java.lang.String remindBy, int firstReminder, int secondReminder,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.addEvent(uuid, userId, plid, title,
			description, startDateMonth, startDateDay, startDateYear,
			startDateHour, startDateMinute, endDateMonth, endDateDay,
			endDateYear, durationHour, durationMinute, allDay,
			timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.calendar.model.CalEvent addEvent(
		long userId, long plid, java.lang.String title,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, boolean repeating,
		com.liferay.portal.kernel.cal.Recurrence recurrence,
		java.lang.String remindBy, int firstReminder, int secondReminder,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.addEvent(userId, plid, title, description,
			startDateMonth, startDateDay, startDateYear, startDateHour,
			startDateMinute, endDateMonth, endDateDay, endDateYear,
			durationHour, durationMinute, allDay, timeZoneSensitive, type,
			repeating, recurrence, remindBy, firstReminder, secondReminder,
			communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.calendar.model.CalEvent addEvent(
		java.lang.String uuid, long userId, long plid, java.lang.String title,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, boolean repeating,
		com.liferay.portal.kernel.cal.Recurrence recurrence,
		java.lang.String remindBy, int firstReminder, int secondReminder,
		java.lang.Boolean addCommunityPermissions,
		java.lang.Boolean addGuestPermissions,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.addEvent(uuid, userId, plid, title,
			description, startDateMonth, startDateDay, startDateYear,
			startDateHour, startDateMinute, endDateMonth, endDateDay,
			endDateYear, durationHour, durationMinute, allDay,
			timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder, addCommunityPermissions,
			addGuestPermissions, communityPermissions, guestPermissions);
	}

	public static void addEventResources(long eventId,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.addEventResources(eventId,
			addCommunityPermissions, addGuestPermissions);
	}

	public static void addEventResources(
		com.liferay.portlet.calendar.model.CalEvent event,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.addEventResources(event, addCommunityPermissions,
			addGuestPermissions);
	}

	public static void addEventResources(long eventId,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.addEventResources(eventId, communityPermissions,
			guestPermissions);
	}

	public static void addEventResources(
		com.liferay.portlet.calendar.model.CalEvent event,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.addEventResources(event, communityPermissions,
			guestPermissions);
	}

	public static void checkEvents()
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.checkEvents();
	}

	public static void deleteEvent(long eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.deleteEvent(eventId);
	}

	public static void deleteEvent(
		com.liferay.portlet.calendar.model.CalEvent event)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.deleteEvent(event);
	}

	public static void deleteEvents(long groupId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.deleteEvents(groupId);
	}

	public static java.io.File exportEvent(long userId, long eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.exportEvent(userId, eventId);
	}

	public static java.io.File exportGroupEvents(long userId, long plid,
		java.lang.String fileName)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.exportGroupEvents(userId, plid, fileName);
	}

	public static com.liferay.portlet.calendar.model.CalEvent getEvent(
		long eventId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getEvent(eventId);
	}

	public static java.util.List getEvents(long groupId, java.lang.String type,
		int begin, int end) throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getEvents(groupId, type, begin, end);
	}

	public static java.util.List getEvents(long groupId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getEvents(groupId, cal);
	}

	public static java.util.List getEvents(long groupId,
		java.util.Calendar cal, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getEvents(groupId, cal, type);
	}

	public static int getEventsCount(long groupId, java.lang.String type)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getEventsCount(groupId, type);
	}

	public static java.util.List getRepeatingEvents(long groupId)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.getRepeatingEvents(groupId);
	}

	public static boolean hasEvents(long groupId, java.util.Calendar cal)
		throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.hasEvents(groupId, cal);
	}

	public static boolean hasEvents(long groupId, java.util.Calendar cal,
		java.lang.String type) throws com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.hasEvents(groupId, cal, type);
	}

	public static void importICal4j(long userId, long plid, java.io.File file)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		calEventLocalService.importICal4j(userId, plid, file);
	}

	public static com.liferay.portlet.calendar.model.CalEvent updateEvent(
		long userId, long eventId, java.lang.String title,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int durationHour,
		int durationMinute, boolean allDay, boolean timeZoneSensitive,
		java.lang.String type, boolean repeating,
		com.liferay.portal.kernel.cal.Recurrence recurrence,
		java.lang.String remindBy, int firstReminder, int secondReminder)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		CalEventLocalService calEventLocalService = CalEventLocalServiceFactory.getService();

		return calEventLocalService.updateEvent(userId, eventId, title,
			description, startDateMonth, startDateDay, startDateYear,
			startDateHour, startDateMinute, endDateMonth, endDateDay,
			endDateYear, durationHour, durationMinute, allDay,
			timeZoneSensitive, type, repeating, recurrence, remindBy,
			firstReminder, secondReminder);
	}
}