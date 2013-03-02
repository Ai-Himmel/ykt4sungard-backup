<%@ include file="/html/extportlet/advquery/init.jsp"%>


<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.CARDUSE_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.CARDUSE_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.CARDUSE_ERROR_EXIST))%> </font>
</c:if>

<html:form action="/ext/carduse_queryresult" method="POST"
	onsubmit="submitPortletForm(this); return false;">
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr><td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.date" /></td>
				<td width="20%" nowrap="nowrap">
				<html:text property="carduse_enddate" styleId="carduse_enddate"/>
				</td>
				<td width="20%" nowrap="nowrap">
					<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'carduse_enddate'})"
													 /> </a>
					</td>
				<td width="8%" nowrap="nowrap">&nbsp;</td>
				<td width="29%" nowrap="nowrap">&nbsp;</td>
				<td width="10%" nowrap="nowrap"></td>
				
			</tr>
		</table>
		</td>
	</tr>
</table>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0" bgcolor="#f8f8f8">
	<tr>
		<td height="30">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="66%" class="red_text"><bean:message key="system.note" /></td>
				<td width="34%" align="center">
				<button onclick="document.carduseform.submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.carduseform.reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</tr></table>
</html:form>