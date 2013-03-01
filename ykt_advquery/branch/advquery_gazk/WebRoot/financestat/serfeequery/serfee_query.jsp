<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
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
<%
  String patchno ="";
  if (null!=session.getAttribute("patchno")){
  	patchno = session.getAttribute("patchno").toString();
  }
  String certno ="";
  if (null!=session.getAttribute("certno")){
  	certno = session.getAttribute("certno").toString();
  }
  String classno ="";
  if (null!=session.getAttribute("classno")){
	classno = session.getAttribute("classno").toString();
  }
  String stuempno="";
  if(null!=session.getAttribute("stuempno")){
  	stuempno = session.getAttribute("stuempno").toString();
  }
  Object SerFeeQuery = null;
  SerFeeQuery = session.getAttribute("SerFeeQuery");
%>
<script>
    function print(){
     
      window.open('<%= ContextUtil.getCtxPath(request)%>/serfeeprint.do',"a","toolbar=no,location=(100,100),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=600,height=500");
      
    }
</script>

<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/financestat/serfeequery/serfee_queryresult.do"
	name=oneaccountdetailform method=post >
	<td>
	
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="serfee.classno" /></td>
				<td nowrap="nowrap"><input type="text" name="classno" value="<%=classno%>"></td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="serfee.patchno" /></td>
				<td nowrap="nowrap"><input type="text" name="patchno" value="<%=patchno%>"></td>
				
			</tr>
			<tr>
				
				<td height="25" align="right" nowrap="nowrap"><bean:message key="serfee.stuempno" /></td>
				<td nowrap="nowrap"><input type="text" name="stuempno" value="<%=stuempno%>"></td>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="serfee.certno" /></td>
				<td nowrap="nowrap"><input type="text" name="certno" value="<%=certno%>"></td>
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
				<%if(null != SerFeeQuery){%>
				<button onclick="print()"><bean:message key="btn.print" /></button>
				<%}%>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</form>
</tr></table>
