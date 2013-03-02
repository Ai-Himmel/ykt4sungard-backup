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

package com.liferay.portal.service.impl;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.auth.PrincipalFinder;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import java.security.Principal;

import javax.ejb.SessionContext;

/**
 * <a href="PrincipalSessionBean.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.13 $
 *
 */
public class PrincipalSessionBean {

	public static final String JRUN_ANONYMOUS = "anonymus-guest";

	public static final String ORACLE_ANONYMOUS = "guest";

	public static final String SUN_ANONYMOUS = "ANONYMOUS";

	public static final String WEBLOGIC_ANONYMOUS = "<anonymous>";

	public static final String[] ANONYMOUS_NAMES = {
		JRUN_ANONYMOUS, ORACLE_ANONYMOUS, SUN_ANONYMOUS, WEBLOGIC_ANONYMOUS
	};

	public static String getUserId(SessionContext sc)
		throws PrincipalException {

		Principal principal = null;

		try {
			principal = sc.getCallerPrincipal();
		}
		catch (Exception e) {
			throw new PrincipalException(e);
		}

		if (principal == null) {
			throw new PrincipalException();
		}

		String name = principal.getName();

		PrincipalFinder principalFinder = null;

		try {
			principalFinder = (PrincipalFinder)InstancePool.get(
				PropsUtil.get(PropsUtil.PRINCIPAL_FINDER));

			name = principalFinder.toLiferay(name);
		}
		catch (Exception e) {
		}

		if (Validator.isNull(name)) {
			throw new PrincipalException("Principal cannot be null");
		}
		else {
			for (int i = 0; i < ANONYMOUS_NAMES.length; i++) {
				if (name.equalsIgnoreCase(ANONYMOUS_NAMES[i])) {
					throw new PrincipalException(
						"Principal cannot be " + ANONYMOUS_NAMES[i]);
				}
			}
		}

		return name;
	}

}