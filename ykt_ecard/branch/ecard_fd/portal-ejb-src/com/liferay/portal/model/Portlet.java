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

import com.liferay.portal.service.persistence.PortletPK;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.CachePortlet;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;

import java.util.HashMap;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Set;

import javax.portlet.PortletConfig;
import javax.portlet.PortletException;
import javax.portlet.PortletMode;
import javax.portlet.UnavailableException;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="Portlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.60 $
 *
 */
public class Portlet extends PortletModel {

	/**
	 * War file separator.
	 */
	public static final String WAR_SEPARATOR = "_WAR_";

	/**
	 * Instance separator.
	 */
	public static final String INSTANCE_SEPARATOR = "_INSTANCE_";

	/**
	 * Gets the root portlet id of the portlet.
	 *
	 * @param		portletId the portlet id of the portlet
	 * @return		the root portlet id of the portlet
	 */
	public static String getRootPortletId(String portletId) {
		int pos = portletId.indexOf(INSTANCE_SEPARATOR);

		if (pos == -1) {
			return portletId;
		}
		else {
			return portletId.substring(0, pos);
		}
	}

	/**
	 * Constructs a portlet with no parameters.
	 */
	public Portlet() {
		super();
	}

	/**
	 * Constructs a portlet with the specified parameters.
	 */
	public Portlet(PortletPK pk) {
		super(pk);

		setStrutsPath(pk.portletId);
		setActive(true);
		setInclude(true);
		_roleMappers = new LinkedHashMap();
		_initParams = new HashMap();
		_portletModes = new HashMap();
		_supportedLocales = new HashSet();
		_userAttributes = new LinkedHashSet();
		_customUserAttributes = new LinkedHashMap();
	}

	/**
	 * Constructs a portlet with the specified parameters.
	 */
	public Portlet(String portletId, String companyId, boolean narrow,
				   String roles, boolean active) {

		super(portletId, companyId, narrow, roles, active);

		setRoles(roles);
	}

	/**
	 * Constructs a portlet with the specified parameters.
	 */
	public Portlet(String portletId, String companyId, String strutsPath,
				   String portletClass, String indexerClass,
				   String schedulerClass,  String defaultPreferences,
				   String prefsValidator, boolean prefsUniquePerLayout,
				   boolean prefsOwnedByGroup, boolean useDefaultTemplate,
				   boolean showPortletAccessDenied, boolean showPortletInactive,
				   boolean restoreCurrentView, boolean ns4Compatible,
				   boolean instanceable, boolean narrow, String roles,
				   Map roleMappers, boolean active, boolean include,
				   Map initParams, Integer expCache, Map portletModes,
				   Set supportedLocales, String resourceBundle,
				   PortletInfo portletInfo, Set userAttributes,
				   Map customUserAttributes, boolean warFile) {

		super(portletId, companyId, narrow, roles, active);

		_strutsPath = strutsPath;
		_portletClass = portletClass;
		_indexerClass = indexerClass;
		_schedulerClass = schedulerClass;
		_defaultPreferences = defaultPreferences;
		_prefsValidator = prefsValidator;
		_prefsUniquePerLayout = prefsUniquePerLayout;
		_prefsOwnedByGroup = prefsOwnedByGroup;
		_useDefaultTemplate = useDefaultTemplate;
		_showPortletAccessDenied = showPortletAccessDenied;
		_showPortletInactive = showPortletInactive;
		_restoreCurrentView = restoreCurrentView;
		_ns4Compatible = ns4Compatible;
		_instanceable = instanceable;
		setRoles(roles);
		_roleMappers = roleMappers;
		_include = include;
		_initParams = initParams;
		_expCache = expCache;
		_portletModes = portletModes;
		_supportedLocales = supportedLocales;
		_resourceBundle = resourceBundle;
		_portletInfo = portletInfo;
		_userAttributes = userAttributes;
		_customUserAttributes = customUserAttributes;
		_warFile = warFile;

		if (_instanceable) {
			_clonedInstances = new Hashtable();
		}
	}

	/**
	 * Gets the root portlet id of the portlet.
	 *
	 * @return		the root portlet id of the portlet
	 */
	public String getRootPortletId() {
		return getRootPortletId(getPortletId());
	}

