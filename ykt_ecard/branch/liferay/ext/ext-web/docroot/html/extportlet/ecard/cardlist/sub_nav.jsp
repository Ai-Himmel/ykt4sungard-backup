<%@ include file="/html/extportlet/ecard/cardlist/init.jsp" %>


<td width="166" class="text_brown">&nbsp;
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardlist/view" /></portlet:renderURL>"><bean:message key="ecardlist.tab.cardlist" /></a>
	·
	<c:if test="<%= PermissionUtil.hasCardlistAdmin(request)%>">
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardlist/admin" /></portlet:renderURL>"><bean:message key="ecard.management" /></a>
	·
	</c:if>
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardlist/view" /></portlet:renderURL>"><bean:message key="ecard.search" /></a>
</td>