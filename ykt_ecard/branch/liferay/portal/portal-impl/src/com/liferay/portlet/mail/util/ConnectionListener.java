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

package com.liferay.portlet.mail.util;

import javax.mail.event.ConnectionEvent;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ConnectionListener.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class ConnectionListener implements javax.mail.event.ConnectionListener {

	public ConnectionListener(String service) {
		super();

		_service = service;
	}

	public void closed(ConnectionEvent event) {
		if (_log.isInfoEnabled()) {
			long uptime = (System.currentTimeMillis() - _startTime) / 1000;

			_log.info(
				"The " + _service + " service has been closed after " +
					uptime + "secs of uptime.");
		}
	}

	public void disconnected(ConnectionEvent event) {
		if (_log.isInfoEnabled()) {
			long uptime = (System.currentTimeMillis() - _startTime) / 1000;

			_log.info(
				"The " + _service + " service has been disconnected after " +
					uptime + "secs of uptime.");
		}
	}

	public void opened(ConnectionEvent event) {
		_startTime = System.currentTimeMillis();

		if (_log.isInfoEnabled()) {
			_log.info("The " + _service + " service has been opened");
		}
	}

	private static Log _log = LogFactory.getLog(ConnectionListener.class);

	private String _service;
	private long _startTime;

}