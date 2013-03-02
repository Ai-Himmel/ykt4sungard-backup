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

package org.apache.wsrp4j.producer.provider;

import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.producer.provider.PortletRegistrationFilterWriter;
import org.apache.wsrp4j.producer.provider.PortletRegistrationFilter;

public interface Provider {

	/**
	 * Returns an instance of DescriptionHandler by calling the constructor
	 * of the corresponding class implementing the DescriptionHandler-Interface
	 *
	 * @return DescriptionHandler DescriptionHandler-instance.
	 */
	public DescriptionHandler getDescriptionHandler();

	/**
	 * Returns an instance of PortletInvoker by calling the constructor
	 * of the corresponding class implementing the PortletInvoker-Interface
	 *
	 * @return PortletInvoker PortletInvoker-instance.
	 */
	public PortletInvoker getPortletInvoker();

	/**
	 * Returns an instance of PortletPool by calling the constructor
	 * of the corresponding class implementing the PortletPool-Interface
	 *
	 * @return PortletPool PortletPool-instance.
	 */
	public PortletPool getPortletPool();

	/**
	 * Returns an instance of PortletProperties by calling the constructor
	 * of the corresponding class implementing the PortletProperties-Interface
	 *
	 * @return PortletProperties PortletProperties-instance.
	 */
	public PortletStateManager getPortletStateManager() throws WSRPException;

	/**
	 * Returns an instance of URLComposer by calling the constructor
	 * of the corresponding class implementing the URLComposer-Interface
	 *
	 * @return URLComposer URLComposer-instance.
	 */
	public URLComposer getURLComposer();

	/**
	 * Returns an instance of the PortletRegistrationFilterWriter
	 * 
	 * @return PortletRegistrationFilterWriter
	 */
	public PortletRegistrationFilterWriter getPortletRegistrationFilterWriter();

	/**
	 * Returns an instance of the PortletRegistrationFilter
	 * 
	 * @return PortletRegistrationFilter
	 */
	public PortletRegistrationFilter getPortletRegistrationFilter();

}