	/**
	 * Gets the struts path of the portlet.
	 *
	 * @return		the struts path of the portlet
	 */
	public String getStrutsPath() {
		return _strutsPath;
	}

	/**
	 * Sets the struts path of the portlet.
	 *
	 * @param		strutsPath the struts path of the portlet
	 */
	public void setStrutsPath(String strutsPath) {
		_strutsPath = strutsPath;
	}

	/**
	 * Gets the name of the portlet class of the portlet.
	 *
	 * @return		the name of the portlet class of the portlet
	 */
	public String getPortletClass() {
		return _portletClass;
	}

	/**
	 * Sets the name of the portlet class of the portlet.
	 *
	 * @param		portletClass the name of the portlet class of the portlet
	 */
	public void setPortletClass(String portletClass) {
		_portletClass = portletClass;
	}

	/**
	 * Gets the name of the indexer class of the portlet.
	 *
	 * @return		the name of the indexer class of the portlet
	 */
	public String getIndexerClass() {
		return _indexerClass;
	}

	/**
	 * Sets the name of the indexer class of the portlet.
	 *
	 * @param		indexerClass the name of the indexer class of the portlet
	 */
	public void setIndexerClass(String indexerClass) {
		_indexerClass = indexerClass;
	}

	/**
	 * Gets the name of the scheduler class of the portlet.
	 *
	 * @return		the name of the scheduler class of the portlet
	 */
	public String getSchedulerClass() {
		return _schedulerClass;
	}

	/**
	 * Sets the name of the scheduler class of the portlet.
	 *
	 * @param		schedulerClass the name of the scheduler class of the
	 *				portlet
	 */
	public void setSchedulerClass(String schedulerClass) {
		_schedulerClass = schedulerClass;
	}

	/**
	 * Gets the default preferences of the portlet.
	 *
	 * @return		the default preferences of the portlet
	 */
	public String getDefaultPreferences() {
		if (Validator.isNull(_defaultPreferences)) {
			return "<portlet-preferences></portlet-preferences>";
		}
		else {
			return _defaultPreferences;
		}
	}

	/**
	 * Sets the default preferences of the portlet.
	 *
	 * @param		defaultPreferences the default preferences of the portlet
	 */
	public void setDefaultPreferences(String defaultPreferences) {
		_defaultPreferences = defaultPreferences;
	}

	/**
	 * Gets the name of the preferences validator class of the portlet.
	 *
	 * @return		the name of the preferences validator class of the portlet
	 */
	public String getPreferencesValidator() {
		return _prefsValidator;
	}

	/**
	 * Sets the name of the preferences validator class of the portlet.
	 *
	 * @param		prefsValidator the name of the preferences validator class
	 *				of the portlet
	 */
	public void setPreferencesValidator(String prefsValidator) {
		if (prefsValidator != null) {

			// Trim this because XDoclet generates preferences validators with
			// extra white spaces

			_prefsValidator = prefsValidator.trim();
		}
		else {
			_prefsValidator = null;
		}
	}

	/**
	 * Returns true if preferences are unique per layout.
	 *
	 * @return		true if preferences are unique per layout
	 */
	public boolean getPreferencesUniquePerLayout() {
		return _prefsUniquePerLayout;
	}

	/**
	 * Returns true if preferences are unique per layout.
	 *
	 * @return		true if preferences are unique per layout
	 */
	public boolean isPreferencesUniquePerLayout() {
		return _prefsUniquePerLayout;
	}

	/**
	 * Sets to true if preferences are unique per layout.
	 *
	 * @param		prefsUniquePerLayout boolean value for whether preferences
	 *				are unique per layout
	 */
	public void setPreferencesUniquePerLayout(boolean prefsUniquePerLayout) {
		_prefsUniquePerLayout = prefsUniquePerLayout;
	}

	/**
	 * Returns true if preferences are owned by the group when the portlet is
	 * shown in a group layout. Returns false if preferences are owned by the
	 * user at all times.
	 *
	 * @return		true if preferences are owned by the group when the portlet
	 *				is shown in a group layout; false if preferences are owned
	 *				by the user at all times.
	 */
	public boolean getPreferencesOwnedByGroup() {
		return _prefsOwnedByGroup;
	}

