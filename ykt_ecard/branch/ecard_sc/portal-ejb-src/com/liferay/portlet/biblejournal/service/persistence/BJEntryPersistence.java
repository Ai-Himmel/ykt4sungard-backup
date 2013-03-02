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

import com.liferay.portlet.biblejournal.NoSuchEntryException;

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
 * <a href="BJEntryPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Rev: $
 *
 */
public class BJEntryPersistence extends BasePersistence {
	public com.liferay.portlet.biblejournal.model.BJEntry create(String entryId) {
		return new com.liferay.portlet.biblejournal.model.BJEntry(entryId);
	}

	public com.liferay.portlet.biblejournal.model.BJEntry remove(String entryId)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class,
					entryId);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					entryId.toString());
				throw new NoSuchEntryException(entryId.toString());
			}

			com.liferay.portlet.biblejournal.model.BJEntry bjEntry = BJEntryHBMUtil.model(bjEntryHBM);
			session.delete(bjEntryHBM);
			session.flush();
			BJEntryPool.remove(entryId);

			return bjEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJEntry update(
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry)
		throws SystemException {
		Session session = null;

		try {
			if (bjEntry.isNew() || bjEntry.isModified()) {
				session = openSession();

				if (bjEntry.isNew()) {
					BJEntryHBM bjEntryHBM = new BJEntryHBM(bjEntry.getEntryId(),
							bjEntry.getCompanyId(), bjEntry.getUserId(),
							bjEntry.getCreateDate(), bjEntry.getModifiedDate(),
							bjEntry.getName(), bjEntry.getContent(),
							bjEntry.getVersesInput());
					session.save(bjEntryHBM);
					session.flush();
				}
				else {
					BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class,
							bjEntry.getPrimaryKey());

					if (bjEntryHBM != null) {
						bjEntryHBM.setCompanyId(bjEntry.getCompanyId());
						bjEntryHBM.setUserId(bjEntry.getUserId());
						bjEntryHBM.setCreateDate(bjEntry.getCreateDate());
						bjEntryHBM.setModifiedDate(bjEntry.getModifiedDate());
						bjEntryHBM.setName(bjEntry.getName());
						bjEntryHBM.setContent(bjEntry.getContent());
						bjEntryHBM.setVersesInput(bjEntry.getVersesInput());
						session.flush();
					}
					else {
						bjEntryHBM = new BJEntryHBM(bjEntry.getEntryId(),
								bjEntry.getCompanyId(), bjEntry.getUserId(),
								bjEntry.getCreateDate(),
								bjEntry.getModifiedDate(), bjEntry.getName(),
								bjEntry.getContent(), bjEntry.getVersesInput());
						session.save(bjEntryHBM);
						session.flush();
					}
				}

				bjEntry.setNew(false);
				bjEntry.setModified(false);
				bjEntry.protect();
				BJEntryPool.put(bjEntry.getPrimaryKey(), bjEntry);
			}

			return bjEntry;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List getBJVerses(String pk)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjVerseHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class.getName());
			query.append(" bjEntryHBM ");
			query.append("JOIN bjEntryHBM.verses AS bjVerseHBM ");
			query.append("WHERE bjEntryHBM.entryId = ? ");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)itr.next();
				list.add(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBMUtil.model(
						bjVerseHBM));
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

	public List getBJVerses(String pk, int begin, int end)
		throws NoSuchEntryException, SystemException {
		return getBJVerses(pk, begin, end, null);
	}

	public List getBJVerses(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjVerseHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class.getName());
			query.append(" bjEntryHBM ");
			query.append("JOIN bjEntryHBM.verses AS bjVerseHBM ");
			query.append("WHERE bjEntryHBM.entryId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
						(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)itr.next();
					list.add(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBMUtil.model(
							bjVerseHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
							(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)sr.get(0);
						list.add(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBMUtil.model(
								bjVerseHBM));

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

	public int getBJVersesSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class.getName());
			query.append(" bjEntryHBM ");
			query.append("JOIN bjEntryHBM.verses AS bjVerseHBM ");
			query.append("WHERE bjEntryHBM.entryId = ? ");

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

	public void setBJVerses(String pk, String[] pks)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			Set versesSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
						pks[i]);

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchVerseException(pks[i].toString());
				}

				versesSet.add(bjVerseHBM);
			}

			bjEntryHBM.setVerses(versesSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setBJVerses(String pk, List verses)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			Set versesSet = new HashSet();
			Iterator itr = verses.iterator();

			while (itr.hasNext()) {
				com.liferay.portlet.biblejournal.model.BJVerse bjVerse = (com.liferay.portlet.biblejournal.model.BJVerse)itr.next();
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
						bjVerse.getPrimaryKey());

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						bjVerse.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVerse.getPrimaryKey()
																						   .toString());
				}

				versesSet.add(bjVerseHBM);
			}

			bjEntryHBM.setVerses(versesSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addBJVerse(String pk, String bjVersePK)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
				null;
			bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
					bjVersePK);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					bjVersePK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVersePK.toString());
			}

			boolean value = bjEntryHBM.getVerses().add(bjVerseHBM);
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

	public boolean addBJVerse(String pk,
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
				null;
			bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
					bjVerse.getPrimaryKey());

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					bjVerse.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVerse.getPrimaryKey()
																					   .toString());
			}

			boolean value = bjEntryHBM.getVerses().add(bjVerseHBM);
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

	public boolean addBJVerses(String pk, String[] bjVersePKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjVersePKs.length; i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					null;
				bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
						bjVersePKs[i]);

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						bjVersePKs[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVersePKs[i].toString());
				}

				if (bjEntryHBM.getVerses().add(bjVerseHBM)) {
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

	public boolean addBJVerses(String pk, List bjVerses)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjVerses.size(); i++) {
				com.liferay.portlet.biblejournal.model.BJVerse bjVerse = (com.liferay.portlet.biblejournal.model.BJVerse)bjVerses.get(i);
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
						bjVerse.getPrimaryKey());

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						bjVerse.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVerse.getPrimaryKey()
																						   .toString());
				}

				if (bjEntryHBM.getVerses().add(bjVerseHBM)) {
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

	public void clearBJVerses(String pk)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			bjEntryHBM.getVerses().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsBJVerse(String pk, String bjVersePK)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
				null;
			bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
					bjVersePK);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					bjVersePK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVersePK.toString());
			}

			Collection c = bjEntryHBM.getVerses();

			return c.contains(bjVerseHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsBJVerse(String pk,
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
				null;
			bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
					bjVerse.getPrimaryKey());

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					bjVerse.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVerse.getPrimaryKey()
																					   .toString());
			}

			Collection c = bjEntryHBM.getVerses();

			return c.contains(bjVerseHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeBJVerse(String pk, String bjVersePK)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
				null;
			bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
					bjVersePK);

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					bjVersePK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVersePK.toString());
			}

			boolean value = bjEntryHBM.getVerses().remove(bjVerseHBM);
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

	public boolean removeBJVerse(String pk,
		com.liferay.portlet.biblejournal.model.BJVerse bjVerse)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
				null;
			bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
					bjVerse.getPrimaryKey());

			if (bjVerseHBM == null) {
				_log.warn("No BJVerse exists with the primary key of " +
					bjVerse.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVerse.getPrimaryKey()
																					   .toString());
			}

			boolean value = bjEntryHBM.getVerses().remove(bjVerseHBM);
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

	public boolean removeBJVerses(String pk, String[] bjVersePKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjVersePKs.length; i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					null;
				bjVerseHBM = (com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
						bjVersePKs[i]);

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						bjVersePKs[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVersePKs[i].toString());
				}

				if (bjEntryHBM.getVerses().remove(bjVerseHBM)) {
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

	public boolean removeBJVerses(String pk, List bjVerses)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchVerseException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjVerses.size(); i++) {
				com.liferay.portlet.biblejournal.model.BJVerse bjVerse = (com.liferay.portlet.biblejournal.model.BJVerse)bjVerses.get(i);
				com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM bjVerseHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJVerseHBM.class,
						bjVerse.getPrimaryKey());

				if (bjVerseHBM == null) {
					_log.warn("No BJVerse exists with the primary key of " +
						bjVerse.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchVerseException(bjVerse.getPrimaryKey()
																						   .toString());
				}

				if (bjEntryHBM.getVerses().remove(bjVerseHBM)) {
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

	public List getBJTopics(String pk)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjTopicHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class.getName());
			query.append(" bjEntryHBM ");
			query.append("JOIN bjEntryHBM.topics AS bjTopicHBM ");
			query.append("WHERE bjEntryHBM.entryId = ? ");
			query.append("ORDER BY ");
			query.append("bjTopicHBM.userId ASC").append(", ");
			query.append("bjTopicHBM.name ASC").append(", ");
			query.append("bjTopicHBM.createDate ASC");

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)itr.next();
				list.add(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBMUtil.model(
						bjTopicHBM));
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

	public List getBJTopics(String pk, int begin, int end)
		throws NoSuchEntryException, SystemException {
		return getBJTopics(pk, begin, end, null);
	}

	public List getBJTopics(String pk, int begin, int end, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT bjTopicHBM FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class.getName());
			query.append(" bjEntryHBM ");
			query.append("JOIN bjEntryHBM.topics AS bjTopicHBM ");
			query.append("WHERE bjEntryHBM.entryId = ? ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("bjTopicHBM.userId ASC").append(", ");
				query.append("bjTopicHBM.name ASC").append(", ");
				query.append("bjTopicHBM.createDate ASC");
			}

			Query q = session.createQuery(query.toString());
			q.setString(0, pk);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
						(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)itr.next();
					list.add(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBMUtil.model(
							bjTopicHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
							(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)sr.get(0);
						list.add(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBMUtil.model(
								bjTopicHBM));

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

	public int getBJTopicsSize(String pk) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) FROM ");
			query.append(com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM.class.getName());
			query.append(" bjEntryHBM ");
			query.append("JOIN bjEntryHBM.topics AS bjTopicHBM ");
			query.append("WHERE bjEntryHBM.entryId = ? ");

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

	public void setBJTopics(String pk, String[] pks)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			Set topicsSet = new HashSet();

			for (int i = 0; (pks != null) && (i < pks.length); i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
						pks[i]);

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						pks[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchTopicException(pks[i].toString());
				}

				topicsSet.add(bjTopicHBM);
			}

			bjEntryHBM.setTopics(topicsSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void setBJTopics(String pk, List topics)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			Set topicsSet = new HashSet();
			Iterator itr = topics.iterator();

			while (itr.hasNext()) {
				com.liferay.portlet.biblejournal.model.BJTopic bjTopic = (com.liferay.portlet.biblejournal.model.BJTopic)itr.next();
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
						bjTopic.getPrimaryKey());

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						bjTopic.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopic.getPrimaryKey()
																						   .toString());
				}

				topicsSet.add(bjTopicHBM);
			}

			bjEntryHBM.setTopics(topicsSet);
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean addBJTopic(String pk, String bjTopicPK)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
				null;
			bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
					bjTopicPK);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					bjTopicPK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopicPK.toString());
			}

			boolean value = bjEntryHBM.getTopics().add(bjTopicHBM);
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

	public boolean addBJTopic(String pk,
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
				null;
			bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
					bjTopic.getPrimaryKey());

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					bjTopic.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopic.getPrimaryKey()
																					   .toString());
			}

			boolean value = bjEntryHBM.getTopics().add(bjTopicHBM);
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

	public boolean addBJTopics(String pk, String[] bjTopicPKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjTopicPKs.length; i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					null;
				bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
						bjTopicPKs[i]);

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						bjTopicPKs[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopicPKs[i].toString());
				}

				if (bjEntryHBM.getTopics().add(bjTopicHBM)) {
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

	public boolean addBJTopics(String pk, List bjTopics)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjTopics.size(); i++) {
				com.liferay.portlet.biblejournal.model.BJTopic bjTopic = (com.liferay.portlet.biblejournal.model.BJTopic)bjTopics.get(i);
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
						bjTopic.getPrimaryKey());

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						bjTopic.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopic.getPrimaryKey()
																						   .toString());
				}

				if (bjEntryHBM.getTopics().add(bjTopicHBM)) {
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

	public void clearBJTopics(String pk)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			bjEntryHBM.getTopics().clear();
			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsBJTopic(String pk, String bjTopicPK)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
				null;
			bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
					bjTopicPK);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					bjTopicPK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopicPK.toString());
			}

			Collection c = bjEntryHBM.getTopics();

			return c.contains(bjTopicHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean containsBJTopic(String pk,
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
				null;
			bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
					bjTopic.getPrimaryKey());

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					bjTopic.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopic.getPrimaryKey()
																					   .toString());
			}

			Collection c = bjEntryHBM.getTopics();

			return c.contains(bjTopicHBM);
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public boolean removeBJTopic(String pk, String bjTopicPK)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
				null;
			bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
					bjTopicPK);

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					bjTopicPK.toString());
				throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopicPK.toString());
			}

			boolean value = bjEntryHBM.getTopics().remove(bjTopicHBM);
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

	public boolean removeBJTopic(String pk,
		com.liferay.portlet.biblejournal.model.BJTopic bjTopic)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
				null;
			bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
					bjTopic.getPrimaryKey());

			if (bjTopicHBM == null) {
				_log.warn("No BJTopic exists with the primary key of " +
					bjTopic.getPrimaryKey().toString());
				throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopic.getPrimaryKey()
																					   .toString());
			}

			boolean value = bjEntryHBM.getTopics().remove(bjTopicHBM);
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

	public boolean removeBJTopics(String pk, String[] bjTopicPKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjTopicPKs.length; i++) {
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					null;
				bjTopicHBM = (com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
						bjTopicPKs[i]);

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						bjTopicPKs[i].toString());
					throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopicPKs[i].toString());
				}

				if (bjEntryHBM.getTopics().remove(bjTopicHBM)) {
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

	public boolean removeBJTopics(String pk, List bjTopics)
		throws NoSuchEntryException, 
			com.liferay.portlet.biblejournal.NoSuchTopicException, 
			SystemException {
		Session session = null;

		try {
			session = openSession();

			BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class, pk);

			if (bjEntryHBM == null) {
				_log.warn("No BJEntry exists with the primary key of " +
					pk.toString());
				throw new NoSuchEntryException(pk.toString());
			}

			boolean value = false;

			for (int i = 0; i < bjTopics.size(); i++) {
				com.liferay.portlet.biblejournal.model.BJTopic bjTopic = (com.liferay.portlet.biblejournal.model.BJTopic)bjTopics.get(i);
				com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM bjTopicHBM =
					(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM)session.get(com.liferay.portlet.biblejournal.service.persistence.BJTopicHBM.class,
						bjTopic.getPrimaryKey());

				if (bjTopicHBM == null) {
					_log.warn("No BJTopic exists with the primary key of " +
						bjTopic.getPrimaryKey().toString());
					throw new com.liferay.portlet.biblejournal.NoSuchTopicException(bjTopic.getPrimaryKey()
																						   .toString());
				}

				if (bjEntryHBM.getTopics().remove(bjTopicHBM)) {
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

	public com.liferay.portlet.biblejournal.model.BJEntry findByPrimaryKey(
		String entryId) throws NoSuchEntryException, SystemException {
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry = BJEntryPool.get(entryId);
		Session session = null;

		try {
			if (bjEntry == null) {
				session = openSession();

				BJEntryHBM bjEntryHBM = (BJEntryHBM)session.get(BJEntryHBM.class,
						entryId);

				if (bjEntryHBM == null) {
					_log.warn("No BJEntry exists with the primary key of " +
						entryId.toString());
					throw new NoSuchEntryException(entryId.toString());
				}

				bjEntry = BJEntryHBMUtil.model(bjEntryHBM);
			}

			return bjEntry;
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
				BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
				list.add(BJEntryHBMUtil.model(bjEntryHBM));
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
					BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
					list.add(BJEntryHBMUtil.model(bjEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BJEntryHBM bjEntryHBM = (BJEntryHBM)sr.get(0);
						list.add(BJEntryHBMUtil.model(bjEntryHBM));

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

	public com.liferay.portlet.biblejournal.model.BJEntry findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJEntry)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJEntry findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJEntry)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJEntry[] findByCompanyId_PrevAndNext(
		String entryId, String companyId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry = findByPrimaryKey(entryId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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

			com.liferay.portlet.biblejournal.model.BJEntry[] array = new com.liferay.portlet.biblejournal.model.BJEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BJEntryHBM bjEntryHBM = (BJEntryHBM)sr.get(0);

					if (bjEntryHBM == null) {
						break;
					}

					com.liferay.portlet.biblejournal.model.BJEntry curBJEntry = BJEntryHBMUtil.model(bjEntryHBM);
					int value = obc.compare(bjEntry, curBJEntry);

					if (value == 0) {
						if (!bjEntry.equals(curBJEntry)) {
							break;
						}

						array[1] = curBJEntry;

						if (sr.previous()) {
							array[0] = BJEntryHBMUtil.model((BJEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BJEntryHBMUtil.model((BJEntryHBM)sr.get(
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
				BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
				list.add(BJEntryHBMUtil.model(bjEntryHBM));
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
					BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
					list.add(BJEntryHBMUtil.model(bjEntryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						BJEntryHBM bjEntryHBM = (BJEntryHBM)sr.get(0);
						list.add(BJEntryHBMUtil.model(bjEntryHBM));

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

	public com.liferay.portlet.biblejournal.model.BJEntry findByUserId_First(
		String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJEntry)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJEntry findByUserId_Last(
		String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchEntryException();
		}
		else {
			return (com.liferay.portlet.biblejournal.model.BJEntry)list.get(0);
		}
	}

	public com.liferay.portlet.biblejournal.model.BJEntry[] findByUserId_PrevAndNext(
		String entryId, String userId, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		com.liferay.portlet.biblejournal.model.BJEntry bjEntry = findByPrimaryKey(entryId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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

			com.liferay.portlet.biblejournal.model.BJEntry[] array = new com.liferay.portlet.biblejournal.model.BJEntry[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					BJEntryHBM bjEntryHBM = (BJEntryHBM)sr.get(0);

					if (bjEntryHBM == null) {
						break;
					}

					com.liferay.portlet.biblejournal.model.BJEntry curBJEntry = BJEntryHBMUtil.model(bjEntryHBM);
					int value = obc.compare(bjEntry, curBJEntry);

					if (value == 0) {
						if (!bjEntry.equals(curBJEntry)) {
							break;
						}

						array[1] = curBJEntry;

						if (sr.previous()) {
							array[0] = BJEntryHBMUtil.model((BJEntryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = BJEntryHBMUtil.model((BJEntryHBM)sr.get(
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM ");
			query.append("ORDER BY ");
			query.append("userId ASC").append(", ");
			query.append("name ASC").append(", ");
			query.append("createDate ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
				list.add(BJEntryHBMUtil.model(bjEntryHBM));
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
				BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
				BJEntryPool.remove((String)bjEntryHBM.getPrimaryKey());
				session.delete(bjEntryHBM);
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
				BJEntryHBM bjEntryHBM = (BJEntryHBM)itr.next();
				BJEntryPool.remove((String)bjEntryHBM.getPrimaryKey());
				session.delete(bjEntryHBM);
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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
				"FROM BJEntry IN CLASS com.liferay.portlet.biblejournal.service.persistence.BJEntryHBM WHERE ");
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

	private static final Log _log = LogFactory.getLog(BJEntryPersistence.class);
}