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

import com.liferay.portlet.tags.NoSuchAssetException;
import com.liferay.portlet.tags.model.TagsAsset;
import com.liferay.portlet.tags.model.impl.TagsAssetImpl;
import com.liferay.portlet.tags.model.impl.TagsAssetModelImpl;

import com.liferay.util.dao.hibernate.QueryPos;
import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Hibernate;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import org.springframework.dao.DataAccessException;

import org.springframework.jdbc.core.SqlParameter;
import org.springframework.jdbc.object.MappingSqlQuery;
import org.springframework.jdbc.object.SqlUpdate;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Types;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="TagsAssetPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsAssetPersistenceImpl extends BasePersistence
	implements TagsAssetPersistence {
	public TagsAsset create(long assetId) {
		TagsAsset tagsAsset = new TagsAssetImpl();

		tagsAsset.setNew(true);
		tagsAsset.setPrimaryKey(assetId);

		return tagsAsset;
	}

	public TagsAsset remove(long assetId)
		throws NoSuchAssetException, SystemException {
		Session session = null;

		try {
			session = openSession();

			TagsAsset tagsAsset = (TagsAsset)session.get(TagsAssetImpl.class,
					new Long(assetId));

			if (tagsAsset == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No TagsAsset exists with the primary key " +
						assetId);
				}

				throw new NoSuchAssetException(
					"No TagsAsset exists with the primary key " + assetId);
			}

			return remove(tagsAsset);
		}
		catch (NoSuchAssetException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public TagsAsset remove(TagsAsset tagsAsset) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(tagsAsset);
		}

		tagsAsset = removeImpl(tagsAsset);

		if (listener != null) {
			listener.onAfterRemove(tagsAsset);
		}

		return tagsAsset;
	}

	protected TagsAsset removeImpl(TagsAsset tagsAsset)
		throws SystemException {
		try {
			clearTagsEntries.clear(tagsAsset.getPrimaryKey());
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}

		Session session = null;

		try {
			session = openSession();

			session.delete(tagsAsset);

			session.flush();

			return tagsAsset;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(TagsAsset.class.getName());
		}
	}

	public TagsAsset update(TagsAsset tagsAsset) throws SystemException {
		return update(tagsAsset, false);
	}

	public TagsAsset update(TagsAsset tagsAsset, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = tagsAsset.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(tagsAsset);
			}
			else {
				listener.onBeforeUpdate(tagsAsset);
			}
		}

		tagsAsset = updateImpl(tagsAsset, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(tagsAsset);
			}
			else {
				listener.onAfterUpdate(tagsAsset);
			}
		}

		return tagsAsset;
	}

	public TagsAsset updateImpl(
		com.liferay.portlet.tags.model.TagsAsset tagsAsset, boolean merge)
		throws SystemException {
		FinderCache.clearCache("TagsAssets_TagsEntries");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(tagsAsset);
			}
			else {
				if (tagsAsset.isNew()) {
					session.save(tagsAsset);
				}
			}

			session.flush();

			tagsAsset.setNew(false);

			return tagsAsset;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(TagsAsset.class.getName());
		}
	}

	public TagsAsset findByPrimaryKey(long assetId)
		throws NoSuchAssetException, SystemException {
		TagsAsset tagsAsset = fetchByPrimaryKey(assetId);

		if (tagsAsset == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No TagsAsset exists with the primary key " +
					assetId);
			}

			throw new NoSuchAssetException(
				"No TagsAsset exists with the primary key " + assetId);
		}

		return tagsAsset;
	}

	public TagsAsset fetchByPrimaryKey(long assetId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (TagsAsset)session.get(TagsAssetImpl.class, new Long(assetId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
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
					"FROM com.liferay.portlet.tags.model.TagsAsset WHERE ");

				query.append("companyId = ?");

				query.append(" ");

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
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
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
					"FROM com.liferay.portlet.tags.model.TagsAsset WHERE ");

				query.append("companyId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
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

	public TagsAsset findByCompanyId_First(long companyId, OrderByComparator obc)
		throws NoSuchAssetException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsAsset exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchAssetException(msg.toString());
		}
		else {
			return (TagsAsset)list.get(0);
		}
	}

	public TagsAsset findByCompanyId_Last(long companyId, OrderByComparator obc)
		throws NoSuchAssetException, SystemException {
		int count = countByCompanyId(companyId);

		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsAsset exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchAssetException(msg.toString());
		}
		else {
			return (TagsAsset)list.get(0);
		}
	}

	public TagsAsset[] findByCompanyId_PrevAndNext(long assetId,
		long companyId, OrderByComparator obc)
		throws NoSuchAssetException, SystemException {
		TagsAsset tagsAsset = findByPrimaryKey(assetId);

		int count = countByCompanyId(companyId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portlet.tags.model.TagsAsset WHERE ");

			query.append("companyId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, companyId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					tagsAsset);

			TagsAsset[] array = new TagsAssetImpl[3];

			array[0] = (TagsAsset)objArray[0];
			array[1] = (TagsAsset)objArray[1];
			array[2] = (TagsAsset)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public TagsAsset findByC_C(long classNameId, long classPK)
		throws NoSuchAssetException, SystemException {
		TagsAsset tagsAsset = fetchByC_C(classNameId, classPK);

		if (tagsAsset == null) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsAsset exists with the key {");

			msg.append("classNameId=" + classNameId);

			msg.append(", ");
			msg.append("classPK=" + classPK);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchAssetException(msg.toString());
		}

		return tagsAsset;
	}

	public TagsAsset fetchByC_C(long classNameId, long classPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
		String finderMethodName = "fetchByC_C";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(classNameId), new Long(classPK)
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
					"FROM com.liferay.portlet.tags.model.TagsAsset WHERE ");

				query.append("classNameId = ?");

				query.append(" AND ");

				query.append("classPK = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, classNameId);

				q.setLong(queryPos++, classPK);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (TagsAsset)list.get(0);
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
				return (TagsAsset)list.get(0);
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
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
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

				query.append("FROM com.liferay.portlet.tags.model.TagsAsset ");

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

	public void removeByCompanyId(long companyId) throws SystemException {
		Iterator itr = findByCompanyId(companyId).iterator();

		while (itr.hasNext()) {
			TagsAsset tagsAsset = (TagsAsset)itr.next();

			remove(tagsAsset);
		}
	}

	public void removeByC_C(long classNameId, long classPK)
		throws NoSuchAssetException, SystemException {
		TagsAsset tagsAsset = findByC_C(classNameId, classPK);

		remove(tagsAsset);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((TagsAsset)itr.next());
		}
	}

	public int countByCompanyId(long companyId) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
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
					"FROM com.liferay.portlet.tags.model.TagsAsset WHERE ");

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

	public int countByC_C(long classNameId, long classPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
		String finderMethodName = "countByC_C";
		String[] finderParams = new String[] {
				Long.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(classNameId), new Long(classPK)
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
					"FROM com.liferay.portlet.tags.model.TagsAsset WHERE ");

				query.append("classNameId = ?");

				query.append(" AND ");

				query.append("classPK = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, classNameId);

				q.setLong(queryPos++, classPK);

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
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED;
		String finderClassName = TagsAsset.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.tags.model.TagsAsset");

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

	public List getTagsEntries(long pk)
		throws NoSuchAssetException, SystemException {
		return getTagsEntries(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getTagsEntries(long pk, int begin, int end)
		throws NoSuchAssetException, SystemException {
		return getTagsEntries(pk, begin, end, null);
	}

	public List getTagsEntries(long pk, int begin, int end,
		OrderByComparator obc) throws NoSuchAssetException, SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED_TAGSASSETS_TAGSENTRIES;
		String finderClassName = "TagsAssets_TagsEntries";
		String finderMethodName = "getTagsEntries";
		String[] finderParams = new String[] {
				Long.class.getName(), "java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(pk), String.valueOf(begin), String.valueOf(end),
				String.valueOf(obc)
			};

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = HibernateUtil.openSession();

				StringMaker sm = new StringMaker();

				sm.append(_SQL_GETTAGSENTRIES);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				else {
					sm.append("ORDER BY ");

					sm.append("TagsEntry.name ASC");
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("TagsEntry",
					com.liferay.portlet.tags.model.impl.TagsEntryImpl.class);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(pk);

				List list = QueryUtil.list(q, getDialect(), begin, end);

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				return list;
			}
			catch (Exception e) {
				throw new SystemException(e);
			}
			finally {
				closeSession(session);
			}
		}
		else {
			return (List)result;
		}
	}

	public int getTagsEntriesSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED_TAGSASSETS_TAGSENTRIES;
		String finderClassName = "TagsAssets_TagsEntries";
		String finderMethodName = "getTagsEntriesSize";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(pk) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			Session session = null;

			try {
				session = openSession();

				SQLQuery q = session.createSQLQuery(_SQL_GETTAGSENTRIESSIZE);

				q.addScalar(HibernateUtil.getCountColumnName(), Hibernate.LONG);

				QueryPos qPos = QueryPos.getInstance(q);

				qPos.add(pk);

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

	public boolean containsTagsEntry(long pk, long tagsEntryPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsAssetModelImpl.CACHE_ENABLED_TAGSASSETS_TAGSENTRIES;
		String finderClassName = "TagsAssets_TagsEntries";
		String finderMethodName = "containsTagsEntries";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(tagsEntryPK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsTagsEntry.contains(pk,
							tagsEntryPK));

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, value);

				return value.booleanValue();
			}
			catch (DataAccessException dae) {
				throw new SystemException(dae);
			}
		}
		else {
			return ((Boolean)result).booleanValue();
		}
	}

	public boolean containsTagsEntries(long pk) throws SystemException {
		if (getTagsEntriesSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addTagsEntry(long pk, long tagsEntryPK)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			addTagsEntry.add(pk, tagsEntryPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void addTagsEntry(long pk,
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			addTagsEntry.add(pk, tagsEntry.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void addTagsEntries(long pk, long[] tagsEntryPKs)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			for (int i = 0; i < tagsEntryPKs.length; i++) {
				addTagsEntry.add(pk, tagsEntryPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void addTagsEntries(long pk, List tagsEntries)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			for (int i = 0; i < tagsEntries.size(); i++) {
				com.liferay.portlet.tags.model.TagsEntry tagsEntry = (com.liferay.portlet.tags.model.TagsEntry)tagsEntries.get(i);

				addTagsEntry.add(pk, tagsEntry.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void clearTagsEntries(long pk)
		throws NoSuchAssetException, SystemException {
		try {
			clearTagsEntries.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsEntry(long pk, long tagsEntryPK)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			removeTagsEntry.remove(pk, tagsEntryPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsEntry(long pk,
		com.liferay.portlet.tags.model.TagsEntry tagsEntry)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			removeTagsEntry.remove(pk, tagsEntry.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsEntries(long pk, long[] tagsEntryPKs)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			for (int i = 0; i < tagsEntryPKs.length; i++) {
				removeTagsEntry.remove(pk, tagsEntryPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsEntries(long pk, List tagsEntries)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			for (int i = 0; i < tagsEntries.size(); i++) {
				com.liferay.portlet.tags.model.TagsEntry tagsEntry = (com.liferay.portlet.tags.model.TagsEntry)tagsEntries.get(i);

				removeTagsEntry.remove(pk, tagsEntry.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void setTagsEntries(long pk, long[] tagsEntryPKs)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			clearTagsEntries.clear(pk);

			for (int i = 0; i < tagsEntryPKs.length; i++) {
				addTagsEntry.add(pk, tagsEntryPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void setTagsEntries(long pk, List tagsEntries)
		throws NoSuchAssetException, 
			com.liferay.portlet.tags.NoSuchEntryException, SystemException {
		try {
			clearTagsEntries.clear(pk);

			for (int i = 0; i < tagsEntries.size(); i++) {
				com.liferay.portlet.tags.model.TagsEntry tagsEntry = (com.liferay.portlet.tags.model.TagsEntry)tagsEntries.get(i);

				addTagsEntry.add(pk, tagsEntry.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	protected void initDao() {
		containsTagsEntry = new ContainsTagsEntry(this);

		addTagsEntry = new AddTagsEntry(this);
		clearTagsEntries = new ClearTagsEntries(this);
		removeTagsEntry = new RemoveTagsEntry(this);
	}

	protected ContainsTagsEntry containsTagsEntry;
	protected AddTagsEntry addTagsEntry;
	protected ClearTagsEntries clearTagsEntries;
	protected RemoveTagsEntry removeTagsEntry;

	protected class ContainsTagsEntry extends MappingSqlQuery {
		protected ContainsTagsEntry(TagsAssetPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSTAGSENTRY);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long assetId, long entryId) {
			List results = execute(new Object[] {
						new Long(assetId), new Long(entryId)
					});

			if (results.size() > 0) {
				Integer count = (Integer)results.get(0);

				if (count.intValue() > 0) {
					return true;
				}
			}

			return false;
		}
	}

	protected class AddTagsEntry extends SqlUpdate {
		protected AddTagsEntry(TagsAssetPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO TagsAssets_TagsEntries (assetId, entryId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long assetId, long entryId) {
			if (!_persistenceImpl.containsTagsEntry.contains(assetId, entryId)) {
				update(new Object[] { new Long(assetId), new Long(entryId) });
			}
		}

		private TagsAssetPersistenceImpl _persistenceImpl;
	}

	protected class ClearTagsEntries extends SqlUpdate {
		protected ClearTagsEntries(TagsAssetPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM TagsAssets_TagsEntries WHERE assetId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long assetId) {
			update(new Object[] { new Long(assetId) });
		}
	}

	protected class RemoveTagsEntry extends SqlUpdate {
		protected RemoveTagsEntry(TagsAssetPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM TagsAssets_TagsEntries WHERE assetId = ? AND entryId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long assetId, long entryId) {
			update(new Object[] { new Long(assetId), new Long(entryId) });
		}
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

	private static final String _SQL_GETTAGSENTRIES = "SELECT {TagsEntry.*} FROM TagsEntry INNER JOIN TagsAssets_TagsEntries ON (TagsAssets_TagsEntries.entryId = TagsEntry.entryId) WHERE (TagsAssets_TagsEntries.assetId = ?)";
	private static final String _SQL_GETTAGSENTRIESSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM TagsAssets_TagsEntries WHERE assetId = ?";
	private static final String _SQL_CONTAINSTAGSENTRY = "SELECT COUNT(*) AS COUNT_VALUE FROM TagsAssets_TagsEntries WHERE assetId = ? AND entryId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.tags.model.TagsAsset"));
	private static Log _log = LogFactory.getLog(TagsAssetPersistenceImpl.class);
}