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

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

/**
 * <a href="GroupModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.96 $
 *
 */
public class GroupModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portal.model.Group"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portal.model.Group"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group"), XSS_ALLOW);
	public static boolean XSS_ALLOW_GROUPID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.groupId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PARENTGROUPID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.parentGroupId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FRIENDLYURL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.friendlyURL"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_THEMEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.themeId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COLORSCHEMEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Group.colorSchemeId"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.GroupModel"));

	public GroupModel() {
	}

	public GroupModel(String groupId) {
		_groupId = groupId;
		setNew(true);
	}

	public GroupModel(String groupId, String companyId, String parentGroupId,
		String name, String friendlyURL, String themeId, String colorSchemeId) {
		_groupId = groupId;
		_companyId = companyId;
		_parentGroupId = parentGroupId;
		_name = name;
		_friendlyURL = friendlyURL;
		_themeId = themeId;
		_colorSchemeId = colorSchemeId;
	}

	public String getPrimaryKey() {
		return _groupId;
	}

	public String getGroupId() {
		return _groupId;
	}

	public void setGroupId(String groupId) {
		if (((groupId == null) && (_groupId != null)) ||
				((groupId != null) && (_groupId == null)) ||
				((groupId != null) && (_groupId != null) &&
				!groupId.equals(_groupId))) {
			if (!XSS_ALLOW_GROUPID) {
				groupId = Xss.strip(groupId);
			}

			_groupId = groupId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
		}
	}

	public String getParentGroupId() {
		return _parentGroupId;
	}

	public void setParentGroupId(String parentGroupId) {
		if (((parentGroupId == null) && (_parentGroupId != null)) ||
				((parentGroupId != null) && (_parentGroupId == null)) ||
				((parentGroupId != null) && (_parentGroupId != null) &&
				!parentGroupId.equals(_parentGroupId))) {
			if (!XSS_ALLOW_PARENTGROUPID) {
				parentGroupId = Xss.strip(parentGroupId);
			}

			_parentGroupId = parentGroupId;
			setModified(true);
		}
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			if (!XSS_ALLOW_NAME) {
				name = Xss.strip(name);
			}

			_name = name;
			setModified(true);
		}
	}

	public String getFriendlyURL() {
		return _friendlyURL;
	}

	public void setFriendlyURL(String friendlyURL) {
		if (((friendlyURL == null) && (_friendlyURL != null)) ||
				((friendlyURL != null) && (_friendlyURL == null)) ||
				((friendlyURL != null) && (_friendlyURL != null) &&
				!friendlyURL.equals(_friendlyURL))) {
			if (!XSS_ALLOW_FRIENDLYURL) {
				friendlyURL = Xss.strip(friendlyURL);
			}

			_friendlyURL = friendlyURL;
			setModified(true);
		}
	}

	public String getThemeId() {
		return _themeId;
	}

	public void setThemeId(String themeId) {
		if (((themeId == null) && (_themeId != null)) ||
				((themeId != null) && (_themeId == null)) ||
				((themeId != null) && (_themeId != null) &&
				!themeId.equals(_themeId))) {
			if (!XSS_ALLOW_THEMEID) {
				themeId = Xss.strip(themeId);
			}

			_themeId = themeId;
			setModified(true);
		}
	}

	public String getColorSchemeId() {
		return _colorSchemeId;
	}

	public void setColorSchemeId(String colorSchemeId) {
		if (((colorSchemeId == null) && (_colorSchemeId != null)) ||
				((colorSchemeId != null) && (_colorSchemeId == null)) ||
				((colorSchemeId != null) && (_colorSchemeId != null) &&
				!colorSchemeId.equals(_colorSchemeId))) {
			if (!XSS_ALLOW_COLORSCHEMEID) {
				colorSchemeId = Xss.strip(colorSchemeId);
			}

			_colorSchemeId = colorSchemeId;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new Group(getGroupId(), getCompanyId(), getParentGroupId(),
			getName(), getFriendlyURL(), getThemeId(), getColorSchemeId());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		Group group = (Group)obj;
		int value = 0;
		value = getName().toLowerCase().compareTo(group.getName().toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		Group group = null;

		try {
			group = (Group)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = group.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
	}

	private String _groupId;
	private String _companyId;
	private String _parentGroupId;
	private String _name;
	private String _friendlyURL;
	private String _themeId;
	private String _colorSchemeId;
}