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

package com.liferay.portal.velocity;

import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.language.UnicodeLanguageUtil;
import com.liferay.portal.kernel.servlet.BrowserSniffer_IW;
import com.liferay.portal.kernel.servlet.ImageServletTokenUtil;
import com.liferay.portal.kernel.util.ArrayUtil;
import com.liferay.portal.kernel.util.ArrayUtil_IW;
import com.liferay.portal.kernel.util.DateUtil_IW;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.GetterUtil_IW;
import com.liferay.portal.kernel.util.JavaConstants;
import com.liferay.portal.kernel.util.ParamUtil_IW;
import com.liferay.portal.kernel.util.Randomizer_IW;
import com.liferay.portal.kernel.util.StaticFieldGetter;
import com.liferay.portal.kernel.util.StringUtil_IW;
import com.liferay.portal.kernel.util.UnicodeFormatter_IW;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.kernel.util.Validator_IW;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.Theme;
import com.liferay.portal.service.permission.AccountPermissionUtil;
import com.liferay.portal.service.permission.CommonPermissionUtil;
import com.liferay.portal.service.permission.GroupPermissionUtil;
import com.liferay.portal.service.permission.LayoutPermissionUtil;
import com.liferay.portal.service.permission.OrganizationPermissionUtil;
import com.liferay.portal.service.permission.PasswordPolicyPermissionUtil;
import com.liferay.portal.service.permission.PortalPermissionUtil;
import com.liferay.portal.service.permission.PortletPermissionUtil;
import com.liferay.portal.service.permission.RolePermissionUtil;
import com.liferay.portal.service.permission.UserGroupPermissionUtil;
import com.liferay.portal.service.permission.UserPermissionUtil;
import com.liferay.portal.theme.NavItem;
import com.liferay.portal.theme.RequestVars;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.DateFormats_IW;
import com.liferay.portal.util.PortalUtil_IW;
import com.liferay.portal.util.PrefsPropsUtil_IW;
import com.liferay.portal.util.PropsUtil_IW;
import com.liferay.portal.util.ServiceLocator;
import com.liferay.portal.util.SessionClicks_IW;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.PortletConfigImpl;
import com.liferay.portlet.PortletURLFactory;
import com.liferay.util.Html_IW;
import com.liferay.util.HttpUtil_IW;

import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import javax.servlet.http.HttpServletRequest;

import org.apache.struts.taglib.tiles.ComponentConstants;
import org.apache.struts.tiles.ComponentContext;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.tools.generic.DateTool;
import org.apache.velocity.tools.generic.EscapeTool;
import org.apache.velocity.tools.generic.IteratorTool;
import org.apache.velocity.tools.generic.ListTool;
import org.apache.velocity.tools.generic.MathTool;
import org.apache.velocity.tools.generic.NumberTool;
import org.apache.velocity.tools.generic.SortTool;

