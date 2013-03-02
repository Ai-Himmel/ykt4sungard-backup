<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
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
<%String beginDate99 = session.getAttribute("begindate99").toString();%>
<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
<form action="<%= ContextUtil.getCtxPath(request)%>/yktrun/createdata/createdata_queryresult.do" name=createdata method=post >
<input type=hidden name=cmd value="query">
<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="26%" nowrap="nowrap"><bean:message key="query.begindate" />
					<input type="text" name="begindate" readonly="readonly" value="<%=beginDate99%>" />
				</td>
				<td width="10%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0"  id="f_trigger_begindate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
					</script>
				<td width="60%" nowrap="nowrap">
					<button onclick="javascript:setCmdValue('query');"><bean:message key="btn.query" /></button>
					<button onclick="javascript:setCmdValue('export');"><bean:message key="btn.exportPDF" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</td>
</form>
</table>
</html>
<script>
  	function setCmdValue(cmd) {      		
  		document.createdata.cmd.value = cmd;
  		document.createdata.submit();
  	}
</script>
