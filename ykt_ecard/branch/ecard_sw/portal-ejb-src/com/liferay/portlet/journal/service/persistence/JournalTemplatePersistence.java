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

import com.liferay.portlet.journal.NoSuchTemplateException;

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
 * <a href="JournalTemplatePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class JournalTemplatePersistence extends BasePersistence {
	public com.liferay.portlet.journal.model.JournalTemplate create(
		String templateId) {
		return new com.liferay.portlet.journal.model.JournalTemplate(templateId);
	}

	public com.liferay.portlet.journal.model.JournalTemplate remove(
		String templateId) throws NoSuchTemplateException, SystemException {
		Session session = null;

		try {
			session = openSession();

			JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)session.get(JournalTemplateHBM.class,
					templateId);

			if (journalTemplateHBM == null) {
				_log.warn("No JournalTemplate exists with the primary key of " +
					templateId.toString());
				throw new NoSuchTemplateException(templateId.toString());
			}

			com.liferay.portlet.journal.model.JournalTemplate journalTemplate = JournalTemplateHBMUtil.model(journalTemplateHBM);
			session.delete(journalTemplateHBM);
			session.flush();
			JournalTemplatePool.remove(templateId);

			return journalTemplate;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate update(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate)
		throws SystemException {
		Session session = null;

		try {
			if (journalTemplate.isNew() || journalTemplate.isModified()) {
				session = openSession();

				if (journalTemplate.isNew()) {
					JournalTemplateHBM journalTemplateHBM = new JournalTemplateHBM(journalTemplate.getTemplateId(),
							journalTemplate.getPortletId(),
							journalTemplate.getGroupId(),
							journalTemplate.getCompanyId(),
							journalTemplate.getUserId(),
							journalTemplate.getUserName(),
							journalTemplate.getCreateDate(),
							journalTemplate.getModifiedDate(),
							journalTemplate.getStructureId(),
							journalTemplate.getName(),
							journalTemplate.getDescription(),
							journalTemplate.getXsl(),
							journalTemplate.getSmallImage(),
							journalTemplate.getSmallImageURL());
					session.save(journalTemplateHBM);
					session.flush();
				}
				else {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)session.get(JournalTemplateHBM.class,
							journalTemplate.getPrimaryKey());

					if (journalTemplateHBM != null) {
						journalTemplateHBM.setPortletId(journalTemplate.getPortletId());
						journalTemplateHBM.setGroupId(journalTemplate.getGroupId());
						journalTemplateHBM.setCompanyId(journalTemplate.getCompanyId());
						journalTemplateHBM.setUserId(journalTemplate.getUserId());
						journalTemplateHBM.setUserName(journalTemplate.getUserName());
						journalTemplateHBM.setCreateDate(journalTemplate.getCreateDate());
						journalTemplateHBM.setModifiedDate(journalTemplate.getModifiedDate());
						journalTemplateHBM.setStructureId(journalTemplate.getStructureId());
						journalTemplateHBM.setName(journalTemplate.getName());
						journalTemplateHBM.setDescription(journalTemplate.getDescription());
						journalTemplateHBM.setXsl(journalTemplate.getXsl());
						journalTemplateHBM.setSmallImage(journalTemplate.getSmallImage());
						journalTemplateHBM.setSmallImageURL(journalTemplate.getSmallImageURL());
						session.flush();
					}
					else {
						journalTemplateHBM = new JournalTemplateHBM(journalTemplate.getTemplateId(),
								journalTemplate.getPortletId(),
								journalTemplate.getGroupId(),
								journalTemplate.getCompanyId(),
								journalTemplate.getUserId(),
								journalTemplate.getUserName(),
								journalTemplate.getCreateDate(),
								journalTemplate.getModifiedDate(),
								journalTemplate.getStructureId(),
								journalTemplate.getName(),
								journalTemplate.getDescription(),
								journalTemplate.getXsl(),
								journalTemplate.getSmallImage(),
								journalTemplate.getSmallImageURL());
						session.save(journalTemplateHBM);
						session.flush();
					}
				}

				journalTemplate.setNew(false);
				journalTemplate.setModified(false);
				journalTemplate.protect();
				JournalTemplatePool.put(journalTemplate.getPrimaryKey(),
					journalTemplate);
			}

			return journalTemplate;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate findByPrimaryKey(
		String templateId) throws NoSuchTemplateException, SystemException {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = JournalTemplatePool.get(templateId);
		Session session = null;

		try {
			if (journalTemplate == null) {
				session = openSession();

				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)session.get(JournalTemplateHBM.class,
						templateId);

				if (journalTemplateHBM == null) {
					_log.warn(
						"No JournalTemplate exists with the primary key of " +
						templateId.toString());
					throw new NoSuchTemplateException(templateId.toString());
				}

				journalTemplate = JournalTemplateHBMUtil.model(journalTemplateHBM);
			}

			return journalTemplate;
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
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
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
					list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);
						list.add(JournalTemplateHBMUtil.model(
								journalTemplateHBM));

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

	public com.liferay.portlet.journal.model.JournalTemplate findByGroupId_First(
		String groupId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate findByGroupId_Last(
		String groupId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		int count = countByGroupId(groupId);
		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate[] findByGroupId_PrevAndNext(
		String templateId, String groupId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = findByPrimaryKey(templateId);
		int count = countByGroupId(groupId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			com.liferay.portlet.journal.model.JournalTemplate[] array = new com.liferay.portlet.journal.model.JournalTemplate[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);

					if (journalTemplateHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalTemplate curJournalTemplate =
						JournalTemplateHBMUtil.model(journalTemplateHBM);
					int value = obc.compare(journalTemplate, curJournalTemplate);

					if (value == 0) {
						if (!journalTemplate.equals(curJournalTemplate)) {
							break;
						}

						array[1] = curJournalTemplate;

						if (sr.previous()) {
							array[0] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
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
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
					list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);
						list.add(JournalTemplateHBMUtil.model(
								journalTemplateHBM));

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

	public com.liferay.portlet.journal.model.JournalTemplate findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate[] findByCompanyId_PrevAndNext(
		String templateId, String companyId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = findByPrimaryKey(templateId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.journal.model.JournalTemplate[] array = new com.liferay.portlet.journal.model.JournalTemplate[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);

					if (journalTemplateHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalTemplate curJournalTemplate =
						JournalTemplateHBMUtil.model(journalTemplateHBM);
					int value = obc.compare(journalTemplate, curJournalTemplate);

					if (value == 0) {
						if (!journalTemplate.equals(curJournalTemplate)) {
							break;
						}

						array[1] = curJournalTemplate;

						if (sr.previous()) {
							array[0] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
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

	public List findByStructureId(String structureId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
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

	public List findByStructureId(String structureId, int begin, int end)
		throws SystemException {
		return findByStructureId(structureId, begin, end, null);
	}

	public List findByStructureId(String structureId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
					list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);
						list.add(JournalTemplateHBMUtil.model(
								journalTemplateHBM));

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

	public com.liferay.portlet.journal.model.JournalTemplate findByStructureId_First(
		String structureId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		List list = findByStructureId(structureId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate findByStructureId_Last(
		String structureId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		int count = countByStructureId(structureId);
		List list = findByStructureId(structureId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate[] findByStructureId_PrevAndNext(
		String templateId, String structureId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = findByPrimaryKey(templateId);
		int count = countByStructureId(structureId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			com.liferay.portlet.journal.model.JournalTemplate[] array = new com.liferay.portlet.journal.model.JournalTemplate[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);

					if (journalTemplateHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalTemplate curJournalTemplate =
						JournalTemplateHBMUtil.model(journalTemplateHBM);
					int value = obc.compare(journalTemplate, curJournalTemplate);

					if (value == 0) {
						if (!journalTemplate.equals(curJournalTemplate)) {
							break;
						}

						array[1] = curJournalTemplate;

						if (sr.previous()) {
							array[0] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
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
				query.append("templateId ASC");
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
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
					list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);
						list.add(JournalTemplateHBMUtil.model(
								journalTemplateHBM));

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

	public com.liferay.portlet.journal.model.JournalTemplate findByP_G_C_First(
		String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		List list = findByP_G_C(portletId, groupId, companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate findByP_G_C_Last(
		String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		int count = countByP_G_C(portletId, groupId, companyId);
		List list = findByP_G_C(portletId, groupId, companyId, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate[] findByP_G_C_PrevAndNext(
		String templateId, String portletId, String groupId, String companyId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = findByPrimaryKey(templateId);
		int count = countByP_G_C(portletId, groupId, companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
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
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			com.liferay.portlet.journal.model.JournalTemplate[] array = new com.liferay.portlet.journal.model.JournalTemplate[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);

					if (journalTemplateHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalTemplate curJournalTemplate =
						JournalTemplateHBMUtil.model(journalTemplateHBM);
					int value = obc.compare(journalTemplate, curJournalTemplate);

					if (value == 0) {
						if (!journalTemplate.equals(curJournalTemplate)) {
							break;
						}

						array[1] = curJournalTemplate;

						if (sr.previous()) {
							array[0] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
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

	public List findByP_G_S(String portletId, String groupId, String structureId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("structureId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, structureId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
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

	public List findByP_G_S(String portletId, String groupId,
		String structureId, int begin, int end) throws SystemException {
		return findByP_G_S(portletId, groupId, structureId, begin, end, null);
	}

	public List findByP_G_S(String portletId, String groupId,
		String structureId, int begin, int end, OrderByComparator obc)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("structureId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, structureId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
					list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);
						list.add(JournalTemplateHBMUtil.model(
								journalTemplateHBM));

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

	public com.liferay.portlet.journal.model.JournalTemplate findByP_G_S_First(
		String portletId, String groupId, String structureId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		List list = findByP_G_S(portletId, groupId, structureId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate findByP_G_S_Last(
		String portletId, String groupId, String structureId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		int count = countByP_G_S(portletId, groupId, structureId);
		List list = findByP_G_S(portletId, groupId, structureId, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchTemplateException();
		}
		else {
			return (com.liferay.portlet.journal.model.JournalTemplate)list.get(0);
		}
	}

	public com.liferay.portlet.journal.model.JournalTemplate[] findByP_G_S_PrevAndNext(
		String templateId, String portletId, String groupId,
		String structureId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate = findByPrimaryKey(templateId);
		int count = countByP_G_S(portletId, groupId, structureId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("structureId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, structureId);

			com.liferay.portlet.journal.model.JournalTemplate[] array = new com.liferay.portlet.journal.model.JournalTemplate[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)sr.get(0);

					if (journalTemplateHBM == null) {
						break;
					}

					com.liferay.portlet.journal.model.JournalTemplate curJournalTemplate =
						JournalTemplateHBMUtil.model(journalTemplateHBM);
					int value = obc.compare(journalTemplate, curJournalTemplate);

					if (value == 0) {
						if (!journalTemplate.equals(curJournalTemplate)) {
							break;
						}

						array[1] = curJournalTemplate;

						if (sr.previous()) {
							array[0] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = JournalTemplateHBMUtil.model((JournalTemplateHBM)sr.get(
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				list.add(JournalTemplateHBMUtil.model(journalTemplateHBM));
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("groupId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, groupId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				JournalTemplatePool.remove((String)journalTemplateHBM.getPrimaryKey());
				session.delete(journalTemplateHBM);
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				JournalTemplatePool.remove((String)journalTemplateHBM.getPrimaryKey());
				session.delete(journalTemplateHBM);
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

	public void removeByStructureId(String structureId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				JournalTemplatePool.remove((String)journalTemplateHBM.getPrimaryKey());
				session.delete(journalTemplateHBM);
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				JournalTemplatePool.remove((String)journalTemplateHBM.getPrimaryKey());
				session.delete(journalTemplateHBM);
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

	public void removeByP_G_S(String portletId, String groupId,
		String structureId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("structureId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("templateId ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, structureId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				JournalTemplateHBM journalTemplateHBM = (JournalTemplateHBM)itr.next();
				JournalTemplatePool.remove((String)journalTemplateHBM.getPrimaryKey());
				session.delete(journalTemplateHBM);
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
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

	public int countByStructureId(String structureId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("structureId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, structureId);

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
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
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

	public int countByP_G_S(String portletId, String groupId, String structureId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM JournalTemplate IN CLASS com.liferay.portlet.journal.service.persistence.JournalTemplateHBM WHERE ");
			query.append("portletId = ?");
			query.append(" AND ");
			query.append("groupId = ?");
			query.append(" AND ");
			query.append("structureId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, portletId);
			q.setString(queryPos++, groupId);
			q.setString(queryPos++, structureId);

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

	private static final Log _log = LogFactory.getLog(JournalTemplatePersistence.class);
}