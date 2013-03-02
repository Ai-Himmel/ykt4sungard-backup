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

package com.liferay.portal.model;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.NullSafeProperties;
import com.liferay.util.PropertiesUtil;
import com.liferay.util.StringPool;

import java.io.IOException;

import java.util.Properties;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="ColorScheme.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.182 $
 *
 */
public class ColorScheme extends ColorSchemeModel {

	public static final String DEFAULT_COLOR_SCHEME_ID =
		PropsUtil.get(PropsUtil.DEFAULT_COLOR_SCHEME_ID);

	public static final String BODY_BG = "body-bg";

	public static final String LAYOUT_BG = "layout-bg";

	public static final String LAYOUT_TEXT = "layout-text";

	public static final String LAYOUT_TAB_BG = "layout-tab-bg";

	public static final String LAYOUT_TAB_TEXT = "layout-tab-text";

	public static final String LAYOUT_TAB_SELECTED_BG =
		"layout-tab-selected-bg";

	public static final String LAYOUT_TAB_SELECTED_TEXT =
		"layout-tab-selected-text";

	public static final String PORTLET_TITLE_BG = "portlet-title-bg";

	public static final String PORTLET_TITLE_TEXT = "portlet-title-text";

	public static final String PORTLET_MENU_BG = "portlet-menu-bg";

	public static final String PORTLET_MENU_TEXT = "portlet-menu-text";

	public static final String PORTLET_BG = "portlet-bg";

	public static final String PORTLET_FONT = "portlet-font";

	public static final String PORTLET_FONT_DIM = "portlet-font-dim";

	public static final String PORTLET_MSG_STATUS = "portlet-msg-status";

	public static final String PORTLET_MSG_INFO = "portlet-msg-info";

	public static final String PORTLET_MSG_ERROR = "portlet-msg-error";

	public static final String PORTLET_MSG_ALERT = "portlet-msg-alert";

	public static final String PORTLET_MSG_SUCCESS = "portlet-msg-success";

	public static final String PORTLET_SECTION_HEADER =
		"portlet-section-header";

	public static final String PORTLET_SECTION_HEADER_BG =
		"portlet-section-header-bg";

	public static final String PORTLET_SECTION_SUBHEADER =
		"portlet-section-subheader";

	public static final String PORTLET_SECTION_SUBHEADER_BG =
		"portlet-section-subheader-bg";

	public static final String PORTLET_SECTION_BODY = "portlet-section-body";

	public static final String PORTLET_SECTION_BODY_BG =
		"portlet-section-body-bg";

	public static final String PORTLET_SECTION_BODY_HOVER =
		"portlet-section-body-hover";

	public static final String PORTLET_SECTION_BODY_HOVER_BG =
		"portlet-section-body-hover-bg";

	public static final String PORTLET_SECTION_ALTERNATE =
		"portlet-section-alternate";

	public static final String PORTLET_SECTION_ALTERNATE_BG =
		"portlet-section-alternate-bg";

	public static final String PORTLET_SECTION_ALTERNATE_HOVER =
		"portlet-section-alternate-hover";

	public static final String PORTLET_SECTION_ALTERNATE_HOVER_BG =
		"portlet-section-alternate-hover-bg";

	public static final String PORTLET_SECTION_SELECTED =
		"portlet-section-selected";

	public static final String PORTLET_SECTION_SELECTED_BG =
		"portlet-section-selected-bg";

	public static final String PORTLET_SECTION_SELECTED_HOVER =
		"portlet-section-selected-hover";

	public static final String PORTLET_SECTION_SELECTED_HOVER_BG =
		"portlet-section-selected-hover-bg";

	public static final ColorScheme NULL_COLOR_SCHEME =
		new ColorScheme(DEFAULT_COLOR_SCHEME_ID, StringPool.BLANK);

	public ColorScheme() {
	}

	public ColorScheme(String colorSchemeId) {
		super(colorSchemeId);
	}

	public ColorScheme(String colorSchemeId, String settings) {
		super(colorSchemeId, settings);

		setSettings(settings);
	}

	public String getName() {
		return _name;
	}

	public void setName(String name) {
		_name = name;
	}

	public String getSettings() {
		return PropertiesUtil.toString(_settingsProperties);
	}

	public void setSettings(String settings) {
		_settingsProperties.clear();

		try {
			PropertiesUtil.load(_settingsProperties, settings);
			PropertiesUtil.trimKeys(_settingsProperties);
		}
		catch (IOException ioe) {
			_log.error(ioe);
		}

		super.setSettings(settings);
	}

