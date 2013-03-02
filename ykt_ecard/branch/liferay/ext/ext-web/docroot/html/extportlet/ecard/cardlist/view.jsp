<%@ include file="/html/extportlet/ecard/cardlist/init.jsp"%>

<%
	List list = ((ResultPage) request.getAttribute("result")).getList();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table cellpadding="4" cellspacing="0" width="100%">
<c:if test="<%=PermissionUtil.hasCardlistAdmin(request)%>">
	<tr>
		<td width="166" class="text_brown">	
	<a class="brown_link"
					href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ecardlist/admin" /></portlet:renderURL>"><bean:message
						key="ecard.management" />
				</a>			
		</td>
	</tr>
</c:if>
	<tr>
		<td>
			&nbsp;
		</td>
	</tr>
	<tr>
		<td>
			&nbsp;
		</td>
	</tr>

	<%
		java.util.Iterator it = list.iterator();
		while (it.hasNext()) {
			EcardInformation info = (EcardInformation) it.next();
	%>
	<tr>
		<td>
			<a class=brown_link_line
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardlistview" /></portlet:renderURL>&id=<%=info.getId()%>">
				<%=info.getInfoTitle()%>(<%=info.getCreateDate() == null ? "" : format
						.format(info.getCreateDate())%>)</a>
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
	<tr>
		<td>
			&nbsp;
		</td>
	</tr>
	<tr>
		<td align=right>
			<a class=text_brown
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardlistview" /></portlet:renderURL>">
				<bean:message key="ecard.more" />>></a>
		</td>
	</tr>
</table>