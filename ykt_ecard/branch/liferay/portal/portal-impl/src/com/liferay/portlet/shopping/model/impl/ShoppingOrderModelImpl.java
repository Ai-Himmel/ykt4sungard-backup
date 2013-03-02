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
import com.liferay.portal.kernel.util.DateUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.impl.BaseModelImpl;
import com.liferay.portal.util.PropsUtil;

import com.liferay.portlet.shopping.model.ShoppingOrder;

import com.liferay.util.Html;

import java.io.Serializable;

import java.lang.reflect.Proxy;

import java.sql.Types;

import java.util.Date;

/**
 * <a href="ShoppingOrderModelImpl.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is a model that represents the <code>ShoppingOrder</code> table
 * in the database.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.model.ShoppingOrder
 * @see com.liferay.portlet.shopping.service.model.ShoppingOrderModel
 * @see com.liferay.portlet.shopping.service.model.impl.ShoppingOrderImpl
 *
 */
public class ShoppingOrderModelImpl extends BaseModelImpl {
	public static final String TABLE_NAME = "ShoppingOrder";
	public static final Object[][] TABLE_COLUMNS = {
			{ "orderId", new Integer(Types.BIGINT) },
			

			{ "groupId", new Integer(Types.BIGINT) },
			

			{ "companyId", new Integer(Types.BIGINT) },
			

			{ "userId", new Integer(Types.BIGINT) },
			

			{ "userName", new Integer(Types.VARCHAR) },
			

			{ "createDate", new Integer(Types.TIMESTAMP) },
			

			{ "modifiedDate", new Integer(Types.TIMESTAMP) },
			

			{ "number_", new Integer(Types.VARCHAR) },
			

			{ "tax", new Integer(Types.DOUBLE) },
			

			{ "shipping", new Integer(Types.DOUBLE) },
			

			{ "altShipping", new Integer(Types.VARCHAR) },
			

			{ "requiresShipping", new Integer(Types.BOOLEAN) },
			

			{ "insure", new Integer(Types.BOOLEAN) },
			

			{ "insurance", new Integer(Types.DOUBLE) },
			

			{ "couponCodes", new Integer(Types.VARCHAR) },
			

			{ "couponDiscount", new Integer(Types.DOUBLE) },
			

			{ "billingFirstName", new Integer(Types.VARCHAR) },
			

			{ "billingLastName", new Integer(Types.VARCHAR) },
			

			{ "billingEmailAddress", new Integer(Types.VARCHAR) },
			

			{ "billingCompany", new Integer(Types.VARCHAR) },
			

			{ "billingStreet", new Integer(Types.VARCHAR) },
			

			{ "billingCity", new Integer(Types.VARCHAR) },
			

			{ "billingState", new Integer(Types.VARCHAR) },
			

			{ "billingZip", new Integer(Types.VARCHAR) },
			

			{ "billingCountry", new Integer(Types.VARCHAR) },
			

			{ "billingPhone", new Integer(Types.VARCHAR) },
			

			{ "shipToBilling", new Integer(Types.BOOLEAN) },
			

			{ "shippingFirstName", new Integer(Types.VARCHAR) },
			

			{ "shippingLastName", new Integer(Types.VARCHAR) },
			

			{ "shippingEmailAddress", new Integer(Types.VARCHAR) },
			

			{ "shippingCompany", new Integer(Types.VARCHAR) },
			

			{ "shippingStreet", new Integer(Types.VARCHAR) },
			

			{ "shippingCity", new Integer(Types.VARCHAR) },
			

			{ "shippingState", new Integer(Types.VARCHAR) },
			

			{ "shippingZip", new Integer(Types.VARCHAR) },
			

			{ "shippingCountry", new Integer(Types.VARCHAR) },
			

			{ "shippingPhone", new Integer(Types.VARCHAR) },
			

			{ "ccName", new Integer(Types.VARCHAR) },
			

			{ "ccType", new Integer(Types.VARCHAR) },
			

			{ "ccNumber", new Integer(Types.VARCHAR) },
			

			{ "ccExpMonth", new Integer(Types.INTEGER) },
			

			{ "ccExpYear", new Integer(Types.INTEGER) },
			

			{ "ccVerNumber", new Integer(Types.VARCHAR) },
			

			{ "comments", new Integer(Types.VARCHAR) },
			

			{ "ppTxnId", new Integer(Types.VARCHAR) },
			

			{ "ppPaymentStatus", new Integer(Types.VARCHAR) },
			

			{ "ppPaymentGross", new Integer(Types.DOUBLE) },
			

			{ "ppReceiverEmail", new Integer(Types.VARCHAR) },
			

			{ "ppPayerEmail", new Integer(Types.VARCHAR) },
			

			{ "sendOrderEmail", new Integer(Types.BOOLEAN) },
			

			{ "sendShippingEmail", new Integer(Types.BOOLEAN) }
		};
	public static final String TABLE_SQL_CREATE = "create table ShoppingOrder (orderId LONG not null primary key,groupId LONG,companyId LONG,userId LONG,userName VARCHAR(75) null,createDate DATE null,modifiedDate DATE null,number_ VARCHAR(75) null,tax DOUBLE,shipping DOUBLE,altShipping VARCHAR(75) null,requiresShipping BOOLEAN,insure BOOLEAN,insurance DOUBLE,couponCodes VARCHAR(75) null,couponDiscount DOUBLE,billingFirstName VARCHAR(75) null,billingLastName VARCHAR(75) null,billingEmailAddress VARCHAR(75) null,billingCompany VARCHAR(75) null,billingStreet VARCHAR(75) null,billingCity VARCHAR(75) null,billingState VARCHAR(75) null,billingZip VARCHAR(75) null,billingCountry VARCHAR(75) null,billingPhone VARCHAR(75) null,shipToBilling BOOLEAN,shippingFirstName VARCHAR(75) null,shippingLastName VARCHAR(75) null,shippingEmailAddress VARCHAR(75) null,shippingCompany VARCHAR(75) null,shippingStreet VARCHAR(75) null,shippingCity VARCHAR(75) null,shippingState VARCHAR(75) null,shippingZip VARCHAR(75) null,shippingCountry VARCHAR(75) null,shippingPhone VARCHAR(75) null,ccName VARCHAR(75) null,ccType VARCHAR(75) null,ccNumber VARCHAR(75) null,ccExpMonth INTEGER,ccExpYear INTEGER,ccVerNumber VARCHAR(75) null,comments STRING null,ppTxnId VARCHAR(75) null,ppPaymentStatus VARCHAR(75) null,ppPaymentGross DOUBLE,ppReceiverEmail VARCHAR(75) null,ppPayerEmail VARCHAR(75) null,sendOrderEmail BOOLEAN,sendShippingEmail BOOLEAN)";
	public static final String TABLE_SQL_DROP = "drop table ShoppingOrder";
	public static final boolean CACHE_ENABLED = GetterUtil.getBoolean(PropsUtil.get(
				"value.object.finder.cache.enabled.com.liferay.portlet.shopping.model.ShoppingOrder"),
			true);
	public static final long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingOrder"));

