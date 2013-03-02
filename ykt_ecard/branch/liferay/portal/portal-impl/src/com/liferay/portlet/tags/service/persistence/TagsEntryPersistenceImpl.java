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

import com.liferay.portlet.tags.NoSuchEntryException;
import com.liferay.portlet.tags.model.TagsEntry;
import com.liferay.portlet.tags.model.impl.TagsEntryImpl;
import com.liferay.portlet.tags.model.impl.TagsEntryModelImpl;

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
 * <a href="TagsEntryPersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class TagsEntryPersistenceImpl extends BasePersistence
	implements TagsEntryPersistence {
	public TagsEntry create(long entryId) {
		TagsEntry tagsEntry = new TagsEntryImpl();

		tagsEntry.setNew(true);
		tagsEntry.setPrimaryKey(entryId);

		return tagsEntry;
	}

	public TagsEntry remove(long entryId)
		throws NoSuchEntryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			TagsEntry tagsEntry = (TagsEntry)session.get(TagsEntryImpl.class,
					new Long(entryId));

			if (tagsEntry == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No TagsEntry exists with the primary key " +
						entryId);
				}

				throw new NoSuchEntryException(
					"No TagsEntry exists with the primary key " + entryId);
			}

			return remove(tagsEntry);
		}
		catch (NoSuchEntryException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public TagsEntry remove(TagsEntry tagsEntry) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(tagsEntry);
		}

		tagsEntry = removeImpl(tagsEntry);

		if (listener != null) {
			listener.onAfterRemove(tagsEntry);
		}

		return tagsEntry;
	}

	protected TagsEntry removeImpl(TagsEntry tagsEntry)
		throws SystemException {
		try {
			clearTagsAssets.clear(tagsEntry.getPrimaryKey());
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

			session.delete(tagsEntry);

			session.flush();

			return tagsEntry;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(TagsEntry.class.getName());
		}
	}

	public TagsEntry update(TagsEntry tagsEntry) throws SystemException {
		return update(tagsEntry, false);
	}

	public TagsEntry update(TagsEntry tagsEntry, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = tagsEntry.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(tagsEntry);
			}
			else {
				listener.onBeforeUpdate(tagsEntry);
			}
		}

		tagsEntry = updateImpl(tagsEntry, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(tagsEntry);
			}
			else {
				listener.onAfterUpdate(tagsEntry);
			}
		}

		return tagsEntry;
	}

	public TagsEntry updateImpl(
		com.liferay.portlet.tags.model.TagsEntry tagsEntry, boolean merge)
		throws SystemException {
		FinderCache.clearCache("TagsAssets_TagsEntries");

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(tagsEntry);
			}
			else {
				if (tagsEntry.isNew()) {
					session.save(tagsEntry);
				}
			}

			session.flush();

			tagsEntry.setNew(false);

			return tagsEntry;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(TagsEntry.class.getName());
		}
	}

	public TagsEntry findByPrimaryKey(long entryId)
		throws NoSuchEntryException, SystemException {
		TagsEntry tagsEntry = fetchByPrimaryKey(entryId);

		if (tagsEntry == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No TagsEntry exists with the primary key " +
					entryId);
			}

			throw new NoSuchEntryException(
				"No TagsEntry exists with the primary key " + entryId);
		}

		return tagsEntry;
	}

	public TagsEntry fetchByPrimaryKey(long entryId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (TagsEntry)session.get(TagsEntryImpl.class, new Long(entryId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public TagsEntry findByC_N(long companyId, String name)
		throws NoSuchEntryException, SystemException {
		TagsEntry tagsEntry = fetchByC_N(companyId, name);

		if (tagsEntry == null) {
			StringMaker msg = new StringMaker();

			msg.append("No TagsEntry exists with the key {");

			msg.append("companyId=" + companyId);

			msg.append(", ");
			msg.append("name=" + name);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchEntryException(msg.toString());
		}

		return tagsEntry;
	}

	public TagsEntry fetchByC_N(long companyId, String name)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED;
		String finderClassName = TagsEntry.class.getName();
		String finderMethodName = "fetchByC_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), name };

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
					"FROM com.liferay.portlet.tags.model.TagsEntry WHERE ");

				query.append("companyId = ?");

				query.append(" AND ");

				if (name == null) {
					query.append("name IS NULL");
				}
				else {
					query.append("name = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("name ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, companyId);

				if (name != null) {
					q.setString(queryPos++, name);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (TagsEntry)list.get(0);
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
				return (TagsEntry)list.get(0);
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
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED;
		String finderClassName = TagsEntry.class.getName();
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

				query.append("FROM com.liferay.portlet.tags.model.TagsEntry ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("name ASC");
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

	public void removeByC_N(long companyId, String name)
		throws NoSuchEntryException, SystemException {
		TagsEntry tagsEntry = findByC_N(companyId, name);

		remove(tagsEntry);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((TagsEntry)itr.next());
		}
	}

	public int countByC_N(long companyId, String name)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED;
		String finderClassName = TagsEntry.class.getName();
		String finderMethodName = "countByC_N";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(companyId), name };

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
					"FROM com.liferay.portlet.tags.model.TagsEntry WHERE ");

				query.append("companyId = ?");

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

				q.setLong(queryPos++, companyId);

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

	public int countAll() throws SystemException {
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED;
		String finderClassName = TagsEntry.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.tags.model.TagsEntry");

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

	public List getTagsAssets(long pk)
		throws NoSuchEntryException, SystemException {
		return getTagsAssets(pk, QueryUtil.ALL_POS, QueryUtil.ALL_POS);
	}

	public List getTagsAssets(long pk, int begin, int end)
		throws NoSuchEntryException, SystemException {
		return getTagsAssets(pk, begin, end, null);
	}

	public List getTagsAssets(long pk, int begin, int end, OrderByComparator obc)
		throws NoSuchEntryException, SystemException {
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED_TAGSASSETS_TAGSENTRIES;
		String finderClassName = "TagsAssets_TagsEntries";
		String finderMethodName = "getTagsAssets";
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

				sm.append(_SQL_GETTAGSASSETS);

				if (obc != null) {
					sm.append("ORDER BY ");
					sm.append(obc.getOrderBy());
				}

				String sql = sm.toString();

				SQLQuery q = session.createSQLQuery(sql);

				q.addEntity("TagsAsset",
					com.liferay.portlet.tags.model.impl.TagsAssetImpl.class);

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

	public int getTagsAssetsSize(long pk) throws SystemException {
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED_TAGSASSETS_TAGSENTRIES;
		String finderClassName = "TagsAssets_TagsEntries";
		String finderMethodName = "getTagsAssetsSize";
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

				SQLQuery q = session.createSQLQuery(_SQL_GETTAGSASSETSSIZE);

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

	public boolean containsTagsAsset(long pk, long tagsAssetPK)
		throws SystemException {
		boolean finderClassNameCacheEnabled = TagsEntryModelImpl.CACHE_ENABLED_TAGSASSETS_TAGSENTRIES;
		String finderClassName = "TagsAssets_TagsEntries";
		String finderMethodName = "containsTagsAssets";
		String[] finderParams = new String[] {
				Long.class.getName(),
				
				Long.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(pk), new Long(tagsAssetPK) };

		Object result = null;

		if (finderClassNameCacheEnabled) {
			result = FinderCache.getResult(finderClassName, finderMethodName,
					finderParams, finderArgs, getSessionFactory());
		}

		if (result == null) {
			try {
				Boolean value = Boolean.valueOf(containsTagsAsset.contains(pk,
							tagsAssetPK));

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

	public boolean containsTagsAssets(long pk) throws SystemException {
		if (getTagsAssetsSize(pk) > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public void addTagsAsset(long pk, long tagsAssetPK)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			addTagsAsset.add(pk, tagsAssetPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void addTagsAsset(long pk,
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			addTagsAsset.add(pk, tagsAsset.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void addTagsAssets(long pk, long[] tagsAssetPKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			for (int i = 0; i < tagsAssetPKs.length; i++) {
				addTagsAsset.add(pk, tagsAssetPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void addTagsAssets(long pk, List tagsAssets)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			for (int i = 0; i < tagsAssets.size(); i++) {
				com.liferay.portlet.tags.model.TagsAsset tagsAsset = (com.liferay.portlet.tags.model.TagsAsset)tagsAssets.get(i);

				addTagsAsset.add(pk, tagsAsset.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void clearTagsAssets(long pk)
		throws NoSuchEntryException, SystemException {
		try {
			clearTagsAssets.clear(pk);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsAsset(long pk, long tagsAssetPK)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			removeTagsAsset.remove(pk, tagsAssetPK);
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsAsset(long pk,
		com.liferay.portlet.tags.model.TagsAsset tagsAsset)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			removeTagsAsset.remove(pk, tagsAsset.getPrimaryKey());
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsAssets(long pk, long[] tagsAssetPKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			for (int i = 0; i < tagsAssetPKs.length; i++) {
				removeTagsAsset.remove(pk, tagsAssetPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void removeTagsAssets(long pk, List tagsAssets)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			for (int i = 0; i < tagsAssets.size(); i++) {
				com.liferay.portlet.tags.model.TagsAsset tagsAsset = (com.liferay.portlet.tags.model.TagsAsset)tagsAssets.get(i);

				removeTagsAsset.remove(pk, tagsAsset.getPrimaryKey());
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void setTagsAssets(long pk, long[] tagsAssetPKs)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			clearTagsAssets.clear(pk);

			for (int i = 0; i < tagsAssetPKs.length; i++) {
				addTagsAsset.add(pk, tagsAssetPKs[i]);
			}
		}
		catch (DataAccessException dae) {
			throw new SystemException(dae);
		}
		finally {
			FinderCache.clearCache("TagsAssets_TagsEntries");
		}
	}

	public void setTagsAssets(long pk, List tagsAssets)
		throws NoSuchEntryException, 
			com.liferay.portlet.tags.NoSuchAssetException, SystemException {
		try {
			clearTagsAssets.clear(pk);

			for (int i = 0; i < tagsAssets.size(); i++) {
				com.liferay.portlet.tags.model.TagsAsset tagsAsset = (com.liferay.portlet.tags.model.TagsAsset)tagsAssets.get(i);

				addTagsAsset.add(pk, tagsAsset.getPrimaryKey());
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
		containsTagsAsset = new ContainsTagsAsset(this);

		addTagsAsset = new AddTagsAsset(this);
		clearTagsAssets = new ClearTagsAssets(this);
		removeTagsAsset = new RemoveTagsAsset(this);
	}

	protected ContainsTagsAsset containsTagsAsset;
	protected AddTagsAsset addTagsAsset;
	protected ClearTagsAssets clearTagsAssets;
	protected RemoveTagsAsset removeTagsAsset;

	protected class ContainsTagsAsset extends MappingSqlQuery {
		protected ContainsTagsAsset(TagsEntryPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(), _SQL_CONTAINSTAGSASSET);

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected Object mapRow(ResultSet rs, int rowNumber)
			throws SQLException {
			return new Integer(rs.getInt("COUNT_VALUE"));
		}

		protected boolean contains(long entryId, long assetId) {
			List results = execute(new Object[] {
						new Long(entryId), new Long(assetId)
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

	protected class AddTagsAsset extends SqlUpdate {
		protected AddTagsAsset(TagsEntryPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"INSERT INTO TagsAssets_TagsEntries (entryId, assetId) VALUES (?, ?)");

			_persistenceImpl = persistenceImpl;

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void add(long entryId, long assetId) {
			if (!_persistenceImpl.containsTagsAsset.contains(entryId, assetId)) {
				update(new Object[] { new Long(entryId), new Long(assetId) });
			}
		}

		private TagsEntryPersistenceImpl _persistenceImpl;
	}

	protected class ClearTagsAssets extends SqlUpdate {
		protected ClearTagsAssets(TagsEntryPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM TagsAssets_TagsEntries WHERE entryId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void clear(long entryId) {
			update(new Object[] { new Long(entryId) });
		}
	}

	protected class RemoveTagsAsset extends SqlUpdate {
		protected RemoveTagsAsset(TagsEntryPersistenceImpl persistenceImpl) {
			super(persistenceImpl.getDataSource(),
				"DELETE FROM TagsAssets_TagsEntries WHERE entryId = ? AND assetId = ?");

			declareParameter(new SqlParameter(Types.BIGINT));
			declareParameter(new SqlParameter(Types.BIGINT));

			compile();
		}

		protected void remove(long entryId, long assetId) {
			update(new Object[] { new Long(entryId), new Long(assetId) });
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

	private static final String _SQL_GETTAGSASSETS = "SELECT {TagsAsset.*} FROM TagsAsset INNER JOIN TagsAssets_TagsEntries ON (TagsAssets_TagsEntries.assetId = TagsAsset.assetId) WHERE (TagsAssets_TagsEntries.entryId = ?)";
	private static final String _SQL_GETTAGSASSETSSIZE = "SELECT COUNT(*) AS COUNT_VALUE FROM TagsAssets_TagsEntries WHERE entryId = ?";
	private static final String _SQL_CONTAINSTAGSASSET = "SELECT COUNT(*) AS COUNT_VALUE FROM TagsAssets_TagsEntries WHERE entryId = ? AND assetId = ?";
	private static final String _LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.tags.model.TagsEntry"));
	private static Log _log = LogFactory.getLog(TagsEntryPersistenceImpl.class);
}