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

package com.liferay.taglib.portletext;

import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Layout;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletPreferencesFactoryUtil;
import com.liferay.portlet.layoutconfiguration.util.RuntimePortletUtil;

import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.ServletContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.JspException;
import javax.servlet.jsp.PageContext;
import javax.servlet.jsp.tagext.TagSupport;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="RuntimeTag.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RuntimeTag extends TagSupport {

	public static void doTag(
			String portletName, PageContext pageContext, ServletContext ctx,
			HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		doTag(portletName, null, pageContext, ctx, req, res);
	}

	public static void doTag(
			String portletName, String queryString, PageContext pageContext,
			ServletContext ctx, HttpServletRequest req, HttpServletResponse res)
		throws Exception {

		doTag(portletName, null, null, pageContext, ctx, req, res);
	}

	public static void doTag(
			String portletName, String queryString, String defaultPreferences,
			PageContext pageContext, ServletContext ctx, HttpServletRequest req,
			HttpServletResponse res)
		throws Exception {

		PortletRequest portletRequest = (PortletRequest)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_REQUEST);

		RenderRequest renderRequest = null;

		if ((portletRequest != null) &&
			(portletRequest instanceof RenderRequest)) {

			renderRequest = (RenderRequest)portletRequest;
		}

		PortletResponse portletResponse = (PortletResponse)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_RESPONSE);

		RenderResponse renderResponse = null;

		if ((portletResponse != null) &&
			(portletResponse instanceof RenderResponse)) {

			renderResponse = (RenderResponse)portletResponse;
		}

		String portletId = portletName;

		StringMaker renderPortletSM = new StringMaker();

		try {
			req.setAttribute(WebKeys.RENDER_PORTLET_RESOURCE, Boolean.TRUE);

			if (Validator.isNotNull(defaultPreferences)) {
				PortletPreferencesFactoryUtil.getPortletSetup(
					req, portletId, true, true, defaultPreferences);
			}

			RuntimePortletUtil.processPortlet(
				renderPortletSM, ctx, req, res, renderRequest, renderResponse,
				portletId, queryString);
		}
		finally {
			req.removeAttribute(WebKeys.RENDER_PORTLET_RESOURCE);
		}

		if (pageContext != null) {
			pageContext.getOut().print(renderPortletSM.toString());
		}
		else {

			// LEP-1023

			//res.getOutputStream().print(renderPortletSM.toString());
			res.getWriter().print(renderPortletSM.toString());
		}
	}

	public int doEndTag() throws JspException {
		try {
			HttpServletRequest req =
				(HttpServletRequest)pageContext.getRequest();

			Layout layout = (Layout)req.getAttribute(WebKeys.LAYOUT);

			if (layout == null) {
				return EVAL_PAGE;
			}

			ServletContext ctx = (ServletContext)req.getAttribute(WebKeys.CTX);

			HttpServletResponse res =
				(HttpServletResponse)pageContext.getResponse();

			doTag(
				_portletName, _queryString, _defaultPreferences, pageContext,
				ctx, req, res);

			return EVAL_PAGE;
		}
		catch (Exception e) {
			_log.error(e, e);

			throw new JspException(e);
		}
	}

	public void setPortletName(String portletName) {
		_portletName = portletName;
	}

	public void setQueryString(String queryString) {
		_queryString = queryString;
	}

	public void setDefaultPreferences(String defaultPreferences) {
		_defaultPreferences = defaultPreferences;
	}

	private static Log _log = LogFactory.getLog(RuntimeTag.class);

	private String _portletName;
	private String _queryString;
	private String _defaultPreferences;

}