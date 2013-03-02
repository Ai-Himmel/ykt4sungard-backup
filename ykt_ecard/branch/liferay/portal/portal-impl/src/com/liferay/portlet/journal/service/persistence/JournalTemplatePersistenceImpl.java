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
import com.liferay.portal.kernel.uuid.PortalUUIDUtil;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.spring.hibernate.FinderCache;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.model.impl.JournalTemplateImpl;
import com.liferay.portlet.journal.model.impl.JournalTemplateModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="JournalTemplatePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalTemplatePersistenceImpl extends BasePersistence
	implements JournalTemplatePersistence {
	public JournalTemplate create(long id) {
		JournalTemplate journalTemplate = new JournalTemplateImpl();

		journalTemplate.setNew(true);
		journalTemplate.setPrimaryKey(id);

		String uuid = PortalUUIDUtil.generate();

		journalTemplate.setUuid(uuid);

		return journalTemplate;
	}

	public JournalTemplate remove(long id)
		throws NoSuchTemplateException, SystemException {
		Session session = null;

		try {
			session = openSession();

			JournalTemplate journalTemplate = (JournalTemplate)session.get(JournalTemplateImpl.class,
					new Long(id));

			if (journalTemplate == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No JournalTemplate exists with the primary key " +
						id);
				}

				throw new NoSuchTemplateException(
					"No JournalTemplate exists with the primary key " + id);
			}

			return remove(journalTemplate);
		}
		catch (NoSuchTemplateException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalTemplate remove(JournalTemplate journalTemplate)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(journalTemplate);
		}

		journalTemplate = removeImpl(journalTemplate);

		if (listener != null) {
			listener.onAfterRemove(journalTemplate);
		}

		return journalTemplate;
	}

	protected JournalTemplate removeImpl(JournalTemplate journalTemplate)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(journalTemplate);

			session.flush();

			return journalTemplate;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(JournalTemplate.class.getName());
		}
	}

	public JournalTemplate update(JournalTemplate journalTemplate)
		throws SystemException {
		return update(journalTemplate, false);
	}

	public JournalTemplate update(JournalTemplate journalTemplate, boolean merge)
		throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = journalTemplate.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(journalTemplate);
			}
			else {
				listener.onBeforeUpdate(journalTemplate);
			}
		}

		journalTemplate = updateImpl(journalTemplate, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(journalTemplate);
			}
			else {
				listener.onAfterUpdate(journalTemplate);
			}
		}

		return journalTemplate;
	}

	public JournalTemplate updateImpl(
		com.liferay.portlet.journal.model.JournalTemplate journalTemplate,
		boolean merge) throws SystemException {
		if (Validator.isNull(journalTemplate.getUuid())) {
			String uuid = PortalUUIDUtil.generate();

			journalTemplate.setUuid(uuid);
		}

		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(journalTemplate);
			}
			else {
				if (journalTemplate.isNew()) {
					session.save(journalTemplate);
				}
			}

			session.flush();

			journalTemplate.setNew(false);

			return journalTemplate;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(JournalTemplate.class.getName());
		}
	}

	public JournalTemplate findByPrimaryKey(long id)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = fetchByPrimaryKey(id);

		if (journalTemplate == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No JournalTemplate exists with the primary key " +
					id);
			}

			throw new NoSuchTemplateException(
				"No JournalTemplate exists with the primary key " + id);
		}

		return journalTemplate;
	}

	public JournalTemplate fetchByPrimaryKey(long id) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (JournalTemplate)session.get(JournalTemplateImpl.class,
				new Long(id));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByUuid(String uuid) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "findByUuid";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { uuid };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
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

	public List findByUuid(String uuid, int begin, int end)
		throws SystemException {
		return findByUuid(uuid, begin, end, null);
	}

	public List findByUuid(String uuid, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "findByUuid";
		String[] finderParams = new String[] {
				String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				uuid,
				
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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("templateId ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
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

	public JournalTemplate findByUuid_First(String uuid, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		List list = findByUuid(uuid, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("uuid=" + uuid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate findByUuid_Last(String uuid, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		int count = countByUuid(uuid);

		List list = findByUuid(uuid, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("uuid=" + uuid);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate[] findByUuid_PrevAndNext(long id, String uuid,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findByPrimaryKey(id);

		int count = countByUuid(uuid);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

			if (uuid == null) {
				query.append("uuid_ IS NULL");
			}
			else {
				query.append("uuid_ = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			if (uuid != null) {
				q.setString(queryPos++, uuid);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalTemplate);

			JournalTemplate[] array = new JournalTemplateImpl[3];

			array[0] = (JournalTemplate)objArray[0];
			array[1] = (JournalTemplate)objArray[1];
			array[2] = (JournalTemplate)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalTemplate findByUUID_G(String uuid, long groupId)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = fetchByUUID_G(uuid, groupId);

		if (journalTemplate == null) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("uuid=" + uuid);

			msg.append(", ");
			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchTemplateException(msg.toString());
		}

		return journalTemplate;
	}

	public JournalTemplate fetchByUUID_G(String uuid, long groupId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "fetchByUUID_G";
		String[] finderParams = new String[] {
				String.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { uuid, new Long(groupId) };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" AND ");

				query.append("groupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
				}

				q.setLong(queryPos++, groupId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (JournalTemplate)list.get(0);
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
				return (JournalTemplate)list.get(0);
			}
		}
	}

	public List findByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

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
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
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

				query.append(
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("templateId ASC");
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

	public JournalTemplate findByGroupId_First(long groupId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate findByGroupId_Last(long groupId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate[] findByGroupId_PrevAndNext(long id, long groupId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findByPrimaryKey(id);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalTemplate);

			JournalTemplate[] array = new JournalTemplateImpl[3];

			array[0] = (JournalTemplate)objArray[0];
			array[1] = (JournalTemplate)objArray[1];
			array[2] = (JournalTemplate)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByTemplateId(String templateId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "findByTemplateId";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { templateId };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (templateId == null) {
					query.append("templateId IS NULL");
				}
				else {
					query.append("templateId = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (templateId != null) {
					q.setString(queryPos++, templateId);
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

	public List findByTemplateId(String templateId, int begin, int end)
		throws SystemException {
		return findByTemplateId(templateId, begin, end, null);
	}

	public List findByTemplateId(String templateId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "findByTemplateId";
		String[] finderParams = new String[] {
				String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				templateId,
				
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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (templateId == null) {
					query.append("templateId IS NULL");
				}
				else {
					query.append("templateId = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("templateId ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (templateId != null) {
					q.setString(queryPos++, templateId);
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

	public JournalTemplate findByTemplateId_First(String templateId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		List list = findByTemplateId(templateId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("templateId=" + templateId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate findByTemplateId_Last(String templateId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		int count = countByTemplateId(templateId);

		List list = findByTemplateId(templateId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("templateId=" + templateId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate[] findByTemplateId_PrevAndNext(long id,
		String templateId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findByPrimaryKey(id);

		int count = countByTemplateId(templateId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

			if (templateId == null) {
				query.append("templateId IS NULL");
			}
			else {
				query.append("templateId = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			if (templateId != null) {
				q.setString(queryPos++, templateId);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalTemplate);

			JournalTemplate[] array = new JournalTemplateImpl[3];

			array[0] = (JournalTemplate)objArray[0];
			array[1] = (JournalTemplate)objArray[1];
			array[2] = (JournalTemplate)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalTemplate findBySmallImageId(long smallImageId)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = fetchBySmallImageId(smallImageId);

		if (journalTemplate == null) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("smallImageId=" + smallImageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchTemplateException(msg.toString());
		}

		return journalTemplate;
	}

	public JournalTemplate fetchBySmallImageId(long smallImageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "fetchBySmallImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(smallImageId) };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("smallImageId = ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, smallImageId);

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (JournalTemplate)list.get(0);
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
				return (JournalTemplate)list.get(0);
			}
		}
	}

	public JournalTemplate findByG_T(long groupId, String templateId)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = fetchByG_T(groupId, templateId);

		if (journalTemplate == null) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("templateId=" + templateId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchTemplateException(msg.toString());
		}

		return journalTemplate;
	}

	public JournalTemplate fetchByG_T(long groupId, String templateId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "fetchByG_T";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), templateId };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (templateId == null) {
					query.append("templateId IS NULL");
				}
				else {
					query.append("templateId = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (templateId != null) {
					q.setString(queryPos++, templateId);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (JournalTemplate)list.get(0);
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
				return (JournalTemplate)list.get(0);
			}
		}
	}

	public List findByG_S(long groupId, String structureId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "findByG_S";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), structureId };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (structureId == null) {
					query.append("structureId IS NULL");
				}
				else {
					query.append("structureId = ?");
				}

				query.append(" ");

				query.append("ORDER BY ");

				query.append("templateId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (structureId != null) {
					q.setString(queryPos++, structureId);
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

	public List findByG_S(long groupId, String structureId, int begin, int end)
		throws SystemException {
		return findByG_S(groupId, structureId, begin, end, null);
	}

	public List findByG_S(long groupId, String structureId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "findByG_S";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				structureId,
				
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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (structureId == null) {
					query.append("structureId IS NULL");
				}
				else {
					query.append("structureId = ?");
				}

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("templateId ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (structureId != null) {
					q.setString(queryPos++, structureId);
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

	public JournalTemplate findByG_S_First(long groupId, String structureId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		List list = findByG_S(groupId, structureId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("structureId=" + structureId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate findByG_S_Last(long groupId, String structureId,
		OrderByComparator obc) throws NoSuchTemplateException, SystemException {
		int count = countByG_S(groupId, structureId);

		List list = findByG_S(groupId, structureId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalTemplate exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("structureId=" + structureId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchTemplateException(msg.toString());
		}
		else {
			return (JournalTemplate)list.get(0);
		}
	}

	public JournalTemplate[] findByG_S_PrevAndNext(long id, long groupId,
		String structureId, OrderByComparator obc)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findByPrimaryKey(id);

		int count = countByG_S(groupId, structureId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			if (structureId == null) {
				query.append("structureId IS NULL");
			}
			else {
				query.append("structureId = ?");
			}

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("templateId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			if (structureId != null) {
				q.setString(queryPos++, structureId);
			}

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalTemplate);

			JournalTemplate[] array = new JournalTemplateImpl[3];

			array[0] = (JournalTemplate)objArray[0];
			array[1] = (JournalTemplate)objArray[1];
			array[2] = (JournalTemplate)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
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
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
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
					"FROM com.liferay.portlet.journal.model.JournalTemplate ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("templateId ASC");
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

	public void removeByUuid(String uuid) throws SystemException {
		Iterator itr = findByUuid(uuid).iterator();

		while (itr.hasNext()) {
			JournalTemplate journalTemplate = (JournalTemplate)itr.next();

			remove(journalTemplate);
		}
	}

	public void removeByUUID_G(String uuid, long groupId)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findByUUID_G(uuid, groupId);

		remove(journalTemplate);
	}

	public void removeByGroupId(long groupId) throws SystemException {
		Iterator itr = findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			JournalTemplate journalTemplate = (JournalTemplate)itr.next();

			remove(journalTemplate);
		}
	}

	public void removeByTemplateId(String templateId) throws SystemException {
		Iterator itr = findByTemplateId(templateId).iterator();

		while (itr.hasNext()) {
			JournalTemplate journalTemplate = (JournalTemplate)itr.next();

			remove(journalTemplate);
		}
	}

	public void removeBySmallImageId(long smallImageId)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findBySmallImageId(smallImageId);

		remove(journalTemplate);
	}

	public void removeByG_T(long groupId, String templateId)
		throws NoSuchTemplateException, SystemException {
		JournalTemplate journalTemplate = findByG_T(groupId, templateId);

		remove(journalTemplate);
	}

	public void removeByG_S(long groupId, String structureId)
		throws SystemException {
		Iterator itr = findByG_S(groupId, structureId).iterator();

		while (itr.hasNext()) {
			JournalTemplate journalTemplate = (JournalTemplate)itr.next();

			remove(journalTemplate);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((JournalTemplate)itr.next());
		}
	}

	public int countByUuid(String uuid) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "countByUuid";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { uuid };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
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

	public int countByUUID_G(String uuid, long groupId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "countByUUID_G";
		String[] finderParams = new String[] {
				String.class.getName(), Long.class.getName()
			};
		Object[] finderArgs = new Object[] { uuid, new Long(groupId) };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (uuid == null) {
					query.append("uuid_ IS NULL");
				}
				else {
					query.append("uuid_ = ?");
				}

				query.append(" AND ");

				query.append("groupId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (uuid != null) {
					q.setString(queryPos++, uuid);
				}

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

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
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
				query.append(
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

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

	public int countByTemplateId(String templateId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "countByTemplateId";
		String[] finderParams = new String[] { String.class.getName() };
		Object[] finderArgs = new Object[] { templateId };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				if (templateId == null) {
					query.append("templateId IS NULL");
				}
				else {
					query.append("templateId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				if (templateId != null) {
					q.setString(queryPos++, templateId);
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

	public int countBySmallImageId(long smallImageId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "countBySmallImageId";
		String[] finderParams = new String[] { Long.class.getName() };
		Object[] finderArgs = new Object[] { new Long(smallImageId) };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("smallImageId = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, smallImageId);

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

	public int countByG_T(long groupId, String templateId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "countByG_T";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), templateId };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (templateId == null) {
					query.append("templateId IS NULL");
				}
				else {
					query.append("templateId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (templateId != null) {
					q.setString(queryPos++, templateId);
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

	public int countByG_S(long groupId, String structureId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
		String finderMethodName = "countByG_S";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName()
			};
		Object[] finderArgs = new Object[] { new Long(groupId), structureId };

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
					"FROM com.liferay.portlet.journal.model.JournalTemplate WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (structureId == null) {
					query.append("structureId IS NULL");
				}
				else {
					query.append("structureId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (structureId != null) {
					q.setString(queryPos++, structureId);
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
		boolean finderClassNameCacheEnabled = JournalTemplateModelImpl.CACHE_ENABLED;
		String finderClassName = JournalTemplate.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.journal.model.JournalTemplate");

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
				"value.object.listener.com.liferay.portlet.journal.model.JournalTemplate"));
	private static Log _log = LogFactory.getLog(JournalTemplatePersistenceImpl.class);
}