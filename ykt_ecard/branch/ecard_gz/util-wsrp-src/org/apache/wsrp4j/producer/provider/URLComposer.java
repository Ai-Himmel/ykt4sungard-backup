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

package org.apache.wsrp4j.producer.provider;

import oasis.names.tc.wsrp.v1.types.RuntimeContext;
import oasis.names.tc.wsrp.v1.types.UserContext;
import oasis.names.tc.wsrp.v1.types.PortletContext;

/**
 * <p>This interface provides methods generating URLs or namespacing
 * tokens that should be called within the getMarkup method of a service.</p>
 * <p>There are two kinds of methods:
 * <ul>
 *   <li>Methods defining URLs or tokens to be rewritten by the consumer.</li>
 *   <li>Methods defining complete URLs or namespaced tokens according to the
 *       templates delivered by the Consumer.</li>
 * </p> 
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 * @author  <a href="mailto:stephan.laertz@de.ibm.com">Stephan Laertz</a>
 */
public interface URLComposer {

	// create URLs that have to be rewritten by the consumer

	/**
	 * Creates an complete parameter string for a blocking action link. Depended on
	 * the passed <code>RuntimeContext</code> and appearance of a non-null
	 * (secure)blockingaction or (secure)default template the url are either furnished with embracing rewrite 
	 * tokens or not. 
	 * Passing a null value for any of the provided parameters implicates that
	 * these url-parameters will not be included in the resulting url.
	 * Passing a null RuntimeContext or a RuntimeContext with a null blockingAction
	 * and default templates implicates the generation of url's which need to be rewritten at the 
	 * consumer side. Otherwise the consumers template is used to generate the urls.
	 * If a <code>UserContext</code> and/or <code>PortletContext</code> is also passed
	 * then the portlethandle and userContextKey from these strutures is used to make
	 * the produce url specific to that values. 
	 *    
	 * @param  portletMode       The portlet mode to be inserted into the parameter
	 *                           string of the url.
	 * @param  navigationalState The navigational state to be inserted into the
	 *                           parameter string of the url.
	 * @param  interactionState  The interaction state to be inserted into the
	 *                           parameter string of the url.
	 * @param  windowState       The window State to be inserted into the parameter
	 *                           string of the url.
	 * @param  secureURL         Boolean flag indicating if secure
	 *                           communications should be used when activating
	 *                           the link.
	 * 
	 * @param  runtimeContext    The <code>RuntimeContext</code> object from the
	 *                            wsrp request. Passing a null results in url's wich
	 *                            require consumer rewriting.
	 * @param portletContext     If a portlet context is passed with a valid portlet handle
	 *                            then this handle is used to be inserted in the url only
	 *                            if the runtimecontext contained a valid blockingAction or default template.
	 **/
	public String createBlockingActionURL(String portletMode,
			String navigationalState, String interactionState,
			String windowState, boolean secureURL,
			RuntimeContext runtimeContext, PortletContext portletContext,
			UserContext userContext);

	/**
	 * Creates an complete parameter string for a render link. Depended on
	 * the passed <code>RuntimeContext</code> and appearance of a non-null
	 * render or default template the url are either furnished with embracing rewrite 
	 * tokens or not. 
	 * Passing a null value for any of the provided parameters implicates that
	 * these url-parameters will not be included in the resulting url.
	 * Passing a null RuntimeContext or a RuntimeContext with a null render and default
	 * templates implicates the generation of url's which need to be rewritten at the 
	 * consumer side. Otherwise the consumers template is used to generate the urls.
	 * If a <code>UserContext</code> and/or <code>PortletContext</code> is also passed
	 * then the portlethandle and userContextKey from these strutures is used to make
	 * the produce url specific to that values. 
	 *    
	 * @param  portletMode       The portlet mode to be inserted into the parameter
	 *                           string of the url.
	 * @param  navigationalState The navigational state to be inserted into the
	 *                           parameter string of the url.
	 * @param  windowState       The window State to be inserted into the parameter
	 *                           string of the url.
	 * @param  secureURL         Boolean flag indicating if secure
	 *                           communications should be used when activating
	 *                           the link.
	 * 
	 * @param  runtimeContext    The <code>RuntimeContext</code> object from the
	 *                            wsrp request. Passing a null results in url's wich
	 *                            require consumer rewriting.
	 * @param portletContext     If a portlet context is passed with a valid portlet handle
	 *                            then this handle is used to be inserted in the url only
	 *                            if the runtimecontext contained a valid render or default template.
	 **/
	public String createRenderURL(String portletMode, String navigationalState,
			String windowState, boolean secureURL,
			RuntimeContext runtimeContext, PortletContext portletContext,
			UserContext userContext);

	/**
	 * Creates an complete parameter string for a resource link. Depended on
	 * the passed <code>RuntimeContext</code> and appearance of a non-null
	 * render or default template the url are either furnished with embracing rewrite 
	 * tokens or not. 
	 * Passing a null value for any of the provided parameters implicates that
	 * these url-parameters will not be included in the resulting url.
	 * Passing a null RuntimeContext or a RuntimeContext with a null render and default
	 * templates implicates the generation of url's which need to be rewritten at the 
	 * consumer side. Otherwise the consumers template is used to generate the urls.
	 * If a <code>UserContext</code> and/or <code>PortletContext</code> is also passed
	 * then the portlethandle and userContextKey from these strutures is used to make
	 * the produce url specific to that values.
	 *
	 * @param  url               Provides the actual url to the resource.
	 * @param  rewriteResource   Boolean flag informing the Consumer that the
	 *                           resource needs to be parsed for URL rewriting.
	 * @param  secureURL         Boolean flag indicating whether secure
	 *                           communications should be used when activating
	 *                           the link.
	 * @param  runtimeContext    The <code>RuntimeContext</code> object from the
	 *                            wsrp request. Passing a null results in url's wich
	 *                            require consumer rewriting.
	 * @param portletContext     If a portlet context is passed with a valid portlet handle
	 *                            then this handle is used to be inserted in the url only
	 *                            if the runtimecontext contained a valid resource or default template.
	 **/
	public String createResourceURL(String url, boolean rewriteResource,
			boolean secureURL, RuntimeContext runtimeContext,
			PortletContext portletContext, UserContext userContext);

	/**
	 * Marks a token that has to be namespaced by the consumer.
	 * If a <code>RuntimeContext</code> with a non-null namespace prefix
	 * attributed is passed then this prefix is used to namespace the given token.
	 * Passing a null RuntimeContext results in a namespace url that requires consumer
	 * rewriting. 
	 *
	 * @param  token Token to be namespaced.
	 * @param  runtimeContext A <code>RuntimeContext</code> with a valid namespaceprefix or null.
	 */
	public String createNamespacedToken(String token,
			RuntimeContext runtimeContext);
}