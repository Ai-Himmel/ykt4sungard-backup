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
<%String remark = configs.getString("savingsortcont"); %>
<%String querytype24="0";
		if (null!=session.getAttribute("querytype24")){
		querytype24 = session.getAttribute("querytype24").toString();
	}
	String queryType = ParamUtil.getString(request, "querytype", querytype24);%>
<%String beginDate24d = session.getAttribute("begindate24d").toString();%>
<%String endDate24d = session.getAttribute("enddate24d").toString();%>
<%String beginDate24m = session.getAttribute("begindate24m").toString();%>
<%String endDate24m = session.getAttribute("enddate24m").toString();%>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktcarduser/savingsort/savingsort_queryresult.do"
	name=savingsortform method=post >
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>

<td>
	<input type=hidden name="querytype" value="<%=queryType%>">
<table width="94%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
		<td nowrap="nowrap"><bean:message key="query.type"/><input
			name="statType" type="radio" value="bydate" 
			<c:if test='<%= queryType.equals("0")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('0')" /><bean:message key="query.bydate" />
		<input type="radio"
			name="statType" value="bymonth"
			<c:if test='<%= queryType.equals("1")%>'>
			checked
			</c:if>
			onclick="javascript:setQueryType('1')" /><bean:message key="query.bymonth" />
		</td>
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
				<td height="25" align="right" nowrap="nowrap"><bean:message
					key="query.savingtype" /></td>
				<td nowrap="nowrap"><select name="seritype" style="width:155">
					<!--<option value="240001"><bean:message key="saving.seri" /></option>-->
					<!-- <option value="240155"><bean:message key="saving.inside" /></option>-->
					<option value="847106"><bean:message key="saving.cash" /></option>
					<option value="930034"><bean:message key="saving.pos" /></option>
					<!-- <option value="8471062"><bean:message key="saving.ticket" /></option>-->
					<!-- <option value="8471063"><bean:message key="saving.outlay" /></option>-->
					<!-- <option value="8471064"><bean:message key="saving.other" /></option>-->
				</select></td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate24d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate24d%>" /></td>
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
				<td width="66%" ><bean:message key="system.note" /><%=remark %></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();" ><bean:message key="btn.query" /></button>
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
				<td height="25" align="right" nowrap="nowrap"><bean:message
					key="query.savingtype" /></td>
				<td nowrap="nowrap"><select name="seritype" style="width:155">
					<option value="847106"><bean:message key="saving.cash" /></option>
					<option value="930034"><bean:message key="saving.pos" /></option>
				</select></td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.beginmonth" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" value="<%=beginDate24m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.endmonth" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" value="<%=endDate24m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_enddate" /></a></td>
					<script language="JavaScript">
						
						Calendar.setup({
					        inputField     :    "begindate",     // id of the input field
					        weekNumbers		:	<%=GetProperty.getProperties("format.byweek",getServletContext())%>,
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
					        button         :    "f_trigger_begindate",  // trigger for the calendar (button ID)
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
				<td width="66%" ><bean:message key="system.note" /><%=remark %></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();" ><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();" ><bean:message key="btn.clear" /></button>
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
		<table width="96%" border="0" align="center" cellpadding="0"
			cellspacing="0">
			<tr>
				<td height="25" align="right" nowrap="nowrap"><bean:message
					key="query.savingtype" /></td>
				<td nowrap="nowrap"><select name="seritype" style="width:155">
					<option value="240001"><bean:message key="saving.seri" /></option>
					<option value="240155"><bean:message key="saving.inside" /></option>
					<option value="847105"><bean:message key="saving.cash" /></option>
					<option value="930034"><bean:message key="saving.pos" /></option>
					<option value="8471062"><bean:message key="saving.ticket" /></option>
					<option value="8471063"><bean:message key="saving.outlay" /></option>
					<option value="8471064"><bean:message key="saving.other" /></option>
				</select></td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
				<td nowrap="nowrap">&nbsp;</td>
			</tr>
			<tr>
				<td width="8%" align="right" nowrap="nowrap"><bean:message
					key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="begindate" readonly="readonly" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22" border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap"><bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap"><input type="text" name="enddate" readonly="readonly" /></td>
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
				<td width="66%" ><bean:message key="system.note" /><%=remark %></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();" ><bean:message key="btn.query" /></button>
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
		document.savingsortform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/yktcarduser/savingsort/savingsort_query.jsp?querytype=' + typevalue;
	}
</script>
