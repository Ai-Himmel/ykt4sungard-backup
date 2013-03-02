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

package org.apache.wsrp4j.consumer;

import java.util.Map;

/**
 * This interface provides methods to query the consumer's urls. 
 * These methods could be used to implement consumer url rewriting.
 *
 * @author <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 **/
public interface URLGenerator {

	/**
	 * Creates a URL pointing to the consumer,triggering a performBlockingInteraction call.    
	 * 
	 * @param params A map with all parameters which should be appended
	 *               to the URL.
	 *
	 * @return a blockingInteraction URL
	 **/
	public String getBlockingActionURL(Map params);

	/**
	 * Creates a URL pointing to the consumer,triggering a getMarkup call.    
	 * 
	 * @param params A map with all parameters which should be appended
	 *               to the URL.
	 *
	 * @return a getMarkup URL
	 **/
	public String getRenderURL(Map params);

	/**
	 * Creates a URL pointing to the consumer,triggering the consumer
	 * to fetch a certain resource
	 * 
	 * @param params A map with all parameters which should be appended
	 *               to the URL.
	 *
	 * @return a resource URL
	 **/
	public String getResourceURL(Map params);

	/**
	 * Creates a 'url' that the consumer can use to namespace tokens.    
	 *     
	 *
	 * @return a prefix which ca nbe used to namespace tokens.
	 **/
	public String getNamespacedToken(String token);

}