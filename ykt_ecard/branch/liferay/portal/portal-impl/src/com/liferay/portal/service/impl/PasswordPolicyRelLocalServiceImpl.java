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

import com.liferay.portal.NoSuchPasswordPolicyRelException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.PasswordPolicyRel;
import com.liferay.portal.service.base.PasswordPolicyRelLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;

/**
 * <a href="PasswordPolicyRelLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Scott Lee
 *
 */
public class PasswordPolicyRelLocalServiceImpl
	extends PasswordPolicyRelLocalServiceBaseImpl {

	public PasswordPolicyRel addPasswordPolicyRel(
			long passwordPolicyId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		PasswordPolicyRel passwordPolicyRel =
			passwordPolicyRelPersistence.fetchByP_C_C(
				passwordPolicyId, classNameId, classPK);

		if (passwordPolicyRel != null) {
			return null;
		}

		try {

			// Ensure that models only have one password policy

			passwordPolicyRelPersistence.removeByC_C(classNameId, classPK);
		}
		catch (NoSuchPasswordPolicyRelException nsppre) {
		}

		long passwordPolicyRelId = counterLocalService.increment();

		passwordPolicyRel = passwordPolicyRelPersistence.create(
			passwordPolicyRelId);

		passwordPolicyRel.setPasswordPolicyId(passwordPolicyId);
		passwordPolicyRel.setClassNameId(classNameId);
		passwordPolicyRel.setClassPK(classPK);

		passwordPolicyRelPersistence.update(passwordPolicyRel);

		return passwordPolicyRel;
	}

	public void addPasswordPolicyRels(
			long passwordPolicyId, String className, long[] classPKs)
		throws PortalException, SystemException {

		for (int i = 0; i < classPKs.length; i++) {
			addPasswordPolicyRel(passwordPolicyId, className, classPKs[i]);
		}
	}

	public void deletePasswordPolicyRel(String className, long classPK)
		throws PortalException, SystemException {

		try {
			long classNameId = PortalUtil.getClassNameId(className);

			passwordPolicyRelPersistence.removeByC_C(classNameId, classPK);
		}
		catch (NoSuchPasswordPolicyRelException nsppre) {
		}
	}

	public void deletePasswordPolicyRel(
			long passwordPolicyId, String className, long classPK)
		throws PortalException, SystemException {

		try {
			long classNameId = PortalUtil.getClassNameId(className);

			passwordPolicyRelPersistence.removeByP_C_C(
				passwordPolicyId, classNameId, classPK);
		}
		catch (NoSuchPasswordPolicyRelException nsppre) {
		}
	}

	public void deletePasswordPolicyRels(
			long passwordPolicyId, String className, long[] classPKs)
		throws PortalException, SystemException {

		for (int i = 0; i < classPKs.length; i++) {
			deletePasswordPolicyRel(passwordPolicyId, className, classPKs[i]);
		}
	}

	public PasswordPolicyRel getPasswordPolicyRel(
			String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return passwordPolicyRelPersistence.findByC_C(classNameId, classPK);
	}

	public PasswordPolicyRel getPasswordPolicyRel(
			long passwordPolicyId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return passwordPolicyRelPersistence.findByP_C_C(
			passwordPolicyId, classNameId, classPK);
	}

	public boolean hasPasswordPolicyRel(
			long passwordPolicyId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		PasswordPolicyRel passwordPolicyRel =
			passwordPolicyRelPersistence.fetchByP_C_C(
				passwordPolicyId, classNameId, classPK);

		if (passwordPolicyRel != null) {
			return true;
		}
		else {
			return false;
		}
	}

}