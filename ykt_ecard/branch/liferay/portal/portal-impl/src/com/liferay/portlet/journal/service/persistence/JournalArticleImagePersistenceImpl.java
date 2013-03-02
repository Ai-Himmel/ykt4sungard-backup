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

import com.liferay.portlet.journal.NoSuchArticleImageException;
import com.liferay.portlet.journal.model.JournalArticleImage;
import com.liferay.portlet.journal.model.impl.JournalArticleImageImpl;
import com.liferay.portlet.journal.model.impl.JournalArticleImageModelImpl;

import com.liferay.util.dao.hibernate.QueryUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.Query;
import org.hibernate.Session;

import java.util.Collections;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="JournalArticleImagePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalArticleImagePersistenceImpl extends BasePersistence
	implements JournalArticleImagePersistence {
	public JournalArticleImage create(long articleImageId) {
		JournalArticleImage journalArticleImage = new JournalArticleImageImpl();

		journalArticleImage.setNew(true);
		journalArticleImage.setPrimaryKey(articleImageId);

		return journalArticleImage;
	}

	public JournalArticleImage remove(long articleImageId)
		throws NoSuchArticleImageException, SystemException {
		Session session = null;

		try {
			session = openSession();

			JournalArticleImage journalArticleImage = (JournalArticleImage)session.get(JournalArticleImageImpl.class,
					new Long(articleImageId));

			if (journalArticleImage == null) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"No JournalArticleImage exists with the primary key " +
						articleImageId);
				}

				throw new NoSuchArticleImageException(
					"No JournalArticleImage exists with the primary key " +
					articleImageId);
			}

			return remove(journalArticleImage);
		}
		catch (NoSuchArticleImageException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalArticleImage remove(JournalArticleImage journalArticleImage)
		throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(journalArticleImage);
		}

		journalArticleImage = removeImpl(journalArticleImage);

		if (listener != null) {
			listener.onAfterRemove(journalArticleImage);
		}

		return journalArticleImage;
	}

	protected JournalArticleImage removeImpl(
		JournalArticleImage journalArticleImage) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(journalArticleImage);

			session.flush();

			return journalArticleImage;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(JournalArticleImage.class.getName());
		}
	}

	public JournalArticleImage update(JournalArticleImage journalArticleImage)
		throws SystemException {
		return update(journalArticleImage, false);
	}

	public JournalArticleImage update(JournalArticleImage journalArticleImage,
		boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = journalArticleImage.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(journalArticleImage);
			}
			else {
				listener.onBeforeUpdate(journalArticleImage);
			}
		}

		journalArticleImage = updateImpl(journalArticleImage, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(journalArticleImage);
			}
			else {
				listener.onAfterUpdate(journalArticleImage);
			}
		}

		return journalArticleImage;
	}

	public JournalArticleImage updateImpl(
		com.liferay.portlet.journal.model.JournalArticleImage journalArticleImage,
		boolean merge) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(journalArticleImage);
			}
			else {
				if (journalArticleImage.isNew()) {
					session.save(journalArticleImage);
				}
			}

			session.flush();

			journalArticleImage.setNew(false);

			return journalArticleImage;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(JournalArticleImage.class.getName());
		}
	}

	public JournalArticleImage findByPrimaryKey(long articleImageId)
		throws NoSuchArticleImageException, SystemException {
		JournalArticleImage journalArticleImage = fetchByPrimaryKey(articleImageId);

		if (journalArticleImage == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No JournalArticleImage exists with the primary key " +
					articleImageId);
			}

			throw new NoSuchArticleImageException(
				"No JournalArticleImage exists with the primary key " +
				articleImageId);
		}

		return journalArticleImage;
	}

	public JournalArticleImage fetchByPrimaryKey(long articleImageId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (JournalArticleImage)session.get(JournalArticleImageImpl.class,
				new Long(articleImageId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" ");

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
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
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

	public JournalArticleImage findByGroupId_First(long groupId,
		OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		List list = findByGroupId(groupId, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchArticleImageException(msg.toString());
		}
		else {
			return (JournalArticleImage)list.get(0);
		}
	}

	public JournalArticleImage findByGroupId_Last(long groupId,
		OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		int count = countByGroupId(groupId);

		List list = findByGroupId(groupId, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchArticleImageException(msg.toString());
		}
		else {
			return (JournalArticleImage)list.get(0);
		}
	}

	public JournalArticleImage[] findByGroupId_PrevAndNext(
		long articleImageId, long groupId, OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		JournalArticleImage journalArticleImage = findByPrimaryKey(articleImageId);

		int count = countByGroupId(groupId);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

			query.append("groupId = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setLong(queryPos++, groupId);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalArticleImage);

			JournalArticleImage[] array = new JournalArticleImageImpl[3];

			array[0] = (JournalArticleImage)objArray[0];
			array[1] = (JournalArticleImage)objArray[1];
			array[2] = (JournalArticleImage)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByTempImage(boolean tempImage) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "findByTempImage";
		String[] finderParams = new String[] { Boolean.class.getName() };
		Object[] finderArgs = new Object[] { Boolean.valueOf(tempImage) };

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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("tempImage = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setBoolean(queryPos++, tempImage);

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

	public List findByTempImage(boolean tempImage, int begin, int end)
		throws SystemException {
		return findByTempImage(tempImage, begin, end, null);
	}

	public List findByTempImage(boolean tempImage, int begin, int end,
		OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "findByTempImage";
		String[] finderParams = new String[] {
				Boolean.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				Boolean.valueOf(tempImage),
				
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("tempImage = ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setBoolean(queryPos++, tempImage);

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

	public JournalArticleImage findByTempImage_First(boolean tempImage,
		OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		List list = findByTempImage(tempImage, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("tempImage=" + tempImage);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchArticleImageException(msg.toString());
		}
		else {
			return (JournalArticleImage)list.get(0);
		}
	}

	public JournalArticleImage findByTempImage_Last(boolean tempImage,
		OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		int count = countByTempImage(tempImage);

		List list = findByTempImage(tempImage, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("tempImage=" + tempImage);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchArticleImageException(msg.toString());
		}
		else {
			return (JournalArticleImage)list.get(0);
		}
	}

	public JournalArticleImage[] findByTempImage_PrevAndNext(
		long articleImageId, boolean tempImage, OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		JournalArticleImage journalArticleImage = findByPrimaryKey(articleImageId);

		int count = countByTempImage(tempImage);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

			query.append("tempImage = ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setBoolean(queryPos++, tempImage);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalArticleImage);

			JournalArticleImage[] array = new JournalArticleImageImpl[3];

			array[0] = (JournalArticleImage)objArray[0];
			array[1] = (JournalArticleImage)objArray[1];
			array[2] = (JournalArticleImage)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findByG_A_V(long groupId, String articleId, double version)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "findByG_A_V";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				articleId, new Double(version)
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

				q.setDouble(queryPos++, version);

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

	public List findByG_A_V(long groupId, String articleId, double version,
		int begin, int end) throws SystemException {
		return findByG_A_V(groupId, articleId, version, begin, end, null);
	}

	public List findByG_A_V(long groupId, String articleId, double version,
		int begin, int end, OrderByComparator obc) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "findByG_A_V";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				articleId, new Double(version),
				
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

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

				q.setDouble(queryPos++, version);

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

	public JournalArticleImage findByG_A_V_First(long groupId,
		String articleId, double version, OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		List list = findByG_A_V(groupId, articleId, version, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(", ");
			msg.append("version=" + version);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchArticleImageException(msg.toString());
		}
		else {
			return (JournalArticleImage)list.get(0);
		}
	}

	public JournalArticleImage findByG_A_V_Last(long groupId, String articleId,
		double version, OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		int count = countByG_A_V(groupId, articleId, version);

		List list = findByG_A_V(groupId, articleId, version, count - 1, count,
				obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(", ");
			msg.append("version=" + version);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchArticleImageException(msg.toString());
		}
		else {
			return (JournalArticleImage)list.get(0);
		}
	}

	public JournalArticleImage[] findByG_A_V_PrevAndNext(long articleImageId,
		long groupId, String articleId, double version, OrderByComparator obc)
		throws NoSuchArticleImageException, SystemException {
		JournalArticleImage journalArticleImage = findByPrimaryKey(articleImageId);

		int count = countByG_A_V(groupId, articleId, version);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append(
				"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

			query.append("groupId = ?");

			query.append(" AND ");

			if (articleId == null) {
				query.append("articleId IS NULL");
			}
			else {
				query.append("articleId = ?");
			}

			query.append(" AND ");

			query.append("version = ?");

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

			q.setDouble(queryPos++, version);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc,
					journalArticleImage);

			JournalArticleImage[] array = new JournalArticleImageImpl[3];

			array[0] = (JournalArticleImage)objArray[0];
			array[1] = (JournalArticleImage)objArray[1];
			array[2] = (JournalArticleImage)objArray[2];

			return array;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public JournalArticleImage findByG_A_V_E_L(long groupId, String articleId,
		double version, String elName, String languageId)
		throws NoSuchArticleImageException, SystemException {
		JournalArticleImage journalArticleImage = fetchByG_A_V_E_L(groupId,
				articleId, version, elName, languageId);

		if (journalArticleImage == null) {
			StringMaker msg = new StringMaker();

			msg.append("No JournalArticleImage exists with the key {");

			msg.append("groupId=" + groupId);

			msg.append(", ");
			msg.append("articleId=" + articleId);

			msg.append(", ");
			msg.append("version=" + version);

			msg.append(", ");
			msg.append("elName=" + elName);

			msg.append(", ");
			msg.append("languageId=" + languageId);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			if (_log.isWarnEnabled()) {
				_log.warn(msg.toString());
			}

			throw new NoSuchArticleImageException(msg.toString());
		}

		return journalArticleImage;
	}

	public JournalArticleImage fetchByG_A_V_E_L(long groupId, String articleId,
		double version, String elName, String languageId)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "fetchByG_A_V_E_L";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName(), String.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				articleId, new Double(version),
				
				elName,
				
				languageId
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

				query.append(" AND ");

				if (elName == null) {
					query.append("elName IS NULL");
				}
				else {
					query.append("elName = ?");
				}

				query.append(" AND ");

				if (languageId == null) {
					query.append("languageId IS NULL");
				}
				else {
					query.append("languageId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

				q.setDouble(queryPos++, version);

				if (elName != null) {
					q.setString(queryPos++, elName);
				}

				if (languageId != null) {
					q.setString(queryPos++, languageId);
				}

				List list = q.list();

				FinderCache.putResult(finderClassNameCacheEnabled,
					finderClassName, finderMethodName, finderParams,
					finderArgs, list);

				if (list.size() == 0) {
					return null;
				}
				else {
					return (JournalArticleImage)list.get(0);
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
				return (JournalArticleImage)list.get(0);
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
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage ");

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

	public void removeByGroupId(long groupId) throws SystemException {
		Iterator itr = findByGroupId(groupId).iterator();

		while (itr.hasNext()) {
			JournalArticleImage journalArticleImage = (JournalArticleImage)itr.next();

			remove(journalArticleImage);
		}
	}

	public void removeByTempImage(boolean tempImage) throws SystemException {
		Iterator itr = findByTempImage(tempImage).iterator();

		while (itr.hasNext()) {
			JournalArticleImage journalArticleImage = (JournalArticleImage)itr.next();

			remove(journalArticleImage);
		}
	}

	public void removeByG_A_V(long groupId, String articleId, double version)
		throws SystemException {
		Iterator itr = findByG_A_V(groupId, articleId, version).iterator();

		while (itr.hasNext()) {
			JournalArticleImage journalArticleImage = (JournalArticleImage)itr.next();

			remove(journalArticleImage);
		}
	}

	public void removeByG_A_V_E_L(long groupId, String articleId,
		double version, String elName, String languageId)
		throws NoSuchArticleImageException, SystemException {
		JournalArticleImage journalArticleImage = findByG_A_V_E_L(groupId,
				articleId, version, elName, languageId);

		remove(journalArticleImage);
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((JournalArticleImage)itr.next());
		}
	}

	public int countByGroupId(long groupId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

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

	public int countByTempImage(boolean tempImage) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "countByTempImage";
		String[] finderParams = new String[] { Boolean.class.getName() };
		Object[] finderArgs = new Object[] { Boolean.valueOf(tempImage) };

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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("tempImage = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setBoolean(queryPos++, tempImage);

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

	public int countByG_A_V(long groupId, String articleId, double version)
		throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "countByG_A_V";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				articleId, new Double(version)
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
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

	public int countByG_A_V_E_L(long groupId, String articleId, double version,
		String elName, String languageId) throws SystemException {
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
		String finderMethodName = "countByG_A_V_E_L";
		String[] finderParams = new String[] {
				Long.class.getName(), String.class.getName(),
				Double.class.getName(), String.class.getName(),
				String.class.getName()
			};
		Object[] finderArgs = new Object[] {
				new Long(groupId),
				
				articleId, new Double(version),
				
				elName,
				
				languageId
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
					"FROM com.liferay.portlet.journal.model.JournalArticleImage WHERE ");

				query.append("groupId = ?");

				query.append(" AND ");

				if (articleId == null) {
					query.append("articleId IS NULL");
				}
				else {
					query.append("articleId = ?");
				}

				query.append(" AND ");

				query.append("version = ?");

				query.append(" AND ");

				if (elName == null) {
					query.append("elName IS NULL");
				}
				else {
					query.append("elName = ?");
				}

				query.append(" AND ");

				if (languageId == null) {
					query.append("languageId IS NULL");
				}
				else {
					query.append("languageId = ?");
				}

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setLong(queryPos++, groupId);

				if (articleId != null) {
					q.setString(queryPos++, articleId);
				}

				q.setDouble(queryPos++, version);

				if (elName != null) {
					q.setString(queryPos++, elName);
				}

				if (languageId != null) {
					q.setString(queryPos++, languageId);
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
		boolean finderClassNameCacheEnabled = JournalArticleImageModelImpl.CACHE_ENABLED;
		String finderClassName = JournalArticleImage.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portlet.journal.model.JournalArticleImage");

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
				"value.object.listener.com.liferay.portlet.journal.model.JournalArticleImage"));
	private static Log _log = LogFactory.getLog(JournalArticleImagePersistenceImpl.class);
}