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

package com.liferay.portlet.biblejournal.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.biblejournal.NoSuchTopicException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <a href="BJTopicPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Rev: $
 *
 */
public class BJTopicPersistence extends BasePersistence {
	public com.liferay.portlet.biblejournal.model.BJTopic create(String topicId) {
		return new com.liferay.portlet.biblejournal.model.BJTopic(topicId);
	}

	public com.liferay.portlet.biblejournal.model.BJTopic remove(String topicId)
		throws NoSuchTopicException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class,
					topicId);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					topicId.toString());
				throw new NoSuchTopicException(topicId.toString());
			}

			com.liferay.portlet.biblejournal.model.BJTopic bjTopic = BJTopicHBMUtil.model(bjTopicHBM);
			session.delete(bjTopicHBM);
			session.flush();
			BJTopicPool.remove(topicId);

			return bjTopic;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJTopic update(
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws SystemException {
		Session session = null;

		try {
			if (bjTopic.isNew() || bjTopic.isModified()) {
				session = openSession();

				if (bjTopic.isNew()) {
					BJTopicHBM bjTopicHBM = new BJTopicHBM(bjTopic.getTopicId(),
							bjTopic.getCompanyId(), bjTopic.getUserId(),
							bjTopic.getCreateDate(), bjTopic.getModifiedDate(),
							bjTopic.getName(), bjTopic.getDescription());
					session.save(bjTopicHBM);
					session.flush();
				}
				else {
					BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class,
							bjTopic.getPrimaryKey());

					if (bjTopicHBM != null) {
						bjTopicHBM.setCompanyId(bjTopic.getCompanyId());
						bjTopicHBM.setUserId(bjTopic.getUserId());
						bjTopicHBM.setCreateDate(bjTopic.getCreateDate());
						bjTopicHBM.setModifiedDate(bjTopic.getModifiedDate());
						bjTopicHBM.setName(bjTopic.getName());
						bjTopicHBM.setDescription(bjTopic.getDescription());
						session.flush();
					}
					else {
						bjTopicHBM = new BJTopicHBM(bjTopic.getTopicId(),
								bjTopic.getCompanyId(), bjTopic.getUserId(),
								bjTopic.getCreateDate(),
								bjTopic.getModifiedDate(), bjTopic.getName(),
								bjTopic.getDescription());
						session.save(bjTopicHBM);
						session.flush();
					}
				}

				bjTopic.setNew(false);
				bjTopic.setModified(false);
				bjTopic.protect();
				BJTopicPool.put(bjTopic.getPrimaryKey(), bjTopic);
			}

			return bjTopic;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getBJEntries(String pk)
		throws NoSuchTopicException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjEntryHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class.getName());
			query.append(" bjTopicHBM ");
			query.append("JOIN bjTopicHBM.entries AS bjEntryHBM ");
			query.append("WHERE bjTopicHBM.topicId = ? ");
			query.append("ORDER BY ");
			query.append("bjEntryHBM.userId ASC").append(", ");
			query.append("bjEntryHBM.name ASC").append(", ");
			query.append("bjEntryHBM.createDate ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)itr.next();
				list.add(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBMUtil.model(
						bjEntryHBM));
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

	public List getBJEntries(String pk, int begin, int end)
		throws NoSuchTopicException, SystemException {
		return getBJEntries(pk, begin, end, null);
	}

	public List getBJEntries(String pk, int begin, int end,
		OrderByComparator obc) throws NoSuchTopicException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjEntryHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class.getName());
			query.append(" bjTopicHBM ");
			query.append("JOIN bjTopicHBM.entries AS bjEntryHBM ");
			query.append("WHERE bjTopicHBM.topicId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("bjEntryHBM.userId ASC").append(", ");
				query.append("bjEntryHBM.name ASC").append(", ");
				query.append("bjEntryHBM.createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
						(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)itr.next();
					list.add(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBMUtil.model(
							bjEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
							(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)sr.get(0);
						list.add(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBMUtil.model(
								bjEntryHBM));

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

	public int getBJEntriesSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class.getName());
			query.append(" bjTopicHBM ");
			query.append("JOIN bjTopicHBM.entries AS bjEntryHBM ");
			query.append("WHERE bjTopicHBM.topicId = ? ");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.iterate();

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

	public void setBJEntries(String pk, String[] pks)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			Set entriesSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
						pks[i]);

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchEntryException(pks[i].toString());
				}

				entriesSet.add(bjEntryHBM);
			}

			bjTopicHBM.setEntries(entriesSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setBJEntries(String pk, List entries)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			Set entriesSet = new HashSet();
			Iterator itr = entries.iterator();

			while (itr.hasNext()) {
				com.liferay.portlet.biblejournal.model.BJEntry bjEntry = (com.liferay.portlet.biblejournal.model.BJEntry)itr.next();
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
						bjEntry.getPrimaryKey());

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						bjEntry.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntry.getPrimaryKey()
																						   .toString());
				}

				entriesSet.add(bjEntryHBM);
			}

			bjTopicHBM.setEntries(entriesSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addBJEntry(String pk, String bjEntryPK)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
				null;
			bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
					bjEntryPK);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					bjEntryPK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntryPK.toString());
			}

			boolean value = bjTopicHBM.getEntries().add(bjEntryHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addBJEntry(String pk,
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
				null;
			bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
					bjEntry.getPrimaryKey());

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					bjEntry.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntry.getPrimaryKey()
																					   .toString());
			}

			boolean value = bjTopicHBM.getEntries().add(bjEntryHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addBJEntries(String pk, String[] bjEntryPKs)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjEntryPKs.length; i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					null;
				bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
						bjEntryPKs[i]);

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						bjEntryPKs[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntryPKs[i].toString());
				}

				if (bjTopicHBM.getEntries().add(bjEntryHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addBJEntries(String pk, List bjEntries)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjEntries.size(); i++) {
				com.liferay.portlet.biblejournal.model.BJEntry bjEntry = (com.liferay.portlet.biblejournal.model.BJEntry)bjEntries.get(i);
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
						bjEntry.getPrimaryKey());

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						bjEntry.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntry.getPrimaryKey()
																						   .toString());
				}

				if (bjTopicHBM.getEntries().add(bjEntryHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void clearBJEntries(String pk)
		throws NoSuchTopicException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			bjTopicHBM.getEntries().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsBJEntry(String pk, String bjEntryPK)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
				null;
			bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
					bjEntryPK);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					bjEntryPK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntryPK.toString());
			}

			Collection c = bjTopicHBM.getEntries();

			return c.contains(bjEntryHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsBJEntry(String pk,
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
				null;
			bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
					bjEntry.getPrimaryKey());

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					bjEntry.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntry.getPrimaryKey()
																					   .toString());
			}

			Collection c = bjTopicHBM.getEntries();

			return c.contains(bjEntryHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeBJEntry(String pk, String bjEntryPK)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
				null;
			bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
					bjEntryPK);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					bjEntryPK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntryPK.toString());
			}

			boolean value = bjTopicHBM.getEntries().remove(bjEntryHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeBJEntry(String pk,
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
				null;
			bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
					bjEntry.getPrimaryKey());

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					bjEntry.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntry.getPrimaryKey()
																					   .toString());
			}

			boolean value = bjTopicHBM.getEntries().remove(bjEntryHBM);
			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeBJEntries(String pk, String[] bjEntryPKs)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjEntryPKs.length; i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					null;
				bjEntryHBM = (com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
						bjEntryPKs[i]);

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						bjEntryPKs[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntryPKs[i].toString());
				}

				if (bjTopicHBM.getEntries().remove(bjEntryHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeBJEntries(String pk, List bjEntries)
		throws NoSuchTopicException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class, pk);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					pk.toString());
				throw new NoSuchTopicException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjEntries.size(); i++) {
				com.liferay.portlet.biblejournal.model.BJEntry bjEntry = (com.liferay.portlet.biblejournal.model.BJEntry)bjEntries.get(i);
				com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM bjEntryHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class,
						bjEntry.getPrimaryKey());

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						bjEntry.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchEntryException(bjEntry.getPrimaryKey()
																						   .toString());
				}

				if (bjTopicHBM.getEntries().remove(bjEntryHBM)) {
					value = true;
				}
			}

			session.flush();

			return value;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJTopic findByPrimaryKey(
		String topicId) throws NoSuchTopicException, SystemException {
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic = BJTopicPool.get(topicId);
		Session session = null;

		try {
			if (bjTopic == null) {
				session = openSession();

				BJTopicHBM bjTopicHBM = (BJTopicHBM)session.get(BJTopicHBM.class,
						topicId);

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						topicId.toString());
					throw new NoSuchTopicException(topicId.toString());
				}

				bjTopic = BJTopicHBMUtil.model(bjTopicHBM);
			}

			return bjTopic;
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("userId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
				list.add(BJTopicHBMUtil.model(bjTopicHBM));
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("userId ASC").append(", ");
				query.append("name ASC").append(", ");
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
					BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
					list.add(BJTopicHBMUtil.model(bjTopicHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BJTopicHBM bjTopicHBM = (BJTopicHBM)sr.get(0);
						list.add(BJTopicHBMUtil.model(bjTopicHBM));

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

	public com.liferay.portlet.biblejournal.model.BJTopic findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJTopic)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJTopic findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJTopic)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJTopic[] findByCompanyId_PrevAndNext(
		String topicId, String companyId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic = findByPrimaryKey(topicId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("userId ASC").append(", ");
				query.append("name ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.biblejournal.model.BJTopic[] array = new com.liferay.portlet.biblejournal.model.BJTopic[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BJTopicHBM bjTopicHBM = (BJTopicHBM)sr.get(0);

					if (bjTopicHBM == null) {
						break;
					}

					com.liferay.portlet.biblejournal.model.BJTopic curBJTopic = BJTopicHBMUtil.model(bjTopicHBM);
					int value = obc.compare(bjTopic, curBJTopic);

					if (value == 0) {
						if (!bjTopic.equals(curBJTopic)) {
							break;
						}

						array[1] = curBJTopic;

						if (sr.previous()) {
							array[0] = BJTopicHBMUtil.model((BJTopicHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BJTopicHBMUtil.model((BJTopicHBM)sr.get(
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("userId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
				list.add(BJTopicHBMUtil.model(bjTopicHBM));
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("userId ASC").append(", ");
				query.append("name ASC").append(", ");
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
					BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
					list.add(BJTopicHBMUtil.model(bjTopicHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BJTopicHBM bjTopicHBM = (BJTopicHBM)sr.get(0);
						list.add(BJTopicHBMUtil.model(bjTopicHBM));

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

	public com.liferay.portlet.biblejournal.model.BJTopic findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJTopic)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJTopic findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchTopicException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJTopic)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJTopic[] findByUserId_PrevAndNext(
		String topicId, String userId, OrderByComparator obc)
		throws NoSuchTopicException, SystemException {
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic = findByPrimaryKey(topicId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("userId ASC").append(", ");
				query.append("name ASC").append(", ");
				query.append("createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.biblejournal.model.BJTopic[] array = new com.liferay.portlet.biblejournal.model.BJTopic[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BJTopicHBM bjTopicHBM = (BJTopicHBM)sr.get(0);

					if (bjTopicHBM == null) {
						break;
					}

					com.liferay.portlet.biblejournal.model.BJTopic curBJTopic = BJTopicHBMUtil.model(bjTopicHBM);
					int value = obc.compare(bjTopic, curBJTopic);

					if (value == 0) {
						if (!bjTopic.equals(curBJTopic)) {
							break;
						}

						array[1] = curBJTopic;

						if (sr.previous()) {
							array[0] = BJTopicHBMUtil.model((BJTopicHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BJTopicHBMUtil.model((BJTopicHBM)sr.get(
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM ");
			query.append("ORDER BY ");
			query.append("userId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
				list.add(BJTopicHBMUtil.model(bjTopicHBM));
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("userId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
				BJTopicPool.remove((String)bjTopicHBM.getPrimaryKey());
				session.delete(bjTopicHBM);
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("userId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BJTopicHBM bjTopicHBM = (BJTopicHBM)itr.next();
				BJTopicPool.remove((String)bjTopicHBM.getPrimaryKey());
				session.delete(bjTopicHBM);
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
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
				"FROM BJTopic IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(BJTopicPersistence.class);
}