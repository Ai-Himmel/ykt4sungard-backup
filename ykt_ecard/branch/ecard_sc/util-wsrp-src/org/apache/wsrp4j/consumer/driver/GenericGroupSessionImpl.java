/*
 * Copyright 2000-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package org.apache.wsrp4j.consumer.driver;

import java.util.Hashtable;
import java.util.Iterator;

import org.apache.wsrp4j.consumer.GroupSessionMgr;
import org.apache.wsrp4j.consumer.PortletSession;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

/**
 * Class implements a consumer based group session
 * 
 */
public abstract class GenericGroupSessionImpl extends InitCookieInfoImpl
		implements GroupSessionMgr {

	// ID of the group this session is bind to 
	private String groupID = null;

	// holding all the portlet session objects for this group
	protected Hashtable portletSessions = null;

	// logger
	private static final Logger logger = LogManager.getLogManager().getLogger(
			GenericGroupSessionImpl.class);

	public GenericGroupSessionImpl(String groupID, String markupInterfaceURL)
			throws WSRPException {
		super(markupInterfaceURL);

		final String MN = "constructor";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		this.groupID = groupID;
		this.portletSessions = new Hashtable();

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	public String getGroupID() {
		return this.groupID;
	}

	public void setGroupID(String groupID) {
		if (groupID != null) {
			this.groupID = groupID;
		}
	}

	public void addPortletSession(PortletSession portletSession) {
		final String MN = "addPortletSession";

		if (portletSession != null) {
			this.portletSessions.put(portletSession.getPortletHandle(),
					portletSession);
			if (logger.isLogging(Logger.TRACE_HIGH)) {
				logger.text(Logger.TRACE_HIGH, MN,
						"added PortletSession with handle: "
								+ portletSession.getPortletHandle()
								+ " to GroupSession with ID: " + groupID);
			}
		}
	}

	public abstract PortletSession getPortletSession(String portletHandle);

	public Iterator getAllPortletSessions() {
		return this.portletSessions.values().iterator();
	}

	public void removePortletSession(String portletHandle) {
		final String MN = "removePortletSession";
		if (portletHandle == null) {
			this.portletSessions.remove(portletHandle);
			if (logger.isLogging(Logger.TRACE_HIGH)) {
				logger.text(Logger.TRACE_HIGH, MN,
						"deleted PortletSession with handle: " + portletHandle
								+ " from GroupSession with ID: " + groupID);
			}
		}
	}

	public void removeAllPortletSessions() {
		this.portletSessions.clear();
	}

	public boolean existsPortletSession(String portletHandle) {
		if (portletHandle == null)
			return false;
		return this.portletSessions.containsKey(portletHandle);
	}
}