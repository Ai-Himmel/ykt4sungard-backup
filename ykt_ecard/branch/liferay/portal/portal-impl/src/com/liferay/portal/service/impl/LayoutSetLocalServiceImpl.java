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

import com.liferay.portal.LayoutSetVirtualHostException;
import com.liferay.portal.NoSuchCompanyException;
import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.NoSuchLayoutSetException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.model.impl.ColorSchemeImpl;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.model.impl.ThemeImpl;
import com.liferay.portal.service.base.LayoutSetLocalServiceBaseImpl;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.util.Http;

import java.io.File;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="LayoutSetLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LayoutSetLocalServiceImpl extends LayoutSetLocalServiceBaseImpl {

	public LayoutSet addLayoutSet(long groupId, boolean privateLayout)
		throws PortalException, SystemException {

		Group group = groupPersistence.findByPrimaryKey(groupId);

		long layoutSetId = counterLocalService.increment();

		LayoutSet layoutSet = layoutSetPersistence.create(layoutSetId);

		layoutSet.setGroupId(groupId);
		layoutSet.setCompanyId(group.getCompanyId());
		layoutSet.setPrivateLayout(privateLayout);
		layoutSet.setThemeId(ThemeImpl.getDefaultRegularThemeId());
		layoutSet.setColorSchemeId(
			ColorSchemeImpl.getDefaultRegularColorSchemeId());
		layoutSet.setWapThemeId(ThemeImpl.getDefaultWapThemeId());
		layoutSet.setWapColorSchemeId(
			ColorSchemeImpl.getDefaultWapColorSchemeId());
		layoutSet.setCss(StringPool.BLANK);

		layoutSetPersistence.update(layoutSet);

		return layoutSet;
	}

	public void deleteLayoutSet(long groupId, boolean privateLayout)
		throws PortalException, SystemException {

		LayoutSet layoutSet = layoutSetPersistence.findByG_P(
			groupId, privateLayout);

		// Layouts

		List layouts = layoutPersistence.findByG_P_P(
			groupId, privateLayout, LayoutImpl.DEFAULT_PARENT_LAYOUT_ID);

		Iterator itr = layouts.iterator();

		while (itr.hasNext()) {
			Layout layout = (Layout) itr.next();

			try {
				layoutLocalService.deleteLayout(layout, false);
			}
			catch (NoSuchLayoutException nsle) {
			}
		}

		// Logo

		ImageLocalUtil.deleteImage(layoutSet.getLogoId());

		// Layout set

		layoutSetPersistence.removeByG_P(groupId, privateLayout);
	}

	public LayoutSet getLayoutSet(long groupId, boolean privateLayout)
		throws PortalException, SystemException {

		return layoutSetPersistence.findByG_P(groupId, privateLayout);
	}

	public LayoutSet getLayoutSet(String virtualHost)
		throws PortalException, SystemException {

		virtualHost = virtualHost.trim().toLowerCase();

		return layoutSetPersistence.findByVirtualHost(virtualHost);
	}

	public void updateLogo(
			long groupId, boolean privateLayout, boolean logo, File file)
		throws PortalException, SystemException {

		LayoutSet layoutSet = layoutSetPersistence.findByG_P(
			groupId, privateLayout);

		layoutSet.setLogo(logo);

		if (logo) {
			long logoId = layoutSet.getLogoId();

			if (logoId <= 0) {
				logoId = counterLocalService.increment();

				layoutSet.setLogoId(logoId);
			}
		}

		layoutSetPersistence.update(layoutSet);

		if (logo) {
			ImageLocalUtil.updateImage(layoutSet.getLogoId(), file);
		}
		else {
			ImageLocalUtil.deleteImage(layoutSet.getLogoId());
		}
	}

	public LayoutSet updateLookAndFeel(
			long groupId, boolean privateLayout, String themeId,
			String colorSchemeId, String css, boolean wapTheme)
		throws PortalException, SystemException {

		LayoutSet layoutSet = layoutSetPersistence.findByG_P(
			groupId, privateLayout);

		if (wapTheme) {
			layoutSet.setWapThemeId(themeId);
			layoutSet.setWapColorSchemeId(colorSchemeId);
		}
		else {
			layoutSet.setThemeId(themeId);
			layoutSet.setColorSchemeId(colorSchemeId);
			layoutSet.setCss(css);
		}

		layoutSetPersistence.update(layoutSet);

		if (PrefsPropsUtil.getBoolean(
				PropsUtil.THEME_SYNC_ON_GROUP,
				PropsValues.THEME_SYNC_ON_GROUP)) {

			LayoutSet otherLayoutSet = layoutSetPersistence.findByG_P(
				layoutSet.getGroupId(), layoutSet.isPrivateLayout());

			if (wapTheme) {
				otherLayoutSet.setWapThemeId(themeId);
				otherLayoutSet.setWapColorSchemeId(colorSchemeId);
			}
			else {
				otherLayoutSet.setThemeId(themeId);
				otherLayoutSet.setColorSchemeId(colorSchemeId);
			}

			layoutSetPersistence.update(otherLayoutSet);
		}

		return layoutSet;
	}

	public LayoutSet updatePageCount(long groupId, boolean privateLayout)
		throws PortalException, SystemException {

		int pageCount = layoutPersistence.countByG_P(groupId, privateLayout);

		LayoutSet layoutSet = layoutSetPersistence.findByG_P(
			groupId, privateLayout);

		layoutSet.setPageCount(pageCount);

		layoutSetPersistence.update(layoutSet);

		return layoutSet;
	}

	public LayoutSet updateVirtualHost(
			long groupId, boolean privateLayout, String virtualHost)
		throws PortalException, SystemException {

		virtualHost = virtualHost.trim().toLowerCase();

		if (virtualHost.startsWith(Http.HTTP_WITH_SLASH) ||
			virtualHost.startsWith(Http.HTTPS_WITH_SLASH)) {

			throw new LayoutSetVirtualHostException();
		}

		LayoutSet layoutSet = layoutSetPersistence.findByG_P(
			groupId, privateLayout);

		if (Validator.isNotNull(virtualHost)) {
			try {
				LayoutSet virtualHostLayoutSet = getLayoutSet(virtualHost);

				if (!layoutSet.equals(virtualHostLayoutSet)) {
					throw new LayoutSetVirtualHostException();
				}
			}
			catch (NoSuchLayoutSetException nslse) {
			}

			try {
				companyLocalService.getCompanyByVirtualHost(virtualHost);

				throw new LayoutSetVirtualHostException();
			}
			catch (NoSuchCompanyException nsce) {
			}
		}

		layoutSet.setVirtualHost(virtualHost);

		layoutSetPersistence.update(layoutSet);

		return layoutSet;
	}

}