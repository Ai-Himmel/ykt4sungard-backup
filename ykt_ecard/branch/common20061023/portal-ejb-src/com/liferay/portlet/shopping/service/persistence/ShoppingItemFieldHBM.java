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

package com.liferay.portlet.shopping.service.persistence;

/**
 * <a href="ShoppingItemFieldHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemFieldHBM {
	protected ShoppingItemFieldHBM() {
	}

	protected ShoppingItemFieldHBM(String itemFieldId) {
		_itemFieldId = itemFieldId;
	}

	protected ShoppingItemFieldHBM(String itemFieldId, String itemId,
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

	protected void setPrimaryKey(String pk) {
		_itemFieldId = pk;
	}

	protected String getItemFieldId() {
		return _itemFieldId;
	}

	protected void setItemFieldId(String itemFieldId) {
		_itemFieldId = itemFieldId;
	}

	protected String getItemId() {
		return _itemId;
	}

	protected void setItemId(String itemId) {
		_itemId = itemId;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getValues() {
		return _values;
	}

	protected void setValues(String values) {
		_values = values;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	private String _itemFieldId;
	private String _itemId;
	private String _name;
	private String _values;
	private String _description;
}