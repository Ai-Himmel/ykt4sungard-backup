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

import java.net.URLEncoder;

import oasis.names.tc.wsrp.v1.types.PortletContext;
import oasis.names.tc.wsrp.v1.types.RuntimeContext;
import oasis.names.tc.wsrp.v1.types.Templates;
import oasis.names.tc.wsrp.v1.types.UserContext;

import org.apache.wsrp4j.exception.ErrorCodes;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.exception.WSRPXHelper;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.producer.provider.Provider;
import org.apache.wsrp4j.producer.provider.URLComposer;
import org.apache.wsrp4j.util.Constants;

/**
 * <p>This class implements the URLComposer interface providing methods to generate
 * URLs or namespace tokens.</p>
 * <p>There are two kinds of methods:
 * <ul>
 *   <li>Methods defining URLs or tokens to be rewritten by the consumer.</li>
 *   <li>Methods defining complete URLs or namespaced tokens according to the
 *       templates delivered by the Consumer.</li></p> 
 *
 * @author  <a href="mailto:stefan.behl@de.ibm.com">Stefan Behl</a>
 */
public class URLComposerImpl implements URLComposer {
	// the provider implementation
	private Provider provider = null;

	// for logging and exception support
	private Logger logger = LogManager.getLogManager().getLogger(
			this.getClass());

	private URLComposerImpl() {
	}

	public static URLComposerImpl getInstance(Provider provider) {
		URLComposerImpl urlComposer = new URLComposerImpl();
		urlComposer.provider = provider;

		return urlComposer;
	}

	// methods generating rewrite urls

