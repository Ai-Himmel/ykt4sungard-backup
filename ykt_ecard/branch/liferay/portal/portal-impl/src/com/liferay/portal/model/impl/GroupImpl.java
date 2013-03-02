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

package com.liferay.portal.model.impl;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.NullSafeProperties;
import com.liferay.portal.kernel.util.PropertiesUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutSet;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.User;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.LayoutSetLocalServiceUtil;
import com.liferay.portal.service.OrganizationLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.GroupNames;
import com.liferay.portal.util.PortalUtil;

import java.io.IOException;

import java.util.List;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="GroupImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class GroupImpl extends GroupModelImpl implements Group {

	public static final long DEFAULT_PARENT_GROUP_ID = 0;

	public static final long DEFAULT_LIVE_GROUP_ID = 0;

	public static final String GUEST = GroupNames.GUEST;

	public static final String[] SYSTEM_GROUPS = GroupNames.SYSTEM_GROUPS;

	public static final int TYPE_COMMUNITY_OPEN = 1;

	public static final String TYPE_COMMUNITY_OPEN_LABEL = "open";

	public static final int TYPE_COMMUNITY_PRIVATE = 3;

	public static final String TYPE_COMMUNITY_PRIVATE_LABEL = "private";

	public static final int TYPE_COMMUNITY_RESTRICTED = 2;

	public static final String TYPE_COMMUNITY_RESTRICTED_LABEL = "restricted";

	public static String getTypeLabel(int type) {
		if (type == TYPE_COMMUNITY_OPEN) {
			return TYPE_COMMUNITY_OPEN_LABEL;
		}
		else if (type == TYPE_COMMUNITY_PRIVATE) {
			return TYPE_COMMUNITY_PRIVATE_LABEL;
		}
		else {
			return TYPE_COMMUNITY_RESTRICTED_LABEL;
		}
	}

	public GroupImpl() {
	}

	public boolean isCommunity() {
		long classNameId = getClassNameId();
		long classPK = getClassPK();

		if ((classNameId <= 0) && (classPK <= 0)) {
			return true;
		}
		else {
			return false;
		}
	}

	public boolean isOrganization() {
		long classNameId = getClassNameId();
		long classPK = getClassPK();

		if ((classNameId > 0) && (classPK > 0)) {
			long organizationClassNameId = PortalUtil.getClassNameId(
				Organization.class);

			if (classNameId == organizationClassNameId) {
				return true;
			}
		}

		return false;
	}

	public boolean isUser() {
		long classNameId = getClassNameId();
		long classPK = getClassPK();

		if ((classNameId > 0) && (classPK > 0)) {
			long userClassNameId = PortalUtil.getClassNameId(User.class);

			if (classNameId == userClassNameId) {
				return true;
			}
		}

		return false;
	}

	public Group getLiveGroup() {
		if (!isStagingGroup()) {
			return null;
		}

		try {
			if (_liveGroup == null) {
				_liveGroup = GroupLocalServiceUtil.getGroup(
					getLiveGroupId());
			}

			return _liveGroup;
		}
		catch (Exception e) {
			_log.error("Error getting live group for " + getLiveGroupId(), e);

			return null;
		}
	}

	public Group getStagingGroup() {
		if (isStagingGroup()) {
			return null;
		}

		try {
			if (_stagingGroup == null) {
				_stagingGroup =
					GroupLocalServiceUtil.getStagingGroup(getGroupId());
			}

			return _stagingGroup;
		}
		catch (Exception e) {
			_log.error("Error getting staging group for " + getGroupId(), e);

			return null;
		}
	}

	public boolean hasStagingGroup() {
		if (isStagingGroup()) {
			return false;
		}

		if (_stagingGroup != null) {
			return true;
		}
		else {
			try {
				_stagingGroup =
					GroupLocalServiceUtil.getStagingGroup(getGroupId());

				return true;
			}
			catch (Exception e) {
				return false;
			}
		}
	}

	public boolean isStagingGroup() {
		if (getLiveGroupId() == DEFAULT_LIVE_GROUP_ID) {
			return false;
		}
		else {
			return true;
		}
	}

	public String getDescriptiveName() {
		String name = getName();

		try {
			if (isOrganization()) {
				long organizationId = getClassPK();

				Organization organization =
					OrganizationLocalServiceUtil.getOrganization(
						organizationId);

				name = organization.getName();
			}
			else if (isUser()) {
				long userId = getClassPK();

				User user = UserLocalServiceUtil.getUserById(userId);

				name = user.getFullName();
			}
		}
		catch (Exception e) {
			_log.error("Error getting descriptive name for " + getGroupId(), e);
		}

		return name;
	}

	public String getTypeLabel() {
		return getTypeLabel(getType());
	}

	public String getTypeSettings() {
		if (_typeSettingsProperties == null) {
			return super.getTypeSettings();
		}
		else {
			return PropertiesUtil.toString(_typeSettingsProperties);
		}
	}

	public void setTypeSettings(String typeSettings) {
		_typeSettingsProperties = null;

		super.setTypeSettings(typeSettings);
	}

	public Properties getTypeSettingsProperties() {
		if (_typeSettingsProperties == null) {
			_typeSettingsProperties = new NullSafeProperties();

			try {
				PropertiesUtil.load(
					_typeSettingsProperties, super.getTypeSettings());
			}
			catch (IOException ioe) {
				_log.error(ioe);
			}
		}

		return _typeSettingsProperties;
	}

	public void setTypeSettingsProperties(Properties typeSettingsProperties) {
		_typeSettingsProperties = typeSettingsProperties;

		super.setTypeSettings(PropertiesUtil.toString(_typeSettingsProperties));
	}

	public String getPathFriendlyURL(
		boolean privateLayout, ThemeDisplay themeDisplay) {

		if (privateLayout) {
			if (isUser()) {
				return themeDisplay.getPathFriendlyURLPrivateUser();
			}
			else {
				return themeDisplay.getPathFriendlyURLPrivateGroup();
			}
		}
		else {
			return themeDisplay.getPathFriendlyURLPublic();
		}
	}

	public String getDefaultFriendlyURL(boolean privateLayout)
		throws PortalException, SystemException {

		if (isUser()) {
			long userId = getClassPK();

			User user = UserLocalServiceUtil.getUserById(userId);

			return StringPool.SLASH + user.getScreenName();
		}
		else {
			return StringPool.SLASH + String.valueOf(getGroupId());
		}
	}

	public long getDefaultPrivatePlid() {
		return getDefaultPlid(true);
	}

	public int getPrivateLayoutsPageCount() {
		try {
			LayoutSet layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(
				getGroupId(), true);

			return layoutSet.getPageCount();
		}
		catch (Exception e) {
			_log.error(e);
		}

		return 0;
	}

	public boolean hasPrivateLayouts() {
		if (getPrivateLayoutsPageCount() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public long getDefaultPublicPlid() {
		return getDefaultPlid(false);
	}

	public int getPublicLayoutsPageCount() {
		try {
			LayoutSet layoutSet = LayoutSetLocalServiceUtil.getLayoutSet(
				getGroupId(), false);

			return layoutSet.getPageCount();
		}
		catch (Exception e) {
			_log.error(e);
		}

		return 0;
	}

	public boolean hasPublicLayouts() {
		if (getPublicLayoutsPageCount() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	protected long getDefaultPlid(boolean privateLayout) {
		try {
			List layouts = LayoutLocalServiceUtil.getLayouts(
				getGroupId(), privateLayout,
				LayoutImpl.DEFAULT_PARENT_LAYOUT_ID, 0, 1);

			if (layouts.size() > 0) {
				Layout layout = (Layout)layouts.get(0);

				return layout.getPlid();
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e.getMessage());
			}
		}

		return LayoutImpl.DEFAULT_PLID;
	}

	private static Log _log = LogFactory.getLog(GroupImpl.class);

	private Group _stagingGroup;
	private Group _liveGroup;
	private Properties _typeSettingsProperties = null;

}