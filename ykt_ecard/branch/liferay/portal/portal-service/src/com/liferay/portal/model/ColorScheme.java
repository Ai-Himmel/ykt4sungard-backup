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

import java.io.Serializable;

import java.util.Properties;

/**
 * <a href="ColorScheme.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface ColorScheme extends Comparable, Serializable {

	public String getColorSchemeId();

	public String getName();

	public void setName(String name);

	public boolean getDefaultCs();

	public boolean isDefaultCs();

	public void setDefaultCs(boolean defaultCs);

	public String getCssClass();

	public void setCssClass(String cssClass);

	public String getColorSchemeImagesPath();

	public void setColorSchemeImagesPath(String colorSchemeImagesPath);

	public String getSettings();

	public void setSettings(String settings);

	public Properties getSettingsProperties();

	public void setSettingsProperties(Properties settingsProperties);

	public String getSetting(String key);

	public String getBodyBg();

	public String getLayoutBg();

	public String getLayoutText();

	public String getLayoutTabBg();

	public String getLayoutTabText();

	public String getLayoutTabSelectedBg();

	public String getLayoutTabSelectedText();

	public String getPortletTitleBg();

	public String getPortletTitleText();

	public String getPortletMenuBg();

	public String getPortletMenuText();

	public String getPortletBg();

	public String getPortletFont();

	public String getPortletFontDim();

	public String getPortletMsgStatus();

	public String getPortletMsgInfo();

	public String getPortletMsgError();

	public String getPortletMsgAlert();

	public String getPortletMsgSuccess();

	public String getPortletSectionHeader();

	public String getPortletSectionHeaderBg();

	public String getPortletSectionSubheader();

	public String getPortletSectionSubheaderBg();

	public String getPortletSectionBody();

	public String getPortletSectionBodyBg();

	public String getPortletSectionBodyHover();

	public String getPortletSectionBodyHoverBg();

	public String getPortletSectionAlternate();

	public String getPortletSectionAlternateBg();

	public String getPortletSectionAlternateHover();

	public String getPortletSectionAlternateHoverBg();

	public String getPortletSectionSelected();

	public String getPortletSectionSelectedBg();

	public String getPortletSectionSelectedHover();

	public String getPortletSectionSelectedHoverBg();

}