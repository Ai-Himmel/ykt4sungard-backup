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

import com.liferay.portal.kernel.util.MethodCache;
import com.liferay.portal.util.PropsUtil;

import java.io.IOException;

import java.lang.reflect.Method;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="YMConnector.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brett Randall
 * @author Bruno Farache
 *
 */
public class YMConnector {

	public static void disconnect() {
		if (_instance != null) {
			_instance._disconnect();
		}
	}

	public static void send(String to, String msg)
		throws IllegalStateException, IOException {

		_instance._send(to, msg);
	}

	private YMConnector() {
	}

	private void _connect() {
		try {
			_ym = (Object)Class.forName(_SESSION).newInstance();
		}
		catch (Exception e) {
			_jYMSGLibraryFound = false;

			if (_log.isWarnEnabled()) {
				_log.warn(
					"jYMSG library could not be loaded: " + e.getMessage());
			}
		}

		try {
			if (_jYMSGLibraryFound) {
				String login = PropsUtil.get(PropsUtil.YM_LOGIN);
				String password = PropsUtil.get(PropsUtil.YM_PASSWORD);

				Method method = MethodCache.get(
					_SESSION, "login",
					new Class[] {String.class, String.class});

				method.invoke(_ym, new Object[] {login, password});
			}
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	private void _disconnect() {
		try {
			if (_ym != null) {
				Method method = MethodCache.get(_SESSION, "logout");

				method.invoke(_ym, new Object[] {});
			}
		}
		catch (Exception e) {
			if (_log.isWarnEnabled()) {
				_log.warn(e);
			}
		}
	}

	private void _send(String to, String msg)
		throws IllegalStateException , IOException {

		try {
			if (_ym == null) {
				_connect();
			}

			if (_jYMSGLibraryFound) {
				Method method = MethodCache.get(
					_SESSION, "sendMessage",
					new Class[] {String.class, String.class});

				method.invoke(_ym, new Object[] {to, msg});
			}
		}
		catch (Exception e) {
			_log.error(e);
		}
	}

	private static final String _SESSION = "ymsg.network.Session";

	private static Log _log = LogFactory.getLog(YMConnector.class);

	private static YMConnector _instance = new YMConnector();

	private boolean _jYMSGLibraryFound = true;
	private Object _ym;

}