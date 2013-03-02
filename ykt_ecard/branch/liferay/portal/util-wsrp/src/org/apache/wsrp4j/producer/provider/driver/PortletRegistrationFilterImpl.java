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

import java.util.HashMap;
import java.util.Iterator;

import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.producer.provider.PortletRegistrationFilter;
import org.apache.wsrp4j.producer.provider.PortletRegistrationFilterWriter;

/**
 * This class implements the interfaces PortletRegistrationFilter and
 * PortletRegistrationFilterWriter.
 *
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 * @author <a href="mailto:Ralf.Altrichter@de.ibm.com">Ralf Altrichter</a>
 */
public class PortletRegistrationFilterImpl implements
		PortletRegistrationFilter, PortletRegistrationFilterWriter {

	// a filter 
	private static PortletRegistrationFilterImpl filter = null;

	// collects ConsumerPortletRegistration objects. RegistrationHandle
	// is the key
	private static HashMap consumerPortletRegistrationMap = new HashMap();

	// for logging and exception support
	private Logger logger = LogManager.getLogManager().getLogger(
			this.getClass());

	/**
	 * @return PortletRegistrationFilterWriter
	 */
	public static PortletRegistrationFilterWriter createWriter() {
		if (filter == null) {
			filter = new PortletRegistrationFilterImpl();
		}

		return filter;
	}

	/**
	 * @return PortletRegistrationFilter
	 */
	public static PortletRegistrationFilter createReader() {
		if (filter == null) {
			filter = new PortletRegistrationFilterImpl();
		}

		return filter;
	}

	/**
	 * Private constructor
	 */
	private PortletRegistrationFilterImpl() {

		String MN = "Constructor";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	/**
	 * Returns all portlet handles of portlets, a certain consumer (identified
	 * by regHandle) can utilize. Returns null if there are no entries for the provided
	 * regHandle.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * 
	 * @return Iterator of portlet handles
	 */
	public Iterator getAvailable(String regHandle) {
		String MN = "getAvailable";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		Iterator iter = null;

		if (consumerPortletRegistrationMap.containsKey(regHandle)) {
			if (logger.isLogging(Logger.TRACE_MEDIUM)) {
				logger.text(Logger.TRACE_MEDIUM, MN, "RegistrationHandle "
						+ regHandle + " found in Map.");
			}

			ConsumerPortletRegistrationImpl cpr = (ConsumerPortletRegistrationImpl) consumerPortletRegistrationMap
					.get(regHandle);
			iter = cpr.getPortletHandles().iterator();
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return iter;
	}

	/**
	 * Indicates whether a certain consumer is allowed to utilize the portlet identified
	 * by portletHandle or not. Returns false if there is no entry for the provided handles.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandle String representing the portlet handle of an portlet
	 * 
	 * @return boolean indicating whether the consumer corresponding to regHandle is
	 *         allowed to use the portlet identified by portletHandle
	 */
	public boolean isAvailable(String regHandle, String portletHandle) {
		String MN = "isAvailable";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		boolean retVal = false;

		if (consumerPortletRegistrationMap.containsKey(regHandle)) {
			if (logger.isLogging(Logger.TRACE_MEDIUM)) {
				logger.text(Logger.TRACE_MEDIUM, MN, "RegistrationHandle "
						+ regHandle + "found in Map.");
			}

			ConsumerPortletRegistrationImpl cpr = (ConsumerPortletRegistrationImpl) consumerPortletRegistrationMap
					.get(regHandle);
			if (cpr.containsPortletHandle(portletHandle)) {
				retVal = true;

				if (logger.isLogging(Logger.TRACE_MEDIUM)) {
					logger.text(Logger.TRACE_MEDIUM, MN, "PortletHandle "
							+ portletHandle + "found for registration.");
				}
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return retVal;
	}

	/**
	 * Makes a certain portlet (identified by portletHandle) available to a consumer
	 * (identified by regHandle). If there is no portlet in the portlet pool that
	 * corresponds to portletHandle, the method performs nothing. 
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandle String representing the portlet handle of a consumer
	 */
	public void makeAvailable(String regHandle, String portletHandle)
			throws WSRPException {
		String MN = "makeAvailable";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		ConsumerPortletRegistrationImpl cpr = null;

		if (!consumerPortletRegistrationMap.containsKey(regHandle)) {
			cpr = new ConsumerPortletRegistrationImpl();
			cpr.setRegistrationHandle(regHandle);
			consumerPortletRegistrationMap.put(regHandle, cpr);
		}
		else {
			cpr = (ConsumerPortletRegistrationImpl) consumerPortletRegistrationMap
					.get(regHandle);
		}

		// add the current portlet handle to the registration
		cpr.addPortletHandle(portletHandle);

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	/**
	 * Makes several portlets (identified by portletHandles) available to
	 * a certain consumer (identified by regHandle). For portlet handles that do not
	 * correspond to portlets kept within the portlet pool, the method makes no
	 * availability-entry.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandles Iterator containing some portlet handles of portlets
	 * 
	 * @throws WSRPException 
	 */
	public void makeAvailable(String regHandle, Iterator portletHandles)
			throws WSRPException {
		String MN = "makeAvailable";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		while (portletHandles.hasNext()) {
			makeAvailable(regHandle, (String) portletHandles.next());
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	/**
	 * Removes an entire entry for a certain consumer (identified by regHandle).
	 * If there are no entries for the provided regHandle, the method performs
	 * nothing. The method is useful when a consumer deregisters.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 */
	public void remove(String regHandle) {
		String MN = "remove";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (consumerPortletRegistrationMap.containsKey(regHandle)) {
			ConsumerPortletRegistrationImpl cpr = (ConsumerPortletRegistrationImpl) consumerPortletRegistrationMap
					.get(regHandle);

			consumerPortletRegistrationMap.remove(regHandle);
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

	}

	/**
	 * Abrogates the availability of a certain portlet (identified by portletHandle)
	 * regarding a certain consumer (identified by regHandle). If there is no entry
	 * for the provided regHandle and portletHandle, the method performs nothing.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandle String representing the portlet handle of a consumer
	 */
	public void remove(String regHandle, String portletHandle)
			throws WSRPException {

		String MN = "remove";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (consumerPortletRegistrationMap.containsKey(regHandle)) {
			ConsumerPortletRegistrationImpl cpr = (ConsumerPortletRegistrationImpl) consumerPortletRegistrationMap
					.get(regHandle);
			cpr.deletePortletHandle(portletHandle);

			// Is the registration list empty? No more Portlets are assigned?
			if (cpr.isEmpty()) {
				// delete the registration list 
				consumerPortletRegistrationMap.remove(regHandle);
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

	}

	/**
	 * Abrogates the availability of several portlets (identified by portletHandles)
	 * regarding a certain consumer (identified by regHandle). For portlet handles
	 * that do not correspond to portlets kept within the portlet pool, the method
	 * performs nothing.
	 *
	 * @param regHandle String representing the registration handle of a consumer
	 * @param portletHandles Iterator containing some portlet handles of portlets
	 */
	public void remove(String regHandle, Iterator portletHandles)
			throws WSRPException {
		String MN = "remove";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (portletHandles != null) {
			while (portletHandles.hasNext()) {
				remove(regHandle, (String) portletHandles.next());
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

}