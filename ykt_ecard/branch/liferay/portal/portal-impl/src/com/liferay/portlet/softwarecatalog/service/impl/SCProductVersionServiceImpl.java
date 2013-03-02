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

package com.liferay.portlet.softwarecatalog.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portlet.softwarecatalog.model.SCProductVersion;
import com.liferay.portlet.softwarecatalog.service.base.SCProductVersionServiceBaseImpl;
import com.liferay.portlet.softwarecatalog.service.permission.SCProductEntryPermission;

import java.util.List;

/**
 * <a href="SCProductVersionServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 *
 */
public class SCProductVersionServiceImpl
	extends SCProductVersionServiceBaseImpl {

	public SCProductVersion addProductVersion(
			long productEntryId, String version, String changeLog,
			String downloadPageURL, String directDownloadURL,
			boolean repoStoreArtifact, long[] frameworkVersionIds,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		SCProductEntryPermission.check(
			getPermissionChecker(), productEntryId, ActionKeys.UPDATE);

		return scProductVersionLocalService.addProductVersion(
			getUserId(), productEntryId, version, changeLog, downloadPageURL,
			directDownloadURL, repoStoreArtifact, frameworkVersionIds,
			addCommunityPermissions, addGuestPermissions);
	}

	public SCProductVersion addProductVersion(
			long productEntryId, String version, String changeLog,
			String downloadPageURL, String directDownloadURL,
			boolean repoStoreArtifact, long[] frameworkVersionIds,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		SCProductEntryPermission.check(
			getPermissionChecker(), productEntryId, ActionKeys.UPDATE);

		return scProductVersionLocalService.addProductVersion(
			getUserId(), productEntryId, version, changeLog, downloadPageURL,
			directDownloadURL, repoStoreArtifact, frameworkVersionIds,
			communityPermissions, guestPermissions);
	}

	public void deleteProductVersion(long productVersionId)
		throws PortalException, SystemException {

		SCProductVersion productVersion =
			scProductVersionLocalService.getProductVersion(productVersionId);

		SCProductEntryPermission.check(
			getPermissionChecker(), productVersion.getProductEntryId(),
			ActionKeys.UPDATE);

		scProductVersionLocalService.deleteProductVersion(productVersionId);
	}

	public SCProductVersion getProductVersion(long productVersionId)
		throws PortalException, SystemException {

		SCProductVersion productVersion =
			scProductVersionLocalService.getProductVersion(productVersionId);

		SCProductEntryPermission.check(
			getPermissionChecker(), productVersion.getProductEntryId(),
			ActionKeys.VIEW);

		return productVersion;
	}

	public List getProductVersions(long productEntryId, int begin, int end)
		throws SystemException, PortalException {

		SCProductEntryPermission.check(
			getPermissionChecker(), productEntryId, ActionKeys.VIEW);

		return scProductVersionLocalService.getProductVersions(
			productEntryId, begin, end);
	}

	public int getProductVersionsCount(long productEntryId)
		throws SystemException, PortalException {

		SCProductEntryPermission.check(
			getPermissionChecker(), productEntryId, ActionKeys.VIEW);

		return scProductVersionLocalService.getProductVersionsCount(
			productEntryId);
	}

	public SCProductVersion updateProductVersion(
			long productVersionId, String version, String changeLog,
			String downloadPageURL, String directDownloadURL,
			boolean repoStoreArtifact, long[] frameworkVersionIds)
		throws PortalException, SystemException {

		SCProductVersion productVersion =
			scProductVersionLocalService.getProductVersion(productVersionId);

		SCProductEntryPermission.check(
			getPermissionChecker(), productVersion.getProductEntryId(),
			ActionKeys.UPDATE);

		return scProductVersionLocalService.updateProductVersion(
			productVersionId, version, changeLog, downloadPageURL,
			directDownloadURL, repoStoreArtifact, frameworkVersionIds);
	}

}