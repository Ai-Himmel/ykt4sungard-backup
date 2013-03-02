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

import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.Validator;

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
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.21 $
 *
 */
public class JSPPortlet extends LiferayPortlet {

	public void init() throws PortletException {
		_aboutJSP = getInitParameter("about-jsp");
		_configJSP = getInitParameter("config-jsp");
		_editJSP = getInitParameter("edit-jsp");
		_editDefaultsJSP = getInitParameter("edit-defaults-jsp");
		_helpJSP = getInitParameter("help-jsp");
		_previewJSP = getInitParameter("preview-jsp");
		_printJSP = getInitParameter("print-jsp");
		_viewJSP = getInitParameter("view-jsp");

		_copyRequestParameters = GetterUtil.get(
			getInitParameter("copy-request-parameters"), true);
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

		include(_aboutJSP, req, res);
	}

	public void doConfig(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(_configJSP, req, res);
	}

	public void doEdit(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			include(_editJSP, req, res);
		}
	}

	public void doEditDefaults(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			include(_editDefaultsJSP, req, res);
		}
	}

	public void doHelp(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(_helpJSP, req, res);
	}

	public void doPreview(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(_previewJSP, req, res);
	}

	public void doPrint(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(_printJSP, req, res);
	}

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		include(_viewJSP, req, res);
	}

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {

		if (_copyRequestParameters) {
			PortalUtil.copyRequestParameters(req, res);
		}
	}

	protected void include(String path, RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		PortletRequestDispatcher prd =
			getPortletContext().getRequestDispatcher(
				Constants.TEXT_HTML_DIR + path);

		if (prd == null) {
			_log.error(path + " is not a valid include");
		}

		prd.include(req, res);

		if (_copyRequestParameters) {
			PortalUtil.clearRequestParameters(req);
		}
	}

	private static final Log _log = LogFactory.getLog(JSPPortlet.class);

	private String _aboutJSP;
	private String _configJSP;
	private String _editJSP;
	private String _editDefaultsJSP;
	private String _helpJSP;
	private String _previewJSP;
	private String _printJSP;
	private String _viewJSP;
	private boolean _copyRequestParameters;

}