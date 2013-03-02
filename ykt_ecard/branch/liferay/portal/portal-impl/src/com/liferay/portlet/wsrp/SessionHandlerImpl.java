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

package com.liferay.portlet.wsrp;

import javax.portlet.PortletSession;

import org.apache.wsrp4j.consumer.ConsumerEnvironment;
import org.apache.wsrp4j.consumer.Producer;
import org.apache.wsrp4j.consumer.UserSessionMgr;
import org.apache.wsrp4j.exception.WSRPException;

/**
 * <a href="SessionHandlerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class SessionHandlerImpl implements SessionHandler {

	private SessionHandlerImpl(ConsumerEnvironment consumerEnv) {
		this._consumerEnv = consumerEnv;
	}

	public static SessionHandler getInstance(ConsumerEnvironment consumerEnv) {
		if (_instance == null) {
			_instance = new SessionHandlerImpl(consumerEnv);
		}

		return _instance;
	}

	public void setPortletSession(PortletSession portletSession) {
		this._portletSession = portletSession;
	}

	public UserSessionMgr getUserSession(String producerID, String userID)
			throws WSRPException {
		if (_portletSession == null) {
			try {
				throw new Exception(
						"PortletSession is null. Call setPortletSession() first.");
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}
		else {

			Producer producer = _consumerEnv.getProducerRegistry().getProducer(
					producerID);

			if (producer != null) {

				String markupURL = producer.getMarkupInterfaceEndpoint();

				return new UserSessionImpl(producerID, userID, markupURL,
						_portletSession);
			}
		}

		return null;
	}

	private PortletSession _portletSession = null;

	private ConsumerEnvironment _consumerEnv = null;

	private static SessionHandler _instance = null;

}