<%@ page import="com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktcarduser/carduseby/cardusestatbycondition_queryresult.do"
	name=carduesbyform method=post >
<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>

				<td height="25" align="left" nowrap="nowrap"><bean:message
					key="query.depno" /> 
					<%
						if (null!=session.getAttribute("depttype")){
					%>
					<input type="text" name="deptno" value="<%=session.getAttribute("depttype")%>" />
					<%}else{%>
					<input type="text" name="deptno" value="" />
					<%}%>
					<!-- 
					<select name="deptno" style="width:180">
					<%
						List deptList = new GetQueryConListDAO().getDeptList();
						String deptType = "";
						if (null!=session.getAttribute("depttype")){
							deptType = session.getAttribute("depttype").toString();
						}
						Iterator iter = deptList.iterator();
						while (iter.hasNext()){
							Object[] row = (Object[])iter.next();
							if (deptType.equals(row[0])){
					%>
					<option value="<%=row[0]%>" selected="selected"><%=row[1]%></option>
					<%}else{%>
					<option value="<%=row[0]%>"><%=row[1]%></option>
					<%}}%>
					</select>
					-->
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
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</form>
</tr></table>
