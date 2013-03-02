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

package com.liferay.portal.im;

import com.liferay.portal.util.PropsUtil;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import rath.msnm.MSNMessenger;
import rath.msnm.UserStatus;

/**
 * <a href="MSNConnector.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brett Randall
 *
 */
public class MSNConnector {

	public static void disconnect() {
		if (_instance != null) {
			_instance._disconnect();
		}
	}

	public static void send(String to, String msg) {
		_instance._send(to, msg);
	}

	private MSNConnector() {
		_login = PropsUtil.get(PropsUtil.MSN_LOGIN);
		_password = PropsUtil.get(PropsUtil.MSN_PASSWORD);

		_msn = new MSNMessenger(_login, _password);
		_msn.setInitialStatus(UserStatus.ONLINE);
	}

	private void _connect() {
		if (!_msn.isLoggedIn()) {
			_msn.login();

			// Spend 5 seconds to attempt to login

			for (int i = 0; i < 50 && !_msn.isLoggedIn(); i++) {
				try {
					Thread.sleep(100);
				}
				catch (InterruptedException e) {
					_log.warn(e);

					break;
				}
			}

			if (!_msn.isLoggedIn()) {
				_log.error("Unable to connect as " + _login);
			}
		}
	}

	private void _disconnect() {
		try {
			if (_msn.isLoggedIn()) {
				_msn.logout();
			}
		}
		catch (Exception e) {
			_log.warn(e);
		}
	}

	private void _send(String to, String msg) {
		_connect();

		_msn.addMsnListener(new MSNMessageAdapter(_msn, to, msg));

		try {
			Thread.sleep(1500);

			_msn.doCallWait(to);
		}
		catch (Exception e) {
			_log.warn(e);
		}
	}

	private static Log _log = LogFactory.getLog(MSNConnector.class);

	private static MSNConnector _instance = new MSNConnector();

	private String _login;
	private String _password;
	private MSNMessenger _msn;

}