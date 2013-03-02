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

package com.liferay.portlet.journal.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.journal.NoSuchArticleException;

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
 * <a href="JournalArticlePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalArticlePersistence extends BasePersistence {
	public com.liferay.portlet.journal.model.JournalArticle create(
		JournalArticlePK journalArticlePK) {
		return new com.liferay.portlet.journal.model.JournalArticle(journalArticlePK);
	}

	public com.liferay.portlet.journal.model.JournalArticle remove(
		JournalArticlePK journalArticlePK)
		throws NoSuchArticleException, SystemException {
		Session session = null;

		try {
			session = openSession();

			JournalArticleHBM journalArticleHBM = (JournalArticleHBM)session.get(JournalArticleHBM.class,
					journalArticlePK);

			if (journalArticleHBM == null) {
				_log.warn("No JournalArticle exists with the primary key of " +
					journalArticlePK.toString());
				throw new NoSuchArticleException(journalArticlePK.toString());
			}

			com.liferay.portlet.journal.model.JournalArticle journalArticle = JournalArticleHBMUtil.model(journalArticleHBM);
			session.delete(journalArticleHBM);
			session.flush();
			JournalArticlePool.remove(journalArticlePK);

			return journalArticle;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle update(
		com.liferay.portlet.journal.model.JournalArticle journalArticle)
		throws SystemException {
		Session session = null;

		try {
			if (journalArticle.isNew() || journalArticle.isModified()) {
				session = openSession();

				if (journalArticle.isNew()) {
					JournalArticleHBM journalArticleHBM = new JournalArticleHBM(journalArticle.getArticleId(),
							journalArticle.getVersion(),
							journalArticle.getPortletId(),
							journalArticle.getGroupId(),
							journalArticle.getCompanyId(),
							journalArticle.getUserId(),
							journalArticle.getUserName(),
							journalArticle.getCreateDate(),
							journalArticle.getModifiedDate(),
							journalArticle.getTitle(),
							journalArticle.getContent(),
							journalArticle.getType(),
							journalArticle.getStructureId(),
							journalArticle.getTemplateId(),
							journalArticle.getDisplayDate(),
							journalArticle.getExpirationDate(),
							journalArticle.getApproved(),
							journalArticle.getApprovedByUserId(),
							journalArticle.getApprovedByUserName());
					session.save(journalArticleHBM);
					session.flush();
				}
				else {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)session.get(JournalArticleHBM.class,
							journalArticle.getPrimaryKey());

					if (journalArticleHBM != null) {
						journalArticleHBM.setPortletId(journalArticle.getPortletId());
						journalArticleHBM.setGroupId(journalArticle.getGroupId());
						journalArticleHBM.setCompanyId(journalArticle.getCompanyId());
						journalArticleHBM.setUserId(journalArticle.getUserId());
						journalArticleHBM.setUserName(journalArticle.getUserName());
						journalArticleHBM.setCreateDate(journalArticle.getCreateDate());
						journalArticleHBM.setModifiedDate(journalArticle.getModifiedDate());
						journalArticleHBM.setTitle(journalArticle.getTitle());
						journalArticleHBM.setContent(journalArticle.getContent());
						journalArticleHBM.setType(journalArticle.getType());
						journalArticleHBM.setStructureId(journalArticle.getStructureId());
						journalArticleHBM.setTemplateId(journalArticle.getTemplateId());
						journalArticleHBM.setDisplayDate(journalArticle.getDisplayDate());
						journalArticleHBM.setExpirationDate(journalArticle.getExpirationDate());
						journalArticleHBM.setApproved(journalArticle.getApproved());
						journalArticleHBM.setApprovedByUserId(journalArticle.getApprovedByUserId());
						journalArticleHBM.setApprovedByUserName(journalArticle.getApprovedByUserName());
						session.flush();
					}
					else {
						journalArticleHBM = new JournalArticleHBM(journalArticle.getArticleId(),
								journalArticle.getVersion(),
								journalArticle.getPortletId(),
								journalArticle.getGroupId(),
								journalArticle.getCompanyId(),
								journalArticle.getUserId(),
								journalArticle.getUserName(),
								journalArticle.getCreateDate(),
								journalArticle.getModifiedDate(),
								journalArticle.getTitle(),
								journalArticle.getContent(),
								journalArticle.getType(),
								journalArticle.getStructureId(),
								journalArticle.getTemplateId(),
								journalArticle.getDisplayDate(),
								journalArticle.getExpirationDate(),
								journalArticle.getApproved(),
								journalArticle.getApprovedByUserId(),
								journalArticle.getApprovedByUserName());
						session.save(journalArticleHBM);
						session.flush();
					}
				}

				journalArticle.setNew(false);
				journalArticle.setModified(false);
				journalArticle.protect();
				JournalArticlePool.put(journalArticle.getPrimaryKey(),
					journalArticle);
			}

			return journalArticle;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByPrimaryKey(
		JournalArticlePK journalArticlePK)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = JournalArticlePool.get(journalArticlePK);
		Session session = null;

		try {
			if (journalArticle == null) {
				session = openSession();

				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)session.get(JournalArticleHBM.class,
						journalArticlePK);

				if (journalArticleHBM == null) {
					_log.warn(
						"No JournalArticle exists with the primary key of " +
						journalArticlePK.toString());
					throw new NoSuchArticleException(journalArticlePK.toString());
				}

				journalArticle = JournalArticleHBMUtil.model(journalArticleHBM);
			}

			return journalArticle;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByArticleId(String articleId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByArticleId(String articleId, int begin, int end)
		throws SystemException {
		return findByArticleId(articleId, begin, end, null);
	}

	public List findByArticleId(String articleId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByArticleId_First(
		String articleId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByArticleId(articleId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByArticleId_Last(
		String articleId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByArticleId(articleId);
		List list = findByArticleId(articleId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByArticleId_PrevAndNext(
		JournalArticlePK journalArticlePK, String articleId,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByArticleId(articleId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByGroupId(String groupId, int begin, int end)
		throws SystemException {
		return findByGroupId(groupId, begin, end, null);
	}

	public List findByGroupId(String groupId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByGroupId_PrevAndNext(
		JournalArticlePK journalArticlePK, String groupId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
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
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByCompanyId_PrevAndNext(
		JournalArticlePK journalArticlePK, String companyId,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByStructureId(String structureId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByStructureId(String structureId, int begin, int end)
		throws SystemException {
		return findByStructureId(structureId, begin, end, null);
	}

	public List findByStructureId(String structureId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByStructureId_First(
		String structureId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByStructureId(structureId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByStructureId_Last(
		String structureId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByStructureId(structureId);
		List list = findByStructureId(structureId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByStructureId_PrevAndNext(
		JournalArticlePK journalArticlePK, String structureId,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByStructureId(structureId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByTemplateId(String templateId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("templateId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, templateId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByTemplateId(String templateId, int begin, int end)
		throws SystemException {
		return findByTemplateId(templateId, begin, end, null);
	}

	public List findByTemplateId(String templateId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("templateId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, templateId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByTemplateId_First(
		String templateId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByTemplateId(templateId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByTemplateId_Last(
		String templateId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByTemplateId(templateId);
		List list = findByTemplateId(templateId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByTemplateId_PrevAndNext(
		JournalArticlePK journalArticlePK, String templateId,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByTemplateId(templateId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("templateId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, templateId);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByA_A(String articleId, boolean approved)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByA_A(String articleId, boolean approved, int begin, int end)
		throws SystemException {
		return findByA_A(articleId, approved, begin, end, null);
	}

	public List findByA_A(String articleId, boolean approved, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);
			q.setBoolean(queryPos++, approved);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByA_A_First(
		String articleId, boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByA_A(articleId, approved, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByA_A_Last(
		String articleId, boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByA_A(articleId, approved);
		List list = findByA_A(articleId, approved, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByA_A_PrevAndNext(
		JournalArticlePK journalArticlePK, String articleId, boolean approved,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByA_A(articleId, approved);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);
			q.setBoolean(queryPos++, approved);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByP_G_C(String portletId, String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByP_G_C(String portletId, String groupId, String companyId,
		int begin, int end) throws SystemException {
		return findByP_G_C(portletId, groupId, companyId, begin, end, null);
	}

	public List findByP_G_C(String portletId, String groupId, String companyId,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_First(
		String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		List list = findByP_G_C(portletId, groupId, companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_Last(
		String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		int count = countByP_G_C(portletId, groupId, companyId);
		List list = findByP_G_C(portletId, groupId, companyId, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_PrevAndNext(
		JournalArticlePK journalArticlePK, String portletId, String groupId,
		String companyId, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByP_G_C(portletId, groupId, companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByP_G_C_T(String portletId, String groupId,
		String companyId, String type) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByP_G_C_T(String portletId, String groupId,
		String companyId, String type, int begin, int end)
		throws SystemException {
		return findByP_G_C_T(portletId, groupId, companyId, type, begin, end,
			null);
	}

	public List findByP_G_C_T(String portletId, String groupId,
		String companyId, String type, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_First(
		String portletId, String groupId, String companyId, String type,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		List list = findByP_G_C_T(portletId, groupId, companyId, type, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_Last(
		String portletId, String groupId, String companyId, String type,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		int count = countByP_G_C_T(portletId, groupId, companyId, type);
		List list = findByP_G_C_T(portletId, groupId, companyId, type,
				count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_T_PrevAndNext(
		JournalArticlePK journalArticlePK, String portletId, String groupId,
		String companyId, String type, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByP_G_C_T(portletId, groupId, companyId, type);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByP_G_C_A(String portletId, String groupId,
		String companyId, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByP_G_C_A(String portletId, String groupId,
		String companyId, boolean approved, int begin, int end)
		throws SystemException {
		return findByP_G_C_A(portletId, groupId, companyId, approved, begin,
			end, null);
	}

	public List findByP_G_C_A(String portletId, String groupId,
		String companyId, boolean approved, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, approved);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_A_First(
		String portletId, String groupId, String companyId, boolean approved,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		List list = findByP_G_C_A(portletId, groupId, companyId, approved, 0,
				1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_A_Last(
		String portletId, String groupId, String companyId, boolean approved,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		int count = countByP_G_C_A(portletId, groupId, companyId, approved);
		List list = findByP_G_C_A(portletId, groupId, companyId, approved,
				count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_A_PrevAndNext(
		JournalArticlePK journalArticlePK, String portletId, String groupId,
		String companyId, boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByP_G_C_A(portletId, groupId, companyId, approved);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, approved);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByP_G_C_T_A(String portletId, String groupId,
		String companyId, String type, boolean approved)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByP_G_C_T_A(String portletId, String groupId,
		String companyId, String type, boolean approved, int begin, int end)
		throws SystemException {
		return findByP_G_C_T_A(portletId, groupId, companyId, type, approved,
			begin, end, null);
	}

	public List findByP_G_C_T_A(String portletId, String groupId,
		String companyId, String type, boolean approved, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_A_First(
		String portletId, String groupId, String companyId, String type,
		boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByP_G_C_T_A(portletId, groupId, companyId, type,
				approved, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_C_T_A_Last(
		String portletId, String groupId, String companyId, String type,
		boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByP_G_C_T_A(portletId, groupId, companyId, type,
				approved);
		List list = findByP_G_C_T_A(portletId, groupId, companyId, type,
				approved, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByP_G_C_T_A_PrevAndNext(
		JournalArticlePK journalArticlePK, String portletId, String groupId,
		String companyId, String type, boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByP_G_C_T_A(portletId, groupId, companyId, type,
				approved);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByP_G_U_A(String portletId, String groupId, String userId,
		boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByP_G_U_A(String portletId, String groupId, String userId,
		boolean approved, int begin, int end) throws SystemException {
		return findByP_G_U_A(portletId, groupId, userId, approved, begin, end,
			null);
	}

	public List findByP_G_U_A(String portletId, String groupId, String userId,
		boolean approved, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, approved);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_U_A_First(
		String portletId, String groupId, String userId, boolean approved,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		List list = findByP_G_U_A(portletId, groupId, userId, approved, 0, 1,
				obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_U_A_Last(
		String portletId, String groupId, String userId, boolean approved,
		OrderByComparator obc) throws NoSuchArticleException, SystemException {
		int count = countByP_G_U_A(portletId, groupId, userId, approved);
		List list = findByP_G_U_A(portletId, groupId, userId, approved,
				count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByP_G_U_A_PrevAndNext(
		JournalArticlePK journalArticlePK, String portletId, String groupId,
		String userId, boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByP_G_U_A(portletId, groupId, userId, approved);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, approved);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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

	public List findByP_G_U_T_A(String portletId, String groupId,
		String userId, String type, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public List findByP_G_U_T_A(String portletId, String groupId,
		String userId, String type, boolean approved, int begin, int end)
		throws SystemException {
		return findByP_G_U_T_A(portletId, groupId, userId, type, approved,
			begin, end, null);
	}

	public List findByP_G_U_T_A(String portletId, String groupId,
		String userId, String type, boolean approved, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
					list.add(JournalArticleHBMUtil.model(journalArticleHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);
						list.add(JournalArticleHBMUtil.model(journalArticleHBM));

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

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_U_T_A_First(
		String portletId, String groupId, String userId, String type,
		boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		List list = findByP_G_U_T_A(portletId, groupId, userId, type, approved,
				0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle findByP_G_U_T_A_Last(
		String portletId, String groupId, String userId, String type,
		boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		int count = countByP_G_U_T_A(portletId, groupId, userId, type, approved);
		List list = findByP_G_U_T_A(portletId, groupId, userId, type, approved,
				count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchArticleException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalArticle)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalArticle[] findByP_G_U_T_A_PrevAndNext(
		JournalArticlePK journalArticlePK, String portletId, String groupId,
		String userId, String type, boolean approved, OrderByComparator obc)
		throws NoSuchArticleException, SystemException {
		com.liferay.portlet.journal.model.JournalArticle journalArticle = findByPrimaryKey(journalArticlePK);
		int count = countByP_G_U_T_A(portletId, groupId, userId, type, approved);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("articleId ASC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			com.liferay.portlet.journal.model.JournalArticle[] array = new com.liferay.portlet.journal.model.JournalArticle[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalArticleHBM journalArticleHBM = (JournalArticleHBM)sr.get(0);

					if (journalArticleHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalArticle curJournalArticle =
						JournalArticleHBMUtil.model(journalArticleHBM);
					int value = obc.compare(journalArticle, curJournalArticle);

					if (value == 0) {
						if (!journalArticle.equals(curJournalArticle)) {
							break;
						}

						array[1] = curJournalArticle;

						if (sr.previous()) {
							array[0] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalArticleHBMUtil.model((JournalArticleHBM)sr.get(
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
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				list.add(JournalArticleHBMUtil.model(journalArticleHBM));
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

	public void removeByArticleId(String articleId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByStructureId(String structureId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByTemplateId(String templateId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("templateId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, templateId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByA_A(String articleId, boolean approved)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByP_G_C(String portletId, String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByP_G_C_T(String portletId, String groupId,
		String companyId, String type) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByP_G_C_A(String portletId, String groupId,
		String companyId, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByP_G_C_T_A(String portletId, String groupId,
		String companyId, String type, boolean approved)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByP_G_U_A(String portletId, String groupId,
		String userId, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public void removeByP_G_U_T_A(String portletId, String groupId,
		String userId, String type, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("articleId ASC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalArticleHBM journalArticleHBM = (JournalArticleHBM)itr.next();
				JournalArticlePool.remove((JournalArticlePK)journalArticleHBM.getPrimaryKey());
				session.delete(journalArticleHBM);
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

	public int countByArticleId(String articleId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);

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

	public int countByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

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

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
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

	public int countByStructureId(String structureId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

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

	public int countByTemplateId(String templateId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("templateId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, templateId);

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

	public int countByA_A(String articleId, boolean approved)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("articleId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, articleId);
			q.setBoolean(queryPos++, approved);

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

	public int countByP_G_C(String portletId, String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
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

	public int countByP_G_C_T(String portletId, String groupId,
		String companyId, String type) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

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

	public int countByP_G_C_A(String portletId, String groupId,
		String companyId, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, approved);

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

	public int countByP_G_C_T_A(String portletId, String groupId,
		String companyId, String type, boolean approved)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

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

	public int countByP_G_U_A(String portletId, String groupId, String userId,
		boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, approved);

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

	public int countByP_G_U_T_A(String portletId, String groupId,
		String userId, String type, boolean approved) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalArticle IN CLASS com.liferay.portlet.journal.service.persistence.JournalArticleHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" AND ");
			query.append("approved = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);
			q.setBoolean(queryPos++, approved);

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

	private static final Log _log = LogFactory.getLog(JournalArticlePersistence.class);
}