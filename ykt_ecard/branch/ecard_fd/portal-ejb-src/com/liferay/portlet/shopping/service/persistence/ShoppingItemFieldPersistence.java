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

import com.liferay.portlet.shopping.NoSuchItemFieldException;

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
 * <a href="ShoppingItemFieldPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemFieldPersistence extends BasePersistence {
	public com.liferay.portlet.shopping.model.ShoppingItemField create(
		String itemFieldId) {
		return new com.liferay.portlet.shopping.model.ShoppingItemField(itemFieldId);
	}

	public com.liferay.portlet.shopping.model.ShoppingItemField remove(
		String itemFieldId) throws NoSuchItemFieldException, SystemException {
		Session session = null;

		try {
			session = openSession();

			ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)session.get(ShoppingItemFieldHBM.class,
					itemFieldId);

			if (shoppingItemFieldHBM == null) {
				_log.warn(
					"No ShoppingItemField exists with the primary key of " +
					itemFieldId.toString());
				throw new NoSuchItemFieldException(itemFieldId.toString());
			}

			com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField =
				ShoppingItemFieldHBMUtil.model(shoppingItemFieldHBM);
			session.delete(shoppingItemFieldHBM);
			session.flush();
			ShoppingItemFieldPool.remove(itemFieldId);

			return shoppingItemField;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemField update(
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField)
		throws SystemException {
		Session session = null;

		try {
			if (shoppingItemField.isNew() || shoppingItemField.isModified()) {
				session = openSession();

				if (shoppingItemField.isNew()) {
					ShoppingItemFieldHBM shoppingItemFieldHBM = new ShoppingItemFieldHBM(shoppingItemField.getItemFieldId(),
							shoppingItemField.getItemId(),
							shoppingItemField.getName(),
							shoppingItemField.getValues(),
							shoppingItemField.getDescription());
					session.save(shoppingItemFieldHBM);
					session.flush();
				}
				else {
					ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)session.get(ShoppingItemFieldHBM.class,
							shoppingItemField.getPrimaryKey());

					if (shoppingItemFieldHBM != null) {
						shoppingItemFieldHBM.setItemId(shoppingItemField.getItemId());
						shoppingItemFieldHBM.setName(shoppingItemField.getName());
						shoppingItemFieldHBM.setValues(shoppingItemField.getValues());
						shoppingItemFieldHBM.setDescription(shoppingItemField.getDescription());
						session.flush();
					}
					else {
						shoppingItemFieldHBM = new ShoppingItemFieldHBM(shoppingItemField.getItemFieldId(),
								shoppingItemField.getItemId(),
								shoppingItemField.getName(),
								shoppingItemField.getValues(),
								shoppingItemField.getDescription());
						session.save(shoppingItemFieldHBM);
						session.flush();
					}
				}

				shoppingItemField.setNew(false);
				shoppingItemField.setModified(false);
				shoppingItemField.protect();
				ShoppingItemFieldPool.put(shoppingItemField.getPrimaryKey(),
					shoppingItemField);
			}

			return shoppingItemField;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemField findByPrimaryKey(
		String itemFieldId) throws NoSuchItemFieldException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField = ShoppingItemFieldPool.get(itemFieldId);
		Session session = null;

		try {
			if (shoppingItemField == null) {
				session = openSession();

				ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)session.get(ShoppingItemFieldHBM.class,
						itemFieldId);

				if (shoppingItemFieldHBM == null) {
					_log.warn(
						"No ShoppingItemField exists with the primary key of " +
						itemFieldId.toString());
					throw new NoSuchItemFieldException(itemFieldId.toString());
				}

				shoppingItemField = ShoppingItemFieldHBMUtil.model(shoppingItemFieldHBM);
			}

			return shoppingItemField;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemField IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)itr.next();
				list.add(ShoppingItemFieldHBMUtil.model(shoppingItemFieldHBM));
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

	public List findByItemId(String itemId, int begin, int end)
		throws SystemException {
		return findByItemId(itemId, begin, end, null);
	}

	public List findByItemId(String itemId, int begin, int end,
		OrderByComparator obc) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemField IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			List list = new ArrayList();

			if (getDialect().supportsLimit()) {
				q.setMaxResults(end - begin);
				q.setFirstResult(begin);

				Iterator itr = q.list().iterator();

				while (itr.hasNext()) {
					ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)itr.next();
					list.add(ShoppingItemFieldHBMUtil.model(
							shoppingItemFieldHBM));
				}
			}
			else {
				ScrollableResults sr = q.scroll();

				if (sr.first() && sr.scroll(begin)) {
					for (int i = begin; i < end; i++) {
						ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)sr.get(0);
						list.add(ShoppingItemFieldHBMUtil.model(
								shoppingItemFieldHBM));

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

	public com.liferay.portlet.shopping.model.ShoppingItemField findByItemId_First(
		String itemId, OrderByComparator obc)
		throws NoSuchItemFieldException, SystemException {
		List list = findByItemId(itemId, 0, 1, obc);

		if (list.size() == 0) {
			throw new NoSuchItemFieldException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItemField)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemField findByItemId_Last(
		String itemId, OrderByComparator obc)
		throws NoSuchItemFieldException, SystemException {
		int count = countByItemId(itemId);
		List list = findByItemId(itemId, count - 1, count, obc);

		if (list.size() == 0) {
			throw new NoSuchItemFieldException();
		}
		else {
			return (com.liferay.portlet.shopping.model.ShoppingItemField)list.get(0);
		}
	}

	public com.liferay.portlet.shopping.model.ShoppingItemField[] findByItemId_PrevAndNext(
		String itemFieldId, String itemId, OrderByComparator obc)
		throws NoSuchItemFieldException, SystemException {
		com.liferay.portlet.shopping.model.ShoppingItemField shoppingItemField = findByPrimaryKey(itemFieldId);
		int count = countByItemId(itemId);
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemField IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			if (obc != null) {
				query.append("ORDER BY " + obc.getOrderBy());
			}
			else {
				query.append("ORDER BY ");
				query.append("itemId ASC").append(", ");
				query.append("name ASC");
			}

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			com.liferay.portlet.shopping.model.ShoppingItemField[] array = new com.liferay.portlet.shopping.model.ShoppingItemField[3];
			ScrollableResults sr = q.scroll();

			if (sr.first()) {
				while (true) {
					ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)sr.get(0);

					if (shoppingItemFieldHBM == null) {
						break;
					}

					com.liferay.portlet.shopping.model.ShoppingItemField curShoppingItemField =
						ShoppingItemFieldHBMUtil.model(shoppingItemFieldHBM);
					int value = obc.compare(shoppingItemField,
							curShoppingItemField);

					if (value == 0) {
						if (!shoppingItemField.equals(curShoppingItemField)) {
							break;
						}

						array[1] = curShoppingItemField;

						if (sr.previous()) {
							array[0] = ShoppingItemFieldHBMUtil.model((ShoppingItemFieldHBM)sr.get(
										0));
						}

						sr.next();

						if (sr.next()) {
							array[2] = ShoppingItemFieldHBMUtil.model((ShoppingItemFieldHBM)sr.get(
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
				"FROM ShoppingItemField IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldHBM ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			Iterator itr = q.iterate();
			List list = new ArrayList();

			while (itr.hasNext()) {
				ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)itr.next();
				list.add(ShoppingItemFieldHBMUtil.model(shoppingItemFieldHBM));
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

	public void removeByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append(
				"FROM ShoppingItemField IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");
			query.append("ORDER BY ");
			query.append("itemId ASC").append(", ");
			query.append("name ASC");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

			Iterator itr = q.list().iterator();

			while (itr.hasNext()) {
				ShoppingItemFieldHBM shoppingItemFieldHBM = (ShoppingItemFieldHBM)itr.next();
				ShoppingItemFieldPool.remove((String)shoppingItemFieldHBM.getPrimaryKey());
				session.delete(shoppingItemFieldHBM);
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

	public int countByItemId(String itemId) throws SystemException {
		Session session = null;

		try {
			session = openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append(
				"FROM ShoppingItemField IN CLASS com.liferay.portlet.shopping.service.persistence.ShoppingItemFieldHBM WHERE ");
			query.append("itemId = ?");
			query.append(" ");

			Query q = session.createQuery(query.toString());
			int queryPos = 0;
			q.setString(queryPos++, itemId);

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

	private static final Log _log = LogFactory.getLog(ShoppingItemFieldPersistence.class);
}