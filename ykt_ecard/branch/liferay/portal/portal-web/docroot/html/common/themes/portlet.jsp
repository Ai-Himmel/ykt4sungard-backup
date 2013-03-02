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

<%@ include file="/html/common/init.jsp" %>

<portlet:defineObjects />

<tiles:useAttribute id="tilesPortletContent" name="portlet_content" classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesPortletDecorate" name="portlet_decorate" classname="java.lang.String" ignore="true" />
<tiles:useAttribute id="tilesPortletPadding" name="portlet_padding" classname="java.lang.String" ignore="true" />

<%
Portlet portlet = (Portlet)request.getAttribute(WebKeys.RENDER_PORTLET);

PortletPreferences portletSetup = PortletPreferencesFactoryUtil.getPortletSetup(request, portletDisplay.getId(), true, true);

RenderResponseImpl renderResponseImpl = (RenderResponseImpl)renderResponse;

// Portlet decorate

boolean tilesPortletDecorateBoolean = GetterUtil.getBoolean(tilesPortletDecorate, true);

boolean portletDecorateDefault = false;

if (tilesPortletDecorateBoolean) {
	portletDecorateDefault = GetterUtil.getBoolean(theme.getSetting("portlet-setup-show-borders-default"), true);
}

boolean portletDecorate = GetterUtil.getBoolean(portletSetup.getValue("portlet-setup-show-borders", String.valueOf(portletDecorateDefault)));

Boolean portletDecorateObj = (Boolean)request.getAttribute(WebKeys.PORTLET_DECORATE);

if (portletDecorateObj != null) {
	portletDecorate = portletDecorateObj.booleanValue();

	request.removeAttribute(WebKeys.PORTLET_DECORATE);
}

// Portlet title

String portletTitle = PortletConfigurationUtil.getPortletTitle(portletSetup, themeDisplay.getLanguageId());

if (portletDisplay.isAccess() && portletDisplay.isActive()) {
	if (Validator.isNull(portletTitle)) {
		portletTitle = renderResponseImpl.getTitle();
	}
}

if (Validator.isNull(portletTitle)) {
	ResourceBundle resourceBundle = portletConfig.getResourceBundle(locale);

	portletTitle = resourceBundle.getString(JavaConstants.JAVAX_PORTLET_TITLE);
}

portletDisplay.setTitle(portletTitle);

Boolean renderPortletResource = (Boolean)request.getAttribute(WebKeys.RENDER_PORTLET_RESOURCE);

boolean runtimePortlet = (renderPortletResource != null) && renderPortletResource.booleanValue();

boolean freeformPortlet = themeDisplay.isFreeformLayout() && !runtimePortlet && !layoutTypePortlet.hasStateMax();

String containerStyles = StringPool.BLANK;

StringMaker sm = new StringMaker();

sm.append("style=\"");

if (freeformPortlet) {
	Properties freeformStyleProps = PropertiesUtil.load(portletSetup.getValue("portlet-freeform-styles", StringPool.BLANK));

	sm.append("height: ");
	sm.append(GetterUtil.getString(freeformStyleProps.getProperty("height"), "300px"));
	sm.append(";");
	sm.append("overflow: auto;");
}

if (portletDisplay.isStateMin()) {
	sm.append("display: none;");
}

sm.append("\"");

containerStyles = sm.toString();
%>

<c:choose>
	<c:when test="<%= themeDisplay.isStateExclusive() %>">
		<%@ include file="/html/common/themes/portlet_content_wrapper.jspf" %>
	</c:when>
	<c:when test="<%= themeDisplay.isStatePopUp() %>">
		<div>
			<c:if test="<%= Validator.isNotNull(tilesPortletContent) %>">
				<liferay-util:include page="<%= StrutsUtil.TEXT_HTML_DIR + tilesPortletContent %>" />
			</c:if>

			<c:if test="<%= Validator.isNull(tilesPortletContent) %>">

				<%
				pageContext.getOut().print(renderRequest.getAttribute(WebKeys.PORTLET_CONTENT));
				%>

			</c:if>
		</div>
	</c:when>
	<c:otherwise>
		<c:choose>
			<c:when test="<%= portletDecorate %>">
				<liferay-theme:wrap-portlet page="portlet.jsp">
					<div class="portlet-content-container" <%= containerStyles %>>
						<%@ include file="/html/common/themes/portlet_content_wrapper.jspf" %>
					</div>
				</liferay-theme:wrap-portlet>

				<c:if test="<%= freeformPortlet && LayoutPermissionUtil.contains(permissionChecker, layout, ActionKeys.UPDATE) %>">
					<div class="portlet-decorate-resize-container">
						<div class="portlet-resize-handle"></div>
					</div>
				</c:if>
			</c:when>
			<c:otherwise>
				<div class="portlet-borderless-container" <%= containerStyles %>>
					<c:if test="<%= (tilesPortletDecorateBoolean && portletDisplay.isShowConfigurationIcon()) || portletDisplay.isShowBackIcon() %>">
						<div class="portlet-borderless-bar">
							<c:if test="<%= tilesPortletDecorateBoolean && portletDisplay.isShowConfigurationIcon() %>">
								<span class="portlet-title-default"><%= portletDisplay.getTitle() %></span>

								- <a href="<%= portletDisplay.getURLPortletCss() %>"><liferay-ui:message key="look-and-feel" /></a>

								- <a href="<%= portletDisplay.getURLConfiguration() %>"><liferay-ui:message key="configuration" /></a>

								<c:if test="<%= portletDisplay.isShowEditIcon() %>">
									- <a href="<%= portletDisplay.getURLEdit() %>"><liferay-ui:message key="preferences" /></a>
								</c:if>

								<c:if test="<%= portletDisplay.isShowCloseIcon() %>">
									- <a href="<%= portletDisplay.getURLClose() %>"><liferay-ui:message key="close" /></a>
								</c:if>
							</c:if>

							<c:if test="<%= portletDisplay.isShowBackIcon() %>">
								- <a href="<%= portletDisplay.getURLBack() %>"><liferay-ui:message key="back" /></a>
							</c:if>
						</div>
					</c:if>

					<%@ include file="/html/common/themes/portlet_content_wrapper.jspf" %>
				</div>

				<c:if test="<%= freeformPortlet %>">
					<div class="portlet-resize-container">
						<div class="portlet-resize-handle"></div>
					</div>
				</c:if>
			</c:otherwise>
		</c:choose>
	</c:otherwise>
</c:choose>