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

import com.liferay.portlet.documentlibrary.NoSuchFileProfileException;

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
 * <a href="DLFileProfilePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileProfilePersistence extends BasePersistence {
	public com.liferay.portlet.documentlibrary.model.DLFileProfile create(
		DLFileProfilePK dlFileProfilePK) {
		return new com.liferay.portlet.documentlibrary.model.DLFileProfile(dlFileProfilePK);
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile remove(
		DLFileProfilePK dlFileProfilePK)
		throws NoSuchFileProfileException, SystemException {
		Session session = null;

		try {
			session = openSession();

			DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)session.get(DLFileProfileHBM.class,
					dlFileProfilePK);

			if (dlFileProfileHBM == null) {
				_log.warn("No DLFileProfile exists with the primary key of " +
					dlFileProfilePK.toString());
				throw new NoSuchFileProfileException(dlFileProfilePK.toString());
			}

			com.liferay.portlet.documentlibrary.model.DLFileProfile dlFileProfile =
				DLFileProfileHBMUtil.model(dlFileProfileHBM);
			session.delete(dlFileProfileHBM);
			session.flush();
			DLFileProfilePool.remove(dlFileProfilePK);

			return dlFileProfile;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile update(
		com.liferay.portlet.documentlibrary.model.DLFileProfile dlFileProfile)
		throws SystemException {
		Session session = null;

		try {
			if (dlFileProfile.isNew() || dlFileProfile.isModified()) {
				session = openSession();

				if (dlFileProfile.isNew()) {
					DLFileProfileHBM dlFileProfileHBM = new DLFileProfileHBM(dlFileProfile.getCompanyId(),
							dlFileProfile.getRepositoryId(),
							dlFileProfile.getFileName(),
							dlFileProfile.getUserId(),
							dlFileProfile.getUserName(),
							dlFileProfile.getVersionUserId(),
							dlFileProfile.getVersionUserName(),
							dlFileProfile.getCreateDate(),
							dlFileProfile.getModifiedDate(),
							dlFileProfile.getReadRoles(),
							dlFileProfile.getWriteRoles(),
							dlFileProfile.getDescription(),
							dlFileProfile.getVersion(), dlFileProfile.getSize());
					session.save(dlFileProfileHBM);
					session.flush();
				}
				else {
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)session.get(DLFileProfileHBM.class,
							dlFileProfile.getPrimaryKey());

					if (dlFileProfileHBM != null) {
						dlFileProfileHBM.setUserId(dlFileProfile.getUserId());
						dlFileProfileHBM.setUserName(dlFileProfile.getUserName());
						dlFileProfileHBM.setVersionUserId(dlFileProfile.getVersionUserId());
						dlFileProfileHBM.setVersionUserName(dlFileProfile.getVersionUserName());
						dlFileProfileHBM.setCreateDate(dlFileProfile.getCreateDate());
						dlFileProfileHBM.setModifiedDate(dlFileProfile.getModifiedDate());
						dlFileProfileHBM.setReadRoles(dlFileProfile.getReadRoles());
						dlFileProfileHBM.setWriteRoles(dlFileProfile.getWriteRoles());
						dlFileProfileHBM.setDescription(dlFileProfile.getDescription());
						dlFileProfileHBM.setVersion(dlFileProfile.getVersion());
						dlFileProfileHBM.setSize(dlFileProfile.getSize());
						session.flush();
					}
					else {
						dlFileProfileHBM = new DLFileProfileHBM(dlFileProfile.getCompanyId(),
								dlFileProfile.getRepositoryId(),
								dlFileProfile.getFileName(),
								dlFileProfile.getUserId(),
								dlFileProfile.getUserName(),
								dlFileProfile.getVersionUserId(),
								dlFileProfile.getVersionUserName(),
								dlFileProfile.getCreateDate(),
								dlFileProfile.getModifiedDate(),
								dlFileProfile.getReadRoles(),
								dlFileProfile.getWriteRoles(),
								dlFileProfile.getDescription(),
								dlFileProfile.getVersion(),
								dlFileProfile.getSize());
						session.save(dlFileProfileHBM);
						session.flush();
					}
				}

				dlFileProfile.setNew(false);
				dlFileProfile.setModified(false);
				dlFileProfile.protect();
				DLFileProfilePool.put(dlFileProfile.getPrimaryKey(),
					dlFileProfile);
			}

			return dlFileProfile;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByPrimaryKey(
		DLFileProfilePK dlFileProfilePK)
		throws NoSuchFileProfileException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileProfile dlFileProfile = DLFileProfilePool.get(dlFileProfilePK);
		Session session = null;

		try {
			if (dlFileProfile == null) {
				session = openSession();

				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)session.get(DLFileProfileHBM.class,
						dlFileProfilePK);

				if (dlFileProfileHBM == null) {
					_log.warn(
						"No DLFileProfile exists with the primary key of " +
						dlFileProfilePK.toString());
					throw new NoSuchFileProfileException(dlFileProfilePK.toString());
				}

				dlFileProfile = DLFileProfileHBMUtil.model(dlFileProfileHBM);
			}

			return dlFileProfile;
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
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
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
					list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)sr.get(0);
						list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileProfileException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileProfile)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileProfileException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileProfile)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile[] findByCompanyId_PrevAndNext(
		DLFileProfilePK dlFileProfilePK, String companyId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileProfile dlFileProfile = findByPrimaryKey(dlFileProfilePK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.documentlibrary.model.DLFileProfile[] array = new com.liferay.portlet.documentlibrary.model.DLFileProfile[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)sr.get(0);

					if (dlFileProfileHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileProfile curDLFileProfile =
						DLFileProfileHBMUtil.model(dlFileProfileHBM);
					int value = obc.compare(dlFileProfile, curDLFileProfile);

					if (value == 0) {
						if (!dlFileProfile.equals(curDLFileProfile)) {
							break;
						}

						array[1] = curDLFileProfile;

						if (sr.previous()) {
							array[0] = DLFileProfileHBMUtil.model((DLFileProfileHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileProfileHBMUtil.model((DLFileProfileHBM)sr.get(
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
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
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
					list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)sr.get(0);
						list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileProfileException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileProfile)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileProfileException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileProfile)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile[] findByUserId_PrevAndNext(
		DLFileProfilePK dlFileProfilePK, String userId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileProfile dlFileProfile = findByPrimaryKey(dlFileProfilePK);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.documentlibrary.model.DLFileProfile[] array = new com.liferay.portlet.documentlibrary.model.DLFileProfile[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)sr.get(0);

					if (dlFileProfileHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileProfile curDLFileProfile =
						DLFileProfileHBMUtil.model(dlFileProfileHBM);
					int value = obc.compare(dlFileProfile, curDLFileProfile);

					if (value == 0) {
						if (!dlFileProfile.equals(curDLFileProfile)) {
							break;
						}

						array[1] = curDLFileProfile;

						if (sr.previous()) {
							array[0] = DLFileProfileHBMUtil.model((DLFileProfileHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileProfileHBMUtil.model((DLFileProfileHBM)sr.get(
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

	public List findByC_R(String companyId, String repositoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
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

	public List findByC_R(String companyId, String repositoryId, int begin,
		int end) throws SystemException {
		return findByC_R(companyId, repositoryId, begin, end, null);
	}

	public List findByC_R(String companyId, String repositoryId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
					list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)sr.get(0);
						list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByC_R_First(
		String companyId, String repositoryId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		List list = findByC_R(companyId, repositoryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileProfileException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileProfile)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile findByC_R_Last(
		String companyId, String repositoryId, OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		int count = countByC_R(companyId, repositoryId);
		List list = findByC_R(companyId, repositoryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileProfileException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileProfile)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileProfile[] findByC_R_PrevAndNext(
		DLFileProfilePK dlFileProfilePK, String companyId, String repositoryId,
		OrderByComparator obc)
		throws NoSuchFileProfileException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileProfile dlFileProfile = findByPrimaryKey(dlFileProfilePK);
		int count = countByC_R(companyId, repositoryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			com.liferay.portlet.documentlibrary.model.DLFileProfile[] array = new com.liferay.portlet.documentlibrary.model.DLFileProfile[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)sr.get(0);

					if (dlFileProfileHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileProfile curDLFileProfile =
						DLFileProfileHBMUtil.model(dlFileProfileHBM);
					int value = obc.compare(dlFileProfile, curDLFileProfile);

					if (value == 0) {
						if (!dlFileProfile.equals(curDLFileProfile)) {
							break;
						}

						array[1] = curDLFileProfile;

						if (sr.previous()) {
							array[0] = DLFileProfileHBMUtil.model((DLFileProfileHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileProfileHBMUtil.model((DLFileProfileHBM)sr.get(
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				list.add(DLFileProfileHBMUtil.model(dlFileProfileHBM));
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				DLFileProfilePool.remove((DLFileProfilePK)dlFileProfileHBM.getPrimaryKey());
				session.delete(dlFileProfileHBM);
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				DLFileProfilePool.remove((DLFileProfilePK)dlFileProfileHBM.getPrimaryKey());
				session.delete(dlFileProfileHBM);
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

	public void removeByC_R(String companyId, String repositoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileProfileHBM dlFileProfileHBM = (DLFileProfileHBM)itr.next();
				DLFileProfilePool.remove((DLFileProfilePK)dlFileProfileHBM.getPrimaryKey());
				session.delete(dlFileProfileHBM);
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
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
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
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

	public int countByC_R(String companyId, String repositoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLFileProfile IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileProfileHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

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

	private static final Log _log = LogFactory.getLog(DLFileProfilePersistence.class);
}