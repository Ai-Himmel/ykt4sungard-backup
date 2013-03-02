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

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.documentlibrary.DuplicateFileException;
import com.liferay.documentlibrary.NoSuchDirectoryException;
import com.liferay.documentlibrary.service.spring.DLServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.lucene.LuceneFields;
import com.liferay.portal.lucene.LuceneUtil;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portlet.messageboards.MessageBodyException;
import com.liferay.portlet.messageboards.MessageSubjectException;
import com.liferay.portlet.messageboards.NoSuchMessageException;
import com.liferay.portlet.messageboards.NoSuchThreadException;
import com.liferay.portlet.messageboards.TopicNameException;
import com.liferay.portlet.messageboards.TopicReadRolesException;
import com.liferay.portlet.messageboards.TopicWriteRolesException;
import com.liferay.portlet.messageboards.model.MBMessage;
import com.liferay.portlet.messageboards.model.MBThread;
import com.liferay.portlet.messageboards.model.MBTopic;
import com.liferay.portlet.messageboards.service.persistence.MBMessagePK;
import com.liferay.portlet.messageboards.service.persistence.MBMessageUtil;
import com.liferay.portlet.messageboards.service.persistence.MBThreadUtil;
import com.liferay.portlet.messageboards.service.persistence.MBTopicUtil;
import com.liferay.portlet.messageboards.service.spring.MBTopicLocalServiceUtil;
import com.liferay.portlet.messageboards.service.spring.MBTopicService;
import com.liferay.portlet.messageboards.util.Indexer;
import com.liferay.util.ObjectValuePair;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lucene.Hits;

import java.io.IOException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.lucene.analysis.WhitespaceAnalyzer;
import org.apache.lucene.index.Term;
import org.apache.lucene.queryParser.ParseException;
import org.apache.lucene.queryParser.QueryParser;
import org.apache.lucene.search.BooleanQuery;
import org.apache.lucene.search.Query;
import org.apache.lucene.search.Searcher;
import org.apache.lucene.search.TermQuery;

/**
 * <a href="MBTopicServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.3 $
 *
 */
