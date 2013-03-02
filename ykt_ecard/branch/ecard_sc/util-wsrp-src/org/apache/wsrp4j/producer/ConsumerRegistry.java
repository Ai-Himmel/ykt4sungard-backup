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

package org.apache.wsrp4j.producer;

import java.util.Iterator;

import oasis.names.tc.wsrp.v1.types.RegistrationData;

import org.apache.wsrp4j.exception.WSRPException;

/**
 * This interface provides access to the ConsumerRegistry. The ConsumerRegistry
 * keeps all Consumer registrations with this Producer. All registrations are
 * identified by a registration handle.
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 */
public interface ConsumerRegistry {

	/**
	 * Provides information about whether this producer requires
	 * registration or not.
	 *
	 * @return A boolean indicating whether registration is required or not.
	 */
	public boolean isRegistrationRequired();

	/**
	 * Creates a new registration-object for a certain consumer,
	 * adds it to the consumer registry and returns it.
	 *
	 * @param  registrationData RegistrationData-object
	 *
	 * @return new registration-object
	 */
	public Registration register(RegistrationData registrationData)
			throws WSRPException;

	/**
	 * Returns a certain registration identified by regHandle.
	 *
	 * @param  regHandle    String representing the regHandle.
	 *
	 * @return registration-object identified by regHandle.
	 */
	public Registration get(String regHandle);

	/**
	 * Returns all registrations (of all consumers) currently stored
	 * in the consumer registry.
	 *
	 * @return Iterator of a registration collection containing all
	 *         registrations.
	 */
	public Iterator getAll();

	/**
	 * Deletes the registration of a certain consumer (identified by regHandle).
	 *
	 * @param regHandle  String representing the regHandle.
	 */
	public void deregister(String regHandle);

	/**
	 * Evaluates whether a consumer identified by regHandle is registered or not.
	 *
	 * @param regHandle  String representing the regHandle.
	 *
	 * @returns A boolean indicating whether registration exists or not.
	 *          Returns true if registration exists, else false.
	 */
	public boolean check(String regHandle);

}