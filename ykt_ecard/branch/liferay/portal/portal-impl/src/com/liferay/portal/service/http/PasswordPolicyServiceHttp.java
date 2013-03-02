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
import com.liferay.portal.kernel.util.IntegerWrapper;
import com.liferay.portal.kernel.util.LongWrapper;
import com.liferay.portal.kernel.util.MethodWrapper;
import com.liferay.portal.kernel.util.NullWrapper;
import com.liferay.portal.security.auth.HttpPrincipal;
import com.liferay.portal.service.PasswordPolicyServiceUtil;

/**
 * <a href="PasswordPolicyServiceHttp.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a HTTP utility for the
 * <code>com.liferay.portal.service.PasswordPolicyServiceUtil</code> service
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
 * @see com.liferay.portal.service.PasswordPolicyServiceUtil
 * @see com.liferay.portal.service.http.PasswordPolicyServiceSoap
 *
 */
public class PasswordPolicyServiceHttp {
	public static com.liferay.portal.model.PasswordPolicy addPasswordPolicy(
		HttpPrincipal httpPrincipal, java.lang.String name,
		java.lang.String description, boolean changeable,
		boolean changeRequired, long minAge, boolean checkSyntax,
		boolean allowDictionaryWords, int minLength, boolean history,
		int historyCount, boolean expireable, long maxAge, long warningTime,
		int graceLimit, boolean lockout, int maxFailure, long lockoutDuration,
		long resetFailureCount)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = name;

			if (name == null) {
				paramObj0 = new NullWrapper("java.lang.String");
			}

			Object paramObj1 = description;

			if (description == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = new BooleanWrapper(changeable);

			Object paramObj3 = new BooleanWrapper(changeRequired);

			Object paramObj4 = new LongWrapper(minAge);

			Object paramObj5 = new BooleanWrapper(checkSyntax);

			Object paramObj6 = new BooleanWrapper(allowDictionaryWords);

			Object paramObj7 = new IntegerWrapper(minLength);

			Object paramObj8 = new BooleanWrapper(history);

			Object paramObj9 = new IntegerWrapper(historyCount);

			Object paramObj10 = new BooleanWrapper(expireable);

			Object paramObj11 = new LongWrapper(maxAge);

			Object paramObj12 = new LongWrapper(warningTime);

			Object paramObj13 = new IntegerWrapper(graceLimit);

			Object paramObj14 = new BooleanWrapper(lockout);

			Object paramObj15 = new IntegerWrapper(maxFailure);

			Object paramObj16 = new LongWrapper(lockoutDuration);

			Object paramObj17 = new LongWrapper(resetFailureCount);

			MethodWrapper methodWrapper = new MethodWrapper(PasswordPolicyServiceUtil.class.getName(),
					"addPasswordPolicy",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17
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

			return (com.liferay.portal.model.PasswordPolicy)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	public static void deletePasswordPolicy(HttpPrincipal httpPrincipal,
		long passwordPolicyId)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(passwordPolicyId);

			MethodWrapper methodWrapper = new MethodWrapper(PasswordPolicyServiceUtil.class.getName(),
					"deletePasswordPolicy", new Object[] { paramObj0 });

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

	public static com.liferay.portal.model.PasswordPolicy updatePasswordPolicy(
		HttpPrincipal httpPrincipal, long passwordPolicyId,
		java.lang.String name, java.lang.String description,
		boolean changeable, boolean changeRequired, long minAge,
		boolean checkSyntax, boolean allowDictionaryWords, int minLength,
		boolean history, int historyCount, boolean expireable, long maxAge,
		long warningTime, int graceLimit, boolean lockout, int maxFailure,
		long lockoutDuration, long resetFailureCount)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		try {
			Object paramObj0 = new LongWrapper(passwordPolicyId);

			Object paramObj1 = name;

			if (name == null) {
				paramObj1 = new NullWrapper("java.lang.String");
			}

			Object paramObj2 = description;

			if (description == null) {
				paramObj2 = new NullWrapper("java.lang.String");
			}

			Object paramObj3 = new BooleanWrapper(changeable);

			Object paramObj4 = new BooleanWrapper(changeRequired);

			Object paramObj5 = new LongWrapper(minAge);

			Object paramObj6 = new BooleanWrapper(checkSyntax);

			Object paramObj7 = new BooleanWrapper(allowDictionaryWords);

			Object paramObj8 = new IntegerWrapper(minLength);

			Object paramObj9 = new BooleanWrapper(history);

			Object paramObj10 = new IntegerWrapper(historyCount);

			Object paramObj11 = new BooleanWrapper(expireable);

			Object paramObj12 = new LongWrapper(maxAge);

			Object paramObj13 = new LongWrapper(warningTime);

			Object paramObj14 = new IntegerWrapper(graceLimit);

			Object paramObj15 = new BooleanWrapper(lockout);

			Object paramObj16 = new IntegerWrapper(maxFailure);

			Object paramObj17 = new LongWrapper(lockoutDuration);

			Object paramObj18 = new LongWrapper(resetFailureCount);

			MethodWrapper methodWrapper = new MethodWrapper(PasswordPolicyServiceUtil.class.getName(),
					"updatePasswordPolicy",
					new Object[] {
						paramObj0, paramObj1, paramObj2, paramObj3, paramObj4,
						paramObj5, paramObj6, paramObj7, paramObj8, paramObj9,
						paramObj10, paramObj11, paramObj12, paramObj13,
						paramObj14, paramObj15, paramObj16, paramObj17,
						paramObj18
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

			return (com.liferay.portal.model.PasswordPolicy)returnObj;
		}
		catch (com.liferay.portal.SystemException se) {
			_log.error(se, se);

			throw se;
		}
	}

	private static Log _log = LogFactoryUtil.getLog(PasswordPolicyServiceHttp.class);
}