	/**
	 * Returns true if preferences are owned by the group when the portlet is
	 * shown in a group layout. Returns false if preferences are owned by the
	 * user at all times.
	 *
	 * @return		true if preferences are owned by the group when the portlet
	 *				is shown in a group layout; false if preferences are owned
	 *				by the user at all times.
	 */
	public boolean isPreferencesOwnedByGroup() {
		return _prefsOwnedByGroup;
	}

	/**
	 * Sets to true if preferences are owned by the group when the portlet is
	 * shown in a group layout. Sets to false if preferences are owned by the
	 * user at all times.
	 *
	 * @param		prefsOwnedByGroup boolean value for whether preferences are
	 *				owned by the group when the portlet is shown in a group
	 *				layout or preferences are owned by the user at all times
	 */
	public void setPreferencesOwnedByGroup(boolean prefsOwnedByGroup) {
		_prefsOwnedByGroup = prefsOwnedByGroup;
	}

	/**
	 * Returns true if the portlet uses the default template.
	 *
	 * @return		true if the portlet uses the default template
	 */
	public boolean getUseDefaultTemplate() {
		return _useDefaultTemplate;
	}

	/**
	 * Returns true if the portlet uses the default template.
	 *
	 * @return		true if the portlet uses the default template
	 */
	public boolean isUseDefaultTemplate() {
		return _useDefaultTemplate;
	}

	/**
	 * Sets to true if the portlet uses the default template.
	 *
	 * @param		useDefaultTemplate boolean value for whether the portlet
	 *				uses the default template
	 */
	public void setUseDefaultTemplate(boolean useDefaultTemplate) {
		_useDefaultTemplate = useDefaultTemplate;
	}

	/**
	 * Returns true if users are shown that they do not have access to the
	 * portlet.
	 *
	 * @return		true if users are shown that they do not have access to the
	 *				portlet
	 */
	public boolean getShowPortletAccessDenied() {
		return _showPortletAccessDenied;
	}

	/**
	 * Returns true if users are shown that they do not have access to the
	 * portlet.
	 *
	 * @return		true if users are shown that they do not have access to the
	 *				portlet
	 */
	public boolean isShowPortletAccessDenied() {
		return _showPortletAccessDenied;
	}

	/**
	 * Sets to true if users are shown that they do not have access to the
	 * portlet.
	 *
	 * @param		showPortletAccessDenied boolean value for whether users are
	 *				shown that they do not have access to the portlet
	 */
	public void setShowPortletAccessDenied(boolean showPortletAccessDenied) {
		_showPortletAccessDenied = showPortletAccessDenied;
	}

	/**
	 * Returns true if users are shown that the portlet is inactive.
	 *
	 * @return		true if users are shown that the portlet is inactive
	 */
	public boolean getShowPortletInactive() {
		return _showPortletInactive;
	}

	/**
	 * Returns true if users are shown that the portlet is inactive.
	 *
	 * @return		true if users are shown that the portlet is inactive
	 */
	public boolean isShowPortletInactive() {
		return _showPortletInactive;
	}

	/**
	 * Sets to true if users are shown that the portlet is inactive.
	 *
	 * @param		showPortletInactive boolean value for whether users are
	 *				shown that the portlet is inactive
	 */
	public void setShowPortletInactive(boolean showPortletInactive) {
		_showPortletInactive = showPortletInactive;
	}

	/**
	 * Returns true if the portlet restores to the current view from the
	 * maximized state.
	 *
	 * @return		true if the portlet restores to the current view from the
	 *				maximized state
	 */
	public boolean getRestoreCurrentView() {
		return _restoreCurrentView;
	}

	/**
	 * Returns true if the portlet restores to the current view from the
	 * maximized state.
	 *
	 * @return		true if the portlet restores to the current view from the
	 *				maximized state
	 */
	public boolean isRestoreCurrentView() {
		return _restoreCurrentView;
	}

	/**
	 * Sets to true if the portlet restores to the current view from the
	 * maximized state.
	 *
	 * @param		restoreCurrentView boolean value for whether the portlet
	 *				restores to the current view from the maximized state
	 */
	public void setRestoreCurrentView(boolean restoreCurrentView) {
		_restoreCurrentView = restoreCurrentView;
	}

