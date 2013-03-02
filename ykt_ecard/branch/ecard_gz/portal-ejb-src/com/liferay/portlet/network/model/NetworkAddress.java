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

package com.liferay.portlet.network.model;

import java.util.Date;

/**
 * <a href="NetworkAddress.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class NetworkAddress extends NetworkAddressModel {

	public static final String NOTIFY_BY_NONE = "none";

	public static final String NOTIFY_BY_EMAIL = "email";

	public static final String NOTIFY_BY_SMS = "sms";

	public static final String NOTIFY_BY_AIM = "aim";

	public static final String NOTIFY_BY_ICQ = "icq";

	public static final String NOTIFY_BY_MSN = "msn";

	public static final String NOTIFY_BY_YM = "ym";

	public NetworkAddress() {
		super();
	}

	public NetworkAddress(String addressId) {
		super(addressId);
	}

	public NetworkAddress(String addressId, String userId, Date createDate,
						  Date modifiedDate, String name, String url,
						  String comments, String content, int status,
						  Date lastUpdated, String notifyBy, long interval,
						  boolean active) {

		super(addressId, userId, createDate, modifiedDate, name, url, comments,
			  content, status, lastUpdated, notifyBy, interval, active);
	}

}