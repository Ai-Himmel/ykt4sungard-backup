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

import com.liferay.portlet.documentlibrary.NoSuchRepositoryException;

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
 * <a href="DLRepositoryPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLRepositoryPersistence extends BasePersistence {
	public com.liferay.portlet.documentlibrary.model.DLRepository create(
		String repositoryId) {
		return new com.liferay.portlet.documentlibrary.model.DLRepository(repositoryId);
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository remove(
		String repositoryId) throws NoSuchRepositoryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)session.get(DLRepositoryHBM.class,
					repositoryId);

			if (dlRepositoryHBM == null) {
				_log.warn("No DLRepository exists with the primary key of " +
					repositoryId.toString());
				throw new NoSuchRepositoryException(repositoryId.toString());
			}

			com.liferay.portlet.documentlibrary.model.DLRepository dlRepository = DLRepositoryHBMUtil.model(dlRepositoryHBM);
			session.delete(dlRepositoryHBM);
			session.flush();
			DLRepositoryPool.remove(repositoryId);

			return dlRepository;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository update(
		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository)
		throws SystemException {
		Session session = null;

		try {
			if (dlRepository.isNew() || dlRepository.isModified()) {
				session = openSession();

				if (dlRepository.isNew()) {
					DLRepositoryHBM dlRepositoryHBM = new DLRepositoryHBM(dlRepository.getRepositoryId(),
							dlRepository.getGroupId(),
							dlRepository.getCompanyId(),
							dlRepository.getUserId(),
							dlRepository.getUserName(),
							dlRepository.getCreateDate(),
							dlRepository.getModifiedDate(),
							dlRepository.getReadRoles(),
							dlRepository.getWriteRoles(),
							dlRepository.getName(),
							dlRepository.getDescription(),
							dlRepository.getLastPostDate());
					session.save(dlRepositoryHBM);
					session.flush();
				}
				else {
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)session.get(DLRepositoryHBM.class,
							dlRepository.getPrimaryKey());

					if (dlRepositoryHBM != null) {
						dlRepositoryHBM.setGroupId(dlRepository.getGroupId());
						dlRepositoryHBM.setCompanyId(dlRepository.getCompanyId());
						dlRepositoryHBM.setUserId(dlRepository.getUserId());
						dlRepositoryHBM.setUserName(dlRepository.getUserName());
						dlRepositoryHBM.setCreateDate(dlRepository.getCreateDate());
						dlRepositoryHBM.setModifiedDate(dlRepository.getModifiedDate());
						dlRepositoryHBM.setReadRoles(dlRepository.getReadRoles());
						dlRepositoryHBM.setWriteRoles(dlRepository.getWriteRoles());
						dlRepositoryHBM.setName(dlRepository.getName());
						dlRepositoryHBM.setDescription(dlRepository.getDescription());
						dlRepositoryHBM.setLastPostDate(dlRepository.getLastPostDate());
						session.flush();
					}
					else {
						dlRepositoryHBM = new DLRepositoryHBM(dlRepository.getRepositoryId(),
								dlRepository.getGroupId(),
								dlRepository.getCompanyId(),
								dlRepository.getUserId(),
								dlRepository.getUserName(),
								dlRepository.getCreateDate(),
								dlRepository.getModifiedDate(),
								dlRepository.getReadRoles(),
								dlRepository.getWriteRoles(),
								dlRepository.getName(),
								dlRepository.getDescription(),
								dlRepository.getLastPostDate());
						session.save(dlRepositoryHBM);
						session.flush();
					}
				}

				dlRepository.setNew(false);
				dlRepository.setModified(false);
				dlRepository.protect();
				DLRepositoryPool.put(dlRepository.getPrimaryKey(), dlRepository);
			}

			return dlRepository;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository findByPrimaryKey(
		String repositoryId) throws NoSuchRepositoryException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository = DLRepositoryPool.get(repositoryId);
		Session session = null;

		try {
			if (dlRepository == null) {
				session = openSession();

				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)session.get(DLRepositoryHBM.class,
						repositoryId);

				if (dlRepositoryHBM == null) {
					_log.warn("No DLRepository exists with the primary key of " +
						repositoryId.toString());
					throw new NoSuchRepositoryException(repositoryId.toString());
				}

				dlRepository = DLRepositoryHBMUtil.model(dlRepositoryHBM);
			}

			return dlRepository;
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
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
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
					list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)sr.get(0);
						list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLRepository findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchRepositoryException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLRepository)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchRepositoryException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLRepository)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository[] findByGroupId_PrevAndNext(
		String repositoryId, String groupId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository = findByPrimaryKey(repositoryId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.documentlibrary.model.DLRepository[] array = new com.liferay.portlet.documentlibrary.model.DLRepository[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)sr.get(0);

					if (dlRepositoryHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLRepository curDLRepository =
						DLRepositoryHBMUtil.model(dlRepositoryHBM);
					int value = obc.compare(dlRepository, curDLRepository);

					if (value == 0) {
						if (!dlRepository.equals(curDLRepository)) {
							break;
						}

						array[1] = curDLRepository;

						if (sr.previous()) {
							array[0] = DLRepositoryHBMUtil.model((DLRepositoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLRepositoryHBMUtil.model((DLRepositoryHBM)sr.get(
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
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
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
					list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)sr.get(0);
						list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLRepository findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchRepositoryException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLRepository)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchRepositoryException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLRepository)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository[] findByCompanyId_PrevAndNext(
		String repositoryId, String companyId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository = findByPrimaryKey(repositoryId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.documentlibrary.model.DLRepository[] array = new com.liferay.portlet.documentlibrary.model.DLRepository[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)sr.get(0);

					if (dlRepositoryHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLRepository curDLRepository =
						DLRepositoryHBMUtil.model(dlRepositoryHBM);
					int value = obc.compare(dlRepository, curDLRepository);

					if (value == 0) {
						if (!dlRepository.equals(curDLRepository)) {
							break;
						}

						array[1] = curDLRepository;

						if (sr.previous()) {
							array[0] = DLRepositoryHBMUtil.model((DLRepositoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLRepositoryHBMUtil.model((DLRepositoryHBM)sr.get(
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

	public List findByG_C(String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
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

	public List findByG_C(String groupId, String companyId, int begin, int end)
		throws SystemException {
		return findByG_C(groupId, companyId, begin, end, null);
	}

	public List findByG_C(String groupId, String companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
					list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)sr.get(0);
						list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLRepository findByG_C_First(
		String groupId, String companyId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		List list = findByG_C(groupId, companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchRepositoryException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLRepository)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository findByG_C_Last(
		String groupId, String companyId, OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		int count = countByG_C(groupId, companyId);
		List list = findByG_C(groupId, companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchRepositoryException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLRepository)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLRepository[] findByG_C_PrevAndNext(
		String repositoryId, String groupId, String companyId,
		OrderByComparator obc)
		throws NoSuchRepositoryException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLRepository dlRepository = findByPrimaryKey(repositoryId);
		int count = countByG_C(groupId, companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			com.liferay.portlet.documentlibrary.model.DLRepository[] array = new com.liferay.portlet.documentlibrary.model.DLRepository[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)sr.get(0);

					if (dlRepositoryHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLRepository curDLRepository =
						DLRepositoryHBMUtil.model(dlRepositoryHBM);
					int value = obc.compare(dlRepository, curDLRepository);

					if (value == 0) {
						if (!dlRepository.equals(curDLRepository)) {
							break;
						}

						array[1] = curDLRepository;

						if (sr.previous()) {
							array[0] = DLRepositoryHBMUtil.model((DLRepositoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLRepositoryHBMUtil.model((DLRepositoryHBM)sr.get(
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				list.add(DLRepositoryHBMUtil.model(dlRepositoryHBM));
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

	public void removeByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				DLRepositoryPool.remove((String)dlRepositoryHBM.getPrimaryKey());
				session.delete(dlRepositoryHBM);
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				DLRepositoryPool.remove((String)dlRepositoryHBM.getPrimaryKey());
				session.delete(dlRepositoryHBM);
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

	public void removeByG_C(String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLRepositoryHBM dlRepositoryHBM = (DLRepositoryHBM)itr.next();
				DLRepositoryPool.remove((String)dlRepositoryHBM.getPrimaryKey());
				session.delete(dlRepositoryHBM);
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

	public int countByGroupId(String groupId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
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
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
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

	public int countByG_C(String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLRepository IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLRepositoryHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
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

	private static final Log _log = LogFactory.getLog(DLRepositoryPersistence.class);
}