	/**
	 * Returns true if the portlet is compatible with Netscape 4.
	 *
	 * @return		true if the portlet is compatible with Netscape 4
	 */
	public boolean getNs4Compatible() {
		return _ns4Compatible;
	}

	/**
	 * Returns true if the portlet is compatible with Netscape 4.
	 *
	 * @return		true if the portlet is compatible with Netscape 4
	 */
	public boolean isNs4Compatible() {
		return _ns4Compatible;
	}

	/**
	 * Sets to true if the portlet is compatible with Netscape 4.
	 *
	 * @param		ns4Compatible boolean value for whether the portlet is
	 *				compatible with Netscape 4
	 */
	public void setNs4Compatible(boolean ns4Compatible) {
		_ns4Compatible = ns4Compatible;
	}

	/**
	 * Returns true if the portlet can be added multiple times to a layout.
	 *
	 * @return		true if the portlet can be added multiple times to a layout
	 */
	public boolean getInstanceable() {
		return _instanceable;
	}

	/**
	 * Returns true if the portlet can be added multiple times to a layout.
	 *
	 * @return		true if the portlet can be added multiple times to a layout
	 */
	public boolean isInstanceable() {
		return _instanceable;
	}

	/**
	 * Sets to true if the portlet can be added multiple times to a layout.
	 *
	 * @param		instanceable boolean value for whether the portlet can be
	 *				added multiple times to a layout
	 */
	public void setInstanceable(boolean instanceable) {
		_instanceable = instanceable;
	}

	/**
	 * Sets a string of ordered comma delimited portlet ids.
	 *
	 * @param		roles a string of ordered comma delimited portlet ids
	 */
	public void setRoles(String roles) {
		_rolesArray = StringUtil.split(roles);

		super.setRoles(roles);
	}

	/**
	 * Gets an array of required roles of the portlet.
	 *
	 * @return		an array of required roles of the portlet
	 */
	public String[] getRolesArray() {
		return _rolesArray;
	}

	/**
	 * Sets an array of required roles of the portlet.
	 *
	 * @param		rolesArray an array of required roles of the portlet
	 */
	public void setRolesArray(String[] rolesArray) {
		_rolesArray = rolesArray;

		super.setRoles(StringUtil.merge(rolesArray));
	}

	/**
	 * Gets the role mappers of the portlet.
	 *
	 * @return		role mappers of the portlet
	 */
	public Map getRoleMappers() {
		return _roleMappers;
	}

	/**
	 * Sets the role mappers of the portlet.
	 *
	 * @param		roleMappers the role mappers of the portlet
	 */
	public void setRoleMappers(Map roleMappers) {
		_roleMappers = roleMappers;
	}

	/**
	 * Link the role names set in portlet.xml with the Liferay roles set in
	 * liferay-portlet.xml.
	 */
	public void linkRoles() {
		for (int i = 0; i < _rolesArray.length; i++) {
			String roleLink = (String)_roleMappers.get(_rolesArray[i]);

			if (Validator.isNotNull(roleLink)) {
				_log.debug(
					"Linking role for portlet [" + getPortletId() +
						"] with role-name [" + _rolesArray[i] +
							"] to role-link [" + roleLink + "]");

				_rolesArray[i] = roleLink;
			}
			else {
				_log.error(
					"Unable to link role for portlet [" + getPortletId() +
						"] with role-name [" + _rolesArray[i] +
							"] because role-link is null");
			}
		}

		setRolesArray(_rolesArray);
	}

	/**
	 * Returns true if the portlet has a role with the specified name.
	 *
	 * @return		true if the portlet has a role with the specified name
	 */
	public boolean hasRoleWithName(String roleName) {
		for (int i = 0; i < _rolesArray.length; i++) {
			if (_rolesArray[i].equalsIgnoreCase(roleName)) {
				return true;
			}
		}

		return false;
	}

	/**
	 * Returns true to include the portlet and make it available to be made
	 * active
	 *
	 * @return		true to include the portlet and make it available to be made
	 * 				active
	 */
	public boolean getInclude() {
		return _include;
	}

