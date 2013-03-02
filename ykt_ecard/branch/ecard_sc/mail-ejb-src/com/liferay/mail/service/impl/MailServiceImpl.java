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

package com.liferay.mail.service.impl;

import com.liferay.mail.service.jms.MailProducer;
import com.liferay.mail.service.spring.MailService;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.lang.MethodWrapper;
import com.liferay.util.mail.MailMessage;

import java.util.List;

/**
 * <a href="MailServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class MailServiceImpl implements MailService {

	public void addForward(String userId, List emailAddresses) {
		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "addForward", new Object[] {userId, emailAddresses});

		MailProducer.produce(methodWrapper);
	}

	public void addUser(
		String userId, String password, String firstName, String middleName,
		String lastName, String emailAddress) {

		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "addUser",
			new Object[] {
				userId, password, firstName, middleName, lastName, emailAddress
			});

		MailProducer.produce(methodWrapper);
	}

	public void addVacationMessage(
		String userId, String emailAddress, String vacationMessage) {

		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "addVacationMessage",
			new Object[] {
				userId, emailAddress, vacationMessage
			});

		MailProducer.produce(methodWrapper);
	}

	public void deleteEmailAddress(String userId) {
		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "deleteEmailAddress", new Object[] {userId});

		MailProducer.produce(methodWrapper);
	}

	public void deleteUser(String userId) {
		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "deleteUser", new Object[] {userId});

		MailProducer.produce(methodWrapper);
	}

	public void sendEmail(MailMessage mailMessage) {
		MailProducer.produce(mailMessage);
	}

	public void updateBlocked(String userId, List blocked) {
		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "updateBlocked", new Object[] {userId, blocked});

		MailProducer.produce(methodWrapper);
	}

	public void updateEmailAddress(String userId, String emailAddress) {
		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "updateEmailAddress",
			new Object[] {userId, emailAddress});

		MailProducer.produce(methodWrapper);
	}

	public void updatePassword(String userId, String password) {
		String hookImpl = PropsUtil.get(PropsUtil.MAIL_HOOK_IMPL);

		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			userId = StringUtil.replace(userId, ".", "_");
		}

		MethodWrapper methodWrapper = new MethodWrapper(
			hookImpl, "updatePassword", new Object[] {userId, password});

		MailProducer.produce(methodWrapper);
	}

}