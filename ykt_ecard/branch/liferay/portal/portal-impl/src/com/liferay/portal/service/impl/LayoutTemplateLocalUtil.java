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

package com.liferay.portal.service.impl;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ObjectValuePair;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.LayoutTemplate;
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.model.impl.LayoutTemplateImpl;
import com.liferay.portal.service.PluginSettingLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.layoutconfiguration.util.velocity.InitColumnProcessor;
import com.liferay.util.Http;
import com.liferay.util.ListUtil;

import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.servlet.ServletContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.app.Velocity;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;

/**
 * <a href="LayoutTemplateLocalUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ivica Cardic
 * @author Jorge Ferrer
 *
*/
public class LayoutTemplateLocalUtil {

	public static String getContent(
			String layoutTemplateId, boolean standard, String themeId)
		throws SystemException {

		LayoutTemplate layoutTemplate = getLayoutTemplate(
			layoutTemplateId, standard, themeId);

		if (layoutTemplate == null) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Layout template " + layoutTemplateId + " does not exist");
			}

			String defaultUserLayoutTemplateId = PropsUtil.get(
				PropsUtil.DEFAULT_USER_LAYOUT_TEMPLATE_ID);

			layoutTemplate = getLayoutTemplate(
				defaultUserLayoutTemplateId, standard, themeId);

