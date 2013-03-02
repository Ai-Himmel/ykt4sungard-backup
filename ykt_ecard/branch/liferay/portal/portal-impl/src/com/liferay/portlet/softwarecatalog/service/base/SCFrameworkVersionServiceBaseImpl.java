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

package com.liferay.portlet.softwarecatalog.service.base;

import com.liferay.counter.service.CounterLocalService;
import com.liferay.counter.service.CounterLocalServiceFactory;
import com.liferay.counter.service.CounterService;
import com.liferay.counter.service.CounterServiceFactory;

import com.liferay.portal.service.ResourceLocalService;
import com.liferay.portal.service.ResourceLocalServiceFactory;
import com.liferay.portal.service.ResourceService;
import com.liferay.portal.service.ResourceServiceFactory;
import com.liferay.portal.service.UserLocalService;
import com.liferay.portal.service.UserLocalServiceFactory;
import com.liferay.portal.service.UserService;
import com.liferay.portal.service.UserServiceFactory;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.persistence.ResourceFinder;
import com.liferay.portal.service.persistence.ResourceFinderUtil;
import com.liferay.portal.service.persistence.ResourcePersistence;
import com.liferay.portal.service.persistence.ResourceUtil;
import com.liferay.portal.service.persistence.UserFinder;
import com.liferay.portal.service.persistence.UserFinderUtil;
import com.liferay.portal.service.persistence.UserPersistence;
import com.liferay.portal.service.persistence.UserUtil;

import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalService;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionService;
import com.liferay.portlet.softwarecatalog.service.SCLicenseLocalService;
import com.liferay.portlet.softwarecatalog.service.SCLicenseLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCLicenseService;
import com.liferay.portlet.softwarecatalog.service.SCLicenseServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalService;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryService;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalService;
import com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductVersionLocalService;
import com.liferay.portlet.softwarecatalog.service.SCProductVersionLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductVersionService;
import com.liferay.portlet.softwarecatalog.service.SCProductVersionServiceFactory;
import com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionPersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCFrameworkVersionUtil;
import com.liferay.portlet.softwarecatalog.service.persistence.SCLicensePersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCLicenseUtil;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryPersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductEntryUtil;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotPersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductScreenshotUtil;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionPersistence;
import com.liferay.portlet.softwarecatalog.service.persistence.SCProductVersionUtil;

import org.springframework.beans.factory.InitializingBean;

