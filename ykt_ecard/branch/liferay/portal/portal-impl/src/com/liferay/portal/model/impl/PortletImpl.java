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

import com.liferay.portal.kernel.lar.PortletDataHandler;
import com.liferay.portal.kernel.plugin.PluginPackage;
import com.liferay.portal.kernel.pop.MessageListener;
import com.liferay.portal.kernel.portlet.ConfigurationAction;
import com.liferay.portal.kernel.portlet.FriendlyURLMapper;
import com.liferay.portal.kernel.portlet.PortletLayoutListener;
import com.liferay.portal.kernel.servlet.URLEncoder;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.ActivityTrackerInterpreter;
import com.liferay.portal.model.PluginSetting;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletInfo;
import com.liferay.portal.model.User;
import com.liferay.portal.service.RoleLocalServiceUtil;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.servlet.PortletContextPool;
import com.liferay.portal.servlet.PortletContextWrapper;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsValues;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

import javax.portlet.PortletMode;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="PortletImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletImpl extends PortletModelImpl implements Portlet {

	/**
	 * Plugin type
	 */
	public static final String PLUGIN_TYPE = "portlet";

	/**
	 * War file separator.
	 */
	public static final String WAR_SEPARATOR = "_WAR_";

	/**
	 * Instance separator.
	 */
	public static final String INSTANCE_SEPARATOR = "_INSTANCE_";

	/**
	 * Layout separator.
	 */
	public static final String LAYOUT_SEPARATOR = "_LAYOUT_";

	/**
	 * Default preferences.
	 */
	public static final String DEFAULT_PREFERENCES = "<portlet-preferences />";

	/**
	 * User principal strategy for screen name.
	 */
	public static final String USER_PRINCIPAL_STRATEGY_SCREEN_NAME =
		"screenName";

	/**
	 * User principal strategy for screen name.
	 */
	public static final String USER_PRINCIPAL_STRATEGY_USER_ID = "userId";

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
	 * Gets the instance id of the portlet.
	 *
	 * @param		portletId the portlet id of the portlet
	 * @return		the instance id of the portlet
	 */
	public static String getInstanceId(String portletId) {
		int pos = portletId.indexOf(INSTANCE_SEPARATOR);

		if (pos == -1) {
			return null;
		}
		else {
			return portletId.substring(
				pos + INSTANCE_SEPARATOR.length(), portletId.length());
		}
	}

	/**
	 * Constructs a portlet with no parameters.
	 */
	public PortletImpl() {
	}

	/**
	 * Constructs a portlet with the specified parameters.
	 */
	public PortletImpl(long companyId, String portletId) {
		setCompanyId(companyId);
		setPortletId(portletId);
		setStrutsPath(portletId);
		setActive(true);
		_headerPortalCss = new ArrayList();
		_headerPortletCss = new ArrayList();
		_headerPortalJavaScript = new ArrayList();
		_headerPortletJavaScript = new ArrayList();
		_footerPortalCss = new ArrayList();
		_footerPortletCss = new ArrayList();
		_footerPortalJavaScript = new ArrayList();
		_footerPortletJavaScript = new ArrayList();
		_unlinkedRoles = new HashSet();
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
	public PortletImpl(
		String portletId, PluginPackage pluginPackage,
		PluginSetting pluginSetting, long companyId, String icon,
		String virtualPath, String strutsPath, String displayName,
		String portletClass, String configurationActionClass,
		String indexerClass, String openSearchClass, String schedulerClass,
		String portletURLClass, String friendlyURLMapperClass,
		String urlEncoderClass, String portletDataHandlerClass,
		String portletLayoutListenerClass,
		String activityTrackerInterpreterClass, String popMessageListenerClass,
		String defaultPreferences, String prefsValidator,
		boolean prefsCompanyWide, boolean prefsUniquePerLayout,
		boolean prefsOwnedByGroup, boolean useDefaultTemplate,
		boolean showPortletAccessDenied, boolean showPortletInactive,
		boolean actionURLRedirect, boolean restoreCurrentView,
		boolean maximizeEdit, boolean maximizeHelp, boolean popUpPrint,
		boolean layoutCacheable, boolean instanceable,
		String userPrincipalStrategy, boolean privateRequestAttributes,
		boolean privateSessionAttributes, int renderWeight, boolean ajaxable,
		List headerPortalCss, List headerPortletCss,
		List headerPortalJavaScript, List headerPortletJavaScript,
		List footerPortalCss, List footerPortletCss,
		List footerPortalJavaScript, List footerPortletJavaScript,
		String cssClassWrapper, boolean addDefaultResource, String roles,
		Set unlinkedRoles, Map roleMappers, boolean system, boolean active,
		boolean include, Map initParams, Integer expCache, Map portletModes,
		Set supportedLocales, String resourceBundle, PortletInfo portletInfo,
		Set userAttributes, Map customUserAttributes, String servletContextName,
		List servletURLPatterns) {

		setPortletId(portletId);
		_pluginPackage = pluginPackage;
		_defaultPluginSetting = pluginSetting;
		setCompanyId(companyId);
		_icon = icon;
		_virtualPath = virtualPath;
		_strutsPath = strutsPath;
		_displayName = displayName;
		_portletClass = portletClass;
		_configurationActionClass = configurationActionClass;
		_indexerClass = indexerClass;
		_openSearchClass = openSearchClass;
		_schedulerClass = schedulerClass;
		_portletURLClass = portletURLClass;
		_friendlyURLMapperClass = friendlyURLMapperClass;
		_urlEncoderClass = urlEncoderClass;
		_portletDataHandlerClass = portletDataHandlerClass;
		_portletLayoutListenerClass = portletLayoutListenerClass;
		_activityTrackerInterpreterClass = activityTrackerInterpreterClass;
		_popMessageListenerClass = popMessageListenerClass;
		_defaultPreferences = defaultPreferences;
		_prefsValidator = prefsValidator;
		_prefsCompanyWide = prefsCompanyWide;
		_prefsUniquePerLayout = prefsUniquePerLayout;
		_prefsOwnedByGroup = prefsOwnedByGroup;
		_useDefaultTemplate = useDefaultTemplate;
		_showPortletAccessDenied = showPortletAccessDenied;
		_showPortletInactive = showPortletInactive;
		_actionURLRedirect = actionURLRedirect;
		_restoreCurrentView = restoreCurrentView;
		_maximizeEdit = maximizeEdit;
		_maximizeHelp = maximizeHelp;
		_popUpPrint = popUpPrint;
		_layoutCacheable = layoutCacheable;
		_instanceable = instanceable;
		_userPrincipalStrategy = userPrincipalStrategy;
		_privateRequestAttributes = privateRequestAttributes;
		_privateSessionAttributes = privateSessionAttributes;
		_renderWeight = renderWeight;
		_ajaxable = ajaxable;
		_headerPortalCss = headerPortalCss;
		_headerPortletCss = headerPortletCss;
		_headerPortalJavaScript = headerPortalJavaScript;
		_headerPortletJavaScript = headerPortletJavaScript;
		_footerPortalCss = footerPortalCss;
		_footerPortletCss = footerPortletCss;
		_footerPortalJavaScript = footerPortalJavaScript;
		_footerPortletJavaScript = footerPortletJavaScript;
		_cssClassWrapper = cssClassWrapper;
		_addDefaultResource = addDefaultResource;
		setRoles(roles);
		_unlinkedRoles = unlinkedRoles;
		_roleMappers = roleMappers;
		_system = system;
		setActive(active);
		_include = include;
		_initParams = initParams;
		_expCache = expCache;
		_portletModes = portletModes;
		_supportedLocales = supportedLocales;
		_resourceBundle = resourceBundle;
		_portletInfo = portletInfo;
		_userAttributes = userAttributes;
		_customUserAttributes = customUserAttributes;
		setServletContextName(servletContextName);
		_servletURLPatterns = servletURLPatterns;

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
	 * Gets the instance id of the portlet.
	 *
	 * @return		the instance id of the portlet
	 */
	public String getInstanceId() {
		return getInstanceId(getPortletId());
	}

	/**
	 * Gets the plugin id of the portlet.
	 *
	 * @return 		the plugin id of the portlet
	 */
	public String getPluginId() {
		return getRootPortletId();
	}

	/**
	 * Gets the plugin type of the portlet.
	 *
	 * @return 		the plugin type of the portlet
	 */
	public String getPluginType() {
		return PLUGIN_TYPE;
	}

	/**
	 * Get the package to which the portlet belongs to.
	 *
	 * @return		the plugin package of the portlet
	 */
	public PluginPackage getPluginPackage() {
		return _pluginPackage;
	}

	/**
	 * Sets the plugin package to which this portlet belongs to.
	 *
	 * @param		pluginPackage the plugin package
	 */
	public void setPluginPackage(PluginPackage pluginPackage) {
		_pluginPackage = pluginPackage;
	}

	/**
	 * Get the default plugin settings of the portlet.
	 *
	 * @return		the plugin settings
	 */
	public PluginSetting getDefaultPluginSetting() {
		return _defaultPluginSetting;
	}

	/**
	 * Sets the default plugin settings of the portlet.
	 *
	 * @param		pluginSetting the plugin setting
	 */
	public void setDefaultPluginSetting(PluginSetting pluginSetting) {
		_defaultPluginSetting = pluginSetting;
	}

	/**
	 * Gets the icon of the portlet.
	 *
	 * @return		the icon of the portlet
	 */
	public String getIcon() {
		return _icon;
	}

	/**
	 * Sets the icon of the portlet.
	 *
	 * @param		icon the icon of the portlet
	 */
	public void setIcon(String icon) {
		_icon = icon;
	}

	/**
	 * Gets the virtual path of the portlet.
	 *
	 * @return		the virtual path of the portlet
	 */
	public String getVirtualPath() {
		return _virtualPath;
	}

	/**
	 * Sets the virtual path of the portlet.
	 *
	 * @param		virtualPath the virtual path of the portlet
	 */
	public void setVirtualPath(String virtualPath) {
		if (_warFile && Validator.isNull(virtualPath)) {
			virtualPath = PropsValues.PORTLET_VIRTUAL_PATH;
		}

		_virtualPath = virtualPath;
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
	 * Gets the display name of the portlet.
	 *
	 * @return		the display name of the portlet
	 */
	public String getDisplayName() {
		return _displayName;
	}

	/**
	 * Sets the display name of the portlet.
	 *
	 * @param		displayName the display name of the portlet
	 */
	public void setDisplayName(String displayName) {
		_displayName = displayName;
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
	 * Gets the configuration action class of the portlet.
	 *
	 * @return		the configuration action class of the portlet
	 */
	public String getConfigurationActionClass() {
		return _configurationActionClass;
	}

	/**
	 * Sets the configuration action class of the portlet.
	 *
	 * @param		configurationActionClass the configuration action class of
	 *				the portlet
	 */
	public void setConfigurationActionClass(String configurationActionClass) {
		_configurationActionClass = configurationActionClass;
	}

	/**
	 * Gets the configuration action instance of the portlet.
	 *
	 * @return		the configuration action instance of the portlet
	 */
	public ConfigurationAction getConfigurationActionInstance() {
		if (Validator.isNotNull(getConfigurationActionClass())) {
			if (isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(getRootPortletId());

				return pcw.getConfigurationActionInstance();
			}
			else {
				return (ConfigurationAction)InstancePool.get(
					getConfigurationActionClass());
			}
		}

		return null;
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
	 * Gets the name of the open search class of the portlet.
	 *
	 * @return		the name of the open search class of the portlet
	 */
	public String getOpenSearchClass() {
		return _openSearchClass;
	}

	/**
	 * Sets the name of the open search class of the portlet.
	 *
	 * @param		openSearchClass the name of the open search class of the
	 *				portlet
	 */
	public void setOpenSearchClass(String openSearchClass) {
		_openSearchClass = openSearchClass;
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
	 * Gets the name of the portlet URL class of the portlet.
	 *
	 * @return		the name of the portlet URL class of the portlet
	 */
	public String getPortletURLClass() {
		return _portletURLClass;
	}

	/**
	 * Sets the name of the portlet URL class of the portlet.
	 *
	 * @param		portletURLClass the name of the portlet URL class of the
	 *				portlet
	 */
	public void setPortletURLClass(String portletURLClass) {
		_portletURLClass = portletURLClass;
	}

	/**
	 * Gets the name of the friendly URL mapper class of the portlet.
	 *
	 * @return		the name of the friendly URL mapper class of the portlet
	 */
	public String getFriendlyURLMapperClass() {
		return _friendlyURLMapperClass;
	}

	/**
	 * Sets the name of the friendly URL mapper class of the portlet.
	 *
	 * @param		friendlyURLMapperClass the name of the friendly URL plugin
	 *				class of the portlet
	 */
	public void setFriendlyURLMapperClass(String friendlyURLMapperClass) {
		_friendlyURLMapperClass = friendlyURLMapperClass;
	}

	/**
	 * Gets the friendly URL mapper instance of the portlet.
	 *
	 * @return		the friendly URL mapper instance of the portlet
	 */
	public FriendlyURLMapper getFriendlyURLMapperInstance() {
		if (Validator.isNotNull(getFriendlyURLMapperClass())) {
			if (isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(getRootPortletId());

				return pcw.getFriendlyURLMapperInstance();
			}
			else {
				return (FriendlyURLMapper)InstancePool.get(
					getFriendlyURLMapperClass());
			}
		}

		return null;
	}

	/**
	 * Gets the name of the URL encoder class of the portlet.
	 *
	 * @return		the name of the URL encoder class of the portlet
	 */
	public String getURLEncoderClass() {
		return _urlEncoderClass;
	}

	/**
	 * Sets the name of the URL encoder class of the portlet.
	 *
	 * @param		urlEncoderClass the name of the URL encoder class of the
	 *				portlet
	 */
	public void setURLEncoderClass(String urlEncoderClass) {
		_urlEncoderClass = urlEncoderClass;
	}

	/**
	 * Gets the URL encoder instance of the portlet.
	 *
	 * @return		the URL encoder instance of the portlet
	 */
	public URLEncoder getURLEncoderInstance() {
		if (Validator.isNotNull(getURLEncoderClass())) {
			if (isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(getRootPortletId());

				return pcw.getURLEncoderInstance();
			}
			else {
				return (URLEncoder)InstancePool.get(getURLEncoderClass());
			}
		}

		return null;
	}

	/**
	 * Gets the name of the portlet data handler class of the portlet.
	 *
	 * @return		the name of the portlet data handler class of the portlet
	 */
	public String getPortletDataHandlerClass() {
		return _portletDataHandlerClass;
	}

	/**
	 * Sets the name of the portlet data handler class of the portlet.
	 *
	 * @param		portletDataHandlerClass the name of portlet data handler
	 *				class of the portlet
	 */
	public void setPortletDataHandlerClass(String portletDataHandlerClass) {
		_portletDataHandlerClass = portletDataHandlerClass;
	}

	/**
	 * Gets the portlet data handler instance of the portlet.
	 *
	 * @return		the portlet data handler instance of the portlet
	 */
	public PortletDataHandler getPortletDataHandlerInstance() {
		if (Validator.isNotNull(getPortletDataHandlerClass())) {
			if (isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(getRootPortletId());

				return pcw.getPortletDataHandlerInstance();
			}
			else {
				return (PortletDataHandler)InstancePool.get(
					getPortletDataHandlerClass());
			}
		}

		return null;
	}

	/**
	 * Gets the portlet layout listener of the portlet.
	 *
	 * @return		the name of the portlet layout listener class of the portlet
	 */
	public PortletLayoutListener getPortletLayoutListener() {
		if (Validator.isNull(getPortletLayoutListenerClass())) {
			return null;
		}

		return (PortletLayoutListener)InstancePool.get(
			getPortletLayoutListenerClass());
	}

	/**
	 * Gets the name of the portlet layout listener class of the portlet.
	 *
	 * @return		the name of the portlet layout listener class of the portlet
	 */
	public String getPortletLayoutListenerClass() {
		return _portletLayoutListenerClass;
	}

	/**
	 * Sets the name of the portlet layout listener class of the portlet.
	 *
	 * @param		portletLayoutListenerClass the name of the portlet layout
	 *				listener class of the portlet
	 */
	public void setPortletLayoutListenerClass(
		String portletLayoutListenerClass) {

		_portletLayoutListenerClass = portletLayoutListenerClass;
	}

	/**
	 * Gets the name of the activity tracker interpreter class of the portlet.
	 *
	 * @return		the name of the activity tracker interpreter class of the
	 *				portlet
	 */
	public String getActivityTrackerInterpreterClass() {
		return _activityTrackerInterpreterClass;
	}

	/**
	 * Sets the name of the activity tracker interpreter class of the portlet.
	 *
	 * @param		activityTrackerInterpreterClass the name of the activity
	 *				tracker interpreter class of the portlet
	 */
	public void setActivityTrackerInterpreterClass(
		String activityTrackerInterpreterClass) {

		_activityTrackerInterpreterClass = activityTrackerInterpreterClass;
	}

	/**
	 * Gets the name of the activity tracker interpreter instance of the
	 * portlet.
	 *
	 * @return		the name of the activity tracker interpreter instance of the
	 *				portlet
	 */
	public ActivityTrackerInterpreter getActivityTrackerInterpreterInstance() {
		if (Validator.isNotNull(getActivityTrackerInterpreterClass())) {
			if (isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(getRootPortletId());

				return pcw.getActivityTrackerInterpreterInstance();
			}
			else {
				return (ActivityTrackerInterpreter)InstancePool.get(
					getActivityTrackerInterpreterClass());
			}
		}

		return null;
	}

	/**
	 * Gets the name of the POP message listener class of the portlet.
	 *
	 * @return		the name of the POP message listener class of the portlet
	 */
	public String getPopMessageListenerClass() {
		return _popMessageListenerClass;
	}

	/**
	 * Sets the name of the POP message listener class of the portlet.
	 *
	 * @param		popMessageListenerClass the name of the POP message listener
	 *				class of the portlet
	 */
	public void setPopMessageListenerClass(String popMessageListenerClass) {
		_popMessageListenerClass = popMessageListenerClass;
	}

	/**
	 * Gets the POP message listener instance of the portlet.
	 *
	 * @return		the POP message listener instance of the portlet
	 */
	public MessageListener getPopMessageListenerInstance() {
		if (Validator.isNotNull(getPopMessageListenerClass())) {
			if (isWARFile()) {
				PortletContextWrapper pcw =
					PortletContextPool.get(getRootPortletId());

				return pcw.getPopMessageListenerInstance();
			}
			else {
				return (MessageListener)InstancePool.get(
					getPopMessageListenerClass());
			}
		}

		return null;
	}

	/**
	 * Gets the default preferences of the portlet.
	 *
	 * @return		the default preferences of the portlet
	 */
	public String getDefaultPreferences() {
		if (Validator.isNull(_defaultPreferences)) {
			return DEFAULT_PREFERENCES;
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
	 * Returns true if preferences are shared across the entire company.
	 *
	 * @return		true if preferences are shared across the entire company
	 */
	public boolean getPreferencesCompanyWide() {
		return _prefsCompanyWide;
	}

	/**
	 * Returns true if preferences are shared across the entire company.
	 *
	 * @return		true if preferences are shared across the entire company
	 */
	public boolean isPreferencesCompanyWide() {
		return _prefsCompanyWide;
	}

	/**
	 * Sets to true if preferences are shared across the entire company.
	 *
	 * @param		prefsCompanyWide boolean value for whether preferences
	 *				are shared across the entire company
	 */
	public void setPreferencesCompanyWide(boolean prefsCompanyWide) {
		_prefsCompanyWide = prefsCompanyWide;
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
	 * Returns true if an action URL for this portlet should cause an auto
	 * redirect.
	 *
	 * @return		true if an action URL for this portlet should cause an auto
	 *				redirect
	 */
	public boolean getActionURLRedirect() {
		return _actionURLRedirect;
	}

	/**
	 * Returns true if an action URL for this portlet should cause an auto
	 * redirect.
	 *
	 * @return		true if an action URL for this portlet should cause an auto
	 *				redirect
	 */
	public boolean isActionURLRedirect() {
		return _actionURLRedirect;
	}

	/**
	 * Sets to true if an action URL for this portlet should cause an auto
	 * redirect.
	 *
	 * @param		actionURLRedirect boolean value for whether an action URL
	 *				for this portlet should cause an auto redirect
	 */
	public void setActionURLRedirect(boolean actionURLRedirect) {
		_actionURLRedirect = actionURLRedirect;
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
	 * Returns true if the portlet goes into the maximized state when the user
	 * goes into the edit mode.
	 *
	 * @return		true if the portlet goes into the maximized state when the
	 *				user goes into the edit mode
	 */
	public boolean getMaximizeEdit() {
		return _maximizeEdit;
	}

	/**
	 * Returns true if the portlet goes into the maximized state when the user
	 * goes into the edit mode.
	 *
	 * @return		true if the portlet goes into the maximized state when the
	 *				user goes into the edit mode
	 */
	public boolean isMaximizeEdit() {
		return _maximizeEdit;
	}

	/**
	 * Sets to true if the portlet goes into the maximized state when the user
	 * goes into the edit mode.
	 *
	 * @param		maximizeEdit boolean value for whether the portlet goes into
	 *				the maximized state when the user goes into the edit mode
	 */
	public void setMaximizeEdit(boolean maximizeEdit) {
		_maximizeEdit = maximizeEdit;
	}

	/**
	 * Returns true if the portlet goes into the maximized state when the user
	 * goes into the help mode.
	 *
	 * @return		true if the portlet goes into the maximized state when the
	 *				user goes into the help mode
	 */
	public boolean getMaximizeHelp() {
		return _maximizeHelp;
	}

	/**
	 * Returns true if the portlet goes into the maximized state when the user
	 * goes into the help mode.
	 *
	 * @return		true if the portlet goes into the maximized state when the
	 *				user goes into the help mode
	 */
	public boolean isMaximizeHelp() {
		return _maximizeHelp;
	}

	/**
	 * Sets to true if the portlet goes into the maximized state when the user
	 * goes into the help mode.
	 *
	 * @param		maximizeHelp boolean value for whether the portlet goes into
	 *				the maximized state when the user goes into the help mode
	 */
	public void setMaximizeHelp(boolean maximizeHelp) {
		_maximizeHelp = maximizeHelp;
	}

	/**
	 * Returns true if the portlet goes into the pop up state when the user goes
	 * into the print mode.
	 *
	 * @return		true if the portlet goes into the pop up state when the user
	 *				goes into the print mode
	 */
	public boolean getPopUpPrint() {
		return _popUpPrint;
	}

	/**
	 * Returns true if the portlet goes into the pop up state when the user goes
	 * into the print mode.
	 *
	 * @return		true if the portlet goes into the pop up state when the user
	 *				goes into the print mode
	 */
	public boolean isPopUpPrint() {
		return _popUpPrint;
	}

	/**
	 * Sets to true if the portlet goes into the pop up state when the user goes
	 * into the print mode.
	 *
	 * @param		popUpPrint boolean value for whether the portlet goes into
	 *				the pop up state when the user goes into the print mode
	 */
	public void setPopUpPrint(boolean popUpPrint) {
		_popUpPrint = popUpPrint;
	}

	/**
	 * Returns true to allow the portlet to be cached within the layout.
	 *
	 * @return		true if the portlet can be cached within the layout
	 */
	public boolean getLayoutCacheable() {
		return _layoutCacheable;
	}

	/**
	 * Returns true to allow the portlet to be cached within the layout.
	 *
	 * @return		true if the portlet can be cached within the layout
	 */
	public boolean isLayoutCacheable() {
		return _layoutCacheable;
	}

	/**
	 * Sets to true to allow the portlet to be cached within the layout.
	 *
	 * @param	layoutCacheable boolean value for whether the portlet can be
	 *			cached within the layout
	 */
	public void setLayoutCacheable(boolean layoutCacheable) {
		_layoutCacheable = layoutCacheable;
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
	 * Gets the user principal strategy of the portlet.
	 *
	 * @return		the user principal strategy of the portlet
	 */
	public String getUserPrincipalStrategy() {
		return _userPrincipalStrategy;
	}

	/**
	 * Sets the user principal strategy of the portlet.
	 *
	 * @param		userPrincipalStrategy the user principal strategy of the
	 *				portlet
	 */
	public void setUserPrincipalStrategy(String userPrincipalStrategy) {
		if (Validator.isNotNull(userPrincipalStrategy)) {
			_userPrincipalStrategy = userPrincipalStrategy;
		}
	}

	/**
	 * Returns true if the portlet does not share request attributes with the
	 * portal or portlets from another WAR.
	 *
	 * @return		true if the portlet does not share request attributes with
	 *				the portal or portlets from another WAR
	 */
	public boolean getPrivateRequestAttributes() {
		return _privateRequestAttributes;
	}

	/**
	 * Returns true if the portlet does not share request attributes with the
	 * portal or portlets from another WAR.
	 *
	 * @return		true if the portlet does not share request attributes with
	 *				the portal or portlets from another WAR
	 */
	public boolean isPrivateRequestAttributes() {
		return _privateRequestAttributes;
	}

	/**
	 * Sets to true if the portlet does not share request attributes with the
	 * portal or portlets from another WAR.
	 *
	 * @param		privateRequestAttributes boolean value for whether the
	 *				portlet shares request attributes with the portal or
	 *				portlets from another WAR
	 */
	public void setPrivateRequestAttributes(boolean privateRequestAttributes) {
		_privateRequestAttributes = privateRequestAttributes;
	}

	/**
	 * Returns true if the portlet does not share session attributes with the
	 * portal.
	 *
	 * @return		true if the portlet does not share session attributes with
	 *				the portal
	 */
	public boolean getPrivateSessionAttributes() {
		return _privateSessionAttributes;
	}

	/**
	 * Returns true if the portlet does not share session attributes with the
	 * portal.
	 *
	 * @return		true if the portlet does not share session attributes with
	 *				the portal
	 */
	public boolean isPrivateSessionAttributes() {
		return _privateSessionAttributes;
	}

	/**
	 * Sets to true if the portlet does not share session attributes with the
	 * portal.
	 *
	 * @param		privateSessionAttributes boolean value for whether the
	 *				portlet shares session attributes with the portal
	 */
	public void setPrivateSessionAttributes(boolean privateSessionAttributes) {
		_privateSessionAttributes = privateSessionAttributes;
	}

	/**
	 * Returns the render weight of the portlet.
	 *
	 * @return		the render weight of the portlet
	 */
	public int getRenderWeight() {
		return _renderWeight;
	}

	/**
	 * Sets the render weight of the portlet.
	 *
	 * @param		renderWeight int value for the render weight of the portlet
	 */
	public void setRenderWeight(int renderWeight) {
		_renderWeight = renderWeight;
	}

	/**
	 * Returns true if the portlet can be displayed via Ajax.
	 *
	 * @return		true if the portlet can be displayed via Ajax
	 */
	public boolean getAjaxable() {
		return _ajaxable;
	}

	/**
	 * Returns true if the portlet can be displayed via Ajax.
	 *
	 * @return		true if the portlet can be displayed via Ajax
	 */
	public boolean isAjaxable() {
		return _ajaxable;
	}

	/**
	 * Sets to true if the portlet can be displayed via Ajax.
	 *
	 * @param		ajaxable boolean value for whether the portlet can be
	 *				displayed via Ajax
	 */
	public void setAjaxable(boolean ajaxable) {
		_ajaxable = ajaxable;
	}

	/**
	 * Gets a list of CSS files that will be referenced from the page's header
	 * relative to the portal's context path.
	 *
	 * @return		a list of CSS files that will be referenced from the page's
	 *				header relative to the portal's context path
	 */
	public List getHeaderPortalCss() {
		return _headerPortalCss;
	}

	/**
	 * Sets a list of CSS files that will be referenced from the page's header
	 * relative to the portal's context path.
	 *
	 * @param		headerPortalCss a list of CSS files that will be referenced
	 *				from the page's header relative to the portal's context path
	 */
	public void setHeaderPortalCss(List headerPortalCss) {
		_headerPortalCss = headerPortalCss;
	}

	/**
	 * Gets a list of CSS files that will be referenced from the page's header
	 * relative to the portlet's context path.
	 *
	 * @return		a list of CSS files that will be referenced from the page's
	 *				header relative to the portlet's context path
	 */
	public List getHeaderPortletCss() {
		return _headerPortletCss;
	}

	/**
	 * Sets a list of CSS files that will be referenced from the page's header
	 * relative to the portlet's context path.
	 *
	 * @param		headerPortletCss a list of CSS files that will be referenced
	 *				from the page's header relative to the portlet's context
	 *				path
	 */
	public void setHeaderPortletCss(List headerPortletCss) {
		_headerPortletCss = headerPortletCss;
	}

	/**
	 * Gets a list of JavaScript files that will be referenced from the page's
	 * header relative to the portal's context path.
	 *
	 * @return		a list of JavaScript files that will be referenced from the
	 *				page's header relative to the portal's context path
	 */
	public List getHeaderPortalJavaScript() {
		return _headerPortalJavaScript;
	}

	/**
	 * Sets a list of JavaScript files that will be referenced from the page's
	 * header relative to the portal's context path.
	 *
	 * @param		headerPortalJavaScript a list of JavaScript files that will
	 *				be referenced from the page's header relative to the
	 *				portal's context path
	 */
	public void setHeaderPortalJavaScript(List headerPortalJavaScript) {
		_headerPortalJavaScript = headerPortalJavaScript;
	}

	/**
	 * Gets a list of JavaScript files that will be referenced from the page's
	 * header relative to the portlet's context path.
	 *
	 * @return		a list of JavaScript files that will be referenced from the
	 *				page's header relative to the portlet's context path
	 */
	public List getHeaderPortletJavaScript() {
		return _headerPortletJavaScript;
	}

	/**
	 * Sets a list of JavaScript files that will be referenced from the page's
	 * header relative to the portlet's context path.
	 *
	 * @param		headerPortletJavaScript a list of JavaScript files that will
	 *				be referenced from the page's header relative to the
	 *				portlet's context path
	 */
	public void setHeaderPortletJavaScript(List headerPortletJavaScript) {
		_headerPortletJavaScript = headerPortletJavaScript;
	}

	/**
	 * Gets a list of CSS files that will be referenced from the page's footer
	 * relative to the portal's context path.
	 *
	 * @return		a list of CSS files that will be referenced from the page's
	 *				footer relative to the portal's context path
	 */
	public List getFooterPortalCss() {
		return _footerPortalCss;
	}

	/**
	 * Sets a list of CSS files that will be referenced from the page's footer
	 * relative to the portal's context path.
	 *
	 * @param		footerPortalCss a list of CSS files that will be referenced
	 *				from the page's footer relative to the portal's context path
	 */
	public void setFooterPortalCss(List footerPortalCss) {
		_footerPortalCss = footerPortalCss;
	}

	/**
	 * Gets a list of CSS files that will be referenced from the page's footer
	 * relative to the portlet's context path.
	 *
	 * @return		a list of CSS files that will be referenced from the page's
	 *				footer relative to the portlet's context path
	 */
	public List getFooterPortletCss() {
		return _footerPortletCss;
	}

	/**
	 * Sets a list of CSS files that will be referenced from the page's footer
	 * relative to the portlet's context path.
	 *
	 * @param		footerPortletCss a list of CSS files that will be referenced
	 *				from the page's footer relative to the portlet's context
	 *				path
	 */
	public void setFooterPortletCss(List footerPortletCss) {
		_footerPortletCss = footerPortletCss;
	}

	/**
	 * Gets a list of JavaScript files that will be referenced from the page's
	 * footer relative to the portal's context path.
	 *
	 * @return		a list of JavaScript files that will be referenced from the
	 *				page's footer relative to the portal's context path
	 */
	public List getFooterPortalJavaScript() {
		return _footerPortalJavaScript;
	}

	/**
	 * Sets a list of JavaScript files that will be referenced from the page's
	 * footer relative to the portal's context path.
	 *
	 * @param		footerPortalJavaScript a list of JavaScript files that will
	 *				be referenced from the page's footer relative to the
	 *				portal's context path
	 */
	public void setFooterPortalJavaScript(List footerPortalJavaScript) {
		_footerPortalJavaScript = footerPortalJavaScript;
	}

	/**
	 * Gets a list of JavaScript files that will be referenced from the page's
	 * footer relative to the portlet's context path.
	 *
	 * @return		a list of JavaScript files that will be referenced from the
	 *				page's footer relative to the portlet's context path
	 */
	public List getFooterPortletJavaScript() {
		return _footerPortletJavaScript;
	}

	/**
	 * Sets a list of JavaScript files that will be referenced from the page's
	 * footer relative to the portlet's context path.
	 *
	 * @param		footerPortletJavaScript a list of JavaScript files that will
	 *				be referenced from the page's footer relative to the
	 *				portlet's context path
	 */
	public void setFooterPortletJavaScript(List footerPortletJavaScript) {
		_footerPortletJavaScript = footerPortletJavaScript;
	}

	/**
	 * Gets the name of the CSS class that will be injected in the DIV that
	 * wraps this portlet.
	 *
	 * @return		the name of the CSS class that will be injected in the DIV
	 *				that wraps this portlet
	 */
	public String getCssClassWrapper() {
		return _cssClassWrapper;
	}

	/**
	 * Sets the name of the CSS class that will be injected in the DIV that
	 * wraps this portlet.
	 *
	 * @param		cssClassWrapper the name of the CSS class that will be
	 *				injected in the DIV that wraps this portlet
	 */
	public void setCssClassWrapper(String cssClassWrapper) {
		_cssClassWrapper = cssClassWrapper;
	}

	/**
	 * Returns true if default resources for the portlet are added to a page.
	 *
	 * @return		true if default resources for the portlet are added to a
	 *				page
	 */
	public boolean getAddDefaultResource() {
		return _addDefaultResource;
	}

	/**
	 * Returns true if default resources for the portlet are added to a page.
	 *
	 * @return		true if default resources for the portlet are added to a
	 *				page
	 */
	public boolean isAddDefaultResource() {
		return _addDefaultResource;
	}

	/**
	 * Sets to true if default resources for the portlet are added to a page.
	 *
	 * @param		addDefaultResource boolean value for whether or not default
	 *				resources for the portlet are added to a page
	 */
	public void setAddDefaultResource(boolean addDefaultResource) {
		_addDefaultResource = addDefaultResource;
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
	 * Gets the unlinked roles of the portlet.
	 *
	 * @return		unlinked roles of the portlet
	 */
	public Set getUnlinkedRoles() {
		return _unlinkedRoles;
	}

	/**
	 * Sets the unlinked roles of the portlet.
	 *
	 * @param		unlinkedRoles the unlinked roles of the portlet
	 */
	public void setUnlinkedRoles(Set unlinkedRoles) {
		_unlinkedRoles = unlinkedRoles;
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
		List linkedRoles = new ArrayList();

		Iterator itr = _unlinkedRoles.iterator();

		while (itr.hasNext()) {
			String unlinkedRole = (String)itr.next();

			String roleLink = (String)_roleMappers.get(unlinkedRole);

			if (Validator.isNotNull(roleLink)) {
				if (_log.isDebugEnabled()) {
					_log.debug(
						"Linking role for portlet [" + getPortletId() +
							"] with role-name [" + unlinkedRole +
								"] to role-link [" + roleLink + "]");
				}

				linkedRoles.add(roleLink);
			}
			else {
				_log.error(
					"Unable to link role for portlet [" + getPortletId() +
						"] with role-name [" + unlinkedRole +
							"] because role-link is null");
			}
		}

		Collections.sort(linkedRoles);

		setRolesArray((String[])linkedRoles.toArray(new String[0]));
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
	 * Returns true if the user has the permission to add the portlet to a
	 * layout.
	 *
	 * @return		true if the user has the permission to add the portlet to a
	 *				layout
	 */
	public boolean hasAddPortletPermission(long userId) {
		try {
			if (_rolesArray.length == 0) {
				return true;
			}
			else if (RoleLocalServiceUtil.hasUserRoles(
						userId, getCompanyId(), _rolesArray, true)) {

				return true;
			}
			else if (RoleLocalServiceUtil.hasUserRole(
						userId, getCompanyId(), RoleImpl.ADMINISTRATOR, true)) {

				return true;
			}
			else {
				User user = UserLocalServiceUtil.getUserById(userId);

				if (user.isDefaultUser() && hasRoleWithName(RoleImpl.GUEST)) {
					return true;
				}
			}
		}
		catch (Exception e) {
			_log.error(e);
		}

		return false;
	}

	/**
	 * Returns true if the portlet is a system portlet that a user cannot
	 * manually add to their page.
	 *
	 * @return		true if the portlet is a system portlet that a user cannot
	 *				manually add to their page
	 */
	public boolean getSystem() {
		return _system;
	}

	/**
	 * Returns true if the portlet is a system portlet that a user cannot
	 * manually add to their page.
	 *
	 * @return		true if the portlet is a system portlet that a user cannot
	 *				manually add to their page
	 */
	public boolean isSystem() {
		return _system;
	}

	/**
	 * Sets to true if the portlet is a system portlet that a user cannot
	 * manually add to their page.
	 *
	 * @param		system boolean value for whether the portlet is a system
	 *				portlet that a user cannot manually add to their page
	 */
	public void setSystem(boolean system) {
		_system = system;
	}

	/**
	 * Returns true to include the portlet and make it available to be made
	 * active.
	 *
	 * @return		true to include the portlet and make it available to be made
	 * 				active
	 */
	public boolean getInclude() {
		return _include;
	}

	/**
	 * Returns true to include the portlet and make it available to be made
	 * active.
	 *
	 * @return		true to include the portlet and make it available to be made
	 * 				active
	 */
	public boolean isInclude() {
		return _include;
	}

	/**
	 * Sets to true to include the portlet and make it available to be made
	 * active.
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
		if (mimeType == null) {
			mimeType = ContentTypes.TEXT_HTML;
		}

		Set mimeTypeModes = (Set)_portletModes.get(mimeType);

		if (mimeTypeModes == null) {
			return false;
		}

		if (mimeTypeModes.contains(portletMode.toString())) {
			return true;
		}
		else {
			return false;
		}
	}

	/**
	 * Gets a list of all portlet modes supported by the portlet.
	 *
	 * @return		a list of all portlet modes supported by the portlet
	 */
	public Set getAllPortletModes() {
		Set allPortletModes = new TreeSet();

		Iterator itr1 = _portletModes.entrySet().iterator();

		while (itr1.hasNext()) {
			Map.Entry entry = (Map.Entry)itr1.next();

			Set mimeTypeModes = (Set)entry.getValue();

			Iterator itr2 = mimeTypeModes.iterator();

			while (itr2.hasNext()) {
				String portletMode = (String)itr2.next();

				allPortletModes.add(portletMode);
			}
		}

		return allPortletModes;
	}

	/**
	 * Returns true if the portlet supports more than one mime type.
	 *
	 * @return		true if the portlet supports more than one mime type
	 */
	public boolean hasMultipleMimeTypes() {
		if (_portletModes.size() > 1) {
			return true;
		}
		else {
			return false;
		}
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
	 * Gets the servlet context name of the portlet.
	 *
	 * @return		the servlet context name of the portlet
	 */
	public String getServletContextName() {
		return _servletContextName;
	}

	/**
	 * Sets the servlet context name of the portlet.
	 *
	 * @param		servletContextName the servlet context name of the portlet
	 */
	public void setServletContextName(String servletContextName) {
		_servletContextName = servletContextName;

		if (Validator.isNotNull(_servletContextName)) {
			_warFile = true;
		}
		else {
			_warFile = false;
		}
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
	 * Gets the servlet context path of the portlet.
	 *
	 * @return		the servlet context path of the portlet
	 */
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

	/**
	 * Returns true if the portlet is found in a WAR file.
	 *
	 * @param		portletId the cloned instance portlet id
	 * @return		a cloned instance of the portlet
	 */
	public Portlet getClonedInstance(String portletId) {
		if (_clonedInstances == null) {

			// LEP-528

			return null;
		}

		Portlet clonedInstance = (Portlet)_clonedInstances.get(portletId);

		if (clonedInstance == null) {
			clonedInstance = (Portlet)clone();

			clonedInstance.setPortletId(portletId);

			// Disable caching of cloned instances until we can figure out how
			// to elegantly refresh the cache when the portlet is dynamically
			// updated by the user. For example, the user might change the
			// portlet from one column to the next. Cloned instances that are
			// cached would not see the new change. We can then also cache
			// static portlet instances.

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
	 *				static portlet that cannot be moved
	 */
	public void setStatic(boolean staticPortlet) {
		_staticPortlet = staticPortlet;
	}

	/**
	 * Returns true if the portlet is a static portlet at the start of a list of
	 * portlets.
	 *
	 * @return		true if the portlet is a static portlet at the start of a
	 *				list of portlets
	 */
	public boolean getStaticStart() {
		return _staticPortletStart;
	}

	/**
	 * Returns true if the portlet is a static portlet at the start of a list of
	 * portlets.
	 *
	 * @return		true if the portlet is a static portlet at the start of a
	 *				list of portlets
	 */
	public boolean isStaticStart() {
		return _staticPortletStart;
	}

	/**
	 * Sets to true if the portlet is a static portlet at the start of a list of
	 * portlets.
	 *
	 * @param		staticPortletStart boolean value for whether the portlet is
	 *				a static portlet at the start of a list of portlets
	 */
	public void setStaticStart(boolean staticPortletStart) {
		_staticPortletStart = staticPortletStart;
	}

	/**
	 * Returns true if the portlet is a static portlet at the end of a list of
	 * portlets.
	 *
	 * @return		true if the portlet is a static portlet at the end of a
	 *				list of portlets
	 */
	public boolean getStaticEnd() {
		return !_staticPortletStart;
	}

	/**
	 * Returns true if the portlet is a static portlet at the end of a list of
	 * portlets.
	 *
	 * @return		true if the portlet is a static portlet at the end of a
	 *				list of portlets
	 */
	public boolean isStaticEnd() {
		return !_staticPortletStart;
	}

	/**
	 * The servlet url patterns that are part of this application.
	 *
	 * @return		The servlet url patterns that are part of this application
	 */
	public List getServletURLPatterns() {
		return _servletURLPatterns;
	}

	/**
	 * The servlet url patterns that are part of this application.
	 *
	 * @param		servletURLPatterns servlet url patterns that are part of
	 *				this application
	 */
	public void setServletURLPatterns(List servletURLPatterns) {
		_servletURLPatterns = servletURLPatterns;
	}

	/**
	 * Creates and returns a copy of this object.
	 *
	 * @return		a copy of this object
	 */
	public Object clone() {
		return new PortletImpl(
			getPortletId(), getPluginPackage(), getDefaultPluginSetting(),
			getCompanyId(), getIcon(), getVirtualPath(), getStrutsPath(),
			getDisplayName(), getPortletClass(), getConfigurationActionClass(),
			getIndexerClass(), getOpenSearchClass(), getSchedulerClass(),
			getPortletURLClass(), getFriendlyURLMapperClass(),
			getURLEncoderClass(), getPortletDataHandlerClass(),
			getPortletLayoutListenerClass(),
			getActivityTrackerInterpreterClass(), getPopMessageListenerClass(),
			getDefaultPreferences(), getPreferencesValidator(),
			isPreferencesCompanyWide(), isPreferencesUniquePerLayout(),
			isPreferencesOwnedByGroup(), isUseDefaultTemplate(),
			isShowPortletAccessDenied(), isShowPortletInactive(),
			isActionURLRedirect(), isRestoreCurrentView(), isMaximizeEdit(),
			isMaximizeHelp(), isPopUpPrint(), isLayoutCacheable(),
			isInstanceable(), getUserPrincipalStrategy(),
			isPrivateRequestAttributes(), isPrivateSessionAttributes(),
			getRenderWeight(), isAjaxable(), getHeaderPortalCss(),
			getHeaderPortletCss(), getHeaderPortalJavaScript(),
			getHeaderPortletJavaScript(), getFooterPortalCss(),
			getFooterPortletCss(), getFooterPortalJavaScript(),
			getFooterPortletJavaScript(), getCssClassWrapper(),
			isAddDefaultResource(), getRoles(), getUnlinkedRoles(),
			getRoleMappers(), isSystem(), isActive(), isInclude(),
			getInitParams(), getExpCache(), getPortletModes(),
			getSupportedLocales(), getResourceBundle(), getPortletInfo(),
			getUserAttributes(), getCustomUserAttributes(),
			getServletContextName(), getServletURLPatterns());
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
	 * Checks whether this portlet is equal to the specified object.
	 *
	 * @param		obj the object to compare this portlet against
	 * @return		true if the portlet is equal to the specified object
	 */
	public boolean equals(Object obj) {
		Portlet portlet = (Portlet)obj;

		return getPortletId().equals(portlet.getPortletId());
	}

	/**
	 * Log instance for this class.
	 */
	private static Log _log = LogFactory.getLog(PortletImpl.class);

	/**
	 * Package to which this plugin belongs to.
	 */
	private PluginPackage _pluginPackage;

	/**
	 * Plugin settings associated with the portlet.
	 */
	private PluginSetting _defaultPluginSetting;

	/**
	 * The icon of the portlet.
	 */
	private String _icon;

	/**
	 * The virtual path of the portlet.
	 */
	private String _virtualPath;

	/**
	 * The struts path of the portlet.
	 */
	private String _strutsPath;

	/**
	 * The display name of the portlet.
	 */
	private String _displayName;

	/**
	 * The name of the portlet class of the portlet.
	 */
	private String _portletClass;

	/**
	 * The configuration action class of the portlet.
	 */
	private String _configurationActionClass;

	/**
	 * The name of the indexer class of the portlet.
	 */
	private String _indexerClass;

	/**
	 * The name of the open search class of the portlet.
	 */
	private String _openSearchClass;

	/**
	 * The name of the scheduler class of the portlet.
	 */
	private String _schedulerClass;

	/**
	 * The name of the portlet URL class of the portlet.
	 */
	private String _portletURLClass;

	/**
	 * The name of the friendly URL mapper class of the portlet.
	 */
	private String _friendlyURLMapperClass;

	/**
	 * The name of the URL encoder class of the portlet.
	 */
	private String _urlEncoderClass;

 	/**
	 * The name of the portlet data handler class of the portlet.
	 */
	private String _portletDataHandlerClass;

 	/**
	 * The name of the portlet data layout listener class of the portlet.
	 */
	private String _portletLayoutListenerClass;

 	/**
	 * The name of the activity tracker interpreter class of the portlet.
	 */
	private String _activityTrackerInterpreterClass;

 	/**
	 * The name of the POP message listener class of the portlet.
	 */
	private String _popMessageListenerClass;

	/**
	 * The default preferences of the portlet.
	 */
	private String _defaultPreferences;

	/**
	 * The name of the preferences validator class of the portlet.
	 */
	private String _prefsValidator;

	/**
	 * True if preferences are shared across the entire company.
	 */
	private boolean _prefsCompanyWide;

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
	private boolean _showPortletAccessDenied =
		PropsValues.LAYOUT_SHOW_PORTLET_ACCESS_DENIED;

	/**
	 * True if users are shown that the portlet is inactive.
	 */
	private boolean _showPortletInactive =
		PropsValues.LAYOUT_SHOW_PORTLET_INACTIVE;

	/**
	 * True if an action URL for this portlet should cause an auto redirect.
	 */
	private boolean _actionURLRedirect;

	/**
	 * True if the portlet restores to the current view from the maximized
	 * state.
	 */
	private boolean _restoreCurrentView = true;

	/**
	 * True if the portlet goes into the maximized state when the user goes into
	 * the edit mode.
	 */
	private boolean _maximizeEdit;

	/**
	 * True if the portlet goes into the maximized state when the user goes into
	 * the help mode.
	 */
	private boolean _maximizeHelp;

	/**
	 * True if the portlet goes into the pop up state when the user goes into
	 * the print mode.
	 */
	private boolean _popUpPrint = true;

	/**
	 * True if the portlet can be cached within the layout.
	 */
	private boolean _layoutCacheable;

	/**
	 * True if the portlet can be added multiple times to a layout.
	 */
	private boolean _instanceable;

	/**
	 * The user principal strategy of the portlet.
	 */
	private String _userPrincipalStrategy =
		PortletImpl.USER_PRINCIPAL_STRATEGY_USER_ID;

	/**
	 * True if the portlet does not share request attributes with the portal or
	 * portlets from another WAR.
	 */
	private boolean _privateRequestAttributes = true;

	/**
	 * True if the portlet does not share session attributes with the portal.
	 */
	private boolean _privateSessionAttributes = true;

	/**
	 * Render weight of the portlet.
	 */
	private int _renderWeight = 1;

	/**
	 * True if the portlet can be displayed via Ajax.
	 */
	private boolean _ajaxable = true;

	/**
	 * A list of CSS files that will be referenced from the page's header
	 * relative to the portal's context path.
	 */
	private List _headerPortalCss;

	/**
	 * A list of CSS files that will be referenced from the page's header
	 * relative to the portlet's context path.
	 */
	private List _headerPortletCss;

	/**
	 * A list of JavaScript files that will be referenced from the page's header
	 * relative to the portal's context path.
	 */
	private List _headerPortalJavaScript;

	/**
	 * A list of JavaScript files that will be referenced from the page's header
	 * relative to the portlet's context path.
	 */
	private List _headerPortletJavaScript;

	/**
	 * A list of CSS files that will be referenced from the page's footer
	 * relative to the portal's context path.
	 */
	private List _footerPortalCss;

	/**
	 * A list of CSS files that will be referenced from the page's footer
	 * relative to the portlet's context path.
	 */
	private List _footerPortletCss;

	/**
	 * A list of JavaScript files that will be referenced from the page's footer
	 * relative to the portal's context path.
	 */
	private List _footerPortalJavaScript;

	/**
	 * A list of JavaScript files that will be referenced from the page's footer
	 * relative to the portlet's context path.
	 */
	private List _footerPortletJavaScript;

	/**
	 * The name of the CSS class that will be injected in the DIV that wraps
	 * this portlet.
	 */
	private String _cssClassWrapper;

	/**
	 * True if default resources for the portlet are added to a page.
	 */
	private boolean _addDefaultResource;

	/**
	 * An array of required roles of the portlet.
	 */
	private String[] _rolesArray;

	/**
	 * The unlinked roles of the portlet.
	 */
	private Set _unlinkedRoles;

	/**
	 * The role mappers of the portlet.
	 */
	private Map _roleMappers;

	/**
	 * True if the portlet is a system portlet that a user cannot manually add
	 * to their page.
	 */
	private boolean _system;

	/**
	 * True to include the portlet and make it available to be made active.
	 */
	private boolean _include = true;

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
	 * The servlet context name of the portlet.
	 */
	private String _servletContextName;

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

	/**
	 * True if the portlet is a static portlet at the start of a list of
	 * portlets.
	 */
	private boolean _staticPortletStart;

	/**
	 * The servlet url patterns that are part of this application.
	 */
	private List _servletURLPatterns;

}