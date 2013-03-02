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

package com.liferay.portlet.blogs.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.blogs.model.BlogsEntry;
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
 * <a href="BlogsEntryFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class BlogsEntryFinder {

	/**
	 * Count all BlogsEntries associated with the specified company id and has
	 * a distinct user.
	 *
	 * @return		the count of all BlogsEntries associated with the specified
	 *				company id and has a distinct user
	 */
	public static int countByCompanyId(String companyId)
		throws SystemException {

		int count = 0;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(DISTINCT userId) ");
			query.append("FROM BlogsEntry ");
			query.append("WHERE companyId = ? AND sharing = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, companyId);
			ps.setBoolean(2, true);

			rs = ps.executeQuery();

			while (rs.next()) {
				count += rs.getInt(1);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return count;
	}

	/**
	 * Count all BlogsEntries associated with the specified user id and display
	 * date.
	 *
	 * @return		the count of all BlogsEntries associated with the specified
	 *				user id and display date
	 */
	public static int countByU_S_DD(
			String userId, Boolean sharing, Date gtDate, Date ltDate)
		throws SystemException {

		return countByU_S_DD(
			userId, sharing, new Timestamp(gtDate.getTime()),
			new Timestamp(ltDate.getTime()));
	}

	/**
	 * Count all BlogsEntries associated with the specified user id and display
	 * date.
	 *
	 * @return		the count of all BlogsEntries associated with the specified
	 *				user id and display date
	 */
	public static int countByU_S_DD(
			String userId, Boolean sharing, Timestamp gtDate, Timestamp ltDate)
		throws SystemException {

		int count = 0;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append("FROM BlogsEntry WHERE ");
			query.append("userId = ? AND ");
			query.append("displayDate >= ? AND displayDate <= ? ");

			if (sharing != null) {
				query.append("AND sharing = ?");
			}

			ps = con.prepareStatement(query.toString());

			ps.setString(1, userId);
			ps.setTimestamp(2, gtDate);
			ps.setTimestamp(3, ltDate);

			if (sharing != null) {
				ps.setBoolean(4, sharing.booleanValue());
			}

			rs = ps.executeQuery();

			while (rs.next()) {
				count += rs.getInt(1);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return count;
	}

	/**
	 * Count all BlogsEntries associated with the specified user id, category
	 * id, and display date.
	 *
	 * @return		the count of all BlogsEntries associated with the specified
	 *				user id, category id, and display date
	 */
	public static int countByU_C_S_DD(
			String userId, String categoryId, Boolean sharing, Date gtDate,
			Date ltDate)
		throws SystemException {

		return countByU_C_S_DD(
			userId, categoryId, sharing, new Timestamp(gtDate.getTime()),
			new Timestamp(ltDate.getTime()));
	}

	/**
	 * Count all BlogsEntries associated with the specified user id, category
	 * id, and display date.
	 *
	 * @return		the count of all BlogsEntries associated with the specified
	 *				user id, category id, and display date
	 */
	public static int countByU_C_S_DD(
			String userId, String categoryId, Boolean sharing, Timestamp gtDate,
			Timestamp ltDate)
		throws SystemException {

		int count = 0;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append("FROM BlogsEntry WHERE ");
			query.append("userId = ? AND categoryId = ? AND ");
			query.append("displayDate >= ? AND displayDate <= ? ");

			if (sharing != null) {
				query.append("AND sharing = ?");
			}

			ps = con.prepareStatement(query.toString());

			ps.setString(1, userId);
			ps.setString(2, categoryId);
			ps.setTimestamp(3, gtDate);
			ps.setTimestamp(4, ltDate);

			if (sharing != null) {
				ps.setBoolean(5, sharing.booleanValue());
			}

			rs = ps.executeQuery();

			while (rs.next()) {
				count += rs.getInt(1);
			}
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return count;
	}

	/**
	 * Find all BlogsEntries associated with the specified user id and display
	 * date.
	 *
	 * @return		a list of all BlogsEntries associated with the specified
	 *				user id and display date
	 */
	public static List findByU_S_DD(
			String userId, Boolean sharing, Date gtDate, Date ltDate)
		throws SystemException {

		return findByU_S_DD(
			userId, sharing, new Timestamp(gtDate.getTime()),
			new Timestamp(ltDate.getTime()));
	}

	/**
	 * Find all BlogsEntries associated with the specified user id and display
	 * date.
	 *
	 * @return		a list of all BlogsEntries associated with the specified
	 *				user id and display date
	 */
	public static List findByU_S_DD(
			String userId, Boolean sharing, Timestamp gtDate, Timestamp ltDate)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT entryId ");
			query.append("FROM BlogsEntry WHERE ");
			query.append("userId = ? AND ");
			query.append("displayDate >= ? AND displayDate <= ? ");

			if (sharing != null) {
				query.append("AND sharing = ? ");
			}

			query.append("ORDER BY displayDate DESC");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, userId);
			ps.setTimestamp(2, gtDate);
			ps.setTimestamp(3, ltDate);

			if (sharing != null) {
				ps.setBoolean(4, sharing.booleanValue());
			}

			rs = ps.executeQuery();

			while (rs.next()) {
				BlogsEntry entry =
					BlogsEntryUtil.findByPrimaryKey(rs.getString(1));

				list.add(entry);
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
	 * Find all BlogsEntries associated with the specified user id, category id,
	 * and display date.
	 *
	 * @return		a list of all BlogsEntries associated with the specified
	 *				user id, category id, and display date
	 */
	public static List findByU_C_S_DD(
			String userId, String categoryId, Boolean sharing, Date gtDate,
			Date ltDate)
		throws SystemException {

		return findByU_C_S_DD(
			userId, categoryId, sharing, new Timestamp(gtDate.getTime()),
			new Timestamp(ltDate.getTime()));
	}

	/**
	 * Find all BlogsEntries associated with the specified user id, category id,
	 * and display date.
	 *
	 * @return		a list of all BlogsEntries associated with the specified
	 *				user id, category id, and display date
	 */
	public static List findByU_C_S_DD(
			String userId, String categoryId, Boolean sharing, Timestamp gtDate,
			Timestamp ltDate)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT entryId ");
			query.append("FROM BlogsEntry WHERE ");
			query.append("userId = ? AND categoryId = ? AND ");
			query.append("displayDate >= ? AND displayDate <= ? ");

			if (sharing != null) {
				query.append("AND sharing = ? ");
			}

			query.append("ORDER BY displayDate DESC");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, userId);
			ps.setString(2, categoryId);
			ps.setTimestamp(3, gtDate);
			ps.setTimestamp(4, ltDate);

			if (sharing != null) {
				ps.setBoolean(5, sharing.booleanValue());
			}

			rs = ps.executeQuery();

			while (rs.next()) {
				BlogsEntry entry =
					BlogsEntryUtil.findByPrimaryKey(rs.getString(1));

				list.add(entry);
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