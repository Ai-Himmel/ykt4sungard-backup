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

import com.liferay.portlet.calendar.NoSuchEventException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="CalEventPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class CalEventPersistence extends BasePersistence {
	public com.liferay.portlet.calendar.model.CalEvent create(String eventId) {
		return new com.liferay.portlet.calendar.model.CalEvent(eventId);
	}

	public com.liferay.portlet.calendar.model.CalEvent remove(String eventId)
		throws NoSuchEventException, SystemException {
		Session session = null;

		try {
			session = openSession();

			CalEventHBM calEventHBM = (CalEventHBM)session.get(CalEventHBM.class,
					eventId);

			if (calEventHBM == null) {
				_log.warn("No CalEvent exists with the primary key of " +
					eventId.toString());
				throw new NoSuchEventException(eventId.toString());
			}

			com.liferay.portlet.calendar.model.CalEvent calEvent = CalEventHBMUtil.model(calEventHBM);
			session.delete(calEventHBM);
			session.flush();
			CalEventPool.remove(eventId);

			return calEvent;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent update(
		com.liferay.portlet.calendar.model.CalEvent calEvent)
		throws SystemException {
		Session session = null;

		try {
			if (calEvent.isNew() || calEvent.isModified()) {
				session = openSession();

				if (calEvent.isNew()) {
					CalEventHBM calEventHBM = new CalEventHBM(calEvent.getEventId(),
							calEvent.getGroupId(), calEvent.getCompanyId(),
							calEvent.getUserId(), calEvent.getUserName(),
							calEvent.getCreateDate(),
							calEvent.getModifiedDate(), calEvent.getTitle(),
							calEvent.getDescription(), calEvent.getStartDate(),
							calEvent.getEndDate(), calEvent.getDurationHour(),
							calEvent.getDurationMinute(), calEvent.getAllDay(),
							calEvent.getTimeZoneSensitive(),
							calEvent.getType(), calEvent.getLocation(),
							calEvent.getStreet(), calEvent.getCity(),
							calEvent.getState(), calEvent.getZip(),
							calEvent.getPhone(), calEvent.getRepeating(),
							calEvent.getRecurrence(), calEvent.getRemindBy(),
							calEvent.getFirstReminder(),
							calEvent.getSecondReminder());
					session.save(calEventHBM);
					session.flush();
				}
				else {
					CalEventHBM calEventHBM = (CalEventHBM)session.get(CalEventHBM.class,
							calEvent.getPrimaryKey());

					if (calEventHBM != null) {
						calEventHBM.setGroupId(calEvent.getGroupId());
						calEventHBM.setCompanyId(calEvent.getCompanyId());
						calEventHBM.setUserId(calEvent.getUserId());
						calEventHBM.setUserName(calEvent.getUserName());
						calEventHBM.setCreateDate(calEvent.getCreateDate());
						calEventHBM.setModifiedDate(calEvent.getModifiedDate());
						calEventHBM.setTitle(calEvent.getTitle());
						calEventHBM.setDescription(calEvent.getDescription());
						calEventHBM.setStartDate(calEvent.getStartDate());
						calEventHBM.setEndDate(calEvent.getEndDate());
						calEventHBM.setDurationHour(calEvent.getDurationHour());
						calEventHBM.setDurationMinute(calEvent.getDurationMinute());
						calEventHBM.setAllDay(calEvent.getAllDay());
						calEventHBM.setTimeZoneSensitive(calEvent.getTimeZoneSensitive());
						calEventHBM.setType(calEvent.getType());
						calEventHBM.setLocation(calEvent.getLocation());
						calEventHBM.setStreet(calEvent.getStreet());
						calEventHBM.setCity(calEvent.getCity());
						calEventHBM.setState(calEvent.getState());
						calEventHBM.setZip(calEvent.getZip());
						calEventHBM.setPhone(calEvent.getPhone());
						calEventHBM.setRepeating(calEvent.getRepeating());
						calEventHBM.setRecurrence(calEvent.getRecurrence());
						calEventHBM.setRemindBy(calEvent.getRemindBy());
						calEventHBM.setFirstReminder(calEvent.getFirstReminder());
						calEventHBM.setSecondReminder(calEvent.getSecondReminder());
						session.flush();
					}
					else {
						calEventHBM = new CalEventHBM(calEvent.getEventId(),
								calEvent.getGroupId(), calEvent.getCompanyId(),
								calEvent.getUserId(), calEvent.getUserName(),
								calEvent.getCreateDate(),
								calEvent.getModifiedDate(),
								calEvent.getTitle(), calEvent.getDescription(),
								calEvent.getStartDate(), calEvent.getEndDate(),
								calEvent.getDurationHour(),
								calEvent.getDurationMinute(),
								calEvent.getAllDay(),
								calEvent.getTimeZoneSensitive(),
								calEvent.getType(), calEvent.getLocation(),
								calEvent.getStreet(), calEvent.getCity(),
								calEvent.getState(), calEvent.getZip(),
								calEvent.getPhone(), calEvent.getRepeating(),
								calEvent.getRecurrence(),
								calEvent.getRemindBy(),
								calEvent.getFirstReminder(),
								calEvent.getSecondReminder());
						session.save(calEventHBM);
						session.flush();
					}
				}

				calEvent.setNew(false);
				calEvent.setModified(false);
				calEvent.protect();
				CalEventPool.put(calEvent.getPrimaryKey(), calEvent);
			}

			return calEvent;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByPrimaryKey(
		String eventId) throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = CalEventPool.get(eventId);
		Session session = null;

		try {
			if (calEvent == null) {
				session = openSession();

				CalEventHBM calEventHBM = (CalEventHBM)session.get(CalEventHBM.class,
						eventId);

				if (calEventHBM == null) {
					_log.warn("No CalEvent exists with the primary key of " +
						eventId.toString());
					throw new NoSuchEventException(eventId.toString());
				}

				calEvent = CalEventHBMUtil.model(calEventHBM);
			}

			return calEvent;
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
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
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
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByGroupId_PrevAndNext(
		String eventId, String groupId, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public List findByC_T(String companyId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByC_T(String companyId, String type, int begin, int end)
		throws SystemException {
		return findByC_T(companyId, type, begin, end, null);
	}

	public List findByC_T(String companyId, String type, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByC_T_First(
		String companyId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByC_T(companyId, type, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByC_T_Last(
		String companyId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByC_T(companyId, type);
		List list = findByC_T(companyId, type, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByC_T_PrevAndNext(
		String eventId, String companyId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByC_T(companyId, type);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public List findByC_U_T(String companyId, String userId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByC_U_T(String companyId, String userId, String type,
		int begin, int end) throws SystemException {
		return findByC_U_T(companyId, userId, type, begin, end, null);
	}

	public List findByC_U_T(String companyId, String userId, String type,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByC_U_T_First(
		String companyId, String userId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByC_U_T(companyId, userId, type, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByC_U_T_Last(
		String companyId, String userId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByC_U_T(companyId, userId, type);
		List list = findByC_U_T(companyId, userId, type, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByC_U_T_PrevAndNext(
		String eventId, String companyId, String userId, String type,
		OrderByComparator obc) throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByC_U_T(companyId, userId, type);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public com.liferay.portlet.calendar.model.CalEvent findByC_U_D_T(
		String companyId, String userId, String description, String type)
		throws NoSuchEventException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("description = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, description);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchEventException();
			}

			CalEventHBM calEventHBM = (CalEventHBM)itr.next();

			return CalEventHBMUtil.model(calEventHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByG_U(String groupId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByG_U(String groupId, String userId, int begin, int end)
		throws SystemException {
		return findByG_U(groupId, userId, begin, end, null);
	}

	public List findByG_U(String groupId, String userId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByG_U_First(
		String groupId, String userId, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByG_U(groupId, userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByG_U_Last(
		String groupId, String userId, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByG_U(groupId, userId);
		List list = findByG_U(groupId, userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByG_U_PrevAndNext(
		String eventId, String groupId, String userId, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByG_U(groupId, userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public List findByG_T(String groupId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByG_T(String groupId, String type, int begin, int end)
		throws SystemException {
		return findByG_T(groupId, type, begin, end, null);
	}

	public List findByG_T(String groupId, String type, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, type);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByG_T_First(
		String groupId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByG_T(groupId, type, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByG_T_Last(
		String groupId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByG_T(groupId, type);
		List list = findByG_T(groupId, type, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByG_T_PrevAndNext(
		String eventId, String groupId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByG_T(groupId, type);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, type);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public List findByG_U_T(String groupId, String userId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByG_U_T(String groupId, String userId, String type,
		int begin, int end) throws SystemException {
		return findByG_U_T(groupId, userId, type, begin, end, null);
	}

	public List findByG_U_T(String groupId, String userId, String type,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByG_U_T_First(
		String groupId, String userId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByG_U_T(groupId, userId, type, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByG_U_T_Last(
		String groupId, String userId, String type, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByG_U_T(groupId, userId, type);
		List list = findByG_U_T(groupId, userId, type, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByG_U_T_PrevAndNext(
		String eventId, String groupId, String userId, String type,
		OrderByComparator obc) throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByG_U_T(groupId, userId, type);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public List findByG_C_R(String groupId, String companyId, boolean repeating)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, repeating);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByG_C_R(String groupId, String companyId,
		boolean repeating, int begin, int end) throws SystemException {
		return findByG_C_R(groupId, companyId, repeating, begin, end, null);
	}

	public List findByG_C_R(String groupId, String companyId,
		boolean repeating, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, repeating);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByG_C_R_First(
		String groupId, String companyId, boolean repeating,
		OrderByComparator obc) throws NoSuchEventException, SystemException {
		List list = findByG_C_R(groupId, companyId, repeating, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByG_C_R_Last(
		String groupId, String companyId, boolean repeating,
		OrderByComparator obc) throws NoSuchEventException, SystemException {
		int count = countByG_C_R(groupId, companyId, repeating);
		List list = findByG_C_R(groupId, companyId, repeating, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByG_C_R_PrevAndNext(
		String eventId, String groupId, String companyId, boolean repeating,
		OrderByComparator obc) throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByG_C_R(groupId, companyId, repeating);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, repeating);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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

	public List findByG_U_R(String groupId, String userId, boolean repeating)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, repeating);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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

	public List findByG_U_R(String groupId, String userId, boolean repeating,
		int begin, int end) throws SystemException {
		return findByG_U_R(groupId, userId, repeating, begin, end, null);
	}

	public List findByG_U_R(String groupId, String userId, boolean repeating,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, repeating);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					CalEventHBM calEventHBM = (CalEventHBM)itr.next();
					list.add(CalEventHBMUtil.model(calEventHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);
						list.add(CalEventHBMUtil.model(calEventHBM));

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

	public com.liferay.portlet.calendar.model.CalEvent findByG_U_R_First(
		String groupId, String userId, boolean repeating, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		List list = findByG_U_R(groupId, userId, repeating, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent findByG_U_R_Last(
		String groupId, String userId, boolean repeating, OrderByComparator obc)
		throws NoSuchEventException, SystemException {
		int count = countByG_U_R(groupId, userId, repeating);
		List list = findByG_U_R(groupId, userId, repeating, count - 1, count,
				obc);

		if (list.size() == 0) {
			throw new NoSuchEventException();
		}
		else {
			return (com.liferay.portlet.calendar.model.CalEvent)list.get(0);
		}
	}

	public com.liferay.portlet.calendar.model.CalEvent[] findByG_U_R_PrevAndNext(
		String eventId, String groupId, String userId, boolean repeating,
		OrderByComparator obc) throws NoSuchEventException, SystemException {
		com.liferay.portlet.calendar.model.CalEvent calEvent = findByPrimaryKey(eventId);
		int count = countByG_U_R(groupId, userId, repeating);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("startDate ASC").append(", ");
				query.append("title ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, repeating);

			com.liferay.portlet.calendar.model.CalEvent[] array = new com.liferay.portlet.calendar.model.CalEvent[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					CalEventHBM calEventHBM = (CalEventHBM)sr.get(0);

					if (calEventHBM == null) {
						break;
					}

					com.liferay.portlet.calendar.model.CalEvent curCalEvent = CalEventHBMUtil.model(calEventHBM);
					int value = obc.compare(calEvent, curCalEvent);

					if (value == 0) {
						if (!calEvent.equals(curCalEvent)) {
							break;
						}

						array[1] = curCalEvent;

						if (sr.previous()) {
							array[0] = CalEventHBMUtil.model((CalEventHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = CalEventHBMUtil.model((CalEventHBM)sr.get(
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
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				list.add(CalEventHBMUtil.model(calEventHBM));
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
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByC_T(String companyId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByC_U_T(String companyId, String userId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByC_U_D_T(String companyId, String userId,
		String description, String type)
		throws NoSuchEventException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("description = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, description);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchEventException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByG_U(String groupId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByG_T(String groupId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByG_U_T(String groupId, String userId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByG_C_R(String groupId, String companyId,
		boolean repeating) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, repeating);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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

	public void removeByG_U_R(String groupId, String userId, boolean repeating)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("startDate ASC").append(", ");
			query.append("title ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, repeating);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				CalEventHBM calEventHBM = (CalEventHBM)itr.next();
				CalEventPool.remove((String)calEventHBM.getPrimaryKey());
				session.delete(calEventHBM);
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
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
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

	public int countByC_T(String companyId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, type);

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

	public int countByC_U_T(String companyId, String userId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

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

	public int countByC_U_D_T(String companyId, String userId,
		String description, String type) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("description = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, description);
			q.setString(queryPos++, type);

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

	public int countByG_U(String groupId, String userId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
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

	public int countByG_T(String groupId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, type);

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

	public int countByG_U_T(String groupId, String userId, String type)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("type_ = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, type);

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

	public int countByG_C_R(String groupId, String companyId, boolean repeating)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);
			q.setBoolean(queryPos++, repeating);

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

	public int countByG_U_R(String groupId, String userId, boolean repeating)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM CalEvent IN CLASS com.liferay.portlet.calendar.service.persistence.CalEventHBM WHERE ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("repeating = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, userId);
			q.setBoolean(queryPos++, repeating);

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

	private static final Log _log = LogFactory.getLog(CalEventPersistence.class);
}