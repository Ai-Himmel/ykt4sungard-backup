
<%@ include file="/html/portlet/ecard/link/init.jsp" %>
<td width="166" class="text_brown">&nbsp;
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardlink/view" /></portlet:renderURL>"><bean:message key="frindslink" /></a>
	·
	<c:if test="<%= PermissionUtil.hasNewsAdmin(request)%>">
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardlink/admin" /></portlet:renderURL>"><bean:message key="frindslink.manager" /></a>
	</c:if>
</td>
