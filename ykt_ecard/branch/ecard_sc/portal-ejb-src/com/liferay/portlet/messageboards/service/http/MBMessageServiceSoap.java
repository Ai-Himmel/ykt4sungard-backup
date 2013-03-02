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

import com.liferay.portlet.messageboards.service.spring.MBMessageServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="MBMessageServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessageServiceSoap {
	public static void deleteMessage(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK pk)
		throws RemoteException {
		try {
			MBMessageServiceUtil.deleteMessage(pk);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageModel getMessage(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK pk)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessage returnValue = MBMessageServiceUtil.getMessage(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageDisplay getMessageDisplay(
		com.liferay.portlet.messageboards.service.persistence.MBMessagePK pk)
		throws RemoteException {
		try {
			com.liferay.portlet.messageboards.model.MBMessageDisplay returnValue =
				MBMessageServiceUtil.getMessageDisplay(pk);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageModel[] getMessagesByThread(
		java.lang.String threadId) throws RemoteException {
		try {
			java.util.List returnValue = MBMessageServiceUtil.getMessagesByThread(threadId);

			return (com.liferay.portlet.messageboards.model.MBMessage[])returnValue.toArray(new com.liferay.portlet.messageboards.model.MBMessage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.messageboards.model.MBMessageModel[] getMessagesByTopic(
		java.lang.String topicId, int begin, int end) throws RemoteException {
		try {
			java.util.List returnValue = MBMessageServiceUtil.getMessagesByTopic(topicId,
					begin, end);

			return (com.liferay.portlet.messageboards.model.MBMessage[])returnValue.toArray(new com.liferay.portlet.messageboards.model.MBMessage[0]);
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getMessagesSizeByThread(java.lang.String threadId)
		throws RemoteException {
		try {
			int returnValue = MBMessageServiceUtil.getMessagesSizeByThread(threadId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getMessagesSizeByTopic(java.lang.String topicId)
		throws RemoteException {
		try {
			int returnValue = MBMessageServiceUtil.getMessagesSizeByTopic(topicId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}

	public static int getReadMessagesSize(java.lang.String topicId,
		java.lang.String userId) throws RemoteException {
		try {
			int returnValue = MBMessageServiceUtil.getReadMessagesSize(topicId,
					userId);

			return returnValue;
		}
		catch (Exception e) {
			throw new RemoteException(e.getMessage());
		}
	}
}