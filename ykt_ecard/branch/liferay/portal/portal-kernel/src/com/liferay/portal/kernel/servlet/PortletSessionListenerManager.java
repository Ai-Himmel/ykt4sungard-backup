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

package com.liferay.portal.kernel.servlet;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpSessionEvent;
import javax.servlet.http.HttpSessionListener;

/**
 * <a href="PortletSessionListenerManager.java.html"><b><i>View Source</i></b>
 * </a>
 *
 * <p>
 * See http://support.liferay.com/browse/LEP-2299.
 * </p>
 *
 * @author Olaf Fricke
 * @author Brian Wing Shun Chan
 *
 */
public class PortletSessionListenerManager implements HttpSessionListener {

	public static void addListener(HttpSessionListener listener) {
		_listeners.add(listener);
	}

	public static void removeListener(HttpSessionListener listener) {
		_listeners.remove(listener);
	}

	public void sessionCreated(HttpSessionEvent event) {
		ClassLoader contextClassLoader =
			Thread.currentThread().getContextClassLoader();

		try {
			Iterator itr = _listeners.iterator();

			while (itr.hasNext()) {
				HttpSessionListener listener = (HttpSessionListener)itr.next();

				ClassLoader listenerClassLoader =
					listener.getClass().getClassLoader();

				Thread.currentThread().setContextClassLoader(
					listenerClassLoader);

				listener.sessionCreated(event);
			}
		}
		finally {
			Thread.currentThread().setContextClassLoader(contextClassLoader);
		}
	}

	public void sessionDestroyed(HttpSessionEvent event) {
		Iterator itr = _listeners.iterator();

		while (itr.hasNext()) {
			HttpSessionListener listener = (HttpSessionListener)itr.next();

			listener.sessionDestroyed(event);
		}
	}

	private static List _listeners = new ArrayList();

}