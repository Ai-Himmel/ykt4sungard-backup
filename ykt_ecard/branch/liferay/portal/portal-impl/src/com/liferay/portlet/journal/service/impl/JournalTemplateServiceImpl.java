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

package com.liferay.portlet.journal.service.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.base.JournalTemplateServiceBaseImpl;
import com.liferay.portlet.journal.service.permission.JournalTemplatePermission;

import java.io.File;

/**
 * <a href="JournalTemplateServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalTemplateServiceImpl extends JournalTemplateServiceBaseImpl {

	public JournalTemplate addTemplate(
			String templateId, boolean autoTemplateId, long plid,
			String structureId, String name, String description, String xsl,
			boolean formatXsl, String langType, boolean cacheable,
			boolean smallImage, String smallImageURL, File smallFile,
			boolean addCommunityPermissions, boolean addGuestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.JOURNAL,
			ActionKeys.ADD_TEMPLATE);

		return journalTemplateLocalService.addTemplate(
			getUserId(), templateId, autoTemplateId, plid, structureId, name,
			description, xsl, formatXsl, langType, cacheable, smallImage,
			smallImageURL, smallFile, addCommunityPermissions,
			addGuestPermissions);
	}

	public JournalTemplate addTemplate(
			String templateId, boolean autoTemplateId, long plid,
			String structureId, String name, String description, String xsl,
			boolean formatXsl, String langType, boolean cacheable,
			boolean smallImage, String smallImageURL, File smallFile,
			String[] communityPermissions, String[] guestPermissions)
		throws PortalException, SystemException {

		PortletPermissionUtil.check(
			getPermissionChecker(), plid, PortletKeys.JOURNAL,
			ActionKeys.ADD_TEMPLATE);

		return journalTemplateLocalService.addTemplate(
			getUserId(), templateId, autoTemplateId, plid, structureId, name,
			description, xsl, formatXsl, langType, cacheable, smallImage,
			smallImageURL, smallFile, communityPermissions, guestPermissions);
	}

	public void deleteTemplate(long groupId, String templateId)
		throws PortalException, SystemException {

		JournalTemplatePermission.check(
			getPermissionChecker(), groupId, templateId, ActionKeys.DELETE);

		journalTemplateLocalService.deleteTemplate(groupId, templateId);
	}

	public JournalTemplate getTemplate(long groupId, String templateId)
		throws PortalException, SystemException {

		JournalTemplatePermission.check(
			getPermissionChecker(), groupId, templateId, ActionKeys.VIEW);

		return journalTemplateLocalService.getTemplate(groupId, templateId);
	}

	public JournalTemplate updateTemplate(
			long groupId, String templateId, String structureId, String name,
			String description, String xsl, boolean formatXsl, String langType,
			boolean cacheable, boolean smallImage, String smallImageURL,
			File smallFile)
		throws PortalException, SystemException {

		JournalTemplatePermission.check(
			getPermissionChecker(), groupId, templateId, ActionKeys.UPDATE);

		return journalTemplateLocalService.updateTemplate(
			groupId, templateId, structureId, name, description, xsl, formatXsl,
			langType, cacheable, smallImage, smallImageURL, smallFile);
	}

}