<%
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
%>

<%@ include file="/html/portal/init.jsp" %>

<%
Portlet portlet = (Portlet)request.getAttribute(WebKeys.RENDER_PORTLET);

String portletId = portlet.getPortletId();
String rootPortletId = portlet.getRootPortletId();
String instanceId = portlet.getInstanceId();

String portletPrimaryKey = PortletPermissionUtil.getPrimaryKey(plid.longValue(), portletId);

String queryString = (String)request.getAttribute(WebKeys.RENDER_PORTLET_QUERY_STRING);
String columnId = (String)request.getAttribute(WebKeys.RENDER_PORTLET_COLUMN_ID);
Integer columnPos = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_COLUMN_POS);
Integer columnCount = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_COLUMN_COUNT);
Boolean renderPortletResource = (Boolean)request.getAttribute(WebKeys.RENDER_PORTLET_RESOURCE);

boolean runtimePortlet = (renderPortletResource != null) && renderPortletResource.booleanValue();

boolean denyAccess = false;

try {
	ResourceLocalServiceUtil.getResource(company.getCompanyId(), rootPortletId, ResourceImpl.SCOPE_INDIVIDUAL, portletPrimaryKey);
}
catch (NoSuchResourceException nsre) {
	boolean addDefaultResource = false;

	if (runtimePortlet) {
		addDefaultResource = true;
	}
	else if (layoutTypePortlet.hasPortletId(portletId)) {
		addDefaultResource = true;
	}
	else if (portlet.isAddDefaultResource()) {
		addDefaultResource = true;
	}
	else if (themeDisplay.isSignedIn()) {
		if (portletId.equals(PortletKeys.LAYOUT_CONFIGURATION) || portletId.equals(PortletKeys.LAYOUT_MANAGEMENT)) {
			Group group = layout.getGroup();

			if (group.isCommunity()) {
				if (GroupPermissionUtil.contains(permissionChecker, portletGroupId.longValue(), ActionKeys.MANAGE_LAYOUTS) ||
					LayoutPermissionUtil.contains(permissionChecker, layout, ActionKeys.UPDATE)) {

					addDefaultResource = true;
				}
			}
			else if (group.isOrganization()) {
				long organizationId = group.getClassPK();

				if (OrganizationPermissionUtil.contains(permissionChecker, organizationId, ActionKeys.MANAGE_LAYOUTS)) {
					addDefaultResource = true;
				}
			}
			else if (group.isUser()) {
				addDefaultResource = true;
			}
		}
	}

	if (!portlet.hasAddPortletPermission(user.getUserId())) {
		addDefaultResource = false;
	}

	if (addDefaultResource) {
		ResourceLocalServiceUtil.addResources(company.getCompanyId(), layout.getGroupId(), 0, rootPortletId, portletPrimaryKey, true, true, true);
	}
	else {
		denyAccess = true;
	}
}

boolean access = PortletPermissionUtil.contains(permissionChecker, plid.longValue(), portlet, ActionKeys.VIEW);

boolean stateMax = layoutTypePortlet.hasStateMaxPortletId(portletId);
boolean stateMin = layoutTypePortlet.hasStateMinPortletId(portletId);

boolean modeAbout = layoutTypePortlet.hasModeAboutPortletId(portletId);
boolean modeConfig = layoutTypePortlet.hasModeConfigPortletId(portletId);
boolean modeEdit = layoutTypePortlet.hasModeEditPortletId(portletId);
boolean modeEditDefaults = layoutTypePortlet.hasModeEditDefaultsPortletId(portletId);
boolean modeEditGuest = layoutTypePortlet.hasModeEditGuestPortletId(portletId);
boolean modeHelp = layoutTypePortlet.hasModeHelpPortletId(portletId);
boolean modePreview = layoutTypePortlet.hasModePreviewPortletId(portletId);
boolean modePrint = layoutTypePortlet.hasModePrintPortletId(portletId);

CachePortlet cachePortlet = null;

try {
	cachePortlet = PortletInstanceFactory.create(portlet, application);
}
/*catch (UnavailableException ue) {
	ue.printStackTrace();
}*/
catch (PortletException pe) {
	pe.printStackTrace();
}
catch (RuntimeException re) {
	re.printStackTrace();
}

PortletPreferences portletSetup = PortletPreferencesFactoryUtil.getPortletSetup(request, portletId, true, true);

