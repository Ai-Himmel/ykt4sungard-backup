<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>

<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%
  String  opeId = "";
        if(session.getAttribute("opeId")!=null){
        	opeId = session.getAttribute("opeId").toString();
         }
  
  String  opename ="";
        if(session.getAttribute("opename")!=null){
        	opename = session.getAttribute("opename").toString();
        } 
    
%>
<form action="<%= ContextUtil.getCtxPath(request)%>/adminresult.do"
	name=oneaccountdetailform method=post >
<table width="598" height="27" border="0" cellpadding="0" cellspacing="0" background="<%=ContextUtil.getCtxPath(request)%>/commons/images/tit.jpg">
  <tr>
    <td width="14">&nbsp;</td>
    <td width="584"><bean:message key="eadvquery.title.usermanage" /></td>
  </tr>
</table>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>

	<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<br/>
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			
			<tr>
			   <td height="25" align="right" nowrap="nowrap"><bean:message key="eadvquery.userid" /></td>
				<td >
				 <input name="opeId" type="text" value="<%=opeId%>"  />
				</td>
				
				
				
				<td height="25" align="right" nowrap="nowrap"><bean:message key="eadvquery.username" /></td>
				<td align="left">
				 <input name="opename" type="text"  value="<%=opename%>" />
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
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>

</tr></table>
</form>
