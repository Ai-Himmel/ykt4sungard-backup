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

import com.liferay.portlet.wiki.NoSuchPageException;

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
 * <a href="WikiPagePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class WikiPagePersistence extends BasePersistence {
	public com.liferay.portlet.wiki.model.WikiPage create(WikiPagePK wikiPagePK) {
		return new com.liferay.portlet.wiki.model.WikiPage(wikiPagePK);
	}

	public com.liferay.portlet.wiki.model.WikiPage remove(WikiPagePK wikiPagePK)
		throws NoSuchPageException, SystemException {
		Session session = null;

		try {
			session = openSession();

			WikiPageHBM wikiPageHBM = (WikiPageHBM)session.get(WikiPageHBM.class,
					wikiPagePK);

			if (wikiPageHBM == null) {
				_log.warn("No WikiPage exists with the primary key of " +
					wikiPagePK.toString());
				throw new NoSuchPageException(wikiPagePK.toString());
			}

			com.liferay.portlet.wiki.model.WikiPage wikiPage = WikiPageHBMUtil.model(wikiPageHBM);
			session.delete(wikiPageHBM);
			session.flush();
			WikiPagePool.remove(wikiPagePK);

			return wikiPage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage update(
		com.liferay.portlet.wiki.model.WikiPage wikiPage)
		throws SystemException {
		Session session = null;

		try {
			if (wikiPage.isNew() || wikiPage.isModified()) {
				session = openSession();

				if (wikiPage.isNew()) {
					WikiPageHBM wikiPageHBM = new WikiPageHBM(wikiPage.getNodeId(),
							wikiPage.getTitle(), wikiPage.getVersion(),
							wikiPage.getCompanyId(), wikiPage.getUserId(),
							wikiPage.getUserName(), wikiPage.getCreateDate(),
							wikiPage.getContent(), wikiPage.getFormat(),
							wikiPage.getHead());
					session.save(wikiPageHBM);
					session.flush();
				}
				else {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)session.get(WikiPageHBM.class,
							wikiPage.getPrimaryKey());

					if (wikiPageHBM != null) {
						wikiPageHBM.setCompanyId(wikiPage.getCompanyId());
						wikiPageHBM.setUserId(wikiPage.getUserId());
						wikiPageHBM.setUserName(wikiPage.getUserName());
						wikiPageHBM.setCreateDate(wikiPage.getCreateDate());
						wikiPageHBM.setContent(wikiPage.getContent());
						wikiPageHBM.setFormat(wikiPage.getFormat());
						wikiPageHBM.setHead(wikiPage.getHead());
						session.flush();
					}
					else {
						wikiPageHBM = new WikiPageHBM(wikiPage.getNodeId(),
								wikiPage.getTitle(), wikiPage.getVersion(),
								wikiPage.getCompanyId(), wikiPage.getUserId(),
								wikiPage.getUserName(),
								wikiPage.getCreateDate(),
								wikiPage.getContent(), wikiPage.getFormat(),
								wikiPage.getHead());
						session.save(wikiPageHBM);
						session.flush();
					}
				}

				wikiPage.setNew(false);
				wikiPage.setModified(false);
				wikiPage.protect();
				WikiPagePool.put(wikiPage.getPrimaryKey(), wikiPage);
			}

			return wikiPage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByPrimaryKey(
		WikiPagePK wikiPagePK) throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = WikiPagePool.get(wikiPagePK);
		Session session = null;

		try {
			if (wikiPage == null) {
				session = openSession();

				WikiPageHBM wikiPageHBM = (WikiPageHBM)session.get(WikiPageHBM.class,
						wikiPagePK);

				if (wikiPageHBM == null) {
					_log.warn("No WikiPage exists with the primary key of " +
						wikiPagePK.toString());
					throw new NoSuchPageException(wikiPagePK.toString());
				}

				wikiPage = WikiPageHBMUtil.model(wikiPageHBM);
			}

			return wikiPage;
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
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
					WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
					list.add(WikiPageHBMUtil.model(wikiPageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);
						list.add(WikiPageHBMUtil.model(wikiPageHBM));

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

	public com.liferay.portlet.wiki.model.WikiPage findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage[] findByCompanyId_PrevAndNext(
		WikiPagePK wikiPagePK, String companyId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = findByPrimaryKey(wikiPagePK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.wiki.model.WikiPage[] array = new com.liferay.portlet.wiki.model.WikiPage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);

					if (wikiPageHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiPage curWikiPage = WikiPageHBMUtil.model(wikiPageHBM);
					int value = obc.compare(wikiPage, curWikiPage);

					if (value == 0) {
						if (!wikiPage.equals(curWikiPage)) {
							break;
						}

						array[1] = curWikiPage;

						if (sr.previous()) {
							array[0] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
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
					WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
					list.add(WikiPageHBMUtil.model(wikiPageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);
						list.add(WikiPageHBMUtil.model(wikiPageHBM));

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

	public com.liferay.portlet.wiki.model.WikiPage findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage[] findByUserId_PrevAndNext(
		WikiPagePK wikiPagePK, String userId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = findByPrimaryKey(wikiPagePK);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.wiki.model.WikiPage[] array = new com.liferay.portlet.wiki.model.WikiPage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);

					if (wikiPageHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiPage curWikiPage = WikiPageHBMUtil.model(wikiPageHBM);
					int value = obc.compare(wikiPage, curWikiPage);

					if (value == 0) {
						if (!wikiPage.equals(curWikiPage)) {
							break;
						}

						array[1] = curWikiPage;

						if (sr.previous()) {
							array[0] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
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

	public List findByNodeId(String nodeId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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

	public List findByNodeId(String nodeId, int begin, int end)
		throws SystemException {
		return findByNodeId(nodeId, begin, end, null);
	}

	public List findByNodeId(String nodeId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
					list.add(WikiPageHBMUtil.model(wikiPageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);
						list.add(WikiPageHBMUtil.model(wikiPageHBM));

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

	public com.liferay.portlet.wiki.model.WikiPage findByNodeId_First(
		String nodeId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		List list = findByNodeId(nodeId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByNodeId_Last(
		String nodeId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		int count = countByNodeId(nodeId);
		List list = findByNodeId(nodeId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage[] findByNodeId_PrevAndNext(
		WikiPagePK wikiPagePK, String nodeId, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = findByPrimaryKey(wikiPagePK);
		int count = countByNodeId(nodeId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);

			com.liferay.portlet.wiki.model.WikiPage[] array = new com.liferay.portlet.wiki.model.WikiPage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);

					if (wikiPageHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiPage curWikiPage = WikiPageHBMUtil.model(wikiPageHBM);
					int value = obc.compare(wikiPage, curWikiPage);

					if (value == 0) {
						if (!wikiPage.equals(curWikiPage)) {
							break;
						}

						array[1] = curWikiPage;

						if (sr.previous()) {
							array[0] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
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

	public List findByN_T(String nodeId, String title)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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

	public List findByN_T(String nodeId, String title, int begin, int end)
		throws SystemException {
		return findByN_T(nodeId, title, begin, end, null);
	}

	public List findByN_T(String nodeId, String title, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
					list.add(WikiPageHBMUtil.model(wikiPageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);
						list.add(WikiPageHBMUtil.model(wikiPageHBM));

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

	public com.liferay.portlet.wiki.model.WikiPage findByN_T_First(
		String nodeId, String title, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		List list = findByN_T(nodeId, title, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByN_T_Last(
		String nodeId, String title, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		int count = countByN_T(nodeId, title);
		List list = findByN_T(nodeId, title, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage[] findByN_T_PrevAndNext(
		WikiPagePK wikiPagePK, String nodeId, String title,
		OrderByComparator obc) throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = findByPrimaryKey(wikiPagePK);
		int count = countByN_T(nodeId, title);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);

			com.liferay.portlet.wiki.model.WikiPage[] array = new com.liferay.portlet.wiki.model.WikiPage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);

					if (wikiPageHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiPage curWikiPage = WikiPageHBMUtil.model(wikiPageHBM);
					int value = obc.compare(wikiPage, curWikiPage);

					if (value == 0) {
						if (!wikiPage.equals(curWikiPage)) {
							break;
						}

						array[1] = curWikiPage;

						if (sr.previous()) {
							array[0] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
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

	public List findByN_T_H(String nodeId, String title, boolean head)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);
			q.setBoolean(queryPos++, head);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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

	public List findByN_T_H(String nodeId, String title, boolean head,
		int begin, int end) throws SystemException {
		return findByN_T_H(nodeId, title, head, begin, end, null);
	}

	public List findByN_T_H(String nodeId, String title, boolean head,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);
			q.setBoolean(queryPos++, head);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
					list.add(WikiPageHBMUtil.model(wikiPageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);
						list.add(WikiPageHBMUtil.model(wikiPageHBM));

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

	public com.liferay.portlet.wiki.model.WikiPage findByN_T_H_First(
		String nodeId, String title, boolean head, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		List list = findByN_T_H(nodeId, title, head, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByN_T_H_Last(
		String nodeId, String title, boolean head, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		int count = countByN_T_H(nodeId, title, head);
		List list = findByN_T_H(nodeId, title, head, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage[] findByN_T_H_PrevAndNext(
		WikiPagePK wikiPagePK, String nodeId, String title, boolean head,
		OrderByComparator obc) throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = findByPrimaryKey(wikiPagePK);
		int count = countByN_T_H(nodeId, title, head);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);
			q.setBoolean(queryPos++, head);

			com.liferay.portlet.wiki.model.WikiPage[] array = new com.liferay.portlet.wiki.model.WikiPage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);

					if (wikiPageHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiPage curWikiPage = WikiPageHBMUtil.model(wikiPageHBM);
					int value = obc.compare(wikiPage, curWikiPage);

					if (value == 0) {
						if (!wikiPage.equals(curWikiPage)) {
							break;
						}

						array[1] = curWikiPage;

						if (sr.previous()) {
							array[0] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
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

	public List findByN_H(String nodeId, boolean head)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setBoolean(queryPos++, head);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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

	public List findByN_H(String nodeId, boolean head, int begin, int end)
		throws SystemException {
		return findByN_H(nodeId, head, begin, end, null);
	}

	public List findByN_H(String nodeId, boolean head, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setBoolean(queryPos++, head);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
					list.add(WikiPageHBMUtil.model(wikiPageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);
						list.add(WikiPageHBMUtil.model(wikiPageHBM));

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

	public com.liferay.portlet.wiki.model.WikiPage findByN_H_First(
		String nodeId, boolean head, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		List list = findByN_H(nodeId, head, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage findByN_H_Last(
		String nodeId, boolean head, OrderByComparator obc)
		throws NoSuchPageException, SystemException {
		int count = countByN_H(nodeId, head);
		List list = findByN_H(nodeId, head, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchPageException();
		}
		else {
			return (com.liferay.portlet.wiki.model.WikiPage)list.get(0);
		}
	}

	public com.liferay.portlet.wiki.model.WikiPage[] findByN_H_PrevAndNext(
		WikiPagePK wikiPagePK, String nodeId, boolean head,
		OrderByComparator obc) throws NoSuchPageException, SystemException {
		com.liferay.portlet.wiki.model.WikiPage wikiPage = findByPrimaryKey(wikiPagePK);
		int count = countByN_H(nodeId, head);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("nodeId ASC").append(", ");
				query.append("title ASC").append(", ");
				query.append("version ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setBoolean(queryPos++, head);

			com.liferay.portlet.wiki.model.WikiPage[] array = new com.liferay.portlet.wiki.model.WikiPage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					WikiPageHBM wikiPageHBM = (WikiPageHBM)sr.get(0);

					if (wikiPageHBM == null) {
						break;
					}

					com.liferay.portlet.wiki.model.WikiPage curWikiPage = WikiPageHBMUtil.model(wikiPageHBM);
					int value = obc.compare(wikiPage, curWikiPage);

					if (value == 0) {
						if (!wikiPage.equals(curWikiPage)) {
							break;
						}

						array[1] = curWikiPage;

						if (sr.previous()) {
							array[0] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = WikiPageHBMUtil.model((WikiPageHBM)sr.get(
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				list.add(WikiPageHBMUtil.model(wikiPageHBM));
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				WikiPagePool.remove((WikiPagePK)wikiPageHBM.getPrimaryKey());
				session.delete(wikiPageHBM);
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				WikiPagePool.remove((WikiPagePK)wikiPageHBM.getPrimaryKey());
				session.delete(wikiPageHBM);
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

	public void removeByNodeId(String nodeId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				WikiPagePool.remove((WikiPagePK)wikiPageHBM.getPrimaryKey());
				session.delete(wikiPageHBM);
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

	public void removeByN_T(String nodeId, String title)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				WikiPagePool.remove((WikiPagePK)wikiPageHBM.getPrimaryKey());
				session.delete(wikiPageHBM);
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

	public void removeByN_T_H(String nodeId, String title, boolean head)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);
			q.setBoolean(queryPos++, head);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				WikiPagePool.remove((WikiPagePK)wikiPageHBM.getPrimaryKey());
				session.delete(wikiPageHBM);
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

	public void removeByN_H(String nodeId, boolean head)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("nodeId ASC").append(", ");
			query.append("title ASC").append(", ");
			query.append("version ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setBoolean(queryPos++, head);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				WikiPageHBM wikiPageHBM = (WikiPageHBM)itr.next();
				WikiPagePool.remove((WikiPagePK)wikiPageHBM.getPrimaryKey());
				session.delete(wikiPageHBM);
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
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
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
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

	public int countByNodeId(String nodeId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);

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

	public int countByN_T(String nodeId, String title)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);

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

	public int countByN_T_H(String nodeId, String title, boolean head)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("title = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setString(queryPos++, title);
			q.setBoolean(queryPos++, head);

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

	public int countByN_H(String nodeId, boolean head)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM WikiPage IN CLASS com.liferay.portlet.wiki.service.persistence.WikiPageHBM WHERE ");
			query.append("nodeId = ?");
			query.append(" AND ");
			query.append("head = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, nodeId);
			q.setBoolean(queryPos++, head);

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

	private static final Log _log = LogFactory.getLog(WikiPagePersistence.class);
}