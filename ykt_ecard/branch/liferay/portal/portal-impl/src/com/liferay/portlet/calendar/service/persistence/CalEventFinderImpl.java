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

package com.liferay.portlet.calendar.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.spring.hibernate.CustomSQLUtil;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portlet.calendar.model.impl.CalEventImpl;
import com.liferay.util.cal.CalendarUtil;
import com.liferay.util.dao.hibernate.QueryPos;

import java.sql.Timestamp;

import java.util.Date;
import java.util.List;

import org.hibernate.SQLQuery;
import org.hibernate.Session;

/**
 * <a href="CalEventFinderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CalEventFinderImpl implements CalEventFinder {

	public static String FIND_BY_G_SD =
		CalEventFinder.class.getName() + ".findByG_SD";

	public static String FIND_BY_REMINDBY =
		CalEventFinder.class.getName() + ".findByRemindBy";

	public List findByG_SD(
			long groupId, Date startDateGT, Date startDateLT,
			boolean timeZoneSensitive)
		throws SystemException {

		Timestamp startDateGT_TS = CalendarUtil.getTimestamp(startDateGT);
		Timestamp startDateLT_TS = CalendarUtil.getTimestamp(startDateLT);

		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_G_SD);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("CalEvent", CalEventImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(groupId);
			qPos.add(startDateGT_TS);
			qPos.add(startDateLT_TS);
			qPos.add(timeZoneSensitive);
			qPos.add(false);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

	public List findByRemindBy() throws SystemException {
		Session session = null;

		try {
			session = HibernateUtil.openSession();

			String sql = CustomSQLUtil.get(FIND_BY_REMINDBY);

			SQLQuery q = session.createSQLQuery(sql);

			q.addEntity("CalEvent", CalEventImpl.class);

			QueryPos qPos = QueryPos.getInstance(q);

			qPos.add(CalEventImpl.REMIND_BY_NONE);

			return q.list();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			HibernateUtil.closeSession(session);
		}
	}

}