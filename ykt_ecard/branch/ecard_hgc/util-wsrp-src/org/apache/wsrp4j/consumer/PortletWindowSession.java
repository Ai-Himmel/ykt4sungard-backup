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

package org.apache.wsrp4j.consumer;

import oasis.names.tc.wsrp.v1.types.MarkupContext;

/**
 * The portlet window session is a session which is unique for
 * every window of a portlet instance. 
 * 
 **/
public interface PortletWindowSession {
	/**
	 * Get the ID of the portlets window this session belongs to.
	 * 
	 * @return The ID of the portlet window.
	 **/
	public String getWindowID();

	/**
	 * Set the ID of the portlets window this sessions belongs to.
	 * 
	 * @param windowID The ID of the portlet window.    
	 **/
	public void setWindowID(String windowID);

	/**
	 * Get the markup context which has been cached. This might be useful
	 * to retrieve the markup which was returned <code>performBlockingInteraction</code>
	 * calls in order to save an additional <code>getMarkup</code> call.
	 * 
	 * @return The cached markup context or null in case the cache is empty.
	 **/
	public MarkupContext getCachedMarkup();

	/**
	 * Update the cache which holds the markup context. This might be useful
	 * to store the markup which was returned by <code>performBlockingInteraction</code>
	 * calls in order to save an additional <code>getMarkup</code> call.
	 * Updateing the cache with a null value clears the markup cache.
	 * 
	 * @param markupContext The markup context or null in case the cache should be cleared.
	 **/
	public void updateMarkupCache(MarkupContext markupContext);

	/**
	 * Get the portlet session this window session belongs to.
	 * 
	 * @return The <code>PortletSession</code> this window session belongs to.     
	 **/
	public PortletSession getPortletSession();
}