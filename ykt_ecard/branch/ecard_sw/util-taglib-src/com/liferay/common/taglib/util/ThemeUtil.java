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

package com.liferay.common.taglib.util;

import com.liferay.portal.language.LanguageUtil_IW;
import com.liferay.portal.model.Theme;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil_IW;
import com.liferay.portal.util.PropsUtil_IW;
import com.liferay.portal.util.ServiceLocator;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.portlet.PortletURLFactory;
import com.liferay.util.ArrayUtil_IW;
import com.liferay.util.BrowserSniffer_IW;
import com.liferay.util.GetterUtil;
import com.liferay.util.GetterUtil_IW;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil_IW;
import com.liferay.util.lang.StaticFieldGetter;
import com.liferay.util.servlet.StringServletResponse;
import com.liferay.util.velocity.ServletResourceLoader;
import com.liferay.util.velocity.VelocityContextPool;

import java.io.StringWriter;

import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletContext;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.taglib.tiles.ComponentConstants;
import org.apache.struts.tiles.ComponentContext;
import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.Velocity;

/**
 * <a href="ThemeUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.12 $
 *
 */
public class ThemeUtil {

	public static void include(
			ServletContext ctx, ServletRequest req, ServletResponse res,
			PageContext pageContext, String page, Theme theme)
		throws Exception {

		String extension = theme.getTemplateExtension();

		if (extension.equals("vm")) {
			includeVM(ctx, req, pageContext, page, theme);
		}
		else {
			String path =
				theme.getTemplatesPath() + StringPool.SLASH + page;

			includeJSP(ctx, req, res, path, theme);
		}
	}

	protected static void includeJSP(
			ServletContext ctx, ServletRequest req, ServletResponse res,
			String path, Theme theme)
		throws Exception {

		if (theme.isWARFile()) {
			ServletContext themeCtx = ctx.getContext(
				StringPool.SLASH + theme.getServletContextName());

			if (themeCtx == null) {
				_log.error(
					"Theme " + theme.getThemeId() + " cannot find its " +
						"servlet context at " + theme.getServletContextName());
			}
			else {
				RequestDispatcher rd = themeCtx.getRequestDispatcher(path);

				if (rd == null) {
					_log.error(
						"Theme " + theme.getThemeId() + " does not have " +
							path);
				}
				else {
					rd.include(req, res);
				}
			}
		}
		else {
			RequestDispatcher rd = ctx.getRequestDispatcher(path);

			if (rd == null) {
				_log.error(
					"Theme " + theme.getThemeId() + " does not have " + path);
			}
			else {
				rd.include(req, res);
			}
		}
	}