	public Properties getSettingsProperties() {
		return _settingsProperties;
	}

	public void setSettingsProperties(Properties settingsProperties) {
		_settingsProperties = settingsProperties;
	}

	public String getSetting(String key) {
		return _settingsProperties.getProperty(key);
	}

	public String getBodyBg() {
		return getSetting(BODY_BG);
	}

	public String getLayoutBg() {
		return getSetting(LAYOUT_BG);
	}

	public String getLayoutText() {
		return getSetting(LAYOUT_TEXT);
	}

	public String getLayoutTabBg() {
		return getSetting(LAYOUT_TAB_BG);
	}

	public String getLayoutTabText() {
		return getSetting(LAYOUT_TAB_TEXT);
	}

	public String getLayoutTabSelectedBg() {
		return getSetting(LAYOUT_TAB_SELECTED_BG);
	}

	public String getLayoutTabSelectedText() {
		return getSetting(LAYOUT_TAB_SELECTED_TEXT);
	}

	public String getPortletTitleBg() {
		return getSetting(PORTLET_TITLE_BG);
	}

	public String getPortletTitleText() {
		return getSetting(PORTLET_TITLE_TEXT);
	}

	public String getPortletMenuBg() {
		return getSetting(PORTLET_MENU_BG);
	}

	public String getPortletMenuText() {
		return getSetting(PORTLET_MENU_TEXT);
	}

	public String getPortletBg() {
		return getSetting(PORTLET_BG);
	}

	public String getPortletFont() {
		return getSetting(PORTLET_FONT);
	}

	public String getPortletFontDim() {
		return getSetting(PORTLET_FONT_DIM);
	}

	public String getPortletMsgStatus() {
		return getSetting(PORTLET_MSG_STATUS);
	}

	public String getPortletMsgInfo() {
		return getSetting(PORTLET_MSG_INFO);
	}

	public String getPortletMsgError() {
		return getSetting(PORTLET_MSG_ERROR);
	}

	public String getPortletMsgAlert() {
		return getSetting(PORTLET_MSG_ALERT);
	}

	public String getPortletMsgSuccess() {
		return getSetting(PORTLET_MSG_SUCCESS);
	}

	public String getPortletSectionHeader() {
		return getSetting(PORTLET_SECTION_HEADER);
	}

	public String getPortletSectionHeaderBg() {
		return getSetting(PORTLET_SECTION_HEADER_BG);
	}

	public String getPortletSectionSubheader() {
		return getSetting(PORTLET_SECTION_SUBHEADER);
	}

	public String getPortletSectionSubheaderBg() {
		return getSetting(PORTLET_SECTION_SUBHEADER_BG);
	}

	public String getPortletSectionBody() {
		return getSetting(PORTLET_SECTION_BODY);
	}

	public String getPortletSectionBodyBg() {
		return getSetting(PORTLET_SECTION_BODY_BG);
	}

	public String getPortletSectionBodyHover() {
		return getSetting(PORTLET_SECTION_BODY_HOVER);
	}

	public String getPortletSectionBodyHoverBg() {
		return getSetting(PORTLET_SECTION_BODY_HOVER_BG);
	}

	public String getPortletSectionAlternate() {
		return getSetting(PORTLET_SECTION_ALTERNATE);
	}

	public String getPortletSectionAlternateBg() {
		return getSetting(PORTLET_SECTION_ALTERNATE_BG);
	}

	public String getPortletSectionAlternateHover() {
		return getSetting(PORTLET_SECTION_ALTERNATE_HOVER);
	}

	public String getPortletSectionAlternateHoverBg() {
		return getSetting(PORTLET_SECTION_ALTERNATE_HOVER_BG);
	}

	public String getPortletSectionSelected() {
		return getSetting(PORTLET_SECTION_SELECTED);
	}

	public String getPortletSectionSelectedBg() {
		return getSetting(PORTLET_SECTION_SELECTED_BG);
	}

	public String getPortletSectionSelectedHover() {
		return getSetting(PORTLET_SECTION_SELECTED_HOVER);
	}

	public String getPortletSectionSelectedHoverBg() {
		return getSetting(PORTLET_SECTION_SELECTED_HOVER_BG);
	}

	private static final Log _log = LogFactory.getLog(ColorScheme.class);

	private Properties _settingsProperties = new NullSafeProperties();
	private String _name;

}