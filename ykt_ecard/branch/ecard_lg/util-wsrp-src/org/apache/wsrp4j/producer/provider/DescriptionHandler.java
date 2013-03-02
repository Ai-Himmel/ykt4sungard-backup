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

import oasis.names.tc.wsrp.v1.types.PortletDescription;
import oasis.names.tc.wsrp.v1.types.RegistrationContext;
import oasis.names.tc.wsrp.v1.types.ServiceDescription;
import oasis.names.tc.wsrp.v1.types.UserContext;

import org.apache.wsrp4j.exception.WSRPException;

/**
 * This interface provides methods to access portlet descriptions as well as
 * the service description.
 *
 * @author Stefan Behl
 *
 */
public interface DescriptionHandler {

	/**
	 * Returns a ServiceDescription, based on the input arguments.
	 * See the getProducerOfferedPortletDescriptions() method for more details.
	 * 
	 * @param regContext         contains data related to a particular registration
	 *                           (e.g. the registration handle and state)
	 * @param desiredLocales     array of requested locales, if null request all available locales
	 * 
	 */
	public ServiceDescription getServiceDescription(
			RegistrationContext regContext, String[] desiredLocales)
			throws WSRPException;

	/**
	 * Indicates whether registration is required (for this Producer) or not.
	 * 
	 * @return Returns true if registration is required, otherwise false. 
	 */
	public boolean isRegistrationRequired() throws WSRPException;

	/**
	 * Returns an array containing all portlet descriptions, i.e. one portlet
	 * description per producer offered portlet.
	 * 
	 * @param regContext         contains data related to a particular registration
	 *                           (e.g. the registration handle and state)
	 * @param desiredLocales     array of requested locales, if null request all available locales
	 * 
	 * @return    Array of PortletDescription-objects.
	 */
	public PortletDescription[] getProducerOfferedPortletDescriptions(
			RegistrationContext regContext, String[] desiredLocales)
			throws WSRPException;

	/**
	 * Returns an PortletDescription for the given PortletHandle based on the input
	 * arguments. On how the desiredLocales and sendAllLocales parameter affects the
	 * returned PortletDescription, please see the method getProducerOfferedPortletDescriptions().
	 * 
	 * @param portletHandle      the handle of a particular portlet
	 * @param regContext         contains data related to a particular registration
	 *                           (e.g. the registration handle and state)
	 * @param userContext        contains the user context
	 * @param desiredLocales     array of requested locales, if null request all available locales
	 * 
	 * @return PortletDescription
	 */
	public PortletDescription getPortletDescription(String portletHandle,
			RegistrationContext regContext, UserContext userContext,
			String[] desiredLocales) throws WSRPException;

	/**
	 * Returns a complete PortletDescription for the given PortletHandle.
	 * 
	 * @param portletHandle      the handle of a particular portlet
	 * 
	 * @return PortletDescription
	 */
	public PortletDescription getPortletDescription(String portletHandle)
			throws WSRPException;

}