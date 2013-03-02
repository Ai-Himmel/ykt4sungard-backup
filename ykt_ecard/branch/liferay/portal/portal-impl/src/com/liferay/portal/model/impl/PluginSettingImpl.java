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

import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.model.User;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PluginSettingImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PluginSettingImpl
	extends PluginSettingModelImpl implements PluginSetting {

	public PluginSettingImpl() {
	}

	public PluginSettingImpl(PluginSetting pluginSetting) {
		setCompanyId(pluginSetting.getCompanyId());
		setPluginId(pluginSetting.getPluginId());
		setPluginType(pluginSetting.getPluginType());
		setRoles(pluginSetting.getRoles());
		setActive(pluginSetting.getActive());
	}

	/**
	 * Adds a role to the list of roles.
	 *
	 * @param		role a role name
	 */
	public void addRole(String role) {
		setRolesArray(ArrayUtil.append(_rolesArray, role));
	}

	/**
	 * Sets a string of ordered comma delimited plugin ids.
	 *
	 * @param		roles a string of ordered comma delimited plugin ids
	 */
	public void setRoles(String roles) {
		_rolesArray = StringUtil.split(roles);

		super.setRoles(roles);
	}

	/**
	 * Gets an array of required roles of the plugin.
	 *
	 * @return		an array of required roles of the plugin
	 */
	public String[] getRolesArray() {
		return _rolesArray;
	}

	/**
	 * Sets an array of required roles of the plugin.
	 *
	 * @param		rolesArray an array of required roles of the plugin
	 */
	public void setRolesArray(String[] rolesArray) {
		_rolesArray = rolesArray;

		super.setRoles(StringUtil.merge(rolesArray));
	}

	/**
	 * Returns true if the plugin has a role with the specified name.
	 *
	 * @return		true if the plugin has a role with the specified name
	 */
	public boolean hasRoleWithName(String roleName) {
		for (int i = 0; i < _rolesArray.length; i++) {
			if (_rolesArray[i].equalsIgnoreCase(roleName)) {
				return true;
			}
		}

		return false;
	}

	/**
	 * Returns true if the user has permission to use this plugin
	 *
	 * @param		userId the id of the user
	 * @return		true if the user has permission to use this plugin
	 */
	public boolean hasPermission(long userId) {
		try {
			if (_rolesArray.length == 0) {
				return true;
			}
			else if (RoleLocalServiceUtil.hasUserRoles(
						userId, getCompanyId(), _rolesArray, true)) {

				return true;
			}
			else if (RoleLocalServiceUtil.hasUserRole(
						userId, getCompanyId(), RoleImpl.ADMINISTRATOR, true)) {

				return true;
			}
			else {
				User user = UserLocalServiceUtil.getUserById(userId);

				if (user.isDefaultUser() && hasRoleWithName(RoleImpl.GUEST)) {
					return true;
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return false;
	}

	/**
	 * Log instance for this class.
	 */
	private static Log _log = LogFactory.getLog(PluginSettingImpl.class);

	/**
	 * An array of required roles of the plugin.
	 */
	private String[] _rolesArray;

}