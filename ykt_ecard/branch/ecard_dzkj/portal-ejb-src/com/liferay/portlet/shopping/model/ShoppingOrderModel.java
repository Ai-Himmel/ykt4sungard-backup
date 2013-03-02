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
 * <a href="ShoppingOrderModel.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.81 $
 *
 */
public class ShoppingOrderModel extends BaseModel {
	public static boolean CACHEABLE = GetterUtil.get(PropsUtil.get(
				"value.object.cacheable.com.liferay.portlet.shopping.model.ShoppingOrder"),
			VALUE_OBJECT_CACHEABLE);
	public static int MAX_SIZE = GetterUtil.get(PropsUtil.get(
				"value.object.max.size.com.liferay.portlet.shopping.model.ShoppingOrder"),
			VALUE_OBJECT_MAX_SIZE);
	public static boolean XSS_ALLOW_BY_MODEL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder"),
			XSS_ALLOW);
	public static boolean XSS_ALLOW_ORDERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.orderId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMPANYID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.companyId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_USERID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.userId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_ALTSHIPPING = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.altShipping"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COUPONIDS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.couponIds"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGFIRSTNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingFirstName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGLASTNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingLastName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGEMAILADDRESS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingEmailAddress"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGCOMPANY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingCompany"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGSTREET = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingStreet"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGCITY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingCity"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGSTATE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingState"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGZIP = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingZip"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGCOUNTRY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingCountry"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_BILLINGPHONE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.billingPhone"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGFIRSTNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingFirstName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGLASTNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingLastName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGEMAILADDRESS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingEmailAddress"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGCOMPANY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingCompany"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGSTREET = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingStreet"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGCITY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingCity"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGSTATE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingState"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGZIP = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingZip"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGCOUNTRY = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingCountry"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_SHIPPINGPHONE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.shippingPhone"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CCNAME = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ccName"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CCTYPE = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ccType"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CCNUMBER = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ccNumber"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_CCVERNUMBER = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ccVerNumber"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_COMMENTS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.comments"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PPTXNID = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ppTxnId"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PPPAYMENTSTATUS = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ppPaymentStatus"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PPRECEIVEREMAIL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ppReceiverEmail"),
			XSS_ALLOW_BY_MODEL);
	public static boolean XSS_ALLOW_PPPAYEREMAIL = GetterUtil.get(PropsUtil.get(
				"xss.allow.com.liferay.portlet.shopping.model.ShoppingOrder.ppPayerEmail"),
			XSS_ALLOW_BY_MODEL);
	public static long LOCK_EXPIRATION_TIME = GetterUtil.getLong(PropsUtil.get(
				"lock.expiration.time.com.liferay.portlet.shopping.model.ShoppingOrderModel"));

	public ShoppingOrderModel() {
	}

	public ShoppingOrderModel(String orderId) {
		_orderId = orderId;
		setNew(true);
	}

	public ShoppingOrderModel(String orderId, String companyId, String userId,
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

	public String getOrderId() {
		return _orderId;
	}

	public void setOrderId(String orderId) {
		if (((orderId == null) && (_orderId != null)) ||
				((orderId != null) && (_orderId == null)) ||
				((orderId != null) && (_orderId != null) &&
				!orderId.equals(_orderId))) {
			if (!XSS_ALLOW_ORDERID) {
				orderId = Xss.strip(orderId);
			}

			_orderId = orderId;
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

	public String getUserId() {
		return _userId;
	}

	public void setUserId(String userId) {
		if (((userId == null) && (_userId != null)) ||
				((userId != null) && (_userId == null)) ||
				((userId != null) && (_userId != null) &&
				!userId.equals(_userId))) {
			if (!XSS_ALLOW_USERID) {
				userId = Xss.strip(userId);
			}

			_userId = userId;
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

	public double getTax() {
		return _tax;
	}

	public void setTax(double tax) {
		if (tax != _tax) {
			_tax = tax;
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

	public String getAltShipping() {
		return _altShipping;
	}

	public void setAltShipping(String altShipping) {
		if (((altShipping == null) && (_altShipping != null)) ||
				((altShipping != null) && (_altShipping == null)) ||
				((altShipping != null) && (_altShipping != null) &&
				!altShipping.equals(_altShipping))) {
			if (!XSS_ALLOW_ALTSHIPPING) {
				altShipping = Xss.strip(altShipping);
			}

			_altShipping = altShipping;
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

	public boolean getInsure() {
		return _insure;
	}

	public boolean isInsure() {
		return _insure;
	}

	public void setInsure(boolean insure) {
		if (insure != _insure) {
			_insure = insure;
			setModified(true);
		}
	}

	public double getInsurance() {
		return _insurance;
	}

	public void setInsurance(double insurance) {
		if (insurance != _insurance) {
			_insurance = insurance;
			setModified(true);
		}
	}

	public String getCouponIds() {
		return _couponIds;
	}

	public void setCouponIds(String couponIds) {
		if (((couponIds == null) && (_couponIds != null)) ||
				((couponIds != null) && (_couponIds == null)) ||
				((couponIds != null) && (_couponIds != null) &&
				!couponIds.equals(_couponIds))) {
			if (!XSS_ALLOW_COUPONIDS) {
				couponIds = Xss.strip(couponIds);
			}

			_couponIds = couponIds;
			setModified(true);
		}
	}

	public double getCouponDiscount() {
		return _couponDiscount;
	}

	public void setCouponDiscount(double couponDiscount) {
		if (couponDiscount != _couponDiscount) {
			_couponDiscount = couponDiscount;
			setModified(true);
		}
	}

	public String getBillingFirstName() {
		return _billingFirstName;
	}

	public void setBillingFirstName(String billingFirstName) {
		if (((billingFirstName == null) && (_billingFirstName != null)) ||
				((billingFirstName != null) && (_billingFirstName == null)) ||
				((billingFirstName != null) && (_billingFirstName != null) &&
				!billingFirstName.equals(_billingFirstName))) {
			if (!XSS_ALLOW_BILLINGFIRSTNAME) {
				billingFirstName = Xss.strip(billingFirstName);
			}

			_billingFirstName = billingFirstName;
			setModified(true);
		}
	}

	public String getBillingLastName() {
		return _billingLastName;
	}

	public void setBillingLastName(String billingLastName) {
		if (((billingLastName == null) && (_billingLastName != null)) ||
				((billingLastName != null) && (_billingLastName == null)) ||
				((billingLastName != null) && (_billingLastName != null) &&
				!billingLastName.equals(_billingLastName))) {
			if (!XSS_ALLOW_BILLINGLASTNAME) {
				billingLastName = Xss.strip(billingLastName);
			}

			_billingLastName = billingLastName;
			setModified(true);
		}
	}

	public String getBillingEmailAddress() {
		return _billingEmailAddress;
	}

	public void setBillingEmailAddress(String billingEmailAddress) {
		if (((billingEmailAddress == null) && (_billingEmailAddress != null)) ||
				((billingEmailAddress != null) &&
				(_billingEmailAddress == null)) ||
				((billingEmailAddress != null) &&
				(_billingEmailAddress != null) &&
				!billingEmailAddress.equals(_billingEmailAddress))) {
			if (!XSS_ALLOW_BILLINGEMAILADDRESS) {
				billingEmailAddress = Xss.strip(billingEmailAddress);
			}

			_billingEmailAddress = billingEmailAddress;
			setModified(true);
		}
	}

	public String getBillingCompany() {
		return _billingCompany;
	}

	public void setBillingCompany(String billingCompany) {
		if (((billingCompany == null) && (_billingCompany != null)) ||
				((billingCompany != null) && (_billingCompany == null)) ||
				((billingCompany != null) && (_billingCompany != null) &&
				!billingCompany.equals(_billingCompany))) {
			if (!XSS_ALLOW_BILLINGCOMPANY) {
				billingCompany = Xss.strip(billingCompany);
			}

			_billingCompany = billingCompany;
			setModified(true);
		}
	}

	public String getBillingStreet() {
		return _billingStreet;
	}

	public void setBillingStreet(String billingStreet) {
		if (((billingStreet == null) && (_billingStreet != null)) ||
				((billingStreet != null) && (_billingStreet == null)) ||
				((billingStreet != null) && (_billingStreet != null) &&
				!billingStreet.equals(_billingStreet))) {
			if (!XSS_ALLOW_BILLINGSTREET) {
				billingStreet = Xss.strip(billingStreet);
			}

			_billingStreet = billingStreet;
			setModified(true);
		}
	}

	public String getBillingCity() {
		return _billingCity;
	}

	public void setBillingCity(String billingCity) {
		if (((billingCity == null) && (_billingCity != null)) ||
				((billingCity != null) && (_billingCity == null)) ||
				((billingCity != null) && (_billingCity != null) &&
				!billingCity.equals(_billingCity))) {
			if (!XSS_ALLOW_BILLINGCITY) {
				billingCity = Xss.strip(billingCity);
			}

			_billingCity = billingCity;
			setModified(true);
		}
	}

	public String getBillingState() {
		return _billingState;
	}

	public void setBillingState(String billingState) {
		if (((billingState == null) && (_billingState != null)) ||
				((billingState != null) && (_billingState == null)) ||
				((billingState != null) && (_billingState != null) &&
				!billingState.equals(_billingState))) {
			if (!XSS_ALLOW_BILLINGSTATE) {
				billingState = Xss.strip(billingState);
			}

			_billingState = billingState;
			setModified(true);
		}
	}

	public String getBillingZip() {
		return _billingZip;
	}

	public void setBillingZip(String billingZip) {
		if (((billingZip == null) && (_billingZip != null)) ||
				((billingZip != null) && (_billingZip == null)) ||
				((billingZip != null) && (_billingZip != null) &&
				!billingZip.equals(_billingZip))) {
			if (!XSS_ALLOW_BILLINGZIP) {
				billingZip = Xss.strip(billingZip);
			}

			_billingZip = billingZip;
			setModified(true);
		}
	}

	public String getBillingCountry() {
		return _billingCountry;
	}

	public void setBillingCountry(String billingCountry) {
		if (((billingCountry == null) && (_billingCountry != null)) ||
				((billingCountry != null) && (_billingCountry == null)) ||
				((billingCountry != null) && (_billingCountry != null) &&
				!billingCountry.equals(_billingCountry))) {
			if (!XSS_ALLOW_BILLINGCOUNTRY) {
				billingCountry = Xss.strip(billingCountry);
			}

			_billingCountry = billingCountry;
			setModified(true);
		}
	}

	public String getBillingPhone() {
		return _billingPhone;
	}

	public void setBillingPhone(String billingPhone) {
		if (((billingPhone == null) && (_billingPhone != null)) ||
				((billingPhone != null) && (_billingPhone == null)) ||
				((billingPhone != null) && (_billingPhone != null) &&
				!billingPhone.equals(_billingPhone))) {
			if (!XSS_ALLOW_BILLINGPHONE) {
				billingPhone = Xss.strip(billingPhone);
			}

			_billingPhone = billingPhone;
			setModified(true);
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
			setModified(true);
		}
	}

	public String getShippingFirstName() {
		return _shippingFirstName;
	}

	public void setShippingFirstName(String shippingFirstName) {
		if (((shippingFirstName == null) && (_shippingFirstName != null)) ||
				((shippingFirstName != null) && (_shippingFirstName == null)) ||
				((shippingFirstName != null) && (_shippingFirstName != null) &&
				!shippingFirstName.equals(_shippingFirstName))) {
			if (!XSS_ALLOW_SHIPPINGFIRSTNAME) {
				shippingFirstName = Xss.strip(shippingFirstName);
			}

			_shippingFirstName = shippingFirstName;
			setModified(true);
		}
	}

	public String getShippingLastName() {
		return _shippingLastName;
	}

	public void setShippingLastName(String shippingLastName) {
		if (((shippingLastName == null) && (_shippingLastName != null)) ||
				((shippingLastName != null) && (_shippingLastName == null)) ||
				((shippingLastName != null) && (_shippingLastName != null) &&
				!shippingLastName.equals(_shippingLastName))) {
			if (!XSS_ALLOW_SHIPPINGLASTNAME) {
				shippingLastName = Xss.strip(shippingLastName);
			}

			_shippingLastName = shippingLastName;
			setModified(true);
		}
	}

	public String getShippingEmailAddress() {
		return _shippingEmailAddress;
	}

	public void setShippingEmailAddress(String shippingEmailAddress) {
		if (((shippingEmailAddress == null) && (_shippingEmailAddress != null)) ||
				((shippingEmailAddress != null) &&
				(_shippingEmailAddress == null)) ||
				((shippingEmailAddress != null) &&
				(_shippingEmailAddress != null) &&
				!shippingEmailAddress.equals(_shippingEmailAddress))) {
			if (!XSS_ALLOW_SHIPPINGEMAILADDRESS) {
				shippingEmailAddress = Xss.strip(shippingEmailAddress);
			}

			_shippingEmailAddress = shippingEmailAddress;
			setModified(true);
		}
	}

	public String getShippingCompany() {
		return _shippingCompany;
	}

	public void setShippingCompany(String shippingCompany) {
		if (((shippingCompany == null) && (_shippingCompany != null)) ||
				((shippingCompany != null) && (_shippingCompany == null)) ||
				((shippingCompany != null) && (_shippingCompany != null) &&
				!shippingCompany.equals(_shippingCompany))) {
			if (!XSS_ALLOW_SHIPPINGCOMPANY) {
				shippingCompany = Xss.strip(shippingCompany);
			}

			_shippingCompany = shippingCompany;
			setModified(true);
		}
	}

	public String getShippingStreet() {
		return _shippingStreet;
	}

	public void setShippingStreet(String shippingStreet) {
		if (((shippingStreet == null) && (_shippingStreet != null)) ||
				((shippingStreet != null) && (_shippingStreet == null)) ||
				((shippingStreet != null) && (_shippingStreet != null) &&
				!shippingStreet.equals(_shippingStreet))) {
			if (!XSS_ALLOW_SHIPPINGSTREET) {
				shippingStreet = Xss.strip(shippingStreet);
			}

			_shippingStreet = shippingStreet;
			setModified(true);
		}
	}

	public String getShippingCity() {
		return _shippingCity;
	}

	public void setShippingCity(String shippingCity) {
		if (((shippingCity == null) && (_shippingCity != null)) ||
				((shippingCity != null) && (_shippingCity == null)) ||
				((shippingCity != null) && (_shippingCity != null) &&
				!shippingCity.equals(_shippingCity))) {
			if (!XSS_ALLOW_SHIPPINGCITY) {
				shippingCity = Xss.strip(shippingCity);
			}

			_shippingCity = shippingCity;
			setModified(true);
		}
	}

	public String getShippingState() {
		return _shippingState;
	}

	public void setShippingState(String shippingState) {
		if (((shippingState == null) && (_shippingState != null)) ||
				((shippingState != null) && (_shippingState == null)) ||
				((shippingState != null) && (_shippingState != null) &&
				!shippingState.equals(_shippingState))) {
			if (!XSS_ALLOW_SHIPPINGSTATE) {
				shippingState = Xss.strip(shippingState);
			}

			_shippingState = shippingState;
			setModified(true);
		}
	}

	public String getShippingZip() {
		return _shippingZip;
	}

	public void setShippingZip(String shippingZip) {
		if (((shippingZip == null) && (_shippingZip != null)) ||
				((shippingZip != null) && (_shippingZip == null)) ||
				((shippingZip != null) && (_shippingZip != null) &&
				!shippingZip.equals(_shippingZip))) {
			if (!XSS_ALLOW_SHIPPINGZIP) {
				shippingZip = Xss.strip(shippingZip);
			}

			_shippingZip = shippingZip;
			setModified(true);
		}
	}

	public String getShippingCountry() {
		return _shippingCountry;
	}

	public void setShippingCountry(String shippingCountry) {
		if (((shippingCountry == null) && (_shippingCountry != null)) ||
				((shippingCountry != null) && (_shippingCountry == null)) ||
				((shippingCountry != null) && (_shippingCountry != null) &&
				!shippingCountry.equals(_shippingCountry))) {
			if (!XSS_ALLOW_SHIPPINGCOUNTRY) {
				shippingCountry = Xss.strip(shippingCountry);
			}

			_shippingCountry = shippingCountry;
			setModified(true);
		}
	}

	public String getShippingPhone() {
		return _shippingPhone;
	}

	public void setShippingPhone(String shippingPhone) {
		if (((shippingPhone == null) && (_shippingPhone != null)) ||
				((shippingPhone != null) && (_shippingPhone == null)) ||
				((shippingPhone != null) && (_shippingPhone != null) &&
				!shippingPhone.equals(_shippingPhone))) {
			if (!XSS_ALLOW_SHIPPINGPHONE) {
				shippingPhone = Xss.strip(shippingPhone);
			}

			_shippingPhone = shippingPhone;
			setModified(true);
		}
	}

	public String getCcName() {
		return _ccName;
	}

	public void setCcName(String ccName) {
		if (((ccName == null) && (_ccName != null)) ||
				((ccName != null) && (_ccName == null)) ||
				((ccName != null) && (_ccName != null) &&
				!ccName.equals(_ccName))) {
			if (!XSS_ALLOW_CCNAME) {
				ccName = Xss.strip(ccName);
			}

			_ccName = ccName;
			setModified(true);
		}
	}

	public String getCcType() {
		return _ccType;
	}

	public void setCcType(String ccType) {
		if (((ccType == null) && (_ccType != null)) ||
				((ccType != null) && (_ccType == null)) ||
				((ccType != null) && (_ccType != null) &&
				!ccType.equals(_ccType))) {
			if (!XSS_ALLOW_CCTYPE) {
				ccType = Xss.strip(ccType);
			}

			_ccType = ccType;
			setModified(true);
		}
	}

	public String getCcNumber() {
		return _ccNumber;
	}

	public void setCcNumber(String ccNumber) {
		if (((ccNumber == null) && (_ccNumber != null)) ||
				((ccNumber != null) && (_ccNumber == null)) ||
				((ccNumber != null) && (_ccNumber != null) &&
				!ccNumber.equals(_ccNumber))) {
			if (!XSS_ALLOW_CCNUMBER) {
				ccNumber = Xss.strip(ccNumber);
			}

			_ccNumber = ccNumber;
			setModified(true);
		}
	}

	public int getCcExpMonth() {
		return _ccExpMonth;
	}

	public void setCcExpMonth(int ccExpMonth) {
		if (ccExpMonth != _ccExpMonth) {
			_ccExpMonth = ccExpMonth;
			setModified(true);
		}
	}

	public int getCcExpYear() {
		return _ccExpYear;
	}

	public void setCcExpYear(int ccExpYear) {
		if (ccExpYear != _ccExpYear) {
			_ccExpYear = ccExpYear;
			setModified(true);
		}
	}

	public String getCcVerNumber() {
		return _ccVerNumber;
	}

	public void setCcVerNumber(String ccVerNumber) {
		if (((ccVerNumber == null) && (_ccVerNumber != null)) ||
				((ccVerNumber != null) && (_ccVerNumber == null)) ||
				((ccVerNumber != null) && (_ccVerNumber != null) &&
				!ccVerNumber.equals(_ccVerNumber))) {
			if (!XSS_ALLOW_CCVERNUMBER) {
				ccVerNumber = Xss.strip(ccVerNumber);
			}

			_ccVerNumber = ccVerNumber;
			setModified(true);
		}
	}

	public String getComments() {
		return _comments;
	}

	public void setComments(String comments) {
		if (((comments == null) && (_comments != null)) ||
				((comments != null) && (_comments == null)) ||
				((comments != null) && (_comments != null) &&
				!comments.equals(_comments))) {
			if (!XSS_ALLOW_COMMENTS) {
				comments = Xss.strip(comments);
			}

			_comments = comments;
			setModified(true);
		}
	}

	public String getPpTxnId() {
		return _ppTxnId;
	}

	public void setPpTxnId(String ppTxnId) {
		if (((ppTxnId == null) && (_ppTxnId != null)) ||
				((ppTxnId != null) && (_ppTxnId == null)) ||
				((ppTxnId != null) && (_ppTxnId != null) &&
				!ppTxnId.equals(_ppTxnId))) {
			if (!XSS_ALLOW_PPTXNID) {
				ppTxnId = Xss.strip(ppTxnId);
			}

			_ppTxnId = ppTxnId;
			setModified(true);
		}
	}

	public String getPpPaymentStatus() {
		return _ppPaymentStatus;
	}

	public void setPpPaymentStatus(String ppPaymentStatus) {
		if (((ppPaymentStatus == null) && (_ppPaymentStatus != null)) ||
				((ppPaymentStatus != null) && (_ppPaymentStatus == null)) ||
				((ppPaymentStatus != null) && (_ppPaymentStatus != null) &&
				!ppPaymentStatus.equals(_ppPaymentStatus))) {
			if (!XSS_ALLOW_PPPAYMENTSTATUS) {
				ppPaymentStatus = Xss.strip(ppPaymentStatus);
			}

			_ppPaymentStatus = ppPaymentStatus;
			setModified(true);
		}
	}

	public double getPpPaymentGross() {
		return _ppPaymentGross;
	}

	public void setPpPaymentGross(double ppPaymentGross) {
		if (ppPaymentGross != _ppPaymentGross) {
			_ppPaymentGross = ppPaymentGross;
			setModified(true);
		}
	}

	public String getPpReceiverEmail() {
		return _ppReceiverEmail;
	}

	public void setPpReceiverEmail(String ppReceiverEmail) {
		if (((ppReceiverEmail == null) && (_ppReceiverEmail != null)) ||
				((ppReceiverEmail != null) && (_ppReceiverEmail == null)) ||
				((ppReceiverEmail != null) && (_ppReceiverEmail != null) &&
				!ppReceiverEmail.equals(_ppReceiverEmail))) {
			if (!XSS_ALLOW_PPRECEIVEREMAIL) {
				ppReceiverEmail = Xss.strip(ppReceiverEmail);
			}

			_ppReceiverEmail = ppReceiverEmail;
			setModified(true);
		}
	}

	public String getPpPayerEmail() {
		return _ppPayerEmail;
	}

	public void setPpPayerEmail(String ppPayerEmail) {
		if (((ppPayerEmail == null) && (_ppPayerEmail != null)) ||
				((ppPayerEmail != null) && (_ppPayerEmail == null)) ||
				((ppPayerEmail != null) && (_ppPayerEmail != null) &&
				!ppPayerEmail.equals(_ppPayerEmail))) {
			if (!XSS_ALLOW_PPPAYEREMAIL) {
				ppPayerEmail = Xss.strip(ppPayerEmail);
			}

			_ppPayerEmail = ppPayerEmail;
			setModified(true);
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
			setModified(true);
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
			setModified(true);
		}
	}

	public BaseModel getProtected() {
		return null;
	}

	public void protect() {
	}

	public Object clone() {
		return new ShoppingOrder(getOrderId(), getCompanyId(), getUserId(),
			getCreateDate(), getModifiedDate(), getTax(), getShipping(),
			getAltShipping(), getRequiresShipping(), getInsure(),
			getInsurance(), getCouponIds(), getCouponDiscount(),
			getBillingFirstName(), getBillingLastName(),
			getBillingEmailAddress(), getBillingCompany(), getBillingStreet(),
			getBillingCity(), getBillingState(), getBillingZip(),
			getBillingCountry(), getBillingPhone(), getShipToBilling(),
			getShippingFirstName(), getShippingLastName(),
			getShippingEmailAddress(), getShippingCompany(),
			getShippingStreet(), getShippingCity(), getShippingState(),
			getShippingZip(), getShippingCountry(), getShippingPhone(),
			getCcName(), getCcType(), getCcNumber(), getCcExpMonth(),
			getCcExpYear(), getCcVerNumber(), getComments(), getPpTxnId(),
			getPpPaymentStatus(), getPpPaymentGross(), getPpReceiverEmail(),
			getPpPayerEmail(), getSendOrderEmail(), getSendShippingEmail());
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		ShoppingOrder shoppingOrder = (ShoppingOrder)obj;
		int value = 0;
		value = getCreateDate().compareTo(shoppingOrder.getCreateDate());
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

		ShoppingOrder shoppingOrder = null;

		try {
			shoppingOrder = (ShoppingOrder)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String pk = shoppingOrder.getPrimaryKey();

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