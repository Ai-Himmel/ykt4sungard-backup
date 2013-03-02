/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portlet.shopping.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.util.HibernateUtil;

import com.liferay.portlet.shopping.NoSuchCategoryException;

import com.liferay.util.dao.hibernate.OrderByComparator;
import com.liferay.util.lang.FastStringBuffer;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.ScrollableResults;
import org.hibernate.Session;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="ShoppingCategoryPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingCategoryPersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingCategory create(
		String categoryId) {
		return new com.liferay.portlet.shopping.model.ShoppingCategory(categoryId);
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory remove(
		String categoryId) throws NoSuchCategoryException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)session.get(ShoppingCategoryHBM.class,
					categoryId);

			if (shoppingCategoryHBM == null) {
				_log.warn("No ShoppingCategory exists with the primary key of " +
					categoryId.toString());
				throw new NoSuchCategoryException(categoryId.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory =
				ShoppingCategoryHBMUtil.model(shoppingCategoryHBM);
			session.delete(shoppingCategoryHBM);
			session.flush();
			ShoppingCategoryPool.remove(categoryId);

			return shoppingCategory;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory update(
		com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingCategory.isNew() || shoppingCategory.isModified()) {
				session = openSession();

				if (shoppingCategory.isNew()) {
					ShoppingCategoryHBM shoppingCategoryHBM = new ShoppingCategoryHBM(shoppingCategory.getCategoryId(),
							shoppingCategory.getCompanyId(),
							shoppingCategory.getCreateDate(),
							shoppingCategory.getModifiedDate(),
							shoppingCategory.getParentCategoryId(),
							shoppingCategory.getName());
					session.save(shoppingCategoryHBM);
					session.flush();
				}
				else {
					ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)session.get(ShoppingCategoryHBM.class,
							shoppingCategory.getPrimaryKey());

					if (shoppingCategoryHBM != null) {
						shoppingCategoryHBM.setCompanyId(shoppingCategory.getCompanyId());
						shoppingCategoryHBM.setCreateDate(shoppingCategory.getCreateDate());
						shoppingCategoryHBM.setModifiedDate(shoppingCategory.getModifiedDate());
						shoppingCategoryHBM.setParentCategoryId(shoppingCategory.getParentCategoryId());
						shoppingCategoryHBM.setName(shoppingCategory.getName());
						session.flush();
					}
					else {
						shoppingCategoryHBM = new ShoppingCategoryHBM(shoppingCategory.getCategoryId(),
								shoppingCategory.getCompanyId(),
								shoppingCategory.getCreateDate(),
								shoppingCategory.getModifiedDate(),
								shoppingCategory.getParentCategoryId(),
								shoppingCategory.getName());
						session.save(shoppingCategoryHBM);
						session.flush();
					}
				}

				shoppingCategory.setNew(false);
				shoppingCategory.setModified(false);
				shoppingCategory.protect();
				ShoppingCategoryPool.put(shoppingCategory.getPrimaryKey(),
					shoppingCategory);
			}

			return shoppingCategory;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory findByPrimaryKey(
		String categoryId) throws NoSuchCategoryException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory = ShoppingCategoryPool.get(categoryId);
		Session session = null;

		try {
			if (shoppingCategory == null) {
				session = openSession();

				ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)session.get(ShoppingCategoryHBM.class,
						categoryId);

				if (shoppingCategoryHBM == null) {
					_log.warn(
						"No ShoppingCategory exists with the primary key of " +
						categoryId.toString());
					throw new NoSuchCategoryException(categoryId.toString());
				}

				shoppingCategory = ShoppingCategoryHBMUtil.model(shoppingCategoryHBM);
			}

			return shoppingCategory;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentCategoryId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
				list.add(ShoppingCategoryHBMUtil.model(shoppingCategoryHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByCompanyId(String companyId, int begin, int end)
		throws SystemException {
		return findByCompanyId(companyId, begin, end, null);
	}

	public List findByCompanyId(String companyId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentCategoryId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
					list.add(ShoppingCategoryHBMUtil.model(shoppingCategoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)sr.get(0);
						list.add(ShoppingCategoryHBMUtil.model(
								shoppingCategoryHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory findByCompanyId_First(
		String companyId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		List list = findByCompanyId(companyId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCategory)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory findByCompanyId_Last(
		String companyId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		int count = countByCompanyId(companyId);
		List list = findByCompanyId(companyId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCategory)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory[] findByCompanyId_PrevAndNext(
		String categoryId, String companyId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory = findByPrimaryKey(categoryId);
		int count = countByCompanyId(companyId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentCategoryId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			com.liferay.portlet.shopping.model.ShoppingCategory[] array = new com.liferay.portlet.shopping.model.ShoppingCategory[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)sr.get(0);

					if (shoppingCategoryHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingCategory curShoppingCategory =
						ShoppingCategoryHBMUtil.model(shoppingCategoryHBM);
					int value = obc.compare(shoppingCategory,
							curShoppingCategory);

					if (value == 0) {
						if (!shoppingCategory.equals(curShoppingCategory)) {
							break;
						}

						array[1] = curShoppingCategory;

						if (sr.previous()) {
							array[0] = ShoppingCategoryHBMUtil.model((ShoppingCategoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingCategoryHBMUtil.model((ShoppingCategoryHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByC_P(String companyId, String parentCategoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentCategoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentCategoryId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentCategoryId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
				list.add(ShoppingCategoryHBMUtil.model(shoppingCategoryHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByC_P(String companyId, String parentCategoryId, int begin,
		int end) throws SystemException {
		return findByC_P(companyId, parentCategoryId, begin, end, null);
	}

	public List findByC_P(String companyId, String parentCategoryId, int begin,
		int end, OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentCategoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentCategoryId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentCategoryId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
					list.add(ShoppingCategoryHBMUtil.model(shoppingCategoryHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)sr.get(0);
						list.add(ShoppingCategoryHBMUtil.model(
								shoppingCategoryHBM));

						if (!sr.next()) {
							break;
						}
					}
				}
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory findByC_P_First(
		String companyId, String parentCategoryId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		List list = findByC_P(companyId, parentCategoryId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCategory)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory findByC_P_Last(
		String companyId, String parentCategoryId, OrderByComparator obc)
		throws NoSuchCategoryException, SystemException {
		int count = countByC_P(companyId, parentCategoryId);
		List list = findByC_P(companyId, parentCategoryId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchCategoryException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingCategory)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingCategory[] findByC_P_PrevAndNext(
		String categoryId, String companyId, String parentCategoryId,
		OrderByComparator obc) throws NoSuchCategoryException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingCategory shoppingCategory = findByPrimaryKey(categoryId);
		int count = countByC_P(companyId, parentCategoryId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentCategoryId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("parentCategoryId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentCategoryId);

			com.liferay.portlet.shopping.model.ShoppingCategory[] array = new com.liferay.portlet.shopping.model.ShoppingCategory[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)sr.get(0);

					if (shoppingCategoryHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingCategory curShoppingCategory =
						ShoppingCategoryHBMUtil.model(shoppingCategoryHBM);
					int value = obc.compare(shoppingCategory,
							curShoppingCategory);

					if (value == 0) {
						if (!shoppingCategory.equals(curShoppingCategory)) {
							break;
						}

						array[1] = curShoppingCategory;

						if (sr.previous()) {
							array[0] = ShoppingCategoryHBMUtil.model((ShoppingCategoryHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingCategoryHBMUtil.model((ShoppingCategoryHBM)sr.get(
										0));
						}

						break;
					}

					if (count == 1) {
						break;
					}

					count = (int)Math.ceil(count / 2.0);

					if (value < 0) {
						if (!sr.scroll(count * -1)) {
							break;
						}
					}
					else {
						if (!sr.scroll(count)) {
							break;
						}
					}
				}
			}

			return array;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findAll() throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM ");
			query.append("ORDER BY ");
			query.append("parentCategoryId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
				list.add(ShoppingCategoryHBMUtil.model(shoppingCategoryHBM));
			}

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentCategoryId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
				ShoppingCategoryPool.remove((String)shoppingCategoryHBM.getPrimaryKey());
				session.delete(shoppingCategoryHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public void removeByC_P(String companyId, String parentCategoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentCategoryId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("parentCategoryId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentCategoryId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingCategoryHBM shoppingCategoryHBM = (ShoppingCategoryHBM)itr.next();
				ShoppingCategoryPool.remove((String)shoppingCategoryHBM.getPrimaryKey());
				session.delete(shoppingCategoryHBM);
			}

			session.flush();
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByCompanyId(String companyId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public int countByC_P(String companyId, String parentCategoryId)
		throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingCategory IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingCategoryHBM WHERE ");
			query.append("companyId = ?");
			query.append(" AND ");
			query.append("parentCategoryId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, companyId);
			q.setString(queryPos++, parentCategoryId);

			Iterator itr = q.list().iterator();

			if (itr.hasNext()) {
				Integer count = (Integer)itr.next();

				if (count != null) {
					return count.intValue();
				}
			}

			return 0;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	private static final Log _log = LogFactory.getLog(ShoppingCategoryPersistence.class);
}