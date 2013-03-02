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

package org.apache.wsrp4j.producer.driver;

import oasis.names.tc.wsrp.v1.types.RegistrationContext;
import oasis.names.tc.wsrp.v1.types.RegistrationData;

import org.apache.wsrp4j.producer.Registration;

/**
 * <p>This class implements the Registration interface encapsulating
 * a registration-object. Provides setters and getters.</p>
 * <p>Implements the Serializable interface to enable serialization, e.g. to
 * an XML-file.</p>
 * 
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @see     Registration  
 */
public class RegistrationImpl implements Registration, java.io.Serializable {
	//a WSRP registration context
	private RegistrationContext context = null;

	//WSRP registration data
	private RegistrationData data = null;

	/**
	 * Returns the registration context. The registration context contains a
	 * registration handle (required) and optionally a registration state.
	 *
	 * @return RegistrationContext
	 */
	public RegistrationContext getRegistrationContext() {
		return this.context;
	}

	/**
	 * Returns the registration data. Supplies consumer data required for
	 * registration with a Producer.
	 *
	 * @return RegistrationData
	 */
	public RegistrationData getRegistrationData() {
		return this.data;
	}

	/**
	 * Sets the registration context. The registration context contains a
	 * registration handle (required) and optionally a registration state.
	 *
	 * @param registrationContext The registration context of a certain Consumer.
	 */
	public void setRegistrationContext(RegistrationContext registrationContext) {
		this.context = registrationContext;
	}

	/**
	 * Sets the registration data. Supplies consumer data required for
	 * registration with a Producer.
	 *
	 * @param registrationData The registration data of a certain Consumer.
	 */
	public void setRegistrationData(RegistrationData registrationData) {
		this.data = registrationData;
	}

}