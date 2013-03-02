
<%@page
	import="com.kingstargroup.ecard.portlet.hitinfo.service.HitInfoServiceUtil"%>
<%@ include file="/html/extportlet/ecard/hitinfo/init.jsp"%>
<%@ include file="/html/extportlet/ecard/hitinfo/permission.jsp"%>
<%
    ResultPage curpage = (ResultPage) request.getAttribute("result");
    List list = curpage.getList();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="100%" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td width="2%">
						&nbsp;
					</td>
					<td width="72%" class="text_blue_12_c">
						<bean:message key="ecardhit.tab.view" />
					</td>
					<td width="11%" valign="bottom">
						&nbsp;
					</td>
					<td width="15%" align="right" valign="middle" nowrap
						class="text_brown">
						&nbsp;
					</td>
				</tr>
			</table>
		</td>
	</tr>
</table>
<table width="100" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td height="5"></td>
	</tr>
</table>
<table width="100%" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top" align=center>
			<!-- content table -->
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td valign="bottom">
						&nbsp;
						<br>
						<%
							Iterator it = list.iterator();
							while (it.hasNext()) {
								HashMap hitInfo = (HashMap) it.next();
								String infoType = (String) hitInfo.get("infoType");
								String[] urlInfos = TypeMappingUtil.getPortletURLInfo(infoType);
								if (infoType.equals(EcardConstants.INFORMATION_DOCUMENT_TYPE)) {
									String[] attachIds = StringUtil.split((String) hitInfo
											.get("attachments"), EcardConstants.DELIMITER);
						%>
						<a href="<%=urlInfos[1]%>?id=<%=attachIds[0]%>"
							class="blue_link_line"><%=hitInfo.get("title")%>(<%=format.format((Date) hitInfo.get("createDate"))%>)</a>
						&nbsp;&nbsp;
						<%
							} else if (infoType.indexOf(EcardConstants.INFORMATION_FAQ_TYPE
										+ ".") == 0) {
						%>
						<a
							href="<portlet:renderURL portletName="<%=urlInfos[0]%>" windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&subid=<%=infoType%>"
							class="blue_link_line"><%=hitInfo.get("title")%>(<%=format.format((Date) hitInfo.get("createDate"))%>)</a>
						&nbsp;&nbsp;
						<%
							} else {
						%>
						<a
							href="<portlet:renderURL portletName="<%=urlInfos[0]%>" windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&id=<%=hitInfo.get("infoId")%>"
							class="blue_link_line"><%=hitInfo.get("title")%>(<%=format.format((Date) hitInfo.get("createDate"))%>)</a>
						&nbsp;&nbsp;
						<%
							}
						%>
						<br>
						<%
							}
						%>
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