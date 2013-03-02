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
import com.liferay.portal.service.persistence.PropertiesPK;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

/**
 * <a href="PropertiesModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class PropertiesModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portal.model.Properties"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portal.model.Properties"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Properties"), XSS_ALLOW);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Properties.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_TYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Properties.type"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PROPERTIES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portal.model.Properties.properties"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portal.model.PropertiesModel"));

	public PropertiesModel() {
	}

	public PropertiesModel(PropertiesPK pk) {
		_companyId = pk.companyId;
		_type = pk.type;
		setNew(true);
	}

	public PropertiesModel(String companyId, String type, String properties) {
		_companyId = companyId;
		_type = type;
		_properties = properties;
	}

	public PropertiesPK getPrimaryKey() {
		return new PropertiesPK(_companyId, _type);
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

	public String getProperties() {
		return _properties;
	}

	public void setProperties(String properties) {
		if (((properties == null) && (_properties != null)) ||
				((properties != null) && (_properties == null)) ||
				((properties != null) && (_properties != null) &&
				!properties.equals(_properties))) {
			if (!XSS_ALLOW_PROPERTIES) {
				properties = Xss.strip(properties);
			}

			_properties = properties;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new Properties(getCompanyId(), getType(), getProperties());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		Properties properties = (Properties)obj;
		PropertiesPK pk = properties.getPrimaryKey();

		return getPrimaryKey().compareTo(pk);
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		Properties properties = null;

		try {
			properties = (Properties)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		PropertiesPK pk = properties.getPrimaryKey();

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

	private String _companyId;
	private String _type;
	private String _properties;
}