	public ShoppingOrderModelImpl() {
	}

	public long getPrimaryKey() {
		return _orderId;
	}

	public void setPrimaryKey(long pk) {
		setOrderId(pk);
	}

	public Serializable getPrimaryKeyObj() {
		return new Long(_orderId);
	}

	public long getOrderId() {
		return _orderId;
	}

	public void setOrderId(long orderId) {
		if (orderId != _orderId) {
			_orderId = orderId;
		}
	}

	public long getGroupId() {
		return _groupId;
	}

	public void setGroupId(long groupId) {
		if (groupId != _groupId) {
			_groupId = groupId;
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

	public String getNumber() {
		return GetterUtil.getString(_number);
	}

	public void setNumber(String number) {
		if (((number == null) && (_number != null)) ||
				((number != null) && (_number == null)) ||
				((number != null) && (_number != null) &&
				!number.equals(_number))) {
			_number = number;
		}
	}

	public double getTax() {
		return _tax;
	}

	public void setTax(double tax) {
		if (tax != _tax) {
			_tax = tax;
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

	public String getAltShipping() {
		return GetterUtil.getString(_altShipping);
	}

	public void setAltShipping(String altShipping) {
		if (((altShipping == null) && (_altShipping != null)) ||
				((altShipping != null) && (_altShipping == null)) ||
				((altShipping != null) && (_altShipping != null) &&
				!altShipping.equals(_altShipping))) {
			_altShipping = altShipping;
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

	public boolean getInsure() {
		return _insure;
	}

	public boolean isInsure() {
		return _insure;
	}

	public void setInsure(boolean insure) {
		if (insure != _insure) {
			_insure = insure;
		}
	}

	public double getInsurance() {
		return _insurance;
	}

	public void setInsurance(double insurance) {
		if (insurance != _insurance) {
			_insurance = insurance;
		}
	}

	public String getCouponCodes() {
		return GetterUtil.getString(_couponCodes);
	}

	public void setCouponCodes(String couponCodes) {
		if (((couponCodes == null) && (_couponCodes != null)) ||
				((couponCodes != null) && (_couponCodes == null)) ||
				((couponCodes != null) && (_couponCodes != null) &&
				!couponCodes.equals(_couponCodes))) {
			_couponCodes = couponCodes;
		}
	}

	public double getCouponDiscount() {
		return _couponDiscount;
	}

	public void setCouponDiscount(double couponDiscount) {
		if (couponDiscount != _couponDiscount) {
			_couponDiscount = couponDiscount;
		}
	}

	public String getBillingFirstName() {
		return GetterUtil.getString(_billingFirstName);
	}

	public void setBillingFirstName(String billingFirstName) {
		if (((billingFirstName == null) && (_billingFirstName != null)) ||
				((billingFirstName != null) && (_billingFirstName == null)) ||
				((billingFirstName != null) && (_billingFirstName != null) &&
				!billingFirstName.equals(_billingFirstName))) {
			_billingFirstName = billingFirstName;
		}
	}

	public String getBillingLastName() {
		return GetterUtil.getString(_billingLastName);
	}

	public void setBillingLastName(String billingLastName) {
		if (((billingLastName == null) && (_billingLastName != null)) ||
				((billingLastName != null) && (_billingLastName == null)) ||
				((billingLastName != null) && (_billingLastName != null) &&
				!billingLastName.equals(_billingLastName))) {
			_billingLastName = billingLastName;
		}
	}

	public String getBillingEmailAddress() {
		return GetterUtil.getString(_billingEmailAddress);
	}

	public void setBillingEmailAddress(String billingEmailAddress) {
		if (((billingEmailAddress == null) && (_billingEmailAddress != null)) ||
				((billingEmailAddress != null) &&
				(_billingEmailAddress == null)) ||
				((billingEmailAddress != null) &&
				(_billingEmailAddress != null) &&
				!billingEmailAddress.equals(_billingEmailAddress))) {
			_billingEmailAddress = billingEmailAddress;
		}
	}

	public String getBillingCompany() {
		return GetterUtil.getString(_billingCompany);
	}

	public void setBillingCompany(String billingCompany) {
		if (((billingCompany == null) && (_billingCompany != null)) ||
				((billingCompany != null) && (_billingCompany == null)) ||
				((billingCompany != null) && (_billingCompany != null) &&
				!billingCompany.equals(_billingCompany))) {
			_billingCompany = billingCompany;
		}
	}

	public String getBillingStreet() {
		return GetterUtil.getString(_billingStreet);
	}

	public void setBillingStreet(String billingStreet) {
		if (((billingStreet == null) && (_billingStreet != null)) ||
				((billingStreet != null) && (_billingStreet == null)) ||
				((billingStreet != null) && (_billingStreet != null) &&
				!billingStreet.equals(_billingStreet))) {
			_billingStreet = billingStreet;
		}
	}

	public String getBillingCity() {
		return GetterUtil.getString(_billingCity);
	}

	public void setBillingCity(String billingCity) {
		if (((billingCity == null) && (_billingCity != null)) ||
				((billingCity != null) && (_billingCity == null)) ||
				((billingCity != null) && (_billingCity != null) &&
				!billingCity.equals(_billingCity))) {
			_billingCity = billingCity;
		}
	}

	public String getBillingState() {
		return GetterUtil.getString(_billingState);
	}

	public void setBillingState(String billingState) {
		if (((billingState == null) && (_billingState != null)) ||
				((billingState != null) && (_billingState == null)) ||
				((billingState != null) && (_billingState != null) &&
				!billingState.equals(_billingState))) {
			_billingState = billingState;
		}
	}

	public String getBillingZip() {
		return GetterUtil.getString(_billingZip);
	}

	public void setBillingZip(String billingZip) {
		if (((billingZip == null) && (_billingZip != null)) ||
				((billingZip != null) && (_billingZip == null)) ||
				((billingZip != null) && (_billingZip != null) &&
				!billingZip.equals(_billingZip))) {
			_billingZip = billingZip;
		}
	}

	public String getBillingCountry() {
		return GetterUtil.getString(_billingCountry);
	}

	public void setBillingCountry(String billingCountry) {
		if (((billingCountry == null) && (_billingCountry != null)) ||
				((billingCountry != null) && (_billingCountry == null)) ||
				((billingCountry != null) && (_billingCountry != null) &&
				!billingCountry.equals(_billingCountry))) {
			_billingCountry = billingCountry;
		}
	}

	public String getBillingPhone() {
		return GetterUtil.getString(_billingPhone);
	}

	public void setBillingPhone(String billingPhone) {
		if (((billingPhone == null) && (_billingPhone != null)) ||
				((billingPhone != null) && (_billingPhone == null)) ||
				((billingPhone != null) && (_billingPhone != null) &&
				!billingPhone.equals(_billingPhone))) {
			_billingPhone = billingPhone;
		}
	}

	public boolean getShipToBilling() {
		return _shipToBilling;
	}

	public boolean isShipToBilling() {
		return _shipToBilling;
	}

	public void setShipToBilling(boolean shipToBilling) {
		if (shipToBilling != _shipToBilling) {
			_shipToBilling = shipToBilling;
		}
	}

	public String getShippingFirstName() {
		return GetterUtil.getString(_shippingFirstName);
	}

	public void setShippingFirstName(String shippingFirstName) {
		if (((shippingFirstName == null) && (_shippingFirstName != null)) ||
				((shippingFirstName != null) && (_shippingFirstName == null)) ||
				((shippingFirstName != null) && (_shippingFirstName != null) &&
				!shippingFirstName.equals(_shippingFirstName))) {
			_shippingFirstName = shippingFirstName;
		}
	}

	public String getShippingLastName() {
		return GetterUtil.getString(_shippingLastName);
	}

	public void setShippingLastName(String shippingLastName) {
		if (((shippingLastName == null) && (_shippingLastName != null)) ||
				((shippingLastName != null) && (_shippingLastName == null)) ||
				((shippingLastName != null) && (_shippingLastName != null) &&
				!shippingLastName.equals(_shippingLastName))) {
			_shippingLastName = shippingLastName;
		}
	}

	public String getShippingEmailAddress() {
		return GetterUtil.getString(_shippingEmailAddress);
	}

	public void setShippingEmailAddress(String shippingEmailAddress) {
		if (((shippingEmailAddress == null) && (_shippingEmailAddress != null)) ||
				((shippingEmailAddress != null) &&
				(_shippingEmailAddress == null)) ||
				((shippingEmailAddress != null) &&
				(_shippingEmailAddress != null) &&
				!shippingEmailAddress.equals(_shippingEmailAddress))) {
			_shippingEmailAddress = shippingEmailAddress;
		}
	}

	public String getShippingCompany() {
		return GetterUtil.getString(_shippingCompany);
	}

	public void setShippingCompany(String shippingCompany) {
		if (((shippingCompany == null) && (_shippingCompany != null)) ||
				((shippingCompany != null) && (_shippingCompany == null)) ||
				((shippingCompany != null) && (_shippingCompany != null) &&
				!shippingCompany.equals(_shippingCompany))) {
			_shippingCompany = shippingCompany;
		}
	}

	public String getShippingStreet() {
		return GetterUtil.getString(_shippingStreet);
	}

	public void setShippingStreet(String shippingStreet) {
		if (((shippingStreet == null) && (_shippingStreet != null)) ||
				((shippingStreet != null) && (_shippingStreet == null)) ||
				((shippingStreet != null) && (_shippingStreet != null) &&
				!shippingStreet.equals(_shippingStreet))) {
			_shippingStreet = shippingStreet;
		}
	}

	public String getShippingCity() {
		return GetterUtil.getString(_shippingCity);
	}

	public void setShippingCity(String shippingCity) {
		if (((shippingCity == null) && (_shippingCity != null)) ||
				((shippingCity != null) && (_shippingCity == null)) ||
				((shippingCity != null) && (_shippingCity != null) &&
				!shippingCity.equals(_shippingCity))) {
			_shippingCity = shippingCity;
		}
	}

	public String getShippingState() {
		return GetterUtil.getString(_shippingState);
	}

	public void setShippingState(String shippingState) {
		if (((shippingState == null) && (_shippingState != null)) ||
				((shippingState != null) && (_shippingState == null)) ||
				((shippingState != null) && (_shippingState != null) &&
				!shippingState.equals(_shippingState))) {
			_shippingState = shippingState;
		}
	}

	public String getShippingZip() {
		return GetterUtil.getString(_shippingZip);
	}

	public void setShippingZip(String shippingZip) {
		if (((shippingZip == null) && (_shippingZip != null)) ||
				((shippingZip != null) && (_shippingZip == null)) ||
				((shippingZip != null) && (_shippingZip != null) &&
				!shippingZip.equals(_shippingZip))) {
			_shippingZip = shippingZip;
		}
	}

	public String getShippingCountry() {
		return GetterUtil.getString(_shippingCountry);
	}

	public void setShippingCountry(String shippingCountry) {
		if (((shippingCountry == null) && (_shippingCountry != null)) ||
				((shippingCountry != null) && (_shippingCountry == null)) ||
				((shippingCountry != null) && (_shippingCountry != null) &&
				!shippingCountry.equals(_shippingCountry))) {
			_shippingCountry = shippingCountry;
		}
	}

	public String getShippingPhone() {
		return GetterUtil.getString(_shippingPhone);
	}

	public void setShippingPhone(String shippingPhone) {
		if (((shippingPhone == null) && (_shippingPhone != null)) ||
				((shippingPhone != null) && (_shippingPhone == null)) ||
				((shippingPhone != null) && (_shippingPhone != null) &&
				!shippingPhone.equals(_shippingPhone))) {
			_shippingPhone = shippingPhone;
		}
	}

	public String getCcName() {
		return GetterUtil.getString(_ccName);
	}

	public void setCcName(String ccName) {
		if (((ccName == null) && (_ccName != null)) ||
				((ccName != null) && (_ccName == null)) ||
				((ccName != null) && (_ccName != null) &&
				!ccName.equals(_ccName))) {
			_ccName = ccName;
		}
	}

	public String getCcType() {
		return GetterUtil.getString(_ccType);
	}

	public void setCcType(String ccType) {
		if (((ccType == null) && (_ccType != null)) ||
				((ccType != null) && (_ccType == null)) ||
				((ccType != null) && (_ccType != null) &&
				!ccType.equals(_ccType))) {
			_ccType = ccType;
		}
	}

	public String getCcNumber() {
		return GetterUtil.getString(_ccNumber);
	}

	public void setCcNumber(String ccNumber) {
		if (((ccNumber == null) && (_ccNumber != null)) ||
				((ccNumber != null) && (_ccNumber == null)) ||
				((ccNumber != null) && (_ccNumber != null) &&
				!ccNumber.equals(_ccNumber))) {
			_ccNumber = ccNumber;
		}
	}

	public int getCcExpMonth() {
		return _ccExpMonth;
	}

	public void setCcExpMonth(int ccExpMonth) {
		if (ccExpMonth != _ccExpMonth) {
			_ccExpMonth = ccExpMonth;
		}
	}

	public int getCcExpYear() {
		return _ccExpYear;
	}

	public void setCcExpYear(int ccExpYear) {
		if (ccExpYear != _ccExpYear) {
			_ccExpYear = ccExpYear;
		}
	}

	public String getCcVerNumber() {
		return GetterUtil.getString(_ccVerNumber);
	}

	public void setCcVerNumber(String ccVerNumber) {
		if (((ccVerNumber == null) && (_ccVerNumber != null)) ||
				((ccVerNumber != null) && (_ccVerNumber == null)) ||
				((ccVerNumber != null) && (_ccVerNumber != null) &&
				!ccVerNumber.equals(_ccVerNumber))) {
			_ccVerNumber = ccVerNumber;
		}
	}

	public String getComments() {
		return GetterUtil.getString(_comments);
	}

	public void setComments(String comments) {
		if (((comments == null) && (_comments != null)) ||
				((comments != null) && (_comments == null)) ||
				((comments != null) && (_comments != null) &&
				!comments.equals(_comments))) {
			_comments = comments;
		}
	}

	public String getPpTxnId() {
		return GetterUtil.getString(_ppTxnId);
	}

	public void setPpTxnId(String ppTxnId) {
		if (((ppTxnId == null) && (_ppTxnId != null)) ||
				((ppTxnId != null) && (_ppTxnId == null)) ||
				((ppTxnId != null) && (_ppTxnId != null) &&
				!ppTxnId.equals(_ppTxnId))) {
			_ppTxnId = ppTxnId;
		}
	}

	public String getPpPaymentStatus() {
		return GetterUtil.getString(_ppPaymentStatus);
	}

	public void setPpPaymentStatus(String ppPaymentStatus) {
		if (((ppPaymentStatus == null) && (_ppPaymentStatus != null)) ||
				((ppPaymentStatus != null) && (_ppPaymentStatus == null)) ||
				((ppPaymentStatus != null) && (_ppPaymentStatus != null) &&
				!ppPaymentStatus.equals(_ppPaymentStatus))) {
			_ppPaymentStatus = ppPaymentStatus;
		}
	}

	public double getPpPaymentGross() {
		return _ppPaymentGross;
	}

	public void setPpPaymentGross(double ppPaymentGross) {
		if (ppPaymentGross != _ppPaymentGross) {
			_ppPaymentGross = ppPaymentGross;
		}
	}

	public String getPpReceiverEmail() {
		return GetterUtil.getString(_ppReceiverEmail);
	}

	public void setPpReceiverEmail(String ppReceiverEmail) {
		if (((ppReceiverEmail == null) && (_ppReceiverEmail != null)) ||
				((ppReceiverEmail != null) && (_ppReceiverEmail == null)) ||
				((ppReceiverEmail != null) && (_ppReceiverEmail != null) &&
				!ppReceiverEmail.equals(_ppReceiverEmail))) {
			_ppReceiverEmail = ppReceiverEmail;
		}
	}

	public String getPpPayerEmail() {
		return GetterUtil.getString(_ppPayerEmail);
	}

	public void setPpPayerEmail(String ppPayerEmail) {
		if (((ppPayerEmail == null) && (_ppPayerEmail != null)) ||
				((ppPayerEmail != null) && (_ppPayerEmail == null)) ||
				((ppPayerEmail != null) && (_ppPayerEmail != null) &&
				!ppPayerEmail.equals(_ppPayerEmail))) {
			_ppPayerEmail = ppPayerEmail;
		}
	}

	public boolean getSendOrderEmail() {
		return _sendOrderEmail;
	}

	public boolean isSendOrderEmail() {
		return _sendOrderEmail;
	}

	public void setSendOrderEmail(boolean sendOrderEmail) {
		if (sendOrderEmail != _sendOrderEmail) {
			_sendOrderEmail = sendOrderEmail;
		}
	}

	public boolean getSendShippingEmail() {
		return _sendShippingEmail;
	}

	public boolean isSendShippingEmail() {
		return _sendShippingEmail;
	}

	public void setSendShippingEmail(boolean sendShippingEmail) {
		if (sendShippingEmail != _sendShippingEmail) {
			_sendShippingEmail = sendShippingEmail;
		}
	}

	public ShoppingOrder toEscapedModel() {
		if (isEscapedModel()) {
			return (ShoppingOrder)this;
		}
		else {
			ShoppingOrder model = new ShoppingOrderImpl();

			model.setEscapedModel(true);

			model.setOrderId(getOrderId());
			model.setGroupId(getGroupId());
			model.setCompanyId(getCompanyId());
			model.setUserId(getUserId());
			model.setUserName(Html.escape(getUserName()));
			model.setCreateDate(getCreateDate());
			model.setModifiedDate(getModifiedDate());
			model.setNumber(Html.escape(getNumber()));
			model.setTax(getTax());
			model.setShipping(getShipping());
			model.setAltShipping(Html.escape(getAltShipping()));
			model.setRequiresShipping(getRequiresShipping());
			model.setInsure(getInsure());
			model.setInsurance(getInsurance());
			model.setCouponCodes(Html.escape(getCouponCodes()));
			model.setCouponDiscount(getCouponDiscount());
			model.setBillingFirstName(Html.escape(getBillingFirstName()));
			model.setBillingLastName(Html.escape(getBillingLastName()));
			model.setBillingEmailAddress(Html.escape(getBillingEmailAddress()));
			model.setBillingCompany(Html.escape(getBillingCompany()));
			model.setBillingStreet(Html.escape(getBillingStreet()));
			model.setBillingCity(Html.escape(getBillingCity()));
			model.setBillingState(Html.escape(getBillingState()));
			model.setBillingZip(Html.escape(getBillingZip()));
			model.setBillingCountry(Html.escape(getBillingCountry()));
			model.setBillingPhone(Html.escape(getBillingPhone()));
			model.setShipToBilling(getShipToBilling());
			model.setShippingFirstName(Html.escape(getShippingFirstName()));
			model.setShippingLastName(Html.escape(getShippingLastName()));
			model.setShippingEmailAddress(Html.escape(getShippingEmailAddress()));
			model.setShippingCompany(Html.escape(getShippingCompany()));
			model.setShippingStreet(Html.escape(getShippingStreet()));
			model.setShippingCity(Html.escape(getShippingCity()));
			model.setShippingState(Html.escape(getShippingState()));
			model.setShippingZip(Html.escape(getShippingZip()));
			model.setShippingCountry(Html.escape(getShippingCountry()));
			model.setShippingPhone(Html.escape(getShippingPhone()));
			model.setCcName(Html.escape(getCcName()));
			model.setCcType(Html.escape(getCcType()));
			model.setCcNumber(Html.escape(getCcNumber()));
			model.setCcExpMonth(getCcExpMonth());
			model.setCcExpYear(getCcExpYear());
			model.setCcVerNumber(Html.escape(getCcVerNumber()));
			model.setComments(Html.escape(getComments()));
			model.setPpTxnId(Html.escape(getPpTxnId()));
			model.setPpPaymentStatus(Html.escape(getPpPaymentStatus()));
			model.setPpPaymentGross(getPpPaymentGross());
			model.setPpReceiverEmail(Html.escape(getPpReceiverEmail()));
			model.setPpPayerEmail(Html.escape(getPpPayerEmail()));
			model.setSendOrderEmail(getSendOrderEmail());
			model.setSendShippingEmail(getSendShippingEmail());

			model = (ShoppingOrder)Proxy.newProxyInstance(ShoppingOrder.class.getClassLoader(),
					new Class[] { ShoppingOrder.class },
					new ReadOnlyBeanHandler(model));

			return model;
		}
	}

	public Object clone() {
		ShoppingOrderImpl clone = new ShoppingOrderImpl();

		clone.setOrderId(getOrderId());
		clone.setGroupId(getGroupId());
		clone.setCompanyId(getCompanyId());
		clone.setUserId(getUserId());
		clone.setUserName(getUserName());
		clone.setCreateDate(getCreateDate());
		clone.setModifiedDate(getModifiedDate());
		clone.setNumber(getNumber());
		clone.setTax(getTax());
		clone.setShipping(getShipping());
		clone.setAltShipping(getAltShipping());
		clone.setRequiresShipping(getRequiresShipping());
		clone.setInsure(getInsure());
		clone.setInsurance(getInsurance());
		clone.setCouponCodes(getCouponCodes());
		clone.setCouponDiscount(getCouponDiscount());
		clone.setBillingFirstName(getBillingFirstName());
		clone.setBillingLastName(getBillingLastName());
		clone.setBillingEmailAddress(getBillingEmailAddress());
		clone.setBillingCompany(getBillingCompany());
		clone.setBillingStreet(getBillingStreet());
		clone.setBillingCity(getBillingCity());
		clone.setBillingState(getBillingState());
		clone.setBillingZip(getBillingZip());
		clone.setBillingCountry(getBillingCountry());
		clone.setBillingPhone(getBillingPhone());
		clone.setShipToBilling(getShipToBilling());
		clone.setShippingFirstName(getShippingFirstName());
		clone.setShippingLastName(getShippingLastName());
		clone.setShippingEmailAddress(getShippingEmailAddress());
		clone.setShippingCompany(getShippingCompany());
		clone.setShippingStreet(getShippingStreet());
		clone.setShippingCity(getShippingCity());
		clone.setShippingState(getShippingState());
		clone.setShippingZip(getShippingZip());
		clone.setShippingCountry(getShippingCountry());
		clone.setShippingPhone(getShippingPhone());
		clone.setCcName(getCcName());
		clone.setCcType(getCcType());
		clone.setCcNumber(getCcNumber());
		clone.setCcExpMonth(getCcExpMonth());
		clone.setCcExpYear(getCcExpYear());
		clone.setCcVerNumber(getCcVerNumber());
		clone.setComments(getComments());
		clone.setPpTxnId(getPpTxnId());
		clone.setPpPaymentStatus(getPpPaymentStatus());
		clone.setPpPaymentGross(getPpPaymentGross());
		clone.setPpReceiverEmail(getPpReceiverEmail());
		clone.setPpPayerEmail(getPpPayerEmail());
		clone.setSendOrderEmail(getSendOrderEmail());
		clone.setSendShippingEmail(getSendShippingEmail());

		return clone;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingOrderImpl shoppingOrder = (ShoppingOrderImpl)obj;

		int value = 0;

		value = DateUtil.compareTo(getCreateDate(),
				shoppingOrder.getCreateDate());

		value = value * -1;

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		ShoppingOrderImpl shoppingOrder = null;

		try {
			shoppingOrder = (ShoppingOrderImpl)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		long pk = shoppingOrder.getPrimaryKey();

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

	private long _orderId;
	private long _groupId;
	private long _companyId;
	private long _userId;
	private String _userName;
	private Date _createDate;
	private Date _modifiedDate;
	private String _number;
	private double _tax;
	private double _shipping;
	private String _altShipping;
	private boolean _requiresShipping;
	private boolean _insure;
	private double _insurance;
	private String _couponCodes;
	private double _couponDiscount;
	private String _billingFirstName;
	private String _billingLastName;
	private String _billingEmailAddress;
	private String _billingCompany;
	private String _billingStreet;
	private String _billingCity;
	private String _billingState;
	private String _billingZip;
	private String _billingCountry;
	private String _billingPhone;
	private boolean _shipToBilling;
	private String _shippingFirstName;
	private String _shippingLastName;
	private String _shippingEmailAddress;
	private String _shippingCompany;
	private String _shippingStreet;
	private String _shippingCity;
	private String _shippingState;
	private String _shippingZip;
	private String _shippingCountry;
	private String _shippingPhone;
	private String _ccName;
	private String _ccType;
	private String _ccNumber;
	private int _ccExpMonth;
	private int _ccExpYear;
	private String _ccVerNumber;
	private String _comments;
	private String _ppTxnId;
	private String _ppPaymentStatus;
	private double _ppPaymentGross;
	private String _ppReceiverEmail;
	private String _ppPayerEmail;
	private boolean _sendOrderEmail;
	private boolean _sendShippingEmail;
}