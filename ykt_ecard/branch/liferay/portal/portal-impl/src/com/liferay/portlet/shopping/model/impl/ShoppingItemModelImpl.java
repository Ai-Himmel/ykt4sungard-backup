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

import com.liferay.portlet.shopping.model.ShoppingItem;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="ShoppingItemModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ShoppingItem</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingItem
 * @see com.liferay.portlet.shopping.service.model.ShoppingItemModel
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingItemImpl
 *
 */
public class ShoppingItemModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ShoppingItem";
	public static final Object[][] TABLE_COLUMNS = {
			{ "itemId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "categoryId", new Integer(Types.BIGINT) },
			

			{ "sku", new Integer(Types.VARCHAR) },
			

			{ "name", new Integer(Types.VARCHAR) },
			

			{ "description", new Integer(Types.VARCHAR) },
			

			{ "properties", new Integer(Types.VARCHAR) },
			

			{ "fields_", new Integer(Types.BOOLEAN) },
			

			{ "fieldsQuantities", new Integer(Types.VARCHAR) },
			

			{ "minQuantity", new Integer(Types.INTEGER) },
			

			{ "maxQuantity", new Integer(Types.INTEGER) },
			

			{ "price", new Integer(Types.DOUBLE) },
			

			{ "discount", new Integer(Types.DOUBLE) },
			

			{ "taxable", new Integer(Types.BOOLEAN) },
			

			{ "shipping", new Integer(Types.DOUBLE) },
			

			{ "useShippingFormula", new Integer(Types.BOOLEAN) },
			

			{ "requiresShipping", new Integer(Types.BOOLEAN) },
			

			{ "stockQuantity", new Integer(Types.INTEGER) },
			

			{ "featured_", new Integer(Types.BOOLEAN) },
			

			{ "sale_", new Integer(Types.BOOLEAN) },
			

			{ "smallImage", new Integer(Types.BOOLEAN) },
			

			{ "smallImageId", new Integer(Types.BIGINT) },
			

			{ "smallImageURL", new Integer(Types.VARCHAR) },
			

			{ "mediumImage", new Integer(Types.BOOLEAN) },
			

			{ "mediumImageId", new Integer(Types.BIGINT) },
			

			{ "mediumImageURL", new Integer(Types.VARCHAR) },
			

			{ "largeImage", new Integer(Types.BOOLEAN) },
			

			{ "largeImageId", new Integer(Types.BIGINT) },
			

			{ "largeImageURL", new Integer(Types.VARCHAR) }
		};
	public static final String TABLE_SQL_CREATE = "create table ShoppingItem (itemId LONG not null primary key,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,categoryId LONG,sku VARCHAR(75) null,name VARCHAR(200) null,description STRING null,properties STRING null,fields_ BOOLEAN,fieldsQuantities STRING null,minQuantity INTEGER,maxQuantity INTEGER,price DOUBLE,discount DOUBLE,taxable BOOLEAN,shipping DOUBLE,useShippingFormula BOOLEAN,requiresShipping BOOLEAN,stockQuantity INTEGER,featured_ BOOLEAN,sale_ BOOLEAN,smallImage BOOLEAN,smallImageId LONG,smallImageURL VARCHAR(75) null,mediumImage BOOLEAN,mediumImageId LONG,mediumImageURL VARCHAR(75) null,largeImage BOOLEAN,largeImageId LONG,largeImageURL VARCHAR(75) null)";
	public static final String TABLE_SQL_DROP = "drop table ShoppingItem";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.shopping.model.ShoppingItem"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingItem"));

	public ShoppingItemModelImpl() {
	}

	public long getPrimaryKey() {
		return _itemId;
	}

	public void setPrimaryKey(long pk) {
		setItemId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_itemId);
	}

	public long getItemId() {
		return _itemId;
	}

	public void setItemId(long itemId) {
		if (itemId != _itemId) {
			_itemId = itemId;
		}
	}

	public long getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(long companyId) {
		if (companyId != _companyId) {
			_companyId = companyId;
		}
	}

	public long getUserId() {
		return _userId;
	}

	public void setUserId(long userId) {
		if (userId != _userId) {
			_userId = userId;
		}
	}

	public String getUserName() {
		return GetterUtil.getString(_userName);
	}

	public void setUserName(String userName) {
		if (((userName == null) && (_userName != null)) ||
				((userName != null) && (_userName == null)) ||
				((userName != null) && (_userName != null) &&
				!userName.equals(_userName))) {
			_userName = userName;
		}
	}

	public Date getCreateDate() {
		return _createDate;
	}

	public void setCreateDate(Date createDate) {
		if (((createDate == null) && (_createDate != null)) ||
				((createDate != null) && (_createDate == null)) ||
				((createDate != null) && (_createDate != null) &&
				!createDate.equals(_createDate))) {
			_createDate = createDate;
		}
	}

	public Date getModifiedDate() {
		return _modifiedDate;
	}

	public void setModifiedDate(Date modifiedDate) {
		if (((modifiedDate == null) && (_modifiedDate != null)) ||
				((modifiedDate != null) && (_modifiedDate == null)) ||
				((modifiedDate != null) && (_modifiedDate != null) &&
				!modifiedDate.equals(_modifiedDate))) {
			_modifiedDate = modifiedDate;
		}
	}

	public long getCategoryId() {
		return _categoryId;
	}

	public void setCategoryId(long categoryId) {
		if (categoryId != _categoryId) {
			_categoryId = categoryId;
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

	public boolean getFields() {
		return _fields;
	}

	public boolean isFields() {
		return _fields;
	}

	public void setFields(boolean fields) {
		if (fields != _fields) {
			_fields = fields;
		}
	}

	public String getFieldsQuantities() {
		return GetterUtil.getString(_fieldsQuantities);
	}

	public void setFieldsQuantities(String fieldsQuantities) {
		if (((fieldsQuantities == null) && (_fieldsQuantities != null)) ||
				((fieldsQuantities != null) && (_fieldsQuantities == null)) ||
				((fieldsQuantities != null) && (_fieldsQuantities != null) &&
				!fieldsQuantities.equals(_fieldsQuantities))) {
			_fieldsQuantities = fieldsQuantities;
		}
	}

	public int getMinQuantity() {
		return _minQuantity;
	}

	public void setMinQuantity(int minQuantity) {
		if (minQuantity != _minQuantity) {
			_minQuantity = minQuantity;
		}
	}

	public int getMaxQuantity() {
		return _maxQuantity;
	}

	public void setMaxQuantity(int maxQuantity) {
		if (maxQuantity != _maxQuantity) {
			_maxQuantity = maxQuantity;
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

	public double getDiscount() {
		return _discount;
	}

	public void setDiscount(double discount) {
		if (discount != _discount) {
			_discount = discount;
		}
	}

	public boolean getTaxable() {
		return _taxable;
	}

	public boolean isTaxable() {
		return _taxable;
	}

	public void setTaxable(boolean taxable) {
		if (taxable != _taxable) {
			_taxable = taxable;
		}
	}

	public double getShipping() {
		return _shipping;
	}

	public void setShipping(double shipping) {
		if (shipping != _shipping) {
			_shipping = shipping;
		}
	}

	public boolean getUseShippingFormula() {
		return _useShippingFormula;
	}

	public boolean isUseShippingFormula() {
		return _useShippingFormula;
	}

	public void setUseShippingFormula(boolean useShippingFormula) {
		if (useShippingFormula != _useShippingFormula) {
			_useShippingFormula = useShippingFormula;
		}
	}

	public boolean getRequiresShipping() {
		return _requiresShipping;
	}

	public boolean isRequiresShipping() {
		return _requiresShipping;
	}

	public void setRequiresShipping(boolean requiresShipping) {
		if (requiresShipping != _requiresShipping) {
			_requiresShipping = requiresShipping;
		}
	}

	public int getStockQuantity() {
		return _stockQuantity;
	}

	public void setStockQuantity(int stockQuantity) {
		if (stockQuantity != _stockQuantity) {
			_stockQuantity = stockQuantity;
		}
	}

	public boolean getFeatured() {
		return _featured;
	}

	public boolean isFeatured() {
		return _featured;
	}

	public void setFeatured(boolean featured) {
		if (featured != _featured) {
			_featured = featured;
		}
	}

	public boolean getSale() {
		return _sale;
	}

	public boolean isSale() {
		return _sale;
	}

	public void setSale(boolean sale) {
		if (sale != _sale) {
			_sale = sale;
		}
	}

	public boolean getSmallImage() {
		return _smallImage;
	}

	public boolean isSmallImage() {
		return _smallImage;
	}

	public void setSmallImage(boolean smallImage) {
		if (smallImage != _smallImage) {
			_smallImage = smallImage;
		}
	}

	public long getSmallImageId() {
		return _smallImageId;
	}

	public void setSmallImageId(long smallImageId) {
		if (smallImageId != _smallImageId) {
			_smallImageId = smallImageId;
		}
	}

	public String getSmallImageURL() {
		return GetterUtil.getString(_smallImageURL);
	}

	public void setSmallImageURL(String smallImageURL) {
		if (((smallImageURL == null) && (_smallImageURL != null)) ||
				((smallImageURL != null) && (_smallImageURL == null)) ||
				((smallImageURL != null) && (_smallImageURL != null) &&
				!smallImageURL.equals(_smallImageURL))) {
			_smallImageURL = smallImageURL;
		}
	}

	public boolean getMediumImage() {
		return _mediumImage;
	}

	public boolean isMediumImage() {
		return _mediumImage;
	}

	public void setMediumImage(boolean mediumImage) {
		if (mediumImage != _mediumImage) {
			_mediumImage = mediumImage;
		}
	}

	public long getMediumImageId() {
		return _mediumImageId;
	}

	public void setMediumImageId(long mediumImageId) {
		if (mediumImageId != _mediumImageId) {
			_mediumImageId = mediumImageId;
		}
	}

	public String getMediumImageURL() {
		return GetterUtil.getString(_mediumImageURL);
	}

	public void setMediumImageURL(String mediumImageURL) {
		if (((mediumImageURL == null) && (_mediumImageURL != null)) ||
				((mediumImageURL != null) && (_mediumImageURL == null)) ||
				((mediumImageURL != null) && (_mediumImageURL != null) &&
				!mediumImageURL.equals(_mediumImageURL))) {
			_mediumImageURL = mediumImageURL;
		}
	}

	public boolean getLargeImage() {
		return _largeImage;
	}

	public boolean isLargeImage() {
		return _largeImage;
	}

	public void setLargeImage(boolean largeImage) {
		if (largeImage != _largeImage) {
			_largeImage = largeImage;
		}
	}

	public long getLargeImageId() {
		return _largeImageId;
	}

	public void setLargeImageId(long largeImageId) {
		if (largeImageId != _largeImageId) {
			_largeImageId = largeImageId;
		}
	}

	public String getLargeImageURL() {
		return GetterUtil.getString(_largeImageURL);
	}

	public void setLargeImageURL(String largeImageURL) {
		if (((largeImageURL == null) && (_largeImageURL != null)) ||
				((largeImageURL != null) && (_largeImageURL == null)) ||
				((largeImageURL != null) && (_largeImageURL != null) &&
				!largeImageURL.equals(_largeImageURL))) {
			_largeImageURL = largeImageURL;
		}
	}

	public ShoppingItem toEscapedModel() {
		if (isEscapedModel()) {
			return (ShoppingItem)this;
		}
		else {
			ShoppingItem model = new ShoppingItemImpl();

			model.setEscapedModel(true);

			model.setItemId(getItemId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setCategoryId(getCategoryId());
			model.setSku(Html.escape(getSku()));
			model.setName(Html.escape(getName()));
			model.setDescription(Html.escape(getDescription()));
			model.setProperties(Html.escape(getProperties()));
			model.setFields(getFields());
			model.setFieldsQuantities(Html.escape(getFieldsQuantities()));
			model.setMinQuantity(getMinQuantity());
			model.setMaxQuantity(getMaxQuantity());
			model.setPrice(getPrice());
			model.setDiscount(getDiscount());
			model.setTaxable(getTaxable());
			model.setShipping(getShipping());
			model.setUseShippingFormula(getUseShippingFormula());
			model.setRequiresShipping(getRequiresShipping());
			model.setStockQuantity(getStockQuantity());
			model.setFeatured(getFeatured());
			model.setSale(getSale());
			model.setSmallImage(getSmallImage());
			model.setSmallImageId(getSmallImageId());
			model.setSmallImageURL(Html.escape(getSmallImageURL()));
			model.setMediumImage(getMediumImage());
			model.setMediumImageId(getMediumImageId());
			model.setMediumImageURL(Html.escape(getMediumImageURL()));
			model.setLargeImage(getLargeImage());
			model.setLargeImageId(getLargeImageId());
			model.setLargeImageURL(Html.escape(getLargeImageURL()));

			model = (ShoppingItem)Proxy.newProxyInstance(ShoppingItem.class.getClassLoader(),
					new Class[] { ShoppingItem.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ShoppingItemImpl clone = new ShoppingItemImpl();

		clone.setItemId(getItemId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setCategoryId(getCategoryId());
		clone.setSku(getSku());
		clone.setName(getName());
		clone.setDescription(getDescription());
		clone.setProperties(getProperties());
		clone.setFields(getFields());
		clone.setFieldsQuantities(getFieldsQuantities());
		clone.setMinQuantity(getMinQuantity());
		clone.setMaxQuantity(getMaxQuantity());
		clone.setPrice(getPrice());
		clone.setDiscount(getDiscount());
		clone.setTaxable(getTaxable());
		clone.setShipping(getShipping());
		clone.setUseShippingFormula(getUseShippingFormula());
		clone.setRequiresShipping(getRequiresShipping());
		clone.setStockQuantity(getStockQuantity());
		clone.setFeatured(getFeatured());
		clone.setSale(getSale());
		clone.setSmallImage(getSmallImage());
		clone.setSmallImageId(getSmallImageId());
		clone.setSmallImageURL(getSmallImageURL());
		clone.setMediumImage(getMediumImage());
		clone.setMediumImageId(getMediumImageId());
		clone.setMediumImageURL(getMediumImageURL());
		clone.setLargeImage(getLargeImage());
		clone.setLargeImageId(getLargeImageId());
		clone.setLargeImageURL(getLargeImageURL());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingItemImpl shoppingItem = (ShoppingItemImpl)obj;

		int value = 0;

		if (getItemId() < shoppingItem.getItemId()) {
			value = -1;
		}
		else if (getItemId() > shoppingItem.getItemId()) {
			value = 1;
		}
		else {
			value = 0;
		}

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingItemImpl shoppingItem = null;

		try {
			shoppingItem = (ShoppingItemImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = shoppingItem.getPrimaryKey();

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