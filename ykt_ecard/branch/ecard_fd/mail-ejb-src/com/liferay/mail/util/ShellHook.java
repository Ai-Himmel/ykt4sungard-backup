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

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.lang.ProcessUtil;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ShellHook.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Lawrence
 * @version $Revision: 1.3 $
 *
 */
public class ShellHook implements Hook {

	public static String SHELL_SCRIPT =
		PropsUtil.get(PropsUtil.MAIL_HOOK_SHELL_SCRIPT);

	public void addForward(String userId, List emailAddresses) {
		_execute(
			new String[] {
				SHELL_SCRIPT, "addForward", userId,
				StringUtil.merge(emailAddresses)
			}
		);
	}

	public void addUser(
		String userId, String password, String firstName, String middleName,
		String lastName, String emailAddress) {

		_execute(
			new String[] {
				SHELL_SCRIPT, "addUser", userId, password, firstName,
				middleName, lastName, emailAddress
			}
		);
	}

	public void addVacationMessage(
		String userId, String emailAddress, String vacationMessage) {

		_execute(
			new String[] {
				SHELL_SCRIPT, "addVacationMessage", userId, emailAddress,
				vacationMessage
			}
		);
	}

	public void deleteEmailAddress(String userId) {
		_execute(
			new String[] {
				SHELL_SCRIPT, "deleteEmailAddress", userId
			}
		);
	}

	public void deleteUser(String userId) {
		_execute(
			new String[] {
				SHELL_SCRIPT, "deleteUser", userId
			}
		);
	}

	public void updateBlocked(String userId, List blocked) {
		_execute(
			new String[] {
				SHELL_SCRIPT, "updateBlocked", userId, StringUtil.merge(blocked)
			}
		);
	}

	public void updateEmailAddress(String userId, String emailAddress) {
		_execute(
			new String[] {
				SHELL_SCRIPT, "updateEmailAddress", userId, emailAddress
			}
		);
	}

	public void updatePassword(String userId, String password) {
		_execute(
			new String[] {
				SHELL_SCRIPT, "updatePassword", userId, password
		});
	}

	private void _execute(String cmdLine[]) {
		for (int i = 0; i < cmdLine.length; i++) {
			if (cmdLine[i].trim().length() == 0) {
				cmdLine[i] = StringPool.UNDERLINE;
			}
		}

		try {
	 		Runtime rt = Runtime.getRuntime();

			Process p = rt.exec(cmdLine);

			ProcessUtil.close(p);

			int exitValue = p.exitValue();

			if (exitValue != 0) {
				FastStringBuffer cmd = new FastStringBuffer();

				for (int i = 0; i < cmdLine.length; i++) {
					cmd.append(cmdLine[i]);
					cmd.append(StringPool.SPACE);
				}

				throw new IllegalArgumentException(cmd.toString());
			}
		}
		catch (Exception e) {
			_log.error(e.getMessage());
		}
	}

	private static final Log _log = LogFactory.getLog(ShellHook.class);

}