/**
 * <a href="SCFrameworkVersionServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class SCFrameworkVersionServiceBaseImpl extends PrincipalBean
	implements SCFrameworkVersionService, InitializingBean {
	public SCLicenseLocalService getSCLicenseLocalService() {
		return scLicenseLocalService;
	}

	public void setSCLicenseLocalService(
		SCLicenseLocalService scLicenseLocalService) {
		this.scLicenseLocalService = scLicenseLocalService;
	}

	public SCLicenseService getSCLicenseService() {
		return scLicenseService;
	}

	public void setSCLicenseService(SCLicenseService scLicenseService) {
		this.scLicenseService = scLicenseService;
	}

	public SCLicensePersistence getSCLicensePersistence() {
		return scLicensePersistence;
	}

	public void setSCLicensePersistence(
		SCLicensePersistence scLicensePersistence) {
		this.scLicensePersistence = scLicensePersistence;
	}

	public SCFrameworkVersionLocalService getSCFrameworkVersionLocalService() {
		return scFrameworkVersionLocalService;
	}

	public void setSCFrameworkVersionLocalService(
		SCFrameworkVersionLocalService scFrameworkVersionLocalService) {
		this.scFrameworkVersionLocalService = scFrameworkVersionLocalService;
	}

	public SCFrameworkVersionPersistence getSCFrameworkVersionPersistence() {
		return scFrameworkVersionPersistence;
	}

	public void setSCFrameworkVersionPersistence(
		SCFrameworkVersionPersistence scFrameworkVersionPersistence) {
		this.scFrameworkVersionPersistence = scFrameworkVersionPersistence;
	}

	public SCProductEntryLocalService getSCProductEntryLocalService() {
		return scProductEntryLocalService;
	}

	public void setSCProductEntryLocalService(
		SCProductEntryLocalService scProductEntryLocalService) {
		this.scProductEntryLocalService = scProductEntryLocalService;
	}

	public SCProductEntryService getSCProductEntryService() {
		return scProductEntryService;
	}

	public void setSCProductEntryService(
		SCProductEntryService scProductEntryService) {
		this.scProductEntryService = scProductEntryService;
	}

	public SCProductEntryPersistence getSCProductEntryPersistence() {
		return scProductEntryPersistence;
	}

	public void setSCProductEntryPersistence(
		SCProductEntryPersistence scProductEntryPersistence) {
		this.scProductEntryPersistence = scProductEntryPersistence;
	}

	public SCProductScreenshotLocalService getSCProductScreenshotLocalService() {
		return scProductScreenshotLocalService;
	}

	public void setSCProductScreenshotLocalService(
		SCProductScreenshotLocalService scProductScreenshotLocalService) {
		this.scProductScreenshotLocalService = scProductScreenshotLocalService;
	}

	public SCProductScreenshotPersistence getSCProductScreenshotPersistence() {
		return scProductScreenshotPersistence;
	}

	public void setSCProductScreenshotPersistence(
		SCProductScreenshotPersistence scProductScreenshotPersistence) {
		this.scProductScreenshotPersistence = scProductScreenshotPersistence;
	}

	public SCProductVersionLocalService getSCProductVersionLocalService() {
		return scProductVersionLocalService;
	}

	public void setSCProductVersionLocalService(
		SCProductVersionLocalService scProductVersionLocalService) {
		this.scProductVersionLocalService = scProductVersionLocalService;
	}

	public SCProductVersionService getSCProductVersionService() {
		return scProductVersionService;
	}

	public void setSCProductVersionService(
		SCProductVersionService scProductVersionService) {
		this.scProductVersionService = scProductVersionService;
	}

	public SCProductVersionPersistence getSCProductVersionPersistence() {
		return scProductVersionPersistence;
	}

	public void setSCProductVersionPersistence(
		SCProductVersionPersistence scProductVersionPersistence) {
		this.scProductVersionPersistence = scProductVersionPersistence;
	}

	public CounterLocalService getCounterLocalService() {
		return counterLocalService;
	}

	public void setCounterLocalService(CounterLocalService counterLocalService) {
		this.counterLocalService = counterLocalService;
	}

	public CounterService getCounterService() {
		return counterService;
	}

	public void setCounterService(CounterService counterService) {
		this.counterService = counterService;
	}

	public ResourceLocalService getResourceLocalService() {
		return resourceLocalService;
	}

	public void setResourceLocalService(
		ResourceLocalService resourceLocalService) {
		this.resourceLocalService = resourceLocalService;
	}

	public ResourceService getResourceService() {
		return resourceService;
	}

	public void setResourceService(ResourceService resourceService) {
		this.resourceService = resourceService;
	}

	public ResourcePersistence getResourcePersistence() {
		return resourcePersistence;
	}

	public void setResourcePersistence(ResourcePersistence resourcePersistence) {
		this.resourcePersistence = resourcePersistence;
	}

	public ResourceFinder getResourceFinder() {
		return resourceFinder;
	}

	public void setResourceFinder(ResourceFinder resourceFinder) {
		this.resourceFinder = resourceFinder;
	}

	public UserLocalService getUserLocalService() {
		return userLocalService;
	}

	public void setUserLocalService(UserLocalService userLocalService) {
		this.userLocalService = userLocalService;
	}

	public UserService getUserService() {
		return userService;
	}

	public void setUserService(UserService userService) {
		this.userService = userService;
	}

	public UserPersistence getUserPersistence() {
		return userPersistence;
	}

	public void setUserPersistence(UserPersistence userPersistence) {
		this.userPersistence = userPersistence;
	}

	public UserFinder getUserFinder() {
		return userFinder;
	}

	public void setUserFinder(UserFinder userFinder) {
		this.userFinder = userFinder;
	}

	public void afterPropertiesSet() {
		if (scLicenseLocalService == null) {
			scLicenseLocalService = SCLicenseLocalServiceFactory.getImpl();
		}

		if (scLicenseService == null) {
			scLicenseService = SCLicenseServiceFactory.getImpl();
		}

		if (scLicensePersistence == null) {
			scLicensePersistence = SCLicenseUtil.getPersistence();
		}

		if (scFrameworkVersionLocalService == null) {
			scFrameworkVersionLocalService = SCFrameworkVersionLocalServiceFactory.getImpl();
		}

		if (scFrameworkVersionPersistence == null) {
			scFrameworkVersionPersistence = SCFrameworkVersionUtil.getPersistence();
		}

		if (scProductEntryLocalService == null) {
			scProductEntryLocalService = SCProductEntryLocalServiceFactory.getImpl();
		}

		if (scProductEntryService == null) {
			scProductEntryService = SCProductEntryServiceFactory.getImpl();
		}

		if (scProductEntryPersistence == null) {
			scProductEntryPersistence = SCProductEntryUtil.getPersistence();
		}

		if (scProductScreenshotLocalService == null) {
			scProductScreenshotLocalService = SCProductScreenshotLocalServiceFactory.getImpl();
		}

		if (scProductScreenshotPersistence == null) {
			scProductScreenshotPersistence = SCProductScreenshotUtil.getPersistence();
		}

		if (scProductVersionLocalService == null) {
			scProductVersionLocalService = SCProductVersionLocalServiceFactory.getImpl();
		}

		if (scProductVersionService == null) {
			scProductVersionService = SCProductVersionServiceFactory.getImpl();
		}

		if (scProductVersionPersistence == null) {
			scProductVersionPersistence = SCProductVersionUtil.getPersistence();
		}

		if (counterLocalService == null) {
			counterLocalService = CounterLocalServiceFactory.getImpl();
		}

		if (counterService == null) {
			counterService = CounterServiceFactory.getImpl();
		}

		if (resourceLocalService == null) {
			resourceLocalService = ResourceLocalServiceFactory.getImpl();
		}

		if (resourceService == null) {
			resourceService = ResourceServiceFactory.getImpl();
		}

		if (resourcePersistence == null) {
			resourcePersistence = ResourceUtil.getPersistence();
		}

		if (resourceFinder == null) {
			resourceFinder = ResourceFinderUtil.getFinder();
		}

		if (userLocalService == null) {
			userLocalService = UserLocalServiceFactory.getImpl();
		}

		if (userService == null) {
			userService = UserServiceFactory.getImpl();
		}

		if (userPersistence == null) {
			userPersistence = UserUtil.getPersistence();
		}

		if (userFinder == null) {
			userFinder = UserFinderUtil.getFinder();
		}
	}

	protected SCLicenseLocalService scLicenseLocalService;
	protected SCLicenseService scLicenseService;
	protected SCLicensePersistence scLicensePersistence;
	protected SCFrameworkVersionLocalService scFrameworkVersionLocalService;
	protected SCFrameworkVersionPersistence scFrameworkVersionPersistence;
	protected SCProductEntryLocalService scProductEntryLocalService;
	protected SCProductEntryService scProductEntryService;
	protected SCProductEntryPersistence scProductEntryPersistence;
	protected SCProductScreenshotLocalService scProductScreenshotLocalService;
	protected SCProductScreenshotPersistence scProductScreenshotPersistence;
	protected SCProductVersionLocalService scProductVersionLocalService;
	protected SCProductVersionService scProductVersionService;
	protected SCProductVersionPersistence scProductVersionPersistence;
	protected CounterLocalService counterLocalService;
	protected CounterService counterService;
	protected ResourceLocalService resourceLocalService;
	protected ResourceService resourceService;
	protected ResourcePersistence resourcePersistence;
	protected ResourceFinder resourceFinder;
	protected UserLocalService userLocalService;
	protected UserService userService;
	protected UserPersistence userPersistence;
	protected UserFinder userFinder;
}