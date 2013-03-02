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

package com.liferay.util.dao;

import com.liferay.portal.kernel.util.StringMaker;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

/**
 * <a href="CounterDAO.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class CounterDAO {

	public static String COUNTER_TABLE = "Counter";

	public synchronized static long increment(String location, String rowName)
		throws DataAccessException {

		return increment(location, COUNTER_TABLE, rowName);
	}

	public synchronized static long increment(
			String location, String tableName, String rowName)
		throws DataAccessException {

		long currentId = 0;

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(location);

			StringMaker query = new StringMaker();

			query.append(
				"SELECT currentId FROM " + tableName + " WHERE name = ?");

			ps = con.prepareStatement(query.toString());

			ps.setString(1, rowName);

			rs = ps.executeQuery();

			while (rs.next()) {
				currentId = rs.getInt(1);
			}

			if (currentId == 0) {
				ps = con.prepareStatement(
					"INSERT INTO " + tableName +
						" (name, currentId) VALUES (?, ?)");

				ps.setString(1, rowName);
				ps.setLong(2, ++currentId);

				ps.executeUpdate();
			}
			else {
				ps = con.prepareStatement(
					"UPDATE " + tableName +
						" SET currentId = ? WHERE name = ?");

				ps.setLong(1, ++currentId);
				ps.setString(2, rowName);

				ps.executeUpdate();
			}
		}
		catch (Exception e) {
			throw new DataAccessException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}

		return currentId;
	}

	public synchronized static void reset(String location, String rowName)
		throws DataAccessException {

		reset(location, COUNTER_TABLE, rowName);
	}

	public synchronized static void reset(
			String location, String tableName, String rowName)
		throws DataAccessException {

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			con = DataAccess.getConnection(location);

			StringMaker update = new StringMaker();

			update.append("DELETE FROM " + tableName + " WHERE name = ?");

			ps = con.prepareStatement(update.toString());

			ps.setString(1, rowName);

			ps.executeUpdate();
		}
		catch (Exception e) {
			throw new DataAccessException(e);
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);
		}
	}

}