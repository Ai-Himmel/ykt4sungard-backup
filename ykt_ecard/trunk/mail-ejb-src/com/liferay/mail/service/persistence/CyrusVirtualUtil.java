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

package com.liferay.mail.service.persistence;

import com.liferay.mail.NoSuchCyrusVirtualException;
import com.liferay.mail.model.CyrusVirtual;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.HibernateUtil;
import com.liferay.util.lang.FastStringBuffer;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * <a href="CyrusVirtualUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class CyrusVirtualUtil {

	public static void remove(String emailAddress)
		throws NoSuchCyrusVirtualException, SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CyrusVirtualHBM hbm = (CyrusVirtualHBM)session.load(
				CyrusVirtualHBM.class, emailAddress);

			session.delete(hbm);

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchCyrusVirtualException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public static void update(CyrusVirtual user) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			try {
				CyrusVirtualHBM hbm = (CyrusVirtualHBM)session.load(
					CyrusVirtualHBM.class, user.getEmailAddress());

				hbm.setUserId(user.getUserId());

				session.flush();
			}
			catch (ObjectNotFoundException onfe) {
				CyrusVirtualHBM hbm = new CyrusVirtualHBM(
					user.getEmailAddress(), user.getUserId());

				session.save(hbm);

				session.flush();
			}
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public static CyrusVirtual model(CyrusVirtualHBM hbm) {
		return new CyrusVirtual(hbm.getEmailAddress(), hbm.getUserId());
	}

	public static CyrusVirtual findByPrimaryKey(String emailAddress)
		throws NoSuchCyrusVirtualException, SystemException {

		CyrusVirtual model = null;

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CyrusVirtualHBM hbm = (CyrusVirtualHBM)session.load(
				CyrusVirtualHBM.class, emailAddress);

			model = model(hbm);

			return model;
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchCyrusVirtualException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public static List findByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("FROM CyrusVirtual ");
			query.append("IN CLASS com.liferay.mail.ejb.CyrusVirtualHBM ");
			query.append("WHERE ");
			query.append("userId = ?");

			Query q = session.createQuery(query.toString());

			q.setString(0, userId);

			Iterator itr = q.iterate();

			List list = new ArrayList();

			while (itr.hasNext()) {
				CyrusVirtualHBM hbm = (CyrusVirtualHBM)itr.next();

				list.add(model(hbm));
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

	public static void removeByUserId(String userId) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			FastStringBuffer query = new FastStringBuffer();
			query.append("FROM CyrusVirtual ");
			query.append("IN CLASS com.liferay.mail.ejb.CyrusVirtualHBM ");
			query.append("WHERE ");
			query.append("userId = ?");

			Query q = session.createQuery(query.toString());

			q.setString(0, userId);

			Iterator itr = q.iterate();

			while (itr.hasNext()) {
				CyrusVirtualHBM hbm = (CyrusVirtualHBM)itr.next();

				session.delete(hbm);
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

}