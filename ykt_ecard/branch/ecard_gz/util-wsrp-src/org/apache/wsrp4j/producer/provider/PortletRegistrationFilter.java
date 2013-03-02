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

/**
 * This interface provides methods to inspect portlets that are
 * accessible by a certain consumer.
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @version 1.1
 *
 */
public interface PortletRegistrationFilter {

	/**
	 * Returns all portlet handles of portlets, a certain consumer (identified
	 * by regHandle) can utilize. Returns null if there are no entries for the provided
	 * regHandle.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * 
	 * @return Iterator of portlet handles
	 */
	public Iterator getAvailable(String regHandle);

	/**
	 * Indicates whether a certain consumer is allowed to utilize the portlet identified
	 * by portletHandle or not. Returns false if there is no entry for the provided handles.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandle String representing the portlet handle of an portlet
	 * 
	 * @return boolean indicating whether the consumer corresponding to regHandle is
	 *         allowed to use the portlet identified by portletHandle
	 */
	public boolean isAvailable(String regHandle, String portletHandle);

}