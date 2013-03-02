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

package com.liferay.jdbc;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.io.Reader;

import java.math.BigDecimal;

import java.net.URL;

import java.sql.Array;
import java.sql.Blob;
import java.sql.Clob;
import java.sql.Connection;
import java.sql.Date;
import java.sql.ParameterMetaData;
import java.sql.PreparedStatement;
import java.sql.Ref;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.Time;
import java.sql.Timestamp;

import java.util.Calendar;

/**
 * <a href="LiferayPreparedStatement.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class LiferayPreparedStatement implements PreparedStatement {

	public static final String STRING_TRUE = "1";

	public static final String STRING_FALSE = "0";

	public LiferayPreparedStatement(PreparedStatement ps, boolean db2) {
		_ps = ps;
		_db2 = db2;
	}

	public void setBoolean(int p1, boolean p2) throws SQLException {
		if (_db2) {
			_ps.setString(p1, p2 ? STRING_TRUE : STRING_FALSE);
		}
		else {
			_ps.setBoolean(p1, p2);
		}
	}

	public void setByte(int p1, byte p2) throws SQLException {
		_ps.setByte(p1, p2);
	}

	public void setShort(int p1, short p2) throws SQLException {
		_ps.setShort(p1, p2);
	}

	public void setInt(int p1, int p2) throws SQLException {
		_ps.setInt(p1, p2);
	}

	public void setLong(int p1, long p2) throws SQLException {
		_ps.setLong(p1, p2);
	}

	public void setFloat(int p1, float p2) throws SQLException {
		_ps.setFloat(p1, p2);
	}

	public void setDouble(int p1, double p2) throws SQLException {
		_ps.setDouble(p1, p2);
	}

	public void setURL(int p1, URL p2) throws SQLException {
		_ps.setURL(p1, p2);
	}

	public void setTime(int p1, Time p2) throws SQLException {
		_ps.setTime(p1, p2);
	}

	public void setTime(int p1, Time p2, Calendar p3) throws SQLException {
		_ps.setTime(p1, p2, p3);
	}

	public boolean execute() throws SQLException {
		return _ps.execute();
	}

	public ResultSet executeQuery() throws SQLException {
		return _ps.executeQuery();
	}

	public int executeUpdate() throws SQLException {
		return _ps.executeUpdate();
	}

	public void setNull(int p1, int p2) throws SQLException {
		_ps.setNull(p1, p2);
	}

	public void setNull(int p1, int p2, String p3) throws SQLException {
		_ps.setNull(p1, p2, p3);
	}

	public void setBigDecimal(int p1, BigDecimal p2)
		throws SQLException {

		_ps.setBigDecimal(p1, p2);
	}

	public void setString(int p1, String p2) throws SQLException {
		if (p2 != null) {
			byte[] bytes = p2.getBytes();

			InputStream is = new ByteArrayInputStream(bytes);

			_ps.setAsciiStream(p1, is, bytes.length);
		}
		else {
			_ps.setString(p1, p2);
		}
	}

	public void setBytes(int p1, byte[] p2) throws SQLException {
		_ps.setBytes(p1, p2);
	}

	public void setDate(int p1, Date p2) throws SQLException {
		_ps.setDate(p1, p2);
	}

	public void setDate(int p1, Date p2, Calendar p3) throws SQLException {
		_ps.setDate(p1, p2, p3);
	}

	public void setTimestamp(int p1, Timestamp p2, Calendar p3)
		throws SQLException {

		_ps.setTimestamp(p1, p2, p3);
	}

	public void setTimestamp(int p1, Timestamp p2) throws SQLException {
		_ps.setTimestamp(p1, p2);
	}

	public void setAsciiStream(int p1, InputStream p2, int p3)
		throws SQLException {

		_ps.setAsciiStream(p1, p2, p3);
	}

	public void setUnicodeStream(int p1, InputStream p2, int p3)
		throws SQLException {

		_ps.setUnicodeStream(p1, p2, p3);
	}

	public void setBinaryStream(int p1, InputStream p2, int p3)
		throws SQLException {

		_ps.setBinaryStream(p1, p2, p3);
	}

	public void clearParameters() throws SQLException {
		_ps.clearParameters();
	}

	public void setObject(int p1, Object p2, int p3, int p4)
		throws SQLException {

		_ps.setObject(p1, p2, p3, p4);
	}

	public void setObject(int p1, Object p2, int p3) throws SQLException {
		_ps.setObject(p1, p2, p3);
	}

	public void setObject(int p1, Object p2) throws SQLException {
		_ps.setObject(p1, p2);
	}

	public void addBatch() throws SQLException {
		_ps.addBatch();
	}

	public void setCharacterStream(int p1, Reader p2, int p3)
		throws SQLException {

		_ps.setCharacterStream(p1, p2, p3);
	}

	public void setRef(int p1, Ref p2) throws SQLException {
		_ps.setRef(p1, p2);
	}

	public void setBlob(int p1, Blob p2) throws SQLException {
		_ps.setBlob(p1, p2);
	}

	public void setClob(int p1, Clob p2) throws SQLException {
		_ps.setClob(p1, p2);
	}

	public void setArray(int p1, Array p2) throws SQLException {
		_ps.setArray(p1, p2);
	}

	public ResultSetMetaData getMetaData() throws SQLException {
		return _ps.getMetaData();
	}

	public ParameterMetaData getParameterMetaData() throws SQLException {
		return _ps.getParameterMetaData();
	}

	public void close() throws SQLException {
		_ps.close();
	}

	public boolean execute(String p1, int p2) throws SQLException {
		return _ps.execute(p1, p2);
	}

	public boolean execute(String p1) throws SQLException {
		return _ps.execute(p1);
	}

	public boolean execute(String p1, String[] p2) throws SQLException {
		return _ps.execute(p1, p2);
	}

	public boolean execute(String p1, int[] p2) throws SQLException {
		return _ps.execute(p1, p2);
	}

	public ResultSet executeQuery(String p1) throws SQLException {
		return _ps.executeQuery(p1);
	}

	public int executeUpdate(String p1) throws SQLException {
		return _ps.executeUpdate(p1);
	}

	public int executeUpdate(String p1, String[] p2) throws SQLException {
		return _ps.executeUpdate(p1, p2);
	}

	public int executeUpdate(String p1, int[] p2) throws SQLException {
		return _ps.executeUpdate(p1, p2);
	}

	public int executeUpdate(String p1, int p2) throws SQLException {
		return _ps.executeUpdate(p1, p2);
	}

	public void addBatch(String p1) throws SQLException {
		_ps.addBatch(p1);
	}

	public int getMaxFieldSize() throws SQLException {
		return _ps.getMaxFieldSize();
	}

	public void setMaxFieldSize(int p1) throws SQLException {
		_ps.setMaxFieldSize(p1);
	}

	public int getMaxRows() throws SQLException {
		return _ps.getMaxRows();
	}

	public void setMaxRows(int p1) throws SQLException {
		_ps.setMaxRows(p1);
	}

	public void setEscapeProcessing(boolean p1) throws SQLException {
		_ps.setEscapeProcessing(p1);
	}

	public int getQueryTimeout() throws SQLException {
		return _ps.getQueryTimeout();
	}

	public void setQueryTimeout(int p1) throws SQLException {
		_ps.setQueryTimeout(p1);
	}

	public void cancel() throws SQLException {
		_ps.cancel();
	}

	public SQLWarning getWarnings() throws SQLException {
		return _ps.getWarnings();
	}

	public void clearWarnings() throws SQLException {
		_ps.clearWarnings();
	}

	public void setCursorName(String p1) throws SQLException {
		_ps.setCursorName(p1);
	}

	public ResultSet getResultSet() throws SQLException {
		return _ps.getResultSet();
	}

	public int getUpdateCount() throws SQLException {
		return _ps.getUpdateCount();
	}

	public boolean getMoreResults(int p1) throws SQLException {
		return _ps.getMoreResults(p1);
	}

	public boolean getMoreResults() throws SQLException {
		return _ps.getMoreResults();
	}

	public void setFetchDirection(int p1) throws SQLException {
		_ps.setFetchDirection(p1);
	}

	public int getFetchDirection() throws SQLException {
		return _ps.getFetchDirection();
	}

	public void setFetchSize(int p1) throws SQLException {
		_ps.setFetchSize(p1);
	}

	public int getFetchSize() throws SQLException {
		return _ps.getFetchSize();
	}

	public int getResultSetConcurrency() throws SQLException {
		return _ps.getResultSetConcurrency();
	}

	public int getResultSetType() throws SQLException {
		return _ps.getResultSetType();
	}

	public void clearBatch() throws SQLException {
		_ps.clearBatch();
	}

	public int[] executeBatch() throws SQLException {
		return _ps.executeBatch();
	}

	public Connection getConnection() throws SQLException {
		return _ps.getConnection();
	}

	public ResultSet getGeneratedKeys() throws SQLException {
		return _ps.getGeneratedKeys();
	}

	public int getResultSetHoldability() throws SQLException {
		return _ps.getResultSetHoldability();
	}

	private PreparedStatement _ps;
	private boolean _db2;

}