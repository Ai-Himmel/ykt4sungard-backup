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

import java.util.HashMap;

import oasis.names.tc.wsrp.v1.types.ModelDescription;
import oasis.names.tc.wsrp.v1.types.PropertyList;

import org.w3c.dom.Element;

/**
 This interface provides access to the portlet's internal state.
 * @author Stefan Behl
 *
 */
public interface PortletState {

	/**
	 * Method getAsString.
	 * @return String
	 */
	public String getAsString();

	/**
	 * Method getPortletHandle
	 * @return portletHandle as String
	 */
	public String getPortletHandle();

	/**
	 * Method setPortletHandle
	 * @param portletHandle as String
	 */
	public void setPortletHandle(String portletHandle);

	/**
	 * Method getAsPropertyList.
	 * @return Iterator
	 */
	public PropertyList getAsPropertyList();

	/**
	 * Method setAsString.
	 * @param state
	 */
	public void setAsString(String state);

	/**
	 * Method setAsPropertyList.
	 * @param props
	 */
	public void setAsPropertyList(PropertyList props);

	/**
	 * Method getAsPropertylist.
	 * @param names
	 */
	public PropertyList getAsPropertylist(String[] names);

	/**
	 * Method getAsString.
	 * @param names
	 * @return String
	 */
	public String getAsString(String[] names);

	/**
	 * Method setAsElement.
	 * @param props
	 */
	public void setAsElement(Element props);

	/**
	 * Method getAsElement.
	 */
	public Element getAsElement();

	/**
	 * Method getAsElement.
	 * @param names
	 */
	public Element getAsElement(String[] names);

	/**
	 * Return the Property map
	 * @return HashMap
	 */
	public HashMap getPropertyMap();

	/**
	 * Set the Property map
	 * @param propertyMap properties 
	 */
	public void setPropertyMap(HashMap propertyMap);

	/**
	 Set the WSRP model description
	 @param modelDescription WSRP model description
	 */
	public void setModelDescription(ModelDescription modelDescription);

	/**
	 Return the WSRP model description
	 @return ModelDescription
	 */
	public ModelDescription getModelDescription();

}