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

import com.liferay.portal.kernel.portlet.LiferayPortlet;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.struts.StrutsUtil;
import com.liferay.portal.util.PortalUtil;

import java.io.IOException;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.PortletException;
import javax.portlet.PortletRequestDispatcher;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="JSPPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JSPPortlet extends LiferayPortlet {

	public void init() throws PortletException {
		aboutJSP = getInitParameter("about-jsp");
		configJSP = getInitParameter("config-jsp");
		editJSP = getInitParameter("edit-jsp");
		editDefaultsJSP = getInitParameter("edit-defaults-jsp");
		editGuestJSP = getInitParameter("edit-guest-jsp");
		helpJSP = getInitParameter("help-jsp");
		previewJSP = getInitParameter("preview-jsp");
		printJSP = getInitParameter("print-jsp");
		viewJSP = getInitParameter("view-jsp");

		copyRequestParameters = GetterUtil.getBoolean(
			getInitParameter("copy-request-parameters"), true);
	}

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {

		if (copyRequestParameters) {
			PortalUtil.copyRequestParameters(req, res);
		}
	}

	public void doDispatch(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		String jspPage = req.getParameter("jsp_page");

		if (Validator.isNotNull(jspPage)) {
			include(jspPage, req, res);
		}
		else {
			super.doDispatch(req, res);
		}
	}

	public void doAbout(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(aboutJSP, req, res);
	}

	public void doConfig(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(configJSP, req, res);
	}

	public void doEdit(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			include(editJSP, req, res);
		}
	}

	public void doEditDefaults(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			include(editDefaultsJSP, req, res);
		}
	}

	public void doEditGuest(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			include(editGuestJSP, req, res);
		}
	}

	public void doHelp(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(helpJSP, req, res);
	}

	public void doPreview(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(previewJSP, req, res);
	}

	public void doPrint(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(printJSP, req, res);
	}

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(viewJSP, req, res);
	}

	protected void include(String path, RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		PortletRequestDispatcher prd =
			getPortletContext().getRequestDispatcher(
				StrutsUtil.TEXT_HTML_DIR + path);

		if (prd == null) {
			_log.error(path + " is not a valid include");
		}
		else {
			prd.include(req, res);
		}

		if (copyRequestParameters) {
			PortalUtil.clearRequestParameters(req);
		}
	}

	protected String aboutJSP;
	protected String configJSP;
	protected String editJSP;
	protected String editDefaultsJSP;
	protected String editGuestJSP;
	protected String helpJSP;
	protected String previewJSP;
	protected String printJSP;
	protected String viewJSP;
	protected boolean copyRequestParameters;

	private static Log _log = LogFactory.getLog(JSPPortlet.class);

}