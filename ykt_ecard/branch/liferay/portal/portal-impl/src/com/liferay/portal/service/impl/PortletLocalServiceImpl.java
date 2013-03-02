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

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.LocaleUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletCategory;
import com.liferay.portal.model.PortletInfo;
import com.liferay.portal.model.impl.CompanyImpl;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.base.PortletLocalServiceBaseImpl;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsValues;
import com.liferay.portlet.PortletPreferencesSerializer;
import com.liferay.util.CollectionFactory;
import com.liferay.util.ListUtil;

import java.io.IOException;
import java.io.StringWriter;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletMode;
import javax.portlet.PreferencesValidator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.XMLWriter;

/**
 * <a href="PortletLocalServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 * @author Raymond Augé
 *
 */
public class PortletLocalServiceImpl extends PortletLocalServiceBaseImpl {

	public void destroyPortlet(Portlet portlet) {
		Map portletsPool = _getPortletsPool();

		portletsPool.remove(portlet.getRootPortletId());

		_clearCaches();
	}

	public PortletCategory getEARDisplay(String xml) throws SystemException {
		try {
			return _readLiferayDisplayXML(xml);
		}
		catch (DocumentException de) {
			throw new SystemException(de);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	public PortletCategory getWARDisplay(String servletContextName, String xml)
		throws SystemException {

		try {
			return _readLiferayDisplayXML(servletContextName, xml);
		}
		catch (DocumentException de) {
			throw new SystemException(de);
		}
		catch (IOException ioe) {
			throw new SystemException(ioe);
		}
	}

	public List getFriendlyURLMappers() {
		return _getFriendlyURLMappers();
	}

	public Portlet getPortletById(long companyId, String portletId)
		throws SystemException {

		portletId = PortalUtil.getJsSafePortletId(portletId);

		Portlet portlet = null;

		Map companyPortletsPool = _getPortletsPool(companyId);

		String rootPortletId = PortletImpl.getRootPortletId(portletId);

		if (portletId.equals(rootPortletId)) {
			portlet = (Portlet)companyPortletsPool.get(portletId);
		}
		else {
			portlet = (Portlet)companyPortletsPool.get(rootPortletId);

			if (portlet != null) {
				portlet = portlet.getClonedInstance(portletId);
			}
		}

		if ((portlet == null) &&
			(!portletId.equals(PortletKeys.LIFERAY_PORTAL))) {

			if (_log.isWarnEnabled()) {
				_log.warn(
					"Portlet not found for " + companyId + " " + portletId);
			}
		}

		return portlet;
	}

	public Portlet getPortletByStrutsPath(long companyId, String strutsPath)
		throws SystemException {

		return getPortletById(companyId, _getPortletId(strutsPath));
	}

	public List getPortlets() {
		Map portletsPool = _getPortletsPool();

		return ListUtil.fromCollection(portletsPool.values());
	}

	public List getPortlets(long companyId) throws SystemException {
		return getPortlets(companyId, true, true);
	}

	public List getPortlets(
			long companyId, boolean showSystem, boolean showPortal)
		throws SystemException {

		Map portletsPool = _getPortletsPool(companyId);

		List portlets = ListUtil.fromCollection(portletsPool.values());

		if (!showSystem || !showPortal) {
			Iterator itr = portlets.iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				if (showPortal &&
					portlet.getPortletId().equals(PortletKeys.PORTAL)) {

				}
				else if (!showPortal &&
						 portlet.getPortletId().equals(PortletKeys.PORTAL)) {

					itr.remove();
				}
				else if (!showSystem && portlet.isSystem()) {
					itr.remove();
				}
			}
		}

		return portlets;
	}

	public boolean hasPortlet(long companyId, String portletId)
		throws SystemException {

		portletId = PortalUtil.getJsSafePortletId(portletId);

		Portlet portlet = null;

		Map companyPortletsPool = _getPortletsPool(companyId);

		String rootPortletId = PortletImpl.getRootPortletId(portletId);

		if (portletId.equals(rootPortletId)) {
			portlet = (Portlet)companyPortletsPool.get(portletId);
		}
		else {
			portlet = (Portlet)companyPortletsPool.get(rootPortletId);
		}

		if (portlet == null) {
			return false;
		}
		else {
			return true;
		}
	}

	public void initEAR(String[] xmls, PluginPackage pluginPackage) {
		Map portletsPool = _getPortletsPool();

		try {
			List servletURLPatterns = _readWebXML(xmls[4]);

			Set portletIds = _readPortletXML(
				xmls[0], portletsPool, servletURLPatterns, pluginPackage);

			portletIds.addAll(_readPortletXML(
				xmls[1], portletsPool, servletURLPatterns, pluginPackage));

			Set liferayPortletIds =
				_readLiferayPortletXML(xmls[2], portletsPool);

			liferayPortletIds.addAll(
				_readLiferayPortletXML(xmls[3], portletsPool));

			// Check for missing entries in liferay-portlet.xml

			Iterator itr = portletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				if (_log.isWarnEnabled() &&
					!liferayPortletIds.contains(portletId)) {

					_log.warn(
						"Portlet with the name " + portletId +
							" is described in portlet.xml but does not " +
								"have a matching entry in liferay-portlet.xml");
				}
			}

			// Check for missing entries in portlet.xml

			itr = liferayPortletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				if (_log.isWarnEnabled() && !portletIds.contains(portletId)) {
					_log.warn(
						"Portlet with the name " + portletId +
							" is described in liferay-portlet.xml but does " +
								"not have a matching entry in portlet.xml");
				}
			}

			// Remove portlets that should not be included

			itr = portletsPool.entrySet().iterator();

			while (itr.hasNext()) {
				Map.Entry entry = (Map.Entry)itr.next();

				Portlet portletModel = (Portlet)entry.getValue();

				if (!portletModel.getPortletId().equals(PortletKeys.ADMIN) &&
					!portletModel.getPortletId().equals(
						PortletKeys.MY_ACCOUNT) &&
					!portletModel.isInclude()) {

					itr.remove();
				}
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	public List initWAR(
		String servletContextName, String[] xmls, PluginPackage pluginPackage) {

		List portlets = new ArrayList();

		Map portletsPool = _getPortletsPool();

		try {
			List servletURLPatterns = _readWebXML(xmls[3]);

			Set portletIds = _readPortletXML(
				servletContextName, xmls[0], portletsPool, servletURLPatterns,
				pluginPackage);

			portletIds.addAll(_readPortletXML(
				servletContextName, xmls[1], portletsPool, servletURLPatterns,
				pluginPackage));

			Set liferayPortletIds = _readLiferayPortletXML(
				servletContextName, xmls[2], portletsPool);

			// Check for missing entries in liferay-portlet.xml

			Iterator itr = portletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				if (_log.isWarnEnabled() &&
					!liferayPortletIds.contains(portletId)) {

					_log.warn(
						"Portlet with the name " + portletId +
							" is described in portlet.xml but does not " +
								"have a matching entry in liferay-portlet.xml");
				}
			}

			// Check for missing entries in portlet.xml

			itr = liferayPortletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				if (_log.isWarnEnabled() && !portletIds.contains(portletId)) {
					_log.warn(
						"Portlet with the name " + portletId +
							" is described in liferay-portlet.xml but does " +
								"not have a matching entry in portlet.xml");
				}
			}

			// Return the new portlets

			itr = portletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				Portlet portlet = (Portlet)_getPortletsPool().get(portletId);

				portlets.add(portlet);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}

		_clearCaches();

		return portlets;
	}

