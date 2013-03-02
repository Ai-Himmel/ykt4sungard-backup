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

package com.liferay.portlet.calendar.service.persistence;

import com.kingstargroup.ecard.util.DBUtil;
import com.liferay.portal.SystemException;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.calendar.model.CalEvent;
import com.liferay.util.SystemProperties;
import com.liferay.util.dao.DataAccess;
import com.liferay.util.lang.FastStringBuffer;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * <a href="CalEventFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.22 $
 *
 */
public class CalEventFinder {

	/**
	 * Find all CalEvents associated with the specified group id, company id,
	 * and start date.
	 *
	 * @return		a list of all CalEvents associated with the specified
	 *				group id, company id, and start date
	 */
	public static List findByG_C_SD(
			String groupId, String companyId, Date gtDate, Date ltDate,
			boolean timeZoneSensitive)
		throws SystemException {

		return findByG_C_SD(
			groupId, companyId, new Timestamp(gtDate.getTime()),
			new Timestamp(ltDate.getTime()), timeZoneSensitive);
	}

	/**
	 * Find all CalEvents associated with the specified group id, company id,
	 * and start date.
	 *
	 * @return		a list of all CalEvents associated with the specified
	 *				group id, company id, and start date
	 */
	public static List findByG_C_SD(
			String groupId, String companyId, Timestamp gtDate,
			Timestamp ltDate, boolean timeZoneSensitive)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			/*
			 * Support DB2 Schema
			 * Xiao Qi
			 * 2005-08-30
			 */
			query.append("SELECT eventId ");
			query.append("FROM ")
				.append(DBUtil.getSchemaName())
				.append("CalEvent WHERE ");						
			query.append("groupId = ? AND companyId = ? AND ");
			query.append("startDate >= ? AND startDate <= ? AND ");
			query.append("timeZoneSensitive = ? AND repeating = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, groupId);
			ps.setString(2, companyId);
			ps.setTimestamp(3, gtDate);
			ps.setTimestamp(4, ltDate);
			ps.setBoolean(5, timeZoneSensitive);
			ps.setBoolean(6, false);

			rs = ps.executeQuery();

			while (rs.next()) {
				CalEvent event = CalEventUtil.findByPrimaryKey(rs.getString(1));

				list.add(event);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return list;
	}

	/**
	 * Find all CalEvents associated with the specified group id, user id, and
	 * start date.
	 *
	 * @return		a list of all CalEvents associated with the specified
	 *				group id, user id, and start date
	 */
	public static List findByG_U_SD(
			String groupId, String userId, Date gtDate, Date ltDate,
			boolean timeZoneSensitive)
		throws SystemException {

		return findByG_U_SD(
			groupId, userId, new Timestamp(gtDate.getTime()),
			new Timestamp(ltDate.getTime()), timeZoneSensitive);
	}

	/**
	 * Find all CalEvents associated with the specified group id, user id, and
	 * start date.
	 *
	 * @return		a list of all CalEvents associated with the specified
	 *				group id, user id, and start date
	 */
	public static List findByG_U_SD(
			String groupId, String userId, Timestamp gtDate, Timestamp ltDate,
			boolean timeZoneSensitive)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			/*
			 * Support DB2 Schema
			 * Xiao Qi
			 * 2005-08-30
			 */
			query.append("SELECT eventId ");
			query.append("FROM ")
				.append(DBUtil.getSchemaName())
				.append("CalEvent WHERE ");
			query.append("groupId = ? AND userId = ? AND ");
			query.append("startDate >= ? AND startDate <= ? AND ");
			query.append("timeZoneSensitive = ? AND repeating = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, groupId);
			ps.setString(2, userId);
			ps.setTimestamp(3, gtDate);
			ps.setTimestamp(4, ltDate);
			ps.setBoolean(5, timeZoneSensitive);
			ps.setBoolean(6, false);

			rs = ps.executeQuery();

			while (rs.next()) {
				CalEvent event = CalEventUtil.findByPrimaryKey(rs.getString(1));

				list.add(event);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return list;
	}

	/**
	 * Find all CalEvents that have reminders.
	 *
	 * @return		all CalEvents that have reminders
	 */
	public static List findByRemindBy() throws SystemException {
		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			/*
			 * Support DB2 Schema
			 * Xiao Qi
			 * 2005-08-30
			 */
			query.append("SELECT eventId ");
			query.append("FROM ")
				.append(DBUtil.getSchemaName())
				.append("CalEvent WHERE ");
			query.append("remindBy != ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, CalEvent.REMIND_BY_NONE);

			rs = ps.executeQuery();

			while (rs.next()) {
				CalEvent event = CalEventUtil.findByPrimaryKey(rs.getString(1));

				list.add(event);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return list;
	}
}