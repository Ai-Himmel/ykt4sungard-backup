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

package org.apache.wsrp4j.log;

import java.io.InputStream;
import java.util.Properties;

/**
 Logger factory return an appropriate implementation of a Logger
 */
public class LogManager {

	private static final String LOG_PROPERTIES_FILE = "wsrp-logger.properties";

	private static final String PROPERTY_PREFIX = "wsrp4j.logger.";

	private static final String GLOBAL_LOG_LEVEL_PROPERTY = "wsrp4j.logger";

	private static int globalLogLevel = Logger.ERROR;

	private static Properties wsrp4jLevels = new Properties();

	private static LogManager logManager = new LogManager();

	/**
	 private constructor prohibits sub-classing
	 */
	private LogManager() {
		try {
			InputStream propertiesInputStream;
			propertiesInputStream = this.getClass().getClassLoader()
					.getResourceAsStream(LOG_PROPERTIES_FILE);
			wsrp4jLevels.load(propertiesInputStream);
		}
		catch (Exception e) {
			System.err
					.println("LogManager: Error while initializing log properties. StackTrace follows.");
			e.printStackTrace(System.err);
		}
		try {
			//load log4j configuration from properties
			org.apache.log4j.PropertyConfigurator.configure(wsrp4jLevels);

			//log used properties file
			org.apache.log4j.Logger.getLogger(this.getClass()).info(
					"Logger.properties file: " + LOG_PROPERTIES_FILE);

			//initialize wsrp4j-logger levels from properties
			int userDefinedGlobalLevel = getLevelFromString(wsrp4jLevels
					.getProperty(GLOBAL_LOG_LEVEL_PROPERTY));
			if (userDefinedGlobalLevel != 0) {
				globalLogLevel = userDefinedGlobalLevel;
			}

			//log global wsrp4jlog level
			org.apache.log4j.Logger.getLogger(this.getClass()).info(
					"Global log level: "
							+ this.getLevelAsString(globalLogLevel));

		}
		catch (Exception e) {
			System.err.println("LogManager: Error while initializing Logger.");
			// StackTrace follows.");
			//e.printStackTrace(System.err);
		}
	}

	/**
	 Returns the LogManager instance
	 
	 @return LogManager instance
	 */
	public static LogManager getLogManager() {
		return logManager;
	}

	/**
	 Returns a Logger instance for the calling class
	 
	 @param aClass The class that requests the logger instance.
	 @return instance of <CODE>Logger</CODE>.
	 */
	public Logger getLogger(Class aClass) {
		//create a Logger
		org.apache.log4j.Logger logger = org.apache.log4j.Logger
				.getLogger(aClass);

		//determine log level for aClass
		String propertyName = PROPERTY_PREFIX + aClass.getName();
		int level = globalLogLevel;
		int userDefinedLevel = getLevelFromString(wsrp4jLevels
				.getProperty(propertyName));
		if (userDefinedLevel != 0) {
			level = userDefinedLevel;
		}
		return new LoggerImpl(logger, level);
	}

	/*
	 Returns an int LogLevel defined by a String {ERROR, WARN, INFO, TRACE_HIGH, TRACE_MEDIUM, TRACE_LOW}.
	 Use this method to convert levels defined in a properties file
	 If the string does not represent a correct level this method returns 0
	 */
	private int getLevelFromString(String s) {
		if (s != null) {
			if (s.equalsIgnoreCase("ERROR")) {
				return Logger.ERROR;
			}
			else if (s.equalsIgnoreCase("WARN")) {
				return Logger.WARN;
			}
			else if (s.equalsIgnoreCase("INFO")) {
				return Logger.INFO;
			}
			else if (s.equalsIgnoreCase("TRACE_LOW")) {
				return Logger.TRACE_LOW;
			}
			else if (s.equalsIgnoreCase("TRACE_MEDIUM")) {
				return Logger.TRACE_MEDIUM;
			}
			else if (s.equalsIgnoreCase("TRACE_HIGH")) {
				return Logger.TRACE_HIGH;
			}
			else {
				return 0;
			}
		}
		else {
			return 0;
		}
	}

	/*
	 Translates a int logLevel to a String
	 */
	private String getLevelAsString(int level) {
		String sLevel;
		if (level < Logger.WARN) {
			sLevel = "ERROR";
		}
		else if (level < Logger.INFO) {
			sLevel = "WARN";
		}
		else if (level < Logger.TRACE_LOW) {
			sLevel = "INFO";
		}
		else if (level < Logger.TRACE_MEDIUM) {
			sLevel = "TRACE_LOW";
		}
		else if (level < Logger.TRACE_HIGH) {
			sLevel = "TRACE_MEDIUM";
		}
		else {
			sLevel = "TRACE_HIGH";
		}
		return sLevel;
	}
}