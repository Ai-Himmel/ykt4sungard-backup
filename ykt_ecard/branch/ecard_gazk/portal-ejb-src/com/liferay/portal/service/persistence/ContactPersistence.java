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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchContactException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

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
 * <a href="ContactPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ContactPersistence extends BasePersistence {
	public com.liferay.portal.model.Contact create(String contactId) {
		return new com.liferay.portal.model.Contact(contactId);
	}

	public com.liferay.portal.model.Contact remove(String contactId)
		throws NoSuchContactException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ContactHBM contactHBM = (ContactHBM)session.get(ContactHBM.class,
					contactId);

			if (contactHBM == null) {
				_log.warn("No Contact exists with the primary key of " +
					contactId.toString());
				throw new NoSuchContactException(contactId.toString());
			}

			com.liferay.portal.model.Contact contact = ContactHBMUtil.model(contactHBM);
			session.delete(contactHBM);
			session.flush();
			ContactPool.remove(contactId);

			return contact;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Contact update(
		com.liferay.portal.model.Contact contact) throws SystemException {
		Session session = null;

		try {
			if (contact.isNew() || contact.isModified()) {
				session = openSession();

				if (contact.isNew()) {
					ContactHBM contactHBM = new ContactHBM(contact.getContactId(),
							contact.getCompanyId(), contact.getUserId(),
							contact.getUserName(), contact.getCreateDate(),
							contact.getModifiedDate(),
							contact.getParentContactId(),
							contact.getFirstName(), contact.getMiddleName(),
							contact.getLastName(), contact.getNickName(),
							contact.getEmailAddress1(),
							contact.getEmailAddress2(), contact.getSmsId(),
							contact.getAimId(), contact.getIcqId(),
							contact.getMsnId(), contact.getSkypeId(),
							contact.getYmId(), contact.getWebsite(),
							contact.getMale(), contact.getBirthday(),
							contact.getTimeZoneId(),
							contact.getEmployeeNumber(), contact.getJobTitle(),
							contact.getJobClass(), contact.getHoursOfOperation());
					session.save(contactHBM);
					session.flush();
				}
				else {
					ContactHBM contactHBM = (ContactHBM)session.get(ContactHBM.class,
							contact.getPrimaryKey());

					if (contactHBM != null) {
						contactHBM.setCompanyId(contact.getCompanyId());
						contactHBM.setUserId(contact.getUserId());
						contactHBM.setUserName(contact.getUserName());
						contactHBM.setCreateDate(contact.getCreateDate());
						contactHBM.setModifiedDate(contact.getModifiedDate());
						contactHBM.setParentContactId(contact.getParentContactId());
						contactHBM.setFirstName(contact.getFirstName());
						contactHBM.setMiddleName(contact.getMiddleName());
						contactHBM.setLastName(contact.getLastName());
						contactHBM.setNickName(contact.getNickName());
						contactHBM.setEmailAddress1(contact.getEmailAddress1());
						contactHBM.setEmailAddress2(contact.getEmailAddress2());
						contactHBM.setSmsId(contact.getSmsId());
						contactHBM.setAimId(contact.getAimId());
						contactHBM.setIcqId(contact.getIcqId());
						contactHBM.setMsnId(contact.getMsnId());
						contactHBM.setSkypeId(contact.getSkypeId());
						contactHBM.setYmId(contact.getYmId());
						contactHBM.setWebsite(contact.getWebsite());
						contactHBM.setMale(contact.getMale());
						contactHBM.setBirthday(contact.getBirthday());
						contactHBM.setTimeZoneId(contact.getTimeZoneId());
						contactHBM.setEmployeeNumber(contact.getEmployeeNumber());
						contactHBM.setJobTitle(contact.getJobTitle());
						contactHBM.setJobClass(contact.getJobClass());
						contactHBM.setHoursOfOperation(contact.getHoursOfOperation());
						session.flush();
					}
					else {
						contactHBM = new ContactHBM(contact.getContactId(),
								contact.getCompanyId(), contact.getUserId(),
								contact.getUserName(), contact.getCreateDate(),
								contact.getModifiedDate(),
								contact.getParentContactId(),
								contact.getFirstName(),
								contact.getMiddleName(), contact.getLastName(),
								contact.getNickName(),
								contact.getEmailAddress1(),
								contact.getEmailAddress2(), contact.getSmsId(),
								contact.getAimId(), contact.getIcqId(),
								contact.getMsnId(), contact.getSkypeId(),
								contact.getYmId(), contact.getWebsite(),
								contact.getMale(), contact.getBirthday(),
								contact.getTimeZoneId(),
								contact.getEmployeeNumber(),
								contact.getJobTitle(), contact.getJobClass(),
								contact.getHoursOfOperation());
						session.save(contactHBM);
						session.flush();
					}
				}

				contact.setNew(false);
				contact.setModified(false);
				contact.protect();
				ContactPool.put(contact.getPrimaryKey(), contact);
			}

			return contact;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Contact findByPrimaryKey(String contactId)
		throws NoSuchContactException, SystemException {
		com.liferay.portal.model.Contact contact = ContactPool.get(contactId);
		Session session = null;

		try {
			if (contact == null) {
				session = openSession();

				ContactHBM contactHBM = (ContactHBM)session.get(ContactHBM.class,
						contactId);

				if (contactHBM == null) {
					_log.warn("No Contact exists with the primary key of " +
						contactId.toString());
					throw new NoSuchContactException(contactId.toString());
				}

				contact = ContactHBMUtil.model(contactHBM);
			}

			return contact;
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ContactHBM contactHBM = (ContactHBM)itr.next();
				list.add(ContactHBMUtil.model(contactHBM));
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
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
					ContactHBM contactHBM = (ContactHBM)itr.next();
					list.add(ContactHBMUtil.model(contactHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ContactHBM contactHBM = (ContactHBM)sr.get(0);
						list.add(ContactHBMUtil.model(contactHBM));

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

	public com.liferay.portal.model.Contact findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchContactException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchContactException();
		}
		else {
			return (com.liferay.portal.model.Contact)list.get(0);
		}
	}

	public com.liferay.portal.model.Contact findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchContactException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchContactException();
		}
		else {
			return (com.liferay.portal.model.Contact)list.get(0);
		}
	}

	public com.liferay.portal.model.Contact[] findByCompanyId_PrevAndNext(
		String contactId, String companyId, OrderByComparator obc)
		throws NoSuchContactException, SystemException {
		com.liferay.portal.model.Contact contact = findByPrimaryKey(contactId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portal.model.Contact[] array = new com.liferay.portal.model.Contact[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ContactHBM contactHBM = (ContactHBM)sr.get(0);

					if (contactHBM == null) {
						break;
					}

					com.liferay.portal.model.Contact curContact = ContactHBMUtil.model(contactHBM);
					int value = obc.compare(contact, curContact);

					if (value == 0) {
						if (!contact.equals(curContact)) {
							break;
						}

						array[1] = curContact;

						if (sr.previous()) {
							array[0] = ContactHBMUtil.model((ContactHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ContactHBMUtil.model((ContactHBM)sr.get(
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ContactHBM contactHBM = (ContactHBM)itr.next();
				list.add(ContactHBMUtil.model(contactHBM));
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
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
					ContactHBM contactHBM = (ContactHBM)itr.next();
					list.add(ContactHBMUtil.model(contactHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ContactHBM contactHBM = (ContactHBM)sr.get(0);
						list.add(ContactHBMUtil.model(contactHBM));

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

	public com.liferay.portal.model.Contact findByUserId_First(String userId,
		OrderByComparator obc) throws NoSuchContactException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchContactException();
		}
		else {
			return (com.liferay.portal.model.Contact)list.get(0);
		}
	}

	public com.liferay.portal.model.Contact findByUserId_Last(String userId,
		OrderByComparator obc) throws NoSuchContactException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchContactException();
		}
		else {
			return (com.liferay.portal.model.Contact)list.get(0);
		}
	}

	public com.liferay.portal.model.Contact[] findByUserId_PrevAndNext(
		String contactId, String userId, OrderByComparator obc)
		throws NoSuchContactException, SystemException {
		com.liferay.portal.model.Contact contact = findByPrimaryKey(contactId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portal.model.Contact[] array = new com.liferay.portal.model.Contact[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ContactHBM contactHBM = (ContactHBM)sr.get(0);

					if (contactHBM == null) {
						break;
					}

					com.liferay.portal.model.Contact curContact = ContactHBMUtil.model(contactHBM);
					int value = obc.compare(contact, curContact);

					if (value == 0) {
						if (!contact.equals(curContact)) {
							break;
						}

						array[1] = curContact;

						if (sr.previous()) {
							array[0] = ContactHBMUtil.model((ContactHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ContactHBMUtil.model((ContactHBM)sr.get(
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ContactHBM contactHBM = (ContactHBM)itr.next();
				list.add(ContactHBMUtil.model(contactHBM));
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ContactHBM contactHBM = (ContactHBM)itr.next();
				ContactPool.remove((String)contactHBM.getPrimaryKey());
				session.delete(contactHBM);
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ContactHBM contactHBM = (ContactHBM)itr.next();
				ContactPool.remove((String)contactHBM.getPrimaryKey());
				session.delete(contactHBM);
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
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
				"FROM Contact IN CLASS com.liferay.portal.service.persistence.ContactHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(ContactPersistence.class);
}