/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.polls.NoSuchVoteException;
import com.liferay.portlet.polls.model.PollsVote;
import com.liferay.portlet.polls.model.impl.PollsVoteImpl;
import com.liferay.portlet.polls.model.impl.PollsVoteModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="PollsVotePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PollsVotePersistenceImpl extends BasePersistence
	implements PollsVotePersistence {
	public PollsVote create(long voteId) {
		PollsVote pollsVote = new PollsVoteImpl();

		pollsVote.setNew(true);
		pollsVote.setPrimaryKey(voteId);

		return pollsVote;
	}

	public PollsVote remove(long voteId)
		throws NoSuchVoteException, SystemException {
		Session session = null;

		try {
			session = openSession();

			PollsVote pollsVote = (PollsVote)session.get(PollsVoteImpl.class,
					new Long(voteId));

			if (pollsVote == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No PollsVote exists with the primary key " +
						voteId);
				}

				throw new NoSuchVoteException(
					"No PollsVote exists with the primary key " + voteId);
			}

			return remove(pollsVote);
		}
		catch (NoSuchVoteException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public PollsVote remove(PollsVote pollsVote) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(pollsVote);
		}

		pollsVote = removeImpl(pollsVote);

		if (listener != null) {
			listener.onAfterRemove(pollsVote);
		}

		return pollsVote;
	}

	protected PollsVote removeImpl(PollsVote pollsVote)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(pollsVote);

			session.flush();

			return pollsVote;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(PollsVote.class.getName());
		}
	}

	public PollsVote update(PollsVote pollsVote) throws SystemException {
		return update(pollsVote, false);
	}

	public PollsVote update(PollsVote pollsVote, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = pollsVote.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(pollsVote);
			}
			else {
				listener.onBeforeUpdate(pollsVote);
			}
		}

		pollsVote = updateImpl(pollsVote, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(pollsVote);
			}
			else {
				listener.onAfterUpdate(pollsVote);
			}
		}

		return pollsVote;
	}

	public PollsVote updateImpl(
		com.liferay.portlet.polls.model.PollsVote pollsVote, boolean merge)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(pollsVote);
			}
			else {
				if (pollsVote.isNew()) {
					session.save(pollsVote);
				}
			}

			session.flush();

			pollsVote.setNew(false);

			return pollsVote;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(PollsVote.class.getName());
		}
	}

	public PollsVote findByPrimaryKey(long voteId)
		throws NoSuchVoteException, SystemException {
		PollsVote pollsVote = fetchByPrimaryKey(voteId);

		if (pollsVote == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No PollsVote exists with the primary key " + voteId);
			}

			throw new NoSuchVoteException(
				"No PollsVote exists with the primary key " + voteId);
		}

		return pollsVote;
	}

	public PollsVote fetchByPrimaryKey(long voteId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (PollsVote)session.get(PollsVoteImpl.class, new Long(voteId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByQuestionId(long questionId) throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "findByQuestionId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(questionId) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("questionId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, questionId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public List findByQuestionId(long questionId, int begin, int end)
		throws SystemException {
		return findByQuestionId(questionId, begin, end, null);
	}

	public List findByQuestionId(long questionId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "findByQuestionId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(questionId),
				
				String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("questionId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, questionId);

				List list = QueryUtil.list(q, getDialect(), begin, end);

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public PollsVote findByQuestionId_First(long questionId,
		OrderByComparator obc) throws NoSuchVoteException, SystemException {
		List list = findByQuestionId(questionId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PollsVote exists with the key {");

			msg.append("questionId=" + questionId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchVoteException(msg.toString());
		}
		else {
			return (PollsVote)list.get(0);
		}
	}

	public PollsVote findByQuestionId_Last(long questionId,
		OrderByComparator obc) throws NoSuchVoteException, SystemException {
		int count = countByQuestionId(questionId);

		List list = findByQuestionId(questionId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PollsVote exists with the key {");

			msg.append("questionId=" + questionId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchVoteException(msg.toString());
		}
		else {
			return (PollsVote)list.get(0);
		}
	}

	public PollsVote[] findByQuestionId_PrevAndNext(long voteId,
		long questionId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		PollsVote pollsVote = findByPrimaryKey(voteId);

		int count = countByQuestionId(questionId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

			query.append("questionId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, questionId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					pollsVote);

			PollsVote[] array = new PollsVoteImpl[3];

			array[0] = (PollsVote)objArray[0];
			array[1] = (PollsVote)objArray[1];
			array[2] = (PollsVote)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByChoiceId(long choiceId) throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "findByChoiceId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(choiceId) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("choiceId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, choiceId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public List findByChoiceId(long choiceId, int begin, int end)
		throws SystemException {
		return findByChoiceId(choiceId, begin, end, null);
	}

	public List findByChoiceId(long choiceId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "findByChoiceId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(choiceId),
				
				String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("choiceId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, choiceId);

				List list = QueryUtil.list(q, getDialect(), begin, end);

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public PollsVote findByChoiceId_First(long choiceId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		List list = findByChoiceId(choiceId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PollsVote exists with the key {");

			msg.append("choiceId=" + choiceId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchVoteException(msg.toString());
		}
		else {
			return (PollsVote)list.get(0);
		}
	}

	public PollsVote findByChoiceId_Last(long choiceId, OrderByComparator obc)
		throws NoSuchVoteException, SystemException {
		int count = countByChoiceId(choiceId);

		List list = findByChoiceId(choiceId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PollsVote exists with the key {");

			msg.append("choiceId=" + choiceId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchVoteException(msg.toString());
		}
		else {
			return (PollsVote)list.get(0);
		}
	}

	public PollsVote[] findByChoiceId_PrevAndNext(long voteId, long choiceId,
		OrderByComparator obc) throws NoSuchVoteException, SystemException {
		PollsVote pollsVote = findByPrimaryKey(voteId);

		int count = countByChoiceId(choiceId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

			query.append("choiceId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, choiceId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					pollsVote);

			PollsVote[] array = new PollsVoteImpl[3];

			array[0] = (PollsVote)objArray[0];
			array[1] = (PollsVote)objArray[1];
			array[2] = (PollsVote)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public PollsVote findByQ_U(long questionId, long userId)
		throws NoSuchVoteException, SystemException {
		PollsVote pollsVote = fetchByQ_U(questionId, userId);

		if (pollsVote == null) {
			StringMaker msg = new StringMaker();

			msg.append("No PollsVote exists with the key {");

			msg.append("questionId=" + questionId);

			msg.append(", ");
			msg.append("userId=" + userId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchVoteException(msg.toString());
		}

		return pollsVote;
	}

	public PollsVote fetchByQ_U(long questionId, long userId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "fetchByQ_U";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(questionId), new Long(userId)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("questionId = ?");

				query.append(" AND ");

				query.append("userId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, questionId);

				q.setLong(queryPos++, userId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (PollsVote)list.get(0);
				}
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			List list = (List)result;

			if (list.size() == 0) {
				return null;
			}
			else {
				return (PollsVote)list.get(0);
			}
		}
	}

	public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			DynamicQuery query = queryInitializer.initialize(session);

			return query.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findWithDynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			DynamicQuery query = queryInitializer.initialize(session);

			query.setLimit(begin, end);

			return query.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		return findAll(QueryUtil.ALL_POS, QueryUtil.ALL_POS, null);
	}

	public List findAll(int begin, int end) throws SystemException {
		return findAll(begin, end, null);
	}

	public List findAll(int begin, int end, OrderByComparator obc)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "findAll";
		String[] finderParams = new String[] {
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				String.valueOf(begin), String.valueOf(end), String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("FROM com.liferay.portlet.polls.model.PollsVote ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				List list = QueryUtil.list(q, getDialect(), begin, end);

				if (obc == null) {
					Collections.sort(list);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public void removeByQuestionId(long questionId) throws SystemException {
		Iterator itr = findByQuestionId(questionId).iterator();

		while (itr.hasNext()) {
			PollsVote pollsVote = (PollsVote)itr.next();

			remove(pollsVote);
		}
	}

	public void removeByChoiceId(long choiceId) throws SystemException {
		Iterator itr = findByChoiceId(choiceId).iterator();

		while (itr.hasNext()) {
			PollsVote pollsVote = (PollsVote)itr.next();

			remove(pollsVote);
		}
	}

	public void removeByQ_U(long questionId, long userId)
		throws NoSuchVoteException, SystemException {
		PollsVote pollsVote = findByQ_U(questionId, userId);

		remove(pollsVote);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((PollsVote)itr.next());
		}
	}

	public int countByQuestionId(long questionId) throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "countByQuestionId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(questionId) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("questionId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, questionId);

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	public int countByChoiceId(long choiceId) throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "countByChoiceId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(choiceId) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("choiceId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, choiceId);

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	public int countByQ_U(long questionId, long userId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "countByQ_U";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(questionId), new Long(userId)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				StringMaker query = new StringMaker();

				query.append("SELECT COUNT(*) ");
				query.append(
					"FROM com.liferay.portlet.polls.model.PollsVote WHERE ");

				query.append("questionId = ?");

				query.append(" AND ");

				query.append("userId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, questionId);

				q.setLong(queryPos++, userId);

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	public int countAll() throws SystemException {
		boolean finderClassNameCacheEnabled = PollsVoteModelImpl.CACHE_ENABLED;
		String finderClassName = PollsVote.class.getName();
		String finderMethodName = "countAll";
		String[] finderParams = new String[] {  };
		Object[] finderArgs = new Object[] {  };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				Query q = session.createQuery(
						"SELECT COUNT(*) FROM com.liferay.portlet.polls.model.PollsVote");

				Long count = null;

				Iterator itr = q.list().iterator();

				if (itr.hasNext()) {
					count = (Long)itr.next();
				}

				if (count == null) {
					count = new Long(0);
				}

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, count);

				return count.intValue();
			}
			catch (Exception e) {
				throw HibernateUtil.processException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return ((Long)result).intValue();
		}
	}

	protected void initDao() {
	}

	private static ModelListener _getListener() {
		if (Validator.isNotNull(_LISTENER)) {
			try {
				return (ModelListener)Class.forName(_LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e);
			}
		}

		return null;
	}

	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.polls.model.PollsVote"));
	private static Log _log = LogFactory.getLog(PollsVotePersistenceImpl.class);
}