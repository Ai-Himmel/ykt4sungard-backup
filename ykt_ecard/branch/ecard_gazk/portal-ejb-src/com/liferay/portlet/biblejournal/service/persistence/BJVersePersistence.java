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

import com.liferay.portlet.biblejournal.NoSuchVerseException;

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
import java.util.Collection;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

/**
 * <a href="BJVersePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Rev: $
 *
 */
public class BJVersePersistence extends BasePersistence {
	public com.liferay.portlet.biblejournal.model.BJVerse create(String verseId) {
		return new com.liferay.portlet.biblejournal.model.BJVerse(verseId);
	}

	public com.liferay.portlet.biblejournal.model.BJVerse remove(String verseId)
		throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class,
					verseId);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					verseId.toString());
				throw new NoSuchVerseException(verseId.toString());
			}

			com.liferay.portlet.biblejournal.model.BJVerse bjVerse = BJVerseHBMUtil.model(bjVerseHBM);
			session.delete(bjVerseHBM);
			session.flush();
			BJVersePool.remove(verseId);

			return bjVerse;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJVerse update(
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws SystemException {
		Session session = null;

		try {
			if (bjVerse.isNew() || bjVerse.isModified()) {
				session = openSession();

				if (bjVerse.isNew()) {
					BJVerseHBM bjVerseHBM = new BJVerseHBM(bjVerse.getVerseId(),
							bjVerse.getCompanyId(), bjVerse.getUserId(),
							bjVerse.getName());
					session.save(bjVerseHBM);
					session.flush();
				}
				else {
					BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class,
							bjVerse.getPrimaryKey());

					if (bjVerseHBM != null) {
						bjVerseHBM.setCompanyId(bjVerse.getCompanyId());
						bjVerseHBM.setUserId(bjVerse.getUserId());
						bjVerseHBM.setName(bjVerse.getName());
						session.flush();
					}
					else {
						bjVerseHBM = new BJVerseHBM(bjVerse.getVerseId(),
								bjVerse.getCompanyId(), bjVerse.getUserId(),
								bjVerse.getName());
						session.save(bjVerseHBM);
						session.flush();
					}
				}

				bjVerse.setNew(false);
				bjVerse.setModified(false);
				bjVerse.protect();
				BJVersePool.put(bjVerse.getPrimaryKey(), bjVerse);
			}

			return bjVerse;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getBJEntries(String pk)
		throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjEntryHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class.getName());
			query.append(" bjVerseHBM ");
			query.append("JOIN bjVerseHBM.entries AS bjEntryHBM ");
			query.append("WHERE bjVerseHBM.verseId = ? ");
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
		throws NoSuchVerseException, SystemException {
		return getBJEntries(pk, begin, end, null);
	}

	public List getBJEntries(String pk, int begin, int end,
		OrderByComparator obc) throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjEntryHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class.getName());
			query.append(" bjVerseHBM ");
			query.append("JOIN bjVerseHBM.entries AS bjEntryHBM ");
			query.append("WHERE bjVerseHBM.verseId = ? ");

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
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class.getName());
			query.append(" bjVerseHBM ");
			query.append("JOIN bjVerseHBM.entries AS bjEntryHBM ");
			query.append("WHERE bjVerseHBM.verseId = ? ");

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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			bjVerseHBM.setEntries(entriesSet);
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			bjVerseHBM.setEntries(entriesSet);
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			boolean value = bjVerseHBM.getEntries().add(bjEntryHBM);
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			boolean value = bjVerseHBM.getEntries().add(bjEntryHBM);
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

				if (bjVerseHBM.getEntries().add(bjEntryHBM)) {
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

				if (bjVerseHBM.getEntries().add(bjEntryHBM)) {
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
		throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
			}

			bjVerseHBM.getEntries().clear();
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			Collection c = bjVerseHBM.getEntries();

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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			Collection c = bjVerseHBM.getEntries();

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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			boolean value = bjVerseHBM.getEntries().remove(bjEntryHBM);
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

			boolean value = bjVerseHBM.getEntries().remove(bjEntryHBM);
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

				if (bjVerseHBM.getEntries().remove(bjEntryHBM)) {
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
		throws NoSuchVerseException, 
			com.liferay.portlet.biblejournal.NoSuchEntryException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class, pk);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					pk.toString());
				throw new NoSuchVerseException(pk.toString());
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

				if (bjVerseHBM.getEntries().remove(bjEntryHBM)) {
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

	public com.liferay.portlet.biblejournal.model.BJVerse findByPrimaryKey(
		String verseId) throws NoSuchVerseException, SystemException {
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse = BJVersePool.get(verseId);
		Session session = null;

		try {
			if (bjVerse == null) {
				session = openSession();

				BJVerseHBM bjVerseHBM = (BJVerseHBM)session.get(BJVerseHBM.class,
						verseId);

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						verseId.toString());
					throw new NoSuchVerseException(verseId.toString());
				}

				bjVerse = BJVerseHBMUtil.model(bjVerseHBM);
			}

			return bjVerse;
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				list.add(BJVerseHBMUtil.model(bjVerseHBM));
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
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
					BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
					list.add(BJVerseHBMUtil.model(bjVerseHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BJVerseHBM bjVerseHBM = (BJVerseHBM)sr.get(0);
						list.add(BJVerseHBMUtil.model(bjVerseHBM));

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

	public com.liferay.portlet.biblejournal.model.BJVerse findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchVerseException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchVerseException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJVerse)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJVerse findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchVerseException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchVerseException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJVerse)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJVerse[] findByCompanyId_PrevAndNext(
		String verseId, String companyId, OrderByComparator obc)
		throws NoSuchVerseException, SystemException {
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse = findByPrimaryKey(verseId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.biblejournal.model.BJVerse[] array = new com.liferay.portlet.biblejournal.model.BJVerse[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BJVerseHBM bjVerseHBM = (BJVerseHBM)sr.get(0);

					if (bjVerseHBM == null) {
						break;
					}

					com.liferay.portlet.biblejournal.model.BJVerse curBJVerse = BJVerseHBMUtil.model(bjVerseHBM);
					int value = obc.compare(bjVerse, curBJVerse);

					if (value == 0) {
						if (!bjVerse.equals(curBJVerse)) {
							break;
						}

						array[1] = curBJVerse;

						if (sr.previous()) {
							array[0] = BJVerseHBMUtil.model((BJVerseHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BJVerseHBMUtil.model((BJVerseHBM)sr.get(
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				list.add(BJVerseHBMUtil.model(bjVerseHBM));
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
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
					BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
					list.add(BJVerseHBMUtil.model(bjVerseHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BJVerseHBM bjVerseHBM = (BJVerseHBM)sr.get(0);
						list.add(BJVerseHBMUtil.model(bjVerseHBM));

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

	public com.liferay.portlet.biblejournal.model.BJVerse findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchVerseException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchVerseException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJVerse)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJVerse findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchVerseException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchVerseException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJVerse)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJVerse[] findByUserId_PrevAndNext(
		String verseId, String userId, OrderByComparator obc)
		throws NoSuchVerseException, SystemException {
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse = findByPrimaryKey(verseId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portlet.biblejournal.model.BJVerse[] array = new com.liferay.portlet.biblejournal.model.BJVerse[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BJVerseHBM bjVerseHBM = (BJVerseHBM)sr.get(0);

					if (bjVerseHBM == null) {
						break;
					}

					com.liferay.portlet.biblejournal.model.BJVerse curBJVerse = BJVerseHBMUtil.model(bjVerseHBM);
					int value = obc.compare(bjVerse, curBJVerse);

					if (value == 0) {
						if (!bjVerse.equals(curBJVerse)) {
							break;
						}

						array[1] = curBJVerse;

						if (sr.previous()) {
							array[0] = BJVerseHBMUtil.model((BJVerseHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BJVerseHBMUtil.model((BJVerseHBM)sr.get(
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

	public com.liferay.portlet.biblejournal.model.BJVerse findByName(
		String name) throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, name);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchVerseException();
			}

			BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();

			return BJVerseHBMUtil.model(bjVerseHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJVerse findByC_U_N(
		String companyId, String userId, String name)
		throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, name);

			Iterator itr = q.list().iterator();

			if (!itr.hasNext()) {
				throw new NoSuchVerseException();
			}

			BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();

			return BJVerseHBMUtil.model(bjVerseHBM);
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				list.add(BJVerseHBMUtil.model(bjVerseHBM));
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				BJVersePool.remove((String)bjVerseHBM.getPrimaryKey());
				session.delete(bjVerseHBM);
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				BJVersePool.remove((String)bjVerseHBM.getPrimaryKey());
				session.delete(bjVerseHBM);
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

	public void removeByName(String name)
		throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, name);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				BJVersePool.remove((String)bjVerseHBM.getPrimaryKey());
				session.delete(bjVerseHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchVerseException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByC_U_N(String companyId, String userId, String name)
		throws NoSuchVerseException, SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, name);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				BJVerseHBM bjVerseHBM = (BJVerseHBM)itr.next();
				BJVersePool.remove((String)bjVerseHBM.getPrimaryKey());
				session.delete(bjVerseHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchVerseException();
			}
			else {
				throw new SystemException(he);
			}
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
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
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
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

	public int countByName(String name) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, name);

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

	public int countByC_U_N(String companyId, String userId, String name)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM BJVerse IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("userId = ?");
			query.append(" AND ");
			query.append("name = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, userId);
			q.setString(queryPos++, name);

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

	private static final Log _log = LogFactory.getLog(BJVersePersistence.class);
}