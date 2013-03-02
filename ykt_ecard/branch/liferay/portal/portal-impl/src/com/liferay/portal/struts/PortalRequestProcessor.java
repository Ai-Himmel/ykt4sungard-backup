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

package com.liferay.portal.struts;

import com.liferay.portal.LayoutPermissionException;
import com.liferay.portal.PortletActiveException;
import com.liferay.portal.RequiredLayoutException;
import com.liferay.portal.RequiredRoleException;
import com.liferay.portal.UserActiveException;
import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.portlet.LiferayWindowState;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletPreferencesIds;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserTracker;
import com.liferay.portal.model.UserTrackerPath;
import com.liferay.portal.model.impl.LayoutImpl;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.service.LayoutLocalServiceUtil;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.service.PortletPreferencesLocalServiceUtil;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.service.persistence.UserTrackerPathUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.*;
import com.liferay.portlet.CachePortlet;
import com.liferay.portlet.PortletConfigFactory;
import com.liferay.portlet.PortletInstanceFactory;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.portlet.RenderRequestFactory;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.RenderResponseFactory;
import com.liferay.portlet.RenderResponseImpl;
import com.liferay.util.CollectionFactory;
import com.liferay.util.HttpUtil;
import com.liferay.util.servlet.SessionErrors;

import java.io.IOException;

import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.Map.Entry;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.WindowState;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.config.ForwardConfig;
import org.apache.struts.tiles.TilesRequestProcessor;

/**
 * <a href="PortalRequestProcessor.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 *
 */
public class PortalRequestProcessor extends TilesRequestProcessor {

	public PortalRequestProcessor() {

		// auth.forward.last.path.

		_lastPaths = CollectionFactory.getHashSet();

		_lastPaths.add(_PATH_PORTAL_LAYOUT);

		_addPaths(_lastPaths, PropsUtil.AUTH_FORWARD_LAST_PATHS);

		// auth.public.path.

		_publicPaths = CollectionFactory.getHashSet();

		_publicPaths.add(_PATH_C);
		_publicPaths.add(_PATH_PORTAL_CSS);
		_publicPaths.add(_PATH_PORTAL_CSS_CACHED);
		_publicPaths.add(_PATH_PORTAL_FLASH);
		_publicPaths.add(_PATH_PORTAL_J_LOGIN);
		_publicPaths.add(_PATH_PORTAL_JAVASCRIPT);
		_publicPaths.add(_PATH_PORTAL_JAVASCRIPT_CACHED);
		_publicPaths.add(_PATH_PORTAL_LAYOUT);
		_publicPaths.add(_PATH_PORTAL_LOGIN);
		_publicPaths.add(_PATH_PORTAL_LOGIN_CAPTCHA);
		_publicPaths.add(_PATH_PORTAL_RENDER_PORTLET);
		_publicPaths.add(_PATH_PORTAL_TCK);

		_addPaths(_publicPaths, PropsUtil.AUTH_PUBLIC_PATHS);

		_trackerIgnorePaths = CollectionFactory.getHashSet();

		_addPaths(_trackerIgnorePaths, PropsUtil.SESSION_TRACKER_IGNORE_PATHS);
	}

