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

package org.apache.wsrp4j.util;

import java.io.InputStream;
import java.util.Properties;

import org.apache.wsrp4j.exception.ErrorCodes;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.exception.WSRPXHelper;

public class Utility {

	/**
	 * Loads a property file with the given name using the class loader.
	 * 
	 * @return A <code>Properties</code> object containig the properties in the file
	 * @throws WSRPException if any error occured
	 **/
	public static Properties loadPropertiesFromFile(String fileName)
			throws WSRPException {

		try {
			// read in .properties-file
			InputStream in = Utility.class.getClassLoader()
					.getResourceAsStream(fileName);
			Properties properties = new Properties();
			properties.load(in);

			return properties;

		}
		catch (Exception e) {

			WSRPXHelper.throwX(ErrorCodes.PROPERTY_FILE_NOT_FOUND, e);

		}

		return null;

	}

}