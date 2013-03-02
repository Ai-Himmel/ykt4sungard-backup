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

package com.liferay.portal.security.permission;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.language.LanguageUtil;
import com.liferay.portal.kernel.security.permission.ActionKeys;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Location;
import com.liferay.portal.model.Organization;
import com.liferay.portal.model.PasswordPolicy;
import com.liferay.portal.model.Permission;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.Role;
import com.liferay.portal.model.User;
import com.liferay.portal.model.UserGroup;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.PortletLocalServiceUtil;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.PortletResourceBundles;
import com.liferay.util.CollectionFactory;
import com.liferay.util.UniqueList;

import java.io.StringReader;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Set;

import javax.servlet.jsp.PageContext;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="ResourceActionsUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ResourceActionsUtil {

	public static final String ACTION_NAME_PREFIX = "action.";

	public static final String MODEL_RESOURCE_NAME_PREFIX = "model.resource.";

	public static final String[] ORGANIZATION_MODEL_RESOURCES = {
		Location.class.getName(), Organization.class.getName(),
		PasswordPolicy.class.getName(), User.class.getName()
	};

	public static final String[] PORTAL_MODEL_RESOURCES = {
		Location.class.getName(), Organization.class.getName(),
		PasswordPolicy.class.getName(), Role.class.getName(),
		User.class.getName(), UserGroup.class.getName()
	};

	public static String getAction(
		long companyId, Locale locale, String action) {

		String key = ACTION_NAME_PREFIX + action;

		String value = LanguageUtil.get(companyId, locale, key, null);

		if ((value == null) || (value.equals(key))) {
			value = PortletResourceBundles.getString(locale, key);
		}

		if (value == null) {
			value = key;
		}

		return value;
	}

	public static String getAction(PageContext pageContext, String action) {
		String key = ACTION_NAME_PREFIX + action;

		String value = LanguageUtil.get(pageContext, key, null);

		if ((value == null) || (value.equals(key))) {
			value = PortletResourceBundles.getString(pageContext, key);
		}

		if (value == null) {
			value = key;
		}

		return value;
	}

	public static List getActions(List permissions) {
		List actions = new UniqueList();

		Iterator itr = permissions.iterator();

		while (itr.hasNext()) {
			Permission permission = (Permission)itr.next();

			actions.add(permission.getActionId());
		}

		return actions;
	}

	public static List getActionsNames(PageContext pageContext, List actions) {
		List uniqueList = new UniqueList();

		Iterator itr = actions.iterator();

		while (itr.hasNext()) {
			String action = (String)itr.next();

			uniqueList.add(getAction(pageContext, action));
		}

		List list = new ArrayList();

		list.addAll(uniqueList);

		Collections.sort(list);

		return list;
	}

	public static List getModelPortletResources(String name) {
		return _instance._getModelPortletResources(name);
	}

	public static String getModelResource(
		long companyId, Locale locale, String name) {

		String key = MODEL_RESOURCE_NAME_PREFIX + name;

		String value = LanguageUtil.get(companyId, locale, key, null);

		if ((value == null) || (value.equals(key))) {
			value = PortletResourceBundles.getString(locale, key);
		}

		if (value == null) {
			value = key;
		}

		return value;
	}

	public static String getModelResource(
		PageContext pageContext, String name) {

		String key = MODEL_RESOURCE_NAME_PREFIX + name;

		String value = LanguageUtil.get(pageContext, key, null);

		if ((value == null) || (value.equals(key))) {
			value = PortletResourceBundles.getString(pageContext, key);
		}

		if (value == null) {
			value = key;
		}

		return value;
	}

	public static List getModelResourceActions(String name) {
		return _instance._getModelResourceActions(name);
	}

	public static List getModelResourceCommunityDefaultActions(String name) {
		return _instance._getModelResourceCommunityDefaultActions(name);
	}

	public static List getModelResourceGuestDefaultActions(String name) {
		return _instance._getModelResourceGuestDefaultActions(name);
	}

	public static List getModelResourceGuestUnsupportedActions(String name) {
		return _instance._getModelResourceGuestUnsupportedActions(name);
	}

	public static List getPortletModelResources(String portletName) {
		return _instance._getPortletModelResources(portletName);
	}

	public static List getPortletResourceActions(long companyId, String name)
		throws SystemException {

		return _instance._getPortletResourceActions(companyId, name);
	}

	public static List getPortletResourceCommunityDefaultActions(String name)
		throws SystemException {

		return _instance._getPortletResourceCommunityDefaultActions(name);
	}

	public static List getPortletResourceGuestDefaultActions(String name)
		throws SystemException {

		return _instance._getPortletResourceGuestDefaultActions(name);
	}

	public static List getPortletResourceGuestUnsupportedActions(String name)
		throws SystemException {

		return _instance._getPortletResourceGuestUnsupportedActions(name);
	}

	public static List getPortletResourceLayoutManagerActions(String name)
		throws SystemException {

		return _instance._getPortletResourceLayoutManagerActions(name);
	}

	public static List getResourceActions(
			long companyId, String portletResource, String modelResource)
		throws SystemException {

		List actions = null;

		if (Validator.isNull(modelResource)) {
			actions = getPortletResourceActions(companyId, portletResource);
		}
		else {
			actions = getModelResourceActions(modelResource);
		}

		return actions;
	}

	public static List getResourceGuestUnsupportedActions(
			String portletResource, String modelResource)
		throws SystemException {

		List actions = null;

		if (Validator.isNull(modelResource)) {
			actions =
				getPortletResourceGuestUnsupportedActions(portletResource);
		}
		else {
			actions = getModelResourceGuestUnsupportedActions(modelResource);
		}

		return actions;
	}

	public static boolean isOrganizationModelResource(String modelResource) {
		return _instance._isOrganizationModelResource(modelResource);
	}

	public static boolean isPortalModelResource(String modelResource) {
		return _instance._isPortalModelResource(modelResource);
	}

	public static void read(
			String servletContextName, ClassLoader classLoader, String source)
		throws Exception {

		_instance._read(servletContextName, classLoader, source);
	}

	private ResourceActionsUtil() {
		_organizationModelResources = CollectionFactory.getHashSet();

		for (int i = 0; i < ORGANIZATION_MODEL_RESOURCES.length; i++) {
			_organizationModelResources.add(ORGANIZATION_MODEL_RESOURCES[i]);
		}

		_portalModelResources = CollectionFactory.getHashSet();

		for (int i = 0; i < PORTAL_MODEL_RESOURCES.length; i++) {
			_portalModelResources.add(PORTAL_MODEL_RESOURCES[i]);
		}

		_portletModelResources = CollectionFactory.getHashMap();
		_portletResourceActions = CollectionFactory.getHashMap();
		_portletResourceCommunityDefaultActions =
			CollectionFactory.getHashMap();
		_portletResourceGuestDefaultActions = CollectionFactory.getHashMap();
		_portletResourceGuestUnsupportedActions =
			CollectionFactory.getHashMap();
		_portletResourceLayoutManagerActions = CollectionFactory.getHashMap();
		_modelPortletResources = CollectionFactory.getHashMap();
		_modelResourceActions = CollectionFactory.getHashMap();
		_modelResourceCommunityDefaultActions = CollectionFactory.getHashMap();
		_modelResourceGuestDefaultActions = CollectionFactory.getHashMap();
		_modelResourceGuestUnsupportedActions = CollectionFactory.getHashMap();

		try {
			ClassLoader classLoader = getClass().getClassLoader();

			String[] configs = StringUtil.split(
				PropsUtil.get(PropsUtil.RESOURCE_ACTIONS_CONFIGS));

			for (int i = 0; i < configs.length; i++) {
				_read(null, classLoader, configs[i]);
			}
		}
		catch (Exception e) {
			_log.error(e, e);
		}
	}

	private void _checkGuestUnsupportedActions(
		List guestUnsupportedActions, List guestDefaultActions) {

		// Guest default actions cannot reference guest unsupported actions

		Iterator itr = guestDefaultActions.iterator();

		while (itr.hasNext()) {
			String actionId = (String)itr.next();

			if (guestUnsupportedActions.contains(actionId)) {
				itr.remove();
			}
		}
	}

	private void _checkPortletActions(List actions) {
		if (!actions.contains("CONFIGURATION")) {
			actions.add("CONFIGURATION");
		}

		if (!actions.contains("VIEW")) {
			actions.add("VIEW");
		}
	}

	private void _checkPortletCommunityDefaultActions(List actions) {
		if (actions.size() == 0) {
			actions.add("VIEW");
		}
	}

	private void _checkPortletGuestDefaultActions(List actions) {
		if (actions.size() == 0) {
			actions.add("VIEW");
		}
	}

	private void _checkPortletLayoutManagerActions(List actions) {
		if (!actions.contains("CONFIGURATION")) {
			actions.add("CONFIGURATION");
		}

		if (!actions.contains("VIEW")) {
			actions.add("VIEW");
		}
	}

	private List _getActions(Map map, String name) {
		List actions = (List)map.get(name);

		if (actions == null) {
			actions = new UniqueList();

			map.put(name, actions);
		}

		return actions;
	}

	private List _getModelPortletResources(String name) {
		Set resources = (Set)_modelPortletResources.get(name);

		if (resources == null) {
			return new UniqueList();
		}
		else {
			return Collections.list(Collections.enumeration(resources));
		}
	}

	private List _getModelResourceActions(String name) {
		return _getActions(_modelResourceActions, name);
	}

	private List _getModelResourceCommunityDefaultActions(String name) {
		return _getActions(_modelResourceCommunityDefaultActions, name);
	}

	private List _getModelResourceGuestDefaultActions(String name) {
		return _getActions(_modelResourceGuestDefaultActions, name);
	}

	private List _getModelResourceGuestUnsupportedActions(String name) {
		return _getActions(_modelResourceGuestUnsupportedActions, name);
	}

	private List _getPortletModelResources(String portletName) {
		portletName = PortletImpl.getRootPortletId(portletName);

		Set resources = (Set)_portletModelResources.get(portletName);

		if (resources == null) {
			return new UniqueList();
		}
		else {
			return Collections.list(Collections.enumeration(resources));
		}
	}

	private List _getPortletResourceActions(long companyId, String name)
		throws SystemException {

		name = PortletImpl.getRootPortletId(name);

		List actions = _getActions(_portletResourceActions, name);

		if (actions.size() == 0) {
			synchronized (this) {
				Portlet portlet = PortletLocalServiceUtil.getPortletById(
					companyId, name);

				Map portletModes = portlet.getPortletModes();

				Set mimeTypeModes = (Set)portletModes.get("text/html");

				if (mimeTypeModes != null) {
					Iterator itr = mimeTypeModes.iterator();

					while (itr.hasNext()) {
						String actionId = (String)itr.next();

						if (actionId.equalsIgnoreCase("edit")) {
							actions.add(ActionKeys.PREFERENCES);
						}
						else if (actionId.equalsIgnoreCase("edit_guest")) {
							actions.add(ActionKeys.GUEST_PREFERENCES);
						}
						else {
							actions.add(actionId.toUpperCase());
						}
					}
				}

				_checkPortletActions(actions);

				List communityDefaultActions =
					(List)_portletResourceCommunityDefaultActions.get(name);

				if (communityDefaultActions == null) {
					communityDefaultActions = new UniqueList();

					_portletResourceCommunityDefaultActions.put(
						name, communityDefaultActions);

					_checkPortletCommunityDefaultActions(
						communityDefaultActions);
				}

				List guestDefaultActions =
					(List)_portletResourceGuestDefaultActions.get(name);

				if (guestDefaultActions == null) {
					guestDefaultActions = new UniqueList();

					_portletResourceGuestDefaultActions.put(
						name, guestDefaultActions);

					_checkPortletGuestDefaultActions(guestDefaultActions);
				}

				List layoutManagerActions =
					(List)_portletResourceLayoutManagerActions.get(name);

				if (layoutManagerActions == null) {
					layoutManagerActions = new UniqueList();

					_portletResourceLayoutManagerActions.put(
						name, layoutManagerActions);

					_checkPortletLayoutManagerActions(layoutManagerActions);
				}
			}
		}

		return actions;
	}

	private List _getPortletResourceCommunityDefaultActions(String name)
		throws SystemException {

		// This method should always be called only after
		// _getPortletResourceActions has been called at least once to
		// populate the default community actions. Check to make sure this is
		// the case. However, if it is not, that means the methods
		// _getPortletResourceGuestDefaultActions and
		// _getPortletResourceGuestDefaultActions may not work either.

		name = PortletImpl.getRootPortletId(name);

		return _getActions(_portletResourceCommunityDefaultActions, name);
	}

	private List _getPortletResourceGuestDefaultActions(String name)
		throws SystemException {

		name = PortletImpl.getRootPortletId(name);

		return _getActions(_portletResourceGuestDefaultActions, name);
	}

	private List _getPortletResourceGuestUnsupportedActions(String name)
		throws SystemException {

		name = PortletImpl.getRootPortletId(name);

		return _getActions(_portletResourceGuestUnsupportedActions, name);
	}

	private List _getPortletResourceLayoutManagerActions(String name)
		throws SystemException {

		name = PortletImpl.getRootPortletId(name);

		List actions = _getActions(_portletResourceLayoutManagerActions, name);

		// This check can never return an empty list. If the list is empty, it
		// means that the portlet does not have an explicit resource-actions
		// configuration file and should therefore be handled as if it has
		// defaults of CONFIGURATION and VIEW.

		if (actions.size() < 1) {
			actions.add("CONFIGURATION");
			actions.add("VIEW");
		}

		return actions;
	}

	private boolean _isOrganizationModelResource(String modelResource) {
		if (_organizationModelResources.contains(modelResource)) {
			return true;
		}
		else {
			return false;
		}
	}

	private boolean _isPortalModelResource(String modelResource) {
		if (_portalModelResources.contains(modelResource)) {
			return true;
		}
		else {
			return false;
		}
	}

	private void _read(
			String servletContextName, ClassLoader classLoader, String source)
		throws Exception {

		String xml = null;

		try {
			xml = StringUtil.read(classLoader, source);
		}
		catch (Exception e) {
			_log.warn("Cannot load " + source);
		}

		if (xml == null) {
			return;
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Loading " + source);
		}

		SAXReader reader = new SAXReader();

		Document doc = reader.read(new StringReader(xml));

		Element root = doc.getRootElement();

		Iterator itr1 = root.elements("resource").iterator();

		while (itr1.hasNext()) {
			Element resource = (Element)itr1.next();

			String file = resource.attributeValue("file");

			_read(servletContextName, classLoader, file);
		}

		itr1 = root.elements("portlet-resource").iterator();

		while (itr1.hasNext()) {
			Element resource = (Element)itr1.next();

			String name = resource.elementText("portlet-name");

			if (servletContextName != null) {
				name = name + PortletImpl.WAR_SEPARATOR + servletContextName;
			}

			name = PortalUtil.getJsSafePortletId(name);

			// Actions

			List actions = _getActions(_portletResourceActions, name);

			Element supports = resource.element("supports");

			Iterator itr2 = supports.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					actions.add(actionKeyText);
				}
			}

			if (!name.equals(PortletKeys.PORTAL)) {
				_checkPortletActions(actions);
			}

			// Community default actions

			List communityDefaultActions =
				_getActions(_portletResourceCommunityDefaultActions, name);

			Element communityDefaults = resource.element("community-defaults");

			itr2 = communityDefaults.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					communityDefaultActions.add(actionKeyText);
				}
			}

			// Guest default actions

			List guestDefaultActions =
				_getActions(_portletResourceGuestDefaultActions, name);

			Element guestDefaults = resource.element("guest-defaults");

			itr2 = guestDefaults.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					guestDefaultActions.add(actionKeyText);
				}
			}

			// Guest unsupported actions

			List guestUnsupportedActions =
				_getActions(_portletResourceGuestUnsupportedActions, name);

			Element guestUnsupported = resource.element("guest-unsupported");

			itr2 = guestUnsupported.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					guestUnsupportedActions.add(actionKeyText);
				}
			}

			_checkGuestUnsupportedActions(
				guestUnsupportedActions, guestDefaultActions);

			// Layout manager actions

			List layoutManagerActions = _getActions(
				_portletResourceLayoutManagerActions, name);

			Element layoutManager = resource.element("layout-manager");

			if (layoutManager != null) {
				itr2 = layoutManager.elements("action-key").iterator();

				while (itr2.hasNext()) {
					Element actionKey = (Element)itr2.next();

					String actionKeyText = actionKey.getText();

					if (Validator.isNotNull(actionKeyText)) {
						layoutManagerActions.add(actionKeyText);
					}
				}
			}
			else {

				// Set the layout manager actions to contain all the portlet
				// resource actions if the element is not specified

				layoutManagerActions.addAll(actions);
			}
		}

		itr1 = root.elements("model-resource").iterator();

		while (itr1.hasNext()) {
			Element resource = (Element)itr1.next();

			String name = resource.elementText("model-name");

			Element portletRef = resource.element("portlet-ref");

			Iterator itr2 = portletRef.elements("portlet-name").iterator();

			while (itr2.hasNext()) {
				Element portletName = (Element)itr2.next();

				String portletNameString = portletName.getText();

				if (servletContextName != null) {
					portletNameString =
						portletNameString + PortletImpl.WAR_SEPARATOR +
							servletContextName;
				}

				portletNameString = PortalUtil.getJsSafePortletId(
					portletNameString);

				// Reference for a portlet to child models

				Set modelResources = (Set)_portletModelResources.get(
					portletNameString);

				if (modelResources == null) {
					modelResources = new HashSet();

					_portletModelResources.put(
						portletNameString, modelResources);
				}

				modelResources.add(name);

				// Reference for a model to parent portlets

				Set portletResources = (Set)_modelPortletResources.get(name);

				if (portletResources == null) {
					portletResources = new HashSet();

					_modelPortletResources.put(name, portletResources);
				}

				portletResources.add(portletNameString);
			}

			// Actions

			List actions = _getActions(_modelResourceActions, name);

			Element supports = resource.element("supports");

			itr2 = supports.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					actions.add(actionKeyText);
				}
			}

			// Community default actions

			List communityDefaultActions =
				_getActions(_modelResourceCommunityDefaultActions, name);

			Element communityDefaults = resource.element("community-defaults");

			itr2 = communityDefaults.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					communityDefaultActions.add(actionKeyText);
				}
			}

			// Guest default actions

			List guestDefaultActions =
				_getActions(_modelResourceGuestDefaultActions, name);

			Element guestDefaults = resource.element("guest-defaults");

			itr2 = guestDefaults.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					guestDefaultActions.add(actionKeyText);
				}
			}

			// Guest unsupported actions

			List guestUnsupportedActions =
				_getActions(_modelResourceGuestUnsupportedActions, name);

			Element guestUnsupported = resource.element("guest-unsupported");

			itr2 = guestUnsupported.elements("action-key").iterator();

			while (itr2.hasNext()) {
				Element actionKey = (Element)itr2.next();

				String actionKeyText = actionKey.getText();

				if (Validator.isNotNull(actionKeyText)) {
					guestUnsupportedActions.add(actionKeyText);
				}
			}

			_checkGuestUnsupportedActions(
				guestUnsupportedActions, guestDefaultActions);
		}
	}

	private static Log _log = LogFactory.getLog(ResourceActionsUtil.class);

	private static ResourceActionsUtil _instance = new ResourceActionsUtil();

	private Set _organizationModelResources;
	private Set _portalModelResources;
	private Map _portletModelResources;
	private Map _portletResourceActions;
	private Map _portletResourceCommunityDefaultActions;
	private Map _portletResourceGuestDefaultActions;
	private Map _portletResourceGuestUnsupportedActions;
	private Map _portletResourceLayoutManagerActions;
	private Map _modelPortletResources;
	private Map _modelResourceActions;
	private Map _modelResourceCommunityDefaultActions;
	private Map _modelResourceGuestDefaultActions;
	private Map _modelResourceGuestUnsupportedActions;

}