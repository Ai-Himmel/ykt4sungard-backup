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

package com.liferay.portal.servlet;

import java.io.IOException;
import java.io.StringReader;
import java.util.Enumeration;
import java.util.Iterator;
import java.util.Map;
import java.util.TreeMap;

import javax.servlet.ServletContext;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.jsp.PageContext;

import org.apache.commons.fileupload.FileUploadException;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.Globals;
import org.apache.struts.action.ActionServlet;
import org.apache.struts.tiles.TilesUtilImpl;
import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;
import org.quartz.ObjectAlreadyExistsException;

import com.httpbridge.webproxy.http.TaskController;
import com.liferay.portal.auth.PrincipalFinder;
import com.liferay.portal.auth.PrincipalThreadLocal;
import com.liferay.portal.events.EventsProcessor;
import com.liferay.portal.events.StartupAction;
import com.liferay.portal.job.JobScheduler;
import com.liferay.portal.job.Scheduler;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.CompanyLocalServiceUtil;
import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.service.spring.ThemeServiceUtil;
import com.liferay.portal.service.spring.UserServiceUtil;
import com.liferay.portal.struts.MultiMessageResources;
import com.liferay.portal.struts.PortletRequestProcessor;
import com.liferay.portal.struts.StrutsUtil;
import com.liferay.portal.util.CompanyPropsUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.EntityResolver;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.ShutdownUtil;
import com.liferay.portal.util.WebAppPool;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletInstanceFactory;
import com.liferay.portlet.admin.service.spring.AdminConfigServiceUtil;
import com.liferay.portlet.calendar.service.spring.CalEventLocalServiceUtil;
import com.liferay.portlet.chat.servlet.ChatServlet;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.InstancePool;
import com.liferay.util.ParamUtil;
import com.liferay.util.ServerDetector;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;
import com.liferay.util.servlet.EncryptedServletRequest;
import com.liferay.util.servlet.ProtectedServletRequest;
import com.liferay.util.servlet.UploadServletRequest;

/**
 * <a href="MainServlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Jorge Ferrer
 * @author  Brian Myunghun Kim
 * @version $Revision: 1.60 $
 *
 */
public class MainServlet extends ActionServlet {

