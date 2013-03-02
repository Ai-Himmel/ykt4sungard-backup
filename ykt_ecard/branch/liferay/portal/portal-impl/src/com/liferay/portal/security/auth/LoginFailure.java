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
 * <a href="LoginFailure.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Scott Lee
 *
 */
public class LoginFailure implements AuthFailure {

	public void onFailureByEmailAddress(
			long companyId, String emailAddress, Map headerMap,
			Map parameterMap)
		throws AuthException {

		try {
			UserLocalServiceUtil.checkLoginFailureByEmailAddress(
				companyId, emailAddress);
		}
		catch (Exception e) {
			throw new AuthException(e);
		}
	}

	public void onFailureByScreenName(
			long companyId, String screenName, Map headerMap, Map parameterMap)
		throws AuthException {

		try {
			UserLocalServiceUtil.checkLoginFailureByScreenName(
				companyId, screenName);
		}
		catch (Exception e) {
			throw new AuthException(e);
		}
	}

	public void onFailureByUserId(
			long companyId, long userId, Map headerMap, Map parameterMap)
		throws AuthException {

		try {
			UserLocalServiceUtil.checkLoginFailureById(userId);
		}
		catch (Exception e) {
			throw new AuthException(e);
		}
	}

}