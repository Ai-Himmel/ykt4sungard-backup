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
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutReference;
import com.liferay.portal.model.impl.ThemeImpl;
import com.liferay.portal.service.base.LayoutServiceBaseImpl;
import com.liferay.portal.service.permission.GroupPermissionUtil;
import com.liferay.portal.service.permission.LayoutPermissionUtil;

import java.io.File;
import java.io.InputStream;

import java.util.HashMap;
import java.util.Locale;
import java.util.Map;

/**
 * <a href="LayoutServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutServiceImpl extends LayoutServiceBaseImpl {

	public Layout addLayout(
			long groupId, boolean privateLayout, long parentLayoutId,
			String name, String title, String description, String type,
			boolean hidden, String friendlyURL)
		throws PortalException, SystemException {

		Map localeNamesMap = new HashMap();

		Locale defaultLocale = LocaleUtil.getDefault();

		localeNamesMap.put(defaultLocale, name);

		return addLayout(
			groupId, privateLayout, parentLayoutId, localeNamesMap,
			new HashMap(), description, type, hidden, friendlyURL);
	}

	public Layout addLayout(
			long groupId, boolean privateLayout, long parentLayoutId,
			Map localeNamesMap, Map localeTitlesMap, String description,
			String type, boolean hidden, String friendlyURL)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.MANAGE_LAYOUTS);

		return layoutLocalService.addLayout(
			getUserId(), groupId, privateLayout, parentLayoutId, localeNamesMap,
			localeTitlesMap, description, type, hidden, friendlyURL);
	}

	public void deleteLayout(long plid)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), plid, ActionKeys.DELETE);

		layoutLocalService.deleteLayout(plid);
	}

	public void deleteLayout(long groupId, boolean privateLayout, long layoutId)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.DELETE);

		layoutLocalService.deleteLayout(groupId, privateLayout, layoutId);
	}

	public String getLayoutName(
			long groupId, boolean privateLayout, long layoutId,
			String languageId)
		throws PortalException, SystemException {

		Layout layout = layoutLocalService.getLayout(
			groupId, privateLayout, layoutId);

		return layout.getName(languageId);
	}

	public LayoutReference[] getLayoutReferences(
			long companyId, String portletId, String prefsKey,
			String prefsValue)
		throws SystemException {

		return layoutLocalService.getLayouts(
			companyId, portletId, prefsKey, prefsValue);
	}

	public byte[] exportLayouts(
			long groupId, boolean privateLayout, Map parameterMap)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.MANAGE_LAYOUTS);

		return layoutLocalService.exportLayouts(
			groupId, privateLayout, parameterMap);
	}

	public byte[] exportLayouts(
			long groupId, boolean privateLayout, long[] layoutIds,
			Map parameterMap)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.MANAGE_LAYOUTS);

		return layoutLocalService.exportLayouts(
			groupId, privateLayout, layoutIds, parameterMap);
	}

	public byte[] exportPortletInfo(
			long plid, String portletId, Map parameterMap)
		throws PortalException, SystemException {

		Layout layout = layoutLocalService.getLayout(plid);

		GroupPermissionUtil.check(
			getPermissionChecker(), layout.getGroupId(),
			ActionKeys.MANAGE_LAYOUTS);

		return layoutLocalService.exportPortletInfo(
			plid, portletId, parameterMap);
	}

	public void importLayouts(
			long groupId, boolean privateLayout, Map parameterMap, File file)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.MANAGE_LAYOUTS);

		layoutLocalService.importLayouts(
			getUserId(), groupId, privateLayout, parameterMap, file);
	}

	public void importLayouts(
			long groupId, boolean privateLayout, Map parameterMap,
			InputStream is)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.MANAGE_LAYOUTS);

		layoutLocalService.importLayouts(
			getUserId(), groupId, privateLayout, parameterMap, is);
	}

	public void importPortletInfo(
			long plid, String portletId, Map parameterMap, File file)
		throws PortalException, SystemException {

		Layout layout = layoutLocalService.getLayout(plid);

		GroupPermissionUtil.check(
			getPermissionChecker(), layout.getGroupId(),
			ActionKeys.MANAGE_LAYOUTS);

		layoutLocalService.importPortletInfo(
			getUserId(), plid, portletId, parameterMap, file);
	}

	public void importPortletInfo(
			long plid, String portletId, Map parameterMap, InputStream is)
		throws PortalException, SystemException {

		Layout layout = layoutLocalService.getLayout(plid);

		GroupPermissionUtil.check(
			getPermissionChecker(), layout.getGroupId(),
			ActionKeys.MANAGE_LAYOUTS);

		layoutLocalService.importPortletInfo(
			getUserId(), plid, portletId, parameterMap, is);
	}

	public void setLayouts(
			long groupId, boolean privateLayout, long parentLayoutId,
			long[] layoutIds)
		throws PortalException, SystemException {

		GroupPermissionUtil.check(
			getPermissionChecker(), groupId, ActionKeys.MANAGE_LAYOUTS);

		layoutLocalService.setLayouts(
			groupId, privateLayout, parentLayoutId, layoutIds);
	}

	public Layout updateLayout(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId, Map localeNamesMap, Map localeTitlesMap,
			String description, String type, boolean hidden, String friendlyURL)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		return layoutLocalService.updateLayout(
			groupId, privateLayout, layoutId, parentLayoutId, localeNamesMap,
			localeTitlesMap, description, type, hidden, friendlyURL);
	}

	public Layout updateLayout(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId, Map localeNamesMap, Map localeTitlesMap,
			String description, String type, boolean hidden, String friendlyURL,
			Boolean iconImage, byte[] iconBytes)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		return layoutLocalService.updateLayout(
			groupId, privateLayout, layoutId, parentLayoutId, localeNamesMap,
			localeTitlesMap, description, type, hidden, friendlyURL, iconImage,
			iconBytes);
	}

	public Layout updateLayout(
			long groupId, boolean privateLayout, long layoutId,
			String typeSettings)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		return layoutLocalService.updateLayout(
			groupId, privateLayout, layoutId, typeSettings);
	}

	public Layout updateLookAndFeel(
			long groupId, boolean privateLayout, long layoutId, String themeId,
			String colorSchemeId, String css, boolean wapTheme)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		pluginSettingLocalService.checkPermission(
			getUserId(), themeId, ThemeImpl.PLUGIN_TYPE);

		return layoutLocalService.updateLookAndFeel(
			groupId, privateLayout, layoutId, themeId, colorSchemeId, css,
			wapTheme);
	}

	public Layout updateName(long plid, String name, String languageId)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), plid, ActionKeys.UPDATE);

		return layoutLocalService.updateName(plid, name, languageId);
	}

	public Layout updateName(
			long groupId, boolean privateLayout, long layoutId, String name,
			String languageId)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		return layoutLocalService.updateName(
			groupId, privateLayout, layoutId, name, languageId);
	}

	public Layout updateParentLayoutId(long plid, long parentPlid)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), plid, ActionKeys.UPDATE);

		return layoutLocalService.updateParentLayoutId(plid, parentPlid);
	}

	public Layout updateParentLayoutId(
			long groupId, boolean privateLayout, long layoutId,
			long parentLayoutId)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		return layoutLocalService.updateParentLayoutId(
			groupId, privateLayout, layoutId, parentLayoutId);
	}

	public Layout updatePriority(long plid, int priority)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), plid, ActionKeys.UPDATE);

		return layoutLocalService.updatePriority(plid, priority);
	}

	public Layout updatePriority(
			long groupId, boolean privateLayout, long layoutId, int priority)
		throws PortalException, SystemException {

		LayoutPermissionUtil.check(
			getPermissionChecker(), groupId, privateLayout, layoutId,
			ActionKeys.UPDATE);

		return layoutLocalService.updatePriority(
			groupId, privateLayout, layoutId, priority);
	}

}