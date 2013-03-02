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

package com.liferay.portlet.wiki.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.wiki.model.WikiNode;
import com.liferay.portlet.wiki.service.base.WikiNodeServiceBaseImpl;
import com.liferay.portlet.wiki.service.permission.WikiNodePermission;

/**
 * <a href="WikiNodeServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Charles May
 *
 */
public class WikiNodeServiceImpl extends WikiNodeServiceBaseImpl {

	public WikiNode addNode(
			long plid, String name, String description,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.WIKI,
			ActionKeys.ADD_NODE);

		return wikiNodeLocalService.addNode(
			getUserId(), plid, name, description, addCommunityPermissions,
			addGuestPermissions);
	}

	public WikiNode addNode(
			long plid, String name, String description,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.WIKI,
			ActionKeys.ADD_NODE);

		return wikiNodeLocalService.addNode(
			getUserId(), plid, name, description, communityPermissions,
			guestPermissions);
	}

	public void deleteNode(long nodeId)
		throws PortalException, SystemException {

		WikiNodePermission.check(
			getPermissionChecker(), nodeId, ActionKeys.DELETE);

		wikiNodeLocalService.deleteNode(nodeId);
	}

	public WikiNode getNode(long nodeId)
		throws PortalException, SystemException {

		WikiNodePermission.check(
			getPermissionChecker(), nodeId, ActionKeys.VIEW);

		return wikiNodeLocalService.getNode(nodeId);
	}

	public WikiNode updateNode(long nodeId, String name, String description)
		throws PortalException, SystemException {

		WikiNodePermission.check(
			getPermissionChecker(), nodeId, ActionKeys.UPDATE);

		return wikiNodeLocalService.updateNode(nodeId, name, description);
	}

}