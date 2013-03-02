<%@ include file="/html/extportlet/ecard/lostfound/init.jsp" %>


<td width="166" class="text_brown">&nbsp;
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/lostfound/view" /></portlet:renderURL>"><bean:message key="lostfound.tab.lostfound" /></a>
	·
	<c:if test="<%= PermissionUtil.hasLostFoundAdmin(request)%>">
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/lostfound/admin" /></portlet:renderURL>"><bean:message key="ecard.management" /></a>
	·
	</c:if>
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/lostfound/view" /></portlet:renderURL>"><bean:message key="ecard.search" /></a>
</td>