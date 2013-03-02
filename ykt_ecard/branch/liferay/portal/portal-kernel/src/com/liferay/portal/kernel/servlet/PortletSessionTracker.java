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

import java.io.Serializable;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

import javax.servlet.http.HttpSession;
import javax.servlet.http.HttpSessionBindingEvent;
import javax.servlet.http.HttpSessionBindingListener;

/**
 * <a href="PortletSessionTracker.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * See http://support.liferay.com/browse/LEP-1466.
 * </p>
 *
 * @author Rudy Hilado
 *
 */
public class PortletSessionTracker
	implements HttpSessionBindingListener, Serializable {

	public static void add(HttpSession session) {
		_instance._add(session);
	}

	public static HttpSessionBindingListener getInstance() {
		return _instance;
	}

	public static void invalidate(String sessionId) {
		_instance._invalidate(sessionId);
	}

	public void valueBound(HttpSessionBindingEvent event) {
	}

	public void valueUnbound(HttpSessionBindingEvent event) {
		invalidate(event.getSession().getId());
	}

	private PortletSessionTracker() {
		_sessions = new HashMap();
	}

	private void _add(HttpSession session) {
		String sessionId = session.getId();

		synchronized (_sessions) {
			Set portletSessions = (Set)_sessions.get(sessionId);

			if (portletSessions == null) {
				portletSessions = new HashSet();

				_sessions.put(sessionId, portletSessions);
			}

			portletSessions.add(session);
		}
	}

	private void _invalidate(String sessionId) {
		synchronized (_sessions) {
			Set portletSessions = (Set)_sessions.get(sessionId);

			if (portletSessions != null) {
				Iterator itr = portletSessions.iterator();

				while (itr.hasNext()) {
					HttpSession session = (HttpSession)itr.next();

					try {
						session.invalidate();
					}
					catch (Exception e) {
					}
				}
			}

			_sessions.remove(sessionId);
		}
	}

	private static PortletSessionTracker _instance =
		new PortletSessionTracker();

	private transient Map _sessions;

}