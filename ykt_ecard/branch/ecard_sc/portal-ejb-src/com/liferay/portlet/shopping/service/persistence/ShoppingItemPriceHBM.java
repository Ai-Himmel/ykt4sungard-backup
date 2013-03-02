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
 * <a href="ShoppingItemPriceHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemPriceHBM {
	protected ShoppingItemPriceHBM() {
	}

	protected ShoppingItemPriceHBM(String itemPriceId) {
		_itemPriceId = itemPriceId;
	}

	protected ShoppingItemPriceHBM(String itemPriceId, String itemId,
		int minQuantity, int maxQuantity, double price, double discount,
		boolean taxable, double shipping, boolean useShippingFormula, int status) {
		_itemPriceId = itemPriceId;
		_itemId = itemId;
		_minQuantity = minQuantity;
		_maxQuantity = maxQuantity;
		_price = price;
		_discount = discount;
		_taxable = taxable;
		_shipping = shipping;
		_useShippingFormula = useShippingFormula;
		_status = status;
	}

	public String getPrimaryKey() {
		return _itemPriceId;
	}

	protected void setPrimaryKey(String pk) {
		_itemPriceId = pk;
	}

	protected String getItemPriceId() {
		return _itemPriceId;
	}

	protected void setItemPriceId(String itemPriceId) {
		_itemPriceId = itemPriceId;
	}

	protected String getItemId() {
		return _itemId;
	}

	protected void setItemId(String itemId) {
		_itemId = itemId;
	}

	protected int getMinQuantity() {
		return _minQuantity;
	}

	protected void setMinQuantity(int minQuantity) {
		_minQuantity = minQuantity;
	}

	protected int getMaxQuantity() {
		return _maxQuantity;
	}

	protected void setMaxQuantity(int maxQuantity) {
		_maxQuantity = maxQuantity;
	}

	protected double getPrice() {
		return _price;
	}

	protected void setPrice(double price) {
		_price = price;
	}

	protected double getDiscount() {
		return _discount;
	}

	protected void setDiscount(double discount) {
		_discount = discount;
	}

	protected boolean getTaxable() {
		return _taxable;
	}

	protected void setTaxable(boolean taxable) {
		_taxable = taxable;
	}

	protected double getShipping() {
		return _shipping;
	}

	protected void setShipping(double shipping) {
		_shipping = shipping;
	}

	protected boolean getUseShippingFormula() {
		return _useShippingFormula;
	}

	protected void setUseShippingFormula(boolean useShippingFormula) {
		_useShippingFormula = useShippingFormula;
	}

	protected int getStatus() {
		return _status;
	}

	protected void setStatus(int status) {
		_status = status;
	}

	private String _itemPriceId;
	private String _itemId;
	private int _minQuantity;
	private int _maxQuantity;
	private double _price;
	private double _discount;
	private boolean _taxable;
	private double _shipping;
	private boolean _useShippingFormula;
	private int _status;
}