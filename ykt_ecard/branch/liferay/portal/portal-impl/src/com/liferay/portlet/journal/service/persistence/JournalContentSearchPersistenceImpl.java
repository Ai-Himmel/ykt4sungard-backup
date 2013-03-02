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

package com.liferay.portlet.journal.service.persistence;

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

import com.liferay.portlet.journal.NoSuchContentSearchException;
import com.liferay.portlet.journal.model.JournalContentSearch;
import com.liferay.portlet.journal.model.impl.JournalContentSearchImpl;
import com.liferay.portlet.journal.model.impl.JournalContentSearchModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="JournalContentSearchPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalContentSearchPersistenceImpl extends BasePersistence
	implements JournalContentSearchPersistence {
	public JournalContentSearch create(long contentSearchId) {
		JournalContentSearch journalContentSearch = new JournalContentSearchImpl();

		journalContentSearch.setNew(true);
		journalContentSearch.setPrimaryKey(contentSearchId);

		return journalContentSearch;
	}

	public JournalContentSearch remove(long contentSearchId)
		throws NoSuchContentSearchException, SystemException {
		Session session = null;

		try {
			session = openSession();

			JournalContentSearch journalContentSearch = (JournalContentSearch)session.get(JournalContentSearchImpl.class,
					new Long(contentSearchId));

			if (journalContentSearch == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No JournalContentSearch exists with the primary key " +
						contentSearchId);
				}

				throw new NoSuchContentSearchException(
					"No JournalContentSearch exists with the primary key " +
					contentSearchId);
			}

			return remove(journalContentSearch);
		}
		catch (NoSuchContentSearchException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalContentSearch remove(
		JournalContentSearch journalContentSearch) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(journalContentSearch);
		}

		journalContentSearch = removeImpl(journalContentSearch);

		if (listener != null) {
			listener.onAfterRemove(journalContentSearch);
		}

		return journalContentSearch;
	}

	protected JournalContentSearch removeImpl(
		JournalContentSearch journalContentSearch) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(journalContentSearch);

			session.flush();

			return journalContentSearch;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(JournalContentSearch.class.getName());
		}
	}

	public JournalContentSearch update(
		JournalContentSearch journalContentSearch) throws SystemException {
		return update(journalContentSearch, false);
	}

	public JournalContentSearch update(
		JournalContentSearch journalContentSearch, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = journalContentSearch.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(journalContentSearch);
			}
			else {
				listener.onBeforeUpdate(journalContentSearch);
			}
		}

		journalContentSearch = updateImpl(journalContentSearch, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(journalContentSearch);
			}
			else {
				listener.onAfterUpdate(journalContentSearch);
			}
		}

		return journalContentSearch;
	}

	public JournalContentSearch updateImpl(
		com.liferay.portlet.journal.model.JournalContentSearch journalContentSearch,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(journalContentSearch);
			}
			else {
				if (journalContentSearch.isNew()) {
					session.save(journalContentSearch);
				}
			}

			session.flush();

			journalContentSearch.setNew(false);

			return journalContentSearch;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(JournalContentSearch.class.getName());
		}
	}

	public JournalContentSearch findByPrimaryKey(long contentSearchId)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = fetchByPrimaryKey(contentSearchId);

		if (journalContentSearch == null) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"No JournalContentSearch exists with the primary key " +
					contentSearchId);
			}

			throw new NoSuchContentSearchException(
				"No JournalContentSearch exists with the primary key " +
				contentSearchId);
		}

		return journalContentSearch;
	}

	public JournalContentSearch fetchByPrimaryKey(long contentSearchId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (JournalContentSearch)session.get(JournalContentSearchImpl.class,
				new Long(contentSearchId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_P(long groupId, boolean privateLayout)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout)
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

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

	public List findByG_P(long groupId, boolean privateLayout, int begin,
		int end) throws SystemException {
		return findByG_P(groupId, privateLayout, begin, end, null);
	}

	public List findByG_P(long groupId, boolean privateLayout, int begin,
		int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

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

	public JournalContentSearch findByG_P_First(long groupId,
		boolean privateLayout, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		List list = findByG_P(groupId, privateLayout, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch findByG_P_Last(long groupId,
		boolean privateLayout, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		int count = countByG_P(groupId, privateLayout);

		List list = findByG_P(groupId, privateLayout, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch[] findByG_P_PrevAndNext(long contentSearchId,
		long groupId, boolean privateLayout, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = findByPrimaryKey(contentSearchId);

		int count = countByG_P(groupId, privateLayout);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("privateLayout = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, privateLayout);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalContentSearch);

			JournalContentSearch[] array = new JournalContentSearchImpl[3];

			array[0] = (JournalContentSearch)objArray[0];
			array[1] = (JournalContentSearch)objArray[1];
			array[2] = (JournalContentSearch)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_A(long groupId, String articleId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_A";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), articleId };

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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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

	public List findByG_A(long groupId, String articleId, int begin, int end)
		throws SystemException {
		return findByG_A(groupId, articleId, begin, end, null);
	}

	public List findByG_A(long groupId, String articleId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_A";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				articleId,
				
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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

	public JournalContentSearch findByG_A_First(long groupId, String articleId,
		OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		List list = findByG_A(groupId, articleId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch findByG_A_Last(long groupId, String articleId,
		OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		int count = countByG_A(groupId, articleId);

		List list = findByG_A(groupId, articleId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch[] findByG_A_PrevAndNext(long contentSearchId,
		long groupId, String articleId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = findByPrimaryKey(contentSearchId);

		int count = countByG_A(groupId, articleId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			if (articleId == null) {
				query.append("articleId IS NULL");
			}
			else {
				query.append("articleId = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			if (articleId != null) {
				q.setString(queryPos++, articleId);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalContentSearch);

			JournalContentSearch[] array = new JournalContentSearchImpl[3];

			array[0] = (JournalContentSearch)objArray[0];
			array[1] = (JournalContentSearch)objArray[1];
			array[2] = (JournalContentSearch)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P_L";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId)
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

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

	public List findByG_P_L(long groupId, boolean privateLayout, long layoutId,
		int begin, int end) throws SystemException {
		return findByG_P_L(groupId, privateLayout, layoutId, begin, end, null);
	}

	public List findByG_P_L(long groupId, boolean privateLayout, long layoutId,
		int begin, int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P_L";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId),
				
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

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

	public JournalContentSearch findByG_P_L_First(long groupId,
		boolean privateLayout, long layoutId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		List list = findByG_P_L(groupId, privateLayout, layoutId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("layoutId=" + layoutId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch findByG_P_L_Last(long groupId,
		boolean privateLayout, long layoutId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		int count = countByG_P_L(groupId, privateLayout, layoutId);

		List list = findByG_P_L(groupId, privateLayout, layoutId, count - 1,
				count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("layoutId=" + layoutId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch[] findByG_P_L_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		long layoutId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = findByPrimaryKey(contentSearchId);

		int count = countByG_P_L(groupId, privateLayout, layoutId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("privateLayout = ?");

			query.append(" AND ");

			query.append("layoutId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, privateLayout);

			q.setLong(queryPos++, layoutId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalContentSearch);

			JournalContentSearch[] array = new JournalContentSearchImpl[3];

			array[0] = (JournalContentSearch)objArray[0];
			array[1] = (JournalContentSearch)objArray[1];
			array[2] = (JournalContentSearch)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_P_A(long groupId, boolean privateLayout,
		String articleId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				
				articleId
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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

	public List findByG_P_A(long groupId, boolean privateLayout,
		String articleId, int begin, int end) throws SystemException {
		return findByG_P_A(groupId, privateLayout, articleId, begin, end, null);
	}

	public List findByG_P_A(long groupId, boolean privateLayout,
		String articleId, int begin, int end, OrderByComparator obc)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				
				articleId,
				
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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

	public JournalContentSearch findByG_P_A_First(long groupId,
		boolean privateLayout, String articleId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		List list = findByG_P_A(groupId, privateLayout, articleId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch findByG_P_A_Last(long groupId,
		boolean privateLayout, String articleId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		int count = countByG_P_A(groupId, privateLayout, articleId);

		List list = findByG_P_A(groupId, privateLayout, articleId, count - 1,
				count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch[] findByG_P_A_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		String articleId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = findByPrimaryKey(contentSearchId);

		int count = countByG_P_A(groupId, privateLayout, articleId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("privateLayout = ?");

			query.append(" AND ");

			if (articleId == null) {
				query.append("articleId IS NULL");
			}
			else {
				query.append("articleId = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, privateLayout);

			if (articleId != null) {
				q.setString(queryPos++, articleId);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalContentSearch);

			JournalContentSearch[] array = new JournalContentSearchImpl[3];

			array[0] = (JournalContentSearch)objArray[0];
			array[1] = (JournalContentSearch)objArray[1];
			array[2] = (JournalContentSearch)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, String portletId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P_L_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId),
				
				portletId
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" AND ");

				if (portletId == null) {
					query.append("portletId IS NULL");
				}
				else {
					query.append("portletId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

				if (portletId != null) {
					q.setString(queryPos++, portletId);
				}

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

	public List findByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, String portletId, int begin, int end)
		throws SystemException {
		return findByG_P_L_P(groupId, privateLayout, layoutId, portletId,
			begin, end, null);
	}

	public List findByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, String portletId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "findByG_P_L_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(), String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId),
				
				portletId,
				
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" AND ");

				if (portletId == null) {
					query.append("portletId IS NULL");
				}
				else {
					query.append("portletId = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

				if (portletId != null) {
					q.setString(queryPos++, portletId);
				}

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

	public JournalContentSearch findByG_P_L_P_First(long groupId,
		boolean privateLayout, long layoutId, String portletId,
		OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		List list = findByG_P_L_P(groupId, privateLayout, layoutId, portletId,
				0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("layoutId=" + layoutId);

			msg.append(", ");
			msg.append("portletId=" + portletId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch findByG_P_L_P_Last(long groupId,
		boolean privateLayout, long layoutId, String portletId,
		OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		int count = countByG_P_L_P(groupId, privateLayout, layoutId, portletId);

		List list = findByG_P_L_P(groupId, privateLayout, layoutId, portletId,
				count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("layoutId=" + layoutId);

			msg.append(", ");
			msg.append("portletId=" + portletId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchContentSearchException(msg.toString());
		}
		else {
			return (JournalContentSearch)list.get(0);
		}
	}

	public JournalContentSearch[] findByG_P_L_P_PrevAndNext(
		long contentSearchId, long groupId, boolean privateLayout,
		long layoutId, String portletId, OrderByComparator obc)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = findByPrimaryKey(contentSearchId);

		int count = countByG_P_L_P(groupId, privateLayout, layoutId, portletId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("privateLayout = ?");

			query.append(" AND ");

			query.append("layoutId = ?");

			query.append(" AND ");

			if (portletId == null) {
				query.append("portletId IS NULL");
			}
			else {
				query.append("portletId = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, privateLayout);

			q.setLong(queryPos++, layoutId);

			if (portletId != null) {
				q.setString(queryPos++, portletId);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalContentSearch);

			JournalContentSearch[] array = new JournalContentSearchImpl[3];

			array[0] = (JournalContentSearch)objArray[0];
			array[1] = (JournalContentSearch)objArray[1];
			array[2] = (JournalContentSearch)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalContentSearch findByG_P_L_P_A(long groupId,
		boolean privateLayout, long layoutId, String portletId, String articleId)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = fetchByG_P_L_P_A(groupId,
				privateLayout, layoutId, portletId, articleId);

		if (journalContentSearch == null) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalContentSearch exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("layoutId=" + layoutId);

			msg.append(", ");
			msg.append("portletId=" + portletId);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchContentSearchException(msg.toString());
		}

		return journalContentSearch;
	}

	public JournalContentSearch fetchByG_P_L_P_A(long groupId,
		boolean privateLayout, long layoutId, String portletId, String articleId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "fetchByG_P_L_P_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(), String.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId),
				
				portletId,
				
				articleId
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" AND ");

				if (portletId == null) {
					query.append("portletId IS NULL");
				}
				else {
					query.append("portletId = ?");
				}

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

				if (portletId != null) {
					q.setString(queryPos++, portletId);
				}

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (JournalContentSearch)list.get(0);
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
				return (JournalContentSearch)list.get(0);
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
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.journal.model.JournalContentSearch ");

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

	public void removeByG_P(long groupId, boolean privateLayout)
		throws SystemException {
		Iterator itr = findByG_P(groupId, privateLayout).iterator();

		while (itr.hasNext()) {
			JournalContentSearch journalContentSearch = (JournalContentSearch)itr.next();

			remove(journalContentSearch);
		}
	}

	public void removeByG_A(long groupId, String articleId)
		throws SystemException {
		Iterator itr = findByG_A(groupId, articleId).iterator();

		while (itr.hasNext()) {
			JournalContentSearch journalContentSearch = (JournalContentSearch)itr.next();

			remove(journalContentSearch);
		}
	}

	public void removeByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws SystemException {
		Iterator itr = findByG_P_L(groupId, privateLayout, layoutId).iterator();

		while (itr.hasNext()) {
			JournalContentSearch journalContentSearch = (JournalContentSearch)itr.next();

			remove(journalContentSearch);
		}
	}

	public void removeByG_P_A(long groupId, boolean privateLayout,
		String articleId) throws SystemException {
		Iterator itr = findByG_P_A(groupId, privateLayout, articleId).iterator();

		while (itr.hasNext()) {
			JournalContentSearch journalContentSearch = (JournalContentSearch)itr.next();

			remove(journalContentSearch);
		}
	}

	public void removeByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, String portletId) throws SystemException {
		Iterator itr = findByG_P_L_P(groupId, privateLayout, layoutId, portletId)
						   .iterator();

		while (itr.hasNext()) {
			JournalContentSearch journalContentSearch = (JournalContentSearch)itr.next();

			remove(journalContentSearch);
		}
	}

	public void removeByG_P_L_P_A(long groupId, boolean privateLayout,
		long layoutId, String portletId, String articleId)
		throws NoSuchContentSearchException, SystemException {
		JournalContentSearch journalContentSearch = findByG_P_L_P_A(groupId,
				privateLayout, layoutId, portletId, articleId);

		remove(journalContentSearch);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((JournalContentSearch)itr.next());
		}
	}

	public int countByG_P(long groupId, boolean privateLayout)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "countByG_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout)
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

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

	public int countByG_A(long groupId, String articleId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "countByG_A";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), articleId };

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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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

	public int countByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "countByG_P_L";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId)
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

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

	public int countByG_P_A(long groupId, boolean privateLayout,
		String articleId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "countByG_P_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				
				articleId
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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

	public int countByG_P_L_P(long groupId, boolean privateLayout,
		long layoutId, String portletId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "countByG_P_L_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId),
				
				portletId
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" AND ");

				if (portletId == null) {
					query.append("portletId IS NULL");
				}
				else {
					query.append("portletId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

				if (portletId != null) {
					q.setString(queryPos++, portletId);
				}

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

	public int countByG_P_L_P_A(long groupId, boolean privateLayout,
		long layoutId, String portletId, String articleId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
		String finderMethodName = "countByG_P_L_P_A";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(), String.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(layoutId),
				
				portletId,
				
				articleId
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
					"FROM com.liferay.portlet.journal.model.JournalContentSearch WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" AND ");

				if (portletId == null) {
					query.append("portletId IS NULL");
				}
				else {
					query.append("portletId = ?");
				}

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

				if (portletId != null) {
					q.setString(queryPos++, portletId);
				}

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

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
		boolean finderClassNameCacheEnabled = JournalContentSearchModelImpl.CACHE_ENABLED;
		String finderClassName = JournalContentSearch.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.journal.model.JournalContentSearch");

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
				"value.object.listener.com.liferay.portlet.journal.model.JournalContentSearch"));
	private static Log _log = LogFactory.getLog(JournalContentSearchPersistenceImpl.class);
}