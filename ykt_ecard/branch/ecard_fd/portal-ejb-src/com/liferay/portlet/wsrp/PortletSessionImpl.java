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

package com.liferay.portlet.wsrp;

import org.apache.wsrp4j.consumer.PortletWindowSession;
import org.apache.wsrp4j.consumer.driver.GenericPortletSessionImpl;
import org.apache.wsrp4j.consumer.driver.GenericPortletWindowSessionImpl;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

/**
 * <a href="PortletSessionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.3 $
 *
 */
public class PortletSessionImpl extends GenericPortletSessionImpl {

	public PortletSessionImpl(String handle) {
		super(handle);
	}

	/**
	 * Get the <code>PortletWindowSession</code> of the portlet window with
	 * the given ID.
	 *
	 * @param windowID
	 *            The ID of the portlet window
	 * @return The <code>PorletWindowSession</code> with the given ID.
	 */
	public PortletWindowSession getPortletWindowSession(String windowID) {
		final String MN = "getPortletWindowSession";

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		PortletWindowSession session = (PortletWindowSession) this.windowSessions
				.get(windowID);
		if (session == null) {
			session = new GenericPortletWindowSessionImpl(windowID, this);
			this.windowSessions.put(windowID, session);

			if (_logger.isLogging(Logger.TRACE_HIGH)) {
				_logger.text(Logger.TRACE_HIGH, MN,
						"created windowSession with ID: " + windowID);
			}
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}

		return session;
	}

	// logger
	private static final Logger _logger = LogManager.getLogManager().getLogger(
			PortletSessionImpl.class);

}