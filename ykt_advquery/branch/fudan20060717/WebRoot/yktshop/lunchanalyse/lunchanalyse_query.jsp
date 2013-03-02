<%@ page import="com.kingstargroup.advquery.common.GetProperty" %>
<%@ page import="com.kingstargroup.advquery.util.ParamUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.LunchUtil" %>
<%@ page import="com.kingstargroup.advquery.hibernate.util.CutTypeUtil" %>
<%@ page import="com.kingstargroup.advquery.cuttype.TCifCuttypefee" %>
<%@ page import="java.util.Map" %>
<%@ include file="/commons/init.jsp" %>
<%@ include file="/commons/top_calendar.jsp"%>
<%@ include file="permission.jsp" %>
<html xmlns="http://www.w3.org/1999/xhtml">
<head>
<title><bean:message key="system.name" /></title>
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/style.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/ele.css" rel="stylesheet" type="text/css" />
<link href="<%= ContextUtil.getCtxPath(request)%>/commons/styles/frame.css" rel="stylesheet" type="text/css" />
<script language="JavaScript" src="<%= ContextUtil.getCtxPath(request)%>/js/util.js"></script>
</head>
<%String queryType = ParamUtil.getString(request, "querytype", "1");%>
<%String userName = session.getAttribute("username").toString();%>
<%String beginDate35d = session.getAttribute("begindate35d").toString();%>
<%String endDate35d = session.getAttribute("enddate35d").toString();%>
<%String beginDate35m = session.getAttribute("begindate35m").toString();%>
<%String endDate35m = session.getAttribute("enddate35m").toString();%>
<%
	List feeTypeList = LunchUtil.getFeeType();
	List cutTypeList = CutTypeUtil.getCutType();
%>
<table width="100%" border="0" align="center" cellpadding="0"
	cellspacing="0">
	<tr>
<form action="<%= ContextUtil.getCtxPath(request)%>/yktshop/lunchanalyse/lunchanalyse_queryresult.do"
	name=lunchanalyseform method=post >
	<td>
	<input type=hidden name="querytype" value="0">
	<input type=hidden name=operCode value='<%= userName%>'>
