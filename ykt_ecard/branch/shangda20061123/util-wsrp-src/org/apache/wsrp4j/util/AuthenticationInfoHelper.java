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

import javax.portlet.*;

public class AuthenticationInfoHelper {
	/**
	 * No authentication was done
	 **/
	public static final String WSRP_NONE = "wsrp:none";

	/**
	 * End-User identified themselves using password/username scenario
	 **/
	public static final String WSRP_PASSWD = "wsrp:password";

	/**
	 * End-User presented a security certificate
	 **/
	public static final String WSRP_CERT = "wsrp:certificate";

	/**
	 * Get a string representation of the user authentification
	 * as defined in the WSRP spec. from a passed authentification
	 * info defined in the portlet spec. If the passed value could not
	 * be matched the same string is returned. 
	 * 
	 * @param jsrAuthInfo Authentification info as defined in the portlet spec
	 * @return The authentification info as defined in the WSRP spec. or the
	 *          argument if no match could be made.
	 **/
	public static String getWsrpFromPortlet(String jsrAuthInfo) {
		if (jsrAuthInfo == null) {
			return WSRP_NONE;
		}
		else if (jsrAuthInfo == PortletRequest.BASIC_AUTH
				|| jsrAuthInfo == PortletRequest.FORM_AUTH
				|| jsrAuthInfo.equals(PortletRequest.BASIC_AUTH)
				|| jsrAuthInfo.equals(PortletRequest.FORM_AUTH)) {
			return WSRP_PASSWD;

		}
		else if (jsrAuthInfo == PortletRequest.CLIENT_CERT_AUTH
				|| jsrAuthInfo.equals(PortletRequest.CLIENT_CERT_AUTH)) {

			return WSRP_CERT;

		}
		else {

			return jsrAuthInfo;
		}
	}

	/**
	 * Get the authentification info as defined in the portlet spec
	 * from a passed authentification info defined in the WSRP spec..
	 * If wsrp:none is passed <code>null</code> is returned. In case the
	 * passed info could not be matched the same string is returned.
	 * 
	 * @param wsrpInfo
	 * @return     
	 **/
	public static String getPortletFromWsrp(String wsrpInfo) {
		if (wsrpInfo.equals(WSRP_PASSWD)) {
			return PortletRequest.FORM_AUTH;

		}
		else if (wsrpInfo.equals(WSRP_CERT)) {
			return PortletRequest.CLIENT_CERT_AUTH;

		}
		else if (wsrpInfo.equals(WSRP_NONE)) {

			return null;

		}
		else {

			return wsrpInfo;
		}
	}
}