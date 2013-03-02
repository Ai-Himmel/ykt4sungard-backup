/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.wsrp;

import com.liferay.util.CollectionFactory;

import java.util.Iterator;
import java.util.Map;

import oasis.names.tc.wsrp.v1.types.RegistrationContext;
import oasis.names.tc.wsrp.v1.types.RegistrationData;

import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.producer.ConsumerRegistry;
import org.apache.wsrp4j.producer.Registration;
import org.apache.wsrp4j.producer.driver.RegistrationImpl;
import org.apache.wsrp4j.producer.provider.DescriptionHandler;
import org.apache.wsrp4j.producer.provider.Provider;
import org.apache.wsrp4j.util.HandleGenerator;
import org.apache.wsrp4j.util.HandleGeneratorFactoryImpl;

/**
 * <a href="ConsumerRegistryImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @version $Revision: 1.5 $
 *
 */
public class ConsumerRegistryImpl implements ConsumerRegistry {

	public ConsumerRegistryImpl(Provider provider) throws WSRPException {
		String MN = "Constructor";
		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		this._provider = provider;

		if (provider != null) {

			DescriptionHandler descrHandler = null;

			if ((descrHandler = provider.getDescriptionHandler()) != null) {
				_requiresRegistration = descrHandler.isRegistrationRequired();
			}
		}

		_genFactory = new HandleGeneratorFactoryImpl();
		_generator = _genFactory.getHandleGenerator();

		_registrations = CollectionFactory.getSyncHashMap();

		// restore registration objects from persistent file store
		if (_logger.isLogging(Logger.TRACE_MEDIUM)) {
			_logger.text(Logger.TRACE_MEDIUM, MN,
					"ConsumerRegistry successfully constructed.");
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}

	}

	/**
	 * Provides information about whether this producer requires registration or
	 * not. Queries the DescriptionHandler to figure this out.
	 *
	 * @return A boolean indicating whether registration is required or not
	 */
	public boolean isRegistrationRequired() {

		return this._requiresRegistration;

	}

	/**
	 * Creates a new registration-object for a certain consumer, adds it to the
	 * hashmap and returns it.
	 *
	 * @param registrationData
	 *            RegistrationData-object
	 *
	 * @return Registration Registration-object
	 *
	 * @throws WSRPException
	 */
	public Registration register(RegistrationData registrationData)
			throws WSRPException {

		String MN = "register";
		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		Registration newRegistration = new RegistrationImpl();

		RegistrationContext newContext = new RegistrationContext();

		newContext.setRegistrationHandle(_generator.generateHandle());
		newContext.setRegistrationState(null);
		newContext.setExtensions(null);

		// set RegistrationData, RegistrationContext etc.
		newRegistration.setRegistrationData(registrationData);
		newRegistration.setRegistrationContext(newContext);

		// add new registration to hashmap
		_registrations.put(newContext.getRegistrationHandle(), newRegistration);

		if (_logger.isLogging(Logger.TRACE_MEDIUM)) {
			_logger.text(Logger.TRACE_MEDIUM, MN,
					"Consumer with registration handle: "
							+ newContext.getRegistrationHandle()
							+ " is registered");
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}

		return newRegistration;
	}

	/**
	 * Returns a certain registration identified by regHandle.
	 *
	 * @param regHandle
	 *            String representing the regHandle.
	 *
	 * @return Registration Registration-object identified by regHandle.
	 */
	public Registration get(String regHandle) {
		return (Registration) _registrations.get(regHandle);
	}

	/**
	 * Returns all registrations (of all consumers) currently stored in the
	 * hashmap.
	 *
	 * @return Iterator of an registration collection containing all
	 *         registrations.
	 */
	public Iterator getAll() {
		return _registrations.values().iterator();
	}

	/**
	 * Deletes the registration of a certain consumer (identified by regHandle)
	 * from the hashmap.
	 *
	 * @param regHandle
	 *            String representing the regHandle.
	 */
	public void deregister(String regHandle) {

		String MN = "deregister";
		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		_registrations.remove(regHandle);

		if (_logger.isLogging(Logger.TRACE_MEDIUM)) {
			_logger.text(Logger.TRACE_MEDIUM, MN,
					"Consumer with registration handle: " + regHandle
							+ " is now deregistered.");
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	/**
	 * Evaluates whether a registration with regHandle exists or not. Returns
	 * true if registration exists, else false.
	 *
	 * @param regHandle
	 *            String representing the regHandle.
	 *
	 * @return Returns true if registration exists, else false.
	 */
	public boolean check(String regHandle) {

		String MN = "check";
		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		// check registration
		boolean regExists = false;
		if (_registrations.get(regHandle) != null) {
			regExists = true;

			if (_logger.isLogging(Logger.TRACE_MEDIUM)) {
				_logger.text(Logger.TRACE_MEDIUM, MN,
						"Consumer with registration handle: " + regHandle
								+ " is registered");
			}
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}
		return regExists;
	}

	// initialized handle generator factory
	private HandleGeneratorFactoryImpl _genFactory = null;

	// initialized handle factory
	private HandleGenerator _generator = null;

	// indicates whether the consumer requires registration
	private boolean _requiresRegistration = false;

	// refernce to the provider
	private Provider _provider = null;

	// holds the actual consumer information
	private Map _registrations = null;

	// log and trace support
	private Logger _logger = LogManager.getLogManager().getLogger(
			this.getClass());

}