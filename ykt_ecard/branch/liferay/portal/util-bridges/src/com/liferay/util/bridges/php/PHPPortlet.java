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

package com.liferay.util.bridges.php;

import com.liferay.portal.kernel.servlet.PortletServlet;
import com.liferay.portal.kernel.servlet.StringServletResponse;
import com.liferay.util.servlet.DynamicServletConfig;

import java.io.IOException;
import java.io.PrintWriter;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.GenericPortlet;
import javax.portlet.PortletException;
import javax.portlet.PortletURL;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletConfig;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.portals.bridges.common.ScriptPostProcess;

/**
 * <a href="PHPPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Jorge Ferrer
 *
 */
public class PHPPortlet extends GenericPortlet {

	public static final String PHP_URI_PARAM = "phpURI";

	public void init() throws PortletException {
		editUri = getInitParameter("edit-uri");
		helpUri = getInitParameter("help-uri");
		viewUri = getInitParameter("view-uri");
	}

	public void doDispatch(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		String phpUri = req.getParameter(PHP_URI_PARAM);

		if (phpUri != null) {
			processPHP(phpUri, req, res);
		}
		else {
			super.doDispatch(req, res);
		}
	}

	public void doEdit(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			processPHP(editUri, req, res);
		}
	}

	public void doHelp(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		processPHP(helpUri, req, res);
	}

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		processPHP(viewUri, req, res);
	}

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {

		String phpURI = req.getParameter(PHP_URI_PARAM);

		if (phpURI != null) {
			res.setRenderParameter(PHP_URI_PARAM, phpURI);
		}
	}

	public void destroy() {
		if (quercusServlet != null) {
			quercusServlet.destroy();
		}
	}

	protected synchronized void initQuercus(ServletConfig config)
		throws PortletException {

		if (quercusServlet == null) {
			try {
				quercusServlet = (HttpServlet)Class.forName(
					_QUERCUS_SERVLET).newInstance();

				Map params = new HashMap();

				Enumeration enu = config.getInitParameterNames();

				while (enu.hasMoreElements()) {
					String name = (String)enu.nextElement();

					if (!name.equals("portlet-class")) {
						params.put(name, config.getInitParameter(name));
					}
				}

				config = new DynamicServletConfig(config, params);

				quercusServlet.init(config);
			}
			catch (Exception e) {
				throw new PortletException(e);
			}
		}
	}

	protected void processPHP(
			String phpURI, RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		try {
			ServletConfig config = (ServletConfig)req.getAttribute(
				PortletServlet.PORTLET_SERVLET_CONFIG);

			initQuercus(config);

			HttpServletRequest httpReq = (HttpServletRequest)req.getAttribute(
				PortletServlet.PORTLET_SERVLET_REQUEST);
			HttpServletResponse httpRes = (HttpServletResponse)req.getAttribute(
				PortletServlet.PORTLET_SERVLET_RESPONSE);

			PHPServletRequest phpReq = new PHPServletRequest(
				httpReq, config, req, res, getPortletConfig(), phpURI);

			StringServletResponse phpRes = new StringServletResponse(httpRes);

			quercusServlet.service(phpReq, phpRes);

			String result = phpRes.getString();

			if (phpRes.getContentType().startsWith("text/")) {
				result = rewriteURLs(result, res.createRenderURL());
			}

			PrintWriter writer = httpRes.getWriter();

			writer.write(result.toCharArray());
		}
		catch (Exception e) {
			_log.error("Error processing PHP", e);
		}
	}

	protected String rewriteURLs(String page, PortletURL portletURL) {
		ScriptPostProcess processor = new ScriptPostProcess();

		processor.setInitalPage(new StringBuffer(page));
		processor.postProcessPage(portletURL, PHP_URI_PARAM);

		return processor.getFinalizedPage();
	}

	private static final String _QUERCUS_SERVLET =
		"com.caucho.quercus.servlet.QuercusServlet";

	private static Log _log = LogFactory.getLog(PHPPortlet.class);

	protected String editUri;
	protected String helpUri;
	protected String viewUri;
	protected HttpServlet quercusServlet;

}