	/**
	 * Returns true to include the portlet and make it available to be made
	 * active
	 *
	 * @return		true to include the portlet and make it available to be made
	 * 				active
	 */
	public boolean isInclude() {
		return _include;
	}

	/**
	 * Sets to true to include the portlet and make it available to be made
	 * active
	 *
	 * @param		include boolean value for whether to include the portlet and
	 * 				make it available to be made active
	 */
	public void setInclude(boolean include) {
		_include = include;
	}

	/**
	 * Gets the init parameters of the portlet.
	 *
	 * @return		init parameters of the portlet
	 */
	public Map getInitParams() {
		return _initParams;
	}

	/**
	 * Sets the init parameters of the portlet.
	 *
	 * @param		initParams the init parameters of the portlet
	 */
	public void setInitParams(Map initParams) {
		_initParams = initParams;
	}

	/**
	 * Gets expiration cache of the portlet.
	 *
	 * @return		expiration cache of the portlet
	 */
	public Integer getExpCache() {
		return _expCache;
	}

	/**
	 * Sets expiration cache of the portlet.
	 *
	 * @param		expCache expiration cache of the portlet
	 */
	public void setExpCache(Integer expCache) {
		_expCache = expCache;
	}

	/**
	 * Gets the portlet modes of the portlet.
	 *
	 * @return		portlet modes of the portlet
	 */
	public Map getPortletModes() {
		return _portletModes;
	}

	/**
	 * Sets the portlet modes of the portlet.
	 *
	 * @param		portletModes the portlet modes of the portlet
	 */
	public void setPortletModes(Map portletModes) {
		_portletModes = portletModes;
	}

	/**
	 * Returns true if the portlet supports the specified mime type and
	 * portlet mode.
	 *
	 * @return		true if the portlet supports the specified mime type and
	 *				portlet mode
	 */
	public boolean hasPortletMode(String mimeType, PortletMode portletMode) {
		if (portletMode.equals(PortletMode.VIEW)) {
			return true;
		}

		if (mimeType == null) {
			mimeType = Constants.TEXT_HTML;
		}

		Set mimeTypeModes = (Set)_portletModes.get(mimeType);

		if (mimeTypeModes == null) {
			return false;
		}

		return mimeTypeModes.contains(portletMode.toString());
	}

	/**
	 * Gets the supported locales of the portlet.
	 *
	 * @return		supported locales of the portlet
	 */
	public Set getSupportedLocales() {
		return _supportedLocales;
	}

	/**
	 * Sets the supported locales of the portlet.
	 *
	 * @param		supportedLocales the supported locales of the portlet
	 */
	public void setSupportedLocales(Set supportedLocales) {
		_supportedLocales = supportedLocales;
	}

	/**
	 * Gets the resource bundle of the portlet.
	 *
	 * @return		resource bundle of the portlet
	 */
	public String getResourceBundle() {
		return _resourceBundle;
	}

	/**
	 * Sets the resource bundle of the portlet.
	 *
	 * @param		resourceBundle the resource bundle of the portlet
	 */
	public void setResourceBundle(String resourceBundle) {
		_resourceBundle = resourceBundle;
	}

	/**
	 * Gets the portlet info of the portlet.
	 *
	 * @return		portlet info of the portlet
	 */
	public PortletInfo getPortletInfo() {
		return _portletInfo;
	}

	/**
	 * Sets the portlet info of the portlet.
	 *
	 * @param		portletInfo the portlet info of the portlet
	 */
	public void setPortletInfo(PortletInfo portletInfo) {
		_portletInfo = portletInfo;
	}

	/**
	 * Gets the user attributes of the portlet.
	 *
	 * @return		user attributes of the portlet
	 */
	public Set getUserAttributes() {
		return _userAttributes;
	}

	/**
	 * Sets the user attributes of the portlet.
	 *
	 * @param		userAttributes the user attributes of the portlet
	 */
	public void setUserAttributes(Set userAttributes) {
		_userAttributes = userAttributes;
	}

	/**
	 * Gets the custom user attributes of the portlet.
	 *
	 * @return		custom user attributes of the portlet
	 */
	public Map getCustomUserAttributes() {
		return _customUserAttributes;
	}