			if (layoutTemplate == null) {
				_log.error(
					"Layout template " + layoutTemplateId +
						" and default user layout template " +
							defaultUserLayoutTemplateId + " does not exist");

				return StringPool.BLANK;
			}
		}

		if (PropsValues.LAYOUT_TEMPLATE_CACHE_ENABLED) {
			return layoutTemplate.getContent();
		}
		else {
			try {
				return layoutTemplate.getUncachedContent();
			}
			catch (IOException ioe) {
				throw new SystemException(ioe);
			}
		}
	}

	public static LayoutTemplate getLayoutTemplate(
		String layoutTemplateId, boolean standard, String themeId) {

		if (Validator.isNull(layoutTemplateId)) {
			return null;
		}

		LayoutTemplate layoutTemplate = null;

		if (themeId != null) {
			if (standard) {
				layoutTemplate = (LayoutTemplate)_getThemesStandard(
					themeId).get(layoutTemplateId);
			}
			else {
				layoutTemplate = (LayoutTemplate)_getThemesCustom(
					themeId).get(layoutTemplateId);
			}

			if (layoutTemplate != null) {
				return layoutTemplate;
			}
		}

		if (standard) {
			layoutTemplate =
				(LayoutTemplate)_warStandard.get(layoutTemplateId);

			if (layoutTemplate == null) {
				layoutTemplate =
					(LayoutTemplate)_portalStandard.get(layoutTemplateId);
			}
		}
		else {
			layoutTemplate =
				(LayoutTemplate)_warCustom.get(layoutTemplateId);

			if (layoutTemplate == null) {
				layoutTemplate =
					(LayoutTemplate)_portalCustom.get(layoutTemplateId);
			}
		}

		return layoutTemplate;
	}

	public static List getLayoutTemplates() {
		List customLayoutTemplates = new ArrayList(
			_portalCustom.size() + _warCustom.size());

		customLayoutTemplates.addAll(
			ListUtil.fromCollection(_portalCustom.values()));

		customLayoutTemplates.addAll(
			ListUtil.fromCollection(_warCustom.values()));

		return customLayoutTemplates;
	}

	public static List getLayoutTemplates(String themeId) {
		Map _themesCustom = _getThemesCustom(themeId);

		List customLayoutTemplates = new ArrayList(
			_portalCustom.size() + _warCustom.size() + _themesCustom.size());

		Iterator itr = _portalCustom.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String layoutTemplateId = (String)entry.getKey();
			LayoutTemplate layoutTemplate = (LayoutTemplate)entry.getValue();

			if (_themesCustom.containsKey(layoutTemplateId)) {
				customLayoutTemplates.add(_themesCustom.get(layoutTemplateId));
			}
			else if (_warCustom.containsKey(layoutTemplateId)) {
				customLayoutTemplates.add(_warCustom.get(layoutTemplateId));
			}
			else {
				customLayoutTemplates.add(layoutTemplate);
			}
		}

		itr = _warCustom.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String layoutTemplateId = (String)entry.getKey();

			if (!_portalCustom.containsKey(layoutTemplateId) &&
				!_themesCustom.containsKey(layoutTemplateId)) {

				customLayoutTemplates.add(_warCustom.get(layoutTemplateId));
			}
		}

		itr = _themesCustom.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			String layoutTemplateId = (String)entry.getKey();

			if (!_portalCustom.containsKey(layoutTemplateId) &&
				!_warCustom.containsKey(layoutTemplateId)) {

				customLayoutTemplates.add(_themesCustom.get(layoutTemplateId));
			}
		}

		return customLayoutTemplates;
	}

	public static String getWapContent(
			String layoutTemplateId, boolean standard, String themeId)
		throws SystemException {

		LayoutTemplate layoutTemplate = getLayoutTemplate(
			layoutTemplateId, standard, themeId);

		if (layoutTemplate == null) {
			if (_log.isWarnEnabled()) {
				_log.warn(
					"Layout template " + layoutTemplateId + " does not exist");
			}

			String defaultUserLayoutTemplateId = PropsUtil.get(
				PropsUtil.DEFAULT_USER_LAYOUT_TEMPLATE_ID);

			layoutTemplate = getLayoutTemplate(
				defaultUserLayoutTemplateId, standard, themeId);

			if (layoutTemplate == null) {
				_log.error(
					"Layout template " + layoutTemplateId +
						" and default user layout template " +
							defaultUserLayoutTemplateId + " does not exist");

				return StringPool.BLANK;
			}
		}

		if (GetterUtil.getBoolean(PropsUtil.get(
				PropsUtil.LAYOUT_TEMPLATE_CACHE_ENABLED))) {

			return layoutTemplate.getWapContent();
		}
		else {
			try {
				return layoutTemplate.getUncachedWapContent();
			}
			catch (IOException ioe) {
				throw new SystemException(ioe);
			}
		}
	}

	public static List init(
		ServletContext ctx, String[] xmls, PluginPackage pluginPackage) {

		return init(null, ctx, xmls, pluginPackage);
	}

	public static List init(
		String servletContextName, ServletContext ctx, String[] xmls,
		PluginPackage pluginPackage) {

		List layoutTemplateIds = new ArrayList();

		try {
			for (int i = 0; i < xmls.length; i++) {
				Iterator itr = _readLayoutTemplates(
					servletContextName, ctx, xmls[i], pluginPackage).iterator();

				while (itr.hasNext()) {
					ObjectValuePair ovp = (ObjectValuePair)itr.next();

					if (!layoutTemplateIds.contains(ovp)) {
						layoutTemplateIds.add(ovp);
					}
				}
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return layoutTemplateIds;
	}

	public static void readLayoutTemplate(
			String servletContextName, ServletContext ctx,
			Set layoutTemplateIds, Element el, boolean standard, String themeId,
			PluginPackage pluginPackage)
		throws IOException {

		Map layoutTemplates = null;

		if (themeId != null) {
			if (standard) {
				layoutTemplates = _getThemesStandard(themeId);
			}
			else {
				layoutTemplates = _getThemesCustom(themeId);
			}
		}
		else if (servletContextName != null) {
			if (standard) {
				layoutTemplates = _warStandard;
			}
			else {
				layoutTemplates = _warCustom;
			}
		}
		else {
			if (standard) {
				layoutTemplates = _portalStandard;
			}
			else {
				layoutTemplates = _portalCustom;
			}
		}

		Iterator itr = el.elements("layout-template").iterator();

		while (itr.hasNext()) {
			Element layoutTemplate = (Element)itr.next();

			String layoutTemplateId = layoutTemplate.attributeValue("id");

			if (layoutTemplateIds != null) {
				ObjectValuePair ovp = new ObjectValuePair(
					layoutTemplateId, Boolean.valueOf(standard));

				layoutTemplateIds.add(ovp);
			}

			LayoutTemplate layoutTemplateModel =
				(LayoutTemplate)layoutTemplates.get(layoutTemplateId);

			if (layoutTemplateModel == null) {
				layoutTemplateModel = new LayoutTemplateImpl(layoutTemplateId);

				layoutTemplates.put(layoutTemplateId, layoutTemplateModel);
			}

			PluginSetting pluginSetting =
				PluginSettingLocalServiceUtil.getDefaultPluginSetting();

			layoutTemplateModel.setPluginPackage(pluginPackage);
			layoutTemplateModel.setServletContext(ctx);

			if (servletContextName != null) {
				layoutTemplateModel.setServletContextName(servletContextName);
			}

			layoutTemplateModel.setStandard(standard);
			layoutTemplateModel.setName(GetterUtil.getString(
				layoutTemplate.attributeValue("name"),
				layoutTemplateModel.getName()));
			layoutTemplateModel.setTemplatePath(GetterUtil.getString(
				layoutTemplate.elementText("template-path"),
				layoutTemplateModel.getTemplatePath()));
			layoutTemplateModel.setWapTemplatePath(GetterUtil.getString(
				layoutTemplate.elementText("wap-template-path"),
				layoutTemplateModel.getWapTemplatePath()));
			layoutTemplateModel.setThumbnailPath(GetterUtil.getString(
				layoutTemplate.elementText("thumbnail-path"),
				layoutTemplateModel.getThumbnailPath()));

			String content = null;

			try {
				content = Http.URLtoString(ctx.getResource(
					layoutTemplateModel.getTemplatePath()));
			}
			catch (Exception e) {
				_log.error(
					"Unable to get content at template path " +
						layoutTemplateModel.getTemplatePath() + ": " +
							e.getMessage());
			}

			if (Validator.isNull(content)) {
				_log.error(
					"No content found at template path " +
						layoutTemplateModel.getTemplatePath());
			}
			else {
				layoutTemplateModel.setContent(content);
				layoutTemplateModel.setColumns(_getColumns(content));
			}

			if (Validator.isNull(layoutTemplateModel.getWapTemplatePath())) {
				_log.error(
					"The element wap-template-path is not defined for " +
						layoutTemplateId);
			}
			else {
				String wapContent = null;

				try {
					wapContent = Http.URLtoString(ctx.getResource(
						layoutTemplateModel.getWapTemplatePath()));
				}
				catch (Exception e) {
					_log.error(
						"Unable to get content at WAP template path " +
							layoutTemplateModel.getWapTemplatePath() + ": " +
								e.getMessage());
				}

				if (Validator.isNull(wapContent)) {
					_log.error(
						"No content found at WAP template path " +
							layoutTemplateModel.getWapTemplatePath());
				}
				else {
					layoutTemplateModel.setWapContent(wapContent);
				}
			}

			Element rolesEl = layoutTemplate.element("roles");

			if (rolesEl != null) {
				Iterator itr2 = rolesEl.elements("role-name").iterator();

				while (itr2.hasNext()) {
					Element roleNameEl = (Element)itr2.next();

					pluginSetting.addRole(roleNameEl.getText());
				}
			}

			layoutTemplateModel.setDefaultPluginSetting(pluginSetting);
		}
	}

	public static void uninstallLayoutTemplate(
		String layoutTemplateId, boolean standard) {

		if (standard) {
			_warStandard.remove(layoutTemplateId);
		}
		else {
			_warCustom.remove(layoutTemplateId);
		}
	}

	public static void uninstallLayoutTemplates(String themeId) {
		_getThemesStandard(themeId).clear();
		_getThemesCustom(themeId).clear();
	}

	private static List _getColumns(String content) {
		try {
			InitColumnProcessor processor = new InitColumnProcessor();

			VelocityContext context = new VelocityContext();

			context.put("processor", processor);

			Velocity.evaluate(
				context, new PrintWriter(new StringWriter()),
				LayoutTemplateLocalUtil.class.getName(), content);

			List columns = processor.getColumns();

			Collections.sort(columns);

			return columns;
		}
		catch (Exception e) {
			_log.error(e);

			return new ArrayList();
		}
	}

	private static Set _readLayoutTemplates(
			String servletContextName, ServletContext ctx, String xml,
			PluginPackage pluginPackage)
		throws DocumentException, IOException {

		Set layoutTemplateIds = new HashSet();

		if (xml == null) {
			return layoutTemplateIds;
		}

		Document doc = PortalUtil.readDocumentFromXML(xml, true);

		Element root = doc.getRootElement();

		Element standardEl = root.element("standard");

		if (standardEl != null) {
			readLayoutTemplate(
				servletContextName, ctx, layoutTemplateIds, standardEl, true,
				null, pluginPackage);
		}

		Element customEl = root.element("custom");

		if (customEl != null) {
			readLayoutTemplate(
				servletContextName, ctx, layoutTemplateIds, customEl, false,
				null, pluginPackage);
		}

		return layoutTemplateIds;
	}

	private static Map _getThemesCustom(String themeId) {
		String key = themeId + _CUSTOM_SEPARATOR;

		Map layoutTemplates = (Map)_themes.get(key);

		if (layoutTemplates == null) {
			layoutTemplates = new LinkedHashMap();

			_themes.put(key, layoutTemplates);
		}

		return layoutTemplates;
	}

	private static Map _getThemesStandard(String themeId) {
		String key = themeId + _STANDARD_SEPARATOR;

		Map layoutTemplates = (Map)_themes.get(key);

		if (layoutTemplates == null) {
			layoutTemplates = new LinkedHashMap();

			_themes.put(key, layoutTemplates);
		}

		return layoutTemplates;
	}

	private static final String _STANDARD_SEPARATOR = "_STANDARD_";

	private static final String _CUSTOM_SEPARATOR = "_CUSTOM_";

	private static Log _log = LogFactory.getLog(LayoutTemplateLocalUtil.class);

	private static Map _portalStandard = new LinkedHashMap();
	private static Map _portalCustom = new LinkedHashMap();

	private static Map _warStandard = new LinkedHashMap();
	private static Map _warCustom = new LinkedHashMap();

	private static Map _themes = new LinkedHashMap();

}