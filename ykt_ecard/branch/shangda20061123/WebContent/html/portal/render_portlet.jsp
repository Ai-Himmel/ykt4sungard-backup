<%
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
%>

<%@ include file="/html/portal/init.jsp" %>

<%
Portlet portlet = (Portlet)request.getAttribute(WebKeys.RENDER_PORTLET);
Integer portletWidth = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_WIDTH);
String[] columnOrder = StringUtil.split(layoutTypePortlet.getColumnOrder());
String curColumnOrder = (String)request.getAttribute(WebKeys.RENDER_PORTLET_CUR_COLUMN_ORDER);
Integer curColumnPos = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_CUR_COLUMN_POS);
Integer curColumnCount = (Integer)request.getAttribute(WebKeys.RENDER_PORTLET_CUR_COLUMN_COUNT);

boolean access = RoleLocalServiceUtil.hasRoles(user.getUserId(), portlet.getRolesArray());

boolean stateMax = layoutTypePortlet.hasStateMaxPortletId(portlet.getPortletId());
boolean stateMin = layoutTypePortlet.hasStateMinPortletId(portlet.getPortletId());

boolean modeAbout = layoutTypePortlet.hasModeAboutPortletId(portlet.getPortletId());
boolean modeConfig = layoutTypePortlet.hasModeConfigPortletId(portlet.getPortletId());
boolean modeEdit = layoutTypePortlet.hasModeEditPortletId(portlet.getPortletId());
boolean modeEditDefaults = layoutTypePortlet.hasModeEditDefaultsPortletId(portlet.getPortletId());
boolean modeHelp = layoutTypePortlet.hasModeHelpPortletId(portlet.getPortletId());
boolean modePreview = layoutTypePortlet.hasModePreviewPortletId(portlet.getPortletId());
boolean modePrint = layoutTypePortlet.hasModePrintPortletId(portlet.getPortletId());

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

PortletPreferences portletPrefs = PortletPreferencesServiceUtil.getPreferences(company.getCompanyId(), PortalUtil.getPortletPreferencesPK(request, portlet.getPortletId()));

PortletConfig portletConfig = PortletConfigFactory.create(portlet, application);
PortletContext portletCtx = portletConfig.getPortletContext();

WindowState windowState = WindowState.NORMAL;
if (themeDisplay.isStatePopUp()) {
	windowState = LiferayWindowState.POP_UP;
}
else if (stateMax) {
	windowState = WindowState.MAXIMIZED;
}
PortletMode portletMode = PortletMode.VIEW;
if (modeEdit) {
	portletMode = PortletMode.EDIT;
}
else if (modeHelp) {
	portletMode = PortletMode.HELP;
}

RenderRequestImpl renderRequestImpl = RenderRequestFactory.create(request, portlet, cachePortlet, portletCtx, windowState, portletMode, portletPrefs, layoutId);

StringServletResponse stringServletRes = new StringServletResponse(response);

RenderResponseImpl renderResponseImpl = RenderResponseFactory.create(renderRequestImpl, stringServletRes, portlet.getPortletId(), company.getCompanyId(), layoutId);

renderRequestImpl.defineObjects(portletConfig, renderResponseImpl);

boolean showEditIcon = false;
if (portlet.hasPortletMode(renderResponseImpl.getContentType(), PortletMode.EDIT)) {
	if (!layout.isGroup()) {
		showEditIcon = true;
	}
	else {
		if (portlet.isPreferencesOwnedByGroup()) {
			if (RoleLocalServiceUtil.hasRole(user.getUserId(), Role.ADMINISTRATOR)) {
				showEditIcon = true;
			}
		}
		else {
			showEditIcon = true;
		}
	}
}

boolean showHelpIcon = portlet.hasPortletMode(renderResponseImpl.getContentType(), PortletMode.HELP);
boolean showMoveIcon = (curColumnCount.intValue() > 1) ? true : false;
boolean showMinIcon = (modeEdit || modeHelp || (columnOrder.length == 1 && curColumnCount.intValue() == 1) || (layoutTypePortlet.getPortletIds().length == 1)) ? false : true;
boolean showMaxIcon = (modeEdit || modeHelp || (columnOrder.length == 1 && curColumnCount.intValue() == 1 && !stateMax)) ? false : true;
boolean showCloseIcon = true;

// Only administrators can remove or move portlets on a group layout

if (layout.isGroup() && !RoleLocalServiceUtil.hasRole(user.getUserId(), Role.ADMINISTRATOR)) {
	showMoveIcon = false;
	showCloseIcon = false;
}

// Unauthenticated users cannot modify the layout

