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
 * <a href="ShoppingItemPriceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.shopping.service.http.ShoppingItemPriceServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.http.ShoppingItemPriceServiceSoap
 *
 */
public class ShoppingItemPriceSoap implements Serializable {
	public static ShoppingItemPriceSoap toSoapModel(ShoppingItemPrice model) {
		ShoppingItemPriceSoap soapModel = new ShoppingItemPriceSoap();

		soapModel.setItemPriceId(model.getItemPriceId());
		soapModel.setItemId(model.getItemId());
		soapModel.setMinQuantity(model.getMinQuantity());
		soapModel.setMaxQuantity(model.getMaxQuantity());
		soapModel.setPrice(model.getPrice());
		soapModel.setDiscount(model.getDiscount());
		soapModel.setTaxable(model.getTaxable());
		soapModel.setShipping(model.getShipping());
		soapModel.setUseShippingFormula(model.getUseShippingFormula());
		soapModel.setStatus(model.getStatus());

		return soapModel;
	}

	public static ShoppingItemPriceSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			ShoppingItemPrice model = (ShoppingItemPrice)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ShoppingItemPriceSoap[])soapModels.toArray(new ShoppingItemPriceSoap[0]);
	}

	public ShoppingItemPriceSoap() {
	}

	public long getPrimaryKey() {
		return _itemPriceId;
	}

	public void setPrimaryKey(long pk) {
		setItemPriceId(pk);
	}

	public long getItemPriceId() {
		return _itemPriceId;
	}

	public void setItemPriceId(long itemPriceId) {
		_itemPriceId = itemPriceId;
	}

	public long getItemId() {
		return _itemId;
	}

	public void setItemId(long itemId) {
		_itemId = itemId;
	}

	public int getMinQuantity() {
		return _minQuantity;
	}

	public void setMinQuantity(int minQuantity) {
		_minQuantity = minQuantity;
	}

	public int getMaxQuantity() {
		return _maxQuantity;
	}

	public void setMaxQuantity(int maxQuantity) {
		_maxQuantity = maxQuantity;
	}

	public double getPrice() {
		return _price;
	}

	public void setPrice(double price) {
		_price = price;
	}

	public double getDiscount() {
		return _discount;
	}

	public void setDiscount(double discount) {
		_discount = discount;
	}

	public boolean getTaxable() {
		return _taxable;
	}

	public boolean isTaxable() {
		return _taxable;
	}

	public void setTaxable(boolean taxable) {
		_taxable = taxable;
	}

	public double getShipping() {
		return _shipping;
	}

	public void setShipping(double shipping) {
		_shipping = shipping;
	}

	public boolean getUseShippingFormula() {
		return _useShippingFormula;
	}

	public boolean isUseShippingFormula() {
		return _useShippingFormula;
	}

	public void setUseShippingFormula(boolean useShippingFormula) {
		_useShippingFormula = useShippingFormula;
	}

	public int getStatus() {
		return _status;
	}

	public void setStatus(int status) {
		_status = status;
	}

	private long _itemPriceId;
	private long _itemId;
	private int _minQuantity;
	private int _maxQuantity;
	private double _price;
	private double _discount;
	private boolean _taxable;
	private double _shipping;
	private boolean _useShippingFormula;
	private int _status;
}