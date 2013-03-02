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

package com.liferay.portlet.chat.util;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.lang.IntegerWrapper;

import java.io.IOException;

import java.net.BindException;
import java.net.ServerSocket;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ChatUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class ChatUtil {

	public static int getNextPort() {
		return _instance._getNextPort();
	}

	private ChatUtil() {
		int defaultPort = GetterUtil.get(
			PropsUtil.get(PropsUtil.CHAT_SERVER_DEFAULT_PORT), 7777);

		_port = new IntegerWrapper(defaultPort);
	}

	private synchronized int _getNextPort() {
		ServerSocket socket = null;

		// Do this for at most 100 times

		for (int i = 0; i < 100; i++) {
			try {
				socket = new ServerSocket(_port.getValue());

				break;
			}
			catch (BindException be) {
				if (be.getMessage().startsWith("Address already in use")) {
					_log.warn(
						"Port " + _port.getValue() + " is already in use");

					_port.increment();
				}
				else {
					_log.error(be.getMessage());

					break;
				}
			}
			catch (IOException ioe) {
				ioe.printStackTrace();

				break;
			}
			finally {
				try {
					socket.close();
				}
				catch (Exception e) {
				}
			}
		}

		_log.debug("Using port " + _port.getValue());

		int returnValue = _port.getValue();

		_port.increment();

		return returnValue;
	}

	private static final Log _log = LogFactory.getLog(ChatUtil.class);

	private static ChatUtil _instance = new ChatUtil();

	private IntegerWrapper _port;

}