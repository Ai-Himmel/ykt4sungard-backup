<%@ include file="/html/extportlet/advquery/init.jsp"%>
  
<c:if
	test="<%=SessionErrors.contains(request,
								EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST)%>">
	<font class="portlet-msg-error"> <%=LanguageUtil.format(pageContext,
								EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST, SessionErrors.get(
										request, EcardConstants.QUERYACCOUNTDTL_ERROR_EXIST))%> </font>
</c:if>
<html:form action="/ext/accounttransdtl_queryresult" method="POST"
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
				<td  width="7%" height="25"  nowrap="nowrap"><bean:message
					key="query.empno" /></td>
				<td  width="20%" nowrap="nowrap">
				<html:text property="custId"/>
				</td>
				<td  width="20%"></td>
				<td width="8%" nowrap="nowrap"><bean:message
					key="query.stuempno" />&nbsp;</td>
				<td width="20%" nowrap="nowrap">
				 <html:text property="stuempno" />
				</td>
				<td width="20%" height="25"  nowrap="nowrap"></td>
			</tr>
			<tr>
				<td width="7%" nowrap="nowrap">
						<bean:message key="query.begindate" />	</td>
				<td width="20%" nowrap="nowrap">
						<html:text property="queryaccountdtl_begindate" styleId="queryaccountdtl_begindate"></html:text>
				</td>
				<td width="20%" nowrap="nowrap">
						<a href="javascript:void(0);">
						<img   			src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'queryaccountdtl_begindate'})" /> </a>
				</td>
				<td width="8%" nowrap="nowrap">
											<bean:message key="query.enddate" />
				</td>
				<td width="20%" nowrap="nowrap">
											<html:text property="queryaccountdtl_enddate" styleId="queryaccountdtl_enddate"></html:text>
				</td>
			    <td width="20%" nowrap="nowrap">
											<a href="javascript:void(0);"><img
													src="/html/extthemes/classic/images/advquery/search.jpg"
													width="33" height="22" border="0"
													onclick="WdatePicker({el:'queryaccountdtl_enddate'})" /> </a>
				</td> 
						

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
				<input type="button" onclick="document.queryaccountdtlform.submit();" value="<bean:message key="btn.query" />">
				<input type="reset" onclick="document.queryaccountdtlform.reset();" value="<bean:message key="btn.clear" />">
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</tr></table>
</html:form>