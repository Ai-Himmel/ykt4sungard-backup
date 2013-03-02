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

import org.apache.wsrp4j.producer.provider.ConsumerConfiguredPortlet;

/**
 * This class implements the ConsumerConfiguredPortlet interface. It also
 * extends the PortletImpl class.
 * 
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @see     ConsumerConfiguredPortlet, PortletImpl
 */
public class ConsumerConfiguredPortletImpl extends PortletImpl implements
		ConsumerConfiguredPortlet {

	/**                                                                      
	 * Portlet handle of the parent ProducerOfferedPortlet object 
	 */
	private String parentHandle = "";

	/**
	 * Sets the portlet handle of the parent ProducerOfferedPortlet.
	 *
	 * @param handle String representing the portlet handle of the corresponding
	 *               parent ProducerOfferedPortlet. 
	 **/
	public void setParentHandle(String handle) {
		parentHandle = handle;
	}

	/**
	 * Returns the portlet handle of the corresponding parent ProducerOfferedPortlet.
	 *
	 * @return String representing the portlet handle of the corresponding parent
	 *         ProducerOfferedPortlet.
	 **/
	public String getParentHandle() {
		return parentHandle;
	}

	/**
	 * Redefines the clone-method of the Cloneable-interface. This is necessary
	 * as the clone-method is declared protected in the Object class.
	 *
	 * @return    Object representing the cloned object.
	 */
	public Object clone() {
		ConsumerConfiguredPortlet clone = new ConsumerConfiguredPortletImpl();
		clone.setParentHandle(parentHandle);
		return clone;
	}

}