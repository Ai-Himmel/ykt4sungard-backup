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

package com.liferay.portlet.polls.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.polls.NoSuchVoteException;

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
 * <a href="PollsVotePersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class PollsVotePersistence extends BasePersistence {
	public com.liferay.portlet.polls.model.PollsVote create(
		PollsVotePK pollsVotePK) {
		return new com.liferay.portlet.polls.model.PollsVote(pollsVotePK);
	}

	public com.liferay.portlet.polls.model.PollsVote remove(
		PollsVotePK pollsVotePK) throws NoSuchVoteException, SystemException {
		Session session = null;

		try {
			session = openSession();

			PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)session.get(PollsVoteHBM.class,
					pollsVotePK);

			if (pollsVoteHBM == null) {
				_log.warn("No PollsVote exists with the primary key of " +
					pollsVotePK.toString());
				throw new NoSuchVoteException(pollsVotePK.toString());
			}

			com.liferay.portlet.polls.model.PollsVote pollsVote = PollsVoteHBMUtil.model(pollsVoteHBM);
			session.delete(pollsVoteHBM);
			session.flush();
			PollsVotePool.remove(pollsVotePK);

			return pollsVote;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.polls.model.PollsVote update(
		com.liferay.portlet.polls.model.PollsVote pollsVote)
		throws SystemException {
		Session session = null;

		try {
			if (pollsVote.isNew() || pollsVote.isModified()) {
				session = openSession();

				if (pollsVote.isNew()) {
					PollsVoteHBM pollsVoteHBM = new PollsVoteHBM(pollsVote.getQuestionId(),
							pollsVote.getUserId(), pollsVote.getChoiceId(),
							pollsVote.getVoteDate());
					session.save(pollsVoteHBM);
					session.flush();
				}
				else {
					PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)session.get(PollsVoteHBM.class,
							pollsVote.getPrimaryKey());

					if (pollsVoteHBM != null) {
						pollsVoteHBM.setChoiceId(pollsVote.getChoiceId());
						pollsVoteHBM.setVoteDate(pollsVote.getVoteDate());
						session.flush();
					}
					else {
						pollsVoteHBM = new PollsVoteHBM(pollsVote.getQuestionId(),
								pollsVote.getUserId(), pollsVote.getChoiceId(),
								pollsVote.getVoteDate());
						session.save(pollsVoteHBM);
						session.flush();
					}
				}

				pollsVote.setNew(false);
				pollsVote.setModified(false);
				pollsVote.protect();
				PollsVotePool.put(pollsVote.getPrimaryKey(), pollsVote);
			}

			return pollsVote;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.polls.model.PollsVote findByPrimaryKey(
		PollsVotePK pollsVotePK) throws NoSuchVoteException, SystemException {
		com.liferay.portlet.polls.model.PollsVote pollsVote = PollsVotePool.get(pollsVotePK);
		Session session = null;

		try {
			if (pollsVote == null) {
				session = openSession();

				PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)session.get(PollsVoteHBM.class,
						pollsVotePK);

				if (pollsVoteHBM == null) {
					_log.warn("No PollsVote exists with the primary key of " +
						pollsVotePK.toString());
					throw new NoSuchVoteException(pollsVotePK.toString());
				}

				pollsVote = PollsVoteHBMUtil.model(pollsVoteHBM);
			}

			return pollsVote;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByQuestionId(String questionId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
				list.add(PollsVoteHBMUtil.model(pollsVoteHBM));
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

	public List findByQuestionId(String questionId, int begin, int end)
		throws SystemException {
		return findByQuestionId(questionId, begin, end, null);
	}

	public List findByQuestionId(String questionId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
					list.add(PollsVoteHBMUtil.model(pollsVoteHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)sr.get(0);
						list.add(PollsVoteHBMUtil.model(pollsVoteHBM));

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

	public com.liferay.portlet.polls.model.PollsVote findByQuestionId_First(
		String questionId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		List list = findByQuestionId(questionId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchVoteException();
		}
		else {
			return (com.liferay.portlet.polls.model.PollsVote)list.get(0);
		}
	}

	public com.liferay.portlet.polls.model.PollsVote findByQuestionId_Last(
		String questionId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		int count = countByQuestionId(questionId);
		List list = findByQuestionId(questionId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchVoteException();
		}
		else {
			return (com.liferay.portlet.polls.model.PollsVote)list.get(0);
		}
	}

	public com.liferay.portlet.polls.model.PollsVote[] findByQuestionId_PrevAndNext(
		PollsVotePK pollsVotePK, String questionId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		com.liferay.portlet.polls.model.PollsVote pollsVote = findByPrimaryKey(pollsVotePK);
		int count = countByQuestionId(questionId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);

			com.liferay.portlet.polls.model.PollsVote[] array = new com.liferay.portlet.polls.model.PollsVote[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)sr.get(0);

					if (pollsVoteHBM == null) {
						break;
					}

					com.liferay.portlet.polls.model.PollsVote curPollsVote = PollsVoteHBMUtil.model(pollsVoteHBM);
					int value = obc.compare(pollsVote, curPollsVote);

					if (value == 0) {
						if (!pollsVote.equals(curPollsVote)) {
							break;
						}

						array[1] = curPollsVote;

						if (sr.previous()) {
							array[0] = PollsVoteHBMUtil.model((PollsVoteHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = PollsVoteHBMUtil.model((PollsVoteHBM)sr.get(
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

	public List findByQ_C(String questionId, String choiceId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" AND ");
			query.append("choiceId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);
			q.setString(queryPos++, choiceId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
				list.add(PollsVoteHBMUtil.model(pollsVoteHBM));
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

	public List findByQ_C(String questionId, String choiceId, int begin, int end)
		throws SystemException {
		return findByQ_C(questionId, choiceId, begin, end, null);
	}

	public List findByQ_C(String questionId, String choiceId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" AND ");
			query.append("choiceId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);
			q.setString(queryPos++, choiceId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
					list.add(PollsVoteHBMUtil.model(pollsVoteHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)sr.get(0);
						list.add(PollsVoteHBMUtil.model(pollsVoteHBM));

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

	public com.liferay.portlet.polls.model.PollsVote findByQ_C_First(
		String questionId, String choiceId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		List list = findByQ_C(questionId, choiceId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchVoteException();
		}
		else {
			return (com.liferay.portlet.polls.model.PollsVote)list.get(0);
		}
	}

	public com.liferay.portlet.polls.model.PollsVote findByQ_C_Last(
		String questionId, String choiceId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		int count = countByQ_C(questionId, choiceId);
		List list = findByQ_C(questionId, choiceId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchVoteException();
		}
		else {
			return (com.liferay.portlet.polls.model.PollsVote)list.get(0);
		}
	}

	public com.liferay.portlet.polls.model.PollsVote[] findByQ_C_PrevAndNext(
		PollsVotePK pollsVotePK, String questionId, String choiceId,
		OrderByComparator obc) throws NoSuchVoteException, SystemException {
		com.liferay.portlet.polls.model.PollsVote pollsVote = findByPrimaryKey(pollsVotePK);
		int count = countByQ_C(questionId, choiceId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" AND ");
			query.append("choiceId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);
			q.setString(queryPos++, choiceId);

			com.liferay.portlet.polls.model.PollsVote[] array = new com.liferay.portlet.polls.model.PollsVote[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)sr.get(0);

					if (pollsVoteHBM == null) {
						break;
					}

					com.liferay.portlet.polls.model.PollsVote curPollsVote = PollsVoteHBMUtil.model(pollsVoteHBM);
					int value = obc.compare(pollsVote, curPollsVote);

					if (value == 0) {
						if (!pollsVote.equals(curPollsVote)) {
							break;
						}

						array[1] = curPollsVote;

						if (sr.previous()) {
							array[0] = PollsVoteHBMUtil.model((PollsVoteHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = PollsVoteHBMUtil.model((PollsVoteHBM)sr.get(
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
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM ");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
				list.add(PollsVoteHBMUtil.model(pollsVoteHBM));
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

	public void removeByQuestionId(String questionId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
				PollsVotePool.remove((PollsVotePK)pollsVoteHBM.getPrimaryKey());
				session.delete(pollsVoteHBM);
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

	public void removeByQ_C(String questionId, String choiceId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" AND ");
			query.append("choiceId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);
			q.setString(queryPos++, choiceId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				PollsVoteHBM pollsVoteHBM = (PollsVoteHBM)itr.next();
				PollsVotePool.remove((PollsVotePK)pollsVoteHBM.getPrimaryKey());
				session.delete(pollsVoteHBM);
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

	public int countByQuestionId(String questionId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);

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

	public int countByQ_C(String questionId, String choiceId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM PollsVote IN CLASS com.liferay.portlet.polls.service.persistence.PollsVoteHBM WHERE ");
			query.append("questionId = ?");
			query.append(" AND ");
			query.append("choiceId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, questionId);
			q.setString(queryPos++, choiceId);

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

	private static final Log _log = LogFactory.getLog(PollsVotePersistence.class);
}