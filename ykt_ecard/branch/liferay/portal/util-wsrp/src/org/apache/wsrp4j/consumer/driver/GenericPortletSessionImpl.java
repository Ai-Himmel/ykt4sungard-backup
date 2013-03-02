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

import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

import oasis.names.tc.wsrp.v1.types.SessionContext;

import org.apache.wsrp4j.consumer.PortletSession;
import org.apache.wsrp4j.consumer.PortletWindowSession;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

public abstract class GenericPortletSessionImpl implements PortletSession {
	// the session context passed from the producer to store
	private SessionContext sessionCtx = null;

	// the portlet handle identifying the where the session belogns to
	private String handle = null;

	// holds the varios window sessions for this portlet instance
	protected final Map windowSessions;

	// logger
	private static final Logger logger = LogManager.getLogManager().getLogger(
			GenericPortletSessionImpl.class);

	public GenericPortletSessionImpl(String handle) {
		final String MN = "constructor";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		this.windowSessions = new HashMap();
		this.handle = handle;

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	public String getPortletHandle() {
		return handle;
	}

	public void setPortletHandle(String handle) {
		if (handle != null) {
			this.handle = handle;
		}
	}

	public SessionContext getSessionContext() {
		return sessionCtx;
	}

	public void setSessionContext(SessionContext ctx) {
		this.sessionCtx = ctx;
	}

	/**
	 * Get the <code>PortletWindowSession</code> of the portlet window with the given ID.
	 * 
	 * @param windowID The ID of the portlet window
	 * @return The <code>PorletWindowSession</code> with the given ID.    
	 **/
	public abstract PortletWindowSession getPortletWindowSession(String windowID);

	/**
	 * Get all window session which belong to the portlet session
	 * 
	 * @return An Iterator of <code>SimplePortletWindowSession</code> objects.     
	 **/
	public Iterator getAllPorletWindowSessions() {

		return this.windowSessions.entrySet().iterator();
	}

	/**
	 * Remove the porlet window session with the given window id.
	 * 
	 * @param windowID The ID of the portlet window whichs session shoul dbe removed
	 * @return The portlet window session which has been removed or null if the session did not exist.    
	 **/
	public PortletWindowSession removePortletWindowSession(String windowID) {
		final String MN = "getPortletWindowSession";

		PortletWindowSession winSession = (PortletWindowSession) this.windowSessions
				.remove(windowID);

		if (logger.isLogging(Logger.TRACE_HIGH) && winSession != null) {
			logger.text(Logger.TRACE_HIGH, MN,
					"removed PortletWindowSession with ID: " + windowID);
		}

		return winSession;
	}

	/**
	 * Remove all portlet window sessions which  belong to this portlet session.
	 **/
	public void removeAllPortletWindowSessions() {
		this.windowSessions.clear();
	}
}