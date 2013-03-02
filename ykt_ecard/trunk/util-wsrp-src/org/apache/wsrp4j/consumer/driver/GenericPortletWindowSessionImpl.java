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

import org.apache.wsrp4j.consumer.PortletWindowSession;
import org.apache.wsrp4j.consumer.PortletSession;

import oasis.names.tc.wsrp.v1.types.MarkupContext;

public class GenericPortletWindowSessionImpl implements PortletWindowSession {
	// the markup context we store between performBlockingInteraction and getMarkup calls
	private transient MarkupContext markupCtx = null;

	// the window ID identifying this session
	private String windowID = null;

	// the refering PortletSession     
	private PortletSession pSession = null;

	public GenericPortletWindowSessionImpl(String windowID,
			PortletSession pSession) {
		this.windowID = windowID;
		this.pSession = pSession;
	}

	public PortletSession getPortletSession() {
		return this.pSession;
	}

	public String getWindowID() {
		return windowID;
	}

	public void setWindowID(String windowID) {
		this.windowID = windowID;
	}

	public MarkupContext getCachedMarkup() {
		return markupCtx;
	}

	public void updateMarkupCache(MarkupContext markupContext) {
		markupCtx = markupContext;
	}
}