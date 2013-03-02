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

import com.liferay.portal.NoSuchNoteException;
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
 * <a href="NotePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class NotePersistence extends BasePersistence {
	public com.liferay.portal.model.Note create(String noteId) {
		return new com.liferay.portal.model.Note(noteId);
	}

	public com.liferay.portal.model.Note remove(String noteId)
		throws NoSuchNoteException, SystemException {
		Session session = null;

		try {
			session = openSession();

			NoteHBM noteHBM = (NoteHBM)session.get(NoteHBM.class, noteId);

			if (noteHBM == null) {
				_log.warn("No Note exists with the primary key of " +
					noteId.toString());
				throw new NoSuchNoteException(noteId.toString());
			}

			com.liferay.portal.model.Note note = NoteHBMUtil.model(noteHBM);
			session.delete(noteHBM);
			session.flush();
			NotePool.remove(noteId);

			return note;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Note update(
		com.liferay.portal.model.Note note) throws SystemException {
		Session session = null;

		try {
			if (note.isNew() || note.isModified()) {
				session = openSession();

				if (note.isNew()) {
					NoteHBM noteHBM = new NoteHBM(note.getNoteId(),
							note.getCompanyId(), note.getUserId(),
							note.getUserName(), note.getCreateDate(),
							note.getModifiedDate(), note.getClassName(),
							note.getClassPK(), note.getContent());
					session.save(noteHBM);
					session.flush();
				}
				else {
					NoteHBM noteHBM = (NoteHBM)session.get(NoteHBM.class,
							note.getPrimaryKey());

					if (noteHBM != null) {
						noteHBM.setCompanyId(note.getCompanyId());
						noteHBM.setUserId(note.getUserId());
						noteHBM.setUserName(note.getUserName());
						noteHBM.setCreateDate(note.getCreateDate());
						noteHBM.setModifiedDate(note.getModifiedDate());
						noteHBM.setClassName(note.getClassName());
						noteHBM.setClassPK(note.getClassPK());
						noteHBM.setContent(note.getContent());
						session.flush();
					}
					else {
						noteHBM = new NoteHBM(note.getNoteId(),
								note.getCompanyId(), note.getUserId(),
								note.getUserName(), note.getCreateDate(),
								note.getModifiedDate(), note.getClassName(),
								note.getClassPK(), note.getContent());
						session.save(noteHBM);
						session.flush();
					}
				}

				note.setNew(false);
				note.setModified(false);
				note.protect();
				NotePool.put(note.getPrimaryKey(), note);
			}

			return note;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portal.model.Note findByPrimaryKey(String noteId)
		throws NoSuchNoteException, SystemException {
		com.liferay.portal.model.Note note = NotePool.get(noteId);
		Session session = null;

		try {
			if (note == null) {
				session = openSession();

				NoteHBM noteHBM = (NoteHBM)session.get(NoteHBM.class, noteId);

				if (noteHBM == null) {
					_log.warn("No Note exists with the primary key of " +
						noteId.toString());
					throw new NoSuchNoteException(noteId.toString());
				}

				note = NoteHBMUtil.model(noteHBM);
			}

			return note;
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				list.add(NoteHBMUtil.model(noteHBM));
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
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
					NoteHBM noteHBM = (NoteHBM)itr.next();
					list.add(NoteHBMUtil.model(noteHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						NoteHBM noteHBM = (NoteHBM)sr.get(0);
						list.add(NoteHBMUtil.model(noteHBM));

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

	public com.liferay.portal.model.Note findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note[] findByCompanyId_PrevAndNext(
		String noteId, String companyId, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		com.liferay.portal.model.Note note = findByPrimaryKey(noteId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portal.model.Note[] array = new com.liferay.portal.model.Note[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					NoteHBM noteHBM = (NoteHBM)sr.get(0);

					if (noteHBM == null) {
						break;
					}

					com.liferay.portal.model.Note curNote = NoteHBMUtil.model(noteHBM);
					int value = obc.compare(note, curNote);

					if (value == 0) {
						if (!note.equals(curNote)) {
							break;
						}

						array[1] = curNote;

						if (sr.previous()) {
							array[0] = NoteHBMUtil.model((NoteHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = NoteHBMUtil.model((NoteHBM)sr.get(0));
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				list.add(NoteHBMUtil.model(noteHBM));
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
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
					NoteHBM noteHBM = (NoteHBM)itr.next();
					list.add(NoteHBMUtil.model(noteHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						NoteHBM noteHBM = (NoteHBM)sr.get(0);
						list.add(NoteHBMUtil.model(noteHBM));

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

	public com.liferay.portal.model.Note findByUserId_First(String userId,
		OrderByComparator obc) throws NoSuchNoteException, SystemException {
		List list = findByUserId(userId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note findByUserId_Last(String userId,
		OrderByComparator obc) throws NoSuchNoteException, SystemException {
		int count = countByUserId(userId);
		List list = findByUserId(userId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note[] findByUserId_PrevAndNext(
		String noteId, String userId, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		com.liferay.portal.model.Note note = findByPrimaryKey(noteId);
		int count = countByUserId(userId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			com.liferay.portal.model.Note[] array = new com.liferay.portal.model.Note[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					NoteHBM noteHBM = (NoteHBM)sr.get(0);

					if (noteHBM == null) {
						break;
					}

					com.liferay.portal.model.Note curNote = NoteHBMUtil.model(noteHBM);
					int value = obc.compare(note, curNote);

					if (value == 0) {
						if (!note.equals(curNote)) {
							break;
						}

						array[1] = curNote;

						if (sr.previous()) {
							array[0] = NoteHBMUtil.model((NoteHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = NoteHBMUtil.model((NoteHBM)sr.get(0));
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

	public List findByC_C(String companyId, String className)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				list.add(NoteHBMUtil.model(noteHBM));
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

	public List findByC_C(String companyId, String className, int begin, int end)
		throws SystemException {
		return findByC_C(companyId, className, begin, end, null);
	}

	public List findByC_C(String companyId, String className, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					NoteHBM noteHBM = (NoteHBM)itr.next();
					list.add(NoteHBMUtil.model(noteHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						NoteHBM noteHBM = (NoteHBM)sr.get(0);
						list.add(NoteHBMUtil.model(noteHBM));

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

	public com.liferay.portal.model.Note findByC_C_First(String companyId,
		String className, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		List list = findByC_C(companyId, className, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note findByC_C_Last(String companyId,
		String className, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		int count = countByC_C(companyId, className);
		List list = findByC_C(companyId, className, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note[] findByC_C_PrevAndNext(
		String noteId, String companyId, String className, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		com.liferay.portal.model.Note note = findByPrimaryKey(noteId);
		int count = countByC_C(companyId, className);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);

			com.liferay.portal.model.Note[] array = new com.liferay.portal.model.Note[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					NoteHBM noteHBM = (NoteHBM)sr.get(0);

					if (noteHBM == null) {
						break;
					}

					com.liferay.portal.model.Note curNote = NoteHBMUtil.model(noteHBM);
					int value = obc.compare(note, curNote);

					if (value == 0) {
						if (!note.equals(curNote)) {
							break;
						}

						array[1] = curNote;

						if (sr.previous()) {
							array[0] = NoteHBMUtil.model((NoteHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = NoteHBMUtil.model((NoteHBM)sr.get(0));
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

	public List findByC_C_C(String companyId, String className, String classPK)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" AND ");
			query.append("classPK = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);
			q.setString(queryPos++, classPK);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				list.add(NoteHBMUtil.model(noteHBM));
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

	public List findByC_C_C(String companyId, String className, String classPK,
		int begin, int end) throws SystemException {
		return findByC_C_C(companyId, className, classPK, begin, end, null);
	}

	public List findByC_C_C(String companyId, String className, String classPK,
		int begin, int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" AND ");
			query.append("classPK = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);
			q.setString(queryPos++, classPK);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					NoteHBM noteHBM = (NoteHBM)itr.next();
					list.add(NoteHBMUtil.model(noteHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						NoteHBM noteHBM = (NoteHBM)sr.get(0);
						list.add(NoteHBMUtil.model(noteHBM));

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

	public com.liferay.portal.model.Note findByC_C_C_First(String companyId,
		String className, String classPK, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		List list = findByC_C_C(companyId, className, classPK, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note findByC_C_C_Last(String companyId,
		String className, String classPK, OrderByComparator obc)
		throws NoSuchNoteException, SystemException {
		int count = countByC_C_C(companyId, className, classPK);
		List list = findByC_C_C(companyId, className, classPK, count - 1,
				count, obc);

		if (list.size() == 0) {
			throw new NoSuchNoteException();
		}
		else {
			return (com.liferay.portal.model.Note)list.get(0);
		}
	}

	public com.liferay.portal.model.Note[] findByC_C_C_PrevAndNext(
		String noteId, String companyId, String className, String classPK,
		OrderByComparator obc) throws NoSuchNoteException, SystemException {
		com.liferay.portal.model.Note note = findByPrimaryKey(noteId);
		int count = countByC_C_C(companyId, className, classPK);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" AND ");
			query.append("classPK = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("companyId DESC").append(", ");
				query.append("className DESC").append(", ");
				query.append("classPK DESC").append(", ");
				query.append("createDate DESC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);
			q.setString(queryPos++, classPK);

			com.liferay.portal.model.Note[] array = new com.liferay.portal.model.Note[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					NoteHBM noteHBM = (NoteHBM)sr.get(0);

					if (noteHBM == null) {
						break;
					}

					com.liferay.portal.model.Note curNote = NoteHBMUtil.model(noteHBM);
					int value = obc.compare(note, curNote);

					if (value == 0) {
						if (!note.equals(curNote)) {
							break;
						}

						array[1] = curNote;

						if (sr.previous()) {
							array[0] = NoteHBMUtil.model((NoteHBM)sr.get(0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = NoteHBMUtil.model((NoteHBM)sr.get(0));
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				list.add(NoteHBMUtil.model(noteHBM));
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				NotePool.remove((String)noteHBM.getPrimaryKey());
				session.delete(noteHBM);
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("userId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, userId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				NotePool.remove((String)noteHBM.getPrimaryKey());
				session.delete(noteHBM);
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

	public void removeByC_C(String companyId, String className)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				NotePool.remove((String)noteHBM.getPrimaryKey());
				session.delete(noteHBM);
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

	public void removeByC_C_C(String companyId, String className, String classPK)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" AND ");
			query.append("classPK = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("companyId DESC").append(", ");
			query.append("className DESC").append(", ");
			query.append("classPK DESC").append(", ");
			query.append("createDate DESC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);
			q.setString(queryPos++, classPK);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				NoteHBM noteHBM = (NoteHBM)itr.next();
				NotePool.remove((String)noteHBM.getPrimaryKey());
				session.delete(noteHBM);
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
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
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
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

	public int countByC_C(String companyId, String className)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);

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

	public int countByC_C_C(String companyId, String className, String classPK)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM Note IN CLASS com.liferay.portal.service.persistence.NoteHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("className = ?");
			query.append(" AND ");
			query.append("classPK = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, className);
			q.setString(queryPos++, classPK);

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

	private static final Log _log = LogFactory.getLog(NotePersistence.class);
}