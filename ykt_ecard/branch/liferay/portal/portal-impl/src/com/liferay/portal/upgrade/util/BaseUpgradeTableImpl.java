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

package com.liferay.portal.upgrade.util;

import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.spring.hibernate.HibernateUtil;
import com.liferay.portal.tools.sql.DBUtil;
import com.liferay.portal.upgrade.StagnantRowException;
import com.liferay.portal.upgrade.UpgradeException;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.SystemProperties;
import com.liferay.util.dao.DataAccess;
import com.liferay.util.dao.hibernate.BooleanType;
import com.liferay.util.dao.hibernate.DoubleType;
import com.liferay.util.dao.hibernate.FloatType;
import com.liferay.util.dao.hibernate.IntegerType;
import com.liferay.util.dao.hibernate.LongType;
import com.liferay.util.dao.hibernate.ShortType;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

import java.sql.Clob;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Timestamp;
import java.sql.Types;

import java.text.DateFormat;

import java.util.Date;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.hibernate.usertype.UserType;

/**
 * <a href="BaseUpgradeTableImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 * @author Brian Wing Shun Chan
 *
 */
public abstract class BaseUpgradeTableImpl {

	public static final String SAFE_RETURN_CHARACTER =
		"_SAFE_RETURN_CHARACTER_";

	public static final String SAFE_COMMA_CHARACTER =
		"_SAFE_COMMA_CHARACTER_";

	public static final String SAFE_NEWLINE_CHARACTER =
		"_SAFE_NEWLINE_CHARACTER_";

	public static final String[][] SAFE_CHARS = {
		{StringPool.RETURN, StringPool.COMMA, StringPool.NEW_LINE},
		{SAFE_RETURN_CHARACTER, SAFE_COMMA_CHARACTER, SAFE_NEWLINE_CHARACTER}
	};

	public BaseUpgradeTableImpl(String tableName) {
		_tableName = tableName;
	}

	public String getTableName() {
		return _tableName;
	}

	public Object[][] getColumns() {
		return _columns;
	}

	public void setColumns(Object[][] columns) {
		_columns = columns;
	}

	public abstract String getExportedData(ResultSet rs) throws Exception;

	public void appendColumn(StringMaker sm, Object value, boolean last)
		throws Exception {

		if (value == null) {
			throw new UpgradeException(
				"Nulls should never be inserted into the database. " +
					"Attempted to append column to " + sm.toString() + ".");
		}
		else if (value instanceof Clob || value instanceof String) {
			value = StringUtil.replace(
				(String)value, SAFE_CHARS[0], SAFE_CHARS[1]);

			sm.append(value);
		}
		else if (value instanceof Date) {
			DateFormat df = DateUtil.getISOFormat();

			sm.append(df.format(value));
		}
		else {
			sm.append(value);
		}

		sm.append(StringPool.COMMA);

		if (last) {
			sm.append(StringPool.NEW_LINE);
		}
	}

	public void appendColumn(
			StringMaker sm, ResultSet rs, String name, Integer type,
			boolean last)
		throws Exception {

		Object value = getValue(rs, name, type);

		appendColumn(sm, value, last);
	}

	public String getCreateSQL() throws Exception {
		return _createSQL;
	}

	public void setCreateSQL(String createSQL) throws Exception {
		if (_calledUpdateTable) {
			throw new UpgradeException(
				"setCreateSQL is called after updateTable");
		}

		_createSQL = createSQL;
	}

	public String getDeleteSQL() throws Exception {
		return "DELETE FROM " + _tableName;
	}

	public String getInsertSQL() throws Exception {
		String sql = "INSERT INTO " + _tableName + " (";

		for (int i = 0; i < _columns.length; i++) {
			sql += _columns[i][0];

			if ((i + 1) < _columns.length) {
				sql += ", ";
			}
			else {
				sql += ") VALUES (";
			}
		}

		for (int i = 0; i < _columns.length; i++) {
			sql += "?";

			if ((i + 1) < _columns.length) {
				sql += ", ";
			}
			else {
				sql += ")";
			}
		}

		return sql;
	}

