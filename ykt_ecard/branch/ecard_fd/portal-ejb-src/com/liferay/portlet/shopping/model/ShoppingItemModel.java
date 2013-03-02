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

import com.liferay.portal.model.BaseModel;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.Xss;

import java.util.Date;

/**
 * <a href="ShoppingItemModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.79 $
 *
 */
public class ShoppingItemModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingItem"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingItem"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ITEMID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.itemId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CATEGORYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.categoryId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SKU = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.sku"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_NAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.name"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_DESCRIPTION = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.description"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PROPERTIES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.properties"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SUPPLIERUSERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.supplierUserId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_FIELDSQUANTITIES = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.fieldsQuantities"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SMALLIMAGEURL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.smallImageURL"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_MEDIUMIMAGEURL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.mediumImageURL"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_LARGEIMAGEURL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingItem.largeImageURL"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingItemModel"));

	public ShoppingItemModel() {
	}

	public ShoppingItemModel(String itemId) {
		_itemId = itemId;
		setNew(true);
	}

	public ShoppingItemModel(String itemId, String companyId, Date createDate,
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

	public String getItemId() {
		return _itemId;
	}

	public void setItemId(String itemId) {
		if (((itemId == null) && (_itemId != null)) ||
				((itemId != null) && (_itemId == null)) ||
				((itemId != null) && (_itemId != null) &&
				!itemId.equals(_itemId))) {
			if (!XSS_ALLOW_ITEMID) {
				itemId = Xss.strip(itemId);
			}

			_itemId = itemId;
			setModified(true);
		}
	}

	public String getCompanyId() {
		return _companyId;
	}

	public void setCompanyId(String companyId) {
		if (((companyId == null) && (_companyId != null)) ||
				((companyId != null) && (_companyId == null)) ||
				((companyId != null) && (_companyId != null) &&
				!companyId.equals(_companyId))) {
			if (!XSS_ALLOW_COMPANYID) {
				companyId = Xss.strip(companyId);
			}

			_companyId = companyId;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public String getCategoryId() {
		return _categoryId;
	}

	public void setCategoryId(String categoryId) {
		if (((categoryId == null) && (_categoryId != null)) ||
				((categoryId != null) && (_categoryId == null)) ||
				((categoryId != null) && (_categoryId != null) &&
				!categoryId.equals(_categoryId))) {
			if (!XSS_ALLOW_CATEGORYID) {
				categoryId = Xss.strip(categoryId);
			}

			_categoryId = categoryId;
			setModified(true);
		}
	}

	public String getSku() {
		return _sku;
	}

	public void setSku(String sku) {
		if (((sku == null) && (_sku != null)) ||
				((sku != null) && (_sku == null)) ||
				((sku != null) && (_sku != null) && !sku.equals(_sku))) {
			if (!XSS_ALLOW_SKU) {
				sku = Xss.strip(sku);
			}

			_sku = sku;
			setModified(true);
		}
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		if (((name == null) && (_name != null)) ||
				((name != null) && (_name == null)) ||
				((name != null) && (_name != null) && !name.equals(_name))) {
			if (!XSS_ALLOW_NAME) {
				name = Xss.strip(name);
			}

			_name = name;
			setModified(true);
		}
	}

	public String getDescription() {
		return _description;
	}

	public void setDescription(String description) {
		if (((description == null) && (_description != null)) ||
				((description != null) && (_description == null)) ||
				((description != null) && (_description != null) &&
				!description.equals(_description))) {
			if (!XSS_ALLOW_DESCRIPTION) {
				description = Xss.strip(description);
			}

			_description = description;
			setModified(true);
		}
	}

	public String getProperties() {
		return _properties;
	}

	public void setProperties(String properties) {
		if (((properties == null) && (_properties != null)) ||
				((properties != null) && (_properties == null)) ||
				((properties != null) && (_properties != null) &&
				!properties.equals(_properties))) {
			if (!XSS_ALLOW_PROPERTIES) {
				properties = Xss.strip(properties);
			}

			_properties = properties;
			setModified(true);
		}
	}

	public String getSupplierUserId() {
		return _supplierUserId;
	}

	public void setSupplierUserId(String supplierUserId) {
		if (((supplierUserId == null) && (_supplierUserId != null)) ||
				((supplierUserId != null) && (_supplierUserId == null)) ||
				((supplierUserId != null) && (_supplierUserId != null) &&
				!supplierUserId.equals(_supplierUserId))) {
			if (!XSS_ALLOW_SUPPLIERUSERID) {
				supplierUserId = Xss.strip(supplierUserId);
			}

			_supplierUserId = supplierUserId;
			setModified(true);
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
			setModified(true);
		}
	}

	public String getFieldsQuantities() {
		return _fieldsQuantities;
	}

	public void setFieldsQuantities(String fieldsQuantities) {
		if (((fieldsQuantities == null) && (_fieldsQuantities != null)) ||
				((fieldsQuantities != null) && (_fieldsQuantities == null)) ||
				((fieldsQuantities != null) && (_fieldsQuantities != null) &&
				!fieldsQuantities.equals(_fieldsQuantities))) {
			if (!XSS_ALLOW_FIELDSQUANTITIES) {
				fieldsQuantities = Xss.strip(fieldsQuantities);
			}

			_fieldsQuantities = fieldsQuantities;
			setModified(true);
		}
	}

	public int getMinQuantity() {
		return _minQuantity;
	}

	public void setMinQuantity(int minQuantity) {
		if (minQuantity != _minQuantity) {
			_minQuantity = minQuantity;
			setModified(true);
		}
	}

	public int getMaxQuantity() {
		return _maxQuantity;
	}

	public void setMaxQuantity(int maxQuantity) {
		if (maxQuantity != _maxQuantity) {
			_maxQuantity = maxQuantity;
			setModified(true);
		}
	}

	public double getPrice() {
		return _price;
	}

	public void setPrice(double price) {
		if (price != _price) {
			_price = price;
			setModified(true);
		}
	}

	public double getDiscount() {
		return _discount;
	}

	public void setDiscount(double discount) {
		if (discount != _discount) {
			_discount = discount;
			setModified(true);
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
			setModified(true);
		}
	}

	public double getShipping() {
		return _shipping;
	}

	public void setShipping(double shipping) {
		if (shipping != _shipping) {
			_shipping = shipping;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public int getStockQuantity() {
		return _stockQuantity;
	}

	public void setStockQuantity(int stockQuantity) {
		if (stockQuantity != _stockQuantity) {
			_stockQuantity = stockQuantity;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public String getSmallImageURL() {
		return _smallImageURL;
	}

	public void setSmallImageURL(String smallImageURL) {
		if (((smallImageURL == null) && (_smallImageURL != null)) ||
				((smallImageURL != null) && (_smallImageURL == null)) ||
				((smallImageURL != null) && (_smallImageURL != null) &&
				!smallImageURL.equals(_smallImageURL))) {
			if (!XSS_ALLOW_SMALLIMAGEURL) {
				smallImageURL = Xss.strip(smallImageURL);
			}

			_smallImageURL = smallImageURL;
			setModified(true);
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
			setModified(true);
		}
	}

	public String getMediumImageURL() {
		return _mediumImageURL;
	}

	public void setMediumImageURL(String mediumImageURL) {
		if (((mediumImageURL == null) && (_mediumImageURL != null)) ||
				((mediumImageURL != null) && (_mediumImageURL == null)) ||
				((mediumImageURL != null) && (_mediumImageURL != null) &&
				!mediumImageURL.equals(_mediumImageURL))) {
			if (!XSS_ALLOW_MEDIUMIMAGEURL) {
				mediumImageURL = Xss.strip(mediumImageURL);
			}

			_mediumImageURL = mediumImageURL;
			setModified(true);
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
			setModified(true);
		}
	}

	public String getLargeImageURL() {
		return _largeImageURL;
	}

	public void setLargeImageURL(String largeImageURL) {
		if (((largeImageURL == null) && (_largeImageURL != null)) ||
				((largeImageURL != null) && (_largeImageURL == null)) ||
				((largeImageURL != null) && (_largeImageURL != null) &&
				!largeImageURL.equals(_largeImageURL))) {
			if (!XSS_ALLOW_LARGEIMAGEURL) {
				largeImageURL = Xss.strip(largeImageURL);
			}

			_largeImageURL = largeImageURL;
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingItem(getItemId(), getCompanyId(), getCreateDate(),
			getModifiedDate(), getCategoryId(), getSku(), getName(),
			getDescription(), getProperties(), getSupplierUserId(),
			getFields(), getFieldsQuantities(), getMinQuantity(),
			getMaxQuantity(), getPrice(), getDiscount(), getTaxable(),
			getShipping(), getUseShippingFormula(), getRequiresShipping(),
			getStockQuantity(), getFeatured(), getSale(), getSmallImage(),
			getSmallImageURL(), getMediumImage(), getMediumImageURL(),
			getLargeImage(), getLargeImageURL());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingItem shoppingItem = (ShoppingItem)obj;
		int value = 0;
		value = getItemId().compareTo(shoppingItem.getItemId());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingItem shoppingItem = null;

		try {
			shoppingItem = (ShoppingItem)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingItem.getPrimaryKey();

		if (getPrimaryKey().equals(pk)) {
			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getPrimaryKey().hashCode();
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
}