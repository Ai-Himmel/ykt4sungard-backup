<%@ include file="/commons/init.jsp" %>
<%String error = request.getAttribute("errorcont").toString();%>
<table width="100%" height="10" border="0" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="50"></td>
	</tr>
</table>
<table width="354" height="137" border="0" align="center"
	cellpadding="0" cellspacing="0" background="<%= ContextUtil.getCtxPath(request)%>/commons/images/err.jpg">
	<tr>
		<td valign="top">
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td width="5%" height="24">&nbsp;</td>
				<td width="95%"><bean:message key="system.error" /></td>
			</tr>
		</table>
		<table width="100%" border="0" cellspacing="0" cellpadding="0">
			<tr>
				<td width="45%" height="96">&nbsp;</td>
				<td width="55%"><%=error%> </td>
			</tr>
		</table>
		</td>
	</tr>
</table>