	/**
	 * Sets the custom user attributes of the portlet.
	 *
	 * @param		customUserAttributes the custom user attributes of the
	 *				portlet
	 */
	public void setCustomUserAttributes(Map customUserAttributes) {
		_customUserAttributes = customUserAttributes;
	}

	/**
	 * Returns true if the portlet is found in a WAR file.
	 *
	 * @return		true if the portlet is found in a WAR file
	 */
	public boolean getWARFile() {
		return _warFile;
	}

	/**
	 * Returns true if the portlet is found in a WAR file.
	 *
	 * @return		true if the portlet is found in a WAR file
	 */
	public boolean isWARFile() {
		return _warFile;
	}

	/**
	 * Sets to true if the portlet is found in a WAR file.
	 *
	 * @param		warFile boolean value for whether the portlet is found in a
	 *				WAR file
	 */
	public void setWARFile(boolean warFile) {
		_warFile = warFile;
	}

	/**
	 * Returns true if the portlet is found in a WAR file.
	 *
	 * @param		portletId the cloned instance portlet id
	 * @return		a cloned instance of the portlet
	 */
	public Portlet getClonedInstance(String portletId) {
		Portlet clonedInstance = (Portlet)_clonedInstances.get(portletId);

		if (clonedInstance == null) {
			clonedInstance = (Portlet)clone();

			clonedInstance.setPortletId(portletId);

			// Disable caching of cloned instances until we can figure out how
			// to elegantly refresh the cache when the portlet is dynamically
			// updated by the user. For example, the user might change the
			// portlet from narrow to wide. Cloned instances that are cached
			// would not see the new change. We can then also cache static
			// portlet instances.

			//_clonedInstances.put(portletId, clonedInstance);
		}

		return clonedInstance;
	}

	/**
	 * Returns true if the portlet is a static portlet that is cannot be moved.
	 *
	 * @return		true if the portlet is a static portlet that is cannot be
	 *				moved
	 */
	public boolean getStatic() {
		return _staticPortlet;
	}

	/**
	 * Returns true if the portlet is a static portlet that is cannot be moved.
	 *
	 * @return		true if the portlet is a static portlet that is cannot be
	 *				moved
	 */
	public boolean isStatic() {
		return _staticPortlet;
	}

	/**
	 * Sets to true if the portlet is a static portlet that is cannot be moved.
	 *
	 * @param		staticPortlet boolean value for whether the portlet is a
	 *				static portlet that is cannot be moved found in a
	 */
	public void setStatic(boolean staticPortlet) {
		_staticPortlet = staticPortlet;
	}

	/**
	 * Initialize the portlet instance.
	 */
	public CachePortlet init(PortletConfig portletConfig)
		throws PortletException {

		return init(portletConfig, null);
	}

	/**
	 * Initialize the portlet instance.
	 */
	public CachePortlet init(
			PortletConfig portletConfig, javax.portlet.Portlet portletInstance)
		throws PortletException {

		CachePortlet cachePortlet = null;

		try {
			if (portletInstance == null) {
				portletInstance = (javax.portlet.Portlet)
					Class.forName(getPortletClass()).newInstance();
			}

			cachePortlet = new CachePortlet(
				portletInstance, portletConfig.getPortletContext(),
				getExpCache());

			cachePortlet.init(portletConfig);
		}
		catch (ClassNotFoundException cnofe) {
			throw new UnavailableException(cnofe.getMessage());
		}
		catch (InstantiationException ie) {
			throw new UnavailableException(ie.getMessage());
		}
		catch (IllegalAccessException iae) {
			throw new UnavailableException(iae.getMessage());
		}

		return cachePortlet;
	}

	/**
	 * Creates and returns a copy of this object.
	 *
     * @return		a copy of this object
	 */
	public Object clone() {
		return new Portlet(
			getPortletId(), getCompanyId(), getStrutsPath(), getPortletClass(),
			getIndexerClass(), getSchedulerClass(), getDefaultPreferences(),
			getPreferencesValidator(), isPreferencesUniquePerLayout(),
			isPreferencesOwnedByGroup(), isUseDefaultTemplate(),
			isShowPortletAccessDenied(), isShowPortletInactive(),
			isRestoreCurrentView(), isNs4Compatible(), isInstanceable(),
			isNarrow(), getRoles(), getRoleMappers(), isActive(), getInclude(),
			getInitParams(), getExpCache(), getPortletModes(),
			getSupportedLocales(), getResourceBundle(), getPortletInfo(),
			getUserAttributes(), getCustomUserAttributes(), isWARFile());
	}

