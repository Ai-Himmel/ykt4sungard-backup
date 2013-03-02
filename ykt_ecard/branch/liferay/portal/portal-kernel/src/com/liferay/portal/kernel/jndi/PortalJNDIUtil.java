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

package com.liferay.portal.kernel.jndi;

import com.liferay.portal.kernel.bean.BeanLocatorUtil;

import javax.mail.Session;

import javax.naming.NamingException;

import javax.sql.DataSource;

/**
 * <a href="PortalJNDIUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalJNDIUtil {

	public static DataSource getDataSource() throws NamingException {
		return getPortalJNDI().getDataSource();
	}

	public static Session getMailSession() throws NamingException {
		return getPortalJNDI().getMailSession();
	}

	public static PortalJNDI getPortalJNDI() {
		return _getUtil()._portalJNDI;
	}

	public void setPortalJNDI(PortalJNDI portalJNDI) {
		_portalJNDI = portalJNDI;
	}

	private static PortalJNDIUtil _getUtil() {
		if (_util == null) {
			_util = (PortalJNDIUtil)BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = PortalJNDIUtil.class.getName();

	private static PortalJNDIUtil _util;

	private PortalJNDI _portalJNDI;

}