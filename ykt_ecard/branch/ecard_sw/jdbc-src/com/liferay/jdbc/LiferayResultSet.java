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

import java.io.IOException;
import java.io.InputStream;

import java.net.URL;

import java.sql.Array;
import java.sql.Blob;
import java.sql.Clob;
import java.sql.Date;
import java.sql.Ref;
import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.Statement;
import java.sql.Time;
import java.sql.Timestamp;

import java.util.Calendar;
import java.util.Map;

/**
 * <a href="LiferayResultSet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.7 $
 *
 */
public class LiferayResultSet implements ResultSet {

	public LiferayResultSet(ResultSet rs) {
		_rs = rs;
	}

	public Object getObject(String p1, Map p2) throws SQLException {
		return _rs.getObject(p1, p2);
	}

	public Object getObject(int p1, Map p2) throws SQLException {
		return _rs.getObject(p1, p2);
	}

	public Object getObject(String p1) throws SQLException {
		return _rs.getObject(p1);
	}

	public Object getObject(int p1) throws SQLException {
		return _rs.getObject(p1);
	}

	public boolean getBoolean(String p1) throws SQLException {
		return _rs.getBoolean(p1);
	}

	public boolean getBoolean(int p1) throws SQLException {
		return _rs.getBoolean(p1);
	}

	public byte getByte(String p1) throws SQLException {
		return _rs.getByte(p1);
	}

	public byte getByte(int p1) throws SQLException {
		return _rs.getByte(p1);
	}

	public short getShort(int p1) throws SQLException {
		return _rs.getShort(p1);
	}

	public short getShort(String p1) throws SQLException {
		return _rs.getShort(p1);
	}

	public int getInt(int p1) throws SQLException {
		return _rs.getInt(p1);
	}

	public int getInt(String p1) throws SQLException {
		return _rs.getInt(p1);
	}

	public long getLong(String p1) throws SQLException {
		return _rs.getLong(p1);
	}

	public long getLong(int p1) throws SQLException {
		return _rs.getLong(p1);
	}

	public float getFloat(String p1) throws SQLException {
		return _rs.getFloat(p1);
	}

	public float getFloat(int p1) throws SQLException {
		return _rs.getFloat(p1);
	}

	public double getDouble(int p1) throws SQLException {
		return _rs.getDouble(p1);
	}

	public double getDouble(String p1) throws SQLException {
		return _rs.getDouble(p1);
	}

	public byte[] getBytes(int p1) throws SQLException {
		return _rs.getBytes(p1);
	}

	public byte[] getBytes(String p1) throws SQLException {
		return _rs.getBytes(p1);
	}

	public boolean next() throws SQLException {
		return _rs.next();
	}

	public URL getURL(String p1) throws SQLException {
		return _rs.getURL(p1);
	}

	public URL getURL(int p1) throws SQLException {
		return _rs.getURL(p1);
	}

	public int getType() throws SQLException {
		return _rs.getType();
	}

	public boolean previous() throws SQLException {
		return _rs.previous();
	}

	public void close() throws SQLException {
		_rs.close();
	}

	public String getString(String p1) throws SQLException {
		return _rs.getString(p1);
	}

	public String getString(int p1) throws SQLException {
		InputStream is = getAsciiStream(1);

		StringBuffer sb = new StringBuffer();

		try {
			int c;

			while ((c = is.read()) != -1) {
				sb.append((char)c);
			}

			is.close();
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
			throw new SQLException(ioe.toString());
		}

		return sb.toString();
	}

	public Ref getRef(int p1) throws SQLException {
		return _rs.getRef(p1);
	}

	public Ref getRef(String p1) throws SQLException {
		return _rs.getRef(p1);
	}

	public Time getTime(String p1, Calendar p2) throws SQLException {
		return _rs.getTime(p1, p2);
	}

	public Time getTime(int p1) throws SQLException {
		return _rs.getTime(p1);
	}

	public Time getTime(String p1) throws SQLException {
		return _rs.getTime(p1);
	}