<table width="96%" border="0" align="center" cellpadding="0"
	cellspacing="6">
	<tr>
		<td nowrap="nowrap" width="50%">
		<bean:message key="query.type"/>
		<input name="statType" type="radio" value="bydate" 
			<c:if test='<%= queryType.equals("0")%>'>checked</c:if>
			onclick="javascript:setQueryType('0')" /><bean:message key="query.bydate" />
		<input type="radio" name="statType" value="bymonth"
			<c:if test='<%= queryType.equals("1")%>'>checked</c:if>
			onclick="javascript:setQueryType('1')" /><bean:message key="query.bymonth" />
		</td>
		<TD nowrap="nowrap" align="left" width="50%">
			<bean:message key="lunchanalyse.daylimit" />	
			<select name="dayLimit">
				<option>&gt;&#61;</option>
				<option>&gt;</option>
				<option>&#61;</option>
				<option>&lt;&#61;</option>
				<option>&lt;</option>
			</select>
			<input name="day" maxlength="4" size="4"/>
			<bean:message key="lunchanalyse.day" />
		</TD>
	</tr>
	<tr>
		<td nowrap="nowrap">
			<bean:message key="lunchanalyse.meallimit" />	
			<select name="mealLimit">
				<option>&gt;&#61;</option>
				<option>&gt;</option>
				<option>&#61;</option>
				<option>&lt;&#61;</option>
				<option>&lt;</option>
			</select>
			<input name="meal" maxlength="4" size="4"/>
			<bean:message key="lunchanalyse.amount" />
		</td>
		<td>
			<bean:message key="lunchanalyse.moneylimit" />	
			<select name="moneyLimit">
				<option>&lt;&#61;</option>
				<option>&lt;</option>
				<option>&#61;</option>
				<option>&gt;&#61;</option>
				<option>&gt;</option>
			</select>
			<input name="money" maxlength="8" size="8"/>
			<bean:message key="lunchanalyse.money" />
		</td>
	</tr>
	<tr>
		<td nowrap="nowrap" width="50%" colspan="2">
			<bean:message key="lunch.cuttype"/>
			<select name="cuttype">
				<option value=""></option>
				<%for(int i=0;i<cutTypeList.size();i++){
					TCifCuttypefee row = (TCifCuttypefee)cutTypeList.get(i);
				%>
					<option value="<%=row.getCutType() %>" label="<%=row.getTypeName() %>"/>
				<%
				}
				%>	
			</select>
		</td>
	</tr>
	<tr>
		<td nowrap="nowrap" width="50%" colspan="2">
			<bean:message key="lunch.feetype"/>
			<select name="feetype">
				<option value=""></option>
				<%for(int i=0;i<feeTypeList.size();i++){
					Map row = (Map)feeTypeList.get(i);
					String feeType = row.get("feeType")==null?"":row.get("feeType").toString();
					String feeName = row.get("feeName")==null?"":row.get("feeName").toString();
				%>
					<option value="<%=feeType %>" label="<%=feeName %>"/>
				<%
				}
				%>	
			</select>
		</td>
	</tr>
	<tr>
		<td nowrap="nowrap" width="50%">
			<bean:message key="lunch.stuempno"/>&nbsp;&nbsp;&nbsp;&nbsp;<input name="stuempno" type="text" />
		</td>
		<TD nowrap="nowrap" align="left" width="50%">
			<bean:message key="lunch.custname"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input name="custname" type="text" />
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
				<td width="8%" nowrap="nowrap"><bean:message key="query.begindate" /></td>
				<td width="20%" nowrap="nowrap">&nbsp;<input type="text" name="begindate" readonly="readonly" value="<%=beginDate35d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap">&nbsp;&nbsp;<bean:message key="query.enddate" /></td>
				<td width="20%" nowrap="nowrap">&nbsp;&nbsp;<input type="text" name="enddate" readonly="readonly" value="<%=endDate35d%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_enddate" /></a></td>
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
				<td width="66%" class="red_text"></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
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
				<td width="8%" nowrap="nowrap"><bean:message key="query.beginmonth" /></td>
				<td width="20%" nowrap="nowrap">&nbsp;<input type="text" name="begindate" readonly="readonly" value="<%=beginDate35m%>" /></td>
				<td width="20%" nowrap="nowrap"><a href="#"><img
					src="<%= ContextUtil.getCtxPath(request)%>/commons/images/search.jpg" width="33" height="22"
					border="0" id="f_trigger_begindate" /></a></td>
				<td width="8%" nowrap="nowrap">&nbsp;&nbsp;<bean:message key="query.endmonth" /></td>
				<td width="20%" nowrap="nowrap">&nbsp;&nbsp;<input type="text" name="enddate"  readonly="readonly" value="<%=endDate35m%>" /></td>
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
					        button         :    "f_trigger_enddate",  // trigger for the calendar (button ID)
					    	ifFormat	   :	"<%=GetProperty.getProperties("format.month",getServletContext())%>",
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
				<td width="66%" class="red_text"></td>
				<td width="34%" align="center">
				<button onclick="document.forms[0].submit();"><bean:message key="btn.query" /></button>
				<button onclick="document.forms[0].reset();"><bean:message key="btn.clear" /></button>
				</td>
			</tr>
		</table>
		</td>
	</tr>
</table>
</c:if>
</td>
</form>
</tr></table>
<script>
	function setQueryType(typevalue) {
		document.lunchanalyseform.querytype.value = typevalue;
		self.location = '<%= ContextUtil.getCtxPath(request)%>/yktshop/lunchanalyse/lunchanalyse_query.jsp?querytype=' + typevalue;
	}
</script>
