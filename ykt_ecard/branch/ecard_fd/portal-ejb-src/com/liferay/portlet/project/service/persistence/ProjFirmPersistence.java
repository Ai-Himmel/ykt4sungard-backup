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

package com.liferay.portlet.project.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.project.NoSuchFirmException;

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
 * <a href="ProjFirmPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjFirmPersistence extends BasePersistence {
	public com.liferay.portlet.project.model.ProjFirm create(String firmId) {
		return new com.liferay.portlet.project.model.ProjFirm(firmId);
	}

	public com.liferay.portlet.project.model.ProjFirm remove(String firmId)
		throws NoSuchFirmException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjFirmHBM projFirmHBM = (ProjFirmHBM)session.get(ProjFirmHBM.class,
					firmId);

			if (projFirmHBM == null) {
				_log.warn("No ProjFirm exists with the primary key of " +
					firmId.toString());
				throw new NoSuchFirmException(firmId.toString());
			}

			com.liferay.portlet.project.model.ProjFirm projFirm = ProjFirmHBMUtil.model(projFirmHBM);
			session.delete(projFirmHBM);
			session.flush();
			ProjFirmPool.remove(firmId);

			return projFirm;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjFirm update(
		com.liferay.portlet.project.model.ProjFirm projFirm)
		throws SystemException {
		Session session = null;

		try {
			if (projFirm.isNew() || projFirm.isModified()) {
				session = openSession();

				if (projFirm.isNew()) {
					ProjFirmHBM projFirmHBM = new ProjFirmHBM(projFirm.getFirmId(),
							projFirm.getCompanyId(), projFirm.getUserId(),
							projFirm.getUserName(), projFirm.getCreateDate(),
							projFirm.getModifiedDate(), projFirm.getName(),
							projFirm.getDescription(), projFirm.getUrl());
					session.save(projFirmHBM);
					session.flush();
				}
				else {
					ProjFirmHBM projFirmHBM = (ProjFirmHBM)session.get(ProjFirmHBM.class,
							projFirm.getPrimaryKey());

					if (projFirmHBM != null) {
						projFirmHBM.setCompanyId(projFirm.getCompanyId());
						projFirmHBM.setUserId(projFirm.getUserId());
						projFirmHBM.setUserName(projFirm.getUserName());
						projFirmHBM.setCreateDate(projFirm.getCreateDate());
						projFirmHBM.setModifiedDate(projFirm.getModifiedDate());
						projFirmHBM.setName(projFirm.getName());
						projFirmHBM.setDescription(projFirm.getDescription());
						projFirmHBM.setUrl(projFirm.getUrl());
						session.flush();
					}
					else {
						projFirmHBM = new ProjFirmHBM(projFirm.getFirmId(),
								projFirm.getCompanyId(), projFirm.getUserId(),
								projFirm.getUserName(),
								projFirm.getCreateDate(),
								projFirm.getModifiedDate(), projFirm.getName(),
								projFirm.getDescription(), projFirm.getUrl());
						session.save(projFirmHBM);
						session.flush();
					}
				}

				projFirm.setNew(false);
				projFirm.setModified(false);
				projFirm.protect();
				ProjFirmPool.put(projFirm.getPrimaryKey(), projFirm);
			}

			return projFirm;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjFirm findByPrimaryKey(
		String firmId) throws NoSuchFirmException, SystemException {
		com.liferay.portlet.project.model.ProjFirm projFirm = ProjFirmPool.get(firmId);
		Session session = null;

		try {
			if (projFirm == null) {
				session = openSession();

				ProjFirmHBM projFirmHBM = (ProjFirmHBM)session.get(ProjFirmHBM.class,
						firmId);

				if (projFirmHBM == null) {
					_log.warn("No ProjFirm exists with the primary key of " +
						firmId.toString());
					throw new NoSuchFirmException(firmId.toString());
				}

				projFirm = ProjFirmHBMUtil.model(projFirmHBM);
			}

			return projFirm;
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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
				ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
				list.add(ProjFirmHBMUtil.model(projFirmHBM));
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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
					ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
					list.add(ProjFirmHBMUtil.model(projFirmHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjFirmHBM projFirmHBM = (ProjFirmHBM)sr.get(0);
						list.add(ProjFirmHBMUtil.model(projFirmHBM));

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

	public com.liferay.portlet.project.model.ProjFirm findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchFirmException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFirmException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjFirm)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjFirm findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchFirmException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFirmException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjFirm)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjFirm[] findByCompanyId_PrevAndNext(
		String firmId, String companyId, OrderByComparator obc)
		throws NoSuchFirmException, SystemException {
		com.liferay.portlet.project.model.ProjFirm projFirm = findByPrimaryKey(firmId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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

			com.liferay.portlet.project.model.ProjFirm[] array = new com.liferay.portlet.project.model.ProjFirm[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjFirmHBM projFirmHBM = (ProjFirmHBM)sr.get(0);

					if (projFirmHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjFirm curProjFirm = ProjFirmHBMUtil.model(projFirmHBM);
					int value = obc.compare(projFirm, curProjFirm);

					if (value == 0) {
						if (!projFirm.equals(curProjFirm)) {
							break;
						}

						array[1] = curProjFirm;

						if (sr.previous()) {
							array[0] = ProjFirmHBMUtil.model((ProjFirmHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjFirmHBMUtil.model((ProjFirmHBM)sr.get(
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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
				ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
				list.add(ProjFirmHBMUtil.model(projFirmHBM));
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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
					ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
					list.add(ProjFirmHBMUtil.model(projFirmHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjFirmHBM projFirmHBM = (ProjFirmHBM)sr.get(0);
						list.add(ProjFirmHBMUtil.model(projFirmHBM));

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

	public com.liferay.portlet.project.model.ProjFirm findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchFirmException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchFirmException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjFirm)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjFirm findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchFirmException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchFirmException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjFirm)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjFirm[] findByUserId_PrevAndNext(
		String firmId, String userId, OrderByComparator obc)
		throws NoSuchFirmException, SystemException {
		com.liferay.portlet.project.model.ProjFirm projFirm = findByPrimaryKey(firmId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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

			com.liferay.portlet.project.model.ProjFirm[] array = new com.liferay.portlet.project.model.ProjFirm[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjFirmHBM projFirmHBM = (ProjFirmHBM)sr.get(0);

					if (projFirmHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjFirm curProjFirm = ProjFirmHBMUtil.model(projFirmHBM);
					int value = obc.compare(projFirm, curProjFirm);

					if (value == 0) {
						if (!projFirm.equals(curProjFirm)) {
							break;
						}

						array[1] = curProjFirm;

						if (sr.previous()) {
							array[0] = ProjFirmHBMUtil.model((ProjFirmHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjFirmHBMUtil.model((ProjFirmHBM)sr.get(
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
				list.add(ProjFirmHBMUtil.model(projFirmHBM));
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
				ProjFirmPool.remove((String)projFirmHBM.getPrimaryKey());
				session.delete(projFirmHBM);
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjFirmHBM projFirmHBM = (ProjFirmHBM)itr.next();
				ProjFirmPool.remove((String)projFirmHBM.getPrimaryKey());
				session.delete(projFirmHBM);
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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
				"FROM ProjFirm IN CLASS com.liferay.portlet.project.service.persistence.ProjFirmHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(ProjFirmPersistence.class);
}