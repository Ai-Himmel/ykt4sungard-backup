<%@ include file="/html/extportlet/ecard/lostfound/init.jsp"%>

<%
	List list = ((ResultPage) request.getAttribute("result")).getList();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table cellpadding="4" cellspacing="0" width="95%" align="center">
	<c:if test="<%=PermissionUtil.hasLostFoundAdmin(request)%>">
		<tr>
			<td width="166" class="text_brown">
				<a class="brown_link"
					href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/lostfoundadmin" /></portlet:renderURL>"><bean:message
						key="ecard.management" /> </a>
			</td>
		</tr>
	</c:if>
	<tr height="15px">
		<td>
			&nbsp;
		</td>
	</tr>

	<%
		java.util.Iterator it = list.iterator();
		while (it.hasNext()) {
			EcardInformation info = (EcardInformation) it.next();
	%>
	<tr height="20px">
		<td>
			<img src="/html/extthemes/classic/images/ecard/jiantou.jpg" width="8"
				height="8">
			<a class="brown_link_line"
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/lostfoundview" /></portlet:renderURL>&id=<%=info.getId()%>">
				<%=info.getInfoTitle()%>(<%=format.format(info.getCreateDate())%>) </a>
			<c:if test="<%=DateFormatUtil.isHotInfo(info.getCreateDate())%>">
				<img src="/html/extthemes/classic/images/ecard/hot.gif" width="17"
					height="8">
			</c:if>
		</td>
	</tr>
	<%
		}
	%>
	<tr height="15px">
		<td>
			&nbsp;
		</td>
	</tr>
	<tr>
		<td align=right>
			<a class=text_brown
				href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/lostfoundview" /></portlet:renderURL>">
				<bean:message key="ecard.more" />>></a>
		</td>
	</tr>
</table>