PortletPreferencesIds portletPreferencesIds = PortletPreferencesFactoryUtil.getPortletPreferencesIds(request, portletId);

PortletPreferences portletPreferences = PortletPreferencesLocalServiceUtil.getPreferences(portletPreferencesIds);

PortletConfig portletConfig = PortletConfigFactory.create(portlet, application);
PortletContext portletCtx = portletConfig.getPortletContext();

WindowState windowState = WindowState.NORMAL;

if (themeDisplay.isStateExclusive()) {
	windowState = LiferayWindowState.EXCLUSIVE;
}
else if (themeDisplay.isStatePopUp()) {
	windowState = LiferayWindowState.POP_UP;
}
else if (stateMax) {
	windowState = WindowState.MAXIMIZED;
}

PortletMode portletMode = PortletMode.VIEW;

if (modeAbout) {
	portletMode = LiferayPortletMode.ABOUT;
}
else if (modeConfig) {
	portletMode = LiferayPortletMode.CONFIG;
}
else if (modeEdit) {
	portletMode = PortletMode.EDIT;
}
else if (modeEditDefaults) {
	portletMode = LiferayPortletMode.EDIT_DEFAULTS;
}
else if (modeEditGuest) {
	portletMode = LiferayPortletMode.EDIT_GUEST;
}
else if (modeHelp) {
	portletMode = PortletMode.HELP;
}
else if (modePreview) {
	portletMode = LiferayPortletMode.PREVIEW;
}
else if (modePrint) {
	portletMode = LiferayPortletMode.PRINT;
}

HttpServletRequest originalReq = PortalUtil.getOriginalServletRequest(request);

RenderRequestImpl renderRequestImpl = RenderRequestFactory.create(originalReq, portlet, cachePortlet, portletCtx, windowState, portletMode, portletPreferences, plid.longValue());

if (Validator.isNotNull(queryString)) {
	DynamicServletRequest dynamicReq = (DynamicServletRequest)renderRequestImpl.getHttpServletRequest();

	String[] params = StringUtil.split(queryString, StringPool.AMPERSAND);

	for (int i = 0; i < params.length; i++) {
		String[] kvp = StringUtil.split(params[i], StringPool.EQUAL);

		if (kvp.length > 1) {
			dynamicReq.setParameter(kvp[0], kvp[1]);
		}
		else {
			dynamicReq.setParameter(kvp[0], StringPool.BLANK);
		}
	}
}

StringServletResponse stringServletRes = new StringServletResponse(response);

RenderResponseImpl renderResponseImpl = RenderResponseFactory.create(renderRequestImpl, stringServletRes, portletId, company.getCompanyId(), plid.longValue());

renderRequestImpl.defineObjects(portletConfig, renderResponseImpl);

String responseContentType = renderRequestImpl.getResponseContentType();

String currentURL = PortalUtil.getCurrentURL(request);

Portlet portletResourcePortlet = null;

if (portletId.equals(PortletKeys.PORTLET_CONFIGURATION)) {
	String portletResource = ParamUtil.getString(request, "portletResource");

	if (Validator.isNotNull(portletResource)) {
		portletResourcePortlet = PortletLocalServiceUtil.getPortletById(company.getCompanyId(), portletResource);
	}
}

boolean showCloseIcon = true;
boolean showConfigurationIcon = false;
boolean showEditIcon = false;
boolean showEditDefaultsIcon = false;
boolean showEditGuestIcon = false;
boolean showHelpIcon = portlet.hasPortletMode(responseContentType, PortletMode.HELP);
boolean showMaxIcon = true;
boolean showMinIcon = true;
boolean showMoveIcon = !stateMax && !themeDisplay.isStateExclusive();
boolean showPortletCssIcon = false;
boolean showPortletIcon = (portletResourcePortlet != null) ? Validator.isNotNull(portletResourcePortlet.getIcon()) : Validator.isNotNull(portlet.getIcon());
boolean showPrintIcon = portlet.hasPortletMode(responseContentType, LiferayPortletMode.PRINT);
boolean showRefreshIcon = portlet.isAjaxable() && (portlet.getRenderWeight() == 0);

Boolean portletParallelRender = (Boolean)request.getAttribute(WebKeys.PORTLET_PARALLEL_RENDER);

if ((portletParallelRender != null) && (portletParallelRender.booleanValue() == false)) {
	showRefreshIcon = false;
}

