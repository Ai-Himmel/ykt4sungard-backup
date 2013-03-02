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

/**
 * Defines the information which uniquely identifies an portlet provided by a producer.
 * The portlet key does not identify a use of an portlet
 * 
 * @author <a href='mailto:Stephan.Laertz@de.ibm.com'>Stephan Laertz</a>
 **/
public interface PortletKey {

	/**
	 * Get the portlet handle which identifies an portlet in the scope of one producer
	 * 
	 * @return The portlet handle
	 **/
	public String getPortletHandle();

	/**
	 * Set the portlet handle which identifies an portlet in the scope of one producer
	 * 
	 * @param portletHandle The portlet handle
	 **/
	public void setPortletHandle(String portletHandle);

	/**
	 * Get the ID of the producer providing the portlet
	 * 
	 * @return The ID of the producer
	 **/
	public String getProducerId();

	/**
	 * Set the ID of the producer providing the portlet
	 * 
	 * @param id The ID of the producer
	 **/
	public void setProducerId(String id);
}