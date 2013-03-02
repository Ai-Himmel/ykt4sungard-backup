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

package com.liferay.portal.theme;

import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;

import java.io.Serializable;

import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import javax.portlet.PortletURL;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ThemeDisplay.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.21 $
 *
 */
public class ThemeDisplay implements Serializable {

	public Company getCompany() {
		return _company;
	}

	public void setCompany(Company company) {
		_company = company;
	}

	public String getCompanyId() {
		return _company.getCompanyId();
	}

	public String getCompanyLogo() {
		return _companyLogo;
	}

	public void setCompanyLogo(String companyLogo) {
		_companyLogo = companyLogo;
	}

	public User getUser() {
		return _user;
	}

	public void setUser(User user) {
		_user = user;
	}

	public String getUserId() {
		return _user.getUserId();
	}

	public Layout getLayout() {
		return _layout;
	}

	public void setLayout(Layout layout) {
		_layout = layout;
	}

	public List getLayouts() {
		return _layouts;
	}

	public void setLayouts(List layouts) {
		_layouts = layouts;
	}

	public String getLayoutId() {
		return _layoutId;
	}

	public void setLayoutId(String layoutId) {
		_layoutId = layoutId;
	}

	public LayoutTypePortlet getLayoutTypePortlet() {
		return _layoutTypePortlet;
	}

	public void setLayoutTypePortlet(LayoutTypePortlet layoutTypePortlet) {
		_layoutTypePortlet = layoutTypePortlet;
	}

	public String getPortletGroupId() {
		return _portletGroupId;
	}

	public void setPortletGroupId(String portletGroupId) {
		_portletGroupId = portletGroupId;
	}

	public boolean isSignedIn() {
		return _signedIn;
	}

	public void setSignedIn(boolean signedIn) {
		_signedIn = signedIn;
	}

	public Locale getLocale() {
		return _locale;
	}

	public void setLocale(Locale locale) {
		_locale = locale;
	}

	public TimeZone getTimeZone() {
		return _timeZone;
	}

	public void setTimeZone(TimeZone timeZone) {
		_timeZone = timeZone;
	}

	public Theme getTheme() {
		return _theme;
	}

	public void setTheme(Theme theme) {
		_theme = theme;
	}

	public ColorScheme getColorScheme() {
		return _colorScheme;
	}

	public void setColorScheme(ColorScheme colorScheme) {
		_colorScheme = colorScheme;
	}

	public int getResNarrow() {
		return _resNarrow;
	}

	public void setResNarrow(int resNarrow) {
		_resNarrow = resNarrow;
	}

	public int getResWide() {
		return _resWide;
	}

	public void setResWide(int resWide) {
		_resWide = resWide;
	}

	public int getResTotal() {
		return _resTotal;
	}

	public void setResTotal(int resTotal) {
		_resTotal = resTotal;
	}

	public boolean isStatePopUp() {
		return _statePopUp;
	}

	public void setStatePopUp(boolean statePopUp) {
		_statePopUp = statePopUp;
	}

	public String getPathApplet() {
		return _pathApplet;
	}

	public void setPathApplet(String pathApplet) {
		_pathApplet = pathApplet;
	}

	public String getPathCaptcha() {
		return _pathCaptcha;
	}

	public void setPathCaptcha(String pathCaptcha) {
		_pathCaptcha = pathCaptcha;
	}

	public String getPathColorSchemeImage() {
		return _pathColorSchemeImage;
	}

	public void setPathColorSchemeImage(String pathColorSchemeImage) {
		_pathColorSchemeImage = pathColorSchemeImage;
	}

	public String getPathContext() {
		return _pathContext;
	}

	public void setPathContext(String pathContext) {
		_pathContext = pathContext;
	}

	public String getPathFlash() {
		return _pathFlash;
	}

	public void setPathFlash(String pathFlash) {
		_pathFlash = pathFlash;
	}

	public String getPathFriendlyURL() {
		return _pathFriendlyURL;
	}

	public void setPathFriendlyURL(String pathFriendlyURL) {
		_pathFriendlyURL = pathFriendlyURL;
	}

	public String getPathImage() {
		return _pathImage;
	}

	public void setPathImage(String pathImage) {
		_pathImage = pathImage;
	}

	public String getPathJavaScript() {
		return _pathJavaScript;
	}

	public void setPathJavaScript(String pathJavaScript) {
		_pathJavaScript = pathJavaScript;
	}

	public String getPathMain() {
		return _pathMain;
	}

	public void setPathMain(String pathMain) {
		_pathMain = pathMain;
	}

	public String getPathRoot() {
		return _pathRoot;
	}

