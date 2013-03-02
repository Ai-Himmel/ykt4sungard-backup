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

package org.apache.wsrp4j.exception;

import java.io.InputStream;
import java.util.Properties;

import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

/**
 Holds all exception messages
 */
public class Messages {

	/** defines the lowest message code for common messages */
	public static final int COMMON_LOWER_BOUND = 1000;

	/** defines the highest message code for common messages */
	public static final int COMMON_UPPER_BOUND = 1999;

	/** defines the lowest message code for producer messages */
	public static final int PRODUCER_LOWER_BOUND = 2000;

	/** defines the highest message code for producer messages */
	public static final int PRODUCER_UPPER_BOUND = 2999;

	/** defines the lowest message code for provider messages */
	public static final int PROVIDER_LOWER_BOUND = 3000;

	/** defines the highest message code for provider messages */
	public static final int PROVIDER_UPPER_BOUND = 3999;

	/** defines the lowest message code for consumer messages */
	public static final int CONSUMER_LOWER_BOUND = 6000;

	/** defines the highest message code for consumer messages */
	public static final int CONSUMER_UPPER_BOUND = 6999;

	private static final String FILE_MSG_PROPERTIES = "wsrp-messages.properties";

	private static final String MSG_EXCEPTION_ON_LOAD = "Error while loading messages from "
			+ FILE_MSG_PROPERTIES + ".";

	private static final String MSG_NO_MSG_FOUND = "No message found.";

	private static final String MSG_NO_MSG_FOUND_FOR = "No message found for ";

	private static final String METHOD_INIT = "<init>";

	private static final String METHOD_GET = "get()";

	private static Logger logger = LogManager.getLogManager().getLogger(
			Messages.class);

	private static Properties msgMap = new Properties();

	private static Messages messages = new Messages();

	/**
	 Private constructor loads messages from <code>messages.properties</code> file in
	 <code>org.apache.wsrp4j.exception</code>
	 */
	private Messages() {

		//load properties file
		try {
			InputStream in = getClass().getClassLoader().getResourceAsStream(
					FILE_MSG_PROPERTIES);
			msgMap.load(in);
		}
		catch (Exception e) {
			logger.text(Logger.ERROR, METHOD_INIT, e, MSG_EXCEPTION_ON_LOAD);
		}
	}

	/**
	 Returns an error message for a message code
	 @param msgCode code that identifies a message
	 @return String representing a message
	 */
	public static String get(int msgCode) {
		String msg = (String) msgMap.get(new Integer(msgCode).toString());
		if (msg == null) {
			msg = MSG_NO_MSG_FOUND;
			if (logger.isLogging(Logger.TRACE_LOW)) {
				logger.text(Logger.TRACE_LOW, METHOD_GET, MSG_NO_MSG_FOUND_FOR
						+ msgCode + " in " + FILE_MSG_PROPERTIES + ".");
			}
		}
		return msg;
	}
}