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

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.dao.DynamicQueryInitializer;

import com.liferay.portlet.softwarecatalog.model.SCProductScreenshot;
import com.liferay.portlet.softwarecatalog.model.impl.SCProductScreenshotImpl;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalService;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionService;
import com.liferay.portlet.softwarecatalog.service.SCFrameworkVersionServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCLicenseLocalService;
import com.liferay.portlet.softwarecatalog.service.SCLicenseLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCLicenseService;
import com.liferay.portlet.softwarecatalog.service.SCLicenseServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalService;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryLocalServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryService;
import com.liferay.portlet.softwarecatalog.service.SCProductEntryServiceFactory;
import com.liferay.portlet.softwarecatalog.service.SCProductScreenshotLocalService;
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

import java.util.List;

/**
 * <a href="SCProductScreenshotLocalServiceBaseImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public abstract class SCProductScreenshotLocalServiceBaseImpl
	implements SCProductScreenshotLocalService, InitializingBean {
	public SCProductScreenshot addSCProductScreenshot(SCProductScreenshot model)
		throws SystemException {
		SCProductScreenshot scProductScreenshot = new SCProductScreenshotImpl();

		scProductScreenshot.setNew(true);

		scProductScreenshot.setProductScreenshotId(model.getProductScreenshotId());
		scProductScreenshot.setCompanyId(model.getCompanyId());
		scProductScreenshot.setGroupId(model.getGroupId());
		scProductScreenshot.setProductEntryId(model.getProductEntryId());
		scProductScreenshot.setThumbnailId(model.getThumbnailId());
		scProductScreenshot.setFullImageId(model.getFullImageId());
		scProductScreenshot.setPriority(model.getPriority());

		return scProductScreenshotPersistence.update(scProductScreenshot);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer)
		throws SystemException {
		return scProductScreenshotPersistence.findWithDynamicQuery(queryInitializer);
	}

	public List dynamicQuery(DynamicQueryInitializer queryInitializer,
		int begin, int end) throws SystemException {
		return scProductScreenshotPersistence.findWithDynamicQuery(queryInitializer,
			begin, end);
	}

	public SCProductScreenshot updateSCProductScreenshot(
		SCProductScreenshot model) throws SystemException {
		SCProductScreenshot scProductScreenshot = new SCProductScreenshotImpl();

		scProductScreenshot.setNew(false);

		scProductScreenshot.setProductScreenshotId(model.getProductScreenshotId());
		scProductScreenshot.setCompanyId(model.getCompanyId());
		scProductScreenshot.setGroupId(model.getGroupId());
		scProductScreenshot.setProductEntryId(model.getProductEntryId());
		scProductScreenshot.setThumbnailId(model.getThumbnailId());
		scProductScreenshot.setFullImageId(model.getFullImageId());
		scProductScreenshot.setPriority(model.getPriority());

		return scProductScreenshotPersistence.update(scProductScreenshot);
	}

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

	public SCFrameworkVersionService getSCFrameworkVersionService() {
		return scFrameworkVersionService;
	}

	public void setSCFrameworkVersionService(
		SCFrameworkVersionService scFrameworkVersionService) {
		this.scFrameworkVersionService = scFrameworkVersionService;
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

		if (scFrameworkVersionService == null) {
			scFrameworkVersionService = SCFrameworkVersionServiceFactory.getImpl();
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
	}

	protected SCLicenseLocalService scLicenseLocalService;
	protected SCLicenseService scLicenseService;
	protected SCLicensePersistence scLicensePersistence;
	protected SCFrameworkVersionLocalService scFrameworkVersionLocalService;
	protected SCFrameworkVersionService scFrameworkVersionService;
	protected SCFrameworkVersionPersistence scFrameworkVersionPersistence;
	protected SCProductEntryLocalService scProductEntryLocalService;
	protected SCProductEntryService scProductEntryService;
	protected SCProductEntryPersistence scProductEntryPersistence;
	protected SCProductScreenshotPersistence scProductScreenshotPersistence;
	protected SCProductVersionLocalService scProductVersionLocalService;
	protected SCProductVersionService scProductVersionService;
	protected SCProductVersionPersistence scProductVersionPersistence;
}