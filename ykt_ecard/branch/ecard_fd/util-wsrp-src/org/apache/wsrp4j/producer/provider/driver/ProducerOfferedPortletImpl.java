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

package org.apache.wsrp4j.producer.provider.driver;

import java.util.Iterator;
import java.util.LinkedList;

import org.apache.wsrp4j.producer.provider.ConsumerConfiguredPortlet;
import org.apache.wsrp4j.producer.provider.ProducerOfferedPortlet;

/**
 * <p>This class implements the ProducerOfferedPortlet interface encapsulating
 * ProducerOfferedPortlet-objects. Provides setters and getters.</p>
 * 
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @see     ProducerOfferedPortlet  
 */
public class ProducerOfferedPortletImpl extends PortletImpl implements
		ProducerOfferedPortlet {
	// handle ID
	private String handle = "";

	// boolean, if registration is required or not
	private boolean requiresRegistration = false;

	// list of clone handles for this ProducerOfferedPortlet
	public LinkedList cloneHandles = null;

	/**
	 * constructor
	 */
	public ProducerOfferedPortletImpl() {
		cloneHandles = new LinkedList();
	}

	/**
	 * Returns the portletHandle.
	 *
	 * @return    A String representing the portletHandle.
	 */
	public String getPortletHandle() {
		return this.handle;
	}

	/**
	 * Returns a flag indicating whether registration is required or not.
	 *
	 * @return    Boolean flag.
	 */
	public boolean isRegistrationRequired() {
		return this.requiresRegistration;
	}

	/**
	 * Sets the flag indicating whether registration is required or not. 
	 *
	 * @param     required  Boolean to be assigned to the requiresReg.-flag.
	 */
	public void setRegistrationRequired(boolean required) {
		this.requiresRegistration = required;
	}

	/**
	 * Sets the portletHandle to enable identification of the portlet.
	 *
	 * @param     portletHandle  String to be assigned to handle.
	 */
	public void setPortletHandle(String portletHandle) {
		this.handle = portletHandle;
	}

	/**
	 * Adds a clone referencing a ConsumerConfiguredPortlet.
	 *
	 */
	public void addClone(ConsumerConfiguredPortlet cce) {
		cloneHandles.add(cce);
	}

	/**
	 * Deletes a clone referencing a ConsumerConfiguredPortlet.
	 *
	 * @param   cce  String representing the portlet-handle of the
	 *                 corresponding ConsumerConfiguredPortlet.
	 */
	public void deleteClone(ConsumerConfiguredPortlet cce) {
		if (cloneHandles.remove(cce)) {
		}
	}

	/**
	 * Returns an iterator containing all clone-handles.
	 *
	 * @return  Iterator
	 */
	public Iterator getClones() {
		return cloneHandles.iterator();
	}

	/**
	 * Redefines the clone-method of the Cloneable-interface. This is necessary
	 * as the clone-method is declared protected in the Object class.
	 *
	 * @return    Object representing the cloned object.
	 */
	public Object clone() {

		ConsumerConfiguredPortlet clone = new ConsumerConfiguredPortletImpl();

		clone.setParentHandle(handle);

		return clone;
	}

}