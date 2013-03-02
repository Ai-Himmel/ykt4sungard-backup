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

import oasis.names.tc.wsrp.v1.types.ModelDescription;
import oasis.names.tc.wsrp.v1.types.PropertyList;

/**
 Manages the portlet states. Provides convenience mehtods usefull for state handling
 * @author Stefan Behl
 *
 */
public interface PortletStateManager {

	/** defines an error state */
	public static final int INITIALIZATION_FAILED = 3007;//TODO do we need this?

	/**
	 Returns the portlet's state for a given portlet handle
	 @param portletHandle String representing a portlet handle
	 @return PortletState
	 */
	public PortletState get(String portletHandle);

	/**
	 Returns the portlet's state as String for a given portlet handle
	 @param  portletHandle String representing a portlet handle
	 @return String representing the portlet's state
	 */
	public String getAsString(String portletHandle);

	/**
	 Converts a PortletState object to java.lang.String
	 @param state PortletState
	 @return java.lang.String representing a portlet state
	 */
	public String getAsString(PortletState state);

	/**
	 Converts a subset of the portlet stateto java.lang.String.
	 The subset of the state is represented by an array of names.
	 @param portletHandle String representing a portlet handle
	 @param names array of String 
	 @return String representing a subset of a portlte state
	 */
	public String getAsString(String portletHandle, String[] names);

	/**
	 Returns the portlet's state as PropertyList
	 @param portletHandle String representing a portlte handle
	 @return PropertyList
	 */
	public PropertyList getAsPropertyList(String portletHandle);

	/**
	 Converts a portlet's state to a PropertyList
	 @param  state the portlet's state
	 @return PropertyList
	 */
	public PropertyList getAsPropertyList(PortletState state);

	/**
	 Converts a subset of the portlet state to a PropertyList. The subset
	 of the state is represented by an array of names.
	 @param portletHandle String representing a portlet handle
	 @param names array of String 
	 @return PropertyList
	 */
	public PropertyList getAsPropertyList(String portletHandle, String[] names);

	/**
	 Set the portlet's state
	 @param portletHandle String representing a portlet handle
	 @param state PortletState
	 */
	public void set(String portletHandle, PortletState state);

	/**
	 Set the portlet state
	 @param portletHandle String representing a portlet handle
	 @param state String representing the portlet's state
	 */
	public void setAsString(String portletHandle, String state);

	/**
	 Set the portlet state
	 @param  portletHandle String representing a portlet handle
	 @param state PropretyList representing the portlte's state
	 */
	public void setAsPropertyList(String portletHandle, PropertyList state);

	/**
	 Destroys a portlet state
	 @param  portletHandle String representing a portlet handle
	 */
	public void destroy(String portletHandle);

	/**
	 Returns the WSRP model description for a portlet's state.
	 @param  portletHandle String representing a portlet handle
	 @param desiredLocales determine the desired locales
	 @param sendAllLocales indicates if all locales are desired
	 @return ModelDescription
	 */
	public ModelDescription getModelDescription(String portletHandle,
			String[] desiredLocales, boolean sendAllLocales);

}