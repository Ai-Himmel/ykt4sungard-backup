<%@ include file="/html/portlet/ecard/cardnews/init.jsp" %>


<td width="166" class="text_brown">&nbsp;
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardnews/view" /></portlet:renderURL>"><bean:message key="ecardnews.tab.newslist" /></a>
	·
	<c:if test="<%= PermissionUtil.hasNewsAdmin(request)%>">
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardnews/admin" /></portlet:renderURL>"><bean:message key="ecard.management" /></a>
	·
	</c:if>
	<a class="brown_link" href="<portlet:renderURL windowState="<%= WindowState.MAXIMIZED.toString() %>" portletMode="<%= PortletMode.VIEW.toString() %>"><portlet:param name="struts_action" value="/ecardnews/view" /></portlet:renderURL>"><bean:message key="ecard.search" /></a>
</td>