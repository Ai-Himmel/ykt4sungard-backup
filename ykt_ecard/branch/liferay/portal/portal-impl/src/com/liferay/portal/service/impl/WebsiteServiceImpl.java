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
import com.liferay.portal.model.Website;
import com.liferay.portal.service.base.WebsiteServiceBaseImpl;
import com.liferay.portal.service.permission.CommonPermissionUtil;

import java.util.List;

/**
 * <a href="WebsiteServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WebsiteServiceImpl extends WebsiteServiceBaseImpl {

	public Website addWebsite(
			String className, long classPK, String url, int typeId,
			boolean primary)
		throws PortalException, SystemException {

		CommonPermissionUtil.check(
			getPermissionChecker(), className, classPK, ActionKeys.UPDATE);

		return websiteLocalService.addWebsite(
			getUserId(), className, classPK, url, typeId, primary);
	}

	public void deleteWebsite(long websiteId)
		throws PortalException, SystemException {

		Website website = websitePersistence.findByPrimaryKey(websiteId);

		CommonPermissionUtil.check(
			getPermissionChecker(), website.getClassNameId(),
			website.getClassPK(), ActionKeys.UPDATE);

		websiteLocalService.deleteWebsite(websiteId);
	}

	public Website getWebsite(long websiteId)
		throws PortalException, SystemException {

		Website website = websitePersistence.findByPrimaryKey(websiteId);

		CommonPermissionUtil.check(
			getPermissionChecker(), website.getClassNameId(),
			website.getClassPK(), ActionKeys.VIEW);

		return website;
	}

	public List getWebsites(String className, long classPK)
		throws PortalException, SystemException {

		CommonPermissionUtil.check(
			getPermissionChecker(), className, classPK, ActionKeys.VIEW);

		return websiteLocalService.getWebsites(
			getUser().getCompanyId(), className, classPK);
	}

	public Website updateWebsite(
			long websiteId, String url, int typeId, boolean primary)
		throws PortalException, SystemException {

		Website website = websitePersistence.findByPrimaryKey(websiteId);

		CommonPermissionUtil.check(
			getPermissionChecker(), website.getClassNameId(),
			website.getClassPK(), ActionKeys.UPDATE);

		return websiteLocalService.updateWebsite(
			websiteId, url, typeId, primary);
	}

}