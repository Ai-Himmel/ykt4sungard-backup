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

import java.io.Serializable;

import org.apache.wsrp4j.producer.provider.Portlet;
import org.apache.wsrp4j.producer.provider.ProducerOfferedPortlet;

/**
 * <p>This abstract class implements the Portlet interface encapsulating
 * Portlet-objects. Provides setters and getters.</p>
 * <p>Implements the Cloneable interface to enable cloning of portlets.</p>
 * <p>Implements the Serializable interface to enable serialization, e.g. to
 * an XML-file.</p>
 * 
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @see     ProducerOfferedPortlet  
 */
public abstract class PortletImpl implements Portlet, Serializable {

	private String handle = "";

	/**
	 * Returns the portletHandle.
	 *
	 * @return    A String representing the portletHandle.
	 */
	public String getPortletHandle() {
		return this.handle;
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
	 * Redefines the clone-method of the Cloneable-interface. This is necessary
	 * as the clone-method is declared protected in the Object class.
	 *
	 * @return    Object representing the cloned object.
	 */
	public abstract Object clone();
}