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

package com.liferay.mail.util;

import com.liferay.mail.NoSuchCyrusUserException;
import com.liferay.mail.model.CyrusUser;
import com.liferay.mail.model.CyrusVirtual;
import com.liferay.mail.service.persistence.CyrusUserUtil;
import com.liferay.mail.service.persistence.CyrusVirtualUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.util.FileUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.lang.ProcessUtil;

import java.io.File;
import java.io.IOException;

import java.util.List;

/**
 * <a href="CyrusHook.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class CyrusHook implements Hook {

	public void addForward(String userId, List emailAddresses) {
		try {
			if (emailAddresses != null) {
				String home = PropsUtil.get(PropsUtil.MAIL_HOOK_CYRUS_HOME);

				File file = new File(home + "/" + userId + ".procmail.forward");

				if (emailAddresses.size() > 0) {
					FastStringBuffer sb = new FastStringBuffer();
					sb.append(":0\n");
					sb.append("!");

					for (int i = 0; i < emailAddresses.size(); i++) {
						String emailAddress = (String)emailAddresses.get(i);
						sb.append(" ").append(emailAddress);
					}

					sb.append("\n");

					FileUtil.write(file, sb.toString());
				}
				else {
					file.delete();
				}
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public void addUser(
		String userId, String password, String firstName, String middleName,
		String lastName, String emailAddress) {

		try {

			// User

			CyrusUser user = new CyrusUser(userId, password);

			CyrusUserUtil.update(user);

			// Virtual

			CyrusVirtual virtual = new CyrusVirtual(emailAddress, userId);

			CyrusVirtualUtil.update(virtual);

			// Expect

			String addUserCmd =
				PropsUtil.get(PropsUtil.MAIL_HOOK_CYRUS_ADD_USER);

			addUserCmd = StringUtil.replace(addUserCmd, "%1%", userId);

			Runtime rt = Runtime.getRuntime();

			Process p = rt.exec(addUserCmd);

			ProcessUtil.close(p);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void addVacationMessage(
		String userId, String emailAddress, String vacationMessage) {

		try {
			String home = PropsUtil.get(PropsUtil.MAIL_HOOK_CYRUS_HOME);

			// Remove vacation cache

			new File(home + "/" + userId + ".vacation.cache").delete();

			// Update vacation message

			File vacation = new File(home + "/" + userId + ".vacation");

			if (Validator.isNull(vacationMessage)) {
				vacation.delete();
			}
			else {
				FileUtil.write(vacation, emailAddress + "\n" + vacationMessage);
			}
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public void deleteEmailAddress(String userId) {
		try {
			CyrusVirtualUtil.removeByUserId(userId);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void deleteUser(String userId) {
		try {

			// User

			try {
				CyrusUserUtil.remove(userId);
			}
			catch (NoSuchCyrusUserException nscue) {
			}

			// Virtual

			CyrusVirtualUtil.removeByUserId(userId);

			// Expect

			String deleteUserCmd =
				PropsUtil.get(PropsUtil.MAIL_HOOK_CYRUS_DELETE_USER);

			deleteUserCmd = StringUtil.replace(deleteUserCmd, "%1%", userId);

			Runtime rt = Runtime.getRuntime();

			Process p = rt.exec(deleteUserCmd);

			ProcessUtil.close(p);

			// Procmail

			String home = PropsUtil.get(PropsUtil.MAIL_HOOK_CYRUS_HOME);

			File file = new File(home + "/" + userId + ".procmail.blocked");

			if (file.exists()) {
				file.delete();
			}

			file = new File(home + "/" + userId + ".procmail.forward");

			if (file.exists()) {
				file.delete();
			}

			file = new File(home + "/" + userId + ".vacation");

			if (file.exists()) {
				file.delete();
			}

			file = new File(home + "/" + userId + ".vacation.cache");

			if (file.exists()) {
				file.delete();
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void updateBlocked(String userId, List blocked) {
		String home = PropsUtil.get(PropsUtil.MAIL_HOOK_CYRUS_HOME);

		File file = new File(home + "/" + userId + ".procmail.blocked");

		if ((blocked == null) || (blocked.size() == 0)) {
			file.delete();

			return;
		}

		FastStringBuffer sb = new FastStringBuffer();

		for (int i = 0; i < blocked.size(); i++) {
			String emailAddress = (String)blocked.get(i);

			sb.append("\n");
			sb.append(":0\n");
			sb.append("* ^From.*").append(emailAddress).append("\n");
			sb.append("{\n");
			sb.append(":0\n");
			sb.append("/dev/null\n");
			sb.append("}\n");
		}

		try {
			FileUtil.write(file, sb.toString());
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}

	public void updateEmailAddress(String userId, String emailAddress) {
		try {
			CyrusVirtualUtil.removeByUserId(userId);

			CyrusVirtual virtual = new CyrusVirtual(emailAddress, userId);

			CyrusVirtualUtil.update(virtual);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	public void updatePassword(String userId, String password) {
		CyrusUser user = null;

		try {
			user = CyrusUserUtil.findByPrimaryKey(userId);
		}
		catch (NoSuchCyrusUserException nscue) {
			user = new CyrusUser(userId, password);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		try {
			user.setPassword(password);

			CyrusUserUtil.update(user);
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

}