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
<%String beginDate410d = session.getAttribute("begindate410d").toString();%>
<%String endDate410d = session.getAttribute("enddate410d").toString();%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/shopbusinessquery/result.do"
	name=ticketform method=post >
	<td>
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
</table>
<table width="98%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td height="40"><table width="96%" border="0" align="center" cellpadding="0" cellspacing="0">
	<tr>
	  <td align="right" nowrap="nowrap"><bean:message key="query.begindate" /></td>
		<td nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate410d%>"/>
		  <a href="#"><img
			src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
			border="0"  id="f_trigger_begindate" /></a>		  <a href="#"></a></td>
		<td align="right" nowrap="nowrap"><bean:message key="query.enddate" /></td>
		<td colspan="6" nowrap="nowrap"><a href="#">
		  <input type="text" name="enddate" readonly="readonly" value="<%=endDate410d%>"/>
		</a><a href="#"></a><a href="#"><img
			src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
			border="0"  id="f_trigger_enddate" /></a></td>
		<script language="JavaScript">
				
				Calendar.setup({
			        inputField     :    "begindate",     // id of the input field
			        weekNumbers		:	false,
			        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
			    	ifFormat	   :	"%Y-%m-%d",
			        align          :    "Tr",           // alignment (defaults to "Bl")
			        singleClick    :    true
			    });
			    
				Calendar.setup({
			        inputField     :    "enddate",     // id of the input field
			        weekNumbers		:	false,
			        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
			    	ifFormat	   :	"%Y-%m-%d",
			        align          :    "Tr",           // alignment (defaults to "Bl")
			        singleClick    :    true
			    });
			</script>
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
				</button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</form>
</tr></table>