	protected static void includeVM(
			ServletContext ctx, ServletRequest req, PageContext pageContext,
			String page, Theme theme)
		throws Exception {

		// Get template

		// The servlet context name will be null when the portal is deployed to
		// the root directory in Tomcat. See
		// com.liferay.portlet.PortletContextImpl where a null servlet context
		// name is also converted to an empty string.

		String ctxName = GetterUtil.getString(ctx.getServletContextName());

		if (VelocityContextPool.get(ctxName) == null) {

			// This should only happen if the Velocity template is the first
			// page to be accessed in the system

			VelocityContextPool.put(ctxName, ctx);
		}

		int pos = page.lastIndexOf(StringPool.PERIOD);

		String source =
			ctxName + ServletResourceLoader.CONTEXT_SEPARATOR +
				theme.getTemplatesPath() + StringPool.SLASH +
					page.substring(0, pos) + ".vm";

		if (!Velocity.resourceExists(source)) {
			_log.error(source + " does not exist");

			return;
		}

		Template template = Velocity.getTemplate(source);

		StringWriter sw = new StringWriter();

		VelocityContext vc = new VelocityContext();

		// Request

		vc.put("request", req);

		// Page context

		vc.put("pageContext", pageContext);

		// Portlet config

		PortletConfigImpl portletConfig =
			(PortletConfigImpl)req.getAttribute(WebKeys.JAVAX_PORTLET_CONFIG);

		if (portletConfig != null) {
			vc.put("portletConfig", portletConfig);
		}

		// Render request

		PortletRequest portletRequest =
			(PortletRequest)req.getAttribute(WebKeys.JAVAX_PORTLET_REQUEST);

		if (portletRequest != null) {
			if (portletRequest instanceof RenderRequest) {
				vc.put("renderRequest", portletRequest);
			}
		}

		// Render response

		PortletResponse portletResponse =
			(PortletResponse)req.getAttribute(WebKeys.JAVAX_PORTLET_RESPONSE);

		if (portletResponse != null) {
			if (portletResponse instanceof RenderResponse) {
				vc.put("renderResponse", portletResponse);
			}
		}

		// Theme display

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		if (themeDisplay != null) {
			vc.put("themeDisplay", themeDisplay);
			vc.put("company", themeDisplay.getCompany());
			vc.put("user", themeDisplay.getUser());
			vc.put("layout", themeDisplay.getLayout());
			vc.put("layouts", themeDisplay.getLayouts());
			vc.put("layoutId", themeDisplay.getLayoutId());
			vc.put("layoutTypePortlet", themeDisplay.getLayoutTypePortlet());
			vc.put("portletGroupId", themeDisplay.getPortletGroupId());
			vc.put("locale", themeDisplay.getLocale());
			vc.put("timeZone", themeDisplay.getTimeZone());
			vc.put("theme", themeDisplay.getTheme());
			vc.put("colorScheme", themeDisplay.getColorScheme());
			vc.put("portletDisplay", themeDisplay.getPortletDisplay());
		}

		// Tiles attributes

		_setTilesAttribute(pageContext, vc, "tilesTitle", "title");
		_setTilesAttribute(pageContext, vc, "tilesSubNav", "sub_nav");
		_setTilesAttribute(pageContext, vc, "tilesContent", "content");
		_setTilesAttribute(pageContext, vc, "tilesSelectable", "selectable");

		// Full templates path

		vc.put(
			"fullTemplatesPath",
			ctxName + ServletResourceLoader.CONTEXT_SEPARATOR +
				theme.getTemplatesPath());

		// liferay:include tag library

		StringServletResponse stringServletResponse = new StringServletResponse(
			(HttpServletResponse)pageContext.getResponse());

		vc.put(
			"taglibLiferay",
			new VelocityInclude(ctx, req, stringServletResponse));

		// Helper utilities

		_setHelperUtilities(vc);

		// Merge templates

		template.merge(vc, sw);

		// Print output

		pageContext.getOut().print(sw.toString());
	}

	private static void _setHelperUtilities(VelocityContext vc) {

		// Array util

		vc.put("arrayUtil", ArrayUtil_IW.getInstance());

		// Browser sniffer

		vc.put(
			"browserSniffer", BrowserSniffer_IW.getInstance());

		// Getter util

		vc.put("getterUtil", GetterUtil_IW.getInstance());

		// Language

		vc.put("languageUtil", LanguageUtil_IW.getInstance());

		// Portal util

		vc.put("portalUtil", PortalUtil_IW.getInstance());

		// Props util

		vc.put("propsUtil", PropsUtil_IW.getInstance());

		// Portlet URL factory

		vc.put("portletURLFactory", PortletURLFactory.getInstance());

		// Service locator

		vc.put("serviceLocator", ServiceLocator.getInstance());

		// Static field getter

		vc.put("staticFieldGetter", StaticFieldGetter.getInstance());

		// String util

		vc.put("stringUtil", StringUtil_IW.getInstance());
	}

	private static void _setTilesAttribute(
		PageContext pageContext, VelocityContext vc, String attributeId,
		String attributeName) {

		ComponentContext componentContext =
			(ComponentContext)pageContext.getAttribute(
				ComponentConstants.COMPONENT_CONTEXT,
				PageContext.REQUEST_SCOPE);

		if (componentContext != null) {
			Object value = componentContext.getAttribute(attributeName);

			if (value != null) {
				vc.put(attributeId, value);
			}
		}
	}

	private static final Log _log = LogFactory.getLog(ThemeUtil.class);

}