if (!themeDisplay.isSignedIn()) {
	showEditIcon = false;
	//showHelpIcon = false;
	showMoveIcon = false;
	showMinIcon = GetterUtil.getBoolean(PropsUtil.get(PropsUtil.LAYOUT_GUEST_SHOW_MIN_ICON));
	showMaxIcon = GetterUtil.getBoolean(PropsUtil.get(PropsUtil.LAYOUT_GUEST_SHOW_MAX_ICON));
	showCloseIcon = false;
}

// Portlets cannot be moved unless they belong to the layout

if (!layoutTypePortlet.hasPortletId(portlet.getPortletId())) {
	showMoveIcon = false;
	showCloseIcon = false;
}

// Static portlets cannot be moved

if (portlet.isStatic()) {
	showMoveIcon = false;
	showCloseIcon = false;
}

portletDisplay.recycle();

portletDisplay.setId(portlet.getPortletId());
portletDisplay.setWidth(portletWidth.intValue());
portletDisplay.setNarrow(portlet.isNarrow());

portletDisplay.setAccess(access);
portletDisplay.setActive(portlet.isActive());

portletDisplay.setCurColumnOrder(curColumnOrder);
portletDisplay.setCurColumnPos(curColumnPos.intValue());
portletDisplay.setCurColumnCount(curColumnCount.intValue());

portletDisplay.setStateMax(stateMax);
portletDisplay.setStateMin(stateMin);
portletDisplay.setStatePopUp(themeDisplay.isStatePopUp());

portletDisplay.setModeAbout(modeAbout);
portletDisplay.setModeConfig(modeConfig);
portletDisplay.setModeEdit(modeEdit);
portletDisplay.setModeEditDefaults(modeEditDefaults);
portletDisplay.setModeHelp(modeHelp);
portletDisplay.setModePreview(modePreview);
portletDisplay.setModePrint(modePrint);

portletDisplay.setShowEditIcon(showEditIcon);
portletDisplay.setShowHelpIcon(showHelpIcon);
portletDisplay.setShowMoveIcon(showMoveIcon);
portletDisplay.setShowMinIcon(showMinIcon);
portletDisplay.setShowMaxIcon(showMaxIcon);
portletDisplay.setShowCloseIcon(showCloseIcon);

portletDisplay.setRestoreCurrentView(portlet.isRestoreCurrentView());

if ((cachePortlet != null) && cachePortlet.isStrutsPortlet()) {

	// Make sure the Tiles context is reset for the next portlet

	request.removeAttribute(ComponentConstants.COMPONENT_CONTEXT);
}

boolean portletException = false;

if (portlet.isActive() && access) {
	try {
		cachePortlet.render(renderRequestImpl, renderResponseImpl);
	}
	catch (UnavailableException ue) {
		portletException = true;

		PortletInstanceFactory.destroy(portlet);
	}
	catch (Exception e) {
		portletException = true;

		e.printStackTrace();
	}

	SessionMessages.clear(renderRequestImpl);
	SessionErrors.clear(renderRequestImpl);
}
%>

<c:if test="<%= Validator.isNotNull(curColumnOrder) %>">
	<script language="JavaScript">
		<%= curColumnOrder %>Portlets[<%= curColumnPos.intValue() %>] = "<%= portlet.getPortletId() %>";
		<%= curColumnOrder %>PortletsStatic[<%= curColumnPos.intValue() %>] = "<%= portlet.isStatic() %>";
	</script>
</c:if>

<%
boolean showPortletAccessDenied = portlet.isShowPortletAccessDenied();
boolean showPortletInactive = portlet.isShowPortletInactive();
%>
<!--
<a name="p_<%= portlet.getPortletId() %>"></a>
-->
<div id="p_p_id<%= renderResponseImpl.getNamespace() %>">
	<c:choose>
		<c:when test="<%= !access && !portlet.isShowPortletAccessDenied() %>">
		</c:when>
		<c:when test="<%= !portlet.isActive() && !portlet.isShowPortletInactive() %>">
		</c:when>
		<c:when test="<%= portlet.isNs4Compatible() && BrowserSniffer.is_ns_4(request) %>">
			<tiles:insert template='<%= Constants.TEXT_HTML_DIR + "/common/themes/portlet.jsp" %>' flush="false">
				<tiles:put name="portlet_content" value="/portal/portlet_not_supported.jsp" />
			</tiles:insert>
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

					String templatePath = Constants.TEXT_HTML_DIR + "/common/themes/portlet.jsp";
					if (definition != null) {
						templatePath = Constants.TEXT_HTML_DIR + definition.getPath();
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

						<tiles:insert template='<%= Constants.TEXT_HTML_DIR + "/common/themes/portlet.jsp" %>' flush="false">
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
						<tiles:insert template='<%= Constants.TEXT_HTML_DIR + "/common/themes/portlet.jsp" %>' flush="false">
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
</div>

<%
RenderRequestFactory.recycle(renderRequestImpl);
RenderResponseFactory.recycle(renderResponseImpl);
%>