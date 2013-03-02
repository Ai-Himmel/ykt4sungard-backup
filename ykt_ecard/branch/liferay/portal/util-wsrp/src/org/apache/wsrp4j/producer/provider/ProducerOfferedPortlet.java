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

/**
 * Provides an interface to a class encapsulating a ProducerOfferedPortlet-
 * object.
 * 
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @see     Portlet
 */
public interface ProducerOfferedPortlet extends Portlet {

	/**
	 * Returns a flag indicating whether registration is required or not.
	 *
	 * @return    Boolean flag.
	 */
	public boolean isRegistrationRequired();

	/**
	 * Sets the flag indicating whether registration is required or not. 
	 *
	 * @param  required  Boolean to be assigned to the requiresReg.-flag.
	 */
	public void setRegistrationRequired(boolean required);

	/**
	 * Adds a clone referencing a ConsumerConfiguredPortlet.
	 *
	 */
	public void addClone(ConsumerConfiguredPortlet cce);

	/**
	 * Deletes a clone-handle referencing a ConsumerConfiguredPortlet.
	 *
	 * @param   cce  String representing the portlet-handle of the
	 *                 corresponding ConsumerConfiguredPortlet.
	 */
	public void deleteClone(ConsumerConfiguredPortlet cce);

	/**
	 * Returns an iterator containing all clones.
	 *
	 * @return  Iterator
	 */
	public Iterator getClones();

	/**
	 * Redefines the clone-method of the Cloneable-interface. This is necessary
	 * as the clone-method is declared protected in the Object class.
	 *
	 * @return  Object Object representing the cloned object.
	 */
	public Object clone();

}