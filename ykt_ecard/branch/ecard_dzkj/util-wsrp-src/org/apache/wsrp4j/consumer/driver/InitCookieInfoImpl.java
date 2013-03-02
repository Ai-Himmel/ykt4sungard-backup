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

import java.net.MalformedURLException;
import java.net.URL;

import oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType;
import oasis.names.tc.wsrp.v1.wsdl.WSRPServiceLocator;

import org.apache.wsrp4j.consumer.InitCookieInfo;
import org.apache.wsrp4j.exception.ErrorCodes;
import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.exception.WSRPXHelper;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

public class InitCookieInfoImpl implements InitCookieInfo {

	private Logger logger = null;;

	private String markupInterfaceURL = null;

	private boolean initCookieRequired;

	private boolean initCookieDone;

	private WSRP_v1_Markup_PortType markupInterface;

	public InitCookieInfoImpl(String markupURL) throws WSRPException {
		final String MN = "init";

		logger = LogManager.getLogManager().getLogger(getClass());

		this.initCookieDone = false;
		this.initCookieRequired = false;
		this.markupInterfaceURL = markupURL;

		try {
			WSRPServiceLocator serviceLocator = new WSRPServiceLocator();
			serviceLocator.setMaintainSession(true);

			markupInterface = serviceLocator.getWSRPBaseService(new URL(
					markupURL));

		}
		catch (javax.xml.rpc.ServiceException xmlEx) {
			WSRPXHelper.throwX(logger, Logger.ERROR, MN,
					ErrorCodes.INIT_OF_MARKUP_PORT_FAILED, xmlEx);
		}
		catch (MalformedURLException urlEx) {
			WSRPXHelper.throwX(logger, Logger.ERROR, MN,
					ErrorCodes.INVALID_URL_OF_MARKUP_PORT, urlEx);
		}
	}

	public boolean isInitCookieRequired() {
		return initCookieRequired;
	}

	public void setInitCookieRequired(boolean initCookieRequired) {
		this.initCookieRequired = initCookieRequired;
	}

	public boolean isInitCookieDone() {
		return initCookieDone;
	}

	public void setInitCookieDone(boolean initCookieDone) {
		this.initCookieDone = initCookieDone;
	}

	public String getMarkupInterfaceURL() {
		return markupInterfaceURL;
	}

	public WSRP_v1_Markup_PortType getWSRPBaseService() {
		return markupInterface;
	}

	public void setWSRPBaseService(WSRP_v1_Markup_PortType markupPortType) {
		if (markupPortType != null) {
			this.markupInterface = markupPortType;
		}
	}

}