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

package com.liferay.portal.security.auth;

import com.liferay.portal.service.UserLocalServiceUtil;

import java.util.Map;

/**
 * <a href="LoginMaxFailures.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Scott Lee
 *
 */
public class LoginMaxFailures implements AuthFailure {

	public void onFailureByEmailAddress(
			long companyId, String emailAddress, Map headerMap,
			Map parameterMap)
		throws AuthException {

		try {
			UserLocalServiceUtil.updateLockoutByEmailAddress(
				companyId, emailAddress, true);
		}
		catch (Exception e) {
			throw new AuthException();
		}
	}

	public void onFailureByScreenName(
			long companyId, String screenName, Map headerMap, Map parameterMap)
		throws AuthException {

		try {
			UserLocalServiceUtil.updateLockoutByScreenName(
				companyId, screenName, true);
		}
		catch (Exception e) {
			throw new AuthException();
		}
	}

	public void onFailureByUserId(
			long companyId, long userId, Map headerMap, Map parameterMap)
		throws AuthException {

		try {
			UserLocalServiceUtil.updateLockoutById(userId, true);
		}
		catch (Exception e) {
			throw new AuthException();
		}
	}

}