	public void process(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		String path = super.processPath(req, res);

		ActionMapping mapping =
			(ActionMapping)moduleConfig.findActionConfig(path);

		if ((mapping == null) && !path.startsWith(_PATH_WSRP)) {
			String lastPath = getLastPath(req);

			if (_log.isDebugEnabled()) {
				_log.debug("Last path " + lastPath);
			}

			res.sendRedirect(lastPath);

			return;
		}

		super.process(req, res);

		try {
			if (isPortletPath(path)) {
				cleanUp(req);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	protected void callParentDoForward(
			String uri, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		super.doForward(uri, req, res);
	}

	protected void doForward(
			String uri, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		StrutsUtil.forward(uri, getServletContext(), req, res);
	}

	protected void doInclude(
			String uri, HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		StrutsUtil.include(uri, getServletContext(), req, res);
	}

	protected HttpServletRequest callParentProcessMultipart(
		HttpServletRequest req) {

		return super.processMultipart(req);
	}

	protected HttpServletRequest processMultipart(HttpServletRequest req) {

		// Disable Struts from automatically wrapping a multipart request

		return req;
	}

	protected String callParentProcessPath(
			HttpServletRequest req, HttpServletResponse res)
		throws IOException {

		return super.processPath(req, res);
	}

	protected StringMaker getFriendlyTrackerPath(
			String path, ThemeDisplay themeDisplay, HttpServletRequest req)
		throws Exception {

		if (!path.equals(_PATH_PORTAL_LAYOUT)) {
			return null;
		}

		long plid = ParamUtil.getLong(req, "p_l_id");

		if (plid == 0) {
			return null;
		}

		Layout layout = LayoutLocalServiceUtil.getLayout(plid);

		String layoutFriendlyURL = PortalUtil.getLayoutFriendlyURL(
			layout, themeDisplay);

		StringMaker sm = new StringMaker();

		sm.append(layoutFriendlyURL);

		String portletId = ParamUtil.getString(req, "p_p_id");

		if (Validator.isNull(portletId)) {
			return sm;
		}

		long companyId = PortalUtil.getCompanyId(req);

		Portlet portlet = PortletLocalServiceUtil.getPortletById(
			companyId, portletId);

		if (portlet == null) {
			String strutsPath = path.substring(
				1, path.lastIndexOf(StringPool.SLASH));

			portlet = PortletLocalServiceUtil.getPortletByStrutsPath(
				companyId, strutsPath);
		}

		if ((portlet == null) || !portlet.isActive()) {
			sm.append(StringPool.QUESTION);
			sm.append(req.getQueryString());

			return sm;
		}

		String namespace = PortalUtil.getPortletNamespace(portletId);

		FriendlyURLMapper friendlyURLMapper =
			portlet.getFriendlyURLMapperInstance();

		if (friendlyURLMapper == null) {
			sm.append(StringPool.QUESTION);
			sm.append(req.getQueryString());

			return sm;
		}

		PortletURLImpl portletURL = new PortletURLImpl(
			req, portletId, plid, false);

		Iterator itr = req.getParameterMap().entrySet().iterator();

		while (itr.hasNext()) {
			Entry entry = (Entry)itr.next();

			String key = (String)entry.getKey();

			if (key.startsWith(namespace)) {
				key = key.substring(namespace.length());

				Object value = entry.getValue();

				if (value instanceof String[]) {
					portletURL.setParameter(key, (String[])entry.getValue());
				}
				else {
					portletURL.setParameter(key, (String)entry.getValue());
				}
			}
		}

		String portletFriendlyURL = friendlyURLMapper.buildPath(portletURL);

		if (portletFriendlyURL != null) {
			sm.append(portletFriendlyURL);
		}
		else {
			sm.append(StringPool.QUESTION);
			sm.append(req.getQueryString());
		}

		return sm;
	}

	protected String processPath(
			HttpServletRequest req, HttpServletResponse res)
		throws IOException {

		String path = super.processPath(req, res);

		HttpSession ses = req.getSession();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		// Current users

		UserTracker userTracker = LiveUsers.getUserTracker(ses.getId());

		if ((userTracker != null) && (path != null) &&
			(!path.equals(_PATH_C)) &&
			(path.indexOf(_PATH_J_SECURITY_CHECK) == -1) &&
			(path.indexOf(_PATH_PORTAL_PROTECTED) == -1) &&
			(!_trackerIgnorePaths.contains(path))) {

			StringMaker sm = null;

			try {
				if (PropsValues.SESSION_TRACKER_FRIENDLY_PATHS_ENABLED) {
					sm = getFriendlyTrackerPath(path, themeDisplay, req);
				}
			}
			catch (Exception e) {
				_log.error(e, e);
			}

			if (sm == null) {
				sm = new StringMaker();

				sm.append(path);
				sm.append(StringPool.QUESTION);
				sm.append(req.getQueryString());
			}

			UserTrackerPath userTrackerPath = UserTrackerPathUtil.create(0);

			userTrackerPath.setUserTrackerId(userTracker.getUserTrackerId());
			userTrackerPath.setPath(sm.toString());
			userTrackerPath.setPathDate(new Date());

			userTracker.addPath(userTrackerPath);
		}

		String remoteUser = req.getRemoteUser();

		User user = null;

		try {
			user = PortalUtil.getUser(req);
		}
		catch (Exception e) {
		}

		// Last path

		if ((path != null) && (_lastPaths.contains(path)) &&
			(!_trackerIgnorePaths.contains(path))) {

			boolean saveLastPath = ParamUtil.getBoolean(
				req, "save_last_path", true);

			// Exclusive and pop up window states should never be set as the
			// last path

			if (LiferayWindowState.isExclusive(req) ||
				LiferayWindowState.isPopUp(req)) {

				saveLastPath = false;
			}

			// Save last path

			if (saveLastPath) {

				// Was a last path set by another servlet that dispatched to
				// the MainServlet? If so, use that last path instead.

				LastPath lastPath =
					(LastPath)req.getAttribute(WebKeys.LAST_PATH);

				if (lastPath == null) {
					lastPath = new LastPath(
						themeDisplay.getPathMain(), path,
						req.getParameterMap());
				}

				ses.setAttribute(WebKeys.LAST_PATH, lastPath);
			}
		}

		// Authenticated users can always log out

		if ((remoteUser != null || user != null) && (path != null) &&
			(path.equals(_PATH_PORTAL_LOGOUT))) {

			return _PATH_PORTAL_LOGOUT;
		}

		// Authenticated users can retrieve CSS and JavaScript

		if ((remoteUser != null || user != null) && (path != null) &&
			(path.equals(_PATH_PORTAL_CSS) ||
			 path.equals(_PATH_PORTAL_CSS_CACHED) ||
			 path.equals(_PATH_PORTAL_JAVASCRIPT) ||
			 path.equals(_PATH_PORTAL_JAVASCRIPT_CACHED))) {

			return path;
		}

		// Authenticated users can always agree to terms of use

		if ((remoteUser != null || user != null) && (path != null) &&
			(path.equals(_PATH_PORTAL_UPDATE_TERMS_OF_USE))) {

			return _PATH_PORTAL_UPDATE_TERMS_OF_USE;
		}

		// Authenticated users must still exist in the system

		if ((remoteUser != null) && (user == null)) {
			return _PATH_PORTAL_LOGOUT;
		}

		// Authenticated users must agree to Terms of Use

		if ((user != null) && (!user.isAgreedToTermsOfUse())) {
			if (PropsValues.TERMS_OF_USE_REQUIRED) {
				return _PATH_PORTAL_TERMS_OF_USE;
			}
		}

		// Authenticated users must be active

		if ((user != null) && (!user.isActive())) {
			SessionErrors.add(req, UserActiveException.class.getName());

			return _PATH_PORTAL_ERROR;
		}

		// Authenticated users may not be allowed to have simultaneous logins

		if (!PropsValues.AUTH_SIMULTANEOUS_LOGINS) {
			Boolean staleSession =
				(Boolean)ses.getAttribute(WebKeys.STALE_SESSION);

			if ((user != null) && (staleSession != null) &&
				(staleSession.booleanValue())) {

				return _PATH_PORTAL_ERROR;
			}
		}

		// Authenticated users must have a current password

		if ((user != null) && (user.isPasswordReset())) {
			return _PATH_PORTAL_CHANGE_PASSWORD;
		}

		// Authenticated users must have at least one personalized page

		if (user != null) {
			List layouts = themeDisplay.getLayouts();

			if ((layouts == null) || (layouts.size() == 0)) {
				SessionErrors.add(
					req, RequiredLayoutException.class.getName());

				return _PATH_PORTAL_ERROR;
			}
		}

		// Users must sign in

		if (!isPublicPath(path)) {
			if (user == null) {
				SessionErrors.add(req, PrincipalException.class.getName());

				return _PATH_PORTAL_LOGIN;
			}
		}

		ActionMapping mapping =
			(ActionMapping)moduleConfig.findActionConfig(path);

		if (path.startsWith(_PATH_WSRP)) {
			path = _PATH_WSRP;
		}
		else {
			path = mapping.getPath();
		}

		// Authenticated users must have at least one role

		if (user != null) {
			try {

				// FIX ME

				if (false) {
					SessionErrors.add(
						req, RequiredRoleException.class.getName());

					return _PATH_PORTAL_ERROR;
				}
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}

		// Define the portlet objects

		if (isPortletPath(path)) {
			try {
				Portlet portlet = null;

				long companyId = PortalUtil.getCompanyId(req);
				String portletId = ParamUtil.getString(req, "p_p_id");

				if (Validator.isNotNull(portletId)) {
					portlet = PortletLocalServiceUtil.getPortletById(
						companyId, portletId);
				}

				if (portlet == null) {
					String strutsPath = path.substring(
						1, path.lastIndexOf(StringPool.SLASH));

					portlet = PortletLocalServiceUtil.getPortletByStrutsPath(
						companyId, strutsPath);
				}

				if (portlet != null && portlet.isActive()) {
					defineObjects(req, res, portlet);
				}
			}
			catch (Exception e) {
				req.setAttribute(PageContext.EXCEPTION, e);

				path = _PATH_COMMON_ERROR;
			}
		}

		// Authenticated users must have access to at least one layout

		if (SessionErrors.contains(
				req, LayoutPermissionException.class.getName())) {

			return _PATH_PORTAL_ERROR;
		}

		return path;
	}

	protected boolean callParentProcessRoles(
			HttpServletRequest req, HttpServletResponse res,
			ActionMapping mapping)
		throws IOException, ServletException {

		return super.processRoles(req, res, mapping);
	}

	protected boolean processRoles(
			HttpServletRequest req, HttpServletResponse res,
			ActionMapping mapping)
		throws IOException, ServletException {

		String path = mapping.getPath();

		if (isPublicPath(path)) {
			return true;
		}

		boolean authorized = true;

		User user = null;

		try {
			user = PortalUtil.getUser(req);
		}
		catch (Exception e) {
		}

		if ((user != null) && isPortletPath(path)) {
			try {

				// Authenticated users can always log out

				if (path.equals(_PATH_PORTAL_LOGOUT)) {
					return true;
				}

				Portlet portlet = null;

				String portletId = ParamUtil.getString(req, "p_p_id");

				if (Validator.isNotNull(portletId)) {
					portlet = PortletLocalServiceUtil.getPortletById(
						user.getCompanyId(), portletId);
				}

				String strutsPath = path.substring(
					1, path.lastIndexOf(StringPool.SLASH));

				if (portlet != null) {
					if (!strutsPath.equals(portlet.getStrutsPath())) {
						throw new PrincipalException();
					}
				}
				else {
					portlet = PortletLocalServiceUtil.getPortletByStrutsPath(
						user.getCompanyId(), strutsPath);
				}

				if ((portlet != null) && portlet.isActive()) {
					ThemeDisplay themeDisplay =
						(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

					Layout layout = themeDisplay.getLayout();
					PermissionChecker permissionChecker =
						themeDisplay.getPermissionChecker();

					if (!PortletPermissionUtil.contains(
							permissionChecker, layout.getPlid(), portlet,
							ActionKeys.VIEW)) {

						throw new PrincipalException();
					}
				}
				else if (portlet != null && !portlet.isActive()) {
					SessionErrors.add(
						req, PortletActiveException.class.getName());

					authorized = false;
				}
			}
			catch (Exception e) {
				SessionErrors.add(req, PrincipalException.class.getName());

				authorized = false;
			}
		}

		if (!authorized) {
			ForwardConfig forwardConfig =
				mapping.findForward(_PATH_PORTAL_ERROR);

			processForwardConfig(req, res, forwardConfig);

			return false;
		}
		else {
			return true;
		}
	}

	protected String getLastPath(HttpServletRequest req) {
		HttpSession ses = req.getSession();

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		Boolean httpsInitial = (Boolean)ses.getAttribute(WebKeys.HTTPS_INITIAL);

		String portalURL = null;

		if ((PropsValues.COMPANY_SECURITY_AUTH_REQUIRES_HTTPS) &&
			(httpsInitial != null) && (!httpsInitial.booleanValue())) {

			portalURL = PortalUtil.getPortalURL(req, false);
		}
		else {
			portalURL = PortalUtil.getPortalURL(req);
		}

		StringMaker sm = new StringMaker();

		sm.append(portalURL);
		sm.append(themeDisplay.getPathMain());
		sm.append(_PATH_PORTAL_LAYOUT);

		if (!PropsValues.AUTH_FORWARD_BY_LAST_PATH) {
			if (req.getRemoteUser() != null) {

				// If we do not forward by last path and the user is logged in,
				// forward to the user's default layout to prevent a lagging
				// loop

				sm.append(StringPool.QUESTION);
				sm.append("p_l_id");
				sm.append(StringPool.EQUAL);
				sm.append(LayoutImpl.DEFAULT_PLID);
			}

			return sm.toString();
		}

		LastPath lastPath = (LastPath)ses.getAttribute(WebKeys.LAST_PATH);

		if (lastPath == null) {
			return sm.toString();
		}

		Map parameterMap = lastPath.getParameterMap();

		// Only test for existing mappings for last paths that were set when the
		// user accessed a layout directly instead of through its friendly URL

		if (lastPath.getContextPath().equals(themeDisplay.getPathMain())) {
			ActionMapping mapping =
				(ActionMapping)moduleConfig.findActionConfig(
					lastPath.getPath());

			if ((mapping == null) || (parameterMap == null)) {
				return sm.toString();
			}
		}

		StringMaker lastPathSM = new StringMaker();

		lastPathSM.append(portalURL);
		lastPathSM.append(lastPath.getContextPath());
		lastPathSM.append(lastPath.getPath());
		lastPathSM.append(HttpUtil.parameterMapToString(parameterMap));

		return lastPathSM.toString();
	}

	protected boolean isPortletPath(String path) {
		if ((path != null) &&
			(!path.equals(_PATH_C)) &&
			(!path.startsWith(_PATH_COMMON)) &&
			(path.indexOf(_PATH_J_SECURITY_CHECK) == -1) &&
			(!path.startsWith(_PATH_PORTAL)) &&
			(!path.startsWith(_PATH_WSRP))) {

			return true;
		}
		else {
			return false;
		}
	}

	protected boolean isPublicPath(String path) {
		if ((path != null) &&
			(_publicPaths.contains(path)) ||
			(path.startsWith(_PATH_COMMON)) ||
			(path.startsWith(_PATH_WSRP))) {

			return true;
		}
		else {
			return false;
		}
	}

	protected void defineObjects(
			HttpServletRequest req, HttpServletResponse res, Portlet portlet)
		throws Exception {

		String portletId = portlet.getPortletId();

		ServletContext ctx =
			(ServletContext)req.getAttribute(WebKeys.CTX);

		CachePortlet cachePortlet = PortletInstanceFactory.create(portlet, ctx);

		PortletPreferencesIds portletPreferencesIds =
			PortletPreferencesFactoryUtil.getPortletPreferencesIds(
				req, portletId);

		PortletPreferences portletPreferences =
			PortletPreferencesLocalServiceUtil.getPreferences(
				portletPreferencesIds);

		PortletConfig portletConfig = PortletConfigFactory.create(portlet, ctx);
		PortletContext portletCtx =
			portletConfig.getPortletContext();

		RenderRequestImpl renderRequestImpl = RenderRequestFactory.create(
			req, portlet, cachePortlet, portletCtx, WindowState.MAXIMIZED,
			PortletMode.VIEW, portletPreferences);

		RenderResponseImpl renderResponseImpl = RenderResponseFactory.create(
			renderRequestImpl, res, portletId, portlet.getCompanyId());

		renderRequestImpl.defineObjects(portletConfig, renderResponseImpl);

		req.setAttribute(WebKeys.PORTLET_STRUTS_EXECUTE, Boolean.TRUE);
	}

	protected void cleanUp(HttpServletRequest req) throws Exception {

		// Clean up portlet objects that may have been created by defineObjects
		// for portlets that are called directly from a Struts path

		RenderRequestImpl renderRequestImpl =
			(RenderRequestImpl)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_REQUEST);

		if (renderRequestImpl != null) {
			RenderRequestFactory.recycle(renderRequestImpl);
		}

		RenderResponseImpl renderResponseImpl =
			(RenderResponseImpl)req.getAttribute(
				JavaConstants.JAVAX_PORTLET_RESPONSE);

		if (renderResponseImpl != null) {
			RenderResponseFactory.recycle(renderResponseImpl);
		}
	}

	private void _addPaths(Set paths, String propsKey) {
		String[] pathsArray = PropsUtil.getArray(propsKey);

		for (int i = 0; i < pathsArray.length; i++) {
			paths.add(pathsArray[i]);
		}
	}

	private static String _PATH_C = "/c";

	private static String _PATH_COMMON = "/common";

	private static String _PATH_COMMON_ERROR = "/common/error";

	private static String _PATH_J_SECURITY_CHECK = "/j_security_check";

	private static String _PATH_PORTAL = "/portal";

	private static String _PATH_PORTAL_CHANGE_PASSWORD =
		"/portal/change_password";

	private static String _PATH_PORTAL_CSS = "/portal/css";

	private static String _PATH_PORTAL_CSS_CACHED = "/portal/css_cached";

	private static String _PATH_PORTAL_ERROR = "/portal/error";

	private static String _PATH_PORTAL_FLASH = "/portal/flash";

	private static String _PATH_PORTAL_J_LOGIN = "/portal/j_login";

	private static String _PATH_PORTAL_JAVASCRIPT = "/portal/javascript";

	private static String _PATH_PORTAL_JAVASCRIPT_CACHED =
		"/portal/javascript_cached";

	private static String _PATH_PORTAL_LAYOUT = "/portal/layout";

	private static String _PATH_PORTAL_LOGIN = "/portal/login";

	private static String _PATH_PORTAL_LOGIN_CAPTCHA = "/portal/login_captcha";

	private static String _PATH_PORTAL_LOGOUT = "/portal/logout";

	private static String _PATH_PORTAL_PROTECTED = "/portal/protected";

	private static String _PATH_PORTAL_RENDER_PORTLET =
		"/portal/render_portlet";

	private static String _PATH_PORTAL_TCK = "/portal/tck";

	private static String _PATH_PORTAL_TERMS_OF_USE = "/portal/terms_of_use";

	private static String _PATH_PORTAL_UPDATE_TERMS_OF_USE =
		"/portal/update_terms_of_use";

	private static String _PATH_WSRP = "/wsrp";

	private static Log _log = LogFactory.getLog(PortalRequestProcessor.class);

	private Set _lastPaths;
	private Set _publicPaths;
	private Set _trackerIgnorePaths;

}