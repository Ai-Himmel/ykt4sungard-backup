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

/* 

 */

package org.apache.wsrp4j.consumer.driver;

import java.util.Hashtable;
import java.util.Iterator;

import org.apache.wsrp4j.consumer.PortletKey;
import org.apache.wsrp4j.consumer.PortletRegistry;
import org.apache.wsrp4j.consumer.WSRPPortlet;
import org.apache.wsrp4j.exception.WSRPException;

public abstract class GenericPortletRegistryImpl implements PortletRegistry {

	// maps portlet keys to portlets
	private Hashtable portlets = null;

	public GenericPortletRegistryImpl() {
		portlets = new Hashtable();
	}

	/**
	 * Add a portlet to the registry
	 *
	 * @param portlet The portlet to add
	 */
	public void addPortlet(WSRPPortlet portlet) throws WSRPException {
		if (portlet != null) {

			portlets.put(portlet.getPortletKey().toString(), portlet);

		}
	}

	/**
	 * Get the portlet for the given producer and portlet handle
	 *
	 * @param portletKey The portlet key identifying the portlet
	 *
	 * @return The portlet with the given portlet key
	 **/
	public WSRPPortlet getPortlet(PortletKey portletKey) {

		if (portletKey == null)
			return null;

		WSRPPortlet portlet = (WSRPPortlet) portlets.get(portletKey.toString());

		return portlet;
	}

	/**
	 * Remove the portlet with the given portlet key
	 *
	 * @param portletKey The portlet key identifying the portlet
	 * @return The portlet which has been removed or null
	 **/
	public WSRPPortlet removePortlet(PortletKey portletKey) {
		if (portletKey == null)
			return null;

		return (WSRPPortlet) portlets.remove(portletKey.toString());
	}

	/**
	 *  Remove all portlets from the registry 
	 **/
	public void removeAllPortlets() {
		portlets.clear();
	}

	/**
	 * Tests if a portlet with the given portlet key
	 * 
	 * @param portletKey The portlet key identifying the portlet
	 * 
	 * @return True if portlet exists with this portlet key
	 **/
	public boolean existsPortlet(PortletKey portletKey) {
		if (portletKey == null)
			return false;

		return portlets.containsKey(portletKey.toString());
	}

	/**
	 * Get all the portlets in the register
	 * 
	 * @return Iterator with all portlets in the registry
	 **/
	public Iterator getAllPortlets() {
		return portlets.values().iterator();
	}
}