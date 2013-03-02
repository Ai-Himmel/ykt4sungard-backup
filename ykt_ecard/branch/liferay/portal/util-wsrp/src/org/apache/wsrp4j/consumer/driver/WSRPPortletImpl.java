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

import oasis.names.tc.wsrp.v1.types.PortletContext;

import org.apache.wsrp4j.consumer.PortletKey;
import org.apache.wsrp4j.consumer.WSRPPortlet;
import org.apache.wsrp4j.util.StateChangedServiceImpl;

/**
 * Implements the portlet interface
 **/
public class WSRPPortletImpl extends StateChangedServiceImpl implements
		WSRPPortlet {

	private PortletKey portletKey = null;

	private PortletContext portletContext = null;

	private String parentHandle = null;

	// for castor persistence
	public WSRPPortletImpl() {
	}

	public WSRPPortletImpl(PortletKey portletKey) {
		this.portletKey = portletKey;
		this.parentHandle = portletKey.getPortletHandle();
	}

	public PortletKey getPortletKey() {
		return this.portletKey;
	}

	public void setPortletKey(PortletKey portletKey) {
		if (portletKey != null) {
			this.portletKey = portletKey;

			if (this.portletContext != null) {
				this.portletContext.setPortletHandle(portletKey
						.getPortletHandle());
			}

			if (parentHandle == null) {
				parentHandle = portletKey.getPortletHandle();
			}

			stateChanged();
		}
	}

	public void setPortletContext(PortletContext portletContext) {
		if (portletContext != null) {
			this.portletContext = portletContext;
			this.portletKey.setPortletHandle(portletContext.getPortletHandle());

			stateChanged();
		}
	}

	public PortletContext getPortletContext() {
		return this.portletContext;
	}

	public String getParent() {
		return this.parentHandle;
	}

	public void setParent(String portletHandle) {
		this.parentHandle = portletHandle;

		stateChanged();
	}

	public boolean isConsumerConfigured() {

		return !getParent().equals(portletKey.getPortletHandle());
	}
}