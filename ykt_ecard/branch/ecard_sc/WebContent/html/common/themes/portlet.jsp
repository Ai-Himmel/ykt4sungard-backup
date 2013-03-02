

<%@ include file="/html/common/init.jsp" %>

<portlet:defineObjects />

<tiles:useAttribute id="tilesPortletSubNav" name="portlet_sub_nav" classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesPortletContent" name="portlet_content" classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesPortletDecorate" name="portlet_decorate" classname="java.lang.String" ignore="true" />

<%
boolean portletDecorate = GetterUtil.get(tilesPortletDecorate, true);

RenderResponseImpl renderResponseImpl = (RenderResponseImpl)renderResponse;

// Portlet title

if (portletDisplay.isAccess() && portletDisplay.isActive()) {
	portletDisplay.setTitle(renderResponseImpl.getTitle());
}
else {
	portletDisplay.setTitle(portletConfig.getResourceBundle(locale).getString(WebKeys.JAVAX_PORTLET_TITLE));
}

// URL Edit

PortletURL urlEdit = new PortletURLImpl(request, portletDisplay.getId(), layoutId, false);

if (portletDisplay.isModeEdit()) {
	urlEdit.setWindowState(WindowState.NORMAL);
	urlEdit.setPortletMode(PortletMode.VIEW);
}
else {
	urlEdit.setWindowState(WindowState.MAXIMIZED);
	urlEdit.setPortletMode(PortletMode.EDIT);
}

urlEdit.setSecure(request.isSecure());

portletDisplay.setURLEdit(urlEdit);

// URL Help

PortletURL urlHelp = new PortletURLImpl(request, portletDisplay.getId(), layoutId, false);

if (portletDisplay.isModeHelp()) {
	urlHelp.setWindowState(WindowState.NORMAL);
	urlHelp.setPortletMode(PortletMode.VIEW);
}
else {
	urlHelp.setWindowState(WindowState.MAXIMIZED);
	urlHelp.setPortletMode(PortletMode.HELP);
}

urlHelp.setSecure(request.isSecure());

portletDisplay.setURLHelp(urlHelp);

// URL Max

boolean action = !portletDisplay.isRestoreCurrentView();

PortletURL urlMax = new PortletURLImpl(request, portletDisplay.getId(), layoutId, action);

if (portletDisplay.isStateMax()) {
	urlMax.setWindowState(WindowState.NORMAL);
}
else {
	urlMax.setWindowState(WindowState.MAXIMIZED);
}

if (!action) {
	String portletNamespace = PortalUtil.getPortletNamespace(portletDisplay.getId());

	Map renderParameters = RenderParametersPool.get(request, layoutId, portletDisplay.getId());

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

urlMax.setSecure(request.isSecure());

portletDisplay.setURLMax(urlMax);
%>

<c:if test="<%= !portletDisplay.isStatePopUp() %>">

	<c:if test="<%= portletDecorate %>">
		<theme:box top="portlet_top.jsp" bottom="portlet_bottom.jsp">
			<!--
			<div id="p_p_content<%= PortalUtil.getPortletNamespace(portletDisplay.getId()) %>" style="margin-top: 0; margin-bottom: 0;">
			-->
				<%@ include file="/html/common/themes/portlet_content.jsp" %>
			<!--
			</div>
			-->
		</theme:box>
	</c:if>

	<c:if test="<%= !portletDecorate %>">
		<%@ include file="/html/common/themes/ecard_portlet_content.jsp" %>
	</c:if>
</c:if>

<c:if test="<%= portletDisplay.isStatePopUp() %>">
	<table border="0" cellpadding="0" cellspacing="0" height="100%" width="100%">
	<tr class="gamma">
		<td align="center" valign="middle">
			<table border="0" cellpadding="0" cellspacing="0">
			<tr>
				<td align="center">
					<c:if test="<%= Validator.isNotNull(tilesPortletContent) %>">
						<liferay:include page="<%= Constants.TEXT_HTML_DIR + tilesPortletContent %>" flush="true" />
					</c:if>

					<c:if test="<%= Validator.isNull(tilesPortletContent) %>">

						<%
						pageContext.getOut().print(renderRequest.getAttribute(WebKeys.PORTLET_CONTENT));
						%>

					</c:if>
				</td>
			</tr>
			</table>
		</td>
	</tr>
	</table>
</c:if>