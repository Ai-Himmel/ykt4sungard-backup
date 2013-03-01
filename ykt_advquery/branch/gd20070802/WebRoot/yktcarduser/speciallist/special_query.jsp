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
<%String beginDate27d = session.getAttribute("begindate27d").toString();%>
<%String endDate27d = session.getAttribute("enddate27d").toString();%>
<%String bnum = "0";
	if (null!=session.getAttribute("bnum")){
		bnum = session.getAttribute("bnum").toString();}%>
<%String enum11 = "0";
	if (null!=session.getAttribute("enum11")){
		enum11 = session.getAttribute("enum11").toString();}%>
<%String bfee = "0";
	if (null!=session.getAttribute("bfee")){
		bfee = session.getAttribute("bfee").toString();}%>
<%String efee = "0";
	if (null!=session.getAttribute("efee")){
		efee = session.getAttribute("efee").toString();}%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktcarduser/speciallist/speciallist_queryresult.do"
	name=oneaccountform method=post >
	<td>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="special.bnum"/></td>
				<td nowrap="nowrap"><input type="text" name="bnum" value="<%=bnum%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				        <td nowrap="nowrap"><bean:message key="special.enum"/></td>
				<td nowrap="nowrap"><input type="text" name="enum11" value="<%=enum11%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message key="special.bfee"/></td>
				<td nowrap="nowrap"><input type="text" name="bfee" value="<%=bfee%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
				        <td nowrap="nowrap"><bean:message key="special.efee"/></td>
				<td nowrap="nowrap"><input type="text" name="efee" value="<%=efee%>"></td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate27d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><div align="right"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate27d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
						    ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					</script>
					
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
</form>
</tr></table>
