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

package com.liferay.util.dao.hibernate;

import com.liferay.util.JNDIUtil;

import java.sql.Connection;
import java.sql.SQLException;

import java.util.Properties;

import javax.naming.InitialContext;

import javax.sql.DataSource;

import org.hibernate.HibernateException;
import org.hibernate.cfg.Environment;
import org.hibernate.connection.ConnectionProvider;

/**
 * <a href="DSConnectionProvider.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class DSConnectionProvider implements ConnectionProvider {

	public void configure(Properties props) throws HibernateException {
		String location = props.getProperty(Environment.DATASOURCE);

		try {
			_ds = (DataSource)JNDIUtil.lookup(new InitialContext(), location);
		}
		catch (Exception e) {
			throw new HibernateException(e.getMessage());
		}
	}

	public Connection getConnection() throws SQLException {
		return _ds.getConnection();
	}

	public void close() {
	}

	public void closeConnection(Connection con) throws SQLException {
		con.close();
	}

	public boolean supportsAggressiveRelease() {
		return false;
	}

	private DataSource _ds;

}