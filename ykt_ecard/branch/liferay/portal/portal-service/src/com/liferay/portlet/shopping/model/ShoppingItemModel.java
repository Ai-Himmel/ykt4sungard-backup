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

import com.liferay.portal.model.BaseModel;

import java.util.Date;

/**
 * <a href="ShoppingItemModel.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>ShoppingItem</code>
 * table in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingItem
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingItemImpl
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingItemModelImpl
 *
 */
public interface ShoppingItemModel extends BaseModel {
	public long getPrimaryKey();

	public void setPrimaryKey(long pk);

	public long getItemId();

	public void setItemId(long itemId);

	public long getCompanyId();

	public void setCompanyId(long companyId);

	public long getUserId();

	public void setUserId(long userId);

	public String getUserName();

	public void setUserName(String userName);

	public Date getCreateDate();

	public void setCreateDate(Date createDate);

	public Date getModifiedDate();

	public void setModifiedDate(Date modifiedDate);

	public long getCategoryId();

	public void setCategoryId(long categoryId);

	public String getSku();

	public void setSku(String sku);

	public String getName();

	public void setName(String name);

	public String getDescription();

	public void setDescription(String description);

	public String getProperties();

	public void setProperties(String properties);

	public boolean getFields();

	public boolean isFields();

	public void setFields(boolean fields);

	public String getFieldsQuantities();

	public void setFieldsQuantities(String fieldsQuantities);

	public int getMinQuantity();

	public void setMinQuantity(int minQuantity);

	public int getMaxQuantity();

	public void setMaxQuantity(int maxQuantity);

	public double getPrice();

	public void setPrice(double price);

	public double getDiscount();

	public void setDiscount(double discount);

	public boolean getTaxable();

	public boolean isTaxable();

	public void setTaxable(boolean taxable);

	public double getShipping();

	public void setShipping(double shipping);

	public boolean getUseShippingFormula();

	public boolean isUseShippingFormula();

	public void setUseShippingFormula(boolean useShippingFormula);

	public boolean getRequiresShipping();

	public boolean isRequiresShipping();

	public void setRequiresShipping(boolean requiresShipping);

	public int getStockQuantity();

	public void setStockQuantity(int stockQuantity);

	public boolean getFeatured();

	public boolean isFeatured();

	public void setFeatured(boolean featured);

	public boolean getSale();

	public boolean isSale();

	public void setSale(boolean sale);

	public boolean getSmallImage();

	public boolean isSmallImage();

	public void setSmallImage(boolean smallImage);

	public long getSmallImageId();

	public void setSmallImageId(long smallImageId);

	public String getSmallImageURL();

	public void setSmallImageURL(String smallImageURL);

	public boolean getMediumImage();

	public boolean isMediumImage();

	public void setMediumImage(boolean mediumImage);

	public long getMediumImageId();

	public void setMediumImageId(long mediumImageId);

	public String getMediumImageURL();

	public void setMediumImageURL(String mediumImageURL);

	public boolean getLargeImage();

	public boolean isLargeImage();

	public void setLargeImage(boolean largeImage);

	public long getLargeImageId();

	public void setLargeImageId(long largeImageId);

	public String getLargeImageURL();

	public void setLargeImageURL(String largeImageURL);

	public ShoppingItem toEscapedModel();
}