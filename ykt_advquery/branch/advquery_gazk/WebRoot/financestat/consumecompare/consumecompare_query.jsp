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
<%String querytype46="0";
		if (null!=session.getAttribute("querytype46")){
		querytype46 = session.getAttribute("querytype46").toString();
	}
	String queryType = ParamUtil.getString(request, "querytype", querytype46);%>
<%String beginDate46d = session.getAttribute("begindate46d").toString();%>
<%String endDate46d = session.getAttribute("enddate46d").toString();%>
<%String beginDate46m = session.getAttribute("begindate46m").toString();%>
<%String endDate46m = session.getAttribute("enddate46m").toString();%>
<%String beginDate46w = session.getAttribute("begindate46w").toString();%>
<%String endDate46w = session.getAttribute("enddate46w").toString();%>
<form action="<%= ContextUtil.getCtxPath(request)%>/financestat/consumecompare/allconsumecompare_queryresult.do"
	name=consumecompareform method=post >
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>

	<td>
	<input type=hidden name="querytype" value="<%=queryType%>">
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td nowrap="nowrap" width="50%"><bean:message key="query.type"/><input
			name="statType" type="radio" value="bydate" 
			<c:if test='<%= queryType.equals("0")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('0')" /><bean:message key="query.bydate" />
		<input type="radio"
			name="statType" value="byweek"
			<c:if test='<%= queryType.equals("2")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('2')" /><bean:message key="query.byweek" />
		<input type="radio"
			name="statType" value="bymonth"
			<c:if test='<%= queryType.equals("1")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('1')" /><bean:message key="query.bymonth" />
		</td>
		<TD nowrap="nowrap"align="left" width="50%"><bean:message key="showtitle.type"/>
			<INPUT name="showType" type="radio" checked="checked" value = "line"/><bean:message key="showpic.line"/>
			<INPUT name="showType" type="radio" value = "bar"/><bean:message key="showpic.bar"/>
			<INPUT name="showType" type="radio" value = "stack"/><bean:message key="showpic.stack"/>
			
		</TD>
	</tr>
</table>
<c:if test='<%= queryType.equals("0")%>'>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<TD nowrap="nowrap" align="left" width="50%">
				<bean:message key="query.stat.type"/><input type="radio" name="moneyornum" value="money" checked="checked" align="left"><bean:message key="query.money" />
				<input type="radio" name="moneyornum" value="num"><bean:message key="query.num" />
				</TD>
			</tr>
		</table>
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="7%" nowrap="nowrap"><bean:message key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate46d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate46d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("1")%>'>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<TD nowrap="nowrap" align="left" width="50%">
				<bean:message key="query.stat.type"/><input type="radio" name="moneyornum" value="money" checked="checked" align="left"><bean:message key="query.money" />
				<input type="radio" name="moneyornum" value="num"><bean:message key="query.num" />
				</TD>
			</tr>
		</table>
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="7%" nowrap="nowrap"><bean:message key="query.beginmonth" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate46m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.endmonth" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate46m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
<c:if test='<%= queryType.equals("2")%>'>
<table width="98%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td height="40">
		<table width="94%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<TD nowrap="nowrap" align="left" width="50%">
				<bean:message key="query.stat.type"/><input type="radio" name="moneyornum" value="money" checked="checked" align="left"><bean:message key="query.money" />
				<input type="radio" name="moneyornum" value="num"><bean:message key="query.num" />
				</TD>
			</tr>
		</table>
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td width="7%" nowrap="nowrap"><bean:message key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate46w%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate46w%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
					        align          :    "Tr",           // alignment (defaults to "Bl")
					        singleClick    :    true
					    });
					    
						Calendar.setup({
					        inputField     :    "enddate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.date",getServletContext())%>",
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
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
				<button onclick="document.forms[0].submit();"><bean:message
					key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
</td>

</tr></table>
</form>
<script>
	function setQueryType(typevalue) {
		document.consumecompareform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/financestat/consumecompare/consumecompare_query.jsp?querytype=' + typevalue;
	}
</script>
