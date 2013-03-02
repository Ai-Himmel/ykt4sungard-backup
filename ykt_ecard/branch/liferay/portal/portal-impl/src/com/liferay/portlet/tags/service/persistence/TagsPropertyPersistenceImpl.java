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

package com.liferay.portlet.tags.service.persistence;

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

import com.liferay.portlet.tags.NoSuchPropertyException;
import com.liferay.portlet.tags.model.TagsProperty;
import com.liferay.portlet.tags.model.impl.TagsPropertyImpl;
import com.liferay.portlet.tags.model.impl.TagsPropertyModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="TagsPropertyPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsPropertyPersistenceImpl extends BasePersistence
	implements TagsPropertyPersistence {
	public TagsProperty create(long propertyId) {
		TagsProperty tagsProperty = new TagsPropertyImpl();

		tagsProperty.setNew(true);
		tagsProperty.setPrimaryKey(propertyId);

		return tagsProperty;
	}

	public TagsProperty remove(long propertyId)
		throws NoSuchPropertyException, SystemException {
		Session session = null;

		try {
			session = openSession();

			TagsProperty tagsProperty = (TagsProperty)session.get(TagsPropertyImpl.class,
					new Long(propertyId));

			if (tagsProperty == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No TagsProperty exists with the primary key " +
						propertyId);
				}

				throw new NoSuchPropertyException(
					"No TagsProperty exists with the primary key " +
					propertyId);
			}

			return remove(tagsProperty);
		}
		catch (NoSuchPropertyException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public TagsProperty remove(TagsProperty tagsProperty)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(tagsProperty);
		}

		tagsProperty = removeImpl(tagsProperty);

		if (listener != null) {
			listener.onAfterRemove(tagsProperty);
		}

		return tagsProperty;
	}

	protected TagsProperty removeImpl(TagsProperty tagsProperty)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(tagsProperty);

			session.flush();

			return tagsProperty;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(TagsProperty.class.getName());
		}
	}

	public TagsProperty update(TagsProperty tagsProperty)
		throws SystemException {
		return update(tagsProperty, false);
	}

	public TagsProperty update(TagsProperty tagsProperty, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = tagsProperty.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(tagsProperty);
			}
			else {
				listener.onBeforeUpdate(tagsProperty);
			}
		}

		tagsProperty = updateImpl(tagsProperty, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(tagsProperty);
			}
			else {
				listener.onAfterUpdate(tagsProperty);
			}
		}

		return tagsProperty;
	}

	public TagsProperty updateImpl(
		com.liferay.portlet.tags.model.TagsProperty tagsProperty, boolean merge)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(tagsProperty);
			}
			else {
				if (tagsProperty.isNew()) {
					session.save(tagsProperty);
				}
			}

			session.flush();

			tagsProperty.setNew(false);

			return tagsProperty;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(TagsProperty.class.getName());
		}
	}

	public TagsProperty findByPrimaryKey(long propertyId)
		throws NoSuchPropertyException, SystemException {
		TagsProperty tagsProperty = fetchByPrimaryKey(propertyId);

		if (tagsProperty == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No TagsProperty exists with the primary key " +
					propertyId);
			}

			throw new NoSuchPropertyException(
				"No TagsProperty exists with the primary key " + propertyId);
		}

		return tagsProperty;
	}

	public TagsProperty fetchByPrimaryKey(long propertyId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (TagsProperty)session.get(TagsPropertyImpl.class,
				new Long(propertyId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("key_ ASC");

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
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("key_ ASC");
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

	public TagsProperty findByCompanyId_First(long companyId,
		OrderByComparator obc) throws NoSuchPropertyException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPropertyException(msg.toString());
		}
		else {
			return (TagsProperty)list.get(0);
		}
	}

	public TagsProperty findByCompanyId_Last(long companyId,
		OrderByComparator obc) throws NoSuchPropertyException, SystemException {
		int count = countByCompanyId(companyId);

		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPropertyException(msg.toString());
		}
		else {
			return (TagsProperty)list.get(0);
		}
	}

	public TagsProperty[] findByCompanyId_PrevAndNext(long propertyId,
		long companyId, OrderByComparator obc)
		throws NoSuchPropertyException, SystemException {
		TagsProperty tagsProperty = findByPrimaryKey(propertyId);

		int count = countByCompanyId(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

			query.append("companyId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("key_ ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					tagsProperty);

			TagsProperty[] array = new TagsPropertyImpl[3];

			array[0] = (TagsProperty)objArray[0];
			array[1] = (TagsProperty)objArray[1];
			array[2] = (TagsProperty)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByEntryId(long entryId) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "findByEntryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(entryId) };

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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("entryId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("key_ ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, entryId);

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

	public List findByEntryId(long entryId, int begin, int end)
		throws SystemException {
		return findByEntryId(entryId, begin, end, null);
	}

	public List findByEntryId(long entryId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "findByEntryId";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(entryId),
				
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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("entryId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("key_ ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, entryId);

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

	public TagsProperty findByEntryId_First(long entryId, OrderByComparator obc)
		throws NoSuchPropertyException, SystemException {
		List list = findByEntryId(entryId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("entryId=" + entryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPropertyException(msg.toString());
		}
		else {
			return (TagsProperty)list.get(0);
		}
	}

	public TagsProperty findByEntryId_Last(long entryId, OrderByComparator obc)
		throws NoSuchPropertyException, SystemException {
		int count = countByEntryId(entryId);

		List list = findByEntryId(entryId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("entryId=" + entryId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPropertyException(msg.toString());
		}
		else {
			return (TagsProperty)list.get(0);
		}
	}

	public TagsProperty[] findByEntryId_PrevAndNext(long propertyId,
		long entryId, OrderByComparator obc)
		throws NoSuchPropertyException, SystemException {
		TagsProperty tagsProperty = findByPrimaryKey(propertyId);

		int count = countByEntryId(entryId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

			query.append("entryId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("key_ ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, entryId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					tagsProperty);

			TagsProperty[] array = new TagsPropertyImpl[3];

			array[0] = (TagsProperty)objArray[0];
			array[1] = (TagsProperty)objArray[1];
			array[2] = (TagsProperty)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByC_K(long companyId, String key) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "findByC_K";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), key };

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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (key == null) {
					query.append("key_ IS NULL");
				}
				else {
					query.append("key_ = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("key_ ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (key != null) {
					q.setString(queryPos++, key);
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

	public List findByC_K(long companyId, String key, int begin, int end)
		throws SystemException {
		return findByC_K(companyId, key, begin, end, null);
	}

	public List findByC_K(long companyId, String key, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "findByC_K";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(companyId),
				
				key,
				
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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (key == null) {
					query.append("key_ IS NULL");
				}
				else {
					query.append("key_ = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("key_ ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (key != null) {
					q.setString(queryPos++, key);
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

	public TagsProperty findByC_K_First(long companyId, String key,
		OrderByComparator obc) throws NoSuchPropertyException, SystemException {
		List list = findByC_K(companyId, key, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("key=" + key);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPropertyException(msg.toString());
		}
		else {
			return (TagsProperty)list.get(0);
		}
	}

	public TagsProperty findByC_K_Last(long companyId, String key,
		OrderByComparator obc) throws NoSuchPropertyException, SystemException {
		int count = countByC_K(companyId, key);

		List list = findByC_K(companyId, key, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("key=" + key);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchPropertyException(msg.toString());
		}
		else {
			return (TagsProperty)list.get(0);
		}
	}

	public TagsProperty[] findByC_K_PrevAndNext(long propertyId,
		long companyId, String key, OrderByComparator obc)
		throws NoSuchPropertyException, SystemException {
		TagsProperty tagsProperty = findByPrimaryKey(propertyId);

		int count = countByC_K(companyId, key);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

			query.append("companyId = ?");

			query.append(" AND ");

			if (key == null) {
				query.append("key_ IS NULL");
			}
			else {
				query.append("key_ = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("key_ ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			if (key != null) {
				q.setString(queryPos++, key);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					tagsProperty);

			TagsProperty[] array = new TagsPropertyImpl[3];

			array[0] = (TagsProperty)objArray[0];
			array[1] = (TagsProperty)objArray[1];
			array[2] = (TagsProperty)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public TagsProperty findByE_K(long entryId, String key)
		throws NoSuchPropertyException, SystemException {
		TagsProperty tagsProperty = fetchByE_K(entryId, key);

		if (tagsProperty == null) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsProperty exists with the key {");

			msg.append("entryId=" + entryId);

			msg.append(", ");
			msg.append("key=" + key);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchPropertyException(msg.toString());
		}

		return tagsProperty;
	}

	public TagsProperty fetchByE_K(long entryId, String key)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "fetchByE_K";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(entryId), key };

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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("entryId = ?");

				query.append(" AND ");

				if (key == null) {
					query.append("key_ IS NULL");
				}
				else {
					query.append("key_ = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("key_ ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, entryId);

				if (key != null) {
					q.setString(queryPos++, key);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (TagsProperty)list.get(0);
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
				return (TagsProperty)list.get(0);
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
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
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
					"FROM com.liferay.portlet.tags.model.TagsProperty ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("key_ ASC");
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

	public void removeByCompanyId(long companyId) throws SystemException {
		Iterator itr = findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			TagsProperty tagsProperty = (TagsProperty)itr.next();

			remove(tagsProperty);
		}
	}

	public void removeByEntryId(long entryId) throws SystemException {
		Iterator itr = findByEntryId(entryId).iterator();

		while (itr.hasNext()) {
			TagsProperty tagsProperty = (TagsProperty)itr.next();

			remove(tagsProperty);
		}
	}

	public void removeByC_K(long companyId, String key)
		throws SystemException {
		Iterator itr = findByC_K(companyId, key).iterator();

		while (itr.hasNext()) {
			TagsProperty tagsProperty = (TagsProperty)itr.next();

			remove(tagsProperty);
		}
	}

	public void removeByE_K(long entryId, String key)
		throws NoSuchPropertyException, SystemException {
		TagsProperty tagsProperty = findByE_K(entryId, key);

		remove(tagsProperty);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((TagsProperty)itr.next());
		}
	}

	public int countByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
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
				query.append(
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

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

	public int countByEntryId(long entryId) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "countByEntryId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(entryId) };

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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("entryId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, entryId);

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

	public int countByC_K(long companyId, String key) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "countByC_K";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), key };

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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (key == null) {
					query.append("key_ IS NULL");
				}
				else {
					query.append("key_ = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (key != null) {
					q.setString(queryPos++, key);
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

	public int countByE_K(long entryId, String key) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
		String finderMethodName = "countByE_K";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(entryId), key };

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
					"FROM com.liferay.portlet.tags.model.TagsProperty WHERE ");

				query.append("entryId = ?");

				query.append(" AND ");

				if (key == null) {
					query.append("key_ IS NULL");
				}
				else {
					query.append("key_ = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, entryId);

				if (key != null) {
					q.setString(queryPos++, key);
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
		boolean finderClassNameCacheEnabled = TagsPropertyModelImpl.CACHE_ENABLED;
		String finderClassName = TagsProperty.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.tags.model.TagsProperty");

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
				"value.object.listener.com.liferay.portlet.tags.model.TagsProperty"));
	private static Log _log = LogFactory.getLog(TagsPropertyPersistenceImpl.class);
}