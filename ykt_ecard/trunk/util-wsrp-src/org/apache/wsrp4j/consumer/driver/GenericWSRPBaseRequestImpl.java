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

package org.apache.wsrp4j.consumer.driver;

import org.apache.wsrp4j.consumer.WSRPBaseRequest;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

import oasis.names.tc.wsrp.v1.types.ClientData;

public abstract class GenericWSRPBaseRequestImpl implements WSRPBaseRequest {

	protected Logger logger = LogManager.getLogManager().getLogger(
			GenericWSRPBaseRequestImpl.class);

	public abstract String getSessionID();

	public abstract String getPortletInstanceKey();

	public abstract String getNavigationalState();

	public abstract String getWindowState();

	public abstract String getMode();

	public abstract ClientData getClientData();

	public abstract String[] getLocales();

	public abstract String[] getModes();

	public abstract String[] getWindowStates();

	public abstract String[] getMimeTypes();

	public abstract String[] getCharacterEncodingSet();

	public boolean isModeSupported(String wsrpMode) {
		final String MN = "isModeSupported(String)";

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (wsrpMode == null)
			throw new IllegalArgumentException("mode must not be null");

		String[] mods = getModes();
		for (int i = 0; i < mods.length; i++) {
			if (wsrpMode.equalsIgnoreCase(mods[i])) {
				return true;
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return false;
	}

	public boolean isWindowStateSupported(String wsrpWindowState) {
		final String MN = "isWindowStateSupported(String)";

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (wsrpWindowState == null)
			throw new IllegalArgumentException("window state must not be null");

		String[] stats = getWindowStates();
		for (int i = 0; i < stats.length; i++) {
			if (wsrpWindowState.equalsIgnoreCase(stats[i])) {
				return true;
			}
		}

		if (logger.isLogging(Logger.TRACE_HIGH)) {
			logger.exit(Logger.TRACE_HIGH, MN);
		}

		return false;
	}

	public abstract String getUserAuthentication();
}