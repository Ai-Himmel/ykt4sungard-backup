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

package org.apache.wsrp4j.consumer.driver;

import oasis.names.tc.wsrp.v1.types.StateChange;

import org.apache.wsrp4j.consumer.ConsumerEnvironment;
import org.apache.wsrp4j.consumer.PortletDriverRegistry;
import org.apache.wsrp4j.consumer.PortletRegistry;
import org.apache.wsrp4j.consumer.ProducerRegistry;
import org.apache.wsrp4j.consumer.SessionHandler;
import org.apache.wsrp4j.consumer.URLRewriter;
import org.apache.wsrp4j.consumer.URLTemplateComposer;
import org.apache.wsrp4j.consumer.UserRegistry;

public abstract class GenericConsumerEnvironment implements ConsumerEnvironment {

	private String consumerAgent = null;

	private String[] supportedLocales = null;

	private String[] supportedModes = null;

	private String[] supportedWindowStates = null;

	private StateChange portletStateChange = null;

	private String userAuthMethod = null;

	private String[] characterEncoding = null;

	private String[] mimeTypes = null;

	private UserRegistry userRegistry = null;

	private ProducerRegistry producerRegistry = null;

	private PortletRegistry portletRegistry = null;

	private PortletDriverRegistry portletDriverRegistry = null;

	private SessionHandler sessionHandler = null;

	private URLTemplateComposer templateComposer = null;

	private URLRewriter urlRewriter = null;

	public GenericConsumerEnvironment() {
	}

	/**
	 * Get the name of the consumer
	 * 
	 * @return The name of the consumer
	 **/
	public String getConsumerAgent() {
		return consumerAgent;
	}

	/**
	 * Set the name of the consumer
	 * 
	 * @param name The new name of the consumer    
	 **/
	public void setConsumerAgent(String name) {
		consumerAgent = name;
	}

	/**
	 * Get the locales which are supported by the consumer.
	 * (ISO-639 + "_" + ISO-3166)
	 * 
	 * @return Array with String representations of the locales which are
	 * supported by the consumer
	 **/
	public String[] getSupportedLocales() {
		return supportedLocales;
	}

	/**
	 * Set the locales which are supported by the consumer.
	 * Pattern: ISO-639 + "_" + ISO-3166
	 * 
	 * @param locales Array of String representations of the supported locales     
	 **/
	public void setSupportedLocales(String[] locales) {
		supportedLocales = locales;
	}

	/**
	 * Get the portlet modes the consumer is willing to manage.     
	 * 
	 * @return Array with string representations of the portlet modes which are
	 * supported by the consumer
	 **/
	public String[] getSupportedModes() {
		return supportedModes;
	}

	/**
	 * Set the portlet modes which are supported by the consumer.     
	 * 
	 * @param modes Array of string representations of portlet modes
	 **/
	public void setSupportedModes(String[] modes) {
		supportedModes = modes;
	}

	/**
	 * Get the window states the consumer is willing to manage.     
	 * 
	 * @return Array with string representations of the window states which are
	 * supported by the consumer
	 **/
	public String[] getSupportedWindowStates() {
		return supportedWindowStates;
	}

	/**
	 * Set the window states which are supported by the consumer.     
	 * 
	 * @param states Array of string representations of window states
	 **/
	public void setSupportedWindowStates(String[] states) {
		supportedWindowStates = states;
	}

	/**
	 * Returns a flag which is used to indicate the producer wether or not
	 * the processing of portlets is allowed to modify the portlet state.
	 * 
	 * @return A flag
	 **/
	public StateChange getPortletStateChange() {
		return portletStateChange;
	}

	/**
	 * Set a flag which is used to indicate the producer wether or not
	 * the processing of portlets is allowed to modify the portlet state.
	 * 
	 * @param portletStateChange A flag with one of the following values (OK, Clone, Fault)
	 **/
	public void setPortletStateChange(StateChange portletStateChange) {
		this.portletStateChange = portletStateChange;
	}

	/**
	 * Get the character sets the consumer wants the remote portlet to use for encoding the markup.
	 * Valid character sets are defined <a href='http://www.iana.org/assignments/character-sets'>here</a>
	 * 
	 * @return Array of string representations of the character encoding.
	 **/
	public String[] getCharacterEncodingSet() {
		return characterEncoding;
	}

	/**
	 * Set the character set the consumer wants the remote portlet to use for encoding the markup.
	 * Valid character sets are defined <a href='http://www.iana.org/assignments/character-sets'>here</a>
	 * 
	 * @param charEncoding Array of string representations of the character encoding.
	 **/
	public void setCharacterEncodingSet(String[] charEncoding) {
		characterEncoding = charEncoding;
	}

