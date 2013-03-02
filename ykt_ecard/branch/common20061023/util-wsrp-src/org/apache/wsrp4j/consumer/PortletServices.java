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

import oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType;
import oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType;

/**
 * WSRP portlet services are all wsrp service interfaces which
 * are session dependent. With the implemented version 0.91 of the 
 * WSRP specification the markup interface and the portlet management interface
 * depend on using the same session cookie in an clustered environment.
 * 
 * This interface provides a vehicle to store and retrieve the portTypes of these
 * interfaces.
 * 
 * @author Stephan Laertz
 **/
public interface PortletServices {

	/**
	 * Set the portType object of the portlet management service.
	 * 
	 * @param portletManagementPortType Port type object which describes the operations of the
	 *                                  producers portlet mamagement service endpoint
	 **/
	public void setWSRPPortletManagementService(
			WSRP_v1_PortletManagement_PortType portletManagementPortType);

	/**
	 * Get a port type object describing the operations of a produces portlet management service
	 * endpoint.
	 * 
	 * @return Portlet management port type object
	 **/
	public WSRP_v1_PortletManagement_PortType getWSRPPortletManagementService();

	/**
	 * Set the portType object of the markup service.
	 * 
	 * @param markupPortType Port type object which describes the operations of the
	 *                                  producers markup service endpoint
	 **/
	public void setWSRPBaseService(WSRP_v1_Markup_PortType markupPortType);

	/**
	 * Get a port type object describing the operations of a produces markup service
	 * endpoint.
	 * 
	 * @return Markup port type object
	 **/
	public WSRP_v1_Markup_PortType getWSRPBaseService();

	/**
	 * Get the URL of the producers markup and portlet management service interface.
	 * Since both services can depend on a producer session they need to have the same
	 * accessPoint. 
	 *
	 * @return The URL of the producers markup and portlet management service interface.
	 **/
	public String getPortletServicesURL();
}