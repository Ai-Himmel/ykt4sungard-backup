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

import com.liferay.portal.DuplicatePasswordPolicyException;
import com.liferay.portal.NoSuchPasswordPolicyException;
import com.liferay.portal.NoSuchPasswordPolicyRelException;
import com.liferay.portal.PasswordPolicyNameException;
import com.liferay.portal.PortalException;
import com.liferay.portal.RequiredPasswordPolicyException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.OrderByComparator;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.model.PasswordPolicyRel;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ResourceImpl;
import com.liferay.portal.security.ldap.PortalLDAPUtil;
import com.liferay.portal.service.base.PasswordPolicyLocalServiceBaseImpl;
import com.liferay.portal.util.PropsValues;

import java.util.Date;
import java.util.List;

/**
 * <a href="PasswordPolicyLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Scott Lee
 *
 */
public class PasswordPolicyLocalServiceImpl
	extends PasswordPolicyLocalServiceBaseImpl {

	public PasswordPolicy addPasswordPolicy(
			long userId, boolean defaultPolicy, String name, String description,
			boolean changeable, boolean changeRequired, long minAge,
			boolean checkSyntax, boolean allowDictionaryWords, int minLength,
			boolean history, int historyCount, boolean expireable, long maxAge,
			long warningTime, int graceLimit, boolean lockout, int maxFailure,
			long lockoutDuration, long resetFailureCount)
		throws PortalException, SystemException {

		// Password policy

		User user = userPersistence.findByPrimaryKey(userId);
		Date now = new Date();

		validate(0, user.getCompanyId(), name);

		long passwordPolicyId = counterLocalService.increment();

		PasswordPolicy passwordPolicy = passwordPolicyPersistence.create(
			passwordPolicyId);

		passwordPolicy.setUserId(userId);
		passwordPolicy.setCompanyId(user.getCompanyId());
		passwordPolicy.setUserName(user.getFullName());
		passwordPolicy.setCreateDate(now);
		passwordPolicy.setModifiedDate(now);
		passwordPolicy.setDefaultPolicy(defaultPolicy);
		passwordPolicy.setName(name);
		passwordPolicy.setDescription(description);
		passwordPolicy.setChangeable(changeable);
		passwordPolicy.setChangeRequired(changeRequired);
		passwordPolicy.setMinAge(minAge);
		passwordPolicy.setCheckSyntax(checkSyntax);
		passwordPolicy.setAllowDictionaryWords(allowDictionaryWords);
		passwordPolicy.setMinLength(minLength);
		passwordPolicy.setHistory(history);
		passwordPolicy.setHistoryCount(historyCount);
		passwordPolicy.setExpireable(expireable);
		passwordPolicy.setMaxAge(maxAge);
		passwordPolicy.setWarningTime(warningTime);
		passwordPolicy.setGraceLimit(graceLimit);
		passwordPolicy.setLockout(lockout);
		passwordPolicy.setMaxFailure(maxFailure);
		passwordPolicy.setLockoutDuration(lockoutDuration);
		passwordPolicy.setRequireUnlock(lockoutDuration == 0);
		passwordPolicy.setResetFailureCount(resetFailureCount);

		passwordPolicyPersistence.update(passwordPolicy);

		// Resources

		if (!user.isDefaultUser()) {
			resourceLocalService.addResources(
				user.getCompanyId(), 0, userId, PasswordPolicy.class.getName(),
				passwordPolicy.getPasswordPolicyId(), false, false, false);
		}

		return passwordPolicy;
	}

	public void checkDefaultPasswordPolicy(long companyId)
		throws PortalException, SystemException {

		String defaultPasswordPolicyName =
			PropsValues.PASSWORDS_DEFAULT_POLICY_NAME;

		try {
			passwordPolicyPersistence.findByC_N(
				companyId, defaultPasswordPolicyName);
		}
		catch (NoSuchPasswordPolicyException nsppe) {
			long defaultUserId = userLocalService.getDefaultUserId(companyId);

			addPasswordPolicy(
				defaultUserId, true, defaultPasswordPolicyName,
				defaultPasswordPolicyName, true, false, 0, false, true, 6,
				false, 6, false, 8640000, 86400, 0, false, 3, 0, 600);
		}
	}

	public void deletePasswordPolicy(long passwordPolicyId)
		throws PortalException, SystemException {

		PasswordPolicy passwordPolicy =
			passwordPolicyPersistence.findByPrimaryKey(passwordPolicyId);

		if (passwordPolicy.isDefaultPolicy()) {
			throw new RequiredPasswordPolicyException();
		}

		// Resources

		resourceLocalService.deleteResource(
			passwordPolicy.getCompanyId(), PasswordPolicy.class.getName(),
			ResourceImpl.SCOPE_INDIVIDUAL,
			passwordPolicy.getPasswordPolicyId());

		// Password policy

		passwordPolicyPersistence.remove(passwordPolicyId);
	}

	public PasswordPolicy getDefaultPasswordPolicy(long companyId)
		throws PortalException, SystemException {

		if (PortalLDAPUtil.isPasswordPolicyEnabled(companyId)) {
			return null;
		}

		return passwordPolicyPersistence.findByC_DP(companyId, true);
	}

	public PasswordPolicy getPasswordPolicy(long passwordPolicyId)
		throws PortalException, SystemException {

		return passwordPolicyPersistence.findByPrimaryKey(passwordPolicyId);
	}

	/**
	 * @deprecated
	 */
	public PasswordPolicy getPasswordPolicy(
			long companyId, long organizationId, long locationId)
		throws PortalException, SystemException {

		return getPasswordPolicy(
			companyId, new long[] {organizationId, locationId});
	}

	public PasswordPolicy getPasswordPolicy(
			long companyId, long[] organizationIds)
		throws PortalException, SystemException {

		if (PortalLDAPUtil.isPasswordPolicyEnabled(companyId)) {
			return null;
		}

		PasswordPolicyRel passwordPolicyRel = null;

		// Check for password policy specifically assigned to any of the
		// organizations

		for (int i = 0; i < organizationIds.length; i++) {
			long organizationId = organizationIds[i];

			try {
				passwordPolicyRel =
					passwordPolicyRelLocalService.getPasswordPolicyRel(
						Organization.class.getName(), organizationId);

				return getPasswordPolicy(
					passwordPolicyRel.getPasswordPolicyId());
			}
			catch (NoSuchPasswordPolicyRelException nsppre) {
			}
		}

		// Get default password policy

		return getDefaultPasswordPolicy(companyId);
	}

	public PasswordPolicy getPasswordPolicyByUserId(long userId)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);

		if (PortalLDAPUtil.isPasswordPolicyEnabled(user.getCompanyId())) {
			return null;
		}

		PasswordPolicyRel passwordPolicyRel = null;

		// Check for password policy specifically assigned to this user

		try {
			passwordPolicyRel =
				passwordPolicyRelLocalService.getPasswordPolicyRel(
					User.class.getName(), userId);

			return getPasswordPolicy(passwordPolicyRel.getPasswordPolicyId());
		}
		catch (NoSuchPasswordPolicyRelException nsppre) {
		}

		long[] organizationIds = user.getOrganizationIds();

		return getPasswordPolicy(user.getCompanyId(), organizationIds);
	}

	public List search(
			long companyId, String name, int begin, int end,
			OrderByComparator obc)
		throws SystemException {

		return passwordPolicyFinder.findByC_N(companyId, name, begin, end, obc);
	}

	public int searchCount(long companyId, String name)
		throws SystemException {

		return passwordPolicyFinder.countByC_N(companyId, name);
	}

	public PasswordPolicy updatePasswordPolicy(
			long passwordPolicyId, String name, String description,
			boolean changeable, boolean changeRequired, long minAge,
			boolean checkSyntax, boolean allowDictionaryWords, int minLength,
			boolean history, int historyCount, boolean expireable, long maxAge,
			long warningTime, int graceLimit, boolean lockout, int maxFailure,
			long lockoutDuration, long resetFailureCount)
		throws PortalException, SystemException {

		Date now = new Date();

		PasswordPolicy passwordPolicy =
			passwordPolicyPersistence.findByPrimaryKey(
				passwordPolicyId);

		if (!passwordPolicy.getDefaultPolicy()) {
			validate(passwordPolicyId, passwordPolicy.getCompanyId(), name);

			passwordPolicy.setName(name);
		}

		passwordPolicy.setModifiedDate(now);
		passwordPolicy.setDescription(description);
		passwordPolicy.setChangeable(changeable);
		passwordPolicy.setChangeRequired(changeRequired);
		passwordPolicy.setMinAge(minAge);
		passwordPolicy.setCheckSyntax(checkSyntax);
		passwordPolicy.setAllowDictionaryWords(allowDictionaryWords);
		passwordPolicy.setMinLength(minLength);
		passwordPolicy.setHistory(history);
		passwordPolicy.setHistoryCount(historyCount);
		passwordPolicy.setExpireable(expireable);
		passwordPolicy.setMaxAge(maxAge);
		passwordPolicy.setWarningTime(warningTime);
		passwordPolicy.setGraceLimit(graceLimit);
		passwordPolicy.setLockout(lockout);
		passwordPolicy.setMaxFailure(maxFailure);
		passwordPolicy.setLockoutDuration(lockoutDuration);
		passwordPolicy.setRequireUnlock(lockoutDuration == 0);
		passwordPolicy.setResetFailureCount(resetFailureCount);

		passwordPolicyPersistence.update(passwordPolicy);

		return passwordPolicy;
	}

	protected void validate(long passwordPolicyId, long companyId, String name)
		throws PortalException, SystemException {

		if ((Validator.isNull(name)) || (Validator.isNumber(name)) ||
			(name.indexOf(StringPool.COMMA) != -1) ||
			(name.indexOf(StringPool.STAR) != -1)) {

			throw new PasswordPolicyNameException();
		}

		try {
			PasswordPolicy passwordPolicy = passwordPolicyPersistence.findByC_N(
				companyId, name);

			if ((passwordPolicyId <= 0) ||
				(passwordPolicy.getPasswordPolicyId() != passwordPolicyId)) {

				throw new DuplicatePasswordPolicyException();
			}
		}
		catch (NoSuchPasswordPolicyException nsge) {
		}
	}

}