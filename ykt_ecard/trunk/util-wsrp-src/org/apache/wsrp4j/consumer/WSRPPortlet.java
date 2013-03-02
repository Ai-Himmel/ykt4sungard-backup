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

import oasis.names.tc.wsrp.v1.types.PortletContext;

/**
 * Defines a consumer-side representation of a remote portlet.
 * A portlet is uniquely identified by its portlet key.
 * Consumer configured portlets are the result of clone operations on
 * existing portlets (parents).
 * 
 * @author Stephan Laertz 
 **/
public interface WSRPPortlet {

	/**
	 * Get the portlet key of the portlet. The key can be used to reference
	 * to the portlet.
	 * 
	 * @return a portlet key object
	 **/
	public PortletKey getPortletKey();

	/**
	 * Set the portlet key of the portlet.
	 * 
	 * @param portletKey The portlet key of the portlet
	 **/
	public void setPortletKey(PortletKey portletKey);

	/**
	 * Get the portlet context object which contains information about
	 * the portlet state.
	 * 
	 * @return the portlet context object of the portlet.
	 **/
	public PortletContext getPortletContext();

	/**
	 * Set the portlet context of the portlet.
	 * 
	 * @param portletContext The portlet context of the portlet
	 **/
	public void setPortletContext(PortletContext portletContext);

	/**
	 * Checks if a portlet is consumer configured portlet.
	 * 
	 * @return True if the result <code>getParent()</code> is not equal 
	 *         to the portlet handle of the portlet key.
	 **/
	public boolean isConsumerConfigured();

	/**
	 * Get the portlet handle of the parent portlet. If the portlet
	 * is not a consumer configured portlet the handle returned by this method
	 * should be the same as the handle in the portlet key returned 
	 * by <code>getPortletKey</code>.
	 * 
	 * @return the portlet handle of the parent portlet.
	 **/
	public String getParent();

	/**
	 * Set the portlet handle of the parent portlet. If the supplied 
	 * handle is not equal to the handle in the portlet key returned by 
	 * <code>getPortletKey</code> this method makes the portlet a 
	 * consumer configured portlet.
	 * 
	 * @param portletHandle the portlet handle of the parent portlet
	 **/
	public void setParent(String portletHandle);
}