	/**
	 * creates a rewrite blocking-action-url
	 * 
	 * @param portletMode
	 * @param navigationalState
	 * @param interactionState
	 * @param windowState
	 * @param secureURL
	 * @param runtimeContext
	 * @param portletContext
	 * @param userContext
	 * 
	 * @return URL as String
	 */
	public String createBlockingActionURL(String portletMode,
			String navigationalState, String interactionState,
			String windowState, boolean secureURL,
			RuntimeContext runtimeContext, PortletContext portletContext,
			UserContext userContext) {
		String MN = "createBlockingActionURL";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		// check if valid templates are provided
		if (runtimeContext != null) {

			Templates templates = runtimeContext.getTemplates();
			if (templates != null) {

				String template = null;
				if (secureURL) {

					template = templates.getSecureBlockingActionTemplate();
					if (template == null)
						template = templates.getSecureDefaultTemplate();

				}
				else {

					template = templates.getBlockingActionTemplate();
					if (template == null)
						template = templates.getDefaultTemplate();
				}

				try {
					if (template != null) {

						if (logger.isLogging(Logger.TRACE_HIGH)) {
							logger.exit(Logger.TRACE_HIGH, MN);
						}

						return this.createBlockingActionURLByTemplate(template,
								portletMode, navigationalState,
								interactionState, windowState,
								portletContext == null ? null : portletContext
										.getPortletHandle(),
								userContext == null ? null : userContext
										.getUserContextKey(), runtimeContext
										.getPortletInstanceKey(),
								runtimeContext.getSessionID());
					}
				}
				catch (WSRPException e) {

					// TODO: pass exception to consumer
				}
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return createRewriteURL(Constants.URL_TYPE_BLOCKINGACTION, portletMode,
				navigationalState, interactionState, windowState, null, null,
				null, java.lang.String.valueOf(secureURL));
	}

	/**
	 * creates a rewrite render-url
	 */
	public String createRenderURL(String portletMode, String navigationalState,
			String windowState, boolean secureURL,
			RuntimeContext runtimeContext, PortletContext portletContext,
			UserContext userContext) {
		String MN = "createRenderURL";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		// check if valid templates are provided
		if (runtimeContext != null) {

			Templates templates = runtimeContext.getTemplates();
			if (templates != null) {

				String template = null;
				if (secureURL) {

					template = templates.getSecureRenderTemplate();
					if (template == null)
						template = templates.getDefaultTemplate();

				}
				else {

					template = templates.getRenderTemplate();
					if (template == null)
						template = templates.getDefaultTemplate();
				}

				try {
					if (template != null) {

						if (logger.isLogging(Logger.TRACE_HIGH)) {
							logger.exit(Logger.TRACE_HIGH, MN);
						}

						return this.createRenderURLByTemplate(template,
								portletMode, navigationalState, windowState,
								portletContext == null ? null : portletContext
										.getPortletHandle(),
								userContext == null ? null : userContext
										.getUserContextKey(), runtimeContext
										.getPortletInstanceKey(),
								runtimeContext.getSessionID());
					}
				}
				catch (WSRPException e) {

					// TODO: pass exception to consumer

				}
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return createRewriteURL(Constants.URL_TYPE_RENDER, portletMode,
				navigationalState, null, windowState, null, null, null,
				java.lang.String.valueOf(secureURL));
	}

	/**
	 * creates a rewrite resource-url
	 */
	public String createResourceURL(String url, boolean rewriteResource,
			boolean secureURL, RuntimeContext runtimeContext,
			PortletContext portletContext, UserContext userContext) {
		String MN = "createResourceURL";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		// check if valid templates are provided
		if (runtimeContext != null) {

			Templates templates = runtimeContext.getTemplates();
			if (templates != null) {

				String template = null;
				if (secureURL) {

					template = templates.getSecureResourceTemplate();
					if (template == null)
						template = templates.getDefaultTemplate();

				}
				else {

					template = templates.getResourceTemplate();
					if (template == null)
						template = templates.getDefaultTemplate();
				}

				try {
					if (template != null) {

						if (logger.isLogging(Logger.TRACE_HIGH)) {
							logger.exit(Logger.TRACE_HIGH, MN);
						}

						return this.createResourceURLByTemplate(template, url,
								rewriteResource, portletContext == null ? null
										: portletContext.getPortletHandle(),
								userContext == null ? null : userContext
										.getUserContextKey(), runtimeContext
										.getPortletInstanceKey(),
								runtimeContext.getSessionID());
					}

				}
				catch (WSRPException e) {

					// TODO: pass exception to consumer

				}
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return createRewriteURL(Constants.URL_TYPE_RESOURCE, null, null, null,
				null, url, java.lang.String.valueOf(rewriteResource), null,
				java.lang.String.valueOf(secureURL));
	}

	/**
	 * creates a namespaced token
	 */
	public String createNamespacedToken(String token,
			RuntimeContext runtimeContext) {
		String MN = "createNamespacedToken";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		String nsToken = null;

		// first get the prefix
		// this is either the prefix passed in the RuntimeContext
		if (runtimeContext != null) {
			nsToken = runtimeContext.getNamespacePrefix();
		}
		// no namespace prefix obtained?
		// then need to put in the rewrite NS wsrp_rewrite_ 
		if (nsToken == null) {
			nsToken = Constants.REWRITE_START + Constants.NAMESPACE_START;
		}

		// append the token
		// if token is null, simply return the namespace
		if (token != null) {
			nsToken = nsToken.concat(token);
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return nsToken;
	}

	private String createRewriteURL(String urlType, String portletMode,
			String navigationalState, String interactionState,
			String windowState, String url, String rewriteResource,
			String token, String secureURL) {

		String MN = "createRewriteURL()";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN, new Object[] { urlType,
					portletMode, navigationalState, interactionState,
					windowState, url, rewriteResource, token, secureURL });
		}

		StringBuffer resultURL = new StringBuffer();

		resultURL.append(Constants.REWRITE_START);
		resultURL.append(Constants.PARAMS_START);

		// urlType must be first (required)
		if (urlType != null) {
			resultURL.append(appendNameValuePair(Constants.URL_TYPE, urlType));
		}
		else {

			//TODO: Error
		}

		// portletMode
		if (portletMode != null && portletMode.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			resultURL.append(appendNameValuePair(Constants.PORTLET_MODE,
					portletMode));
		}

		// navigationalState
		if (navigationalState != null && navigationalState.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			resultURL.append(appendNameValuePair(Constants.NAVIGATIONAL_STATE,
					navigationalState));
		}

		// interactionState
		if (interactionState != null && interactionState.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			resultURL.append(appendNameValuePair(Constants.INTERACTION_STATE,
					interactionState));
		}

		// windowState
		if (windowState != null && windowState.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			resultURL.append(appendNameValuePair(Constants.WINDOW_STATE,
					windowState));
		}

		// url
		if (url != null && url.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			String fileEncoding = System.getProperty("file.encoding", "UTF-8");
			try {
				resultURL.append(appendNameValuePair(Constants.URL, URLEncoder
						.encode(url, fileEncoding)));
			}
			catch (Exception e) {
				logger.text(Logger.ERROR, MN, e, "Encoding not supported.");
			}
		}

		// rewriteResource
		if (rewriteResource != null && rewriteResource.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			resultURL.append(appendNameValuePair(Constants.REWRITE_RESOURCE,
					rewriteResource));
		}

		// secureURL
		if (secureURL != null && secureURL.length() > 0) {
			resultURL.append(Constants.NEXT_PARAM_AMP);
			resultURL.append(appendNameValuePair(Constants.SECURE_URL,
					secureURL));
		}

		resultURL.append(Constants.REWRITE_END);

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		String result = resultURL.toString();

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN, result);
		}

		return result;

	}

	private String createNameValuePair(String name, String value) {

		StringBuffer pair = new StringBuffer(name);
		pair.append(Constants.EQUALS);
		pair.append(value);

		return pair.toString();
	}

	private String appendNameValuePair(String name, String value) {
		return createNameValuePair(name, value);
	}

	// methods generating urls by template processing

	private String createBlockingActionURLByTemplate(
			String blockingActionTemplate, String portletMode,
			String navigationalState, String interactionState,
			String windowState) throws WSRPException {

		return processTemplate(blockingActionTemplate,
				Constants.URL_TYPE_BLOCKINGACTION, portletMode,
				navigationalState, interactionState, windowState, null, null,
				null, null, null, null);

	}

	private String createBlockingActionURLByTemplate(
			String blockingActionTemplate, String portletMode,
			String navigationalState, String interactionState,
			String windowState, String portletHandle, String userContextKey,
			String portletInstanceKey, String sessionID) throws WSRPException {

		return processTemplate(blockingActionTemplate,
				Constants.URL_TYPE_BLOCKINGACTION, portletMode,
				navigationalState, interactionState, windowState, null, null,
				portletHandle, userContextKey, portletInstanceKey, sessionID);

	}

	private String createRenderURLByTemplate(String renderTemplate,
			String portletMode, String navigationalState, String windowState)
			throws WSRPException {

		return processTemplate(renderTemplate, Constants.URL_TYPE_RENDER,
				portletMode, navigationalState, null, windowState, null, null,
				null, null, null, null);
	}

	private String createRenderURLByTemplate(String renderTemplate,
			String portletMode, String navigationalState, String windowState,
			String portletHandle, String userContextKey,
			String portletInstanceKey, String sessionID) throws WSRPException {

		return processTemplate(renderTemplate, Constants.URL_TYPE_RENDER,
				portletMode, navigationalState, null, windowState, null, null,
				portletHandle, userContextKey, portletInstanceKey, sessionID);

	}

	private String createResourceURLByTemplate(String resourceTemplate,
			String url, boolean rewriteResource) throws WSRPException {

		return processTemplate(resourceTemplate, Constants.URL_TYPE_RESOURCE,
				null, null, null, null, url, java.lang.String
						.valueOf(rewriteResource), null, null, null, null);

	}

	private String createResourceURLByTemplate(String resourceTemplate,
			String url, boolean rewriteResource, String portletHandle,
			String userContextKey, String portletInstanceKey, String sessionID)
			throws WSRPException {

		return processTemplate(resourceTemplate, Constants.URL_TYPE_RESOURCE,
				null, null, null, null, url, java.lang.String
						.valueOf(rewriteResource), portletHandle,
				userContextKey, portletInstanceKey, sessionID);

	}

	private String processTemplate(String template, String urlType,
			String portletMode, String navigationalState,
			String interactionState, String windowState, String url,
			String rewriteResource, String portletHandle,
			String userContextKey, String portletInstanceKey, String sessionID)
			throws WSRPException {

		String MN = "processTemplate";
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		String replaceToken = "";

		// Any template containing "{" or "}" will be processed.
		while ((template.indexOf(Constants.REPLACE_START) != -1)
				| (template.indexOf(Constants.REPLACE_END) != -1)) {

			StringBuffer templateBuffer = new StringBuffer(template);

			// get positions of next left and right brackets
			int left_br = template.indexOf(Constants.REPLACE_START);
			int right_br = template.indexOf(Constants.REPLACE_END) + 1;

			// check if bracketing is correct 
			if ((left_br > right_br) | (left_br == -1) | (right_br == -1)) {

				WSRPXHelper.throwX(logger, Logger.ERROR, MN,
						ErrorCodes.SYNTAX_ERROR_IN_TEMPLATE);

			}

			// get replaceToken without curly brackets enclosing it
			replaceToken = templateBuffer.substring(left_br + 1, right_br - 1);

			// urlType
			if (replaceToken.equalsIgnoreCase(Constants.URL_TYPE)) {
				if (urlType == null) {
					urlType = "";
				}
				templateBuffer.replace(left_br, right_br, urlType);
			}

			// portletMode
			else if (replaceToken.equalsIgnoreCase(Constants.PORTLET_MODE)) {
				if (portletMode == null) {
					portletMode = "";
				}
				templateBuffer.replace(left_br, right_br, portletMode);
			}

			// navigationalState
			else if (replaceToken
					.equalsIgnoreCase(Constants.NAVIGATIONAL_STATE)) {
				if (navigationalState == null) {
					navigationalState = "";
				}
				templateBuffer.replace(left_br, right_br, navigationalState);
			}

			// interactionState
			else if (replaceToken.equalsIgnoreCase(Constants.INTERACTION_STATE)) {
				if (interactionState == null) {
					interactionState = "";
				}
				templateBuffer.replace(left_br, right_br, interactionState);
			}

			// windowState
			else if (replaceToken.equalsIgnoreCase(Constants.WINDOW_STATE)) {
				if (windowState == null) {
					windowState = "";
				}
				templateBuffer.replace(left_br, right_br, windowState);
			}

			// url
			else if (replaceToken.equalsIgnoreCase(Constants.URL)) {
				if (url == null) {
					url = "";
				}
				templateBuffer.replace(left_br, right_br, url);
			}

			// rewriteResource
			else if (replaceToken.equalsIgnoreCase(Constants.REWRITE_RESOURCE)) {
				if (rewriteResource == null) {
					rewriteResource = "";
				}
				templateBuffer.replace(left_br, right_br, rewriteResource);
			}

			/*
			 
			 // secureURL
			 else if (replaceToken.equalsIgnoreCase(Constants.SECURE_URL))
			 {
			 if (secureURL == null)
			 {
			 secureURL = "";
			 }
			 templateBuffer.replace(left_br, right_br, secureURL);
			 }
			 
			 // token
			 else if (replaceToken.equalsIgnoreCase(Constants.TOKEN))
			 {
			 if (token == null)
			 {
			 token = "";
			 }
			 templateBuffer.replace(left_br, right_br, token);
			 }
			 */
			// portletHandle
			else if (replaceToken.equalsIgnoreCase(Constants.PORTLET_HANDLE)) {
				if (portletHandle == null) {
					portletHandle = "";
				}
				templateBuffer.replace(left_br, right_br, portletHandle);
			}

			// userContextKey
			else if (replaceToken.equalsIgnoreCase(Constants.USER_CONTEXT_KEY)) {
				if (userContextKey == null) {
					userContextKey = "";
				}
				templateBuffer.replace(left_br, right_br, userContextKey);
			}

			// portletInstanceKey
			else if (replaceToken
					.equalsIgnoreCase(Constants.PORTLET_INSTANCE_KEY)) {
				if (portletInstanceKey == null) {
					portletInstanceKey = "";
				}
				templateBuffer.replace(left_br, right_br, portletInstanceKey);
			}

			// sessionID
			else if (replaceToken.equalsIgnoreCase(Constants.SESSION_ID)) {
				if (sessionID == null) {
					sessionID = "";
				}
				templateBuffer.replace(left_br, right_br, sessionID);
			}

			// unknown
			else {

				WSRPXHelper.throwX(logger, Logger.ERROR, MN,
						ErrorCodes.UNKNOWN_TOKEN_IN_TEMPLATE);

			}

			// update template
			template = templateBuffer.toString();

		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return template;
	}

}