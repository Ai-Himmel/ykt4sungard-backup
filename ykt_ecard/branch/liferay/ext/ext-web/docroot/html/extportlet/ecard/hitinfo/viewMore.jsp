<%@ include file="/html/extportlet/ecard/hitinfo/init.jsp"%>

<%
	ResultPage curpage = (ResultPage) request.getAttribute("result");
    List list = curpage.getList();
	SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd");
%>
<table width="100%" border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td width="2%">
						&nbsp;
					</td>
					<td width="72%" class="text_blue_12_c">
						&nbsp;
					</td>
					<td width="11%" valign="bottom">
						<table border="0" cellspacing="0" cellpadding="0">
							<tr>
								<td width="13" align="right">
									<c:if test="<%=curpage.isPreviousPage()%>">
										<a href="javascript:goto('<%=curpage.getPage() - 1%>')"> <img
												align="middle"
												src="/html/extthemes/classic/images/ecard/left.gif"
												width="13" height="9" border="0"> </a>
									</c:if>
								</td>
								<td width="40" align="center" class="text_brown">
									<%=curpage.getPage() + 1%>/<%=curpage.getTotalPage()%></td>
								<td width="13">
									<c:if test="<%=curpage.isNextPage()%>">
										<a href="javascript:goto('<%=curpage.getPage() + 1%>')"> <img
												align="middle"
												src="/html/extthemes/classic/images/ecard/right.gif"
												width="13" height="9" border="0">
										</a>
									</c:if>
								</td>
							</tr>
						</table>
					</td>
					<td width="15%" align="right" valign="middle" nowrap
						class="text_brown">
						<bean:message key="ecard.goto" />
						<select name="select2"
							onchange="goto(this.options[this.selectedIndex].value)">
							<%
								for (int i = 1; i <= curpage.getTotalPage(); i++) {
							%>
							<option value="<%=i - 1%>"
								<c:if test="<%=i == (curpage.getPage() + 1)%>">
                      	selected
                      </c:if>><%=i%></option>
							<%
								}
							%>
						</select>
						<bean:message key="ecard.page" />
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
<table width="719" border="0" cellspacing="0" cellpadding="0">

	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top">
			<!-- content table -->

			<table cellpadding="4" cellspacing="0" width="100%">
				<%
					int i = 0;
					Iterator it = list.iterator();
					while (it.hasNext()) {
						HitInfoResult hitInfo = (HitInfoResult) it.next();
						String infoType = hitInfo.getInfoType();
						String[] urlInfos = TypeMappingUtil.getPortletURLInfo(infoType);
				%>
				<tr height="20px">
					<td>
						<img src="/html/extthemes/classic/images/ecard/jiantou.jpg"
							width="8" height="8">
						<%
							if (infoType.equals(EcardConstants.INFORMATION_DOCUMENT_TYPE)) {
									String[] attachIds = StringUtil.split(hitInfo
											.getAttachments(), EcardConstants.DELIMITER);
						%>

						<a href="<%=urlInfos[1]%>?id=<%=attachIds[0]%>"
							class="blue_link_line"><%=hitInfo.getTitle()%>(<%=format.format((Date) hitInfo.getCreateDate())%>)</a>
						&nbsp;&nbsp;
						<%
							} else if (infoType.indexOf(EcardConstants.INFORMATION_FAQ_TYPE
										+ ".") == 0) {
						%>
						<a
							href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&subid=<%=infoType%>"
							class="blue_link_line"><%=hitInfo.getTitle()%>(<%=format.format((Date) hitInfo.getCreateDate())%>)</a>
						&nbsp;&nbsp;
						<%
							} else {
						%>
						<a
							href="<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="<%=urlInfos[1]%>" /></portlet:renderURL>&id=<%=hitInfo.getInfoId()%>"
							class="blue_link_line"><%=hitInfo.getTitle()%>(<%=format.format((Date) hitInfo.getCreateDate())%>)</a>
						&nbsp;&nbsp;
						<%
							}
						%>
					</td>
				</tr>
				<%
					i++;
					}
				%>
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
<script>
function goto(page) {
	self.location = '<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardhitview" /></portlet:renderURL>&page=' + page;
}
</script>