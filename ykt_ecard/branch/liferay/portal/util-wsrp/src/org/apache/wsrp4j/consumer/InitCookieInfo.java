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

/**
 * The init cookie information provides a mean to store
 * information if a <code>InitCookie</code> call is required before 
 * performing any other wsrp call. Since a call of init cookie may
 * be required only once for a group or a user per producer, this interface also
 * offers method to check this call has been done already or not.
 * 
 * As an initCookie call in WSRP can be required on a per group or
 * per user basis an object implementing this interface can typically
 * be hold in a user or group session.
 * 
 * Implementations of this interface hold a MarkupPortType stub
 * to handle cookies correctly
 * 
 * @author Stephan Laertz
 * @author <a href='mailto:peter.fischer@de.ibm.com'>Peter Fischer</a>
 **/
public interface InitCookieInfo {

	/**
	 * Check if an initCookie call is generally required. This
	 * does not necessarily say anything if the required initCookie call
	 * has been done already. Use <code>isInitCookieDone</code> for 
	 * this purpose.
	 * 
	 * @return True if a call of init cookie is generally required.
	 **/
	public boolean isInitCookieRequired();

	/**
	 * Set a boolean value to indicate if an initCookie call
	 * needs to be done.
	 * 
	 * @param initCookieRequired True if an initCookie call is generally required
	 **/
	public void setInitCookieRequired(boolean initCookieRequired);

	/**
	 * Check wether a initCookie call has been done already or not.
	 * 
	 * @return True if an initCookie has been done already
	 **/
	public boolean isInitCookieDone();

	/**
	 * Set if an initCookie call has been done already or not.
	 * 
	 * @param initCookieDone Set to true if the call has been done; false otherwise
	 **/
	public void setInitCookieDone(boolean initCookieDone);

	/**
	 * Get the markup interface URL
	 * 
	 * @return the markup interface URL
	 **/
	public String getMarkupInterfaceURL();

	/**
	 * Get the markup interface portType
	 * 
	 * @return the markup interface portType
	 **/
	public WSRP_v1_Markup_PortType getWSRPBaseService();

	/**
	 * set the markup interface portType
	 * 
	 * @param markupPortType the markup interface portType
	 **/
	public void setWSRPBaseService(WSRP_v1_Markup_PortType markupPortType);
}