	public Portlet updatePortlet(
			long companyId, String portletId, String roles, boolean active)
		throws PortalException, SystemException {

		portletId = PortalUtil.getJsSafePortletId(portletId);

		Portlet portlet = portletPersistence.fetchByC_P(companyId, portletId);

		if (portlet == null) {
			long id = counterLocalService.increment();

			portlet = portletPersistence.create(id);

			portlet.setCompanyId(companyId);
			portlet.setPortletId(portletId);
		}

		portlet.setRoles(roles);
		portlet.setActive(active);

		portletPersistence.update(portlet);

		portlet = getPortletById(companyId, portletId);

		portlet.setRoles(roles);
		portlet.setActive(active);

		return portlet;
	}

	private void _clearCaches() {

		// Refresh security path to portlet id mapping for all portlets

		_portletIdsByStrutsPath.clear();

		// Refresh company portlets

		_companyPortletsPool.clear();
	}

	private List _getFriendlyURLMappers() {
		List friendlyURLMappers = new ArrayList(
			_friendlyURLMapperPortlets.size());

		Iterator itr = _friendlyURLMapperPortlets.entrySet().iterator();

		while (itr.hasNext()) {
			Map.Entry entry = (Map.Entry)itr.next();

			Portlet portlet = (Portlet)entry.getValue();

			FriendlyURLMapper friendlyURLMapper =
				portlet.getFriendlyURLMapperInstance();

			if (friendlyURLMapper != null) {
				friendlyURLMappers.add(friendlyURLMapper);
			}
		}

		return friendlyURLMappers;
	}

