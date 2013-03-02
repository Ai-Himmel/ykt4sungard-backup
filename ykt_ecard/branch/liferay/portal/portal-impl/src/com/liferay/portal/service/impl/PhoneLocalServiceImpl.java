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

import com.liferay.portal.PhoneNumberException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Phone;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ListTypeImpl;
import com.liferay.portal.service.base.PhoneLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.format.PhoneNumberUtil;

import java.rmi.RemoteException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="PhoneLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PhoneLocalServiceImpl extends PhoneLocalServiceBaseImpl {

	public Phone addPhone(
			long userId, String className, long classPK, String number,
			String extension, int typeId, boolean primary)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);
		Date now = new Date();

		number = PhoneNumberUtil.strip(number);
		extension = PhoneNumberUtil.strip(extension);

		validate(
			0, user.getCompanyId(), classNameId, classPK, number, typeId,
			primary);

		long phoneId = counterLocalService.increment();

		Phone phone = phonePersistence.create(phoneId);

		phone.setCompanyId(user.getCompanyId());
		phone.setUserId(user.getUserId());
		phone.setUserName(user.getFullName());
		phone.setCreateDate(now);
		phone.setModifiedDate(now);
		phone.setClassNameId(classNameId);
		phone.setClassPK(classPK);
		phone.setNumber(number);
		phone.setExtension(extension);
		phone.setTypeId(typeId);
		phone.setPrimary(primary);

		phonePersistence.update(phone);

		return phone;
	}

	public void deletePhone(long phoneId)
		throws PortalException, SystemException {

		phonePersistence.remove(phoneId);
	}

	public void deletePhones(long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		phonePersistence.removeByC_C_C(companyId, classNameId, classPK);
	}

	public Phone getPhone(long phoneId)
		throws PortalException, SystemException {

		return phonePersistence.findByPrimaryKey(phoneId);
	}

	public List getPhones() throws SystemException {
		return phonePersistence.findAll();
	}

	public List getPhones(long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return phonePersistence.findByC_C_C(companyId, classNameId, classPK);
	}

	public Phone updatePhone(
			long phoneId, String number, String extension, int typeId,
			boolean primary)
		throws PortalException, SystemException {

		number = PhoneNumberUtil.strip(number);
		extension = PhoneNumberUtil.strip(extension);

		validate(phoneId, 0, 0, 0, number, typeId, primary);

		Phone phone = phonePersistence.findByPrimaryKey(phoneId);

		phone.setModifiedDate(new Date());
		phone.setNumber(number);
		phone.setExtension(extension);
		phone.setTypeId(typeId);
		phone.setPrimary(primary);

		phonePersistence.update(phone);

		return phone;
	}

	protected void validate(
			long phoneId, long companyId, long classNameId, long classPK,
			String number, int typeId, boolean primary)
		throws PortalException, SystemException {

		if (Validator.isNull(number)) {
			throw new PhoneNumberException();
		}

		if (phoneId > 0) {
			Phone phone = phonePersistence.findByPrimaryKey(phoneId);

			companyId = phone.getCompanyId();
			classNameId = phone.getClassNameId();
			classPK = phone.getClassPK();
		}

		try {
			listTypeService.validate(typeId, classNameId, ListTypeImpl.PHONE);
		}
		catch (RemoteException re) {
			throw new SystemException(re);
		}

		validate(phoneId, companyId, classNameId, classPK, primary);
	}

	protected void validate(
			long phoneId, long companyId, long classNameId, long classPK,
			boolean primary)
		throws PortalException, SystemException {

		// Check to make sure there isn't another phone with the same company
		// id, class name, and class pk that also has primary set to true

		if (primary) {
			Iterator itr = phonePersistence.findByC_C_C_P(
				companyId, classNameId, classPK, primary).iterator();

			while (itr.hasNext()) {
				Phone phone = (Phone)itr.next();

				if ((phoneId <= 0) ||
					(phone.getPhoneId() != phoneId)) {

					phone.setPrimary(false);

					phonePersistence.update(phone);
				}
			}
		}
	}

}