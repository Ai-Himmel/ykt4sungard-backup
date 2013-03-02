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

package com.liferay.portlet.shopping.model;

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="ShoppingCategoryModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.72 $
 *
 */
public class ShoppingCategoryModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingCategory"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingCategory"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCategory"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_CATEGORYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCategory.categoryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCategory.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PARENTCATEGORYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCategory.parentCategoryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingCategory.name"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingCategoryModel"));

	public ShoppingCategoryModel() {
	}

	public ShoppingCategoryModel(String categoryId) {
		_categoryId = categoryId;
		setNew(true);
	}

	public ShoppingCategoryModel(String categoryId, String companyId,
		Date createDate, Date modifiedDate, String parentCategoryId, String name) {
		_categoryId = categoryId;
		_companyId = companyId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_parentCategoryId = parentCategoryId;
		_name = name;
	}

	public String getPrimaryKey() {
		return _categoryId;
	}

	public String getCategoryId() {
		return _categoryId;
	}

	public void setCategoryId(String categoryId) {
		if (((categoryId == null) && (_categoryId != null)) ||
				((categoryId != null) && (_categoryId == null)) ||
				((categoryId != null) && (_categoryId != null) &&
				!categoryId.equals(_categoryId))) {
			if (!XSS_ALLOW_CATEGORYID) {
				categoryId = Xss.strip(categoryId);
			}

			_categoryId = categoryId;
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

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
			setModified(true);
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
			setModified(true);
		}
	}

	public String getParentCategoryId() {
		return _parentCategoryId;
	}

	public void setParentCategoryId(String parentCategoryId) {
		if (((parentCategoryId == null) && (_parentCategoryId != null)) ||
				((parentCategoryId != null) && (_parentCategoryId == null)) ||
				((parentCategoryId != null) && (_parentCategoryId != null) &&
				!parentCategoryId.equals(_parentCategoryId))) {
			if (!XSS_ALLOW_PARENTCATEGORYID) {
				parentCategoryId = Xss.strip(parentCategoryId);
			}

			_parentCategoryId = parentCategoryId;
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

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingCategory(getCategoryId(), getCompanyId(),
			getCreateDate(), getModifiedDate(), getParentCategoryId(), getName());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingCategory shoppingCategory = (ShoppingCategory)obj;
		int value = 0;
		value = getParentCategoryId().compareTo(shoppingCategory.getParentCategoryId());

		if (value != 0) {
			return value;
		}

		value = getName().toLowerCase().compareTo(shoppingCategory.getName()
																  .toLowerCase());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingCategory shoppingCategory = null;

		try {
			shoppingCategory = (ShoppingCategory)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingCategory.getPrimaryKey();

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

	private String _categoryId;
	private String _companyId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _parentCategoryId;
	private String _name;
}