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

package com.liferay.portal.servlet.taglib.portlet;

import com.liferay.portal.kernel.portlet.LiferayPortletURL;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.portlet.RenderResponseImpl;
import com.liferay.util.MapUtil;

import java.util.Map;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ActionURLTagUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionURLTagUtil {

	public static String doEndTag(
			boolean action, String windowState, String portletMode, String var,
			String varImpl, Boolean secure, String portletName, Boolean anchor,
			Boolean encrypt, long doAsUserId, Boolean portletConfiguration,
			Map params, boolean writeOutput, PageContext pageContext)
		throws JspException {

		try {
			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			if (portletName == null) {
				PortletConfigImpl portletConfig =
					(PortletConfigImpl)req.getAttribute(
						JavaConstants.JAVAX_PORTLET_CONFIG);

				portletName = portletConfig.getPortletId();
			}

			RenderResponseImpl renderResponse =
				(RenderResponseImpl)req.getAttribute(
					JavaConstants.JAVAX_PORTLET_RESPONSE);

			if (renderResponse == null) {
				_log.error(
					"Render response is null because this tag is not being " +
						"called within the context of a portlet");

				return StringPool.BLANK;
			}

			LiferayPortletURL portletURL = null;

			if (action) {
				portletURL = (LiferayPortletURL)renderResponse.createActionURL(
					portletName);
			}
			else {
				portletURL = (LiferayPortletURL)renderResponse.createRenderURL(
					portletName);
			}

			if (Validator.isNotNull(windowState)) {
				portletURL.setWindowState(new WindowState(windowState));
			}

			if (Validator.isNotNull(portletMode)) {
				portletURL.setPortletMode(new PortletMode(portletMode));
			}

			if (secure != null) {
				portletURL.setSecure(secure.booleanValue());
			}
			else {
				portletURL.setSecure(req.isSecure());
			}

			if (anchor != null) {
				portletURL.setAnchor(anchor.booleanValue());
			}

			if (encrypt != null) {
				portletURL.setEncrypt(encrypt.booleanValue());
			}

			if (doAsUserId > 0) {
				portletURL.setDoAsUserId(doAsUserId);
			}

			if ((portletConfiguration != null) &&
				portletConfiguration.booleanValue()) {

				String returnToFullPageURL = ParamUtil.getString(
					req, "returnToFullPageURL");
				String portletResource = ParamUtil.getString(
					req, "portletResource");
				String previewWidth = ParamUtil.getString(req, "previewWidth");

				portletURL.setParameter(
					"struts_action",
					"/portlet_configuration/edit_configuration");
				portletURL.setParameter(
					"returnToFullPageURL", returnToFullPageURL);
				portletURL.setParameter("portletResource", portletResource);
				portletURL.setParameter("previewWidth", previewWidth);
			}

			if (params != null) {
				MapUtil.merge(portletURL.getParameterMap(), params);

				portletURL.setParameters(params);
			}

			if (Validator.isNotNull(var)) {
				pageContext.setAttribute(var, portletURL.toString());
			}
			else if (Validator.isNotNull(varImpl)) {
				pageContext.setAttribute(varImpl, portletURL);
			}
			else if (writeOutput) {
				pageContext.getOut().print(portletURL.toString());
			}

			return portletURL.toString();
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new JspException(e);
		}
	}

	private static Log _log = LogFactory.getLog(ActionURLTagUtil.class);

}