	public Time getTime(int p1, Calendar p2) throws SQLException {
		return _rs.getTime(p1, p2);
	}

	public Date getDate(String p1, Calendar p2) throws SQLException {
		return _rs.getDate(p1, p2);
	}

	public Date getDate(String p1) throws SQLException {
		return _rs.getDate(p1);
	}

	public Date getDate(int p1) throws SQLException {
		return _rs.getDate(p1);
	}

	public Date getDate(int p1, Calendar p2) throws SQLException {
		return _rs.getDate(p1, p2);
	}

	public boolean wasNull() throws SQLException {
		return _rs.wasNull();
	}

	public java.math.BigDecimal getBigDecimal(String p1) throws SQLException {
		return _rs.getBigDecimal(p1);
	}

	public java.math.BigDecimal getBigDecimal(String p1, int p2)
		throws SQLException {

		return _rs.getBigDecimal(p1, p2);
	}

	public java.math.BigDecimal getBigDecimal(int p1, int p2)
		throws SQLException {

		return _rs.getBigDecimal(p1, p2);
	}

	public java.math.BigDecimal getBigDecimal(int p1)
		throws SQLException {

		return _rs.getBigDecimal(p1);
	}

	public Timestamp getTimestamp(int p1)
		throws SQLException {

		return _rs.getTimestamp(p1);
	}

	public Timestamp getTimestamp(int p1, Calendar p2) throws SQLException {
		return _rs.getTimestamp(p1, p2);
	}

	public Timestamp getTimestamp(String p1, Calendar p2) throws SQLException {
		return _rs.getTimestamp(p1, p2);
	}

	public Timestamp getTimestamp(String p1) throws SQLException {
		return _rs.getTimestamp(p1);
	}

	public java.io.InputStream getAsciiStream(String p1) throws SQLException {
		return _rs.getAsciiStream(p1);
	}

	public java.io.InputStream getAsciiStream(int p1) throws SQLException {
		return _rs.getAsciiStream(p1);
	}

	public java.io.InputStream getUnicodeStream(String p1) throws SQLException {
		return _rs.getUnicodeStream(p1);
	}

	public java.io.InputStream getUnicodeStream(int p1) throws SQLException {
		return _rs.getUnicodeStream(p1);
	}

	public java.io.InputStream getBinaryStream(String p1) throws SQLException {
		return _rs.getBinaryStream(p1);
	}

	public java.io.InputStream getBinaryStream(int p1) throws SQLException {
		return _rs.getBinaryStream(p1);
	}

	public SQLWarning getWarnings() throws SQLException {
		return _rs.getWarnings();
	}

	public void clearWarnings() throws SQLException {
		_rs.clearWarnings();
	}

	public String getCursorName() throws SQLException {
		return _rs.getCursorName();
	}

	public ResultSetMetaData getMetaData() throws SQLException {
		return _rs.getMetaData();
	}

	public int findColumn(String p1) throws SQLException {
		return _rs.findColumn(p1);
	}

	public java.io.Reader getCharacterStream(int p1) throws SQLException {
		return _rs.getCharacterStream(p1);
	}

	public java.io.Reader getCharacterStream(String p1) throws SQLException {
		return _rs.getCharacterStream(p1);
	}

	public boolean isBeforeFirst() throws SQLException {
		return _rs.isBeforeFirst();
	}

	public boolean isAfterLast() throws SQLException {
		return _rs.isAfterLast();
	}

	public boolean isFirst() throws SQLException {
		return _rs.isFirst();
	}

	public boolean isLast() throws SQLException {
		return _rs.isLast();
	}

	public void beforeFirst() throws SQLException {
		_rs.beforeFirst();
	}

	public void afterLast() throws SQLException {
		_rs.afterLast();
	}

	public boolean first() throws SQLException {
		return _rs.first();
	}

	public boolean last() throws SQLException {
		return _rs.last();
	}

	public int getRow() throws SQLException {
		return _rs.getRow();
	}

