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
 * <a href="ShoppingOrderHBM.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ShoppingOrderHBM {
	protected ShoppingOrderHBM() {
	}

	protected ShoppingOrderHBM(String orderId) {
		_orderId = orderId;
	}

	protected ShoppingOrderHBM(String orderId, String companyId, String userId,
		Date createDate, Date modifiedDate, double tax, double shipping,
		String altShipping, boolean requiresShipping, boolean insure,
		double insurance, String couponIds, double couponDiscount,
		String billingFirstName, String billingLastName,
		String billingEmailAddress, String billingCompany,
		String billingStreet, String billingCity, String billingState,
		String billingZip, String billingCountry, String billingPhone,
		boolean shipToBilling, String shippingFirstName,
		String shippingLastName, String shippingEmailAddress,
		String shippingCompany, String shippingStreet, String shippingCity,
		String shippingState, String shippingZip, String shippingCountry,
		String shippingPhone, String ccName, String ccType, String ccNumber,
		int ccExpMonth, int ccExpYear, String ccVerNumber, String comments,
		String ppTxnId, String ppPaymentStatus, double ppPaymentGross,
		String ppReceiverEmail, String ppPayerEmail, boolean sendOrderEmail,
		boolean sendShippingEmail) {
		_orderId = orderId;
		_companyId = companyId;
		_userId = userId;
		_createDate = createDate;
		_modifiedDate = modifiedDate;
		_tax = tax;
		_shipping = shipping;
		_altShipping = altShipping;
		_requiresShipping = requiresShipping;
		_insure = insure;
		_insurance = insurance;
		_couponIds = couponIds;
		_couponDiscount = couponDiscount;
		_billingFirstName = billingFirstName;
		_billingLastName = billingLastName;
		_billingEmailAddress = billingEmailAddress;
		_billingCompany = billingCompany;
		_billingStreet = billingStreet;
		_billingCity = billingCity;
		_billingState = billingState;
		_billingZip = billingZip;
		_billingCountry = billingCountry;
		_billingPhone = billingPhone;
		_shipToBilling = shipToBilling;
		_shippingFirstName = shippingFirstName;
		_shippingLastName = shippingLastName;
		_shippingEmailAddress = shippingEmailAddress;
		_shippingCompany = shippingCompany;
		_shippingStreet = shippingStreet;
		_shippingCity = shippingCity;
		_shippingState = shippingState;
		_shippingZip = shippingZip;
		_shippingCountry = shippingCountry;
		_shippingPhone = shippingPhone;
		_ccName = ccName;
		_ccType = ccType;
		_ccNumber = ccNumber;
		_ccExpMonth = ccExpMonth;
		_ccExpYear = ccExpYear;
		_ccVerNumber = ccVerNumber;
		_comments = comments;
		_ppTxnId = ppTxnId;
		_ppPaymentStatus = ppPaymentStatus;
		_ppPaymentGross = ppPaymentGross;
		_ppReceiverEmail = ppReceiverEmail;
		_ppPayerEmail = ppPayerEmail;
		_sendOrderEmail = sendOrderEmail;
		_sendShippingEmail = sendShippingEmail;
	}

	public String getPrimaryKey() {
		return _orderId;
	}

	protected void setPrimaryKey(String pk) {
		_orderId = pk;
	}

	protected String getOrderId() {
		return _orderId;
	}

	protected void setOrderId(String orderId) {
		_orderId = orderId;
	}

	protected String getCompanyId() {
		return _companyId;
	}

	protected void setCompanyId(String companyId) {
		_companyId = companyId;
	}

	protected String getUserId() {
		return _userId;
	}

	protected void setUserId(String userId) {
		_userId = userId;
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

	protected double getTax() {
		return _tax;
	}

	protected void setTax(double tax) {
		_tax = tax;
	}

	protected double getShipping() {
		return _shipping;
	}

	protected void setShipping(double shipping) {
		_shipping = shipping;
	}

	protected String getAltShipping() {
		return _altShipping;
	}

	protected void setAltShipping(String altShipping) {
		_altShipping = altShipping;
	}

	protected boolean getRequiresShipping() {
		return _requiresShipping;
	}

	protected void setRequiresShipping(boolean requiresShipping) {
		_requiresShipping = requiresShipping;
	}

	protected boolean getInsure() {
		return _insure;
	}

	protected void setInsure(boolean insure) {
		_insure = insure;
	}

	protected double getInsurance() {
		return _insurance;
	}

	protected void setInsurance(double insurance) {
		_insurance = insurance;
	}

	protected String getCouponIds() {
		return _couponIds;
	}

	protected void setCouponIds(String couponIds) {
		_couponIds = couponIds;
	}

	protected double getCouponDiscount() {
		return _couponDiscount;
	}

	protected void setCouponDiscount(double couponDiscount) {
		_couponDiscount = couponDiscount;
	}

	protected String getBillingFirstName() {
		return _billingFirstName;
	}

	protected void setBillingFirstName(String billingFirstName) {
		_billingFirstName = billingFirstName;
	}

	protected String getBillingLastName() {
		return _billingLastName;
	}

	protected void setBillingLastName(String billingLastName) {
		_billingLastName = billingLastName;
	}

	protected String getBillingEmailAddress() {
		return _billingEmailAddress;
	}

	protected void setBillingEmailAddress(String billingEmailAddress) {
		_billingEmailAddress = billingEmailAddress;
	}

	protected String getBillingCompany() {
		return _billingCompany;
	}

	protected void setBillingCompany(String billingCompany) {
		_billingCompany = billingCompany;
	}

	protected String getBillingStreet() {
		return _billingStreet;
	}

	protected void setBillingStreet(String billingStreet) {
		_billingStreet = billingStreet;
	}

	protected String getBillingCity() {
		return _billingCity;
	}

	protected void setBillingCity(String billingCity) {
		_billingCity = billingCity;
	}

	protected String getBillingState() {
		return _billingState;
	}

	protected void setBillingState(String billingState) {
		_billingState = billingState;
	}

	protected String getBillingZip() {
		return _billingZip;
	}

	protected void setBillingZip(String billingZip) {
		_billingZip = billingZip;
	}

	protected String getBillingCountry() {
		return _billingCountry;
	}

	protected void setBillingCountry(String billingCountry) {
		_billingCountry = billingCountry;
	}

	protected String getBillingPhone() {
		return _billingPhone;
	}

	protected void setBillingPhone(String billingPhone) {
		_billingPhone = billingPhone;
	}

	protected boolean getShipToBilling() {
		return _shipToBilling;
	}

	protected void setShipToBilling(boolean shipToBilling) {
		_shipToBilling = shipToBilling;
	}

	protected String getShippingFirstName() {
		return _shippingFirstName;
	}

	protected void setShippingFirstName(String shippingFirstName) {
		_shippingFirstName = shippingFirstName;
	}

	protected String getShippingLastName() {
		return _shippingLastName;
	}

	protected void setShippingLastName(String shippingLastName) {
		_shippingLastName = shippingLastName;
	}

	protected String getShippingEmailAddress() {
		return _shippingEmailAddress;
	}

	protected void setShippingEmailAddress(String shippingEmailAddress) {
		_shippingEmailAddress = shippingEmailAddress;
	}

	protected String getShippingCompany() {
		return _shippingCompany;
	}

	protected void setShippingCompany(String shippingCompany) {
		_shippingCompany = shippingCompany;
	}

	protected String getShippingStreet() {
		return _shippingStreet;
	}

	protected void setShippingStreet(String shippingStreet) {
		_shippingStreet = shippingStreet;
	}

	protected String getShippingCity() {
		return _shippingCity;
	}

	protected void setShippingCity(String shippingCity) {
		_shippingCity = shippingCity;
	}

	protected String getShippingState() {
		return _shippingState;
	}

	protected void setShippingState(String shippingState) {
		_shippingState = shippingState;
	}

	protected String getShippingZip() {
		return _shippingZip;
	}

	protected void setShippingZip(String shippingZip) {
		_shippingZip = shippingZip;
	}

	protected String getShippingCountry() {
		return _shippingCountry;
	}

	protected void setShippingCountry(String shippingCountry) {
		_shippingCountry = shippingCountry;
	}

	protected String getShippingPhone() {
		return _shippingPhone;
	}

	protected void setShippingPhone(String shippingPhone) {
		_shippingPhone = shippingPhone;
	}

	protected String getCcName() {
		return _ccName;
	}

	protected void setCcName(String ccName) {
		_ccName = ccName;
	}

	protected String getCcType() {
		return _ccType;
	}

	protected void setCcType(String ccType) {
		_ccType = ccType;
	}

	protected String getCcNumber() {
		return _ccNumber;
	}

	protected void setCcNumber(String ccNumber) {
		_ccNumber = ccNumber;
	}

	protected int getCcExpMonth() {
		return _ccExpMonth;
	}

	protected void setCcExpMonth(int ccExpMonth) {
		_ccExpMonth = ccExpMonth;
	}

	protected int getCcExpYear() {
		return _ccExpYear;
	}

	protected void setCcExpYear(int ccExpYear) {
		_ccExpYear = ccExpYear;
	}

	protected String getCcVerNumber() {
		return _ccVerNumber;
	}

	protected void setCcVerNumber(String ccVerNumber) {
		_ccVerNumber = ccVerNumber;
	}

	protected String getComments() {
		return _comments;
	}

	protected void setComments(String comments) {
		_comments = comments;
	}

	protected String getPpTxnId() {
		return _ppTxnId;
	}

	protected void setPpTxnId(String ppTxnId) {
		_ppTxnId = ppTxnId;
	}

	protected String getPpPaymentStatus() {
		return _ppPaymentStatus;
	}

	protected void setPpPaymentStatus(String ppPaymentStatus) {
		_ppPaymentStatus = ppPaymentStatus;
	}

	protected double getPpPaymentGross() {
		return _ppPaymentGross;
	}

	protected void setPpPaymentGross(double ppPaymentGross) {
		_ppPaymentGross = ppPaymentGross;
	}

	protected String getPpReceiverEmail() {
		return _ppReceiverEmail;
	}

	protected void setPpReceiverEmail(String ppReceiverEmail) {
		_ppReceiverEmail = ppReceiverEmail;
	}

	protected String getPpPayerEmail() {
		return _ppPayerEmail;
	}

	protected void setPpPayerEmail(String ppPayerEmail) {
		_ppPayerEmail = ppPayerEmail;
	}

	protected boolean getSendOrderEmail() {
		return _sendOrderEmail;
	}

	protected void setSendOrderEmail(boolean sendOrderEmail) {
		_sendOrderEmail = sendOrderEmail;
	}

	protected boolean getSendShippingEmail() {
		return _sendShippingEmail;
	}

	protected void setSendShippingEmail(boolean sendShippingEmail) {
		_sendShippingEmail = sendShippingEmail;
	}

	private String _orderId;
	private String _companyId;
	private String _userId;
	private Date _createDate;
	private Date _modifiedDate;
	private double _tax;
	private double _shipping;
	private String _altShipping;
	private boolean _requiresShipping;
	private boolean _insure;
	private double _insurance;
	private String _couponIds;
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