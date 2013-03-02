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

package com.liferay.portal.servlet;

import com.liferay.portal.deploy.hot.PluginPackageHotDeployListener;
import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.events.StartupAction;
import com.liferay.portal.job.Scheduler;
import com.liferay.portal.kernel.deploy.hot.HotDeployUtil;
import com.liferay.portal.kernel.events.ActionException;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.pop.MessageListener;
import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.servlet.PortletSessionTracker;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.PortalInitableUtil;
import com.liferay.portal.kernel.util.ReleaseInfo;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.lastmodified.LastModifiedAction;
import com.liferay.portal.model.ActivityTrackerInterpreter;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.model.impl.ActivityTrackerInterpreterImpl;
import com.liferay.portal.pop.POPServerUtil;
import com.liferay.portal.security.auth.CompanyThreadLocal;
import com.liferay.portal.security.auth.PrincipalThreadLocal;
import com.liferay.portal.service.CompanyLocalServiceUtil;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.service.impl.LayoutTemplateLocalUtil;
import com.liferay.portal.service.impl.ThemeLocalUtil;
import com.liferay.portal.struts.PortletRequestProcessor;
import com.liferay.portal.struts.StrutsUtil;
import com.liferay.portal.util.ActivityTrackerInterpreterUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.InitUtil;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.ShutdownUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portal.velocity.VelocityContextPool;
import com.liferay.portlet.PortletInstanceFactory;
import com.liferay.util.CollectionFactory;
import com.liferay.util.Http;
import com.liferay.util.servlet.EncryptedServletRequest;
import com.liferay.util.servlet.ProtectedServletRequest;
import com.liferay.util.servlet.UploadServletRequest;

import java.io.IOException;

import java.util.Iterator;
import java.util.List;
import java.util.Set;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionServlet;
import org.apache.struts.config.ModuleConfig;
import org.apache.struts.tiles.TilesUtilImpl;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;

import org.quartz.ObjectAlreadyExistsException;

/**
 * <a href="MainServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Jorge Ferrer
 * @author Brian Myunghun Kim
 *
 */
public class MainServlet extends ActionServlet {

	static {
		InitUtil.init();
	}

