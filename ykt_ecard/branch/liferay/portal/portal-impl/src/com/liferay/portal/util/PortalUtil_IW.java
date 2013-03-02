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

package com.liferay.portal.util;

/**
 * <a href="PortalUtil_IW.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortalUtil_IW {
	public static PortalUtil_IW getInstance() {
		return _instance;
	}

	public void clearRequestParameters(javax.portlet.RenderRequest req) {
		PortalUtil.clearRequestParameters(req);
	}

	public void copyRequestParameters(javax.portlet.ActionRequest req,
		javax.portlet.ActionResponse res) {
		PortalUtil.copyRequestParameters(req, res);
	}

	public java.lang.String createSecureProxyURL(java.lang.String url,
		java.security.Key key, boolean secure) {
		return PortalUtil.createSecureProxyURL(url, key, secure);
	}

	public java.lang.String getCDNHost() {
		return PortalUtil.getCDNHost();
	}

	public java.lang.String getClassName(long classNameId) {
		return PortalUtil.getClassName(classNameId);
	}

	public long getClassNameId(java.lang.Class classObj) {
		return PortalUtil.getClassNameId(classObj);
	}

	public long getClassNameId(java.lang.String value) {
		return PortalUtil.getClassNameId(value);
	}

	public java.lang.String getClassNamePortletId(java.lang.String className) {
		return PortalUtil.getClassNamePortletId(className);
	}

	public com.liferay.portal.model.Company getCompany(
		javax.servlet.http.HttpServletRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getCompany(req);
	}

	public com.liferay.portal.model.Company getCompany(
		javax.portlet.ActionRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getCompany(req);
	}

	public com.liferay.portal.model.Company getCompany(
		javax.portlet.RenderRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getCompany(req);
	}

	public long getCompanyId(javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getCompanyId(req);
	}

	public long getCompanyId(javax.portlet.ActionRequest req) {
		return PortalUtil.getCompanyId(req);
	}

	public long getCompanyId(javax.portlet.PortletRequest req) {
		return PortalUtil.getCompanyId(req);
	}

	public long getCompanyId(javax.portlet.RenderRequest req) {
		return PortalUtil.getCompanyId(req);
	}

	public long getCompanyIdByWebId(javax.servlet.ServletContext ctx) {
		return PortalUtil.getCompanyIdByWebId(ctx);
	}

	public long getCompanyIdByWebId(java.lang.String webId) {
		return PortalUtil.getCompanyIdByWebId(webId);
	}

	public java.lang.String getComputerName() {
		return PortalUtil.getComputerName();
	}

	public java.lang.String getCurrentURL(
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getCurrentURL(req);
	}

	public java.lang.String getCurrentURL(javax.portlet.PortletRequest req) {
		return PortalUtil.getCurrentURL(req);
	}

	public java.util.Date getDate(int month, int day, int year,
		com.liferay.portal.PortalException pe)
		throws com.liferay.portal.PortalException {
		return PortalUtil.getDate(month, day, year, pe);
	}

	public java.util.Date getDate(int month, int day, int year,
		java.util.TimeZone timeZone, com.liferay.portal.PortalException pe)
		throws com.liferay.portal.PortalException {
		return PortalUtil.getDate(month, day, year, timeZone, pe);
	}

	public java.util.Date getDate(int month, int day, int year, int hour,
		int min, com.liferay.portal.PortalException pe)
		throws com.liferay.portal.PortalException {
		return PortalUtil.getDate(month, day, year, hour, min, pe);
	}

	public java.util.Date getDate(int month, int day, int year, int hour,
		int min, java.util.TimeZone timeZone,
		com.liferay.portal.PortalException pe)
		throws com.liferay.portal.PortalException {
		return PortalUtil.getDate(month, day, year, hour, min, timeZone, pe);
	}

	public java.lang.String getHost(javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getHost(req);
	}

	public java.lang.String getHost(javax.portlet.ActionRequest req) {
		return PortalUtil.getHost(req);
	}

	public java.lang.String getHost(javax.portlet.RenderRequest req) {
		return PortalUtil.getHost(req);
	}

	public javax.servlet.http.HttpServletRequest getHttpServletRequest(
		javax.portlet.PortletRequest req) {
		return PortalUtil.getHttpServletRequest(req);
	}

	public javax.servlet.http.HttpServletResponse getHttpServletResponse(
		javax.portlet.PortletResponse res) {
		return PortalUtil.getHttpServletResponse(res);
	}

	public java.lang.String getLayoutEditPage(
		com.liferay.portal.model.Layout layout) {
		return PortalUtil.getLayoutEditPage(layout);
	}

	public java.lang.String getLayoutViewPage(
		com.liferay.portal.model.Layout layout) {
		return PortalUtil.getLayoutViewPage(layout);
	}

	public java.lang.String getLayoutURL(
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutURL(themeDisplay);
	}

	public java.lang.String getLayoutURL(
		com.liferay.portal.model.Layout layout,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutURL(layout, themeDisplay);
	}

	public java.lang.String getLayoutURL(
		com.liferay.portal.model.Layout layout,
		com.liferay.portal.theme.ThemeDisplay themeDisplay, boolean doAsUser)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutURL(layout, themeDisplay, doAsUser);
	}

	public java.lang.String getLayoutActualURL(
		com.liferay.portal.model.Layout layout)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutActualURL(layout);
	}

	public java.lang.String getLayoutActualURL(
		com.liferay.portal.model.Layout layout, java.lang.String mainPath)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutActualURL(layout, mainPath);
	}

	public java.lang.String getLayoutActualURL(long groupId,
		boolean privateLayout, java.lang.String mainPath,
		java.lang.String friendlyURL)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutActualURL(groupId, privateLayout, mainPath,
			friendlyURL);
	}

	public java.lang.String getLayoutActualURL(long groupId,
		boolean privateLayout, java.lang.String mainPath,
		java.lang.String friendlyURL, java.util.Map params)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutActualURL(groupId, privateLayout, mainPath,
			friendlyURL, params);
	}

	public java.lang.String getLayoutFriendlyURL(
		com.liferay.portal.model.Layout layout,
		com.liferay.portal.theme.ThemeDisplay themeDisplay)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getLayoutFriendlyURL(layout, themeDisplay);
	}

	public java.lang.String getLayoutTarget(
		com.liferay.portal.model.Layout layout) {
		return PortalUtil.getLayoutTarget(layout);
	}

	public java.lang.String getJsSafePortletId(java.lang.String portletId) {
		return PortalUtil.getJsSafePortletId(portletId);
	}

	public java.lang.String getJsSafePortletName(java.lang.String portletName) {
		return PortalUtil.getJsSafePortletName(portletName);
	}

	public java.util.Locale getLocale(javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getLocale(req);
	}

	public java.util.Locale getLocale(javax.portlet.RenderRequest req) {
		return PortalUtil.getLocale(req);
	}

	public javax.servlet.http.HttpServletRequest getOriginalServletRequest(
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getOriginalServletRequest(req);
	}

	public java.lang.String getPathContext() {
		return PortalUtil.getPathContext();
	}

	public java.lang.String getPathFriendlyURLPrivateGroup() {
		return PortalUtil.getPathFriendlyURLPrivateGroup();
	}

	public java.lang.String getPathFriendlyURLPrivateUser() {
		return PortalUtil.getPathFriendlyURLPrivateUser();
	}

	public java.lang.String getPathFriendlyURLPublic() {
		return PortalUtil.getPathFriendlyURLPublic();
	}

	public java.lang.String getPathImage() {
		return PortalUtil.getPathImage();
	}

	public java.lang.String getPathMain() {
		return PortalUtil.getPathMain();
	}

	public long getPlidIdFromFriendlyURL(long companyId,
		java.lang.String friendlyURL) {
		return PortalUtil.getPlidIdFromFriendlyURL(companyId, friendlyURL);
	}

	public java.lang.String getPortalLibDir() {
		return PortalUtil.getPortalLibDir();
	}

	public java.lang.String getPortalURL(
		com.liferay.portal.theme.ThemeDisplay themeDisplay) {
		return PortalUtil.getPortalURL(themeDisplay);
	}

	public java.lang.String getPortalURL(
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getPortalURL(req);
	}

	public java.lang.String getPortalURL(
		javax.servlet.http.HttpServletRequest req, boolean secure) {
		return PortalUtil.getPortalURL(req, secure);
	}

	public java.lang.String getPortalURL(javax.portlet.PortletRequest req) {
		return PortalUtil.getPortalURL(req);
	}

	public java.lang.String getPortalURL(javax.portlet.PortletRequest req,
		boolean secure) {
		return PortalUtil.getPortalURL(req, secure);
	}

	public java.lang.String getPortalURL(java.lang.String serverName,
		int serverPort, boolean secure) {
		return PortalUtil.getPortalURL(serverName, serverPort, secure);
	}

	public java.lang.Object[] getPortletFriendlyURLMapper(long groupId,
		boolean privateLayout, java.lang.String url)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getPortletFriendlyURLMapper(groupId, privateLayout,
			url);
	}

	public java.lang.Object[] getPortletFriendlyURLMapper(long groupId,
		boolean privateLayout, java.lang.String url, java.util.Map params)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getPortletFriendlyURLMapper(groupId, privateLayout,
			url, params);
	}

	public long getPortletGroupId(long plid) {
		return PortalUtil.getPortletGroupId(plid);
	}

	public long getPortletGroupId(com.liferay.portal.model.Layout layout) {
		return PortalUtil.getPortletGroupId(layout);
	}

	public long getPortletGroupId(javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getPortletGroupId(req);
	}

	public long getPortletGroupId(javax.portlet.ActionRequest req) {
		return PortalUtil.getPortletGroupId(req);
	}

	public long getPortletGroupId(javax.portlet.RenderRequest req) {
		return PortalUtil.getPortletGroupId(req);
	}

	public java.lang.String getPortletNamespace(java.lang.String portletId) {
		return PortalUtil.getPortletNamespace(portletId);
	}

	public java.lang.String getPortletXmlFileName()
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getPortletXmlFileName();
	}

	public java.lang.String getPortletTitle(java.lang.String portletId,
		long companyId, java.lang.String languageId) {
		return PortalUtil.getPortletTitle(portletId, companyId, languageId);
	}

	public java.lang.String getPortletTitle(java.lang.String portletId,
		com.liferay.portal.model.User user) {
		return PortalUtil.getPortletTitle(portletId, user);
	}

	public java.lang.String getPortletTitle(
		com.liferay.portal.model.Portlet portlet,
		javax.servlet.ServletContext ctx, java.util.Locale locale) {
		return PortalUtil.getPortletTitle(portlet, ctx, locale);
	}

	public javax.portlet.PortletPreferences getPreferences(
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getPreferences(req);
	}

	public javax.portlet.PreferencesValidator getPreferencesValidator(
		com.liferay.portal.model.Portlet portlet) {
		return PortalUtil.getPreferencesValidator(portlet);
	}

	public com.liferay.portlet.RenderResponseImpl getRenderResponseImpl(
		javax.portlet.RenderResponse res) {
		return PortalUtil.getRenderResponseImpl(res);
	}

	public com.liferay.portal.model.User getSelectedUser(
		javax.servlet.http.HttpServletRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.getSelectedUser(req);
	}

	public com.liferay.portal.model.User getSelectedUser(
		javax.servlet.http.HttpServletRequest req, boolean checkPermission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.getSelectedUser(req, checkPermission);
	}

	public com.liferay.portal.model.User getSelectedUser(
		javax.portlet.ActionRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.getSelectedUser(req);
	}

	public com.liferay.portal.model.User getSelectedUser(
		javax.portlet.ActionRequest req, boolean checkPermission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.getSelectedUser(req, checkPermission);
	}

	public com.liferay.portal.model.User getSelectedUser(
		javax.portlet.RenderRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.getSelectedUser(req);
	}

	public com.liferay.portal.model.User getSelectedUser(
		javax.portlet.RenderRequest req, boolean checkPermission)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.getSelectedUser(req, checkPermission);
	}

	public java.lang.String getStrutsAction(
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getStrutsAction(req);
	}

	public java.lang.String[] getSystemCommunityRoles() {
		return PortalUtil.getSystemCommunityRoles();
	}

	public java.lang.String[] getSystemGroups() {
		return PortalUtil.getSystemGroups();
	}

	public java.lang.String[] getSystemOrganizationRoles() {
		return PortalUtil.getSystemOrganizationRoles();
	}

	public java.lang.String[] getSystemRoles() {
		return PortalUtil.getSystemRoles();
	}

	public com.liferay.util.servlet.UploadPortletRequest getUploadPortletRequest(
		javax.portlet.ActionRequest req) {
		return PortalUtil.getUploadPortletRequest(req);
	}

	public com.liferay.util.servlet.UploadServletRequest getUploadServletRequest(
		javax.servlet.http.HttpServletRequest httpReq) {
		return PortalUtil.getUploadServletRequest(httpReq);
	}

	public java.util.Date getUptime() {
		return PortalUtil.getUptime();
	}

	public java.lang.String getURLWithSessionId(java.lang.String url,
		java.lang.String sessionId) {
		return PortalUtil.getURLWithSessionId(url, sessionId);
	}

	public com.liferay.portal.model.User getUser(
		javax.servlet.http.HttpServletRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getUser(req);
	}

	public com.liferay.portal.model.User getUser(
		javax.portlet.ActionRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getUser(req);
	}

	public com.liferay.portal.model.User getUser(
		javax.portlet.RenderRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.getUser(req);
	}

	public long getUserId(javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getUserId(req);
	}

	public long getUserId(javax.portlet.ActionRequest req) {
		return PortalUtil.getUserId(req);
	}

	public long getUserId(javax.portlet.RenderRequest req) {
		return PortalUtil.getUserId(req);
	}

	public java.lang.String getUserName(long userId,
		java.lang.String defaultUserName) {
		return PortalUtil.getUserName(userId, defaultUserName);
	}

	public java.lang.String getUserName(long userId,
		java.lang.String defaultUserName, java.lang.String userAttribute) {
		return PortalUtil.getUserName(userId, defaultUserName, userAttribute);
	}

	public java.lang.String getUserName(long userId,
		java.lang.String defaultUserName,
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getUserName(userId, defaultUserName, req);
	}

	public java.lang.String getUserName(long userId,
		java.lang.String defaultUserName, java.lang.String userAttribute,
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getUserName(userId, defaultUserName, userAttribute,
			req);
	}

	public java.lang.String getUserPassword(javax.servlet.http.HttpSession ses) {
		return PortalUtil.getUserPassword(ses);
	}

	public java.lang.String getUserPassword(
		javax.servlet.http.HttpServletRequest req) {
		return PortalUtil.getUserPassword(req);
	}

	public java.lang.String getUserPassword(javax.portlet.ActionRequest req) {
		return PortalUtil.getUserPassword(req);
	}

	public java.lang.String getUserPassword(javax.portlet.RenderRequest req) {
		return PortalUtil.getUserPassword(req);
	}

	public java.lang.String getUserValue(long userId, java.lang.String param,
		java.lang.String defaultValue)
		throws com.liferay.portal.SystemException {
		return PortalUtil.getUserValue(userId, param, defaultValue);
	}

	public boolean isMethodGet(javax.portlet.PortletRequest req) {
		return PortalUtil.isMethodGet(req);
	}

	public boolean isMethodPost(javax.portlet.PortletRequest req) {
		return PortalUtil.isMethodPost(req);
	}

	public boolean isLayoutFriendliable(com.liferay.portal.model.Layout layout) {
		return PortalUtil.isLayoutFriendliable(layout);
	}

	public boolean isLayoutParentable(com.liferay.portal.model.Layout layout) {
		return PortalUtil.isLayoutParentable(layout);
	}

	public boolean isLayoutParentable(java.lang.String type) {
		return PortalUtil.isLayoutParentable(type);
	}

	public boolean isLayoutSitemapable(com.liferay.portal.model.Layout layout) {
		return PortalUtil.isLayoutSitemapable(layout);
	}

	public boolean isReservedParameter(java.lang.String name) {
		return PortalUtil.isReservedParameter(name);
	}

	public boolean isSystemGroup(java.lang.String groupName) {
		return PortalUtil.isSystemGroup(groupName);
	}

	public boolean isSystemRole(java.lang.String roleName) {
		return PortalUtil.isSystemRole(roleName);
	}

	public boolean isUpdateAvailable()
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException {
		return PortalUtil.isUpdateAvailable();
	}

	public org.dom4j.Document readDocumentFromFile(java.io.File file)
		throws org.dom4j.DocumentException {
		return PortalUtil.readDocumentFromFile(file);
	}

	public org.dom4j.Document readDocumentFromFile(java.io.File file,
		boolean validate) throws org.dom4j.DocumentException {
		return PortalUtil.readDocumentFromFile(file, validate);
	}

	public org.dom4j.Document readDocumentFromStream(java.io.InputStream is)
		throws org.dom4j.DocumentException {
		return PortalUtil.readDocumentFromStream(is);
	}

	public org.dom4j.Document readDocumentFromStream(java.io.InputStream is,
		boolean validate) throws org.dom4j.DocumentException {
		return PortalUtil.readDocumentFromStream(is, validate);
	}

	public org.dom4j.Document readDocumentFromURL(java.lang.String url)
		throws org.dom4j.DocumentException, java.io.IOException {
		return PortalUtil.readDocumentFromURL(url);
	}

	public org.dom4j.Document readDocumentFromURL(java.lang.String url,
		boolean validate)
		throws org.dom4j.DocumentException, java.io.IOException {
		return PortalUtil.readDocumentFromURL(url, validate);
	}

	public org.dom4j.Document readDocumentFromXML(java.lang.String xml)
		throws org.dom4j.DocumentException {
		return PortalUtil.readDocumentFromXML(xml);
	}

	public org.dom4j.Document readDocumentFromXML(java.lang.String xml,
		boolean validate) throws org.dom4j.DocumentException {
		return PortalUtil.readDocumentFromXML(xml, validate);
	}

	public void renderPage(com.liferay.portal.kernel.util.StringMaker sm,
		javax.servlet.ServletContext ctx,
		javax.servlet.http.HttpServletRequest req,
		javax.servlet.http.HttpServletResponse res, java.lang.String path)
		throws java.io.IOException, javax.servlet.ServletException {
		PortalUtil.renderPage(sm, ctx, req, res, path);
	}

	public void renderPortlet(com.liferay.portal.kernel.util.StringMaker sm,
		javax.servlet.ServletContext ctx,
		javax.servlet.http.HttpServletRequest req,
		javax.servlet.http.HttpServletResponse res,
		com.liferay.portal.model.Portlet portlet, java.lang.String queryString)
		throws java.io.IOException, javax.servlet.ServletException {
		PortalUtil.renderPortlet(sm, ctx, req, res, portlet, queryString);
	}

	public void renderPortlet(com.liferay.portal.kernel.util.StringMaker sm,
		javax.servlet.ServletContext ctx,
		javax.servlet.http.HttpServletRequest req,
		javax.servlet.http.HttpServletResponse res,
		com.liferay.portal.model.Portlet portlet, java.lang.String queryString,
		java.lang.String columnId, java.lang.Integer columnPos,
		java.lang.Integer columnCount)
		throws java.io.IOException, javax.servlet.ServletException {
		PortalUtil.renderPortlet(sm, ctx, req, res, portlet, queryString,
			columnId, columnPos, columnCount);
	}

	public void renderPortlet(com.liferay.portal.kernel.util.StringMaker sm,
		javax.servlet.ServletContext ctx,
		javax.servlet.http.HttpServletRequest req,
		javax.servlet.http.HttpServletResponse res,
		com.liferay.portal.model.Portlet portlet, java.lang.String queryString,
		java.lang.String columnId, java.lang.Integer columnPos,
		java.lang.Integer columnCount, java.lang.String path)
		throws java.io.IOException, javax.servlet.ServletException {
		PortalUtil.renderPortlet(sm, ctx, req, res, portlet, queryString,
			columnId, columnPos, columnCount, path);
	}

	public void sendError(int status, java.lang.Exception e,
		javax.servlet.http.HttpServletRequest req,
		javax.servlet.http.HttpServletResponse res)
		throws java.io.IOException, javax.servlet.ServletException {
		PortalUtil.sendError(status, e, req, res);
	}

	public void setPageSubtitle(java.lang.String subtitle,
		javax.servlet.http.HttpServletRequest req) {
		PortalUtil.setPageSubtitle(subtitle, req);
	}

	public void setPageTitle(java.lang.String title,
		javax.servlet.http.HttpServletRequest req) {
		PortalUtil.setPageTitle(title, req);
	}

	public void storePreferences(javax.portlet.PortletPreferences prefs)
		throws java.io.IOException, javax.portlet.ValidatorException {
		PortalUtil.storePreferences(prefs);
	}

	public javax.portlet.PortletMode updatePortletMode(
		java.lang.String portletId, com.liferay.portal.model.User user,
		com.liferay.portal.model.Layout layout,
		javax.portlet.PortletMode portletMode,
		javax.servlet.http.HttpServletRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.updatePortletMode(portletId, user, layout,
			portletMode, req);
	}

	public javax.portlet.WindowState updateWindowState(
		java.lang.String portletId, com.liferay.portal.model.User user,
		com.liferay.portal.model.Layout layout,
		javax.portlet.WindowState windowState,
		javax.servlet.http.HttpServletRequest req)
		throws com.liferay.portal.SystemException, 
			com.liferay.portal.PortalException, java.rmi.RemoteException {
		return PortalUtil.updateWindowState(portletId, user, layout,
			windowState, req);
	}

	private PortalUtil_IW() {
	}

	private static PortalUtil_IW _instance = new PortalUtil_IW();
}