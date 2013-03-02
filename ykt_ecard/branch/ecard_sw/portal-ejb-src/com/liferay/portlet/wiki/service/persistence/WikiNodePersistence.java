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

package com.liferay.portlet.wiki.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.wiki.NoSuchNodeException;

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
 * <a href="WikiNodePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiNodePersistence extends BasePersistence {
	public com.liferay.portlet.wiki.model.WikiNode create(String nodeId) {
		return new com.liferay.portlet.wiki.model.WikiNode(nodeId);
	}

	public com.liferay.portlet.wiki.model.WikiNode remove(String nodeId)
		throws NoSuchNodeException, SystemException {
		Session session = null;

		try {
			session = openSession();

			WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)session.get(WikiNodeHBM.class,
					nodeId);

			if (wikiNodeHBM == null) {
				_log.warn("No WikiNode exists with the primary key of " +
					nodeId.toString());
				throw new NoSuchNodeException(nodeId.toString());
			}

			com.liferay.portlet.wiki.model.WikiNode wikiNode = WikiNodeHBMUtil.model(wikiNodeHBM);
			session.delete(wikiNodeHBM);
			session.flush();
			WikiNodePool.remove(nodeId);

			return wikiNode;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode update(
		com.liferay.portlet.wiki.model.WikiNode wikiNode)
		throws SystemException {
		Session session = null;

		try {
			if (wikiNode.isNew() || wikiNode.isModified()) {
				session = openSession();

				if (wikiNode.isNew()) {
					WikiNodeHBM wikiNodeHBM = new WikiNodeHBM(wikiNode.getNodeId(),
							wikiNode.getCompanyId(), wikiNode.getUserId(),
							wikiNode.getUserName(), wikiNode.getCreateDate(),
							wikiNode.getModifiedDate(),
							wikiNode.getReadRoles(), wikiNode.getWriteRoles(),
							wikiNode.getName(), wikiNode.getDescription(),
							wikiNode.getSharing(), wikiNode.getLastPostDate());
					session.save(wikiNodeHBM);
					session.flush();
				}
				else {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)session.get(WikiNodeHBM.class,
							wikiNode.getPrimaryKey());

					if (wikiNodeHBM != null) {
						wikiNodeHBM.setCompanyId(wikiNode.getCompanyId());
						wikiNodeHBM.setUserId(wikiNode.getUserId());
						wikiNodeHBM.setUserName(wikiNode.getUserName());
						wikiNodeHBM.setCreateDate(wikiNode.getCreateDate());
						wikiNodeHBM.setModifiedDate(wikiNode.getModifiedDate());
						wikiNodeHBM.setReadRoles(wikiNode.getReadRoles());
						wikiNodeHBM.setWriteRoles(wikiNode.getWriteRoles());
						wikiNodeHBM.setName(wikiNode.getName());
						wikiNodeHBM.setDescription(wikiNode.getDescription());
						wikiNodeHBM.setSharing(wikiNode.getSharing());
						wikiNodeHBM.setLastPostDate(wikiNode.getLastPostDate());
						session.flush();
					}
					else {
						wikiNodeHBM = new WikiNodeHBM(wikiNode.getNodeId(),
								wikiNode.getCompanyId(), wikiNode.getUserId(),
								wikiNode.getUserName(),
								wikiNode.getCreateDate(),
								wikiNode.getModifiedDate(),
								wikiNode.getReadRoles(),
								wikiNode.getWriteRoles(), wikiNode.getName(),
								wikiNode.getDescription(),
								wikiNode.getSharing(),
								wikiNode.getLastPostDate());
						session.save(wikiNodeHBM);
						session.flush();
					}
				}

				wikiNode.setNew(false);
				wikiNode.setModified(false);
				wikiNode.protect();
				WikiNodePool.put(wikiNode.getPrimaryKey(), wikiNode);
			}

			return wikiNode;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode findByPrimaryKey(
		String nodeId) throws NoSuchNodeException, SystemException {
		com.liferay.portlet.wiki.model.WikiNode wikiNode = WikiNodePool.get(nodeId);
		Session session = null;

		try {
			if (wikiNode == null) {
				session = openSession();

				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)session.get(WikiNodeHBM.class,
						nodeId);

				if (wikiNodeHBM == null) {
					_log.warn("No WikiNode exists with the primary key of " +
						nodeId.toString());
					throw new NoSuchNodeException(nodeId.toString());
				}

				wikiNode = WikiNodeHBMUtil.model(wikiNodeHBM);
			}

			return wikiNode;
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
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
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
					list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);
						list.add(WikiNodeHBMUtil.model(wikiNodeHBM));

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

	public com.liferay.portlet.wiki.model.WikiNode findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode[] findByCompanyId_PrevAndNext(
		String nodeId, String companyId, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		com.liferay.portlet.wiki.model.WikiNode wikiNode = findByPrimaryKey(nodeId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.wiki.model.WikiNode[] array = new com.liferay.portlet.wiki.model.WikiNode[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);

					if (wikiNodeHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiNode curWikiNode = WikiNodeHBMUtil.model(wikiNodeHBM);
					int value = obc.compare(wikiNode, curWikiNode);

					if (value == 0) {
						if (!wikiNode.equals(curWikiNode)) {
							break;
						}

						array[1] = curWikiNode;

						if (sr.previous()) {
							array[0] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
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
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
					list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);
						list.add(WikiNodeHBMUtil.model(wikiNodeHBM));

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

	public com.liferay.portlet.wiki.model.WikiNode findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode[] findByUserId_PrevAndNext(
		String nodeId, String userId, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		com.liferay.portlet.wiki.model.WikiNode wikiNode = findByPrimaryKey(nodeId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.wiki.model.WikiNode[] array = new com.liferay.portlet.wiki.model.WikiNode[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);

					if (wikiNodeHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiNode curWikiNode = WikiNodeHBMUtil.model(wikiNodeHBM);
					int value = obc.compare(wikiNode, curWikiNode);

					if (value == 0) {
						if (!wikiNode.equals(curWikiNode)) {
							break;
						}

						array[1] = curWikiNode;

						if (sr.previous()) {
							array[0] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
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

	public List findByC_S(String companyId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
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

	public List findByC_S(String companyId, boolean sharing, int begin, int end)
		throws SystemException {
		return findByC_S(companyId, sharing, begin, end, null);
	}

	public List findByC_S(String companyId, boolean sharing, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, sharing);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
					list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);
						list.add(WikiNodeHBMUtil.model(wikiNodeHBM));

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

	public com.liferay.portlet.wiki.model.WikiNode findByC_S_First(
		String companyId, boolean sharing, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		List list = findByC_S(companyId, sharing, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode findByC_S_Last(
		String companyId, boolean sharing, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		int count = countByC_S(companyId, sharing);
		List list = findByC_S(companyId, sharing, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode[] findByC_S_PrevAndNext(
		String nodeId, String companyId, boolean sharing, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		com.liferay.portlet.wiki.model.WikiNode wikiNode = findByPrimaryKey(nodeId);
		int count = countByC_S(companyId, sharing);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, sharing);

			com.liferay.portlet.wiki.model.WikiNode[] array = new com.liferay.portlet.wiki.model.WikiNode[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);

					if (wikiNodeHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiNode curWikiNode = WikiNodeHBMUtil.model(wikiNodeHBM);
					int value = obc.compare(wikiNode, curWikiNode);

					if (value == 0) {
						if (!wikiNode.equals(curWikiNode)) {
							break;
						}

						array[1] = curWikiNode;

						if (sr.previous()) {
							array[0] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
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

	public List findByU_S(String userId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
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

	public List findByU_S(String userId, boolean sharing, int begin, int end)
		throws SystemException {
		return findByU_S(userId, sharing, begin, end, null);
	}

	public List findByU_S(String userId, boolean sharing, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
					list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);
						list.add(WikiNodeHBMUtil.model(wikiNodeHBM));

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

	public com.liferay.portlet.wiki.model.WikiNode findByU_S_First(
		String userId, boolean sharing, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		List list = findByU_S(userId, sharing, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode findByU_S_Last(
		String userId, boolean sharing, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		int count = countByU_S(userId, sharing);
		List list = findByU_S(userId, sharing, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNodeException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiNode)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiNode[] findByU_S_PrevAndNext(
		String nodeId, String userId, boolean sharing, OrderByComparator obc)
		throws NoSuchNodeException, SystemException {
		com.liferay.portlet.wiki.model.WikiNode wikiNode = findByPrimaryKey(nodeId);
		int count = countByU_S(userId, sharing);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			com.liferay.portlet.wiki.model.WikiNode[] array = new com.liferay.portlet.wiki.model.WikiNode[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)sr.get(0);

					if (wikiNodeHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiNode curWikiNode = WikiNodeHBMUtil.model(wikiNodeHBM);
					int value = obc.compare(wikiNode, curWikiNode);

					if (value == 0) {
						if (!wikiNode.equals(curWikiNode)) {
							break;
						}

						array[1] = curWikiNode;

						if (sr.previous()) {
							array[0] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiNodeHBMUtil.model((WikiNodeHBM)sr.get(
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				list.add(WikiNodeHBMUtil.model(wikiNodeHBM));
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				WikiNodePool.remove((String)wikiNodeHBM.getPrimaryKey());
				session.delete(wikiNodeHBM);
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				WikiNodePool.remove((String)wikiNodeHBM.getPrimaryKey());
				session.delete(wikiNodeHBM);
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

	public void removeByC_S(String companyId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				WikiNodePool.remove((String)wikiNodeHBM.getPrimaryKey());
				session.delete(wikiNodeHBM);
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

	public void removeByU_S(String userId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiNodeHBM wikiNodeHBM = (WikiNodeHBM)itr.next();
				WikiNodePool.remove((String)wikiNodeHBM.getPrimaryKey());
				session.delete(wikiNodeHBM);
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
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
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
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

	public int countByC_S(String companyId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, sharing);

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

	public int countByU_S(String userId, boolean sharing)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM WikiNode IN CLASS com.liferay.portlet.wiki.service.persistence.WikiNodeHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("sharing = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, sharing);

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

	private static final Log _log = LogFactory.getLog(WikiNodePersistence.class);
}