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

package com.liferay.portal.jndi;

import com.liferay.portal.kernel.jndi.PortalJNDI;
import com.liferay.util.JNDIUtil;

import javax.mail.Session;

import javax.naming.InitialContext;
import javax.naming.NamingException;

import javax.sql.DataSource;

/**
 * <a href="PortalJNDIImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalJNDIImpl implements PortalJNDI {

	public static final String DATA_SOURCE_JNDI = "jdbc/LiferayPool";

	public static final String MAIL_SESSION_JNDI = "mail/MailSession";

	public DataSource getDataSource() throws NamingException {
		if (_dataSource == null) {
			_dataSource = (DataSource)JNDIUtil.lookup(
				new InitialContext(), DATA_SOURCE_JNDI);
		}

		return _dataSource;
	}

	public Session getMailSession() throws NamingException {
		if (_mailSession == null) {
			_mailSession = (Session)JNDIUtil.lookup(
				new InitialContext(), MAIL_SESSION_JNDI);
		}

		return _mailSession;
	}

	private DataSource _dataSource;
	private Session _mailSession;

}