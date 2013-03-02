<%@ include file="/html/extportlet/ecard/hitinfo/init.jsp"%>
<%@ include file="/html/extportlet/ecard/hitinfo/permission.jsp"%>
<%
	Object obj = request.getAttribute("HitInputForm");
	String mapInfoTitle = "";
	if (obj != null) {
		String mapInfoId = (String) ((DynaValidatorForm) obj)
				.get("mapInfoId");
		if (!mapInfoId.equals("")) {
			mapInfoTitle = EcardInformationServiceUtil.getInfoById(
					mapInfoId).getInfoTitle();
		}
	}
%>
<table width="719" height="29" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td>
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td width="2%">
						&nbsp;
					</td>
					<td width="72%" class="text_blue_12_c">
						<bean:message key="ecardhit.tab.add" />
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
<table width="719" border="0" cellspacing="0" cellpadding="0">
	<tr>
		<td width="9" height="7"></td>
		<td height="7"></td>
		<td width="6" height="7"></td>
	</tr>
	<tr>
		<td>
			&nbsp;
		</td>
		<td valign="top" align=center>
			<!-- content table -->
			<html:form action="/ext/ecardhitadd_result" method="POST" 
				onsubmit="javascript:submitPortletForm(this); return false;">
				<html:hidden property="cmd" />
				<html:hidden property="mapInfoId" />
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="8%">
							&nbsp;
						</td>
						<td width="92%">
							<c:if
								test="<%=SessionErrors.contains(request,
							EcardConstants.ADD_INFO_SUCCEED)%>">
								<font style="font-size: 11;"> <bean:message
										key="ecard.error.addinfosucceed" /> </font>
							</c:if>
						</td>
					</tr>
				</table>
				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="10%" valign="baseline" class="text_or_12">
							<bean:message key="ecard.title" />
							:
						</td>
						<td align=left width="70%" valign="baseline" class="text_or_12">
							<html:text property="title" size="60" />
						</td>
						<td width="20%" align=left>
							<font style="font-size: 11;"><html:errors property="title" />
							</font>
						</td>
					</tr>
				</table>


				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>

				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="10%" valign="baseline" class="text_or_12">
							<bean:message key="ecardhit.content.mapinfo" />
							:
						</td>
						<td align=left width="70%" valign="baseline" class="text_blue_12">
							<%=mapInfoTitle%>
						</td>
						<td width="20%" align=left>
							<font style="font-size: 11;"><html:errors
									property="mapInfoId" /> </font>
						</td>
					</tr>
				</table>


				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
					</tr>
				</table>

				<table width="100%" border="0" cellspacing="0" cellpadding="0">

					<tr>
						<td width="10%" valign="top" class="text_or_12">
							&nbsp;
						</td>
						<td align=left width="75%" valign="baseline" class="text_or_12">
							<iframe name="mapidframe" height="275" width="520"
								frameborder="0"
								src="/html/extportlet/ecard/hitinfo/inner_infolist.jsp"></iframe>
						</td>
						<td width="15%" align=left valign=top>
							<font style="font-size: 11;"> </font>
						</td>
					</tr>
				</table>
				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="89%" height="35" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td align="right">
							<html:submit styleClass="button_blank" property="save"
								value='<%=LanguageUtil.get(pageContext, "ecard.save")%>'
								onclick="javascript:setCmdType('save');" />
							<html:submit property="saveandnext" styleClass="button_blank"
								value='<%=LanguageUtil.get(pageContext, "ecard.saveandnext")%>'
								onclick="javascript:setCmdType('saveandnext');" />
							<html:button property="reset" styleClass="button_blank"
								value='<%=LanguageUtil.get(pageContext, "ecard.reset")%>' />
							<html:button property="add" styleClass="button_blank"
								value='<%=LanguageUtil.get(pageContext, "ecard.goback")%>'
								onclick="javascript:renderAdminPage();" />
						</td>
					</tr>
				</table>
			</html:form>
			<!-- content table -->
		</td>
		<td>
			&nbsp;
		</td>
	</tr>
	<tr>
		<td width="9" height="7"></td>
		<td height="7"></td>
		<td width="6" height="7"></td>
	</tr>
</table>
<script>			
		function setCmdType(cmd) {
			document.HitInputForm.cmd.value = cmd;
		}
		function renderAdminPage() {
			self.location = '<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecardhitadmin" /></portlet:renderURL>';
		}
	</script>