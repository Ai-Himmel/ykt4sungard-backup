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

package com.liferay.portlet.messageboards.service.impl;

import com.liferay.documentlibrary.NoSuchDirectoryException;
import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Company;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.messageboards.NoSuchMessageFlagException;
import com.liferay.portlet.messageboards.NoSuchThreadException;
import com.liferay.portlet.messageboards.RequiredMessageException;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBMessageDisplay;
import com.liferay.portlet.messageboards.model.MBMessageFlag;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.portlet.messageboards.model.MBTopic;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagPK;
import com.liferay.portlet.messageboards.service.persistence.MBMessageFlagUtil;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePK;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.messageboards.service.persistence.MBThreadUtil;
import com.liferay.portlet.messageboards.service.persistence.MBTopicUtil;
import com.liferay.portlet.messageboards.service.spring.MBMessageService;
import com.liferay.portlet.messageboards.service.spring.MBTopicServiceUtil;
import com.liferay.portlet.messageboards.util.Indexer;
import com.liferay.portlet.messageboards.util.MBMessageComparator;
import com.liferay.portlet.messageboards.util.MBThreadComparator;
import com.liferay.portlet.messageboards.util.TreeWalker;

import java.io.IOException;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="MBMessageServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class MBMessageServiceImpl
	extends PrincipalBean implements MBMessageService {

	// Business methods

	public void deleteMessage(MBMessagePK pk)
		throws PortalException, SystemException {

		if (!MBTopicServiceUtil.hasAdmin(pk.topicId)) {
			throw new PrincipalException();
		}

		MBMessage message = MBMessageUtil.findByPrimaryKey(pk);

		int count = MBMessageUtil.countByThreadId(message.getThreadId());

		if (count == 1) {
			MBThreadUtil.remove(message.getThreadId());
		}
		else if (count > 1) {
			MBThread thread =
				MBThreadUtil.findByPrimaryKey(message.getThreadId());

			// Message is a root message

			if (thread.getRootMessageId().equals(pk.messageId)) {
				List childrenMessages = MBMessageUtil.findByT_P(
					message.getThreadId(), pk.messageId);

				if (childrenMessages.size() > 1) {
					throw new RequiredMessageException();
				}
				else if (childrenMessages.size() == 1) {
					MBMessage childMessage = (MBMessage)childrenMessages.get(0);

					childMessage.setParentMessageId(
						MBMessage.DEFAULT_PARENT_MESSAGE_ID);

					MBMessageUtil.update(childMessage);

					thread.setRootMessageId(childMessage.getMessageId());

					MBThreadUtil.update(thread);
				}
			}

			// Message is a child message

			else {
				List childrenMessages = MBMessageUtil.findByT_P(
					message.getThreadId(), pk.messageId);

				// Message has children messages

				if (childrenMessages.size() > 0) {
					Iterator itr = childrenMessages.iterator();

					while (itr.hasNext()) {
						MBMessage childMessage = (MBMessage)itr.next();

						childMessage.setParentMessageId(
							message.getParentMessageId());

						MBMessageUtil.update(childMessage);
					}
				}
			}

			// Update thread

			thread.setMessageCount(count - 1);

			MBThreadUtil.update(thread);
		}

		// Delete message flags

		MBMessageFlagUtil.removeByT_M(pk.topicId, pk.messageId);

		// Delete message

		MBMessageUtil.remove(pk);

		// Update lucene

		MBTopic topic = MBTopicUtil.findByPrimaryKey(pk.topicId);

		try {
			Indexer.deleteMessage(
				topic.getCompanyId(), topic.getPortletId(), pk.topicId,
				pk.messageId);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		// File attachments

		if (message.isAttachments()) {
			String companyId = message.getCompanyId();
			String portletId = Company.SYSTEM;
			String repositoryId = Company.SYSTEM;
			String dirName = message.getAttachmentsDir();

			try {
				DLServiceUtil.deleteDirectory(
					companyId, portletId, repositoryId, dirName);
			}
			catch (NoSuchDirectoryException nsde) {
			}
		}
	}

	public MBMessage getMessage(MBMessagePK pk)
		throws PortalException, SystemException {

		if (!MBTopicServiceUtil.hasRead(pk.topicId)) {
			throw new PrincipalException();
		}

		return MBMessageUtil.findByPrimaryKey(pk);
	}

	public MBMessageDisplay getMessageDisplay(MBMessagePK pk)
		throws PortalException, SystemException {

		MBMessage message = getMessage(pk);

		MBMessageFlagPK flagPK =
			new MBMessageFlagPK(pk.topicId, pk.messageId, getUserId());

		try {
			MBMessageFlagUtil.findByPrimaryKey(flagPK);
		}
		catch (NoSuchMessageFlagException nsmfe) {
			MBMessageFlag messageFlag = MBMessageFlagUtil.create(flagPK);

			messageFlag.setFlag(MBMessageFlag.READ_FLAG);

			MBMessageFlagUtil.update(messageFlag);
		}

		MBMessage parentMessage = null;
		if (message.isReply()) {
			parentMessage = MBMessageUtil.findByPrimaryKey(
				new MBMessagePK(message.getParentMessageId(),
								message.getTopicId()));
		}

		MBThread thread = MBThreadUtil.findByPrimaryKey(message.getThreadId());

		TreeWalker treeWalker = new TreeWalker(message);

		MBThreadComparator threadComparator = new MBThreadComparator(false);

		MBThread[] prevAndNextThreads = MBThreadUtil.findByTopicId_PrevAndNext(
			message.getThreadId(), message.getTopicId(), threadComparator);

		MBThread previousThread = prevAndNextThreads[0];
		MBThread nextThread = prevAndNextThreads[2];

		MBThread firstThread = null;
		try {
			firstThread = MBThreadUtil.findByTopicId_First(
				message.getTopicId(), threadComparator);
		}
		catch (NoSuchThreadException nste) {
		}

		MBThread lastThread = null;
		try {
			lastThread = MBThreadUtil.findByTopicId_Last(
				message.getTopicId(), threadComparator);
		}
		catch (NoSuchThreadException nste) {
		}

		return new MBMessageDisplay(
			message, parentMessage, thread, treeWalker, previousThread,
			nextThread, firstThread, lastThread);
	}

	public List getMessagesByThread(String threadId)
		throws PortalException, SystemException {

		MBThread thread = MBThreadUtil.findByPrimaryKey(threadId);

		if (!MBTopicServiceUtil.hasRead(thread.getTopicId())) {
			throw new PrincipalException();
		}

		List messages = MBMessageUtil.findByThreadId(threadId);

		Collections.sort(messages, new MBMessageComparator());

		return messages;
	}

	public List getMessagesByTopic(String topicId, int begin, int end)
		throws PortalException, SystemException {

		if (!MBTopicServiceUtil.hasRead(topicId)) {
			throw new PrincipalException();
		}

		return MBMessageUtil.findByTopicId(topicId, begin, end);
	}

	public int getMessagesSizeByThread(String threadId) throws SystemException {
		return MBMessageUtil.countByThreadId(threadId);
	}

	public int getMessagesSizeByTopic(String topicId) throws SystemException {
		return MBMessageUtil.countByTopicId(topicId);
	}

	public int getReadMessagesSize(String topicId, String userId)
		throws SystemException {

		return MBMessageFlagUtil.countByT_U(topicId, userId);
	}

}