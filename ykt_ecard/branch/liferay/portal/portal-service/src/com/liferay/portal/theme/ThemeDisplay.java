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

package com.liferay.portal.theme;

import com.liferay.portal.kernel.log.Log;
import com.liferay.portal.kernel.log.LogFactoryUtil;
import com.liferay.portal.kernel.security.permission.PermissionChecker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.model.Account;
import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Contact;
import com.liferay.portal.model.Layout;
import com.liferay.portal.model.LayoutTypePortlet;
import com.liferay.portal.model.Theme;
import com.liferay.portal.model.User;

import java.io.Serializable;

import java.util.List;
import java.util.Locale;
import java.util.TimeZone;

import javax.portlet.PortletURL;

/**
 * <a href="ThemeDisplay.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeDisplay implements Serializable {

	public ThemeDisplay() {
		if (_log.isDebugEnabled()) {
			_log.debug("Creating new instance " + hashCode());
		}
	}

	public Company getCompany() {
		return _company;
	}

	public void setCompany(Company company) {
		_company = company;

		setAccount(company.getAccount());
	}

	public long getCompanyId() {
		return _company.getCompanyId();
	}

	public String getCompanyLogo() {
		return _companyLogo;
	}

	public void setCompanyLogo(String companyLogo) {
		_companyLogo = companyLogo;
	}

	public int getCompanyLogoHeight() {
		return _companyLogoHeight;
	}

	public void setCompanyLogoHeight(int companyLogoHeight) {
		_companyLogoHeight = companyLogoHeight;
	}

	public int getCompanyLogoWidth() {
		return _companyLogoWidth;
	}

	public void setCompanyLogoWidth(int companyLogoWidth) {
		_companyLogoWidth = companyLogoWidth;
	}

	public String getRealCompanyLogo() {
		return _realCompanyLogo;
	}

	public void setRealCompanyLogo(String realCompanyLogo) {
		_realCompanyLogo = realCompanyLogo;
	}

	public int getRealCompanyLogoHeight() {
		return _realCompanyLogoHeight;
	}

	public void setRealCompanyLogoHeight(int realCompanyLogoHeight) {
		_realCompanyLogoHeight = realCompanyLogoHeight;
	}

	public int getRealCompanyLogoWidth() {
		return _realCompanyLogoWidth;
	}

	public void setRealCompanyLogoWidth(int realCompanyLogoWidth) {
		_realCompanyLogoWidth = realCompanyLogoWidth;
	}

	public Account getAccount() {
		return _account;
	}

	public void setAccount(Account account) {
		_account = account;
	}

	public User getDefaultUser() {
		if (_defaultUser == null) {
			_defaultUser = _company.getDefaultUser();
		}

		return _defaultUser;
	}

	public long getDefaultUserId() {
		return getDefaultUser().getUserId();
	}

	public User getUser() {
		return _user;
	}

	public void setUser(User user) {
		_user = user;

		setContact(user.getContact());
	}

	public long getUserId() {
		return _user.getUserId();
	}

	public User getRealUser() {
		return _realUser;
	}

	public void setRealUser(User realUser) {
		_realUser = realUser;
	}

	public long getRealUserId() {
		return _realUser.getUserId();
	}

	public String getDoAsUserId() {
		return _doAsUserId;
	}

	public void setDoAsUserId(String doAsUserId) {
		_doAsUserId = doAsUserId;
	}

	public boolean isImpersonated() {
		if (getUserId() == getRealUserId()) {
			return false;
		}
		else {
			return true;
		}
	}

	public Contact getContact() {
		return _contact;
	}

	public void setContact(Contact contact) {
		_contact = contact;
	}

	public String getLayoutSetLogo() {
		return _layoutSetLogo;
	}

	public void setLayoutSetLogo(String layoutSetLogo) {
		_layoutSetLogo = layoutSetLogo;
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

	public long getPlid() {
		return _plid;
	}

	public void setPlid(long plid) {
		_plid = plid;
	}

	public LayoutTypePortlet getLayoutTypePortlet() {
		return _layoutTypePortlet;
	}

	public void setLayoutTypePortlet(LayoutTypePortlet layoutTypePortlet) {
		_layoutTypePortlet = layoutTypePortlet;
	}

	public long getPortletGroupId() {
		return _portletGroupId;
	}

	public void setPortletGroupId(long portletGroupId) {
		_portletGroupId = portletGroupId;
	}

	public boolean isSignedIn() {
		return _signedIn;
	}

	public void setSignedIn(boolean signedIn) {
		_signedIn = signedIn;
	}

	public PermissionChecker getPermissionChecker() {
		return _permissionChecker;
	}

	public void setPermissionChecker(PermissionChecker permissionChecker) {
		_permissionChecker = permissionChecker;
	}

	public Locale getLocale() {
		return _locale;
	}

	public void setLocale(Locale locale) {
		_locale = locale;
	}

	public String getLanguageId() {
		return _languageId;
	}

	public void setLanguageId(String languageId) {
		_languageId = languageId;
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

	public String getThemeId() {
		return _theme.getThemeId();
	}

	public ColorScheme getColorScheme() {
		return _colorScheme;
	}

	public String getColorSchemeId() {
		return _colorScheme.getColorSchemeId();
	}

	public boolean isWapTheme() {
		return _theme.isWapTheme();
	}

	public void setLookAndFeel(Theme theme, ColorScheme colorScheme) {
		setLookAndFeel(getPathContext(), theme, colorScheme);
	}

	public void setLookAndFeel(
		String contextPath, Theme theme, ColorScheme colorScheme) {

		_theme = theme;
		_colorScheme = colorScheme;

		if ((theme != null) && (colorScheme != null)) {
			String themeContextPath = contextPath;

			if (theme.isWARFile()) {
				themeContextPath = theme.getContextPath();
			}

			String cdnHost = getCDNHost();

			setPathColorSchemeImages(
				cdnHost + themeContextPath +
					colorScheme.getColorSchemeImagesPath());

			setPathThemeCss(cdnHost + themeContextPath + theme.getCssPath());
			setPathThemeImages(
				cdnHost + themeContextPath + theme.getImagesPath());
			setPathThemeJavaScript(
				cdnHost + themeContextPath + theme.getJavaScriptPath());
			setPathThemeRoot(themeContextPath + theme.getRootPath());
		}
	}

	public boolean isThemeCssFastLoad() {
		return _themeCssFastLoad;
	}

	public void setThemeCssFastLoad(boolean themeCssFastLoad) {
		_themeCssFastLoad = themeCssFastLoad;
	}

	public boolean isFreeformLayout() {
		return _freeformLayout;
	}

	public void setFreeformLayout(boolean freeformLayout) {
		_freeformLayout = freeformLayout;
	}

	public String getServerName() {
		return _serverName;
	}

	public void setServerName(String serverName) {
		_serverName = serverName;
	}

	public int getServerPort() {
		return _serverPort;
	}

	public void setServerPort(int serverPort) {
		_serverPort = serverPort;
	}

	public boolean isSecure() {
		return _secure;
	}

	public void setSecure(boolean secure) {
		_secure = secure;
	}

	public boolean isStateExclusive() {
		return _stateExclusive;
	}

	public void setStateExclusive(boolean stateExclusive) {
		_stateExclusive = stateExclusive;
	}

	public boolean isStateMaximized() {
		return _stateMaximized;
	}

	public void setStateMaximized(boolean stateMaximized) {
		_stateMaximized = stateMaximized;
	}

	public boolean isStatePopUp() {
		return _statePopUp;
	}

	public void setStatePopUp(boolean statePopUp) {
		_statePopUp = statePopUp;
	}

	public String getCDNHost() {
		return _cdnHost;
	}

	public void setCDNHost(String cdnHost) {
		_cdnHost = cdnHost;
	}

	public String getPathApplet() {
		return _pathApplet;
	}

	public void setPathApplet(String pathApplet) {
		_pathApplet = pathApplet;
	}

	public String getPathCms() {
		return _pathCms;
	}

	public void setPathCms(String pathCms) {
		_pathCms = pathCms;
	}

	public String getPathColorSchemeImages() {
		return _pathColorSchemeImages;
	}

	public void setPathColorSchemeImages(String pathColorSchemeImages) {
		_pathColorSchemeImages = pathColorSchemeImages;
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

	public String getPathFriendlyURLPrivateGroup() {
		return _pathFriendlyURLPrivateGroup;
	}

	public void setPathFriendlyURLPrivateGroup(
		String pathFriendlyURLPrivateGroup) {

		_pathFriendlyURLPrivateGroup = pathFriendlyURLPrivateGroup;
	}

	public String getPathFriendlyURLPrivateUser() {
		return _pathFriendlyURLPrivateUser;
	}

	public void setPathFriendlyURLPrivateUser(
		String pathFriendlyURLPrivateUser) {

		_pathFriendlyURLPrivateUser = pathFriendlyURLPrivateUser;
	}

	public String getPathFriendlyURLPublic() {
		return _pathFriendlyURLPublic;
	}

	public void setPathFriendlyURLPublic(String pathFriendlyURLPublic) {
		_pathFriendlyURLPublic = pathFriendlyURLPublic;
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

	public String getPathSound() {
		return _pathSound;
	}

	public void setPathSound(String pathSound) {
		_pathSound = pathSound;
	}

	public String getPathThemeCss() {
		return _pathThemeCss;
	}

	public void setPathThemeCss(String pathThemeCss) {
		_pathThemeCss = pathThemeCss;
	}

	/**
	 * @deprecated Use <code>getPathThemeImages</code>.
	 */
	public String getPathThemeImage() {
		return getPathThemeImages();
	}

	public String getPathThemeImages() {
		return _pathThemeImages;
	}

	public void setPathThemeImages(String pathThemeImages) {
		_pathThemeImages = pathThemeImages;
	}

	public String getPathThemeJavaScript() {
		return _pathThemeJavaScript;
	}

	public void setPathThemeJavaScript(String pathThemeJavaScript) {
		_pathThemeJavaScript = pathThemeJavaScript;
	}

	public String getPathThemeRoot() {
		return _pathThemeRoot;
	}

	public void setPathThemeRoot(String pathThemeRoot) {
		_pathThemeRoot = pathThemeRoot;
	}

	public boolean isShowAddContentIcon() {
		return _showAddContentIcon;
	}

	public void setShowAddContentIcon(boolean showAddContentIcon) {
		_showAddContentIcon = showAddContentIcon;
	}

	public boolean isShowHomeIcon() {
		return _showHomeIcon;
	}

	public void setShowHomeIcon(boolean showHomeIcon) {
		_showHomeIcon = showHomeIcon;
	}

	public boolean isShowLayoutTemplatesIcon() {
		return _showLayoutTemplatesIcon;
	}

	public void setShowLayoutTemplatesIcon(boolean showLayoutTemplatesIcon) {
		_showLayoutTemplatesIcon = showLayoutTemplatesIcon;
	}

	public boolean isShowMyAccountIcon() {
		return _showMyAccountIcon;
	}

	public void setShowMyAccountIcon(boolean showMyAccountIcon) {
		_showMyAccountIcon = showMyAccountIcon;
	}

	public boolean isShowPageSettingsIcon() {
		return _showPageSettingsIcon;
	}

	public void setShowPageSettingsIcon(boolean showPageSettingsIcon) {
		_showPageSettingsIcon = showPageSettingsIcon;
	}

	public boolean isShowPortalIcon() {
		return _showPortalIcon;
	}

	public void setShowPortalIcon(boolean showPortalIcon) {
		_showPortalIcon = showPortalIcon;
	}

	public boolean isShowSignInIcon() {
		return _showSignInIcon;
	}

	public void setShowSignInIcon(boolean showSignInIcon) {
		_showSignInIcon = showSignInIcon;
	}

	public boolean isShowSignOutIcon() {
		return _showSignOutIcon;
	}

	public void setShowSignOutIcon(boolean showSignOutIcon) {
		_showSignOutIcon = showSignOutIcon;
	}

	public String getURLAddContent() {
		return _urlAddContent;
	}

	public void setURLAddContent(String urlAddContent) {
		_urlAddContent = urlAddContent;
	}

	public PortletURL getURLCreateAccount() {
		return _urlCreateAccount;
	}

	public void setURLCreateAccount(PortletURL urlCreateAccount) {
		_urlCreateAccount = urlCreateAccount;
	}

	public String getURLCurrent() {
		return _urlCurrent;
	}

	public void setURLCurrent(String urlCurrent) {
		_urlCurrent = urlCurrent;
	}

	public String getURLHome() {
		return _urlHome;
	}

	public void setURLHome(String urlHome) {
		_urlHome = urlHome;
	}

	public String getURLLayoutTemplates() {
		return _urlLayoutTemplates;
	}

	public void setURLLayoutTemplates(String urlLayoutTemplates) {
		_urlLayoutTemplates = urlLayoutTemplates;
	}

	public PortletURL getURLMyAccount() {
		return _urlMyAccount;
	}

	public void setURLMyAccount(PortletURL urlMyAccount) {
		_urlMyAccount = urlMyAccount;
	}

	public PortletURL getURLPageSettings() {
		return _urlPageSettings;
	}

	public void setURLPageSettings(PortletURL urlPageSettings) {
		_urlPageSettings = urlPageSettings;
	}

	public String getURLPortal() {
		return _urlPortal;
	}

	public void setURLPortal(String urlPortal) {
		_urlPortal = urlPortal;
	}

	public PortletURL getURLPublishToLive() {
		return _urlPublishToLive;
	}

	public void setURLPublishToLive(PortletURL urlPublishToLive) {
		_urlPublishToLive = urlPublishToLive;
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

	public PortletURL getURLUpdateManager() {
		return _urlUpdateManager;
	}

	public void setURLUpdateManager(PortletURL urlUpdateManager) {
		_urlUpdateManager = urlUpdateManager;
	}

	public String getTilesTitle() {
		return _tilesTitle;
	}

	public void setTilesTitle(String tilesTitle) {
		_tilesTitle = tilesTitle;
	}

	public String getTilesContent() {
		return _tilesContent;
	}

	public void setTilesContent(String tilesContent) {
		_tilesContent = tilesContent;
	}

	public boolean isTilesSelectable() {
		return _tilesSelectable;
	}

	public void setTilesSelectable(boolean tilesSelectable) {
		_tilesSelectable = tilesSelectable;
	}

	public boolean isIncludeCalendarJs() {
		return _includeCalendarJs;
	}

	public void setIncludeCalendarJs(boolean includeCalendarJs) {
		_includeCalendarJs = includeCalendarJs;
	}

	public boolean isIncludePortletCssJs() {
		return _includePortletCssJs;
	}

	public void setIncludePortletCssJs(boolean includePortletCssJs) {
		_includePortletCssJs = includePortletCssJs;
	}

	public boolean isIncludeServiceJs() {
		return _includeServiceJs;
	}

	public void setIncludeServiceJs(boolean includeServiceJs) {
		_includeServiceJs = includeServiceJs;
	}

	public boolean isIncludedJs(String js) {
		String path = getPathJavaScript();

		if (isIncludeCalendarJs() &&
			js.equals(path + "/calendar/calendar_stripped.js")) {

			return true;
		}
		else if (isIncludePortletCssJs() &&
				 js.equals(path + "/liferay/portlet_css_packed.js")) {

			return true;
		}
		else if (isIncludeServiceJs() &&
				 js.equals(path + "/liferay/service_packed.js")) {

			return true;
		}
		else {
			return false;
		}
	}

	public PortletDisplay getPortletDisplay() {
		return _portletDisplay;
	}

	public void setPortletDisplay(PortletDisplay portletDisplay) {
		_portletDisplay = portletDisplay;
	}

	public void recycle() {
		if (_log.isDebugEnabled()) {
			_log.debug("Recycling instance " + hashCode());
		}

		_company = null;
		_companyLogo = StringPool.BLANK;
		_companyLogoHeight = 0;
		_companyLogoWidth = 0;
		_realCompanyLogo = StringPool.BLANK;
		_realCompanyLogoHeight = 0;
		_realCompanyLogoWidth = 0;
		_account = null;
		_defaultUser = null;
		_user = null;
		_realUser = null;
		_doAsUserId = StringPool.BLANK;
		_layoutSetLogo = StringPool.BLANK;
		_layout = null;
		_layouts = null;
		_plid = 0;
		_layoutTypePortlet = null;
		_portletGroupId = 0;
		_signedIn = false;
		_permissionChecker = null;
		_locale = null;
		_languageId = null;
		_timeZone = null;
		_theme = null;
		_colorScheme = null;
		_themeCssFastLoad = false;
		_freeformLayout = false;
		_serverName = StringPool.BLANK;
		_serverPort = 0;
		_secure = false;
		_stateExclusive = false;
		_stateMaximized = false;
		_statePopUp = false;
		_cdnHost = StringPool.BLANK;
		_pathApplet = StringPool.BLANK;
		_pathCms = StringPool.BLANK;
		_pathColorSchemeImages = StringPool.BLANK;
		_pathContext = StringPool.BLANK;
		_pathFlash = StringPool.BLANK;
		_pathFriendlyURLPrivateGroup = StringPool.BLANK;
		_pathFriendlyURLPrivateUser = StringPool.BLANK;
		_pathFriendlyURLPublic = StringPool.BLANK;
		_pathImage = StringPool.BLANK;
		_pathJavaScript = StringPool.BLANK;
		_pathMain = StringPool.BLANK;
		_pathSound = StringPool.BLANK;
		_pathThemeCss = StringPool.BLANK;
		_pathThemeImages = StringPool.BLANK;
		_pathThemeJavaScript = StringPool.BLANK;
		_pathThemeRoot = StringPool.BLANK;
		_showAddContentIcon = false;
		_showHomeIcon = false;
		_showLayoutTemplatesIcon = false;
		_showMyAccountIcon = false;
		_showPageSettingsIcon = false;
		_showPortalIcon = false;
		_showSignInIcon = false;
		_showSignOutIcon = false;
		_urlAddContent = StringPool.BLANK;
		_urlCreateAccount = null;
		_urlCurrent = StringPool.BLANK;
		_urlHome = StringPool.BLANK;
		_urlLayoutTemplates = StringPool.BLANK;
		_urlMyAccount = null;
		_urlPageSettings = null;
		_urlPortal = StringPool.BLANK;
		_urlPublishToLive = null;
		_urlSignIn = StringPool.BLANK;
		_urlSignOut = StringPool.BLANK;
		_urlUpdateManager = null;
		_tilesTitle = StringPool.BLANK;
		_tilesContent = StringPool.BLANK;
		_tilesSelectable = false;
		_includeCalendarJs = false;
		_includePortletCssJs = false;
		_includeServiceJs = false;
		_portletDisplay.recycle();
	}

	private static Log _log = LogFactoryUtil.getLog(ThemeDisplay.class);

	private Company _company;
	private String _companyLogo = StringPool.BLANK;
	private int _companyLogoHeight;
	private int _companyLogoWidth;
	private String _realCompanyLogo = StringPool.BLANK;
	private int _realCompanyLogoHeight;
	private int _realCompanyLogoWidth;
	private Account _account;
	private User _defaultUser;
	private User _user;
	private User _realUser;
	private String _doAsUserId = StringPool.BLANK;
	private Contact _contact;
	private String _layoutSetLogo = StringPool.BLANK;
	private Layout _layout;
	private List _layouts;
	private long _plid;
	private LayoutTypePortlet _layoutTypePortlet;
	private long _portletGroupId;
	private boolean _signedIn;
	private PermissionChecker _permissionChecker;
	private Locale _locale;
	private String _languageId;
	private TimeZone _timeZone;
	private Theme _theme;
	private ColorScheme _colorScheme;
	private boolean _themeCssFastLoad;
	private boolean _freeformLayout;
	private String _serverName;
	private int _serverPort;
	private boolean _secure;
	private boolean _stateExclusive;
	private boolean _stateMaximized;
	private boolean _statePopUp;
	private String _cdnHost = StringPool.BLANK;
	private String _pathApplet = StringPool.BLANK;
	private String _pathCms = StringPool.BLANK;
	private String _pathColorSchemeImages = StringPool.BLANK;
	private String _pathContext = StringPool.BLANK;
	private String _pathFlash = StringPool.BLANK;
	private String _pathFriendlyURLPrivateGroup = StringPool.BLANK;
	private String _pathFriendlyURLPrivateUser = StringPool.BLANK;
	private String _pathFriendlyURLPublic = StringPool.BLANK;
	private String _pathImage = StringPool.BLANK;
	private String _pathJavaScript = StringPool.BLANK;
	private String _pathMain = StringPool.BLANK;
	private String _pathSound = StringPool.BLANK;
	private String _pathThemeCss = StringPool.BLANK;
	private String _pathThemeImages = StringPool.BLANK;
	private String _pathThemeJavaScript = StringPool.BLANK;
	private String _pathThemeRoot = StringPool.BLANK;
	private boolean _showAddContentIcon;
	private boolean _showHomeIcon;
	private boolean _showLayoutTemplatesIcon;
	private boolean _showMyAccountIcon;
	private boolean _showPageSettingsIcon;
	private boolean _showPortalIcon;
	private boolean _showSignInIcon;
	private boolean _showSignOutIcon;
	private String _urlAddContent = StringPool.BLANK;
	private transient PortletURL _urlCreateAccount = null;
	private String _urlCurrent = StringPool.BLANK;
	private String _urlHome = StringPool.BLANK;
	private String _urlLayoutTemplates = StringPool.BLANK;
	private transient PortletURL _urlMyAccount = null;
	private transient PortletURL _urlPageSettings = null;
	private String _urlPortal = StringPool.BLANK;
	private transient PortletURL _urlPublishToLive = null;
	private String _urlSignIn = StringPool.BLANK;
	private String _urlSignOut = StringPool.BLANK;
	private transient PortletURL _urlUpdateManager = null;
	private String _tilesTitle = StringPool.BLANK;
	private String _tilesContent = StringPool.BLANK;
	private boolean _tilesSelectable;
	private boolean _includeCalendarJs;
	private boolean _includePortletCssJs;
	private boolean _includeServiceJs;
	private PortletDisplay _portletDisplay = new PortletDisplay();

}