	/**
	 * Get an array of mime types which are supported by the consumer.
	 * The order in the array defines the order of preference of the consumer.
	 * 
	 * @return An array of mimes types the consumer supports.
	 **/
	public String[] getMimeTypes() {
		return mimeTypes;
	}

	/**
	 * Set the mime types the consumer supports
	 * The order in the array defines the order of preference of the consumer.
	 * 
	 * @param mimeTypes An array of mimes types the consumer supports.
	 **/
	public void setMimeTypes(String[] mimeTypes) {
		this.mimeTypes = mimeTypes;
	}

	/**
	 * Get the method which is used by the consumer to authenticate its users.
	 *      
	 * @return String indicating how end-users were authenticated by the consumer.
	 **/
	public String getUserAuthentication() {
		return userAuthMethod;
	}

	/**
	 * Set the method of end user authentication used by the consumer..
	 *      
	 * @param authMethod String indicating how end-users are authenticated by the consumer.
	 **/
	public void setUserAuthentication(String authMethod) {
		userAuthMethod = authMethod;
	}

	/**
	 * Get the user registry of the consumer.
	 * 
	 * @return The consumer specific user registry
	 **/
	public UserRegistry getUserRegistry() {
		return userRegistry;
	}

	/**
	 * Set the user registry of the consumer.
	 * 
	 * @param userRegistry The consumer specific user registry
	 **/
	public void setUserRegistry(UserRegistry userRegistry) {
		this.userRegistry = userRegistry;
	}

	/**
	 * Get the producer registry of the consumer.
	 * 
	 * @return The consumer specific producer registry
	 **/
	public ProducerRegistry getProducerRegistry() {
		return producerRegistry;
	}

	/**
	 * Set the producer registry of the consumer.
	 * 
	 * @param producerRegistry The consumer specific producer registry
	 **/
	public void setProducerRegistry(ProducerRegistry producerRegistry) {
		this.producerRegistry = producerRegistry;
	}

	/**
	 * Get the portlet registry of the consumer.
	 * 
	 * @return Interface to the consumer specific portlet registry
	 **/
	public PortletRegistry getPortletRegistry() {
		return portletRegistry;
	}

	/**
	 * Set the portlet registry of the consumer.
	 * 
	 * @param portletRegistry The consumer specific portlet registry
	 **/
	public void setPortletRegistry(PortletRegistry portletRegistry) {
		this.portletRegistry = portletRegistry;
	}

	/**
	 * Get the portlet driver registry of the consumer.
	 * 
	 * @return Interface to the consumer specific portlet driver registry
	 **/
	public PortletDriverRegistry getPortletDriverRegistry() {
		return portletDriverRegistry;
	}

	/**
	 * Set the portlet driver registry of the consumer.
	 * 
	 * @param portletDriverRegistry The consumer specific portlet driver registry
	 **/
	public void setPortletDriverRegistry(
			PortletDriverRegistry portletDriverRegistry) {
		this.portletDriverRegistry = portletDriverRegistry;
	}

	/**
	 * Get the session handler of the consumer.
	 * 
	 * @return Interface to the consumer specific session handler
	 **/
	public SessionHandler getSessionHandler() {
		return sessionHandler;
	}

	/**
	 * Set the session handler of the consumer.
	 * 
	 * @param sessionHandler The consumer specific session handler
	 **/
	public void setSessionHandler(SessionHandler sessionHandler) {
		this.sessionHandler = sessionHandler;
	}

	/**
	 * Get the url template composer for template proccessing
	 * 
	 * @return Interface to the consumer specific template composer
	 **/
	public URLTemplateComposer getTemplateComposer() {
		return templateComposer;
	}

	/**
	 * Set the url template composer for template proccessing
	 * 
	 * @param templateComposer The consumer specific template composer
	 **/
	public void setTemplateComposer(URLTemplateComposer templateComposer) {
		this.templateComposer = templateComposer;
	}

	/**
	 * Get the url rewriter for consumer url-rewriting
	 * 
	 * @return The consumer specific url rewriter
	 **/
	public URLRewriter getURLRewriter() {
		return urlRewriter;
	}

	/**
	 * Set the url rewriter for consumer url-rewriting
	 * 
	 * @param urlRewriter The consumer specific url rewriter
	 **/
	public void setURLRewriter(URLRewriter urlRewriter) {
		this.urlRewriter = urlRewriter;
	}

}