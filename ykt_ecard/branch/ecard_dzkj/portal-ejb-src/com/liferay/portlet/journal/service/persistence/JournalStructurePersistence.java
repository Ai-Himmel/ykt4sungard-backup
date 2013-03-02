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

package com.liferay.portlet.journal.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.journal.NoSuchStructureException;

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
 * <a href="JournalStructurePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalStructurePersistence extends BasePersistence {
	public com.liferay.portlet.journal.model.JournalStructure create(
		String structureId) {
		return new com.liferay.portlet.journal.model.JournalStructure(structureId);
	}

	public com.liferay.portlet.journal.model.JournalStructure remove(
		String structureId) throws NoSuchStructureException, SystemException {
		Session session = null;

		try {
			session = openSession();

			JournalStructureHBM journalStructureHBM = (JournalStructureHBM)session.get(JournalStructureHBM.class,
					structureId);

			if (journalStructureHBM == null) {
				_log.warn("No JournalStructure exists with the primary key of " +
					structureId.toString());
				throw new NoSuchStructureException(structureId.toString());
			}

			com.liferay.portlet.journal.model.JournalStructure journalStructure = JournalStructureHBMUtil.model(journalStructureHBM);
			session.delete(journalStructureHBM);
			session.flush();
			JournalStructurePool.remove(structureId);

			return journalStructure;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure update(
		com.liferay.portlet.journal.model.JournalStructure journalStructure)
		throws SystemException {
		Session session = null;

		try {
			if (journalStructure.isNew() || journalStructure.isModified()) {
				session = openSession();

				if (journalStructure.isNew()) {
					JournalStructureHBM journalStructureHBM = new JournalStructureHBM(journalStructure.getStructureId(),
							journalStructure.getPortletId(),
							journalStructure.getGroupId(),
							journalStructure.getCompanyId(),
							journalStructure.getUserId(),
							journalStructure.getUserName(),
							journalStructure.getCreateDate(),
							journalStructure.getModifiedDate(),
							journalStructure.getName(),
							journalStructure.getDescription(),
							journalStructure.getXsd());
					session.save(journalStructureHBM);
					session.flush();
				}
				else {
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)session.get(JournalStructureHBM.class,
							journalStructure.getPrimaryKey());

					if (journalStructureHBM != null) {
						journalStructureHBM.setPortletId(journalStructure.getPortletId());
						journalStructureHBM.setGroupId(journalStructure.getGroupId());
						journalStructureHBM.setCompanyId(journalStructure.getCompanyId());
						journalStructureHBM.setUserId(journalStructure.getUserId());
						journalStructureHBM.setUserName(journalStructure.getUserName());
						journalStructureHBM.setCreateDate(journalStructure.getCreateDate());
						journalStructureHBM.setModifiedDate(journalStructure.getModifiedDate());
						journalStructureHBM.setName(journalStructure.getName());
						journalStructureHBM.setDescription(journalStructure.getDescription());
						journalStructureHBM.setXsd(journalStructure.getXsd());
						session.flush();
					}
					else {
						journalStructureHBM = new JournalStructureHBM(journalStructure.getStructureId(),
								journalStructure.getPortletId(),
								journalStructure.getGroupId(),
								journalStructure.getCompanyId(),
								journalStructure.getUserId(),
								journalStructure.getUserName(),
								journalStructure.getCreateDate(),
								journalStructure.getModifiedDate(),
								journalStructure.getName(),
								journalStructure.getDescription(),
								journalStructure.getXsd());
						session.save(journalStructureHBM);
						session.flush();
					}
				}

				journalStructure.setNew(false);
				journalStructure.setModified(false);
				journalStructure.protect();
				JournalStructurePool.put(journalStructure.getPrimaryKey(),
					journalStructure);
			}

			return journalStructure;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure findByPrimaryKey(
		String structureId) throws NoSuchStructureException, SystemException {
		com.liferay.portlet.journal.model.JournalStructure journalStructure = JournalStructurePool.get(structureId);
		Session session = null;

		try {
			if (journalStructure == null) {
				session = openSession();

				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)session.get(JournalStructureHBM.class,
						structureId);

				if (journalStructureHBM == null) {
					_log.warn(
						"No JournalStructure exists with the primary key of " +
						structureId.toString());
					throw new NoSuchStructureException(structureId.toString());
				}

				journalStructure = JournalStructureHBMUtil.model(journalStructureHBM);
			}

			return journalStructure;
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				list.add(JournalStructureHBMUtil.model(journalStructureHBM));
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("structureId ASC");
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
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
					list.add(JournalStructureHBMUtil.model(journalStructureHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalStructureHBM journalStructureHBM = (JournalStructureHBM)sr.get(0);
						list.add(JournalStructureHBMUtil.model(
								journalStructureHBM));

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

	public com.liferay.portlet.journal.model.JournalStructure findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchStructureException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchStructureException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalStructure)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchStructureException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchStructureException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalStructure)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure[] findByGroupId_PrevAndNext(
		String structureId, String groupId, OrderByComparator obc)
		throws NoSuchStructureException, SystemException {
		com.liferay.portlet.journal.model.JournalStructure journalStructure = findByPrimaryKey(structureId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("structureId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.journal.model.JournalStructure[] array = new com.liferay.portlet.journal.model.JournalStructure[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)sr.get(0);

					if (journalStructureHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalStructure curJournalStructure =
						JournalStructureHBMUtil.model(journalStructureHBM);
					int value = obc.compare(journalStructure,
							curJournalStructure);

					if (value == 0) {
						if (!journalStructure.equals(curJournalStructure)) {
							break;
						}

						array[1] = curJournalStructure;

						if (sr.previous()) {
							array[0] = JournalStructureHBMUtil.model((JournalStructureHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalStructureHBMUtil.model((JournalStructureHBM)sr.get(
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				list.add(JournalStructureHBMUtil.model(journalStructureHBM));
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("structureId ASC");
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
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
					list.add(JournalStructureHBMUtil.model(journalStructureHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalStructureHBM journalStructureHBM = (JournalStructureHBM)sr.get(0);
						list.add(JournalStructureHBMUtil.model(
								journalStructureHBM));

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

	public com.liferay.portlet.journal.model.JournalStructure findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchStructureException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchStructureException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalStructure)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchStructureException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchStructureException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalStructure)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure[] findByCompanyId_PrevAndNext(
		String structureId, String companyId, OrderByComparator obc)
		throws NoSuchStructureException, SystemException {
		com.liferay.portlet.journal.model.JournalStructure journalStructure = findByPrimaryKey(structureId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("structureId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.journal.model.JournalStructure[] array = new com.liferay.portlet.journal.model.JournalStructure[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)sr.get(0);

					if (journalStructureHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalStructure curJournalStructure =
						JournalStructureHBMUtil.model(journalStructureHBM);
					int value = obc.compare(journalStructure,
							curJournalStructure);

					if (value == 0) {
						if (!journalStructure.equals(curJournalStructure)) {
							break;
						}

						array[1] = curJournalStructure;

						if (sr.previous()) {
							array[0] = JournalStructureHBMUtil.model((JournalStructureHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalStructureHBMUtil.model((JournalStructureHBM)sr.get(
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

	public List findByP_G_C(String portletId, String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				list.add(JournalStructureHBMUtil.model(journalStructureHBM));
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

	public List findByP_G_C(String portletId, String groupId, String companyId,
		int begin, int end) throws SystemException {
		return findByP_G_C(portletId, groupId, companyId, begin, end, null);
	}

	public List findByP_G_C(String portletId, String groupId, String companyId,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("structureId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
					list.add(JournalStructureHBMUtil.model(journalStructureHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalStructureHBM journalStructureHBM = (JournalStructureHBM)sr.get(0);
						list.add(JournalStructureHBMUtil.model(
								journalStructureHBM));

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

	public com.liferay.portlet.journal.model.JournalStructure findByP_G_C_First(
		String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchStructureException, SystemException {
		List list = findByP_G_C(portletId, groupId, companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchStructureException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalStructure)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure findByP_G_C_Last(
		String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchStructureException, SystemException {
		int count = countByP_G_C(portletId, groupId, companyId);
		List list = findByP_G_C(portletId, groupId, companyId, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchStructureException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalStructure)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalStructure[] findByP_G_C_PrevAndNext(
		String structureId, String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchStructureException, SystemException {
		com.liferay.portlet.journal.model.JournalStructure journalStructure = findByPrimaryKey(structureId);
		int count = countByP_G_C(portletId, groupId, companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("structureId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			com.liferay.portlet.journal.model.JournalStructure[] array = new com.liferay.portlet.journal.model.JournalStructure[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalStructureHBM journalStructureHBM = (JournalStructureHBM)sr.get(0);

					if (journalStructureHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalStructure curJournalStructure =
						JournalStructureHBMUtil.model(journalStructureHBM);
					int value = obc.compare(journalStructure,
							curJournalStructure);

					if (value == 0) {
						if (!journalStructure.equals(curJournalStructure)) {
							break;
						}

						array[1] = curJournalStructure;

						if (sr.previous()) {
							array[0] = JournalStructureHBMUtil.model((JournalStructureHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalStructureHBMUtil.model((JournalStructureHBM)sr.get(
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				list.add(JournalStructureHBMUtil.model(journalStructureHBM));
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				JournalStructurePool.remove((String)journalStructureHBM.getPrimaryKey());
				session.delete(journalStructureHBM);
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				JournalStructurePool.remove((String)journalStructureHBM.getPrimaryKey());
				session.delete(journalStructureHBM);
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

	public void removeByP_G_C(String portletId, String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("structureId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalStructureHBM journalStructureHBM = (JournalStructureHBM)itr.next();
				JournalStructurePool.remove((String)journalStructureHBM.getPrimaryKey());
				session.delete(journalStructureHBM);
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
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
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
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

	public int countByP_G_C(String portletId, String groupId, String companyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalStructure IN CLASS com.liferay.portlet.journal.service.persistence.JournalStructureHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
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

	private static final Log _log = LogFactory.getLog(JournalStructurePersistence.class);
}