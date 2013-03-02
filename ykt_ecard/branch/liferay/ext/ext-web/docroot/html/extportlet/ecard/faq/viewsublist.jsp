<%@ include file="/html/extportlet/ecard/faq/init.jsp"%>

<%
	ResultPage result = (ResultPage) request.getAttribute("result");
	List subList = result.getList();
%>
<table width="719" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>
		<c:if test="<%= PermissionUtil.hasFAQAdmin(request)%>">
			<a class="txt_or"
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardfaqview" /></portlet:renderURL>">
				<bean:message key="ecardfaq.tab.faqlist" /> </a> ·
			<a class="txt_or"
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardfaqadmin" /></portlet:renderURL>">
				<bean:message key="ecard.management" /> </a> .
			<a class="txt_or"
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardfaqadmin_type" /></portlet:renderURL>">
				<bean:message key="ecard.managesubtype" /> </a>
		</c:if>
		</td>
	</tr>
</table>
<table width="100" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td height="5"></td>
	</tr>
</table>
<table width="719" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top">
			<!-- content table -->

			<table cellpadding="4" cellspacing="0" width="100%">


				<%
					java.util.Iterator it = subList.iterator();
					while (it.hasNext()) {
						InfoType type = (InfoType) it.next();
				%>
				<tr>
					<td>
						<img src="/html/extthemes/classic/images/ecard/jiantou.jpg"
							width="8" height="8">
						<a
							href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardfaqview" /></portlet:renderURL>&subid=<%=type.getInfoType()%>"
							class=blue_link_line> <%=type.getInfoName()%></a>
					</td>
				</tr>
				<%
					}
				%>
				<tr>
					<td>
						&nbsp;
					</td>
				</tr>
			</table>
			<!-- content table -->
		</td>
		<td>
			&nbsp;
		</td>
	</tr>
</table>