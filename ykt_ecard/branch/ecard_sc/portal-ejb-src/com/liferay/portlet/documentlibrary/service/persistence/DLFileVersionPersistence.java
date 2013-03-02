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

import com.liferay.portlet.documentlibrary.NoSuchFileVersionException;

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
 * <a href="DLFileVersionPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class DLFileVersionPersistence extends BasePersistence {
	public com.liferay.portlet.documentlibrary.model.DLFileVersion create(
		DLFileVersionPK dlFileVersionPK) {
		return new com.liferay.portlet.documentlibrary.model.DLFileVersion(dlFileVersionPK);
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion remove(
		DLFileVersionPK dlFileVersionPK)
		throws NoSuchFileVersionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)session.get(DLFileVersionHBM.class,
					dlFileVersionPK);

			if (dlFileVersionHBM == null) {
				_log.warn("No DLFileVersion exists with the primary key of " +
					dlFileVersionPK.toString());
				throw new NoSuchFileVersionException(dlFileVersionPK.toString());
			}

			com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion =
				DLFileVersionHBMUtil.model(dlFileVersionHBM);
			session.delete(dlFileVersionHBM);
			session.flush();
			DLFileVersionPool.remove(dlFileVersionPK);

			return dlFileVersion;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion update(
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion)
		throws SystemException {
		Session session = null;

		try {
			if (dlFileVersion.isNew() || dlFileVersion.isModified()) {
				session = openSession();

				if (dlFileVersion.isNew()) {
					DLFileVersionHBM dlFileVersionHBM = new DLFileVersionHBM(dlFileVersion.getCompanyId(),
							dlFileVersion.getRepositoryId(),
							dlFileVersion.getFileName(),
							dlFileVersion.getVersion(),
							dlFileVersion.getUserId(),
							dlFileVersion.getUserName(),
							dlFileVersion.getCreateDate(),
							dlFileVersion.getSize());
					session.save(dlFileVersionHBM);
					session.flush();
				}
				else {
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)session.get(DLFileVersionHBM.class,
							dlFileVersion.getPrimaryKey());

					if (dlFileVersionHBM != null) {
						dlFileVersionHBM.setUserId(dlFileVersion.getUserId());
						dlFileVersionHBM.setUserName(dlFileVersion.getUserName());
						dlFileVersionHBM.setCreateDate(dlFileVersion.getCreateDate());
						dlFileVersionHBM.setSize(dlFileVersion.getSize());
						session.flush();
					}
					else {
						dlFileVersionHBM = new DLFileVersionHBM(dlFileVersion.getCompanyId(),
								dlFileVersion.getRepositoryId(),
								dlFileVersion.getFileName(),
								dlFileVersion.getVersion(),
								dlFileVersion.getUserId(),
								dlFileVersion.getUserName(),
								dlFileVersion.getCreateDate(),
								dlFileVersion.getSize());
						session.save(dlFileVersionHBM);
						session.flush();
					}
				}

				dlFileVersion.setNew(false);
				dlFileVersion.setModified(false);
				dlFileVersion.protect();
				DLFileVersionPool.put(dlFileVersion.getPrimaryKey(),
					dlFileVersion);
			}

			return dlFileVersion;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByPrimaryKey(
		DLFileVersionPK dlFileVersionPK)
		throws NoSuchFileVersionException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion = DLFileVersionPool.get(dlFileVersionPK);
		Session session = null;

		try {
			if (dlFileVersion == null) {
				session = openSession();

				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)session.get(DLFileVersionHBM.class,
						dlFileVersionPK);

				if (dlFileVersionHBM == null) {
					_log.warn(
						"No DLFileVersion exists with the primary key of " +
						dlFileVersionPK.toString());
					throw new NoSuchFileVersionException(dlFileVersionPK.toString());
				}

				dlFileVersion = DLFileVersionHBMUtil.model(dlFileVersionHBM);
			}

			return dlFileVersion;
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("repositoryId DESC").append(", ");
				query.append("fileName DESC").append(", ");
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
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
					list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)sr.get(0);
						list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileVersionException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileVersion)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileVersionException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileVersion)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion[] findByCompanyId_PrevAndNext(
		DLFileVersionPK dlFileVersionPK, String companyId, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion = findByPrimaryKey(dlFileVersionPK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("repositoryId DESC").append(", ");
				query.append("fileName DESC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.documentlibrary.model.DLFileVersion[] array = new com.liferay.portlet.documentlibrary.model.DLFileVersion[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)sr.get(0);

					if (dlFileVersionHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileVersion curDLFileVersion =
						DLFileVersionHBMUtil.model(dlFileVersionHBM);
					int value = obc.compare(dlFileVersion, curDLFileVersion);

					if (value == 0) {
						if (!dlFileVersion.equals(curDLFileVersion)) {
							break;
						}

						array[1] = curDLFileVersion;

						if (sr.previous()) {
							array[0] = DLFileVersionHBMUtil.model((DLFileVersionHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileVersionHBMUtil.model((DLFileVersionHBM)sr.get(
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("repositoryId DESC").append(", ");
				query.append("fileName DESC").append(", ");
				query.append("version DESC");
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
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
					list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)sr.get(0);
						list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByC_R_First(
		String companyId, String repositoryId, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		List list = findByC_R(companyId, repositoryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileVersionException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileVersion)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByC_R_Last(
		String companyId, String repositoryId, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		int count = countByC_R(companyId, repositoryId);
		List list = findByC_R(companyId, repositoryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileVersionException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileVersion)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion[] findByC_R_PrevAndNext(
		DLFileVersionPK dlFileVersionPK, String companyId, String repositoryId,
		OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion = findByPrimaryKey(dlFileVersionPK);
		int count = countByC_R(companyId, repositoryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("repositoryId DESC").append(", ");
				query.append("fileName DESC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			com.liferay.portlet.documentlibrary.model.DLFileVersion[] array = new com.liferay.portlet.documentlibrary.model.DLFileVersion[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)sr.get(0);

					if (dlFileVersionHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileVersion curDLFileVersion =
						DLFileVersionHBMUtil.model(dlFileVersionHBM);
					int value = obc.compare(dlFileVersion, curDLFileVersion);

					if (value == 0) {
						if (!dlFileVersion.equals(curDLFileVersion)) {
							break;
						}

						array[1] = curDLFileVersion;

						if (sr.previous()) {
							array[0] = DLFileVersionHBMUtil.model((DLFileVersionHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileVersionHBMUtil.model((DLFileVersionHBM)sr.get(
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
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
				query.append("companyId DESC").append(", ");
				query.append("repositoryId DESC").append(", ");
				query.append("fileName DESC").append(", ");
				query.append("version DESC");
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
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
					list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)sr.get(0);
						list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));

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

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByC_R_FN_First(
		String companyId, String repositoryId, String fileName,
		OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		List list = findByC_R_FN(companyId, repositoryId, fileName, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFileVersionException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileVersion)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion findByC_R_FN_Last(
		String companyId, String repositoryId, String fileName,
		OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		int count = countByC_R_FN(companyId, repositoryId, fileName);
		List list = findByC_R_FN(companyId, repositoryId, fileName, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchFileVersionException();
		}
		else {
			return (com.liferay.portlet.documentlibrary.model.DLFileVersion)list.get(0);
		}
	}

	public com.liferay.portlet.documentlibrary.model.DLFileVersion[] findByC_R_FN_PrevAndNext(
		DLFileVersionPK dlFileVersionPK, String companyId, String repositoryId,
		String fileName, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion = findByPrimaryKey(dlFileVersionPK);
		int count = countByC_R_FN(companyId, repositoryId, fileName);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
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
				query.append("companyId DESC").append(", ");
				query.append("repositoryId DESC").append(", ");
				query.append("fileName DESC").append(", ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			com.liferay.portlet.documentlibrary.model.DLFileVersion[] array = new com.liferay.portlet.documentlibrary.model.DLFileVersion[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)sr.get(0);

					if (dlFileVersionHBM == null) {
						break;
					}

					com.liferay.portlet.documentlibrary.model.DLFileVersion curDLFileVersion =
						DLFileVersionHBMUtil.model(dlFileVersionHBM);
					int value = obc.compare(dlFileVersion, curDLFileVersion);

					if (value == 0) {
						if (!dlFileVersion.equals(curDLFileVersion)) {
							break;
						}

						array[1] = curDLFileVersion;

						if (sr.previous()) {
							array[0] = DLFileVersionHBMUtil.model((DLFileVersionHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = DLFileVersionHBMUtil.model((DLFileVersionHBM)sr.get(
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				list.add(DLFileVersionHBMUtil.model(dlFileVersionHBM));
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				DLFileVersionPool.remove((DLFileVersionPK)dlFileVersionHBM.getPrimaryKey());
				session.delete(dlFileVersionHBM);
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				DLFileVersionPool.remove((DLFileVersionPK)dlFileVersionHBM.getPrimaryKey());
				session.delete(dlFileVersionHBM);
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repositoryId = ?");
			query.append(" AND ");
			query.append("fileName = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("repositoryId DESC").append(", ");
			query.append("fileName DESC").append(", ");
			query.append("version DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, repositoryId);
			q.setString(queryPos++, fileName);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				DLFileVersionHBM dlFileVersionHBM = (DLFileVersionHBM)itr.next();
				DLFileVersionPool.remove((DLFileVersionPK)dlFileVersionHBM.getPrimaryKey());
				session.delete(dlFileVersionHBM);
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
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
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

	public int countByC_R(String companyId, String repositoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
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

	public int countByC_R_FN(String companyId, String repositoryId,
		String fileName) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM DLFileVersion IN CLASS com.liferay.portlet.documentlibrary.service.persistence.DLFileVersionHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(DLFileVersionPersistence.class);
}