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

import JOscarLib.Core.OscarConnection;

import JOscarLib.Tool.OscarInterface;

import com.liferay.portal.kernel.util.KeyValuePair;
import com.liferay.portal.util.PropsUtil;

import java.util.Iterator;
import java.util.List;
import java.util.Observable;
import java.util.Observer;
import java.util.Vector;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ICQConnector.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brett Randall
 *
 */
public class ICQConnector implements Observer {

	public static void disconnect() {
		if (_instance != null) {
			_instance._disconnect();
		}
	}

	public static void send(String to, String msg) {
		_instance._send(to, msg);
	}

	public void update(Observable obs, Object obj) {
		_connecting = false;

		Iterator itr = _messages.iterator();

		while (itr.hasNext()) {
			KeyValuePair kvp = (KeyValuePair)itr.next();

			OscarInterface.sendMessage(_icq, kvp.getKey(), kvp.getValue());
		}
	}

	private ICQConnector() {
		_messages = new Vector();
	}

	private void _connect() {
		_connecting = true;

		String login = PropsUtil.get(PropsUtil.ICQ_LOGIN);
		String password = PropsUtil.get(PropsUtil.ICQ_PASSWORD);

		_icq = new OscarConnection("login.icq.com", 5190, login, password);

		//_icq.getPacketAnalyser().setDebug(true);

		_icq.addObserver(this);
	}

	private void _disconnect() {
		try {
			_icq.close();
		}
		catch (Exception e) {
			_log.warn(e);
		}
	}

	private synchronized void _send(String to, String msg) {
		if (((_icq == null) || !_icq.isLogged()) && !_connecting) {
			_connect();

			_messages.add(new KeyValuePair(to, msg));
		}
		else {
			OscarInterface.sendMessage(_icq, to, msg);
		}
	}

	private static Log _log = LogFactory.getLog(ICQConnector.class);

	private static ICQConnector _instance = new ICQConnector();

	private OscarConnection _icq;
	private List _messages;
	private boolean _connecting;

}