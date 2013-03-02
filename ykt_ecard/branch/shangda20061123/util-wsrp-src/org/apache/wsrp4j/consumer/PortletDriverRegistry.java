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

package org.apache.wsrp4j.consumer;

import java.util.Iterator;

import org.apache.wsrp4j.exception.WSRPException;

/**
 * This interface defines a registry which can be used to store
 * portlet driver objects.
 * 
 * @author Stephan Laertz
 **/
public interface PortletDriverRegistry {

	/**
	 * Get an portlet driver for the given portlet. If there is no portlet driver
	 * object cached a new portlet driver will be created and returned.
	 * 
	 * @param portlet The portlet the returned portlet driver is bind to
	 * 
	 * @return The portlet driver for this portlet
	 **/
	public PortletDriver getPortletDriver(WSRPPortlet portlet)
			throws WSRPException;

	/**
	 * Get all cached portlet drivers.
	 * 
	 * @return Iterator with all portlet drivers in the registry
	 **/
	public Iterator getAllPortletDrivers();
}