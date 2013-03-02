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

package com.liferay.portlet.biblejournal.service.http;

import com.liferay.portlet.biblejournal.service.spring.BJTopicServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="BJTopicServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class BJTopicServiceSoap {
	public static com.liferay.portlet.biblejournal.model.BJTopicModel addTopic(
		java.lang.String name, java.lang.String description)
		throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJTopic returnValue = BJTopicServiceUtil.addTopic(name,
					description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteTopic(java.lang.String topicId)
		throws RemoteException {
		try {
			BJTopicServiceUtil.deleteTopic(topicId);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteTopic(
		com.liferay.portlet.biblejournal.model.BJTopic topic)
		throws RemoteException {
		try {
			BJTopicServiceUtil.deleteTopic(topic);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJTopicModel[] getEntries(
		java.lang.String topicId) throws RemoteException {
		try {
			java.util.List returnValue = BJTopicServiceUtil.getEntries(topicId);

			return (com.liferay.portlet.biblejournal.model.BJTopic[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJTopic[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJTopicModel getTopic(
		java.lang.String topicId) throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJTopic returnValue = BJTopicServiceUtil.getTopic(topicId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJTopicModel[] getTopicsByCompany(
		java.lang.String companyId) throws RemoteException {
		try {
			java.util.List returnValue = BJTopicServiceUtil.getTopicsByCompany(companyId);

			return (com.liferay.portlet.biblejournal.model.BJTopic[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJTopic[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJTopicModel[] getTopicsByUser(
		java.lang.String userId) throws RemoteException {
		try {
			java.util.List returnValue = BJTopicServiceUtil.getTopicsByUser(userId);

			return (com.liferay.portlet.biblejournal.model.BJTopic[])returnValue.toArray(new com.liferay.portlet.biblejournal.model.BJTopic[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.biblejournal.model.BJTopicModel updateTopic(
		java.lang.String topicId, java.lang.String name,
		java.lang.String description) throws RemoteException {
		try {
			com.liferay.portlet.biblejournal.model.BJTopic returnValue = BJTopicServiceUtil.updateTopic(topicId,
					name, description);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}