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

package com.liferay.portal.service.persistence;

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.LayoutModelImpl;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="LayoutPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutPersistenceImpl extends BasePersistence
	implements LayoutPersistence {
	public Layout create(long plid) {
		Layout layout = new LayoutImpl();

		layout.setNew(true);
		layout.setPrimaryKey(plid);

		return layout;
	}

	public Layout remove(long plid)
		throws NoSuchLayoutException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Layout layout = (Layout)session.get(LayoutImpl.class, new Long(plid));

			if (layout == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Layout exists with the primary key " + plid);
				}

				throw new NoSuchLayoutException(
					"No Layout exists with the primary key " + plid);
			}

			return remove(layout);
		}
		catch (NoSuchLayoutException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Layout remove(Layout layout) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(layout);
		}

		layout = removeImpl(layout);

		if (listener != null) {
			listener.onAfterRemove(layout);
		}

		return layout;
	}

	protected Layout removeImpl(Layout layout) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(layout);

			session.flush();

			return layout;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Layout.class.getName());
		}
	}

	public Layout update(Layout layout) throws SystemException {
		return update(layout, false);
	}

	public Layout update(Layout layout, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = layout.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(layout);
			}
			else {
				listener.onBeforeUpdate(layout);
			}
		}

		layout = updateImpl(layout, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(layout);
			}
			else {
				listener.onAfterUpdate(layout);
			}
		}

		return layout;
	}

	public Layout updateImpl(com.liferay.portal.model.Layout layout,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(layout);
			}
			else {
				if (layout.isNew()) {
					session.save(layout);
				}
			}

			session.flush();

			layout.setNew(false);

			return layout;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Layout.class.getName());
		}
	}

	public Layout findByPrimaryKey(long plid)
		throws NoSuchLayoutException, SystemException {
		Layout layout = fetchByPrimaryKey(plid);

		if (layout == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Layout exists with the primary key " + plid);
			}

			throw new NoSuchLayoutException(
				"No Layout exists with the primary key " + plid);
		}

		return layout;
	}

	public Layout fetchByPrimaryKey(long plid) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Layout)session.get(LayoutImpl.class, new Long(plid));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "findByGroupId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(groupId) };

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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

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

	public List findByGroupId(long groupId, int begin, int end)
		throws SystemException {
		return findByGroupId(groupId, begin, end, null);
	}

	public List findByGroupId(long groupId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "findByGroupId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("parentLayoutId ASC, ");
					query.append("priority ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

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

	public Layout findByGroupId_First(long groupId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout findByGroupId_Last(long groupId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout[] findByGroupId_PrevAndNext(long plid, long groupId,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		Layout layout = findByPrimaryKey(plid);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Layout WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, layout);

			Layout[] array = new LayoutImpl[3];

			array[0] = (Layout)objArray[0];
			array[1] = (Layout)objArray[1];
			array[2] = (Layout)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "findByCompanyId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(companyId) };

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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

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

	public List findByCompanyId(long companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(long companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "findByCompanyId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId),
				
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("parentLayoutId ASC, ");
					query.append("priority ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

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

	public Layout findByCompanyId_First(long companyId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout findByCompanyId_Last(long companyId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		int count = countByCompanyId(companyId);

		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout[] findByCompanyId_PrevAndNext(long plid, long companyId,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		Layout layout = findByPrimaryKey(plid);

		int count = countByCompanyId(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Layout WHERE ");

			query.append("companyId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, layout);

			Layout[] array = new LayoutImpl[3];

			array[0] = (Layout)objArray[0];
			array[1] = (Layout)objArray[1];
			array[2] = (Layout)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Layout findByDLFolderId(long dlFolderId)
		throws NoSuchLayoutException, SystemException {
		Layout layout = fetchByDLFolderId(dlFolderId);

		if (layout == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("dlFolderId=" + dlFolderId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchLayoutException(msg.toString());
		}

		return layout;
	}

	public Layout fetchByDLFolderId(long dlFolderId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "fetchByDLFolderId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(dlFolderId) };

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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("dlFolderId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, dlFolderId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Layout)list.get(0);
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
				return (Layout)list.get(0);
			}
		}
	}

	public Layout findByIconImageId(long iconImageId)
		throws NoSuchLayoutException, SystemException {
		Layout layout = fetchByIconImageId(iconImageId);

		if (layout == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("iconImageId=" + iconImageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchLayoutException(msg.toString());
		}

		return layout;
	}

	public Layout fetchByIconImageId(long iconImageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "fetchByIconImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(iconImageId) };

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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("iconImageId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, iconImageId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Layout)list.get(0);
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
				return (Layout)list.get(0);
			}
		}
	}

	public List findByG_P(long groupId, boolean privateLayout)
		throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

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
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("parentLayoutId ASC, ");
					query.append("priority ASC");
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

	public Layout findByG_P_First(long groupId, boolean privateLayout,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		List list = findByG_P(groupId, privateLayout, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout findByG_P_Last(long groupId, boolean privateLayout,
		OrderByComparator obc) throws NoSuchLayoutException, SystemException {
		int count = countByG_P(groupId, privateLayout);

		List list = findByG_P(groupId, privateLayout, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout[] findByG_P_PrevAndNext(long plid, long groupId,
		boolean privateLayout, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		Layout layout = findByPrimaryKey(plid);

		int count = countByG_P(groupId, privateLayout);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Layout WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("privateLayout = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, privateLayout);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, layout);

			Layout[] array = new LayoutImpl[3];

			array[0] = (Layout)objArray[0];
			array[1] = (Layout)objArray[1];
			array[2] = (Layout)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Layout findByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws NoSuchLayoutException, SystemException {
		Layout layout = fetchByG_P_L(groupId, privateLayout, layoutId);

		if (layout == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("layoutId=" + layoutId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchLayoutException(msg.toString());
		}

		return layout;
	}

	public Layout fetchByG_P_L(long groupId, boolean privateLayout,
		long layoutId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "fetchByG_P_L";
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("layoutId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, layoutId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Layout)list.get(0);
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
				return (Layout)list.get(0);
			}
		}
	}

	public List findByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "findByG_P_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(parentLayoutId)
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("parentLayoutId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, parentLayoutId);

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

	public List findByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId, int begin, int end) throws SystemException {
		return findByG_P_P(groupId, privateLayout, parentLayoutId, begin, end,
			null);
	}

	public List findByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId, int begin, int end, OrderByComparator obc)
		throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "findByG_P_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(parentLayoutId),
				
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("parentLayoutId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("parentLayoutId ASC, ");
					query.append("priority ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, parentLayoutId);

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

	public Layout findByG_P_P_First(long groupId, boolean privateLayout,
		long parentLayoutId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		List list = findByG_P_P(groupId, privateLayout, parentLayoutId, 0, 1,
				obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("parentLayoutId=" + parentLayoutId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout findByG_P_P_Last(long groupId, boolean privateLayout,
		long parentLayoutId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		int count = countByG_P_P(groupId, privateLayout, parentLayoutId);

		List list = findByG_P_P(groupId, privateLayout, parentLayoutId,
				count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("parentLayoutId=" + parentLayoutId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchLayoutException(msg.toString());
		}
		else {
			return (Layout)list.get(0);
		}
	}

	public Layout[] findByG_P_P_PrevAndNext(long plid, long groupId,
		boolean privateLayout, long parentLayoutId, OrderByComparator obc)
		throws NoSuchLayoutException, SystemException {
		Layout layout = findByPrimaryKey(plid);

		int count = countByG_P_P(groupId, privateLayout, parentLayoutId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Layout WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			query.append("privateLayout = ?");

			query.append(" AND ");

			query.append("parentLayoutId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			q.setBoolean(queryPos++, privateLayout);

			q.setLong(queryPos++, parentLayoutId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, layout);

			Layout[] array = new LayoutImpl[3];

			array[0] = (Layout)objArray[0];
			array[1] = (Layout)objArray[1];
			array[2] = (Layout)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Layout findByG_P_F(long groupId, boolean privateLayout,
		String friendlyURL) throws NoSuchLayoutException, SystemException {
		Layout layout = fetchByG_P_F(groupId, privateLayout, friendlyURL);

		if (layout == null) {
			StringMaker msg = new StringMaker();

			msg.append("No Layout exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("privateLayout=" + privateLayout);

			msg.append(", ");
			msg.append("friendlyURL=" + friendlyURL);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchLayoutException(msg.toString());
		}

		return layout;
	}

	public Layout fetchByG_P_F(long groupId, boolean privateLayout,
		String friendlyURL) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "fetchByG_P_F";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				
				friendlyURL
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

				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				if (friendlyURL == null) {
					query.append("friendlyURL IS NULL");
				}
				else {
					query.append("lower(friendlyURL) = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("parentLayoutId ASC, ");
				query.append("priority ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				if (friendlyURL != null) {
					q.setString(queryPos++, friendlyURL);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (Layout)list.get(0);
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
				return (Layout)list.get(0);
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
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
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

				query.append("FROM com.liferay.portal.model.Layout ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("parentLayoutId ASC, ");
					query.append("priority ASC");
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

	public void removeByGroupId(long groupId) throws SystemException {
		Iterator itr = findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			remove(layout);
		}
	}

	public void removeByCompanyId(long companyId) throws SystemException {
		Iterator itr = findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			remove(layout);
		}
	}

	public void removeByDLFolderId(long dlFolderId)
		throws NoSuchLayoutException, SystemException {
		Layout layout = findByDLFolderId(dlFolderId);

		remove(layout);
	}

	public void removeByIconImageId(long iconImageId)
		throws NoSuchLayoutException, SystemException {
		Layout layout = findByIconImageId(iconImageId);

		remove(layout);
	}

	public void removeByG_P(long groupId, boolean privateLayout)
		throws SystemException {
		Iterator itr = findByG_P(groupId, privateLayout).iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			remove(layout);
		}
	}

	public void removeByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws NoSuchLayoutException, SystemException {
		Layout layout = findByG_P_L(groupId, privateLayout, layoutId);

		remove(layout);
	}

	public void removeByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId) throws SystemException {
		Iterator itr = findByG_P_P(groupId, privateLayout, parentLayoutId)
						   .iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout)itr.next();

			remove(layout);
		}
	}

	public void removeByG_P_F(long groupId, boolean privateLayout,
		String friendlyURL) throws NoSuchLayoutException, SystemException {
		Layout layout = findByG_P_F(groupId, privateLayout, friendlyURL);

		remove(layout);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Layout)itr.next());
		}
	}

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "countByGroupId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(groupId) };

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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

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

	public int countByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "countByCompanyId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(companyId) };

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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

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

	public int countByDLFolderId(long dlFolderId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "countByDLFolderId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(dlFolderId) };

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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("dlFolderId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, dlFolderId);

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

	public int countByIconImageId(long iconImageId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "countByIconImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(iconImageId) };

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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("iconImageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, iconImageId);

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

	public int countByG_P(long groupId, boolean privateLayout)
		throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

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

	public int countByG_P_L(long groupId, boolean privateLayout, long layoutId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

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

	public int countByG_P_P(long groupId, boolean privateLayout,
		long parentLayoutId) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "countByG_P_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				new Long(parentLayoutId)
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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				query.append("parentLayoutId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				q.setLong(queryPos++, parentLayoutId);

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

	public int countByG_P_F(long groupId, boolean privateLayout,
		String friendlyURL) throws SystemException {
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
		String finderMethodName = "countByG_P_F";
		String[] finderParams = new String[] {
				Long.class.getName(), Boolean.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId), Boolean.valueOf(privateLayout),
				
				friendlyURL
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
				query.append("FROM com.liferay.portal.model.Layout WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				query.append("privateLayout = ?");

				query.append(" AND ");

				if (friendlyURL == null) {
					query.append("friendlyURL IS NULL");
				}
				else {
					query.append("lower(friendlyURL) = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				q.setBoolean(queryPos++, privateLayout);

				if (friendlyURL != null) {
					q.setString(queryPos++, friendlyURL);
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
		boolean finderClassNameCacheEnabled = LayoutModelImpl.CACHE_ENABLED;
		String finderClassName = Layout.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Layout");

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
				"value.object.listener.com.liferay.portal.model.Layout"));
	private static Log _log = LogFactory.getLog(LayoutPersistenceImpl.class);
}