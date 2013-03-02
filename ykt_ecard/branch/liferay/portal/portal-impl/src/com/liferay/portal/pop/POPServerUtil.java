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

package com.liferay.portal.pop;

import com.liferay.portal.job.JobScheduler;
import com.liferay.portal.kernel.pop.MessageListener;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="POPServerUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class POPServerUtil {

	public static void addListener(MessageListener listener)
		throws Exception {

		_instance._addListener(listener);
	}

	public static void deleteListener(MessageListener listener)
		throws Exception {

		_instance._deleteListener(listener);
	}

	public static List getListeners() throws Exception {
		return _instance._getListeners();
	}

	public static void start() {
		_instance._start();
	}

	public static void stop() {
		_instance._stop();
	}

	private POPServerUtil() {
	}

	private void _addListener(MessageListener listener) {
		if (listener == null) {
			if (_log.isDebugEnabled()) {
				_log.debug("Do not add null listener");
			}

			return;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Add listener " + listener.getClass().getName());
		}

		MessageListenerWrapper messageListenerWrapper =
			new MessageListenerWrapper(listener);

		_deleteListener(messageListenerWrapper);

		_listeners.add(messageListenerWrapper);

		if (_log.isDebugEnabled()) {
			_log.debug("Listeners size " + _listeners.size());
		}
	}

	private void _deleteListener(MessageListenerWrapper listener) {
		Iterator itr = _listeners.iterator();

		while (itr.hasNext()) {
			MessageListenerWrapper curListener =
				(MessageListenerWrapper)itr.next();

			if (curListener.equals(listener)) {
				itr.remove();
			}
		}
	}

	private void _deleteListener(MessageListener listener) {
		if (listener == null) {
			if (_log.isDebugEnabled()) {
				_log.debug("Do not delete null listener");
			}

			return;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Delete listener " + listener.getClass().getName());
		}

		MessageListenerWrapper messageListenerWrapper =
			new MessageListenerWrapper(listener);

		_deleteListener(messageListenerWrapper);

		if (_log.isDebugEnabled()) {
			_log.debug("Listeners size " + _listeners.size());
		}
	}

	private List _getListeners() {
		if (_log.isDebugEnabled()) {
			_log.debug("Listeners size " + _listeners.size());
		}

		return Collections.unmodifiableList(_listeners);
	}

	private void _start() {
		if (_log.isDebugEnabled()) {
			_log.debug("Start");
		}

		try {
			POPNotificationsJob popNotificationsJob = new POPNotificationsJob();

			JobScheduler.schedule(popNotificationsJob);

			//popNotificationsJob.pollPopServer();
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private void _stop() {
		if (_log.isDebugEnabled()) {
			_log.debug("Stop");
		}

		try {
			JobScheduler.unscheduleJob(POPNotificationsJob.class.getName());
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private static Log _log = LogFactory.getLog(POPServerUtil.class);

	private static POPServerUtil _instance = new POPServerUtil();

	private List _listeners = new ArrayList();

}