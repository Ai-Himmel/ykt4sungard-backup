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

package com.liferay.portal.model;

import java.io.Serializable;

/**
 * <a href="PermissionDisplay.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class PermissionDisplay implements Comparable, Serializable {

	public PermissionDisplay(
		Permission permission, Resource resource, String portletName,
		String portletLabel, String modelName, String modelLabel,
		String actionId, String actionLabel) {

		_permission = permission;
		_resource = resource;
		_portletName = portletName;
		_portletLabel = portletLabel;
		_modelName = modelName;
		_modelLabel = modelLabel;
		_actionId = actionId;
		_actionLabel = actionLabel;
	}

	public Permission getPermission() {
		return _permission;
	}

	public Resource getResource() {
		return _resource;
	}

	public String getPortletName() {
		return _portletName;
	}

	public String getPortletLabel() {
		return _portletLabel;
	}

	public String getModelName() {
		return _modelName;
	}

	public String getModelLabel() {
		return _modelLabel;
	}

	public String getActionId() {
		return _actionId;
	}

	public String getActionLabel() {
		return _actionLabel;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		PermissionDisplay permissionDisplay = (PermissionDisplay)obj;

		int value = getPortletLabel().compareTo(
			permissionDisplay.getPortletLabel());

		if (value == 0) {
			value = getModelLabel().compareTo(
				permissionDisplay.getModelLabel());

			if (value == 0) {
				value = getActionLabel().compareTo(
					permissionDisplay.getActionLabel());
			}
		}

		return value;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		if (!(obj instanceof PermissionDisplay)) {
			return false;
		}

		PermissionDisplay permissionDisplay = (PermissionDisplay)obj;

		if (_portletName.equals(permissionDisplay.getPortletName()) &&
			_modelName.equals(permissionDisplay.getModelName()) &&
			_actionId.equals(permissionDisplay.getActionId())) {

			return true;
		}
		else {
			return false;
		}
	}

	private Permission _permission;
	private Resource _resource;
	private String _portletName;
	private String _portletLabel;
	private String _modelName;
	private String _modelLabel;
	private String _actionId;
	private String _actionLabel;

}