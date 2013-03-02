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

import org.apache.wsrp4j.exception.WSRPException;

/**
 * <p>This class provides the interface to the portlet pool. All portlets
 * (producer offered as well as consumer configured portlets) should be kept
 * within the portlet pool. It is recommended that this interface is
 * implemented by a container associating portlet handles with portlet-objects.
 * </p>
 *
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 */
public interface PortletPool {

	/**
	 * <p>Clones an portlet (Producer Offered or Consumer Configured Portlet)
	 * associated by portlet-handle. Only the portlet-object should be cloned,
	 * not the portlet-description the portlet references.</p>
	 * <p>Adds the new Consumer Configured Portlet (after assigning a new
	 * portletHandle)to the hashmap after cloning.</p>
	 * <p>Creates a new portlet state corresponding to the portlet state of
	 * the portlet to be cloned by calling the PortletStateManager.</p>
	 * <p>Throws CommonException if portlet to be cloned could not be found</p>
	 *
	 * @param     portletHandle  String identifying the portlet to be cloned.
	 *
	 * @return    ConsumerConfiguredPortlet  The portlet-clone.
	 */
	public Portlet clone(String portletHandle) throws WSRPException;

	/**
	 * Returns all portlets that are currently stored within the
	 * PortletPool.
	 *
	 * @return    Iterator of an portlet collection containing all portlets.
	 */
	public Iterator getAllProducerOfferedPortlets();

	/**
	 * Returns all portlets that are currently stored within the
	 * PortletPool.
	 *
	 * @return    Iterator of an portlet collection containing all portlets.
	 */
	public Iterator getAllConsumerConfiguredPortlets();

	/**
	 * Returns a certain portlet identified by portletHandle.
	 * Throws CommonException if there is no portlet corresponding to portletHandle.
	 *
	 * @param     portletHandle  String representing the portletHandle.
	 *
	 * @return    ProducerOfferedPortlet portlet-object identified by portletHandle.
	 */
	public Portlet get(String portletHandle) throws WSRPException;

	/**
	 * <p>Deletes the portlet identified by portletHandle from the PortletPool.
	 * Only consumer configured portlets can be deleted, NOT producer offered ones.
	 * After update, the persistent file store is refreshed.</p>
	 * <p>Deletes all existing portlet sessions (SessionHandler) and portlet states
	 * (PortletStateManager) as well.</p>
	 * <p>Throws CommonException if portlet corresponding to portletHandle could not
	 * be found.</p> 
	 *
	 * @param  portletHandle  String representing the portletHandle.
	 *
	 * @return Boolean indicating if deletion was successful. Returns false, if portletHandle
	 *         refers to a producer offered portlet.
	 */
	public boolean destroy(String portletHandle) throws WSRPException;

	/**
	 * Deletes several portlets from the PortletPool.
	 *
	 * @param  portletHandles  Iterator of portletHandles.
	 *
	 * @return Iterator containing those portletHandles refering to portlets
	 *         that could not be deleted (e.g. producer offered portlets).
	 */
	public Iterator destroySeveral(Iterator portletHandles);

}