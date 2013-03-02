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

package com.liferay.portal.tools;

import Zql.ZConstant;
import Zql.ZInsert;
import Zql.ZStatement;
import Zql.ZqlParser;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.util.FileUtil;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.StringReader;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.Statement;
import java.sql.Timestamp;

import java.util.List;

/**
 * <a href="DBLoader.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class DBLoader {

	public static void main(String[] args) {
		if (args.length == 2) {
			new DBLoader(args[0], args[1], StringPool.BLANK);
		}
		else if (args.length == 3) {
			new DBLoader(args[0], args[1], args[2]);
		}
		else {
			throw new IllegalArgumentException();
		}
	}

	public DBLoader(String databaseType, String databaseName, String fileName) {
		try {
			_databaseType = databaseType;
			_databaseName = databaseName;
			_fileName = fileName;

			if (_databaseType.equals("derby")) {
				_loadDerby();
			}
			else if (_databaseType.equals("hypersonic")) {
				_loadHypersonic();
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private PreparedStatement _getStatementDerby(Connection con, String sql)
		throws Exception {

		sql = StringUtil.replace(
			sql, "current timestamp", "'current timestamp'");

		sql += ";";

		ZqlParser zParser = new ZqlParser(
			new ByteArrayInputStream(sql.getBytes()));

		ZStatement zStatement = zParser.readStatement();

		ZInsert zInsert = (ZInsert)zStatement;

		sql = "insert into " + zInsert.getTable() + " (";

		List columns = zInsert.getColumns();

		for (int i = 0; i < columns.size(); i++) {
			sql += columns.get(i);

			if ((i + 1) < columns.size()) {
				sql += ", ";
			}
		}

		sql += ") values (";

		for (int i = 0; i < columns.size(); i++) {
			sql += "?";

			if ((i + 1) < columns.size()) {
				sql += ", ";
			}
		}

		sql += ")";

		PreparedStatement ps = con.prepareStatement(sql);

		List values = zInsert.getValues();

		for (int i = 0; i < values.size(); i++) {
			ZConstant zConstant = (ZConstant)values.get(i);

			int pos = i + 1;

			String value = (String)zConstant.getValue();

			if (value.equals("current timestamp")) {
				ps.setTimestamp(
					pos, new Timestamp(System.currentTimeMillis()));
			}
			else if (value.length() < 32000) {
				ps.setString(pos, zConstant.getValue());
			}
			else {
				ps.setCharacterStream(
					pos, new StringReader(value), value.length());
			}
		}

		return ps;
	}

	private void _loadDerby() throws Exception {
		Class.forName("org.apache.derby.jdbc.EmbeddedDriver");

		Connection con = DriverManager.getConnection(
			"jdbc:derby:" + _databaseName + ";create=true", "", "");

		if (Validator.isNull(_fileName)) {
			_loadDerby(con, "../sql/portal/portal-derby.sql");
			_loadDerby(con, "../sql/indexes.sql");
		}
		else {
			_loadDerby(con, _fileName);
		}
	}

	private void _loadDerby(Connection con, String fileName)
		throws Exception {

		StringMaker sm = new StringMaker();

		BufferedReader br = new BufferedReader(
			new StringReader(FileUtil.read(fileName)));

		String line = null;

		while ((line = br.readLine()) != null) {
			if (!line.startsWith("--")) {
				sm.append(line);

				if (line.endsWith(";")) {
					String sql = sm.toString();

					sql =
						StringUtil.replace(
							sql,
							new String[] {
								"\\'",
								"\\\"",
								"\\\\",
								"\\n",
								"\\r"
							},
							new String[] {
								"''",
								"\"",
								"\\",
								"\n",
								"\r"
							});

					sql = sql.substring(0, sql.length() - 1);

					sm = new StringMaker();

					if (sql.startsWith("commit")) {
						continue;
					}

					PreparedStatement ps = null;

					if (sql.startsWith("insert into Image (") ||
						sql.startsWith("insert into JournalArticle (") ||
						sql.startsWith("insert into JournalStructure (") ||
						sql.startsWith("insert into JournalTemplate (") ||
						sql.startsWith("insert into Layout (") ||
						sql.startsWith("insert into PortletPreferences (")) {

						// Derby isn't able to process long inserts. Zql parses
						// the SQL statement so that we can manually set the
						// insert statement. Zql also isn't able to properly
						// parse certain unicode characters.

						sql = StringUtil.replace(
							sql,
							new String[] {
								"\u0161",
								"\u017e",
								"\u2013",
								"\u2014",
								"\u2015",
								"\u2019",
								"\u2022",
								"\u201c",
								"\u2122"
							},
							new String[] {
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK,
								StringPool.BLANK
							});

						try {
							ps = _getStatementDerby(con, sql);
						}
						catch (Exception e) {
							System.out.println("Unable to parse " + sql);

							e.printStackTrace();

							throw e;
						}
					}
					else {
						ps = con.prepareStatement(sql);
					}

					try {
						ps.executeUpdate();
					}
					catch (Exception e) {
						System.out.println("Unable to execute " + sql);

						e.printStackTrace();

						throw e;
					}
					finally {
						if (ps != null) {
							ps.close();
						}
					}
				}
			}
		}

		br.close();
	}

	private void _loadHypersonic() throws Exception {
		Class.forName("org.hsqldb.jdbcDriver");

		// See LEP-2927. Appending ;shutdown=true to the database connection URL
		// guarantees that ${_databaseName}.log is purged.

		Connection con = DriverManager.getConnection(
			"jdbc:hsqldb:" + _databaseName + ";shutdown=true", "sa", "");

		if (Validator.isNull(_fileName)) {
			_loadHypersonic(con, "../sql/portal/portal-hypersonic.sql");
			_loadHypersonic(con, "../sql/indexes.sql");
		}
		else {
			_loadDerby(con, _fileName);
		}

		// Shutdown Hypersonic

		Statement statement = con.createStatement();

		statement.execute("SHUTDOWN COMPACT");

		statement.close();

		con.close();

		// Hypersonic will encode unicode characters twice, this will undo
		// it

		String content = FileUtil.read(_databaseName + ".script");

		content = StringUtil.replace(content, "\\u005cu", "\\u");

		FileUtil.write(_databaseName + ".script", content);
	}

	private void _loadHypersonic(Connection con, String fileName)
		throws Exception {

		StringMaker sm = new StringMaker();

		BufferedReader br = new BufferedReader(
			new StringReader(FileUtil.read(fileName)));

		String line = null;

		while ((line = br.readLine()) != null) {
			if (!line.startsWith("//")) {
				sm.append(line);

				if (line.endsWith(";")) {
					String sql = sm.toString();

					sql =
						StringUtil.replace(
							sql,
							new String[] {
								"\\\"",
								"\\\\",
								"\\n",
								"\\r"
							},
							new String[] {
								"\"",
								"\\",
								"\\u000a",
								"\\u000a"
							});

					sm = new StringMaker();

					PreparedStatement ps = con.prepareStatement(sql);

					ps.executeUpdate();

					ps.close();
				}
			}
		}

		br.close();
	}

	private String _databaseType;
	private String _databaseName;
	private String _fileName;

}