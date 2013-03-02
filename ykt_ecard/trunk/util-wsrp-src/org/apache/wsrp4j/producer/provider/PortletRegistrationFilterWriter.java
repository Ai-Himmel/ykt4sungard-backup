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

package org.apache.wsrp4j.producer.provider;

import java.util.Iterator;
import org.apache.wsrp4j.exception.WSRPException;

/**
 * This interface provides methods to make portlets available
 * to a certain consumer. If a certain consumer deregisters, the consumer
 * registry is responsible for updating, i.e. removing the entries within
 * the PortletRegistratinFilter component. If an portlet was removed, the
 * portlet pool has to remove the affected entries by calling the provided
 * remove-methods.
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *                                                                          
 * @version 1.1
 *
 */
public interface PortletRegistrationFilterWriter extends
		PortletRegistrationFilter {

	/**
	 * Makes a certain portlet (identified by portletHandle) available to a consumer
	 * (identified by regHandle). If there is no portlet in the portlet pool that
	 * corresponds to portletHandle, the method performs nothing. 
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandle String representing the portlet handle of a consumer
	 */
	public void makeAvailable(String regHandle, String portletHandle)
			throws WSRPException;

	/**
	 * Makes several portlets (identified by portletHandles) available to
	 * a certain consumer (identified by regHandle). For portlet handles that do not
	 * correspond to portlets kept within the portlet pool, the method makes no
	 * availability-entry.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandles Iterator containing some portlet handles of portlets
	 */
	public void makeAvailable(String regHandle, Iterator portletHandles)
			throws WSRPException;

	/**
	 * Removes an entire entry for a certain consumer (identified by regHandle).
	 * If there are no entries for the provided regHandle, the method performs
	 * nothing. The method is useful when a consumer deregisters.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 */
	public void remove(String regHandle);

	/**
	 * Abrogates the availability of a certain portlet (identified by portletHandle)
	 * regarding a certain consumer (identified by regHandle). If there is no entry
	 * for the provided regHandle and portletHandle, the method performs nothing.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandle String representing the portlet handle of a consumer
	 */
	public void remove(String regHandle, String portletHandle)
			throws WSRPException;

	/**
	 * Abrogates the availability of several portlets (identified by portletHandles)
	 * regarding a certain consumer (identified by regHandle). For portlet handles
	 * that do not correspond to portlets kept within the portlet pool, the method
	 * performs nothing.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandles Iterator containing some portlet handles of portlets
	 */
	public void remove(String regHandle, Iterator portletHandles)
			throws WSRPException;

}