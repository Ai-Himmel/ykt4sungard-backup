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

package com.liferay.portlet.admin.action;

import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.struts.PortletAction;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.EntityResolver;
import com.liferay.portal.util.OmniadminUtil;
import com.liferay.portal.util.ShutdownUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.ActionResponseImpl;
import com.liferay.util.ParamUtil;
import com.liferay.util.Time;
import com.liferay.util.Validator;
import com.liferay.util.servlet.NullServletResponse;
import com.liferay.util.servlet.SessionErrors;

import java.util.Enumeration;
import java.util.Iterator;
import java.util.Set;
import java.util.TreeSet;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletConfig;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionMapping;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ServerAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.6 $
 *
 */
public class ServerAction extends PortletAction {

	public void processAction(
			ActionMapping mapping, ActionForm form, PortletConfig config,
			ActionRequest req, ActionResponse res)
		throws Exception {

		if (!OmniadminUtil.isOmniadmin(req.getRemoteUser())) {
			SessionErrors.add(req, PrincipalException.class.getName());

			setForward(req, "portlet.admin.error");
		}
		else {
			String cmd = ParamUtil.getString(req, Constants.CMD);

			try {
				if (cmd.equals("gc")) {
					_gc();
				}
				else if (cmd.equals("precompile_jsps")) {
					_precompileJSPs(req, res);
				}
				else if (cmd.equals("shutdown")) {
					_shutdown(req);
				}
				else if (cmd.equals("log_levels")) {
					_updateLogLevels(req);
				}
			}
			catch (Exception e) {
				if (e != null &&
					e instanceof PrincipalException) {

					SessionErrors.add(req, e.getClass().getName());

					setForward(req, "portlet.admin.error");
				}
				else {
					req.setAttribute(PageContext.EXCEPTION, e);

					setForward(req, Constants.COMMON_ERROR);
				}
			}

			setForward(req, "portlet.admin.server");
		}
	}

	private void _gc() throws Exception {
		Runtime.getRuntime().gc();
	}

	private void _precompileJSPs(ActionRequest req, ActionResponse res)
		throws Exception {

		Set jsps = new TreeSet();

		ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

		// Struts

		SAXReader reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(ctx.getResource(
			"/WEB-INF/struts-config.xml"));

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

		itr1 = root.element("action-mappings").elements(
			"action").iterator();

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

		reader = new SAXReader();
		reader.setEntityResolver(new EntityResolver());

		doc = reader.read(ctx.getResource("/WEB-INF/tiles-defs.xml"));

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

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;
		ActionResponseImpl resImpl = (ActionResponseImpl)res;

		HttpServletRequest httpReq = reqImpl.getHttpServletRequest();
		HttpServletResponse httpRes = new NullServletResponse(
			(HttpServletResponse)resImpl.getHttpServletResponse());

		itr1 = jsps.iterator();

		while (itr1.hasNext()) {
			try {
				String jsp = Constants.TEXT_HTML_DIR + itr1.next();

				RequestDispatcher rd = ctx.getRequestDispatcher(jsp);

				if (rd != null) {
					_log.debug("Precompiling " + jsp);

					rd.include(httpReq, httpRes);
				}
			}
			catch (Exception ex) {
			}
		}
	}

	private void _shutdown(ActionRequest req) throws Exception {
		long minutes = ParamUtil.getInteger(
			req, "shutdown_minutes") * Time.MINUTE;
		String message = ParamUtil.getString(req, "shutdown_message");

		if (minutes <= 0) {
			ShutdownUtil.cancel();
		}
		else {
			ShutdownUtil.shutdown(minutes, message);
		}
	}

	private void _updateLogLevels(ActionRequest req) throws Exception {
		Enumeration enu = req.getParameterNames();

		while (enu.hasMoreElements()) {
			String name = (String)enu.nextElement();

			if (name.startsWith("log_level_")) {
				String loggerName = name.substring(10, name.length());

				String priority = ParamUtil.getString(
					req, name, Level.INFO.toString());

				Logger logger = Logger.getLogger(loggerName);

				logger.setLevel(Level.toLevel(priority));
			}
		}
	}

	private static final Log _log = LogFactory.getLog(ServerAction.class);

}