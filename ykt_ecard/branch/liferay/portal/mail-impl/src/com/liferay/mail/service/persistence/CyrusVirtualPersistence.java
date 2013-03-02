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

package com.liferay.mail.service.persistence;

import com.liferay.mail.NoSuchCyrusVirtualException;
import com.liferay.mail.model.CyrusVirtual;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.BasePersistence;
import com.liferay.portal.spring.hibernate.HibernateUtil;

import java.util.Iterator;
import java.util.List;

import org.hibernate.ObjectNotFoundException;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * <a href="CyrusVirtualPersistence.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CyrusVirtualPersistence extends BasePersistence {

	public static String FIND_BY_USER_ID =
		"FROM " + CyrusVirtual.class.getName() + " WHERE userId = ?";

	public void remove(String emailAddress)
		throws NoSuchCyrusVirtualException, SystemException {

		Session session = null;

		try {
			session = getSessionFactory().openSession();

			CyrusVirtual virtual = (CyrusVirtual)session.load(
				CyrusVirtual.class, emailAddress);

			session.delete(virtual);

			session.flush();
		}
		catch (ObjectNotFoundException onfe) {
			throw new NoSuchCyrusVirtualException();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			session.close();
		}
	}

	public void update(CyrusVirtual virtual) throws SystemException {
		Session session = null;

		try {
			session = getSessionFactory().openSession();

			try {
				CyrusVirtual virtualModel = (CyrusVirtual)session.load(
					CyrusVirtual.class, virtual.getEmailAddress());

				virtualModel.setUserId(virtual.getUserId());

				session.flush();
			}
			catch (ObjectNotFoundException onfe) {
				CyrusVirtual virtualModel = new CyrusVirtual(
					virtual.getEmailAddress(), virtual.getUserId());

				session.save(virtualModel);

				session.flush();
			}
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			session.close();
		}
	}

	public CyrusVirtual findByPrimaryKey(String emailAddress)
		throws NoSuchCyrusVirtualException, SystemException {

		Session session = null;

		try {
			session = getSessionFactory().openSession();

			return (CyrusVirtual)session.load(CyrusVirtual.class, emailAddress);
		}
		catch (ObjectNotFoundException onfe) {
			throw new NoSuchCyrusVirtualException();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			session.close();
		}
	}

	public List findByUserId(long userId) throws SystemException {
		Session session = null;

		try {
			session = getSessionFactory().openSession();

			Query q = session.createQuery(FIND_BY_USER_ID);

			q.setString(0, String.valueOf(userId));

			return q.list();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			session.close();
		}
	}

	public void removeByUserId(long userId) throws SystemException {
		Session session = null;

		try {
			session = getSessionFactory().openSession();

			Query q = session.createQuery(FIND_BY_USER_ID);

			q.setString(0, String.valueOf(userId));

			Iterator itr = q.iterate();

			while (itr.hasNext()) {
				CyrusVirtual virtual = (CyrusVirtual)itr.next();

				session.delete(virtual);
			}

			session.flush();
		}
		catch (Exception e) {
			throw HibernateUtil.processException(e);
		}
		finally {
			session.close();
		}
	}

}