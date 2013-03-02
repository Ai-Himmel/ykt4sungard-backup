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

import com.liferay.portlet.imagegallery.NoSuchImageException;

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
 * <a href="IGImagePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class IGImagePersistence extends BasePersistence {
	public com.liferay.portlet.imagegallery.model.IGImage create(
		IGImagePK igImagePK) {
		return new com.liferay.portlet.imagegallery.model.IGImage(igImagePK);
	}

	public com.liferay.portlet.imagegallery.model.IGImage remove(
		IGImagePK igImagePK) throws NoSuchImageException, SystemException {
		Session session = null;

		try {
			session = openSession();

			IGImageHBM igImageHBM = (IGImageHBM)session.get(IGImageHBM.class,
					igImagePK);

			if (igImageHBM == null) {
				_log.warn("No IGImage exists with the primary key of " +
					igImagePK.toString());
				throw new NoSuchImageException(igImagePK.toString());
			}

			com.liferay.portlet.imagegallery.model.IGImage igImage = IGImageHBMUtil.model(igImageHBM);
			session.delete(igImageHBM);
			session.flush();
			IGImagePool.remove(igImagePK);

			return igImage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage update(
		com.liferay.portlet.imagegallery.model.IGImage igImage)
		throws SystemException {
		Session session = null;

		try {
			if (igImage.isNew() || igImage.isModified()) {
				session = openSession();

				if (igImage.isNew()) {
					IGImageHBM igImageHBM = new IGImageHBM(igImage.getImageId(),
							igImage.getCompanyId(), igImage.getUserId(),
							igImage.getCreateDate(), igImage.getModifiedDate(),
							igImage.getFolderId(), igImage.getDescription(),
							igImage.getHeight(), igImage.getWidth(),
							igImage.getSize());
					session.save(igImageHBM);
					session.flush();
				}
				else {
					IGImageHBM igImageHBM = (IGImageHBM)session.get(IGImageHBM.class,
							igImage.getPrimaryKey());

					if (igImageHBM != null) {
						igImageHBM.setUserId(igImage.getUserId());
						igImageHBM.setCreateDate(igImage.getCreateDate());
						igImageHBM.setModifiedDate(igImage.getModifiedDate());
						igImageHBM.setFolderId(igImage.getFolderId());
						igImageHBM.setDescription(igImage.getDescription());
						igImageHBM.setHeight(igImage.getHeight());
						igImageHBM.setWidth(igImage.getWidth());
						igImageHBM.setSize(igImage.getSize());
						session.flush();
					}
					else {
						igImageHBM = new IGImageHBM(igImage.getImageId(),
								igImage.getCompanyId(), igImage.getUserId(),
								igImage.getCreateDate(),
								igImage.getModifiedDate(),
								igImage.getFolderId(),
								igImage.getDescription(), igImage.getHeight(),
								igImage.getWidth(), igImage.getSize());
						session.save(igImageHBM);
						session.flush();
					}
				}

				igImage.setNew(false);
				igImage.setModified(false);
				igImage.protect();
				IGImagePool.put(igImage.getPrimaryKey(), igImage);
			}

			return igImage;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage findByPrimaryKey(
		IGImagePK igImagePK) throws NoSuchImageException, SystemException {
		com.liferay.portlet.imagegallery.model.IGImage igImage = IGImagePool.get(igImagePK);
		Session session = null;

		try {
			if (igImage == null) {
				session = openSession();

				IGImageHBM igImageHBM = (IGImageHBM)session.get(IGImageHBM.class,
						igImagePK);

				if (igImageHBM == null) {
					_log.warn("No IGImage exists with the primary key of " +
						igImagePK.toString());
					throw new NoSuchImageException(igImagePK.toString());
				}

				igImage = IGImageHBMUtil.model(igImageHBM);
			}

			return igImage;
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				list.add(IGImageHBMUtil.model(igImageHBM));
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
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
					IGImageHBM igImageHBM = (IGImageHBM)itr.next();
					list.add(IGImageHBMUtil.model(igImageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						IGImageHBM igImageHBM = (IGImageHBM)sr.get(0);
						list.add(IGImageHBMUtil.model(igImageHBM));

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

	public com.liferay.portlet.imagegallery.model.IGImage findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchImageException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGImage)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchImageException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGImage)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage[] findByCompanyId_PrevAndNext(
		IGImagePK igImagePK, String companyId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		com.liferay.portlet.imagegallery.model.IGImage igImage = findByPrimaryKey(igImagePK);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.imagegallery.model.IGImage[] array = new com.liferay.portlet.imagegallery.model.IGImage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					IGImageHBM igImageHBM = (IGImageHBM)sr.get(0);

					if (igImageHBM == null) {
						break;
					}

					com.liferay.portlet.imagegallery.model.IGImage curIGImage = IGImageHBMUtil.model(igImageHBM);
					int value = obc.compare(igImage, curIGImage);

					if (value == 0) {
						if (!igImage.equals(curIGImage)) {
							break;
						}

						array[1] = curIGImage;

						if (sr.previous()) {
							array[0] = IGImageHBMUtil.model((IGImageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = IGImageHBMUtil.model((IGImageHBM)sr.get(
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				list.add(IGImageHBMUtil.model(igImageHBM));
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
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
					IGImageHBM igImageHBM = (IGImageHBM)itr.next();
					list.add(IGImageHBMUtil.model(igImageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						IGImageHBM igImageHBM = (IGImageHBM)sr.get(0);
						list.add(IGImageHBMUtil.model(igImageHBM));

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

	public com.liferay.portlet.imagegallery.model.IGImage findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchImageException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGImage)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchImageException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGImage)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage[] findByUserId_PrevAndNext(
		IGImagePK igImagePK, String userId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		com.liferay.portlet.imagegallery.model.IGImage igImage = findByPrimaryKey(igImagePK);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.imagegallery.model.IGImage[] array = new com.liferay.portlet.imagegallery.model.IGImage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					IGImageHBM igImageHBM = (IGImageHBM)sr.get(0);

					if (igImageHBM == null) {
						break;
					}

					com.liferay.portlet.imagegallery.model.IGImage curIGImage = IGImageHBMUtil.model(igImageHBM);
					int value = obc.compare(igImage, curIGImage);

					if (value == 0) {
						if (!igImage.equals(curIGImage)) {
							break;
						}

						array[1] = curIGImage;

						if (sr.previous()) {
							array[0] = IGImageHBMUtil.model((IGImageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = IGImageHBMUtil.model((IGImageHBM)sr.get(
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

	public List findByC_F(String companyId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, folderId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				list.add(IGImageHBMUtil.model(igImageHBM));
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

	public List findByC_F(String companyId, String folderId, int begin, int end)
		throws SystemException {
		return findByC_F(companyId, folderId, begin, end, null);
	}

	public List findByC_F(String companyId, String folderId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, folderId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					IGImageHBM igImageHBM = (IGImageHBM)itr.next();
					list.add(IGImageHBMUtil.model(igImageHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						IGImageHBM igImageHBM = (IGImageHBM)sr.get(0);
						list.add(IGImageHBMUtil.model(igImageHBM));

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

	public com.liferay.portlet.imagegallery.model.IGImage findByC_F_First(
		String companyId, String folderId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		List list = findByC_F(companyId, folderId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchImageException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGImage)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage findByC_F_Last(
		String companyId, String folderId, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		int count = countByC_F(companyId, folderId);
		List list = findByC_F(companyId, folderId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchImageException();
		}
		else {
			return (com.liferay.portlet.imagegallery.model.IGImage)list.get(0);
		}
	}

	public com.liferay.portlet.imagegallery.model.IGImage[] findByC_F_PrevAndNext(
		IGImagePK igImagePK, String companyId, String folderId,
		OrderByComparator obc) throws NoSuchImageException, SystemException {
		com.liferay.portlet.imagegallery.model.IGImage igImage = findByPrimaryKey(igImagePK);
		int count = countByC_F(companyId, folderId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, folderId);

			com.liferay.portlet.imagegallery.model.IGImage[] array = new com.liferay.portlet.imagegallery.model.IGImage[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					IGImageHBM igImageHBM = (IGImageHBM)sr.get(0);

					if (igImageHBM == null) {
						break;
					}

					com.liferay.portlet.imagegallery.model.IGImage curIGImage = IGImageHBMUtil.model(igImageHBM);
					int value = obc.compare(igImage, curIGImage);

					if (value == 0) {
						if (!igImage.equals(curIGImage)) {
							break;
						}

						array[1] = curIGImage;

						if (sr.previous()) {
							array[0] = IGImageHBMUtil.model((IGImageHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = IGImageHBMUtil.model((IGImageHBM)sr.get(
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				list.add(IGImageHBMUtil.model(igImageHBM));
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				IGImagePool.remove((IGImagePK)igImageHBM.getPrimaryKey());
				session.delete(igImageHBM);
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				IGImagePool.remove((IGImagePK)igImageHBM.getPrimaryKey());
				session.delete(igImageHBM);
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

	public void removeByC_F(String companyId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, folderId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				IGImageHBM igImageHBM = (IGImageHBM)itr.next();
				IGImagePool.remove((IGImagePK)igImageHBM.getPrimaryKey());
				session.delete(igImageHBM);
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
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
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
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

	public int countByC_F(String companyId, String folderId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM IGImage IN CLASS com.liferay.portlet.imagegallery.service.persistence.IGImageHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("folderId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, folderId);

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

	private static final Log _log = LogFactory.getLog(IGImagePersistence.class);
}