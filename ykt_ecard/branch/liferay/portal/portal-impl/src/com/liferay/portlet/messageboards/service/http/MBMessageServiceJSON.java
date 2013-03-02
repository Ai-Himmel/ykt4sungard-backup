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

package com.liferay.portlet.messageboards.service.http;

import com.liferay.portlet.messageboards.service.MBMessageServiceUtil;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="MBMessageServiceJSON.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a JSON utility for the
 * <code>com.liferay.portlet.messageboards.service.MBMessageServiceUtil</code>
 * service utility. The static methods of this class calls the same methods of
 * the service utility. However, the signatures are different because it is
 * difficult for JSON to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to a <code>org.json.JSONArray</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.messageboards.model.MBMessage</code>,
 * that is translated to a <code>org.json.JSONObject</code>. Methods that JSON
 * cannot safely use are skipped. The logic for the translation is encapsulated
 * in <code>com.liferay.portlet.messageboards.service.http.MBMessageJSONSerializer</code>.
 * </p>
 *
 * <p>
 * This allows you to call the the backend services directly from JavaScript.
 * See <code>portal-web/docroot/html/portlet/tags_admin/unpacked.js</code> for a
 * reference of how that portlet uses the generated JavaScript in
 * <code>portal-web/docroot/html/js/service.js</code> to call the backend
 * services directly from JavaScript.
 * </p>
 *
 * <p>
 * The JSON utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBMessageServiceUtil
 * @see com.liferay.portlet.messageboards.service.http.MBMessageJSONSerializer
 *
 */
public class MBMessageServiceJSON {
	public static JSONObject addMessage(long categoryId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
				subject, body, files, anonymous, priority, tagsEntries,
				addCommunityPermissions, addGuestPermissions);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject addMessage(long categoryId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
				subject, body, files, anonymous, priority, tagsEntries,
				communityPermissions, guestPermissions);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject addMessage(long categoryId, long threadId,
		long parentMessageId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
				threadId, parentMessageId, subject, body, files, anonymous,
				priority, tagsEntries, addCommunityPermissions,
				addGuestPermissions);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject addMessage(long categoryId, long threadId,
		long parentMessageId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
				threadId, parentMessageId, subject, body, files, anonymous,
				priority, tagsEntries, communityPermissions, guestPermissions);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}

	public static void deleteDiscussionMessage(long groupId,
		java.lang.String className, long classPK, long messageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		MBMessageServiceUtil.deleteDiscussionMessage(groupId, className,
			classPK, messageId);
	}

	public static void deleteMessage(long messageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		MBMessageServiceUtil.deleteMessage(messageId);
	}

	public static JSONArray getCategoryMessages(long categoryId, int begin,
		int end)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.util.List returnValue = MBMessageServiceUtil.getCategoryMessages(categoryId,
				begin, end);

		return MBMessageJSONSerializer.toJSONArray(returnValue);
	}

	public static int getCategoryMessagesCount(long categoryId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		int returnValue = MBMessageServiceUtil.getCategoryMessagesCount(categoryId);

		return returnValue;
	}

	public static java.lang.String getCategoryMessagesRSS(long categoryId,
		int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = MBMessageServiceUtil.getCategoryMessagesRSS(categoryId,
				max, type, version, displayStyle, feedURL, entryURL);

		return returnValue;
	}

	public static java.lang.String getCompanyMessagesRSS(long companyId,
		int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = MBMessageServiceUtil.getCompanyMessagesRSS(companyId,
				max, type, version, displayStyle, feedURL, entryURL);

		return returnValue;
	}

	public static java.lang.String getGroupMessagesRSS(long groupId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = MBMessageServiceUtil.getGroupMessagesRSS(groupId,
				max, type, version, displayStyle, feedURL, entryURL);

		return returnValue;
	}

	public static java.lang.String getGroupMessagesRSS(long groupId,
		long userId, int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = MBMessageServiceUtil.getGroupMessagesRSS(groupId,
				userId, max, type, version, displayStyle, feedURL, entryURL);

		return returnValue;
	}

	public static JSONObject getMessage(long messageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.getMessage(messageId);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		long messageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessageDisplay returnValue = MBMessageServiceUtil.getMessageDisplay(messageId);

		return returnValue;
	}

	public static java.lang.String getThreadMessagesRSS(long threadId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		java.lang.String returnValue = MBMessageServiceUtil.getThreadMessagesRSS(threadId,
				max, type, version, displayStyle, feedURL, entryURL);

		return returnValue;
	}

	public static void subscribeMessage(long messageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		MBMessageServiceUtil.subscribeMessage(messageId);
	}

	public static void unsubscribeMessage(long messageId)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		MBMessageServiceUtil.unsubscribeMessage(messageId);
	}

	public static JSONObject updateDiscussionMessage(long groupId,
		java.lang.String className, long classPK, long messageId,
		java.lang.String subject, java.lang.String body)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.updateDiscussionMessage(groupId,
				className, classPK, messageId, subject, body);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}

	public static JSONObject updateMessage(long messageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		double priority, java.lang.String[] tagsEntries)
		throws java.rmi.RemoteException, com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.updateMessage(messageId,
				subject, body, files, priority, tagsEntries);

		return MBMessageJSONSerializer.toJSONObject(returnValue);
	}
}