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

package com.liferay.counter.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.util.HibernateUtil;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.hibernate.HibernateException;
import org.hibernate.ObjectNotFoundException;
import org.hibernate.Query;
import org.hibernate.Session;

/**
 * <a href="CounterUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class CounterUtil {

	public static List getNames() throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			List list = new ArrayList();

			Query q = session.createQuery(
				"FROM Counter IN CLASS " + CounterHBM.class.getName());

			Iterator itr = q.iterate();

			while (itr.hasNext()) {
				CounterHBM counterHBM = (CounterHBM)itr.next();

				list.add(counterHBM.getName());
			}

			Collections.sort(list);

			return list;
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public static synchronized long increment(String name)
		throws SystemException {

		return increment(name, true);
	}
	
	public static synchronized long increment(String name, boolean increase) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CounterHBM counterHBM = null;

			try {
				counterHBM =
					(CounterHBM)session.load(CounterHBM.class, name);
			}
			catch (ObjectNotFoundException onfe) {
				counterHBM = new CounterHBM();

				counterHBM.setName(name);
				counterHBM.setCurrentId(0);

				session.save(counterHBM);

				session.flush();
			}
			long currentId = 0;
			if (increase) {
				currentId = counterHBM.getCurrentId() + 1;
				counterHBM.setCurrentId(currentId);
			} else {
				currentId = counterHBM.getCurrentId();
			}
			session.flush();

			return currentId;
		} catch (HibernateException he) {
			he.printStackTrace();

			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}
	
	public static synchronized void rename(String oldName, String newName)
		throws SystemException {

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CounterHBM counterHBM =
				(CounterHBM)session.load(CounterHBM.class, oldName);

			long currentId = counterHBM.getCurrentId();

			session.delete(counterHBM);

			counterHBM = new CounterHBM();

			counterHBM.setName(newName);
			counterHBM.setCurrentId(currentId);

			session.save(counterHBM);

			session.flush();
		}
		catch (ObjectNotFoundException onfe) {
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public static synchronized void reset(String name) throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			CounterHBM counterHBM =
				(CounterHBM)session.load(CounterHBM.class, name);

			session.delete(counterHBM);

			session.flush();
		}
		catch (ObjectNotFoundException onfe) {
		}
		catch (HibernateException he) {
			throw new SystemException(he);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

}