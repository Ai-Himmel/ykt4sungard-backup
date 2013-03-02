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

package com.liferay.util.spring.hibernate;

import com.liferay.util.dao.hibernate.LiferayClassicSession;

import java.lang.Object;
import java.lang.reflect.InvocationHandler;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import org.hibernate.HibernateException;
import org.hibernate.SessionFactory;
import org.hibernate.classic.Session;

import org.springframework.orm.hibernate3.SessionFactoryUtils;

/**
 * <a href="SessionFactoryInvocationHandler.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * <p>
 * See http://support.liferay.com/browse/LEP-2996.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class SessionFactoryInvocationHandler implements InvocationHandler {

	public SessionFactoryInvocationHandler(SessionFactory sessionFactory) {
		_sessionFactory = sessionFactory;
	}

	public Object invoke(Object proxy, Method method, Object[] args)
		throws Throwable {

		String methodName = method.getName();

		if (methodName.equals("getCurrentSession")) {
			try {
				Session session = (Session)SessionFactoryUtils.doGetSession(
					(SessionFactory)proxy, false);

				return wrapLiferaySession(session);
			}
			catch (IllegalStateException ise) {
				throw new HibernateException(ise.getMessage());
			}
		}
		else if (methodName.equals("openSession")) {
			Session session = (Session)method.invoke(_sessionFactory, args);

			return wrapLiferaySession(session);
		}
		else if (methodName.equals("equals")) {
			if (proxy == args[0]) {
				return Boolean.TRUE;
			}
			else {
				return Boolean.FALSE;
			}
		}
		else if (methodName.equals("hashCode")) {
			return new Integer(hashCode());
		}

		try {
			return method.invoke(_sessionFactory, args);
		}
		catch (InvocationTargetException ite) {
			throw ite.getTargetException();
		}
	}

	protected Session wrapLiferaySession(Session session) {
		if (session.getClass().getName().equals(
				LiferayClassicSession.class.getName())) {

			return session;
		}
		else {
			return new LiferayClassicSession(session);
		}
	}

	private final SessionFactory _sessionFactory;

}