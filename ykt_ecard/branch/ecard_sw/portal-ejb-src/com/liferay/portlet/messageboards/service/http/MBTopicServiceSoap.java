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

package com.liferay.portlet.messageboards.service.http;

import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="MBTopicServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBTopicServiceSoap {
	public static com.liferay.portlet.messageboards.model.MBTopicModel addTopic(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String readRoles, java.lang.String writeRoles,
		java.lang.String name, java.lang.String description)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBTopic returnValue = MBTopicServiceUtil.addTopic(portletId,
					groupId, readRoles, writeRoles, name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteTopic(java.lang.String topicId)
		throws RemoteException {
		try {
			MBTopicServiceUtil.deleteTopic(topicId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBTopicModel getTopic(
		java.lang.String topicId) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBTopic returnValue = MBTopicServiceUtil.getTopic(topicId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBTopicModel[] getTopics(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = MBTopicServiceUtil.getTopics(portletId,
					groupId, companyId);

			return (com.liferay.portlet.messageboards.model.MBTopic[])returnValue.toArray(new com.liferay.portlet.messageboards.model.MBTopic[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBTopicModel[] getTopics(
		java.lang.String portletId, java.lang.String groupId,
		java.lang.String companyId, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = MBTopicServiceUtil.getTopics(portletId,
					groupId, companyId, begin, end);

			return (com.liferay.portlet.messageboards.model.MBTopic[])returnValue.toArray(new com.liferay.portlet.messageboards.model.MBTopic[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getTopicsSize(java.lang.String portletId,
		java.lang.String groupId, java.lang.String companyId)
		throws RemoteException {
		try {
			int returnValue = MBTopicServiceUtil.getTopicsSize(portletId,
					groupId, companyId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessage postNewThread(
		java.lang.String topicId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBTopicServiceUtil.postNewThread(topicId,
					subject, body, files, anonymous);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessage postReply(
		java.lang.String topicId, java.lang.String threadId,
		java.lang.String parentMessageId, java.lang.String subject,
		java.lang.String body, java.util.List files, boolean anonymous)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBTopicServiceUtil.postReply(topicId,
					threadId, parentMessageId, subject, body, files, anonymous);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void reIndex(java.lang.String[] ids)
		throws RemoteException {
		try {
			MBTopicServiceUtil.reIndex(ids);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.util.lucene.Hits search(
		java.lang.String companyId, java.lang.String portletId,
		java.lang.String groupId, java.lang.String[] topicIds,
		java.lang.String keywords) throws RemoteException {
		try {
			com.liferay.util.lucene.Hits returnValue = MBTopicServiceUtil.search(companyId,
					portletId, groupId, topicIds, keywords);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBTopicModel updateTopic(
		java.lang.String topicId, java.lang.String readRoles,
		java.lang.String writeRoles, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBTopic returnValue = MBTopicServiceUtil.updateTopic(topicId,
					readRoles, writeRoles, name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasAdmin(java.lang.String topicId)
		throws RemoteException {
		try {
			boolean returnValue = MBTopicServiceUtil.hasAdmin(topicId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasRead(java.lang.String topicId)
		throws RemoteException {
		try {
			boolean returnValue = MBTopicServiceUtil.hasRead(topicId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static boolean hasWrite(java.lang.String topicId)
		throws RemoteException {
		try {
			boolean returnValue = MBTopicServiceUtil.hasWrite(topicId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}