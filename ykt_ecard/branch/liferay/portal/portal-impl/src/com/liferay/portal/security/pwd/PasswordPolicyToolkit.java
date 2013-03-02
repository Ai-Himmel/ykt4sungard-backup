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

package com.liferay.portal.security.pwd;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.UserPasswordException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.model.User;
import com.liferay.portal.service.PasswordTrackerLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.words.util.WordsUtil;
import com.liferay.util.PwdGenerator;

import java.util.Date;

/**
 * <a href="PasswordPolicyToolkit.java.html"><b><i>View Source</i></b></a>
 *
 * @author Scott Lee
 *
 */
public class PasswordPolicyToolkit extends BasicToolkit {

	public String generate() {
		String generator = GetterUtil.getString(PropsUtil.get(
			PropsUtil.PASSWORDS_PASSWORDPOLICYTOOLKIT_GENERATOR));

		if (generator.equals("static")) {
			String password = GetterUtil.getString(PropsUtil.get(
				PropsUtil.PASSWORDS_PASSWORDPOLICYTOOLKIT_STATIC));

			return password;
		}
		else {
			return PwdGenerator.getPassword();
		}
	}

	public void validate(
			long userId, String password1, String password2,
			PasswordPolicy passwordPolicy)
		throws PortalException, SystemException {

		if (passwordPolicy.getCheckSyntax()) {
			if (!passwordPolicy.getAllowDictionaryWords() &&
					WordsUtil.isDictionaryWord(password1)) {

				throw new UserPasswordException(
					UserPasswordException.PASSWORD_CONTAINS_TRIVIAL_WORDS);
			}

			if (password1.length() < passwordPolicy.getMinLength()) {
				throw new UserPasswordException(
					UserPasswordException.PASSWORD_LENGTH);
			}
		}

//		if (!passwordPolicy.getChangeable()) {
//			throw new UserPasswordException(
//				UserPasswordException.PASSWORD_NOT_CHANGEABLE);
//		}

		if (userId != 0) {
			if (passwordPolicy.getChangeable()) {
				User user = UserLocalServiceUtil.getUserById(userId);

				Date passwordModfiedDate = user.getPasswordModifiedDate();

				if (passwordModfiedDate != null) {

					// LEP-2961

					Date now = new Date();

					long passwordModificationElapsedTime =
						now.getTime() - passwordModfiedDate.getTime();

					long userCreationElapsedTime =
						now.getTime() - user.getCreateDate().getTime();

					long minAge = passwordPolicy.getMinAge() * 1000;

					if ((passwordModificationElapsedTime < minAge) &&
						(userCreationElapsedTime > minAge)) {

						throw new UserPasswordException(
							UserPasswordException.PASSWORD_TOO_YOUNG);
					}
				}
			}

			if (PasswordTrackerLocalServiceUtil.isSameAsCurrentPassword(
					userId, password1)) {

				throw new UserPasswordException(
					UserPasswordException.PASSWORD_SAME_AS_CURRENT);
			}
			else if (!PasswordTrackerLocalServiceUtil.isValidPassword(
						userId, password1)) {

				throw new UserPasswordException(
					UserPasswordException.PASSWORD_ALREADY_USED);
			}
		}
	}

}