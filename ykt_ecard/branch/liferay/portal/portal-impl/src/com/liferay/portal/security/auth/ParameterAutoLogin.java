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

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="ParameterAutoLogin.java.html"><b><i>View Source</i></b></a>
 *
 * @author Minhchau Dang
 *
 */
public class ParameterAutoLogin implements AutoLogin {

	public String[] login(HttpServletRequest req, HttpServletResponse res)
		throws AutoLoginException {

		try {
			String login = ParamUtil.getString(req, getLoginParam());

			if (Validator.isNull(login)) {
				return null;
			}

			String password = ParamUtil.getString(req, getPasswordParam());

			if (Validator.isNull(password)) {
				return null;
			}

			Company company = PortalUtil.getCompany(req);

			String authType = company.getAuthType();

			long userId = 0;

			if (authType.equals(CompanyImpl.AUTH_TYPE_EA)) {
				userId = UserLocalServiceUtil.getUserIdByEmailAddress(
					company.getCompanyId(), login);
			}
			else if (authType.equals(CompanyImpl.AUTH_TYPE_SN)) {
				userId = UserLocalServiceUtil.getUserIdByScreenName(
					company.getCompanyId(), login);
			}
			else if (authType.equals(CompanyImpl.AUTH_TYPE_ID)) {
				userId = GetterUtil.getLong(login);
			}
			else {
				return null;
			}

			String[] credentials = new String[] {
				String.valueOf(userId), password, Boolean.FALSE.toString()
			};

			return credentials;
		}
		catch (Exception e) {
			throw new AutoLoginException(e);
		}
	}

	protected String getLoginParam() {
		return _LOGIN_PARAM;
	}

	protected String getPasswordParam() {
		return _PASSWORD_PARAM;
	}

	private static final String _LOGIN_PARAM = "parameterAutoLoginLogin";

	private static final String _PASSWORD_PARAM = "parameterAutoLoginPassword";

}