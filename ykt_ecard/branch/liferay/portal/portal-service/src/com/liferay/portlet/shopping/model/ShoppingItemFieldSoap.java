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

package com.liferay.portlet.shopping.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="ShoppingItemFieldSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.shopping.service.http.ShoppingItemFieldServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.http.ShoppingItemFieldServiceSoap
 *
 */
public class ShoppingItemFieldSoap implements Serializable {
	public static ShoppingItemFieldSoap toSoapModel(ShoppingItemField model) {
		ShoppingItemFieldSoap soapModel = new ShoppingItemFieldSoap();

		soapModel.setItemFieldId(model.getItemFieldId());
		soapModel.setItemId(model.getItemId());
		soapModel.setName(model.getName());
		soapModel.setValues(model.getValues());
		soapModel.setDescription(model.getDescription());

		return soapModel;
	}

	public static ShoppingItemFieldSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			ShoppingItemField model = (ShoppingItemField)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ShoppingItemFieldSoap[])soapModels.toArray(new ShoppingItemFieldSoap[0]);
	}

	public ShoppingItemFieldSoap() {
	}

	public long getPrimaryKey() {
		return _itemFieldId;
	}

	public void setPrimaryKey(long pk) {
		setItemFieldId(pk);
	}

	public long getItemFieldId() {
		return _itemFieldId;
	}

	public void setItemFieldId(long itemFieldId) {
		_itemFieldId = itemFieldId;
	}

	public long getItemId() {
		return _itemId;
	}

	public void setItemId(long itemId) {
		_itemId = itemId;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getValues() {
		return _values;
	}

	public void setValues(String values) {
		_values = values;
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		_description = description;
	}

	private long _itemFieldId;
	private long _itemId;
	private String _name;
	private String _values;
	private String _description;
}