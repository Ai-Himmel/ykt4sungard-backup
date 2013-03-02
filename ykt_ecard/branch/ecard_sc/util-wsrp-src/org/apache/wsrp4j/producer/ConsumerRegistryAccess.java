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

import java.util.Properties;

import org.apache.wsrp4j.exception.ErrorCodes;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.exception.WSRPXHelper;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.util.Utility;

/**
 * This class provides a static method to access the ConsumerRegistry.
 * Reads in the file "wsrp-services.properties".
 *
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 */
public class ConsumerRegistryAccess {

	// the name of the .properties file
	private static String WSRP_SERVICES = "wsrp-services.properties";

	/** String representing a factory type */
	public static String CONSUMER_REGISTRY_FACTORY = "consumer.registry.factory";

	// the content of the properties file
	private static Properties pFactories = null;

	// holds an instance of a consumer registry
	private static ConsumerRegistry consumerRegistry = null;

	// log and trace support
	private static Logger logger = LogManager.getLogManager().getLogger(
			ConsumerRegistryAccess.class);

	/**
	 * Fetches a ConsumerRegistry-instance utilizing the read
	 * ConsumerRegistryFactory and returns it.
	 *
	 * @return ConsumerRegistry-interface.
	 */
	public static ConsumerRegistry getConsumerRegistry() throws WSRPException {
		String MN = "getConsumerRegistry";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (consumerRegistry == null) {
			// get ConsumerRegistry
			ConsumerRegistryFactory factory = (ConsumerRegistryFactory) getFactory(CONSUMER_REGISTRY_FACTORY);
			consumerRegistry = factory.getConsumerRegistry(ProviderAccess
					.getProvider());
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return consumerRegistry;
	}

	/**
	 Internal mehtod.
	 Returns a configured Factory class.
	 @param type java.lang.String representing the factory type.
	 @return java.lang.Object
	 */
	private static Object getFactory(String type) throws WSRPException {
		String MN = "getFactory";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		Object obj = null;

		try {
			pFactories = Utility.loadPropertiesFromFile(WSRP_SERVICES);
			String factoryName = (String) pFactories.get(type);
			Class cl = Class.forName(factoryName);

			if (logger.isLogging(Logger.TRACE_HIGH)) {
				logger.exit(Logger.TRACE_HIGH, MN);
			}

			obj = cl.newInstance();

		}
		catch (Exception e) {

			WSRPXHelper.throwX(logger, Logger.ERROR, MN,
					ErrorCodes.CONSUMER_REGISTRY_FACTORY_NOT_FOUND);

		}

		return obj;
	}
}