	public boolean absolute(int p1) throws SQLException {
		return _rs.absolute(p1);
	}

	public boolean relative(int p1) throws SQLException {
		return _rs.relative(p1);
	}

	public void setFetchDirection(int p1) throws SQLException {
		_rs.setFetchDirection(p1);
	}

	public int getFetchDirection() throws SQLException {
		return _rs.getFetchDirection();
	}

	public void setFetchSize(int p1) throws SQLException {
		_rs.setFetchSize(p1);
	}

	public int getFetchSize() throws SQLException {
		return _rs.getFetchSize();
	}

	public int getConcurrency() throws SQLException {
		return _rs.getConcurrency();
	}

	public boolean rowUpdated() throws SQLException {
		return _rs.rowUpdated();
	}

	public boolean rowInserted() throws SQLException {
		return _rs.rowInserted();
	}

	public boolean rowDeleted() throws SQLException {
		return _rs.rowDeleted();
	}

	public void updateNull(String p1) throws SQLException {
		_rs.updateNull(p1);
	}

	public void updateNull(int p1) throws SQLException {
		_rs.updateNull(p1);
	}

	public void updateBoolean(String p1, boolean p2) throws SQLException {
		_rs.updateBoolean(p1, p2);
	}

	public void updateBoolean(int p1, boolean p2) throws SQLException {
		_rs.updateBoolean(p1, p2);
	}

	public void updateByte(int p1, byte p2) throws SQLException {
		_rs.updateByte(p1, p2);
	}

	public void updateByte(String p1, byte p2) throws SQLException {
		_rs.updateByte(p1, p2);
	}

	public void updateShort(String p1, short p2) throws SQLException {
		_rs.updateShort(p1, p2);
	}

	public void updateShort(int p1, short p2) throws SQLException {
		_rs.updateShort(p1, p2);
	}

	public void updateInt(int p1, int p2) throws SQLException {
		_rs.updateInt(p1, p2);
	}

	public void updateInt(String p1, int p2) throws SQLException {
		_rs.updateInt(p1, p2);
	}

	public void updateLong(int p1, long p2) throws SQLException {
		_rs.updateLong(p1, p2);
	}

	public void updateLong(String p1, long p2) throws SQLException {
		_rs.updateLong(p1, p2);
	}

	public void updateFloat(String p1, float p2) throws SQLException {
		_rs.updateFloat(p1, p2);
	}

	public void updateFloat(int p1, float p2) throws SQLException {
		_rs.updateFloat(p1, p2);
	}

	public void updateDouble(int p1, double p2) throws SQLException {
		_rs.updateDouble(p1, p2);
	}

	public void updateDouble(String p1, double p2) throws SQLException {
		_rs.updateDouble(p1, p2);
	}

	public void updateBigDecimal(String p1, java.math.BigDecimal p2)
		throws SQLException {

		_rs.updateBigDecimal(p1, p2);
	}

	public void updateBigDecimal(int p1, java.math.BigDecimal p2)
		throws SQLException {

		_rs.updateBigDecimal(p1, p2);
	}

	public void updateString(String p1, String p2) throws SQLException {
		_rs.updateString(p1, p2);
	}

	public void updateString(int p1, String p2) throws SQLException {
		_rs.updateString(p1, p2);
	}

	public void updateBytes(String p1, byte[] p2) throws SQLException {
		_rs.updateBytes(p1, p2);
	}

	public void updateBytes(int p1, byte[] p2) throws SQLException {
		_rs.updateBytes(p1, p2);
	}

	public void updateDate(String p1, Date p2) throws SQLException {
		_rs.updateDate(p1, p2);
	}

	public void updateDate(int p1, Date p2) throws SQLException {
		_rs.updateDate(p1, p2);
	}

	public void updateTime(String p1, Time p2) throws SQLException {
		_rs.updateTime(p1, p2);
	}

	public void updateTime(int p1, Time p2) throws SQLException {
		_rs.updateTime(p1, p2);
	}