if (!portletId.equals(PortletKeys.PORTLET_CONFIGURATION)) {
	if (PortletPermissionUtil.contains(permissionChecker, plid.longValue(), portletId, ActionKeys.CONFIGURATION)) {
		showConfigurationIcon = true;

		if (PropsValues.PORTLET_CSS_ENABLED) {
			showPortletCssIcon = true;
		}
	}
}

if (portlet.hasPortletMode(responseContentType, PortletMode.EDIT)) {
	if (PortletPermissionUtil.contains(permissionChecker, plid.longValue(), portletId, ActionKeys.PREFERENCES)) {
		showEditIcon = true;
	}
}

if (portlet.hasPortletMode(responseContentType, LiferayPortletMode.EDIT_DEFAULTS)) {
	if (showEditIcon && !layout.isPrivateLayout() && themeDisplay.isShowAddContentIcon()) {
		showEditDefaultsIcon = true;
	}
}

if (portlet.hasPortletMode(responseContentType, LiferayPortletMode.EDIT_GUEST)) {
	if (showEditIcon && !layout.isPrivateLayout() && themeDisplay.isShowAddContentIcon()) {
		showEditGuestIcon = true;
	}
}

boolean supportsMimeType = portlet.hasPortletMode(responseContentType, portletMode);

if (responseContentType.equals(ContentTypes.XHTML_MP) && portlet.hasMultipleMimeTypes()) {
	supportsMimeType = GetterUtil.getBoolean(portletSetup.getValue("portlet-setup-supported-clients-mobile-devices-" + portletMode, String.valueOf(supportsMimeType)));
}

// Unauthenticated users and users without UPDATE permission for the layout
// cannot modify the layout

if (!themeDisplay.isSignedIn() ||
	!LayoutPermissionUtil.contains(permissionChecker, layout, ActionKeys.UPDATE)) {

	showCloseIcon = false;
	showMaxIcon = PropsValues.LAYOUT_GUEST_SHOW_MAX_ICON;
	showMinIcon = PropsValues.LAYOUT_GUEST_SHOW_MIN_ICON;
	showMoveIcon = false;
}

// Portlets cannot be moved unless they belong to the layout

if (!layoutTypePortlet.hasPortletId(portletId)) {
	showCloseIcon = false;
	showMoveIcon = false;
}

// Static portlets cannot be moved

if (portlet.isStatic()) {
	showCloseIcon = false;
	showMoveIcon = false;
}

// Deny access

if (denyAccess) {
	access = false;

	showCloseIcon = false;
	showConfigurationIcon = false;
	showEditIcon = false;
	showEditDefaultsIcon = false;
	showEditGuestIcon = false;
	showHelpIcon = false;
	showMaxIcon = false;
	showMinIcon = false;
	showMoveIcon = false;
	showPortletCssIcon = false;
	showPrintIcon = false;
}

portletDisplay.recycle();

portletDisplay.setId(portletId);
portletDisplay.setRootPortletId(rootPortletId);
portletDisplay.setInstanceId(instanceId);
portletDisplay.setResourcePK(portletPrimaryKey);
portletDisplay.setPortletName(portletConfig.getPortletName());
portletDisplay.setNamespace(PortalUtil.getPortletNamespace(portletId));

portletDisplay.setAccess(access);
portletDisplay.setActive(portlet.isActive());

portletDisplay.setColumnId(columnId);
portletDisplay.setColumnPos(columnPos.intValue());
portletDisplay.setColumnCount(columnCount.intValue());

portletDisplay.setStateExclusive(themeDisplay.isStateExclusive());
portletDisplay.setStateMax(stateMax);
portletDisplay.setStateMin(stateMin);
portletDisplay.setStatePopUp(themeDisplay.isStatePopUp());

portletDisplay.setModeAbout(modeAbout);
portletDisplay.setModeConfig(modeConfig);
portletDisplay.setModeEdit(modeEdit);
portletDisplay.setModeEditDefaults(modeEditDefaults);
portletDisplay.setModeEditGuest(modeEditGuest);
portletDisplay.setModeHelp(modeHelp);
portletDisplay.setModePreview(modePreview);
portletDisplay.setModePrint(modePrint);

