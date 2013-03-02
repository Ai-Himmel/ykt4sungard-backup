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

/**
 * The consumer provides access to consumer specific components.
 * 
 * @author <a href='mailto:peter.fischer@de.ibm.com'>Peter Fischer</a>
 */
public interface Consumer {

	/**
	 * Get the session handler of the consumer.
	 * 
	 * @return Interface to the consumer specific session handler
	 **/
	public SessionHandler getSessionHandler();

	/**
	 * Get the portlet registry of the consumer.
	 * 
	 * @return Interface to the consumer specific portlet registry
	 **/
	public PortletRegistry getPortletRegistry();

	/**
	 * Get the portlet driver registry of the consumer.
	 * 
	 * @return Interface to the consumer specific portlet driver registry
	 **/
	public PortletDriverRegistry getPortletDriverRegistry();

	/**
	 * Get the producer registry of the consumer.
	 * 
	 * @return The consumer specific producer registry
	 **/
	public ProducerRegistry getProducerRegistry();

	/**
	 * Get the user registry of the consumer.
	 * 
	 * @return The consumer specific user registry
	 **/
	public UserRegistry getUserRegistry();

	/**
	 * Get the url template composer for template proccessing
	 * 
	 * @return Interface to the consumer specific template composer
	 **/
	public URLTemplateComposer getTemplateComposer();

	/**
	 * Get the url rewriter for consumer url-rewriting
	 * 
	 * @return The consumer specific url rewriter
	 **/
	public URLRewriter getURLRewriter();

}