public class MBTopicServiceImpl
	extends PrincipalBean implements MBTopicService {

	// Business methods

	public MBTopic addTopic(
			String portletId, String groupId, String readRoles,
			String writeRoles, String name, String description)
		throws PortalException, SystemException {

		_validate(readRoles, writeRoles, name);

		User user = getUser();

		String topicId = Long.toString(CounterServiceUtil.increment(
			MBTopic.class.getName()));

		MBTopic topic = MBTopicUtil.create(topicId);

		Date now = new Date();

		topic.setPortletId(portletId);
		topic.setGroupId(groupId);
		topic.setCompanyId(user.getCompanyId());
		topic.setUserId(user.getUserId());
		topic.setUserName(user.getFullName());
		topic.setCreateDate(now);
		topic.setModifiedDate(now);
		topic.setReadRoles(readRoles);
		topic.setWriteRoles(writeRoles);
		topic.setName(name);
		topic.setDescription(description);

		MBTopicUtil.update(topic);

		return topic;
	}

	public void deleteTopic(String topicId)
		throws PortalException, SystemException {

		if (!hasAdmin(topicId)) {
			throw new PrincipalException();
		}

		MBTopicLocalServiceUtil.deleteTopic(topicId);
	}

	public MBTopic getTopic(String topicId)
		throws PortalException, SystemException {

		if (!hasRead(topicId)) {
			throw new PrincipalException();
		}

		return MBTopicUtil.findByPrimaryKey(topicId);
	}

	public List getTopics(String portletId, String groupId, String companyId)
		throws PortalException, SystemException {

		return MBTopicUtil.findByP_G_C_R(
			portletId, groupId, companyId, _getRoleNames());
	}

	public List getTopics(
			String portletId, String groupId, String companyId, int begin,
			int end)
		throws PortalException, SystemException {

		return MBTopicUtil.findByP_G_C_R(
			portletId, groupId, companyId, _getRoleNames(), begin, end);
	}

	public int getTopicsSize(
			String portletId, String groupId, String companyId)
		throws PortalException, SystemException {

		return MBTopicUtil.countByP_G_C_R(
			portletId, groupId, companyId, _getRoleNames());
	}

	public MBMessage postNewThread(
			String topicId, String subject, String body, List files,
			boolean anonymous)
		throws PortalException, SystemException {

		return postReply(topicId, null, null, subject, body, files, anonymous);
	}

	public MBMessage postReply(
			String topicId, String threadId, String parentMessageId,
			String subject, String body, List files, boolean anonymous)
		throws PortalException, SystemException {

		if (!hasWrite(topicId)) {
			throw new PrincipalException();
		}

		if (Validator.isNull(subject)) {
			throw new MessageSubjectException();
		}

		if (Validator.isNull(body)) {
			throw new MessageBodyException();
		}

		User user = getUser();

		String rootMessageId = Long.toString(CounterServiceUtil.increment(
			MBMessage.class.getName() + "." + topicId));

		String messageId = rootMessageId;

		MBMessage message = MBMessageUtil.create(
			new MBMessagePK(messageId, topicId));

		Date now = new Date();

		message.setCompanyId(user.getCompanyId());

		// File attachments

		if (files.size() > 0) {
			String companyId = message.getCompanyId();
			String portletId = Company.SYSTEM;
			String groupId = Group.DEFAULT_PARENT_GROUP_ID;
			String repositoryId = Company.SYSTEM;
			String dirName = message.getAttachmentsDir();

			try {
				DLServiceUtil.deleteDirectory(
					companyId, portletId, repositoryId, dirName);
			}
			catch (NoSuchDirectoryException nsde) {
			}

			DLServiceUtil.addDirectory(companyId, repositoryId, dirName);

			for (int i = 0; i < files.size(); i++) {
				ObjectValuePair ovp = (ObjectValuePair)files.get(i);

				String fileName = (String)ovp.getKey();
				byte[] byteArray = (byte[])ovp.getValue();

				try {
					DLServiceUtil.addFile(
						companyId, portletId, groupId, repositoryId,
						dirName + "/" + fileName, byteArray);
				}
				catch (DuplicateFileException dfe) {
				}
			}
		}

		// Find thread

		try {
			MBMessageUtil.findByPrimaryKey(
				new MBMessagePK(parentMessageId, topicId));
		}
		catch (NoSuchMessageException nsme) {
			parentMessageId = MBMessage.DEFAULT_PARENT_MESSAGE_ID;
		}

		MBThread thread = null;

		if (threadId != null) {
			try {
				thread = MBThreadUtil.findByPrimaryKey(threadId);
			}
			catch (NoSuchThreadException nste) {
			}
		}

		if (thread == null ||
			parentMessageId.equals(MBMessage.DEFAULT_PARENT_MESSAGE_ID)) {

			// Add thread

			threadId = Long.toString(CounterServiceUtil.increment(
				MBThread.class.getName()));

			thread = MBThreadUtil.create(threadId);

			thread.setRootMessageId(rootMessageId);
			thread.setTopicId(topicId);

			MBThreadUtil.update(thread);
		}

		// Update thread

		thread.setMessageCount(thread.getMessageCount() + 1);
		thread.setLastPostDate(now);

		MBThreadUtil.update(thread);

		// Add message

		message.setCompanyId(user.getCompanyId());
		message.setUserId(user.getUserId());
		message.setUserName(user.getFullName());
		message.setCreateDate(now);
		message.setModifiedDate(now);
		message.setThreadId(threadId);
		message.setParentMessageId(parentMessageId);
		message.setSubject(subject);
		message.setBody(body);
		message.setAttachments((files.size() > 0 ? true : false));
		message.setAnonymous(anonymous);

		MBMessageUtil.update(message);

		// Update topic

		MBTopic topic = MBTopicUtil.findByPrimaryKey(topicId);

		topic.setLastPostDate(now);

		MBTopicUtil.update(topic);

		// Update lucene

		try {
			Indexer.addMessage(
				topic.getCompanyId(), topic.getPortletId(), topic.getGroupId(),
				topicId, messageId, subject, body);
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return message;
	}

	public void reIndex(String[] ids) throws SystemException {
		try {
			String companyId = ids[0];

			Iterator itr1 = MBTopicUtil.findByCompanyId(companyId).iterator();

			while (itr1.hasNext()) {
				MBTopic topic = (MBTopic)itr1.next();

				String topicId = topic.getTopicId();

				Iterator itr2 = MBMessageUtil.findByTopicId(topicId).iterator();

				while (itr2.hasNext()) {
					MBMessage message = (MBMessage)itr2.next();

					String portletId = topic.getPortletId();
					String groupId = topic.getGroupId();
					String messageId = message.getMessageId();
					String title = message.getSubject();
					String content = message.getBody();

					try {
						Indexer.addMessage(
							companyId, portletId, groupId, topicId, messageId,
							title, content);
					}
					catch (Exception e1) {

						// Continue indexing even if one message fails

						_log.error(e1.getMessage());
					}
				}
			}
		}
		catch (SystemException se) {
			throw se;
		}
		catch (Exception e2) {
			throw new SystemException(e2);
		}
	}

	public Hits search(
   			String companyId, String portletId, String groupId,
			String[] topicIds, String keywords)
		throws SystemException {

		try {
			Hits hits = new Hits();

			if (Validator.isNull(keywords)) {
				return hits;
			}

			BooleanQuery booleanQuery = new BooleanQuery();

			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.PORTLET_ID, portletId);
			LuceneUtil.addRequiredTerm(
				booleanQuery, LuceneFields.GROUP_ID, groupId);

			LuceneUtil.addTerm(booleanQuery, LuceneFields.TITLE, keywords);
			LuceneUtil.addTerm(booleanQuery, LuceneFields.CONTENT, keywords);

			if ((topicIds != null) && (topicIds.length > 0)) {
				BooleanQuery topicIdsQuery = new BooleanQuery();

				for (int i = 0; i < topicIds.length; i++) {
					topicIdsQuery.add(new TermQuery(new Term(
						"topicId", topicIds[i])), false, false);
				}

				booleanQuery.add(topicIdsQuery, true, false);
			}

			Searcher searcher = LuceneUtil.getSearcher(companyId);

			Query query = QueryParser.parse(
				booleanQuery.toString(), LuceneFields.CONTENT,
				new WhitespaceAnalyzer());

			hits.recordHits(searcher.search(query));

			return hits;
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
		catch (ParseException pe) {
			throw new SystemException(pe);
		}
	}

	public MBTopic updateTopic(
			String topicId, String readRoles, String writeRoles, String name,
			String description)
		throws PortalException, SystemException {

		_validate(readRoles, writeRoles, name);

		if (!hasAdmin(topicId)) {
			throw new PrincipalException();
		}

		MBTopic topic = MBTopicUtil.findByPrimaryKey(topicId);

		topic.setModifiedDate(new Date());
		topic.setReadRoles(readRoles);
		topic.setWriteRoles(writeRoles);
		topic.setName(name);
		topic.setDescription(description);

		MBTopicUtil.update(topic);

		return topic;
	}

	// Permission methods

	public boolean hasAdmin(String topicId)
		throws PortalException, SystemException {

		MBTopic topic = MBTopicUtil.findByPrimaryKey(topicId);

		User user = null;

		try  {
			user = getUser();
		}
		catch (PrincipalException pe) {
			return false;
		}

		if ((topic.getUserId().equals(user.getUserId())) ||
			(user.getCompanyId().equals(topic.getCompanyId()) &&
			 RoleServiceUtil.hasRole(
				user.getUserId(), Role.MESSAGE_BOARDS_ADMIN))) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasRead(String topicId)
		throws PortalException, SystemException {

		MBTopic topic = MBTopicUtil.findByPrimaryKey(topicId);

		User user = null;

		try  {
			user = getUser();
		}
		catch (PrincipalException pe) {
			String[] readRoles = StringUtil.split(topic.getReadRoles());

			for (int i = 0; i < readRoles.length; i++) {
				if (readRoles[i].equals(Role.GUEST)) {
					return true;
				}
			}

			return false;
		}

		if (user.getCompanyId().equals(topic.getCompanyId()) &&
			RoleServiceUtil.hasRoles(
				user.getUserId(), StringUtil.split(topic.getReadRoles()))) {

			return true;
		}
		else {
			return false;
		}
	}

	public boolean hasWrite(String topicId)
		throws PortalException, SystemException {

		MBTopic topic = MBTopicUtil.findByPrimaryKey(topicId);

		if (getUser().getCompanyId().equals(topic.getCompanyId()) &&
			RoleServiceUtil.hasRoles(
				getUserId(), StringUtil.split(topic.getWriteRoles()))) {

			return true;
		}
		else {
			return false;
		}
	}

	// Private methods

	private String[] _getRoleNames() throws PortalException, SystemException {
		String[] roleNames = null;

		try {
			User user = getUser();

			if (RoleServiceUtil.isAdministrator(user.getUserId())) {

				// Administrators pass in an empty array of role names so that
				// roles are not checked

				roleNames = new String[0];
			}
			else {
				List roles = UserServiceUtil.getRoles(user.getUserId());

				roleNames = new String[roles.size()];

				for (int i = 0; i < roles.size(); i++) {
					Role role = (Role)roles.get(i);

					roleNames[i] = role.getName();
				}

				if (roleNames.length == 0) {

					// This can happen, but needs to be changed so that
					// authenticated users always have at least one role

					roleNames = new String[] {Role.ADMINISTRATOR};
				}
			}
		}
		catch (PrincipalException pe) {

			// Unauthenticated users only pass in the Guest role name

			roleNames = new String[] {Role.GUEST};
		}

		return roleNames;
	}

	private void _validate(String readRoles, String writeRoles, String name)
		throws PortalException, SystemException {

		String[] readRolesArray = StringUtil.split(readRoles);

		if (readRolesArray.length == 0 ||
			!RoleServiceUtil.exists(readRolesArray)) {

			throw new TopicReadRolesException();
		}

		String[] writeRolesArray = StringUtil.split(writeRoles);

		if (writeRolesArray.length == 0 ||
			!RoleServiceUtil.exists(writeRolesArray)) {

			throw new TopicWriteRolesException();
		}

		if (Validator.isNull(name)) {
			throw new TopicNameException();
		}
	}

	private static final Log _log = LogFactory.getLog(MBTopicServiceImpl.class);

}