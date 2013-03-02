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

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import com.liferay.portlet.messageboards.service.MBMessageServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="MBMessageServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.messageboards.service.MBMessageServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.messageboards.model.MBMessageSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.messageboards.model.MBMessage</code>,
 * that is translated to a <code>com.liferay.portlet.messageboards.model.MBMessageSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.messageboards.service.MBMessageServiceUtil
 * @see com.liferay.portlet.messageboards.service.http.MBMessageServiceHttp
 * @see com.liferay.portlet.messageboards.service.model.MBMessageSoap
 *
 */
public class MBMessageServiceSoap {
	public static com.liferay.portlet.messageboards.model.MBMessageSoap addMessage(
		long categoryId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries, boolean addCommunityPermissions,
		boolean addGuestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
					subject, body, files, anonymous, priority, tagsEntries,
					addCommunityPermissions, addGuestPermissions);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap addMessage(
		long categoryId, java.lang.String subject, java.lang.String body,
		java.util.List files, boolean anonymous, double priority,
		java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
					subject, body, files, anonymous, priority, tagsEntries,
					communityPermissions, guestPermissions);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap addMessage(
		long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		boolean addCommunityPermissions, boolean addGuestPermissions)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
					threadId, parentMessageId, subject, body, files, anonymous,
					priority, tagsEntries, addCommunityPermissions,
					addGuestPermissions);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap addMessage(
		long categoryId, long threadId, long parentMessageId,
		java.lang.String subject, java.lang.String body, java.util.List files,
		boolean anonymous, double priority, java.lang.String[] tagsEntries,
		java.lang.String[] communityPermissions,
		java.lang.String[] guestPermissions) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.addMessage(categoryId,
					threadId, parentMessageId, subject, body, files, anonymous,
					priority, tagsEntries, communityPermissions,
					guestPermissions);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteDiscussionMessage(long groupId,
		java.lang.String className, long classPK, long messageId)
		throws RemoteException {
		try {
			MBMessageServiceUtil.deleteDiscussionMessage(groupId, className,
				classPK, messageId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteMessage(long messageId) throws RemoteException {
		try {
			MBMessageServiceUtil.deleteMessage(messageId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap[] getCategoryMessages(
		long categoryId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = MBMessageServiceUtil.getCategoryMessages(categoryId,
					begin, end);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static int getCategoryMessagesCount(long categoryId)
		throws RemoteException {
		try {
			int returnValue = MBMessageServiceUtil.getCategoryMessagesCount(categoryId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getCategoryMessagesRSS(long categoryId,
		int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL) throws RemoteException {
		try {
			java.lang.String returnValue = MBMessageServiceUtil.getCategoryMessagesRSS(categoryId,
					max, type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getCompanyMessagesRSS(long companyId,
		int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL) throws RemoteException {
		try {
			java.lang.String returnValue = MBMessageServiceUtil.getCompanyMessagesRSS(companyId,
					max, type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getGroupMessagesRSS(long groupId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws RemoteException {
		try {
			java.lang.String returnValue = MBMessageServiceUtil.getGroupMessagesRSS(groupId,
					max, type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getGroupMessagesRSS(long groupId,
		long userId, int max, java.lang.String type, double version,
		java.lang.String displayStyle, java.lang.String feedURL,
		java.lang.String entryURL) throws RemoteException {
		try {
			java.lang.String returnValue = MBMessageServiceUtil.getGroupMessagesRSS(groupId,
					userId, max, type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap getMessage(
		long messageId) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.getMessage(messageId);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		long messageId) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessageDisplay returnValue =
				MBMessageServiceUtil.getMessageDisplay(messageId);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static java.lang.String getThreadMessagesRSS(long threadId, int max,
		java.lang.String type, double version, java.lang.String displayStyle,
		java.lang.String feedURL, java.lang.String entryURL)
		throws RemoteException {
		try {
			java.lang.String returnValue = MBMessageServiceUtil.getThreadMessagesRSS(threadId,
					max, type, version, displayStyle, feedURL, entryURL);

			return returnValue;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void subscribeMessage(long messageId)
		throws RemoteException {
		try {
			MBMessageServiceUtil.subscribeMessage(messageId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void unsubscribeMessage(long messageId)
		throws RemoteException {
		try {
			MBMessageServiceUtil.unsubscribeMessage(messageId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap updateDiscussionMessage(
		long groupId, java.lang.String className, long classPK, long messageId,
		java.lang.String subject, java.lang.String body)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.updateDiscussionMessage(groupId,
					className, classPK, messageId, subject, body);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageSoap updateMessage(
		long messageId, java.lang.String subject, java.lang.String body,
		java.util.List files, double priority, java.lang.String[] tagsEntries)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.updateMessage(messageId,
					subject, body, files, priority, tagsEntries);

			return com.liferay.portlet.messageboards.model.MBMessageSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(MBMessageServiceSoap.class);
}