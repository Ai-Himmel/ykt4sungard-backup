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


/**
 * <a href="Portlet.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This interface is a model that represents the <code>Portlet</code> table
 * in the database.
 * </p>
 *
 * <p>
 * Customize <code>com.liferay.portal.service.model.impl.PortletImpl</code>
 * and rerun the ServiceBuilder to generate the new methods.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.model.PortletModel
 * @see com.liferay.portal.service.model.impl.PortletImpl
 * @see com.liferay.portal.service.model.impl.PortletModelImpl
 *
 */
public interface Portlet extends PortletModel {
	public java.lang.String getRootPortletId();

	public java.lang.String getInstanceId();

	public java.lang.String getPluginId();

	public java.lang.String getPluginType();

	public com.liferay.portal.kernel.plugin.PluginPackage getPluginPackage();

	public void setPluginPackage(
		com.liferay.portal.kernel.plugin.PluginPackage pluginPackage);

	public com.liferay.portal.model.PluginSetting getDefaultPluginSetting();

	public void setDefaultPluginSetting(
		com.liferay.portal.model.PluginSetting pluginSetting);

	public java.lang.String getIcon();

	public void setIcon(java.lang.String icon);

	public java.lang.String getVirtualPath();

	public void setVirtualPath(java.lang.String virtualPath);

	public java.lang.String getStrutsPath();

	public void setStrutsPath(java.lang.String strutsPath);

	public java.lang.String getDisplayName();

	public void setDisplayName(java.lang.String displayName);

	public java.lang.String getPortletClass();

	public void setPortletClass(java.lang.String portletClass);

	public java.lang.String getConfigurationActionClass();

	public void setConfigurationActionClass(
		java.lang.String configurationActionClass);

	public com.liferay.portal.kernel.portlet.ConfigurationAction getConfigurationActionInstance();

	public java.lang.String getIndexerClass();

	public void setIndexerClass(java.lang.String indexerClass);

	public java.lang.String getOpenSearchClass();

	public void setOpenSearchClass(java.lang.String openSearchClass);

	public java.lang.String getSchedulerClass();

	public void setSchedulerClass(java.lang.String schedulerClass);

	public java.lang.String getPortletURLClass();

	public void setPortletURLClass(java.lang.String portletURLClass);

	public java.lang.String getFriendlyURLMapperClass();

	public void setFriendlyURLMapperClass(
		java.lang.String friendlyURLMapperClass);

	public com.liferay.portal.kernel.portlet.FriendlyURLMapper getFriendlyURLMapperInstance();

	public java.lang.String getURLEncoderClass();

	public void setURLEncoderClass(java.lang.String urlEncoderClass);

	public com.liferay.portal.kernel.servlet.URLEncoder getURLEncoderInstance();

	public java.lang.String getPortletDataHandlerClass();

	public void setPortletDataHandlerClass(
		java.lang.String portletDataHandlerClass);

	public com.liferay.portal.kernel.lar.PortletDataHandler getPortletDataHandlerInstance();

	public com.liferay.portal.kernel.portlet.PortletLayoutListener getPortletLayoutListener();

	public java.lang.String getPortletLayoutListenerClass();

	public void setPortletLayoutListenerClass(
		java.lang.String portletLayoutListenerClass);

	public java.lang.String getActivityTrackerInterpreterClass();

	public void setActivityTrackerInterpreterClass(
		java.lang.String activityTrackerInterpreterClass);

	public com.liferay.portal.model.ActivityTrackerInterpreter getActivityTrackerInterpreterInstance();

	public java.lang.String getPopMessageListenerClass();

	public void setPopMessageListenerClass(
		java.lang.String popMessageListenerClass);

	public com.liferay.portal.kernel.pop.MessageListener getPopMessageListenerInstance();

	public java.lang.String getDefaultPreferences();

	public void setDefaultPreferences(java.lang.String defaultPreferences);

	public java.lang.String getPreferencesValidator();

	public void setPreferencesValidator(java.lang.String prefsValidator);

	public boolean getPreferencesCompanyWide();

	public boolean isPreferencesCompanyWide();

	public void setPreferencesCompanyWide(boolean prefsCompanyWide);

	public boolean getPreferencesUniquePerLayout();

	public boolean isPreferencesUniquePerLayout();

	public void setPreferencesUniquePerLayout(boolean prefsUniquePerLayout);

	public boolean getPreferencesOwnedByGroup();

	public boolean isPreferencesOwnedByGroup();

	public void setPreferencesOwnedByGroup(boolean prefsOwnedByGroup);

	public boolean getUseDefaultTemplate();

	public boolean isUseDefaultTemplate();

	public void setUseDefaultTemplate(boolean useDefaultTemplate);

	public boolean getShowPortletAccessDenied();

	public boolean isShowPortletAccessDenied();

	public void setShowPortletAccessDenied(boolean showPortletAccessDenied);

	public boolean getShowPortletInactive();

	public boolean isShowPortletInactive();

	public void setShowPortletInactive(boolean showPortletInactive);

	public boolean getActionURLRedirect();

	public boolean isActionURLRedirect();

	public void setActionURLRedirect(boolean actionURLRedirect);

	public boolean getRestoreCurrentView();

	public boolean isRestoreCurrentView();

	public void setRestoreCurrentView(boolean restoreCurrentView);

