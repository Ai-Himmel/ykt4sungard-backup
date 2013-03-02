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

package com.liferay.portal.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.util.BooleanWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.CompanyServiceUtil;

/**
 * <a href="CompanyServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portal.service.CompanyServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it requires an
 * additional <code>com.liferay.portal.security.auth.HttpPrincipal</code>
 * parameter.
 * </p>
 *
 * <p>
 * The benefits of using the HTTP utility is that it is fast and allows for
 * tunneling without the cost of serializing to text. The drawback is that it
 * only works with Java.
 * </p>
 *
 * <p>
 * Set the property <code>tunnel.servlet.hosts.allowed</code> in
 * portal.properties to configure security.
 * </p>
 *
 * <p>
 * The HTTP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.security.auth.HttpPrincipal
 * @see com.liferay.portal.service.CompanyServiceUtil
 * @see com.liferay.portal.service.http.CompanyServiceSoap
 *
 */
public class CompanyServiceHttp {
	public static com.liferay.portal.model.Company addCompany(
		HttpPrincipal httpPrincipal, java.lang.String webId,
		java.lang.String virtualHost, java.lang.String mx)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = webId;

			if (webId == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = virtualHost;

			if (virtualHost == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = mx;

			if (mx == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CompanyServiceUtil.class.getName(),
					"addCompany",
					new Object[] { paramObj0, paramObj1, paramObj2 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.Company)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Company updateCompany(
		HttpPrincipal httpPrincipal, long companyId,
		java.lang.String virtualHost, java.lang.String mx)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = virtualHost;

			if (virtualHost == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = mx;

			if (mx == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CompanyServiceUtil.class.getName(),
					"updateCompany",
					new Object[] { paramObj0, paramObj1, paramObj2 });

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.Company)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static com.liferay.portal.model.Company updateCompany(
		HttpPrincipal httpPrincipal, long companyId,
		java.lang.String virtualHost, java.lang.String mx,
		java.lang.String name, java.lang.String legalName,
		java.lang.String legalId, java.lang.String legalType,
		java.lang.String sicCode, java.lang.String tickerSymbol,
		java.lang.String industry, java.lang.String type, java.lang.String size)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = virtualHost;

			if (virtualHost == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = mx;

			if (mx == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = name;

			if (name == null) {
				paramObj3 = new NullWrapper("java.lang.String");
			}

			Object paramObj4 = legalName;

			if (legalName == null) {
				paramObj4 = new NullWrapper("java.lang.String");
			}

			Object paramObj5 = legalId;

			if (legalId == null) {
				paramObj5 = new NullWrapper("java.lang.String");
			}

			Object paramObj6 = legalType;

			if (legalType == null) {
				paramObj6 = new NullWrapper("java.lang.String");
			}

			Object paramObj7 = sicCode;

			if (sicCode == null) {
				paramObj7 = new NullWrapper("java.lang.String");
			}

			Object paramObj8 = tickerSymbol;

			if (tickerSymbol == null) {
				paramObj8 = new NullWrapper("java.lang.String");
			}

			Object paramObj9 = industry;

			if (industry == null) {
				paramObj9 = new NullWrapper("java.lang.String");
			}

			Object paramObj10 = type;

			if (type == null) {
				paramObj10 = new NullWrapper("java.lang.String");
			}

			Object paramObj11 = size;

			if (size == null) {
				paramObj11 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CompanyServiceUtil.class.getName(),
					"updateCompany",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11
					});

			Object returnObj = null;

			try {
				returnObj = TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}

			return (com.liferay.portal.model.Company)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void updateDisplay(HttpPrincipal httpPrincipal,
		long companyId, java.lang.String languageId, java.lang.String timeZoneId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = languageId;

			if (languageId == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = timeZoneId;

			if (timeZoneId == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CompanyServiceUtil.class.getName(),
					"updateDisplay",
					new Object[] { paramObj0, paramObj1, paramObj2 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void updateLogo(HttpPrincipal httpPrincipal, long companyId,
		java.io.File file)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = file;

			if (file == null) {
				paramObj1 = new NullWrapper("java.io.File");
			}

			MethodWrapper methodWrapper = new MethodWrapper(CompanyServiceUtil.class.getName(),
					"updateLogo", new Object[] { paramObj0, paramObj1 });

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void updateSecurity(HttpPrincipal httpPrincipal,
		long companyId, java.lang.String authType, boolean autoLogin,
		boolean sendPassword, boolean strangers, boolean strangersWithMx,
		boolean strangersVerify, boolean communityLogo)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(companyId);

			Object paramObj1 = authType;

			if (authType == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = new BooleanWrapper(autoLogin);

			Object paramObj3 = new BooleanWrapper(sendPassword);

			Object paramObj4 = new BooleanWrapper(strangers);

			Object paramObj5 = new BooleanWrapper(strangersWithMx);

			Object paramObj6 = new BooleanWrapper(strangersVerify);

			Object paramObj7 = new BooleanWrapper(communityLogo);

			MethodWrapper methodWrapper = new MethodWrapper(CompanyServiceUtil.class.getName(),
					"updateSecurity",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7
					});

			try {
				TunnelUtil.invoke(httpPrincipal, methodWrapper);
			}
			catch (Exception e) {
				if (e instanceof com.liferay.portal.SystemException) {
					throw (com.liferay.portal.SystemException)e;
				}

				if (e instanceof com.liferay.portal.PortalException) {
					throw (com.liferay.portal.PortalException)e;
				}

				throw new com.liferay.portal.SystemException(e);
			}
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(CompanyServiceHttp.class);
}