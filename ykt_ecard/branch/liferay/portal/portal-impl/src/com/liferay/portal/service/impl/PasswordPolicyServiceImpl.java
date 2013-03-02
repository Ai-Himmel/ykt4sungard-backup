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

package com.liferay.portal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.service.base.PasswordPolicyServiceBaseImpl;
import com.liferay.portal.service.permission.PasswordPolicyPermissionUtil;
import com.liferay.portal.service.permission.PortalPermissionUtil;

/**
 * <a href="PasswordPolicyServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Scott Lee
 *
 */
public class PasswordPolicyServiceImpl extends PasswordPolicyServiceBaseImpl {

	public PasswordPolicy addPasswordPolicy(
			String name, String description, boolean changeable,
			boolean changeRequired, long minAge, boolean checkSyntax,
			boolean allowDictionaryWords, int minLength, boolean history,
			int historyCount, boolean expireable, long maxAge, long warningTime,
			int graceLimit, boolean lockout, int maxFailure,
			long lockoutDuration, long resetFailureCount)
		throws PortalException, SystemException {

		PortalPermissionUtil.check(
			getPermissionChecker(), ActionKeys.ADD_PASSWORD_POLICY);

		return passwordPolicyLocalService.addPasswordPolicy(
			getUserId(), false, name, description, changeable, changeRequired,
			minAge, checkSyntax, allowDictionaryWords, minLength, history,
			historyCount, expireable, maxAge, warningTime, graceLimit, lockout,
			maxFailure, lockoutDuration, resetFailureCount);
	}

	public void deletePasswordPolicy(long passwordPolicyId)
		throws PortalException, SystemException {

		PasswordPolicyPermissionUtil.check(
			getPermissionChecker(), passwordPolicyId, ActionKeys.DELETE);

		passwordPolicyLocalService.deletePasswordPolicy(passwordPolicyId);
	}

	public PasswordPolicy updatePasswordPolicy(
			long passwordPolicyId, String name, String description,
			boolean changeable, boolean changeRequired, long minAge,
			boolean checkSyntax, boolean allowDictionaryWords, int minLength,
			boolean history, int historyCount, boolean expireable, long maxAge,
			long warningTime, int graceLimit, boolean lockout, int maxFailure,
			long lockoutDuration, long resetFailureCount)
		throws PortalException, SystemException {

		PasswordPolicyPermissionUtil.check(
			getPermissionChecker(), passwordPolicyId, ActionKeys.UPDATE);

		return passwordPolicyLocalService.updatePasswordPolicy(
			passwordPolicyId, name, description, changeable, changeRequired,
			minAge, checkSyntax, allowDictionaryWords, minLength, history,
			historyCount, expireable, maxAge, warningTime, graceLimit, lockout,
			maxFailure, lockoutDuration, resetFailureCount);
	}

}