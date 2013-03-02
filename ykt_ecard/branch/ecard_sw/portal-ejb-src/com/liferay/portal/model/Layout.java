/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

package com.liferay.portal.model;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.LayoutServiceUtil;
import com.liferay.portal.service.spring.RoleLocalServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.NullSafeProperties;
import com.liferay.util.PropertiesUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;

import java.io.IOException;

import java.util.List;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="Layout.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.36 $
 *
 */
public class Layout extends LayoutModel {

	public static final String GROUP = "group.";

	public static final String DEFAULT_LAYOUT_ID = "1";

	public static final String DEFAULT_PARENT_LAYOUT_ID = "-1";

	public static final String[] TYPES =
		PropsUtil.getArray(PropsUtil.LAYOUT_TYPES);

	public static final String TYPE_PORTLET = "portlet";

	public static final String TYPE_URL = "url";

	public static final String TYPE_EMBEDDED = "embedded";

	public static String getGroupId(String layoutId) {
		if (layoutId == null) {
			return null;
		}

		int pos = layoutId.indexOf(StringPool.PERIOD);

		if (pos == -1) {
			return null;
		}
		else {
			return layoutId.substring(0, pos);
		}
	}

	public static boolean isGroup(String layoutId) {
		if ((layoutId == null) ||
			(layoutId.indexOf(StringPool.PERIOD) == - 1)) {

			return false;
		}
		else {
			return true;
		}
	}

	public Layout() {
		super();
	}

	public Layout(LayoutPK pk) {
		super(pk);

		setUserId(pk.userId);
	}

	public Layout(String layoutId, String userId, String companyId,
				  String parentLayoutId, String name, String type,
				  String typeSettings, String friendlyURL, int priority) {

		super(layoutId, userId, companyId, parentLayoutId, name, type,
			  typeSettings, friendlyURL, priority);

		setUserId(userId);
		setTypeSettings(typeSettings);
	}

	public void setUserId(String userId) {
		if (userId.indexOf(GROUP) != -1) {
			_group = true;
			_groupId = StringUtil.replace(userId, GROUP, StringPool.BLANK);
		}
		else {
			_group = false;
		}

		super.setUserId(userId);
	}

	public String getGroupId() {
		return _groupId;
	}

	public boolean isGroup() {
		return _group;
	}

	public String getAncestorLayoutId()
		throws PortalException, SystemException {

		// Perhaps we can cache this value because layouts cannot be moved from
		// one parent to another

		String ancestorLayoutId = StringPool.BLANK;

		Layout ancestorLayout = this;

		while (true) {
			if (!ancestorLayout.getParentLayoutId().equals(
					Layout.DEFAULT_PARENT_LAYOUT_ID)) {

				ancestorLayout = LayoutServiceUtil.getLayout(new LayoutPK(
					ancestorLayout.getParentLayoutId(),
					ancestorLayout.getUserId()));
			}
			else {
				ancestorLayoutId = ancestorLayout.getLayoutId();

				break;
			}
		}

		return ancestorLayoutId;
	}

	public List getChildren() throws PortalException, SystemException {
		if (_group) {
			return GroupLocalServiceUtil.getLayouts(getGroupId(), getLayoutId());
		}
		else {
			return UserLocalServiceUtil.getLayouts(getUserId(), getLayoutId());
		}
	}

	public LayoutType getLayoutType() {

		// Refactor this to a factory implementation that can be set in
		// portal.properties

		/*String type = getType();

		if (type.equals(TYPE_PORTLET)) {
			return new LayoutTypePortlet(this);
		}
		else if (type.equals(TYPE_URL)) {
			return new LayoutTypeURL(this);
		}*/

		return new LayoutTypePortlet(this);
	}

	public String getTypeSettings() {
		return PropertiesUtil.toString(_typeSettingsProperties);
	}

	public void setTypeSettings(String typeSettings) {
		_typeSettingsProperties.clear();

		try {
			PropertiesUtil.load(_typeSettingsProperties, typeSettings);
		}
		catch (IOException ioe) {
			_log.error(ioe);
		}

		super.setTypeSettings(typeSettings);
	}

	public Properties getTypeSettingsProperties() {
		return _typeSettingsProperties;
	}

	public void setTypeSettingsProperties(Properties typeSettingsProperties) {
		_typeSettingsProperties = typeSettingsProperties;
	}

	public boolean isContentModifiable(String userId) {
		if (isGroup()) {
			try {
				if (RoleLocalServiceUtil.isAdministrator(userId)) {
					return true;
				}
			}
			catch (Exception e) {
			}

			return false;
		}
		else {
			if (User.isLayoutsRequired(userId)) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	public boolean isThemeModifiable(String userId) {
		boolean themeModifiable = GetterUtil.getBoolean(
			PropsUtil.get(PropsUtil.LOOK_AND_FEEL_MODIFIABLE));

		if (!themeModifiable) {
			return false;
		}

		if (isGroup()) {
			try {
				if (RoleLocalServiceUtil.isAdministrator(userId)) {
					return true;
				}
			}
			catch (Exception e) {
			}

			return false;
		}
		else {
			return true;
		}
	}

	private static final Log _log = LogFactory.getLog(Layout.class);

	private String _groupId;
	private boolean _group;
	private Properties _typeSettingsProperties = new NullSafeProperties();

}