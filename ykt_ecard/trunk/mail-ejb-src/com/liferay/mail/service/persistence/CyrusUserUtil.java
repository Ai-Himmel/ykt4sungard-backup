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

import com.liferay.mail.NoSuchCyrusUserException;
import com.liferay.mail.model.CyrusUser;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.HibernateUtil;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
import org.hibernate.Session;

/**
 * <a href="CyrusUserUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class CyrusUserUtil {

	public static void remove(String userId)
		throws NoSuchCyrusUserException, SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CyrusUserHBM hbm = (CyrusUserHBM)session.load(
				CyrusUserHBM.class, userId);

			session.delete(hbm);

			session.flush();
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchCyrusUserException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public static void update(CyrusUser user) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			try {
				CyrusUserHBM hbm = (CyrusUserHBM)session.load(
					CyrusUserHBM.class, user.getUserId());

				hbm.setPassword(user.getPassword());

				session.flush();
			}
			catch (ObjectNotFoundException onfe) {
				CyrusUserHBM hbm = new CyrusUserHBM(
					user.getUserId(), user.getPassword());

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

	public static CyrusUser model(CyrusUserHBM hbm) {
		return new CyrusUser(hbm.getUserId(), hbm.getPassword());
	}

	public static CyrusUser findByPrimaryKey(String userId)
		throws NoSuchCyrusUserException, SystemException {

		CyrusUser model = null;

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CyrusUserHBM hbm = (CyrusUserHBM)session.load(
				CyrusUserHBM.class, userId);

			model = model(hbm);

			return model;
		}
		catch (HibernateException he) {
			if (he instanceof ObjectNotFoundException) {
				throw new NoSuchCyrusUserException();
			}
			else {
				throw new SystemException(he);
			}
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

}