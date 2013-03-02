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

package com.liferay.portlet.documentlibrary.service.persistence;

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

import com.liferay.portlet.documentlibrary.NoSuchFileVersionException;
import com.liferay.portlet.documentlibrary.model.DLFileVersion;
import com.liferay.portlet.documentlibrary.model.impl.DLFileVersionImpl;
import com.liferay.portlet.documentlibrary.model.impl.DLFileVersionModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="DLFileVersionPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DLFileVersionPersistenceImpl extends BasePersistence
	implements DLFileVersionPersistence {
	public DLFileVersion create(long fileVersionId) {
		DLFileVersion dlFileVersion = new DLFileVersionImpl();

		dlFileVersion.setNew(true);
		dlFileVersion.setPrimaryKey(fileVersionId);

		return dlFileVersion;
	}

	public DLFileVersion remove(long fileVersionId)
		throws NoSuchFileVersionException, SystemException {
		Session session = null;

		try {
			session = openSession();

			DLFileVersion dlFileVersion = (DLFileVersion)session.get(DLFileVersionImpl.class,
					new Long(fileVersionId));

			if (dlFileVersion == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No DLFileVersion exists with the primary key " +
						fileVersionId);
				}

				throw new NoSuchFileVersionException(
					"No DLFileVersion exists with the primary key " +
					fileVersionId);
			}

			return remove(dlFileVersion);
		}
		catch (NoSuchFileVersionException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public DLFileVersion remove(DLFileVersion dlFileVersion)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(dlFileVersion);
		}

		dlFileVersion = removeImpl(dlFileVersion);

		if (listener != null) {
			listener.onAfterRemove(dlFileVersion);
		}

		return dlFileVersion;
	}

	protected DLFileVersion removeImpl(DLFileVersion dlFileVersion)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(dlFileVersion);

			session.flush();

			return dlFileVersion;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(DLFileVersion.class.getName());
		}
	}

	public DLFileVersion update(DLFileVersion dlFileVersion)
		throws SystemException {
		return update(dlFileVersion, false);
	}

	public DLFileVersion update(DLFileVersion dlFileVersion, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = dlFileVersion.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(dlFileVersion);
			}
			else {
				listener.onBeforeUpdate(dlFileVersion);
			}
		}

		dlFileVersion = updateImpl(dlFileVersion, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(dlFileVersion);
			}
			else {
				listener.onAfterUpdate(dlFileVersion);
			}
		}

		return dlFileVersion;
	}

	public DLFileVersion updateImpl(
		com.liferay.portlet.documentlibrary.model.DLFileVersion dlFileVersion,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(dlFileVersion);
			}
			else {
				if (dlFileVersion.isNew()) {
					session.save(dlFileVersion);
				}
			}

			session.flush();

			dlFileVersion.setNew(false);

			return dlFileVersion;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(DLFileVersion.class.getName());
		}
	}

	public DLFileVersion findByPrimaryKey(long fileVersionId)
		throws NoSuchFileVersionException, SystemException {
		DLFileVersion dlFileVersion = fetchByPrimaryKey(fileVersionId);

		if (dlFileVersion == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No DLFileVersion exists with the primary key " +
					fileVersionId);
			}

			throw new NoSuchFileVersionException(
				"No DLFileVersion exists with the primary key " +
				fileVersionId);
		}

		return dlFileVersion;
	}

	public DLFileVersion fetchByPrimaryKey(long fileVersionId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (DLFileVersion)session.get(DLFileVersionImpl.class,
				new Long(fileVersionId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByF_N(long folderId, String name) throws SystemException {
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
		String finderMethodName = "findByF_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(folderId), name };

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
					"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion WHERE ");

				query.append("folderId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("folderId DESC, ");
				query.append("name DESC, ");
				query.append("version DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				if (name != null) {
					q.setString(queryPos++, name);
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

	public List findByF_N(long folderId, String name, int begin, int end)
		throws SystemException {
		return findByF_N(folderId, name, begin, end, null);
	}

	public List findByF_N(long folderId, String name, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
		String finderMethodName = "findByF_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(folderId),
				
				name,
				
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
					"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion WHERE ");

				query.append("folderId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("folderId DESC, ");
					query.append("name DESC, ");
					query.append("version DESC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				if (name != null) {
					q.setString(queryPos++, name);
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

	public DLFileVersion findByF_N_First(long folderId, String name,
		OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		List list = findByF_N(folderId, name, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No DLFileVersion exists with the key {");

			msg.append("folderId=" + folderId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFileVersionException(msg.toString());
		}
		else {
			return (DLFileVersion)list.get(0);
		}
	}

	public DLFileVersion findByF_N_Last(long folderId, String name,
		OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		int count = countByF_N(folderId, name);

		List list = findByF_N(folderId, name, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No DLFileVersion exists with the key {");

			msg.append("folderId=" + folderId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchFileVersionException(msg.toString());
		}
		else {
			return (DLFileVersion)list.get(0);
		}
	}

	public DLFileVersion[] findByF_N_PrevAndNext(long fileVersionId,
		long folderId, String name, OrderByComparator obc)
		throws NoSuchFileVersionException, SystemException {
		DLFileVersion dlFileVersion = findByPrimaryKey(fileVersionId);

		int count = countByF_N(folderId, name);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion WHERE ");

			query.append("folderId = ?");

			query.append(" AND ");

			if (name == null) {
				query.append("name IS NULL");
			}
			else {
				query.append("name = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("folderId DESC, ");
				query.append("name DESC, ");
				query.append("version DESC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, folderId);

			if (name != null) {
				q.setString(queryPos++, name);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					dlFileVersion);

			DLFileVersion[] array = new DLFileVersionImpl[3];

			array[0] = (DLFileVersion)objArray[0];
			array[1] = (DLFileVersion)objArray[1];
			array[2] = (DLFileVersion)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public DLFileVersion findByF_N_V(long folderId, String name, double version)
		throws NoSuchFileVersionException, SystemException {
		DLFileVersion dlFileVersion = fetchByF_N_V(folderId, name, version);

		if (dlFileVersion == null) {
			StringMaker msg = new StringMaker();

			msg.append("No DLFileVersion exists with the key {");

			msg.append("folderId=" + folderId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(", ");
			msg.append("version=" + version);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchFileVersionException(msg.toString());
		}

		return dlFileVersion;
	}

	public DLFileVersion fetchByF_N_V(long folderId, String name, double version)
		throws SystemException {
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
		String finderMethodName = "fetchByF_N_V";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(folderId),
				
				name, new Double(version)
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
					"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion WHERE ");

				query.append("folderId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("folderId DESC, ");
				query.append("name DESC, ");
				query.append("version DESC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				if (name != null) {
					q.setString(queryPos++, name);
				}

				q.setDouble(queryPos++, version);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (DLFileVersion)list.get(0);
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
				return (DLFileVersion)list.get(0);
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
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
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
					"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("folderId DESC, ");
					query.append("name DESC, ");
					query.append("version DESC");
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

	public void removeByF_N(long folderId, String name)
		throws SystemException {
		Iterator itr = findByF_N(folderId, name).iterator();

		while (itr.hasNext()) {
			DLFileVersion dlFileVersion = (DLFileVersion)itr.next();

			remove(dlFileVersion);
		}
	}

	public void removeByF_N_V(long folderId, String name, double version)
		throws NoSuchFileVersionException, SystemException {
		DLFileVersion dlFileVersion = findByF_N_V(folderId, name, version);

		remove(dlFileVersion);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((DLFileVersion)itr.next());
		}
	}

	public int countByF_N(long folderId, String name) throws SystemException {
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
		String finderMethodName = "countByF_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(folderId), name };

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
					"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion WHERE ");

				query.append("folderId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				if (name != null) {
					q.setString(queryPos++, name);
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

	public int countByF_N_V(long folderId, String name, double version)
		throws SystemException {
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
		String finderMethodName = "countByF_N_V";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(folderId),
				
				name, new Double(version)
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
					"FROM com.liferay.portlet.documentlibrary.model.DLFileVersion WHERE ");

				query.append("folderId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, folderId);

				if (name != null) {
					q.setString(queryPos++, name);
				}

				q.setDouble(queryPos++, version);

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
		boolean finderClassNameCacheEnabled = DLFileVersionModelImpl.CACHE_ENABLED;
		String finderClassName = DLFileVersion.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.documentlibrary.model.DLFileVersion");

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
				"value.object.listener.com.liferay.portlet.documentlibrary.model.DLFileVersion"));
	private static Log _log = LogFactory.getLog(DLFileVersionPersistenceImpl.class);
}