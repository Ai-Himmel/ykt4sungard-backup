/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

package com.liferay.portlet;

import com.liferay.portal.kernel.portlet.LiferayRenderRequest;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.servlet.BrowserSniffer;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.servlet.NamespaceServletRequest;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.portal.servlet.SharedSessionUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.CollectionFactory;
import com.liferay.util.servlet.DynamicServletRequest;
import com.liferay.util.servlet.ProtectedPrincipal;
import com.liferay.util.servlet.SharedSessionServletRequest;

import java.security.Principal;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;

import javax.portlet.PortalContext;
import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.PortletSession;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;

/**
 * <a href="RenderRequestImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Brian Myunghun Kim
 * @author Sergey Ponomarev
 *
 */
public class RenderRequestImpl implements LiferayRenderRequest {

	public WindowState getWindowState() {
		return _windowState;
	}

	public void setWindowState(WindowState windowState) {
		_windowState = windowState;
	}

	public boolean isWindowStateAllowed(WindowState windowState) {
		return PortalContextImpl.isSupportedWindowState(windowState);
	}

	public PortletMode getPortletMode() {
		return _portletMode;
	}

	public void setPortletMode(PortletMode portletMode) {
		_portletMode = portletMode;
	}

	public boolean isPortletModeAllowed(PortletMode portletMode) {
		if ((portletMode == null) || Validator.isNull(portletMode.toString())) {
			return true;
		}
		else {
			return _portlet.hasPortletMode(
				getResponseContentType(), portletMode);
		}
	}

	public PortletPreferences getPreferences() {
		return new PortletPreferencesWrapper(getPreferencesImpl(), false);
	}

	public PortletPreferencesImpl getPreferencesImpl() {
		return (PortletPreferencesImpl)_prefs;
	}

	public PortletSession getPortletSession() {
		return _ses;
	}

	public PortletSession getPortletSession(boolean create) {
		/*HttpSession httpSes = _req.getSession(create);

		if (httpSes == null) {
			return null;
		}
		else {
			if (create) {
				_ses = new PortletSessionImpl(
					_req, _portletName, _portletCtx, _portalSessionId,
					_plid);
			}

			return _ses;
		}*/

		/*if ((_ses == null) && create) {
			_req.getSession(create);

			_ses = new PortletSessionImpl(
				_req, _portletName, _portletCtx, _portalSessionId, _plid);
		}*/

		return _ses;
	}

	public String getProperty(String name) {
		return _portalCtx.getProperty(name);
	}

	public Enumeration getProperties(String name) {
		List values = new ArrayList();

		String value = _portalCtx.getProperty(name);

		if (value != null) {
			values.add(value);
		}

		return Collections.enumeration(values);
	}

	public Enumeration getPropertyNames() {
		return _portalCtx.getPropertyNames();
	}

	public PortalContext getPortalContext() {
		return _portalCtx;
	}

	public String getAuthType() {
		return _req.getAuthType();
	}

	public String getContextPath() {
		//return StringPool.SLASH + _req.getContextPath();
		return StringPool.SLASH + _portletCtx.getPortletContextName();
	}

	public String getRemoteUser() {
		return _remoteUser;
	}

	public Principal getUserPrincipal() {
		return _userPrincipal;
	}

	public boolean isUserInRole(String role) {
		if (_remoteUserId <= 0) {
			return false;
		}
		else {
			try {
				long companyId = PortalUtil.getCompanyId(_req);

				return RoleLocalServiceUtil.hasUserRole(
					_remoteUserId, companyId, role, true);
			}
			catch (Exception e) {
				_log.error(e);
			}

			return _req.isUserInRole(role);
		}
	}

