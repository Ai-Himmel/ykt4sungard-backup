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

package com.liferay.portal.service.impl;

import com.liferay.portal.SystemException;
import com.liferay.portal.model.ColorScheme;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.Theme;
import com.liferay.portal.service.spring.ThemeService;
import com.liferay.portal.util.EntityResolver;
import com.liferay.portal.util.ReleaseInfo;
import com.liferay.util.CollectionFactory;
import com.liferay.util.GetterUtil;
import com.liferay.util.ListUtil;
import com.liferay.util.NullSafeProperties;
import com.liferay.util.PropertiesUtil;
import com.liferay.util.SimpleCachePool;

import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Properties;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ThemeServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ThemeServiceImpl extends PrincipalBean implements ThemeService {

	// Business methods

	public Theme getTheme(String themeId) throws SystemException {
		Theme theme = (Theme)_getThemesPool().get(themeId);

		if (theme == null) {
			theme = (Theme)_getThemesPool().get(Theme.DEFAULT_THEME_ID);
		}

		return theme;
	}

	public List getThemes() {
		List themes = ListUtil.fromCollection(_getThemesPool().values());

		Collections.sort(themes);

		return themes;
	}

	public List init(String[] xmls) {
		return init(null, xmls);
	}

	public List init(String servletContextName, String[] xmls) {
		List themeIds = new ArrayList();

		Map themesPool = _getThemesPool();

		try {
			for (int i = 0; i < xmls.length; i++) {
				Iterator itr = _readThemes(
					servletContextName, xmls[i], themesPool).iterator();

				while (itr.hasNext()) {
					String themeId = (String)itr.next();

					if (!themeIds.contains(themeId)) {
						themeIds.add(themeId);
					}
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return themeIds;
	}

	public void uninstallTheme(String themeId) {
		_getThemesPool().remove(themeId);
	}

	// Private methods

	private Map _getThemesPool() {
		String themesPoolKey =
			ColorSchemeServiceImpl.class.getName() + ".THEMES";

		Map themesPool = (Map)SimpleCachePool.get(themesPoolKey);

		if (themesPool == null) {
			themesPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(themesPoolKey, themesPool);
		}

		return themesPool;
	}

	private void _readColorSchemes(Element theme, Map colorSchemesPool)
		throws IOException {

		Iterator itr = theme.elements("color-scheme").iterator();

		while (itr.hasNext()) {
			Element colorScheme = (Element)itr.next();

			String id = colorScheme.attributeValue("id");
			String name = colorScheme.attributeValue("name");
			String settings = colorScheme.getText();

			ColorScheme colorSchemeModel =
				(ColorScheme)colorSchemesPool.get(id);

			if (colorSchemeModel == null) {
				colorSchemeModel = new ColorScheme(id, settings);
			}
			else {
				Properties p = new NullSafeProperties();

				PropertiesUtil.load(p, settings);
				PropertiesUtil.trimKeys(p);

				PropertiesUtil.merge(
					colorSchemeModel.getSettingsProperties(), p);
			}

			colorSchemeModel.setName(GetterUtil.get(
				name, colorSchemeModel.getName()));

			colorSchemesPool.put(id, colorSchemeModel);
		}
	}

	private Set _readThemes(
			String servletContextName, String xml, Map themesPool)
		throws DocumentException, IOException {

		Set themeIds = new HashSet();

		if (xml == null) {
			return themeIds;
		}

		SAXReader reader = new SAXReader(true);
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		Set compatibleVersions = new HashSet();

		Element compatibilityEl = root.element("compatibility");

		if (compatibilityEl != null) {
			Iterator itr = compatibilityEl.elements("version").iterator();

			while (itr.hasNext()) {
				Element versionEl = (Element)itr.next();

				String version = versionEl.getTextTrim();

				compatibleVersions.add(version);
			}
		}

		if (!compatibleVersions.contains(ReleaseInfo.getVersion())) {
			_log.error(
				"Themes in this WAR are not compatible with " +
					ReleaseInfo.getServerInfo());

			return themeIds;
		}

		Iterator itr1 = root.elements("theme").iterator();

		while (itr1.hasNext()) {
			Element theme = (Element)itr1.next();

			String themeId = theme.attributeValue("id");
			if (servletContextName != null) {
				themeId =
					themeId + Portlet.WAR_SEPARATOR + servletContextName;
			}

			themeIds.add(themeId);

			Theme themeModel = (Theme)themesPool.get(themeId);

			if (themeModel == null) {
				themeModel = new Theme(themeId);

				themesPool.put(themeId, themeModel);
			}

			if (servletContextName != null) {
				themeModel.setServletContextName(servletContextName);
			}

			themeModel.setName(GetterUtil.get(
				theme.attributeValue("name"),
				themeModel.getName()));
			themeModel.setRootPath(GetterUtil.get(
				theme.elementText("root-path"),
				themeModel.getRootPath()));
			themeModel.setTemplatesPath(GetterUtil.get(
				theme.elementText("templates-path"),
				themeModel.getTemplatesPath()));
			themeModel.setImagesPath(GetterUtil.get(
				theme.elementText("images-path"),
				themeModel.getImagesPath()));
			themeModel.setTemplateExtension(GetterUtil.get(
				theme.elementText("template-extension"),
				themeModel.getTemplateExtension()));

			Element settingsEl = theme.element("settings");

			if (settingsEl != null) {
				Iterator itr2 = settingsEl.elements("setting").iterator();

				while (itr2.hasNext()) {
					Element settingEl = (Element)itr2.next();

					String key = settingEl.attributeValue("key");
					String value = settingEl.attributeValue("value");

					themeModel.setSetting(key, value);
				}
			}

			_readColorSchemes(theme, themeModel.getColorSchemesMap());
			_readColorSchemes(theme, themeModel.getColorSchemesMap());
		}

		return themeIds;
	}

	private static final Log _log = LogFactory.getLog(ThemeServiceImpl.class);

}