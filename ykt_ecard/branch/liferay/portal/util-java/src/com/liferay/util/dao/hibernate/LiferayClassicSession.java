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

package com.liferay.util.dao.hibernate;

import java.io.Serializable;

import java.lang.Class;
import java.lang.Object;
import java.lang.String;

import java.util.Collection;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.classic.Session;
import org.hibernate.type.Type;

/**
 * <a href="LiferayClassicSession.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * See http://support.liferay.com/browse/LEP-2996.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LiferayClassicSession extends LiferaySession implements Session {

	public LiferayClassicSession(Session session) {
		super(session);

		_session = session;
	}

	public Session getHibernateClassicSession() {
		return _session;
	}

	/**
	 * @deprecated
	 */
	public Query createSQLQuery(
		String sql, String returnAlias, Class returnClass) {

		return _session.createSQLQuery(sql, returnAlias, returnClass);
	}

	/**
	 * @deprecated
	 */
	public Query createSQLQuery(
		String sql, String[] returnAliases, Class[] returnClasses) {

		return _session.createSQLQuery(sql, returnAliases, returnClasses);
	}

	/**
	 * @deprecated
	 */
	public int delete(String query) throws HibernateException {
		return _session.delete(query);
	}

	/**
	 * @deprecated
	 */
	public int delete(String query, Object value, Type type)
		throws HibernateException {

		return _session.delete(query, value, type);
	}

	/**
	 * @deprecated
	 */
	public int delete(String query, Object[] values, Type[] types)
		throws HibernateException {

		return _session.delete(query, values, types);
	}

	/**
	 * @deprecated
	 */
	public Collection filter(Object collection, String filter)
		throws HibernateException {

		return _session.filter(collection, filter);
	}

	/**
	 * @deprecated
	 */
	public Collection filter(
			Object collection, String filter, Object value, Type type)
		throws HibernateException {

		return _session.filter(collection, filter, value, type);
	}

	/**
	 * @deprecated
	 */
	public Collection filter(
			Object collection, String filter, Object[] values, Type[] types)
		throws HibernateException {

		return _session.filter(collection, filter, values, types);
	}

	/**
	 * @deprecated
	 */
	public List find(String query) throws HibernateException {
		return _session.find(query);
	}

	/**
	 * @deprecated
	 */
	public List find(String query, Object value, Type type)
		throws HibernateException {

		return _session.find(query, value, type);
	}

	/**
	 * @deprecated
	 */
	public List find(String query, Object[] values, Type[] types)
		throws HibernateException {

		return _session.find(query, values, types);
	}

	/**
	 * @deprecated
	 */
	public Iterator iterate(String query) throws HibernateException {
		return _session.iterate(query);
	}

	/**
	 * @deprecated
	 */
	public Iterator iterate(String query, Object value, Type type)
		throws HibernateException {

		return _session.iterate(query, value, type);
	}

	/**
	 * @deprecated
	 */
	public Iterator iterate(String query, Object[] values, Type[] types)
		throws HibernateException {

		return _session.iterate(query, values, types);
	}

	/**
	 * @deprecated
	 */
	public void save(Object object, Serializable id) throws HibernateException {
		_session.save(object, id);
	}

	/**
	 * @deprecated
	 */
	public void save(String entityName, Object object, Serializable id)
		throws HibernateException {

		_session.save(entityName, object, id);
	}

	/**
	 * @deprecated
	 */
	public Object saveOrUpdateCopy(Object object) throws HibernateException {
		return _session.saveOrUpdateCopy(object);
	}

	/**
	 * @deprecated
	 */
	public Object saveOrUpdateCopy(Object object, Serializable id)
		throws HibernateException {

		return _session.saveOrUpdateCopy(object, id);
	}

	/**
	 * @deprecated
	 */
	public Object saveOrUpdateCopy(String entityName, Object object)
		throws HibernateException {

		return _session.saveOrUpdateCopy(entityName, object);
	}

	/**
	 * @deprecated
	 */
	public Object saveOrUpdateCopy(
			String entityName, Object object, Serializable id)
		throws HibernateException {

		return _session.saveOrUpdateCopy(entityName, object, id);
	}

	/**
	 * @deprecated
	 */
	public void update(Object object, Serializable id)
		throws HibernateException {

		_session.update(object, id);
	}

	/**
	 * @deprecated
	 */
	public void update(String entityName, Object object, Serializable id)
		throws HibernateException {

		_session.update(entityName, object, id);
	}

	private Session _session;

}