	public void init() throws ServletException {

		// Initialize

		if (_log.isDebugEnabled()) {
			_log.debug("Initialize");
		}

		super.init();

		// Process startup events

		if (_log.isDebugEnabled()) {
			_log.debug("Process startup events");
		}

		try {
			EventsProcessor.process(
				new String[] {
					StartupAction.class.getName()
				},
				true);
		}
		catch (RuntimeException re) {
			ShutdownUtil.shutdown(0);

			throw new ServletException(re);
		}
		catch (ActionException ae) {
			_log.error(ae, ae);
		}

		// Velocity

		String contextPath = PortalUtil.getPathContext();

		ServletContext ctx = getServletContext();

		VelocityContextPool.put(contextPath, ctx);

		// Initialize plugin package

		if (_log.isDebugEnabled()) {
			_log.debug("Initialize plugin package");
		}

		PluginPackage pluginPackage = null;

		try {
			pluginPackage =
				PluginPackageHotDeployListener.readPluginPackage(ctx);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Initialize portlets

		if (_log.isDebugEnabled()) {
			_log.debug("Initialize portlets");
		}

		List portlets = null;

		try {
			String[] xmls = new String[] {
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/" + PortalUtil.PORTLET_XML_FILE_NAME_CUSTOM)),
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/portlet-ext.xml")),
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-portlet.xml")),
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-portlet-ext.xml")),
				Http.URLtoString(ctx.getResource("/WEB-INF/web.xml"))
			};

			PortletLocalServiceUtil.initEAR(xmls, pluginPackage);

			portlets = PortletLocalServiceUtil.getPortlets();

			Iterator itr = portlets.iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				PortletInstanceFactory.create(portlet, ctx);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Initialize layout templates

		if (_log.isDebugEnabled()) {
			_log.debug("Initialize layout templates");
		}

		try {
			String[] xmls = new String[] {
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-layout-templates.xml")),
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-layout-templates-ext.xml"))
			};

			LayoutTemplateLocalUtil.init(ctx, xmls, pluginPackage);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Initialize look and feel

		if (_log.isDebugEnabled()) {
			_log.debug("Initialize look and feel");
		}

		try {
			String[] xmls = new String[] {
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-look-and-feel.xml")),
				Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-look-and-feel-ext.xml"))
			};

			ThemeLocalUtil.init(ctx, null, true, xmls, pluginPackage);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Scheduler

		if (_log.isDebugEnabled()) {
			_log.debug("Scheduler");
		}

		try {
			if (GetterUtil.getBoolean(PropsUtil.get(
					PropsUtil.SCHEDULER_ENABLED))) {

				Iterator itr = portlets.iterator();

				while (itr.hasNext()) {
					Portlet portlet = (Portlet)itr.next();

					String className = portlet.getSchedulerClass();

					if (portlet.isActive() && Validator.isNotNull(className)) {
						Scheduler scheduler =
							(Scheduler)InstancePool.get(className);

						scheduler.schedule();
					}
				}
			}
		}
		catch (ObjectAlreadyExistsException oaee) {
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Activity tracker interpreter

		if (_log.isDebugEnabled()) {
			_log.debug("Activity tracker interpreter");
		}

		try {
			Iterator itr = portlets.iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				ActivityTrackerInterpreter activityTrackerInterpreter =
					portlet.getActivityTrackerInterpreterInstance();

				if (portlet.isActive() &&
					(activityTrackerInterpreter != null)) {

					activityTrackerInterpreter =
						new ActivityTrackerInterpreterImpl(
							activityTrackerInterpreter);

					ActivityTrackerInterpreterUtil.
						addActivityTrackerInterpreter(
							activityTrackerInterpreter);
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// POP message listener

		if (_log.isDebugEnabled()) {
			_log.debug("POP message listener");
		}

		try {
			Iterator itr = portlets.iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				MessageListener popMessageListener =
					portlet.getPopMessageListenerInstance();

				if (portlet.isActive() && (popMessageListener != null)) {
					POPServerUtil.addListener(popMessageListener);
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Check web settings

		if (_log.isDebugEnabled()) {
			_log.debug("Check web settings");
		}

		try {
			String xml = Http.URLtoString(ctx.getResource("/WEB-INF/web.xml"));

			checkWebSettings(xml);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Last modified paths

		if (_log.isDebugEnabled()) {
			_log.debug("Last modified paths");
		}

		if (_lastModifiedPaths == null) {
			_lastModifiedPaths = CollectionFactory.getHashSet();

			String[] pathsArray = PropsUtil.getArray(
				PropsUtil.LAST_MODIFIED_PATHS);

			for (int i = 0; i < pathsArray.length; i++) {
				_lastModifiedPaths.add(pathsArray[i]);
			}
		}

		// Process global startup events

		if (_log.isDebugEnabled()) {
			_log.debug("Process global startup events");
		}

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.GLOBAL_STARTUP_EVENTS), true);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		// Initialize companies

		String[] webIds = PortalInstances.getWebIds();

		for (int i = 0; i < webIds.length; i++) {
			PortalInstances.initCompany(ctx, webIds[i]);
		}

		// See LEP-2885. Don't flush hot deploy events until after the portal
		// has initialized.

		PortalInitableUtil.flushInitables();
		HotDeployUtil.flushEvents();
	}

	public void callParentService(
			HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		super.service(req, res);
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		if (_log.isDebugEnabled()) {
			_log.debug("Process service request");
		}

		if (ShutdownUtil.isShutdown()) {
			res.setContentType(ContentTypes.TEXT_HTML_UTF8);

			String html = ContentUtil.get(
				"com/liferay/portal/dependencies/shutdown.html");

			res.getOutputStream().print(html);

			return;
		}

		HttpSession ses = req.getSession();

		// Company id

		long companyId = PortalInstances.getCompanyId(req);

		//CompanyThreadLocal.setCompanyId(companyId);

		// CTX

		ServletContext ctx = getServletContext();

		req.setAttribute(WebKeys.CTX, ctx);

		// Struts module config

		ModuleConfig moduleConfig = getModuleConfig(req);

		// Last modified check

		if (PropsValues.LAST_MODIFIED_CHECK) {
			String path = req.getPathInfo();

			if ((path != null) && _lastModifiedPaths.contains(path)) {
				ActionMapping mapping =
					(ActionMapping)moduleConfig.findActionConfig(path);

				LastModifiedAction lastModifiedAction =
					(LastModifiedAction)InstancePool.get(mapping.getType());

				String lmKey = lastModifiedAction.getLastModifiedKey(req);

				if (lmKey != null) {
					long ifModifiedSince =
						req.getDateHeader(HttpHeaders.IF_MODIFIED_SINCE);

					if (ifModifiedSince <= 0) {
						lastModifiedAction.setLastModifiedValue(lmKey, lmKey);
					}
					else {
						String lmValue =
							lastModifiedAction.getLastModifiedValue(lmKey);

						if (lmValue != null) {
							res.setStatus(HttpServletResponse.SC_NOT_MODIFIED);

							return;
						}
						else {
							lastModifiedAction.setLastModifiedValue(
								lmKey, lmKey);
						}
					}
				}
			}
		}

		// Portlet session tracker

		if (ses.getAttribute(WebKeys.PORTLET_SESSION_TRACKER) == null ) {
			ses.setAttribute(
				WebKeys.PORTLET_SESSION_TRACKER,
				PortletSessionTracker.getInstance());
		}

		// Portlet Request Processor

		PortletRequestProcessor portletReqProcessor =
			(PortletRequestProcessor)ctx.getAttribute(
				WebKeys.PORTLET_STRUTS_PROCESSOR);

		if (portletReqProcessor == null) {
			portletReqProcessor =
				PortletRequestProcessor.getInstance(this, moduleConfig);

			ctx.setAttribute(
				WebKeys.PORTLET_STRUTS_PROCESSOR, portletReqProcessor);
		}

		// Tiles definitions factory

		if (ctx.getAttribute(TilesUtilImpl.DEFINITIONS_FACTORY) == null) {
			ctx.setAttribute(
				TilesUtilImpl.DEFINITIONS_FACTORY,
				ctx.getAttribute(TilesUtilImpl.DEFINITIONS_FACTORY));
		}

		Object applicationAssociate = ctx.getAttribute(WebKeys.ASSOCIATE_KEY);

		if (ctx.getAttribute(WebKeys.ASSOCIATE_KEY) == null) {
			ctx.setAttribute(WebKeys.ASSOCIATE_KEY, applicationAssociate);
		}

		
		if (ParamUtil.get(req, WebKeys.ENCRYPT, false)) {// Encrypt request
			try {
				Company company = CompanyLocalServiceUtil.getCompanyById(
					companyId);

				req = new EncryptedServletRequest(req, company.getKeyObj());
			}
			catch (Exception e) {
			}
		}

		// Current URL

		PortalUtil.getCurrentURL(req);

		// Login

		long userId = PortalUtil.getUserId(req);
		String remoteUser = req.getRemoteUser();

		// Is JAAS enabled?

		if (!PropsValues.PORTAL_JAAS_ENABLE) {
			String jRemoteUser = (String)ses.getAttribute("j_remoteuser");

			if (jRemoteUser != null) {
				remoteUser = jRemoteUser;

				ses.removeAttribute("j_remoteuser");
			}
		}

		if ((userId > 0) && (remoteUser == null)) {
			remoteUser = String.valueOf(userId);
		}

		// WebSphere will not return the remote user unless you are
		// authenticated AND accessing a protected path. Other servers will
		// return the remote user for all threads associated with an
		// authenticated user. We use ProtectedServletRequest to ensure we get
		// similar behavior across all servers.

		req = new ProtectedServletRequest(req, remoteUser);

		if ((userId > 0) || (remoteUser != null)) {

			// Set the principal associated with this thread

			String name = String.valueOf(userId);

			if (remoteUser != null) {
				name = remoteUser;
			}

			PrincipalThreadLocal.setName(name);
		}

		if ((userId <= 0) && (remoteUser != null)) {
			try {

				// User id

				userId = GetterUtil.getLong(remoteUser);

				// Pre login events

				EventsProcessor.process(PropsValues.LOGIN_EVENTS_PRE, req, res);

				// User

				User user = UserLocalServiceUtil.getUserById(userId);

				UserLocalServiceUtil.updateLastLogin(
					userId, req.getRemoteAddr());

				// User id

				ses.setAttribute(WebKeys.USER_ID, new Long(userId));

				// User locale

				ses.setAttribute(Globals.LOCALE_KEY, user.getLocale());

				// Post login events

				EventsProcessor.process(
					PropsValues.LOGIN_EVENTS_POST, req, res);
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}

		// Process pre service events

		try {
			EventsProcessor.process(
				PropsValues.SERVLET_SERVICE_EVENTS_PRE, req, res);
		}
		catch (Exception e) {
			_log.error(e, e);

			req.setAttribute(PageContext.EXCEPTION, e);

			StrutsUtil.forward(
				PropsValues.SERVLET_SERVICE_EVENTS_PRE_ERROR_PAGE, ctx, req,
				res);
		}

		try {

			// Struts service

			callParentService(req, res);
		}
		finally {

			// Process post service events

			try {
				EventsProcessor.process(
					PropsValues.SERVLET_SERVICE_EVENTS_POST, req, res);
			}
			catch (Exception e) {
				_log.error(e, e);
			}

			res.addHeader(
				_LIFERAY_PORTAL_REQUEST_HEADER, ReleaseInfo.getReleaseInfo());

			// Clear the company id associated with this thread

			CompanyThreadLocal.setCompanyId(0);

			// Clear the principal associated with this thread

			PrincipalThreadLocal.setName(null);
		}
	}

	public void destroy() {
		try {
			Iterator itr = PortletLocalServiceUtil.getPortlets().iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				PortletInstanceFactory.destroy(portlet);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		long[] companyIds = PortalInstances.getCompanyIds();

		for (int i = 0; i < companyIds.length; i++) {
			destroyCompany(companyIds[i]);
		}

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.GLOBAL_SHUTDOWN_EVENTS), true);
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		super.destroy();
	}

	protected void checkWebSettings(String xml) throws DocumentException {
		Document doc = PortalUtil.readDocumentFromXML(xml);

		Element root = doc.getRootElement();

		int timeout = PropsValues.SESSION_TIMEOUT;

		Element sessionConfig = root.element("session-config");

		if (sessionConfig != null) {
			String sessionTimeout =
				sessionConfig.elementText("session-timeout");

			timeout = GetterUtil.getInteger(sessionTimeout, timeout);
		}

		PropsUtil.set(PropsUtil.SESSION_TIMEOUT, String.valueOf(timeout));

		PropsValues.SESSION_TIMEOUT = timeout;
	}

	protected void destroyCompany(long companyId) {
		if (_log.isDebugEnabled()) {
			_log.debug("Process shutdown events");
		}

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.APPLICATION_SHUTDOWN_EVENTS),
				new String[] {String.valueOf(companyId)});
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private static final String _LIFERAY_PORTAL_REQUEST_HEADER =
		"Liferay-Portal";

	private static Log _log = LogFactory.getLog(MainServlet.class);

	private Set _lastModifiedPaths;

}