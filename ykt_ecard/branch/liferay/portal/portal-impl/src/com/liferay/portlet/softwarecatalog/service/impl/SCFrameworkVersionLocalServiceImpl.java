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
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portlet.softwarecatalog.FrameworkVersionNameException;
import com.liferay.portlet.softwarecatalog.model.SCFrameworkVersion;
import com.liferay.portlet.softwarecatalog.service.base.SCFrameworkVersionLocalServiceBaseImpl;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

/**
 * <a href="SCFrameworkVersionLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Jorge Ferrer
 * @author Brian Wing Shun Chan
 *
 */
public class SCFrameworkVersionLocalServiceImpl
	extends SCFrameworkVersionLocalServiceBaseImpl {

	public SCFrameworkVersion addFrameworkVersion(
			long userId, long plid, String name, String url, boolean active,
			int priority, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		return addFrameworkVersion(
			userId, plid, name, url, active, priority,
			Boolean.valueOf(addCommunityPermissions),
			Boolean.valueOf(addGuestPermissions), null, null);
	}

	public SCFrameworkVersion addFrameworkVersion(
			long userId, long plid, String name, String url, boolean active,
			int priority, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		return addFrameworkVersion(
			userId, plid, name, url, active, priority, null, null,
			communityPermissions, guestPermissions);
	}

	public SCFrameworkVersion addFrameworkVersion(
			long userId, long plid, String name, String url, boolean active,
			int priority, Boolean addCommunityPermissions,
			Boolean addGuestPermissions, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		// Framework version

		User user = userPersistence.findByPrimaryKey(userId);
		long groupId = PortalUtil.getPortletGroupId(plid);
		Date now = new Date();

		validate(name);

		long frameworkVersionId = counterLocalService.increment();

		SCFrameworkVersion frameworkVersion =
			scFrameworkVersionPersistence.create(
				frameworkVersionId);

		frameworkVersion.setGroupId(groupId);
		frameworkVersion.setCompanyId(user.getCompanyId());
		frameworkVersion.setUserId(user.getUserId());
		frameworkVersion.setUserName(user.getFullName());
		frameworkVersion.setCreateDate(now);
		frameworkVersion.setModifiedDate(now);
		frameworkVersion.setName(name);
		frameworkVersion.setUrl(url);
		frameworkVersion.setActive(active);
		frameworkVersion.setPriority(priority);

		scFrameworkVersionPersistence.update(frameworkVersion);

		// Resources

		if ((addCommunityPermissions != null) &&
			(addGuestPermissions != null)) {

			addFrameworkVersionResources(
				frameworkVersion, addCommunityPermissions.booleanValue(),
				addGuestPermissions.booleanValue());
		}
		else {
			addFrameworkVersionResources(
				frameworkVersion, communityPermissions, guestPermissions);
		}

		return frameworkVersion;
	}

	public void addFrameworkVersionResources(
			long frameworkVersionId, boolean addCommunityPermissions,
			boolean addGuestPermissions)
		throws PortalException, SystemException {

		SCFrameworkVersion frameworkVersion =
			scFrameworkVersionPersistence.findByPrimaryKey(frameworkVersionId);

		addFrameworkVersionResources(
			frameworkVersion, addCommunityPermissions, addGuestPermissions);
	}

	public void addFrameworkVersionResources(
			SCFrameworkVersion frameworkVersion,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addResources(
			frameworkVersion.getCompanyId(), frameworkVersion.getGroupId(),
			frameworkVersion.getUserId(), SCFrameworkVersion.class.getName(),
			frameworkVersion.getFrameworkVersionId(), false,
			addCommunityPermissions, addGuestPermissions);
	}

	public void addFrameworkVersionResources(
			long frameworkVersionId, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		SCFrameworkVersion frameworkVersion =
			scFrameworkVersionPersistence.findByPrimaryKey(frameworkVersionId);

		addFrameworkVersionResources(
			frameworkVersion, communityPermissions, guestPermissions);
	}

	public void addFrameworkVersionResources(
			SCFrameworkVersion frameworkVersion, String[] communityPermissions,
			String[] guestPermissions)
		throws PortalException, SystemException {

		resourceLocalService.addModelResources(
			frameworkVersion.getCompanyId(), frameworkVersion.getGroupId(),
			frameworkVersion.getUserId(), SCFrameworkVersion.class.getName(),
			frameworkVersion.getFrameworkVersionId(), communityPermissions,
			guestPermissions);
	}

	public void deleteFrameworkVersion(long frameworkVersionId)
		throws PortalException, SystemException {

		scFrameworkVersionPersistence.remove(frameworkVersionId);
	}

	public void deleteFrameworkVersion(SCFrameworkVersion frameworkVersion)
		throws PortalException, SystemException {

		scFrameworkVersionPersistence.remove(frameworkVersion);
	}

	public void deleteFrameworkVersions(long groupId)
		throws PortalException, SystemException {

		Iterator itr = scFrameworkVersionPersistence.findByGroupId(
			groupId).iterator();

		while (itr.hasNext()) {
			SCFrameworkVersion frameworkVersion =
				(SCFrameworkVersion)itr.next();

			deleteFrameworkVersion(frameworkVersion);
		}
	}

	public SCFrameworkVersion getFrameworkVersion(long frameworkVersionId)
		throws PortalException, SystemException {

		return scFrameworkVersionPersistence.findByPrimaryKey(
			frameworkVersionId);
	}

	public List getFrameworkVersions(long groupId, int begin, int end)
		throws SystemException {

		return scFrameworkVersionPersistence.findByGroupId(groupId, begin, end);
	}

	public List getFrameworkVersions(long groupId, boolean active)
		throws SystemException {

		return scFrameworkVersionPersistence.findByG_A(groupId, active);
	}

	public List getFrameworkVersions(
			long groupId, boolean active, int begin, int end)
		throws SystemException {

		return scFrameworkVersionPersistence.findByG_A(
			groupId, active, begin, end);
	}

	public int getFrameworkVersionsCount(long groupId)
		throws SystemException {

		return scFrameworkVersionPersistence.countByGroupId(groupId);
	}

	public int getFrameworkVersionsCount(long groupId, boolean active)
		throws SystemException {

		return scFrameworkVersionPersistence.countByG_A(groupId, active);
	}

	public List getProductVersionFrameworkVersions(long productVersionId)
		throws PortalException, SystemException {

		return scProductVersionPersistence.getSCFrameworkVersions(
			productVersionId);
	}

	public SCFrameworkVersion updateFrameworkVersion(
			long frameworkVersionId, String name, String url, boolean active,
			int priority)
		throws PortalException, SystemException {

		validate(name);

		SCFrameworkVersion frameworkVersion =
			scFrameworkVersionPersistence.findByPrimaryKey(frameworkVersionId);

		frameworkVersion.setName(name);
		frameworkVersion.setUrl(url);
		frameworkVersion.setActive(active);
		frameworkVersion.setPriority(priority);

		scFrameworkVersionPersistence.update(frameworkVersion);

		return frameworkVersion;
	}

	protected void validate(String name) throws PortalException {
		if (Validator.isNull(name)) {
			throw new FrameworkVersionNameException();
		}
	}

}