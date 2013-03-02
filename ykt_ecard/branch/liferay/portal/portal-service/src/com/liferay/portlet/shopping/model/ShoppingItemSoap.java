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
import java.util.Date;
import java.util.List;

/**
 * <a href="ShoppingItemSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portlet.shopping.service.http.ShoppingItemServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.http.ShoppingItemServiceSoap
 *
 */
public class ShoppingItemSoap implements Serializable {
	public static ShoppingItemSoap toSoapModel(ShoppingItem model) {
		ShoppingItemSoap soapModel = new ShoppingItemSoap();

		soapModel.setItemId(model.getItemId());
		soapModel.setCompanyId(model.getCompanyId());
		soapModel.setUserId(model.getUserId());
		soapModel.setUserName(model.getUserName());
		soapModel.setCreateDate(model.getCreateDate());
		soapModel.setModifiedDate(model.getModifiedDate());
		soapModel.setCategoryId(model.getCategoryId());
		soapModel.setSku(model.getSku());
		soapModel.setName(model.getName());
		soapModel.setDescription(model.getDescription());
		soapModel.setProperties(model.getProperties());
		soapModel.setFields(model.getFields());
		soapModel.setFieldsQuantities(model.getFieldsQuantities());
		soapModel.setMinQuantity(model.getMinQuantity());
		soapModel.setMaxQuantity(model.getMaxQuantity());
		soapModel.setPrice(model.getPrice());
		soapModel.setDiscount(model.getDiscount());
		soapModel.setTaxable(model.getTaxable());
		soapModel.setShipping(model.getShipping());
		soapModel.setUseShippingFormula(model.getUseShippingFormula());
		soapModel.setRequiresShipping(model.getRequiresShipping());
		soapModel.setStockQuantity(model.getStockQuantity());
		soapModel.setFeatured(model.getFeatured());
		soapModel.setSale(model.getSale());
		soapModel.setSmallImage(model.getSmallImage());
		soapModel.setSmallImageId(model.getSmallImageId());
		soapModel.setSmallImageURL(model.getSmallImageURL());
		soapModel.setMediumImage(model.getMediumImage());
		soapModel.setMediumImageId(model.getMediumImageId());
		soapModel.setMediumImageURL(model.getMediumImageURL());
		soapModel.setLargeImage(model.getLargeImage());
		soapModel.setLargeImageId(model.getLargeImageId());
		soapModel.setLargeImageURL(model.getLargeImageURL());

		return soapModel;
	}

	public static ShoppingItemSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			ShoppingItem model = (ShoppingItem)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (ShoppingItemSoap[])soapModels.toArray(new ShoppingItemSoap[0]);
	}

	public ShoppingItemSoap() {
	}

	public long getPrimaryKey() {
		return _itemId;
	}

	public void setPrimaryKey(long pk) {
		setItemId(pk);
	}

	public long getItemId() {
		return _itemId;
	}

	public void setItemId(long itemId) {
		_itemId = itemId;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		_companyId = companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		_userId = userId;
	}

	public String getUserName() {
		return _userName;
	}

	public void setUserName(String userName) {
		_userName = userName;
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		_createDate = createDate;
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		_modifiedDate = modifiedDate;
	}

	public long getCategoryId() {
		return _categoryId;
	}

	public void setCategoryId(long categoryId) {
		_categoryId = categoryId;
	}

	public String getSku() {
		return _sku;
	}

	public void setSku(String sku) {
		_sku = sku;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		_description = description;
	}

	public String getProperties() {
		return _properties;
	}

	public void setProperties(String properties) {
		_properties = properties;
	}

	public boolean getFields() {
		return _fields;
	}

	public boolean isFields() {
		return _fields;
	}

	public void setFields(boolean fields) {
		_fields = fields;
	}

	public String getFieldsQuantities() {
		return _fieldsQuantities;
	}

	public void setFieldsQuantities(String fieldsQuantities) {
		_fieldsQuantities = fieldsQuantities;
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

	public boolean getRequiresShipping() {
		return _requiresShipping;
	}

	public boolean isRequiresShipping() {
		return _requiresShipping;
	}

	public void setRequiresShipping(boolean requiresShipping) {
		_requiresShipping = requiresShipping;
	}

	public int getStockQuantity() {
		return _stockQuantity;
	}

	public void setStockQuantity(int stockQuantity) {
		_stockQuantity = stockQuantity;
	}

	public boolean getFeatured() {
		return _featured;
	}

	public boolean isFeatured() {
		return _featured;
	}

	public void setFeatured(boolean featured) {
		_featured = featured;
	}

	public boolean getSale() {
		return _sale;
	}

	public boolean isSale() {
		return _sale;
	}

	public void setSale(boolean sale) {
		_sale = sale;
	}

	public boolean getSmallImage() {
		return _smallImage;
	}

	public boolean isSmallImage() {
		return _smallImage;
	}

	public void setSmallImage(boolean smallImage) {
		_smallImage = smallImage;
	}

	public long getSmallImageId() {
		return _smallImageId;
	}

	public void setSmallImageId(long smallImageId) {
		_smallImageId = smallImageId;
	}

	public String getSmallImageURL() {
		return _smallImageURL;
	}

	public void setSmallImageURL(String smallImageURL) {
		_smallImageURL = smallImageURL;
	}

	public boolean getMediumImage() {
		return _mediumImage;
	}

	public boolean isMediumImage() {
		return _mediumImage;
	}

	public void setMediumImage(boolean mediumImage) {
		_mediumImage = mediumImage;
	}

	public long getMediumImageId() {
		return _mediumImageId;
	}

	public void setMediumImageId(long mediumImageId) {
		_mediumImageId = mediumImageId;
	}

	public String getMediumImageURL() {
		return _mediumImageURL;
	}

	public void setMediumImageURL(String mediumImageURL) {
		_mediumImageURL = mediumImageURL;
	}

	public boolean getLargeImage() {
		return _largeImage;
	}

	public boolean isLargeImage() {
		return _largeImage;
	}

	public void setLargeImage(boolean largeImage) {
		_largeImage = largeImage;
	}

	public long getLargeImageId() {
		return _largeImageId;
	}

	public void setLargeImageId(long largeImageId) {
		_largeImageId = largeImageId;
	}

	public String getLargeImageURL() {
		return _largeImageURL;
	}

	public void setLargeImageURL(String largeImageURL) {
		_largeImageURL = largeImageURL;
	}

	private long _itemId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private long _categoryId;
	private String _sku;
	private String _name;
	private String _description;
	private String _properties;
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
	private long _smallImageId;
	private String _smallImageURL;
	private boolean _mediumImage;
	private long _mediumImageId;
	private String _mediumImageURL;
	private boolean _largeImage;
	private long _largeImageId;
	private String _largeImageURL;
}