portletDisplay.setShowCloseIcon(showCloseIcon);
portletDisplay.setShowConfigurationIcon(showConfigurationIcon);
portletDisplay.setShowEditIcon(showEditIcon);
portletDisplay.setShowEditDefaultsIcon(showEditDefaultsIcon);
portletDisplay.setShowEditGuestIcon(showEditGuestIcon);
portletDisplay.setShowHelpIcon(showHelpIcon);
portletDisplay.setShowMaxIcon(showMaxIcon);
portletDisplay.setShowMinIcon(showMinIcon);
portletDisplay.setShowMoveIcon(showMoveIcon);
portletDisplay.setShowPortletCssIcon(showPortletCssIcon);
portletDisplay.setShowPortletIcon(showPortletIcon);
portletDisplay.setShowPrintIcon(showPrintIcon);
portletDisplay.setShowRefreshIcon(showRefreshIcon);

portletDisplay.setRestoreCurrentView(portlet.isRestoreCurrentView());

// Portlet icon

String portletIcon = null;

if (portletResourcePortlet != null) {
	portletIcon = portletResourcePortlet.getContextPath() + portletResourcePortlet.getIcon();
}
else {
	portletIcon = portlet.getContextPath() + portlet.getIcon();
}

portletDisplay.setURLPortlet(themeDisplay.getCDNHost() + portletIcon);

// URL close

String urlClose = "javascript: closePortlet('" + plid.longValue() + "', '" + portletDisplay.getId() + "', '" + themeDisplay.getDoAsUserId() + "');";

portletDisplay.setURLClose(urlClose.toString());

// URL configuration

PortletURLImpl urlConfiguration = new PortletURLImpl(request, PortletKeys.PORTLET_CONFIGURATION, plid.longValue(), false);

urlConfiguration.setWindowState(WindowState.MAXIMIZED);

if (Validator.isNotNull(portlet.getConfigurationActionClass())) {
	urlConfiguration.setParameter("struts_action", "/portlet_configuration/edit_configuration");
}
else {
	urlConfiguration.setParameter("struts_action", "/portlet_configuration/edit_permissions");
}

urlConfiguration.setParameter("redirect", currentURL);
urlConfiguration.setParameter("returnToFullPageURL", currentURL);
urlConfiguration.setParameter("portletResource", portletDisplay.getId());
urlConfiguration.setParameter("resourcePrimKey", PortletPermissionUtil.getPrimaryKey(plid.longValue(), portlet.getPortletId()));

portletDisplay.setURLConfiguration("javascript: self.location = '" + HttpUtil.encodeURL(urlConfiguration.toString()) + "&" + PortalUtil.getPortletNamespace(PortletKeys.PORTLET_CONFIGURATION) + "previewWidth=' + document.getElementById('p_p_id" + portletDisplay.getNamespace() + "').offsetWidth;");

// URL edit

PortletURLImpl urlEdit = new PortletURLImpl(request, portletDisplay.getId(), plid.longValue(), false);

if (portletDisplay.isModeEdit()) {
	urlEdit.setWindowState(WindowState.NORMAL);
	urlEdit.setPortletMode(PortletMode.VIEW);
}
else {
	if (portlet.isMaximizeEdit()) {
		urlEdit.setWindowState(WindowState.MAXIMIZED);
	}
	else {
		urlEdit.setWindowState(WindowState.NORMAL);
	}

	urlEdit.setPortletMode(PortletMode.EDIT);
}

portletDisplay.setURLEdit(urlEdit.toString());

// URL edit defaults

PortletURLImpl urlEditDefaults = new PortletURLImpl(request, portletDisplay.getId(), plid.longValue(), false);

if (portletDisplay.isModeEditDefaults()) {
	urlEditDefaults.setWindowState(WindowState.NORMAL);
	urlEditDefaults.setPortletMode(PortletMode.VIEW);
}
else {
	if (portlet.isMaximizeEdit()) {
		urlEditDefaults.setWindowState(WindowState.MAXIMIZED);
	}
	else {
		urlEditDefaults.setWindowState(WindowState.NORMAL);
	}

	urlEditDefaults.setPortletMode(LiferayPortletMode.EDIT_DEFAULTS);
}

portletDisplay.setURLEditDefaults(urlEditDefaults.toString());

// URL edit guest

PortletURLImpl urlEditGuest = new PortletURLImpl(request, portletDisplay.getId(), plid.longValue(), false);

