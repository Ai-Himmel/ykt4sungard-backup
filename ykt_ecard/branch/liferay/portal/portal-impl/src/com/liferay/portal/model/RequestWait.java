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

package com.liferay.portal.model;

import com.liferay.portal.util.PropsValues;

/**
 * <a href="RequestWait.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ming-Gih Lam
 *
 */
public class RequestWait {

	public String getCmd() {
		return _cmd;
	}

	public void setCmd(String cmd) {
		_cmd = cmd;
	}

	public boolean isExpired() {
		return _expired;
	}

	public void setExpired(boolean expired) {
		this._expired = expired;
	}

	public String getSessionId() {
		return _sessionId;
	}

	public void setSessionId(String sessionId) {
		_sessionId = sessionId;
	}

	public boolean isTimedOut() {
		return _timedOut;
	}

	public void setTimedOut(boolean timedOut) {
		_timedOut = timedOut;
	}

	public synchronized void expire() {
		_timedOut = false;
		_expired = true;

		notify();
	}

	public synchronized void notifyWait() {
		_timedOut = false;

		notify();
	}

	public synchronized void waitForRequest() throws InterruptedException {
		_timedOut = true;

		wait(PropsValues.REVERSE_AJAX_HEARTBEAT);
	}

	private String _cmd;
	private String _sessionId;
	private boolean _expired = false;
	private boolean _timedOut = false;

}