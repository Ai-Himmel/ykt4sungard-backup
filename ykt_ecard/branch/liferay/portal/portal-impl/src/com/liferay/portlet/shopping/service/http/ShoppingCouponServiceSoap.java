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

package com.liferay.portlet.shopping.service.http;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;

import com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil;

import java.rmi.RemoteException;

/**
 * <a href="ShoppingCouponServiceSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class provides a SOAP utility for the
 * <code>com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil</code> service
 * utility. The static methods of this class calls the same methods of the
 * service utility. However, the signatures are different because it is
 * difficult for SOAP to support certain types.
 * </p>
 *
 * <p>
 * ServiceBuilder follows certain rules in translating the methods. For example,
 * if the method in the service utility returns a <code>java.util.List</code>,
 * that is translated to an array of
 * <code>com.liferay.portlet.shopping.model.ShoppingCouponSoap</code>. If the method in the
 * service utility returns a <code>com.liferay.portlet.shopping.model.ShoppingCoupon</code>,
 * that is translated to a <code>com.liferay.portlet.shopping.model.ShoppingCouponSoap</code>.
 * Methods that SOAP cannot safely wire are skipped.
 * </p>
 *
 * <p>
 * The benefits of using the SOAP utility is that it is cross platform
 * compatible. SOAP allows different languages like Java, .NET, C++, PHP, and
 * even Perl, to call the generated services. One drawback of SOAP is that it is
 * slow because it needs to serialize all calls into a text format (XML).
 * </p>
 *
 * <p>
 * You can see a list of services at
 * http://localhost:8080/tunnel-web/secure/axis. Set the property
 * <code>tunnel.servlet.hosts.allowed</code> in portal.properties to configure
 * security.
 * </p>
 *
 * <p>
 * The SOAP utility is only generated for remote services.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portlet.shopping.service.ShoppingCouponServiceUtil
 * @see com.liferay.portlet.shopping.service.http.ShoppingCouponServiceHttp
 * @see com.liferay.portlet.shopping.service.model.ShoppingCouponSoap
 *
 */
public class ShoppingCouponServiceSoap {
	public static com.liferay.portlet.shopping.model.ShoppingCouponSoap addCoupon(
		long plid, java.lang.String code, boolean autoCode,
		java.lang.String name, java.lang.String description,
		int startDateMonth, int startDateDay, int startDateYear,
		int startDateHour, int startDateMinute, int endDateMonth,
		int endDateDay, int endDateYear, int endDateHour, int endDateMinute,
		boolean neverExpire, boolean active, java.lang.String limitCategories,
		java.lang.String limitSkus, double minOrder, double discount,
		java.lang.String discountType) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCoupon returnValue = ShoppingCouponServiceUtil.addCoupon(plid,
					code, autoCode, name, description, startDateMonth,
					startDateDay, startDateYear, startDateHour,
					startDateMinute, endDateMonth, endDateDay, endDateYear,
					endDateHour, endDateMinute, neverExpire, active,
					limitCategories, limitSkus, minOrder, discount, discountType);

			return com.liferay.portlet.shopping.model.ShoppingCouponSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static void deleteCoupon(long plid, long couponId)
		throws RemoteException {
		try {
			ShoppingCouponServiceUtil.deleteCoupon(plid, couponId);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponSoap getCoupon(
		long plid, long couponId) throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCoupon returnValue = ShoppingCouponServiceUtil.getCoupon(plid,
					couponId);

			return com.liferay.portlet.shopping.model.ShoppingCouponSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponSoap[] search(
		long plid, long companyId, java.lang.String code, boolean active,
		java.lang.String discountType, boolean andOperator, int begin, int end)
		throws RemoteException {
		try {
			java.util.List returnValue = ShoppingCouponServiceUtil.search(plid,
					companyId, code, active, discountType, andOperator, begin,
					end);

			return com.liferay.portlet.shopping.model.ShoppingCouponSoap.toSoapModels(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	public static com.liferay.portlet.shopping.model.ShoppingCouponSoap updateCoupon(
		long plid, long couponId, java.lang.String name,
		java.lang.String description, int startDateMonth, int startDateDay,
		int startDateYear, int startDateHour, int startDateMinute,
		int endDateMonth, int endDateDay, int endDateYear, int endDateHour,
		int endDateMinute, boolean neverExpire, boolean active,
		java.lang.String limitCategories, java.lang.String limitSkus,
		double minOrder, double discount, java.lang.String discountType)
		throws RemoteException {
		try {
			com.liferay.portlet.shopping.model.ShoppingCoupon returnValue = ShoppingCouponServiceUtil.updateCoupon(plid,
					couponId, name, description, startDateMonth, startDateDay,
					startDateYear, startDateHour, startDateMinute,
					endDateMonth, endDateDay, endDateYear, endDateHour,
					endDateMinute, neverExpire, active, limitCategories,
					limitSkus, minOrder, discount, discountType);

			return com.liferay.portlet.shopping.model.ShoppingCouponSoap.toSoapModel(returnValue);
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new RemoteException(e.getMessage());
		}
	}

	private static Log _log = LogFactoryUtil.getLog(ShoppingCouponServiceSoap.class);
}