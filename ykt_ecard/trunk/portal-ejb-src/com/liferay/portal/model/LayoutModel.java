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
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

/**
 * <a href="LayoutModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.95 $
 *
 */
public class LayoutModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portal.model.Layout"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portal.model.Layout"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout"), XSS_ALLOW);
	public static boolean XSS_ALLOW_LAYOUTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.layoutId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PARENTLAYOUTID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.parentLayoutId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.type"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TYPESETTINGS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.typeSettings"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FRIENDLYURL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Layout.friendlyURL"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.LayoutModel"));

	public LayoutModel() {
	}

	public LayoutModel(LayoutPK pk) {
		_layoutId = pk.layoutId;
		_userId = pk.userId;
		setNew(true);
	}

	public LayoutModel(String layoutId, String userId, String companyId,
		String parentLayoutId, String name, String type, String typeSettings,
		String friendlyURL, int priority) {
		_layoutId = layoutId;
		_userId = userId;
		_companyId = companyId;
		_parentLayoutId = parentLayoutId;
		_name = name;
		_type = type;
		_typeSettings = typeSettings;
		_friendlyURL = friendlyURL;
		_priority = priority;
	}

	public LayoutPK getPrimaryKey() {
		return new LayoutPK(_layoutId, _userId);
	}

	public String getLayoutId() {
		return _layoutId;
	}

	public void setLayoutId(String layoutId) {
		if (((layoutId == null) && (_layoutId != null)) ||
				((layoutId != null) && (_layoutId == null)) ||
				((layoutId != null) && (_layoutId != null) &&
				!layoutId.equals(_layoutId))) {
			if (!XSS_ALLOW_LAYOUTID) {
				layoutId = Xss.strip(layoutId);
			}

			_layoutId = layoutId;
			setModified(true);
		}
	}

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
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

	public String getParentLayoutId() {
		return _parentLayoutId;
	}

	public void setParentLayoutId(String parentLayoutId) {
		if (((parentLayoutId == null) && (_parentLayoutId != null)) ||
				((parentLayoutId != null) && (_parentLayoutId == null)) ||
				((parentLayoutId != null) && (_parentLayoutId != null) &&
				!parentLayoutId.equals(_parentLayoutId))) {
			if (!XSS_ALLOW_PARENTLAYOUTID) {
				parentLayoutId = Xss.strip(parentLayoutId);
			}

			_parentLayoutId = parentLayoutId;
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

	public String getType() {
		return _type;
	}

	public void setType(String type) {
		if (((type == null) && (_type != null)) ||
				((type != null) && (_type == null)) ||
				((type != null) && (_type != null) && !type.equals(_type))) {
			if (!XSS_ALLOW_TYPE) {
				type = Xss.strip(type);
			}

			_type = type;
			setModified(true);
		}
	}

	public String getTypeSettings() {
		return _typeSettings;
	}

	public void setTypeSettings(String typeSettings) {
		if (((typeSettings == null) && (_typeSettings != null)) ||
				((typeSettings != null) && (_typeSettings == null)) ||
				((typeSettings != null) && (_typeSettings != null) &&
				!typeSettings.equals(_typeSettings))) {
			if (!XSS_ALLOW_TYPESETTINGS) {
				typeSettings = Xss.strip(typeSettings);
			}

			_typeSettings = typeSettings;
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

	public int getPriority() {
		return _priority;
	}

	public void setPriority(int priority) {
		if (priority != _priority) {
			_priority = priority;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new Layout(getLayoutId(), getUserId(), getCompanyId(),
			getParentLayoutId(), getName(), getType(), getTypeSettings(),
			getFriendlyURL(), getPriority());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		Layout layout = (Layout)obj;
		int value = 0;
		value = getParentLayoutId().compareTo(layout.getParentLayoutId());

		if (value != 0) {
			return value;
		}

		if (getPriority() < layout.getPriority()) {
			value = -1;
		}
		else if (getPriority() > layout.getPriority()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		Layout layout = null;

		try {
			layout = (Layout)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		LayoutPK pk = layout.getPrimaryKey();

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

	private String _layoutId;
	private String _userId;
	private String _companyId;
	private String _parentLayoutId;
	private String _name;
	private String _type;
	private String _typeSettings;
	private String _friendlyURL;
	private int _priority;
}