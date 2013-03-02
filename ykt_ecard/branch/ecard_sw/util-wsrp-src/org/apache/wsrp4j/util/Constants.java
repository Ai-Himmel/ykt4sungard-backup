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

package org.apache.wsrp4j.util;

public final class Constants {

	// locales
	public static final String LOCALE_EN_US = "en";

	public static final String LOCALE_DE_DE = "de";

	// markup types
	public static final String MIME_TYPE_HTML = "text/html";

	// character sets
	public static final String UTF_8 = "UTF-8";

	// Constants for URL-Handling

	// tokens, tags etc.
	public static final String REWRITE_START = "wsrp_rewrite";

	public static final String REWRITE_END = "/wsrp_rewrite";

	public static final String NEXT_PARAM = "&";

	public static final String NEXT_PARAM_AMP = "&amp;";

	public static final String EQUALS = "=";

	public static final String PARAMS_START = "?";

	public static final String NAMESPACE_START = "_";

	// replacement tokens
	public static final String REPLACE_START = "{";

	public static final String REPLACE_END = "}";

	// parameter names
	public static final String URL_TYPE = "wsrp-urlType";

	public static final String NAVIGATIONAL_STATE = "wsrp-navigationalState";

	public static final String INTERACTION_STATE = "wsrp-interactionState";

	public static final String WINDOW_STATE = "wsrp-windowState";

	public static final String PORTLET_MODE = "wsrp-mode";

	public static final String URL = "wsrp-url";

	public static final String FRAGMENT_ID = "wsrp-fragmentID";

	public static final String SECURE_URL = "wsrp-secureURL";

	public static final String REWRITE_RESOURCE = "wsrp-requiresRewrite";

	public static final String FORM_PARAMETERS = "wsrp-formParameters";

	public static final String PORTLET_HANDLE = "wsrp-portletHandle";

	public static final String USER_CONTEXT_KEY = "wsrp-userContextKey";

	public static final String PORTLET_INSTANCE_KEY = "wsrp-portletInstanceKey";

	public static final String SESSION_ID = "wsrp-sessionID";

	// parameter values for url type
	public static final String URL_TYPE_BLOCKINGACTION = "blockingAction";

	public static final String URL_TYPE_RENDER = "render";

	public static final String URL_TYPE_RESOURCE = "resource";

	// constants for parameter checker
	public static final boolean NILLABLE_TRUE = true;

	public static final boolean NILLABLE_FALSE = false;

	// fault names as they appear on the wire
	public static final String ACCESS_DENIED_FAULT = "AccessDenied";

	public static final String INCONSISTENT_PARAMETERS_FAULT = "InconsistenParameters";

	public static final String INVALID_REGISTRATION_FAULT = "InvalidRegistration";

	public static final String INVALID_COOKIE_FAULT = "InvalidCookie";

	public static final String INVALID_HANDLE_FAULT = "InvalidHandle";

	public static final String INVALID_SESSION_FAULT = "InvalidSession";

	public static final String INVALID_USER_CATEGORY_FAULT = "InvalidUserCategory";

	public static final String MISSING_PARAMETERS_FAULT = "MissingParameters";

	public static final String OPERATION_FAILED_FAULT = "OperationFailed";

	public static final String PORTLET_STATE_CHANGE_REQUIRED_FAULT = "PortletStateChangeRequired";

	public static final String UNSUPPORTED_LOCALE_FAULT = "UnsupportedLocale";

	public static final String UNSUPPORTED_MIME_TYPE_FAULT = "UnsupportedMimeType";

	public static final String UNSUPPORTED_MODE_FAULT = "UnsupportedMode";

	public static final String UNSUPPORTED_WINDOW_STATE_FAULT = "UnsupportedWindowState";

	private static final String[] knownParams = new String[] {
			Constants.NAVIGATIONAL_STATE, Constants.INTERACTION_STATE,
			Constants.PORTLET_MODE, Constants.WINDOW_STATE, Constants.URL,
			Constants.FRAGMENT_ID, Constants.SECURE_URL, Constants.URL_TYPE,
			Constants.PORTLET_HANDLE, Constants.PORTLET_INSTANCE_KEY,
			Constants.SESSION_ID, Constants.USER_CONTEXT_KEY,
			Constants.REWRITE_RESOURCE };

	public static boolean isWsrpURLParam(String param) {
		if (!param.startsWith("wsrp-"))
			return false;

		for (int i = 0; i < knownParams.length; i++)
			if (param.equalsIgnoreCase(knownParams[i]))
				return true;

		return false;
	}

	public static String[] getWsrpParameters() {
		return knownParams;
	}

}