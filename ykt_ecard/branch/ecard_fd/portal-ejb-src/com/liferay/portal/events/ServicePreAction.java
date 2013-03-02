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

package com.liferay.portal.events;

import com.liferay.portal.NoSuchLayoutException;
import com.liferay.portal.NoSuchUserException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.language.LanguageUtil;
import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.LayoutPK;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.GroupServiceUtil;
import com.liferay.portal.service.spring.LayoutServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.struts.Action;
import com.liferay.portal.struts.ActionException;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.theme.ThemeDisplayFactory;
import com.liferay.portal.util.CompanyPropsUtil;
import com.liferay.portal.util.CookieKeys;
import com.liferay.portal.util.ImageKey;
import com.liferay.portal.util.LayoutClonePool;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.Resolution;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.LiferayWindowState;
import com.liferay.portlet.PortletURLImpl;
import com.liferay.util.CookieUtil;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.ListUtil;
import com.liferay.util.LocaleUtil;
import com.liferay.util.ParamUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import javax.portlet.PortletMode;
import javax.portlet.PortletURL;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.struts.Globals;

/**
 * <a href="ServicePreAction.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Felix Ventero
 * @version $Revision: 1.45 $
 *
 */
public class ServicePreAction extends Action {

	public void run(HttpServletRequest req, HttpServletResponse res)
		throws ActionException {

		try {
			HttpSession ses = req.getSession();
			
			// Company

			Company company = PortalUtil.getCompany(req);

			String companyId = company.getCompanyId();

			// Paths

			String contextPath = CompanyPropsUtil.get(
				companyId, PropsUtil.PORTAL_CTX);
			if (contextPath.equals(StringPool.SLASH)) {
				contextPath = StringPool.BLANK;
			}

			String rootPath = (String)req.getAttribute(WebKeys.ROOT_PATH);
			String mainPath = (String)req.getAttribute(WebKeys.MAIN_PATH);
			String captchaPath = (String)req.getAttribute(WebKeys.CAPTCHA_PATH);
			String friendlyURLPath =
				(String)req.getAttribute(WebKeys.FRIENDLY_URL_PATH);
			String imagePath = (String)req.getAttribute(WebKeys.IMAGE_PATH);

			// Company logo

			String companyLogo = StringPool.BLANK;

			if (true) {

				// For now, always set the company logo URL. This behavior may
				// change if it makes life easier for the theme designer. The
				// company logo URL would then be blank if the company has never
				// set a logo.

				companyLogo =
					imagePath + "/company_logo?img_id=" + companyId + "&key=" +
						ImageKey.get(companyId);
			}

			// User

			User user = null;

			try {
				user = PortalUtil.getUser(req);
			}
			catch (NoSuchUserException nsue) {
				return;
			}

			// Is the user signed in?

			boolean signedIn = false;

			if (user == null) {
				user = company.getDefaultUser();
			}
			else {
				signedIn = true;
			}

			// Locale

			Locale locale = (Locale)ses.getAttribute(Globals.LOCALE_KEY);

			if (locale == null) {
				if (signedIn) {
					locale = user.getLocale();
				}
				else {

					// User previously set their preferred language

					String languageId = CookieUtil.get(
						req.getCookies(), CookieKeys.GUEST_LANGUAGE_ID);

					if (Validator.isNotNull(languageId)) {
						locale = LocaleUtil.fromLanguageId(languageId);
					}

					// Get locale from the request

					if ((locale == null) &&
						GetterUtil.getBoolean(
							PropsUtil.get(PropsUtil.LOCALE_DEFAULT_REQUEST))) {

						locale = req.getLocale();
					}

					// Get locale from the default user

					if (locale == null) {
						locale = user.getLocale();
					}

					if (Validator.isNull(locale.getCountry())) {

						// Locales must contain the country code

						locale = LanguageUtil.getLocale(locale.getLanguage());
					}

					List availableLocales = ListUtil.fromArray(
						LanguageUtil.getAvailableLocales());

					if (!availableLocales.contains(locale)) {
						locale = user.getLocale();
					}
				}

				ses.setAttribute(Globals.LOCALE_KEY, locale);

				if (!GetterUtil.getBoolean(PropsUtil.get(PropsUtil.TCK_URL))) {

					// Setting a cookie will cause the TCK to lose its ability
					// to track sessions

					LanguageUtil.updateCookie(res, locale);
				}
			}

			// Time zone

			TimeZone timeZone = user.getTimeZone();

			if (timeZone == null) {
				timeZone = company.getTimeZone();
			}

			// Layouts

			Layout layout = null;
			List layouts = null;

			String layoutId = ParamUtil.getString(req, "p_l_id");

			if (Validator.isNotNull(layoutId)) {
				int pos = layoutId.indexOf(".");

				if (pos != -1) {
					String groupId = layoutId.substring(0, pos);

					try {
						layout = LayoutServiceUtil.getLayout(
							new LayoutPK(layoutId, Layout.GROUP + groupId));

						if (!isGroupLayoutViewable(user, groupId)) {
							layout = null;
						}
						else {

							// Updates to group layouts are not reflected until
							// the next time the user logs in because group
							// layouts are cached in the session

							layout = LayoutClonePool.clone(req, layout);

							layouts = GroupServiceUtil.getLayouts(
								groupId, Layout.DEFAULT_PARENT_LAYOUT_ID);
						}
					}
					catch (NoSuchLayoutException nsle) {
					}
				}
				else {
					try {
						layout = LayoutServiceUtil.getLayout(
							new LayoutPK(layoutId, user.getUserId()));

						layouts = UserLocalServiceUtil.getLayouts(
							user.getUserId(), Layout.DEFAULT_PARENT_LAYOUT_ID);
					}
					catch (NoSuchLayoutException nsle) {
					}
				}
			}

			if (layout == null) {
				if (signedIn) {
					if (user.isLayoutsRequired()) {
						layouts = UserLocalServiceUtil.getLayouts(
							user.getUserId(), Layout.DEFAULT_PARENT_LAYOUT_ID);

						if (layouts.size() > 0) {
							layout = (Layout)layouts.get(0);
						}
					}
					else {

						// Iterate through all groups and get a layout from the
						// first group that has layouts

						List groups =
							UserLocalServiceUtil.getGroups(user.getUserId());

						for (int i = 0; i < groups.size(); i++) {
							Group group = (Group)groups.get(i);
							
							List groupLayouts =
								GroupLocalServiceUtil.getLayouts(
									group.getGroupId(),
									Layout.DEFAULT_PARENT_LAYOUT_ID);
							
							if (groupLayouts.size() > 0) {
								/*Fix Group Layout Control bug
								 * Xiao Qi 2005-9-9
								 * */
								for (int k = 0 ;k < groupLayouts.size(); k++) {
									Layout tmpLayout = (Layout) groupLayouts.get(k);
									if (tmpLayout.getLayoutId().equals(layoutId)) {
										layout = tmpLayout;
									}
								}
								if (layout == null) {
									layout = (Layout)groupLayouts.get(0);
								}
								
								layouts = groupLayouts;
								/*fixed */
								break;
							}
						}
					}
				}
				else {
					Group generalGuestGroup =
						GroupLocalServiceUtil.getGroupByName(
							user.getActualCompanyId(), Group.GENERAL_GUEST);					
					
					layouts = GroupLocalServiceUtil.getLayouts(
						generalGuestGroup.getGroupId(),
						Layout.DEFAULT_PARENT_LAYOUT_ID);

					if (layouts.size() > 0) {
						layout = (Layout)layouts.get(0);
					}
				}
			}

			LayoutTypePortlet layoutTypePortlet = null;

			if (layout != null) {
				req.setAttribute(WebKeys.LAYOUT, layout);
				req.setAttribute(WebKeys.LAYOUTS, layouts);

				layoutId = layout.getLayoutId();
				layoutTypePortlet = (LayoutTypePortlet)layout.getLayoutType();
			}

			String portletGroupId = PortalUtil.getPortletGroupId(layoutId);

			// Theme and color scheme

			Theme theme = null;
			ColorScheme colorScheme = null;

			if ((layout != null) && layout.isGroup()) {
				Group group = GroupLocalServiceUtil.getGroupById(
					layout.getGroupId());

				theme = group.getTheme();
				colorScheme = group.getColorScheme();
			}
			else {
				theme = user.getTheme();
				colorScheme = user.getColorScheme();
			}

			req.setAttribute(WebKeys.THEME, theme);
			req.setAttribute(WebKeys.COLOR_SCHEME, colorScheme);

			// Resolution

			int resNarrow = 0;
			int resTotal = 0;
			int resWide = 0;

			String resolution = user.getResolution();

			if (resolution.equals(Resolution.S1024X768_KEY)) {
				if ((layout != null) &&
					(layoutTypePortlet.getNumOfColumns() == 3)) {

					resNarrow = Resolution.S800X600_NARROW;
					resTotal = Resolution.S1024X768_TOTAL;
					resWide = Resolution.S800X600_WIDE;
				}
				else if ((layout != null) &&
						 (layoutTypePortlet.getNumOfColumns() == 1)) {

					resTotal = Resolution.S1024X768_TOTAL;
					resWide = resTotal;
				}
				else {
					resNarrow = Resolution.S1024X768_NARROW;
					resTotal = Resolution.S1024X768_TOTAL;
					resWide = Resolution.S1024X768_WIDE;
				}
			}
			else {
				if ((layout != null) &&
					(layoutTypePortlet.getNumOfColumns() == 3)) {

					resNarrow = Resolution.S800X600_NARROW;
					resTotal = Resolution.S1024X768_TOTAL;
					resWide = Resolution.S800X600_WIDE;
				}
				else if ((layout != null) &&
						 (layoutTypePortlet.getNumOfColumns() == 1)) {

					resTotal = Resolution.S800X600_TOTAL;
					resWide = resTotal;
				}
				else {
					resNarrow = Resolution.S800X600_NARROW;
					resTotal = Resolution.S800X600_TOTAL;
					resWide = Resolution.S800X600_WIDE;
				}
			}

			// Theme display

			String protocol = Http.getProtocol(req) + "://";

			String themeContextPath = contextPath;
			if (theme.isWARFile()) {
				themeContextPath = "/" + theme.getServletContextName();
			}

			ThemeDisplay themeDisplay = ThemeDisplayFactory.create();

			themeDisplay.setCompany(company);
			themeDisplay.setCompanyLogo(companyLogo);
			themeDisplay.setUser(user);
			themeDisplay.setSignedIn(signedIn);
			themeDisplay.setLayout(layout);
			themeDisplay.setLayouts(layouts);
			themeDisplay.setLayoutId(layoutId);
			themeDisplay.setLayoutTypePortlet(layoutTypePortlet);
			themeDisplay.setPortletGroupId(portletGroupId);
			themeDisplay.setLocale(locale);
			themeDisplay.setTimeZone(timeZone);
			themeDisplay.setTheme(theme);
			themeDisplay.setColorScheme(colorScheme);
			themeDisplay.setResNarrow(resNarrow);
			themeDisplay.setResWide(resWide);
			themeDisplay.setResTotal(resTotal);
			themeDisplay.setStatePopUp(LiferayWindowState.isPopUp(req));
			themeDisplay.setPathApplet(contextPath + "/applets");
			themeDisplay.setPathCaptcha(captchaPath);
			themeDisplay.setPathColorSchemeImage(
				themeContextPath + theme.getRootPath() + "/color_schemes/" +
					colorScheme.getColorSchemeId());
			themeDisplay.setPathContext(contextPath);
			themeDisplay.setPathFlash(contextPath + "/flash");
			themeDisplay.setPathFriendlyURL(friendlyURLPath);
			themeDisplay.setPathImage(imagePath);
			themeDisplay.setPathJavaScript(contextPath + "/html/js");
			themeDisplay.setPathMain(mainPath);
			themeDisplay.setPathRoot(rootPath);
			themeDisplay.setPathSound(contextPath + "/html/sound");
			themeDisplay.setPathThemeImage(
				themeContextPath + theme.getImagesPath());
			themeDisplay.setPathThemeRoot(
				themeContextPath + theme.getRootPath());
			themeDisplay.setURLAbout(mainPath + "/portal/about");
			themeDisplay.setURLDisclaimer(mainPath + "/portal/disclaimer");
			themeDisplay.setURLHome(protocol + company.getHomeURL());
			themeDisplay.setURLLanguage(mainPath + "/portal/language");

			// My Account
			/*Set myaccounturl with user previlege control model*/
			if (layouts != null) {
				/*
				String myAccountLayoutId = PortalUtil.getLayoutIdWithPortletId(
					layouts, PortletKeys.MY_ACCOUNT, layoutId);

				PortletURL myAccountURL = new PortletURLImpl(
					req, PortletKeys.MY_ACCOUNT, myAccountLayoutId, true);
				*/
				String userPrevilege = PortalUtil.getLayoutIdWithPortletId(
						layouts, "ecarduser", layoutId);
				PortletURL myAccountURL = new PortletURLImpl(
						req, "ecarduser", userPrevilege, false);
				myAccountURL.setWindowState(WindowState.MAXIMIZED);
				myAccountURL.setPortletMode(PortletMode.VIEW);				

				myAccountURL.setParameter(
					"struts_action", "/ecarduser/edit_password");

				themeDisplay.setURLMyAccount(myAccountURL);
			}

			themeDisplay.setURLPortal(protocol + company.getPortalURL());
			themeDisplay.setURLSignIn(mainPath + "/portal/login");
			themeDisplay.setURLSignOut(
				mainPath + "/portal/logout?referer=" + mainPath);

			req.setAttribute(WebKeys.THEME_DISPLAY, themeDisplay);
		}
		catch (Exception e) {
			e.printStackTrace();

			throw new ActionException(e);
		}
	}

	protected boolean isGroupLayoutViewable(User user, String groupId)
		throws PortalException, SystemException {

		// Guest layouts are always viewable

		Group generalGuestGroup =
			GroupLocalServiceUtil.getGroupByName(
				user.getActualCompanyId(), Group.GENERAL_GUEST);

		if (generalGuestGroup.getGroupId().equals(groupId)) {
			return true;
		}

		// Authenticated users can only see group layouts if they belong to the
		// group

		if (UserLocalServiceUtil.hasGroupById(user.getUserId(), groupId)) {
			return true;
		}
		else {
			return false;
		}
	}

}