	public String getSelectSQL() throws Exception {
		/*String sql = "SELECT ";

		for (int i = 0; i < _columns.length; i++) {
			sql += _columns[i][0];

			if ((i + 1) < _columns.length) {
				sql += ", ";
			}
			else {
				sql += " FROM " + _tableName;
			}
		}

		return sql;*/

		return "SELECT * FROM " + _tableName;
	}

	public Object getValue(ResultSet rs, String name, Integer type)
		throws Exception {

		Object value = null;

		int t = type.intValue();

		UserType userType = null;

		if (t == Types.BIGINT) {
			userType = new LongType();
		}
		else if (t == Types.BOOLEAN) {
			userType = new BooleanType();
		}
		else if (t == Types.CLOB) {
			try {
				Clob clob = rs.getClob(name);

				if (clob == null) {
					value = StringPool.BLANK;
				}
				else {
					BufferedReader br = new BufferedReader(
						clob.getCharacterStream());

					StringMaker sm = new StringMaker();

					String line = null;

					while ((line = br.readLine()) != null) {
						if (sm.length() != 0) {
							sm.append(SAFE_NEWLINE_CHARACTER);
						}

						sm.append(line);
					}

					value = sm.toString();
				}
			}
			catch (Exception e) {

				// If the database doesn't allow CLOB types for the column
				// value, then try retrieving it as a String

				value = GetterUtil.getString(rs.getString(name));
			}
		}
		else if (t == Types.DOUBLE) {
			userType = new DoubleType();
		}
		else if (t == Types.FLOAT) {
			userType = new FloatType();
		}
		else if (t == Types.INTEGER) {
			userType = new IntegerType();
		}
		else if (t == Types.SMALLINT) {
			userType = new ShortType();
		}
		else if (t == Types.TIMESTAMP) {
			try {
				value = rs.getTimestamp(name);
			}
			catch (Exception e) {
			}

			if (value == null) {
				value = StringPool.NULL;
			}
		}
		else if (t == Types.VARCHAR) {
			value = GetterUtil.getString(rs.getString(name));
		}
		else {
			throw new UpgradeException(
				"Upgrade code using unsupported class type " + type);
		}

		if (userType != null) {
			try {
				value = userType.nullSafeGet(rs, new String[] {name}, null);
			}
			catch (Exception e) {
				_log.error(
					"Unable to nullSafeGet " + name + " with " +
						userType.getClass().getName());

				throw e;
			}
		}

		return value;
	}

	public void setColumn(
			PreparedStatement ps, int index, Integer type, String value)
		throws Exception {

		int t = type.intValue();

		int paramIndex = index + 1;

		if (t == Types.BIGINT) {
			ps.setLong(paramIndex, GetterUtil.getLong(value));
		}
		else if (t == Types.BOOLEAN) {
			ps.setBoolean(paramIndex, GetterUtil.getBoolean(value));
		}
		else if ((t == Types.CLOB) || (t == Types.VARCHAR)) {
			value = StringUtil.replace(value, SAFE_CHARS[1], SAFE_CHARS[0]);

			ps.setString(paramIndex, value);
		}
		else if (t == Types.DOUBLE) {
			ps.setDouble(paramIndex, GetterUtil.getDouble(value));
		}
		else if (t == Types.FLOAT) {
			ps.setFloat(paramIndex, GetterUtil.getFloat(value));
		}
		else if (t == Types.INTEGER) {
			ps.setInt(paramIndex, GetterUtil.getInteger(value));
		}
		else if (t == Types.SMALLINT) {
			ps.setShort(paramIndex, GetterUtil.getShort(value));
		}
		else if (t == Types.TIMESTAMP) {
			if (StringPool.NULL.equals(value)) {
				ps.setTimestamp(paramIndex, null);
			}
			else {
				DateFormat df = DateUtil.getISOFormat();

				ps.setTimestamp(
					paramIndex, new Timestamp(df.parse(value).getTime()));
			}
		}
		else {
			throw new UpgradeException(
				"Upgrade code using unsupported class type " + type);
		}
	}

