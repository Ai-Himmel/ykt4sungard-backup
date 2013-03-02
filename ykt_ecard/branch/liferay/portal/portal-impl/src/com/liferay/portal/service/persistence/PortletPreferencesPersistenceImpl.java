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

import com.liferay.portal.NoSuchPortletPreferencesException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.model.impl.PortletPreferencesImpl;
import com.liferay.portal.model.impl.PortletPreferencesModelImpl;
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
 * <a href="PortletPreferencesPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPreferencesPersistenceImpl extends BasePersistence
	implements PortletPreferencesPersistence {
	public PortletPreferences create(long portletPreferencesId) {
		PortletPreferences portletPreferences = new PortletPreferencesImpl();

		portletPreferences.setNew(true);
		portletPreferences.setPrimaryKey(portletPreferencesId);

		return portletPreferences;
	}

	public PortletPreferences remove(long portletPreferencesId)
		throws NoSuchPortletPreferencesException, SystemException {
		Session session = null;

		try {
			session = openSession();

			PortletPreferences portletPreferences = (PortletPreferences)session.get(PortletPreferencesImpl.class,
					new Long(portletPreferencesId));

			if (portletPreferences == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No PortletPreferences exists with the primary key " +
						portletPreferencesId);
				}

				throw new NoSuchPortletPreferencesException(
					"No PortletPreferences exists with the primary key " +
					portletPreferencesId);
			}

			return remove(portletPreferences);
		}
		catch (NoSuchPortletPreferencesException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public PortletPreferences remove(PortletPreferences portletPreferences)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(portletPreferences);
		}

		portletPreferences = removeImpl(portletPreferences);

		if (listener != null) {
			listener.onAfterRemove(portletPreferences);
		}

		return portletPreferences;
	}

	protected PortletPreferences removeImpl(
		PortletPreferences portletPreferences) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(portletPreferences);

			session.flush();

			return portletPreferences;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(PortletPreferences.class.getName());
		}
	}

	public PortletPreferences update(PortletPreferences portletPreferences)
		throws SystemException {
		return update(portletPreferences, false);
	}

	public PortletPreferences update(PortletPreferences portletPreferences,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = portletPreferences.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(portletPreferences);
			}
			else {
				listener.onBeforeUpdate(portletPreferences);
			}
		}

		portletPreferences = updateImpl(portletPreferences, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(portletPreferences);
			}
			else {
				listener.onAfterUpdate(portletPreferences);
			}
		}

		return portletPreferences;
	}

	public PortletPreferences updateImpl(
		com.liferay.portal.model.PortletPreferences portletPreferences,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(portletPreferences);
			}
			else {
				if (portletPreferences.isNew()) {
					session.save(portletPreferences);
				}
			}

			session.flush();

			portletPreferences.setNew(false);

			return portletPreferences;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(PortletPreferences.class.getName());
		}
	}

	public PortletPreferences findByPrimaryKey(long portletPreferencesId)
		throws NoSuchPortletPreferencesException, SystemException {
		PortletPreferences portletPreferences = fetchByPrimaryKey(portletPreferencesId);

		if (portletPreferences == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No PortletPreferences exists with the primary key " +
					portletPreferencesId);
			}

			throw new NoSuchPortletPreferencesException(
				"No PortletPreferences exists with the primary key " +
				portletPreferencesId);
		}

		return portletPreferences;
	}

	public PortletPreferences fetchByPrimaryKey(long portletPreferencesId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (PortletPreferences)session.get(PortletPreferencesImpl.class,
				new Long(portletPreferencesId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByPlid(long plid) throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "findByPlid";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(plid) };

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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("plid = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, plid);

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

	public List findByPlid(long plid, int begin, int end)
		throws SystemException {
		return findByPlid(plid, begin, end, null);
	}

	public List findByPlid(long plid, int begin, int end, OrderByComparator obc)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "findByPlid";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(plid),
				
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("plid = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, plid);

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

	public PortletPreferences findByPlid_First(long plid, OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		List list = findByPlid(plid, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("plid=" + plid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPortletPreferencesException(msg.toString());
		}
		else {
			return (PortletPreferences)list.get(0);
		}
	}

	public PortletPreferences findByPlid_Last(long plid, OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		int count = countByPlid(plid);

		List list = findByPlid(plid, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("plid=" + plid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPortletPreferencesException(msg.toString());
		}
		else {
			return (PortletPreferences)list.get(0);
		}
	}

	public PortletPreferences[] findByPlid_PrevAndNext(
		long portletPreferencesId, long plid, OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		PortletPreferences portletPreferences = findByPrimaryKey(portletPreferencesId);

		int count = countByPlid(plid);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portal.model.PortletPreferences WHERE ");

			query.append("plid = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, plid);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					portletPreferences);

			PortletPreferences[] array = new PortletPreferencesImpl[3];

			array[0] = (PortletPreferences)objArray[0];
			array[1] = (PortletPreferences)objArray[1];
			array[2] = (PortletPreferences)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByP_P(long plid, String portletId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "findByP_P";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(plid), portletId };

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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("plid = ?");

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

				q.setLong(queryPos++, plid);

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

	public List findByP_P(long plid, String portletId, int begin, int end)
		throws SystemException {
		return findByP_P(plid, portletId, begin, end, null);
	}

	public List findByP_P(long plid, String portletId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "findByP_P";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(plid),
				
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("plid = ?");

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

				q.setLong(queryPos++, plid);

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

	public PortletPreferences findByP_P_First(long plid, String portletId,
		OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		List list = findByP_P(plid, portletId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("plid=" + plid);

			msg.append(", ");
			msg.append("portletId=" + portletId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPortletPreferencesException(msg.toString());
		}
		else {
			return (PortletPreferences)list.get(0);
		}
	}

	public PortletPreferences findByP_P_Last(long plid, String portletId,
		OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		int count = countByP_P(plid, portletId);

		List list = findByP_P(plid, portletId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("plid=" + plid);

			msg.append(", ");
			msg.append("portletId=" + portletId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPortletPreferencesException(msg.toString());
		}
		else {
			return (PortletPreferences)list.get(0);
		}
	}

	public PortletPreferences[] findByP_P_PrevAndNext(
		long portletPreferencesId, long plid, String portletId,
		OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		PortletPreferences portletPreferences = findByPrimaryKey(portletPreferencesId);

		int count = countByP_P(plid, portletId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portal.model.PortletPreferences WHERE ");

			query.append("plid = ?");

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

			q.setLong(queryPos++, plid);

			if (portletId != null) {
				q.setString(queryPos++, portletId);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					portletPreferences);

			PortletPreferences[] array = new PortletPreferencesImpl[3];

			array[0] = (PortletPreferences)objArray[0];
			array[1] = (PortletPreferences)objArray[1];
			array[2] = (PortletPreferences)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByO_O_P(long ownerId, int ownerType, long plid)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "findByO_O_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(ownerId), new Integer(ownerType), new Long(plid)
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("ownerId = ?");

				query.append(" AND ");

				query.append("ownerType = ?");

				query.append(" AND ");

				query.append("plid = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, ownerId);

				q.setInteger(queryPos++, ownerType);

				q.setLong(queryPos++, plid);

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

	public List findByO_O_P(long ownerId, int ownerType, long plid, int begin,
		int end) throws SystemException {
		return findByO_O_P(ownerId, ownerType, plid, begin, end, null);
	}

	public List findByO_O_P(long ownerId, int ownerType, long plid, int begin,
		int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "findByO_O_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(ownerId), new Integer(ownerType), new Long(plid),
				
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("ownerId = ?");

				query.append(" AND ");

				query.append("ownerType = ?");

				query.append(" AND ");

				query.append("plid = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, ownerId);

				q.setInteger(queryPos++, ownerType);

				q.setLong(queryPos++, plid);

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

	public PortletPreferences findByO_O_P_First(long ownerId, int ownerType,
		long plid, OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		List list = findByO_O_P(ownerId, ownerType, plid, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("ownerId=" + ownerId);

			msg.append(", ");
			msg.append("ownerType=" + ownerType);

			msg.append(", ");
			msg.append("plid=" + plid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPortletPreferencesException(msg.toString());
		}
		else {
			return (PortletPreferences)list.get(0);
		}
	}

	public PortletPreferences findByO_O_P_Last(long ownerId, int ownerType,
		long plid, OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		int count = countByO_O_P(ownerId, ownerType, plid);

		List list = findByO_O_P(ownerId, ownerType, plid, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("ownerId=" + ownerId);

			msg.append(", ");
			msg.append("ownerType=" + ownerType);

			msg.append(", ");
			msg.append("plid=" + plid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPortletPreferencesException(msg.toString());
		}
		else {
			return (PortletPreferences)list.get(0);
		}
	}

	public PortletPreferences[] findByO_O_P_PrevAndNext(
		long portletPreferencesId, long ownerId, int ownerType, long plid,
		OrderByComparator obc)
		throws NoSuchPortletPreferencesException, SystemException {
		PortletPreferences portletPreferences = findByPrimaryKey(portletPreferencesId);

		int count = countByO_O_P(ownerId, ownerType, plid);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portal.model.PortletPreferences WHERE ");

			query.append("ownerId = ?");

			query.append(" AND ");

			query.append("ownerType = ?");

			query.append(" AND ");

			query.append("plid = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, ownerId);

			q.setInteger(queryPos++, ownerType);

			q.setLong(queryPos++, plid);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					portletPreferences);

			PortletPreferences[] array = new PortletPreferencesImpl[3];

			array[0] = (PortletPreferences)objArray[0];
			array[1] = (PortletPreferences)objArray[1];
			array[2] = (PortletPreferences)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public PortletPreferences findByO_O_P_P(long ownerId, int ownerType,
		long plid, String portletId)
		throws NoSuchPortletPreferencesException, SystemException {
		PortletPreferences portletPreferences = fetchByO_O_P_P(ownerId,
				ownerType, plid, portletId);

		if (portletPreferences == null) {
			StringMaker msg = new StringMaker();

			msg.append("No PortletPreferences exists with the key {");

			msg.append("ownerId=" + ownerId);

			msg.append(", ");
			msg.append("ownerType=" + ownerType);

			msg.append(", ");
			msg.append("plid=" + plid);

			msg.append(", ");
			msg.append("portletId=" + portletId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchPortletPreferencesException(msg.toString());
		}

		return portletPreferences;
	}

	public PortletPreferences fetchByO_O_P_P(long ownerId, int ownerType,
		long plid, String portletId) throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "fetchByO_O_P_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(ownerId), new Integer(ownerType), new Long(plid),
				
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("ownerId = ?");

				query.append(" AND ");

				query.append("ownerType = ?");

				query.append(" AND ");

				query.append("plid = ?");

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

				q.setLong(queryPos++, ownerId);

				q.setInteger(queryPos++, ownerType);

				q.setLong(queryPos++, plid);

				if (portletId != null) {
					q.setString(queryPos++, portletId);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (PortletPreferences)list.get(0);
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
				return (PortletPreferences)list.get(0);
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
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
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
					"FROM com.liferay.portal.model.PortletPreferences ");

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

	public void removeByPlid(long plid) throws SystemException {
		Iterator itr = findByPlid(plid).iterator();

		while (itr.hasNext()) {
			PortletPreferences portletPreferences = (PortletPreferences)itr.next();

			remove(portletPreferences);
		}
	}

	public void removeByP_P(long plid, String portletId)
		throws SystemException {
		Iterator itr = findByP_P(plid, portletId).iterator();

		while (itr.hasNext()) {
			PortletPreferences portletPreferences = (PortletPreferences)itr.next();

			remove(portletPreferences);
		}
	}

	public void removeByO_O_P(long ownerId, int ownerType, long plid)
		throws SystemException {
		Iterator itr = findByO_O_P(ownerId, ownerType, plid).iterator();

		while (itr.hasNext()) {
			PortletPreferences portletPreferences = (PortletPreferences)itr.next();

			remove(portletPreferences);
		}
	}

	public void removeByO_O_P_P(long ownerId, int ownerType, long plid,
		String portletId)
		throws NoSuchPortletPreferencesException, SystemException {
		PortletPreferences portletPreferences = findByO_O_P_P(ownerId,
				ownerType, plid, portletId);

		remove(portletPreferences);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((PortletPreferences)itr.next());
		}
	}

	public int countByPlid(long plid) throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "countByPlid";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(plid) };

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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("plid = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, plid);

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

	public int countByP_P(long plid, String portletId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "countByP_P";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(plid), portletId };

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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("plid = ?");

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

				q.setLong(queryPos++, plid);

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

	public int countByO_O_P(long ownerId, int ownerType, long plid)
		throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "countByO_O_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(ownerId), new Integer(ownerType), new Long(plid)
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("ownerId = ?");

				query.append(" AND ");

				query.append("ownerType = ?");

				query.append(" AND ");

				query.append("plid = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, ownerId);

				q.setInteger(queryPos++, ownerType);

				q.setLong(queryPos++, plid);

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

	public int countByO_O_P_P(long ownerId, int ownerType, long plid,
		String portletId) throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
		String finderMethodName = "countByO_O_P_P";
		String[] finderParams = new String[] {
				Long.class.getName(), Integer.class.getName(),
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(ownerId), new Integer(ownerType), new Long(plid),
				
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
					"FROM com.liferay.portal.model.PortletPreferences WHERE ");

				query.append("ownerId = ?");

				query.append(" AND ");

				query.append("ownerType = ?");

				query.append(" AND ");

				query.append("plid = ?");

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

				q.setLong(queryPos++, ownerId);

				q.setInteger(queryPos++, ownerType);

				q.setLong(queryPos++, plid);

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

	public int countAll() throws SystemException {
		boolean finderClassNameCacheEnabled = PortletPreferencesModelImpl.CACHE_ENABLED;
		String finderClassName = PortletPreferences.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.PortletPreferences");

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
				"value.object.listener.com.liferay.portal.model.PortletPreferences"));
	private static Log _log = LogFactory.getLog(PortletPreferencesPersistenceImpl.class);
}