if (portletDisplay.isModeEditGuest()) {
	urlEditGuest.setWindowState(WindowState.NORMAL);
	urlEditGuest.setPortletMode(PortletMode.VIEW);
}
else {
	if (portlet.isMaximizeEdit()) {
		urlEditGuest.setWindowState(WindowState.MAXIMIZED);
	}
	else {
		urlEditGuest.setWindowState(WindowState.NORMAL);
	}

	urlEditGuest.setPortletMode(LiferayPortletMode.EDIT_GUEST);
}

portletDisplay.setURLEditGuest(urlEditGuest.toString());

// URL help

PortletURLImpl urlHelp = new PortletURLImpl(request, portletDisplay.getId(), plid.longValue(), false);

if (portletDisplay.isModeHelp()) {
	urlHelp.setWindowState(WindowState.NORMAL);
	urlHelp.setPortletMode(PortletMode.VIEW);
}
else {
	if (portlet.isMaximizeHelp()) {
		urlHelp.setWindowState(WindowState.MAXIMIZED);
	}
	else {
		urlHelp.setWindowState(WindowState.NORMAL);
	}

	urlHelp.setPortletMode(PortletMode.HELP);
}

portletDisplay.setURLHelp(urlHelp.toString());

// URL max

boolean action = !portletDisplay.isRestoreCurrentView();

PortletURLImpl urlMax = new PortletURLImpl(request, portletDisplay.getId(), plid.longValue(), action);

if (portletDisplay.isStateMax()) {
	urlMax.setWindowState(WindowState.NORMAL);
}
else {
	urlMax.setWindowState(WindowState.MAXIMIZED);
}

if (!action) {
	String portletNamespace = portletDisplay.getNamespace();

	Map renderParameters = RenderParametersPool.get(request, plid.longValue(), portletDisplay.getId());

	Iterator itr = renderParameters.entrySet().iterator();

	while (itr.hasNext()) {
		Map.Entry entry = (Map.Entry)itr.next();

		String key = (String)entry.getKey();

		if (key.startsWith(portletNamespace)) {
			key = key.substring(portletNamespace.length(), key.length());

			String[] values = (String[])entry.getValue();

			urlMax.setParameter(key, values);
		}
	}
}

portletDisplay.setURLMax(urlMax.toString());

// URL min

String urlMin = "javascript: minimizePortlet('" + plid.longValue() + "', '" + portletDisplay.getId() + "', " + portletDisplay.isStateMin() + ", '" + themeDisplay.getDoAsUserId() + "');";

portletDisplay.setURLMin(urlMin);

// URL portlet css

String urlPortletCss = "javascript: Liferay.PortletCSS.init('" + portletDisplay.getId() + "');";

portletDisplay.setURLPortletCss(urlPortletCss.toString());

// URL print

PortletURLImpl urlPrint = new PortletURLImpl(request, portletDisplay.getId(), plid.longValue(), false);

if (portletDisplay.isModePrint()) {
	urlPrint.setWindowState(WindowState.NORMAL);
	urlPrint.setPortletMode(PortletMode.VIEW);
}
else {
	if (portlet.isPopUpPrint()) {
		urlPrint.setWindowState(LiferayWindowState.POP_UP);
	}
	else {
		urlPrint.setWindowState(WindowState.NORMAL);
	}

	urlPrint.setPortletMode(LiferayPortletMode.PRINT);
}

portletDisplay.setURLPrint(urlPrint.toString());

// URL refresh

String urlRefresh = "javascript: " + portletDisplay.getNamespace() + "refreshPortlet();";

portletDisplay.setURLRefresh(urlRefresh);

// URL back

String urlBack = null;

if (portletDisplay.isModeEdit()) {
	urlBack = urlEdit.toString();
}
else if (portletDisplay.isModeEditDefaults()) {
	urlBack = urlEditDefaults.toString();
}
else if (portletDisplay.isModeEditGuest()) {
	urlBack = urlEditGuest.toString();
}
else if (portletDisplay.isModeHelp()) {
	urlBack = urlHelp.toString();
}
else if (portletDisplay.isModePrint()) {
	urlBack = urlPrint.toString();
}
else if (portletDisplay.isStateMax()) {
	//if (portletDisplay.getId().equals(PortletKeys.PORTLET_CONFIGURATION)) {
		/*String portletResource = ParamUtil.getString(request, "portletResource");

		urlMax.setAnchor(false);

		urlBack = urlMax.toString() + "#p_" + portletResource;*/

		//urlBack = ParamUtil.getString(renderRequestImpl, "returnToFullPageURL");
	//}
	//else {
	//	urlBack = urlMax.toString();
	//}

	urlBack = ParamUtil.getString(renderRequestImpl, "returnToFullPageURL");

	if (Validator.isNull(urlBack)) {
		urlBack = urlMax.toString();
	}
}