	public Object getAttribute(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		if (name.equals(RenderRequest.USER_INFO)) {
			if (getRemoteUser() != null) {
				LinkedHashMap userInfo = new LinkedHashMap();

				// Liferay user attributes

				try {
					User user = PortalUtil.getUser(_req);

					UserAttributes userAttributes = new UserAttributes(user);

					// Mandatory user attributes

					userInfo.put(
						UserAttributes.LIFERAY_COMPANY_ID,
						userAttributes.getValue(
							UserAttributes.LIFERAY_COMPANY_ID));

					userInfo.put(
						UserAttributes.LIFERAY_USER_ID,
						userAttributes.getValue(
							UserAttributes.LIFERAY_USER_ID));

					// Portlet user attributes

					Iterator itr = _portlet.getUserAttributes().iterator();

					while (itr.hasNext()) {
						String attrName = (String)itr.next();
						String attrValue = userAttributes.getValue(attrName);

						if (attrValue != null) {
							userInfo.put(attrName, attrValue);
						}
					}
				}
				catch (Exception e) {
					e.printStackTrace();
				}

				Map unmodifiableUserInfo =
					Collections.unmodifiableMap((Map)userInfo.clone());

				// Custom user attributes

				Map cuaInstances = CollectionFactory.getHashMap();

				Iterator itr =
					_portlet.getCustomUserAttributes().entrySet().iterator();

				while (itr.hasNext()) {
					Map.Entry entry = (Map.Entry)itr.next();

					String attrName = (String)entry.getKey();
					String attrCustomClass = (String)entry.getValue();

					CustomUserAttributes cua =
						(CustomUserAttributes)cuaInstances.get(attrCustomClass);

					if (cua == null) {
						if (_portlet.isWARFile()) {
							PortletContextWrapper pcw =
								(PortletContextWrapper)PortletContextPool.get(
									_portlet.getRootPortletId());

							cua =
								(CustomUserAttributes)
									pcw.getCustomUserAttributes().get(
										attrCustomClass);

							cua = (CustomUserAttributes)cua.clone();
						}
						else {
							try {
								cua = (CustomUserAttributes)Class.forName(
									attrCustomClass).newInstance();
							}
							catch (Exception e) {
								e.printStackTrace();
							}
						}

						cuaInstances.put(attrCustomClass, cua);
					}

					if (cua != null) {
						String attrValue = cua.getValue(
							attrName, unmodifiableUserInfo);

						if (attrValue != null) {
							userInfo.put(attrName, attrValue);
						}
					}
				}

				return userInfo;
			}
		}

		return _req.getAttribute(name);
	}

