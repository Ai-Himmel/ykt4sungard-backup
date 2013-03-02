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

package com.liferay.portlet;

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
import javax.servlet.http.HttpSession;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;

import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.CollectionFactory;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.servlet.DynamicServletRequest;

/**
 * <a href="RenderRequestImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.46 $
 *
 */
public class RenderRequestImpl implements RenderRequest {

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
		if (portletMode == null || Validator.isNull(portletMode.toString())) {
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
					_layoutId);
			}

			return _ses;
		}*/

		if ((_ses == null) && create) {
			HttpSession httpSes = _req.getSession(create);

			_ses = new PortletSessionImpl(
				_req, _portletName, _portletCtx, _portalSessionId, _layoutId);
		}

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
		return _req.getRemoteUser();
	}

	public Principal getUserPrincipal() {
		return _req.getUserPrincipal();
	}

	public boolean isUserInRole(String role) {
		return _req.isUserInRole(role);
	}

	public Object getAttribute(String name) {
		if (name == null) {
			throw new IllegalArgumentException();
		}

		if (name.equals(RenderRequest.USER_INFO)) {
			if (_req.getRemoteUser() != null) {
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

			if (!name.equals("javax.servlet.include.path_info")) {
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
		return Constants.TEXT_HTML;
	}

	public Enumeration getResponseContentTypes() {
		List responseContentTypes = new ArrayList();

		responseContentTypes.add(getResponseContentType());

		return Collections.enumeration(responseContentTypes);
	}

	public Locale getLocale() {
		Locale locale =
			(Locale)_req.getSession().getAttribute(Globals.LOCALE_KEY);

		if (locale == null) {
			locale = _req.getLocale();
		}

		if (locale == null) {
			locale = Locale.getDefault();
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

	public Map getRenderParameters() {
		return RenderParametersPool.get(_req, _layoutId, _portletName);
	}

	public void defineObjects(PortletConfig portletConfig, RenderResponse res) {
		setAttribute(WebKeys.JAVAX_PORTLET_CONFIG, portletConfig);
		setAttribute(WebKeys.JAVAX_PORTLET_REQUEST, this);
		setAttribute(WebKeys.JAVAX_PORTLET_RESPONSE, res);
	}

	public boolean isAction() {
		return false;
	}

	protected RenderRequestImpl() {
		_log.debug("Creating new instance " + hashCode());
	}

	protected void init(
		HttpServletRequest req, Portlet portlet, CachePortlet cachePortlet,
		PortletContext portletCtx, WindowState windowState,
		PortletMode portletMode, PortletPreferences prefs, String layoutId) {

		_portletName = portlet.getPortletId();

		DynamicServletRequest dynamicReq =
			new DynamicServletRequest(req, false);

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

			RenderParametersPool.put(
				req, layoutId, _portletName, renderParameters);

			enu = req.getParameterNames();
		}
		else {
			renderParameters = RenderParametersPool.get(
				req, layoutId, _portletName);

			enu = Collections.enumeration(renderParameters.keySet());
		}

		String prefix = PortalUtil.getPortletNamespace(_portletName);

		while (enu.hasMoreElements()) {
			String param = (String)enu.nextElement();
			
			 
			
			if (param.startsWith(prefix)) {
				String newParam =
					param.substring(prefix.length(), param.length());
				String[] values = null;

				if (portletFocus) {
					values = req.getParameterValues(param);

					renderParameters.put(param, values);
				}
				else {
					values = (String[])renderParameters.get(param);
				}
				
				/*
				 * adjust maximize display
				 */
				if (param.endsWith("struts_action")) {
					Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);
					LayoutTypePortlet layoutType = (LayoutTypePortlet) layout.getLayoutType();
					int length = 0;
					try {
						length = layoutType.getPortlets().length;
					} catch (Exception ex) {
						
					}
					
					if (windowState.equals(WindowState.NORMAL) && length > 1) {
						values = new String[] {(String) portlet.getInitParams().get("view-action")};
					}
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
		_portlet = portlet;
		_cachePortlet = cachePortlet;
		_portalCtx = new PortalContextImpl();
		_portletCtx = portletCtx;
		_windowState = windowState;
		_portletMode = portletMode;
		_prefs = prefs;
		_portalSessionId = _req.getRequestedSessionId();
		_ses = new PortletSessionImpl(
			_req, _portletName, _portletCtx, _portalSessionId, layoutId);
		_layoutId = layoutId;
	}

	protected void recycle() {
		_log.debug("Recycling instance " + hashCode());

		_req = null;
		_portlet = null;
		_cachePortlet = null;
		_portletName = null;
		_portalCtx = null;
		_portletCtx = null;
		_windowState = null;
		_portletMode = null;
		_prefs = null;
		_ses = null;
		_portalSessionId = null;
		_layoutId = null;
	}

	private static final Log _log = LogFactory.getLog(RenderRequestImpl.class);

	private DynamicServletRequest _req;
	private Portlet _portlet;
	private CachePortlet _cachePortlet;
	private String _portletName;
	private PortalContext _portalCtx;
	private PortletContext _portletCtx;
	private WindowState _windowState;
	private PortletMode _portletMode;
	private PortletPreferences _prefs;
	private PortletSessionImpl _ses;
	private String _portalSessionId;
	private String _layoutId;

}