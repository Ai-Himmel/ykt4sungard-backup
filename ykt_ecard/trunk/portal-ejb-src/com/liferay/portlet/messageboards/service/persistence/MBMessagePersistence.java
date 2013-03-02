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

package com.liferay.portlet.messageboards.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.messageboards.NoSuchMessageException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="MBMessagePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MBMessagePersistence extends BasePersistence {
	public com.liferay.portlet.messageboards.model.MBMessage create(
		MBMessagePK mbMessagePK) {
		return new com.liferay.portlet.messageboards.model.MBMessage(mbMessagePK);
	}

	public com.liferay.portlet.messageboards.model.MBMessage remove(
		MBMessagePK mbMessagePK) throws NoSuchMessageException, SystemException {
		Session session = null;

		try {
			session = openSession();

			MBMessageHBM mbMessageHBM = (MBMessageHBM)session.get(MBMessageHBM.class,
					mbMessagePK);

			if (mbMessageHBM == null) {
				_log.warn("No MBMessage exists with the primary key of " +
					mbMessagePK.toString());
				throw new NoSuchMessageException(mbMessagePK.toString());
			}

			com.liferay.portlet.messageboards.model.MBMessage mbMessage = MBMessageHBMUtil.model(mbMessageHBM);
			session.delete(mbMessageHBM);
			session.flush();
			MBMessagePool.remove(mbMessagePK);

			return mbMessage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage update(
		com.liferay.portlet.messageboards.model.MBMessage mbMessage)
		throws SystemException {
		Session session = null;

		try {
			if (mbMessage.isNew() || mbMessage.isModified()) {
				session = openSession();

				if (mbMessage.isNew()) {
					MBMessageHBM mbMessageHBM = new MBMessageHBM(mbMessage.getMessageId(),
							mbMessage.getTopicId(), mbMessage.getCompanyId(),
							mbMessage.getUserId(), mbMessage.getUserName(),
							mbMessage.getCreateDate(),
							mbMessage.getModifiedDate(),
							mbMessage.getThreadId(),
							mbMessage.getParentMessageId(),
							mbMessage.getSubject(), mbMessage.getBody(),
							mbMessage.getAttachments(), mbMessage.getAnonymous());
					session.save(mbMessageHBM);
					session.flush();
				}
				else {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)session.get(MBMessageHBM.class,
							mbMessage.getPrimaryKey());

					if (mbMessageHBM != null) {
						mbMessageHBM.setCompanyId(mbMessage.getCompanyId());
						mbMessageHBM.setUserId(mbMessage.getUserId());
						mbMessageHBM.setUserName(mbMessage.getUserName());
						mbMessageHBM.setCreateDate(mbMessage.getCreateDate());
						mbMessageHBM.setModifiedDate(mbMessage.getModifiedDate());
						mbMessageHBM.setThreadId(mbMessage.getThreadId());
						mbMessageHBM.setParentMessageId(mbMessage.getParentMessageId());
						mbMessageHBM.setSubject(mbMessage.getSubject());
						mbMessageHBM.setBody(mbMessage.getBody());
						mbMessageHBM.setAttachments(mbMessage.getAttachments());
						mbMessageHBM.setAnonymous(mbMessage.getAnonymous());
						session.flush();
					}
					else {
						mbMessageHBM = new MBMessageHBM(mbMessage.getMessageId(),
								mbMessage.getTopicId(),
								mbMessage.getCompanyId(),
								mbMessage.getUserId(), mbMessage.getUserName(),
								mbMessage.getCreateDate(),
								mbMessage.getModifiedDate(),
								mbMessage.getThreadId(),
								mbMessage.getParentMessageId(),
								mbMessage.getSubject(), mbMessage.getBody(),
								mbMessage.getAttachments(),
								mbMessage.getAnonymous());
						session.save(mbMessageHBM);
						session.flush();
					}
				}

				mbMessage.setNew(false);
				mbMessage.setModified(false);
				mbMessage.protect();
				MBMessagePool.put(mbMessage.getPrimaryKey(), mbMessage);
			}

			return mbMessage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByPrimaryKey(
		MBMessagePK mbMessagePK) throws NoSuchMessageException, SystemException {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = MBMessagePool.get(mbMessagePK);
		Session session = null;

		try {
			if (mbMessage == null) {
				session = openSession();

				MBMessageHBM mbMessageHBM = (MBMessageHBM)session.get(MBMessageHBM.class,
						mbMessagePK);

				if (mbMessageHBM == null) {
					_log.warn("No MBMessage exists with the primary key of " +
						mbMessagePK.toString());
					throw new NoSuchMessageException(mbMessagePK.toString());
				}

				mbMessage = MBMessageHBMUtil.model(mbMessageHBM);
			}

			return mbMessage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				list.add(MBMessageHBMUtil.model(mbMessageHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(String companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
					list.add(MBMessageHBMUtil.model(mbMessageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);
						list.add(MBMessageHBMUtil.model(mbMessageHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage[] findByCompanyId_PrevAndNext(
		MBMessagePK mbMessagePK, String companyId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = findByPrimaryKey(mbMessagePK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.messageboards.model.MBMessage[] array = new com.liferay.portlet.messageboards.model.MBMessage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);

					if (mbMessageHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBMessage curMBMessage =
						MBMessageHBMUtil.model(mbMessageHBM);
					int value = obc.compare(mbMessage, curMBMessage);

					if (value == 0) {
						if (!mbMessage.equals(curMBMessage)) {
							break;
						}

						array[1] = curMBMessage;

						if (sr.previous()) {
							array[0] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				list.add(MBMessageHBMUtil.model(mbMessageHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByUserId(String userId, int begin, int end)
		throws SystemException {
		return findByUserId(userId, begin, end, null);
	}

	public List findByUserId(String userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
					list.add(MBMessageHBMUtil.model(mbMessageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);
						list.add(MBMessageHBMUtil.model(mbMessageHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage[] findByUserId_PrevAndNext(
		MBMessagePK mbMessagePK, String userId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = findByPrimaryKey(mbMessagePK);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.messageboards.model.MBMessage[] array = new com.liferay.portlet.messageboards.model.MBMessage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);

					if (mbMessageHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBMessage curMBMessage =
						MBMessageHBMUtil.model(mbMessageHBM);
					int value = obc.compare(mbMessage, curMBMessage);

					if (value == 0) {
						if (!mbMessage.equals(curMBMessage)) {
							break;
						}

						array[1] = curMBMessage;

						if (sr.previous()) {
							array[0] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByTopicId(String topicId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				list.add(MBMessageHBMUtil.model(mbMessageHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByTopicId(String topicId, int begin, int end)
		throws SystemException {
		return findByTopicId(topicId, begin, end, null);
	}

	public List findByTopicId(String topicId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
					list.add(MBMessageHBMUtil.model(mbMessageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);
						list.add(MBMessageHBMUtil.model(mbMessageHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByTopicId_First(
		String topicId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		List list = findByTopicId(topicId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByTopicId_Last(
		String topicId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		int count = countByTopicId(topicId);
		List list = findByTopicId(topicId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage[] findByTopicId_PrevAndNext(
		MBMessagePK mbMessagePK, String topicId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = findByPrimaryKey(mbMessagePK);
		int count = countByTopicId(topicId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			com.liferay.portlet.messageboards.model.MBMessage[] array = new com.liferay.portlet.messageboards.model.MBMessage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);

					if (mbMessageHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBMessage curMBMessage =
						MBMessageHBMUtil.model(mbMessageHBM);
					int value = obc.compare(mbMessage, curMBMessage);

					if (value == 0) {
						if (!mbMessage.equals(curMBMessage)) {
							break;
						}

						array[1] = curMBMessage;

						if (sr.previous()) {
							array[0] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByThreadId(String threadId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				list.add(MBMessageHBMUtil.model(mbMessageHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByThreadId(String threadId, int begin, int end)
		throws SystemException {
		return findByThreadId(threadId, begin, end, null);
	}

	public List findByThreadId(String threadId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
					list.add(MBMessageHBMUtil.model(mbMessageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);
						list.add(MBMessageHBMUtil.model(mbMessageHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByThreadId_First(
		String threadId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		List list = findByThreadId(threadId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByThreadId_Last(
		String threadId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		int count = countByThreadId(threadId);
		List list = findByThreadId(threadId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage[] findByThreadId_PrevAndNext(
		MBMessagePK mbMessagePK, String threadId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = findByPrimaryKey(mbMessagePK);
		int count = countByThreadId(threadId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);

			com.liferay.portlet.messageboards.model.MBMessage[] array = new com.liferay.portlet.messageboards.model.MBMessage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);

					if (mbMessageHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBMessage curMBMessage =
						MBMessageHBMUtil.model(mbMessageHBM);
					int value = obc.compare(mbMessage, curMBMessage);

					if (value == 0) {
						if (!mbMessage.equals(curMBMessage)) {
							break;
						}

						array[1] = curMBMessage;

						if (sr.previous()) {
							array[0] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByT_P(String threadId, String parentMessageId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" AND ");
			query.append("parentMessageId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);
			q.setString(queryPos++, parentMessageId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				list.add(MBMessageHBMUtil.model(mbMessageHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByT_P(String threadId, String parentMessageId, int begin,
		int end) throws SystemException {
		return findByT_P(threadId, parentMessageId, begin, end, null);
	}

	public List findByT_P(String threadId, String parentMessageId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" AND ");
			query.append("parentMessageId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);
			q.setString(queryPos++, parentMessageId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
					list.add(MBMessageHBMUtil.model(mbMessageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);
						list.add(MBMessageHBMUtil.model(mbMessageHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByT_P_First(
		String threadId, String parentMessageId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		List list = findByT_P(threadId, parentMessageId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage findByT_P_Last(
		String threadId, String parentMessageId, OrderByComparator obc)
		throws NoSuchMessageException, SystemException {
		int count = countByT_P(threadId, parentMessageId);
		List list = findByT_P(threadId, parentMessageId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchMessageException();
		}
		else {
			return (com.liferay.portlet.messageboards.model.MBMessage)list.get(0);
		}
	}

	public com.liferay.portlet.messageboards.model.MBMessage[] findByT_P_PrevAndNext(
		MBMessagePK mbMessagePK, String threadId, String parentMessageId,
		OrderByComparator obc) throws NoSuchMessageException, SystemException {
		com.liferay.portlet.messageboards.model.MBMessage mbMessage = findByPrimaryKey(mbMessagePK);
		int count = countByT_P(threadId, parentMessageId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" AND ");
			query.append("parentMessageId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC").append(", ");
				query.append("messageId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);
			q.setString(queryPos++, parentMessageId);

			com.liferay.portlet.messageboards.model.MBMessage[] array = new com.liferay.portlet.messageboards.model.MBMessage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MBMessageHBM mbMessageHBM = (MBMessageHBM)sr.get(0);

					if (mbMessageHBM == null) {
						break;
					}

					com.liferay.portlet.messageboards.model.MBMessage curMBMessage =
						MBMessageHBMUtil.model(mbMessageHBM);
					int value = obc.compare(mbMessage, curMBMessage);

					if (value == 0) {
						if (!mbMessage.equals(curMBMessage)) {
							break;
						}

						array[1] = curMBMessage;

						if (sr.previous()) {
							array[0] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MBMessageHBMUtil.model((MBMessageHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				list.add(MBMessageHBMUtil.model(mbMessageHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				MBMessagePool.remove((MBMessagePK)mbMessageHBM.getPrimaryKey());
				session.delete(mbMessageHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				MBMessagePool.remove((MBMessagePK)mbMessageHBM.getPrimaryKey());
				session.delete(mbMessageHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByTopicId(String topicId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				MBMessagePool.remove((MBMessagePK)mbMessageHBM.getPrimaryKey());
				session.delete(mbMessageHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByThreadId(String threadId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				MBMessagePool.remove((MBMessagePK)mbMessageHBM.getPrimaryKey());
				session.delete(mbMessageHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByT_P(String threadId, String parentMessageId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" AND ");
			query.append("parentMessageId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC").append(", ");
			query.append("messageId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);
			q.setString(queryPos++, parentMessageId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MBMessageHBM mbMessageHBM = (MBMessageHBM)itr.next();
				MBMessagePool.remove((MBMessagePK)mbMessageHBM.getPrimaryKey());
				session.delete(mbMessageHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByTopicId(String topicId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("topicId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, topicId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByThreadId(String threadId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByT_P(String threadId, String parentMessageId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM MBMessage IN CLASS com.liferay.portlet.messageboards.service.persistence.MBMessageHBM WHERE ");
			query.append("threadId = ?");
			query.append(" AND ");
			query.append("parentMessageId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, threadId);
			q.setString(queryPos++, parentMessageId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	private static final Log _log = LogFactory.getLog(MBMessagePersistence.class);
}