	public boolean getMaximizeEdit();

	public boolean isMaximizeEdit();

	public void setMaximizeEdit(boolean maximizeEdit);

	public boolean getMaximizeHelp();

	public boolean isMaximizeHelp();

	public void setMaximizeHelp(boolean maximizeHelp);

	public boolean getPopUpPrint();

	public boolean isPopUpPrint();

	public void setPopUpPrint(boolean popUpPrint);

	public boolean getLayoutCacheable();

	public boolean isLayoutCacheable();

	public void setLayoutCacheable(boolean layoutCacheable);

	public boolean getInstanceable();

	public boolean isInstanceable();

	public void setInstanceable(boolean instanceable);

	public java.lang.String getUserPrincipalStrategy();

	public void setUserPrincipalStrategy(java.lang.String userPrincipalStrategy);

	public boolean getPrivateRequestAttributes();

	public boolean isPrivateRequestAttributes();

	public void setPrivateRequestAttributes(boolean privateRequestAttributes);

	public boolean getPrivateSessionAttributes();

	public boolean isPrivateSessionAttributes();

	public void setPrivateSessionAttributes(boolean privateSessionAttributes);

	public int getRenderWeight();

	public void setRenderWeight(int renderWeight);

	public boolean getAjaxable();

	public boolean isAjaxable();

	public void setAjaxable(boolean ajaxable);

	public java.util.List getHeaderPortalCss();

	public void setHeaderPortalCss(java.util.List headerPortalCss);

	public java.util.List getHeaderPortletCss();

	public void setHeaderPortletCss(java.util.List headerPortletCss);

	public java.util.List getHeaderPortalJavaScript();

	public void setHeaderPortalJavaScript(java.util.List headerPortalJavaScript);

	public java.util.List getHeaderPortletJavaScript();

	public void setHeaderPortletJavaScript(
		java.util.List headerPortletJavaScript);

	public java.util.List getFooterPortalCss();

	public void setFooterPortalCss(java.util.List footerPortalCss);

	public java.util.List getFooterPortletCss();

	public void setFooterPortletCss(java.util.List footerPortletCss);

	public java.util.List getFooterPortalJavaScript();

	public void setFooterPortalJavaScript(java.util.List footerPortalJavaScript);

	public java.util.List getFooterPortletJavaScript();

	public void setFooterPortletJavaScript(
		java.util.List footerPortletJavaScript);

	public java.lang.String getCssClassWrapper();

	public void setCssClassWrapper(java.lang.String cssClassWrapper);

	public boolean getAddDefaultResource();

	public boolean isAddDefaultResource();

	public void setAddDefaultResource(boolean addDefaultResource);

	public void setRoles(java.lang.String roles);

	public java.lang.String[] getRolesArray();

	public void setRolesArray(java.lang.String[] rolesArray);

	public java.util.Set getUnlinkedRoles();

	public void setUnlinkedRoles(java.util.Set unlinkedRoles);

	public java.util.Map getRoleMappers();

	public void setRoleMappers(java.util.Map roleMappers);

	public void linkRoles();

	public boolean hasRoleWithName(java.lang.String roleName);

	public boolean hasAddPortletPermission(long userId);

	public boolean getSystem();

	public boolean isSystem();

	public void setSystem(boolean system);

	public boolean getInclude();

	public boolean isInclude();

	public void setInclude(boolean include);

	public java.util.Map getInitParams();

	public void setInitParams(java.util.Map initParams);

	public java.lang.Integer getExpCache();

	public void setExpCache(java.lang.Integer expCache);

	public java.util.Map getPortletModes();

	public void setPortletModes(java.util.Map portletModes);

	public boolean hasPortletMode(java.lang.String mimeType,
		javax.portlet.PortletMode portletMode);

	public java.util.Set getAllPortletModes();

	public boolean hasMultipleMimeTypes();

	public java.util.Set getSupportedLocales();

	public void setSupportedLocales(java.util.Set supportedLocales);

	public java.lang.String getResourceBundle();

	public void setResourceBundle(java.lang.String resourceBundle);

	public com.liferay.portal.model.PortletInfo getPortletInfo();

	public void setPortletInfo(com.liferay.portal.model.PortletInfo portletInfo);

	public java.util.Set getUserAttributes();

	public void setUserAttributes(java.util.Set userAttributes);

	public java.util.Map getCustomUserAttributes();

	public void setCustomUserAttributes(java.util.Map customUserAttributes);

	public java.lang.String getServletContextName();

	public void setServletContextName(java.lang.String servletContextName);

	public boolean getWARFile();

	public boolean isWARFile();

	public void setWARFile(boolean warFile);

	public java.lang.String getContextPath();

	public com.liferay.portal.model.Portlet getClonedInstance(
		java.lang.String portletId);

	public boolean getStatic();

	public boolean isStatic();

	public void setStatic(boolean staticPortlet);

	public boolean getStaticStart();

	public boolean isStaticStart();

	public void setStaticStart(boolean staticPortletStart);

	public boolean getStaticEnd();

	public boolean isStaticEnd();

	public java.util.List getServletURLPatterns();

	public void setServletURLPatterns(java.util.List servletURLPatterns);

	public java.lang.Object clone();

	public int compareTo(java.lang.Object obj);

	public boolean equals(java.lang.Object obj);
}