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

package com.liferay.portlet.calendar.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.calendar.NoSuchTaskException;

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
 * <a href="CalTaskPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalTaskPersistence extends BasePersistence {
	public com.liferay.portlet.calendar.model.CalTask create(String taskId) {
		return new com.liferay.portlet.calendar.model.CalTask(taskId);
	}

	public com.liferay.portlet.calendar.model.CalTask remove(String taskId)
		throws NoSuchTaskException, SystemException {
		Session session = null;

		try {
			session = openSession();

			CalTaskHBM calTaskHBM = (CalTaskHBM)session.get(CalTaskHBM.class,
					taskId);

			if (calTaskHBM == null) {
				_log.warn("No CalTask exists with the primary key of " +
					taskId.toString());
				throw new NoSuchTaskException(taskId.toString());
			}

			com.liferay.portlet.calendar.model.CalTask calTask = CalTaskHBMUtil.model(calTaskHBM);
			session.delete(calTaskHBM);
			session.flush();
			CalTaskPool.remove(taskId);

			return calTask;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask update(
		com.liferay.portlet.calendar.model.CalTask calTask)
		throws SystemException {
		Session session = null;

		try {
			if (calTask.isNew() || calTask.isModified()) {
				session = openSession();

				if (calTask.isNew()) {
					CalTaskHBM calTaskHBM = new CalTaskHBM(calTask.getTaskId(),
							calTask.getCompanyId(), calTask.getUserId(),
							calTask.getCreateDate(), calTask.getModifiedDate(),
							calTask.getTitle(), calTask.getDescription(),
							calTask.getNoDueDate(), calTask.getDueDate(),
							calTask.getPriority(), calTask.getStatus());
					session.save(calTaskHBM);
					session.flush();
				}
				else {
					CalTaskHBM calTaskHBM = (CalTaskHBM)session.get(CalTaskHBM.class,
							calTask.getPrimaryKey());

					if (calTaskHBM != null) {
						calTaskHBM.setCompanyId(calTask.getCompanyId());
						calTaskHBM.setUserId(calTask.getUserId());
						calTaskHBM.setCreateDate(calTask.getCreateDate());
						calTaskHBM.setModifiedDate(calTask.getModifiedDate());
						calTaskHBM.setTitle(calTask.getTitle());
						calTaskHBM.setDescription(calTask.getDescription());
						calTaskHBM.setNoDueDate(calTask.getNoDueDate());
						calTaskHBM.setDueDate(calTask.getDueDate());
						calTaskHBM.setPriority(calTask.getPriority());
						calTaskHBM.setStatus(calTask.getStatus());
						session.flush();
					}
					else {
						calTaskHBM = new CalTaskHBM(calTask.getTaskId(),
								calTask.getCompanyId(), calTask.getUserId(),
								calTask.getCreateDate(),
								calTask.getModifiedDate(), calTask.getTitle(),
								calTask.getDescription(),
								calTask.getNoDueDate(), calTask.getDueDate(),
								calTask.getPriority(), calTask.getStatus());
						session.save(calTaskHBM);
						session.flush();
					}
				}

				calTask.setNew(false);
				calTask.setModified(false);
				calTask.protect();
				CalTaskPool.put(calTask.getPrimaryKey(), calTask);
			}

			return calTask;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask findByPrimaryKey(
		String taskId) throws NoSuchTaskException, SystemException {
		com.liferay.portlet.calendar.model.CalTask calTask = CalTaskPool.get(taskId);
		Session session = null;

		try {
			if (calTask == null) {
				session = openSession();

				CalTaskHBM calTaskHBM = (CalTaskHBM)session.get(CalTaskHBM.class,
						taskId);

				if (calTaskHBM == null) {
					_log.warn("No CalTask exists with the primary key of " +
						taskId.toString());
					throw new NoSuchTaskException(taskId.toString());
				}

				calTask = CalTaskHBMUtil.model(calTaskHBM);
			}

			return calTask;
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
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				list.add(CalTaskHBMUtil.model(calTaskHBM));
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
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
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
					CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
					list.add(CalTaskHBMUtil.model(calTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);
						list.add(CalTaskHBMUtil.model(calTaskHBM));

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

	public com.liferay.portlet.calendar.model.CalTask findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask[] findByUserId_PrevAndNext(
		String taskId, String userId, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.calendar.model.CalTask calTask = findByPrimaryKey(taskId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.calendar.model.CalTask[] array = new com.liferay.portlet.calendar.model.CalTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);

					if (calTaskHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalTask curCalTask = CalTaskHBMUtil.model(calTaskHBM);
					int value = obc.compare(calTask, curCalTask);

					if (value == 0) {
						if (!calTask.equals(curCalTask)) {
							break;
						}

						array[1] = curCalTask;

						if (sr.previous()) {
							array[0] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
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

	public List findByU_P(String userId, int priority)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				list.add(CalTaskHBMUtil.model(calTaskHBM));
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

	public List findByU_P(String userId, int priority, int begin, int end)
		throws SystemException {
		return findByU_P(userId, priority, begin, end, null);
	}

	public List findByU_P(String userId, int priority, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
					list.add(CalTaskHBMUtil.model(calTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);
						list.add(CalTaskHBMUtil.model(calTaskHBM));

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

	public com.liferay.portlet.calendar.model.CalTask findByU_P_First(
		String userId, int priority, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByU_P(userId, priority, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask findByU_P_Last(
		String userId, int priority, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByU_P(userId, priority);
		List list = findByU_P(userId, priority, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask[] findByU_P_PrevAndNext(
		String taskId, String userId, int priority, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.calendar.model.CalTask calTask = findByPrimaryKey(taskId);
		int count = countByU_P(userId, priority);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);

			com.liferay.portlet.calendar.model.CalTask[] array = new com.liferay.portlet.calendar.model.CalTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);

					if (calTaskHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalTask curCalTask = CalTaskHBMUtil.model(calTaskHBM);
					int value = obc.compare(calTask, curCalTask);

					if (value == 0) {
						if (!calTask.equals(curCalTask)) {
							break;
						}

						array[1] = curCalTask;

						if (sr.previous()) {
							array[0] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
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

	public List findByU_S(String userId, int status) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				list.add(CalTaskHBMUtil.model(calTaskHBM));
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

	public List findByU_S(String userId, int status, int begin, int end)
		throws SystemException {
		return findByU_S(userId, status, begin, end, null);
	}

	public List findByU_S(String userId, int status, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
					list.add(CalTaskHBMUtil.model(calTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);
						list.add(CalTaskHBMUtil.model(calTaskHBM));

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

	public com.liferay.portlet.calendar.model.CalTask findByU_S_First(
		String userId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByU_S(userId, status, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask findByU_S_Last(
		String userId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByU_S(userId, status);
		List list = findByU_S(userId, status, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask[] findByU_S_PrevAndNext(
		String taskId, String userId, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		com.liferay.portlet.calendar.model.CalTask calTask = findByPrimaryKey(taskId);
		int count = countByU_S(userId, status);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			com.liferay.portlet.calendar.model.CalTask[] array = new com.liferay.portlet.calendar.model.CalTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);

					if (calTaskHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalTask curCalTask = CalTaskHBMUtil.model(calTaskHBM);
					int value = obc.compare(calTask, curCalTask);

					if (value == 0) {
						if (!calTask.equals(curCalTask)) {
							break;
						}

						array[1] = curCalTask;

						if (sr.previous()) {
							array[0] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
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

	public List findByU_P_S(String userId, int priority, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				list.add(CalTaskHBMUtil.model(calTaskHBM));
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

	public List findByU_P_S(String userId, int priority, int status, int begin,
		int end) throws SystemException {
		return findByU_P_S(userId, priority, status, begin, end, null);
	}

	public List findByU_P_S(String userId, int priority, int status, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);
			q.setInteger(queryPos++, status);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
					list.add(CalTaskHBMUtil.model(calTaskHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);
						list.add(CalTaskHBMUtil.model(calTaskHBM));

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

	public com.liferay.portlet.calendar.model.CalTask findByU_P_S_First(
		String userId, int priority, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		List list = findByU_P_S(userId, priority, status, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask findByU_P_S_Last(
		String userId, int priority, int status, OrderByComparator obc)
		throws NoSuchTaskException, SystemException {
		int count = countByU_P_S(userId, priority, status);
		List list = findByU_P_S(userId, priority, status, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTaskException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalTask)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalTask[] findByU_P_S_PrevAndNext(
		String taskId, String userId, int priority, int status,
		OrderByComparator obc) throws NoSuchTaskException, SystemException {
		com.liferay.portlet.calendar.model.CalTask calTask = findByPrimaryKey(taskId);
		int count = countByU_P_S(userId, priority, status);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);
			q.setInteger(queryPos++, status);

			com.liferay.portlet.calendar.model.CalTask[] array = new com.liferay.portlet.calendar.model.CalTask[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalTaskHBM calTaskHBM = (CalTaskHBM)sr.get(0);

					if (calTaskHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalTask curCalTask = CalTaskHBMUtil.model(calTaskHBM);
					int value = obc.compare(calTask, curCalTask);

					if (value == 0) {
						if (!calTask.equals(curCalTask)) {
							break;
						}

						array[1] = curCalTask;

						if (sr.previous()) {
							array[0] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalTaskHBMUtil.model((CalTaskHBM)sr.get(
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
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				list.add(CalTaskHBMUtil.model(calTaskHBM));
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
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				CalTaskPool.remove((String)calTaskHBM.getPrimaryKey());
				session.delete(calTaskHBM);
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

	public void removeByU_P(String userId, int priority)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				CalTaskPool.remove((String)calTaskHBM.getPrimaryKey());
				session.delete(calTaskHBM);
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

	public void removeByU_S(String userId, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				CalTaskPool.remove((String)calTaskHBM.getPrimaryKey());
				session.delete(calTaskHBM);
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

	public void removeByU_P_S(String userId, int priority, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);
			q.setInteger(queryPos++, status);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalTaskHBM calTaskHBM = (CalTaskHBM)itr.next();
				CalTaskPool.remove((String)calTaskHBM.getPrimaryKey());
				session.delete(calTaskHBM);
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
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
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

	public int countByU_P(String userId, int priority)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);

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

	public int countByU_S(String userId, int status) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, status);

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

	public int countByU_P_S(String userId, int priority, int status)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalTask IN CLASS com.liferay.portlet.calendar.service.persistence.CalTaskHBM WHERE ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("priority = ?");
			query.append(" AND ");
			query.append("status = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);
			q.setInteger(queryPos++, priority);
			q.setInteger(queryPos++, status);

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

	private static final Log _log = LogFactory.getLog(CalTaskPersistence.class);
}