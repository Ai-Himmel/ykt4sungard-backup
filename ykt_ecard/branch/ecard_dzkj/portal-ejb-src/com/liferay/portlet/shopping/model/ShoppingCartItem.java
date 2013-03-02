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

import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.io.Serializable;

/**
 * <a href="ShoppingCartItem.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class ShoppingCartItem implements Comparable, Serializable {

	public static String[] getFieldsArray(String fields) {
		return StringUtil.split(fields, "&");
	}

	public ShoppingCartItem() {
		super();
	}

	public ShoppingCartItem(ShoppingItem item, String fields) {
		_item = item;
		_fields = fields;
	}

	public String getCartItemId() {
		String itemId = getItem().getItemId();

		if (Validator.isNull(_fields)) {
			return itemId;
		}
		else {
			return itemId + "|" + _fields;
		}
	}

	public ShoppingItem getItem() {
		return _item;
	}

	public String getFields() {
		return _fields;
	}

	public String[] getFieldsArray() {
		return getFieldsArray(_fields);
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingCartItem cartItem = (ShoppingCartItem)obj;

		int value = getItem().compareTo(cartItem.getItem());

		if (value == 0) {
			value = getFields().compareTo(cartItem.getFields());
		}

		return value;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingCartItem cartItem = (ShoppingCartItem)obj;

		if (getItem().equals(cartItem.getItem()) &&
			getFields().equals(cartItem.getFields())) {

			return true;
		}
		else {
			return false;
		}
	}

	private ShoppingItem _item;
	private String _fields;

}