if (urlBack != null) {
	portletDisplay.setShowBackIcon(true);
	portletDisplay.setURLBack(urlBack);
}

// Make sure the Tiles context is reset for the next portlet

if ((cachePortlet != null) && cachePortlet.isStrutsPortlet()) {
	request.removeAttribute(ComponentConstants.COMPONENT_CONTEXT);
}

// Render portlet

boolean portletException = false;

if (portlet.isActive() && access && supportsMimeType) {
	try {
		cachePortlet.render(renderRequestImpl, renderResponseImpl);

		if (themeDisplay.isStateExclusive()) {
			renderRequestImpl.setAttribute(WebKeys.STRING_SERVLET_RESPONSE, stringServletRes);
		}
	}
	catch (UnavailableException ue) {
		portletException = true;

		PortletInstanceFactory.destroy(portlet);
	}
	catch (Exception e) {
		portletException = true;

		LogUtil.log(_log, e);
	}
}
%>

<%@ include file="/html/portal/render_portlet-ext.jsp" %>

<c:if test="<%= !themeDisplay.isStateExclusive() %>">

	<%
	String freeformStyles = StringPool.BLANK;

	if (themeDisplay.isFreeformLayout() && !runtimePortlet && !layoutTypePortlet.hasStateMax()) {
		StringMaker sm = new StringMaker();

		Properties freeformStyleProps = PropertiesUtil.load(portletSetup.getValue("portlet-freeform-styles", StringPool.BLANK));

		sm.append("style=\"position: absolute; ");
		sm.append("width: ");
		sm.append(GetterUtil.getString(freeformStyleProps.getProperty("width"), "400px"));
		sm.append("; ");
		sm.append("top: ");
		sm.append(GetterUtil.getString(freeformStyleProps.getProperty("top"), "0"));
		sm.append("; ");
		sm.append("left: ");
		sm.append(GetterUtil.getString(freeformStyleProps.getProperty("left"), "0"));
		sm.append(";\"");

		freeformStyles = sm.toString();
	}
	%>

	<div id="p_p_id<%= renderResponseImpl.getNamespace() %>" class="portlet-boundary portlet-boundary<%= PortalUtil.getPortletNamespace(portlet.getRootPortletId()) %> <%= portlet.getCssClassWrapper() %>" <%= freeformStyles %>>
		<a name="p_<%= portletId %>"></a>
</c:if>

<c:choose>
	<c:when test="<%= !supportsMimeType %>">
	</c:when>
	<c:when test="<%= !access && !portlet.isShowPortletAccessDenied() %>">
	</c:when>
	<c:when test="<%= !portlet.isActive() && !portlet.isShowPortletInactive() %>">
	</c:when>
	<c:otherwise>

		<%
		boolean useDefaultTemplate = portlet.isUseDefaultTemplate();
		Boolean useDefaultTemplateObj = renderResponseImpl.getUseDefaultTemplate();

		if (useDefaultTemplateObj != null) {
			useDefaultTemplate = useDefaultTemplateObj.booleanValue();
		}

		if ((cachePortlet != null) && cachePortlet.isStrutsPortlet()) {
			if (!access || portletException) {
				PortletRequestProcessor portletReqProcessor = (PortletRequestProcessor)portletCtx.getAttribute(WebKeys.PORTLET_STRUTS_PROCESSOR);

				ActionMapping actionMapping = portletReqProcessor.processMapping(request, response, (String)portlet.getInitParams().get("view-action"));

				ComponentDefinition definition = null;

				if (actionMapping != null) {

					// See action path /weather/view

					String definitionName = actionMapping.getForward();

					if (definitionName == null) {

						// See action path /journal/view_articles

						String[] definitionNames = actionMapping.findForwards();

						for (int definitionNamesPos = 0; definitionNamesPos < definitionNames.length; definitionNamesPos++) {
							if (definitionNames[definitionNamesPos].endsWith("view")) {
								definitionName = definitionNames[definitionNamesPos];

								break;
							}
						}

						if (definitionName == null) {
							definitionName = definitionNames[0];
						}
					}

					definition = TilesUtil.getDefinition(definitionName, request, application);
				}

				String templatePath = StrutsUtil.TEXT_HTML_DIR + "/common/themes/portlet.jsp";

				if (definition != null) {
					templatePath = StrutsUtil.TEXT_HTML_DIR + definition.getPath();
				}
		%>

				<tiles:insert template="<%= templatePath %>" flush="false">
					<tiles:put name="portlet_content" value="/portal/portlet_error.jsp" />
				</tiles:insert>

		<%
			}
			else {
				if (useDefaultTemplate) {
					renderRequestImpl.setAttribute(WebKeys.PORTLET_CONTENT, stringServletRes.getString());
		%>

					<tiles:insert template='<%= StrutsUtil.TEXT_HTML_DIR + "/common/themes/portlet.jsp" %>' flush="false">
						<tiles:put name="portlet_content" value="<%= StringPool.BLANK %>" />
					</tiles:insert>

		<%
				}
				else {
					pageContext.getOut().print(stringServletRes.getString());
				}
			}
		}
		else {
			renderRequestImpl.setAttribute(WebKeys.PORTLET_CONTENT, stringServletRes.getString());

			String portletContent = StringPool.BLANK;

			if (portletException) {
				portletContent = "/portal/portlet_error.jsp";
			}
		%>

			<c:choose>
				<c:when test="<%= useDefaultTemplate || portletException %>">
					<tiles:insert template='<%= StrutsUtil.TEXT_HTML_DIR + "/common/themes/portlet.jsp" %>' flush="false">
						<tiles:put name="portlet_content" value="<%= portletContent %>" />
					</tiles:insert>
				</c:when>
				<c:otherwise>
					<%= renderRequestImpl.getAttribute(WebKeys.PORTLET_CONTENT) %>
				</c:otherwise>
			</c:choose>

		<%
		}
		%>

	</c:otherwise>
