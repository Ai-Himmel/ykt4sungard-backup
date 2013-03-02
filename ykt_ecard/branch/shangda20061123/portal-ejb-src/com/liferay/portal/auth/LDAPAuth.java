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

package com.liferay.portal.auth;

import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.UserLocalServiceUtil;

import java.util.Date;
import java.util.Locale;

/**
 * <a href="LDAPAuth.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.16 $
 *
 */
public class LDAPAuth implements Authenticator {

	public int authenticateByEmailAddress(
			String companyId, String emailAddress, String password)
		throws AuthException {

		try {

			// Check the LDAP server to ensure the company id, email address,
			// and password is valid

			boolean success = true;

			if (success) {

				// Make sure the user has a portal account

				User user = null;

				try {
					user = UserLocalServiceUtil.getUserByEmailAddress(
						companyId, emailAddress);
				}
				catch (NoSuchUserException nsue) {

					// Grab attributes from LDAP

					boolean autoUserId = true;
					String userId = "";
					boolean autoPassword = false;
					String password1 = password;
					String password2 = password;
					boolean passwordReset = false;
					String firstName = "";
					String middleName = "";
					String lastName = "";
					String nickName = "";
					boolean male = true;
					Date birthday = new Date();
					Locale locale = Locale.US;

					/*
					user = UserLocalServiceUtil.addUser(
						companyId, autoUserId, userId, autoPassword, password1,
						password2, passwordReset, firstName, middleName,
						lastName, nickName, male, birthday, emailAddress,
						locale);
					*/
				}

				return SUCCESS;
			}
			else {
				return FAILURE;
			}
		}
		catch (Exception e) {
			throw new AuthException(e);
		}
	}

	public int authenticateByUserId(
			String companyId, String userId, String password)
		throws AuthException {

		try {

			// Check the LDAP server to ensure the company id, user id, and
			// password is valid

			boolean success = true;

			if (success) {

				// Make sure the user has a portal account

				User user = null;

				try {
					user = UserLocalServiceUtil.getUserById(companyId, userId);
				}
				catch (NoSuchUserException nsue) {

					// Grab attributes from LDAP

					boolean autoUserId = true;
					boolean autoPassword = false;
					String password1 = password;
					String password2 = password;
					boolean passwordReset = false;
					String firstName = "";
					String middleName = "";
					String lastName = "";
					String nickName = "";
					boolean male = true;
					Date birthday = new Date();
					String emailAddress = "";
					Locale locale = Locale.US;

					/*
					user = UserLocalServiceUtil.addUser(
						companyId, autoUserId, userId, autoPassword, password1,
						password2, passwordReset, firstName, middleName,
						lastName, nickName, male, birthday, emailAddress,
						locale);
					*/
				}

				return SUCCESS;
			}
			else {
				return FAILURE;
			}
		}
		catch (Exception e) {
			throw new AuthException(e);
		}
	}

}