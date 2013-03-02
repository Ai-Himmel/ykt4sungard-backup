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

package com.liferay.portlet.admin.action;

import com.liferay.portal.kernel.cache.CacheRegistry;
import com.liferay.portal.kernel.cache.MultiVMPoolUtil;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.PortalClassInvoker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.webcache.WebCachePoolUtil;
import com.liferay.portal.lastmodified.LastModifiedCSS;
import com.liferay.portal.lastmodified.LastModifiedJavaScript;
import com.liferay.portal.lucene.LuceneIndexer;
import com.liferay.portal.security.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.struts.StrutsUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalInstances;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PrefsPropsUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.ShutdownUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.Time;
import com.liferay.util.servlet.NullServletResponse;
import com.liferay.util.servlet.SessionErrors;

import java.lang.reflect.Method;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;
import javax.portlet.PortletPreferences;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.Element;

/**
 * <a href="EditServerAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class EditServerAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		PermissionChecker permissionChecker =
			themeDisplay.getPermissionChecker();

		if (!permissionChecker.isOmniadmin()) {
			SessionErrors.add(req, PrincipalException.class.getName());

			setForward(req, "portlet.admin.error");

			return;
		}

		PortletPreferences prefs = PrefsPropsUtil.getPreferences();

		String cmd = ParamUtil.getString(req, Constants.CMD);

		if (cmd.equals("addLogLevel")) {
			addLogLevel(req);
		}
		else if (cmd.equals("cacheDb")) {
			cacheDb();
		}
		else if (cmd.equals("cacheMulti")) {
			cacheMulti();
		}
		else if (cmd.equals("cacheSingle")) {
			cacheSingle();
		}
		else if (cmd.equals("gc")) {
			gc();
		}
		else if (cmd.equals("precompile")) {
			precompile(req, res);
		}
		else if (cmd.equals("reIndex")) {
			reIndex();
		}
		else if (cmd.equals("shutdown")) {
			shutdown(req);
		}
		else if (cmd.equals("threadDump")) {
			threadDump();
		}
		else if (cmd.equals("updateLogLevels")) {
			updateLogLevels(req);
		}
		else if (cmd.equals("updateOpenOffice")) {
			updateOpenOffice(req, prefs);
		}

		sendRedirect(req, res);
	}

	protected void addLogLevel(ActionRequest req) throws Exception {
		String loggerName = ParamUtil.getString(req, "loggerName");
		String priority = ParamUtil.getString(req, "priority");

		Logger logger = Logger.getLogger(loggerName);

		logger.setLevel(Level.toLevel(priority));
	}

	protected void cacheDb() throws Exception {
		CacheRegistry.clear();
	}

	protected void cacheMulti() throws Exception {
		MultiVMPoolUtil.clear();
	}

	protected void cacheSingle() throws Exception {
		LastModifiedCSS.clear();
		LastModifiedJavaScript.clear();
		WebCachePoolUtil.clear();
	}

	protected void gc() throws Exception {
		Runtime.getRuntime().gc();
	}

	protected void jvm4ThreadDump(StringBuffer sb, ThreadGroup group) {
		Thread[] threads = new Thread[group.activeCount()];

		group.enumerate(threads, false);

		for (int i = 0; i < threads.length && threads[i] != null; i++) {
			Thread thread = threads[i];

			sb.append(StringPool.QUOTE);
			sb.append(thread.getName());
			sb.append(StringPool.QUOTE);

			if (thread.getThreadGroup() != null) {
				sb.append(StringPool.SPACE);
				sb.append(StringPool.OPEN_PARENTHESIS);
				sb.append(thread.getThreadGroup().getName());
				sb.append(StringPool.CLOSE_PARENTHESIS);
			}

			sb.append(", priority=" + thread.getPriority());
			sb.append("\n");
		}

		ThreadGroup[] groups = new ThreadGroup[group.activeGroupCount()];

		group.enumerate(groups, false);

		for (int i = 0; i < groups.length && groups[i] != null; i++) {
			jvm4ThreadDump(sb, groups[i]);
		}
	}

	protected void precompile(ActionRequest req, ActionResponse res)
		throws Exception {

		Set jsps = new TreeSet();

		ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

		// Struts

		Document doc = PortalUtil.readDocumentFromStream(
			ctx.getResourceAsStream("/WEB-INF/struts-config.xml"));

		Element root = doc.getRootElement();

		Iterator itr1 = root.element("global-forwards").elements(
			"forward").iterator();

		while (itr1.hasNext()) {
			Element action = (Element)itr1.next();

			String fileName = action.attributeValue("path");

			if ((Validator.isNotNull(fileName)) &&
				(fileName.endsWith(".jsp"))) {

				jsps.add(fileName);
			}
		}

		itr1 = root.element("action-mappings").elements("action").iterator();

		while (itr1.hasNext()) {
			Element action = (Element)itr1.next();

			String fileName = action.attributeValue("forward");

			if ((Validator.isNotNull(fileName)) &&
				(fileName.endsWith(".jsp"))) {

				jsps.add(fileName);
			}
			else {
				Iterator itr2 = action.elements("forward").iterator();

				while (itr2.hasNext()) {
					Element forward = (Element)itr2.next();

					fileName = forward.attributeValue("path");

					if ((Validator.isNotNull(fileName)) &&
						(fileName.endsWith(".jsp"))) {

						jsps.add(fileName);
					}
				}
			}
		}

		// Tiles

		doc = PortalUtil.readDocumentFromStream(
			ctx.getResourceAsStream("/WEB-INF/tiles-defs.xml"));

		root = doc.getRootElement();

		itr1 = root.elements("definition").iterator();

		while (itr1.hasNext()) {
			Element definition = (Element)itr1.next();

			String fileName = definition.attributeValue("path");

			if ((Validator.isNotNull(fileName)) &&
				(fileName.endsWith(".jsp"))) {

				jsps.add(fileName);
			}
			else {
				Iterator itr2 = definition.elements("put").iterator();

				while (itr2.hasNext()) {
					Element put = (Element)itr2.next();

					fileName = put.attributeValue("value");

					if ((Validator.isNotNull(fileName)) &&
						(fileName.endsWith(".jsp"))) {

						jsps.add(fileName);
					}
				}
			}
		}

		// Precompile JSPs

		HttpServletRequest httpReq = PortalUtil.getHttpServletRequest(req);
		HttpServletResponse httpRes = new NullServletResponse(
			PortalUtil.getHttpServletResponse(res));

		itr1 = jsps.iterator();

		while (itr1.hasNext()) {
			try {
				String jsp = StrutsUtil.TEXT_HTML_DIR + itr1.next();

				RequestDispatcher rd = ctx.getRequestDispatcher(jsp);

				if (rd != null) {
					if (_log.isInfoEnabled()) {
						_log.info("Precompiling " + jsp);
					}

					rd.include(httpReq, httpRes);
				}
			}
			catch (Exception e) {
				_log.debug(e, e);
			}
		}
	}

	protected void reIndex() throws Exception {
		long[] companyIds = PortalInstances.getCompanyIds();

		for (int i = 0; i < companyIds.length; i++) {
			long companyId = companyIds[i];

			try {
				LuceneIndexer indexer = new LuceneIndexer(companyId);

				indexer.reIndex();
			}
			catch (Exception e) {
				_log.error(e, e);
			}
		}
	}

	protected void shutdown(ActionRequest req) throws Exception {
		long minutes = ParamUtil.getInteger(req, "minutes") * Time.MINUTE;
		String message = ParamUtil.getString(req, "message");

		if (minutes <= 0) {
			ShutdownUtil.cancel();
		}
		else {
			ShutdownUtil.shutdown(minutes, message);
		}
	}

	protected void threadDump() throws Exception {
		String jvm =
			System.getProperty("java.vm.name") + " " +
				System.getProperty("java.vm.version");

		StringBuffer sb = null;

		try {
			sb = new StringBuffer("Full thread dump " + jvm + "\n\n");

			Map stackTraces = (Map)PortalClassInvoker.invoke(
				Thread.class.getName(), "getAllStackTraces", false);

			Class[] nullParams = new Class[] {};
			Object[] nullArgs = new Object[] {};

			Method getId = Thread.class.getMethod("getId", nullParams);
			Method getState = Thread.class.getMethod("getState", nullParams);

			Iterator itr = stackTraces.keySet().iterator();

			while (itr.hasNext()) {
				Thread thread = (Thread)itr.next();

				StackTraceElement[] elements =
					(StackTraceElement[])stackTraces.get(thread);

				sb.append(StringPool.QUOTE);
				sb.append(thread.getName());
				sb.append(StringPool.QUOTE);

				if (thread.getThreadGroup() != null) {
					sb.append(StringPool.SPACE);
					sb.append(StringPool.OPEN_PARENTHESIS);
					sb.append(thread.getThreadGroup().getName());
					sb.append(StringPool.CLOSE_PARENTHESIS);
				}

				sb.append(", priority=" + thread.getPriority());
				sb.append(", id=" + getId.invoke(thread, nullArgs));
				sb.append(", state=" + getState.invoke(thread, nullArgs));
				sb.append("\n");

				for (int i = 0; i < elements.length; i++) {
					sb.append("\t" + elements[i] + "\n");
				}

				sb.append("\n");
			}
		}
		catch (Exception e) {
			ThreadGroup root = Thread.currentThread().getThreadGroup();

			while (root.getParent() != null) {
		    	root = root.getParent();
			}

			sb = new StringBuffer("Summarized thread dump " + jvm + "\n\n");

			jvm4ThreadDump(sb, root);
		}

		_log.info(sb.toString());
	}

	protected void updateLogLevels(ActionRequest req) throws Exception {
		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith("logLevel")) {
				String loggerName = name.substring(8, name.length());

				String priority = ParamUtil.getString(
					req, name, Level.INFO.toString());

				Logger logger = Logger.getLogger(loggerName);

				logger.setLevel(Level.toLevel(priority));
			}
		}
	}

	protected void updateOpenOffice(ActionRequest req, PortletPreferences prefs)
		throws Exception {

		boolean enabled = ParamUtil.getBoolean(req, "enabled");
		String host = ParamUtil.getString(req, "host");
		int port = ParamUtil.getInteger(req, "port");

		prefs.setValue(
			PropsUtil.OPENOFFICE_SERVER_ENABLED, String.valueOf(enabled));
		prefs.setValue(PropsUtil.OPENOFFICE_SERVER_HOST, host);
		prefs.setValue(PropsUtil.OPENOFFICE_SERVER_PORT, String.valueOf(port));

		prefs.store();
	}

	private static Log _log = LogFactory.getLog(EditServerAction.class);

}