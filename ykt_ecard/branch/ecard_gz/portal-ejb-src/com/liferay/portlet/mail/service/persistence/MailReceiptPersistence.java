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

package com.liferay.portlet.mail.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.mail.NoSuchReceiptException;

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
 * <a href="MailReceiptPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class MailReceiptPersistence extends BasePersistence {
	public com.liferay.portlet.mail.model.MailReceipt create(String receiptId) {
		return new com.liferay.portlet.mail.model.MailReceipt(receiptId);
	}

	public com.liferay.portlet.mail.model.MailReceipt remove(String receiptId)
		throws NoSuchReceiptException, SystemException {
		Session session = null;

		try {
			session = openSession();

			MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)session.get(MailReceiptHBM.class,
					receiptId);

			if (mailReceiptHBM == null) {
				_log.warn("No MailReceipt exists with the primary key of " +
					receiptId.toString());
				throw new NoSuchReceiptException(receiptId.toString());
			}

			com.liferay.portlet.mail.model.MailReceipt mailReceipt = MailReceiptHBMUtil.model(mailReceiptHBM);
			session.delete(mailReceiptHBM);
			session.flush();
			MailReceiptPool.remove(receiptId);

			return mailReceipt;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.mail.model.MailReceipt update(
		com.liferay.portlet.mail.model.MailReceipt mailReceipt)
		throws SystemException {
		Session session = null;

		try {
			if (mailReceipt.isNew() || mailReceipt.isModified()) {
				session = openSession();

				if (mailReceipt.isNew()) {
					MailReceiptHBM mailReceiptHBM = new MailReceiptHBM(mailReceipt.getReceiptId(),
							mailReceipt.getCompanyId(),
							mailReceipt.getUserId(),
							mailReceipt.getCreateDate(),
							mailReceipt.getModifiedDate(),
							mailReceipt.getRecipientName(),
							mailReceipt.getRecipientAddress(),
							mailReceipt.getSubject(),
							mailReceipt.getSentDate(),
							mailReceipt.getReadCount(),
							mailReceipt.getFirstReadDate(),
							mailReceipt.getLastReadDate());
					session.save(mailReceiptHBM);
					session.flush();
				}
				else {
					MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)session.get(MailReceiptHBM.class,
							mailReceipt.getPrimaryKey());

					if (mailReceiptHBM != null) {
						mailReceiptHBM.setCompanyId(mailReceipt.getCompanyId());
						mailReceiptHBM.setUserId(mailReceipt.getUserId());
						mailReceiptHBM.setCreateDate(mailReceipt.getCreateDate());
						mailReceiptHBM.setModifiedDate(mailReceipt.getModifiedDate());
						mailReceiptHBM.setRecipientName(mailReceipt.getRecipientName());
						mailReceiptHBM.setRecipientAddress(mailReceipt.getRecipientAddress());
						mailReceiptHBM.setSubject(mailReceipt.getSubject());
						mailReceiptHBM.setSentDate(mailReceipt.getSentDate());
						mailReceiptHBM.setReadCount(mailReceipt.getReadCount());
						mailReceiptHBM.setFirstReadDate(mailReceipt.getFirstReadDate());
						mailReceiptHBM.setLastReadDate(mailReceipt.getLastReadDate());
						session.flush();
					}
					else {
						mailReceiptHBM = new MailReceiptHBM(mailReceipt.getReceiptId(),
								mailReceipt.getCompanyId(),
								mailReceipt.getUserId(),
								mailReceipt.getCreateDate(),
								mailReceipt.getModifiedDate(),
								mailReceipt.getRecipientName(),
								mailReceipt.getRecipientAddress(),
								mailReceipt.getSubject(),
								mailReceipt.getSentDate(),
								mailReceipt.getReadCount(),
								mailReceipt.getFirstReadDate(),
								mailReceipt.getLastReadDate());
						session.save(mailReceiptHBM);
						session.flush();
					}
				}

				mailReceipt.setNew(false);
				mailReceipt.setModified(false);
				mailReceipt.protect();
				MailReceiptPool.put(mailReceipt.getPrimaryKey(), mailReceipt);
			}

			return mailReceipt;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.mail.model.MailReceipt findByPrimaryKey(
		String receiptId) throws NoSuchReceiptException, SystemException {
		com.liferay.portlet.mail.model.MailReceipt mailReceipt = MailReceiptPool.get(receiptId);
		Session session = null;

		try {
			if (mailReceipt == null) {
				session = openSession();

				MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)session.get(MailReceiptHBM.class,
						receiptId);

				if (mailReceiptHBM == null) {
					_log.warn("No MailReceipt exists with the primary key of " +
						receiptId.toString());
					throw new NoSuchReceiptException(receiptId.toString());
				}

				mailReceipt = MailReceiptHBMUtil.model(mailReceiptHBM);
			}

			return mailReceipt;
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
				list.add(MailReceiptHBMUtil.model(mailReceiptHBM));
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
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
					MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
					list.add(MailReceiptHBMUtil.model(mailReceiptHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)sr.get(0);
						list.add(MailReceiptHBMUtil.model(mailReceiptHBM));

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

	public com.liferay.portlet.mail.model.MailReceipt findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchReceiptException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchReceiptException();
		}
		else {
			return (com.liferay.portlet.mail.model.MailReceipt)list.get(0);
		}
	}

	public com.liferay.portlet.mail.model.MailReceipt findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchReceiptException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchReceiptException();
		}
		else {
			return (com.liferay.portlet.mail.model.MailReceipt)list.get(0);
		}
	}

	public com.liferay.portlet.mail.model.MailReceipt[] findByCompanyId_PrevAndNext(
		String receiptId, String companyId, OrderByComparator obc)
		throws NoSuchReceiptException, SystemException {
		com.liferay.portlet.mail.model.MailReceipt mailReceipt = findByPrimaryKey(receiptId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.mail.model.MailReceipt[] array = new com.liferay.portlet.mail.model.MailReceipt[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)sr.get(0);

					if (mailReceiptHBM == null) {
						break;
					}

					com.liferay.portlet.mail.model.MailReceipt curMailReceipt = MailReceiptHBMUtil.model(mailReceiptHBM);
					int value = obc.compare(mailReceipt, curMailReceipt);

					if (value == 0) {
						if (!mailReceipt.equals(curMailReceipt)) {
							break;
						}

						array[1] = curMailReceipt;

						if (sr.previous()) {
							array[0] = MailReceiptHBMUtil.model((MailReceiptHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MailReceiptHBMUtil.model((MailReceiptHBM)sr.get(
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
				list.add(MailReceiptHBMUtil.model(mailReceiptHBM));
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
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
					MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
					list.add(MailReceiptHBMUtil.model(mailReceiptHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)sr.get(0);
						list.add(MailReceiptHBMUtil.model(mailReceiptHBM));

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

	public com.liferay.portlet.mail.model.MailReceipt findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchReceiptException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchReceiptException();
		}
		else {
			return (com.liferay.portlet.mail.model.MailReceipt)list.get(0);
		}
	}

	public com.liferay.portlet.mail.model.MailReceipt findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchReceiptException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchReceiptException();
		}
		else {
			return (com.liferay.portlet.mail.model.MailReceipt)list.get(0);
		}
	}

	public com.liferay.portlet.mail.model.MailReceipt[] findByUserId_PrevAndNext(
		String receiptId, String userId, OrderByComparator obc)
		throws NoSuchReceiptException, SystemException {
		com.liferay.portlet.mail.model.MailReceipt mailReceipt = findByPrimaryKey(receiptId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.mail.model.MailReceipt[] array = new com.liferay.portlet.mail.model.MailReceipt[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)sr.get(0);

					if (mailReceiptHBM == null) {
						break;
					}

					com.liferay.portlet.mail.model.MailReceipt curMailReceipt = MailReceiptHBMUtil.model(mailReceiptHBM);
					int value = obc.compare(mailReceipt, curMailReceipt);

					if (value == 0) {
						if (!mailReceipt.equals(curMailReceipt)) {
							break;
						}

						array[1] = curMailReceipt;

						if (sr.previous()) {
							array[0] = MailReceiptHBMUtil.model((MailReceiptHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = MailReceiptHBMUtil.model((MailReceiptHBM)sr.get(
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
				list.add(MailReceiptHBMUtil.model(mailReceiptHBM));
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
				MailReceiptPool.remove((String)mailReceiptHBM.getPrimaryKey());
				session.delete(mailReceiptHBM);
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				MailReceiptHBM mailReceiptHBM = (MailReceiptHBM)itr.next();
				MailReceiptPool.remove((String)mailReceiptHBM.getPrimaryKey());
				session.delete(mailReceiptHBM);
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
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
				"FROM MailReceipt IN CLASS com.liferay.portlet.mail.service.persistence.MailReceiptHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(MailReceiptPersistence.class);
}