	/**
	 * Compares this portlet to the specified object.
	 *
     * @param		obj the object to compare this portlet against
     * @return		the value 0 if the argument portlet is equal to this
     *				portlet; a value less than -1 if this portlet is less than
     *				the portlet argument; and 1 if this portlet is greater than
     *				the portlet argument
	 */
	public int compareTo(Object obj) {
		Portlet portlet = (Portlet)obj;

		return getPortletId().compareTo(portlet.getPortletId());
	}

	/**
	 * Log instance for this class.
	 */
	private static final Log _log = LogFactory.getLog(Portlet.class);

	/**
	 * The struts path of the portlet.
	 */
	private String _strutsPath;

	/**
	 * The name of the portlet class of the portlet.
	 */
	private String _portletClass;

	/**
	 * The name of the indexer class of the portlet.
	 */
	private String _indexerClass;

	/**
	 * The name of the scheduler class of the portlet.
	 */
	private String _schedulerClass;

	/**
	 * The default preferences of the portlet.
	 */
	private String _defaultPreferences;

	/**
	 * The name of the preferences validator class of the portlet.
	 */
	private String _prefsValidator;

	/**
	 * True if preferences are unique per layout.
	 */
	private boolean _prefsUniquePerLayout = true;

	/**
	 * True if preferences are owned by the group when the portlet is shown in a
	 * group layout. False if preferences are owned by the user at all times.
	 */
	private boolean _prefsOwnedByGroup = true;

	/**
	 * True if the portlet uses the default template.
     */
	private boolean _useDefaultTemplate = true;

	/**
	 * True if users are shown that they do not have access to the portlet.
     */
	private boolean _showPortletAccessDenied = GetterUtil.getBoolean(
		PropsUtil.get(PropsUtil.LAYOUT_SHOW_PORTLET_ACCESS_DENIED));

	/**
	 * True if users are shown that the portlet is inactive.
     */
	private boolean _showPortletInactive = GetterUtil.getBoolean(
		PropsUtil.get(PropsUtil.LAYOUT_SHOW_PORTLET_INACTIVE));

	/**
	 * True if the portlet restores to the current view from the maximized
	 * state.
     */
	private boolean _restoreCurrentView;

	/**
	 * True if the portlet is compatible with Netscape 4.
     */
	private boolean _ns4Compatible = true;

	/**
	 * True if the portlet can be added multiple times to a layout.
     */
	private boolean _instanceable;

	/**
	 * An array of required roles of the portlet.
	 */
	private String[] _rolesArray;

	/**
	 * The role mappers of the portlet.
	 */
	private Map _roleMappers;

	/**
	 * True to include the portlet and make it available to be made active.
	 */
	private boolean _include;

	/**
	 * The init parameters of the portlet.
	 */
	private Map _initParams;

	/**
	 * The expiration cache of the portlet.
	 */
	private Integer _expCache;

	/**
	 * The portlet modes of the portlet.
	 */
	private Map _portletModes;

	/**
	 * The supported locales of the portlet.
	 */
	private Set _supportedLocales;

	/**
	 * The resource bundle of the portlet.
	 */
	private String _resourceBundle;

	/**
	 * The portlet info of the portlet.
	 */
	private PortletInfo _portletInfo;

	/**
	 * The user attributes of the portlet.
	 */
	private Set _userAttributes;

	/**
	 * The custom user attributes of the portlet.
	 */
	private Map _customUserAttributes;

	/**
	 * True if the portlet is found in a WAR file.
	 */
	private boolean _warFile;

	/**
	 * The cloned instances of the portlet.
	 */
	private Map _clonedInstances;

	/**
	 * True if the portlet is a static portlet that is cannot be moved.
	 */
	private boolean _staticPortlet;

}