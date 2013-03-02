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

import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.util.multiaccount.MailCache;
import com.liferay.util.CollectionFactory;

import java.util.Map;

import javax.mail.Folder;
import javax.mail.MessagingException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailSessionLock.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class MailSessionLock {

	public static void cleanUp(HttpSession ses) {
		_instance._cleanUp(ses);
	}

	public static void lock(HttpServletRequest req) {
		_instance._lock(req.getSession().getId());
	}

	public static void unlock(HttpServletRequest req) {
		_instance._unlock(req.getSession().getId());
	}

	private MailSessionLock() {
	}

	private void _cleanUp(HttpSession ses) {
		try {

			// This method duplicates the same method in MailUtil because of
			// LEP-4829.

			Folder folder = (Folder)ses.getAttribute(WebKeys.MAIL_FOLDER);

			if ((folder != null) && folder.isOpen()) {
				try {
					folder.close(false);
				}
				catch (MessagingException me) {
					if (_log.isWarnEnabled()) {
						_log.warn(me);
					}
				}

				ses.removeAttribute(WebKeys.MAIL_FOLDER);
			}

			MailCache.clearCache(ses);

			ses.removeAttribute(WebKeys.MAIL_MESSAGE_ID);
		}
		catch (Exception e) {
		}

		synchronized (_sessionMap) {
			_sessionMap.remove(ses.getId());
		}
	}

	private void _lock(String sessionId) {
		ThreadLocal threadLocal = null;

		for (;;) {
			synchronized (_sessionMap) {
				threadLocal = (ThreadLocal)_sessionMap.get(sessionId);

				if (threadLocal == null) {

					// Initialize reentrant counter.

					threadLocal = new ThreadLocal();

					threadLocal.set(new Long(0));

					_sessionMap.put(sessionId, threadLocal);

					break;
				}
				else if (threadLocal.get() != null) {

					// This thread instantiated the thread local. Increment the
					// reentrant counter.

					Long count = (Long)threadLocal.get();

					threadLocal.set(new Long(count.longValue() + 1L));

					break;
				}
			}

			// Another thread instantiated the thread local. Wait until that
			// thread is done.

			try {
				wait(100);
			}
			catch (Exception ex) {
			}
		}
	}

	private void _unlock(String sessionId) {
		ThreadLocal threadLocal = null;

		synchronized (_sessionMap) {
			threadLocal = (ThreadLocal)_sessionMap.get(sessionId);

			// The variable can be null at this time if a method called unlock()
			// twice or cleanUp() was called.

			if (threadLocal != null) {
				Long count = (Long)threadLocal.get();

				if (count.longValue() == 0L) {

					// All reentrant calls have completed

					_sessionMap.remove(sessionId);
				}
				else {

					// Finished one of the reentrant calls

					count = new Long(count.longValue() - 1L);

					threadLocal.set(count);
				}
			}
		}
	}

	private static Log _log = LogFactory.getLog(MailSessionLock.class);

	private static MailSessionLock _instance = new MailSessionLock();

	private Map _sessionMap = CollectionFactory.getHashMap();

}