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

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.SQLWarning;
import java.sql.Statement;

/**
 * <a href="LiferayStatement.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class LiferayStatement implements Statement {

	public LiferayStatement(Statement s) {
		_s = s;
	}

	public void close() throws SQLException {
		_s.close();
	}

	public boolean execute(String p1, int p2) throws SQLException {
		return _s.execute(p1, p2);
	}

	public boolean execute(String p1, int[] p2) throws SQLException {
		return _s.execute(p1, p2);
	}

	public boolean execute(String p1, String[] p2) throws SQLException {
		return _s.execute(p1, p2);
	}

	public boolean execute(String p1) throws SQLException {
		return _s.execute(p1);
	}

	public ResultSet executeQuery(String p1) throws SQLException {
		return _s.executeQuery(p1);
	}

	public int executeUpdate(String p1) throws SQLException {
		return _s.executeUpdate(p1);
	}

	public int executeUpdate(String p1, String[] p2) throws SQLException {
		return _s.executeUpdate(p1, p2);
	}

	public int executeUpdate(String p1, int p2) throws SQLException {
		return _s.executeUpdate(p1, p2);
	}

	public int executeUpdate(String p1, int[] p2) throws SQLException {
		return _s.executeUpdate(p1, p2);
	}

	public int getMaxFieldSize() throws SQLException {
		return _s.getMaxFieldSize();
	}

	public void setMaxFieldSize(int p1) throws SQLException {
		_s.setMaxFieldSize(p1);
	}

	public int getMaxRows() throws SQLException {
		return _s.getMaxRows();
	}

	public void setMaxRows(int p1) throws SQLException {
		_s.setMaxRows(p1);
	}

	public void setEscapeProcessing(boolean p1) throws SQLException {
		_s.setEscapeProcessing(p1);
	}

	public int getQueryTimeout() throws SQLException {
		return _s.getQueryTimeout();
	}

	public void setQueryTimeout(int p1) throws SQLException {
		_s.setQueryTimeout(p1);
	}

	public void cancel() throws SQLException {
		_s.cancel();
	}

	public SQLWarning getWarnings() throws SQLException {
		return _s.getWarnings();
	}

	public void clearWarnings() throws SQLException {
		_s.clearWarnings();
	}

	public void setCursorName(String p1) throws SQLException {
		_s.setCursorName(p1);
	}

	public ResultSet getResultSet() throws SQLException {
		return _s.getResultSet();
	}

	public int getUpdateCount() throws SQLException {
		return _s.getUpdateCount();
	}

	public boolean getMoreResults(int p1) throws SQLException {
		return _s.getMoreResults(p1);
	}

	public boolean getMoreResults() throws SQLException {
		return _s.getMoreResults();
	}

	public void setFetchDirection(int p1) throws SQLException {
		_s.setFetchDirection(p1);
	}

	public int getFetchDirection() throws SQLException {
		return _s.getFetchDirection();
	}

	public void setFetchSize(int p1) throws SQLException {
		_s.setFetchSize(p1);
	}

	public int getFetchSize() throws SQLException {
		return _s.getFetchSize();
	}

	public int getResultSetConcurrency() throws SQLException {
		return _s.getResultSetConcurrency();
	}

	public int getResultSetType() throws SQLException {
		return _s.getResultSetType();
	}

	public void addBatch(String p1) throws SQLException {
		_s.addBatch(p1);
	}

	public void clearBatch() throws SQLException {
		_s.clearBatch();
	}

	public int[] executeBatch() throws SQLException {
		return _s.executeBatch();
	}

	public Connection getConnection() throws SQLException {
		return _s.getConnection();
	}

	public ResultSet getGeneratedKeys() throws SQLException {
		return _s.getGeneratedKeys();
	}

	public int getResultSetHoldability() throws SQLException {
		return _s.getResultSetHoldability();
	}

	private Statement _s;

}