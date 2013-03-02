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

package com.liferay.portlet.shopping.model.impl;

import com.liferay.portal.kernel.bean.ReadOnlyBeanHandler;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.shopping.model.ShoppingOrderItem;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="ShoppingOrderItemModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ShoppingOrderItem</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingOrderItem
 * @see com.liferay.portlet.shopping.service.model.ShoppingOrderItemModel
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingOrderItemImpl
 *
 */
public class ShoppingOrderItemModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ShoppingOrderItem";
	public static final Object[][] TABLE_COLUMNS = {
			{ "orderItemId", new Integer(Types.BIGINT) },
			

			{ "orderId", new Integer(Types.BIGINT) },
			

			{ "itemId", new Integer(Types.VARCHAR) },
			

			{ "sku", new Integer(Types.VARCHAR) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "properties", new Integer(Types.VARCHAR) },
			

			{ "price", new Integer(Types.DOUBLE) },
			

			{ "quantity", new Integer(Types.INTEGER) },
			

			{ "shippedDate", new Integer(Types.TIMESTAMP) }
		};
	public static final String TABLE_SQL_CREATE = "create table ShoppingOrderItem (orderItemId LONG not null primary key,orderId LONG,itemId VARCHAR(75) null,sku VARCHAR(75) null,name VARCHAR(200) null,description STRING null,properties STRING null,price DOUBLE,quantity INTEGER,shippedDate DATE null)";
	public static final String TABLE_SQL_DROP = "drop table ShoppingOrderItem";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.shopping.model.ShoppingOrderItem"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingOrderItem"));

	public ShoppingOrderItemModelImpl() {
	}

	public long getPrimaryKey() {
		return _orderItemId;
	}

	public void setPrimaryKey(long pk) {
		setOrderItemId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_orderItemId);
	}

	public long getOrderItemId() {
		return _orderItemId;
	}

	public void setOrderItemId(long orderItemId) {
		if (orderItemId != _orderItemId) {
			_orderItemId = orderItemId;
		}
	}

	public long getOrderId() {
		return _orderId;
	}

	public void setOrderId(long orderId) {
		if (orderId != _orderId) {
			_orderId = orderId;
		}
	}

	public String getItemId() {
		return GetterUtil.getString(_itemId);
	}

	public void setItemId(String itemId) {
		if (((itemId == null) && (_itemId != null)) ||
				((itemId != null) && (_itemId == null)) ||
				((itemId != null) && (_itemId != null) &&
				!itemId.equals(_itemId))) {
			_itemId = itemId;
		}
	}

	public String getSku() {
		return GetterUtil.getString(_sku);
	}

	public void setSku(String sku) {
		if (((sku == null) && (_sku != null)) ||
				((sku != null) && (_sku == null)) ||
				((sku != null) && (_sku != null) && !sku.equals(_sku))) {
			_sku = sku;
		}
	}

	public String getName() {
		return GetterUtil.getString(_name);
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			_name = name;
		}
	}

	public String getDescription() {
		return GetterUtil.getString(_description);
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			_description = description;
		}
	}

	public String getProperties() {
		return GetterUtil.getString(_properties);
	}

	public void setProperties(String properties) {
		if (((properties == null) && (_properties != null)) ||
				((properties != null) && (_properties == null)) ||
				((properties != null) && (_properties != null) &&
				!properties.equals(_properties))) {
			_properties = properties;
		}
	}

	public double getPrice() {
		return _price;
	}

	public void setPrice(double price) {
		if (price != _price) {
			_price = price;
		}
	}

	public int getQuantity() {
		return _quantity;
	}

	public void setQuantity(int quantity) {
		if (quantity != _quantity) {
			_quantity = quantity;
		}
	}

	public Date getShippedDate() {
		return _shippedDate;
	}

	public void setShippedDate(Date shippedDate) {
		if (((shippedDate == null) && (_shippedDate != null)) ||
				((shippedDate != null) && (_shippedDate == null)) ||
				((shippedDate != null) && (_shippedDate != null) &&
				!shippedDate.equals(_shippedDate))) {
			_shippedDate = shippedDate;
		}
	}

	public ShoppingOrderItem toEscapedModel() {
		if (isEscapedModel()) {
			return (ShoppingOrderItem)this;
		}
		else {
			ShoppingOrderItem model = new ShoppingOrderItemImpl();

			model.setEscapedModel(true);

			model.setOrderItemId(getOrderItemId());
			model.setOrderId(getOrderId());
			model.setItemId(Html.escape(getItemId()));
			model.setSku(Html.escape(getSku()));
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));
			model.setProperties(Html.escape(getProperties()));
			model.setPrice(getPrice());
			model.setQuantity(getQuantity());
			model.setShippedDate(getShippedDate());

			model = (ShoppingOrderItem)Proxy.newProxyInstance(ShoppingOrderItem.class.getClassLoader(),
					new Class[] { ShoppingOrderItem.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ShoppingOrderItemImpl clone = new ShoppingOrderItemImpl();

		clone.setOrderItemId(getOrderItemId());
		clone.setOrderId(getOrderId());
		clone.setItemId(getItemId());
		clone.setSku(getSku());
		clone.setName(getName());
		clone.setDescription(getDescription());
		clone.setProperties(getProperties());
		clone.setPrice(getPrice());
		clone.setQuantity(getQuantity());
		clone.setShippedDate(getShippedDate());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingOrderItemImpl shoppingOrderItem = (ShoppingOrderItemImpl)obj;

		int value = 0;

		value = getName().compareTo(shoppingOrderItem.getName());

		if (value != 0) {
			return value;
		}

		value = getDescription().compareTo(shoppingOrderItem.getDescription());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingOrderItemImpl shoppingOrderItem = null;

		try {
			shoppingOrderItem = (ShoppingOrderItemImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = shoppingOrderItem.getPrimaryKey();

		if (getPrimaryKey() == pk) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return (int)getPrimaryKey();
	}

	private long _orderItemId;
	private long _orderId;
	private String _itemId;
	private String _sku;
	private String _name;
	private String _description;
	private String _properties;
	private double _price;
	private int _quantity;
	private Date _shippedDate;
}