	public void setAttribute(String name, Object obj) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		if (obj == null) {
			removeAttribute(name);
		}
		else {
			_req.setAttribute(name, obj);
		}
	}

	public void removeAttribute(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		_req.removeAttribute(name);
	}

	public Enumeration getAttributeNames() {
		List names = new ArrayList();

		Enumeration enu = _req.getAttributeNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (!name.equals(JavaConstants.JAVAX_SERVLET_INCLUDE_PATH_INFO)) {
				names.add(name);
			}
		}

		return Collections.enumeration(names);
	}

	public String getParameter(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		return _req.getParameter(name);
	}

	public Enumeration getParameterNames() {
		return _req.getParameterNames();
	}

	public String[] getParameterValues(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		return _req.getParameterValues(name);
	}

	public Map getParameterMap() {
		return _req.getParameterMap();
	}

	public boolean isSecure() {
		return _req.isSecure();
	}

	public String getRequestedSessionId() {
		return _req.getSession().getId();
	}

	public boolean isRequestedSessionIdValid() {
		if (_ses != null) {
			return _ses.isValid();
		}
		else {
			return _req.isRequestedSessionIdValid();
		}
	}

	public String getResponseContentType() {
		if (_wapTheme) {
			return ContentTypes.XHTML_MP;
		}
		else {
			return ContentTypes.TEXT_HTML;
		}
	}

	public Enumeration getResponseContentTypes() {
		List responseContentTypes = new ArrayList();

		responseContentTypes.add(getResponseContentType());

		return Collections.enumeration(responseContentTypes);
	}

	public Locale getLocale() {
		Locale locale = _locale;

		if (locale == null) {
			locale = _req.getLocale();
		}

		if (locale == null) {
			locale = LocaleUtil.getDefault();
		}

		return locale;
	}

	public Enumeration getLocales() {
		return _req.getLocales();
	}

	public String getScheme() {
		return _req.getScheme();
	}

	public String getServerName() {
		return _req.getServerName();
	}

	public int getServerPort() {
		return _req.getServerPort();
	}

	public HttpServletRequest getHttpServletRequest() {
		return _req;
	}

	public String getPortletName() {
		return _portletName;
	}

	public Portlet getPortlet() {
		return _portlet;
	}

	public boolean isPrivateRequestAttributes() {
		return _portlet.isPrivateRequestAttributes();
	}

	public Map getRenderParameters() {
		return RenderParametersPool.get(_req, _plid, _portletName);
	}

	public void defineObjects(PortletConfig portletConfig, RenderResponse res) {
		setAttribute(JavaConstants.JAVAX_PORTLET_CONFIG, portletConfig);
		setAttribute(JavaConstants.JAVAX_PORTLET_REQUEST, this);
		setAttribute(JavaConstants.JAVAX_PORTLET_RESPONSE, res);
	}

	public boolean isAction() {
		return false;
	}

	protected RenderRequestImpl() {
		if (_log.isDebugEnabled()) {
			_log.debug("Creating new instance " + hashCode());
		}
	}

	protected void init(
		HttpServletRequest req, Portlet portlet, CachePortlet cachePortlet,
		PortletContext portletCtx, WindowState windowState,
		PortletMode portletMode, PortletPreferences prefs, long plid) {

		_portletName = portlet.getPortletId();

		String portletNamespace = PortalUtil.getPortletNamespace(_portletName);

		Map sharedSessionAttributes =
			SharedSessionUtil.getSharedSessionAttributes(req);

		boolean portalSessionShared = false;

		if (portlet.isWARFile() && !portlet.isPrivateSessionAttributes()) {
			portalSessionShared = true;
		}

		req = new SharedSessionServletRequest(
			req, sharedSessionAttributes, portalSessionShared);

		DynamicServletRequest dynamicReq = null;

		if (portlet.isPrivateRequestAttributes()) {
			dynamicReq = new NamespaceServletRequest(
				req, portletNamespace, portletNamespace, false);
		}
		else {
			dynamicReq = new DynamicServletRequest(req, false);
		}

		Enumeration enu = null;

		Map renderParameters = null;

		boolean portletFocus = false;

		if (_portletName.equals(req.getParameter("p_p_id"))) {

			// Request was targeted to this portlet

			boolean action = ParamUtil.getBoolean(req, "p_p_action");

			if (!action) {

				// Request was triggered by a render URL

			   portletFocus = true;
			}
			else if (action && isAction()) {

				// Request was triggered by an action URL and is being processed
				// by com.liferay.portlet.ActionRequestImpl

			   portletFocus = true;
			}
		}

		if (portletFocus) {
			renderParameters = new HashMap();

			if (!isAction() &&
				!LiferayWindowState.isExclusive(req) &&
				!LiferayWindowState.isPopUp(req)) {

				RenderParametersPool.put(
					req, plid, _portletName, renderParameters);
			}

			enu = req.getParameterNames();
		}
		else {
			renderParameters = RenderParametersPool.get(
				req, plid, _portletName);

			if (!_portletName.equals(req.getParameter("p_p_id"))) {
				_putNamespaceParams(
					req, portletNamespace, plid, renderParameters);
			}

			enu = Collections.enumeration(renderParameters.keySet());
		}

		while (enu.hasMoreElements()) {
			String param = (String)enu.nextElement();

			if (param.startsWith(portletNamespace) &&
				!cachePortlet.isFacesPortlet()) {

				String newParam =
					param.substring(portletNamespace.length(), param.length());
				String[] values = null;

				if (portletFocus) {
					values = req.getParameterValues(param);

					renderParameters.put(param, values);
				}
				else {
					values = (String[])renderParameters.get(param);
				}

				dynamicReq.setParameterValues(newParam, values);
			}
			else {

				// Do not allow reserved or null parameters to pass through.
				// Jetty has a bug that adds an additional null parameter
				// the enumeration of parameter names.

				if (!PortalUtil.isReservedParameter(param) &&
					Validator.isNotNull(param)) {

					String[] values = null;

					if (portletFocus) {
						values = req.getParameterValues(param);

						renderParameters.put(param, values);
					}
					else {
						values = (String[])renderParameters.get(param);
					}

					dynamicReq.setParameterValues(param, values);
				}
			}
		}

		_req = dynamicReq;
		_wapTheme = BrowserSniffer.is_wap_xhtml(_req);
		_portlet = portlet;
		_portalCtx = new PortalContextImpl();
		_portletCtx = portletCtx;
		_windowState = windowState;
		_portletMode = portletMode;
		_prefs = prefs;
		_portalSessionId = _req.getRequestedSessionId();
		_ses = new PortletSessionImpl(
			_req, _portletName, _portletCtx, _portalSessionId, plid);

		long userId = PortalUtil.getUserId(req);
		String remoteUser = req.getRemoteUser();

		String userPrincipalStrategy = portlet.getUserPrincipalStrategy();

		if (userPrincipalStrategy.equals(
				PortletImpl.USER_PRINCIPAL_STRATEGY_SCREEN_NAME)) {

			try {
				User user = PortalUtil.getUser(req);

				_remoteUser = user.getScreenName();
				_remoteUserId = user.getUserId();
				_userPrincipal = new ProtectedPrincipal(_remoteUser);
			}
			catch (Exception e) {
				_log.error(e);
			}
		}
		else {
			if ((userId > 0) && (remoteUser == null)) {
				_remoteUser = String.valueOf(userId);
				_remoteUserId = userId;
				_userPrincipal = new ProtectedPrincipal(_remoteUser);
			}
			else {
				_remoteUser = remoteUser;
				_remoteUserId = GetterUtil.getLong(remoteUser);
				_userPrincipal = req.getUserPrincipal();
			}
		}

		_locale = (Locale)_req.getSession().getAttribute(Globals.LOCALE_KEY);
		_plid = plid;
	}

	protected void recycle() {
		if (_log.isDebugEnabled()) {
			_log.debug("Recycling instance " + hashCode());
		}

		_req.removeAttribute(JavaConstants.JAVAX_PORTLET_CONFIG);
		_req.removeAttribute(JavaConstants.JAVAX_PORTLET_REQUEST);
		_req.removeAttribute(JavaConstants.JAVAX_PORTLET_RESPONSE);

		_req = null;
		_wapTheme = false;
		_portlet = null;
		_portletName = null;
		_portalCtx = null;
		_portletCtx = null;
		_windowState = null;
		_portletMode = null;
		_prefs = null;
		_ses = null;
		_portalSessionId = null;
		_remoteUser = null;
		_userPrincipal = null;
		_locale = null;
		_plid = 0;
	}

	private void _putNamespaceParams(
		HttpServletRequest req, String prefix, long plid,
		Map renderParameters) {

		// Adds params that are prefixed with given prefix to parameters pool.
		// Functionality added by Sergey Ponomarev to allow passing parameters
		// to multiple portlets in one portlet URL.

		Enumeration names = req.getParameterNames();

		while (names.hasMoreElements()) {
			String key = (String)(names.nextElement());

			if (key.startsWith(prefix)) {
				renderParameters.put(key, req.getParameterValues(key));
			}
		}

		RenderParametersPool.put(req, plid, _portletName, renderParameters);
	}

	private static Log _log = LogFactory.getLog(RenderRequestImpl.class);

	private DynamicServletRequest _req;
	private boolean _wapTheme;
	private Portlet _portlet;
	private String _portletName;
	private PortalContext _portalCtx;
	private PortletContext _portletCtx;
	private WindowState _windowState;
	private PortletMode _portletMode;
	private PortletPreferences _prefs;
	private PortletSessionImpl _ses;
	private String _portalSessionId;
	private String _remoteUser;
	private long _remoteUserId;
	private Principal _userPrincipal;
	private Locale _locale;
	private long _plid;

}