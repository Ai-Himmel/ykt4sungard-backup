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
 * <p>This interface provides methods to generate URL templates.</p>
 * <p>The generated templates will be transmitted to Producers (or respectively portlets)
 * that are willing to properly write URLs for a Consumer. (With templates the Consumer
 * indicates how it needs URLs formatted in order to process them properly.)</p> 
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 *
 * @version 1.1
 */
public interface URLTemplateComposer {

	/**
	 * Sets the URLGenerator to be used.
	 */
	public void setURLGenerator(URLGenerator urlGenerator);

	/**
	 * Creates a blocking action template. Includes tokens for url-type, portletMode,
	 * navigationalState, interactionState and windowState to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createBlockingActionTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Creates a secure blocking action template. Includes tokens for url-type,
	 * portletMode, navigationalState, interactionState, windowState and secureURL to be replaced by
	 * the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createSecureBlockingActionTemplate(
			boolean includePortletHandle, boolean includeUserContextKey,
			boolean includePortletInstanceKey, boolean includeSessionID);

	/**
	 * Creates a render template. Includes tokens for url-type, portletMode,
	 * navigationalState, interactionState and windowState to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createRenderTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Creates a secure render template. Includes tokens for url-type, portletMode,
	 * navigationalState, interactionState, windowState and secureURL to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createSecureRenderTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Creates a resource template. Includes tokens for url-type,
	 * rewriteResource and url to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createResourceTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Creates a secure resource template. Includes tokens for url-type, url,
	 * rewriteResource, and secureURL to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createSecureResourceTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Creates a default template. Includes tokens for url-type, portletMode,
	 * navigationalState, interactionState, windowState, url, rewriteResource
	 * and secureURL to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createDefaultTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Creates a secure default template. Includes tokens for url-type, portletMode,
	 * navigationalState, interactionState, windowState, url, rewriteResource and secureURL
	 * to be replaced by the producer.
	 *
	 * @return String representing the entire template.
	 */
	public String createSecureDefaultTemplate(boolean includePortletHandle,
			boolean includeUserContextKey, boolean includePortletInstanceKey,
			boolean includeSessionID);

	/**
	 * Get the consumers namespace prefix which is used by the portlet
	 * to namespace tokens which need to be unique on a aggregated page. 
	 *
	 * @return The namespace prefix of the consumer.
	 **/
	public String getNamespacePrefix();
}