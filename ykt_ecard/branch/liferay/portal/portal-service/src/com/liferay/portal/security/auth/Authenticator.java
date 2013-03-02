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

import java.util.Map;

/**
 * <a href="Authenticator.java.html"><b><i>View Source</i></b></a>
 * 
 * @author Brian Wing Shun Chan
 * 
 */
public interface Authenticator {

	public static final int LDAPSUCCESS = 2;

	public static final int LOCALSUCCESS = 3;

	public static final int ECARDSUCCESS = 1;

	public static final int FAILURE = -1;

	public static final int DNE = 0;

	public int authenticateByEmailAddress(long companyId, String emailAddress,
			String password, Map headerMap, Map parameterMap)
			throws AuthException;

	public int authenticateByScreenName(long companyId, String screenName,
			String password, Map headerMap, Map parameterMap)
			throws AuthException;

	public int authenticateByUserId(long companyId, long userId,
			String password, Map headerMap, Map parameterMap)
			throws AuthException;
	
	public int authenticateByEmailAddressSSO(long companyId, String emailAddress)
			throws AuthException;

	public int authenticateByScreenNameSSO(long companyId, String screenName)
			throws AuthException;

	public int authenticateByUserIdSSO(long companyId, long userId)
			throws AuthException;

}