	public void updateTimestamp(int p1, Timestamp p2) throws SQLException {
		_rs.updateTimestamp(p1, p2);
	}

	public void updateTimestamp(String p1, Timestamp p2) throws SQLException {
		_rs.updateTimestamp(p1, p2);
	}

	public void updateAsciiStream(String p1, java.io.InputStream p2, int p3)
		throws SQLException {

		_rs.updateAsciiStream(p1, p2, p3);
	}

	public void updateAsciiStream(int p1, java.io.InputStream p2, int p3)
		throws SQLException {

		_rs.updateAsciiStream(p1, p2, p3);
	}

	public void updateBinaryStream(String p1, java.io.InputStream p2, int p3)
		throws SQLException {

		_rs.updateBinaryStream(p1, p2, p3);
	}

	public void updateBinaryStream(int p1, java.io.InputStream p2, int p3)
		throws SQLException {

		_rs.updateBinaryStream(p1, p2, p3);
	}

	public void updateCharacterStream(String p1, java.io.Reader p2, int p3)
		throws SQLException {

		_rs.updateCharacterStream(p1, p2, p3);
	}

	public void updateCharacterStream(int p1, java.io.Reader p2, int p3)
		throws SQLException {

		_rs.updateCharacterStream(p1, p2, p3);
	}

	public void updateObject(int p1, Object p2, int p3) throws SQLException {
		_rs.updateObject(p1, p2, p3);
	}

	public void updateObject(int p1, Object p2) throws SQLException {
		_rs.updateObject(p1, p2);
	}

	public void updateObject(String p1, Object p2) throws SQLException {
		_rs.updateObject(p1, p2);
	}

	public void updateObject(String p1, Object p2, int p3) throws SQLException {
		_rs.updateObject(p1, p2, p3);
	}

	public void insertRow() throws SQLException {
		_rs.insertRow();
	}

	public void updateRow() throws SQLException {
		_rs.updateRow();
	}

	public void deleteRow() throws SQLException {
		_rs.deleteRow();
	}

	public void refreshRow() throws SQLException {
		_rs.refreshRow();
	}

	public void cancelRowUpdates() throws SQLException {
		_rs.cancelRowUpdates();
	}

	public void moveToInsertRow() throws SQLException {
		_rs.moveToInsertRow();
	}

	public void moveToCurrentRow() throws SQLException {
		_rs.moveToCurrentRow();
	}

	public Statement getStatement() throws SQLException {
		return _rs.getStatement();
	}

	public Blob getBlob(String p1) throws SQLException {
		return _rs.getBlob(p1);
	}

	public Blob getBlob(int p1) throws SQLException {
		return _rs.getBlob(p1);
	}

	public Clob getClob(int p1) throws SQLException {
		return _rs.getClob(p1);
	}

	public Clob getClob(String p1) throws SQLException {
		return _rs.getClob(p1);
	}

	public Array getArray(int p1) throws SQLException {
		return _rs.getArray(p1);
	}

	public Array getArray(String p1) throws SQLException {
		return _rs.getArray(p1);
	}

	public void updateRef(int p1, Ref p2) throws SQLException {
		_rs.updateRef(p1, p2);
	}

	public void updateRef(String p1, Ref p2) throws SQLException {
		_rs.updateRef(p1, p2);
	}

	public void updateBlob(String p1, Blob p2) throws SQLException {
		_rs.updateBlob(p1, p2);
	}

	public void updateBlob(int p1, Blob p2) throws SQLException {
		_rs.updateBlob(p1, p2);
	}

	public void updateClob(String p1, Clob p2) throws SQLException {
		_rs.updateClob(p1, p2);
	}

	public void updateClob(int p1, Clob p2) throws SQLException {
		_rs.updateClob(p1, p2);
	}

	public void updateArray(String p1, Array p2) throws SQLException {
		_rs.updateArray(p1, p2);
	}

	public void updateArray(int p1, Array p2) throws SQLException {
		_rs.updateArray(p1, p2);
	}

	private ResultSet _rs;

}