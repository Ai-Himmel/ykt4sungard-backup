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

import java.util.Date;

/**
 * <a href="ShoppingOrderItemHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderItemHBM {
	protected ShoppingOrderItemHBM() {
	}

	protected ShoppingOrderItemHBM(ShoppingOrderItemPK pk) {
		_orderId = pk.orderId;
		_itemId = pk.itemId;
	}

	protected ShoppingOrderItemHBM(String orderId, String itemId, String sku,
		String name, String description, String properties,
		String supplierUserId, double price, int quantity, Date shippedDate) {
		_orderId = orderId;
		_itemId = itemId;
		_sku = sku;
		_name = name;
		_description = description;
		_properties = properties;
		_supplierUserId = supplierUserId;
		_price = price;
		_quantity = quantity;
		_shippedDate = shippedDate;
	}

	public ShoppingOrderItemPK getPrimaryKey() {
		return new ShoppingOrderItemPK(_orderId, _itemId);
	}

	protected void setPrimaryKey(ShoppingOrderItemPK pk) {
		_orderId = pk.orderId;
		_itemId = pk.itemId;
	}

	protected String getOrderId() {
		return _orderId;
	}

	protected void setOrderId(String orderId) {
		_orderId = orderId;
	}

	protected String getItemId() {
		return _itemId;
	}

	protected void setItemId(String itemId) {
		_itemId = itemId;
	}

	protected String getSku() {
		return _sku;
	}

	protected void setSku(String sku) {
		_sku = sku;
	}

	protected String getName() {
		return _name;
	}

	protected void setName(String name) {
		_name = name;
	}

	protected String getDescription() {
		return _description;
	}

	protected void setDescription(String description) {
		_description = description;
	}

	protected String getProperties() {
		return _properties;
	}

	protected void setProperties(String properties) {
		_properties = properties;
	}

	protected String getSupplierUserId() {
		return _supplierUserId;
	}

	protected void setSupplierUserId(String supplierUserId) {
		_supplierUserId = supplierUserId;
	}

	protected double getPrice() {
		return _price;
	}

	protected void setPrice(double price) {
		_price = price;
	}

	protected int getQuantity() {
		return _quantity;
	}

	protected void setQuantity(int quantity) {
		_quantity = quantity;
	}

	protected Date getShippedDate() {
		return _shippedDate;
	}

	protected void setShippedDate(Date shippedDate) {
		_shippedDate = shippedDate;
	}

	private String _orderId;
	private String _itemId;
	private String _sku;
	private String _name;
	private String _description;
	private String _properties;
	private String _supplierUserId;
	private double _price;
	private int _quantity;
	private Date _shippedDate;
}