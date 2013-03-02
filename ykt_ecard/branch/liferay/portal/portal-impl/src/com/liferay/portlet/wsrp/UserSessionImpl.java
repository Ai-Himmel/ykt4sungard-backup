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

import java.util.Hashtable;
import java.util.Map;

import javax.portlet.PortletSession;

import oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType;

import org.apache.wsrp4j.consumer.GroupSessionMgr;
import org.apache.wsrp4j.consumer.driver.GenericUserSessionImpl;
import org.apache.wsrp4j.consumer.util.ConsumerConstants;
import org.apache.wsrp4j.exception.WSRPException;

/**
 * <a href="UserSessionImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class UserSessionImpl extends GenericUserSessionImpl {

	public UserSessionImpl(String producerID, String userID,
			String portletServicesURL, PortletSession portletSession)
			throws WSRPException {

		super(producerID, userID, portletServicesURL);

		this._portletSession = portletSession;
		_userSession = getUserSessionMap();
		setGroupSessionTable(getGroupSessionTable());
	}

	private Hashtable getGroupSessionTable() {

		if ((groupSessions = (Hashtable) _userSession
				.get(ConsumerConstants.WSRP_GROUPSESSIONS)) == null) {
			groupSessions = new Hashtable();
			_userSession
					.put(ConsumerConstants.WSRP_GROUPSESSIONS, groupSessions);
		}

		return groupSessions;
	}

	/**
	 * Get the group session for this group ID
	 *
	 * @param groupID
	 *            ID of the portlet application
	 * @return The group session for the provided group ID
	 */
	public GroupSessionMgr getGroupSession(String groupID)
		throws WSRPException {

		if (groupID != null) {
			GroupSessionMgr groupSession = (GroupSessionMgr) this.groupSessions
					.get(groupID);
			if (groupSession == null) {

				groupSession = new GroupSessionImpl(groupID, this
						.getMarkupInterfaceURL());
				addGroupSession(groupSession);
			}

			return groupSession;
		}
		return null;
	}

	public WSRP_v1_Markup_PortType getWSRPBaseService() {
		WSRP_v1_Markup_PortType markupPort = null;
		if ((markupPort = (WSRP_v1_Markup_PortType) _userSession
				.get(ConsumerConstants.WSRP_MARKUP_PORT)) == null) {
			markupPort = super.getWSRPBaseService();
			_userSession.put(ConsumerConstants.WSRP_MARKUP_PORT, markupPort);
		}

		this.setWSRPBaseService(markupPort);
		return markupPort;
	}

	public boolean isInitCookieRequired() {
		Boolean initCookieReq = null;
		if ((initCookieReq = (Boolean) _userSession
				.get(ConsumerConstants.WSRP_INIT_COOKIE_REQ)) == null) {
			initCookieReq = Boolean.valueOf(super.isInitCookieRequired());
			setInitCookieRequired(initCookieReq.booleanValue());
		}

		return initCookieReq.booleanValue();
	}

	public void setInitCookieRequired(boolean initCookieRequired) {
		_userSession.put(ConsumerConstants.WSRP_INIT_COOKIE_REQ, Boolean.valueOf(
				initCookieRequired));
		super.setInitCookieRequired(initCookieRequired);
	}

	public boolean isInitCookieDone() {
		Boolean initCookieDone = null;
		if ((initCookieDone = (Boolean) _userSession
				.get(ConsumerConstants.WSRP_INIT_COOKIE_DONE)) == null) {
			initCookieDone = Boolean.valueOf(super.isInitCookieDone());
			setInitCookieDone(initCookieDone.booleanValue());
		}

		return initCookieDone.booleanValue();
	}

	public void setInitCookieDone(boolean initCookieDone) {
		_userSession.put(ConsumerConstants.WSRP_INIT_COOKIE_DONE, Boolean.valueOf(
				initCookieDone));
		super.setInitCookieRequired(initCookieDone);
	}

	private Map getUserSessionMap() {
		String key = createKey();
		Map myMap = (Map) this._portletSession.getAttribute(key,
				PortletSession.APPLICATION_SCOPE);

		if (myMap == null) {
			myMap = new Hashtable();
			this._portletSession.setAttribute(key, myMap,
					PortletSession.APPLICATION_SCOPE);
		}

		return myMap;
	}

	private String createKey() {
		return "user :" + this.getUserID() + " producer:"
				+ this.getProducerID();
	}

	private PortletSession _portletSession = null;

	private Map _userSession = null;

}