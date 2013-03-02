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

package com.liferay.portlet.messageboards.service.impl;

import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.documentlibrary.NoSuchDirectoryException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.mail.MailMessage;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.ObjectValuePair;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.ModelHintsUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.model.impl.GroupImpl;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.blogs.model.BlogsEntry;
import com.liferay.portlet.messageboards.MessageBodyException;
import com.liferay.portlet.messageboards.MessageSubjectException;
import com.liferay.portlet.messageboards.NoSuchDiscussionException;
import com.liferay.portlet.messageboards.NoSuchThreadException;
import com.liferay.portlet.messageboards.RequiredMessageException;
import com.liferay.portlet.messageboards.model.MBCategory;
import com.liferay.portlet.messageboards.model.MBDiscussion;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBMessageDisplay;
import com.liferay.portlet.messageboards.model.MBStatsUser;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.portlet.messageboards.model.MBTreeWalker;
import com.liferay.portlet.messageboards.model.impl.MBMessageDisplayImpl;
import com.liferay.portlet.messageboards.model.impl.MBMessageImpl;
import com.liferay.portlet.messageboards.model.impl.MBThreadImpl;
import com.liferay.portlet.messageboards.model.impl.MBTreeWalkerImpl;
import com.liferay.portlet.messageboards.service.base.MBMessageLocalServiceBaseImpl;
import com.liferay.portlet.messageboards.service.jms.MBMessageProducer;
import com.liferay.portlet.messageboards.util.Indexer;
import com.liferay.portlet.messageboards.util.MBUtil;
import com.liferay.portlet.messageboards.util.comparator.MessageThreadComparator;
import com.liferay.portlet.messageboards.util.comparator.ThreadLastPostDateComparator;

import java.io.IOException;

import java.rmi.RemoteException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.mail.internet.InternetAddress;

import javax.portlet.PortletPreferences;