	private String _getPortletId(String securityPath) throws SystemException {
		if (_portletIdsByStrutsPath.size() == 0) {
			Iterator itr = _getPortletsPool().values().iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				_portletIdsByStrutsPath.put(
					portlet.getStrutsPath(), portlet.getPortletId());
			}
		}

		String portletId = (String)_portletIdsByStrutsPath.get(securityPath);

		if (Validator.isNull(portletId)) {
			_log.error(
				"Struts path " + securityPath + " is not mapped to a portlet " +
					"in liferay-portlet.xml");
		}

		return portletId;
	}

	private Map _getPortletsPool() {
		return _portletsPool;
	}

	private Map _getPortletsPool(long companyId) throws SystemException {
		Long companyIdObj = new Long(companyId);

		Map portletsPool = (Map)_companyPortletsPool.get(companyIdObj);

		if (portletsPool == null) {
			portletsPool = CollectionFactory.getSyncHashMap();

			Map parentPortletsPool = _getPortletsPool();

			if (parentPortletsPool == null) {

				// The Upgrade scripts sometimes try to access portlet
				// preferences before the portal's been initialized. Return an
				// empty pool.

				return portletsPool;
			}

			Iterator itr = parentPortletsPool.values().iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)((Portlet)itr.next()).clone();

				portlet.setCompanyId(companyId);

				portletsPool.put(portlet.getPortletId(), portlet);
			}

			itr = portletPersistence.findByCompanyId(companyId).iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				Portlet portletModel =
					(Portlet)portletsPool.get(portlet.getPortletId());

				// Portlet may be null if it exists in the database but its
				// portlet WAR is not yet loaded

				if (portletModel != null) {
					portletModel.setPluginPackage(portlet.getPluginPackage());
					portletModel.setDefaultPluginSetting(
						portlet.getDefaultPluginSetting());
					portletModel.setRoles(portlet.getRoles());
					portletModel.setActive(portlet.getActive());
				}
			}

			_companyPortletsPool.put(companyIdObj, portletsPool);
		}

		return portletsPool;
	}

	private Set _readPortletXML(
			String xml, Map portletsPool, List servletURLPatterns,
			PluginPackage pluginPackage)
		throws DocumentException, IOException {

		return _readPortletXML(
			null, xml, portletsPool, servletURLPatterns, pluginPackage);
	}

	private Set _readPortletXML(
			String servletContextName, String xml, Map portletsPool,
			List servletURLPatterns, PluginPackage pluginPackage)
		throws DocumentException, IOException {

		Set portletIds = new HashSet();

		if (xml == null) {
			return portletIds;
		}

		Document doc = PortalUtil.readDocumentFromXML(xml);

		Element root = doc.getRootElement();

		Set userAttributes = new HashSet();

		Iterator itr1 = root.elements("user-attribute").iterator();

		while (itr1.hasNext()) {
			Element userAttribute = (Element)itr1.next();

			String name = userAttribute.elementText("name");

			userAttributes.add(name);
		}

		itr1 = root.elements("portlet").iterator();

		while (itr1.hasNext()) {
			Element portlet = (Element)itr1.next();

			String portletId = portlet.elementText("portlet-name");

			if (servletContextName != null) {
				portletId =
					portletId + PortletImpl.WAR_SEPARATOR + servletContextName;
			}

			portletId = PortalUtil.getJsSafePortletId(portletId);

			if (_log.isDebugEnabled()) {
				_log.debug("Reading portlet " + portletId);
			}

			portletIds.add(portletId);

			Portlet portletModel = (Portlet)portletsPool.get(portletId);

			if (portletModel == null) {
				portletModel = new PortletImpl(CompanyImpl.SYSTEM, portletId);

				portletsPool.put(portletId, portletModel);
			}

			portletModel.setPluginPackage(pluginPackage);

			if (servletContextName != null) {
				portletModel.setServletContextName(servletContextName);
			}

			if (servletURLPatterns != null) {
				portletModel.setServletURLPatterns(servletURLPatterns);
			}

			portletModel.setDisplayName(GetterUtil.getString(
				portlet.elementText("display-name"),
				portletModel.getDisplayName()));
			portletModel.setPortletClass(GetterUtil.getString(
				portlet.elementText("portlet-class")));

			Iterator itr2 = portlet.elements("init-param").iterator();

			while (itr2.hasNext()) {
				Element initParam = (Element)itr2.next();

				portletModel.getInitParams().put(
					initParam.elementText("name"),
					initParam.elementText("value"));
			}

			Element expirationCache = portlet.element("expiration-cache");

			if (expirationCache != null) {
				portletModel.setExpCache(new Integer(GetterUtil.getInteger(
					expirationCache.getText())));
			}

			itr2 = portlet.elements("supports").iterator();

			while (itr2.hasNext()) {
				Element supports = (Element)itr2.next();

				String mimeType = supports.elementText("mime-type");

				Set mimeTypeModes =
					(Set)portletModel.getPortletModes().get(mimeType);

				if (mimeTypeModes == null) {
					mimeTypeModes = new HashSet();

					portletModel.getPortletModes().put(mimeType, mimeTypeModes);
				}

				mimeTypeModes.add(PortletMode.VIEW.toString().toLowerCase());

				Iterator itr3 = supports.elements("portlet-mode").iterator();

				while (itr3.hasNext()) {
					Element portletMode = (Element)itr3.next();

					mimeTypeModes.add(portletMode.getTextTrim().toLowerCase());
				}
			}

			Set supportedLocales = portletModel.getSupportedLocales();

			supportedLocales.add(
				LocaleUtil.toLanguageId(LocaleUtil.getDefault()));

			itr2 = portlet.elements("supported-locale").iterator();

			while (itr2.hasNext()) {
				Element supportedLocaleEl = (Element)itr2.next();

				String supportedLocale = supportedLocaleEl.getText();

				supportedLocales.add(supportedLocale);
			}

			portletModel.setResourceBundle(
				portlet.elementText("resource-bundle"));

			Element portletInfo = portlet.element("portlet-info");

			String portletInfoTitle = null;
			String portletInfoShortTitle = null;
			String portletInfoKeyWords = null;

			if (portletInfo != null) {
				portletInfoTitle = portletInfo.elementText("title");
				portletInfoShortTitle = portletInfo.elementText("short-title");
				portletInfoKeyWords = portletInfo.elementText("keywords");
			}

			portletModel.setPortletInfo(new PortletInfo(
				portletInfoTitle, portletInfoShortTitle, portletInfoKeyWords));

			Element portletPreferences = portlet.element("portlet-preferences");

			String defaultPreferences = null;
			String prefsValidator = null;

			if (portletPreferences != null) {
				Element prefsValidatorEl =
					portletPreferences.element("preferences-validator");

				if (prefsValidatorEl != null) {
					prefsValidator = prefsValidatorEl.getText();

					portletPreferences.remove(prefsValidatorEl);
				}

				StringWriter sw = new StringWriter();

				XMLWriter writer = new XMLWriter(
					sw, OutputFormat.createCompactFormat());

				writer.write(portletPreferences);

				defaultPreferences = sw.toString();
			}

			portletModel.setDefaultPreferences(defaultPreferences);
			portletModel.setPreferencesValidator(prefsValidator);

			if (!portletModel.isWARFile() &&
				Validator.isNotNull(prefsValidator) &&
				PropsValues.PREFERENCE_VALIDATE_ON_STARTUP) {

				try {
					PreferencesValidator prefsValidatorObj =
						PortalUtil.getPreferencesValidator(portletModel);

					prefsValidatorObj.validate(
						PortletPreferencesSerializer.fromDefaultXML(
							defaultPreferences));
				}
				catch (Exception e) {
					if (_log.isWarnEnabled()) {
						_log.warn(
							"Portlet with the name " + portletId +
								" does not have valid default preferences");
					}
				}
			}

			Set unlikedRoles = portletModel.getUnlinkedRoles();

			itr2 = portlet.elements("security-role-ref").iterator();

			while (itr2.hasNext()) {
				Element role = (Element)itr2.next();

				unlikedRoles.add(role.elementText("role-name"));
			}

			portletModel.getUserAttributes().addAll(userAttributes);
		}

		return portletIds;
	}

	private void _readLiferayDisplay(
		String servletContextName, Element el, PortletCategory portletCategory,
		Set portletIds) {

		Iterator itr1 = el.elements("category").iterator();

		while (itr1.hasNext()) {
			Element category = (Element)itr1.next();

			String name = category.attributeValue("name");

			PortletCategory curPortletCategory = new PortletCategory(name);

			portletCategory.addCategory(curPortletCategory);

			Set curPortletIds = curPortletCategory.getPortlets();

			Iterator itr2 = category.elements("portlet").iterator();

			while (itr2.hasNext()) {
				Element portlet = (Element)itr2.next();

				String portletId = portlet.attributeValue("id");

				if (servletContextName != null) {
					portletId =
						portletId + PortletImpl.WAR_SEPARATOR +
							servletContextName;
				}

				portletId = PortalUtil.getJsSafePortletId(portletId);

				portletIds.add(portletId);
				curPortletIds.add(portletId);
			}

			_readLiferayDisplay(
				servletContextName, category, curPortletCategory, portletIds);
		}
	}

	private PortletCategory _readLiferayDisplayXML(String xml)
		throws DocumentException, IOException {

		return _readLiferayDisplayXML(null, xml);
	}

	private PortletCategory _readLiferayDisplayXML(
			String servletContextName, String xml)
		throws DocumentException, IOException {

		PortletCategory portletCategory = new PortletCategory();

		if (xml == null) {
			xml = ContentUtil.get(
				"com/liferay/portal/deploy/dependencies/liferay-display.xml");
		}

		Document doc = PortalUtil.readDocumentFromXML(xml, true);

		Element root = doc.getRootElement();

		Set portletIds = new HashSet();

		_readLiferayDisplay(
			servletContextName, root, portletCategory, portletIds);

		// Portlets that do not belong to any categories should default to the
		// Undefined category

		Set undefinedPortletIds = new HashSet();

		Iterator itr = _getPortletsPool().values().iterator();

		while (itr.hasNext()) {
			Portlet portlet = (Portlet)itr.next();

			String portletId = portlet.getPortletId();

			if ((servletContextName != null) && (portlet.isWARFile()) &&
				(portletId.endsWith(
					PortletImpl.WAR_SEPARATOR +
						PortalUtil.getJsSafePortletId(servletContextName)) &&
				(!portletIds.contains(portletId)))) {

				undefinedPortletIds.add(portletId);
			}
			else if ((servletContextName == null) && (!portlet.isWARFile()) &&
					 (portletId.indexOf(PortletImpl.WAR_SEPARATOR) == -1) &&
					 (!portletIds.contains(portletId))) {

				undefinedPortletIds.add(portletId);
			}
		}

		if (undefinedPortletIds.size() > 0) {
			PortletCategory undefinedCategory =
				new PortletCategory("category.undefined");

			portletCategory.addCategory(undefinedCategory);

			undefinedCategory.getPortlets().addAll(undefinedPortletIds);
		}

		return portletCategory;
	}

	private Set _readLiferayPortletXML(String xml, Map portletsPool)
		throws DocumentException, IOException {

		return _readLiferayPortletXML(null, xml, portletsPool);
	}

	private Set _readLiferayPortletXML(
			String servletContextName, String xml, Map portletsPool)
		throws DocumentException, IOException {

		Set liferayPortletIds = new HashSet();

		if (xml == null) {
			return liferayPortletIds;
		}

		Document doc = PortalUtil.readDocumentFromXML(xml, true);

		Element root = doc.getRootElement();

		Map roleMappers = new HashMap();

		Iterator itr1 = root.elements("role-mapper").iterator();

		while (itr1.hasNext()) {
			Element roleMapper = (Element)itr1.next();

			String roleName = roleMapper.elementText("role-name");
			String roleLink = roleMapper.elementText("role-link");

			roleMappers.put(roleName, roleLink);
		}

		Map customUserAttributes = new HashMap();

		itr1 = root.elements("custom-user-attribute").iterator();

		while (itr1.hasNext()) {
			Element customUserAttribute = (Element)itr1.next();

			String customClass = customUserAttribute.elementText(
				"custom-class");

			Iterator itr2 = customUserAttribute.elements("name").iterator();

			while (itr2.hasNext()) {
				Element nameEl = (Element)itr2.next();

				String name = nameEl.getText();

				customUserAttributes.put(name, customClass);
			}
		}

		itr1 = root.elements("portlet").iterator();

		while (itr1.hasNext()) {
			Element portlet = (Element)itr1.next();

			String portletId = portlet.elementText("portlet-name");

			if (servletContextName != null) {
				portletId =
					portletId + PortletImpl.WAR_SEPARATOR + servletContextName;
			}

			portletId = PortalUtil.getJsSafePortletId(portletId);

			if (_log.isDebugEnabled()) {
				_log.debug("Reading portlet extension " + portletId);
			}

			liferayPortletIds.add(portletId);

			Portlet portletModel = (Portlet)portletsPool.get(portletId);

			if (portletModel != null) {
				portletModel.setIcon(GetterUtil.getString(
					portlet.elementText("icon"), portletModel.getIcon()));
				portletModel.setVirtualPath(GetterUtil.getString(
					portlet.elementText("virtual-path"),
					portletModel.getVirtualPath()));
				portletModel.setStrutsPath(GetterUtil.getString(
					portlet.elementText("struts-path"),
					portletModel.getStrutsPath()));

				if (Validator.isNotNull(
						portlet.elementText("configuration-path"))) {

					_log.error(
						"The configuration-path element is no longer " +
							"supported. Use configuration-action-class " +
								"instead.");
				}

				portletModel.setConfigurationActionClass(GetterUtil.getString(
					portlet.elementText("configuration-action-class"),
					portletModel.getConfigurationActionClass()));
				portletModel.setIndexerClass(GetterUtil.getString(
					portlet.elementText("indexer-class"),
					portletModel.getIndexerClass()));
				portletModel.setOpenSearchClass(GetterUtil.getString(
					portlet.elementText("open-search-class"),
					portletModel.getOpenSearchClass()));
				portletModel.setSchedulerClass(GetterUtil.getString(
					portlet.elementText("scheduler-class"),
					portletModel.getSchedulerClass()));
				portletModel.setPortletURLClass(GetterUtil.getString(
					portlet.elementText("portlet-url-class"),
					portletModel.getPortletURLClass()));

				portletModel.setFriendlyURLMapperClass(GetterUtil.getString(
					portlet.elementText("friendly-url-mapper-class"),
					portletModel.getFriendlyURLMapperClass()));

				if (Validator.isNull(
						portletModel.getFriendlyURLMapperClass())) {

					_friendlyURLMapperPortlets.remove(portletId);
				}
				else {
					_friendlyURLMapperPortlets.put(portletId, portletModel);
				}

				portletModel.setURLEncoderClass(GetterUtil.getString(
					portlet.elementText("url-encoder-class"),
					portletModel.getURLEncoderClass()));
				portletModel.setPortletDataHandlerClass(GetterUtil.getString(
					portlet.elementText("portlet-data-handler-class"),
					portletModel.getPortletDataHandlerClass()));
				portletModel.setPortletLayoutListenerClass(GetterUtil.getString(
					portlet.elementText("portlet-layout-listener-class"),
					portletModel.getPortletLayoutListenerClass()));
				portletModel.setActivityTrackerInterpreterClass(
					GetterUtil.getString(
						portlet.elementText(
							"activity-tracker-interpreter-class"),
							portletModel.getActivityTrackerInterpreterClass()));
				portletModel.setPopMessageListenerClass(GetterUtil.getString(
					portlet.elementText("pop-message-listener-class"),
					portletModel.getPopMessageListenerClass()));
				portletModel.setPreferencesCompanyWide(GetterUtil.getBoolean(
					portlet.elementText("preferences-company-wide"),
					portletModel.isPreferencesCompanyWide()));
				portletModel.setPreferencesUniquePerLayout(
					GetterUtil.getBoolean(
						portlet.elementText("preferences-unique-per-layout"),
						portletModel.isPreferencesUniquePerLayout()));
				portletModel.setPreferencesOwnedByGroup(GetterUtil.getBoolean(
					portlet.elementText("preferences-owned-by-group"),
					portletModel.isPreferencesOwnedByGroup()));
				portletModel.setUseDefaultTemplate(GetterUtil.getBoolean(
					portlet.elementText("use-default-template"),
					portletModel.isUseDefaultTemplate()));
				portletModel.setShowPortletAccessDenied(GetterUtil.getBoolean(
					portlet.elementText("show-portlet-access-denied"),
					portletModel.isShowPortletAccessDenied()));
				portletModel.setShowPortletInactive(GetterUtil.getBoolean(
					portlet.elementText("show-portlet-inactive"),
					portletModel.isShowPortletInactive()));
				portletModel.setActionURLRedirect(GetterUtil.getBoolean(
					portlet.elementText("action-url-redirect"),
					portletModel.isActionURLRedirect()));
				portletModel.setRestoreCurrentView(GetterUtil.getBoolean(
					portlet.elementText("restore-current-view"),
					portletModel.isRestoreCurrentView()));
				portletModel.setMaximizeEdit(GetterUtil.getBoolean(
					portlet.elementText("maximize-edit"),
					portletModel.isMaximizeEdit()));
				portletModel.setMaximizeHelp(GetterUtil.getBoolean(
					portlet.elementText("maximize-help"),
					portletModel.isMaximizeHelp()));
				portletModel.setPopUpPrint(GetterUtil.getBoolean(
					portlet.elementText("pop-up-print"),
					portletModel.isPopUpPrint()));
				portletModel.setLayoutCacheable(GetterUtil.getBoolean(
					portlet.elementText("layout-cacheable"),
					portletModel.isLayoutCacheable()));
				portletModel.setInstanceable(GetterUtil.getBoolean(
					portlet.elementText("instanceable"),
					portletModel.isInstanceable()));
				portletModel.setUserPrincipalStrategy(GetterUtil.getString(
					portlet.elementText("user-principal-strategy"),
					portletModel.getUserPrincipalStrategy()));
				portletModel.setPrivateRequestAttributes(GetterUtil.getBoolean(
					portlet.elementText("private-request-attributes"),
					portletModel.isPrivateRequestAttributes()));
				portletModel.setPrivateSessionAttributes(GetterUtil.getBoolean(
					portlet.elementText("private-session-attributes"),
					portletModel.isPrivateSessionAttributes()));
				portletModel.setRenderWeight(GetterUtil.getInteger(
					portlet.elementText("render-weight"),
					portletModel.getRenderWeight()));
				portletModel.setAjaxable(GetterUtil.getBoolean(
					portlet.elementText("ajaxable"),
					portletModel.isAjaxable()));

				List headerPortalCssList = portletModel.getHeaderPortalCss();

				Iterator itr2 = portlet.elements(
					"header-portal-css").iterator();

				while (itr2.hasNext()) {
					Element headerPortalCssEl = (Element)itr2.next();

					headerPortalCssList.add(headerPortalCssEl.getText());
				}

				List headerPortletCssList = portletModel.getHeaderPortletCss();

				List list = new ArrayList();

				list.addAll(portlet.elements("header-css"));
				list.addAll(portlet.elements("header-portlet-css"));

				itr2 = list.iterator();

				while (itr2.hasNext()) {
					Element headerPortletCssEl = (Element)itr2.next();

					headerPortletCssList.add(headerPortletCssEl.getText());
				}

				List headerPortalJavaScriptList =
					portletModel.getHeaderPortalJavaScript();

				itr2 = portlet.elements("header-portal-javascript").iterator();

				while (itr2.hasNext()) {
					Element headerPortalJavaScriptEl = (Element)itr2.next();

					headerPortalJavaScriptList.add(
						headerPortalJavaScriptEl.getText());
				}

				List headerPortletJavaScriptList =
					portletModel.getHeaderPortletJavaScript();

				list.clear();

				list.addAll(portlet.elements("header-javascript"));
				list.addAll(portlet.elements("header-portlet-javascript"));

				itr2 = list.iterator();

				while (itr2.hasNext()) {
					Element headerPortletJavaScriptEl = (Element)itr2.next();

					headerPortletJavaScriptList.add(
						headerPortletJavaScriptEl.getText());
				}

				List footerPortalCssList = portletModel.getFooterPortalCss();

				itr2 = portlet.elements("footer-portal-css").iterator();

				while (itr2.hasNext()) {
					Element footerPortalCssEl = (Element)itr2.next();

					footerPortalCssList.add(footerPortalCssEl.getText());
				}

				List footerPortletCssList = portletModel.getFooterPortletCss();

				itr2 = portlet.elements("footer-portlet-css").iterator();

				while (itr2.hasNext()) {
					Element footerPortletCssEl = (Element)itr2.next();

					footerPortletCssList.add(footerPortletCssEl.getText());
				}

				List footerPortalJavaScriptList =
					portletModel.getFooterPortalJavaScript();

				itr2 = portlet.elements("footer-portal-javascript").iterator();

				while (itr2.hasNext()) {
					Element footerPortalJavaScriptEl = (Element)itr2.next();

					footerPortalJavaScriptList.add(
						footerPortalJavaScriptEl.getText());
				}

				List footerPortletJavaScriptList =
					portletModel.getFooterPortletJavaScript();

				itr2 = portlet.elements("footer-portlet-javascript").iterator();

				while (itr2.hasNext()) {
					Element footerPortletJavaScriptEl = (Element)itr2.next();

					footerPortletJavaScriptList.add(
						footerPortletJavaScriptEl.getText());
				}

				portletModel.setCssClassWrapper(GetterUtil.getString(
					portlet.elementText("css-class-wrapper"),
					portletModel.getCssClassWrapper()));
				portletModel.setAddDefaultResource(GetterUtil.getBoolean(
					portlet.elementText("add-default-resource"),
					portletModel.isAddDefaultResource()));
				portletModel.setSystem(GetterUtil.getBoolean(
					portlet.elementText("system"),
					portletModel.isSystem()));
				portletModel.setActive(GetterUtil.getBoolean(
					portlet.elementText("active"),
					portletModel.isActive()));
				portletModel.setInclude(GetterUtil.getBoolean(
					portlet.elementText("include"),
					portletModel.isInclude()));

				if (!portletModel.isAjaxable() &&
					(portletModel.getRenderWeight() < 1)) {

					portletModel.setRenderWeight(1);
				}

				portletModel.getRoleMappers().putAll(roleMappers);
				portletModel.linkRoles();

				portletModel.getCustomUserAttributes().putAll(
					customUserAttributes);
			}
		}

		return liferayPortletIds;
	}

	private List _readWebXML(String xml) throws DocumentException, IOException {
		List servletURLPatterns = new ArrayList();

		if (xml == null) {
			return servletURLPatterns;
		}

		Document doc = PortalUtil.readDocumentFromXML(xml);

		Element root = doc.getRootElement();

		Iterator itr = root.elements("servlet-mapping").iterator();

		while (itr.hasNext()) {
			Element servletMapping = (Element)itr.next();

			String urlPattern = servletMapping.elementText("url-pattern");

			servletURLPatterns.add(urlPattern);
		}

		return servletURLPatterns;

	}

	private static Log _log = LogFactory.getLog(PortletLocalServiceImpl.class);

	private static Map _portletsPool = CollectionFactory.getSyncHashMap();
	private static Map _companyPortletsPool =
		CollectionFactory.getSyncHashMap();
	private static Map _portletIdsByStrutsPath =
		CollectionFactory.getSyncHashMap();
	private static Map _friendlyURLMapperPortlets =
		CollectionFactory.getSyncHashMap();

}