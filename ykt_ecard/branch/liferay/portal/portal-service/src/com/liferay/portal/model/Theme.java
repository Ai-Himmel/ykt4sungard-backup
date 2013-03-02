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

package com.liferay.portal.model;

import com.liferay.portal.theme.ThemeCompanyLimit;
import com.liferay.portal.theme.ThemeGroupLimit;

import java.io.Serializable;

import java.util.List;
import java.util.Map;
import java.util.Properties;

/**
 * <a href="Theme.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface Theme extends Comparable, Plugin, Serializable {

	public String getThemeId();

	public ThemeCompanyLimit getThemeCompanyLimit();

	public void setThemeCompanyLimit(ThemeCompanyLimit themeCompanyLimit);

	public boolean isCompanyAvailable(long companyId);

	public ThemeGroupLimit getThemeGroupLimit();

	public void setThemeGroupLimit(ThemeGroupLimit themeGroupLimit);

	public boolean isGroupAvailable(long groupId);

	public long getTimestamp();

	public void setTimestamp(long timestamp);

	public String getName();

	public void setName(String name);

	public String getRootPath();

	public void setRootPath(String rootPath);

	public String getTemplatesPath();

	public void setTemplatesPath(String templatesPath);

	public String getCssPath();

	public void setCssPath(String cssPath);

	public String getImagesPath();

	public void setImagesPath(String imagesPath);

	public String getJavaScriptPath();

	public void setJavaScriptPath(String javaScriptPath);

	public String getVirtualPath();

	public void setVirtualPath(String virtualPath);

	public String getTemplateExtension();

	public void setTemplateExtension(String templateExtension);

	public Properties getSettings();

	public String getSetting(String key);

	public void setSetting(String key, String value);

	public boolean getWapTheme();

	public boolean isWapTheme();

	public void setWapTheme(boolean wapTheme);

	public List getColorSchemes();

	public Map getColorSchemesMap();

	public boolean hasColorSchemes();

	public String getServletContextName();

	public void setServletContextName(String servletContextName);

	public boolean getWARFile();

	public boolean isWARFile();

	public String getContextPath();

	public boolean getLoadFromServletContext();

	public boolean isLoadFromServletContext();

	public void setLoadFromServletContext(boolean loadFromServletContext);

	public String getVelocityResourceListener();

}