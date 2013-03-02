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

package com.liferay.portlet.wiki.service.persistence;

import com.liferay.portal.SystemException;
import com.liferay.portal.util.Constants;
import com.liferay.portlet.wiki.model.WikiPage;
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
 * <a href="WikiPageFinder.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class WikiPageFinder {

	/**
	 * Count all WikiPages associated with the specified node id created before
	 * or after the specified date.
	 *
	 * @return		the count of all WikiPages associated with the specified
	 *				node id before or after the specified date
	 */
	public static int countByCreateDate(
			String nodeId, Date createDate, boolean before)
		throws SystemException {

		return countByCreateDate(
			nodeId, new Timestamp(createDate.getTime()), before);
	}

	/**
	 * Count all WikiPages associated with the specified node id created before
	 * or after the specified date.
	 *
	 * @return		the count of all WikiPages associated with the specified
	 *				node id before or after the specified date
	 */
	public static int countByCreateDate(
			String nodeId, Timestamp createDate, boolean before)
		throws SystemException {

		int count = 0;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			String comparator = ">";
			if (before) {
				comparator = "<";
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT COUNT(*) ");
			query.append("FROM WikiPage WHERE ");
			query.append("nodeId = ? AND ");
			query.append("createDate ").append(comparator).append(" ? AND ");
			query.append("head = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, nodeId);
			ps.setTimestamp(2, createDate);
			ps.setBoolean(3, true);

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
	 * Find all WikiPages associated with the specified node id created before
	 * or after the specified date.
	 *
	 * @return		a list of all WikiPages associated with the specified node
	 *				id before or after the specified date
	 */
	public static List findByCreateDate(
			String nodeId, Date createDate, boolean before)
		throws SystemException {

		return findByCreateDate(
			nodeId, new Timestamp(createDate.getTime()), before);
	}

	/**
	 * Find all WikiPages associated with the specified node id created before
	 * or after the specified date.
	 *
	 * @return		a list of all WikiPages associated with the specified node
	 *				id before or after the specified date
	 */
	public static List findByCreateDate(
			String nodeId, Timestamp createDate, boolean before)
		throws SystemException {

		List list = new ArrayList();

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(Constants.DATA_SOURCE);

			String comparator = ">";
			if (before) {
				comparator = "<";
			}

			FastStringBuffer query = new FastStringBuffer();
			query.append("SELECT title, version ");
			query.append("FROM WikiPage WHERE ");
			query.append("nodeId = ? AND ");
			query.append("createDate ").append(comparator).append(" ? AND ");
			query.append("head = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, nodeId);
			ps.setTimestamp(2, createDate);
			ps.setBoolean(3, true);

			rs = ps.executeQuery();

			while (rs.next()) {
				WikiPage node = WikiPageUtil.findByPrimaryKey(
					new WikiPagePK(nodeId, rs.getString(1), rs.getDouble(2)));

				list.add(node);
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