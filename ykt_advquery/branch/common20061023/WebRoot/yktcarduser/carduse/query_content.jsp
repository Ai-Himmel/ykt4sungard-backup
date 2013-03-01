<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="test.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
</head>
<%String beginDate21d = session.getAttribute("begindate21d").toString();%>

<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktcarduser/carduse/query_result.do"
	name=queryresuleform method=post ><td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.date" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate21d%>"/></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<script language="JavaScript">
					
					Calendar.setup({
				        inputField     :    "begindate",     // id of the input field
				        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
				        align          :    "Tr",           // alignment (defaults to "Bl")
				        singleClick    :    true
				    });
				    
				</script>
				
				<td width="8%" nowrap="nowrap">&nbsp;</td>
				<td width="29%" nowrap="nowrap">&nbsp;</td>
				<td width="10%" nowrap="nowrap"><a href="#"></a></td>
				
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
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
