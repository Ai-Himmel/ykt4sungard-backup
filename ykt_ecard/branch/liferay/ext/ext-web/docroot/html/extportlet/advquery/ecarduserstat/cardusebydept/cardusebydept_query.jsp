<%@ include file="/html/extportlet/advquery/init.jsp"%>

<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.CARDUSEBYDEPT_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.CARDUSEBYDEPT_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.CARDUSEBYDEPT_ERROR_EXIST))%> </font>
</c:if>


<html:form  action="/ext/cardusebydept_queryresult" method="POST"
	onsubmit="submitPortletForm(this); return false;">
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="25" align="left" nowrap="nowrap">
				<bean:message		key="query.depno" /> 
					<html:select property="deptcode">
						<html:options collection="deptList" labelProperty="deptname"  	property="deptcode" />
					</html:select>				
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
				<td width="34%" align="center">
				<button onclick="document.cardusebydeptform.submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.cardusebydeptform.reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</tr></table>
</html:form>