</c:choose>

<c:if test="<%= !themeDisplay.isStateExclusive() %>">
	</div>
</c:if>

<%
String staticVar = "yes";

if (portletDisplay.isShowMoveIcon()) {
	staticVar = "no";
}
else {
	if (portlet.isStaticStart()) {
		staticVar = "start";
	}

	if (portlet.isStaticEnd()) {
		staticVar = "end";
	}
}
%>

<c:if test="<%= !themeDisplay.isStateExclusive() %>">
	<script type="text/javascript">
		<c:if test="<%= !runtimePortlet %>">
			document.getElementById("p_p_id<%= renderResponseImpl.getNamespace() %>").portletId = "<%= portletDisplay.getId() %>";
			document.getElementById("p_p_id<%= renderResponseImpl.getNamespace() %>").columnPos = <%= columnPos %>;

			<c:if test='<%= !staticVar.equals("no") %>'>
				document.getElementById("p_p_id<%= renderResponseImpl.getNamespace() %>").isStatic = "<%= staticVar %>";
			</c:if>

			if (!Liferay.Portlet.isAjax("<%= portletDisplay.getId() %>")) {
				Liferay.Portlet.process("<%= portletDisplay.getId() %>");
			}
		</c:if>

		<c:if test="<%= PortletPermissionUtil.contains(permissionChecker, plid.longValue(), portletId, ActionKeys.CONFIGURATION) %>">
			jQuery(
				function() {
					Liferay.Util.portletTitleEdit(
						{
							obj: jQuery("#p_p_id_<%= portletDisplay.getId() %>_"),
							plid: "<%= layout.getPlid() %>",
							doAsUserId: "<%= themeDisplay.getDoAsUserId() %>",
							portletId: "<%= portletDisplay.getId() %>"
						}
					);
				}
			);
		</c:if>
	</script>
</c:if>

<%
if (showPortletCssIcon) {
	themeDisplay.setIncludePortletCssJs(true);
}

SessionMessages.clear(renderRequestImpl);
SessionErrors.clear(renderRequestImpl);

if (themeDisplay.isStateExclusive()) {
	request.setAttribute(JavaConstants.JAVAX_PORTLET_REQUEST, renderRequestImpl);
	request.setAttribute(JavaConstants.JAVAX_PORTLET_RESPONSE, renderResponseImpl);
}
else {
	RenderRequestFactory.recycle(renderRequestImpl);
	RenderResponseFactory.recycle(renderResponseImpl);
}
%>

<%!
private static Log _log = LogFactoryUtil.getLog("portal-web.docroot.html.portal.render_portlet.jsp");
%>