	public void updateTable() throws Exception {
		_calledUpdateTable = true;

		String tempFileName = getTempFileName();

		try {
			DBUtil dbUtil = DBUtil.getInstance();

			if (Validator.isNotNull(_createSQL)) {
				dbUtil.runSQL("drop table " + _tableName);

				dbUtil.runSQL(_createSQL);
			}

			if (Validator.isNotNull(tempFileName)) {
				dbUtil.runSQL(getDeleteSQL());

				repopulateTable(tempFileName);
			}
		}
		finally {
			if (Validator.isNotNull(tempFileName)) {
				FileUtil.delete(tempFileName);
			}
		}
	}

	protected String getTempFileName() throws Exception {
		Connection con = null;
		PreparedStatement ps = null;
		ResultSet rs = null;

		boolean isEmpty = true;

		String tempFileName =
			SystemProperties.get(SystemProperties.TMP_DIR) + "/temp-db-" +
				_tableName + "-" + System.currentTimeMillis();

		String selectSQL = getSelectSQL();

		BufferedWriter bw = new BufferedWriter(new FileWriter(tempFileName));

		try {
			con = HibernateUtil.getConnection();

			ps = con.prepareStatement(selectSQL);

			rs = ps.executeQuery();

			while (rs.next()) {
				String data = null;

				try {
					data = getExportedData(rs);

					bw.write(data);

					isEmpty = false;
				}
				catch (StagnantRowException sre) {
					if (_log.isWarnEnabled()) {
						_log.warn(
							"Skipping stagnant data in " + _tableName + ": " +
								sre.getMessage());
					}
				}
			}

			if (_log.isInfoEnabled()) {
				_log.info(
					_tableName + " table backed up to file " + tempFileName);
			}
		}
		catch (Exception e) {
			FileUtil.delete(tempFileName);

			throw e;
		}
		finally {
			DataAccess.cleanUp(con, ps, rs);

			bw.close();
		}

		if (!isEmpty) {
			return tempFileName;
		}
		else {
			FileUtil.delete(tempFileName);

			return null;
		}
	}

	protected void repopulateTable(String tempFileName) throws Exception {
		Connection con = null;
		PreparedStatement ps = null;

		String insertSQL = getInsertSQL();

		BufferedReader br = new BufferedReader(new FileReader(tempFileName));

		String line = null;

		try {
			con = HibernateUtil.getConnection();

			boolean useBatch = con.getMetaData().supportsBatchUpdates();

			if (!useBatch) {
				if (_log.isInfoEnabled()) {
					_log.info("Database does not support batch updates");
				}
			}

			int count = 0;

			while ((line = br.readLine()) != null) {
				String[] values = StringUtil.split(line);

				if (values.length != _columns.length) {
					throw new UpgradeException(
						"Columns differ between temp file and schema. " +
							"Attempted to insert row " + line  + ".");
				}

				if (count == 0) {
					ps = con.prepareStatement(insertSQL);
				}

				for (int i = 0; i < _columns.length; i++) {
					setColumn(ps, i, (Integer)_columns[i][1], values[i]);
				}

				if (useBatch) {
					ps.addBatch();

					if (count == _BATCH_SIZE) {
						repopulateTableRows(ps, true);

						count = 0;
					}
					else {
						count++;
					}
				}
				else {
					repopulateTableRows(ps, false);
				}
			}

			if (useBatch) {
				if (count != 0) {
					repopulateTableRows(ps, true);
				}
			}
		}
		finally {
			DataAccess.cleanUp(con, ps);

			br.close();
		}

		if (_log.isInfoEnabled()) {
			_log.info(_tableName + " table repopulated with data");
		}
	}

	protected void repopulateTableRows(PreparedStatement ps, boolean batch)
		throws Exception {

		if (_log.isDebugEnabled()) {
			_log.debug("Updating rows for " + _tableName);
		}

		if (batch) {
			ps.executeBatch();
		}
		else {
			ps.executeUpdate();
		}

		ps.close();
	}

	private static final int _BATCH_SIZE = GetterUtil.getInteger(
		PropsUtil.get("hibernate.jdbc.batch_size"));

	private static Log _log = LogFactory.getLog(BaseUpgradeTableImpl.class);

	private String _tableName;
	private Object[][] _columns;
	private String _createSQL;
	private boolean _calledUpdateTable;

}