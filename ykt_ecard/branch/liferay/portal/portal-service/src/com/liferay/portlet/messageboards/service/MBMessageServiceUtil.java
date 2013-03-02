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

package com.liferay.portlet.messageboards.service;


/**
 * <a href="MBMessageServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides static methods for the
 * <code>com.liferay.portlet.messageboards.service.MBMessageService</code>
 * bean. The static methods of this class calls the same methods of the bean
 * instance. It's convenient to be able to just write one line to call a method
 * on a bean instead of writing a lookup call and a method call.
 * </p>
 *
 * <p>
 * <code>com.liferay.portlet.messageboards.service.MBMessageServiceFactory</code>
 * is responsible for the lookup of the bean.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBMessageService
 * @see com.liferay.portlet.messageboards.service.MBMessageServiceFactory
 *
 */
public class MBMessageServiceUtil {
	public static com.liferay.portlet.messageboards.model.MBMessage addDiscussionMessage(
		long groupId, java.lang.String className, long classPK, long threadId,
		long parentMessageId, java.lang.String subject, java.lang.String body,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addDiscussionMessage(groupId, className,
			classPK, threadId, parentMessageId, subject, body, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, subject, body, files,
			anonymous, priority, tagsEntries, addCommunityPermissions,
			addGuestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, subject, body, files,
			anonymous, priority, tagsEntries, communityPermissions,
			guestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, javax.portlet.PortletPreferences prefs,
		boolean addCommunityPermissions, boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, subject, body, files,
			anonymous, priority, tagsEntries, prefs, addCommunityPermissions,
			addGuestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, javax.portlet.PortletPreferences prefs,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, subject, body, files,
			anonymous, priority, tagsEntries, prefs, communityPermissions,
			guestPermissions, themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, threadId,
			parentMessageId, subject, body, files, anonymous, priority,
			tagsEntries, addCommunityPermissions, addGuestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, threadId,
			parentMessageId, subject, body, files, anonymous, priority,
			tagsEntries, communityPermissions, guestPermissions);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		boolean addCommunityPermissions, boolean addGuestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, threadId,
			parentMessageId, subject, body, files, anonymous, priority,
			tagsEntries, prefs, addCommunityPermissions, addGuestPermissions,
			themeDisplay);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage addMessage(
		long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.addMessage(categoryId, threadId,
			parentMessageId, subject, body, files, anonymous, priority,
			tagsEntries, prefs, communityPermissions, guestPermissions,
			themeDisplay);
	}

	public static void deleteDiscussionMessage(long groupId,
		java.lang.String className, long classPK, long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		mbMessageService.deleteDiscussionMessage(groupId, className, classPK,
			messageId);
	}

	public static void deleteMessage(long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		mbMessageService.deleteMessage(messageId);
	}

	public static java.util.List getCategoryMessages(long categoryId,
		int begin, int end)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getCategoryMessages(categoryId, begin, end);
	}

	public static int getCategoryMessagesCount(long categoryId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getCategoryMessagesCount(categoryId);
	}

	public static java.lang.String getCategoryMessagesRSS(long categoryId,
		int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getCategoryMessagesRSS(categoryId, max, type,
			version, displayStyle, feedURL, entryURL);
	}

	public static java.lang.String getCompanyMessagesRSS(long companyId,
		int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getCompanyMessagesRSS(companyId, max, type,
			version, displayStyle, feedURL, entryURL);
	}

	public static java.lang.String getGroupMessagesRSS(long groupId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getGroupMessagesRSS(groupId, max, type,
			version, displayStyle, feedURL, entryURL);
	}

	public static java.lang.String getGroupMessagesRSS(long groupId,
		long userId, int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getGroupMessagesRSS(groupId, userId, max, type,
			version, displayStyle, feedURL, entryURL);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage getMessage(
		long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getMessage(messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getMessageDisplay(messageId);
	}

	public static java.lang.String getThreadMessagesRSS(long threadId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.getThreadMessagesRSS(threadId, max, type,
			version, displayStyle, feedURL, entryURL);
	}

	public static void subscribeMessage(long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		mbMessageService.subscribeMessage(messageId);
	}

	public static void unsubscribeMessage(long messageId)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		mbMessageService.unsubscribeMessage(messageId);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateDiscussionMessage(
		long groupId, java.lang.String className, long classPK, long messageId,
		java.lang.String subject, java.lang.String body)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.updateDiscussionMessage(groupId, className,
			classPK, messageId, subject, body);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateMessage(
		long messageId, java.lang.String subject, java.lang.String body,
		java.util.List files, double priority, java.lang.String[] tagsEntries)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.updateMessage(messageId, subject, body, files,
			priority, tagsEntries);
	}

	public static com.liferay.portlet.messageboards.model.MBMessage updateMessage(
		long messageId, java.lang.String subject, java.lang.String body,
		java.util.List files, double priority, java.lang.String[] tagsEntries,
		javax.portlet.PortletPreferences prefs,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException, java.rmi.RemoteException {
		MBMessageService mbMessageService = MBMessageServiceFactory.getService();

		return mbMessageService.updateMessage(messageId, subject, body, files,
			priority, tagsEntries, prefs, themeDisplay);
	}
}