/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.jaas;

import com.liferay.portal.util.Constants;

import java.util.HashMap;
import java.util.Map;

import javax.security.auth.login.AppConfigurationEntry;
import javax.security.auth.login.Configuration;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortalConfiguration.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Weisser
 * @version $Revision: 1.12 $
 *
 */
public class PortalConfiguration extends Configuration {

	public PortalConfiguration(Configuration config) {
		_config = config;
	}

	public AppConfigurationEntry[] getAppConfigurationEntry(String name) {
		AppConfigurationEntry[] aceArray =
			_config.getAppConfigurationEntry(name);

		if (name != null && !name.equals(Constants.JBOSS_LOGIN_MODULE)) {
			_log.debug(name);

			Map options = null;
			if (aceArray == null || aceArray.length == 0) {
				options = new HashMap();
			}
			else {
				options = aceArray[0].getOptions();
			}

			AppConfigurationEntry ace = new AppConfigurationEntry(
				PortalLoginModule.class.getName(),
				AppConfigurationEntry.LoginModuleControlFlag.SUFFICIENT,
				options);

			if (aceArray == null || aceArray.length == 0) {
				aceArray = new AppConfigurationEntry[] {ace};
			}
			else {
				AppConfigurationEntry[] newAceArray =
					new AppConfigurationEntry[aceArray.length + 1];

				if (name.equals(Constants.REALM_NAME)) {
					newAceArray[0] = ace;

					System.arraycopy(
						aceArray, 0, newAceArray, 1, aceArray.length);
				}
				else {
					newAceArray[aceArray.length] = ace;

					System.arraycopy(
						aceArray, 0, newAceArray, 0, aceArray.length);
				}

				aceArray = newAceArray;

				for (int i = 0; i < newAceArray.length; i++) {
					if (newAceArray[i].getControlFlag().equals(
							AppConfigurationEntry.LoginModuleControlFlag.
								REQUIRED)) {

						newAceArray[i] = new AppConfigurationEntry(
							newAceArray[i].getLoginModuleName(),
							AppConfigurationEntry.LoginModuleControlFlag.
								SUFFICIENT,
							newAceArray[i].getOptions());
					}

					_log.debug(
						newAceArray[i].getLoginModuleName() + " " +
						newAceArray[i].getControlFlag()
					);
				}
			}
		}

		return aceArray;
	}

	public void refresh() {
		_config.refresh();
	}

	private static final Log _log =
		LogFactory.getLog(PortalConfiguration.class);

	private Configuration _config = null;

}