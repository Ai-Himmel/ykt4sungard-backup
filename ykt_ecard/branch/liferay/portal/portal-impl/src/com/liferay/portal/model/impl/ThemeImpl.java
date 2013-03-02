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

package com.liferay.portal.model.impl;

import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Theme;
import com.liferay.portal.theme.ThemeCompanyLimit;
import com.liferay.portal.theme.ThemeGroupLimit;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.velocity.VelocityResourceListener;
import com.liferay.util.ListUtil;

import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ThemeImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ThemeImpl extends PluginBaseImpl implements Theme {

	public static final String PLUGIN_TYPE = "theme";

	public static String getDefaultRegularThemeId() {
		return _DEFAULT_REGULAR_THEME_ID;
	}

	public static String getDefaultWapThemeId() {
		return _DEFAULT_WAP_THEME_ID;
	}

	public ThemeImpl() {
	}

	public ThemeImpl(String themeId) {
		_themeId = themeId;
	}

	public ThemeImpl(String themeId, String name) {
		_themeId = themeId;
		_name = name;
	}

	public String getThemeId() {
		return _themeId;
	}

	public String getPluginId() {
		return getThemeId();
	}

	public String getPluginType() {
		return PLUGIN_TYPE;
	}

	public ThemeCompanyLimit getThemeCompanyLimit() {
		return _themeCompanyLimit;
	}

	public void setThemeCompanyLimit(ThemeCompanyLimit themeCompanyLimit) {
		_themeCompanyLimit = themeCompanyLimit;
	}

	public boolean isCompanyAvailable(long companyId) {
		return isAvailable(getThemeCompanyLimit(), companyId);
	}

	public ThemeGroupLimit getThemeGroupLimit() {
		return _themeGroupLimit;
	}

	public void setThemeGroupLimit(ThemeGroupLimit themeGroupLimit) {
		_themeGroupLimit = themeGroupLimit;
	}

	public boolean isGroupAvailable(long groupId) {
		return isAvailable(getThemeGroupLimit(), groupId);
	}

	public long getTimestamp() {
		return _timestamp;
	}

	public void setTimestamp(long timestamp) {
		_timestamp = timestamp;
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getRootPath() {
		return _rootPath;
	}

	public void setRootPath(String rootPath) {
		_rootPath = rootPath;
	}

	public String getTemplatesPath() {
		return _templatesPath;
	}

	public void setTemplatesPath(String templatesPath) {
		_templatesPath = templatesPath;
	}

	public String getCssPath() {
		return _cssPath;
	}

	public void setCssPath(String cssPath) {
		_cssPath = cssPath;
	}

	public String getImagesPath() {
		return _imagesPath;
	}

	public void setImagesPath(String imagesPath) {
		_imagesPath = imagesPath;
	}

	public String getJavaScriptPath() {
		return _javaScriptPath;
	}

	public void setJavaScriptPath(String javaScriptPath) {
		_javaScriptPath = javaScriptPath;
	}

	public String getVirtualPath() {
		return _virtualPath;
	}

	public void setVirtualPath(String virtualPath) {
		if (_warFile && Validator.isNull(virtualPath)) {
			virtualPath = PropsValues.THEME_VIRTUAL_PATH;
		}

		_virtualPath = virtualPath;
	}

	public String getTemplateExtension() {
		return _templateExtension;
	}

	public void setTemplateExtension(String templateExtension) {
		_templateExtension = templateExtension;
	}

	public Properties getSettings() {
		return _settings;
	}

	public String getSetting(String key) {
		return _settings.getProperty(key);
	}

	public void setSetting(String key, String value) {
		_settings.setProperty(key, value);
	}

	public boolean getWapTheme() {
		return _wapTheme;
	}

	public boolean isWapTheme() {
		return _wapTheme;
	}

	public void setWapTheme(boolean wapTheme) {
		_wapTheme = wapTheme;
	}

	public List getColorSchemes() {
		List colorSchemes = ListUtil.fromCollection(_colorSchemesMap.values());

		Collections.sort(colorSchemes);

		return colorSchemes;
	}

	public Map getColorSchemesMap() {
		return _colorSchemesMap;
	}

	public boolean hasColorSchemes() {
		if (_colorSchemesMap.size() > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	public String getServletContextName() {
		return _servletContextName;
	}

	public void setServletContextName(String servletContextName) {
		_servletContextName = servletContextName;

		if (Validator.isNotNull(_servletContextName)) {
			_warFile = true;
		}
		else {
			_warFile = false;
		}
	}

	public boolean getWARFile() {
		return _warFile;
	}

	public boolean isWARFile() {
		return _warFile;
	}

	public String getContextPath() {
		String virtualPath = getVirtualPath();

		if (Validator.isNotNull(virtualPath)) {
			return virtualPath;
		}

		if (isWARFile()) {
			StringMaker sm = new StringMaker();

			sm.append(StringPool.SLASH);
			sm.append(getServletContextName());

			return sm.toString();
		}
		else {
			return PortalUtil.getPathContext();
		}
	}

	public boolean getLoadFromServletContext() {
		return _loadFromServletContext;
	}

	public boolean isLoadFromServletContext() {
		return _loadFromServletContext;
	}

	public void setLoadFromServletContext(boolean loadFromServletContext) {
		_loadFromServletContext = loadFromServletContext;
	}

	public String getVelocityResourceListener() {
		if (_loadFromServletContext) {
			return VelocityResourceListener.SERVLET_SEPARATOR;
		}
		else {
			return VelocityResourceListener.THEME_LOADER_SEPARATOR;
		}
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		Theme theme = (Theme)obj;

		return getName().compareTo(theme.getName());
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		Theme theme = null;

		try {
			theme = (Theme)obj;
		}
		catch (ClassCastException cce) {
			return false;
		}

		String themeId = theme.getThemeId();

		if (getThemeId().equals(themeId)) {
			return true;
		}
		else {
			return false;
		}
	}

	protected boolean isAvailable(ThemeCompanyLimit limit, long id) {
		boolean available = true;

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Check if theme " + getThemeId() + " is available for " + id);
		}

		if (limit != null) {
			List includes = limit.getIncludes();
			List excludes = limit.getExcludes();

			if ((includes.size() != 0) && (excludes.size() != 0)) {

				// Since includes and excludes are specified, check to
				// make sure the current company id is included and also
				// not excluded

				if (_log.isDebugEnabled()) {
					_log.debug("Check includes and excludes");
				}

				available = limit.isIncluded(id);

				if (available) {
					available = !limit.isExcluded(id);
				}
			}
			else if ((includes.size() == 0) && (excludes.size() != 0)) {

				// Since no includes are specified, check to make sure
				// the current company id is not excluded

				if (_log.isDebugEnabled()) {
					_log.debug("Check excludes");
				}

				available = !limit.isExcluded(id);
			}
			else if ((includes.size() != 0) && (excludes.size() == 0)) {

				// Since no excludes are specified, check to make sure
				// the current company id is included

				if (_log.isDebugEnabled()) {
					_log.debug("Check includes");
				}

				available = limit.isIncluded(id);
			}
			else {

				// Since no includes or excludes are specified, this
				// theme is available for every company

				if (_log.isDebugEnabled()) {
					_log.debug("No includes or excludes set");
				}

				available = true;
			}
		}

		if (_log.isDebugEnabled()) {
			_log.debug(
				"Theme " + getThemeId() + " is " +
					(!available ? "NOT " : "") + "available for " + id);
		}

		return available;
	}

	private static final String _DEFAULT_REGULAR_THEME_ID =
		PortalUtil.getJsSafePortletId(PropsValues.DEFAULT_REGULAR_THEME_ID);

	private static final String _DEFAULT_WAP_THEME_ID =
		PortalUtil.getJsSafePortletId(PropsValues.DEFAULT_WAP_THEME_ID);

	private static Log _log = LogFactory.getLog(ThemeImpl.class);

	private String _themeId;
	private ThemeCompanyLimit _themeCompanyLimit;
	private ThemeGroupLimit _themeGroupLimit;
	private long _timestamp;
	private String _name;
	private String _rootPath = "/";
	private String _templatesPath = "${root-path}/templates";
	private String _cssPath = "${root-path}/css";
	private String _imagesPath = "${root-path}/images";
	private String _javaScriptPath = "${root-path}/javascript";
	private String _virtualPath = StringPool.BLANK;
	private String _templateExtension = "vm";
	private Properties _settings = new Properties();
	private boolean _wapTheme;
	private Map _colorSchemesMap = new HashMap();
	private String _servletContextName = StringPool.BLANK;
	private boolean _warFile;
	private boolean _loadFromServletContext;

}