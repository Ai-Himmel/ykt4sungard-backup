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

import org.walluck.oscar.AIMConnection;
import org.walluck.oscar.AIMSession;
import org.walluck.oscar.client.Oscar;

/**
 * <a href="AIMConnector.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brett Randall
 * @author Bruno Farache
 *
 */
public class AIMConnector {

	public static void disconnect() {
		if (_instance != null) {
			_instance._disconnect();
		}
	}

	public static void send(String to, String msg) {
		_instance._send(to, msg);
	}

	private AIMConnector() {
	}

	private void _connect() {
		String login = PropsUtil.get(PropsUtil.AIM_LOGIN);
		String password = PropsUtil.get(PropsUtil.AIM_PASSWORD);

		AIMSession ses = new AIMSession();

		ses.setSN(login);

		Oscar oscar = new Oscar();

		oscar.setSN(login);
		oscar.setPassword(password);

		ses.init();
	}

	private void _disconnect() {
		if (_aim != null) {
			AIMConnection.killAllInSess(_aim);
		}
	}

	private void _send(String to, String msg) {
		try {
			if (_aim == null) {
				_connect();

				// Daim's listeners are buggy. Instead, just wait a second
				// before sending the first message.

				Thread.sleep(1000);
			}

			_oscar.sendIM(_aim, to, msg, Oscar.getICQCaps());
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn("Could not send AIM message");
			}
		}
	}

	private static AIMConnector _instance = new AIMConnector();

	private static Log _log = LogFactory.getLog(AIMConnector.class);

	private AIMSession _aim;
	private Oscar _oscar;

}