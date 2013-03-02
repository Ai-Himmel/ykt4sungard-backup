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

package com.liferay.portlet.wsrp;

import com.liferay.portal.model.Portlet;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.wsrp.util.WSRPUtil;
import com.liferay.util.CollectionFactory;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletMode;
import javax.portlet.PortletRequest;

import oasis.names.tc.wsrp.v1.types.ClientData;
import oasis.names.tc.wsrp.v1.types.MarkupContext;
import oasis.names.tc.wsrp.v1.types.NamedString;
import oasis.names.tc.wsrp.v1.types.SessionContext;

import org.apache.wsrp4j.consumer.InteractionRequest;
import org.apache.wsrp4j.consumer.MarkupRequest;
import org.apache.wsrp4j.consumer.PortletWindowSession;
import org.apache.wsrp4j.consumer.driver.GenericWSRPBaseRequestImpl;
import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.util.AuthenticationInfoHelper;
import org.apache.wsrp4j.util.Constants;
import org.apache.wsrp4j.util.LocaleHelper;
import org.apache.wsrp4j.util.Modes;
import org.apache.wsrp4j.util.WindowStates;

/**
 * <a href="WSRPRequestImpl.java.html"> <b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @version $Revision: 1.9 $
 *
 */
public class WSRPRequestImpl extends GenericWSRPBaseRequestImpl implements
		InteractionRequest, MarkupRequest {

	public WSRPRequestImpl(PortletWindowSession windowSession,
			PortletRequest portletRequest) {

		this._windowSession = windowSession;
		this._portletRequest = portletRequest;
		this._userAuth = AuthenticationInfoHelper
				.getWsrpFromPortlet(portletRequest.getAuthType());

		integrateParameter();
	}

	public String getInteractionState() {
		return _interactionState;
	}

	public NamedString[] getFormParameters() {
		return _formParameters;
	}

	public MarkupContext getCachedMarkup() {
		if (_windowSession == null)
			return null;

		return _windowSession.getCachedMarkup();
	}

	public String getSessionID() {
		if (this._windowSession != null) {
			SessionContext sessionCtx = this._windowSession.getPortletSession()
					.getSessionContext();
			if (sessionCtx != null) {
				return sessionCtx.getSessionID();

			}
		}

		return null;
	}

	public String getPortletInstanceKey() {
		return _windowSession.getWindowID();
	}

	public String getNavigationalState() {
		return _naviState;
	}

	public String getWindowState() {
		if (_currentState == null) {
			//map portlet window states to wsrp:window states
			javax.portlet.WindowState portletWindowState = _portletRequest
					.getWindowState();
			_currentState = WindowStates.getWsrpStateFromJsrPortletState(
					portletWindowState).toString();
		}

		return _currentState;
	}

	public String getMode() {
		if (_currentMode == null) {
			//map jsr-168 modes to wsrp:modes
			PortletMode portletMode = _portletRequest.getPortletMode();
			_currentMode = Modes.getWsrpModeFromJsrPortletMode(portletMode)
					.toString();
		}

		return _currentMode;
	}

	public ClientData getClientData() {
		// TODO: need to find out the client data here
		return null;
	}

	public String[] getLocales() {
		if (this._locales == null) {
			Enumeration eLocales = _portletRequest.getLocales();
			List wsrpLocales = new ArrayList();
			while (eLocales.hasMoreElements()) {
				Locale locale = (Locale) eLocales.nextElement();
				wsrpLocales.add(LocaleHelper.getWsrpLocale(locale));
			}

			_locales = (String[]) wsrpLocales.toArray(new String[0]);
		}

		return _locales;
	}

	public String[] getModes() {
		final String MN = "getModes()";

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		if (this._modes != null) {
			if (_logger.isLogging(Logger.TRACE_HIGH)) {
				_logger.exit(Logger.TRACE_HIGH, MN);
			}

			return this._modes;
		}

		String companyId = PortalUtil.getCompanyId(_portletRequest);
		try {
			Portlet portlet = PortletServiceUtil.getPortletById(companyId,
					_windowSession.getWindowID());
			Map portletModesMap = portlet.getPortletModes();
			Collection mimeTypes = portletModesMap.values();
			Iterator it = mimeTypes.iterator();
			Map portletModes = CollectionFactory.getSyncHashMap();

			for (int i = 0; it.hasNext(); i++) {
				// Required
				Set portletModesSet = (Set) it.next();

				Iterator it2 = portletModesSet.iterator();

				for (int j = 0; it2.hasNext(); j++) {
					String mode = (String) it2.next();

					if (portletModes.get(mode) == null) {
						portletModes.put(mode, mode);
					}
				}
			}

			String[] wsrpModes = new String[portletModes.size()];
			it = portletModes.values().iterator();
			for (int i = 0; it.hasNext(); i++) {
				String mode = (String) it.next();
				wsrpModes[i] = WSRPUtil.toWsrpMode(mode);
			}
			this._modes = wsrpModes;
		}
		catch (Exception e) {
			_logger.entry(Logger.ERROR, "Could not get portlet definition", e);
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}

		return this._modes;
	}

	public String[] getWindowStates() {
		// TODO: for now we simply return what we know
		//       we should return what our environment supports
		return WindowStates.getWindowStatesAsStringArray();
	}

	public String[] getMimeTypes() {
		// TODO: return whatever our environment supports
		return null;
	}

	public String[] getCharacterEncodingSet() {
		// TODO: return whatever our environment supports
		return null;
	}

	public boolean isModeSupported(String wsrpMode) {
		if (wsrpMode == null)
			throw new IllegalArgumentException("A mode must not be null");

		return _portletRequest.isPortletModeAllowed(Modes
				.getJsrPortletModeFromWsrpMode(Modes.fromString(wsrpMode)));
	}

	public boolean isWindowStateSupported(String wsrpWindowState) {
		if (wsrpWindowState == null)
			throw new IllegalArgumentException(
					"A window state must not be null");

		return _portletRequest.isWindowStateAllowed(WindowStates
				.getJsrPortletStateFromWsrpState(WindowStates
						.fromString(wsrpWindowState)));
	}

	public String getUserAuthentication() {
		return this._userAuth;
	}

	private void integrateParameter() {
		final String MN = "integrateParameter()";

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.entry(Logger.TRACE_HIGH, MN);
		}

		ArrayList formParams = new ArrayList();
		Set paramKeysSet = _portletRequest.getParameterMap().keySet();

		// interaction state
		this._interactionState = _portletRequest
				.getParameter(Constants.INTERACTION_STATE);

		// check for navistate
		// if navistate is stored as url parameter take this
		// otherwise look for render param
		this._naviState = _portletRequest
				.getParameter(Constants.NAVIGATIONAL_STATE);
		if (this._naviState == null) {
			this._naviState = _portletRequest
					.getParameter(WSRPProxyPortlet.NAVIGATIONAL_STATE);
		}

		Iterator paramKeys = paramKeysSet.iterator();
		while (paramKeys.hasNext()) {
			String key = (String) paramKeys.next();

			if (!Constants.isWsrpURLParam(key)
					&& !key.equals(WSRPProxyPortlet.NAVIGATIONAL_STATE)
					&& !key.equals(WSRPProxyPortlet.REMOTE_INVOCATION)) {
				// the rest are form parameter
				String[] values = _portletRequest.getParameterValues(key);
				if (values != null) {
					for (int i = 0; i < values.length; i++) {
						NamedString paramPair = new NamedString();
						paramPair.setName(key);
						paramPair.setValue(values[i]);

						formParams.add(paramPair);
					}
				}
			}
		}

		if (!formParams.isEmpty()) {
			_formParameters = new NamedString[formParams.size()];
			formParams.toArray(_formParameters);
		}

		if (_logger.isLogging(Logger.TRACE_HIGH)) {
			_logger.exit(Logger.TRACE_HIGH, MN);
		}
	}

	private final PortletRequest _portletRequest;

	private final PortletWindowSession _windowSession;

	private final String _userAuth;

	private NamedString[] _formParameters = null;

	private String _interactionState = null;

	private String _currentMode = null;

	private String _currentState = null;

	private String _naviState = null;

	//  just for performance reasons we cache this info
	private String[] _modes = null;

	private String[] _locales = null;

	protected Logger _logger = LogManager.getLogManager().getLogger(
			WSRPRequestImpl.class);

}