/**
 * <a href="VelocityVariables.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class VelocityVariables {

	public static void insertHelperUtilities(
		VelocityContext vc, String[] restrictedVariables) {

		// Array util

		vc.put("arrayUtil", ArrayUtil_IW.getInstance());

		// Browser sniffer

		vc.put("browserSniffer", BrowserSniffer_IW.getInstance());

		// Date formats

		vc.put("dateFormats", DateFormats_IW.getInstance());

		// Date tool

		vc.put("dateTool", new DateTool());

		// Date util

		vc.put("dateUtil", DateUtil_IW.getInstance());

		// Escape tool

		vc.put("escapeTool", new EscapeTool());

		// Getter util

		vc.put("getterUtil", GetterUtil_IW.getInstance());

		// Html util

		vc.put("htmlUtil", Html_IW.getInstance());

		// Http util

		vc.put("httpUtil", HttpUtil_IW.getInstance());

		// ImageServletToken

		vc.put("imageToken", ImageServletTokenUtil.getImageServletToken());

		// Iterator tool

		vc.put("iteratorTool", new IteratorTool());

		// Language util

		vc.put("languageUtil", LanguageUtil.getLanguage());
		vc.put("unicodeLanguageUtil", UnicodeLanguageUtil.getUnicodeLanguage());

		// List tool

		vc.put("listTool", new ListTool());

		// Math tool

		vc.put("mathTool", new MathTool());

		// Number tool

		vc.put("numberTool", new NumberTool());

		// Param util

		vc.put("paramUtil", ParamUtil_IW.getInstance());

		// Portal util

		_insertHelperUtility(
			vc, restrictedVariables, "portalUtil", PortalUtil_IW.getInstance());
		_insertHelperUtility(
			vc, restrictedVariables, "portal", PortalUtil_IW.getInstance());

		// Prefs props util

		_insertHelperUtility(
			vc, restrictedVariables, "prefsPropsUtil",
			PrefsPropsUtil_IW.getInstance());

		// Props util

		_insertHelperUtility(
			vc, restrictedVariables, "propsUtil", PropsUtil_IW.getInstance());

		// Portlet URL factory

		vc.put("portletURLFactory", PortletURLFactory.getInstance());

		// Portlet preferences

		_insertHelperUtility(
			vc, restrictedVariables, "velocityPortletPreferences",
			new VelocityPortletPreferences());

		// Randomizer

		vc.put("randomizer", Randomizer_IW.getInstance().getWrappedInstance());

		// Service locator

		_insertHelperUtility(
			vc, restrictedVariables, "serviceLocator",
			ServiceLocator.getInstance());

		// Session clicks

		_insertHelperUtility(
			vc, restrictedVariables, "sessionClicks",
			SessionClicks_IW.getInstance());

		// Sort tool

		vc.put("sortTool", new SortTool());

		// Static field getter

		vc.put("staticFieldGetter", StaticFieldGetter.getInstance());

		// String util

		vc.put("stringUtil", StringUtil_IW.getInstance());

		// Unicode formatter

		vc.put("unicodeFormatter", UnicodeFormatter_IW.getInstance());

		// Validator

		vc.put("validator", Validator_IW.getInstance());

		// Permissions

		vc.put(
			"accountPermission", AccountPermissionUtil.getAccountPermission());
		vc.put("commonPermission", CommonPermissionUtil.getCommonPermission());
		vc.put("groupPermission", GroupPermissionUtil.getGroupPermission());
		vc.put("layoutPermission", LayoutPermissionUtil.getLayoutPermission());
		vc.put(
			"organizationPermission",
			OrganizationPermissionUtil.getOrganizationPermission());
		vc.put(
			"passwordPolicyPermission",
			PasswordPolicyPermissionUtil.getPasswordPolicyPermission());
		vc.put("portalPermission", PortalPermissionUtil.getPortalPermission());
		vc.put(
			"portletPermission", PortletPermissionUtil.getPortletPermission());
		vc.put("rolePermission", RolePermissionUtil.getRolePermission());
		vc.put(
			"userGroupPermission",
			UserGroupPermissionUtil.getUserGroupPermission());
		vc.put("userPermission", UserPermissionUtil.getUserPermission());

		// Deprecated permissions

		vc.put(
			"locationPermission",
			OrganizationPermissionUtil.getOrganizationPermission());
	}

	public static void insertVariables(
		VelocityContext vc, HttpServletRequest req) {

		// Request

		vc.put("request", req);

		// Portlet config

		PortletConfigImpl portletConfig = (PortletConfigImpl)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_CONFIG);

		if (portletConfig != null) {
			vc.put("portletConfig", portletConfig);
		}

		// Render request

		PortletRequest portletRequest = (PortletRequest)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_REQUEST);

		if (portletRequest != null) {
			if (portletRequest instanceof RenderRequest) {
				vc.put("renderRequest", portletRequest);
			}
		}

		// Render response

		PortletResponse portletResponse = (PortletResponse)req.getAttribute(
			JavaConstants.JAVAX_PORTLET_RESPONSE);

		if (portletResponse != null) {
			if (portletResponse instanceof RenderResponse) {
				vc.put("renderResponse", portletResponse);
			}
		}

		// Theme display

		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		if (themeDisplay != null) {
			Theme theme = themeDisplay.getTheme();

			Layout layout = themeDisplay.getLayout();
			List layouts = themeDisplay.getLayouts();

			vc.put("themeDisplay", themeDisplay);
			vc.put("company", themeDisplay.getCompany());
			vc.put("user", themeDisplay.getUser());
			vc.put("realUser", themeDisplay.getRealUser());
			vc.put("layout", layout);
			vc.put("layouts", layouts);
			vc.put("plid", String.valueOf(themeDisplay.getPlid()));
			vc.put("layoutTypePortlet", themeDisplay.getLayoutTypePortlet());
			vc.put(
				"portletGroupId", new Long(themeDisplay.getPortletGroupId()));
			vc.put("permissionChecker", themeDisplay.getPermissionChecker());
			vc.put("locale", themeDisplay.getLocale());
			vc.put("timeZone", themeDisplay.getTimeZone());
			vc.put("theme", theme);
			vc.put("colorScheme", themeDisplay.getColorScheme());
			vc.put("portletDisplay", themeDisplay.getPortletDisplay());

			// Navigation items

			if (layout != null) {
				RequestVars requestVars = new RequestVars(
					req, themeDisplay, layout.getAncestorPlid(),
					layout.getAncestorLayoutId());

				List navItems = NavItem.fromLayouts(requestVars, layouts);

				vc.put("navItems", navItems);
			}

			// Full css and templates path

			String ctxName = GetterUtil.getString(
				theme.getServletContextName());

			vc.put(
				"fullCssPath",
				ctxName + theme.getVelocityResourceListener() +
					theme.getCssPath());

			vc.put(
				"fullTemplatesPath",
				ctxName + theme.getVelocityResourceListener() +
					theme.getTemplatesPath());

			// Init

			vc.put(
				"init",
				themeDisplay.getPathContext() +
					VelocityResourceListener.SERVLET_SEPARATOR +
						"/html/themes/_unstyled/templates/init.vm");
		}

		// Tiles attributes

		String tilesTitle = _insertTilesVariables(
			vc, req, "tilesTitle", "title");
		String tilesContent = _insertTilesVariables(
			vc, req, "tilesContent", "content");
		boolean tilesSelectable = GetterUtil.getBoolean(_insertTilesVariables(
			vc, req, "tilesSelectable", "selectable"));

		if (themeDisplay != null) {
			themeDisplay.setTilesTitle(tilesTitle);
			themeDisplay.setTilesContent(tilesContent);
			themeDisplay.setTilesSelectable(tilesSelectable);
		}

		// Page title and subtitle

		vc.put("pageTitle", req.getAttribute(WebKeys.PAGE_TITLE));
		vc.put("pageSubtitle", req.getAttribute(WebKeys.PAGE_SUBTITLE));

		// Helper utilities

		insertHelperUtilities(vc, null);

		// Insert custom vm variables

		Map vmVariables = (Map)req.getAttribute(WebKeys.VM_VARIABLES);

		if (vmVariables != null) {
			Iterator itr = vmVariables.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				String key = (String)entry.getKey();
				Object value = entry.getValue();

				if (Validator.isNotNull(key)) {
					vc.put(key, value);
				}
			}
		}
	}

	private static void _insertHelperUtility(
		VelocityContext vc, String[] restrictedVariables, String key,
		Object value) {

		if (!ArrayUtil.contains(restrictedVariables, key)) {
			vc.put(key, value);
		}
	}

	private static String _insertTilesVariables(
		VelocityContext vc, HttpServletRequest req, String attributeId,
		String attributeName) {

		ComponentContext componentContext = (ComponentContext)req.getAttribute(
			ComponentConstants.COMPONENT_CONTEXT);

		String value = null;

		if (componentContext != null) {
			value = (String)componentContext.getAttribute(attributeName);

			if (value != null) {
				vc.put(attributeId, value);
			}
		}

		return value;
	}

}