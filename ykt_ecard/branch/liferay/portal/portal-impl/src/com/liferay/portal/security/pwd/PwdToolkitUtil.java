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

package com.liferay.portal.security.pwd;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.util.PropsUtil;

/**
 * <a href="PwdToolkitUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PwdToolkitUtil {

	public static String generate() {
		return _instance._generate();
	}

	public static void validate(
			long companyId, long userId, String password1, String password2,
			PasswordPolicy passwordPolicy)
		throws PortalException, SystemException {

		if (!password1.equals(password2)) {
			throw new UserPasswordException(
				UserPasswordException.PASSWORDS_DO_NOT_MATCH);
		}

		if (!PortalLDAPUtil.isPasswordPolicyEnabled(companyId)) {
			_instance._validate(userId, password1, password2, passwordPolicy);
		}
	}

	private PwdToolkitUtil() {
		_toolkit = (BasicToolkit)InstancePool.get(
			PropsUtil.get(PropsUtil.PASSWORDS_TOOLKIT));
	}

	private String _generate() {
		return _toolkit.generate();
	}

	private void _validate(
			long userId, String password1, String password2,
			PasswordPolicy passwordPolicy)
		throws PortalException, SystemException {

		_toolkit.validate(userId, password1, password2, passwordPolicy);
	}

	private static PwdToolkitUtil _instance = new PwdToolkitUtil();

	private BasicToolkit _toolkit;

}