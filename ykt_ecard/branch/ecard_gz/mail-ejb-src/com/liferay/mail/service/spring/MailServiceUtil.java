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

package com.liferay.mail.service.spring;

import com.liferay.portal.SystemException;
import com.liferay.util.mail.MailMessage;

import java.util.List;

/**
 * <a href="MailServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class MailServiceUtil {

	public static void addForward(String userId, List emailAddresses)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.addForward(userId, emailAddresses);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void addUser(
			String userId, String password, String firstName, String middleName,
			String lastName, String emailAddress)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.addUser(
				userId, password, firstName, middleName, lastName,
				emailAddress);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void addVacationMessage(
			String userId, String emailAddress, String vacationMessage)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.addVacationMessage(
				userId, emailAddress, vacationMessage);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void deleteEmailAddress(String userId)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.deleteEmailAddress(userId);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void deleteUser(String userId) throws SystemException {
		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.deleteUser(userId);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void sendEmail(MailMessage mailMessage)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.sendEmail(mailMessage);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void updateBlocked(String userId, List blocked)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.updateBlocked(userId, blocked);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void updateEmailAddress(String userId, String emailAddress)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.updateEmailAddress(userId, emailAddress);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void updatePassword(String userId, String password)
		throws SystemException {

		try {
			MailService mailService = MailServiceFactory.getService();

			mailService.updatePassword(userId, password);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

}