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

package com.liferay.portal.service.http;

import com.liferay.portal.auth.HttpPrincipal;
import com.liferay.portal.service.spring.AccountServiceUtil;
import com.liferay.portal.servlet.TunnelUtil;

import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.lang.NullWrapper;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="AccountServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class AccountServiceHttp {
	public static com.liferay.portal.model.Account addAccount(
		HttpPrincipal httpPrincipal, java.lang.String parentAccountId,
		java.lang.String name, java.lang.String legalName,
		java.lang.String legalId, java.lang.String legalType,
		java.lang.String sicCode, java.lang.String tickerSymbol,
		java.lang.String industry, java.lang.String type,
		java.lang.String size, java.lang.String website,
		java.lang.String emailAddress1, java.lang.String emailAddress2)
		throws com.liferay.portal.PortalException, 
			com.liferay.portal.SystemException {
		try {
			Object paramObj0 = parentAccountId;

			if (parentAccountId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = name;

			if (name == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = legalName;

			if (legalName == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = legalId;

			if (legalId == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = legalType;

			if (legalType == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = sicCode;

			if (sicCode == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = tickerSymbol;

			if (tickerSymbol == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = industry;

			if (industry == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = type;

			if (type == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = size;

			if (size == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = website;

			if (website == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = emailAddress1;

			if (emailAddress1 == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			Object paramObj12 = emailAddress2;

			if (emailAddress2 == null) {
				paramObj12 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(AccountServiceUtil.class.getName(),
					"addAccount",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12
					});
			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				throw e;
			}

			return (com.liferay.portal.model.Account)returnObj;
		}
		catch (com.liferay.portal.PortalException pe) {
			throw pe;
		}
		catch (com.liferay.portal.SystemException se) {
			throw se;
		}
		catch (Exception e) {
			_log.error(e.getMessage());
			throw new com.liferay.portal.SystemException();
		}
	}

	private static final Log _log = LogFactory.getLog(AccountServiceHttp.class);
}