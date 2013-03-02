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

import com.liferay.portal.EmailAddressException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.EmailAddress;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ListTypeImpl;
import com.liferay.portal.service.base.EmailAddressLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;

import java.rmi.RemoteException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="EmailAddressLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Brian Wing Shun Chan
 * @author Alexander Chow
 *
 */
public class EmailAddressLocalServiceImpl
	extends EmailAddressLocalServiceBaseImpl {

	public EmailAddress addEmailAddress(
			long userId, String className, long classPK, String address,
			int typeId, boolean primary)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);
		Date now = new Date();

		validate(
			0, user.getCompanyId(), classNameId, classPK, address, typeId,
			primary);

		long emailAddressId = counterLocalService.increment();

		EmailAddress emailAddress = emailAddressPersistence.create(
			emailAddressId);

		emailAddress.setCompanyId(user.getCompanyId());
		emailAddress.setUserId(user.getUserId());
		emailAddress.setUserName(user.getFullName());
		emailAddress.setCreateDate(now);
		emailAddress.setModifiedDate(now);
		emailAddress.setClassNameId(classNameId);
		emailAddress.setClassPK(classPK);
		emailAddress.setAddress(address);
		emailAddress.setTypeId(typeId);
		emailAddress.setPrimary(primary);

		emailAddressPersistence.update(emailAddress);

		return emailAddress;
	}

	public void deleteEmailAddress(long emailAddressId)
		throws PortalException, SystemException {

		emailAddressPersistence.remove(emailAddressId);
	}

	public void deleteEmailAddresses(
			long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		emailAddressPersistence.removeByC_C_C(companyId, classNameId, classPK);
	}

	public EmailAddress getEmailAddress(long emailAddressId)
		throws PortalException, SystemException {

		return emailAddressPersistence.findByPrimaryKey(emailAddressId);
	}

	public List getEmailAddresses() throws SystemException {
		return emailAddressPersistence.findAll();
	}

	public List getEmailAddresses(
			long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return emailAddressPersistence.findByC_C_C(
			companyId, classNameId, classPK);
	}

	public EmailAddress updateEmailAddress(
			long emailAddressId, String address, int typeId, boolean primary)
		throws PortalException, SystemException {

		validate(emailAddressId, 0, 0, 0, address, typeId, primary);

		EmailAddress emailAddress = emailAddressPersistence.findByPrimaryKey(
			emailAddressId);

		emailAddress.setModifiedDate(new Date());
		emailAddress.setAddress(address);
		emailAddress.setTypeId(typeId);
		emailAddress.setPrimary(primary);

		emailAddressPersistence.update(emailAddress);

		return emailAddress;
	}

	protected void validate(
			long emailAddressId, long companyId, long classNameId,
			long classPK, String address, int typeId, boolean primary)
		throws PortalException, SystemException {

		if (!Validator.isEmailAddress(address)) {
			throw new EmailAddressException();
		}

		if (emailAddressId > 0) {
			EmailAddress emailAddress =
				emailAddressPersistence.findByPrimaryKey(
					emailAddressId);

			companyId = emailAddress.getCompanyId();
			classNameId = emailAddress.getClassNameId();
			classPK = emailAddress.getClassPK();
		}

		try {
			listTypeService.validate(
				typeId, classNameId, ListTypeImpl.EMAIL_ADDRESS);
		}
		catch (RemoteException re) {
			throw new SystemException(re);
		}

		validate(emailAddressId, companyId, classNameId, classPK, primary);
	}

	protected void validate(
			long emailAddressId, long companyId, long classNameId, long classPK,
			boolean primary)
		throws PortalException, SystemException {

		// Check to make sure there isn't another emailAddress with the same
		// company id, class name, and class pk that also has primary set to
		// true

		if (primary) {
			Iterator itr = emailAddressPersistence.findByC_C_C_P(
				companyId, classNameId, classPK, primary).iterator();

			while (itr.hasNext()) {
				EmailAddress emailAddress = (EmailAddress)itr.next();

				if ((emailAddressId <= 0) ||
					(emailAddress.getEmailAddressId() != emailAddressId)) {

					emailAddress.setPrimary(false);

					emailAddressPersistence.update(emailAddress);
				}
			}
		}
	}

}