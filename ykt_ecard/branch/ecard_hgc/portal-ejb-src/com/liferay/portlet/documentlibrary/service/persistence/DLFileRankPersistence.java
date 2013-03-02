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

package com.liferay.portlet.documentlibrary.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.documentlibrary.NoSuchFileRankException;

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
 * <a href="DLFileRankPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileRankPersistence extends BasePersistence {
	public com.liferay.portlet.documentlibrary.model.DLFileRank create(
		DLFileRankPK dlFileRankPK) {
		return new com.liferay.portlet.documentlibrary.model.DLFileRank(dlFileRankPK);
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank remove(
		DLFileRankPK dlFileRankPK)
		throws NoSuchFileRankException, SystemException {
		Session session = null;

		try {
			session = openSession();

			DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)session.get(DLFileRankHBM.class,
					dlFileRankPK);

			if (dlFileRankHBM == null) {
				_log.warn("No DLFileRank exists with the primary key of " +
					dlFileRankPK.toString());
				throw new NoSuchFileRankException(dlFileRankPK.toString());
			}

			com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank = DLFileRankHBMUtil.model(dlFileRankHBM);
			session.delete(dlFileRankHBM);
			session.flush();
			DLFileRankPool.remove(dlFileRankPK);

			return dlFileRank;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank update(
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank)
		throws SystemException {
		Session session = null;

		try {
			if (dlFileRank.isNew() || dlFileRank.isModified()) {
				session = openSession();

				if (dlFileRank.isNew()) {
					DLFileRankHBM dlFileRankHBM = new DLFileRankHBM(dlFileRank.getCompanyId(),
							dlFileRank.getUserId(),
							dlFileRank.getRepositoryId(),
							dlFileRank.getFileName(), dlFileRank.getCreateDate());
					session.save(dlFileRankHBM);
					session.flush();
				}
				else {
					DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)session.get(DLFileRankHBM.class,
							dlFileRank.getPrimaryKey());

					if (dlFileRankHBM != null) {
						dlFileRankHBM.setCreateDate(dlFileRank.getCreateDate());
						session.flush();
					}
					else {
						dlFileRankHBM = new DLFileRankHBM(dlFileRank.getCompanyId(),
								dlFileRank.getUserId(),
								dlFileRank.getRepositoryId(),
								dlFileRank.getFileName(),
								dlFileRank.getCreateDate());
						session.save(dlFileRankHBM);
						session.flush();
					}
				}

				dlFileRank.setNew(false);
				dlFileRank.setModified(false);
				dlFileRank.protect();
				DLFileRankPool.put(dlFileRank.getPrimaryKey(), dlFileRank);
			}

			return dlFileRank;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByPrimaryKey(
		DLFileRankPK dlFileRankPK)
		throws NoSuchFileRankException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank = DLFileRankPool.get(dlFileRankPK);
		Session session = null;

		try {
			if (dlFileRank == null) {
				session = openSession();

				DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)session.get(DLFileRankHBM.class,
						dlFileRankPK);

				if (dlFileRankHBM == null) {
					_log.warn("No DLFileRank exists with the primary key of " +
						dlFileRankPK.toString());
					throw new NoSuchFileRankException(dlFileRankPK.toString());
				}

				dlFileRank = DLFileRankHBMUtil.model(dlFileRankHBM);
			}

			return dlFileRank;
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
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
				list.add(DLFileRankHBMUtil.model(dlFileRankHBM));
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
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
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
					DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
					list.add(DLFileRankHBMUtil.model(dlFileRankHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)sr.get(0);
						list.add(DLFileRankHBMUtil.model(dlFileRankHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchFileRankException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileRankException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileRank)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchFileRankException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileRankException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileRank)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank[] findByUserId_PrevAndNext(
		DLFileRankPK dlFileRankPK, String userId, OrderByComparator obc)
		throws NoSuchFileRankException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank = findByPrimaryKey(dlFileRankPK);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.documentlibrary.model.DLFileRank[] array = new com.liferay.portlet.documentlibrary.model.DLFileRank[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)sr.get(0);

					if (dlFileRankHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileRank curDLFileRank =
						DLFileRankHBMUtil.model(dlFileRankHBM);
					int value = obc.compare(dlFileRank, curDLFileRank);

					if (value == 0) {
						if (!dlFileRank.equals(curDLFileRank)) {
							break;
						}

						array[1] = curDLFileRank;

						if (sr.previous()) {
							array[0] = DLFileRankHBMUtil.model((DLFileRankHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileRankHBMUtil.model((DLFileRankHBM)sr.get(
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

	public List findByC_R_FN(String companyId, String repositoryId,
		String fileName) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
				list.add(DLFileRankHBMUtil.model(dlFileRankHBM));
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

	public List findByC_R_FN(String companyId, String repositoryId,
		String fileName, int begin, int end) throws SystemException {
		return findByC_R_FN(companyId, repositoryId, fileName, begin, end, null);
	}

	public List findByC_R_FN(String companyId, String repositoryId,
		String fileName, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
					list.add(DLFileRankHBMUtil.model(dlFileRankHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)sr.get(0);
						list.add(DLFileRankHBMUtil.model(dlFileRankHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByC_R_FN_First(
		String companyId, String repositoryId, String fileName,
		OrderByComparator obc) throws NoSuchFileRankException, SystemException {
		List list = findByC_R_FN(companyId, repositoryId, fileName, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileRankException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileRank)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank findByC_R_FN_Last(
		String companyId, String repositoryId, String fileName,
		OrderByComparator obc) throws NoSuchFileRankException, SystemException {
		int count = countByC_R_FN(companyId, repositoryId, fileName);
		List list = findByC_R_FN(companyId, repositoryId, fileName, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileRankException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileRank)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileRank[] findByC_R_FN_PrevAndNext(
		DLFileRankPK dlFileRankPK, String companyId, String repositoryId,
		String fileName, OrderByComparator obc)
		throws NoSuchFileRankException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileRank dlFileRank = findByPrimaryKey(dlFileRankPK);
		int count = countByC_R_FN(companyId, repositoryId, fileName);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			com.liferay.portlet.documentlibrary.model.DLFileRank[] array = new com.liferay.portlet.documentlibrary.model.DLFileRank[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)sr.get(0);

					if (dlFileRankHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileRank curDLFileRank =
						DLFileRankHBMUtil.model(dlFileRankHBM);
					int value = obc.compare(dlFileRank, curDLFileRank);

					if (value == 0) {
						if (!dlFileRank.equals(curDLFileRank)) {
							break;
						}

						array[1] = curDLFileRank;

						if (sr.previous()) {
							array[0] = DLFileRankHBMUtil.model((DLFileRankHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileRankHBMUtil.model((DLFileRankHBM)sr.get(
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
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
				list.add(DLFileRankHBMUtil.model(dlFileRankHBM));
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

	public void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
				DLFileRankPool.remove((DLFileRankPK)dlFileRankHBM.getPrimaryKey());
				session.delete(dlFileRankHBM);
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

	public void removeByC_R_FN(String companyId, String repositoryId,
		String fileName) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileRankHBM dlFileRankHBM = (DLFileRankHBM)itr.next();
				DLFileRankPool.remove((DLFileRankPK)dlFileRankHBM.getPrimaryKey());
				session.delete(dlFileRankHBM);
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

	public int countByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
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

	public int countByC_R_FN(String companyId, String repositoryId,
		String fileName) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLFileRank IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileRankHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

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

	private static final Log _log = LogFactory.getLog(DLFileRankPersistence.class);
}