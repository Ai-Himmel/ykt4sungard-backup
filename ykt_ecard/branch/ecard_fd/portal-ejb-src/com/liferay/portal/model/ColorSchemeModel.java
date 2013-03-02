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
 * <a href="ColorSchemeModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.182 $
 *
 */
public class ColorSchemeModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portal.model.ColorScheme"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portal.model.ColorScheme"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.ColorScheme"), XSS_ALLOW);
	public static boolean XSS_ALLOW_COLORSCHEMEID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.ColorScheme.colorSchemeId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SETTINGS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.ColorScheme.settings"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.ColorSchemeModel"));

	public ColorSchemeModel() {
	}

	public ColorSchemeModel(String colorSchemeId) {
		_colorSchemeId = colorSchemeId;
		setNew(true);
	}

	public ColorSchemeModel(String colorSchemeId, String settings) {
		_colorSchemeId = colorSchemeId;
		_settings = settings;
	}

	public String getPrimaryKey() {
		return _colorSchemeId;
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

	public String getSettings() {
		return _settings;
	}

	public void setSettings(String settings) {
		if (((settings == null) && (_settings != null)) ||
				((settings != null) && (_settings == null)) ||
				((settings != null) && (_settings != null) &&
				!settings.equals(_settings))) {
			if (!XSS_ALLOW_SETTINGS) {
				settings = Xss.strip(settings);
			}

			_settings = settings;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ColorScheme(getColorSchemeId(), getSettings());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ColorScheme colorScheme = (ColorScheme)obj;
		String pk = colorScheme.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ColorScheme colorScheme = null;

		try {
			colorScheme = (ColorScheme)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = colorScheme.getPrimaryKey();

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

	private String _colorSchemeId;
	private String _settings;
}