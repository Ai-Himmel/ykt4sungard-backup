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

import com.liferay.portal.NoSuchPortletException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletInfo;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.PortletPK;
import com.liferay.portal.service.persistence.PortletUtil;
import com.liferay.portal.service.spring.PortletService;
import com.liferay.portal.util.EntityResolver;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.PortletPreferencesSerializer;
import com.liferay.util.CollectionFactory;
import com.liferay.util.GetterUtil;
import com.liferay.util.KeyValuePair;
import com.liferay.util.ListUtil;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.Validator;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.StringReader;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import javax.portlet.PreferencesValidator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.SAXReader;
import org.dom4j.io.XMLWriter;

/**
 * <a href="PortletServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class PortletServiceImpl
	extends PrincipalBean implements PortletService {

	// Business methods

	public Map getEARDisplay(String xml) throws DocumentException, IOException {
		return _readLiferayDisplayXML(xml);
	}

	public Map getWARDisplay(String servletContextName, String xml)
		throws DocumentException, IOException {

		return _readLiferayDisplayXML(servletContextName, xml);
	}

	public Portlet getPortletById(String companyId, String portletId)
		throws SystemException {

		if (companyId.equals(User.DEFAULT)) {
			throw new SystemException();
		}

		Portlet portlet = null;

		Map companyPortletsPool = _getPortletsPool(companyId);

		String rootPortletId = Portlet.getRootPortletId(portletId);

		if (portletId.equals(rootPortletId)) {
			portlet = (Portlet)companyPortletsPool.get(portletId);
		}
		else {
			portlet = (Portlet)companyPortletsPool.get(rootPortletId);

			if (portlet != null) {
				portlet = portlet.getClonedInstance(portletId);
			}
		}

		return portlet;
	}

	public Portlet getPortletByStrutsPath(String companyId, String strutsPath)
		throws SystemException {

		return getPortletById(companyId, _getPortletId(strutsPath));
	}

	public List getPortlets(String companyId) throws SystemException {
		List list = ListUtil.fromCollection(
			_getPortletsPool(companyId).values());

		Collections.sort(list);

		return list;
	}

	public void initEAR(String[] xmls) {
		String scpId = PortletServiceImpl.class.getName() + "." + _SHARED_KEY;

		Map portletsPool = (Map)SimpleCachePool.get(scpId);

		if (portletsPool == null) {
			portletsPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, portletsPool);
		}

		try {
			Set portletIds = _readPortletXML(xmls[0], portletsPool);
			portletIds.addAll(_readPortletXML(xmls[1], portletsPool));

			Set liferayPortletIds =
				_readLiferayPortletXML(xmls[2], portletsPool);

			liferayPortletIds.addAll(
				_readLiferayPortletXML(xmls[3], portletsPool));

			// Check for missing entries in liferay-portlet.xml

			Iterator itr = portletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				if (!liferayPortletIds.contains(portletId)) {
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

				if (!portletIds.contains(portletId)) {
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
			e.printStackTrace();
		}
	}

	public List initWAR(String servletContextName, String[] xmls) {
		List portlets = new ArrayList();

		String scpId = PortletServiceImpl.class.getName() + "." + _SHARED_KEY;

		Map portletsPool = (Map)SimpleCachePool.get(scpId);

		if (portletsPool == null) {
			portletsPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, portletsPool);
		}

		try {
			Set portletIds = _readPortletXML(
				servletContextName, xmls[0], portletsPool);

			Set liferayPortletIds = _readLiferayPortletXML(
				servletContextName, xmls[1], portletsPool);

			// Check for missing entries in liferay-portlet.xml

			Iterator itr = portletIds.iterator();

			while (itr.hasNext()) {
				String portletId = (String)itr.next();

				if (!liferayPortletIds.contains(portletId)) {
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

				if (!portletIds.contains(portletId)) {
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
			e.printStackTrace();
		}

		// Refresh security path to portlet id mapping for all portlets

		SimpleCachePool.remove(PortletServiceImpl.class.getName());

		// Refresh company portlets

		SimpleCachePool.remove(
			PortletServiceImpl.class.getName() + ".companyPortletsPool");

		return portlets;
	}

	public Portlet updatePortlet(
			String portletId, boolean narrow, String roles, boolean active)
		throws PortalException, SystemException {

		String companyId = getUser().getCompanyId();

		if (!hasAdministrator(companyId)) {
			throw new PrincipalException();
		}

		PortletPK pk = new PortletPK(portletId, companyId);

		Portlet portlet = null;

		try {
			portlet = PortletUtil.findByPrimaryKey(pk);
		}
		catch (NoSuchPortletException nspe) {
			portlet = PortletUtil.create(pk);
		}

		portlet.setNarrow(narrow);
		portlet.setRoles(roles);
		portlet.setActive(active);

		PortletUtil.update(portlet);

		portlet = getPortletById(companyId, portletId);

		portlet.setNarrow(narrow);
		portlet.setRoles(roles);
		portlet.setActive(active);

		return portlet;
	}

	// Private methods

	private String _getPortletId(String securityPath) throws SystemException {
		String scpId = PortletServiceImpl.class.getName();

		Map portletIds = (Map)SimpleCachePool.get(scpId);

		if (portletIds == null) {
			portletIds = CollectionFactory.getHashMap();

			Iterator itr = _getPortletsPool().values().iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				portletIds.put(portlet.getStrutsPath(), portlet.getPortletId());
			}

			SimpleCachePool.put(scpId, portletIds);
		}

		return (String)portletIds.get(securityPath);
	}

	private Map _getPortletsPool() {
		String scpId = PortletServiceImpl.class.getName() + "." + _SHARED_KEY;

		return (Map)SimpleCachePool.get(scpId);
	}

	private Map _getPortletsPool(String companyId) throws SystemException {
		String scpId =
			PortletServiceImpl.class.getName() + ".companyPortletsPool";

		Map companyPortletsPool = (Map)SimpleCachePool.get(scpId);

		if (companyPortletsPool == null) {
			companyPortletsPool = CollectionFactory.getSyncHashMap();

			SimpleCachePool.put(scpId, companyPortletsPool);
		}

		Map portletsPool = (Map)companyPortletsPool.get(companyId);

		if (portletsPool == null) {
			portletsPool = CollectionFactory.getSyncHashMap();

			Map parentPortletsPool = _getPortletsPool();

			Iterator itr = parentPortletsPool.values().iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)((Portlet)itr.next()).clone();

				portlet.setCompanyId(companyId);

				portletsPool.put(portlet.getPortletId(), portlet);
			}

			itr = PortletUtil.findByCompanyId(companyId).iterator();

			while (itr.hasNext()) {
				Portlet portlet = (Portlet)itr.next();

				Portlet portletModel =
					(Portlet)portletsPool.get(portlet.getPortletId());

				// Portlet may be null if it exists in the database but its
				// portlet WAR is not yet loaded

				if (portletModel != null) {
					portletModel.setNarrow(portlet.getNarrow());
					portletModel.setRoles(portlet.getRoles());
					portletModel.setActive(portlet.getActive());
				}
			}

			companyPortletsPool.put(companyId, portletsPool);
		}

		return portletsPool;
	}

	private Set _readPortletXML(String xml, Map portletsPool)
		throws DocumentException, IOException {

		return _readPortletXML(null, xml, portletsPool);
	}

	private Set _readPortletXML(
			String servletContextName, String xml, Map portletsPool)
		throws DocumentException, IOException {

		Set portletIds = new HashSet();

		if (xml == null) {
			return portletIds;
		}

		// Crimson cannot do XSD validation. See the following links:
		//
		// http://www.geocities.com/herong_yang/jdk/xsd_validation.html
		// http://www.burnthacker.com/archives/000086.html
		// http://www.theserverside.com/news/thread.tss?thread_id=22525

		SAXReader reader = null;
		try {
			reader = new SAXReader(_SAX_PARSER_IMPL);

			reader.setEntityResolver(new EntityResolver());

			reader.setFeature(_FEATURES_VALIDATION, true);
			reader.setFeature(_FEATURES_VALIDATION_SCHEMA, true);
			reader.setFeature(_FEATURES_VALIDATION_SCHEMA_FULL_CHECKING, true);
			reader.setFeature(_FEATURES_DYNAMIC, true);
		}
		catch (Exception e) {
			_log.warn("XSD validation is diasabled");

			reader = new SAXReader();
		}

		Document doc = reader.read(new StringReader(xml));

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
					portletId + Portlet.WAR_SEPARATOR + servletContextName;
			}

			portletIds.add(portletId);

			Portlet portletModel = (Portlet)portletsPool.get(portletId);
			if (portletModel == null) {
				portletModel = new Portlet(
					new PortletPK(portletId, _SHARED_KEY));

				portletsPool.put(portletId, portletModel);
			}

			if (servletContextName != null) {
				portletModel.setWARFile(true);
			}

			portletModel.setPortletClass(portlet.elementText("portlet-class"));

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

				Iterator itr3 = supports.elements("portlet-mode").iterator();

				while (itr3.hasNext()) {
					Element portletMode = (Element)itr3.next();

					Set mimeTypeModes =
						(Set)portletModel.getPortletModes().get(mimeType);

					if (mimeTypeModes == null) {
						mimeTypeModes = new HashSet();

						portletModel.getPortletModes().put(
							mimeType, mimeTypeModes);
					}

					mimeTypeModes.add(portletMode.getTextTrim().toLowerCase());
				}
			}

			Set supportedLocales = portletModel.getSupportedLocales();

			supportedLocales.add(Locale.getDefault().getLanguage());

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

				String prefsValidatorName = null;

				if (prefsValidatorEl != null) {
					prefsValidator = prefsValidatorEl.getText();

					portletPreferences.remove(prefsValidatorEl);
				}

				ByteArrayOutputStream baos = new ByteArrayOutputStream();

				XMLWriter writer = new XMLWriter(
					baos, OutputFormat.createCompactFormat());

				writer.write(portletPreferences);

				defaultPreferences = baos.toString();
			}

			portletModel.setDefaultPreferences(defaultPreferences);
			portletModel.setPreferencesValidator(prefsValidator);

			if (!portletModel.isWARFile() &&
				Validator.isNotNull(prefsValidator) &&
				GetterUtil.getBoolean(PropsUtil.get(
					PropsUtil.PREFERENCE_VALIDATE_ON_STARTUP))) {

				try {
					PreferencesValidator prefsValidatorObj =
						PortalUtil.getPreferencesValidator(portletModel);

					prefsValidatorObj.validate(
						PortletPreferencesSerializer.fromDefaultXML(
							defaultPreferences));
				}
				catch (Exception e) {
					_log.warn(
						"Portlet with the name " + portletId +
							" does not have valid default preferences");
				}
			}

			List roles = new ArrayList();

			itr2 = portlet.elements("security-role-ref").iterator();

			while (itr2.hasNext()) {
				Element role = (Element)itr2.next();

				roles.add(role.elementText("role-name"));
			}

			portletModel.setRolesArray((String[])roles.toArray(new String[0]));

			portletModel.getUserAttributes().addAll(userAttributes);
		}

		return portletIds;
	}

	private Map _readLiferayDisplayXML(String xml)
		throws DocumentException, IOException {

		return _readLiferayDisplayXML(null, xml);
	}

	private Map _readLiferayDisplayXML(String servletContextName, String xml)
		throws DocumentException, IOException {

		Map categories = new LinkedHashMap();

		if (xml == null) {
			return categories;
		}

		SAXReader reader = new SAXReader(true);
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(new StringReader(xml));

		Set portletIds = new HashSet();

		Iterator itr1 = doc.getRootElement().elements("category").iterator();

		while (itr1.hasNext()) {
			Element category = (Element)itr1.next();

			String name = category.attributeValue("name");

			List portlets = new ArrayList();

			Iterator itr2 = category.elements("portlet").iterator();

			while (itr2.hasNext()) {
				Element portlet = (Element)itr2.next();

				String portletId = portlet.attributeValue("id");
				if (servletContextName != null) {
					portletId =
						portletId + Portlet.WAR_SEPARATOR + servletContextName;
				}

				portletIds.add(portletId);

				String status = portlet.attributeValue("status");

				portlets.add(new KeyValuePair(portletId, status));
			}

			if (portlets.size() > 0) {
				categories.put(name, portlets);
			}
		}

		// Portlets that do not belong to any categories should default to the
		// Undefined category

		List undefinedPortlets = new ArrayList();

		itr1 = _getPortletsPool().values().iterator();

		while (itr1.hasNext()) {
			Portlet portlet = (Portlet)itr1.next();

			String portletId = portlet.getPortletId();

			if ((servletContextName != null) && (portlet.isWARFile()) &&
				(portletId.startsWith(servletContextName) &&
				(!portletIds.contains(portletId)))) {

				undefinedPortlets.add(new KeyValuePair(portletId, null));
			}
			else if ((servletContextName == null) && (!portlet.isWARFile()) &&
					 (!portletIds.contains(portletId))) {

				undefinedPortlets.add(new KeyValuePair(portletId, null));
			}
		}

		if (undefinedPortlets.size() > 0) {
			categories.put("category.undefined", undefinedPortlets);
		}

		return categories;
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

		SAXReader reader = new SAXReader(true);
		reader.setEntityResolver(new EntityResolver());

		Document doc = reader.read(new StringReader(xml));

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
					portletId + Portlet.WAR_SEPARATOR + servletContextName;
			}

			liferayPortletIds.add(portletId);

			Portlet portletModel = (Portlet)portletsPool.get(portletId);

			if (portletModel != null) {
				portletModel.setStrutsPath(GetterUtil.get(
					portlet.elementText("struts-path"),
					portletModel.getStrutsPath()));
				portletModel.setIndexerClass(GetterUtil.get(
					portlet.elementText("indexer-class"),
					portletModel.getIndexerClass()));
				portletModel.setSchedulerClass(GetterUtil.get(
					portlet.elementText("scheduler-class"),
					portletModel.getSchedulerClass()));
				portletModel.setPreferencesUniquePerLayout(GetterUtil.get(
					portlet.elementText("preferences-unique-per-layout"),
					portletModel.isPreferencesUniquePerLayout()));
				portletModel.setPreferencesOwnedByGroup(GetterUtil.get(
					portlet.elementText("preferences-owned-by-group"),
					portletModel.isPreferencesOwnedByGroup()));
				portletModel.setUseDefaultTemplate(GetterUtil.get(
					portlet.elementText("use-default-template"),
					portletModel.isUseDefaultTemplate()));
				portletModel.setShowPortletAccessDenied(GetterUtil.get(
					portlet.elementText("show-portlet-access-denied"),
					portletModel.isShowPortletAccessDenied()));
				portletModel.setShowPortletInactive(GetterUtil.get(
					portlet.elementText("show-portlet-inactive"),
					portletModel.isShowPortletInactive()));
				portletModel.setRestoreCurrentView(GetterUtil.get(
					portlet.elementText("restore-current-view"),
					portletModel.isRestoreCurrentView()));
				portletModel.setNs4Compatible(GetterUtil.get(
					portlet.elementText("ns-4-compatible"),
					portletModel.isNs4Compatible()));
				portletModel.setInstanceable(GetterUtil.get(
					portlet.elementText("instanceable"),
					portletModel.isInstanceable()));
				portletModel.setNarrow(GetterUtil.get(
					portlet.elementText("narrow"),
					portletModel.isNarrow()));
				portletModel.setActive(GetterUtil.get(
					portlet.elementText("active"),
					portletModel.isActive()));
				portletModel.setInclude(GetterUtil.get(
					portlet.elementText("include"),
					portletModel.isInclude()));

				portletModel.getRoleMappers().putAll(roleMappers);
				portletModel.linkRoles();

				portletModel.getCustomUserAttributes().putAll(
					customUserAttributes);
			}
		}

		return liferayPortletIds;
	}

	private static final Log _log = LogFactory.getLog(PortletServiceImpl.class);

	private static final String _SHARED_KEY = "SHARED_KEY";

	private static final String _SAX_PARSER_IMPL =
		"org.apache.xerces.parsers.SAXParser";

	private static final String _FEATURES_VALIDATION =
		"http://xml.org/sax/features/validation";

	private static final String _FEATURES_VALIDATION_SCHEMA =
		"http://apache.org/xml/features/validation/schema";

	private static final String _FEATURES_VALIDATION_SCHEMA_FULL_CHECKING =
		"http://apache.org/xml/features/validation/schema-full-checking";

	private static final String _FEATURES_DYNAMIC =
		"http://apache.org/xml/features/validation/dynamic";

}