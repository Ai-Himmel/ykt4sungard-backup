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

package com.liferay.portlet.imagegallery.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.imagegallery.NoSuchFolderException;

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
 * <a href="IGFolderPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGFolderPersistence extends BasePersistence {
	public com.liferay.portlet.imagegallery.model.IGFolder create(
		String folderId) {
		return new com.liferay.portlet.imagegallery.model.IGFolder(folderId);
	}

	public com.liferay.portlet.imagegallery.model.IGFolder remove(
		String folderId) throws NoSuchFolderException, SystemException {
		Session session = null;

		try {
			session = openSession();

			IGFolderHBM igFolderHBM = (IGFolderHBM)session.get(IGFolderHBM.class,
					folderId);

			if (igFolderHBM == null) {
				_log.warn("No IGFolder exists with the primary key of " +
					folderId.toString());
				throw new NoSuchFolderException(folderId.toString());
			}

			com.liferay.portlet.imagegallery.model.IGFolder igFolder = IGFolderHBMUtil.model(igFolderHBM);
			session.delete(igFolderHBM);
			session.flush();
			IGFolderPool.remove(folderId);

			return igFolder;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder update(
		com.liferay.portlet.imagegallery.model.IGFolder igFolder)
		throws SystemException {
		Session session = null;

		try {
			if (igFolder.isNew() || igFolder.isModified()) {
				session = openSession();

				if (igFolder.isNew()) {
					IGFolderHBM igFolderHBM = new IGFolderHBM(igFolder.getFolderId(),
							igFolder.getGroupId(), igFolder.getCompanyId(),
							igFolder.getUserId(), igFolder.getCreateDate(),
							igFolder.getModifiedDate(),
							igFolder.getParentFolderId(), igFolder.getName());
					session.save(igFolderHBM);
					session.flush();
				}
				else {
					IGFolderHBM igFolderHBM = (IGFolderHBM)session.get(IGFolderHBM.class,
							igFolder.getPrimaryKey());

					if (igFolderHBM != null) {
						igFolderHBM.setGroupId(igFolder.getGroupId());
						igFolderHBM.setCompanyId(igFolder.getCompanyId());
						igFolderHBM.setUserId(igFolder.getUserId());
						igFolderHBM.setCreateDate(igFolder.getCreateDate());
						igFolderHBM.setModifiedDate(igFolder.getModifiedDate());
						igFolderHBM.setParentFolderId(igFolder.getParentFolderId());
						igFolderHBM.setName(igFolder.getName());
						session.flush();
					}
					else {
						igFolderHBM = new IGFolderHBM(igFolder.getFolderId(),
								igFolder.getGroupId(), igFolder.getCompanyId(),
								igFolder.getUserId(), igFolder.getCreateDate(),
								igFolder.getModifiedDate(),
								igFolder.getParentFolderId(), igFolder.getName());
						session.save(igFolderHBM);
						session.flush();
					}
				}

				igFolder.setNew(false);
				igFolder.setModified(false);
				igFolder.protect();
				IGFolderPool.put(igFolder.getPrimaryKey(), igFolder);
			}

			return igFolder;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder findByPrimaryKey(
		String folderId) throws NoSuchFolderException, SystemException {
		com.liferay.portlet.imagegallery.model.IGFolder igFolder = IGFolderPool.get(folderId);
		Session session = null;

		try {
			if (igFolder == null) {
				session = openSession();

				IGFolderHBM igFolderHBM = (IGFolderHBM)session.get(IGFolderHBM.class,
						folderId);

				if (igFolderHBM == null) {
					_log.warn("No IGFolder exists with the primary key of " +
						folderId.toString());
					throw new NoSuchFolderException(folderId.toString());
				}

				igFolder = IGFolderHBMUtil.model(igFolderHBM);
			}

			return igFolder;
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				list.add(IGFolderHBMUtil.model(igFolderHBM));
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
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
			q.setString(queryPos++, groupId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
					list.add(IGFolderHBMUtil.model(igFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						IGFolderHBM igFolderHBM = (IGFolderHBM)sr.get(0);
						list.add(IGFolderHBMUtil.model(igFolderHBM));

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

	public com.liferay.portlet.imagegallery.model.IGFolder findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGFolder)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGFolder)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder[] findByGroupId_PrevAndNext(
		String folderId, String groupId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		com.liferay.portlet.imagegallery.model.IGFolder igFolder = findByPrimaryKey(folderId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
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
			q.setString(queryPos++, groupId);

			com.liferay.portlet.imagegallery.model.IGFolder[] array = new com.liferay.portlet.imagegallery.model.IGFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					IGFolderHBM igFolderHBM = (IGFolderHBM)sr.get(0);

					if (igFolderHBM == null) {
						break;
					}

					com.liferay.portlet.imagegallery.model.IGFolder curIGFolder = IGFolderHBMUtil.model(igFolderHBM);
					int value = obc.compare(igFolder, curIGFolder);

					if (value == 0) {
						if (!igFolder.equals(curIGFolder)) {
							break;
						}

						array[1] = curIGFolder;

						if (sr.previous()) {
							array[0] = IGFolderHBMUtil.model((IGFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = IGFolderHBMUtil.model((IGFolderHBM)sr.get(
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				list.add(IGFolderHBMUtil.model(igFolderHBM));
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
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
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
					list.add(IGFolderHBMUtil.model(igFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						IGFolderHBM igFolderHBM = (IGFolderHBM)sr.get(0);
						list.add(IGFolderHBMUtil.model(igFolderHBM));

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

	public com.liferay.portlet.imagegallery.model.IGFolder findByG_C_First(
		String groupId, String companyId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		List list = findByG_C(groupId, companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGFolder)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder findByG_C_Last(
		String groupId, String companyId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		int count = countByG_C(groupId, companyId);
		List list = findByG_C(groupId, companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGFolder)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder[] findByG_C_PrevAndNext(
		String folderId, String groupId, String companyId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		com.liferay.portlet.imagegallery.model.IGFolder igFolder = findByPrimaryKey(folderId);
		int count = countByG_C(groupId, companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
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
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			com.liferay.portlet.imagegallery.model.IGFolder[] array = new com.liferay.portlet.imagegallery.model.IGFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					IGFolderHBM igFolderHBM = (IGFolderHBM)sr.get(0);

					if (igFolderHBM == null) {
						break;
					}

					com.liferay.portlet.imagegallery.model.IGFolder curIGFolder = IGFolderHBMUtil.model(igFolderHBM);
					int value = obc.compare(igFolder, curIGFolder);

					if (value == 0) {
						if (!igFolder.equals(curIGFolder)) {
							break;
						}

						array[1] = curIGFolder;

						if (sr.previous()) {
							array[0] = IGFolderHBMUtil.model((IGFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = IGFolderHBMUtil.model((IGFolderHBM)sr.get(
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

	public List findByG_C_P(String groupId, String companyId,
		String parentFolderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentFolderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				list.add(IGFolderHBMUtil.model(igFolderHBM));
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

	public List findByG_C_P(String groupId, String companyId,
		String parentFolderId, int begin, int end) throws SystemException {
		return findByG_C_P(groupId, companyId, parentFolderId, begin, end, null);
	}

	public List findByG_C_P(String groupId, String companyId,
		String parentFolderId, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
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
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentFolderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
					list.add(IGFolderHBMUtil.model(igFolderHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						IGFolderHBM igFolderHBM = (IGFolderHBM)sr.get(0);
						list.add(IGFolderHBMUtil.model(igFolderHBM));

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

	public com.liferay.portlet.imagegallery.model.IGFolder findByG_C_P_First(
		String groupId, String companyId, String parentFolderId,
		OrderByComparator obc) throws NoSuchFolderException, SystemException {
		List list = findByG_C_P(groupId, companyId, parentFolderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGFolder)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder findByG_C_P_Last(
		String groupId, String companyId, String parentFolderId,
		OrderByComparator obc) throws NoSuchFolderException, SystemException {
		int count = countByG_C_P(groupId, companyId, parentFolderId);
		List list = findByG_C_P(groupId, companyId, parentFolderId, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchFolderException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGFolder)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGFolder[] findByG_C_P_PrevAndNext(
		String folderId, String groupId, String companyId,
		String parentFolderId, OrderByComparator obc)
		throws NoSuchFolderException, SystemException {
		com.liferay.portlet.imagegallery.model.IGFolder igFolder = findByPrimaryKey(folderId);
		int count = countByG_C_P(groupId, companyId, parentFolderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
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
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentFolderId);

			com.liferay.portlet.imagegallery.model.IGFolder[] array = new com.liferay.portlet.imagegallery.model.IGFolder[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					IGFolderHBM igFolderHBM = (IGFolderHBM)sr.get(0);

					if (igFolderHBM == null) {
						break;
					}

					com.liferay.portlet.imagegallery.model.IGFolder curIGFolder = IGFolderHBMUtil.model(igFolderHBM);
					int value = obc.compare(igFolder, curIGFolder);

					if (value == 0) {
						if (!igFolder.equals(curIGFolder)) {
							break;
						}

						array[1] = curIGFolder;

						if (sr.previous()) {
							array[0] = IGFolderHBMUtil.model((IGFolderHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = IGFolderHBMUtil.model((IGFolderHBM)sr.get(
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				list.add(IGFolderHBMUtil.model(igFolderHBM));
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				IGFolderPool.remove((String)igFolderHBM.getPrimaryKey());
				session.delete(igFolderHBM);
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				IGFolderPool.remove((String)igFolderHBM.getPrimaryKey());
				session.delete(igFolderHBM);
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

	public void removeByG_C_P(String groupId, String companyId,
		String parentFolderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentFolderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				IGFolderHBM igFolderHBM = (IGFolderHBM)itr.next();
				IGFolderPool.remove((String)igFolderHBM.getPrimaryKey());
				session.delete(igFolderHBM);
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
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
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

	public int countByG_C(String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
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

	public int countByG_C_P(String groupId, String companyId,
		String parentFolderId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM IGFolder IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGFolderHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentFolderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentFolderId);

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

	private static final Log _log = LogFactory.getLog(IGFolderPersistence.class);
}