import org.apache.commons.lang.time.StopWatch;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MBMessageLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MBMessageLocalServiceImpl extends MBMessageLocalServiceBaseImpl {

	public MBMessage addDiscussionMessage(
			long userId, String subject, String body)
		throws PortalException, SystemException {

		long groupId = 0;
		String className = StringPool.BLANK;
		long classPK = 0;
		long threadId = 0;
		long parentMessageId = 0;
		ThemeDisplay themeDisplay = null;

		return addDiscussionMessage(
			userId, groupId, className, classPK, threadId, parentMessageId,
			subject, body, themeDisplay);
	}

	public MBMessage addDiscussionMessage(
			long userId, long groupId, String className, long classPK,
			long threadId, long parentMessageId, String subject, String body)
		throws PortalException, SystemException {

		ThemeDisplay themeDisplay = null;

		MBMessage message = addDiscussionMessage(
			userId, groupId, className, classPK, threadId, parentMessageId,
			subject, body, themeDisplay);

		if (parentMessageId == MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID) {
			long discussionId = counterLocalService.increment();

			MBDiscussion discussion = mbDiscussionPersistence.create(
				discussionId);

			discussion.setClassNameId(PortalUtil.getClassNameId(className));
			discussion.setClassPK(classPK);
			discussion.setThreadId(message.getThreadId());

			mbDiscussionPersistence.update(discussion);
		}

		return message;
	}

	public MBMessage addDiscussionMessage(
			long userId, long groupId, String className, long classPK,
			long threadId, long parentMessageId, String subject, String body,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		long categoryId = CompanyImpl.SYSTEM;

		if (Validator.isNull(subject)) {
			subject = "N/A";
		}

		List files = new ArrayList();
		boolean anonymous = false;
		double priority = 0.0;
		String[] tagsEntries = null;
		PortletPreferences prefs = null;
		boolean addCommunityPermissions = true;
		boolean addGuestPermissions = true;

		mbCategoryLocalService.getSystemCategory();

		MBMessage message = addMessage(
			userId, categoryId, threadId, parentMessageId, subject, body, files,
			anonymous, priority, tagsEntries, prefs, addCommunityPermissions,
			addGuestPermissions, themeDisplay);

		if ((className.equals(BlogsEntry.class.getName())) &&
			(themeDisplay != null)) {

			try {
				sendBlogsCommentsEmail(userId, classPK, message, themeDisplay);
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}

		return message;
	}

	public MBMessage addMessage(
			long userId, long categoryId, String subject, String body,
			List files, boolean anonymous, double priority,
			String[] tagsEntries, PortletPreferences prefs,
			boolean addCommunityPermissions, boolean addGuestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addMessage(
			userId, categoryId, subject, body, files, anonymous, priority,
			tagsEntries, prefs, Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null, themeDisplay);
	}

	public MBMessage addMessage(
			long userId, long categoryId, String subject, String body,
			List files, boolean anonymous, double priority,
			String[] tagsEntries, PortletPreferences prefs,
			String[] communityPermissions, String[] guestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addMessage(
			userId, categoryId, subject, body, files, anonymous, priority,
			tagsEntries, prefs, null, null, communityPermissions,
			guestPermissions, themeDisplay);
	}

	public MBMessage addMessage(
			long userId, long categoryId, String subject, String body,
			List files, boolean anonymous, double priority,
			String[] tagsEntries, PortletPreferences prefs,
			Boolean addCommunityPermissions, Boolean addGuestPermissions,
			String[] communityPermissions, String[] guestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		long threadId = 0;
		long parentMessageId = 0;

		return addMessage(
			null, userId, categoryId, threadId, parentMessageId, subject, body,
			files, anonymous, priority, tagsEntries, prefs,
			addCommunityPermissions, addGuestPermissions, communityPermissions,
			guestPermissions, themeDisplay);
	}

	public MBMessage addMessage(
			long userId, long categoryId, long threadId,
			long parentMessageId, String subject, String body, List files,
			boolean anonymous, double priority, String[] tagsEntries,
			PortletPreferences prefs, boolean addCommunityPermissions,
			boolean addGuestPermissions, ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addMessage(
			null, userId, categoryId, threadId, parentMessageId, subject, body,
			files, anonymous, priority, tagsEntries, prefs,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null, themeDisplay);
	}

	public MBMessage addMessage(
			long userId, long categoryId, long threadId, long parentMessageId,
			String subject, String body, List files, boolean anonymous,
			double priority, String[] tagsEntries, PortletPreferences prefs,
			String[] communityPermissions, String[] guestPermissions,
			ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addMessage(
			null, userId, categoryId, threadId, parentMessageId, subject, body,
			files, anonymous, priority, tagsEntries, prefs, null, null,
			communityPermissions, guestPermissions, themeDisplay);
	}

	public MBMessage addMessage(
			String uuid, long userId, long categoryId, long threadId,
			long parentMessageId, String subject, String body, List files,
			boolean anonymous, double priority, String[] tagsEntries,
			PortletPreferences prefs, boolean addCommunityPermissions,
			boolean addGuestPermissions, ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		return addMessage(
			uuid, userId, categoryId, threadId, parentMessageId, subject, body,
			files, anonymous, priority, tagsEntries, prefs,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null, themeDisplay);
	}

	public MBMessage addMessage(
			String uuid, long userId, long categoryId, long threadId,
			long parentMessageId, String subject, String body, List files,
			boolean anonymous, double priority, String[] tagsEntries,
			PortletPreferences prefs, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions, ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		StopWatch stopWatch = null;

		if (_log.isDebugEnabled()) {
			stopWatch = new StopWatch();

			stopWatch.start();
		}

		// Message

		User user = userPersistence.findByPrimaryKey(userId);
		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);
		subject = ModelHintsUtil.trimString(
			MBMessage.class.getName(), "subject", subject);

		if (prefs != null) {
			if (!MBUtil.isAllowAnonymousPosting(prefs)) {
				if (anonymous || user.isDefaultUser()) {
					throw new PrincipalException();
				}
			}
		}

		if (user.isDefaultUser()) {
			anonymous = true;
		}

		Date now = new Date();

		validate(subject, body);

		long messageId = counterLocalService.increment();

		logAddMessage(messageId, stopWatch, 1);

		MBMessage message = mbMessagePersistence.create(messageId);

		message.setUuid(uuid);
		message.setCompanyId(user.getCompanyId());
		message.setUserId(user.getUserId());
		message.setUserName(user.getFullName());
		message.setCreateDate(now);
		message.setModifiedDate(now);

		// Thread

		MBMessage parentMessage = mbMessagePersistence.fetchByPrimaryKey(
			parentMessageId);

		if (parentMessage == null) {
			parentMessageId = MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID;
		}

		MBThread thread = null;

		if (threadId > 0) {
			thread = mbThreadPersistence.fetchByPrimaryKey(threadId);
		}

		if ((thread == null) ||
			(parentMessageId == MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID)) {

			threadId = counterLocalService.increment();

			thread = mbThreadPersistence.create(threadId);

			thread.setCategoryId(categoryId);
			thread.setRootMessageId(messageId);
		}

		thread.setMessageCount(thread.getMessageCount() + 1);

		if (anonymous) {
			thread.setLastPostByUserId(0);
		}
		else {
			thread.setLastPostByUserId(userId);
		}

		thread.setLastPostDate(now);

		if (priority != MBThreadImpl.PRIORITY_NOT_GIVEN) {
			thread.setPriority(priority);
		}

		logAddMessage(messageId, stopWatch, 2);

		// Message

		message.setCategoryId(categoryId);
		message.setThreadId(threadId);
		message.setParentMessageId(parentMessageId);
		message.setSubject(subject);
		message.setBody(body);
		message.setAttachments((files.size() > 0 ? true : false));
		message.setAnonymous(anonymous);

		// File attachments

		if (files.size() > 0) {
			long companyId = message.getCompanyId();
			String portletId = CompanyImpl.SYSTEM_STRING;
			long groupId = GroupImpl.DEFAULT_PARENT_GROUP_ID;
			long repositoryId = CompanyImpl.SYSTEM;
			String dirName = message.getAttachmentsDir();

			try {
				try {
					dlService.deleteDirectory(
						companyId, portletId, repositoryId, dirName);
				}
				catch (NoSuchDirectoryException nsde) {
				}

				dlService.addDirectory(companyId, repositoryId, dirName);

				for (int i = 0; i < files.size(); i++) {
					ObjectValuePair ovp = (ObjectValuePair)files.get(i);

					String fileName = (String)ovp.getKey();
					byte[] byteArray = (byte[])ovp.getValue();

					try {
						dlService.addFile(
							companyId, portletId, groupId, repositoryId,
							dirName + "/" + fileName, StringPool.BLANK,
							new String[0], byteArray);
					}
					catch (DuplicateFileException dfe) {
					}
				}
			}
			catch (RemoteException re) {
				throw new SystemException(re);
			}
		}

		logAddMessage(messageId, stopWatch, 3);

		// Commit

		mbThreadPersistence.update(thread);
		mbMessagePersistence.update(message);

		logAddMessage(messageId, stopWatch, 4);

		// Resources

		if (!category.isDiscussion()) {
			if (user.isDefaultUser()) {
				addMessageResources(category, message, true, true);
			}
			else if ((addCommunityPermissions != null) &&
					 (addGuestPermissions != null)) {

				addMessageResources(
					category, message, addCommunityPermissions.booleanValue(),
					addGuestPermissions.booleanValue());
			}
			else {
				addMessageResources(
					category, message, communityPermissions, guestPermissions);
			}
		}

		logAddMessage(messageId, stopWatch, 5);

		// Statistics

		if (!category.isDiscussion()) {
			mbStatsUserLocalService.updateStatsUser(
				category.getGroupId(), userId);
		}

		logAddMessage(messageId, stopWatch, 6);

		// Subscriptions

		notifySubscribers(category, message, prefs, themeDisplay, false);

		logAddMessage(messageId, stopWatch, 7);

		// Category

		category.setLastPostDate(now);

		mbCategoryPersistence.update(category);

		logAddMessage(messageId, stopWatch, 8);

		// Tags

		updateTagsAsset(userId, message, tagsEntries);

		logAddMessage(messageId, stopWatch, 9);

		// Activity trackers

		if (!message.isDiscussion() && !user.isDefaultUser()) {
			/*long receiverUserId = 0;

			if (parentMessage != null) {
				receiverUserId = parentMessage.getUserId();
			}

			activityTrackerLocalService.addActivityTracker(
				userId, category.getGroupId(), MBMessage.class.getName(),
				messageId, MBActivityKeys.ADD, StringPool.BLANK,
				receiverUserId);*/
		}

		logAddMessage(messageId, stopWatch, 10);

		// Testing roll back

		/*if (true) {
			throw new SystemException("Testing roll back");
		}*/

		// Lucene

		try {
			if (!category.isDiscussion()) {
				Indexer.addMessage(
					message.getCompanyId(), category.getGroupId(),
					user.getFullName(), category.getCategoryId(), threadId,
					messageId, subject, body, tagsEntries);
			}
		}
		catch (IOException ioe) {
			_log.error("Indexing " + messageId, ioe);
		}

		logAddMessage(messageId, stopWatch, 11);

		return message;
	}

	public void addMessageResources(
			long categoryId, long messageId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		addMessageResources(
			categoryId, null, messageId, addCommunityPermissions,
			addGuestPermissions);
	}

	public void addMessageResources(
			long categoryId, String topicId, long messageId,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);
		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		addMessageResources(
			category, message, addCommunityPermissions, addGuestPermissions);
	}

	public void addMessageResources(
			MBCategory category, MBMessage message,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			message.getCompanyId(), category.getGroupId(), message.getUserId(),
			MBMessage.class.getName(), message.getMessageId(),
			false, addCommunityPermissions, addGuestPermissions);
	}

	public void addMessageResources(
			long categoryId, long messageId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		addMessageResources(
			categoryId, null, messageId, communityPermissions,
			guestPermissions);
	}

	public void addMessageResources(
			long categoryId, String topicId, long messageId,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			categoryId);
		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		addMessageResources(
			category, message, communityPermissions, guestPermissions);
	}

	public void addMessageResources(
			MBCategory category, MBMessage message,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			message.getCompanyId(), category.getGroupId(), message.getUserId(),
			MBMessage.class.getName(), message.getMessageId(),
			communityPermissions, guestPermissions);
	}

	public void deleteDiscussionMessage(long messageId)
		throws PortalException, SystemException {

		deleteMessage(messageId);
	}

	public void deleteDiscussionMessages(String className, long classPK)
		throws PortalException, SystemException {

		try {
			long classNameId = PortalUtil.getClassNameId(className);

			MBDiscussion discussion = mbDiscussionPersistence.findByC_C(
				classNameId, classPK);

			List messages = mbMessagePersistence.findByT_P(
				discussion.getThreadId(),
				MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID, 0, 1);

			if (messages.size() > 0) {
				MBMessage message = (MBMessage)messages.get(0);

				mbThreadLocalService.deleteThread(message.getThreadId());
			}

			mbDiscussionPersistence.remove(discussion.getDiscussionId());
		}
		catch (NoSuchDiscussionException nsde) {
		}
	}

	public void deleteMessage(long messageId)
		throws PortalException, SystemException {

		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		deleteMessage(message);
	}

	public void deleteMessage(MBMessage message)
		throws PortalException, SystemException {

		// Lucene

		try {
			Indexer.deleteMessage(
				message.getCompanyId(), message.getMessageId());
		}
		catch (IOException ioe) {
			_log.error("Deleting index " + message.getMessageId(), ioe);
		}

		// File attachments

		if (message.isAttachments()) {
			long companyId = message.getCompanyId();
			String portletId = CompanyImpl.SYSTEM_STRING;
			long repositoryId = CompanyImpl.SYSTEM;
			String dirName = message.getAttachmentsDir();

			try {
				dlService.deleteDirectory(
					companyId, portletId, repositoryId, dirName);
			}
			catch (NoSuchDirectoryException nsde) {
			}
			catch (RemoteException re) {
				throw new SystemException(re);
			}
		}

		// Thread

		int count = mbMessagePersistence.countByThreadId(message.getThreadId());

		if (count == 1) {

			// File attachments

			long companyId = message.getCompanyId();
			String portletId = CompanyImpl.SYSTEM_STRING;
			long repositoryId = CompanyImpl.SYSTEM;
			String dirName = message.getThreadAttachmentsDir();

			try {
				dlService.deleteDirectory(
					companyId, portletId, repositoryId, dirName);
			}
			catch (NoSuchDirectoryException nsde) {
			}
			catch (RemoteException re) {
				throw new SystemException(re);
			}

			// Subscriptions

			subscriptionLocalService.deleteSubscriptions(
				message.getCompanyId(), MBThread.class.getName(),
				message.getThreadId());

			// Thread

			mbThreadPersistence.remove(message.getThreadId());
		}
		else if (count > 1) {
			MBThread thread = mbThreadPersistence.findByPrimaryKey(
				message.getThreadId());

			// Message is a root message

			if (thread.getRootMessageId() == message.getMessageId()) {
				List childrenMessages = mbMessagePersistence.findByT_P(
					message.getThreadId(), message.getMessageId());

				if (childrenMessages.size() > 1) {
					throw new RequiredMessageException(
						String.valueOf(message.getMessageId()));
				}
				else if (childrenMessages.size() == 1) {
					MBMessage childMessage = (MBMessage)childrenMessages.get(0);

					childMessage.setParentMessageId(
						MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID);

					mbMessagePersistence.update(childMessage);

					thread.setRootMessageId(childMessage.getMessageId());

					mbThreadPersistence.update(thread);
				}
			}

			// Message is a child message

			else {
				List childrenMessages = mbMessagePersistence.findByT_P(
					message.getThreadId(), message.getMessageId());

				// Message has children messages

				if (childrenMessages.size() > 0) {
					Iterator itr = childrenMessages.iterator();

					while (itr.hasNext()) {
						MBMessage childMessage = (MBMessage)itr.next();

						childMessage.setParentMessageId(
							message.getParentMessageId());

						mbMessagePersistence.update(childMessage);
					}
				}
			}

			// Thread

			thread.setMessageCount(count - 1);

			mbThreadPersistence.update(thread);
		}

		// Activity trackers

		activityTrackerLocalService.deleteActivityTrackers(
			MBMessage.class.getName(), message.getMessageId());

		// Tags

		tagsAssetLocalService.deleteAsset(
			MBMessage.class.getName(), message.getMessageId());

		// Message flags

		mbMessageFlagPersistence.removeByMessageId(message.getMessageId());

		// Resources

		if (!message.isDiscussion()) {
			resourceLocalService.deleteResource(
				message.getCompanyId(), MBMessage.class.getName(),
				ResourceImpl.SCOPE_INDIVIDUAL, message.getMessageId());
		}

		// Message

		mbMessagePersistence.remove(message.getPrimaryKey());
	}

	public List getCategoryMessages(long categoryId, int begin, int end)
		throws SystemException {

		return mbMessagePersistence.findByCategoryId(categoryId, begin, end);
	}

	public List getCategoryMessages(
			long categoryId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return mbMessagePersistence.findByCategoryId(
			categoryId, begin, end, obc);
	}

	public int getCategoryMessagesCount(long categoryId)
		throws SystemException {

		return mbMessagePersistence.countByCategoryId(categoryId);
	}

	public int getCategoriesMessagesCount(List categoryIds)
		throws SystemException {

		return mbMessageFinder.countByCategoryIds(categoryIds);
	}

	public List getCompanyMessages(long companyId, int begin, int end)
		throws SystemException {

		return mbMessagePersistence.findByCompanyId(companyId, begin, end);
	}

	public List getCompanyMessages(
			long companyId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return mbMessagePersistence.findByCompanyId(companyId, begin, end, obc);
	}

	public int getCompanyMessagesCount(long companyId)
		throws SystemException {

		return mbMessagePersistence.countByCompanyId(companyId);
	}

	public MBMessageDisplay getDiscussionMessageDisplay(
			long userId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		MBMessage message = null;

		try {
			MBDiscussion discussion = mbDiscussionPersistence.findByC_C(
				classNameId, classPK);

			List messages = mbMessagePersistence.findByT_P(
				discussion.getThreadId(),
				MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID);

			message = (MBMessage)messages.get(0);
		}
		catch (NoSuchDiscussionException nsde) {
			String subject = String.valueOf(classPK);
			String body = subject;

			message = addDiscussionMessage(userId, subject, body);

			long discussionId = counterLocalService.increment();

			MBDiscussion discussion = mbDiscussionPersistence.create(
				discussionId);

			discussion.setClassNameId(classNameId);
			discussion.setClassPK(classPK);
			discussion.setThreadId(message.getThreadId());

			mbDiscussionPersistence.update(discussion);
		}

		return getMessageDisplay(message);
	}

	public int getDiscussionMessagesCount(long classNameId, long classPK)
		throws SystemException {

		MBDiscussion discussion = mbDiscussionPersistence.fetchByC_C(
			classNameId, classPK);

		if (discussion == null) {
			return 0;
		}

		int count = mbMessagePersistence.countByThreadId(
			discussion.getThreadId());

		if (count >= 1) {
			return count - 1;
		}
		else {
			return 0;
		}
	}

	public List getGroupMessages(long groupId, int begin, int end)
		throws SystemException {

		return mbMessageFinder.findByGroupId(groupId, begin, end);
	}

	public List getGroupMessages(
			long groupId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return mbMessageFinder.findByGroupId(groupId, begin, end, obc);
	}

	public List getGroupMessages(long groupId, long userId, int begin, int end)
		throws SystemException {

		return mbMessageFinder.findByG_U(groupId, userId, begin, end);
	}

	public List getGroupMessages(
			long groupId, long userId, int begin, int end, OrderByComparator obc)
		throws SystemException {

		return mbMessageFinder.findByG_U(groupId, userId, begin, end, obc);
	}

	public int getGroupMessagesCount(long groupId) throws SystemException {
		return mbMessageFinder.countByGroupId(groupId);
	}

	public int getGroupMessagesCount(long groupId, long userId)
		throws SystemException {

		return mbMessageFinder.countByG_U(groupId, userId);
	}

	public MBMessage getMessage(long messageId)
		throws PortalException, SystemException {

		return mbMessagePersistence.findByPrimaryKey(messageId);
	}

	public List getMessages(String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return mbMessageFinder.findByC_C(classNameId, classPK);
	}

	public MBMessageDisplay getMessageDisplay(long messageId)
		throws PortalException, SystemException {

		MBMessage message = getMessage(messageId);

		return getMessageDisplay(message);
	}

	public MBMessageDisplay getMessageDisplay(MBMessage message)
		throws PortalException, SystemException {

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			message.getCategoryId());

		MBMessage parentMessage = null;

		if (message.isReply()) {
			parentMessage = mbMessagePersistence.findByPrimaryKey(
				message.getParentMessageId());
		}

		MBThread thread = mbThreadPersistence.findByPrimaryKey(
			message.getThreadId());

		thread.setViewCount(thread.getViewCount() + 1);

		mbThreadPersistence.update(thread);

		MBTreeWalker treeWalker = new MBTreeWalkerImpl(message);

		ThreadLastPostDateComparator comparator =
			new ThreadLastPostDateComparator(false);

		MBThread[] prevAndNextThreads =
			mbThreadPersistence.findByCategoryId_PrevAndNext(
				message.getThreadId(), message.getCategoryId(), comparator);

		MBThread previousThread = prevAndNextThreads[0];
		MBThread nextThread = prevAndNextThreads[2];

		MBThread firstThread = null;

		try {
			firstThread = mbThreadPersistence.findByCategoryId_First(
				message.getCategoryId(), comparator);
		}
		catch (NoSuchThreadException nste) {
		}

		MBThread lastThread = null;

		try {
			lastThread = mbThreadPersistence.findByCategoryId_Last(
				message.getCategoryId(), comparator);
		}
		catch (NoSuchThreadException nste) {
		}

		return new MBMessageDisplayImpl(
			message, parentMessage, category, thread, treeWalker,
			previousThread, nextThread, firstThread, lastThread);
	}

	public List getNoAssetMessages() throws SystemException {
		return mbMessageFinder.findByNoAssets();
	}

	public List getThreadMessages(long threadId) throws SystemException {
		return getThreadMessages(threadId, new MessageThreadComparator());
	}

	public List getThreadMessages(long threadId, Comparator comparator)
		throws SystemException {

		List messages = mbMessagePersistence.findByThreadId(threadId);

		Collections.sort(messages, comparator);

		return messages;
	}

	public int getThreadMessagesCount(long threadId) throws SystemException {
		return mbMessagePersistence.countByThreadId(threadId);
	}

	public void subscribeMessage(long userId, long messageId)
		throws PortalException, SystemException {

		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		subscriptionLocalService.addSubscription(
			userId, MBThread.class.getName(), message.getThreadId());
	}

	public void unsubscribeMessage(long userId, long messageId)
		throws PortalException, SystemException {

		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		subscriptionLocalService.deleteSubscription(
			userId, MBThread.class.getName(), message.getThreadId());
	}

	public MBMessage updateDiscussionMessage(
			long userId, long messageId, String subject, String body)
		throws PortalException, SystemException {

		if (Validator.isNull(subject)) {
			subject = "N/A";
		}

		List files = new ArrayList();
		double priority = 0.0;
		String[] tagsEntries = null;
		PortletPreferences prefs = null;
		ThemeDisplay themeDisplay = null;

		return updateMessage(
			userId, messageId, subject, body, files, priority, tagsEntries,
			prefs, themeDisplay);
	}

	public MBMessage updateMessage(
			long userId, long messageId, String subject, String body,
			List files, double priority, String[] tagsEntries,
			PortletPreferences prefs, ThemeDisplay themeDisplay)
		throws PortalException, SystemException {

		// Message

		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		MBCategory category = message.getCategory();
		subject = ModelHintsUtil.trimString(
			MBMessage.class.getName(), "subject", subject);
		Date now = new Date();

		validate(subject, body);

		// File attachments

		if (files.size() > 0) {
			long companyId = message.getCompanyId();
			String portletId = CompanyImpl.SYSTEM_STRING;
			long groupId = GroupImpl.DEFAULT_PARENT_GROUP_ID;
			long repositoryId = CompanyImpl.SYSTEM;
			String dirName = message.getAttachmentsDir();

			try {
				try {
					dlService.deleteDirectory(
						companyId, portletId, repositoryId, dirName);
				}
				catch (NoSuchDirectoryException nsde) {
				}

				dlService.addDirectory(companyId, repositoryId, dirName);

				for (int i = 0; i < files.size(); i++) {
					ObjectValuePair ovp = (ObjectValuePair)files.get(i);

					String fileName = (String)ovp.getKey();
					byte[] byteArray = (byte[])ovp.getValue();

					try {
						dlService.addFile(
							companyId, portletId, groupId, repositoryId,
							dirName + "/" + fileName, StringPool.BLANK,
							new String[0], byteArray);
					}
					catch (DuplicateFileException dfe) {
					}
				}
			}
			catch (RemoteException re) {
				throw new SystemException(re);
			}
		}

		// Message

		message.setModifiedDate(now);
		message.setSubject(subject);
		message.setBody(body);
		message.setAttachments((files.size() > 0 ? true : false));

		mbMessagePersistence.update(message);

		// Subscriptions

		notifySubscribers(category, message, prefs, themeDisplay, true);

		// Thread

		MBThread thread = mbThreadPersistence.findByPrimaryKey(
			message.getThreadId());

		if (priority != MBThreadImpl.PRIORITY_NOT_GIVEN) {
			thread.setPriority(priority);
		}

		mbThreadPersistence.update(thread);

		// Category

		category.setLastPostDate(now);

		mbCategoryPersistence.update(category);

		// Tags

		updateTagsAsset(userId, message, tagsEntries);

		// Lucene

		try {
			if (!category.isDiscussion()) {
				Indexer.updateMessage(
					message.getCompanyId(), category.getGroupId(),
					message.getUserName(), category.getCategoryId(),
					message.getThreadId(), messageId, subject, body,
					tagsEntries);
			}
		}
		catch (IOException ioe) {
			_log.error("Indexing " + messageId, ioe);
		}

		return message;
	}

	public MBMessage updateMessage(
			long messageId, Date createDate, Date modifiedDate)
		throws PortalException, SystemException {

		// Message

		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		message.setCreateDate(createDate);
		message.setModifiedDate(modifiedDate);

		mbMessagePersistence.update(message);

		// Thread

		MBThread thread = mbThreadPersistence.findByPrimaryKey(
			message.getThreadId());

		if (message.isAnonymous()) {
			thread.setLastPostByUserId(0);
		}
		else {
			thread.setLastPostByUserId(message.getUserId());
		}

		thread.setLastPostDate(modifiedDate);

		mbThreadPersistence.update(thread);

		// Category

		MBCategory category = mbCategoryPersistence.findByPrimaryKey(
			message.getCategoryId());

		category.setLastPostDate(modifiedDate);

		mbCategoryPersistence.update(category);

		// Statistics

		MBStatsUser statsUser = mbStatsUserPersistence.fetchByG_U(
			category.getGroupId(), message.getUserId());

		if (statsUser != null) {
			statsUser.setLastPostDate(modifiedDate);

			mbStatsUserPersistence.update(statsUser);
		}

		return message;
	}

	public MBMessage updateMessage(long messageId, String body)
		throws PortalException, SystemException {

		MBMessage message = mbMessagePersistence.findByPrimaryKey(messageId);

		message.setBody(body);

		mbMessagePersistence.update(message);

		return message;
	}

	public void updateTagsAsset(
			long userId, MBMessage message, String[] tagsEntries)
		throws PortalException, SystemException {

		if (message.isDiscussion()) {
			return;
		}

		tagsAssetLocalService.updateAsset(
			userId, message.getCategory().getGroupId(),
			MBMessage.class.getName(), message.getMessageId(), tagsEntries,
			null, null, null, null, ContentTypes.TEXT_HTML,
			message.getSubject(), null, null, null, 0, 0, null, false);
	}

	protected void logAddMessage(
		long messageId, StopWatch stopWatch, int block) {

		if (_log.isDebugEnabled()) {
			if ((messageId != 1) && ((messageId % 10) != 0)) {
				return;
			}

			_log.debug(
				"Adding message block " + block + " for " + messageId +
					" takes " + stopWatch.getTime() + " ms");
		}
	}

	protected void notifySubscribers(
			MBCategory category, MBMessage message, PortletPreferences prefs,
			ThemeDisplay themeDisplay, boolean update)
		throws PortalException, SystemException {

		try {
			if (category.isDiscussion()) {
				return;
			}

			if (prefs == null) {
				long ownerId = category.getGroupId();
				int ownerType = PortletKeys.PREFS_OWNER_TYPE_GROUP;
				long plid = PortletKeys.PREFS_PLID_SHARED;
				String portletId = PortletKeys.MESSAGE_BOARDS;
				String defaultPreferences = null;

				prefs = portletPreferencesLocalService.getPreferences(
					category.getCompanyId(), ownerId, ownerType, plid,
					portletId, defaultPreferences);
			}

			if (!update && MBUtil.getEmailMessageAddedEnabled(prefs)) {
			}
			else if (update && MBUtil.getEmailMessageUpdatedEnabled(prefs)) {
			}
			else {
				return;
			}

			Company company = companyPersistence.findByPrimaryKey(
				message.getCompanyId());

			Group group = groupPersistence.findByPrimaryKey(
				category.getGroupId());

			User user = userPersistence.findByPrimaryKey(message.getUserId());

			List categoryIds = new ArrayList();

			categoryIds.add(new Long(category.getCategoryId()));
			categoryIds.addAll(category.getAncestorCategoryIds());

			String messageURL = StringPool.BLANK;

			if (themeDisplay != null) {
				String portalURL = PortalUtil.getPortalURL(themeDisplay);
				String layoutURL = PortalUtil.getLayoutURL(themeDisplay);

				messageURL =
					portalURL + layoutURL + "/message_boards/message/" +
						message.getMessageId();
			}

			String portletName = PortalUtil.getPortletTitle(
				PortletKeys.MESSAGE_BOARDS, user);

			String fromName = MBUtil.getEmailFromName(prefs);
			String fromAddress = MBUtil.getEmailFromAddress(prefs);

			String mailingListAddress = StringPool.BLANK;

			if (PropsValues.POP_SERVER_NOTIFICATIONS_ENABLED) {
				mailingListAddress = MBUtil.getMailingListAddress(
					message.getCategoryId(), message.getMessageId(),
					company.getMx());
			}

			String replyToAddress = mailingListAddress;
			String messageId = MBUtil.getMailId(
				company.getMx(), message.getCategoryId(),
				message.getMessageId());

			fromName = StringUtil.replace(
				fromName,
				new String[] {
					"[$COMPANY_ID$]",
					"[$COMPANY_MX$]",
					"[$COMPANY_NAME$]",
					"[$COMMUNITY_NAME$]",
					"[$MAILING_LIST_ADDRESS$]",
					"[$MESSAGE_USER_ADDRESS$]",
					"[$MESSAGE_USER_NAME$]",
					"[$PORTLET_NAME$]"
				},
				new String[] {
					String.valueOf(company.getCompanyId()),
					company.getMx(),
					company.getName(),
					group.getName(),
					mailingListAddress,
					user.getEmailAddress(),
					user.getFullName(),
					portletName
				});

			fromAddress = StringUtil.replace(
				fromAddress,
				new String[] {
					"[$COMPANY_ID$]",
					"[$COMPANY_MX$]",
					"[$COMPANY_NAME$]",
					"[$COMMUNITY_NAME$]",
					"[$MAILING_LIST_ADDRESS$]",
					"[$MESSAGE_USER_ADDRESS$]",
					"[$MESSAGE_USER_NAME$]",
					"[$PORTLET_NAME$]"
				},
				new String[] {
					String.valueOf(company.getCompanyId()),
					company.getMx(),
					company.getName(),
					group.getName(),
					mailingListAddress,
					user.getEmailAddress(),
					user.getFullName(),
					portletName
				});

			String subjectPrefix = null;
			String body = null;
			String signature = null;

			if (update) {
				subjectPrefix = MBUtil.getEmailMessageUpdatedSubjectPrefix(
					prefs);
				body = MBUtil.getEmailMessageUpdatedBody(prefs);
				signature = MBUtil.getEmailMessageUpdatedSignature(prefs);
			}
			else {
				subjectPrefix = MBUtil.getEmailMessageAddedSubjectPrefix(prefs);
				body = MBUtil.getEmailMessageAddedBody(prefs);
				signature = MBUtil.getEmailMessageAddedSignature(prefs);
			}

			if (Validator.isNotNull(signature)) {
				body +=  "\n--\n" + signature;
			}

			subjectPrefix = StringUtil.replace(
				subjectPrefix,
				new String[] {
					"[$CATEGORY_NAME$]",
					"[$COMPANY_ID$]",
					"[$COMPANY_MX$]",
					"[$COMPANY_NAME$]",
					"[$COMMUNITY_NAME$]",
					"[$FROM_ADDRESS$]",
					"[$FROM_NAME$]",
  					"[$MAILING_LIST_ADDRESS$]",
					"[$MESSAGE_BODY$]",
					"[$MESSAGE_ID$]",
					"[$MESSAGE_SUBJECT$]",
					"[$MESSAGE_USER_ADDRESS$]",
					"[$MESSAGE_USER_NAME$]",
					"[$PORTAL_URL$]",
					"[$PORTLET_NAME$]"
				},
				new String[] {
					category.getName(),
					String.valueOf(company.getCompanyId()),
					company.getMx(),
					company.getName(),
					group.getName(),
					fromAddress,
					fromName,
					mailingListAddress,
					message.getBody(),
					String.valueOf(message.getMessageId()),
					message.getSubject(),
					user.getEmailAddress(),
					user.getFullName(),
					company.getVirtualHost(),
					portletName
				});

			body = StringUtil.replace(
				body,
				new String[] {
					"[$CATEGORY_NAME$]",
					"[$COMPANY_ID$]",
					"[$COMPANY_MX$]",
					"[$COMPANY_NAME$]",
					"[$COMMUNITY_NAME$]",
					"[$FROM_ADDRESS$]",
					"[$FROM_NAME$]",
  					"[$MAILING_LIST_ADDRESS$]",
					"[$MESSAGE_BODY$]",
					"[$MESSAGE_ID$]",
					"[$MESSAGE_SUBJECT$]",
					"[$MESSAGE_URL$]",
					"[$MESSAGE_USER_ADDRESS$]",
					"[$MESSAGE_USER_NAME$]",
					"[$PORTAL_URL$]",
					"[$PORTLET_NAME$]"
				},
				new String[] {
					category.getName(),
					String.valueOf(company.getCompanyId()),
					company.getMx(),
					company.getName(),
					group.getName(),
					fromAddress,
					fromName,
					mailingListAddress,
					message.getBody(),
					String.valueOf(message.getMessageId()),
					message.getSubject(),
					messageURL,
					user.getEmailAddress(),
					user.getFullName(),
					company.getVirtualHost(),
					portletName
				});

			String subject = message.getSubject();

			if (subject.indexOf(subjectPrefix) == -1) {
				subject = subjectPrefix + subject;
			}

			String inReplyTo = null;

			if (message.getParentMessageId() !=
					MBMessageImpl.DEFAULT_PARENT_MESSAGE_ID) {

				inReplyTo = MBUtil.getMailId(
					company.getMx(), message.getCategoryId(),
					message.getParentMessageId());
			}

			MBMessageProducer.produce(
				new String[] {
					String.valueOf(message.getCompanyId()),
					String.valueOf(message.getUserId()),
					StringUtil.merge(categoryIds),
					String.valueOf(message.getThreadId()),
					fromName, fromAddress, subject, body, replyToAddress,
					messageId, inReplyTo
				});
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	protected void sendBlogsCommentsEmail(
			long userId, long entryId, MBMessage message,
			ThemeDisplay themeDisplay)
		throws IOException, PortalException, SystemException {

		long companyId = message.getCompanyId();

		if (!PrefsPropsUtil.getBoolean(
				companyId, PropsUtil.BLOGS_EMAIL_COMMENTS_ADDED_ENABLED)) {

			return;
		}

		BlogsEntry entry = blogsEntryPersistence.findByPrimaryKey(entryId);

		String portalURL = PortalUtil.getPortalURL(themeDisplay);
		String layoutURL = PortalUtil.getLayoutURL(themeDisplay);

		String blogsEntryURL =
			portalURL + layoutURL + "/blogs/" + entry.getUrlTitle();

		User blogsUser = userPersistence.findByPrimaryKey(entry.getUserId());
		User commentsUser = userPersistence.findByPrimaryKey(userId);

		String fromName = PrefsPropsUtil.getString(
			companyId, PropsUtil.ADMIN_EMAIL_FROM_NAME);
		String fromAddress = PrefsPropsUtil.getString(
			companyId, PropsUtil.ADMIN_EMAIL_FROM_ADDRESS);

		String toName = blogsUser.getFullName();
		String toAddress = blogsUser.getEmailAddress();

		String subject = PrefsPropsUtil.getContent(
			companyId, PropsUtil.BLOGS_EMAIL_COMMENTS_ADDED_SUBJECT);
		String body = PrefsPropsUtil.getContent(
			companyId, PropsUtil.BLOGS_EMAIL_COMMENTS_ADDED_BODY);

		subject = StringUtil.replace(
			subject,
			new String[] {
				"[$BLOGS_COMMENTS_USER_ADDRESS$]",
				"[$BLOGS_COMMENTS_USER_NAME$]",
				"[$BLOGS_ENTRY_URL$]",
				"[$FROM_ADDRESS$]",
				"[$FROM_NAME$]",
				"[$TO_ADDRESS$]",
				"[$TO_NAME$]"
			},
			new String[] {
				commentsUser.getEmailAddress(),
				commentsUser.getFullName(),
				blogsEntryURL,
				fromAddress,
				fromName,
				toAddress,
				toName
			});

		body = StringUtil.replace(
			body,
			new String[] {
				"[$BLOGS_COMMENTS_USER_ADDRESS$]",
				"[$BLOGS_COMMENTS_USER_NAME$]",
				"[$BLOGS_ENTRY_URL$]",
				"[$FROM_ADDRESS$]",
				"[$FROM_NAME$]",
				"[$TO_ADDRESS$]",
				"[$TO_NAME$]"
			},
			new String[] {
				commentsUser.getEmailAddress(),
				commentsUser.getFullName(),
				blogsEntryURL,
				fromAddress,
				fromName,
				toAddress,
				toName
			});

		InternetAddress from = new InternetAddress(fromAddress, fromName);

		InternetAddress to = new InternetAddress(toAddress, toName);

		MailMessage mailMessage = new MailMessage(
			from, to, subject, body, true);

		mailService.sendEmail(mailMessage);
	}

	protected void validate(String subject, String body)
		throws PortalException {

		if (Validator.isNull(subject)) {
			throw new MessageSubjectException();
		}

		if (Validator.isNull(body)) {
			throw new MessageBodyException();
		}
	}

	private static Log _log =
		LogFactory.getLog(MBMessageLocalServiceImpl.class);

}