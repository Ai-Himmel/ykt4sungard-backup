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

package com.liferay.util.dao;

import com.liferay.util.JNDIUtil;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

import javax.naming.InitialContext;
import javax.naming.NamingException;

import javax.sql.DataSource;

/**
 * <a href="DataAccess.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class DataAccess {

	public static Connection getConnection(String location)
		throws NamingException, SQLException {

		InitialContext ctx = new InitialContext();
		DataSource ds = (DataSource)JNDIUtil.lookup(ctx, location);
		Connection con = ds.getConnection();

		return con;
	}

	public static void cleanUp(Connection con) {
		cleanUp(con, null, null);
	}

	public static void cleanUp(Connection con, Statement s) {
		cleanUp(con, s, null);
	}

	public static void cleanUp(Connection con, Statement s, ResultSet rs) {
		try {
			if (rs != null) {
				rs.close();
			}
		}
		catch (SQLException sqle) {
			sqle.printStackTrace();
		}

		try {
			if (s != null) {
				s.close();
			}
		}
		catch (SQLException sqle) {
			sqle.printStackTrace();
		}

		try {
			if (con != null) {
				con.close();
			}
		}
		catch (SQLException sqle) {
			sqle.printStackTrace();
		}
	}

}