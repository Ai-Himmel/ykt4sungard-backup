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

import com.liferay.portlet.project.NoSuchTimeException;

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
 * <a href="ProjTimePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ProjTimePersistence extends BasePersistence {
	public com.liferay.portlet.project.model.ProjTime create(String timeId) {
		return new com.liferay.portlet.project.model.ProjTime(timeId);
	}

	public com.liferay.portlet.project.model.ProjTime remove(String timeId)
		throws NoSuchTimeException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ProjTimeHBM projTimeHBM = (ProjTimeHBM)session.get(ProjTimeHBM.class,
					timeId);

			if (projTimeHBM == null) {
				_log.warn("No ProjTime exists with the primary key of " +
					timeId.toString());
				throw new NoSuchTimeException(timeId.toString());
			}

			com.liferay.portlet.project.model.ProjTime projTime = ProjTimeHBMUtil.model(projTimeHBM);
			session.delete(projTimeHBM);
			session.flush();
			ProjTimePool.remove(timeId);

			return projTime;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTime update(
		com.liferay.portlet.project.model.ProjTime projTime)
		throws SystemException {
		Session session = null;

		try {
			if (projTime.isNew() || projTime.isModified()) {
				session = openSession();

				if (projTime.isNew()) {
					ProjTimeHBM projTimeHBM = new ProjTimeHBM(projTime.getTimeId(),
							projTime.getCompanyId(), projTime.getUserId(),
							projTime.getUserName(), projTime.getCreateDate(),
							projTime.getModifiedDate(),
							projTime.getProjectId(), projTime.getTaskId(),
							projTime.getDescription(), projTime.getStartDate(),
							projTime.getEndDate());
					session.save(projTimeHBM);
					session.flush();
				}
				else {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)session.get(ProjTimeHBM.class,
							projTime.getPrimaryKey());

					if (projTimeHBM != null) {
						projTimeHBM.setCompanyId(projTime.getCompanyId());
						projTimeHBM.setUserId(projTime.getUserId());
						projTimeHBM.setUserName(projTime.getUserName());
						projTimeHBM.setCreateDate(projTime.getCreateDate());
						projTimeHBM.setModifiedDate(projTime.getModifiedDate());
						projTimeHBM.setProjectId(projTime.getProjectId());
						projTimeHBM.setTaskId(projTime.getTaskId());
						projTimeHBM.setDescription(projTime.getDescription());
						projTimeHBM.setStartDate(projTime.getStartDate());
						projTimeHBM.setEndDate(projTime.getEndDate());
						session.flush();
					}
					else {
						projTimeHBM = new ProjTimeHBM(projTime.getTimeId(),
								projTime.getCompanyId(), projTime.getUserId(),
								projTime.getUserName(),
								projTime.getCreateDate(),
								projTime.getModifiedDate(),
								projTime.getProjectId(), projTime.getTaskId(),
								projTime.getDescription(),
								projTime.getStartDate(), projTime.getEndDate());
						session.save(projTimeHBM);
						session.flush();
					}
				}

				projTime.setNew(false);
				projTime.setModified(false);
				projTime.protect();
				ProjTimePool.put(projTime.getPrimaryKey(), projTime);
			}

			return projTime;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.project.model.ProjTime findByPrimaryKey(
		String timeId) throws NoSuchTimeException, SystemException {
		com.liferay.portlet.project.model.ProjTime projTime = ProjTimePool.get(timeId);
		Session session = null;

		try {
			if (projTime == null) {
				session = openSession();

				ProjTimeHBM projTimeHBM = (ProjTimeHBM)session.get(ProjTimeHBM.class,
						timeId);

				if (projTimeHBM == null) {
					_log.warn("No ProjTime exists with the primary key of " +
						timeId.toString());
					throw new NoSuchTimeException(timeId.toString());
				}

				projTime = ProjTimeHBMUtil.model(projTimeHBM);
			}

			return projTime;
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				list.add(ProjTimeHBMUtil.model(projTimeHBM));
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
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
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
					list.add(ProjTimeHBMUtil.model(projTimeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);
						list.add(ProjTimeHBMUtil.model(projTimeHBM));

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

	public com.liferay.portlet.project.model.ProjTime findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime[] findByCompanyId_PrevAndNext(
		String timeId, String companyId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		com.liferay.portlet.project.model.ProjTime projTime = findByPrimaryKey(timeId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.project.model.ProjTime[] array = new com.liferay.portlet.project.model.ProjTime[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);

					if (projTimeHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTime curProjTime = ProjTimeHBMUtil.model(projTimeHBM);
					int value = obc.compare(projTime, curProjTime);

					if (value == 0) {
						if (!projTime.equals(curProjTime)) {
							break;
						}

						array[1] = curProjTime;

						if (sr.previous()) {
							array[0] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				list.add(ProjTimeHBMUtil.model(projTimeHBM));
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
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
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
					list.add(ProjTimeHBMUtil.model(projTimeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);
						list.add(ProjTimeHBMUtil.model(projTimeHBM));

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

	public com.liferay.portlet.project.model.ProjTime findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime[] findByUserId_PrevAndNext(
		String timeId, String userId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		com.liferay.portlet.project.model.ProjTime projTime = findByPrimaryKey(timeId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.project.model.ProjTime[] array = new com.liferay.portlet.project.model.ProjTime[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);

					if (projTimeHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTime curProjTime = ProjTimeHBMUtil.model(projTimeHBM);
					int value = obc.compare(projTime, curProjTime);

					if (value == 0) {
						if (!projTime.equals(curProjTime)) {
							break;
						}

						array[1] = curProjTime;

						if (sr.previous()) {
							array[0] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
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

	public List findByProjectId(String projectId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				list.add(ProjTimeHBMUtil.model(projTimeHBM));
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

	public List findByProjectId(String projectId, int begin, int end)
		throws SystemException {
		return findByProjectId(projectId, begin, end, null);
	}

	public List findByProjectId(String projectId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
					list.add(ProjTimeHBMUtil.model(projTimeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);
						list.add(ProjTimeHBMUtil.model(projTimeHBM));

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

	public com.liferay.portlet.project.model.ProjTime findByProjectId_First(
		String projectId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		List list = findByProjectId(projectId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime findByProjectId_Last(
		String projectId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		int count = countByProjectId(projectId);
		List list = findByProjectId(projectId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime[] findByProjectId_PrevAndNext(
		String timeId, String projectId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		com.liferay.portlet.project.model.ProjTime projTime = findByPrimaryKey(timeId);
		int count = countByProjectId(projectId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			com.liferay.portlet.project.model.ProjTime[] array = new com.liferay.portlet.project.model.ProjTime[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);

					if (projTimeHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTime curProjTime = ProjTimeHBMUtil.model(projTimeHBM);
					int value = obc.compare(projTime, curProjTime);

					if (value == 0) {
						if (!projTime.equals(curProjTime)) {
							break;
						}

						array[1] = curProjTime;

						if (sr.previous()) {
							array[0] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
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

	public List findByTaskId(String taskId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("taskId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, taskId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				list.add(ProjTimeHBMUtil.model(projTimeHBM));
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

	public List findByTaskId(String taskId, int begin, int end)
		throws SystemException {
		return findByTaskId(taskId, begin, end, null);
	}

	public List findByTaskId(String taskId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("taskId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, taskId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
					list.add(ProjTimeHBMUtil.model(projTimeHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);
						list.add(ProjTimeHBMUtil.model(projTimeHBM));

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

	public com.liferay.portlet.project.model.ProjTime findByTaskId_First(
		String taskId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		List list = findByTaskId(taskId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime findByTaskId_Last(
		String taskId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		int count = countByTaskId(taskId);
		List list = findByTaskId(taskId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTimeException();
		}
		else {
			return (com.liferay.portlet.project.model.ProjTime)list.get(0);
		}
	}

	public com.liferay.portlet.project.model.ProjTime[] findByTaskId_PrevAndNext(
		String timeId, String taskId, OrderByComparator obc)
		throws NoSuchTimeException, SystemException {
		com.liferay.portlet.project.model.ProjTime projTime = findByPrimaryKey(timeId);
		int count = countByTaskId(taskId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("taskId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, taskId);

			com.liferay.portlet.project.model.ProjTime[] array = new com.liferay.portlet.project.model.ProjTime[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ProjTimeHBM projTimeHBM = (ProjTimeHBM)sr.get(0);

					if (projTimeHBM == null) {
						break;
					}

					com.liferay.portlet.project.model.ProjTime curProjTime = ProjTimeHBMUtil.model(projTimeHBM);
					int value = obc.compare(projTime, curProjTime);

					if (value == 0) {
						if (!projTime.equals(curProjTime)) {
							break;
						}

						array[1] = curProjTime;

						if (sr.previous()) {
							array[0] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ProjTimeHBMUtil.model((ProjTimeHBM)sr.get(
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				list.add(ProjTimeHBMUtil.model(projTimeHBM));
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				ProjTimePool.remove((String)projTimeHBM.getPrimaryKey());
				session.delete(projTimeHBM);
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				ProjTimePool.remove((String)projTimeHBM.getPrimaryKey());
				session.delete(projTimeHBM);
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

	public void removeByProjectId(String projectId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				ProjTimePool.remove((String)projTimeHBM.getPrimaryKey());
				session.delete(projTimeHBM);
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

	public void removeByTaskId(String taskId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("taskId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, taskId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ProjTimeHBM projTimeHBM = (ProjTimeHBM)itr.next();
				ProjTimePool.remove((String)projTimeHBM.getPrimaryKey());
				session.delete(projTimeHBM);
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
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
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
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

	public int countByProjectId(String projectId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("projectId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, projectId);

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

	public int countByTaskId(String taskId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ProjTime IN CLASS com.liferay.portlet.project.service.persistence.ProjTimeHBM WHERE ");
			query.append("taskId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, taskId);

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

	private static final Log _log = LogFactory.getLog(ProjTimePersistence.class);
}