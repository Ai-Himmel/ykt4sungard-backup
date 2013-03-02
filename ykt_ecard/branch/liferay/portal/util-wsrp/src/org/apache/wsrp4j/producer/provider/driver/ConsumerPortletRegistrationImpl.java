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

package org.apache.wsrp4j.producer.provider.driver;

import java.util.Collection;
import java.util.HashSet;

/**
 * This class collects the porlet handles for a registered consumer and 
 * is used for persistence purpose.
 *
 * @author <a href="mailto:Ralf.Altrichter@de.ibm.com">Ralf Altrichter</a>
 *
 * @version 1.0
 */
public class ConsumerPortletRegistrationImpl {

	// the registrationHandle of the consumer
	private String _registrationHandle = null;

	// collects all portletHandles for this registrationHandle
	private HashSet _portletHandles = new HashSet();

	/**
	 * Default Constructor
	 */
	public ConsumerPortletRegistrationImpl() {

	}

	/**
	 * Sets the registration handle for a specific consumer
	 * 
	 * @param regHandle, consumer registration handle
	 */
	public void setRegistrationHandle(String regHandle) {
		_registrationHandle = regHandle;
	}

	/**
	 * Returns the registration handle for a specific consumer
	 * 
	 * @return registrationHandle
	 */
	public String getRegistrationHandle() {
		return _registrationHandle;
	}

	/**
	 * Add a portlet handle to the current registration
	 * 
	 * @param portletHandle
	 */
	public void addPortletHandle(String portletHandle) {
		_portletHandles.add(portletHandle);
	}

	/**
	 * Returns true, if the portletHandle is associated to the 
	 * current registration.
	 * 
	 * @return true on success, otherwise false
	 */
	public boolean containsPortletHandle(String portletHandle) {
		return _portletHandles.contains(portletHandle);
	}

	/**
	 * Removes a portlet handle from the current registration
	 * 
	 * @param portletHandle
	 */
	public void deletePortletHandle(String portletHandle) {
		_portletHandles.remove(portletHandle);
	}

	/**
	 * Sets a collection of portlet handles for this registration
	 * 
	 * @param collection
	 */
	public void setPortletHandles(Collection collection) {
		_portletHandles = (HashSet) collection;
	}

	/**
	 * Returns a collection of portlet handles for this registration
	 * 
	 * @return collection
	 */
	public Collection getPortletHandles() {
		return _portletHandles;
	}

	/**
	 * @return true, if no portlet handles are assigned to this registration
	 *         false, if at least one portlet handle is assigned to his registration
	 */
	public boolean isEmpty() {
		boolean retVal = false;

		if (_portletHandles.size() == 0) {
			retVal = true;
		}
		return retVal;
	}
}