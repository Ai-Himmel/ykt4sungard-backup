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

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Properties;
import java.util.StringTokenizer;

/**
 * <a href="LiferaySQL.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LiferaySQL {

	public static void main(String[] args) {
		String sql = "";

		for (int i = 0; i < args.length; i++) {
			sql += args[i] + " ";
		}

		if (!sql.equals("")) {
			new LiferaySQL(sql.trim());
		}
	}

	public LiferaySQL(String sql) {
		System.out.println(sql);

		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		try {
			Properties props = new Properties();

			try {
				props.load(new FileInputStream(new File("db.properties")));
			}
			catch (IOException ioe) {
				ioe.printStackTrace();

				return;
			}

			String driver = props.getProperty("driver");
			String url = props.getProperty("url");
			String user = props.getProperty("user");
			String password = props.getProperty("password");

			Class.forName(driver);

			con = DriverManager.getConnection(url, user, password);

			con.setAutoCommit(false);

			File sqlFile = new File(sql);

			if (sqlFile.exists()) {
				StringBuffer sb = new StringBuffer();

				BufferedReader br = new BufferedReader(new FileReader(sqlFile));

				String line = null;

				while ((line = br.readLine()) != null) {
					if (!line.startsWith("--")) {
						sb.append(line);
					}
				}

				br.close();

				StringTokenizer st = new StringTokenizer(sb.toString(), ";");

				while (st.hasMoreTokens()) {
					line = st.nextToken();

					System.out.println(line + ";");

					ps = con.prepareStatement(line);
					ps.executeUpdate();
				}
			}
			else if (sql.toLowerCase().startsWith("insert ") ||
					 sql.toLowerCase().startsWith("update ")) {

				ps = con.prepareStatement(sql);
				ps.executeUpdate(sql);
			}
			else {
				ps = con.prepareStatement(sql);
				rs = ps.executeQuery(sql);
				ResultSetMetaData rsmd = rs.getMetaData();

				int[] width = new int[rsmd.getColumnCount() + 1];

				StringBuffer sb = new StringBuffer();

				for (int i = 1; i <= rsmd.getColumnCount(); i++) {
					width[i] = rsmd.getColumnLabel(i).length();
				}

				List results = new ArrayList();

				while (rs.next()) {
					String[] rowResult = new String[rsmd.getColumnCount() + 1];

					for (int i = 1; i <= rsmd.getColumnCount(); i++) {
						Object obj = rs.getObject(i);

						if (obj != null) {
							rowResult[i] = obj.toString();

							int objWidth = obj.toString().length();

							if (width[i] < objWidth) {
								width[i] = objWidth;
							}
						}
						else {
							rowResult[i] = "";
						}
					}

					results.add(rowResult);
				}

				_printLine(rsmd, width, sb);

				for (int i = 1; i <= rsmd.getColumnCount(); i++) {
					String label = rsmd.getColumnLabel(i);

					sb.append("| ").append(label);

					for (int j = 0; j <= width[i] - label.length(); j++) {
						sb.append(" ");
					}
				}

				sb.append("|\n");

				_printLine(rsmd, width, sb);

				Iterator itr = results.iterator();

				while (itr.hasNext()) {
					String[] rowResult = (String[])itr.next();

					for (int i = 1; i <= rsmd.getColumnCount(); i++) {
						String s = rowResult[i];

						sb.append("| ").append(s);

						for (int j = 0; j <= width[i] - s.length(); j++) {
							sb.append(" ");
						}
					}

					sb.append("|\n");
				}

				_printLine(rsmd, width, sb);

				System.out.println(sb.toString());
			}

			con.commit();
		}
		catch (SQLException sqle) {
			while (sqle != null) {
				sqle.printStackTrace();

				sqle = sqle.getNextException();
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
		finally {
			_cleanUp(con, ps, rs);
		}
	}

	private void _cleanUp(Connection con, Statement s, ResultSet rs) {
		if (rs != null) {
			try {
				rs.close();
			}
			catch (Exception e) {
			}
		}

		if (s != null) {
			try {
				s.close();
			}
			catch (Exception e) {
			}
		}

		if (con != null) {
			try {
				con.close();
			}
			catch (Exception e) {
			}
		}
	}

	private void _printLine(
			ResultSetMetaData rsmd, int[] width, StringBuffer sb)
		throws SQLException {

		for (int i = 1; i <= rsmd.getColumnCount(); i++) {
			sb.append("+");

			for (int j = 0; j <= width[i] + 1; j++) {
				sb.append("-");
			}
		}

		sb.append("+\n");
	}

}