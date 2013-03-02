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

/**
 * <a href="ShoppingItemFieldModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.14 $
 *
 */
public class ShoppingItemFieldModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingItemField"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingItemField"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemField"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ITEMFIELDID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemField.itemFieldId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ITEMID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemField.itemId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemField.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_VALUES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemField.values"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItemField.description"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingItemFieldModel"));

	public ShoppingItemFieldModel() {
	}

	public ShoppingItemFieldModel(String itemFieldId) {
		_itemFieldId = itemFieldId;
		setNew(true);
	}

	public ShoppingItemFieldModel(String itemFieldId, String itemId,
		String name, String values, String description) {
		_itemFieldId = itemFieldId;
		_itemId = itemId;
		_name = name;
		_values = values;
		_description = description;
	}

	public String getPrimaryKey() {
		return _itemFieldId;
	}

	public String getItemFieldId() {
		return _itemFieldId;
	}

	public void setItemFieldId(String itemFieldId) {
		if (((itemFieldId == null) && (_itemFieldId != null)) ||
				((itemFieldId != null) && (_itemFieldId == null)) ||
				((itemFieldId != null) && (_itemFieldId != null) &&
				!itemFieldId.equals(_itemFieldId))) {
			if (!XSS_ALLOW_ITEMFIELDID) {
				itemFieldId = Xss.strip(itemFieldId);
			}

			_itemFieldId = itemFieldId;
			setModified(true);
		}
	}

	public String getItemId() {
		return _itemId;
	}

	public void setItemId(String itemId) {
		if (((itemId == null) && (_itemId != null)) ||
				((itemId != null) && (_itemId == null)) ||
				((itemId != null) && (_itemId != null) &&
				!itemId.equals(_itemId))) {
			if (!XSS_ALLOW_ITEMID) {
				itemId = Xss.strip(itemId);
			}

			_itemId = itemId;
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

	public String getValues() {
		return _values;
	}

	public void setValues(String values) {
		if (((values == null) && (_values != null)) ||
				((values != null) && (_values == null)) ||
				((values != null) && (_values != null) &&
				!values.equals(_values))) {
			if (!XSS_ALLOW_VALUES) {
				values = Xss.strip(values);
			}

			_values = values;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingItemField(getItemFieldId(), getItemId(), getName(),
			getValues(), getDescription());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingItemField shoppingItemField = (ShoppingItemField)obj;
		int value = 0;
		value = getItemId().compareTo(shoppingItemField.getItemId());

		if (value != 0) {
			return value;
		}

		value = getName().toLowerCase().compareTo(shoppingItemField.getName()
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

		ShoppingItemField shoppingItemField = null;

		try {
			shoppingItemField = (ShoppingItemField)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingItemField.getPrimaryKey();

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

	private String _itemFieldId;
	private String _itemId;
	private String _name;
	private String _values;
	private String _description;
}