	public void init() throws ServletException {
		synchronized (MainServlet.class) {

			// Initialize

			super.init();

			try {
				EventsProcessor.process(
					new String[] {
						StartupAction.class.getName()
					},
					true);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Company id

			ServletContext ctx = getServletContext();

			_companyId = ctx.getInitParameter("company_id");

			ctx.setAttribute(WebKeys.COMPANY_ID, _companyId);

			// Paths

			String rootPath = GetterUtil.getString(
				ctx.getInitParameter("root_path"), StringPool.SLASH);
			if (rootPath.equals(StringPool.SLASH)) {
				rootPath = StringPool.BLANK;
			}

			ctx.setAttribute(WebKeys.ROOT_PATH, rootPath);
			ctx.setAttribute(WebKeys.MAIN_PATH, rootPath + "/c");
			ctx.setAttribute(WebKeys.CAPTCHA_PATH, rootPath + "/captcha");

			String friendlyURLPath = rootPath + PropsUtil.get(
				PropsUtil.LAYOUT_FRIENDLY_URL_SERVLET_MAPPING);

			ctx.setAttribute(WebKeys.FRIENDLY_URL_PATH, friendlyURLPath);
			ctx.setAttribute(WebKeys.IMAGE_PATH, rootPath + "/image");

			// Initialize portlets

			try {
				String[] xmls = new String[] {
					Http.URLtoString(ctx.getResource("/WEB-INF/portlet.xml")),
					Http.URLtoString(ctx.getResource(
						"/WEB-INF/portlet-ext.xml")),
					Http.URLtoString(ctx.getResource(
						"/WEB-INF/liferay-portlet.xml")),
					Http.URLtoString(ctx.getResource(
						"/WEB-INF/liferay-portlet-ext.xml"))
				};

				PortletServiceUtil.initEAR(xmls);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Initialize portlets display

			try {
				String xml = Http.URLtoString(ctx.getResource(
					"/WEB-INF/liferay-display.xml"));

				Map oldCategories = (Map)WebAppPool.get(
					_companyId, WebKeys.PORTLET_CATEGORIES);

				Map newCategories = PortletServiceUtil.getEARDisplay(xml);

				Map mergedCategories =
					PortalUtil.mergeCategories(oldCategories, newCategories);

				WebAppPool.put(
					_companyId, WebKeys.PORTLET_CATEGORIES, mergedCategories);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Initialize color schemes

			try {
				String[] xmls = new String[] {
					Http.URLtoString(ctx.getResource(
						"/WEB-INF/liferay-look-and-feel.xml")),
					Http.URLtoString(ctx.getResource(
						"/WEB-INF/liferay-look-and-feel-ext.xml"))
				};

				ThemeServiceUtil.init(xmls);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Check company

			try {
				CompanyLocalServiceUtil.checkCompany(_companyId);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Check system events

			if (GetterUtil.get(PropsUtil.get(
					PropsUtil.CALENDAR_SYNC_EVENTS_ON_STARTUP), false)) {

				try {
					CalEventLocalServiceUtil.checkSystemEvents(_companyId);
				}
				catch (Exception e) {
					e.printStackTrace();
				}
			}

			// Check web settings

			try {
				String xml = Http.URLtoString(ctx.getResource(
					"/WEB-INF/web.xml"));

				_checkWebSettings(xml);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Scheduler

			try {
				Iterator itr =
					PortletServiceUtil.getPortlets(_companyId).iterator();

				while (itr.hasNext()) {
					Portlet portlet = (Portlet)itr.next();

					String className = portlet.getSchedulerClass();

					if (portlet.isActive() && className != null) {
						Scheduler scheduler =
							(Scheduler)InstancePool.get(className);

						scheduler.schedule();
					}
				}
			}
			catch (ObjectAlreadyExistsException oaee) {
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Message Resources

			MultiMessageResources messageResources =
				(MultiMessageResources)ctx.getAttribute(Globals.MESSAGES_KEY);

			messageResources.setServletContext(ctx);

			WebAppPool.put(_companyId, Globals.MESSAGES_KEY, messageResources);

			// Current users

			WebAppPool.put(_companyId, WebKeys.CURRENT_USERS, new TreeMap());

			// HttpBridge

			TaskController.bridgeUserServicePath = "/httpbridge/home";
			TaskController.bridgeHttpServicePath = "/httpbridge/http";
			TaskController.bridgeGotoTag = "(goto)";
			TaskController.bridgeThenTag = "(then)";
			TaskController.bridgePostTag = "(post)";

			// Call a service that utilizes Castor to ensure it is compatible
			// and configured to work with the current application server

			try {
				AdminConfigServiceUtil.getJournalConfig(
					_companyId, PortletKeys.JOURNAL);
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			// Process startup events

			try {
				EventsProcessor.process(PropsUtil.getArray(
					PropsUtil.GLOBAL_STARTUP_EVENTS), true);

				EventsProcessor.process(PropsUtil.getArray(
					PropsUtil.APPLICATION_STARTUP_EVENTS),
					new String[] {_companyId});
			}
			catch (Exception e) {
				e.printStackTrace();
			}

			PortalInstances.init(_companyId);
		}
	}

	public void callParentService(
			HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {

		super.service(req, res);
	}

	public void service(HttpServletRequest req, HttpServletResponse res)
		throws IOException, ServletException {
		if (!PortalInstances.matches()) {
			res.setContentType(Constants.TEXT_HTML);

			String html = ContentUtil.get("content/en_US/init.html");

			res.getOutputStream().print(html);

			return;
		}

		if (ShutdownUtil.isShutdown()) {
			res.setContentType(Constants.TEXT_HTML);

			String html = ContentUtil.get("content/en_US/shutdown.html");

			res.getOutputStream().print(html);

			return;
		}

		HttpSession ses = req.getSession();
        System.out.println("MainServlet.class -- session getId() is " + ses.getId());
        System.out.println("MainServlet.class -- session.getAttribute()  stuempno is " + ses.getAttribute("stuempno"));
		// Test CAS auto login

		/*ses.setAttribute(
			com.liferay.portal.auth.CASAutoLogin.CAS_FILTER_USER,
			"liferay.com.1");*/

		// CTX

		ServletContext ctx = getServletContext();
		ServletContext portalCtx = ctx.getContext(
			CompanyPropsUtil.get(_companyId, PropsUtil.PORTAL_CTX));
		if (portalCtx == null) {
			portalCtx = ctx;
		}

		req.setAttribute(WebKeys.CTX, portalCtx);

		// WebKeys.COMPANY_ID variable

		String companyId = (String)ctx.getAttribute(WebKeys.COMPANY_ID);

		if (portalCtx.getAttribute(WebKeys.COMPANY_ID) == null) {
			portalCtx.setAttribute(WebKeys.COMPANY_ID, companyId);
		}

		if (ses.getAttribute(WebKeys.COMPANY_ID) == null) {
			ses.setAttribute(WebKeys.COMPANY_ID, companyId);
		}

		req.setAttribute(WebKeys.COMPANY_ID, companyId);

		// ROOT_PATH variable

		String rootPath = (String)ctx.getAttribute(WebKeys.ROOT_PATH);

		if (portalCtx.getAttribute(WebKeys.ROOT_PATH) == null) {
			portalCtx.setAttribute(WebKeys.ROOT_PATH, rootPath);
		}

		if (ses.getAttribute(WebKeys.ROOT_PATH) == null) {
			ses.setAttribute(WebKeys.ROOT_PATH, rootPath);
		}

		req.setAttribute(WebKeys.ROOT_PATH, rootPath);

		// MAIN_PATH variable

		String mainPath = (String)ctx.getAttribute(WebKeys.MAIN_PATH);

		if (portalCtx.getAttribute(WebKeys.MAIN_PATH) == null) {
			portalCtx.setAttribute(WebKeys.MAIN_PATH, mainPath);
		}

		if (ses.getAttribute(WebKeys.MAIN_PATH) == null) {
			ses.setAttribute(WebKeys.MAIN_PATH, mainPath);
		}

		req.setAttribute(WebKeys.MAIN_PATH, mainPath);

		// CAPTCHA_PATH variable

		String captchaPath = (String)ctx.getAttribute(WebKeys.CAPTCHA_PATH);

		if (portalCtx.getAttribute(WebKeys.CAPTCHA_PATH) == null) {
			portalCtx.setAttribute(WebKeys.CAPTCHA_PATH, captchaPath);
		}

		if (ses.getAttribute(WebKeys.CAPTCHA_PATH) == null) {
			ses.setAttribute(WebKeys.CAPTCHA_PATH, captchaPath);
		}

		req.setAttribute(WebKeys.CAPTCHA_PATH, captchaPath);

		// FRIENDLY_URL_PATH variable

		String friendlyURLPath =
			(String)ctx.getAttribute(WebKeys.FRIENDLY_URL_PATH);

		if (portalCtx.getAttribute(WebKeys.FRIENDLY_URL_PATH) == null) {
			portalCtx.setAttribute(WebKeys.FRIENDLY_URL_PATH, friendlyURLPath);
		}

		if (ses.getAttribute(WebKeys.FRIENDLY_URL_PATH) == null) {
			ses.setAttribute(WebKeys.FRIENDLY_URL_PATH, friendlyURLPath);
		}

		req.setAttribute(WebKeys.FRIENDLY_URL_PATH, friendlyURLPath);

		// IMAGE_PATH variable

		String imagePath = (String)ctx.getAttribute(WebKeys.IMAGE_PATH);

		if (portalCtx.getAttribute(WebKeys.IMAGE_PATH) == null) {
			portalCtx.setAttribute(WebKeys.IMAGE_PATH, imagePath);
		}

		if (ses.getAttribute(WebKeys.IMAGE_PATH) == null) {
			ses.setAttribute(WebKeys.IMAGE_PATH, imagePath);
		}

		req.setAttribute(WebKeys.IMAGE_PATH, imagePath);

		// Portlet Request Processor

		PortletRequestProcessor portletReqProcessor =
			(PortletRequestProcessor)portalCtx.getAttribute(
				WebKeys.PORTLET_STRUTS_PROCESSOR);

		if (portletReqProcessor == null) {
			portletReqProcessor =
				PortletRequestProcessor.getInstance(this, getModuleConfig(req));

			portalCtx.setAttribute(
				WebKeys.PORTLET_STRUTS_PROCESSOR, portletReqProcessor);
		}

		// Tiles definitions factory

		if (portalCtx.getAttribute(TilesUtilImpl.DEFINITIONS_FACTORY) == null) {
			portalCtx.setAttribute(
				TilesUtilImpl.DEFINITIONS_FACTORY,
				ctx.getAttribute(TilesUtilImpl.DEFINITIONS_FACTORY));
		}

		// JSF

		ClassLoader classLoader = (ClassLoader)ctx.getAttribute(
			WebKeys.FACES_CLASS_LOADER);

		if (portalCtx.getAttribute(WebKeys.FACES_CLASS_LOADER) == null) {
			portalCtx.setAttribute(WebKeys.FACES_CLASS_LOADER, classLoader);
		}

		Object applicationAssociate = ctx.getAttribute(WebKeys.ASSOCIATE_KEY);

		if (portalCtx.getAttribute(WebKeys.ASSOCIATE_KEY) == null) {
			portalCtx.setAttribute(WebKeys.ASSOCIATE_KEY, applicationAssociate);
		}
		
		// Set character encoding

		String strutsCharEncoding =
			PropsUtil.get(PropsUtil.STRUTS_CHAR_ENCODING);

		req.setCharacterEncoding(strutsCharEncoding);
		
		/*if (!BrowserSniffer.is_wml(req)) {
			res.setContentType(
				Constants.TEXT_HTML + "; charset=" + strutsCharEncoding);
		}*/

		// Determine content type

		String contentType = req.getHeader("Content-Type");
		if ((contentType != null) &&
			(contentType.startsWith("multipart/form-data"))) {
			try {
				req = new UploadServletRequest(req);
			} catch (FileUploadException fue) {
				if (!res.isCommitted()) {					
					res.setHeader("Connection","close");
					res.sendRedirect(Constants.TEXT_HTML_DIR + "/common/upload_warning.jsp");
				}
			}
		} else if (ParamUtil.get(req, WebKeys.ENCRYPT, false)) {
			try {
				Company company = CompanyLocalServiceUtil.getCompany(companyId);

				req = new EncryptedServletRequest(req, company.getKeyObj());
			}
			catch (Exception e) {
			}
		}

		// Current URL

		String completeURL = Http.getCompleteURL(req);

		if ((Validator.isNotNull(completeURL)) &&
			(completeURL.indexOf("j_security_check") == -1)) {

			completeURL = completeURL.substring(
				completeURL.indexOf("://") + 3, completeURL.length());

			completeURL = completeURL.substring(
				completeURL.indexOf("/"), completeURL.length());
		}

		if (Validator.isNull(completeURL)) {
			completeURL = mainPath;
		}

		req.setAttribute(WebKeys.CURRENT_URL, completeURL);

		// Chat server

		Object chatServer = ctx.getAttribute(ChatServlet.CHAT_SERVER);

		if (portalCtx.getAttribute(ChatServlet.CHAT_SERVER) == null) {
			portalCtx.setAttribute(ChatServlet.CHAT_SERVER, chatServer);
		}

		if (ses.getAttribute(ChatServlet.CHAT_SERVER) == null) {
			ses.setAttribute(ChatServlet.CHAT_SERVER, chatServer);
		}

		// Login

		String userId = PortalUtil.getUserId(req);
		String remoteUser = req.getRemoteUser();

		if ((userId != null) || (remoteUser != null)) {

			// Set the principal associated with this thread

			String name = userId;
			if (remoteUser != null) {
				name = remoteUser;
			}

			PrincipalThreadLocal.setName(name);
		}
		/*
		if ((userId != null) && (remoteUser == null)) {

			// WebSphere will not return the remote user unless you are
			// authenticated AND accessing a protected path. Other servers will
			// return the remote user for all threads associated with an
			// authenticated user.
			if (!ServerDetector.isWebSphere()) {
				req = new ProtectedServletRequest(req, userId);
			}
		}*/

		if ((userId == null) && (remoteUser != null)) {
			try {

				// User id

				userId = remoteUser;

				try {
					PrincipalFinder principalFinder =
						(PrincipalFinder)InstancePool.get(
							PropsUtil.get(PropsUtil.PRINCIPAL_FINDER));

					userId = principalFinder.toLiferay(userId);
				}
				catch (Exception e) {
				}

				// Pre login events

				EventsProcessor.process(PropsUtil.getArray(
					PropsUtil.LOGIN_EVENTS_PRE), req, res);

				// User

				User user = UserServiceUtil.getUserById(userId);

				UserServiceUtil.updateLastLogin(req.getRemoteAddr());

				// User id

				ses.setAttribute(WebKeys.USER_ID, userId);

				// User locale

				ses.setAttribute(Globals.LOCALE_KEY, user.getLocale());

				// Post login events

				EventsProcessor.process(PropsUtil.getArray(
					PropsUtil.LOGIN_EVENTS_POST), req, res);
			}
			catch (Exception e) {
				e.printStackTrace();
			}
		}

		// Process pre service events

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.SERVLET_SERVICE_EVENTS_PRE), req, res);
		}
		catch (Exception e) {
			e.printStackTrace();

			req.setAttribute(PageContext.EXCEPTION, e);

			StrutsUtil.forward(
				PropsUtil.get(
					PropsUtil.SERVLET_SERVICE_EVENTS_PRE_ERROR_PAGE),
				portalCtx, req, res);
		}

		// Struts service

		callParentService(req, res);

		// Process post service events

		try {
			EventsProcessor.process(PropsUtil.getArray(
				PropsUtil.SERVLET_SERVICE_EVENTS_POST), req, res);
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Clear the principal associated with this thread

		PrincipalThreadLocal.setName(null);
	}

	public void destroy() {

		// Destroy portlets

		try {
			Iterator itr =
				PortletServiceUtil.getPortlets(_companyId).iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				PortletInstanceFactory.destroy(portlet);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		// Scheduler

		JobScheduler.shutdown();

		// Parent

		super.destroy();
	}

	private void _checkWebSettings(String xml) throws DocumentException {
		SAXReader reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		int timeout = GetterUtil.getInteger(
			PropsUtil.get(PropsUtil.SESSION_TIMEOUT));

		Element sessionConfig = root.element("session-config");

		if (sessionConfig != null) {
			String sessionTimeout =
				sessionConfig.elementText("session-timeout");

			timeout = GetterUtil.get(
				sessionConfig.elementText("session-timeout"), timeout);
		}

		PropsUtil.set(PropsUtil.SESSION_TIMEOUT, Integer.toString(timeout));
	}

	private static final Log _log = LogFactory.getLog(MainServlet.class);

	private String _companyId;

}