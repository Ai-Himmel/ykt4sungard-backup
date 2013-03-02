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

import com.liferay.portal.NoSuchSubscriptionException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Subscription;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.SubscriptionImpl;
import com.liferay.portal.service.base.SubscriptionLocalServiceBaseImpl;
import com.liferay.portal.util.PortalUtil;

import java.util.Date;
import java.util.List;

/**
 * <a href="SubscriptionLocalServiceImpl.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * @author Charles May
 *
 */
public class SubscriptionLocalServiceImpl
	extends SubscriptionLocalServiceBaseImpl {

	public Subscription addSubscription(
			long userId, String className, long classPK)
		throws PortalException, SystemException {

		return addSubscription(
			userId, className, classPK, SubscriptionImpl.FREQUENCY_INSTANT);
	}

	public Subscription addSubscription(
			long userId, String className, long classPK, String frequency)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);
		Date now = new Date();

		long subscriptionId = counterLocalService.increment();

		Subscription subscription = subscriptionPersistence.create(
			subscriptionId);

		subscription.setCompanyId(user.getCompanyId());
		subscription.setUserId(user.getUserId());
		subscription.setUserName(user.getFullName());
		subscription.setCreateDate(now);
		subscription.setModifiedDate(now);
		subscription.setClassNameId(classNameId);
		subscription.setClassPK(classPK);
		subscription.setFrequency(frequency);

		subscriptionPersistence.update(subscription);

		return subscription;
	}

	public void deleteSubscription(long subscriptionId)
		throws PortalException, SystemException {

		subscriptionPersistence.remove(subscriptionId);
	}

	public void deleteSubscription(
			long userId, String className, long classPK)
		throws PortalException, SystemException {

		User user = userPersistence.findByPrimaryKey(userId);
		long classNameId = PortalUtil.getClassNameId(className);

		subscriptionPersistence.removeByC_U_C_C(
			user.getCompanyId(), userId, classNameId, classPK);
	}

	public void deleteSubscriptions(long userId) throws SystemException {
		subscriptionPersistence.removeByUserId(userId);
	}

	public void deleteSubscriptions(
			long companyId, String className, long classPK)
		throws SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		subscriptionPersistence.removeByC_C_C(companyId, classNameId, classPK);
	}

	public Subscription getSubscription(
			long companyId, long userId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return subscriptionPersistence.findByC_U_C_C(
			companyId, userId, classNameId, classPK);
	}

	public List getSubscriptions(
			long companyId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		return subscriptionPersistence.findByC_C_C(
			companyId, classNameId, classPK);
	}

	public boolean isSubscribed(
			long companyId, long userId, String className, long classPK)
		throws PortalException, SystemException {

		long classNameId = PortalUtil.getClassNameId(className);

		try {
			subscriptionPersistence.findByC_U_C_C(
				companyId, userId, classNameId, classPK);

			return true;
		}
		catch (NoSuchSubscriptionException nsse) {
			return false;
		}
	}

}