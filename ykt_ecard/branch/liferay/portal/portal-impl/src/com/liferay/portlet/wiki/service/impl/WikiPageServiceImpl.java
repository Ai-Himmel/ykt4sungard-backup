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
import com.liferay.portlet.wiki.model.WikiPage;
import com.liferay.portlet.wiki.service.base.WikiPageServiceBaseImpl;
import com.liferay.portlet.wiki.service.permission.WikiNodePermission;
import com.liferay.portlet.wiki.service.permission.WikiPagePermission;

/**
 * <a href="WikiPageServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class WikiPageServiceImpl extends WikiPageServiceBaseImpl {

	public WikiPage addPage(long nodeId, String title)
		throws PortalException, SystemException {

		WikiNodePermission.check(
			getPermissionChecker(), nodeId, ActionKeys.ADD_PAGE);

		return wikiPageLocalService.addPage(getUserId(), nodeId, title);
	}

	public void deletePage(long nodeId, String title)
		throws PortalException, SystemException {

		WikiPagePermission.check(
			getPermissionChecker(), nodeId, title, ActionKeys.DELETE);

		wikiPageLocalService.deletePage(nodeId, title);
	}

	public WikiPage getPage(long nodeId, String title)
		throws PortalException, SystemException {

		WikiPagePermission.check(
			getPermissionChecker(), nodeId, title, ActionKeys.VIEW);

		return wikiPageLocalService.getPage(nodeId, title);
	}

	public WikiPage getPage(long nodeId, String title, double version)
		throws PortalException, SystemException {

		WikiPagePermission.check(
			getPermissionChecker(), nodeId, title, ActionKeys.VIEW);

		return wikiPageLocalService.getPage(nodeId, title, version);
	}

	public WikiPage revertPage(long nodeId, String title, double version)
		throws PortalException, SystemException {

		WikiPagePermission.check(
			getPermissionChecker(), nodeId, title, ActionKeys.UPDATE);

		return wikiPageLocalService.revertPage(
			getUserId(), nodeId, title, version);
	}

	public WikiPage updatePage(
			long nodeId, String title, String content, String format,
			String[] tagsEntries)
		throws PortalException, SystemException {

		WikiPagePermission.check(
			getPermissionChecker(), nodeId, title, ActionKeys.UPDATE);

		return wikiPageLocalService.updatePage(
			getUserId(), nodeId, title, content, format, tagsEntries);
	}

}