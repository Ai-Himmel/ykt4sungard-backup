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

import com.liferay.portlet.shopping.model.ShoppingCoupon;
import com.liferay.util.cal.CalendarUtil;

import java.util.Date;

/**
 * <a href="ShoppingCouponImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ShoppingCouponImpl
	extends ShoppingCouponModelImpl implements ShoppingCoupon {

	public static final String[] DISCOUNT_TYPES = {
		"percentage", "actual", "free-shipping", "tax-free"
	};

	public static final String DISCOUNT_TYPE_PERCENTAGE = "percentage";

	public static final String DISCOUNT_TYPE_ACTUAL = "actual";

	public static final String DISCOUNT_TYPE_FREE_SHIPPING = "free-shipping";

	public static final String DISCOUNT_TYPE_TAX_FREE = "tax-free";

	public ShoppingCouponImpl() {
	}

	public boolean hasValidStartDate() {
		Date now = new Date();

		if (CalendarUtil.beforeByDay(now, getStartDate())) {
			return false;
		}
		else {
			return true;
		}
	}

	public boolean hasValidEndDate() {
		if (getEndDate() != null) {
			Date now = new Date();

			if (now.after(getEndDate())) {
				return false;
			}
		}

		return true;
	}

	public boolean hasValidDateRange() {
		if (hasValidStartDate() && hasValidEndDate()) {
			return true;
		}
		else {
			return false;
		}
	}

}