	public void setPathRoot(String pathRoot) {
		_pathRoot = pathRoot;
	}

	public String getPathSound() {
		return _pathSound;
	}

	public void setPathSound(String pathSound) {
		_pathSound = pathSound;
	}

	public String getPathThemeImage() {
		return _pathThemeImage;
	}

	public void setPathThemeImage(String pathThemeImage) {
		_pathThemeImage = pathThemeImage;
	}

	public String getPathThemeRoot() {
		return _pathThemeRoot;
	}

	public void setPathThemeRoot(String pathThemeRoot) {
		_pathThemeRoot = pathThemeRoot;
	}

	public String getURLAbout() {
		return _urlAbout;
	}

	public void setURLAbout(String urlAbout) {
		_urlAbout = urlAbout;
	}

	public String getURLDisclaimer() {
		return _urlDisclaimer;
	}

	public void setURLDisclaimer(String urlDisclaimer) {
		_urlDisclaimer = urlDisclaimer;
	}

	public String getURLHome() {
		return _urlHome;
	}

	public void setURLHome(String urlHome) {
		_urlHome = urlHome;
	}

	public String getURLLanguage() {
		return _urlLanguage;
	}

	public void setURLLanguage(String urlLanguage) {
		_urlLanguage = urlLanguage;
	}

	public PortletURL getURLMyAccount() {
		return _urlMyAccount;
	}

	public void setURLMyAccount(PortletURL urlMyAccount) {
		_urlMyAccount = urlMyAccount;
	}

	public String getURLPortal() {
		return _urlPortal;
	}

	public void setURLPortal(String urlPortal) {
		_urlPortal = urlPortal;
	}

	public String getURLSignIn() {
		return _urlSignIn;
	}

	public void setURLSignIn(String urlSignIn) {
		_urlSignIn = urlSignIn;
	}

	public String getURLSignOut() {
		return _urlSignOut;
	}

	public void setURLSignOut(String urlSignOut) {
		_urlSignOut = urlSignOut;
	}

	public PortletDisplay getPortletDisplay() {
		return _portletDisplay;
	}

	public void setPortletDisplay(PortletDisplay portletDisplay) {
		_portletDisplay = portletDisplay;
	}

	public void recycle() {
		_log.debug("Recycling instance " + hashCode());

		_company = null;
		_companyLogo = null;
		_user = null;
		_signedIn = false;
		_layout = null;
		_layouts = null;
		_layoutId = null;
		_layoutTypePortlet = null;
		_portletGroupId = null;
		_locale = null;
		_timeZone = null;
		_theme = null;
		_colorScheme = null;
		_resNarrow = 0;
		_resWide = 0;
		_resTotal = 0;
		_pathApplet = null;
		_pathCaptcha = null;
		_pathColorSchemeImage = null;
		_pathFlash = null;
		_pathImage = null;
		_pathJavaScript = null;
		_pathMain = null;
		_pathSound = null;
		_pathThemeImage = null;
		_pathThemeRoot = null;
		_urlAbout = null;
		_urlDisclaimer = null;
		_urlHome = null;
		_urlLanguage = null;
		_urlMyAccount = null;
		_urlPortal = null;
		_urlSignIn = null;
		_urlSignOut = null;
		_portletDisplay.recycle();
	}

	protected ThemeDisplay() {
		_log.debug("Creating new instance " + hashCode());
	}

	private static final Log _log = LogFactory.getLog(ThemeDisplay.class);

	private Company _company;
	private String _companyLogo;
	private User _user;
	private boolean _signedIn;
	private Layout _layout;
	private List _layouts;
	private String _layoutId;
	private LayoutTypePortlet _layoutTypePortlet;
	private String _portletGroupId;
	private Locale _locale;
	private TimeZone _timeZone;
	private Theme _theme;
	private ColorScheme _colorScheme;
	private int _resNarrow;
	private int _resWide;
	private int _resTotal;
	private boolean _statePopUp;
	private String _pathApplet;
	private String _pathCaptcha;
	private String _pathColorSchemeImage;
	private String _pathContext;
	private String _pathFlash;
	private String _pathFriendlyURL;
	private String _pathImage;
	private String _pathJavaScript;
	private String _pathMain;
	private String _pathRoot;
	private String _pathSound;
	private String _pathThemeImage;
	private String _pathThemeRoot;
	private String _urlAbout = null;
	private String _urlDisclaimer = null;
	private String _urlHome = null;
	private String _urlLanguage = null;
	private PortletURL _urlMyAccount = null;
	private String _urlPortal = null;
	private String _urlSignIn = null;
	private String _urlSignOut = null;
	private PortletDisplay _portletDisplay = new PortletDisplay();

}