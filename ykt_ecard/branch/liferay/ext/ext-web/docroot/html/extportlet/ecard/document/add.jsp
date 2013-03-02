<%@ include file="/html/extportlet/ecard/document/init.jsp"%>
<%@ include file="/html/extportlet/ecard/document/permission.jsp"%>
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
						<bean:message key="ecarddoc.tab.adddoc" />
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
		<td>
			&nbsp;
		</td>
		<td valign="top" align=center>
			<html:form action="/ext/ecarddocadd_result" method="POST"
				enctype="multipart/form-data">
				<html:hidden property="cmd" />
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td width="5%">
							&nbsp;
						</td>
						<td width="95%">
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
						<td width="15%" valign="baseline" class="text_or_12">
							<bean:message key="ecard.title" />
							:
						</td>
						<td width="60%" valign="baseline" class="text_or_12" align="left">
							<html:text property="title" size="60" />
						</td>
						<td width="29%" align=left>
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
						<td width="15%" valign="top" class="text_or_12">
							<bean:message key="ecardnews.tab.upload" />
							:
						</td>
						<td width="60%" valign="baseline" class="text_or_12" align="left">
							<html:file property="theFile" styleClass="text_or_12" size="60"/>
						</td>
						<td width="29%" valign="top" align=left>
							<font style="font-size: 11;"><html:errors
									property="content" /> <c:if
									test="<%=SessionErrors.contains(request, FileSizeException.class
							.getName())%>">
									<bean:message key="ecard.error.filesize"
										arg0="<%=String.valueOf(EcardConstants.DOC_MAX_SIZE)%>" />
								</c:if> <c:if
									test="<%=SessionErrors.contains(request, FileNameException.class
							.getName())%>">
									<bean:message key="ecard.error.filename"
										arg0='<%=PropsUtil.get("info.upload.document.extension")%>' />
								</c:if> </font>
						</td>
					</tr>
				</table>
				<table width="100%" height="1" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td bgcolor="#e1e1e2"></td>
					</tr>
				</table>
				<table width="100%" height="5" border="0" cellpadding="0"
					cellspacing="0">
					<tr>
						<td></td>
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
		</td>
		<td>
			&nbsp;
		</td>
	</tr>
</table>
<script>			
		function setCmdType(cmd) {
			document.all.cmd.value = cmd;
		}	
	</script>
<script>
	function renderAdminPage() {
		self.location = '<portlet:renderURL windowState="<%=WindowState.MAXIMIZED.toString()%>" portletMode="<%=PortletMode.VIEW.toString()%>"><portlet:param name="struts_action" value="/ext/ecarddocadmin" /></portlet:renderURL>';
	}
	</script>