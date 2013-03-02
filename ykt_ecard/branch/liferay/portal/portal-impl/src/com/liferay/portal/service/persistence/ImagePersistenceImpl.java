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

import com.liferay.portal.NoSuchImageException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQuery;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Image;
import com.liferay.portal.model.ModelListener;
import com.liferay.portal.model.impl.ImageImpl;
import com.liferay.portal.model.impl.ImageModelImpl;
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
 * <a href="ImagePersistenceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ImagePersistenceImpl extends BasePersistence
	implements ImagePersistence {
	public Image create(long imageId) {
		Image image = new ImageImpl();

		image.setNew(true);
		image.setPrimaryKey(imageId);

		return image;
	}

	public Image remove(long imageId)
		throws NoSuchImageException, SystemException {
		Session session = null;

		try {
			session = openSession();

			Image image = (Image)session.get(ImageImpl.class, new Long(imageId));

			if (image == null) {
				if (_log.isWarnEnabled()) {
					_log.warn("No Image exists with the primary key " +
						imageId);
				}

				throw new NoSuchImageException(
					"No Image exists with the primary key " + imageId);
			}

			return remove(image);
		}
		catch (NoSuchImageException nsee) {
			throw nsee;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public Image remove(Image image) throws SystemException {
		ModelListener listener = _getListener();

		if (listener != null) {
			listener.onBeforeRemove(image);
		}

		image = removeImpl(image);

		if (listener != null) {
			listener.onAfterRemove(image);
		}

		return image;
	}

	protected Image removeImpl(Image image) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			session.delete(image);

			session.flush();

			return image;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Image.class.getName());
		}
	}

	public Image update(Image image) throws SystemException {
		return update(image, false);
	}

	public Image update(Image image, boolean merge) throws SystemException {
		ModelListener listener = _getListener();

		boolean isNew = image.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(image);
			}
			else {
				listener.onBeforeUpdate(image);
			}
		}

		image = updateImpl(image, merge);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(image);
			}
			else {
				listener.onAfterUpdate(image);
			}
		}

		return image;
	}

	public Image updateImpl(com.liferay.portal.model.Image image, boolean merge)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			if (merge) {
				session.merge(image);
			}
			else {
				if (image.isNew()) {
					session.save(image);
				}
			}

			session.flush();

			image.setNew(false);

			return image;
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);

			FinderCache.clearCache(Image.class.getName());
		}
	}

	public Image findByPrimaryKey(long imageId)
		throws NoSuchImageException, SystemException {
		Image image = fetchByPrimaryKey(imageId);

		if (image == null) {
			if (_log.isWarnEnabled()) {
				_log.warn("No Image exists with the primary key " + imageId);
			}

			throw new NoSuchImageException(
				"No Image exists with the primary key " + imageId);
		}

		return image;
	}

	public Image fetchByPrimaryKey(long imageId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			return (Image)session.get(ImageImpl.class, new Long(imageId));
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			closeSession(session);
		}
	}

	public List findBySize(int size) throws SystemException {
		boolean finderClassNameCacheEnabled = ImageModelImpl.CACHE_ENABLED;
		String finderClassName = Image.class.getName();
		String finderMethodName = "findBySize";
		String[] finderParams = new String[] { Integer.class.getName() };
		Object[] finderArgs = new Object[] { new Integer(size) };

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

				query.append("FROM com.liferay.portal.model.Image WHERE ");

				query.append("size_ < ?");

				query.append(" ");

				query.append("ORDER BY ");

				query.append("imageId ASC");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setInteger(queryPos++, size);

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

	public List findBySize(int size, int begin, int end)
		throws SystemException {
		return findBySize(size, begin, end, null);
	}

	public List findBySize(int size, int begin, int end, OrderByComparator obc)
		throws SystemException {
		boolean finderClassNameCacheEnabled = ImageModelImpl.CACHE_ENABLED;
		String finderClassName = Image.class.getName();
		String finderMethodName = "findBySize";
		String[] finderParams = new String[] {
				Integer.class.getName(),
				
				"java.lang.Integer", "java.lang.Integer",
				"com.liferay.portal.kernel.util.OrderByComparator"
			};
		Object[] finderArgs = new Object[] {
				new Integer(size),
				
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

				query.append("FROM com.liferay.portal.model.Image WHERE ");

				query.append("size_ < ?");

				query.append(" ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("imageId ASC");
				}

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setInteger(queryPos++, size);

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

	public Image findBySize_First(int size, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		List list = findBySize(size, 0, 1, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Image exists with the key {");

			msg.append("size=" + size);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchImageException(msg.toString());
		}
		else {
			return (Image)list.get(0);
		}
	}

	public Image findBySize_Last(int size, OrderByComparator obc)
		throws NoSuchImageException, SystemException {
		int count = countBySize(size);

		List list = findBySize(size, count - 1, count, obc);

		if (list.size() == 0) {
			StringMaker msg = new StringMaker();

			msg.append("No Image exists with the key {");

			msg.append("size=" + size);

			msg.append(StringPool.CLOSE_CURLY_BRACE);

			throw new NoSuchImageException(msg.toString());
		}
		else {
			return (Image)list.get(0);
		}
	}

	public Image[] findBySize_PrevAndNext(long imageId, int size,
		OrderByComparator obc) throws NoSuchImageException, SystemException {
		Image image = findByPrimaryKey(imageId);

		int count = countBySize(size);

		Session session = null;

		try {
			session = openSession();

			StringMaker query = new StringMaker();

			query.append("FROM com.liferay.portal.model.Image WHERE ");

			query.append("size_ < ?");

			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY ");
				query.append(obc.getOrderBy());
			}

			else {
				query.append("ORDER BY ");

				query.append("imageId ASC");
			}

			Query q = session.createQuery(query.toString());

			int queryPos = 0;

			q.setInteger(queryPos++, size);

			Object[] objArray = QueryUtil.getPrevAndNext(q, count, obc, image);

			Image[] array = new ImageImpl[3];

			array[0] = (Image)objArray[0];
			array[1] = (Image)objArray[1];
			array[2] = (Image)objArray[2];

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
		boolean finderClassNameCacheEnabled = ImageModelImpl.CACHE_ENABLED;
		String finderClassName = Image.class.getName();
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

				query.append("FROM com.liferay.portal.model.Image ");

				if (obc != null) {
					query.append("ORDER BY ");
					query.append(obc.getOrderBy());
				}

				else {
					query.append("ORDER BY ");

					query.append("imageId ASC");
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

	public void removeBySize(int size) throws SystemException {
		Iterator itr = findBySize(size).iterator();

		while (itr.hasNext()) {
			Image image = (Image)itr.next();

			remove(image);
		}
	}

	public void removeAll() throws SystemException {
		Iterator itr = findAll().iterator();

		while (itr.hasNext()) {
			remove((Image)itr.next());
		}
	}

	public int countBySize(int size) throws SystemException {
		boolean finderClassNameCacheEnabled = ImageModelImpl.CACHE_ENABLED;
		String finderClassName = Image.class.getName();
		String finderMethodName = "countBySize";
		String[] finderParams = new String[] { Integer.class.getName() };
		Object[] finderArgs = new Object[] { new Integer(size) };

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
				query.append("FROM com.liferay.portal.model.Image WHERE ");

				query.append("size_ < ?");

				query.append(" ");

				Query q = session.createQuery(query.toString());

				int queryPos = 0;

				q.setInteger(queryPos++, size);

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
		boolean finderClassNameCacheEnabled = ImageModelImpl.CACHE_ENABLED;
		String finderClassName = Image.class.getName();
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
						"SELECT COUNT(*) FROM com.liferay.portal.model.Image");

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
				"value.object.listener.com.liferay.portal.model.Image"));
	private static Log _log = LogFactory.getLog(ImagePersistenceImpl.class);
}