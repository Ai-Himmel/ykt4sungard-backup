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
import java.util.Set;

/**
 * <a href="ShoppingItemHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingItemHBM {
	protected ShoppingItemHBM() {
	}

	protected ShoppingItemHBM(String itemId) {
		_itemId = itemId;
	}

	protected ShoppingItemHBM(String itemId, String companyId, Date createDate,
		Date modifiedDate, String categoryId, String sku, String name,
		String description, String properties, String supplierUserId,
		boolean fields, String fieldsQuantities, int minQuantity,
		int maxQuantity, double price, double discount, boolean taxable,
		double shipping, boolean useShippingFormula, boolean requiresShipping,
		int stockQuantity, boolean featured, boolean sale, boolean smallImage,
		String smallImageURL, boolean mediumImage, String mediumImageURL,
		boolean largeImage, String largeImageURL) {
		_itemId = itemId;
		_companyId = companyId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_categoryId = categoryId;
		_sku = sku;
		_name = name;
		_description = description;
		_properties = properties;
		_supplierUserId = supplierUserId;
		_fields = fields;
		_fieldsQuantities = fieldsQuantities;
		_minQuantity = minQuantity;
		_maxQuantity = maxQuantity;
		_price = price;
		_discount = discount;
		_taxable = taxable;
		_shipping = shipping;
		_useShippingFormula = useShippingFormula;
		_requiresShipping = requiresShipping;
		_stockQuantity = stockQuantity;
		_featured = featured;
		_sale = sale;
		_smallImage = smallImage;
		_smallImageURL = smallImageURL;
		_mediumImage = mediumImage;
		_mediumImageURL = mediumImageURL;
		_largeImage = largeImage;
		_largeImageURL = largeImageURL;
	}

	public String getPrimaryKey() {
		return _itemId;
	}

	protected void setPrimaryKey(String pk) {
		_itemId = pk;
	}

	protected String getItemId() {
		return _itemId;
	}

	protected void setItemId(String itemId) {
		_itemId = itemId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected Date getCreateDate() {
		return _createDate;
	}

	protected void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	protected Date getModifiedDate() {
		return _modifiedDate;
	}

	protected void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	protected String getCategoryId() {
		return _categoryId;
	}

	protected void setCategoryId(String categoryId) {
		_categoryId = categoryId;
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

	protected boolean getFields() {
		return _fields;
	}

	protected void setFields(boolean fields) {
		_fields = fields;
	}

	protected String getFieldsQuantities() {
		return _fieldsQuantities;
	}

	protected void setFieldsQuantities(String fieldsQuantities) {
		_fieldsQuantities = fieldsQuantities;
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

	protected boolean getRequiresShipping() {
		return _requiresShipping;
	}

	protected void setRequiresShipping(boolean requiresShipping) {
		_requiresShipping = requiresShipping;
	}

	protected int getStockQuantity() {
		return _stockQuantity;
	}

	protected void setStockQuantity(int stockQuantity) {
		_stockQuantity = stockQuantity;
	}

	protected boolean getFeatured() {
		return _featured;
	}

	protected void setFeatured(boolean featured) {
		_featured = featured;
	}

	protected boolean getSale() {
		return _sale;
	}

	protected void setSale(boolean sale) {
		_sale = sale;
	}

	protected boolean getSmallImage() {
		return _smallImage;
	}

	protected void setSmallImage(boolean smallImage) {
		_smallImage = smallImage;
	}

	protected String getSmallImageURL() {
		return _smallImageURL;
	}

	protected void setSmallImageURL(String smallImageURL) {
		_smallImageURL = smallImageURL;
	}

	protected boolean getMediumImage() {
		return _mediumImage;
	}

	protected void setMediumImage(boolean mediumImage) {
		_mediumImage = mediumImage;
	}

	protected String getMediumImageURL() {
		return _mediumImageURL;
	}

	protected void setMediumImageURL(String mediumImageURL) {
		_mediumImageURL = mediumImageURL;
	}

	protected boolean getLargeImage() {
		return _largeImage;
	}

	protected void setLargeImage(boolean largeImage) {
		_largeImage = largeImage;
	}

	protected String getLargeImageURL() {
		return _largeImageURL;
	}

	protected void setLargeImageURL(String largeImageURL) {
		_largeImageURL = largeImageURL;
	}

	protected Set getShoppingItemPrices() {
		return _shoppingItemPrices;
	}

	protected void setShoppingItemPrices(Set shoppingItemPrices) {
		_shoppingItemPrices = shoppingItemPrices;
	}

	private String _itemId;
	private String _companyId;
	private Date _createDate;
	private Date _modifiedDate;
	private String _categoryId;
	private String _sku;
	private String _name;
	private String _description;
	private String _properties;
	private String _supplierUserId;
	private boolean _fields;
	private String _fieldsQuantities;
	private int _minQuantity;
	private int _maxQuantity;
	private double _price;
	private double _discount;
	private boolean _taxable;
	private double _shipping;
	private boolean _useShippingFormula;
	private boolean _requiresShipping;
	private int _stockQuantity;
	private boolean _featured;
	private boolean _sale;
	private boolean _smallImage;
	private String _smallImageURL;
	private boolean _mediumImage;
	private String _mediumImageURL;
	private boolean _largeImage;
	private String _largeImageURL;
	private Set _shoppingItemPrices;
}